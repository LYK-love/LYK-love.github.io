---
title: AI Intro 
tags: Machine Learning
categories: Computer Science
mathjax: true
date: 2023-02-08 01:27:25
---

Sources:

1. *Artificial Intelligence A Modern Approach*

<!--more-->

# What is AI

* 强人工智能：think like humans

* 弱人工智能： act rationally
  * 目前的研究都是弱人工智能
* 发展： 达特茅斯会议→ 推理期（60s-70s）→ 知识期(80s初期 - 90s中期) → 学习期（2006）

# What will we learn

* Search  搜索与规划
* knowledge 知识表达与处理
* Uncertainty 不确定建模
* Learning 机器学习

# Agent（智能体）

The **agent function** maps from percept histories to actions:
$$
f: P^* \rarr A
$$


## Agent types

* Simple  reflex agents
  * 简单条件反射，作者把规则写进去
* Reflex agents with state
  * 有记忆能力
* Goal-based agents
  * 没有规则，只有目标
* Utility-based agents
  * 最大化得分

All these can be turned into learning agents

------

* Learning agents
  * 能够生成当下目标（Problem generator）
