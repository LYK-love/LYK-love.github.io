---
title: Pipelined CPU Design
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 21:36:50
---


Source:

1. [UWashington: CSE378, Lecture09](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec09.pdf)
2. [UWashington: CSE378, Lecture10](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec10.pdf)
3. John L. Hennessy & David A. Patterson. (2019). *Appendix C.1. Computer Architecture: A Quantitative Approach* (6th ed.). Elsevier Inc.
4. Randal E. Bryant & David R. O’Hallaron. (2016). *Chapter 4. Processor Architecture. Computer Systems: A Programmer’s Perspective* (3th ed., pp. 387-516). Pearson.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Cover.png" alt="Image from: https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec10.pdf" style="zoom: 33%;" />

Note: the assembly code in this article can be MIPS or RISCV. This shouldn't be consufusing since the only big difference between them is that MIPS add a `$` before the name of each register:

```assembly
# MIPS:
add $t0, $t1, $t2  # add values in $t1 and $t2, the result is stored in $t0

#RISC-V
add t0, t1, t2 # add values in t1 and t2, the result is stored in t0
```

<!--more-->



# What is pipelining ?

Pipelining is an implementation technique whereby multiple instructions are over- lapped in execution.

In a pipelined system, the task to be performed is divided into a series of discrete stages. Each of these stages is called a **pipe stage** or a pipe segment.

Pipelining increases the processor instruction *throughput*but it alsp increases the *latency* due to overhead in the control of the pipeline. 

* Pipelining doesn’t help latency of single load. It'll acturally slightly increase the latency due to the overhead of pipeline registers (explained later).
* Pipelining helps throughput—the number of instructions completed per unit of time—of entire workload.
* Pipeline rate limited by slowest pipeline stage. Since we want to make each state take only one clock cycle, and the clock cycle is bottlenected by the time of the slowest stage.

# Single cycle CPU design

In single cycle CPU design, for every instruction, the 5 stages should be executed sequentially.

Since the CPU cycle time can't be changed after the CPU is produced, we must make it larger enough so that every single instruction can be executed in it.

Therefore, the design of the CPU cycle time is limited by the [latency]() of the longest instructions. 



## Single cycle CPU datapath

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 1.png" alt="Figure 1" style="zoom: 33%;" />

# Pipelined CPU design

* The cycle time of a pipelined CPU design is the latency of its critical stage (the stage with the longest latency).
* Theoretically the maximum CPI of a single-issue pipelined CPU design is 1. 
* However, pipelined CPU design introduces **hazards**.





## 5 stages in pipeline

Canonically, we have the following five steps to complete an instruction:

1. **Fetch** the instruction: In this stage, the processor retrieves the next instruction to be executed **from memory (or "instruction memory")**. The program counter (PC) keeps track of the  current instruction address, and after fetching, the PC is updated to  point to the next instruction.
2. **Decode** the instruction: figure out what we should do and **read the data from the register file**. During this stage the bits from the instruction specify which registers need to be read (or written to).
3. **Execute** the instruction: use the arithmetic/logic unit (**ALU**) to compute a result, the effective address, or direction of the branch.
4. **Memory**: For instructions that involve data memory access (only **load and store** instructions), this stage is used to **read from or write to memory**. Load  instructions read data from the calculated memory address into a  register, while store instructions write data from a register to the  calculated memory address.
5. **Writeback** the instruction: (if required) write the result of the instruction **to the register file**. For arithmetic and logical instructions, this typically involves writing the result into a destination register. For load instructions, the data fetched from memory is written into a destination register.

The processor loops indefinitely, performing these stages. Ideally, **each step is finished in one clock cycle**.

The execution of single instruction is atomic.



(This five-stage model applies to most RISC ISAs, including RISC-V. For some CISC ISAs, they may use a simpler four-stage model.)



Note that some stages will <span style="color: red;">do nothing</span> for some instructions:

![Figure 2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 2.png)

## The Classic Five-Stage Pipeline for a RISC Processor

We can pipeline the execution described in the previous section with almost no changes by simply <u>starting a new instruction on each clock cycle</u>. 

Figure C.1 is the typical way of pipelining. Although each instruction takes 5 clock cycles to complete, on each clock cycle another instruction is fetched and begins its five-cycle execution. If an instruction is started every clock cycle, the performance will be up to five times that of a processor that is not pipelined.



![Figure 3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 3.png)

where

* IF: instruction fetch
* ID: instruction decode
* EX: execution
* MEM: memory access
* WB: write-back



An in-order pipeline in computer architecture refers to a design where instructions are processed in the strict order they appear in the program. This means that each instruction goes through the stages of the pipeline (like fetch, decode, execute, memory access, and write back) in sequence, and each stage must be completed before the next instruction can enter that stage



**SIMD Operations**: SIMD stands for Single Instruction,  Multiple Data. This refers to a method used in parallel computing where a single instruction is applied to multiple data points simultaneously.  SIMD units are particularly useful for tasks that involve processing  large blocks of data with the same operation, such as in graphics  processing, scientific simulations, or operations on arrays/matrices.

## Break datapath into 5 stages

![Figure 4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 4.png)

# Pipeline terminology

![Figure 5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 5.png)

* The **pipeline depth** is the number of stages—in this case, five.
* In the first four cycles here, the pipeline is **filling**, since there are unused functional units.
* In cycle 5, the pipeline is **full**. Five instructions are being executed simultaneously, so all hardware units are in use.
* In cycles 6-9, the pipeline is **emptying**.

# Pipelining Performance

![Figure 6](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 6.png)

Execution time on ideal pipeline, i.e., each stage takes 1 clock cycle: 

<span style="color: red;">time to fill the pipeline</span> + <span style="color: blue;">one cycle per instruction</span>



Suppose we have $N$ instructions, the time costing is:

<span style="color: red;">4 cycles</span> + <span style="color: blue;">N cycles</span>



Compare with other implementations:
- Single Cycle: $N$ cycles.

## Register file

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/register file.png" alt="register file" style="zoom:25%;" />

* We need only one register file to support both the ID and WB stages.
* Reads and writes go to <u>separate ports</u> on the register file.
* **Writes occur in the first half of the cycle, reads occur in the second half.**



## Pipeline registers

We’ll add intermediate registers to our pipelined datapath too.

* For simplicity, we’ll draw just one big **pipeline register** between <u>each stage</u>.

* The registers are named for the stages they connect.

  ```
  IF/ID ID/EX EX/MEM MEM/WB
  ```

* No register is needed after the WB stage, because after WB the instruction is done.

* The function of pipeline registers is: propagate data and control values to later stages.



## Pipelined datapath

![Figure 7](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 7.png)

## Pipelined control path

![Figure 8](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 8.png)

* The control signals are generated in the same way as in the single-cycle processor-after an instruction is fetched, the processor decodes it and produces the appropriate control values.
* But just like before, some of the control signals will <u>not be needed until some later stage</u> and clock cycle. These signals must be propagated through the pipeline until they reach the appropriate stage. 
* We can just pass them in the pipeline registers, along with the other data.
* Control signals can be categorized by the pipeline stage that uses them.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Table of control signals.png" alt="able of control signals" style="zoom:33%;" />

## Pipelined datapath and control

![Figure 9](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 9.png)

Notes about the diagram:

1. The control signals are grouped together in the pipeline registers, just to
   make the diagram a little clearer.
2. Not all of the registers have a write enable signal.
   1. Because the datapath fetches one instruction per cycle, the PC must
      also be updated on each clock cycle. Including a write enable for the
      PC would be redundant.
   2. Similarly, the pipeline registers are also written on every cycle, so no
      explicit write signals are needed.

# Requirements of pipeline

Note that in pipelined design we have some contraints:

* Overlapped instructions can't use the the hardware resources at the same time

* Any data values required in later stages must be propagated through the
  pipeline registers. 

  The most extreme example is the destination register: The `rd` field of the instruction word, retrieved in the first stage (IF), determines the destination register. But that register isn’t updated
  until the fifth stage (WB). Thus, the `rd` field must be passed through all of the pipeline stages,
  as shown in red on the next slide.

* Instructions in different stages can't interfere with one another

* Notice that we can’t keep a single "instruction register" like we did before in the multicycle datapath, because the pipelined machine needs to fetch a new instruction every clock cycle

## Requirement: overlapped instructions can't use the the hardware resources at the same time

In order to use pipeline, one requirement is that **the overlap of instructions in the pipeline cannot use the hardware resources at the same time**. Fortunately, the simplicity of a RISC instruction set makes resource evaluation relatively easy. Figure C.2 shows a simplified version of a RISC data path drawn in pipeline fashion.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 10.png" alt="Figure 10" style="zoom:50%;" />

where:

* IM: instruction memory, (more precisely, instruction memory port)
* DM: data memory (more precisely, data memory port)
* CC: clock cycle.

Note: the register file is used in the two stages: one for <u>reading</u> in ID and one for <u>writing</u> in WB. 

## Requirement: instructions in different stages can't interfere with one another

Another requirement is that **instructions in different stages of the pipeline can't interfere with one another.**

To achieve this separation, we introduce **pipeline registers** <u>between successive stages of the pipeline</u>, so that at the end of a clock cycle all the results from a given stage are stored into a register that is used as the input to the next stage on the next clock cycle.

Figure 3 shows the pipeline drawn with these pipeline registers.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 11.png" alt="Figure 11" style="zoom:50%;" />

# Hazards

Dur to these contraints, three kinds of hazards conspire to make pipelining difficult.

1. **Structural hazards** result from not having enough hardware available to execute multiple instructions simultaneously.
   1. These are avoided by adding more functional units (e.g., more adders
      or memories) or by redesigning the pipeline stages.
2. **Data hazards** can occur when instructions need to access registers that haven’t been updated yet.
   1. Hazards from R-type instructions can be avoided with **forwarding**.
   2. Loads can result in a “true” hazard, which **must stall** the pipeline.
3. **Control hazards** arise when the CPU cannot determine which instruction to fetch next.
   1. We can minimize delays by doing branch tests earlier in the pipeline.
   2. We can also take a chance and predict the branch direction, to make the most of a bad situation.

# Limitations of Pipelining

## Diminishing Returns of Deep Pipelining

Figure5 illustrates another limitation of pipelining. In this example, we have divided the computation into six stages, each requiring 50 ps. Inserting a pipeline register between each pair of stages yields a six-stage pipeline. The minimum clock period for this system is 50 + 20 = 70 picoseconds. But the delay due to register updating becomes a limiting factor.

![Figure 12](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure 12.png)
