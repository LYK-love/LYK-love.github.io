---
title: Compilers Basic
tags: Compilers
categories: Computer Science
mathjax: true
date: 2022-09-11 01:18:57
---


 Outline:

* Language Processors
* Example: GCC
* Phases Overview
* Front End
* Optimizer
* Back End
* Others

<!--more-->

# Language Processors

All roads lead to the CPU:

![All roads lead to the CPU](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Compilers/Compilers%20Basic/All%20roads%20lead%20to%20the%20CPU.png)



## Compiler

![Compiler](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Compiler.png)

* **compiler** **maps** a source program into a **semantically equivalent** target program
* 整个编译过程可以看成 a sequence of phases, 每个phase将源程序的一种表示转换成另一种表示, 程序的中间表示称为IR( Intermediate representation ). phrases大致分两个:
  1. **Analysis**: 解析源程序, 得到语法树, 根据语法树创建IR, 并收集源程序的信息存入symbol table, 与IR一起传入 synthesis part
     * 可分为: Lexical Analysis, Syntax Analysis, Semantic Analysis
  2. **Synthesis**: 根据中间表示和符号表创建目标代码
* 我们定义phases的组合为“**pass**”, 也就是说, 编译器一共要经过3个pass:
  * Frontend pass: 编译器的Analysis部分, 根据源代码生成IR
  * Optimization: The optimizer is an **ir-to-ir** transformer that tries to improve the ir program in some way. 
  * Backend pass: 编译器的Synthesis部分, 根据IR生成目标代码.
* 如果target language是machine language, 那么用户可以**在机器上直接执行**target program. 从source program生成machine language的典型过程:

![A language processing system](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/A%20language%20processing%20system.png)

### Structure

![The Structure of a Compiler](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/The%20Structure%20of%20a%20Compiler.png)

## Interpreter

解释器不会将一种语言翻译为另一种, 而是直接根据 source language 执行

![Interpreter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Interpreter.png)

* 相比机器执行, 解释器执行起来效率更低, 但是更易于debug

## Hybrid

![Hybrid](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Hybrid.png)

* Java的language processor结合了compiler和interpreter. Java program首先被编译为统一格式的bytecode作为target program, 后者再被放入JVM<u>解释执行</u>.
  * 为了提高速度, 有的Java Compiler采用了JIT( just-in-time ), 在编译时不仅生成字节码, 还把字节码编译为机器码, 然后直接运行机器码的程序.
* 无论是将bytecode解释执行, 还是将其编译为机器吗执行, 都需要“dynamic cimpilation”
* Java is **not** the first language to employ such a mix. **Lisp** systems have long included both native-code compilers and virtual-machine implementation schemes [266, 324]. The **Smalltalk**-80 system used a bytecode distribution and a virtual machine [233]; several implementations added just-in-time compilers [126].

# Example: GCC

[动态链接和静态链接](https://lyk-love.cn/2022/05/05/Static-Link-Dynamic-Link/)

以GCC处理C程序的过程为例:

![Language Process](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Language%20Process.png)

1. **Preprocessor**: *source program* $\rightarrow$  *modified source program*
   * gcc的预处理器`cpp`将`.c`, `.h`文件变成`.i`文件
2. **Compiler**: $\rightarrow$  *target assembly program*
   * GCC的编译器是`cc1`， 它把`.i`文件编译成汇编语言的`.s`文件。
3. **Assembler**: $\rightarrow$   *relocatable machine code*
   * GCC的汇编器是`as`， 它把汇编文件汇编成机器指令文件，并打包成"**可重定向**文件"， 这是个二进制文件，后缀为`.o`
4. **Linker/Loader**: $\rightarrow$  *target machine code*
   * GCC的汇编器是`ld`， 它将上一阶段生成的可重定向文件和系统内已存在的可重定向文件，形成最终的**可执行目标文件**( executable object file )并被loader加载入内存
   * 被链接的可重定向文件**包括`.o`文件, 也包括静态库`.a`和动态库`.so`**)链接起来( 在此期间会将相对地址解析为绝对地址 )

在windows中, 可重定向文件后缀为`obj`, 可执行目标文件后缀为`exe`

# Phases Overview

Symbol Table被所有phase使用



![Phases](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Phases.png)

1. Lexical Analyzer： character stream  $\rightarrow$  token stream
2. Syntax Analyzer：  $\rightarrow$  syntax tree
3. Semantic Analyzer：$\rightarrow$ syntax tree
4. Intermediate Code Generator：$\rightarrow$  intermediate representation
5. Machine-Independent Code Optimizer： $\rightarrow$   intermediate representation
6. Code Generator： $\rightarrow$  target-machine code
7. Machine-Dependent Code Optimizer： $\rightarrow$  target-machine code



## Example

![Phases Example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Phases%20Example.png)



# Front End

The front end determines if the input code is well formed, in terms of **lexicality**,  **syntax** and **semantics**. 

* 我们规定: 语法 = 词法+句法, 即 grammer = lexicality + syntax. 由scanner和parser完成grammer的分析.
* Front ends rely on results from formal language theory and type theory

如果语法和语义都正确, 前端就会生成IR.



以句子“Compilers are engineered objects.” 为例:

## Lexical Analysis

* Lexical Analysis( aka scanning ): 找出词法单元, 并赋予其词性( a part of speech ).  最后生成的词法单元形式为(*p*,*s*), where *p* is the word’s *part of speech* and *s* is its spelling. 

![scanning exp](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/scanning%20exp.png)

## Syntax Analysis

* Syntax Analysis( aka parsing ): 根据给出的语法规则( rule ), 得到derivation:



* rules:

  ![rules](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/rules.png)

  

* derivation:

  ![derivation](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/derivation.png)

  可以看到, 原句的derivation满足了给定的rules, 因此原句在**语法上正确**( grammatically correct )

  

## Semantic Analysis

* Semantic Analysis: 一个语法正确的句子未必是有意义的, 比如: “Rocks are green vegetables” 符合上述的语法, 但是没有意义. 

* 程序语言的语义分析一般比较简单, 主要包括Type check, Object binding等等. Analyser使用语法树和符号表来检查源程序的语义, 使得源程序和目标程序的语义一致. 

  同时会收集类型信息，存入语法树或符号表，用于后续的中间代码生成.

# Optimizer

## Analysis

The analysis determines where the compiler can **safely** and profitably apply the technique. 

Compilers use several kinds of analysis to support transformations:

*  *Data- flow analysis* : reasons, at compile time, about the flow of values at runtime.
* *Dependence analysis* : uses number-theoretic tests to reason about the values that can beassumed by subscript expressions.

## Transformation

Compiler不仅要分析IR, 还要利用分析的结果来将IR转换成更“好”的形式( 比如更快, 更节约空间, 更省电... )

![Transformation](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/Transformation.png)

# Back End

根据IR来generate target-machine code

## Instruction Selection

首先要将IR映射到机器指令:

![Instruction Selection](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/Instruction%20Selection.png)

* This code assumes that a, b, c, and d are located at offsets @a, @b, @c, and @d from an address contained in the register rarp.
* 这里用的汇编语言是ILOC( Intermediate Language for an Optimizing Compiler ), 是一个简化版的汇编
* Virtual register: 在Instruction Selection阶段, Compiler使用虚拟的寄存器, 而不关心机器实际的寄存器.  虚拟寄存器到物理寄存器的映射在**Register Allocation**完成.

## Register Allocation

然后将虚拟寄存器映射到目标机器的物理寄存器. 此时还要考虑一些优化问题. 比如, 下面的例子只使用了“最少的寄存器”:

![image-20220912154656851](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/Register%20Allocation.png)

## Instruction Scheduling

编译器可以对指令重拍序, 甚至删除一些指令, 来提高速度:

![before Instruction Scheduling](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/before%20Instruction%20Scheduling.png)

![after Instruction Scheduling](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/after%20Instruction%20Scheduling.png)

## Interactions Among Code-Generation Components

code-genetaion时会遇到很多问题, 这些问题甚至可能是交错的. 比如, 指令重拍就会导致一些变量的依赖出现更改, 影响寄存器分配.

# Others

编译器的一些其他应用:

* Binary Translation:  把平台的机器码程序翻译到另一个平台. 比如把x86机器码翻译到VLIW平台.
* Hardware Synthesis: 硬件设计使用硬件描述语言: Verilog or VHDL( Very high speed integrated circuit
   Language). 它们工作在 register transfer level( RTL )
* Compiled Simulation: 以前都是先有处理器再有编译器, 现在都是先有编译器, 通过模拟器来模拟一个处理器, 使用compiler来衡量该处理器的性能.( 也就是只要有架构设计就行了, 不需要硬件实现. )

