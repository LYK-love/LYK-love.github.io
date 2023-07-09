---
title: I/O Control
tags:
---



# Interrupts



* 中断不是由执行指令引起的, 而是由外部I\O设备的事件引起的
  * Exception handlers for hardware interrupts are often called *interrupt handlers*.

#### Interrupt handling

![Interrupt handling](/Users/lyk/Library/Application Support/typora-user-images/image-20230223143025498.png)

上图描述了中断处理流程:

1. I/O设备(例如network adapters, disk controllers, and timer chips)通过像cpu的interrupt pin发信号来触发中断. I/O设备还会把exception number(用来标识引起终端的设备)放到system bus
2. 当前指令执行完毕后, CPU发现interrupt pin具有高电平, CPU就从system bus读取exception number, 然后保存当前状态, 调用对应的interrupt handler. 
3. CPU执行interrupt handler. 
4. 当interrupt handler返回后, CPU会恢复处理中断之前的状态, 执行下一条指令( 即中断还未发生前时已经执行完的指令的下一条指令). 最终结果就像中断从未发生那样.



From the point of view of the user program, an interrupt is just that: an interrup- tion of the normal sequence of execution. When the interrupt processing is completed, execution resumes 





1. It suspends execution of the current program being executed and saves its context. This means saving the address of the next instruction to be executed (current contents of the program counter) and any other data relevant to the processor’s current activity.
2. It sets the program counter to the starting address of an *interrupt handler* routine.
3. The processor now proceeds to the fetch cycle and fetches the first instruction in the interrupt handler program, which will service the interrupt. 



# Multiple Interrupts 

Two approaches can be taken to dealing with multiple interrupts. 

## Disabled Interrupt

The first is to disable interrupts while an interrupt is being processed. A **disabled interrupt** simply means that the processor can and will ignore that interrupt request signal. If an interrupt occurs during this time, it generally remains pending and will be checked by the processor after the processor has enabled interrupts. Thus, when a user program is executing and an interrupt occurs, interrupts are disabled immedi- ately. After the interrupt handler routine completes, interrupts are enabled before resuming the user program, and the processor checks to see if additional interrupts have occurred.



![Sequential interrupt processing](data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1070 662"></svg>)



## Drawback

The drawback to the preceding approach is that it does not take into account relative priority or time-critical needs. For example, when input arrives from the communications line, it may need to be absorbed rapidly to make room for more input. If the first batch of input has not been processed before the second batch arrives, data may be lost.









## Interrupt Priorities

A second approach is to define priorities for interrupts and to allow an interrupt of higher priority to cause a lower-priority interrupt handler to be itself interrupted.

![Nested interrupt processing](data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1014 636"></svg>)







A user program begins at *t* = 0. At *t* = 10, a printer interrupt occurs; user information is placed on the system stack and execution continues at the printer **interrupt service routine (ISR)**. While this routine is still executing, at *t* = 15, a communications inter- rupt occurs. Because the communications line has higher priority than the printer, the interrupt is honored. The printer ISR is interrupted, its state is pushed onto the stack, and execution continues at the communications ISR. While this routine is exe- cuting, a disk interrupt occurs (*t* = 20). Because this interrupt is of lower priority, it is simply held, and the communications ISR runs to completion.

When the communications ISR is complete (*t* = 25), the previous proces- sor state is restored, which is the execution of the printer ISR. However, before even a single instruction in that routine can be executed, the processor honors the higher-priority disk interrupt and control transfers to the disk ISR. Only when that routine is complete (*t* = 35) is the printer ISR resumed. When that routine com- pletes (*t* = 40), control finally returns to the user program.

![Example Time Sequence of Multiple Interrupts](data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1140 732"></svg>)





> 

### 中断响应优先级和处理优先级

* 中断响应优先级: 由查询程序或硬件排队线路决定的优先权，反映多**个中断同时请求时**选择哪个响应。 

  * 属于中断硬件给定，无法修改；

* 中断处理优先级: 由各自的**中断屏蔽字**来动态设定，反映本中断与其它中断间的关系。

  * 可以通过屏蔽技术进行修改；
  * 中断屏蔽时, 根本就不会响应中断, 也就是不会放在响应优先队列中

* 当多个中断请求到来时, 将它们按照"中断响应优先级"在中断请求队列中排队. 在程序执行时, 每条指令结束后检查是否开中断, 如果是, 则从检查请求队列中是否有中断, 如果是, 则拿出请求队列中的第一个元素. 然后判断拿出的元素的“中断处理优先级”是否高于正在执行的程序, 如果是, 则转入该中断routine. 

  从该中断返回后, 继续执行原本程序. 但是, **在该程序的一条指令都没有执行以前, 再次查看中断请求队列**, 再次查看其第一个元素的优先级, 如果是, 则....



还有个例子:

> 2
>
> 
>
> Imagine your CPU is in "int3" handler now and at that time "int2" happens and the newly happened "int2" has a lower priority compared with "int3". How would we handle with this situation?
>
> A way is when handling "int3", we are masking out other lower priority interrupters. That is we see the "int2" is signaling to CPU but the CPU would not be interrupted by it. After we finishing handling the "int3", we make a return from "int3" and unmasking the lower priority interrupters.
>
> The place we returned to can be:
>
> 1. Another process(in a preemptive system)
> 2. The process that was interrupted by "int3"(in a non-preemptive system or preemptive system)
> 3. An int handler that is interrupted by "int3"， say int1's handler.
>
> In cases 1 and 2, because we unmasked the lower priority interrupters and "int2" is still signaling the CPU: "hi, there is a something for you to handle immediately", then the CPU would be interrupted again, when it is executing instructions from a process, to handle "int2"
>
> In case 3, if the priority of “int2” is higher than "int1", then the CPU would be interrupted again, when it is executing instructions from "int1"'s handler, to handle "int2".
>
> Otherwise, "int1"'s handler is executed without interrupting (because we are also masking out the interrupters with priority lower then "int1" ) and the CPU would return to a process after handling the “int1” and unmask. At that time "int2" would be handled.



这里有个问题是: 根据Instruction Cycle, 每条指令执行完后才会检查中断. 那么从一个中断handler返回后, 源程序不应该至少先继续执行一条指令, 在该指令执行后, 再检查中断, 再转入新的中断routine吗? 为什么可以“在该程序的一条指令都没有执行以前, 再次查看中断请求队列”?



* 中断屏蔽字的规则：
  - 用“1”表示屏蔽，“0”表示可以正常中断请求。
  - 每个中断源对应一个屏蔽字。每个屏蔽字中至少有一个“1”（因为**至少要能屏蔽自身的中断**）。
  - 屏蔽字中“1”越多，优先级越高。

- 
- 

例子:假设中断系统中有4个中断源，其响应优先级为L1>L2>L3>L4，处理优先级为L1>L4>L3>L2。如果在主程序执行时同时发生L1、L3和L4中断，并且在 处理L3中断的过程中发生L2中断，写出掩码字和所有中断服务程序的过程。

![image-20230223163240151](data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1082 800"></svg>)

| #    | L1   | L2   | L3   | L4   |
| ---- | ---- | ---- | ---- | ---- |
| L1   | 1    |      |      |      |
| L2   | 1    |      |      |      |
| L3   |      |      |      |      |
| L4   |      |      |      |      |





#### 2.3.3 相关例题

【例】设某机器有四个中断源 A、B、C、D，其硬件排队优先次序为 A>B>C>D，现要求将中断处理次序改为 D>A>C>B，写出这四个中断源的屏蔽字。（注意题目还会考察程序运行轨迹）

【解】（1）A 的屏蔽字：因为 D>A，所以 D=0；因为需要屏蔽自身，所以 A=1。因此屏蔽字为 1110。

| A    | B    | C    | D    |
| ---- | ---- | ---- | ---- |
| 1    | 1    | 1    | 0    |

（2）B 的屏蔽字：因为 D，A，C>B，所以 D=0，A=0，C=0；因为需要屏蔽自身，所以 A=1。因此屏蔽字为 0100。

| A    | B    | C    | D    |
| ---- | ---- | ---- | ---- |
| 0    | 1    | 0    | 0    |

（3）C 的屏蔽字：因为 D，A>C，所以 D=0，A=0；因为需要屏蔽自身，所以 C=1。因此屏蔽字为 0110。

| A    | B    | C    | D    |
| ---- | ---- | ---- | ---- |
| 0    | 1    | 1    | 0    |

（4）D 的屏蔽字：因为 D 是最高级别的，所以其余全为 0；因为需要屏蔽自身，所以 D=1。因此屏蔽字为 0001。

| A    | B    | C    | D    |
| ---- | ---- | ---- | ---- |
| 0    | 0    | 0    | 1    |

***



![image-20230226012744916](/Users/lyk/Library/Application Support/typora-user-images/image-20230226012744916.png)

![image-20230226012752474](/Users/lyk/Library/Application Support/typora-user-images/image-20230226012752474.png)

中断3在处理中断2,1,5时被屏蔽了, 根本没有进入中断响应队列, 即根本没有被响应



# I/O操作技术

## 编程式I/O

* 中断：无中断，需要100%占用CPU
* I/O命令：控制命令、测试命令、读命令、写命令
* I/O指令：编址方式：存储器映射式I/O、分离式I/O

## 中断驱动式**I/O**

* 中断：有中断

* 中断时保存与恢复：PC、PSW、通用寄存器、掩码字
* 响应优先级和处理优先级：掩码字矩阵

* 设备识别方式：

  * 轮询：轮询次序决定优先级

    [菊花链](#菊花链)：模块连接顺序决定优先级

    独立请求：中断控制器决定优先级

    多条中断线：和前面三者结合，仅挑选优先级最高的中断线



# DMA 方式

无需经过处理器即可直接访问内存

### 3.1 DMA 传送过程

**（1）预处理**：

- DMA 控制器（DMAC）接受外设发出的 DMA 请求（外设传送一个字的请求），并向 CPU 发出总线请求。
- CPU 响应此总线请求，发出总线响应信号，DMA 控制器将接管 CPU 的地址总线、数据总线和控制总线，CPU 的主存控制信号被禁止使用。

**（2）数据传送**：

- CPU 向 DMA 控制器指明传送数据的主存单元地址及长度，以及数据在主存和外设间的传送方向。
- DMA 控制器发出读写等控制信号，执行数据传送操作。每传送一个数据，自动修改主存地址计数和传送长度计数。

**（3）后处理**：

- DMA 控制器向 CPU 报告 DMA 操作的结束，执行中断服务程序。恢复 CPU 的一切权利。

### 3.2 DMA 传送方式

主存和 DMA 控制器之间有一条数据通路，不通过 CPU。但当 I/O 设备和 CPU
同时访问主存时，可能发生冲突，为了有效地使用主存，DMA 控制器与 CPU 通常采用以下 3 种方法使用主存：

- **停止 CPU 访问主存**：CPU 处于不工作状态，未充分发挥 CPU 对主存的利用率。
- **DMA 与 CPU 交替访存**：一个 CPU 周期，分为 C1 和 C2 两个周期，C1 专供 DMA 访存，C2 专供 CPU 访存。
- **周期挪用（周期窃取）**：DMA 访存时有三种可能：CPU 此时不访存（不冲突）；CPU 正在访存（存取周期结束让出总线）；CPU 与 DMA 同时请求访存（I/O 访存优先）。

> 【注意】这里的周期指的是**存取周期**！

## DMA内存访问方式

###  Stop CPU 停止CPU

1. Advantage: simple in control 控制简单
2. Disadvantage: influence CPU, not make full use of memory 影响CPU，对于内存的使用不充分
3. Suitable: block transfer by high speed I/O device 高速I/O设备的块传输

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt17/13.png)

4. 这种情况不常用:他是直接停止了CPU对于其他部分的处理

### Cycle stealing 

周期窃取

1. Advantage: make full use of CPU and memory, and response I/O request in time 充分利用CPU和内存，及时响应I/O请求
2. Disadvantage: DMA should request bus each time DMA应每次请求总线
3. Suitable: I/O cycle is larger than memory cycle **I/O周期大于内存周期**

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt17/14.png)

4. CPU用着，DMA使用则进行使用

### Alternate (time sharing) access 

共享权限

1. Advantage: CPU is not stopped or waited, and DMA doesn’t request bus CPU未停止或等待，DMA未请求总线
2. Suitable: CPU cycle is larger than memory cycle 适用：**CPU周期大于内存周期**

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt17/15.png)

3. 这种情况比较少:简单来看就是讲一个时钟周期加细。
4. 

### DMA 方式与中断方式的比较

| 项目     | 中断方式                                | DMA 方式                                          |
| -------- | --------------------------------------- | ------------------------------------------------- |
| 数据传送 | 程序控制（程序的切换-->保存和恢复现场） | 硬件控制（CPU只需进行预处理和后处理）             |
| 中断请求 | 传送数据                                | 后处理                                            |
| 响应     | 指令执行周期结束后响应中断              | 每个机器周期结束均可，总线空闲时即可响应 DMA 请求 |
| 场景     | CPU控制，低速设备                       | DMA控制器控制，高速设备                           |
| 优先级   | 优先级低于DMA                           | 优先级高于中断                                    |
| 异常处理 | 能处理异常事件                          | 仅传送数据                                        |

### 3.4 相关例题

【例 1】假设磁盘传输数据以 32 位的字为单位，采用 DMA 方式与主机交换信息，其传输速率为 2MB/s，而且 DMA 的预处理需 1000 个时钟周期，DMA 完成传送后处理中断需 500 个时钟周期。如果平均传输的数据长度为 4KB，试问在硬盘工作时，50MHz 的处理器需用多少时间比率进行 DMA 辅助操作（预处理和后处理）？

> 【解】1s 时间内，磁盘传输 2MB 数据，DMA 可以每次传输 4KB，则 DMA 传输次数 = 2MB/4KB = 500 次。
>
> DMA 每次传输前的预处理和传输完成后向 CPU 发起的中断处理，需要的时间周期数为 500+1000 = 1500，则 500 次 DMA 传送总共需要花费 1500*500 个时钟周期。
>
> 1s 时间内，处理器一共有 50M 个时钟周期，因此比率为 (1500*500)/50M = 1.5%。
>
> 【注】“磁盘传输数据以 32 位的字为单位”为干扰条件。因为采用 DMA 传输后，磁盘的传输工作就交给了 DMA，从 CPU 视角看相当于是 CPU 和 DMA 打交道，磁盘好像被“透明化”了。

【例 2】一个 DMA 接口可采用**周期窃取**方式把数据传送到存储器，它支持的最大批量为 400 个字节，总线宽度为 8 位。若存取周期为 0.2us，每处理一次中断需 5us，现有的设备的传输率为 9600bit/s。假设数据之间的传输是无间隙的，试问 DMA 方式每秒因数据传输占用处理器多少时间？如果完全采用中断方式，又需占处理器多少时间？（忽略预处理所需时间）

> 【解】（1）DMA 方式
>
> 1s 时间内，设备传输 9600bit = 1200B 数据，DMA 可以每次传输 400B，则 DMA 传输次数 = 1200B/400B = 3 次。
>
> 1200B 数据需要存取 1200 次，存取周期为 0.2us，则总共花费 1200*0.2 = 240us。
>
> DMA 每次传输前的预处理和传输完成后向 CPU 发起的中断处理，所以中断时间一共为 3*5us = 15us。
>
> 占用处理器时间 = 15us+240us = 255us。
>
> （2）中断方式
>
> 1s 时间内，设备传输 9600bit = 1200B 数据，所以中断时间 = 5*1200 = 6000us。

## DMA**配置机制**

### **单总线分离**DMA

所有模块共享相同的系统总线

DMA模块使用编程式I/O，通过DMA模块在存储器和I/O模块之间交换数据

便宜但低效

![image-20230223170449053](data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1704 446"></svg>)

### 单总线集合的DMA-I/O

DMA逻辑实际上可能是I/O模块的一部分，也可能是控制一个或多个I/O模块的单独模块 



减少总线周期数

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt17/16.png)

### I/O 总线

使用I/O总线将I/O模块连接到DMA模块



多个I/O模块共享DMA，且易于扩展

![](https://spricoder.oss-cn-shanghai.aliyuncs.com/2019-COA19/img/cpt17/17.png)

## Questions

2013 mid

![image-20230226005458745](/Users/lyk/Library/Application Support/typora-user-images/image-20230226005458745.png)

注意, 1Mbps是10^6 bps, 而不是2 ^ 20

***

COA19_10

![image-20230226011343279](/Users/lyk/Library/Application Support/typora-user-images/image-20230226011343279.png)

a)没有理解

***

![image-20230226011557494](/Users/lyk/Library/Application Support/typora-user-images/image-20230226011557494.png)

# I/O**模块的演变**

* **CPU直接控制外设**增加控制器或I/O模块，CPU使用编程式I/O，将CPU与外围设备的细节分离

- 采用**中断**，CPU无需花费时间等待外围设备就绪
- I/O模块可通过**DMA**直接存取存储器，无需CPU负责存储器和I/O模块之间的数据传递
- **I/O通道**(I/O channel):I/O模块**有自己的处理器**，带有专门为I/O操作定制的 指令集
  * CPU指示I/O通道执行存储器中的I/O指令，只有在执行完成后才会中断CPU
  * io通道虽然有处理器，但是是和CPU共享内存的，所以没有自己的存储器
- **I/O处理器**(I/O processor):I/O模块有一个**局部存储器**，I/O模块成为一个自治的计算机，常用于与交互式终端进行通信
  * 只需最少的CPU参与即可控制大量I/O设备
