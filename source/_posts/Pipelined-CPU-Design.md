---
title: Pipelined CPU Design
tags: Computer Architecture
categories: Computer Science
date: 2024-02-06 21:36:50
---


Source:

1. John L. Hennessy & David A. Patterson. (2019). *Appendix C.1. Computer Architecture: A Quantitative Approach* (6th ed.). Elsevier Inc.
2. Randal E. Bryant & David R. O’Hallaron. (2016). *Chapter 4. Processor Architecture. Computer Systems: A Programmer’s Perspective* (3th ed., pp. 387-516). Pearson.

<!--more-->



# What is pipelining ?

Pipelining is an implementation technique whereby multiple instructions are over- lapped in execution.

In a pipelined system, the task to be performed is divided into a series of discrete stages. Each of these stages is called a **pipe stage** or a pipe segment.

The time required between moving an instruction one step down the pipeline is a *processor cycle*. In a computer, this processor cycle is almost always 1 *clock cycle*.

Because all stages proceed at the same time, the length of a processor cycle is determined by the time required for the slowest pipe stage.

Pipelining increases the processor instruction *throughput*—the number of instructions completed per unit of time—but it alsp increases the *latency* due to overhead in the control of the pipeline. 

# Organizing Processing into Stages

Canonically, we have the following five steps to complete an instruction:

1. **Fetch** the instruction: In this stage, the processor retrieves the next instruction to be  executed from memory. The program counter (PC) keeps track of the  current instruction address, and after fetching, the PC is updated to  point to the next instruction.
2. **Decode** the instruction: figure out what we should do and read the data from the register file.
3. **Execute** the instruction: use the arithmetic/logic unit (ALU) to compute a result, the effective address, or direction of the branch.
4. **Memory**: For instructions that involve data memory access (load and store  instructions), this stage is used to **read from or write to memory**. Load  instructions read data from the calculated memory address into a  register, while store instructions write data from a register to the  calculated memory address.
5. **Writeback** the instruction: (if required) write the result of the instruction to the register file. For arithmetic and logical instructions, this typically involves writing the result into a destination register. For load instructions, the data fetched from memory is written into a destination register.

The processor loops indefinitely, performing these stages. Ideally, **each step is finished in one clock cycle**.

(This five-stage model applies to most RISC ISAs, including RISC-V. For some CISC ISAs, they may use a simpler four-stage model.)

# Single cycle CPU design

In single cycle CPU design, for every instruction, the 5 stages should be executed sequentially.

Since the CPU cycle time can't be changed after the CPU is produced, we must make it larger enough so that every single instruction can be executed in it.

Therefore, the design of the CPU cycle time is limited by the [latency]() of the longest instructions. 

# Pipelined CPU design

* The cycle time of a pipelined CPU design is the latency of its critical stage (the stage with the longest latency).
* Theoretically the maximum CPI of a single-issue pipelined CPU design is 1. 
* However, pipelined CPU design introduces **hazards**.

## Hazard

Hazard is a dependency that causes the pipelines to stall.

1. Data dependency: Dependency between two instructions occurs when source of a younger instruction is the destination of an older instruction. 
   * Solution: Forwarding the value from the older instruction to the younger instruction can hide or help thehazard.
2. Control dependency: Dependency caused by waiting for the decision and target address of the branch instruction.
   * Solution: Branch prediction.
3. Structure dependency: Dependency caused by multiple instructions having conflicts in resources.

# The Classic Five-Stage Pipeline for a RISC Processor

We can pipeline the execution described in the previous section with almost no changes by simply <u>starting a new instruction on each clock cycle</u>. 

Figure C.1 is the typical way of pipelining. Although each instruction takes 5 clock cycles to complete, on each clock cycle another instruction is fetched and begins its five-cycle execution. If an instruction is started every clock cycle, the performance will be up to five times that of a processor that is not pipelined.



![Figure 1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure%201.png)

where

* IF: instruction fetch
* ID: instruction decode
* EX: execution
* MEM: memory access
* WB: write-back



An in-order pipeline in computer architecture refers to a design where instructions are processed in the strict order they appear in the program. This means that each instruction goes through the stages of the pipeline (like fetch, decode, execute, memory access, and write back) in sequence, and each stage must be completed before the next instruction can enter that stage



**SIMD Operations**: SIMD stands for Single Instruction,  Multiple Data. This refers to a method used in parallel computing where a single instruction is applied to multiple data points simultaneously.  SIMD units are particularly useful for tasks that involve processing  large blocks of data with the same operation, such as in graphics  processing, scientific simulations, or operations on arrays/matrices.

## Requirement1: overlapped instructions can't use the the hardware resources at the same time

In order to use pipeline, one requirement is that **the overlap of instructions in the pipeline cannot use the hardware resources at the same time**. Fortunately, the simplicity of a RISC instruction set makes resource evaluation relatively easy. Figure C.2 shows a simplified version of a RISC data path drawn in pipeline fashion.

![Figure 2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure%202.png)

where:

* IM: instruction memory, (more precisely, instruction memory port)
* DM: data memory (more precisely, data memory port)
* CC: clock cycle.

Note: the register file is used in the two stages: one for <u>reading</u> in ID and one for <u>writing</u> in WB. 



## Requirement2: instructions in different stages can't interfere with one another

Another requirement is that **instructions in different stages of the pipeline can't interfere with one another.**

To achieve this separation, we introduce **pipeline registers** <u>between successive stages of the pipeline</u>, so that at the end of a clock cycle all the results from a given stage are stored into a register that is used as the input to the next stage on the next clock cycle.

Figure 3 shows the pipeline drawn with these pipeline registers.

![Figure 3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure%203.png)

# Limitations of Pipelining

## Nonuniform Partitioning

Idealy, every stage is finished in one clock cycle. For every pipe stage, its start and end are aligned to the clock cycle.

However, different stages have different executation time. 

In order to gurantee all stages can be finished in one clock cycle, **the clock cycle is designed to be** no less than the **slowest** pipeline stage.





![Figure 4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure%204.png)

## Diminishing Returns of Deep Pipelining

Figure 4.37 illustrates another limitation of pipelining. In this example, we have divided the computation into six stages, each requiring 50 ps. Inserting a pipeline register between each pair of stages yields a six-stage pipeline. The minimum clock period for this system is 50 + 20 = 70 picoseconds. But the delay due to register updating becomes a limiting factor.

![Figure 5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Pipelined%20CPU%20Design/Figure%205.png)
