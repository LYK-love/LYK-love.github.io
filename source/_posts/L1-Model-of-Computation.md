---
title: L1 Model of Computation
tags: Algorithm design and analysis
categories: Algorithm
date: 2021-07-13 07:19:53
---


<i>There is no whiz, bang effect</i>

<i>That's made up of 1s and 0s</i>

<i>That takes a special talent</i>

<!--more-->

# Computer and Computing

* Computing: 计算机“无所不能”的核心在于`01编解码`,这是<u>使能技术</u>
  * Encoding everything into `0`s and `1`s  
  * Operations over `1`s and `0`s
  * Decoding the `1`s and `0` s
* Turing machine 
  * An abstract/logical computer 
* "**计算**"就是对`01编码`的信息的操作

# Algorithm

* Algorithm is the spirit of computing

  * To solve a specific problem( so called an `algorithmic problem` ) 
  * Combination of basic operations 指挥一个机器做事情,把机器的操作组合好
    * in a precise and elegant way 要清晰,优美

* Essential issues

  * Model of computation

  * Algorithm design
  * Algorithm analysis

# Model of Computation

* Problems
  * Why the algorithms we learn can run  almost everywhere?
  * Why the algorithms we learn can be implemented any language?
* Machine- and language- independent algorithms, running on an **abstract** machine   算法是抽象概念,与机器\语言无关. 抽象的算法依赖于抽象的机器,这就是**计算模型**. 经典计算模型:
  * Turing machine: over-qualify
  * RAM model: simple but power 

## The Ram Model of Computation

*  Each <i>simple operation</i> takes one time step
  * E.g., key comparison, +/-, memory access
* Non_simple operation should be decomposed
  * Loop
  * Subroutine(子过程还可以递归 )
* Memory
  * Memory access is a simple operation 对存储器某个位置的访问和读写被认为是简单操作
  * Unlimited memory 我们认为RAM的内存是无限的
* 由于建模的本质是把不重要的细节抽象掉,把精髓留下来. 所以模型建得越精细,就越难用, 建得越粗糙,丢失的信息越多,就越好用,二者有一个Trade-off. 对于本科阶段,Ram模型够用了

# To Create an Algorithm

* Algorithm design
  * Composition of simple operations, to solve an algorithm problems
* Algorithm analysis
  * Amount of work done / memory used
    * In the worst/ average cases
  * Advanced issues
    * Optimality, approximation ratio, ...

 # Algorithm Analysis

* How to measure

  * Not too general 不能太粗糙

    * Given essential indication in comparison  of algorithms

  * Not too precise 不用那么精确

    * Machine independent
    * Language independent
    * Programing paradigm independent
    * implementation independent

  *  Criteria

    * Critical operation
    * How many critical operation are conducted 数关键操作个数!
    * 算法性能好坏由关键操作决定,辅助性操作与关键操作大致是线性关系. 所以只要关注关键操作
  
* | Algorithm problem                              | Critical operation  |
  | ---------------------------------------------- | ------------------- |
  | Sorting, selection, searching, String matching | Comparison(of keys) |
  | Graph traversal                                | Processing a node   |
  | Matrix multiplication                          | Multiplication      |
  
  

* Amount of work done
  * usually depends on <i>size of the input</i> 输入规模
  * usually does not depends on size of the input only

* Worst -case  Complexity
* Average-case Complexity
* Advanced topics
  * Lower bound(Selection)
  * Optionality(Greedy , DP)
  * Computation complexity
  * Approximate/ online / randomized algothms

