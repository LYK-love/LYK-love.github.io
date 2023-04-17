---
title: Instruction Fetch and Execute
tags: Computer Architecture
categories: Computer Science
mathjax: true
---

# Intro





## Instruction Cycle

计算机的基本功能就是执行程序, 而程序就是由若干指令组成的, 指令存储在内存中.



*  **instruction cycle**(指令周期:): CPU执行处理单个指令的流程.

  ![Basic Instruction Cycle](/Users/lyk/Library/Application Support/typora-user-images/image-20230223140454488.png)

  基本的指令周期见上图(此时还没有加入中断处理过程). 

  * 可以看到, 指令周期分两个阶段:
    1. **fetch cycle** : The processor reads (*fetches*) instructions from memory one at a time
    2. **execute cycle** : executes each instruction.
  * Program execution **halts** only if the machine is turned off, some sort of unrecoverable error occurs, or a program instruction that halts the computer is encountered.

  

  # PC

   In a typical processor, a register called the program counter (PC) holds the address of the instruction to be fetched next.

  Unless told otherwise, the processor always increments the PC after each instruction fetch so that it will fetch the next instruction in sequence (i.e., the instruction located at the next higher memory address).

  # IR

  The fetched instruction is loaded into a register in the processor known as the instruction register (IR). 

  The processor interprets the instruction and performs the required action. In general, these actions fall into four categories:

  * **Processor-memory:** Data may be transferred from processor to memory or from memory to processor.
  * **Processor-I/O:** Data may be transferred to or from a peripheral device by transferring between the processor and an I/O module.
  * **Data processing:** The processor may perform some arithmetic or logic oper- ation on data.
  * **Control:** 有些指令的作用是改变指令的执行流. 
    * For example, the processor may fetch an instruction from location 149, which specifies that the next instruction be from location 182. The processor will remember this fact by setting the program counter to 182. Thus, on the next fetch cycle, the instruction will be fetched from location 182 rather than 150.



## Instruction Cycle with Interrupts



![Transfer of Control via Interrupts](/Users/lyk/Library/Application Support/typora-user-images/image-20230223160931296.png)





![Instruction Cycle with Interrupts](/Users/lyk/Library/Application Support/typora-user-images/image-20230223160816783.png)

# Six Steps

- 取指令(Fetch instruction，FI):读下一条预期的指令到缓冲器
- 译码指令(Decode instruction，DI):确定操作码和操作数指定符
- 计算操作数(Calculate operands，CO):计算每个源操作数的有效地址
- 取操作数(Fetch operands，FO):从存储器取出每个操作数，寄存器中 的操作数不需要取
- 执行指令(Execute instruction，EI):完成指定的操作。若有指定的目的 操作数位置，则将结果写入此位置
- 写操作数(Write operand，WO):将结果存入存储器



问题：

* 不是所有指令都包含六个阶段，如LOAD没有WO，只能假设每个指令按六阶段完成；
* 不是所有阶段可以并行完成，如FI、FO、WO都涉及[存储器访问](#分立Cache)；
* 若每个阶段时间不同，则会涉及等待
* 限制：条件分支指令、中断

# Pipeline

流水线阶段数提高的局限：

* 每个阶段转移数据存在开销；
* 处理内存和寄存器依赖以及优化管道所用的控制逻辑数量随着阶段的增加而增加

## 时间

如果流水线中的各段执行时间均为$t$, 那么执行$n$条指令的时间 = 执行第一条指令的时间kt + 其余$n-1$条指令各执行一段的时间$(n-1)t$

令$T_{k,n}$为 k 阶段流水线执行所有 n 条指令所需的总时间:
$$
T_k,n = [k + (n - 1)]t
$$


加速比:
$$
S_{k}=\frac{T_{n}}{T_{k, n}}=\frac{n k t}{[k+(n-1)] t}=\frac{n k}{k+(n-1)}=\frac{n}{1+\frac{n-1}{k}}
$$
上式分子分母同时除以$n$:
$$
S_k = \frac {k}{1 + \frac {k-1}{n}}
$$
实际场景中, $n$一般很大, 因此$S_k$近似为$k$



## 流水线冒险

### 结构冒险

* 结构冒险：硬件资源冲突
  * 问题：已进入流水线的不同指令在同一时刻访问相同的硬件资源
  * 解决：使用[不同的硬件资源](#分立Cache)；或分时访问同一资源

### 数据冒险

* 数据冒险：数据依赖性
  * 问题：未生成指令所需要的数据
  * 解决：插入nop指令；插入bubble；**转发/旁路**；交换指令顺序

### 控制冒险

* 控制冒险：指令顺序被更改

  * 问题：条件转移、中断、异常、调用/返回

  * 解决：

    * 取多条指令：多个指令流；预取分支目标；循环缓冲器

    * 分支预测：静态预测；动态预测

      * 动态预测：转移状态图；转移历史表

      ​                  



- 
- 
