---
title: Bus
tags: Computer Architecture
categories: Computer Science
mathjax: true
---

# Intro

![Bus Interconnection Scheme](/Users/lyk/Library/Application Support/typora-user-images/image-20230223135831399.png)

A bus(总线) is a communication pathway connecting two or more devices. 

* 总线可以连接多个设备, 在总线上传输的信号可以被所有设备接收到.
* 一条总线在同一时间只能对传输一个设备的信号.
* 每条总线都由若干根导线组成. 导线有无电流, 就代表传输的信号是1或0. 因此一根总线所含有的导线数量, 就称作该总线的*width*(宽度). 典型的data bus和address bus的宽度有32-bit和64-bit.



* **system bus**.: A bus that connects major computer components (processor, memory, I/O)
* 系统总线按功能, 可以分为三种:
  1. **data bus**: 由若干根数据线构成
  2. **address bus**: 由若干根数据线构成
  3. **control bus**: used to control the access to and the use of the data and address lines



先回顾几个总线技术：

- 串行总线：只需要一条传输线，成本低廉，广泛应用于长距离传输；应用于计算机内部时，可以节省布线空间。
- 并行总线：总线的逻辑时序比较简单，电路实现起来比较容易。占用更多的布线空间；工作频率较高时，并行的信号线之间会产生严重干扰。
- 总线复用：是指一种信号线在不同的时间传输不同的信息。可以使用较少的线传输更多的信息，从而节省了空间和成本。

### 1.1 内部总线

在 CPU 内部，寄存器之间和算术逻辑部件 ALU 与控制部件之间传输数据所用的总线称为片内总线（又称内部总线，即芯片内部的总线）。它是外设与处理器之间的总线，用于芯片一级的互连。

### 1.2 系统总线（内总线、板级总线）

又称**内总线**或板级总线，它将 CPU、主存、I/O 接口之间相互连接起来。系统总线的结构可分为三类（除这三类外还有四总线结构）：

#### 1.2.1 单总线结构

将 CPU、主存、I/O 接口挂在同一组总线上，注意是同一组，一组里有三种总线——数据总线、地址总线、控制总线。

- 数据总线：双向传输，用来传输各部件之间的数据信息，总线位宽与机器字长、存储字长有关
- 地址总线：单向传输，用来指出数据总线上的数据所在的主存单元或 I/O 端口地址，总线位宽与主存地址空间大小有关
- 控制总线：传输控制信号，包括 CPU 送出的控制命令和主存返回 CPU 的反馈信号

#### 1.2.2 双总线结构

一条是主存总线，另一条是 I/O 总线，而通道作为两条总线的传输中介。这种结构支持突发传送。

- 主存总线：这里面实际是三种总线——数据总线、地址总线、控制总线。
- I/O 总线：用于连接中低速的 I/O 设备，通过 I/O 接口与系统总线相连，目的是将低速设备与高速设备分离，如 USB、PCI 总线。
- I/O 通道：具有特殊功能的处理器，能对 I/O 设备进行统一管理，减轻了设备控制器的负担。通道程序统一放在主存中。

#### 1.2.3 三总线结构

主存总线（这里面实际是三种总线——数据总线、地址总线、控制总线）、I/O 总线、DMA 总线。

- 主存总线：这里面实际是三种总线——数据总线、地址总线、控制总线。
- I/O 总线：用于连接中低速的 I/O 设备，通过 I/O 接口与系统总线相连，目的是将低速设备与高速设备分离，如 USB、PCI 总线。
- DMA 总线：直接内存访问总线。

### 1.3 外部总线（外总线、通信总线）

计算机和外部设备（如远程通信设备、测试设备）之间的总线称为外部总线。

## 2 总线事务和定时

总线事务的四个阶段：

- 申请分配阶段
- 寻址阶段
- 传输阶段
- 结束阶段

### 2.1 同步定时方式

总线控制器采用一个**统一的时钟信号**来协调发送和接收双方的传送定时关系。

若干个时钟产生相等的时间间隔，每个间隔构成一个总线周期。在一个总线周期中，发送方和接收方可进行一次数据传送。

因为采用统一的时钟，每个部件或设备发送或接收信息都在固定的总线传送周期中，一个总线的传送周期结束，下一个总线传送周期开始。

- 优点：传送速度快，具有较高的传输速率；总线控制逻辑简单。
- 缺点：主从设备属于强制性同步；不能及时进行数据通信的有效性检验，可靠性较差。
- 特点：同步通信适用于**总线长度较短（不容易发生信号跳变）及总线所接部件的存取时间比较接近的系统**。



确定每个总线事务的开始和结束时间 

* 总线事务: **地址** + 数据 + ... + 数据

  一次总线事务内可能传多次数据
  
  每次总线事务开始时, 都要先传地址



### Pros & Cons

* 优点: 更容易实现和测试
* 缺点:
  * 所有设备共享同一个时钟
  * 总线长度受到时钟偏差的限制



### 2.2 异步定时方式

在异步定时方式中，没有统一的时钟，也没有固定的时间间隔，完全依靠传送双方相互制约的“握手”信号来实现定时控制。

- 优点：总线周期长度可变，能保证**两个工作速度相差很大的部件或设备**之间可靠地进行信息交换，自动适应时间的配合。
- 缺点：比同步控制方式稍复杂一些，速度比同步定时方式慢。

四种方式：

- **不互锁方式**：主设备发出“请求”信号后，不必等到接到从设备的“回答”信号，而是经过一段时间，便撤销“请求”信号。而从设备在接到“请求”信号后，发出“回答”信号，并经过一段时间，自动撤销“回答”信号。双方不存在互锁关系。
- **半互锁方式**：主设备发出“请求”信号后，必须待接到从设备的“回答”信号后，才撤销“请求”信号，有互锁的关系。而从设备在接到“请求”信号后，发出“回答”信号，但不必等待获知主设备的“请求”信号已经撤销，而是隔一段时间后自动撤销“回答”信号，不存在互锁关系。
- **全互锁方式**：主设备发出“请求”信号后，必须待从设备“回答”后，才撤销“请求”信号；从设备发出“回答”信号，必须待获知主设备“请求”信号已撤销后，再撤销其“回答”信号。双方存在互锁关系。

## 7次握手

注意到, 这里采用复用的总线. Data线先用来传地址, 再用来传数据

![image-20230224195133552](/Users/lyk/Library/Application Support/typora-user-images/image-20230224195133552.png)

1. CPU把地址放到Data bus( 也就是让Data bus呈现相应的电平, 比如地址空间和Data bus宽度都是32-bit, 则这一步就是让Data bus上呈现出一个32-bit的电平), 并设置`ReadReq line`, 即告诉内存, 从Data bus线读取地址
2. 内存从Data bus线读取地址结束, 设置`Ack line`, 告诉CPU, 自己已经读取好了
3. CPU看到`Ack line`为1, 则释放Data bus( 即让Data bus上不再有代表地址的电平)和`ReadReq line`(即不再通知内存从Data bus线读取地址)
4. 这一步主要是一些控制信息的交换. 比如将某根表示“Data bus的作用是地址总线还是数据总线”的控制线的电平反转. 并且还会释放`Ack line`
5. 内存把数据放到Data bus(和第1步类似), 并设置`DataRdy line`, 即告诉CPU, 从Data bus线读取数据
6. CPU从Data bus线读取数据结束, 设置`Ack line`, 告诉内存, 自己已经读取好了
7. 内存看到`Ack line`为1, 则释放Data bus和`ReadReq line`



* 可以看到, 步骤1~3和步骤5~7是类似的

* 步骤1~3是传输地址, 步骤5~7是传输数据. 但是, 每次进行5~7之前必须经历步骤4, 因为步骤4会释放`Ack line`

  * 因此, 一步总线一次完整的总线事务的握手顺序为:

    1,2,3,4,5,6,7,4,5,6,7, ....

    即一次传地址 + N次传数据

  * 不可以1,2,3, 4, 5,6,7,(5,6,7),(5,6,7), .... 即5,6,7前必须有4.

  * 想象一下5,6,7前没有4的情况: 1,2,3之后, `Ack line = 1`, 而缺少了步骤4的释放 `Ack line`后,  `Ack line`在5,6,7也始终为1. 然而 `Ack line`的作用是: CPU通知内存, 自己已经读取数据完毕了. 因此内存一看到`Ack line = 1`, 就会直接释放Data bus和`ReadReq line`, 即直接执行步骤7.

## Pros  & Cons

* 优点: 可以灵活地协调速度不同的设备

* 缺点:
  * 接口逻辑复杂
  * 对噪声敏感

# 总线类型

* 专用总线(高效传输/规模成本高)

* 复用总线(节省空间和成本/复杂的机制)

# Arbitration

总线可被多个设备监听但每次只能由其中一个发出信息 

1. Centralized scheme(集中式): a single hardware device, referred to as a bus controller or arbiter, is responsible for allocating time on the bus(一个简单的作为**总线控制器**或者**仲裁器**的硬件设备，它负责为总线各个设备分配使用时间)
   + Daisy chain(链式)
   + Query by a counter(计数器查询法)
   + Independently request(独自请求)
2. Distributed scheme(分布式): each module contains access control logic and the modules act together to share the bus(每一个部分包含权限控制逻辑并且每个模块同时相应去共享总线)
   + Self selection(自主选择)
   + Collision detection(冲突探测)

# 集中式仲裁方式

## Daisy Chain

菊花链式

1. All the devices are connected serially, and grant is delivered from the highest priority device to the lowest priority device(所有的设备会被线性的连接，并且**许可信号被从高优先级的设备传递到低优先级的设备上去**)
2. If one device receives the grant and has bus request, the device sets the bus busy and the grant is not further delivered(如果一个设备有许可并且有总线请求，那么这个设备会设置总线为忙并且不再发送许可信号)

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt13/4.png)

3. 最左边的是仲裁器，黄色的线表示总线忙，Grant是许可线，来确定具体是哪一个设备可以使用。

### 优点

1. Simple to determine the priority(很简单来保证优先级)
2. Flexible to add devices(添加设备容易)

###  缺点

1. Cannot ensure the fairness(**不能保证公平**)
2. Sensitive to circuit fault(对于设备内部的总线**损坏十分敏感**，如果高优先级损坏，低优先级完全无法使用)。
3. Limit the bus speed(限制总线速度，需要遍历，线性)

## Query By A Counter

计数器查询法

1. Remove bus grant line, and use devices ID lines(移除了许可总线，使用**装置ID线**)
2. If the bus is not busy, the bus arbiter sends the count through device ID lines(**如果总线不忙，则总线仲裁器通过装置ID线发送计数**)
3. If one device requests the bus whose ID equals to the current count, the arbiters stops counting and the device sets the bus busy(如果一个设备需要总线，并且ID和当前的计数相同，则仲裁器终止计数并且设备设置总线为忙。)
4. **通过不同报数规则保证公平性**等。

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt13/5.png)

1. 图中每一个线不是一根线，而是一组线，有N位，则至少有log<sub>2</sub>N 向上取整个。
2. 报号是不会故意等很久的，按照匀速率往下报号。
   + 会稍微等一下，但是不会等很久
3. 报号的方式是可以控制的

### 优点

1. Flexible to determine the device priorities by using different initial counts(通过不同初始化的技术来决定设备的优先级)
   + Fixed priority: 0(初始化优先级:0)
   + Fair priority: the ID following the device used the bus(公平优先级:ID对应的设备使用总线)
2. Not sensitive to circuit fault(对于设备电路损坏不敏感)
3. 可以很灵活，可以平衡公平和灵活。

### 缺点

1. Add the device ID lines(添加了设备ID线)
2. Require to decode and compare device ID signal(需要解码和比较ID信号)
3. 响应速度比较慢。

## Independently Request

单独请求

1. Each device has its bus request line and bus grant line(**每一个设备都有自己的请求线和总线许可线**)
2. When one device request the bus, it sends the request signal to bus arbiter through the bus request line(什么时候一个设备需要总线，它就通过总线请求线来发送信号给总线仲裁器)
3. Bus arbiter determines which device can use the bus(总线仲裁决定了哪一个设备可以使用总线)
   + Determination strategy: fixed priority, fair daisy chain, LRU, FIFO, …(很多的策略)

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt13/6.png)

### 好处

1. Fast response(快速)
2. Programming priority(优先级可以调整)

### 缺点

1. Complex control logic(复杂的控制逻辑)
   + 为什么？是仲裁器电路比较复杂。
2. More control lines(更多的控制线)

# 分布式仲裁方式

## Self Selection

自主选择

1. Fixed priority(固定优先级)
2. Each device sends the request on its bus request line(**每一个设备都可以发送请求到他自己的请求总线的线上**)
   + The lowest priority device doesn’t have request line(最低优先级的设备不需要有总线请求线)
3. Each device independently determines whether it is the device with the highest priority(每一个设备都可以独立的决定这个设备是不是最高优先级)

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt13/7.png)

4. 3的优先级最高:因为3的线最少
   + 蓝色线:双向线:需要监听总线忙或者不忙
   + 如果总线不忙:3使用，通过红色告诉012
   + 如果总线不忙、3不用:2使用，通过绿色告诉01
   + 如果总线不忙、23不用:顺序向下

## Collision Detection

冲突检测法

1. When one device wants to use the bus, it checks whether the bus is busy(**当一个设备想要使用总线，它来检测总线是否在忙**)
   + If bus is not busy, the device uses the bus(如果总线空闲，那么设备使用总线)
2. Collision: if two devices found the bus is not busy, they may use the bus at the same time(冲突：如果两个设备都发现总线空闲，他们有可能同时使用总线)
   + In data transfer, the device will listen to the bus and check whether exists a collision(在**数据传输**过程中，设备需要监听总线并且确定是否存在冲突)
   + If a collision happens, all the devices using bus will stop data transfer and request the bus after a random duration(如果发生冲突，所有使用总线的设备将停止数据传输，并在随机时间后请求总线)
3. 抢椅子，如果抢到了，发现总线占用，则进行再次争夺。
4. 不关心谁在用，而只是发送数据上去，监听有无数据扰动，如无则无人使用，正常使用即可，否则放弃总线，随机等待一定时间后再次使用。

# 总线的性能指标

## 性能指标

| 性能指标                         | 描述                                                         |
| -------------------------------- | ------------------------------------------------------------ |
| 总线**传输周期**（**总线周期**） | **一次总线操作所需的时间**（包括申请阶段、寻址阶段、传输阶段和结束阶段），通常由若干个总线时钟周期构成 |
| 总线**时钟周期**                 | 即**机器的时钟周期**                                         |
| 总线**工作频率**                 | 即**总线周期的倒数**，指一秒内传送几次数据                   |
| 总线**时钟频率**                 | 即**机器的时钟频率**                                         |
| **总线宽度**                     | 又称为**总线位宽**，它是总线上同时能够传输的数据位数，通常是指数据总线的根数，如 32 根称为 32 位（bit）总线 |
| **总线带宽**                     | 即总线的**数据传输率**，即单位时间内总线上可传输数据的位数，通常用每秒钟传送信息的字节数来衡量，单位可用**字节/秒（B/s）** 表示 |
| **信号线数**                     | 地址总线、数据总线和控制总线 3 种总线数的总和称为信号线数    |

> 【注】大多数情况下，一个总线周期包含多个总线时钟周期；有的时候，一个总线周期就是一个总线时钟周期；有的时候，一个总线时钟周期可包含多个总线周期。

## 性能指标的相关公式

- **总线带宽 = 总线工作频率 × 总线宽度（bit/s）** = 总线工作频率 × (总线宽度/8)（B/s）
- **总线带宽 = (1/总线周期) × 总线宽度（bit/s）** = (1/总线周期) × (总线宽度/8)（B/s）

> 【注 1】总线带宽是指总线本身所能达到的最高传输速率。在计算实际的**有效数据传输率**时，要用实际传输的数据量除以耗时。
>
> 【注 2】总线带宽的单位中，KB、MB 等均是以 10 为底的单位，切记！！（严格来讲 KB、MB 应写成 kB、mB）

### 3.3 相关例题

【例 1】在 32 位总线系统中，若时钟频率为 500MHz，传送一个 32 位字需要 5 个时钟周期，则该总线系统的数据传送速率为多少？

> 【解法 1】时钟频率为 500MHz，则时钟周期为 1/500MHz = 2us。
>
> 传送一个 32 位字需要 5 个时钟周期，所以需要的总线周期为 10us。
>
> 所以数据传送速率 = 4B/10us = 0.4B/us = 0.4*106B/s = 400MB/s。
>
> 【解法 2】时钟频率为 500MHz，而总线传送一个 32 位字需要 5 个时钟周期，所以总线的工作频率为 500MHz/5 = 100MHz。
>
> 数据传送速率 = 4B*100MHz = 400MB/s。

【例 2】假设某系统总线在一个总线周期中并行传输 4 字节信息，一个总线周期占用 2 个时钟周期，总线时钟频率为 10MHz，则总线带宽为多少？

> 【解法 1】时钟频率为 10MHz，则时钟周期为 1/10MHz = 100us。
>
> 一个总线周期占用 2 个时钟周期，所以需要的总线周期为 200us。
>
> 所以数据传送速率 = 4B/200us = 0.02B/us = 0.02*106B/s = 20MB/s。
>
> 【解法 2】总线时钟频率为 10MHz，而一个总线周期占用 2 个时钟周期，所以总线的工作频率为 10MHz/2 = 5MHz。
>
> 总线带宽 = 4B*5MHz = 20MB/s。
>
> 【注】通过以上两题，可以发现解法二更为便捷。以后我们采用解法二来解题。

【例 3】某同步总线采用数据线和地址线复用方式，其中地址/数据线有 32 根，总线时钟频率为 66MHz，每个时钟周期传送两次数据（上升沿和下降沿各传送一次数据）。

（1）该总线的最大数据传输率（总线带宽）是多少？

（2）若该总线支持突发（猝发）传输方式，传输一个地址占用一个时钟周期，则一次“主存写”总线事务传输 128 位数据所需要的时间至少是多少？

> 【解】（1）总线时钟频率为 66MHz，**每个时钟周期传送两次数据**，所以总线工作频率为 66MHz*2 = 132MHz。
>
> 最大数据传输率 = 132MHz*4B = 528MB/s。
>
> （2）可以将突发（猝发）传输方式视为 DMA 传输，则只需传送一个地址，然后再传输 4 次数据即可。
>
> 因此，按照题意，传输 128 位数据所需要的时钟周期数 = 1 + 4/2 = 3，所需时间是 3 * (1/66MHz) = 45ns。
>
> 【注】我们一般将突发（猝发）传输方式视为 DMA 传输。

【例 4】假定一台计算机采用 3 通道存储器总线，配套的内存条型号为 DDR3-1333，即内存条所接插的存储器总线的工作频率为 1333 MHz、总线宽度为 64 位，则存储器总线的总带宽大约是多少？

> 【解】采用 3 通道存储器总线，总线宽度扩大三倍，即 64*3 = 128 位 = 24B，则总带宽大约是 24B*1333MHz = 32GB/s。

【例 5】在异步串行传输方式下，起始位为 1 位，数据位为 7 位，偶校验位为 1 位，停止位为 1 位，如果波特率为 1200bit/s（即每秒传输 1200 比特），求这时的**有效**数据传输率为多少？

> 【解】一个数据包含 1+7+1+1=10 位，而每秒传输 1200 比特，则每秒可传输 1200/10=120 个数据。
>
> 每个数据中，有效数据位为 7 位，则每秒可传输 7*120 = 840 位有效数据，即**有效**数据传输率 = 840b/s。

【例 6】假定 CPU 通过存储器总线读取数据的过程为：发送地址和读命令需 1 个时钟周期，存储器准备一个数据需 8 个时钟周期，总线上每传送 1 个数据需 1 个时钟周期。若主存和 Cache 之间交换的主存块大小为 64B，存取宽度和总线宽度都为 8B，则 Cache 的一次缺失损失至少为（）个时钟周期？

> 【解】Cache 一次缺失的数据大小为 64B，而存取宽度和总线宽度都为 8B，所以一共需要传送 8 次。
>
> 每次传送都有：发送地址和读命令需 1 个时钟周期，存储器准备一个数据需 8 个时钟周期，总线上每传送 1 个数据需 1 个时钟周期，所以一共花费 10 个时钟周期。
>
> 因此Cache 的一次缺失损失至少为 10*8 = 80 个时钟周期。

【例 7】假定采用多模块交叉存储器组织方式，存储器芯片和总线支持突发传送，CPU 通过存储器总线读取数据的过程为：发送首地址和读命令需 1 个时钟周期，存储器准备第一个数据需 8 个时钟周期，随后每个时钟周期总线上传送 1 个数据，可连续传送 8 个数据（即突发长度 = 8）。若主存和 Cache 之间交换的主存块大小为 64B，存取宽度和总线宽度都为 8B，则 Cache 的一次缺失损失至少为（）个时钟周期？

> 【解】支持突发传送，即 DMA 传输，传输前：发送首地址和读命令需 1 个时钟周期，存储器准备第一个数据需 8 个时钟周期；传送时：后每个时钟周期总线上传送 1 个数据，可连续传送 8 个数据。总时钟周期为 8+8+1 = 17。
>
> Cache 一次缺失的数据大小为 64B，而存取宽度和总线宽度都为 8B，又因为可连续传送 8 个数据（即突发长度 = 8），所以一共需要传送 1 次，因而 Cache 的一次缺失损失至少为 17 个时钟周期。
>
> 

# Questions

2019

![img](file:////Users/lyk/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image001.png)

注意, 这题里面对于相连的总线事务, 内存访问是分开的. 即: 对于4字传输方式, 每次总线事务的准备前4个字的时间都是30个周期. 但





对于16字传输方式, 前1+30c准备好了前四个字, 后面:

* 2C: 传2字数据
* 6C: 准备4字数据

因此, 取6c * 3, 最后一次只要2c, 因为没有数据需要准备了



***

![image-20230226004345966](/Users/lyk/Library/Application Support/typora-user-images/image-20230226004345966.png)

这题的多个相连的总线事务之间, 内存访问不知为啥又是连续的了, 因此第一个总线事务准备前4个Byte的时间是250, 后面的总线事务准备前4个Byte的时间是100
