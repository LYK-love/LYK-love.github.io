---
title: Instruction Set Architectures
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 21:31:48
---


Sources:

1. John L. Hennessy & David A. Patterson. (2019). *Chapter 2. Memory Hierarchy Design. Computer Architecture: A Quantitative Approach* (6th ed., pp. 78-148). Elsevier Inc.
2. [RISC-V instruction format](https://jlpteaching.github.io/comparch/img/riscv-instr.pdf)
3. [ECS201A: ISAs and Machine Representation](https://jlpteaching.github.io/comparch/modules/processor%20architecture/isa/)

<!--more-->

# Instruction set architectures

Instruction set architectures (ISA) is a contract between **hardware** and **software**.

* Instruction format specifies: instruction format, virtual memory, number of registers, size of registers, exception, and etc.

## Architecture, microarchitecture and technology

* Architecture: In Computer Architecture context, the term *architecture* refers to the interface as seen by the programmer. ISA belongs to architecture.
* Microarchitecture: the hardware implementation of the architecture (specifically, the **ISA**). The study of microarchitecture would include topics like pipelining,  instruction-level parallelism (ILP), out-of-order execution, speculative  execution, branch prediction and caching.
* Techonology: In Computer Architecture context, the term *technology* refers to transistors and process technology.



The cache coherence protocol (the implementation of how the caches are kept transparent to the programmer) is part of the <u>microarchitecture</u>. It is primarily implemented in hardware.



The memory consistency model (the details of how loads and stores are ordered in a program) is part of the <u>architecture</u>.

# Features of ISAs

Nearly all ISAs today are classified as **general-purpose register architectures**, where <u>the operands are either registers or memory locations</u>. The 80x86 has 16 general-purpose registers and 16 that can hold floating-point data, while RISC-V has 32 general-purpose and 32 floating-point registers.

Virtually all ISAS use <u>byte</u> addressing to access memory operands.



ISAs can be classified by following perspectives:

1. Whether can instructions access memory <u>directly</u>:

   1. **register-memory** ISAs: one example is the 80x86, which can access memory as part of many instructions
   2. **load-store** ISAs: two examples are ARMv8 and RISC-V, which can access memory only with load or store instructions. 
      * All ISAs announced since 1985 are load-store.

2. Whether the memory addressing is aligned: Some architectures, like ARMv8, require that objects **must be aligned**. An access to an object of size $s$ bytes at byte address $A$ is aligned if $A \mod s = 0$. 

   The 80x86 and RISC-V **do not require** alignment, but accesses are **generally faster if operands are aligned**.

3. Addressing modes: In addition to specifying registers and constant operands, addressing modes specify the address of a memory object. RISC-V addressing modes are:

   1. Register, 
   2. Immediate (for constants), and 
   3. Displacement, where a constant offset is added to a register to form the memory address. 

   The 80x86 supports those three modes, plus three variations of displacement: no register (absolute), two registers (based indexed with displacement), and two registers.

4. Formats: There are two basic choices: fixed length and variable length. 

   1. **All ARMv8 and RISC-V instructions are 32 bits long**, which simplifies instruction decoding. See Figure 1.7.
   2. The 80x86 encoding is variable length, ranging from 1 to 18 bytes

5. Operations: The general categories of operations are 

   1. data transfer, 
   2. arithmetic logical, 
   3. control (discussed next), and 
   4. floating point. 

   [This table]() summarizes the integer RISC-V ISA, and [this table]() lists the floating-point ISA. 

   The 80x86 has a much richer and larger set of operations.

## RISC

* Reduced instruction set computing (RISC)
  1. Small number of instructions.
  2. Load/store architecture.
  3. Operating on two operands.
  4. Greatly simplifies implementation of allowed for higher frequency.

## CISC

* Complex instruction set computing (CISC)
  * Many instructions --> instructions are broken into sub-operations (micro code) by hardware

# RISC-V

RISC-V is a simple and easy-to-pipeline instruction set architecture, and it is representative of the RISC architectures being used in 2017. 

## Registers

RISC-V registers, names, usage, and calling conventions:

| Register | Name                        | Use                                 | Saver  |
| -------- | --------------------------- | ----------------------------------- | ------ |
| x0       | zero                        | The constant value 0                | N.A.   |
| x1       | ra                          | Return address                      | Caller |
| x2       | sp                          | Stack pointer                       | Callee |
| x3       | gp                          | Global pointer                      | -      |
| x4       | tp                          | Thread pointer                      | -      |
| x5-x7    | t0-t2                       | Temporaries                         | Caller |
| x8       | s0 / fp                     | Saved register/frame pointer        | Callee |
| x9       | s1                          | Saved register                      | Callee |
| x10-x11  | $\mathrm{a} 0-\mathrm{a} 1$ | Function arguments/return values    | Caller |
| x12-x17  | a2-a7                       | Function arguments                  | Caller |
| x18-x27  | s2-s11                      | Saved registers                     | Callee |
| x28-x31  | t3-t6                       | Temporaries                         | Caller |
| f0-f7    | ft0-ft7                     | FP temporaries                      | Caller |
| f8-f9    | fs0-fs1                     | FP saved registers                  | Callee |
| f10-f11  | fa0-fa1                     | FP function arguments/return values | Caller |
| f12-f17  | fa2-fa7                     | FP function arguments               | Caller |
| f18-f27  | fs2-fs11                    | FP saved registers                  | Callee |
| f28-f31  | ft8-ft11                    | FP temporaries                      | Caller |

RISC-V has 32 general-purpose registers (`x0-x31`), and 32 floating-point registers (`f0-f31`) that can hold either a 32-bit single-precision number or a 64-bit double-precision number. 

The registers that are preserved across a procedure call are labeled "Callee" saved.

## Instruction formats

![Figure 1.7 The base RISC-V ISA formats. ](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Instruction%20Set%20Architectures/Figure%201.7%20The%20base%20RISC-V%20ISA%20formats.png)

All instructions are 32 bits long.

All registers are referenced by 5 bits.

Types:

1. The R format is for integer register-to-register operations, such as ADD, SUB, and so on. 
2. The I format is for loads and immediate operations, such as LD and ADDI. 
3. The B format is for branches and 
   * The immediate is disrupted, so it will be decoded when the CPU executes  in the future. After decoding, the CPU needs to restore the disrupted  immediate in order. For example, when the CPU gets a B-type instruction, the immediate in it is scrambled, and the CPU needs to arrange the  immediate in the order of 12-1 to restore the immediate.
4. the J format is for jumps and link. 
   * The immediate of J-type is **signed** and also disrupted. That means that the CPU must  first put the immediate numbers together to restore the original  immediate numbers when decoding.
5. The S format is for stores. Having a separate format for stores allows the three register specifiers (rd, rs1, rs2) to always be in the same location in all formats. 
6. The U format is for the wide immediate instructions (LUI, AUIPC).



# Insturction type

RISC-V has a base set of instructions (R64I) and offers optional extensions: multiply-divide (RVM), single-precision floating point (RVF), double-precision floating point (RVD). 

## Integer insturction types

This table includes R64I and RVM:

| Instruction type/opcode                       | Instruction meaning                                          |
| --------------------------------------------- | ------------------------------------------------------------ |
| Data transfers                                | Move data between registers and memory, or between the integer and FP or special registers; only memory address mode is 12-bit displacement + contents of a GPR |
| `1b, 1bu, sb`                                 | Load byte, load byte unsigned, store byte (to/from integer registers) |
| `1h, 1hu, sh`                                 | Load half word, load half word unsigned, store half word (to/from integer registers) |
| `1w, 1wu, sw`                                 | Load word, load word unsigned, store word (to/from integer registers) |
| `1d, sd`                                      | Load double word, store double word (to/from integer registers) |
| `f1w, f1d, fsw, fsd`                          | Load SP float, load DP float, store SP float, store DP float |
| `fmv..x, fmv.x.`                              | Copy from/to integer register to/from floating-point register; "-"=S for single-precision, D for double-precision |
| `csrrw, csrrwi, csrrs, csrrsi, csrrc, csrrci` | Read counters and write status registers, which include counters: clock cycles, time, instructions retired |
| Arithmetic/logical                            | Operations on integer or logical data in GPRs                |
| `add, addi, addw, addiw`                      | Add, add immediate (all immediates are 12 bits), add 32-bits only & sign-extend to 64 bits, add immediate 32-bits only |
| `sub, subw`                                   | Subtract, subtract 32-bits only                              |
| `mul, mulw, mulh, mulhsu, mulhu`              | Multiply, multiply 32-bits only, multiply upper half, multiply upper half signed-unsigned, multiply upper half unsigned |
| `div, divu, rem, remu`                        | Divide, divide unsigned, remainder, remainder unsigned       |
| `divw, divuw, remw, remuw`                    | Divide and remainder: as previously, but divide only lower 32-bits, producing 32-bit sign-extended result |
| `and, andi`                                   | And, and immediate                                           |
| `or, ori, xor, xori`                          | Or, or immediate, exclusive or, exclusive or immediate       |
| `lui`                                         | Load upper immediate; loads bits 31-12 of register with immediate, then sign-extends |
| `auipc`                                       | Adds immediate in bits 31-12 with zeros in lower bits to PC; used with JALR to transfer control to any 32-bit address |
| `sll, slli, srl, srli, sra, srai`             | Shifts: shift left logical, right logical, right arithmetic; both variable and immediate forms |
| `sllw, slliw, srlw, srliw, sraw, sraiw`       | Shifts: as previously, but shift lower 32-bits, producing 32-bit sign-extended result |
| `slt, slti, sltu, sltiu`                      | Set less than, set less than immediate, signed and unsigned  |
| Control                                       | Conditional branches and jumps; PC-relative or through register |
| `beq, bne, blt, bge, bltu, bgeu`              | Branch GPR equal/not equal; less than; greater than or equal, signed and unsigned |
| `jal, jalr`                                   | Jump and link: save PC+4, target is PC-relative (JAL) or a register (JALR); if specify X0 as destination register, then acts as a simple jump |
| `ecall`                                       | Make a request to the supporting execution environment, which is usually an OS |
| `ebreak`                                      | Debuggers used to cause control to be transferred back to a debugging environment |
| `fence, fence.i`                              | Synchronize threads to guarantee ordering of memory accesses; synchronize instructions and data for stores to instruction memory |

* **JAL (Jump and Link):**: The "jal" instruction also performs an unconditional jump like "j," but it additionally stores the return address in a register..

  It allows a subroutine to jump to a target address and then return back  to the original caller by using the stored return address.

# Floating point insturction types

This table includes R64I, RVF and RVD. 

| Instruction type/opcode                | Instruction meaning                                          |
| -------------------------------------- | ------------------------------------------------------------ |
| Floating point                         | FP operations on DP and SP formats                           |
| `fadd.d, fadd.s`                       | Add DP, SP numbers                                           |
| `fsub.d, fsub.s`                       | Subtract DP, SP numbers                                      |
| `fmul.d, fmul.s`                       | Multiply DP, SP floating point                               |
| `fmadd.d, fmadd.s, fnmadd.d, fnmadd.s` | Multiply-add DP, SP numbers; negative multiply-add DP, SP numbers |
| `fmsub.d, fmsub.s, fnmsub.d, fnmsub.s` | Multiply-sub DP, SP numbers; negative multiply-sub DP, SP numbers |
| `fdiv.d, fdiv.s`                       | Divide DP, SP floating point                                 |
| `fsqrt.d, fsqrt.s`                     | Square root DP, SP floating point                            |
| `fmax.d, fmax.s, fmin.d, fmin.s`       | Maximum and minimum DP, SP floating point                    |
| Convert instructions                   | Convert instructions: FCVT. x. y converts from type x to type y, where x and y are L (64-bit integer), W (32-bit integer), D (DP), or S (SP). Integers can be unsigned (U) |
| `feq._,flt.,fle.-`                     | Floating-point compare between floating-point registers and record the Boolean result in integer register; "-" =S for single-precision, D for double-precision |
| `fclass.d, fclass.s`                   | Writes to integer register a 10-bit mask that indicates the class of the floating-point number (-∞, +∞, -0, +0, NaN, ...) |
| `fsgnj._, fsgnjn._, fsgnjx.-`          | Sign-injection instructions that changes only the sign bit: copy sign bit from other source, the opposite of sign bit of other source, XOR of the 2 sign bits |
