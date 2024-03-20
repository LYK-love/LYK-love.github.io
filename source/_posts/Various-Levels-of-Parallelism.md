---
title: Various-Levels-of-Parallelism
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 21:31:26
---


Sources:

1. [UWashington: CSE471, Lecture04](https://courses.cs.washington.edu/courses/cse471/07sp/lectures/Lecture4.pdf)
1. [UCSD: CSE240A, Lecture13](https://cseweb.ucsd.edu/classes/fa14/cse240A-a/pdf/07/CSE240A-MBT-L13-ReorderBuffer.ppt.pdf)
1. John L. Hennessy & David A. Patterson. (2019). *Chapter 3. Instruction-Level Parallelism and Its Exploitation. Computer Architecture: A Quantitative Approach* (6th ed., pp. 168-266). Elsevier Inc.

<!--more-->

# Kinds of parallelism

- Instruction-level parallelism  (ILP): Finding independent instructions on a scalar core. The ability of a processor to execute multiple  instructions simultaneously
- Data-level parallelism 
  - Each cell or data location is (mostly) independent 
  - Matrix multiply 
- Task-level parallelism: Multiprocess application 
  - Each task is (mostly) independent 
  - Example: web server 

# Flynn's taxonomy

Flynn's taxonomy is a classification to categorize computers based on  the number of instruction streams and data streams they can process  simultaneously. Flynn's taxonomy distinguishes four types of computer  architectures:

1. **Single Instruction, Single Data (SISD)**
2. **Single Instruction, Multiple Data (SIMD)**
3. **Multiple Instruction, Single Data (MISD)**:
4. **Multiple Instruction, Multiple Data (MIMD)**



# Instruction-level parallelism 

ILP refers to the ability of a processor to execute multiple  instructions simultaneously. It focuses on parallel execution within a  single processor core by overlapping the execution of instructions to  improve performance without explicitly programming for parallelism.



The value of the CPI (cycles per instruction) for a pipelined processor is the sum of the base CPI and all contributions from stalls:


$$
\text{Pipeline CPI} = \text{Ideal pipeline CPI} + \text{Structural stalls} + \text{Data hazard stalls} + \text{Control stalls} .
$$


There're 2 types of instruction-level Parallelism (ILP):

1. Static Instruction-level Parallelism (ILP)

   1. Static scheduling
   2. Loop unrolling
   3. Very long instruction word (VLIW)

2. Dynamic ILP: 

   * Out of order execution, which tends to use more power and require more area than static techniques.



In out-of-order processor you can only execute instructions out of order, you still must issue instructions in order and complete (or commit) instructions in order. Why?

1. Must commit instructions in order to make sure that exceptions/interrupts happen precisely for the right instruction.
2. Must issue in order to determine their dependencies. 

# A new ISA type: VLIW

# Dynamic instruction scheduling

Source:

1. [Dynamic Instruction Scheduling](https://ai.eecs.umich.edu/people/conway/ACS/DIS/DIS.pdf).

2. https://ai.eecs.umich.edu/people/conway/ACS/DIS/DIS.pdf

3. [Lynn Conway’s story](https://ai.eecs.umich.edu/people/conway/Retrospective2.html#anchor100470) and her [website](https://ai.eecs.umich.edu/people/conway/) 

   

Dynamic instruction scheduling (DIS)  is one possible implementation of dynamic ILP. It’s one of the first descriptions of a hardware mechanism for ILP.

# Branch prediction

## 2-bit saturating counter predictor

To determine the accuracy of a 2-bit saturating counter predictor given  the branch outcomes and an initial prediction of 'weakly taken', we need to follow the behavior of the predictor through each outcome in the  sequence. The 2-bit saturating counter has four states:

1. Strongly Not Taken (00)
2. Weakly Not Taken (01)
3. Weakly Taken (10)
4. Strongly Taken (11)

For a 2-bit counter, a value of 2 or 3 indicates a taken prediction, and
0 or 1 indicates a not-taken prediction. For a 1-bit counter, it takes on values of only 0 (predict
not taken) or 1 (taken).



For a *2-bit saturating counter* predictor, what is the accuracy for the given branch outcomes? The initial prediction is 'weakly taken'.

NT | T | T | T | T | T | NT | T | T | T | T | T | T | T | T | T | NT | T | T | T

Incorrect Predictions:

- The first "NT" (predictor in 'Weakly Taken' predicts taken)
- The second "NT" after a sequence of "T"s (predictor in 'Strongly Taken' predicts taken)
- The final "NT" (predictor in 'Strongly Taken' predicts taken)
- The first "T".

# Execution Rules

- **True Data Dependency (Read after Write - RAW)**: An instruction cannot execute if it reads from a register that is set to be written by a previous instruction that has not yet executed.
- **Output Dependency (Write after Write - WAW)**: An instruction cannot execute if it writes to a register that is set to be written by a previous instruction that has not yet executed.
- **Anti-dependency (Write after Read - WAR)**: An instruction cannot execute if it writes to a register that is read by a previous instruction that has not yet executed.

# Reorder Buffer

Source: 

1. [The Reorder Buffer (ROB) and the Dispatch Stage](https://docs.boom-core.org/en/latest/sections/reorder-buffer.html)



The **Reorder Buffer (ROB)** tracks the state of all inflight instructions in the pipeline. The role of the ROB is to provide the illusion to the programmer that his program executes in-order. 

After instructions are *decoded* and *renamed*, they are then *dispatched* to the ROB and the **Issue Queue** and marked as *busy*. As instructions finish execution, they inform the ROB and are marked *not busy*. 

Once the “head” of the ROB is no longer busy, the instruction is *committed*, and it’s architectural state now visible. If an exception occurs and the excepting instruction is at the head of the ROB, the pipeline is flushed and no architectural changes that occurred after the excepting instruction are made visible. The ROB then redirects the PC to the appropriate exception handler.



* Use of a reorder buffer: Reorder buffer = circular queue with head and tail pointers
* At issue (renaming time), an instruction is assigned an entry at the tail
  of the reorder buffer (ROB) which becomes the name of (or a pointer
  to) the result register.
  * Recall that instructions are issued in program order, thus the ROB stores
    instructions in program order
* At end of functional-unit computation, value is put in the instruction
  reorder buffer’s position
* When the instruction reaches the head of the buffer, its value is stored
  in the logical or physical (other reorder buffer entry) register.
* Need of a mapping table between logical registers and ROB entries

## Example

![image-20240226194317754](/Users/lyk/Library/Application Support/typora-user-images/image-20240226194317754.png)

Assume reorder buffer is initially at position 6 and has more than 8 slots.

The *mapping table* indicates the correspondence between ROB entries and logical registers.

# Register renaming

[Source: The Rename Stage](https://docs.boom-core.org/en/latest/sections/rename-stage.html)

*Renaming* is a technique to rename the *ISA* (or *logical*) register specifiers in an instruction by mapping them to a new space of *physical* registers. The goal to *register renaming* is to break the false dependencies (**WAR and WAW** hazards) between instructions, leaving only the <u>true dependences</u> (**RAW** hazards). 

* Register renaming does not get rid of RAW dependencies
  * Still need for forwarding or for indicating whether a register has
    received its value
* Register renaming gets rid of WAW and WAR
  dependencies



Typically, a **Physical Register File**, containing many more registers than the ISA dictates, holds both the committed architectural register state and speculative register state. The **Rename Map Table** s contain the information needed to recover the committed state.

## Implementation of Register Renaming

1. **Mapping Table**: A mapping table is used to associate architectural registers (the registers specified by the instruction set architecture) with physical registers. This table is updated with new mappings as instructions are issued.
2. **Free List**: A list of free physical registers is maintained. When an instruction is decoded, and it needs to write to a register, a free physical register is allocated from this list.
3. **Physical Register File**: A larger physical register file is used to hold the values of both architectural and temporary registers. The physical register file has more registers than the architectural register file to support concurrent execution of instructions.
4. **Reorder Buffer**: The reorder buffer tracks the original program order of instructions to ensure that they can be committed (made permanent) in the correct order. This is essential for handling exceptions and maintaining correct program behavior.



Consider two instructions:

1. `ADD R1, R2, R3` (R1 = R2 + R3)
2. `SUB R4, R1, R5` (R4 = R1 - R5)

If these instructions are executed out of order, and a subsequent instruction writes to `R1` before the `SUB` instruction reads `R1`, a **WAR** (Write after Read) hazard occurs. Register renaming can allocate a different physical register for the output of the `ADD` instruction and the subsequent write to `R1`, ensuring the `SUB` instruction reads the correct value.
