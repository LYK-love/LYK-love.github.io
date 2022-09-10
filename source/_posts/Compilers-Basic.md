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
* Phases
* The Evolution of Programming Languages
* Applications of Compiler Technology
* Programming Language Basicss

<!--more-->

# Language Processors

## Compiler

![Compiler](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Compiler.png)

* **compiler** **maps** a source program into a **semantically equivalent** target program
* 整个编译过程可以看成 a sequence of phases, 每个phase将源程序的一种表示转换成另一种表示, 程序的中间表示称为IR( Intermediate representation ). phrases大致分两个:
  1. **Analysis**: 解析源程序, 得到语法树, 根据语法树创建IR, 并收集源程序的信息存入symbol table, 与IR一起传入 synthesis part
     * 可分为: Lexical Analysis, Syntax Analysis, Semantic Analysis
  2. **Synthesis**: 根据中间表示和符号表创建目标代码
* 编译器的Analysis部分称为Frontend, Synthesis部分称为Backend. 前端根据源代码生成IR, 后段根据IR生成目标代码. 为了提升效率, 前后端之间还会增加Optimizer, 其目的是改进中间生成的IR
  * Optimizer将一种IR转换成另一种IR, 严格来讲它也是一种编译器
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

# Phases

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

## Lexical Analysis

aka *Scanning*

## Syntax Analysis

aka *Parsing*

*  将 token-name 构建为  syntax tree 

## Semantic Analysis

* 语义分析使用语法树和符号表来检查源程序的语义，使得源程序和目标程序的语义一致
* 同时收集类型信息，存入语法树或符号表，用于后续的中间代码生成
  * 会执行 *type checking*，对每个operator检查其operands是否合法。 
    * 语言可能会允许编译器执行一些类型转换

## Intermediate Code Generation

## Code Optimization

* 程序在被翻译为目标代码之前，会被翻译为low -level的中间代码 

## Code Generation

* 优化中间代码，使得能生成更好的目标代码

## The Grouping of Phases into Passes

* 多个phase可以整合为一个pass
  * 前端的词法分析、语法分析、语义分析和中间代码生成可看作一个pass
  * 代码优化是一个optional  pass
  * 后端的目标代码生成是一个pass

* 不同编译器的不同pass可以组合

## Compiler-Construction Tools

* *Parser generators* t h a t automatically produce syntax analyzers from a
  grammatical description of a programming language.
2. *Scanner generators* t h a t produce lexical analyzers from a regular-expres-
sion description of t h e tokens of a language.
3. *Syntax-directed translation engines* ： produce collections of routines
for walking a parse tree and generating intermediate code.
4. *Code-generator generators* ： produce a code generator from a collection
of rules for translating each operation of the intermediate language into
the machine language for a target machine.
5. *Data-flow analysis engines*： facilitate the gathering of information
about how values are transmitted from one p a r t of a program to each
other part. Data-flow analysis is a key part of code optimization.
6. *Compiler-construction toolkits*：  provide an integrated set of routines
for constructing various phases of a compiler.

# The Evolution of Programming Languages
1.3.1 T h e Move to Higher-level Languages
1.3.2 Impacts on Compilers
1.3.3 Exercises for Section 1.3
T h e Science of Building a Compiler
1.4.1 Modeling in Compiler Design and Implementation1.4.2 T h e Science of Code Optimization

# Applications of Compiler Technology
1.5.1 Implementation of High-Level Programming Languages1.5.2
 Optimizations for Computer Architectures
1.5.3 Design of New Computer Architectures
1.5.4 Program Translations
1.5.5 Software Productivity Tools
# Programming Language Basics
1.6.1 The Static/Dynamic Distinction
1.6.2 Environments and States
1.6.3 Static Scope and Block Structure
1.6.4 Explicit Access Control
1.6.5 Dynamic Scope
1.6.6 P a r a m e t e r Passing Mechanisms

1.6.7 Aliasing
1.6.8 Exercises for Section 1.6



* 
