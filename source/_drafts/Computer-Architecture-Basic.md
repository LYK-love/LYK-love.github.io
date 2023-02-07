---
title: Computer Architecture Basic
tags: Computer Architecture
categories: Computer Science
---



**组织(****Organization****)**:对编程人员不可见 • 操作单元及其相互连接
 • 包括:控制信号，存储技术，......

• 例如:实现乘法是通过硬件单元还是重复加法?

• **结构(****Architecture****)**:对编程人员可见
 • 直接影响程序逻辑执行的属性
 • 包括:指令集，表示数据类型的位数，......

• 例如:是否有乘法指令?



# Computer Performance

## CPU Performance
* 系统时钟: 

  * **时钟频率** / 时钟速度(单位:Hz):计算机在单位时间内(例如1秒钟)执行最基本操作的次数

  * **时钟周期** / 周期时间(单位:s):执行每次最基本操作的时间

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
  
* 基准程序: 使用一系列基准程序来测量系统的性能

  * 算数平均值:
    $$
    R_{A}=\frac{1}{m} \sum_{i=1}^{m} R_{i}
    $$
    
  * 调和平均值:
    $$
    R_{H}=\frac{m}{\sum_{i=1}^{m} \frac{1}{R_{i}}}
    $$
