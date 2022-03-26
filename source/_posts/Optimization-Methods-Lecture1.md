---
title: Optimization Methods- Lecture1
tags: Optimization Methods
categories: Mathematics
mathjax: true
date: 2021-09-07 21:47:40
---

ref: [Optimization Methods](http://www.lamda.nju.edu.cn/chengq/course/opt2021/opt2021.html)

Outline:

* **Mathematical Optimization**
* **Least-squares**
* **Linear Programming**
* **Convex Optimization**
* **Nonlinear Optimization**
* **Summary**

<!--more-->

# Mathematical Optimization

* **Optimization Problem**
  $$
  min \quad \quad f_0(x) \\
  s.t. \quad f_i(x) \leq b_i, \quad i=1,2,\dots,n
  $$

  * Optimization Variable: $x=(x_1,\dots,x_n)$
  * Objective Function: $f_0:R^n \rarr R$
  *  Constraint Functions: $f_i:R^n \rarr R$​

* $x^*$​ is called **optimal** or a solution

  * $f_i(x^*)\leq b_i$ , $i=1,\dots,m $
  * For any $z$ with $f_i(z)\leq b_i $, we have $f_0(z)\geq f_0(x^*)$

----

* **Linear Program**  线性函数的定义
  $$
  f_i(\alpha x + \beta y) = \alpha f_i(x) + \beta f_i(y)
  $$

  * For all $x,y \in R^n$ and all $\alpha, \beta \in R$​
  * $i$​ 可以为$0$​（目标函数）， 也可以为$1,2,\dots,n$​​​​( 约束函数 )。 当优化问题的目标函数和约束函数都是线性函数时， 整个问题称为**线性规划（线性问题）**

* **Nonlinear Program**

  * If the Optimization Problem is not linear

* **Convex Optimization Problem** 
  $$
  f_i(\alpha x + \beta y) \leq \alpha f_i(x) + \beta f_i(y)
  $$

  * For all $x,y \in R^n$​ and all $\alpha, \beta \in R$​ with $\alpha + \beta=1, \alpha \geq 0, \beta \geq 0$

  * 线性规划是凸优化的一个特例
    * 只要求对$\alpha + \beta=1, \alpha \geq 0, \beta \geq 0$的$\alpha, \beta$成立， 实际上把条件放松了​

## Applications

$$
min \quad \quad f_0(x) \\
s.t. \quad f_i(x) \leq b_i, \quad i=1,2,\dots,n
$$



* **Abstraction**
  * $x$​ represents the choice made 
  * $f_i(x) \leq b_i$ represent firm requirements that limit the possible choices
  * $f_0(x)$​ represents the cost of choosing
  * A solution corresponds to a choice that has minimum cost, among all choices that meet the requirements

### Portfolio Optimization

* **Variables**
  * $x_i$ represents the investment in the $𝑖_th$ asset
  * $x \in R$​ describes the overall portfolio allocation across the set of asset

* **Constraints**
  * A limit on the budget the requirement
  * Investments are nonnegative
  * A minimum acceptable value of expected return for the whole portfolio
* Objective 
  * Minimize the variance of the portfolio return 投资的回报最稳定（ 也可以把目标换成期望的回报最高 ）

### Device Sizing

* **Variables** 
  * $x \in R^n$​  describes the widths and lengths of the devices
* **Constraints**  
  * Limits on the device 
  * Timing 
  * A limit on the total area of the circuit
* Objective 
  * Minimize the total power consumed by the circuit

### Data Fitting

* **Variables** 
  * $x \in R^n$ describes parameters in the model
* **Constraints** 
  *  Prior information 
  * Required limits on the parameters (such as nonnegativity)
* Objective 
  * Minimize the prediction error between the observed data and the values predicted by the model

## Solving Optimization Problems

* **General Optimization Problem** 
  * Very difficult to solve 
  * Constraints can be very complicated, the number of variables can be very large 约束复杂， 变量多
  * Methods involve some compromise, e.g., computation time, or suboptimal solution
* **Exceptions** 
  * Least-squares problems 
  *  Linear programming problems 
  *  Convex optimization problems

# **Least-squares**

* **The Problem**
  $$
  min \quad ||Ax-b||_2^2 = \sum_{i=1}^k { (a_i^T x - b_i)^2 }
  $$

  * $A \in R^{k \times n}$​ ,  $a_i^T$​ is the $i_{th}$​ row of $A,b \in R^k$​
  * $A \in R^n$​ is the optimization variable​

* **Setting the gradient to be 0**
  $$
  2A^T(Ax-b)=0 \\
  \rarr \quad A^TAx = A^Tb \\
  \rarr \quad x = (A^TA)^{-1}A^Tb
  $$

---

* **A Set of Linear Equations**
  $$
  A^TAx = A^Tb
  $$

* **Solving least-squares problems** 
  * Reliable and efficient algorithms and software
  * Computation time proportional to $n^2k( A \in R^{k \times n})$ ; less if structured
  *  A mature technology 
  * Challenging for **extremely large** problems

## Using Least-squares

* **Easy to Recognize** 

* **Weighted least-squares**
  $$
  \sum\limits_{i=1}^k w_i( a_i^Tx-b_i )^2
  $$
  把$w_i$移到括号里就是标准最小二乘

  * Different importance

* **Different importance**
  $$
  \sum\limits_{i=1}^k ( a_i^Tx-b_i )^2 + \rho \sum\limits_{i=1}^n x_i^2
  $$
  也可化为标准最小二乘

  * More stable，避免过拟合

# **Linear Programming**

* **The Problem**
  $$
  min \quad c^Tx \\
  s.t. \quad a_i^Tx \leq b_i, \quad i = 1, \dots, m
  $$

  * $c,a_1,\dots,a_m \in R^n, b_1, \dots, b_m \in R$

* **Solving Linear Programs**
  * No analytical formula for solution 
  * Reliable and efficient algorithms and software 
  * Computation time proportional to $𝑛^2𝑚$ if $ m \geq 𝑛$; less with structure
  * A mature technology 
  * Challenging for **extremely large** problems

## Using Linear Programming

* **Not as easy to recognize** 
*  **Chebyshev Approximation Problem**

$$
min \quad \max\limits_{i=1,\dots,k} |a_i^Tx-b_i| \\
\iff min \quad t \quad \quad \quad s.t. \quad t = \max\limits_{i=1,\dots,k} |a_i^Tx-b_i| \\
  \quad\quad  \quad \iff min \quad t \quad \quad \quad s.t. \quad t \geq  |a_i^Tx-b_i|, {i=1,\dots,k} ( 因为最小化，所以可以等价 )\\
 \quad \quad \quad\iff min \quad t \quad \quad \quad s.t. \quad t \geq  |a_i^Tx-b_i|, {i=1,\dots,k} \\
 \quad \quad \quad \quad \quad \iff min \quad t \quad \quad \quad s.t. \quad -t \leq  a_i^Tx-b_i \leq t, {i=1,\dots,k} \\
$$

# Convex Optimization

* **Local minimizers are also global minimizers**

* The Problem
  $$
  f_i(\alpha x + \beta y) \leq \alpha f_i(x) + \beta f_i(y)
  $$

  * For all $x,y \in R^n$ and all $\alpha, \beta \in R$ with $\alpha + \beta=1, \alpha \geq 0, \beta \geq 0$

  * Least-squares and linear programs as special cases

---

## Solving Convex Optimization Problems

* No analytical solution 
* Reliable and efficient algorithms (e.g., interior-point methods)
* Computation time (roughly) proportional to $\max\{n^3,n^2m,F\}$​
  * $F$ is cost of evaluating $f_i$​'s and their first and second derivatives
* **Almost** a technology

---

* **Often difficult to recognize**
* **Many tricks for transforming problems into convex form**
* **Surprisingly many problems can be solved via convex optimization**

# **Nonlinear Optimization**

* An optimization problem when the objective or constraint functions are not linear, but not known to be convex
* Sadly, there are no effective methods for solving the general nonlinear programming problem 
  * Could be NP-hard
* We need **compromise**

## Local Optimization Methods
* Find a point that minimizes $f_0$ among feasible points near it 
  * The compromise is to give up seeking the optimal $x$
* Fast, can handle large problems 
  * Differentiability
* Require initial guess 
* Provide no information about distance to (global) optimum
* Local optimization methods are more art **than technology**
  * 全凭运气

## Global Optimization

* **Find the global solution** 
  * The compromise is efficiency
* **Worst-case complexity grows exponentially with problem size**
*  **Applications** 
  *  A small number of variables, where computing time is not critical
  *  The value of finding the true global solution is very high

---

* **Worst-case Analysis of a high value or safety-critical system** 
  * Variables represent uncertain parameters 
  * Objective function is a utility function 
  * Constraints represent prior knowledge 
  * If the worst-case value is acceptable, we can certify the system as safe or reliable 能证明系统可靠
* **Local optimization methods can be tried** 
  * If finding values that yield unacceptable performance, then the system is not reliable 局部优化已经发现了不可接受的值，那系统就不可靠
  * But it cannot certify the system as reliable 只能证明系统不可靠，不能证明可靠

## Role of Convex Optimization in Nonconvex Problems

* **Initialization for local optimization** 
  * An approximate, but convex, formulation
* **Convex heuristics for nonconvex optimization** 
  * Sparse solutions (compressive sensing)
* **Bounds for global optimization** 通过凸优化来找全局优化问题的下界
  * Relaxation 把条件松弛
  * Lagrangian relaxation
