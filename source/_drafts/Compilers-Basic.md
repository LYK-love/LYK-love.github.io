---
title: Compilers Basic
tags: Compilers
categories: Computer Science
mathjax: true
---

 龙书来啦，学无止境！

<!--more-->

# Intro

## Compiler && Interpreter

* **compiler** : 将用 source language 编写的原程序翻译为 target language 编写的目标程序

  * source  program  $\rarr$ Compiler  $\rarr$  target  program
  * 如果翻译成了机器语言，那么可以直接执行： input  $\rarr$ Target Program  $\rarr$ output 
  * 翻译过程中，需要报告原程序错误
  * example： 
    *  JIT：just-in-time compilers, translate the bytecodes into machine language
       immediately before they run the intermediate program to process the input.

* **interpreter** ：不会生成目标程序，而是将原程序和input的输出直接执行

  * source program + input  $\rarr$ program interpreter $ \rarr$  target  $\rarr$  program

  

## Language Processors

[动态链接和静态链接](https://lyk-love.cn/2022/05/05/Static-Link-Dynamic-Link/)

以GCC处理C程序为例:

![Language Process](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Compilers%20Basic/Language%20Process.png)

1. **Preprocessor**: *source program* $ \rarr$ *modified source program*
   * gcc的预处理器`cpp`将`.c`, `.h`文件变成`.i`文件
2. **Compiler**: $ \rarr$ *target assembly program*
   * GCC的编译器是`cc1`， 它把`.i`文件编译成汇编语言的`.s`文件。
3. **Assembler**:$ \rarr$  *relocatable machine code*
   * GCC的汇编器是`as`， 它把汇编文件汇编成机器指令文件，并打包成"**可重定向**文件"， 这是个二进制文件，后缀为`.o`
4. **Linker/Loader**: $ \rarr$ *target machine code*
   * GCC的汇编器是`ld`， 它将上一阶段生成的可重定向文件和系统内已存在的可重定向文件，形成最终的**可执行目标文件**( executable object file )并被loader加载入内存
   * 被链接的可重定向文件**包括`.o`文件, 也包括静态库`.a`和动态库`.so`**)链接起来( 在此期间会将相对地址解析为绝对地址 )

在window中, 可重定向文件后缀为`obj`, 可执行目标文件后缀为`exe`

# The Structure of a Compiler

 A compiler as a single box that **maps** a source program into a **semantically equivalent** target,  there are two parts to this mapping: **analysis** and **synthesis**. 

* analysis: 解析源程序，得到语法树，根据语法树创建  intermediate representation，并收集源程序的信息存入symbol table, 与 intermediate representation 一起传入 synthesis part

  * front end

* synthesis: 根据中间表示和符号表创建目标程序

  * back end

* 事实上，整个编译过程可以看成 a sequence of phases, 每个phase将源程序的一种表示转换成另一种表示，phase分为：

  1. Lexical Analyzer： character stream  $\rarr$  token stream
  2. Syntax Analyzer：   $\rarr$ syntax tree
  3. Semantic Analyzer：   $\rarr$  syntax tree
  4. Intermediate Code Generator：    $\rarr$  intermediate representation
  5. Machine-Independent Code Optimizer：   $\rarr$  intermediate representation
  6. Code Generator：   $\rarr$  target-machine code
  7. Machine-Dependent Code Optimizer：  $\rarr$  target-machine code

  * Symbol Table被所有phase使用



## Lexical Analysis

* 将源程序按字符流读入，将字符整合为有意义的序列，称为 *lexemes* ， lexeme再转化成*token*
  * token : *( token-name, attribute-value )*
  * token-name用于语法分析， attribute-value 指向符号表的一项，用于语义分析和代码生成

##  Syntax Analysis

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

# Summary of Chapter 1
