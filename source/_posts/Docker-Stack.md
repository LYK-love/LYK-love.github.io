---
categories:
- Software Engineering
date: 2022-03-25 04:48:35
tags: Docker
title: Docker Stack
---

Outline:

* Basic Idea
* Commands
* docker-stack.yml



Docker Stack是Docker Compose的进化版,  是Docker原生的部署和管理多服务应用的方案, 默认集成在Docker引擎中, 且提供了简单的声明式接口对应用进行部署和全生命周期管理



<!--more-->

# Basic  Idea

虽然是Docker Compose的进化版, 但是Stack是Docker原生的, 和Swarm一样

* 事实上, Docker Stack依赖于Docker Swarm, Stack将被部署到Swarm上



对应用的任何变更都应该通过Stack文件进行声明, 然后用`docker stack deploy`部署

* Stack文件是Stack的配置的唯一声明, 所有Stack相关的改动都要体现在Stack文件中
* 不要用命令来修改



Docker Stack**不支持build**, 意味着在部署Stack之前, 所有镜像必须提前build, 这一点不同于Docker Compose



具体细节就不赘述了, 用的时候再查

# Commands

## 部署

```shell
docker stack deploy
```



## 列出Stack

列出Swarm集群的全部Stack:

```shell
docker stack ls
```


## 查看Stack详情

```shell
docker stack ps <stack>
```



## 删除Stack

从Swarm中移除Stack

```shell
docker stack rm <stack>
```

* 只会删除网络和服务, 不会删除密钥和卷



# docker-stack.yml

Docker Stack根据Stack文件部署应用, 也就是`docker-stack.yml`

`docker-stack.yml`就是`docker-compose.yml`,  唯一的区别就是Docker Stack文件的`version`要大于3.0

* 二者文件格式相同



[项目地址](https://github.com/dockersamples/atsea-sample-shop-apps)

```yaml
version: "3.2"

services:
  reverse_proxy:
    image: dockersamples/atseasampleshopapp_reverse_proxy # 唯一的必填项,指定镜像
    ports: # 指定端口映射
      - "80:80"
      - "443:443"
    secrets:  
      - source: revprox_cert # 定义了两个密钥,不同于网络, 密钥必须在顶级关键字secrets下定义, 且必须在系统上已存在
        target: revprox_cert
      - source: revprox_key
        target: revprox_key
    networks: # 该网络要么已经存在，要么在networks一级key中指定, 后者会让Docker创建该网络
      - front-tier

  database:
    image: dockersamples/atsea_db
    environment: # 向容器中注入环境变量, 一般都将它们以密钥形式传递
      POSTGRES_USER: gordonuser
      POSTGRES_DB_PASSWORD_FILE: /run/secrets/postgres_password
      POSTGRES_DB: atsea
    networks:
      - back-tier
    secrets:
      - postgres_password
    deploy: # 定义服务约束
      placement:
        constraints:
          - 'node.role == worker' # 当前服务只会运行在Swarm的worker上

  appserver:
    image: dockersamples/atsea_app
    networks:
      - front-tier
      - back-tier
      - payment
    deploy:
      replicas: 2 # 含义同docker swarm
      update_config:
        parallelism: 2
        failure_action: rollback
      placement:
        constraints:
          - 'node.role == worker'
      restart_policy: # 定义了Swarm针对容器异常退出的重启策略
        condition: on-failure# # 如果容器以failure退出, 会立即重启当前容器,重启最多重试三次, 
        delay: 5s                        # 每次都会等待120s来检测是否启动成功, 每次重启间隔5s
        max_attempts: 3
        window: 120s  
    secrets:
      - postgres_password

  visualizer:
    image: dockersamples/visualizer:stable
    ports:
      - "8001:8080"
    stop_grace_period: 1m30s
    volumes:
      - "/var/run/docker.sock:/var/run/docker.sock"
    deploy:
      update_config:
        failure_action: rollback
      placement:
        constraints:
          - 'node.role == manager'

  payment_gateway:
    image: dockersamples/atseasampleshopapp_payment_gateway
    secrets:
      - source: staging_token
        target: payment_token
    networks:
      - payment
    deploy:
      update_config:
        failure_action: rollback
      placement:
        constraints:
          - 'node.role == worker'
          - 'node.labels.pcidss == yes'

networks:
  front-tier:
  back-tier:
  payment:`
    driver: overlay
    driver_opts:
      encrypted: 'yes'

secrets:
  postgres_password:
    external: true # 指定在Stack部署之前, 该密钥必须存在
  staging_token:
    external: true
  revprox_key:
    external: true
  revprox_cert:
    external: true

```



## 关键字

顶级关键字:

* `version`: 代表Compose文件格式的版本号.  要应用于Stack, 需要  > 3.0
* `services`
* `networks`: 默认用`overlay`网络, 因为是Swarm模式
* `secrets`: 
  * `external`: 在Stack部署之前, 该密钥必须存在

## 网络

Docker Stack首先会检查并创建`networks`,  因为服务依赖于网络

默认情况下, overlay网络的控制层是加密的, 如果要加密数据层, 需要在Stack文件中`driver_opts`下指定`encrypted: 'yes'`

## 服务

服务只有一个必填的下级关键字`image`, 指定构建服务副本所需的镜像

其余下级关键字:

* `Docker`: 指定Docker Registry, 默认是Docker Hub
* `ports`: 定义端口映射, 注意由于是Swarm模式, 默认网络是Ingress模式, `port`项可以简写, 如果指定用Host模式, 则`port`项要写完整格式
* `secrets`: 定义了密钥, 不同于网络, 密钥必须已经在顶级关键字secrets下定义, 且必须在系统上已存在
* ` envirenment`: 向容器中注入环境变量, 一般都将它们以密钥形式传递
* `deploy`: 定义部署约束, 比如节点ID, 节点名称, 节点角色, 还有更新约束等待
  * 更新约束就是`docker service uodate `的那些参数, `replicas`之类