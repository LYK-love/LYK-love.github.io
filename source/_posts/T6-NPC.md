---
title: T6 NPC
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-08-17 19:37:24
---


Outline：

* **NPC = P ？**
* **NPC判定问题**
* **规约： 等价**

<!--more-->

* 优化问题 → 判定问题： 优化问题往往有某个结构，结构有指标， 给指标选定一个阈值*k*，对*k*做判定

# NPC = P ？

 许多NPC看似是P，但证明是错误的。 即： 目前还无法证明NP = P

* Clique问题的一种错误的规约是“伪Clique问题”，后者是“对给定的k，判断是否存在k顶点的Clique”，该问题是P的。 但是Clique问题的正确表述是“对任意k，判定是否有k顶点的Clique”，即*k*为变量而不是常数，因此Clique问题不是P的。 错误在于**问题的转换**不对。
  * 不过，对NPC的某个参数转变成常数可以将其转化为P,这是一种解NPC的思路

* ChangeCoin代价是$O(nN)$是P, 但它不是NP， 因为在该问题最合理的建模下，数值用k位表示，代价是$O(n2^k)$. 所以**背包问题不是多项式可解​**
* 规约是有代价的（ 如范式间的转换，不一定是P ）
* DNF是多项式可解的，而CNF转换到CNF不是多项式时间的， 所以CNF不是多项式时间可解（不是P）

# NPC判定问题

已知特例为NPC，可以比较容易地判定Genaral是否为NPC, 即： 特例归约到general比较简单。

## Example

* Clique是稠密子图问题的特例，  所以Clique $\leq_P$​​ 稠密子图. 所以稠密子图是NPC
* 已知划分问题是NPC, 它是背包问题的特例， 所以背包问题是NPC

# 归约：等价

* 独立集和点覆盖问题是等价的

  * Proof

    设有独立集I，点覆盖集C,  对G中任意边 e = （u，v），存在点u不属于I（若u，v都属于I，则与独立集矛盾）， 所以u在I的补集中。 即任何一条边，至少有一个点在I的补集中，所以I的补集是C。

* 支配集（Domination Set）与集合覆盖问题是等价的. 
