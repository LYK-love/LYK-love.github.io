---
title: Docker Swarm
tags: Docker
categories: Technology
date: 2022-03-24 23:44:59
---


Outline:

* Basic Idea
* Commands
* Swarm Service
* Swarm Lock

<!--more-->

# Preface

Docker Swarm是一个Docker容器集群编排方案, 同类型的还有K8S, 简而言之, K8S > Docker Swarm. 尽管如此, 但Docker Swarm由Docker原生支持, 而且比K8S简单, 学习它可以初步了解一下容器编排., 可以当作K8S的简易入门.

* 也就是说Docker Swarm就是个玩具...



本章需要结合*Docker Network*理解



使用Swarm, 需要打开Swarm所需端口：

* `TCP/2377`： Swarm的集群管理默认使用2377端口
* `TCP/7946`, `UDP/7946`: Swarm的节点发现使用7946端口



# Basic Idea

Docker Swarm由Docker原生支持, 能够创建Dokcer容器集, 并进行编排

## node

![Docker Swarm Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Swarm/Docker%20Swarm%20Arch.png)

node: 一个集群( Swarm )由多个node组成, 一个node就是一台docker主机. node分为Manager和worker

* Manager:  负责集群的控制面板( Control Plane ),  Manager
* Worker



Swarm node采取主从方式, 有多个Manager,  但同一时刻有且仅有一个Manager处于Active, 处于Active的Manager称为`leader`, 其余Manager称为`follower`

* `leader`是唯一一个对Swarm进行控制的节点, 如果`follower`接收到了Swarm命令, 它会将其转发到主节点
* `leader`, `follower`是Raft的术语, Swarm采用了Raft共识算法



## Raft

Docker Swarm采用了Raft共识算法, 以下是两个原则:

* 部署奇数个Manager. 如果Manager之间分区, 掌握多数Manager的分区就会对Swarm进行管理; 反之,如果偶数个分区,会出现Manager数量相同的情况,无法进行决策,称为Split-Brain
*  Manager数量控制在3~5个. 更多的Manager意味着要花更长的时间达成共识
* Manager可以进行分区, 但是各分区之间的网络一定要确保畅通





## service

Docker Swarm的最小调度单元是服务, 也就是Docker Compose里定义的"服务"

* 服务就是容器的组合, 而且提供了一些高级特性, 比如一些配置文件

## etcd



etcd( European Toiletries and Cosmetics Database) :   a distributed, consistent **key-value** store for **shared configuration** and **service discovery**,  许多分布式系统都采用了etcd, 包括K8S和Docker Swarm

*  etcd位于所有管理节点上, 保存了Swarm的配置和状态

* etcd运行在内存, 并保持数据的最新状态



## token

任何node加入Swarm的唯一凭证就是准入令牌`<token>`



token的格式为:  `PREFIX - VERSION - SWARM ID - TOKEN`

*  `PREFIX`: 永远是`SWMTKN`
* `VERSION`: Swarm的版本
* `SWARM ID`: Swarm认证信息的哈希值
* `TOKEN`: 其内容决定了该令牌是Manager还是worker的准入令牌



   因此,对于指定了加入Swarm的角色的token, 除了`TOKEN`字段外,其他字段应该相同

## TLS

Docker Swarm采用TLS, 每个node都有自己的客户端证书,  证书的更新周期默认是90天



### 查看CA配置:

```
docker system info

# 输出为
Swarm: active                                                                                                                                                                                     
  NodeID: 0b51jn6a7l72c7rky9k7w3b1d                                                                                                                                                                
  Is Manager: true                                                                                                                                                                                 
  ClusterID: 47zrkbd66toz8zo0fyqgk5oyv 
<SNIP>                                    
  CA Configuration:                                                                                                                                                                                
   Expiry Duration: 4 weeks        # 证书过期时间                                                                                                                                                                
   Force Rotate: 0                              
  Autolock Managers: false                                                                       
  Root Rotation In Progress: false
<SNIP>
```

## 指定外部CA

`docker  swarm  init`加` --external-ca`参数来指定外部CA



### 更新证书的更新周期

可以用`docker swarm update` 配置证书的更新周期:

```
# 更新到30天
docker swarm update --cert-expiry 720h
```



### CA配置



```
docker swarm ca
```

* 使用时用`--help`来查看具体功能

# Commands

* 只有manager能查看集群信息, worker无权查看, 因此`docker service ls`之类的命令只有Manager能用

## 创建Swarm

创建一个新的Swarm, 执行该命令的节点会成为第一个Manager, 也是根CA节点, 且切换到Swarm模式, :

```shell
docker swarm init
```

* `--advertise-addr <ip:port>`: 指定该节点公布给外界的ip和端口.  这是可选的,但建议总是手动设置这两个属性
  * 可以指定一个节点上没有的ip用于负载均衡
  * 端口默认是`2377/tcp`
* `--listen-addr <ip:port>`: 指定用于承载Swarm流量的ip和端口, 通常与`--advertise-addr`相匹配
* `--autolock`: 开启swarm锁
* ` --external-ca`: 指定外部CA

## 获取准入令牌



在Manager上, 获取加入到该Swarm的准入令牌( token ):

```shell
docker swarm join-token manager # 获得的token能让其他节点作为manager加入
docker swarm join-token worker # 获得的token能让其他节点作为worker加入
```

## 更新准入令牌

废除原有的准入令牌,再发布新令牌

```shell
docker swarm join-token --rotate manager #  更新已发布的manager的准入令牌
docker swarm join-token --rotate worker # 同理
```

* 新令牌和旧令牌只有`TOKEN`字段不同, `SWARM ID`还是相同的

可以废除当前令牌, 再发布新的

## 加入Swarm

指定节点加入某Swarm

```shell
docker swarm join --token <token> <target-ip:port>
```

* 可以看到, 节点以什么身份加入Swarm, 完全取决于所给的Token, 节点自己没有自定义的权利



## 查看Swarm

列出Swarm中所有节点:

```shell
docker node ls
```

* 仅限Manager使用, worker无权查看集群状态
* `MANAGER  STATUS` 一列没有任何显示的是worker
* ID列显示星号( `*` )的是执行该命令的节点

## 离开Swarm

```shell
docker swarm leave
```

* `--force`: Manager leave需要加`--force`



##   创建Service



创建新服务,  

```shell
docker service create --name <service-name> \
--replicas <num-of-replica> \
<image>
```

* `docker service create` 格式与`docker container run` 类似

* `--replicas`: 告知Docker应该总是有n个此服务的副本, 这定义了`期望状态`
  *  默认为1
  * Leader会按要求在Swarm中实例化n个副本,
    * 服务副本使用相同的镜像和配置
    * **Manager也会作为worker运行**
  
* `-p, --publish port`：`<host-port>:<container-port>`， 宿主机端口映射到容器端口，由于是swarm模式，该宿主机端口会监听在集群所有节点上
  
* 注意，只有**拥有该镜像的节点**才会被调度到运行该服务, 可以从`docker service ps <service>`中看到，某些节点“拒绝了任务调度，因为”：
  
  ```
  No such image: <imaeg>
  ```
  
  
  
  



Swarm会持续确保服务的实际状态和期望状态一致(也就是K8S中的调协循环)

* Swarm会在后台轮询检查所有服务, 来持续比较服务的实际状态和期望状态





## 查看Service

列出Swarm中所有运行中的服务:

```shell
docker service ls
```





进一步查看Swarm中某个服务的信息, 比如哪些节点在运行该服务实例:

```shell
docker service ps <service>
```

* 在运行任务的节点上运行`docker ps`也能看到这个service对应的容器



查看服务的详细信息:

```shell
docker service inspect --pretty <service>
```

* `--pretty`:  文本更可读



## 改变Service

对运行中的服务的属性进行变更, 这要求**节点都处于overlay网络**. 

```shell
docker service update <service>
```

* `--autolock=true`: 开启swarm锁

* 滚动更新:

  ```shell
  docker service update \
  --image <new-image> \ # 指定新镜像
  --update-parallelism <num-of-replica-per-update> \ # 每次更新的副本数
  --update-delay 20s uber-svc # 每次更新的延迟
  <service> 
  ```

所有update操作都是持久的, 可以用`docker service inspect` 查看



## 服务扩缩容

 对服务副本个数进行增减

```shell
docker service scale
```



##  删除Service

删除服务, 该命令不会要求确认

```shell
docker service rm
```

## 配置CA

```shell
docker  swarm ca
```

## 服务滚动更新

```
docker service update \
--image <new-image> \ 
--update-parallelism <num> \ 
--update-delay <time> uber-svc \
<service-to-update>
```

* `--update-parallelism <num>`： 每次更新`num`个副本
* `--update-delay <time>` # 每次更新有`time`s 延迟



## 查看Service日志

  查看服务的日志

```shell
docker service logs
```





# Swarm Service

## 创建Swarm服务

创建新服务,:

```shell
❯ docker service create --name web-fe \
> -p 4000:8080 \
> --replicas 5 \
> nigelpoulton/pluralsight-docker-ci 
```



 ## 副本模式 vs 全局模式

服务的复制模式:

* 副本模式(  `replicated` ): 默认模式, 会部署期望数量的副本,并尽可能均匀地讲个副本分布在各个集群中
  * 这意味着一个主机可能被部署多个副本
* 全局模式了每个节点上仅运行一个副本



## 扩缩容

```shell
 docker service scale=<expected-number>
```

## 删除服务

```shell
docker service rm <service-name>
```



 验证服务是否被删除:

```shell
docker service ls
```

* 只有Manager可用

## 滚动更新

滚动更新需要节点处于overlay网络中. 如果位于bridge网络中, 则其他节点是不会收到更新的



先创建一个overlay网络,:

```
docker network create -d overlay uber-net
```

* 由*Docker Network*得, 一个Swarm节点直到在覆盖网络上启动容器时,才会将自己接入该网络, 因此,此时在其他节点上,看不到该网络



然后创建一个服务,部署4个副本, 连接到overlay网络

```shell
❯ docker service create --name uber-svc \
--network uber-net \ # 接入overlay网络
-p 80:80 --replicas 4 \
nigelpoulton/tu-demo:v1
```

* 此时在其他节点上启动了容器,因此能看到该网络



```shell
❯ docker service update \
--image nigelpoulton/tu-demo:v2 \ # 指定新镜像
--update-parallelism 2 \ # 每次更新两个副本
--update-delay 20s uber-svc # 每次更新有20s延迟
uber-svc # 对uber-svc 进行更新
```

* 此时在其他节点上`docker container ls` 可以看到已经运行了新版本的镜像

# Swarm Security

Docker Swarm提供了许多安全特性( 许多已经被前文提到 ) , 包括:

* 加密 node ID
* 基于TLS的认证
* 安全准入令牌
* 周期性证书更新
* CA配置
* 加密集群存储: 目前的存储基于`etcd`, 且会在Swarm manager间自动复制, 存储默认加密
* 加密网络

# Swarm Lock

重启旧的Manager, 进行备份恢复等操作都会对集群造成影响, 为此, Docker Swarm提供了锁机制, 这会**强制要求重启的管理节点在提供一个集群解锁码之后才能接入集群**

* 需要手动开启



## 开启锁

在创建Swarm时开启锁:

```shell
docker swarm init --autolock
```



 在已有Swarm上开启锁:

```shell
docker swarm update --autolock=true
```



上锁后会得到解锁码:

```shell
❯ docker swarm update --autolock=true
Swarm updated.
To unlock a swarm manager after it restarts, run the `docker swarm unlock`
command and provide the following key:

    SWMKEY-1-RAjjfCURYShYusB+KEJRL3RDzz6B9hA1z48tmqaTJWs

Please remember to store this key in a password manager, since without it you
will not be able to restart the manager.
```

## 验证锁效果

开启锁后, 重启一个管理节点:

```
service docker restart
```



```
docker node ls
```



输出为:

```
error response from daemon: Swarm is encrypted and needs to be unlocked before it can be used. Please use "docker swarm unlock" to unlock it.
```





## 解锁

```shell
 docker swarm unlock
 # 然后会要求你输入解锁码
```

# swarm实战

我们要将前端服务`volatile_frontend_svc`(容器监听80端口)部署到集群，对外暴露集群的80端口

## 配置

| 主机名          | 主机ip | 角色                 |
| --------------- | ------ | -------------------- |
| lyk阿里云服务器 | **     | master，CICD工作节点 |
| lyk华为云服务器 | **     | master               |
| lyk腾讯云服务器 | **     | master               |

3台Master， 3台Worker（ Master也同时作为Worker，因此实际上只有三台主机 ）





## 准备

前置准备：所有节点必须打开：

- UDP/4789： 绑定到VTE
- TCP/2377： Swarm的集群管理默认使用2377端口
- TCP/7946, UDP/7946: Swarm的节点发现使用7946端口

## 步骤



1. 先在阿里云主机上创建第一个master节点：

   ```
   docker  swarm init --advertise-addr **:2377
   ```

   * 填该master节点的公网ip

2. 生成令节点作为master加入集群的令牌：

   ```
   docker swarm join-token manager
   ```

   * 该命令的输出即为令牌

3. 在其他节点上使用上述令牌，使其作为master加入该swarm集群。 成功后执行下述命令，查看集群中的节点：

   ```
   docker node ls 
   ```

4. 在任意master上创建overlay网络，名为`volatile`:

   ```
   docker network create -d overlay volatile
   ```

5. 在master上基于镜像创建新服务`volatile_frontend_svc`，并使用网络`volatile`:

   ```
   docker service create --name volatile_frontend_svc --network volatile -p 80:80 --replicas 3 lyklove/volatile_frontend:latest
   ```

   * 这里设置服务实例数为3
   * 我们将集群的80端口映射到了容器的80端口。 因此访问集群的任意节点的80端口的流量最终都会被抓发到运行了该服务副本的节点

6. （后续）滚动更新:

   ```shell
   docker service update --image lyklove/volatile_frontend:new --update-parallelism 2  --update-delay 1s volatile_frontend_svc
   ```

- 基于新镜像`lyklove/volatile_frontend:new `更新服务，并在其他节点上也进行服务更新
- 该命令可以在任意拥有该新镜像的master节点上执行

## 集成CICD

可以发现，CICD只需要将服务打包成镜像，然后利用该镜像滚动更新就行了



Jenkins脚本`jenkinsfile.groovy`:

```java
// ...
// 根据代码构建新镜像
stage("update service by built image"){
        sh "docker service update --image ${IMAGE_TO_RUN} --update-parallelism 2  --update-delay 2s ${SERVICE_NAME}"
    }
```

## 集群使用

通过`[host-ip]:80`访问前端

其中`host-ip`可以是集群中任意节点的ip
