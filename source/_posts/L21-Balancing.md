---
title: L21 Balancing
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-08-21 11:47:37
---


Outline:

* **找前k大元素**
* **找离medium最近的k个元素**
* **Weighted  medium**
* **找unique**



Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->



# 找前k大元素

（不是第k大）

* $nlogn$: 排序​
* $n+klogn$​​： 建堆，k次`getMax`
* $n+k^2$​​​​：建堆+从堆的前k层里面选k次（共有 $2^k$​​​个元素，对这个堆的`fixHeap`代价是$log2^k=k$​​​,找k次，即$k \times k$​）
* $n+klogk$: 先select出第k大的元素，代价$\Theta(n)$；再以此为partition，对前k个元素排序，代价$\Theta(klogk)$​

# 找离medium最近的k个元素

左界：$L=n/2 - k$

右界: $R=n/2 + k$

* 先 selcect(L)，找出左界的位置，然后partition（L）；对右界同理；最后对中间的部分做操作（方法有很多）

 

# Weighted  medium

$x_1,x_2,\dots,x_n$​两两可比

$w_1,w_2,\dots,w_n$,  $w_i>0$​, ​ $\sum w_i=1$

找出weighted medium $x_k$​, 使得$\sum\limits _{x_i<x_k}w_i < \frac 1 2$​, $ \sum\limits _{x_i > x_k} \leq \frac 1 2$​ （也可以前者$\leq$, 后者$<$,但不能二者都是$\leq$​​）​



* $O(n)$: 先select得到medium（注意，不是 Weighted  medium）； 再以此partition， 算出左右两边的weight，看哪边大于1/2，对子问题递归判断

# 找unique

所有元素只有一个和其他不一样，找出这个元素.

critical operation： compare（a, b）= Y ( a = b ) / N ( a != b)

* 可以用adversary argument 找出下界
