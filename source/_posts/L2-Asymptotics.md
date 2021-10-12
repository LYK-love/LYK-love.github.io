---
title: L2 Asymptotics
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-07-13 08:54:12
---

Outline: 

* **How to Compare Two Algorithms**
* **Brute  Force  by Iteration**
* **Brute  Force  by Recursion**

<!--more-->

# How to Compare Two Algorithms

* Algorithm analysis, with <i>simplification</i>
  * Measure the cost by the number of **critical operations**
  * Large input size only
  * Essential part only
    * Only the leading term in$ f(n)$ is considered
    * Constant coefficients are ignored
* Capturing the essential part in the cost in a mathematical way
  * Asymptotic **growth rate** of $f(n)$



## Relative Growth Rate

* $O(g):$​​ functions that grows no faster than $g$​
  * $O(g(n))=\{f(n): 存在常数c>0和n_0>0,满足0\leq f(n) \leq cg(n)对所有n \geq n_0均成立\}$​
  * $f(n)=O(g(n)) \quad iff \quad \lim\limits_{n \rarr \infty} \frac{f(n)}{g(n)}=c<\infty$

* $o(g)$: 不快于$g$且与$g$有层次上的差距

  * $o(g(n))=\{f(n): 对任意常数c>0, 均存在常数n_0>0,满足0\leq f(n) < cg(n)对所有n \geq n_0均成立\}$​​​
  * $f(n)=o(g(n)) \quad iff \quad \lim\limits_{n \rarr \infty} \frac{f(n)}{g(n)}=0$​

  

* $\Omega(g)$: functions that grow at least as fast as $g$​

  * $\Omega(g(n))=\{f(n): 存在常数c>0和n_0>0,满足0 \leq cg(n)\leq f(n) 对所有n \geq n_0均成立\}$
  * $f(n)=\Omega(g(n)) \quad iff \quad \lim\limits_{n \rarr \infty} \frac{f(n)}{g(n)}=c>0(c也可以为\infty)$​

* $\omega$: 不慢于$g$且与$g$有层次上的差距

  * $\omega(g(n))=\{f(n): 对任意常数c>0,均存在常数n_0>0,满足0 \leq cg(n) < f(n) 对所有n \geq n_0均成立\}$​
  * $f(n)=\omega(g(n)) \quad iff \quad \lim\limits_{n \rarr \infty} \frac{f(n)}{g(n)}=\infty$​​

  

* $\Theta(g):$​​ ... the same rate as $g$​​. (处于同一水平) ( $O$和$\Omega$的交集 )

  * $\Theta(g(n))=\{f(n): 存在常数c_1>0,c_2>0和n_0>0,满足0 \leq c_1g(n)\leq f(n) \leq c_2g(n) 对所有n \geq n_0均成立\}$
  * $f(n)=\Theta(g(n)) \quad iff \quad \lim\limits_{n \rarr \infty} \frac{f(n)}{g(n)}=c>0(0<c<\infty)$​​



* $\theta$: 不存在， $o$​和$\omega$​的交集是空集

# Brute  Force  by Iteration

* Max-sum Subsequence

  * 蛮力是$O(n^3)$,  改进一下是$O（n^2）$​，用分治改进是$O（nlogn）$

  * A linear Algorithm: O(n)

    ```C++
    ThisSum = MaxSum = 0;
    for( j = 0 ; j < N ; j++ )
    {
    	ThisSum += A[j];
    	if( ThisSum > MaxSum )
    		MaxSum = ThisSum;
    	else if( ThisSum < 0 )
    		ThisSum = 0;
    }
    Return MaxSum
    ```

# Brute  Force  by Recursion

* 蛮力策略大智若愚，可以以此为跳板进行改进

* **Job Scheduling**
  * Brute force recursion
    * Select job 'a'
    * Case 1: the result does not contain 'a'
      * Recursion on $J \setminus \{a\}$​​
    * Case 2: the result contains 'a'
      * Recursion on  $J \setminus \{a\} \setminus \{$​ tasks overlapping with $ a\}$​
  * Further improvements
    * Dynamic programming(L16)
    * Greedy algorithms( L14 )
* **Matrix Chain Multiplication**
  * Solutions
    * Brute force recursion(L16)
      * BF1
      * BF2
    * Dynamic programming(L16)
      * Based on brute force recursion 2

