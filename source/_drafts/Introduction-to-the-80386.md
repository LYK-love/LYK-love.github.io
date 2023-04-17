---
title: Introduction to the 80386
tags:
---

# Registers

## General Registers

## Segment Registers

![Segment Registers](/Users/lyk/Library/Application Support/typora-user-images/image-20230228214243779.png)

The segment registers of the 80386 give systems software designers the flexibility to choose among various models of memory organization. Implementation of memory models is the subject of Part II ── Systems Programming. Designers may choose a model in which applications programs do not need to modify segment registers, in which case applications programmers may skip this section.

Complete programs generally consist of many different modules, each consisting of instructions and data. However, at any given time during program execution, only a small subset of a program's modules are actually in use. The 80386 architecture takes advantage of this by providing mechanisms to support direct access to the instructions and data of the current module's environment, with access to additional segments on demand.

At any given instant, **six segments** of memory may be immediately accessible to an executing 80386 program. 

The segment registers **CS, DS, SS, ES, FS, and GS** are used to identify these six current segments. Each of these registers specifies a particular kind of segment, as characterized by the associated mnemonics ("code," "data," or "stack") shown in Figure 2-6. 

**Each register uniquely determines one particular segment, from among the segments that make up the program, that is to be immediately accessible at highest speed.**



CS: 

The segment containing the currently executing sequence of instructions is known as the current **code segment**; it is specified by means of the **CS** register. 

The 80386 fetches all instructions from this code segment, using as an offset the contents of the instruction pointer. 

CS is <u>changed implicitly</u> as the result of intersegment control-transfer instructions (for example, CALL and JMP), interrupts, and exceptions.

Subroutine calls, parameters, and procedure activation records usually require that a region of memory be allocated for a stack. All stack operations use the SS register to locate the stack. Unlike CS, the SS register can be loaded explicitly, thereby permitting programmers to define stacks dynamically.



The DS, ES, FS, and GS registers allow the specification of four data segments, each addressable by the currently executing program. Accessibility to four separate data areas helps programs efficiently access different types of data structures; for example, one data segment register can point to the data structures of the current module, another to the exported data of a higher-level module, another to a dynamically created data structure, and another to data shared with another task. An operand within a data segment is addressed by specifying its offset either directly in an instruction or indirectly via general registers.

Depending on the structure of data (e.g., the way data is parceled into one or more segments), a program may require access to more than four data segments. To access additional segments, the DS, ES, FS, and GS registers can be changed under program control during the course of a program's execution. This simply requires that the program execute an instruction to load the appropriate segment register prior to executing instructions that access the data.
