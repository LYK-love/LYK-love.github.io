---
categories:
- Software Engineering
date: 2021-05-14 14:53:56
tags: Database
title: Database Candidate Key
---

Outline:

* 候选键定义
* 求候选键步骤
* 示例

<!--more-->

# 候选键定义

首先来看候选键的定义：若关系中的某一属性组的值能唯一地标识一个元组，则称该属性组为候选键。

若W是候选键，则必须满足两个条件：W的闭包是U；W没有冗余。

设关系模式R中U=ABC.......等N个属性，U中的属性在FD中有四种范围：

(1)左右出现;
(2)只在左部出现;
(3)只在右部出现;
(4)不在左右出现;

# 求候选键步骤

按以下步骤求候选键：
1.只在FD右部出现的属性，不属于候选码;
2.只在FD左部出现的属性，一定存在于某候选码当中;
3.外部属性一定存在于任何候选码当中;
4.其他属性逐个与2,3的属性组合，求属性闭包，直至X的闭包等于U,若等于U,则X为候选码。

# 示例

例1：R<U,F>,U=(A,B,C,D,E,G),F={AB-->C,CD-->E,E-->A.A-->G},求候选码。

  因G只在右边出现,所以G一定不属于候选码;而B,D只在左边出现,所以B,D一定属于候选码;BD的闭包还是BD,则对BD进行组合,除了G以外,BD可以跟A,C,E进行组合
  先看ABD
  ABD本身自包ABD,而AB-->C,CD-->E,A-->G,所以ABD的闭包为ABDCEG=U
  再看BDC
  CD-->E,E-->A,A-->G,BDC本身自包,所以BDC的闭包为BDCEAG=U
  最后看BDE
  E-->A,A-->G,AB-->C,BDE本身自包,所以BDE的闭包为BDEAGC=U

  因为(ABD)、(BCD)、(BDE)的闭包都是ABCDEG所以本问题的候选码有3个分别是ABC、BCD和BDE

 

例2：R<U,F>,U=(A,B,C),F={AB-->C,C-->B},求候选码。

因为A只出现在左边，所以A一定是候选键。A的闭包还是A，则对A进行组合，可以和B,C进行组合。

首先看AB，AB本身自包AB，而AB-->C，所以AB的闭包是ABC=U。

再看AC，AC本身自包AC，而C-->B，所以AC的闭包是ABC=U。

因为AB,AC的闭包都是ABC，也就是U，所以候选键是AB，AC。