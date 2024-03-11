---
title: Data Hazards in Pipelined Design
tags: Computer Architecture
categories: Computer Science
date: 2024-02-26 18:46:32
---


Sources:

* [UWashington: CSE378, Lecture11](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec11.pdf)
* [UWashington: CSE378, Lecture12](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec12.pdf)

Note: the assembly code in this article can be MIPS or RISCV. This shouldn't be consufusing since the only big difference between them is that MIPS add a `$` before the name of each register:

```assembly
# MIPS:
add $t0, $t1, $t2  # add values in $t1 and $t2, the result is stored in $t0

# RISC-V
add t0, t1, t2 # add values in t1 and t2, the result is stored in t0
```

<!--more-->

# Hazards

Hazard is a dependency that causes the pipelines to stall.

1. Data dependency: Dependency between two instructions occurs when source of a younger instruction is the destination of an older instruction. 

   * Solution: Forwarding the value from the older instruction to the younger instruction can hide or help thehazard.

2. Control dependency: Dependency caused by waiting for the decision and target address of the branch instruction.

   * Solution: Branch prediction.

   * In the five-stage pipeline model used in basic CPU architecture, control hazards (also known as branch hazards) become apparent in the Decode (ID) stage. This is when the processor decodes the instruction and realizes that it is a branch instruction, which could potentially alter the control flow based on its condition.

     However, **the decision to stall** the pipeline due to a control hazard typically occurs after the branch condition is evaluated, which happens in the Execute (EX) stage for most simple pipelines. It's **in the EX stage that the processor can determine whether the branch will be taken or not** and what the target address of the branch will be if it is taken.

3. Structure dependency: Dependency caused by multiple instructions having conflicts in resources, such as the usage of a memory access port for both load and store instructions.

# Data hazards

 A data hazard arises if one instruction needs data that isn't ready yet.

- Below, the AND and OR both need to read register \$2.
- But \$2 isn't updated by SUB until the fifth clock cycle.

Dependency arrows (explained later) that point backwards indicate data hazards:

![Figure 1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 1.png)

# An example of data hazard

![Figure 2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 2.png)

The SUB instruction does not write to register \$2 (remember that in ID stage we need to read the data in register \$2 from **register file**) **until clock cycle 5**. This causes two data hazards in our current pipelined datapath.

1. The AND reads register \$2 in cycle 3. Since SUB hasn’t modified the register yet, this will be the old value of \$2, not the new one.
2. Similarly, the OR instruction uses register \$2 in cycle 4, again before it’s actually updated by SUB.



## Things that are OK

![Figure 3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 3.png)

The ADD instruction is okay, because of the register file design. Remember we have regulated that writes occur in the first half of the cycle, reads occur in the second half, so ADD can read from register \$2 in the second half of cycle 5.

The SW is no problem at all, since it reads \$2 after the SUB finishes.

## Dependency arrows

![Figure 4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 4.png)

Arrows indicate the flow of data between instructions.

1. The tails of the arrows show when register \$2 is written.
2. The heads of the arrows show when \$2 is read.

Any arrow that points **backwards** in time represents **a data hazard** in our basic pipelined datapath. Here, hazards exist between instructions 1 & 2 and 1 & 3.



A fancier pipeline diagram:

![Figure 5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 5.png)

## How to solve it?

We have to eliminate the hazards, so the AND and OR instructions in our example will use the correct value for register \$2.

Let’s look at <u>when the data is actually produced and consumed</u>.

1. The SUB instruction produces its result in its EX stage, during cycle 3 in the diagram below.
2. The AND and OR need the new value of \$2 in their EX stages, during clock cycles 4-5 here.

![Figure 6](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 6 .png)



The ALU result generated in the EX stage is normally passed through the pipeline registers to the MEM and WB stages, before it is finally written to the register file.

This is an abridged diagram of our pipelined datapath.

![Figure 7](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 7.png)

In next section we'll use forwarding technique to solve this kind of data hazard.

# Forwarding data from the pipeline registers

**Forwarding** allows other instructions to <u>read ALU results directly from the pipeline registers, without going through the register file</u>.

Forwarding can only solve data hazards involving **arithmetic instructions**.

In previous example, the actual result `$1 - $3` is computed in clock cycle 3 , before it's needed in cycles 4 and 5. Essentially, we need to pass the ALU output from SUB directly to the AND and OR instructions, without going through the register file.



Since the pipeline registers already contain the ALU result, we could just **forward** that value to subsequent instructions, to prevent data hazards.

- In clock cycle 4, the AND instruction can get the value `$1 - $3` from **the EX/MEM pipeline register** being used by SUB.
- Then in cycle 5 , the OR can get that same result from **the MEM/WB pipeline register** being used by SUB.

![Figure 8](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 8.png)

## Outline of the hareware implementation for forwarding

A <span style="color: red;">forwarding unit</span> selects the correct ALU inputs for the EX stage.

1. If there is no hazard, the ALU’s operands will come from the <span style="color: pink;">register file</span>, just like before.
2. If there is a hazard, the operands will come from either the <span style="color: blue;">EX/MEM</span> or <span style="color: green;">MEM/WB</span> pipeline registers instead.

The ALU sources will be selected by two new multiplexers, with control signals named <span style="color: red;">ForwardingA</span> and <span style="color: red;">ForwardingB</span>.

![Figure 9](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 9.png)

## Simplified datapath with forwarding muxes

![Figure 10](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 10.png)

The implemention details of the forwarding units and the way to detect data hazards are covered in [-->this slide](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec11.pdf).

# Stalling

Foewarding can only solve hazards arising from arithmetic instructions. What if the first instruction in the example was **LW** instead of SUB?

![Figure 11](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 11.png)

The easiest solution is to **stall** the pipeline.

## Stalling and forwarding

We could delay the AND instruction by introducing a one-cycle delay into the pipeline, sometimes called a **bubble**.

![Figure 12](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 12.png)

Notice that we’re still using <u>forwarding</u> in cycle 5, to get data from the MEM/WB pipeline register to the ALU.

## Just stalling

Without forwarding, we’d have to stall for two cycles to wait for the LW instruction’s writeback stage.

![Figure 13](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 13.png)

In general, **you can always stall to avoid hazards**—but dependencies are very common in real code, and stalling often can reduce performance by a significant amount.

## Stalling delays the entire pipeline

If we delay the second instruction, we’ll have to delay the third one too.

1. This is necessary to make forwarding work between AND and OR.
2. It also prevents problems such as two instructions trying to write to the same register in the same cycle.

![Figure 14](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 14.png)

During stalling, some hardware may be idling. So we can set the control signals to 0s.

For example, considering the ALU during cycle 4, the data memory in cycle 5, and the register file write in cycle 6, those units aren’t used in those cycles because of the stall, so we can set the EX, MEM and WB control signals to all 0s.

![Figure 15](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 15.png)

## Stall = Nop conversion

![Figure 16](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Data%20Hazards%20in%20Pipelined%20Design/Figure 16.png)

The effect of a load stall is to insert an empty or **nop** instruction into the pipeline.

