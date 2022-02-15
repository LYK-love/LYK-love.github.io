---
title: dockerizing
tags: Dokcer
categories: Container
---

Outline:

* 单体应用容器化
* 多阶段构建
* 利用构建缓存
* 合并镜像

本章介绍应用的容器化

<!--more-->

# Intro

应用容器化步骤：

1. 编写应用代码
2. 创建Dockerfile,其中包括当前应用的描述，依赖以及如何运行这个应用
3. 对该Dockerfile执行`docker image build`
4. 等待Docker将应用程序构建到Docker镜像中

![dockerizing workflow](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Toolkit/dockerizing%20workflow.png)



# 单体应用容器化

## Dockerfile

构建上下文（Build Context）： 包含应用文件的目录

Dockerfile一般放在构建上下文的根目录下

Dockerfile首字母不能小写

Dockerfile:

* 由一行行命令语句组成，并且支持以 `#` 开头的注释行
  * 命令语句： `INSTRUCTION argument`: 不区分大小写，一般`INSTRUCTION`大写

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

* `FROM  <image>`： 将指定的镜像的作为要构建的镜像的基础镜像层，一般是OS



* ` LABEL <tag> <tag>`：添加一些元数据，每个tag都是键值对



*  `RUN <command>` 或 `RUN ["executable", "param1", "param2"]`：

  前者将在 shell 终端中运行命令，即 `/bin/sh -c`；后者则使用 `exec` 执行。指定使用其它终端可以通过第二种方式实现，例如 `RUN ["/bin/bash", "-c", "echo hello"]`

  每条 `RUN` 指令将在当前镜像基础上执行指定命令，并提交为新的镜像。当命令较长时可以使用 `\` 来换行



*   `COPY <src> <dest>`：

  复制本地主机的 `<src>`（为 Dockerfile 所在目录的相对路径，即构建上下文）到容器中的 `<dest>`



* `ENTRYPOINT`

  两种格式：

  - `ENTRYPOINT ["executable", "param1", "param2"]`
  - `ENTRYPOINT command param1 param2`（shell中执行）。

  配置容器启动后执行的命令，并且不可被 `docker run` 提供的参数覆盖。

  每个 Dockerfile 中只能有一个 `ENTRYPOINT`，当指定多个时，只有最后一个起效。



* `EXPOSE <port> [<port>...]`：

  告诉 Docker 服务端容器暴露的端口号，供互联系统使用。在启动容器时需要通过 -P，Docker 主机会自动分配一个端口转发到指定的端口



* `VOLUME ["/data"]`：

  创建一个可以从本地主机或其他容器挂载的挂载点，一般用来存放数据库和需要保持的数据等。

## 构建镜像

```shell
docker image build [选项] path
```

按行来读取path下（包括子目录）的 Dockerfile，并将该路径下所有内容发送给 Docker 服务端，由服务端来创建镜像

* `-t` : 指定镜像的标签信息,即`<image>`



一般而言，如果指令会对镜像增改，那么会新建镜像层， 如果指令只是指示Docker如何构建或者如何运行应用程序，那么就只会增加镜像的元数据



example:

```shell
docker image build -t web:latest .
```



##  推送镜像

先登陆docker hub：

```shell
docker login
```



push镜像：

```shell
docker image push [OPTIONS]  <image>
```

push镜像需要如下信息：

* Registry: 默认`docker.io`
* Repository: 被推送镜像的REPOSITORY属性值
* Tag:  默认`latest`



 假设镜像仓库名是web, 那么push后，镜像位于`docker.io/web:latest`,然而用户一般没有一级命名空间的权限

## 查看镜像构建过程

```shell
docker image history <image>
```

每行内容都对应Dockerfile的一条指令（自下而上）

