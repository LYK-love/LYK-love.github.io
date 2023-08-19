---
title: L3 Recursion
tags: 
- Algorithm
categories: 
- Computer Science
date: 2021-07-15 09:52:50
---


Outline

* **Recursion in algorithm design**
  * **The divide and conquer strategy**
  * **Proving the correctness of recursive procedures**
* **Solving recurrence equations**
  * **Some elementary techniques**
  * **Master theorem**

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# Recursion in algorithm design

## Divide and Conquer

```java
The general pattern //分治的伪代码
solve(I)
	n = size(I);
	if(n<=smallSize)
		solution=directlySolve(I)
	else
		divide I into I1, ..., Ik;
		for each i ∈ {1, ..., k}
			Si = solve( Ii );
		solution = combine(S1, ..., Sk)
	return solution
```

* The  BF recursion  蛮力递归
  * Problem size: often decreases linearly
    * "n, n-1, n-2, ..."
* The D & C recursion 分治递归
  * Problem size: often decreases exponentially 指数速度降低
    * "n, n/2, n/4, n/8, ..."



## 笨展开

* `Smooth定理`

## Guess and Prove

* 本质上是数学归纳法

* $T(n)= b T(\frac n c) + f(n)$
  * $b$​ : b个子问题
  * $c$​ : 每个子问题的规模 (  实际的`n/c` 不一定等于`b` )
  *   $f(n)$​ :  包含了划分的代价和combine的代价

## Recursion  Tree

* Node
  * None-leaf
    * Non-recursive cost
    * Recursive cost
  * Leaf
    * Base case
  
* Edge
  * Recursion
  
* Solution by row-sums  (等比序列)
  * Increasing geometric series: 第一个节点
  * Constant: $f(n) . log(n)$ : 每一层加起来是$f(n)$, 总共有$logn$​层
  * Decreasing geometric series: 最后一层节点
  
* **Master Theorem**: Loosening the restrictions on $f(n)$

  令$a$, $b$ 为常数， 且$a \geq1$​和$b>1$, $f(n)$为一定义于非负整数上的函数, $T(n)$为定义于非负整数上的递归函数:
  $$
  T(n)=aT(\frac n b)+f(n)
  $$
  递归式中的$\frac n b$指的是$\lfloor \frac n b  \rfloor$或$\lfloor \lceil \frac n b  \rceil$

  * 如果存在某个常数 $\varepsilon>0$,使得$f(n)=O(n^{log_b^{a-\varepsilon}})$, 则$T(n)=\Theta(n^{log_b a})$​
  * 如果$f(n)=\Theta(n^{log_b a}), 则$$T(n)=\Theta(n^{log_b a}logn)$​
  * 如果存在某个常数 $\varepsilon>0$​​,使得$f(n)=\Omega(n^{log_b^{a+\varepsilon}})$​​, 且存在某个常数$c$​ ( $c<1$​ ), 使得对所有充分大的$n$​, $af(\frac n b) \leq cf(n)$​, 则$T(n)=\Theta(f(n))$​​

  * Master定理未能覆盖所有情况

 
