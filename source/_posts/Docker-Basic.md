---
categories:
- Software Engineering
date: 2022-02-13 16:08:27
tags: Docker
title: Docker Basic
---

Outline:

* Docker Specification
* Docker  Engine
* Docker Image
* Docker Container
* Docker Security
* Docker Logs
* Docker Management

介绍了docker的基本概念和命令

<!--more-->



# Docker Specification

Docker采用CS模式， 分为Client ， Engine， Index三部分， docker server就是docker引擎， docker index就是docker镜像存储服务（docker hub之类）

* 由于Index是个服务，Client就是个命令行，**我们指的docker一般就是docker engine**， 它是用于**运行和编排容器的基础工具**

* daemon实现了docker engine的api, client和daemon通过本地`IPC/UNIX Socket`通信（`/var/run/docker.sock`, 用`docker --version`可查看二者的通信 )

 

镜像是未运行的容器，二者是类和对象的关系。 

也可以把容器理解为**命名空间的有组织集合**, 详见下文Security -> Linux -> Namespace

## Docker运行时与编排引擎

引擎分社区和企业版，版本号遵循` YY.MM-xx`格式

每个docker主机称为一个docker节点

## 容器生态

docker内置组件都可以替换为第三方组件，“ Batteries  included but removable”

## 开放容器计划

The Open Container Initiative, OCI:    旨在管理容器标准的委员会， 目前已发布两项规范

1. 镜像规范
2. 容器运行时规范

## Docker安装

建议所有的云服务器都按如下流程走一遍

1. ``sudo apt install docker`



2. 最好使用非root用户来使用Docker,此时需要添加非root用户到本地Docker Unix组：`sudo usermod -aG docker [user_name]`
   * 如果当前登陆用户就是要添加进组的用户的话，需要重新登陆才能生效
     * 这意味着，如果该登陆用户是个jenkins登陆用户，则需要在jenkins上断连再重新连接
   
3. 确认安装结果：

   ```shell
   root@lykRemote:~# docker --version
   Docker version 20.10.12, build e91ed57
   root@lykRemote:~# docker system info
   Client:
    Context:    default
    Debug Mode: false
   <Snip>
   
   Server:
    Containers: 1
     Running: 1
     Paused: 0
     Stopped: 0
    Images: 9
    Server Version: 20.10.12
   <Snip>
   ```

4. 设置docker开机启动：

   `systemctl enable docker`

   * 可能遇到

     `Failed to enable unit: Unit file /etc/systemd/system/docker.service is masked`，

     此时需要：

     `systemctl unmask docker`

5. docker启动和关闭：

   ```shell
   systemctl start docker
   ```




## Docker升级

1. 卸载当前Docker：

   `apt-get remove docker docker-engine docker-ce docker.io -y`

   or：

   `apt-get remove docker docker-* -y`

   在之前的版本中，Docker的包名可能有很多个，该command能确保全部删除



2. 安装新版本Docker：同上

## Docker配置

查看docker配置文件位置：

```docker
systemctl status docker
```

默认是`/usr/lib/systemd/system/docker.service`， 但是该文件还引用了别的文件，很不好管理，因此docker又使用`/etc/docker/daemon.json`来进行统一的配置：

```json
// 这里配置日志级别，并配置源为阿里云
{
        
        "debug": true,
        "log-level": "debug",
        "registry-mirrors": ["https://zz1b9pta.mirror.aliyuncs.com"]
}
```

* 该文件不存在就创建
* 可能还会有`~/.docker/daemon/json`, 亲测这个配置文件不起作用

更新配置：

```shell
sudo systemctl daemon-reload
sudo systemctl restart docker
```



查看配置信息：

```shell
docker info
```



### 换阿里源

如上， 编辑`daemon.json`,  然后更新配置就行了

## 插叙: alpine linux

alpine linux是一个超小的Linux镜像,常用来作为基础镜像层节省空间, 除了纯的alpine linux( e.g. `From alpine:latest`)外, 也可以安装很多用户软件的alpine版本( e.g. `FROM node:14.17.4-alpine`)



许多容器是alpine的，在alpine中使用apk命令可能会很慢， 可以进入容器，在容器内**换源**：

Alpine 的源文件为：

```
/etc/apk/repositories
```

这里面的默认配置例如：

```
http://dl-cdn.alpinelinux.org/alpine/v3.11/main
http://dl-cdn.alpinelinux.org/alpine/v3.11/community
```

可以使用以下命令来进行源的切换（阿里云源）：

```
sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories
```



## Docker存储驱动的选择

每个Docker容器都有一个本地存储空间，用于保存层叠的镜像层（Image Layer）和挂载的容器文件系统，默认情况下容器的所有读写操作都发生在其镜像层或者挂载的文件系统中。

本地存储通过存储驱动（Storage Driver）管理. 存储驱动在上层都采用栈式镜像存储和Copy on Write,  但底层支持不同实现（只针对linux, windows只支持一种存储驱动Windows Filter）

尽管存储空间是容器级别，存储驱动是**节点**级别的，即每个Docker host只能选择一种存储驱动，而不能为每个容器选择不同的存储驱动

下面将存储驱动设置为`overlay2`：(  `daemon.json` )

```shell
{
	"storage-driver": "overlay2" 
}
```

* 修改正在运行的Docker host的存储驱动会导致现有镜像和容器在重启之后不可用， 因为每种存储驱动在主机上存储镜像层的位置不同，修改了驱动，docker就找不到原来的镜像和容器了。 切换到原来的存储驱动就可以继续使用

* 如果要在在切换存储驱动后还能使用原来的镜像和容器，需要先将镜像push到docker仓库，修改本地存储引擎并重启，然后从仓库pull镜像
* json的最后一个属性后面不能加**逗号**



检查存储驱动类型：

```shell
docker system info
<Snip>
Storage Driver: overlay2
  Backing Filesystem: extfs
  Supports d_type: true
  Native Overlay Diff: true
  userxattr: false
<Snip>
```



存储驱动介绍：

* Red Hat Enterprise: 低版本内核或低版本docker, 建议使用`Device Mapper` ; 高版本用`overlay2` 

* Ubuntu 4.x内核或更高的版本建议用`overlay2` 

大部分存储驱动不需要额外配置，但`Device Mapper`默认情况下采用`loopback mpunted sparse file`作为底层实现，性能很差，不能用于生产环境，需要手动更换为` LVM`



# Docker Engine

docker server就是docker引擎，而引擎架构如下：

![docker engine archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20engine%20archetecture.png)

* `daemon`: 实现了与docker client通信的REST API.  自身通过`gRPC` 与`containerd`  通信  
* `containerd`: 用于容器生命周期管理 ---- `start|stop|pause|rm`
  * `containerd`虽然管理容器，但不负责创建容器。 它指挥`runc`创建容器
    * `containerd`将docker image转换为 ` OCI bundle`, 并让`runc`基于此创建容器
  * `containerd`后来也用于镜像管理等
* `shim`： 作为容器的父进程，shim职责为：
  * 保持输入输出流的开启
  * 将容器的退出状态反映给`daemon`
* `runc`是OCI容器运行时规范的参考实现，只能用于创建容器。 
  * `runc`每次创建容器就会fork一个进程。创建完毕， 对应的`runc`进程就会退出。 因此即使运行上百个容器也无需维持上百个`runc`进程
  * 一旦`runc`进程退出，相关联的`containerd-shim`进程就会成为容器的父进程

在这个架构下，容器的启动和管理实现了和`daemon`的解耦。 即容器运行时和`daemon`解耦，称为“无守护进程的容器” `daemonless container`。 因此，对`daemon`的维护「升级等**不会影响到运行中的容器**

# Docker Image

## commands

### 搜索镜像

`docekr search` 通过CLI方式在docker hub搜索镜像：

```shell
docker search [OPTIONS] NAME
```

* `NAME`: 仓库名，即`<repository>`



### 下载镜像

```shell
docker image pull <image> #默认从docker hub
docker image pull <registry>/<image>:# 指定镜像仓库服务
```

* `<registory>`:  `<域名/IP>[:端口号]`。默认地址是 Docker Hub(`docker.io`)

### 列出镜像 

列出本机的所有镜像：

```
docker image ls
```

* `--digest`：查看镜像摘要

* `--filter`: 开启过滤，支持如下过滤器

  * `danglng`： 仅返回 True（悬虚镜像）；false（非悬虚镜像）

  * `before`， `since`： 接受`<mage>`: 作为参数，返回在该image之前/后创建的所有镜像

  * `label`： 根据`label`值过滤

  * `reference`： 按名过滤：

    ```shell
     #  仅显示标签为latest的镜像
     docker image ls --filter reference="*.latest"
    ```

* `--format`：

  用 [Go 的模板语法](https://gohugo.io/templates/introduction/)对输出格式化：

  ```shell
  # 列出镜像结果，并且只包含镜像ID和仓库名
  $ docker image ls --format "{{.ID}}: {{.Repository}}"
  
  5f515359c7f8: redis
  05a60462f8ba: nginx
  fe9198c04d62: mongo
  00285df0df87: <none>
  329ed837d508: ubuntu
  329ed837d508: ubuntu
  ```

  

### 查看镜像

列出镜像细节：

```shell
docker image inspect
```

* To list all the images and their respective OSs

  ```sh
  for i in `docker images --format {{.ID}}`; do echo $i `docker image inspect $i |grep Os`; done
  ```

 ### 删除镜像



```shell
docker image rm <image>
```

 删除全部的悬虚镜像：

```shell
docker image prune
```

### 导出镜像为文件

将指定镜像保存成 tar 文件:

```shell
docker save -o [file-name].tar  <image>
```

* `-o `:输出到的文件

## 镜像服务

可完全类比GitHub

![docker registry](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20registry.png)

* docker image存储在镜像仓库服务 Image Registry中，默认是Docker Hub
* Image Registry包含多个镜像仓库Image Repository,
* Image Repository包含多个镜像
  * Docker Hub分为官方和非官方仓库，官方仓库名(`<repository>`) 一般在命名空间顶层，比如 `ubuntu`， 而个人仓库一般是次级命名空间，比如`user_name/ubuntu`

## 镜像标识（\<image>）

镜像标识方法：

* 镜像名：`</repository>:<tag>`
  * 如果没有在仓库名后指定标签，则默认为`tag=latest`，但是， `latest`并没有特殊含义，不能保证这是最新的镜像
  * 同一镜像可以打多个标签
  * 标签是可变的，因此可能不准确
  * 标签会造成悬虚镜像（`dangling image`）:  当构建了一个新镜像，然后为该镜像打了个已经存在的标签，那么docker会将旧镜像上的标签转移到新镜像上，旧镜像就变成了悬虚镜像，标识为`<none>:<onne>`:
* 镜像ID
* 镜像摘要： 基于内容的散列（最准确）

## 镜像体积

镜像下载和上传过程中镜像是保持着压缩状态

Docker Hub 中显示的体积是压缩后的体积

 `docker image ls` 显示的是镜像下载到本地后，展开的大小，准确说，是展开后的各层所占空间的总和，因为镜像到本地后，查看空间的时候，更关心的是本地磁盘空间占用的大小。

* `docker image ls` 列表中的镜像体积总和并非是所有镜像实际硬盘消耗。由于 Docker 镜像是多层存储结构，并且可以继承、复用，因此不同镜像可能会因为使用相同的基础镜像，从而拥有共同的层。由于 Docker 使用 Union FS，相同的层只需要保存一份即可，因此实际镜像硬盘占用空间很可能要比这个列表镜像大小的总和要小的多



可以通过 `docker system df` 命令来便捷的查看镜像、容器、数据卷所占用的空间。



## 镜像分层



![docker image layer archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20image%20layer%20archetecture.png)

Docker镜像由多个松耦合的只读镜像层组成。Docker负责堆叠这些层，并将它们表示为单个统一的对象

镜像一般比较精简，只包含必须的内容， 如必须的OS等，当然，镜像不包含os内核，容器共享docker host的内核

在镜像上启动的容器全部停止之前，镜像无法被删除：

```shell
docker image rm ubuntu:latest                                                         
Error response from daemon: conflict: unable to remove repository reference "ubuntu:latest" (must force)│
 - container 75f3c86793d8 is using its referenced image 54c9d81cbb44
```



## 查看镜像层

回顾`docker image pull ubuntu:latest`的输出：

```
latest: Pulling from library/ubuntu
952132ac251a: Pull complete
82659f8f1b76: Pull complete
c19118ca682d: Pull complete
8296858250fe: Pull complete
24e0251a0e2c: Pull complete
Digest: sha256:f4691c96e6bbaa99d...28ae95a60369c506dd6e6f6ab
Status: Downloaded newer image for
ubuntu:latest
```

对应的镜像层为：

![docker image layer example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20image%20layer%20example.png)



或者通过`docker  image  inspect`查看镜像：

```
$ docker image inspect ubuntu:latest

[
{
"Id": "sha256:bd3d4369ae.......fa2645f5699037d7d8c6b415a10",
"RepoTags": [
"ubuntu:latest"
<Snip>
]
}
"RootFS": {
"Type": "layers",
"Layers": [
"sha256:c8a75145fc...894129005e461a43875a094b93412",
"sha256:c6f2b330b6...7214ed6aac305dd03f70b95cdc610",
"sha256:055757a193...3a9565d78962c7f368d5ac5984998",
"sha256:4837348061...12695f548406ea77feb5074e195e3",
"sha256:0cad5e07ba...4bae4cfc66b376265e16c32a0aae9"
]
}
```

可以看到还是有五个镜像层，只不过采用了镜像名的SHA256来标识

## 镜像层详解

可以看到，镜像层是**栈**结构的，所有镜像层都起始于一个基础镜像层，后续每当对镜像内容做增改时，就会叠加新的镜像层

example：假如基于Ubuntu Linux 16.04创建一个新的镜像,这就是新镜像的第一层;如果该镜像中添加Python包,就会在基础镜像层之上创建第二个镜像层;如果继续添加一个安全补丁,就创建第三个镜像层。该镜像当前已经包含3个镜像层：

![docker image layer stack app](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20image%20layer%20stack%20app.png)





在添加额外的镜像层的同时,镜像始终保持是当前所有镜像的**组合**

example：

如下图，在外部看来整个镜像只有6个文件,这是因为最上层中的文件7是文件5的一个更新版本。这种情况下,上层镜像层中的文件覆盖了底层镜像层中的文件。这样就使文件的更新版本作为一个新镜像层添加到镜像当中：

![docker image layer set](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20image%20layer%20set.png)



Docker通过存储引擎（新版本采用快照机制）来实现镜像层的栈，并保证多镜像层对外展示为统一的文件系统 所有镜像层堆叠合并，对外提供统一的视图：

example： 上图三层镜像的对外视图，在外界看来，镜像层是合并的

![docker image layer set view](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/docker%20image%20layer%20set%20view.png)



## 共享镜像层

镜像层可以被多个镜像共享，

## 镜像摘要

除了 ` <reposiroty>: <tag>`,  镜像还可以用镜像摘要唯一标识，它是镜像的**内容的散列值**

可以用`docker image ls`的`--digests` option查看摘要：

```shell
root@lykRemote:~# docker image ls --digests alpine                       
REPOSITORY   TAG   DIGEST   IMAGE ID       CREATED        SIZE
alpine       latest    sha256:21a3deaa0d32a8057914f36584b5288d2e5ecc984380bc0118285c70fa8c9300   c059bfaa849c   2 months ago   5.59MB
```

镜像本身就是一个配置对象，其中包含了镜像层的列表以及一些元数据信息

镜像层是实际数据存储的地方，镜像层之间是完全独立的，并没有从属于某个镜像的概念

镜像的唯一标识是其摘要，每个镜像层也有自己的摘要。 这意味着镜像和镜像层是不可变得，任何改动都导致散列值的变化，这就是**内容散列（ Content Hash )**.

但是，在push和pull时，我们往往要对镜像层压缩来节省带宽和仓库存储空间，而压缩会改变镜像内容，这意味着内容散列值会改变，为此，每个镜像层又包含了一个分发散列值（ Distributed  Hash ），这是个压缩版镜像的散列值，用它来校验拉取的镜像是否被篡改过

## 多架构镜像

为了支持多架构，同一`<repository>:<tag>`标识的镜像可以有`Manifest`列表，每个元素是一个`Manifest`指针，指向具体的`Manifest`，其中包含了对应架构的镜像

`Manifest`列表是可选的，在没有`Manifest`列表时，registry返回普通的`Manifest`

因此不同架构的主机可以用相同的命令从registry得到同一镜像的不同架构版本

## 删除镜像

删除镜像会删除镜像配置以及相关的镜像层， 镜像层是引用计数的，可以被多个镜像共享。只有当所有依赖该镜像层的镜像都被删除后，该镜像层才被删除。





# Docker Container

## commands

注意：下文的`<container>`是容器名，和`<image>`镜像名不同

----

### 启动容器

[运行容器](https://docs.docker.com/engine/reference/run/#docker-run-reference)：`docker client`会用API与`docker daemon`通信，后者**先查询本地有无该镜像，如果没有，就从（默认）docker hub pull到本地**

```shell
docker container run [options] <image> <app>
```

* `-i`: Keep STDIN open even if not attached

* `-t`: Allocate a pseudo-tty 终端

  * For interactive processes (like a shell), you must use `-i -t` together in order to allocate a tty for the container process. 

    `-i -t` is often written `-it` as you’ll see in later examples.

* `-d=true` or just `-d`： daemon模式: 在后台运行

* `<app>`: 容器中运行的**主进程**（领头进程）

* `--name [name]`: 给容器起别名

* `-p [host_port:container_port]`: 指定端口映射， 例如`-p 80:8080`将主机的80端口映射到容器的8080端口

* `--network`: 指定容器所属的网络类型：

  * `--net=host`: host网络
  * `--net=none`: 无网络
  * `--net=bridge `: bridge网络，这是默认设置
  * `--net=container:<container>`: 与指定容器共享一个Network Namespace，但其他的namespace还是隔离的

* `-rm`: Automatically remove the container when it exits. 也就是自动移除之前的同名的容器

* ` --restart`: 设置重启策略:

  * `unless-stopped`
  * `always`
  * `no`: Do not automatically restart the container. (the default)



 ` <Ctrl PQ>`： detach容器

### 启动已停止运行的容器

启动处于停止（`Exited`）状态的容器：

```shell
docker container start
```

### 重启容器

 正在运行的容器可以重启:

```shell
docker container restart <container> 
```



----

### 在容器中启动新进程

在运行的容器中启动新进程：

```shell
docker  container exec [options] <container> <app>
```

* `docker container exec -it <container> bash`: 将终端重新连接到容器
  * `exec`在容器中创建了新的bash，输入`ps`可看到两个bash进程。 这意味着在当前shell输入`exit`并不会导致容器终止，因为主进程还在运行中

----

### 列出容器

列出所有运行的容器， options和image的一样

```shell
docker container ls
```

* `-a`: 显示所有容器(默认只显示运行的)
* `--quiet, -q` :只显示数字ID





### 停止容器

停止容器运行：

```shell
docker container stop
```

* 向容器内pid=1的进程发送`SIGTERM`， 如果10s内得到清理并停止运行，则会接着发送`SIGKILL`强制停止该容器
* `docker stop $(docker ps -a -q)`

----

### 删除容器

删除容器：

```shell
docker container rm
```

* `-f`:    发送`Sigkill`停止容器（无需先stop），然后删除（`rm`）
* `docker rm $(docker ps -a -q)`

批量删除容器：

```shell
docker container rm -f $(docker container ls -aq | cut -d " " -f 1) 
```

* 先列出所有容器信息(包括id): `docker container ls -aq`
* 选中指定列, 一般是第一列,这是容器的id: `cut -d " " -f 1`
* 将容器的id传给`rm`: `docker container rm -f`



删除所有Exited的容器:

```shell
docker container prune       
```



### 导出/导入容器的文件系统

将Docker容器里的文件系统作为一个 tar 文件导出到标准输出， 注意与用于序列化镜像的`docker image save`不同：

```shell
docker container export [OPTIONS] <container>
```

* `-o`:将输入内容写到文件



从tar文件中创建镜像:

```shell
docker import [OPTIONS] [file_name].tar <image>
```



### 查看容器信息

```shell
docker  container  inspect <container>
```



查看容器重启策略：

```
docker  container  inspect <container> | grep RestartPolicy -A 20
```



查看容器的挂载情况：

```
docker inspect <container> | grep Mounts -A 20
```





查看端口映射等信息：

```shell
docker container port <container>
```





### 查看容器日志

查看容器内部的**标准输出**:

```shell
docker logs -f <container>    
```





### 查看容器网络

查看容器网络：

```shell
docker network ls
```

### 查看容器卷

查看容器的卷：

```shell
docker volume ls
```



## 容器vs虚拟机

容器共享操作系统资源（OS内核），虚拟机共享硬件资源

容器是OS虚拟化， 虚拟机是硬件虚拟化

虚拟机的每个OS都有开销，都需要授权，都需要打补丁

![vm archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/vm%20archetecture.png)



![container archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/container%20archetecture.png)



##   运行容器

容器镜像都是高度优化的，因此可能没有预装一些命令

容器随着其中运行应用(领头进程)的退出而终止

## 重启策略

重启策略可以指定容器在事件或错误后重启

重启策略可作为参数`docker container run  --restart`  的参数设置或在`Compose`文件中声明

重启策略包括：

* always: 除非容器被明确停止( 如`stop`)，否则该策略会一直尝试重启处于Exited的容器
  * 该策略下，如果重启daemon,  Exited容器（包括`stop`!!）也会被重启
* unless-stopped： always的修复版，不会在daemon重启的时候重启Exited状态的容器
* on-failed： 在退出容器且返回值不是0的时候重启容器，与always相同，如果重启daemon, 明确被停止的容器（包括`stop`!!）也会被重启

### example

下面创建两个新容器,其中“always”容器指定--restart always 策略,另一个“unless- stopped”
器指定了--restart unless-stopped 策略。两个容器均通过docker container stop 命令
止,接着重启Docker。结果“always”容器会重启,但是“unless-stopped”容器不会

1. 创建两个新容器：

   ```shell
   docker container run -d --name always --restart always alpine sleep 1d
   
   docker container run -d --name unless-stopped --restart  unless-stopped alpine sleep 1d
   ```

2. 停止两个容器：

   ```shell
   docker container stop always unless-stopped
   ```

3. 重启docker

   ```shell
   systemctl restart docker
   ```

4.   检查两个容器的状态：

   ```shell
   docker container ls -a
   # 输出略
   ```

# Docker Security

本章内容涉及Docker Swarm



Docker使用了大量Linux的安全技术

![Docker Security with Linux](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/Docker%20Security%20with%20Linux.png)

## Linux Security

### Namespace

Linux Namespace允许对OS进行拆分,

* 例如, 不同的name space可以被分配不同的ip, 这样同一台主机就可以允许多个web服务, 还不存在端口冲突( 因为ip不同 )



**Docker容器本质是命名空间的有组织集合**

* 每个容器都由自己的PID, NET, MNT, IPC, UTS构成, 还可能包括USER
* 这些命名空间的组合就是容器



Linux Docker使用了如下的内核namesoace:

* 进程ID( PID ): 每个容器互相独立, 拥有自己的进程树, 每个容器都有自己的PID为1的进程. PID空间也意味着容器不能看到其他容器或所在主机的进程树
* 网络 ( NET ): 每个容器有互相隔离的网络栈. 例如每个容器都有自己的`eth0`接口, 独立的ip和端口地址
* 文件系统/挂载( MNT ): 每个容器都有互相隔离的根目录, 这也意味着容器不能访问其他容器或宿主机的目录
* 进程内通信(  IPC ): IPC为容器提供共享内存, 这在不同容器间也是独立的
* 用户( USER ): Docker允许用户使用USER命名空间来将容器内用户映射到宿主机的不同用户, 比如将容器内的root映射到宿主机的非root用户
* UTS: 每个容器都有自己的主机名称



### Control  Group

通过控制组来限制资源分配

### Capability

允许拆分用户权限, 即选择容器允许所需的root用户权限

### MAC

Docker Linux采用主流的Linux Mac 技术, 如 SELinux

### Seccomp

Docker使用过滤模式下的Seccomp来限制容器对宿主机内核发起的系统调用

## Docker Original Security

Docker很大一部分安全技术都基于Swarm模式, 详见*Docker Swarm*

此外, 还有Docker安全扫描, 内容信任, Docker Secret等

### 安全扫描

就是对Docker镜像进行二进制代码级别的扫描, 对其中的软件根据已知的缺陷数据库( CVE数据库 )进行检查, 并生成报告

* Docker Hub已经支持安全扫描了



###  内容信任

内容信任允许开发者对push到Image Registry的镜像进行签名, 当镜像被pull的时候确认签名状态, 这可以确保只pull经过验证的镜像



### Docker Secret

提供了`docker secret`系列命令

密钥的存储和传输都是加密的. 使用时被临时挂载到<u>内存文件系统</u>( 只针对Linux, 因为windows没有内存文件系统 )

* 密钥被存在集群存储里,并且加密. 每个Manager都有权访问集群存储
* 密钥只对已经被授权了的服务开放访问





可以在容器/服务创建时指定使用某密钥, 后续该服务的多个示例都会持有该密钥

* 一旦容器/服务的任务完成, 内存文件系统关闭,密钥也随之删除
* 假设指定服务B使用密钥secret1, 在worker2, worker3运行, 则密钥被传输到worker3的B实例时, 传输是加密的
* 服务A不能访问该密钥, 因为没有授权



![Docker Secret example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Basic/Docker%20Secret%20example.png)

# Docker Logs

Docker网络, 集群出现故障, 就需要查日志

日志分为daemon日志和容器日志

## Commands



 查看daemon日志( 仅限于使用`systemd`的系统)： 

````shell
journalctl -u docker.service
````

 

查看容器日志：

```shell
docker container logs -f <container-name>
```

对于Swarm服务：

```shell
docker service logs <service-name>
```

 

## daemon日志

daemon日志： 如果OS用`Systemd`， 日志会存储在`Journald`



### 查看daemon日志

*  查看日志： `journalctl -u docker.service `

### 设置日志详细程度

通过编辑`daemon.json`：

1. 设置`debug`为true

2. 设置log-level:

   * debug: 最详细
   * info： 默认值， 次详细
   * warn： 第三详细
   * error
   * fatal

   ```json
   {
   	<Snip>
   	"debug": true,
   	"log-level": "debug",
   	<Snip>
   }
   ```

   

   

## 容器日志

每个docker容器或服务都可以配置自己的日志驱动：

* json-file: 默认
* journald: 只在运行`systemd`的linux主机有效
* syslog
* ...

### 查看容器日志

```shell
docker container logs <container-name>
docker service logs <service-name> # 针对Swarm服务
```

* json-file和journald日志均可通过这两种命令查看
* 其他驱动的日志需要用第三方平台提供的原生工具查看
* `--follow`: 跟踪日志
* `--tail`: 查看日志尾部
* `--details`: 额外的详细信息

### 指定容器日志驱动

配置docker主机的提供的默认日志驱动：

```json
//daemon.json
{
	"log-driver": "syslog"
}
```

可以在容器启动时通过`--log-driver`和`-log-opts`指定特定的日志驱动，这会覆盖掉主机的配置



# Docker Management

命令行docker管理工具: lazydocker



## 查看配置文件

```shell
systemctl status docker
```



## 更改镜像存储位置

## **使用软链接**

- 默认情况下 `Docker` 镜像的存放位置在 `/var/lib/docker` ：

```javascript
# 默认存放位置
$ sudo docker info | grep "Docker Root Dir"
```

- 采用软链接的方式，修改镜像和容器的存放路径

```javascript
# 停掉Docker服务
$ service docker stop
```

- 然后移动整个 `/var/lib/docker` 目录到空间不较大的目的路径。这时候启动 `Docker` 时发现存储目录依旧是 `/var/lib/docker` 目录，但是实际上是存储在数据盘 `～/data/docker` 上了。

```shell
# 移动原有的内容
$ mv /var/lib/docker ～/data/docker

# 进行链接
$ ln -sf ～/data/docker /var/lib/docker
```



# Others

## 常见镜像版本

### full official image

事实上的标准镜像:

- python:3.8.3
- node:14.1.1

如果不关心最终镜像的大小, 完整镜像是最安全的选择

### buster/stretch/jessie

- buster:Debian 10
- stretch:Debian 9
- jessie:Debian 8

带有stretch、buster或jessie标签的镜像是不同Debian发行版的代号。

在撰写本文时，稳定的Debian发行版是10.4，它的代号是“buster”。 “stretch”是所有版本9变种的代号，“jessie”是所有版本8变种的代号。

正在开发的未来版本是“bullseye ”和“bookworm”，但还不稳定。你可能会在DockerHub上的镜像版本列表中看到这些标签。

如果您的代码与Debian操作系统的特定版本兼容，请选择其中一个镜像。在开始一个新项目时，你很少需要使用旧版本的Debian。

### slim

slim的镜像是完整镜像的配对版本, 这个镜像通常只安装运行特定工具所需的最小包

**但是，在使用这个镜像时，一定要进行彻底的测试！**如果您遇到无法解释的错误，请尝试切换到完整的镜像，看看是否能够解决问题。

### alpine

alipine镜像基于alpine linux项目，这是一个专门为容器内部使用而构建的操作系统。在很长一段时间里，这些是最受欢迎的镜像变体，因为它们的尺寸很小。

然而，一些团队正在弃用alpine镜像，因为这些镜像可能会导致难以调试的兼容性问题。具体来说，如果使用python镜像，一些 wheels将被构建成与Debian兼容，并且需要重新编译，才能与基于apline的镜像一起工作。

使用alpine镜像的主要原因是使你得到的镜像尽可能小。基础镜像将小于5MB。python基础镜像(将python添加到基础alpine镜像)目前是78.9MB。这仍然很小。

**如果考虑到空间问题，强烈推荐使用此镜像。**

它的缺点是不包含一些你可能会需要的包。主要是，它使用了一个更小的musl lib代替glibc。如果您的应用程序有特定的libc需求，您可能会遇到问题。

如果你发现Alpine镜像缺少你需要的东西，你可以直接在Dockerfile中安装它，这样能确保镜像只包含你需要的内容。需要注意，如果您正在安装外部包，您的Dockerfile将会更改。主要的区别是，您将使用apk而不是apt-get来安装包。

对alpine镜像的使用有很多担心之处，所以你需要充分了解它。需要充分阅读文档并研究。 同样，如果您在构建Dockerfile时遇到了无法解释的问题，请尝试切换到完整的镜像，看看是否能解决问题

### windowsservercore

windows或windows Server平台的镜像