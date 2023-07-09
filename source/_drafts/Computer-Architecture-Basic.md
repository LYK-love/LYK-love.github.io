---
title: Computer Architecture Basic
tags: Computer Architecture
categories: Computer Science
mathjax: true
---

# Intro

冯诺依曼模型(the von Neumann machine): 

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/Von_Neumann_Architecture.svg/300px-Von_Neumann_Architecture.svg.png)



计算机组成: 

* I/O 
* 主存(Main memory)
* CPU:
  * ALU
  * PCU( Program Control Unit )



* 冯诺依曼结构的思想: 把**程序和数据**一样以**二进制**的形式存储, 并由计算机自动取出后逐条执行.

## 计算机组织与结构

* 组织：对编程人员不可见，包括控制信号、存储技术。例如：乘法指令的内部实现
* 结构：对编程人员可见，包括指令集、位数。例如：是否提供乘法指令

# 计算机的演变

第一代：真空管；第二代：晶体管；第三代及以后：集成电路

冯诺依曼结构：



* 



* 组成部分：
  * 主存储器
  * 处理单元
  * 控制单元
  * 输入单元，输出单元





## 摩尔定律

单芯片上所能包含的晶体管数量每隔一年翻一倍，到1970年后变为每18个月翻一倍

影响：

- 单个芯片成本基本不变，说明计算机逻辑电路和存储器电路的成本明显下降
- 集成度更高，电子线路长度更短，提高工作速度
- 计算机变得更小，可以放在各种环境中
- 减小了电能损耗对冷却的要求
- 芯片间的连接变少，而集成电路间的连接比焊接可靠



* 





# Computer Performance

性能评价的标准

* CPU：速度；

* 存储器：速度、容量；

* I/O：速度、容量；

* 计算机设计的主要目标：提高CPU的性能



衡量计算机系统的主要指标？

* 速度：**响应时间、吞吐率。**

  **响应时间是开始到完成的时间，吞吐率是单位时间的工作量**。

## Big End

![image-20230226013332067](/Users/lyk/Library/Application Support/typora-user-images/image-20230226013332067.png)

小断: 低字节放在低地址

## CPU Performance

* 时钟以固定频率f(或等价地说，以固定周期时间t)来驱动处理器，这里t=1/f。
* 程序的规模能用程序 所包含的机器指令数，或者指令计数 IC 来衡量。不同的指令会要求不同的时钟周期数来执行。
* 一个重要参 数是程序的平均每条指令周期数(average cycles per instruction，CPI)。
* 执行一个给定程序所需的处理 器时间能表示成: T=IC×CPI×t



* 系统时钟: 

  * **时钟频率** / 时钟速度(单位:Hz):计算机在单位时间内(例如1秒钟)执行最基本操作的次数

  * **时钟周期** / 周期时间(单位:s): **执行每次最基本操作的时间**

    • 时钟滴答(有时也称为“时钟周期”):CPU 中用于同步执行 最基本操作的单个电子脉冲

    • 因此，周期时间即为两个电子脉冲之间的时间

* 指令执行:

  * CPU由时钟驱动, 时钟具有固定的频率f, 或等价为固定的时钟周期t

  * 如果用$\text{CPI}_i$ 来表示指定类型i所需要的周期数，用 $I_i$ 表示在某一给 定程序中所执行的 $i$ 类指令的条数, 则计算整个$\text{CPI}$如下:
    $$
    \text{CPI}=\frac{\sum_{i=1}^{n}\left(C P I_{i} \times I_{i}\right)}{I_{c}}, I_{c}=\sum_{i=1}^{n} I_{i}
    $$
    
  * 执行一个给定程序的处理时间表示为:
    $$
    T=I_{c} \times C P I \times t
    $$
  
  * 每秒百万条指令(MIPS):
    $$
    \text{MIPS}=\frac{I_{c}}{T \times 10^{6}}=\frac{f}{C P I \times 10^{6}}
    $$
    
  *  每秒百万条浮点操作(MFLOPS):
    $$
    \text { MFLOPS }=\frac{N_{\text {floating-point op }}}{T \times 10^{6}}
    $$
  
* 设时钟频率为 f，平均每条指令周期数为 CPI. 所以平均每条指令所需要的时间为 CPI/f

* 

* 基准程序: 使用一系列基准程序来测量系统的性能

  * 算数平均值:
    $$
    R_{A}=\frac{1}{m} \sum_{i=1}^{m} R_{i}
    $$
    
  * 调和平均值:
    $$
    R_{H}=\frac{m}{\sum_{i=1}^{m} \frac{1}{R_{i}}}
    $$





## Data Trans Performance

* 数据传输率: Mbps, 这里的M是指$10^6$

## Questions

* CPU时钟频率越高，机器越快吗？

  还要考虑其他因素，比如存储器、I/O模块存取速度、总线传输速度等

* MIPS越大，性能越好吗？

  不是，MIPS数反映的是机器执行定点指令的速度。不同机器的**指令集**不同，指令的功能也不同。计算机也可以采用了流水线、并行等技术提高性能.
