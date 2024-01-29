---
categories:
- Software Engineering
date: 2022-03-19 01:04:45
tags: Docker
title: Dockerizing
---

Outline:

* 单体应用容器化

  * Dockerfile
  * build image
  * push image

* 多阶段构建

* 构建镜像优化

  

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

### Options

* `FROM  <image>`： 将指定的镜像的作为要构建的镜像的基础镜像层，一般是OS

* ` LABEL <tag> <tag>`：添加一些元数据，每个tag都是键值对

*  `RUN <command>` 或 `RUN ["executable", "param1", "param2"]`：

  * 前者将在 shell 终端中运行命令，即 `/bin/sh -c`；后者则使用 `exec` 执行。指定使用其它终端可以通过第二种方式实现，例如 `RUN ["/bin/bash", "-c", "echo hello"]`
* 每条 `RUN` 指令都会在当前镜像层基础上执行指定命令， 并**新建一个镜像层**

* `ENV <ENV_VARIABLE>=<str>`: 设置环境变量

* `COPY <src> <dest>`：

  复制本地主机的 `<src>`（为 Dockerfile 所在目录的相对路径，即构建上下文）到容器中的 `<dest>`

* `WORKDIR  [dir]`: 为Dockerfile中尚未执行的指令设置工作目录

* `ENTRYPOINT`

  两种格式：

  - `ENTRYPOINT ["executable", "param1", "param2"]`
  - `ENTRYPOINT command param1 param2`（shell中执行）。

  配置镜像以容器方式启动后默认运行的程序，并且不可被 `docker run` 提供的参数覆盖。

  每个 Dockerfile 中只能有一个 `ENTRYPOINT`，当指定多个时，只有最后一个起效。

* `EXPOSE <port> [<port>...]`：暴露容器端口. 一般不用写这个指令，在启动容器的时候自己映射端口. 写这个指令有如下好处:
  1. 告诉告诉镜像使用者,该镜像暴露的端口
  2. 如果使用随机端口映射运行容器，也就是 `docker run -P` ，会自动随机映射 `EXPOSE` 的端口

* `VOLUME ["/data"]`：

  创建一个可以从本地主机或其他容器挂载的挂载点，一般用来存放数据库和需要保持的数据等。

## 构建镜像

### 步骤

```shell
docker image build [选项] path
```

docker daemon按行来读取path下（包括子目录）的 Dockerfile，并将该path下的所有内容发送给 Docker 服务端，由服务端来创建镜像,

* `-t` : 指定镜像的标签信息,即`<image>`, 注意镜像名必须是**全小写**

  * 可以在构建时指定tag:

    ```sh
    docker build -t hangge_server:2.4 .
    ```

* `-f`: 指定dockerfile

  ```sh
  docker build -f /path/to/a/Dockerfile .
  ```

  

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



## 推送镜像

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

# 错误示范
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

   

2. Tag your Docker image with your Docker Hub  username and the repository name you want to use. For example, if your  username is `username` and your image name is `myimage`, you might tag it like this:

   ```shell
   docker image tag <image name> <username>:<new tag>
   ```

   * `image name`: name of the docker image, composed of `REPOSITORY` and `TAG`.

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
*  `-p host_port:container_port`: 指定将主机的端口映射到容器的端口
*  `-P`: 随机端口映射，容器内部端口随机映射到主机的高端口
*  `-d`: 后台运行容器，并返回容器ID
*  `-i`: 以交互模式运行容器，通常与 -t 同时使用
*  `-t`: 为容器重新分配一个伪输入终端，通常与 -i 同时使用
*  `-e username="ritchie"`: 设置环境变量
*  `--env-file=[file]`: 从指定文件读入环境变量
*  `--expose=[port-num]-[port-num]`: 开放（暴露）一个端口或一组端口；
*  `--rm`:  退出时自动删除容器

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





# 构建镜像优化

ref:[如何优化 node 项目的 docker 镜像](https://juejin.cn/post/6991689670027542564), 这篇文章将构建镜像优化到了:

1. **大小从 1.06G 到 73.4M**
2. **构建速度从 29.6 秒到 1.3 秒**



我们以文中的[node项目](https://github.com/iamobj/wechat-bot)为例, 最初的Dockerfile如下:

```dockerfile
FROM node:14.17.3

# 设置环境变量
ENV NODE_ENV=production
ENV APP_PATH=/node/app

# 设置工作目录
WORKDIR $APP_PATH

# 把当前目录下的所有文件拷贝到镜像的工作目录下 .dockerignore 指定的文件不会拷贝
COPY . $APP_PATH

# 安装依赖
RUN yarn

# 暴露端口
EXPOSE 4300

CMD yarn start
```

## 基本操作

* 对于会新建镜像层的指令, 比如`RUN`, `ENV`.... 因此这些指令最好**写成一行**, 可以用 `&&`连接多个命令或用`\\`换行书写.

  例如:

  ```
  ENV NODE_ENV=production \
      APP_PATH=/node/app
  ```

  

* 由于构建镜像时会逐层检查build cache, 因此最好把不经常变动的层提到前面去, 比如`ENV`

## 使用alpine

基础镜像层可以使用alpine, 这是一个超级小的Linux镜像. 上例的基础镜像层是node, 可以:

### 使用软件的alpine版本

[dockerhub](https://link.juejin.cn/?target=https%3A%2F%2Fhub.docker.com%2F_%2Fnode%3Ftab%3Ddescription%26page%3D1%26ordering%3Dlast_updated) 查看 node 版本

对于node等基础软件,使用其alpine版本:

```
FROM node:14.17.4-alpine
```

可以去 

#### 使用alpine linux

使用alpine linux作为基础镜像层,然后手动装node等基础软件. 该方法效果最显著.

alpine使用apk作为包管理工具, 可以到 [apk官网](https://pkgs.alpinelinux.org/packages?name=npm&branch=edge&repo=&arch=&maintainer=) 查看apk包版本

* 需要注意alpine镜像版本. 比如, 如果使用镜像alpine:3.16, 而我需要的nodejs版本只存在于alpine3.13, 就会无法拉取该依赖

  * 即: 一定要指定alpine版本. **不要选择 latest 版本**( `From alpine:latest`) 
* 其次, 有人会用[阿里云的apk源](http://mirrors.aliyun.com/alpine/?spm=a2c6h.25603864.0.0.133a2f83TmQnBB), 此时也要注意选择alpine镜像的版本



```dockerfile
FROM alpine:3.13 AS base
LABEL maintainer="LYK-love"

# RUN echo "http://mirrors.aliyun.com/alpine/edge/main/" > /etc/apk/repositories \
#     && echo "http://mirrors.aliyun.com/alpine/edge/community/" >> /etc/apk/repositories \
RUN apk update \
    && apk add --no-cache --update nodejs=14.20.0-r0 npm=14.20.0-r0 \
    && npm config set registry http://r.cnpmjs.org/ --production

# ... 后面的步骤不变
```

* 用户软件( node, yarn等 )也最好要**指定版本**, 

* **下面的例子中使用方案2**

* 注意:

  * `apk`和其他工具不同, 不会在下载node时顺便下载npm, 所以如果使用npm, 需要手动下载:

    ```sh
    apk add --no-cache --update nodejs=14.17.4-r0 npm=8.19.1-r0 
    ```

    

## 提前下载依赖

* 对于前端项目, 下载依赖在构建镜像时花了很大时间. 我们可以利用构建缓存, **先将package.json 文件单独提前拷贝到镜像，再装依赖**，执行命令装依赖这层的前一层是拷贝 package.json 文件，因为**安装依赖命令不会变化，所以只要 package.json 文件没变化，就不会重新执行 `yarn` 安装依赖，它会复用之前安装好的依赖**.

  示例:

  ```dockerfile
  FROM alpine:latest
  
  # 使用 apk 命令安装 nodejs 和 yarn，如果使用 npm 启动，就不需要装 yarn
  RUN apk add --no-cache --update nodejs=14.17.4-r0 yarn=1.22.10-r0
  
  # 暴露端口
  EXPOSE 4300
  
  # 设置环境变量
  ENV NODE_ENV=production \
      APP_PATH=/node/app
  
  # 设置工作目录
  WORKDIR $APP_PATH
  
  # 拷贝 package.json 到工作跟目录下
  COPY package.json .
  
  # 安装依赖
  RUN yarn
  
  # 把当前目录下的所有文件拷贝到镜像的工作目录下 .dockerignore 指定的文件不会拷贝
  COPY . .
  
  # 启动命令
  CMD yarn start
  ```

  

## 利用多阶段构建

运行 node 程序只需要生产的依赖和最终 node 可以运行的文件，就是说我们运行项目只需要 package.js 文件里 dependencies 里的依赖，devDependencies 依赖只是编译阶段用的

* 比如 <u>eslint 等这些工具在项目运行时是用不到的</u>，再比如我们项目是用 typescript 写的，node 不能直接运行 ts 文件，ts 文件需要编译成 js 文件，

<u>运行项目我们只需要编译后的文件和 dependencies 里的依赖就可以运行，也就是说最终镜像只需要我们需要的东西</u>，任何其他东西都可以删掉，下面我们使用多阶段改写 Dockerfile:

```dockerfile
# 构建基础镜像
    FROM alpine:3.16.2 AS base

    # 设置环境变量
    ENV NODE_ENV=production \
        APP_PATH=/node/app
    
    # 设置工作目录
    WORKDIR $APP_PATH

    # 安装 nodejs 和 yarn
    RUN apk add --no-cache --update nodejs=14.17.4-r0 yarn=1.22.10-r0

# 使用基础镜像 装依赖阶段
    FROM base AS install

    # 拷贝 package.json 到工作跟目录下
    COPY package.json ./

    # 安装依赖
    RUN yarn

# 最终阶段，也就是输出的镜像是这个阶段构建的，前面的阶段都是为这个阶段做铺垫
    FROM base

    # 拷贝 装依赖阶段 生成的 node_modules 文件夹到工作目录下
    COPY --from=install $APP_PATH/node_modules ./node_modules

    # 将当前目录下的所有文件（除了.dockerignore排除的路径），都拷贝进入镜像的工作目录下
    COPY . .

    # 启动
    CMD yarn start
```

## github 的 actions 构建镜像问题

github 提供的 actions，每次都是一个干净的实例，什么意思，就是每次执行，都是干净的机器，这会导致一个问题，会导致 docker 没法使用缓存，那有没有解决办法呢，我想到了两种解决办法：

1. [docker 官方提供的 action 缓存方案](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fdocker%2Fbuild-push-action%2Fblob%2Fmaster%2Fdocs%2Fadvanced%2Fcache.md)

   我用的是 Github cache 方案

2. 自托管 actions 运行机器

   相当于 gitlab 的 runner 一样，自己提供运行器，自己提供的就不会每次都是干净的机器，[详情看 actions 官方文档](https://link.juejin.cn?target=https%3A%2F%2Fdocs.github.com%2Fcn%2Factions%2Fhosting-your-own-runners%2Fabout-self-hosted-runners%23requirements-for-self-hosted-runner-machines)

3. 先构建一个已经安装好依赖包的镜像，然后基于此镜像再次构建，相当于多阶段构建，把前两个阶段构建的镜像产物推送到镜像仓库，再以这个镜像为基础去构建后续部分。借助镜像仓库存储基础镜像从而达到缓存的效果（此方案来源于评论里的大佬）

   ```dockerfile
   # 以这个镜像为基础去构建，这个镜像是已经装好项目依赖的镜像并推送到镜像仓库里，这里从镜像仓库拉下来
   FROM project-base-image:latest
   
   COPY . .
   
   CMD yarn start
   复制代码
   ```

# Examples

## Vue app

### Dockerfile

#### 使用node的alpine:

```dockerfile
# build stage
# FROM node:14.20.1-slim  as build-stage
FROM node:14.16.0-alpine3.13 AS build-stage
LABEL maintainer="LYK-love"
WORKDIR /app
COPY package*.json ./
RUN node -v && npm -v \
    && npm config set registry http://r.cnpmjs.org/ \
    && npm install 

COPY . .
RUN npm run build



# production stage
# FROM nginx:1.21.5 as production-stage
FROM nginx:1.21.5-alpine as production-stage
RUN nginx -v
COPY --from=build-stage /app/dist/ /usr/share/nginx/html/
COPY --from=build-stage /app/default.conf /etc/nginx/conf.d/default.conf
EXPOSE 80
CMD [ "nginx","-g","daemon off;" ]
```

我实验了一下, 如果全都使用标准镜像(`node:14.20.1-slim` +  `nginx:1.21.5` ), 则镜像总大小为151.42MB. 而全都使用alpine镜像后, 总大小为39.03MB, 这是惊人的提升.

#### 使用alpine linux

```dockerfile
RUN apk update \
    && apk add --no-cache --update nodejs=14.20.0-r0 npm=14.20.0-r0 \
    && npm config set registry http://r.cnpmjs.org/ --production

# ENV NODE_ENV production


FROM base AS build-stage
WORKDIR /app
COPY package*.json ./
RUN node -v && npm -v \
    && npm install 
    # && npm install -g @vue/cli@5.0.1

COPY . .
RUN npm run build

# production stage
FROM nginx:1.21.5-alpine as production-stage
COPY --from=build-stage /app/dist/ /usr/share/nginx/html/
COPY --from=build-stage /app/default.conf /etc/nginx/conf.d/default.conf
EXPOSE 80
CMD [ "nginx","-g","daemon off;" ]
```

总体大小为39.03MB, 感觉反而不如node-alpine呢...... 为啥啊??



### .dockerignore

```
#Dependency directory
# https://www.npmjs.org/doc/misc/npm-faq.html#should-i-check-my-node_modules-folder-into-git
node_modules
.DS_Store
dist

# node-waf configuration
.lock-wscript

# Compiled binary addons (http://nodejs.org/api/addons.html)
build/Release
.dockerignore
Dockerfile
*docker-compose*

# Logs
logs
*.log

# Runtime data
.idea
.vscode
*.suo
*.ntvs*
*.njsproj
*.sln
*.sw*
pids
*.pid
*.seed
.git
.hg
.svn
```

### Commands

1. build:

   ```
   docker build -t Frontend_VolatileReborn . 
   ```

2. run:

   ```
   docker run -it -p 8080:80 --rm --name Frontend_VolatileReborn Frontend_VolatileReborn:latest 
   ```

3. visit: localhost:8080