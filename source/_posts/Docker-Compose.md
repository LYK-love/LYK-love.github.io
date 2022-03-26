---
title: Docker Compose
tags: Docker
categories: Technology
date: 2022-02-15 15:11:52
---


Outline:

* Background of Docker Compose
* 部署要点
* Compose文件示例
* 热部署



* 本节使用示例：[here](git@github.com:LYK-love/counter-app.git)

<!--more-->

# Background

* Docker Compose  前身是  Fig

* 目前为止，Docker Compose依然需要在docker主机上进行外部安装

  ```shell
  apt  install docker-compose
  ```

   检查安装是否成功：

  ```shell
  docker-compose --version
  ```

  

* 单引擎模式部署workflow：
  1. 编写定义多容器应用的YAML文件（称为Compose文件）
  2. 将其交给`docker-compose`  命令， 
  3. 该工具会基于docker api完成应用的部署（ 即与docker daemon通信 ）



Docker Compose是Docker Stack的<u>简化版</u>. 能够在Docker节点上以单引擎模式（ Single-Engine Mode ）进行简化版多服务应用的部署和管理

* 真正的多服务应用中, 服务是若干容器的集合, 作为一个整体进行统一管理. 例如Docker Stack
* Docker Compose中的一个服务就只有一个容器,因此是"简化版多服务应用"



# Basic Idea

* 通过Compose文件定义的多容器应用称为Compose应用



* 

* `docker-compose`构建应用时也会利用构建缓存，对于已有的镜像、网络、卷，不会再重新创建



* `docker-compose`的命令和`docker comtainer`大同小异， 所谓的应用就是若干容器， 容器就有运行、停止和关闭三种状态。“关闭”指的是容器资源也被删除

* 由于docker卷的生命周期是与相应的容器完全解耦的。 因此关闭Compose应用，卷不会被删除
* 同样，镜像也不会被删除



* `docker-compose`会将项目名称和Compose文件中定义的服务名称连起来，作为新构建的镜像的名称， 而容器名称是镜像名称+数字后缀，因为`docker-compose`允许扩容

# Commands

## 启动Compose应用

```shell
docker-compose up [ -f [compose_file_name] ]   -d
```

* `-f`: 指定Compose文件，默认情况下， 其名为docker-compose.yml 或docker-compose.yaml
  *  `docker-compose up`会查找Compose文件，基于此构建镜像、网络和卷，并启动容器
* `-d`: daemon模式，在后台启用应用
  * 也可以使用` &`， 但是这样不会重定向输入输出流



## 列出Compose应用：

```shell
docker-copmpose ps
```

 该命令作用和` docker container ls`  差不多

---

## 停止Compose应用

  停止Compose应用, 并删除资源（类似`docker container rm  -f`）：

```shell
docker-compose down
```

*  该命令会停止并关闭容器，删除网络（卷和镜像不会被删除）





停止Compose应用,不删除资源：

```shell
docker-compose stop
```

相当于` docker compose stop`





对于停止的Compose应用,删除其资源：

```shell
docker-compose rm
```

类似` docker compose rm`， 会删除容器和网络



## 重启Compose应用

---

对于停止的Compose应用,重新启动：

```shell
docker-compose restart
```

类似` docker compose restart`

----

## 查看Compose应用运行情况

查看Compose应用运行情况：

```shell
docker-compose top
```

# Compose文件示例

我们给出一个示例：

先进入构建目录：

```shell
❯ cd ./counter-app 
```



查看目录内容：

```shell
❯ ls
app.py  docker-compose.yml  Dockerfile  README.md  requirements.txt
```

* `app.py`: 应用程序代码

## 文件格式

查看示例的`docker-compose.yml`:

```yaml
❯ cat ./docker-compose.yml
version: "3.5"
services:
  web-fe:
    build: .
    command: python app.py
    ports:
      - target: 5000
        published: 5000
    networks:
      - counter-net
    volumes:
      - type: volume
        source: counter-vol
        target: /code
  redis:
    image: "redis:alpine"
    networks:
      counter-net:

networks:
  counter-net:

volumes:
  counter-vol:# 
```

一级key：

* `version`:  指定Compose文件格式 （注意并非compose或者docker引擎的版本号）
* `services`: 定义不同的服务
* `networks`: 令docker创建新的网络
  * （ 默认是桥接模式，这是单主机网络，只能够实现同一主机上容器的连接 ）
* `volumns`: 令docker创建新的卷



二级key：

* `services`  部分定义两个二级`key`，docker-compose会将每个服务部署为一个容器，并使用key作为容器名字的一部分，在二级key中有如下指令：
  *  `build： [file_path]`：指定Dockerfile的所在目录，该Dockerfile会被用于创建镜像，进而启动容器。 如果已经存在镜像了，可以使用`image <image>`
  * `image: <image>`: 指定Docker基于镜像启动容器
  * `command: [executable]`: 指定Docker容器中运行的主程序
  * `ports：- target: [target_port] published: [source_port]`: 指定端口映射， 将主机的`published`端口映射到容器的`target`端口
  * `networks：`: 指定容器连接到的网络， 该网络要么已经存在，要么在`networks`**一级**key中指定, 后者会让Docker创建该网络
  * `volumes`:  指定Docker将` [source]`卷挂到容器的` [target]` 卷, 该网络要么已经存在，要么在``volumes`:`**一级**key中指定

## 解释

示例解释：

在本示例中, DockerCompose会调用Docker来为web-fe 服务部署一个独立的容器。该容器基于Compose文件位于同一目录下的Dockerfile构建的镜像。基于该镜像启动的容器会运行app.py 作为主程序,将5000端口暴露给宿主机,连接到counter-net 网络上,并挂载一个卷到/code . redis服务也类似

由于两个服务都连接到counter-net 网络,因此它们可以通过名称解析到对方的地址。了解这一点重要,本例中上层应用被配置为通过名称与Redis服务通信



查看容器：

```shell
❯ docker container ls
CONTAINER ID   IMAGE                COMMAND                  CREATED             STATUS             PORTS                                       NAMES
b936fbeba406   counter-app_web-fe   "python app.py"          About an hour ago   Up About an hour   0.0.0.0:5000->5000/tcp, :::5000->5000/tcp   counter-app_web-fe_1
1784979d1e6c   redis:alpine         "docker-entrypoint.s…"   About an hour ago   Up About an hour   6379/tcp                                    counter-app_redis_1
```

可以看到每个服务都创建了对应的容器



查看网络：

```shell
❯ docker network ls
NETWORK ID     NAME                      DRIVER    SCOPE
220db3964578   bridge                    bridge    local
5489df9fb5c0   counter-app_counter-net   bridge    local
961ccb2de759   host                      host      local
03b55e96642c   none                      null      local
```

可以看到创建了桥接网络`counter-app_counter-net`



查看卷：

```shell
❯ docker volume ls
DRIVER    VOLUME NAME
<Snip>
local     counter-app_counter-vol
```

可以看到创建了卷`counter-app_counter-vol`

# 热部署

由于主机的卷被挂载到容器上，对主机上卷的改动就是对容器的卷的改动。 `docker-compose`可以做到热部署，就是说可以直接在主机的卷上进行修改，容器就会产生相应的改变，不需要重新部署



example：

先查看示例中卷的挂载情况：

```shell
 ❯ docker volume inspect counter-app_counter-vol | grep Mount
        "Mountpoint": "/var/lib/docker/volumes/counter-app_counter-vol/_data",
```



我们先修改工作目录下的`app.py`， 将其copy到`/var/lib/docker/volumes/counter-app_counter-vol/_data`：

```shell
do some change...

#注意带这个cp命令就是覆盖文件内容
cp ./app.py /var/lib/docker/volumes/counter-app_counter-vol/_data/app.py
```

（当然你也可以直接修改挂载点的文件， 不过由于docker compose每次从构建目录（这里是` ～/counter-cp/`）来构建应用，如果不改变构建目录下的文件的话，下次构建时，）



现在挂载点的文件内容变了，我们打开`localhost:5000`，发现修改也生效了。 整个过程**不需要重新部署**
