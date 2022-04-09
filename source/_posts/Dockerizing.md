---
title: Dockerizing
tags: Docker
categories: Technology
date: 2022-03-19 01:04:45
---


Outline:

* 单体应用容器化

  * Dockerfile
  * build image
  * push image

* 多阶段构建

  

介绍了应用的容器化

<!--more-->

# Intro

应用容器化步骤：

1. 编写应用代码
2. 创建Dockerfile,其中包括当前应用的描述，依赖以及如何运行这个应用
3. 对该Dockerfile执行`docker image build`
4. 等待Docker将应用程序构建到Docker镜像中

![dockerizing workflow](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Dockerizing/docker%20image%20squash.png)



# 单体应用容器化

示例项目：https://github.com/LYK-love/psweb

## Dockerfile

构建上下文（Build Context）： 包含应用文件的目录

Dockerfile一般放在构建上下文的根目录下

Dockerfile首字母不能小写

Dockerfile:

* 除了 `#` 开头的注释行之外， 其他的每一行都是一条指令
  * 指令： `INSTRUCTION argument`: 不区分大小写，一般`INSTRUCTION`大写
* 分为四部分：基础镜像信息、维护者信息、镜像操作指令和容器启动时执行指令
* 只有一部分指令会新建镜像层

```
FROM alpine

LABEL maintainer="nigelpoulton@hotmail.com"

# Install Node and NPM
RUN apk add --update nodejs npm curl

# Copy app to /src
COPY . /src

WORKDIR /src

# Install dependencies
RUN  npm install

EXPOSE 8080

ENTRYPOINT ["node", "./app.js"]

```

* `FROM  <image>`： 将指定的镜像的作为要构建的镜像的基础镜像层，一般是OS



* ` LABEL <tag> <tag>`：添加一些元数据，每个tag都是键值对



*  `RUN <command>` 或 `RUN ["executable", "param1", "param2"]`：

  * 前者将在 shell 终端中运行命令，即 `/bin/sh -c`；后者则使用 `exec` 执行。指定使用其它终端可以通过第二种方式实现，例如 `RUN ["/bin/bash", "-c", "echo hello"]`

  * 每条 `RUN` 指令都会在当前镜像层基础上执行指定命令， 并**新建一个镜像层**
    * 因此， 可以用 `&&`连接多个命令或用`\\`换行， 来将多个命令包含在一个` RUN`指令中

*   `COPY <src> <dest>`：

  复制本地主机的 `<src>`（为 Dockerfile 所在目录的相对路径，即构建上下文）到容器中的 `<dest>`



* `WORKDIR  [dir]`: 为Dockerfile中尚未执行的指令设置工作目录

* `ENTRYPOINT`

  两种格式：

  - `ENTRYPOINT ["executable", "param1", "param2"]`
  - `ENTRYPOINT command param1 param2`（shell中执行）。

  配置镜像以容器方式启动后默认运行的程序，并且不可被 `docker run` 提供的参数覆盖。

  每个 Dockerfile 中只能有一个 `ENTRYPOINT`，当指定多个时，只有最后一个起效。



* `EXPOSE <port> [<port>...]`：

  告诉 Docker 服务端容器暴露的端口号，供互联系统使用。在启动容器时需要通过 -P，Docker 主机会自动分配一个端口转发到指定的端口



* `VOLUME ["/data"]`：

  创建一个可以从本地主机或其他容器挂载的挂载点，一般用来存放数据库和需要保持的数据等。

## 构建镜像

### 步骤

```shell
docker image build [选项] path
```

docker daemon按行来读取path下（包括子目录）的 Dockerfile，并将该path下的所有内容发送给 Docker 服务端，由服务端来创建镜像

* `-t` : 指定镜像的标签信息,即`<image>`

###  原理

#### 增加镜像层



一般而言，如果指令会对镜像增改，那么会**新建镜像层**， 如果指令只是指示Docker如何构建或者如何运行应用程序，那么就只会**增加镜像的元数据**



查看image build的输出：

```shell
❯ docker image build -t web:latest .
Sending build context to Docker daemon  82.43kB
Step 1/8 : FROM alpine
latest: Pulling from library/alpine
3d2430473443: Pull complete 
Digest: sha256:d6d0a0eb4d40ef96f2310ead734848b9c819bb97c9d846385c4aca1767186cd4
Status: Downloaded newer image for alpine:latest
 ---> e9adb5357e84
Step 2/8 : LABEL maintainer="nigelpoulton@hotmail.com"
 ---> Running in 84a356f040f7
Removing intermediate container 84a356f040f7
 ---> f84bda7d881d
Step 3/8 : RUN apk add --update nodejs npm curl
 ---> Running in 16254526f96c
<Snip>
Removing intermediate container 16254526f96c
Step 4/8 : COPY . /src
 ---> 7bee4035f9fb
Step 5/8 : WORKDIR /src
 ---> Running in 9773c1204206
Removing intermediate container 9773c1204206
 ---> a9bea6558795
Step 6/8 : RUN  npm install
 ---> Running in 2117e2800e7d

```



可以发现，对于Dockerfile中的**每一个产生镜像层的指令**， docker server会：

1. 运行一个临时容器
2. 在该容器中执行该指令
3. 将指令执行结果保存为镜像层
4. 删除临时容器



而对于不产生镜像层的指令， 不会生成临时容器

#### build cache

`docker image build`会从顶层自上而下逐条执行Dockerfile中的指令， 对于每一条指令， Docker都会检查缓存中是否已经有与该指令对应的镜像层。 

* 如果Cache hit,  并且会链接到这个镜像层，在此基础上继续构建； 
* 如果Cache miss, 则会**对剩余部分的指令设置缓存无效**（ 这意味着Dockerfile接下来的指令将全部执行， 而不再尝试查找build cache ）， 并基于当前指令构建新的镜像层
  *  一旦某条指令cache miss, 则之后的指令都不会使用缓存。 因此编写Dockerfile时， 尽量将易于导致镜像层改变的指令放到后面
  * `--no-cahce=true`： 强制忽略build cache
  * 判断缓存命中（即镜像是否相同）的算法：计算每一个被构建文件的checksum， 将其与已有镜像层中同一文件的checksum进行对比 。 如果不同，则说明 cache miss

### squash image

正常来说， docker会构建多个镜像层， 并将它们合并为一个镜像 

可以将镜像层手动合并， 这样更方便， 但是会导致被合并的镜像层无法被共享：

```
docker image build --squash 
```



例子：

![docker image squash](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Dockerizing/docker%20image%20squash.png)

可以看到，合并前的镜像层是独立的，可以只发送不同的镜像层， 但合并后，所有镜像层合并为一个镜像层， 所以每次都需要传输完整的镜像

### 示例 

example:

```shell
docker image build -t web:latest .
```



##  推送镜像

push首先需要当前用户登陆dockerhub

![docker push information](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Dockerizing/docker%20push%20information.png)

push镜像需要如下信息：

* Registry: 默认`docker.io`
* Repository: 被推送镜像的REPOSITORY属性值
* Tag:  默认`latest`

### preparation

假设镜像仓库名是web, 那么push后，镜像位于`docker.io/web:latest`,然而用户一般没有一级命名空间的权限,  因此**需要为当前镜像重新打一个标签， 这个标签指定了要推送的用户空间**：

```shell
docker image tag <image-qith-current-wothtag> <image-with-new-tag>
# 该命令会为镜像添加额外的标签，不会删除已有的标签. 可以通过`docker image ls` 查看，发现镜像拥有了两个标签 
```



如果你的标签上的用户名不等于你当前登陆的docker hub id, push会失败：

```shell
#  当前登陆用户为lyklove
❯ docker image ls
REPOSITORY           TAG       IMAGE ID       CREATED        SIZE
hello-world          latest    feb5d9fea6a5   5 months ago   13.3kB
lyk/hello-world      latest    feb5d9fea6a5   5 months ago   13.3kB

❯ docker image push lyk/hello-world:latest
The push refers to repository [docker.io/lyk/hello-world] 
## 可以看到docker试图push到lyk的目录下，但是当前用户是lyklove, 不具有用户lyk的权限， 因此push会失败

e07ee1baac5f: Preparing 
denied: requested access to the resource is denied

```

### 步骤

1. 先登陆docker hub：

   ```shell
   docker login
   ```

   

2. 为当前镜像重新打一个标签（ 与当前dockerhub id相符）：

   ```shell
   docker image tag <current-tag> <new-tag>
   ```

   

3. push镜像（以新标签标识的镜像）：

   ```shell
   docker image push [OPTIONS]  <image>
   ```

   

### 示例

例子：

1. 假设有一个镜像 `web`， 则 `docker  image push web` 实际上会将镜像推送到`docker.io/web:latest` 

   ( 默认Registry是`docker.io`,  默认tag是`latest` ) 

   

2.  但是， 我不可能有`docker.io/`这个以及命名空间的权限， 只能推送到我自己的二级命名空间(也就是用户的命名空间)：

    假如我当前登陆的docker hub id为`lyklove`， 则我需要推送到`docker.io/lyklove/web:latest` 

   

3. 为此，需要给镜像改名：

   ````shell
   docker  image tag web:latest lyklove/web:latest
   
   # 由于镜像web的默认标签名就是latest, 因此也可以:
   docker image tag web lyklove/web
   ````



4. 最后将`lyklove/web` ( 或者`lyklove/web:latest` )  推送到dockerhub

   ```shell
   docker image push lyklove/web:latest
   ```




## 查看镜像构建过程

查看在构建镜像的过程中执行了哪些指令：

```shell
docker image history <image>
```

* 每行内容都对应Dockerfile的一条指令（自下而上,  最后执行的指令（如` ENTRYPOINT`）最先显示）

* 对于示例项目`web:latest`, 可以看到只有Dokcerfile的` FROM`， `RUN`和`ADD`指令添加了镜像层， 其他的指令只是新增了元数据信息：

  ```shell
  ❯ docker image history web
  IMAGE          CREATED         CREATED BY                                      SIZE      COMMENT
  8552b568ff4c   2 minutes ago   /bin/sh -c #(nop)  ENTRYPOINT ["node" "./app…   0B        
  3669d3adfb1a   2 minutes ago   /bin/sh -c #(nop)  EXPOSE 8080                  0B        
  d0005c695ed3   2 minutes ago   /bin/sh -c npm install                          23.4MB    
  a9bea6558795   2 minutes ago   /bin/sh -c #(nop) WORKDIR /src                  0B        
  7bee4035f9fb   2 minutes ago   /bin/sh -c #(nop) COPY dir:09deb2ee65cb723fd…   44.9kB    
  6df93a7da909   2 minutes ago   /bin/sh -c apk add --update nodejs npm curl     52.5MB    
  f84bda7d881d   5 minutes ago   /bin/sh -c #(nop)  LABEL maintainer=nigelpou…   0B        
  e9adb5357e84   30 hours ago    /bin/sh -c #(nop)  CMD ["/bin/sh"]              0B        
  <missing>      30 hours ago    /bin/sh -c #(nop) ADD file:cf4b631a115c2bbfb…   5.57MB    
                              
  ```

  可以看到，第一行是执行的最后一条指令`ENTRYPOINT`。 一共产生了四个镜像层



查看镜像：

```shell
docker image inspect <image>
```

```shell
docker image inspect web:latest # 以示例项目为例, 可以看到确实只有四个镜像层

         <Snip>
        "RootFS": {
            "Type": "layers",
            "Layers": [
                "sha256:5e03d8cae8773cb694fff1d55da34a40d23c2349087ed15ce68476395d33753c",
                "sha256:3dc92b603964ad1b75c9dde518d028676ded40c82858ee4d236e10ef0e3c02fb",
                "sha256:04910df3fe981f716ad106dec89d8b667102690462e81efefef411273dad7d26",
                "sha256:a46c93c283ea7d6611acc8d1422f0b20f40acf1ebadd9d51439e425f7a3dc18d"
            ]
        },
		<Snip>
		
```

## 运行容器

```shell
docker container run -d --name c1 \
-p 80:8080 \
web:latest
```

*  `--name`：  指定容器名
* `-p host_port:container_port`: 指定将主机的端口映射到容器的端口

# 多阶段构建

进行多阶段构建， 概念和Jenkinsfile、 Github Action workflow一样

多阶段构建使用一个Dockerfile, 其中包含多个`FROM`指令， 每个都是一个 Build Stage, 从0开始编号。 每个stage可以复用之前stage的构建结果（jar包， target文件之类的）



示例项目: https://github.com/LYK-love/atsea-sample-shop-app

```shell
FROM node:latest AS storefront
WORKDIR /usr/src/atsea/app/react-app
COPY react-app .
RUN npm install
RUN npm run build # 构建出一个很大的node镜像

FROM maven:latest AS appserver
WORKDIR /usr/src/atsea
COPY pom.xml .
RUN mvn -B -f pom.xml -s /usr/share/maven/ref/settings-docker.xml dependency:resolve
COPY . .
RUN mvn -B -s /usr/share/maven/ref/settings-docker.xml package -DskipTests # 构建出一个很大的maven镜像

FROM java:8-jdk-alpine
RUN adduser -Dh /home/gordon gordon
WORKDIR /static
COPY --from=storefront /usr/src/atsea/app/react-app/build/ . # 从storefront阶段拉取一些文件过来， 复制到工作目录下
WORKDIR /app
COPY --from=appserver /usr/src/atsea/target/AtSea-0.0.1-SNAPSHOT.jar . # 同上， 从appserver阶段拉取一些文件过来， 
ENTRYPOINT ["java", "-jar", "/app/AtSea-0.0.1-SNAPSHOT.jar"]
CMD ["--spring.profiles.active=postgres"] # 构建出一个精简的镜像
```

* `COPY --from` 指令： 从之前stage构建的镜像中仅复制生产环境所需要的文件， 这样镜像中就带有不会冗余文件（比如maven, node）

* 三个`FROM`指令构建出三个镜像， 用`docker image build -t multi:stage`进行构建， 它只会命名最后一个镜像， 我们就只需要将最后一个镜像push到生产环境：

  ```
  ❯ docker image ls
  REPOSITORY                  TAG            IMAGE ID       CREATED          SIZE
  node                        latest         36fad710e29d   2 weeks ago      991MB
  <none>                      <none>         d9c9c532ae40   7 minutes ago    934MB
  maven                       latest         d833a10812ed   3 weeks ago      793MB
  <none>                      <none>         db32cdd21a1a   31 minutes ago   1.15GB
  openjdk                     8-jdk-alpine   a3562aa0b991   2 years ago      105M
  multi                       stage          040df44afa9a   7 minutes ago    211MB
  ```

  * 可以看到， 1第一行是第一阶段拉取的镜像， 第二行是第一阶段生成的镜像； 第三，四，五，六行同理；并且第六行镜像被`-t multi:stage`命了名
  * 还可以看到，只有最后一个镜像会被命名， 而其余的`FROM`指令生成的镜像都变成了玄虚镜像， 可以直接删除， 非常方便



