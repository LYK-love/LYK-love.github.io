---
title: Finite Machine
tags: Compilers
categories: Computer Science
mathjax: true
date: 2022-09-11 00:15:27
---


Outline:

* Intro
* NFA
* DFA

<!--more-->

# Intro

Finite-state machines can model a large number of problems, among which are **electronic design automation**,**communication protocol design**, **parsing** and other engineering applications.

FA和状态转换图本质上相同

NFA, DFA, RE是等价的

# NFA

## Def

NFA( 不确定性有限状态机 ) 是一个五元组 A = (Σ, $S$, $s_0$ , δ, F ):

1. 字母表  $\sum$  ( $\epsilon \notin \sum$ )
2. 有穷的状态集合 S
3. 唯一的初始状态 $s_0 \in S$ 
4. 状态转移函数 δ
   * $δ : S × (Σ ∪ {ε}) → 2^S$
   * 这里$2^S$定义为$S$的幂集
5. 接受状态集合 $F \subseteq   S$

## Language

* 由一个NFA $A$定义(接受)的语言是从开始状态到某个接受状态的所有路径上的符号串集合，称为$L(A)$

- 一个NFA接受输入字符串x，当且仅当对应的 转换图中存在一条从开始状态到某个接受状态 的路径，使得该路径中各条边上的标号组成符 号串x (路径中可能包含ε边)
- 只要存在从开始状态到接受状态的路径，符号串就认为被NFA接受
- 约定: 所有没有对应出边的字符默认指向一个不存在的 `dead state` 

# DFA

## Def

一个NFA被称为DFA，如果:

* 没有$\epsilon$之上的转换动作, 即标记为$\epsilon$的边, 即$δ : S × (\sum) → 2^S$
* 对于每个状态s和每个输入符号a, 有且只有一条标号为a的边
