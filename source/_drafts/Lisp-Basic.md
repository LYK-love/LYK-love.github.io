---
title: Lisp Basic
tags: Lisp
categories: Languages
---



*The programmable programming language.*

# Background

Despite the formal Turing equivalence of all programming languages, you really can get more done more quickly in some languages than others and have more fun doing it. 



Lisp " 

read-eval-print loop,

## Origin

The first Lisp interpreter was implemented by **McCarthy** with the help of colleagues and stu- dents in the Artificial Intelligence Group of the `MIT` Research Laboratory of Electronics and in the `MIT` Computation Center in 1956.

Lisp circa 1956 was designed for "symbolic data processing" and derived its name from one of the things it was quite good at: **LISt Processing**. 

## 1980s

During the <u>AI boom</u> of the 1980s, Lisp remained a favorite tool for programmers writing software to solve hard problems such as automated theorem proving, planning and scheduling, and computer vision. These were problems that required a lot of hard-to-write software; to make a dent in them, AI programmers needed a powerful language, and they grew Lisp into the language they needed. 

And the <u>Cold War</u> helped--as the Pentagon poured money into the Defense Advanced Research Projects Agency (DARPA), a lot of it went to folks working on problems such as large-scale battlefield simulations, automated planning, and natural language interfaces. These folks also used Lisp and continued pushing it to do what they needed.

## Now

**Lisp is by now a family of dialects**

* Scheme became an `IEEE` standard in 1990 (IEEE 1990)
* Common Lisp became an `ANSI` standard in 1994 (ANSI 1994).



Differences between Scheme and Comman Lisp:

* Scheme 被设计为一门教学语言, Common Lisp被设计为一门实用的编程语言. Scheme的语法和标准库都尽可能地小, 这样有利于语言本身的形式化处理, 缺点就是过于精简而不如Common Lisp实用

* Scheme过于强调函数式编程和递归, Common Lisp不是. 很多人对Lisp有FP的固有印象, 这其实来源于Scheme.

  



我选择使用Scheme, Scheme的编译器有多种实现:

* Chez Scheme: 最强大的实现, 自带REPL, 拥有最快的编译和执行速度( 跨过汇编直接生成二进制Native Code )

## Chez Scheme

# Why Lisp

Lisp是给科学家而不是程序员用的语言, 所以别指望着用Lisp干活了. 一般来讲学Lisp只有两个原因:

1. 通过Lisp来深入理解PL
2. 学会Lisp之后就可以自由地说“Lisp很垃圾”而不会被Lisp爱好者以“你怎么知道你又没学过”来驳斥

# Materials

* [A Road to Common Lisp](https://stevelosh.com/blog/2018/08/a-road-to-common-lisp/)
* [Practical Common Lisp](https://gigamonkeys.com/book/)
