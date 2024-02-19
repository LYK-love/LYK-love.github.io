---
title: Instruction-Level Parallelism
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 21:31:26
---


Source:

1. John L. Hennessy & David A. Patterson. (2019). *Chapter 3. Instruction-Level Parallelism and Its Exploitation. Computer Architecture: A Quantitative Approach* (6th ed., pp. 168-266). Elsevier Inc.

<!--more-->

# Instruction-level parallelism 

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

# Register renaming

With register renaming, a technique used in out-of-order execution to  eliminate false dependencies (WAR and WAW hazards), instructions that do not have true dependencies (**RAW** hazards) on the currently executing  instructions or each other can potentially be executed simultaneously,  assuming there are enough execution units and buses.



- Register renaming **ensures that the read operation accesses the correct version of the data** by assigning the read and write operations to different physical registers.
- This allows the read instruction to operate on the data value that was present before the write instruction, maintaining correct program semantics.

### Implementation of Register Renaming

1. **Mapping Table**: A mapping table is used to associate architectural registers (the registers specified by the instruction set architecture) with physical registers. This table is updated with new mappings as instructions are issued.
2. **Free List**: A list of free physical registers is maintained. When an instruction is decoded, and it needs to write to a register, a free physical register is allocated from this list.
3. **Physical Register File**: A larger physical register file is used to hold the values of both architectural and temporary registers. The physical register file has more registers than the architectural register file to support concurrent execution of instructions.
4. **Reorder Buffer**: The reorder buffer tracks the original program order of instructions to ensure that they can be committed (made permanent) in the correct order. This is essential for handling exceptions and maintaining correct program behavior.
5. 

Consider two instructions:

1. `ADD R1, R2, R3` (R1 = R2 + R3)
2. `SUB R4, R1, R5` (R4 = R1 - R5)

If these instructions are executed out of order, and a subsequent instruction writes to `R1` before the `SUB` instruction reads `R1`, a **WAR** (Write after Read) hazard occurs. Register renaming can allocate a different physical register for the output of the `ADD` instruction and the subsequent write to `R1`, ensuring the `SUB` instruction reads the correct value.
