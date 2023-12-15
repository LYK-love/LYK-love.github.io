---
categories:
- Software Engineering
date: 2022-03-23 05:39:44
tags: Docker
title: Docker Network
---

Outline:

* Basic Idea
* Docker DNS服务器
* Commands
* Networks



<!--more-->

# Basic idea

Docker使用了Linux的Namespaces技术来进行资源隔离，如PID Namespace隔离进程，Mount Namespace隔离文件系统，Network Namespace隔离网络等。一个Network Namespace提供了一份独立的网络环境，包括网卡、路由、Iptable规则等. 与其他的Network Namespace隔离

* 因此，一个独立的网络就是一个独立的Network Namespace
* 因此，严格意义上讲，下文介绍的Host， None根本不算网络，因为他们没有自己的Network Namespace



![Docker Network Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Docker%20Network%20Arch.png)

![Docker Network Layers](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Docker%20Network%20Layers.png)

Docker网络架构由三部分组成： 

* CNM：  Container Network Model, 容器网络模型，是设计标准
* Libnetwork：是CNM的具体实现，被Docker采用
* 驱动：Go编写，实现了CNM中列举的核心组件

# Docker DNS服务器

Docker sever有一个**DNS服务器**，可以为容器提供DNS解析功能， 也就是说，在容器网络中， **容器名相当于域名**

* Docker DNS服务器记录了全部容器名称和ip地址的映射
* 每个启动时使用了`--name`或`--net-alias`的Docker容器和Swarm服务， 都会将自己的名称和IP地址注册到Docker DNS服务器



每个Docker容器都有自己的本地DNS解析器，相当于**DNS代理服务器**。像正常的网络一样，如果DNS解析器在本地缓存中没有找到对应映射，就会向Docker DNS服务器发起递归查询



## CNM

定义了三个基本要素：

* Sandbox： 就像容器中的容器，其中运行着独立的网络栈。 被放在容器内部，为容器提供网络连接
* 终端： 相当于虚拟网卡， 负责将沙盒连接到网络
* 网络：就是软件实现的网桥

![CNM](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/CNM.png)



![CNM multi-network](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/CNM%20multi-network.png)

* 虽然容器A,B运行于同一个主机，但是由于有不同的沙盒，所以网络堆栈不同

* 容器A, B可以通信，因为都接入了网络A. 

* 容器B的两个终端属于不同网络， 没有交换机无法通信

## Libnetwork

实现了CNM定义的三大组件



## Driver

Docker封装的内置驱动( on Linux )：

* Bridge
* Overlay
* Macvlan

第三方也可以编写外部驱动

每个驱动都负责其上所有网络资源的创建和管理

Libnetwork支持同时激活多个网络驱动。 这意味着Docker环境可以支持一个庞大的异构网络

# Commands

## 创建网络

注意到只能用对应驱动创建网络， 而None，Host， Container这些特殊的“网络”，不需要驱动，也就没法用驱动创建

创建容器网络：

```shell
docker network create [OPTIONS] [network_name]
```

* `-driver, -d`: 驱动程序管理网络(  默认 `bridge`  )

  * `-d  bridge`: 创建`bridge`网络（仅限linux），这还会在主机内核中创建一个新的网桥， 查看liunx网桥：

    ```shell
    brctl show
    ```
    
  * `-d overlay`： overlay网络， 控制层默认用了TLS加密，  可以再指定`-o encrypted`对数据层加密
  
    * `--subnet=<subnet1> --subnet=<subnet2> ...`:  创建具有多个子网的覆盖网络（覆盖网络可以划分子网）， Docker负责子网间的路由

* `-p`, `--publish`: 指定端口映射


___

## 查看网络

查看已有的网络：

```shell
docker network ls
```



查看指定网络的详细信息：

```shell
docker network inspect [network_name]
```



## 删除网络



删除Docker主机上指定的网络

```shell
docker network rm <network>
```



删除Docker主机上所有未使用的网络

```shell
docker network prune
```





## 创建容器并定制DNS

启动新容器，向其添加自定义的DNS服务器和域名：

```shell
docker container run -it --name <dontainer-name> \
--dns=<nameserver-ip> \
--dns-search=<domain-name> \
<image> <command>
```



# Networks

None， Host， Containers网络比较特殊，我们一般也不用

## 

## none

就是没有网络，使用此网络的主机没有ip地址，处于完全隔离的状态

## host

Host网络即容器直接使用宿主机的网络，与主机在相同的网络命名空间下，使用相同的网络栈，容器可以直接使用主机的所有端口

即不进行任何网络的虚拟化

## container

container网络下的容器都共享相同的Network Namespace， 但除此之外，其他的namespace依然隔离

* 这意味着容器共享了网络栈
* 这意味着两个容器可以互相ping通

## 单机桥接网络

* 单机： 该网络只能在单个主机上运行，且只能连接所在主机上的容器
* 桥接：该网络是交换机的软件实现



每个Docker主机都有一个默认的单机桥接网络， 在linux上名为bridge,  windows上名为nat

* 除非在容器创建时指定参数`--network`. 默认情况下，所有容器都会连接到该网络



linux主机上的bridge网络由Bridge驱动创建， 而Bridge底层基于Linux内核的Linux Bridge技术.

默认的bridge网络被映射到`docker0`Linux网桥, 容器连接到该网络后，docker就会从docker0子网中分配一个 IP 给容器使用，并设置 docker0 的 IP 地址为容器的**默认网关**

![bridge principle](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/bridge%20principle.png)

 创建单机桥接网络：

```shell
docker network create -d bridge [name]
```

### 容器通信

同一网络中的容器可以通过容器名来ping通， 因为容器内部运行了一个本地的DNS解析器，将请求转发到docker内部DNS服务器， 后者记录了容器启动时通过`--name`或`--net-alias` 指定的名称与容器之间的映射

#### 示例

 

```
❯ docker container run -it --name c1 \
--network localnet \
alpine sleep 1d


❯ docker container run -it --name c2 \
--network localnet \
alpine sh
```

### 端口映射

容器启动时可以使用端口映射：

```shell
docker container run -p <host_port>:<container_port> <image>
```

* `-p`, `--publish`: 指定端口映射

## 多机覆盖网络

覆盖网络是个**二层**容器网络,  允许单个网络包含多个主机，这样不同主机上的容器就可以**在链路层实现通信**

* 使用`overlay`驱动， 即需要指定`-d overlay`
  * 覆盖网络的控制层默认是加密的，可以指定`-o encrypted`对数据层加密



* overlay网络需要Swarm模式



* overlay网络中，所有节点必须打开：
  * `UDP/4789`： 绑定到`VTE`， 详见下文“原理”
  * Swarm所需端口：
    * `TCP/2377`： Swarm的集群管理默认使用2377端口
    * `TCP/7946`, `UDP/7946`: Swarm的节点发现使用7946端口



### 容器通信

* 只有当运行中的容器连接到覆盖网络时，该网络才变成可用状态
  * 这意味着在集群中却没有运行（连接到覆盖网络的）容器的节点，是看不到覆盖网络的
    * 此时的`docker network ls` 看不到覆盖网络
    * 当然，创建该网络的节点肯定能看到该网络
* 一个Swarm节点直到在覆盖网络上启动容器时，才会自动将自身加入到覆盖网络
  * 此时的`docker network ls` 可以看到覆盖网络



* 覆盖网络在网络层为容器提供了**完全的抽象**
  * 覆盖网络内的容器在网络层<u>直接通信</u> ， `traceroute`的跳数是1,  尽管这两个容器所在主机可能不在同一个物理网络， 跳数不止1
    * “直接通信” ‘跳数为1“ 的原因是Swarm**默认是Ingress网络，这是个完全图，任意两个节点是直连的**
  * 覆盖网络内的容器可以通过网络内的子网ip通信，也可以用容器名通信（ 参见下文《Ingress网络》 ）

### 原理

> 隧道端点VTEP (VXLAN Tunnel End Point - an entity which originates and/orterminates VXLAN tunnels)
>
> VNI(VXLAN Network Identifier)



Docker使用VXLAN隧道技术， 基于已经存在的三层网络来创建虚拟的二层网络

* VXLAN基于现有的三层网络创建隧道



注意： overlay网络可以实现三层路由，即可以创建一个包含多个子网的overlay网络， Docker负责子网间的路由:

```shell
# 在Sandbo中创建2个虚拟交换机（不再只有1个）， 默认支持路由
docker network create --subnet=<11.1.1.0/24> --subnet=<11.1.1.0/24> -d overlay <network-name>`
```





容器的Sandbox内部会创建一个名为`Br0`的虚拟交换机和一个`VTEP`， 后者一边连到`Br0`， 一边连到**主机的网络栈**， 主机网络栈中的终端可以从所连接的网络中获得IP地址（主机的IP）， 并以UDP Socket的方式<u>绑定到4789端口</u>



每个容器都有自己的虚拟以太网(`veth`)适配器,  并接入本地的`Br0`





![overlay principle](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/overlay%20%20principle.png)

假设node1上的容器为C1, node2上的容器为C2， C1 ping C2 的ip `10.0.0.4`：

* 该请求通过`veth`接口发送到`Br0`, `Br0`的ARP映射表中没有与当前目的ip对应的MAC地址， 因此它会将该frame发送到其上的所有端口
* `VTEP`接口连接到`Br0`,它知道这个frame的映射， 于是`VTEP`将自己的MAC地址返回给`Br0`， 这是个代理ARP响应
  *  和计网一模一样， 只返回下一跳的MAC地址，一步一步迭代
  * `VTEP`接口知道C2, 是因为所有新启动的容器都会将自己的网络详情用网络内置的Gossip协议发送给相同Swarm集群内的其他节点
* `Br0`收到返回结果，它更新自己的ARP映射， 将`10.0.0.4`映射到本地`VTEP`的MAC地址
* `Br0` 将该frame转发到`VTEP`， 后者将frame封装成UDP包， 设置目的IP字段为node2的`VTEP`的IP地址，设置<u>目的UDP Socket端口为4789</u>
  * 封装就是把 VXLAN Header信息（记录了VLAN到VXLAN的映射）添加到frame,  每个VLAN都对应一个VNID, 以便包被解析后可以被转发到正确的VLAN
* 包到达node2后， node2的内核发现目的端口为 UDP 4789, 还知道存在`VTEP`绑定到该端口， 内核就将包发给`VTEP`
* `VTEP`读取VNID, 解压该包， 根据VNID将包发给本地名为`Br0`的连接到VLAN（ 由VNID指定 ）的交换机， 在该交换机上， 包被发送给容器C2

### 示例

注：图中的主机ip请替换为自己的

#### 构建Swarm

![overlay example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/overlay%20%20example.png)

假设有两台Docker主机,  将他们配置为Swarm集群， 令node1为manager, node2为worker:

```shell
# on node1:
docker swarm init --advertise-addr <node1-ip>
```

```shell
# on node2:
# 需要打开2377/tcp, 7946/tcp, 7946/udp
docker swarm join --token <token> <node1-ip>
```

#### 创建覆盖网络

在node1上创建网络：

```shell
# 需要打开4789/udp
docker network create -d overlay <network-name> # 覆盖网络使用overlay驱动
```

* 创建了新的覆盖网络， 还包括了一个TLS加密的控制层
* `-o encrypted`: 设置数据层加密



####  将服务连接到覆盖网络

```shell
# on node1:
docker service create --name <service-name> \
--network <network-name> \
--replicas 2 \
ubuntu sleep infinity        
```

* 创建了新服务，连接到了覆盖网络，且基于指定的镜像创建了两个副本（容器）
  * 在这里，均在容器中用`sleep`来保持容器运行



当Swarm在覆盖网络上启动容器时，会自动将容器运行所在节点加入到网络中

* node2上启动了容器， 因此node2加入到覆盖网络

#### 测试覆盖网络

由后文“服务发现”知， Swarm网络是可以通过容器名来定位的， 这里用ip来定位只是为了测试



先查看被分配给覆盖网络的`Subnet`：

```
docker network inspect uber-net                                                          
[                                                           
    {                                                       
        "Name": "uber-net",                                 
        "Id": "6arolzgpk57l5s6nn3uca25ho",                                                                              
        "Created": "2022-03-23T03:24:24.651086709+08:00",                                                               
        "Scope": "swarm",                                   
        "Driver": "overlay",                                
        "EnableIPv6": false,                                
        "IPAM": {                                           
            "Driver": "default",                                                                                        
            "Options": null,                                
            "Config": [                                     
                {                                           
                    "Subnet": "10.0.1.0/24",        # 子网掩吗                                                                    
                    "Gateway": "10.0.1.1"                                                                               
                }                                           
            ]                                               
<Snip>                   
```

看到覆盖网络的子网是`10.0.0/24`



然后分别查看两个node的对应容器的id和ip地址：

查看id：

```
docker container ls
```



查看容器ip地址：

```shell
docker container inspect \
--format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' \ 
<container>

# node1输出：10.0.1.4 
# node2输出：10.0.1.3
# 确实遵循子网掩码10.0.0/24
```



然后进入任一容器，ping另一个容器的ip,发现能ping通

使用`traceroute`跟踪路由信息，发现路由信息<u>只有一跳</u>，证明覆盖网络中，容器间通信是在网络层直连的



## 接入现有网络

Docker内置的Macvlan驱动可以给容器提供MAC和IP地址， 让容器在物理网络上成为“一等公民”：

![Macvlan principle](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Macvlan%20principle.png)



Macvlan 性能高，但是需要将主机网卡设为混杂模式，大部分公有云平台都不允许这么设置， 因此Macvlan在公有云平台不可行

Macvlan基于linux的Macvlan内核驱动， 因此支持linux内核的所有网络功能， 包括VLAN的Trunk

Macvlan驱动在连接到目标网络前，需要设置：

* 子网信息
* 网关
* 可分配给容器的IP范围
* 主机使用的接口或子接口



### 示例

假设有一个物理网络，其上有两个VLAN： VLAN100： 10.0.0.0/24 ； VLAN200： 192.168.3.0/24



 我们创建一个名为 macvlan100的 Macvlan网络，它连接到VLAN100：

```shell
docker network create -d macvlan \
--subnet=10.0.0.0/24 \
--ip-range=10.0.0.0/25 \
--gateway=10.0.0.1 \
-o parent=eth0.100 \
macvlan100
```

* Macvlan  采用标准的Linux子接口， 需要打上目标VLAN网络的ID, 在本例中是VLAN100, 所以子接口标记为`.100`( `eth0.100` )
* `--ip-range`:   设置Macvlan网络中可分配给容器的IP范围， 这些地址会被保留，不能用于其他节点或者DHCP, 因为没有任何管理功能来检查IP区域重合的问题



将容器部署到网络中：

```shell
docker container run -d --name mactainer1 \
--network macvlan100 \
alpine sleep 1d
```



结果如下：

![Macvlan example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Macvlan%20example.png)





Macvlan支持Trunk功能，这意味着可以在同一台主机创建多个VLAN网络：

![Macvlan multi-vlan](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Macvlan%20multi-vlan.png)

## 服务发现

允许<u>同一网络中的</u>容器和Swarm服务通过名称互相定位

* 显然，这是通过Docker的DNS服务实现的， 原理和正常网络的DNS服务完全相同

### 自定义DNS规则

用户可以自定义Swarm服务和容器的查询规则， 这是通过向容器内部的`/etc/resolv.conf`添加条目实现的（不要问我为什么是`resolv` 而不是`resolve`）

* `--dns`:  添加自定义的DNS服务器， 向`/etc/resolv.conf`中追加这个列表
* `--dns-search`: 指定自定义查询时所使用的域名， 向`/etc/resolv.conf`中追加这个域名



#### 示例

启动新容器，并添加`8.8.8.8`DNS服务器， 同时指定`dockercets.com`作为域名添加到非完整查询中

```
❯ docker container run -it --name c3 \
--dns=8.8.8.8 \
--dns-search=dockercets.com \
> alpine sh
```



进入该容器，查看`/etc/resolv.conf`：

```
/ # cat /etc/resolv.conf
search dockercets.com
nameserver 8.8.8.8
```





## Ingress网络

Swarm支持两种服务发布模式：

* Ingress:   默认， 可以让Swarm集群内任意节点（即使没有运行该服务副本）都能访问该服务
  * Ingress模式底层是一个**完全图**（ 采用Service Mesh网络 ）
  * Ingree网络会**将流量平均分在所有服务副本之上**
* Host： Host模式发布的服务只能通过运行服务副本的节点来访问
  * 这里的host模式不是之前提到的host网络



Host模式发布：

```shell
docker service create -d --name svc1 \
--publish published=5000,target=80,mode=host \
nginx
```

* Ingress模式可以使用简单格式，即形如` -p 5000:80`, 而Host模式必须使用上述的完整格式（逗号前后还不能有空格）
* `published=5000`:  服务通过5000端口向外部提供服务
* `target=80`: 发送到published端口5000的请求， 会映射到服务副本的80端口
* `mode=host`： 只有外部请求发送到运行了服务副本的节点才可以访问该服务

#### 示例

![Ingress example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Container/Docker%20Network/Ingress%20example.png)

* 该命令部署了一个`svc1`服务，连接到了`overnet`网络，并发布到5000端口
* 这里的Swarm节点全部接入了Ingress网络， 所以这个端口被发布到了Swarm范围内
* 集群确保到达Ingress网络中任意节点的5000端口的浏览，都会被路由到80端口的`svc1`  服务
* 当前`svc1`服务只部署了一个副本，因此流量全部分配到Node2
* 箭头展示了访问Node1的5000端口的浏览，通过Ingress网络，被路由到了Node2的正在运行的服务副本上

可以看到，外部流量可能访问任意一个Swarm节点，但是最终都会被路由到运行服务副本的节点