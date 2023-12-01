---
title: Symbol Convention in Statistics
tags:
  - Probability Theory
  - Statistics
categories: Mathematics
mathjax: true
date: 2023-10-15 00:13:25
---




在不同的统计学(包括概率论, 信息论, 随机过程)教材中常常会见到不同的符号约定, 这里整理一下并作出说明.

<!--more-->

# Symbol Convention

给定一个随机试验, 它由概率空间 $(\Omega, \mathcal{F}, \mathbb{P})$ 所定义[^1]. 但一般来说, 我们会使用随机变量将概率空间转化为 $\left(\mathbb{R}, \mathcal B, \mu_X\right)$ 以方便数学处理[^2].

## Alphabet

假设我们使用随机变量$X, Y$ 将$\Omega$中的一个个outcome映射到$\mathbb R$, 我们通常会互换地使用如下符号:

* 随机变量均采用字母表最后几个大写字母(例如$X, Y, Z$)命名, 不会用 $A, B, a, b, x, y, \cdots$ 来命名.

## Random Variable

* rv: **r**andom **v**ariable. 随机变量均采用字母表最后几个大写字母(例如$X, Y, Z$)命名, 不会用 $A, B, a, b, x, y, \cdots$ 来命名.

* A **stochastic process** $X^n$ or $\{X_i\}^n$ is an indexed sequence of $n$ random variables $X_i$:
  $$
  X^n = (X_1, X_2, \cdots, X^n{})
  $$

  * In general, **there can be an arbitrary dependence** among the random variables.
  * $\operatorname{Pr}\left\{\left(X_1, X_2, \ldots, X_n\right)=\left(x_1, x_2, \ldots, x_n\right)\right\}=p\left(x_1, x_2, \ldots, x_n\right).$

## PMF

* $\mathbb P$: the probability measurement funcition, also denoted as $p, \text{Pr}, Pr, \text{P}, P$.

  * 类似的, 各种大写字母符号和其`\mathbb`版本也是互换的, 比如随机变量$X$的数学期望$E(X) \triangleq \mathbb E(X)$.

* 概率度量函数$\mathbb P(E)$的参数$E$是**事件**(event), $E \in \mathcal F$. 在概率空间$\left(\mathbb{R}, \mathcal B, \mu_X\right)$ 中, $B$ 就是一个事件($B \in \mathcal B$), 因此有$\mu_X(B)$. 同样的, 如果随机变量$X, Y$的取值为$\mathcal X, \mathcal Y$, 那么$\mathcal X, \mathcal Y$也就是新的事件空间, 其中的元素$x \in \mathcal X, y \in \mathcal Y$也是事件, 因此有$\mathbb P(x), \mathbb P(y)$. 

* 当然了, 我们总是用statement来定义事件, 比如用$X=x$这个statement指代事件$x$, 因此$\mathbb P(X=x) \triangleq \mathbb P(x)$.

  * $p(x)$ is the short hand for $\mathbb P(x), p(X = x), p_X(x), \mu_X(x), \mu_X(B)$.
  * $p(x|y)$ is the short hand for $p(X = x|Y = y)$.

* 有时参数的圆括号会被写成方括号: $p(X=x) \triangleq p[X=x]$/

## PDF

* $p(X)$ or $p_X$: 随机变量$X$的概率分布函数. 因此, 
  $$
  X \sim p(X) \triangleq X \sim p_X
  $$ {\}

  1. 作者把$X$定义为一个事件, 这是个bad practice, 也很少见到. 事件一般都命名为$A,B,E$之类的.

  2. $p(X)$仅仅是一个运算时的过渡写法, 本身没有什么意义. 比如Shannon Entropy的定义:

     
     $$
     H(X)=\mathbb{E}\left[\log _2 \frac{1}{p(X)}\right]=\sum_x p(x) \log _2 \frac{1}{p(x)} .
     $$
     这里的 $p(X)$ 只是一个过渡的写法, 意思就类似于“$X$的所有取值$x \in \mathcal X$”, 是为了后面的$\sum_x p(x) \log _2 \frac{1}{p(x)}$服务的. **不要死磕 $p(X)$ 的意义.**

## Abbrevation

* `w.p.`: **with probability**.
* 

[^1]: https://lyk-love.cn/2023/10/14/probability-spaces/#probability-space
[^2]: https://lyk-love.cn/2023/10/14/random-variables/#nature-of-random-variable
