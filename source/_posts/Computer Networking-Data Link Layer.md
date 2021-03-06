---
title: Data Link Layer
tags: Computer Networking
categories: Computer Science
date: 2021-06-29 11:25:11
---

Outline:
* 使用点对点信道的数据链路层
* 点对点协议PPP
* 使用广播信道的数据链路层
* 扩展的以太网
* 高速以太网

<!--more-->

数据链路层使用的信道主要有两种类型：

1. 点对点信道
2. 广播信道： 一对多， 需要共享信道协议来协调数据发送

本章我们研究的是在同一个局域网中， 分组怎样从一台主机传送到另一台主机， 但并不经过路由器转发。 从整个互联网角度看， 局域网仍属于数据链路层的范围。

# 使用点对点信道的数据链路层

## 数据链路和帧

* `链路`: 从一个结点到**相邻结点**的物理线路(有线或无线), 而中间没有其他的交换结点. 链路只是一条路径的组成部分
* `数据链路`: 链路 + 必要的通信协议, 现在常用方法是用**网络适配器**(既有硬件也有软件)来实现这些协议
* 帧:  网络层协议的数据单元是`IP数据报(或简称数据报, 分组 或 包)`. 点对点信道的数据链路层在进行通信时的主要步骤如下:
  1. 结点A数据链路层把网络层交下来的`packet`添加首部和尾部封装成帧
  2. 结点A把封装好的帧发送给结点B的数据链路层
  3. 若结点B的数据链路层收到的帧无差错, 则从收到的帧中提取出`packet`交给上层的网络层;  否则丢弃这个帧

## 三个基本问题

### 封装成帧

* 分组交换: 所有在互联网上传送的数据都以`IP数据报(packet)` 为传送单位. `packet`到数据链路层就成为帧的数据部分, 加上首部和尾部就成为完整的帧
* 首部和尾部的一个重要作用是**帧定界**, 此外, 首部和尾部还包含许多必要的控制信息
* 每一种链路层协议都规定了**所能传输的帧的数据部分长度上限 --- 最大传送单元MTU( Maximum Transfer Unit )**

### **透明传输**

* 字节填充

### 差错检测

* CRC

# 点对点协议PPP

* `Point-to-Point Protocol`， 是用户计算机和`ISP`通信时所使用的数据链路层协议

## PPP协议应满足的需求

1. 简单
2. 封装成帧.  
   * PPP协议必须规定特殊的字符作为`帧定界符`
3. 透明性
4. 多种网络协议
   * PPP必须能够**在同一条物理链路上同时支持多种网络层协议**的运行
5. 多种类型链路
   * PPP必须能在多种类型的链路上运行. 例如串行和并行, 同步和异步, 高速和低速, 电和光
6. 差错检测( error detection )
   * 立即丢弃有差错的帧
7. 检测连接状态
   * 必须具有一种机制能够及时自动检测链路是否处于正常工作状态
8. 最大传送单元
   * 必须对每一种类型的点对点链路设置**最大传送单元MTU**的标准默认值. 这是为了促进各种书籍线之间的互操作性. 如果高层协议发送的分组过长并超过MTU的数值, PPP就要丢弃这样的帧. MTU是数据链路层的帧可以载荷的**数据部分**的最大长度, 而**不是帧的总长度**
9. 网络层地址协商
10. 数据压缩协商

# 使用广播信道的数据链路层

## 局域网的数据链路层

* 局域网最主要的特点: **网络为一个单位所拥有, 且地理范围和站点数目均有限**
* 局域网的优点:
  1. 具有广播功能.  从一个站点可很方便地访问全网. 局域网上的主机可共享连接在局域网上的各种硬件和软件资源
  2. 便于习用的扩展和逐渐演变, 各设备的位置可灵活调整和改变
  3. 提高了系统的可靠性( reliability ) ,  可用性( availability ) 和生存性( survivability )
* 局域网的分类( 按拓扑 ):
  * 星型网
  * 总线网
  * 环形网
* **共享信道**要考虑的一个问题是如何使众多用户能合理且方便地共享媒体资源, 这在技术上有两种方法:
  1. **静态划分信道** . 如第二张的频分复用, 时分复用, 波分服用等. 用户只要分配到了信道就不会与其它用户发生冲突. 但这种方式代价较高, 不适合局域网
  2. **动态媒体接入控制**, 又称为**多点接入( multiple access )** , 分两类
     * **随机接入**: 用户可以随机地发送信息. 但如果两个或更多的用户在同一时刻发送信息, 那么在共享媒体上就要产生**碰撞**(即发生了**冲突**), 因此必须有解决碰撞的协议. 以太网属于随机接入
     * **受控接入** 用户不能随机地发送消息而必须接受一定的控制

### 适配器的作用

* 适配器和局域网之间的通信通过`电缆`或者`双绞线`以`串行`传输方式进行
* 适配器和计算机之间的通信通过计算机主板上的`IO总线`以`并行`传输方式进行
* 适配器的一个重要功能是进行数据串行传输和并行传输的转换
* 计算机的`硬件地址`就在适配器的`ROM`中, 而计算机的软件地址---`IP地址`, 则在计算机的存储器中
* 适配器在接受和发送各种帧时, 不使用计算机的CPU. 当适配器收到有差错的帧时, 就把这个帧<u>直接丢弃而不必通知计算机</u>. 当收到正确的帧时, 它就使用`中断`来通知计算机, 并交付协议栈中的网络层.
* 当计算机要发送`IP数据报`时, 就由协议栈把`IP数据报`向下交给适配器, 组装成`帧`后发送到`局域网`

### CSMA/CD协议

* `Carrier Sense Multiple Access with Collision Detection，载波侦听多路访问/冲突检测协议) `
* 早期以太网是`总线型`的. 属于`广播通信`. 为了在总线上实现<u>一对一通信</u>, 可以使每台计算机的`适配器`拥有一个和其他适配器不同的地址, 当发送数据帧时, 在帧的首部写明接收站的地址. 
* **仅当数据帧中的目的地址与适配器ROM中存放的硬件地址一致时**, 该适配器才能接收这个数据帧, 否则就丢弃. 这样, 就在总线上实现了</u>一对一通信</u>
* 以太网采取以下两种措施
  * **无连接**
    *  不必建立链接就可以直接发送数据
    * 适配器对发送的数据帧**不进行编号, 也不要求对方发回确认**
    * 尽最大努力的交付, 即不可靠的交付. 
* 总线特点: **在同一时间只能允许一台计算机发送数据**, 解决方法:
  * CSMA/CD协议
  * 曼彻斯特编码
* CSMA/CD的特点
  * 多点接入
  * 载波监听
    * 检测信道( 发送前和发送中都要不停检测信道 )
  * 碰撞检测

### 以太网的MAC层

* 局域网中, 硬件地址又称为`MAC地址`
* 48位的全球地址, 就是固化在适配器的ROM中的地址
* 发往本站的帧有三种:
  1. 单播( unicast )帧
  2. 广播( broadcast )帧( 一对全体 ), 即发送给本局域网上所有站点的帧( 全1地址 )
  3. 多播(multicast )帧( 一对多 ): 即发送给本局域网上部分站点的帧
* 所有的适配器都能识别前两种帧,有的能通过编程方式识别多播地址

# 扩展的以太网

## 在物理层扩展以太网

* 用集线器
* 缺点：
  * 多个系的以太网通过集线器互连起来后， 多个**碰撞域**会合并成一个
    * 碰撞域： 在任意时刻， 每个碰撞域中只能有一个站在发送数据
  * 如果不同的系使用不同的以太网技术（如数据率不同）， 那么就不可能用集线器把它们互连起来。 集线器基本是个多借口的转发器， 它不能把帧进行缓存

## 在数据链路层扩展以太网

扩展以太网一般在数据链路层进行， 用交换机

### 以太网交换机的特点

* 交换机就是**多接口的网桥**
* 每个接口都直接与单台主机或另一个以太网交换机相连, 且工作在`全双工方式`
* 具有并行性, 能同时连通多对接口, 且多对主机能同时通信, 相互通信的主机都是**独占传输媒体, 无碰撞地传输数据**
* 是一种即插即用设备, 其内部的`帧交换表(地址表)`是通过**自学习算法**建立的
* 交换机能隔离`冲突域`,但不能隔离广播域
  * 交换机使用硬件转发, 比使用软件转发的网桥快很多
* 交换机一般具有多种速率的接口, 因此不同数据率的两给局域网可以互连
* 部分交换机实现`直通(  cut through )`的交换方式. 而网桥只能存储转发

### 以太网交换机的自学习功能

1. A向B发送一帧, 从接口1进入交换机. 交换机收到帧后, 先查找交换表, 没有找到应从哪个接口转发这个帧( 在MAC地址这一列中, 没有找到目的地址为B的项目 ). 接着, 交换机吧这个帧的源地址和接口1写入交换表中, 并**向除接口1外的所有接口广播这个帧**
2. C和D将丢弃这个帧, 因为目的地址不对. B会收下这个帧. 这称为**过滤**
3. 假定接下来B通过接口3向A发送一帧. 交换机查找交换表, 发现交换表中的MAC地址有A, 就应当把收到的帧从接口1转发出去. 并向表中写入源地址B和接口3

* 交换表中每个项目都设有一定的有效时间
* 如果存在冗余链路, 则会导致帧在某个环路中无限兜圈子, 因此IEEE制定了**生成树协议STP( Spanning Tree Protocol )**, 其要点是不改变网络的实际拓扑, 而在逻辑上切断某些链路, 似的从一台主机到所有其他主机的路径是五环路的树状结构, 从而消除了兜圈子现象.

### 从总线到星型以太网

* 目前, 采用以太网**交换机**的**星型拓扑**成为**首选拓扑**
* 总线以太网使用CSMA/DA协议, 以半双工方式工作. 但以太网交换机不使用共享总线, 没有碰撞问题, 因此不使用CSMA/DA协议, 而是以全双工方式工作
* 因为**帧**结构没有改变, 所以现在的局域网还叫以太网

### **虚拟局域网**

* 是由一些局域网网段构成的与物理位置无关的逻辑组, 而这些网段有某些共同的需求. ,每一个VLAN帧都有一个明确的标识符( VLAN tag, 4字节 ), 指明发送方属于哪一个VLAN

# 高速以太网



