---
title: Network Layer
tags: Computer Networking
categories: Computer Science
date: 2022-02-21 00:33:00
---


Outline:

* Intro
* 虚电路和数据报网络
* 路由器工作原理
* 网际协议IP
* ICMP
* 路由选择算法
* 因特网中的路由选择
* 广播和多播路由选择
* VPN, NAT
* MPLS



ref:  *《计算机网络》 --谢希仁； 《计算机网络自顶而下》*

<!--more-->

# Intro

## 网络层的功能

网络层（第三层）有三个功能：

* 转发( forwarding )： 分组在单一的路由器中从一条入链路传送到一条出链路
  * 是路由器的本地动作
  * 硬件实现
* 路由选择( routing )：网络中决定分组从源到目的地所采取的端到端路径
  * 涉及整个网络的路由器
  * 软件实现
  * 转发和路由选择经常混用
* （某些网络层结构，如ATM, MPLS中有）连接建立： 从源到目的地沿着所选择的路径彼此握手，以便在分组传输之前就建立好状态

## 网络层的组件

![网络层三大组件](https://img-blog.csdnimg.cn/20201214232315784.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxMzk4NDE4,size_16,color_FFFFFF,t_70#pic_center)

网络层三大组件：

* IP协议
* 路由选择协议： RIP, OSPF, BGP
* ICMP协议：差错报告、路由器“信令”





因特网的网络层提供**尽力而为服务**，可以理解为无服务。 当然除了因特网外还有其他的网络结构模型，比如ATM，就提供恒定比特率、可用比特率等服务



## 交换机和路由器

交换机： 进行分组转发，是链路层设备。 

路由器：分组转发和路由选择，网络层设备



路由器具有**转发表**，路由器通过检查到达分组的首部字段的值来转发分组，然后使用该值在该路由器的转发表中索引查询

* 路由选择算法决定了插入转发表中的值



路由器： 

#   虚电路和数据报网络

运输层可以提供<u>面向连接服务和无连接服务</u>（TCP, UDP）, 网络层也类似，但与运输层相比又有不同：

* 网络层中，这些服务是主机到主机的服务，而运输层中是进程到进程的服务
* 网络层要么提供面向连接服务，称为**虚电路网络**；要么提供无连接服务， 称为**数据报网络**。 网络层不能同时提供这两种服务。 
  * 虚电路网络： ATM，帧中继
  * 数据报网络： 因特网
* 运输层连接服务只在<u>端系统</u>中实现， 而网络层连接服务需要在端系统和<u>路由器</u>中实现



可以看到，虚电路网络和数据报网络是网络层的两个基本类型

## 虚电路网络

路由器需要为连接维持**连接状态信息**

* 每当建立和释放连接（虚电路），都要在转发表中增/删表项



虚电路的组成：

* 源到目的主机的路径
* VC号， 延着该路径的每段链路的一个号码
* 该路径上每台路由器的转发表

### VC号

虚电路分组将在它的首部携带一个VC号，VC号在每段链路都不同，<u>从中间路由器的转发表表项更新</u>：

* 注意， **一段链路可以有多条虚电路，每条虚电路有一个VC号**， 因此属于某虚电路的分组在到达对应链路时，会获得唯一的VC号（ 不会与同一链路上其他虚电路的分组发生冲突 ）



示例： 假设主机A要与B创建虚电路，且网络给该虚电路选择路径 A-R1-R2-B,并为三段链路分配VC号 12, 22，32。 该分组离开主机A时，首部的VC号是12,而离开R1时，VC号变成了22；离开R2时，VC号是32

![image-20220219195343203](/home/lyk/snap/typora/49/.config/Typora/typora-user-images/image-20220219195343203.png)

R1的转发表：

| 入接口 | 入VC号 | 出接口 | 出VC号 |
| ------ | ------ | ------ | ------ |
| 1      | 12     | 2      | 22     |
| 2      | 63     | 1      | 18     |
| ...    | ...    | ...    | ...    |



每条虚电路的连接和建立都会让路径上所有路由器的转发表更新



VC号在每段链路都不同的原因：

1. 逐链路代替VC号减少了VC号字段在分组首部中的长度
2. 如过一条链路具有多条虚电路，那么约定互不冲突的VC号将花费大量时间

### 虚电路的三个阶段

虚电路的三个阶段：

* 虚电路建立：发送方运输层与网络层联系，指定接收方地址，网络层决定发送方到接收方的路径，为该路径上的**每条链路决定一个VC号**。 最后在路径上的<u>每个路由器</u>中增加一个表项
* 数据传输
* 虚电路拆除：网络层通知接收方的端系统，并<u>更新路径上每个路由器的转发表</u>以表明该虚电路不存在了



虚电路网络层的两个端系统之间路径上的路由器都要参与虚电路的建立，且每台路由器都完全知道经过它的所有虚电路



端系统向网络层发送的指示虚电路启动与终止的报文，以及路由器之间传递的用于建立虚电路（即修改路由表中的连接状态）的报文，称为**信令报文**（ signaling message ）,用于交换这些报文的协议称为**信令协议**（ signaling protocol ）

## 数据报网络

数据报网络中的路由器不需要维持连接状态信息（因为是无连接的，没有虚电路），但是要在转发表中维持转发状态信息。 装发表存储了目的地址到输出链路接口的映射，通过路由选择算法修改

转发表在将分组的目的地址（当然是IP地址）和转发表表项匹配时，采用**最长前缀匹配**

# 路由器工作原理

## 路由器结构



以下“端口“均指硬件端口，和套接字等软件端口不同

* **输入端口**： 将输入的物理链路与路由器连接。 同时还要在这里完成查询转发表。 一般分组转发到交换结构，进而转发到输出端口；而控制分组（如携带路由选择协议信息的分组）转发到路由选择处理器
  * 输入端口拥有**转发表的影子副本**，因此可以进行查找+转发
* **交换结构**： 用于分组交换，有许多实现，比如经内存交换，经总线交换，经复杂的总线网络交换
* **输出端口**
* **路由选择处理器**： 执行路由选择协议， 维护路由表，并由此计算出转发表。 它还执行网络管理功能



输入/输出端口和交换结构共同实现了转发功能，称为**路由器转发平面**（ router forwarding plane ）

* 纯硬件实现，因此在纳秒级别

路由器选择处理器实现了控制功能（路由选择），称为**路由器控制平面**（ router control plane ）

* 软件实现并在路由选择处理器上执行，在毫秒级别



## 转发表

结构：

* 目的网络地址
* （如果划分了子网）子网掩码
* 下一跳地址



路由器的分组转发： 查看转发表，能直接交付就直接交付，否则就转发给本网络的默认路由器

* 过程中需要将目的地址与子网掩吗做与操作得到网络号， 注意网络号匹配采用**最长前缀匹配**

### 队列等待

如果分组队列过长，耗尽了输出端口的可用内存，就会丢弃分组，即**丢包**。 一般需要在缓存填满前便丢弃（或在首部加标记）一个分组，以便向发送方提供一个拥塞信号。

有许多分组丢弃与标记策略，统称为**主动队列管理**（ Active Queue Management, AQM ） 算法，其中最著名的是**随即早期检测**（ Random Early Detection, RED ）算法



RED： 为输出队列维护一个加权平均值，如果该值大于某个阈值，则丢弃后续到达的分组



当然，如果交换结构不够快，那么在输入端口也将发生分组排队

# 网际协议IP（v4）

网络层分组被称为*数据报*

![IPV4 packet](https://img-blog.csdnimg.cn/2020121423232614.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxMzk4NDE4,size_16,color_FFFFFF,t_70#pic_center)



其中的关键字段如下：

* 版本号：4个比特。通过查看版本号，路由器可以确定如何解释IP数据报的剩余部分，因为不同IP版本使用不同数据报格式。
* 首部长度：4个比特。确定IP数据报数据部分实际从哪里开始。
* 服务类型：使不同类型的IP数据报（如要求时延低的数据报）能相互区别开。
* 数据报长度：16个比特，IP数据报的总长度（首部+数据），以字节计算。IP数据报的理论长度为65535字节，但实际很少超过1500字节。
* 标识，标志，**片偏移**：与**IP分片**有关。IPV6不允许路由器对分组分片。
* **寿命（TTL）**：该字段确保数据报不会永远在网络中循环。数据报每过一个路由器，TTL减1，减到0就丢弃。
* **协议**：**仅在达到目的地才有用。指示IP数据报的数据部分交给哪个运输层协议**，比如6表示交给TCP，17交给UDP。协议号是将网络层与运输层绑定到一起的粘合剂，端口号则用于运输层和应用层的绑定。
* 首部校验和：帮助路由器检测收到的IP数据报的比特错误。TCP/IP在运输层与网络层都执行差错检测。
* 源和目的IP地址：通过源主机通过DNS查找来决定目的地址。
* 选项：该字段允许IP首部被扩展。很少使用，所以数据报首部不包括该字段的信息
* 数据：该字段除了包含TCP和UDP外，也可重载其他类型的数据，如ICMP报文。



 IP数据报的首部有20字节（假设无选项）。如果数据报承载一个TCP报文段，每个数据报共承载40字节的首部（有20字节的TCP首部）以及应用层报文



## IP数据报分片

并非所有链路层协议都能承载相同长度的网络层分组



**最大数据单元**（ Maximum Transmission Unit, MTU ）: 一个帧能承载的最大数据量

* 一段路经上的不同链路可能有不同的链路层协议，因此有不同的MTU



分片： 将数据报中的**数据部分**分成较小的数据报，再封装成帧

* 片的组装是相当复杂的工作， 由端系统实现。这是为了保持网络的简单性
* IPV6没有片偏移字段，根本上废止了分片

## IPV4编址

### 分类编址

Classful addressing



### 无类别域间路由选择

Classless Inter Domain Routing, CIDR

* 取消了传统分类网络的概念
* 和子网掩码的区别：子网掩码只是局限于在某一个子网内或一个站点内使用，而CIDR是对**全球路由系统**都是可见的
  * 这意味着在公网，路由器可以直接对CIDR地址块进行寻址，而不必对主机进行寻址，大大提升了效率
    * 这称为路由聚合
    * 相比之下，子网掩码只能在子网使用，因此传统的分类网络在公网只能按主机寻址



## 获取IP地址

这里指的是公网IP,内网IP分配见下文

* ISP从ICANN等机构获得地址

* 组织从ISP获得一组地址
* 组织内可以用DHCP等方式给主机配置IP地址

## IPV6

IPV6新特性：

* 地址长度从32位扩展到128位
* 简化高效的40字节首部
* 流标签与优先级： 某些分组（如音频、视频传输）可以被当作一个**流**，并打上特定的标签



![img](https://img-blog.csdnimg.cn/f738ea7ed02848c584b0da5130efe77b.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAd2VsbG53,size_20,color_FFFFFF,t_70,g_se,x_16)

* 版本：该4比特字段用于标识IP版本号。IPv6将该字段设为6。注意到将该字段值设置为4并不能创建一个合法的IPv4数据报。

* 流量类型：该8比特字段与我们在IPv4中看到的TOS字段的含义相似。

* 流标签：该20比特的字段用于标识一条数据报的流，能够对一条流中的某些数据报给出优先权，或者它能够用来对来自某些应用的数据报给出更高的优先权，以优于来自其他应用的数据报。

* 有效载荷长度：该16比特值作为一个无符号整数，给出了IPv6数据报中跟在定长的40字节数据报首部后面的字节数量。

* 下一个首部（指传输层协议的首部）：该字段标识数据报中的内容（数据字段）需要交付给哪些个协议（如TCP或UDP）。该字段使用与IPv4首部中协议字段相同的值。

* 跳限制： 转发数据报的每台路由器将对该字段的内容减一。如果跳限制计数达到0，则该数据包将被丢弃。

* 源地址和目的地址：128比特地址

* 数据：IPv6数据报的有效载荷部分。当数据报到达目的地时，该有效载荷就从IP数据报中移除，并交给在下一个首部字段中指定的协议处理。



IPV6弃用的特性：

* 分片和重新组装： Pv6不允许在中间路由器上进行分片与重新组装。这种操作只能在源与目的地执行。如果路由器收到的IPv6数据报因太大而不能转发到出链路上的话，则路由器只需丢掉该数据报，并向发送方发回一个分组太大的ICMP差错报文即可。于是发送方能够使用较小长度的IP数据报重新发送数据

* 首部校验和：因为因特网层中的运输层和数据链路层协议执行了校验操作，所以IPv6去除了校验
* 选项：选项字段不再是标准IP首部的一部分了。但是它并未消失，而是可能出现在IPv6首部中由下一个首部指出的位置上

## 从IPV4到IPV6的迁移

![img](https://img-blog.csdnimg.cn/20190325225036683.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5MzI2NDcy,size_16,color_FFFFFF,t_70)

有两种方案： 双栈， 隧道

* 双栈： 使用双栈的IPV6节点具有完整的IPV4实现，即同时具有收发两种数据报的能力。 在与IPV4节点进行交互时采用IPV4, 与IPV6节点交互时采用IPV6
  * 双栈节点需要知道所要交互的节点是否支持IPV4/6, 这可以通过**DNS查询**实现，**如果一个节点支持IPV6,那么DNS返回一个IPV6地址，反之返回IPV4地址**
  * IPV6数据报中一些字段在IPV4中没有，这意味着如果将其IPV6数据报转化为IPV4的，将会丢失一些信息。 对于路径A - B - C -D - E , 假设除了C节点是IPV4外，其他均是IPV6. 那么A-B的IPV6数据报在转换为IPV4时会不可逆地丢失信息，即使后来又被转换为IPV6数据报发向E
* 隧道：如果两台IPV6数据库之间采用IPV6交互，但它们中间经由IPV4路由器互联，那么可以将整个IPV6数据报放到IPV4的有效载荷中。 
  * 比如图中B和E，要使用IPV6交互，但是它们经由中间IPv4路由器关联

## IPsec

* IPsec是提供安全性服务的新型网络层协议，向后兼容IPV4和IPV6
* IPsec只需在两台互相通信的主机中可用，其他主机和路由器可以继续用普通的IPv4
* IPsec是面向连接的。主机间建立会话后，发送的TCP和UDP报文段都享受IPsec的安全性服务
  * 密码技术约定
  * IP数据报有效载荷的加密
  * 数据完整性
  * 初始鉴别。主机确信在数据报中的源IP地址是该数据报的实际源

# ICMP（V4）

ICMP协议用于在网络层进行差错报告



![img](https://imgconvert.csdnimg.cn/aHR0cDovL2JyeWFudHprLm9zcy1jbi1zaGFuZ2hhaS5hbGl5dW5jcy5jb20vaW1nL0lDTVAucG5n?x-oss-process=image/format,png)

ICMP是网络层协议，但从体系结构上讲位于IP协议之上，因为ICMP报文是作为IP报文的有效载荷承载的。同样，当一台主机收到一个指明上层协议为ICMP的IP数据报时，它分解出该报文的内容交给ICMP（就像任何低层次协议到高层一样）



ICMP报文有两种：

* ICMP差错报文
* ICMP查询报文，查询报文总是成对出现



| ICMP种类 | ICMP类型字段 | 编码 | 描述                     |
| -------- | ------------ | ---- | ------------------------ |
| 查询报文 | 0            | 0    | 回显回答（对ping的回答） |
|          | 3            | 0    | 目的主机不可达           |
|          | 3            | 1    | 目的主机不可达           |
|          | 3            | 2    | 目的主机不可达           |
|          | 3            | 3    | 目的主机不可达           |
|          | 3            | 6    | 目的网络未知             |
|          | 3            | 7    | 目的主机未知             |
|          | 4            | 0    | 源抑制（拥塞控制）       |
|          | 8            | 0    | 回显请求                 |
|          | 9            | 0    | 路由器通告               |
| 查询报文 | 10           | 0    | 路由器发现               |
|          | 11           | 0    | TTL过期                  |
|          | 12           | 0    | IP首部损坏               |

## 使用ICMP的程序



ping程序，就是发送一个ICMP类型8编码0的报文到指定主机。 看到该回显（echo）请求，目的主机发回一个类型0编码0的ICMP回显回答

* 大多数提出/IP实现支持在内核中实现ping服务器， 因此ping服务器不一定是个进程



traceroute程序：

* 向目的主机发送一系列普通的IP数据报，每个数据报都携带了具有一个不可达UDP端口号的UDP报文段 第一个数据报的TTL为1,第二个的为2, 依次类推。 该源主机也为每个数据报启动定时器。 

* 当第n台路由器观察到这个数据报的TTL刚好过期，根据IP协议规则，就会丢弃该数据报并发送一个ICMP警告报文（类型11,编码0）。 
* 该警告报文包含了路由器的名字与IP地址。 当该ICMP报文返回路由器时，源主机从定时器得到往返时延，从ICMP报文中得到第n台路由器的名字与地址。 
* 而数据报最终将到达目的主机，由于它包含了一个具有不可达端口号的UDO报文段， 该目的主机将向源发送一个端口不可达的ICMP报文，当源主机收到这个报文时，就可以停止发送探测分组了

## ICMPv6

ICMPv6：用于IPv6， 因为IPv6和IPv4都不保证数据的可靠交付， 需要ICMP来反馈差错信息

* **ARP和IGMP都被合并到了ICMPv6中** 

![image-20220220235802213](/home/lyk/snap/typora/49/.config/Typora/typora-user-images/image-20220220235802213.png)

# 路由选择算法

原理：将网络抽象为图



依据算法是全局的还是分布式的，可以分为：

* 全局式路由选择算法, aka 链路状态算法（ Link State, LS ）： 该算法以所有节点之间的连通性和所有链路的费用作为输入
* 分布式路由选择算法：每个节点仅知道相邻链路的信息，通过迭代计算并于相邻节点交换信息，逐渐计算出到达目的节点的最低费用路径
  * 最著名的有距离向量( Distance-Vector, DV )算法

## LS算法

就是Dijkstra算法，需要有网络的全局信息



LS算法的缺陷： 链路振荡

### 振荡问题

![img](https://img2020.cnblogs.com/blog/1774310/202006/1774310-20200602174957477-1781975823.png)

假设网络出初始的链路费用和路由选择如下，路由费用等于路由负载

那么算法再次运行时， y会发现顺时针到达w的代价为1,低于逆时针的代价，其他节点亦如是，整个链路的方向变为顺时针

算法再次运行，再次发生上述状况，链路方向又变为顺时针 。。。 循环往复，整个链路在不断**振荡**

## DV算法

距离向量（DV）算法是一种迭代的、异步的和分布式的算法，每个节点都要从一个或多个直接相邻邻居接受某些信息，执行计算然后将其计算结果分发给邻居。

* **分布式**：每个结点都从一个或多个直接连接的邻居接收信息，通过对信息的计算，再把结果通告给邻居
* **迭代**： 一直持续到邻居之间无更多信息要交换为止
* **异步**： 不要求节点相互之间步伐一致地操作，而是当收到邻居发来的信息时进行操作即可。

### Bellman-Ford 方程

Bellman-Ford 方程: 令$c(x,v)$ 表示 x 到邻居 v 的开销，$d_v(y) $表示从 节点 v 到目的地 y 的开销，我们需要在 x 的所有邻居中获得最小值。
$$
d_x(y) = min_v\{ \ c(x,v) + d_v(y) \ \}
$$


### 距离向量

距离向量:  x 在 N 中到其他所有结点 y 的开销的估计值
$$
D_x = [D_x (y): \ y ∈ N]
$$


Bellman-Ford 方程为 DV 算法提供了理论基础。简单地说，也就是**结点获得最短路径的下一跳**，并且将该信息写入转发表中。这时我们也



每个节点x维护如下路由选择信息： 

* 对每个邻居v,从x到直接相连邻居的费用为
* 节点x的距离向量，即$D_x = [D_x (y): \ y ∈ N]$,   是 x 在 N 中到其他所有结点 y 的开销的估计值
* 它的每个邻居的距离向量，即对x的每个邻居v,有$D_v = [D_v (y): \ y ∈ N]$

### 算法步骤：

* 每个节点**周期性**向邻居发送它的距离向量副本。 当节点x从它的任何一个邻居v接收到一个新距离向量路由协定，就保存v的距离向量，并根据Bellman-Ford方程更新自己的距离向量如下：
  $$
  D_x(y) = min_v\{ \ c(x,v) + d_v(y) \ \} \quad  对N中的每个节点
  $$

* 如果x的距离向量因为这次更新被改变，x将向它的每个邻居发送其更新后的距离向量



* 已证明： 只要所有节点继续以异步方式执行此算法，每个费用估计$D_x (y)$收敛到 $d_x (y)$,   $d_x (y)$ 为节点x到y的实际最低费用路径的费用

* DV算法的缺点：无穷计数问题

### 无穷计数问题

![img](https://img2020.cnblogs.com/blog/1774310/202006/1774310-20200602203336144-1456539086.png)





>
>
>图中有X、Y、Z三个节点。我们增加链路费用。 Y检测到它到X的路径费用由4增加到了60。此时节点Z的距离向量为：d(X) = 5, d(Y) = 1, d(Z) = 0。于是Y在更新向量时发现，咦，Z到X的距离只有5诶，那可以先到Z再到X，于是Y的距离向量更新为：d(x) = 5 + 1 = 6, d(Y) = 0, d(z) = 1。我们可以发现，这个逻辑显然是错误的，因为Z到X的距离为5的前提是要经过Y，但Y更新后的路径又要经过Z，这就形成了一个选路环路（routing-loop）问题。因为Y的距离向量更新了（虽然是错误的），但它还是向Z发送了更新报文。Z收到更新报文后，比较了下邻居们到X的距离，发现经过Y的路径距离为1 + 6 = 7，小于直接到X的距离，于是Z也更新的自己的距离向量，然后又将更新后的距离向量发给Y。Y收到后又更新向量为8，然后再发给Z。。。这样循环往复，更新报文在Y和Z之间传来传去，直到第44次迭代后，Z算出它经由Y的路径费用大于50为止。此时，Z最终确定到X的最短路径费用是直接到达X的费用50，而Y也得到了最短路径是经Z到X的费用51。



**无穷计数问题**： 链路费用**增加**时，路由选择形成环路，该选择过程会不断迭代直到判断开销过大不符合条件才会跳出

* 解决方案： 毒性逆转



**毒性逆转**： 如果z通过y路由选择到目的地x，则z将通告y：它（z） 到x的距离是无穷大的 。 只要z经y路由选择到x， z就持续地向y讲述这个谎言。y将相信z没有到x的路径，最终y将永远不会试图经由z路由选择到x。

* 毒性逆转并没有解决一般的无穷计数问题，当网络规模增大，涉及到了 3 个及以上的更多节点的环路，毒性逆转将不能探测到故障
* （片面的）解决方案：参加RIP

## 层次路由选择

在互联网等大型网络中，一般把路由器组织为**自治系统**（  Autonomous System, AS  ）

![img](https://img2020.cnblogs.com/blog/1774310/202006/1774310-20200603002359144-1106335193.png)



* 将路由器组织成AS的理由：

  * 互联网上路由器规模庞大，路由选择信息的计算开销大，因此需要对路由器进行分组，降低计算复杂性
  * 许多组织都希望管理自治

  

* 同一AS内，运行相同的**AS内部路由选择协议**（ RIP, OSPF ）； AS之间， 运行相同的**AS间路由选择协议**( BGP )



* 网关路由器（  gateway router ）：在AS内的路由器，负责向在本AS之外的目的地转发分组





# 因特网中的路由选择

## 自治系统内的路由选择协议

也称为**内部网关协议**（ interior gateway protocol ）

### RIP

就是AS内的DV算法，只不过定义了最大跳数（默认16）来解决无穷计数问题，这个方案太简陋了，因为还是要绕圈子， 而且这种定义跳数上限的行为，导致网络中不能存在距离大于16的节点，这导致RIP只能用于小型网络



RIP使用UDP进行传送

### OSPF

开放最短路径优先（ Open Shortest Path First, OSPF）：使用洪泛链路状态信息和Dijkstra最低开销路径算法。，每台路由器知道整个自治系统的完整拓扑图。

* 当且仅当链路状态发生变化时，向本AS中所有路由器发送信息（洪泛）
  * RIP仅和相邻节点交换信息
  * RIP是周期性交换信息，不管链路状态有没有变化
* 发送的信息就是与本路由器相邻的所有路由器的链路状态，但这只是路由器所知道的部分信息



通过交换信息，所有路由器最终都能建立一个链路状态数据库，事实上就是全网（整个AS）的拓扑图，**每个路由器都知道全网的拓扑结构**

* RIP的路由器仅知道下一跳距离和下一跳路由器



OSPF采用IP数据报进行传送， 相比UDP，报文更简短



OSPF的优点如下：

- 安全：OSPF路由器之间的交换可以进行认证，只有受信任的路由器才能参与AS内的OSPF协议，从而防止恶意入侵者；

- 多条相同路径的开销：当到达某目的地的多条路径具有相同的开销时，OSPF允许使用多条路径；

- 对单播与多播路由选择的综合支持：多播OSPF（MOSPF）提供对OSPF的简单扩展，以便提供多播路由选择；

- 支持<u>在单个AS中的层次结构</u>：一个OSPF自治系统能够将AS进一步划分为一个个区域，每个区域都允许自己的OSPF链路状态路由选择算法

  * 面向区域，比面向AS的粒度更细

  * 又比面向主机粒度更粗，在洪泛时可以减少链路负载

    

    



## 自治系统间的路由选择

### BGP

**边界网关协议**BGP, 作用顾名思义。

* BGP并非要寻找最短路径路由，而是比较好的路由。因为要考虑AS自身的策略（比如，中国这个AS不允许其报文经由外国再转发到本地，哪怕这条路由费用比较奥低）



BGP是面向AS的，将AS视为节点



# 广播和多播路由选择

## 广播

最简单的实现方式是“N次单播”，缺点是需要发送方知道所有接收方的信息，这需要额外的协议来保证

* N次单播会在到第一跳的链路上发送N个副本，效率低下（时间为N）且造成巨大的链路负载，但这可以通过转而让后续节点来生成和转发副本来解决。 第一跳仅需要发一份副本



### 无控制洪泛

洪泛（flooding）: 源节点向它的所有邻居发送分组副本，当某邻居接收了一个广播分组时，它复制该分组并向它的所有邻居（除了从其接收该分组的那个邻居）转发。 

* 如果图有环，该方法会导致广播分组死循环

### 受控洪泛

原理：如果节点已经接收并且洪泛了某分组的较早副本，它就不应该继续洪泛该分组

#### 序号控制洪泛

序号控制洪泛： 每个广播分组带有一个广播序号和源节点的地址。节点维护一个接收过的广播分组的广播序号列表。  节点只会复制并转发列表中没有对应序号的分组



#### 反向路径转发

反向路径转发（ Reverse Path Forwarding, RPF ）: 当一台路由器接收到具有给定源地址的广播分组时，仅当**该分组到达的链路正好位于它自己的返回其源的最短单播路径上**，它才向其所有出链路传输报文；否则，路由器只是丢弃入分组而不向任何它的出链路转发分组

![image-20220219232512287](/home/lyk/snap/typora/49/.config/Typora/typora-user-images/image-20220219232512287.png)

如图，假设粗线是源R1到其它接收方的最低费用路径：

1. A先广播一个源为R1的分组到节点R4, R2
2. R4将向R2, R5转发它从节点R1接收到的源为R1的分组（因为R1位于R4自己到R1的最低费用路径上）， R4将忽略从其它任何节点接收的源为R1的分组
3. 考虑R2, R2将从R1和R4接收源为R1的分组， 而R4不在R2自己到R1的最短路径上， 因此R2将忽略来自R4的任何源为R1的分组

### 生成树广播

首先对网络构造出一个最小生成树

实现方法：

* 定义一个根节点
* 所有其它节点对根节点单播，直到到达根节点或根节点的生成树内的任意节点
* 整个单播路径上的所有节点就被加入进生成树

## 多播

多播数据报采用**间接地址**来编址， 用来表示一组接收方， 寻址到该组的分组被交付给所有与该组相关联的多播接收方

* 间接地址是**D类地址**
* 多播组：与多播地址相关联的一组接收方
* 显然多播地址**只能用于目的地址，不能用于源地址**
* 对多播数据报不会产生ICMP差错报文， 因此ping一个多播地址将无法收到响应



多播的两个组件：

* IGMP：将主机加入多播组
* 多播路由选择协议：负责多播数据报的路由选择

### IGMP

* 与ICMP类似，封装在IP数据报中

* IP协议号为2

* 三种报文类型：

  * `menbership_query`: 由一台路由器向所有与主机相连的接口发送一个`menbership_query`报文，以确定该接口上主机已加入的所有多播组集合
    * 路由器**周期性地发送**`menbership_query`

  * `menbership_report`: 主机用一个`menbership_report`报文来响应`menbership_report`。 当一个应用程序首次加入一个多播组时，主机会之动向路由器发送`menbership_report`

  * `leave_group`: 表明主机离开该多播组，该报文是**可选的**， 因为IGMP是软状态协议。 通过周期性地发送`menbership_query`，接收`menbership_report`来更新状态（指某主机加入了多播组）。 如果长时间没有收到`menbership_report`，那么该状态通过超时事件被删除

* **软状态协议**， 通过某个端系统发送的周期性报文来更新状态。 状态能够在一次崩溃中丢失，接着自动地由后继的更新报文所恢复

### 多播路由选择协议

生成树算法，得到一棵包含所有多播组节点（即多播组对应的路由器）的树。 

注意到，该树可能会包含一些非多播组节点，它们因此也会承载多播流量

# VPN

机构可以为内部的主机自行分配IP地址。RFC1918指定了一些专用地址，只能用于内部网络：

* 10.0.0.0——10.255.255.255
* 172.16.0.0——172.31.255.255
* 192.168.0.0——192.168.255.255

**在互联网中的所有路由器，对目的地址是专用地址的数据报一律不进行转发**



专用网PN：采用专用地址的网络

虚拟专用网VPN（  Virtual Private Network ）:  用利用互联网来作为本机构各专用网之间的通信载体。。如果专用网的通信必须经过互联网，但又有保密的要求，那么所有通过互联网传送的数据都必须加密

* 尽管可能要经过互联网，但还是用于机构内部的通信，因此称为专用网
* 显然，一个机构的不同专用网要在公网上通信，每个专用网之间需要有至少一个代理路由器，具有公网IP
* 可以认为，VPN和PN的区别就是有公网IP
* VPN采用**隧道**技术，组织A内的主机可以采用专用地址与主机B通信，主机B可能在本专用网内，可能在另一个专用网，后一种情况下无非是将A的数据报发给本专用网的代理服务器为其做转发，整个过程对通信的双方透明明



# NAT

网络地址转换NAT（Network Address Transition）：将专用地址映射为公用地址， 用于专用网内的主机和互联网上的主机通信

* 运行NAT的路由器称为NAT代理，显然，如果NAT代理具有n个公网IP，则最多允许n个内网主机联网。
* 由于一个公网IP可能会映射不同的内网主机， 外部主机将无法通过NAT代理与内网通信。因此，专用网内部的主机无法当服务器用



NAPT：同时做IP映射和端口映射， 此时内网主机在代理时可通过端口来区分，哪怕它们映射到一个公网IP

* NAPT技术使得内网主机能接受外网的请求了

# MPLS

传统的IP网络中， 路由器对分组在转发表中进行最长前缀匹配， 找到下一跳的IP地址，这个过程需要软件计算路由表，速度太慢



转发等价类FEC（  Forwarding Equivalence Class ）:  路由器按照同样方式对待的IP数据报的集合（ 比如，具有相同的源和目的地址 ）



多协议标记交换MPLS（  MultiProtocol Label Switching ）: 给属于同一FEC的IP数据报打上相同的标记，路由器 **仅仅根据转发表**来对打上标记的数据报进行转发，

* 这里的“路由器”只用到了转发表，没用到路由表，相当于交换机，即整个转发由硬件实现
* 硬件意味着开销小，且需要人为控制，这也称为**流量工程**



## MPLS首部的位置

由于IPv4 首部没有多余的位置存放MPLS标记，MPLS首部实际上位于第二层和第三层之间：

![image-20220220235545288](/home/lyk/snap/typora/49/.config/Typora/typora-user-images/image-20220220235545288.png)

“打标记” 就是在帧首部和IP数据报首部之间插入一个4字节的MPLS首部，具体的标记值是一个整数，位于首部字段中





.
