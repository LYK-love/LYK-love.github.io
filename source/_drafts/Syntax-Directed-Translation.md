---
title: Syntax Directed Translation
tags: Compilers Principles, Techniques, and Tools
categories: Compilers 
mathjax: true
---





o

Outline：

* 语法制导定义
* SDD的求值顺序
* 语法制导翻译的应用
* 

# 语法制导定义

* Syntax-Directed Definition, SDD: 是一个上下文无关文法和**属性**及**规则**的结合
  * SDD惟一确定了语法分析树上每个`non-terminal`节点的属性值
    * SDD没有规定以什么方式、什么顺序计算这些属性值
  * 属性和文法符号关联，规则和`production`关联
    * 如果`X`是文法符号， `a`是`X`的一个属性`X.a`表示a在某个标号为`X`的分析树节点上的值

## 继承属性和综合属性

* `non-terminal`的两种属性：

  * 综合属性: 在分析树节点`N`上的`non-terminal` `A`的综合属性是由`N`上的`production`所关联的语义规则来定义的

    * 这个`production`的`head`一定是`A`

    * 节点`N`上的综合属性只能通过`N`的**子节点**或`N`本身上的属性值来定义

  * 继承属性：在分析树节点`N`上的`non-terminal` `B`的继承属性是由`N`的父节点的产生式所关联的语义规则来定义的

    * 这个`production`的`body`中必然包含符号`B`

    * 节点`N`上的继承属性只能通过`N`的**父节点**、`N`本身和`N`的兄弟节点上的属性值来定义
    * 不允许`N`上的继承属性通过`N`的子节点上的属性值来定义，但允许节点`N`上的综合属性通过节点`N`本身的继承属性来定义

* `terminal`可以具有综合属性，但不能有继承属性。 `terminal`的属性值是由词法分析其提供的词法值，在SDD中没有计算`terminal`的属性值的语义规则
* `依赖图`用于确定一颗给定的语法分析树中各个属性实例之间的依赖关系
