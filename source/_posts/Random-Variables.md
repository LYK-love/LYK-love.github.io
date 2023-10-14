---
title: Random Variables
tags: Probability Theory
categories: Mathematics
mathjax: true
date: 2023-10-14 01:15:03
---

Ref:

1. [NOTES ON PROBABILITY by Greg Lawler](https://www.math.uchicago.edu/~lawler/probnotes.pdf)
2. [Probability_Theory by Kyle Siegrist](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/02%3A_Probability_Spaces)
3. [The Book of Statistical Proofs](https://statproofbook.github.io/)

<!--more-->


# Random Variable

> The term 'random variable' can be misleading as it is not actually random nor a variable, but rather it is a [function](https://en.wikipedia.org/wiki/Function_(mathematics)).

**Definition:** A random variable $X$ is a measurable **function** from a probability space $(\Omega, \mathcal{F}, \mathbb{P})$ to the real numbers $\mathbb{R}$[^1], i.e., it is a function
$$
X: \Omega \longrightarrow(-\infty, \infty)
$$
such that for every Borel set $B$,
$$
X^{-1}(B)=\{X \in B\} \in \mathcal{F}
$$
Here we use the shorthand notation
$$
\{X \in B\}=\{\omega \in \Omega: X(\omega) \in B\} .
$$
If $X$ is a random variable, then for every Borel subset $B$ of $\mathbb{R}, X^{-1}(B) \in \mathcal{F}$. We can define a function on Borel sets by
$$
\mu_X(B)=\mathbb{P}\{X \in B\}=\mathbb{P}\left[X^{-1}(B)\right] .
$$
**This function is in fact a measure, and $\left(\mathbb{R}, \mathcal B, \mu_X\right)$ is a probability space.** 

The measure $\mu_X$ is called **the distribution of the random variable**. 





## Nature of Random Variable

**使用随机变量的本质就是转换概率空间, 将 $(\Omega, \mathcal{F}, \mathbb{P})$ 转化为 $\left(\mathbb{R}, \mathcal B, \mu_X\right)$, 使问题的形式更加方便用数学处理**. 

### Explanation

首先我们知道:

* 对于概率空间 $(\Omega, \mathcal{F}, \mathbb{P})$, 概率度量函数$\mathbb P(E)$的参数为$E$, $E \subseteq \Omega$, $E \in \mathcal F$.
* 对于概率空间 $\left(\mathbb{R}, \mathcal B, \mu_X\right)$, 概率度量函数$\mu_X(B)$的参数为$B$, $B \subseteq \Omega$, $E \in \mathcal B$.



虽然我们用statement([->参见前文](http://lyk-love.cn/2023/10/13/Probability-Spaces/#event)))将 $B$ 和 $E$ 定义为event, 但 $B$ 和 $E$ 自身是outcome的集合.

### Example

例如, 定义随机实验为"购买一个汉堡, 品尝其肉馅是什么肉", 规定:

* $\Omega = \{牛肉馅,猪肉馅,鸭肉馅,鱼肉馅\}$, 记四个元素(outcome)为$\omega_1, \omega_2, \omega_3, \omega_4$.
* $\mathcal F$ = $\{(E_1), (E_2)\} = \{(\omega_1,\omega_4), (\omega_2,\omega_3)\}$.
  * 定义event $E_1$: "汉堡是牛肉馅或者鱼肉馅的", 这个event是$\omega_1, \omega_4$的集合, 即: $E_1=\{\omega_1, \omega_4\}$. $\omega_1, \omega_4 \in \Omega$.
  * 定义event $E_2$: "汉堡是猪肉馅或者鸭肉馅的", $E_2=\{\omega_2, \omega_3\}$. $\omega_1, \omega_3 \in \Omega$.
* $\mathbb P(E)$ = 事件$E$发生的概率.

概率空间 =  $(\Omega, \mathcal{F}, \mathbb{P})$.



接着定义随机变量$X$: $X(\omega_i) = i$. 记$X$的取值为$\mathcal X$, 则:

* $\mathcal X = \{1,2,3,4\}$, 记四个元素(outcome)为$x_1, x_2, x_3, x_4$.
* $\mathcal B$ = $\{(B_1), (B_2)\} = \{(x_1,x_4), (x_2,x_3)\} = \{(1,4), (2,3)\}$.
  * 定义event $B_1$: "$X^{-1}(B_1)$为True", 这个event是$x_1, x_4$的集合, 即: $B_1=\{x_1, x_4\} =\{1, 4\}$. $1, 4 \in \mathcal X$, $(1,4) \in \mathcal B$.
  * 定义event $B_1$: "$X^{-1}(B_2)$为True", 这个event是$x_2, x_3$的集合, 即: $B_2=\{x_2, x_3\} =\{2, 3\}$. $2, 3 \in \mathcal X$, $(2,3) \in \mathcal B$.
* $\mu_X(B)$ = 事件$B$发生的概率.

概率空间 =  $\left(\mathbb{R}, \mathcal B, \mu_X\right)$, 或者说 $\left(\mathcal {X}, \mathcal B, \mu_X\right)$.

定义event $B$: "$X$取值为1或者4", 这个event其实是$x_1,x_4$的集合, 即: $B=\{1, 4\}$. $x_1, x_4 \in \mathcal X$,  $\mathcal X$ 是$\mathbb R$的子集. 

注意到, $B_1, B_2$自身只是outcome的集合, 但我们用"$X^{-1}(B_1), X^{-1}(B_2)$成立"这两个statement来定义它们. $B_1, B_2$的取值让statement为True, 也就是事件发生.

## Probability Measure == Probability Distribution

Let $\mu$ be any probability measure on $(\mathbb{R}, B)$. Consider the trivial random variable
$$
X=x
$$
defined on the probability space $(\mathbb{R}, B, \mu)$. Then $X$ is a random variable and $\mu_X=\mu$. **Hence every probability measure on $\mathbb{R}$ is the distribution of a random variable.** 

因此随机变量的概率度量函数也被称为概率分布函数.



Note: 这里的样本空间是$\mathbb R$而不是$\Omega$, 说明这里的每个"outcome"是随机变量, 也就是说题目在对随机变量进行讨论. 

# Discrete and Continuous Random Variables

* If $\mu_X$ gives measure one to a countable set of reals, then $X$ is called a **discrete random variable**. 

  * In this case, $X$ can be described by a [probability mass function](https://statproofbook.github.io/D/pmf);

* If $\mu_X$​ gives zero measure to every singleton set, and hence to every countable set, $X$​ is called a **continuous random variable**. 

  * If it is absolutely continuous, $X$ can be described by a [probability density function](https://statproofbook.github.io/D/pdf).
  
  

Every random variable can be written as a sum of a discrete random variable and a continuous random variable. 

All random variables defined on a discrete probability space are discrete.

# Probability Distribution Function

**The distribution $\mu_X$ is often given in terms of the distribution function**[^2] defined by
$$
F_X(x)=\mathbb{P}\{X \leq x\}=\mu_X(-\infty, x] .
$$
Note that $F=F_X$ satisfies the following:

- $\lim _{x \rightarrow-\infty} F(x)=0$.
- $\lim _{x \rightarrow \infty} F(x)=1$.
- $F$ is a nondecreasing function.
- $F$ is right continuous, i.e., for every $x$,

$$
F(x+):=\lim _{\epsilon \downarrow 0} F(x+\epsilon)=F(x) .
$$

Conversely, any $F$ satisfying the conditions above is the distribution function of a random variable. **The distribution can be obtained from the distribution function** by setting
$$
\mu_X(-\infty, x]=F_X(x),
$$
and extending uniquely to the Borel sets.

# Probability Density Function

For some <u>continuous</u> random variables $X$, there is a function $f=f_X: \mathbb{R} \rightarrow[0, \infty)$ such that
$$
\mathbb{P}\{a \leq X \leq b\}=\int_a^b f(x) d x .
$$
Such a function, if it exists, is called the *density*[^3] of the random variable. If the density exists, then
$$
F(x)=\int_{-\infty}^x f(t) d t
$$


If $f$ is continuous at $t$, then the fundamental theorem of calculus implies that
$$
f(x)=F^{\prime}(x) .
$$
A density $f$ satisfies
$$
\int_{-\infty}^{\infty} f(x) d x=1 .
$$
Conversely, any nonnegative function that integrates to one is the density of a random variable.

# Indicator Function

Example If $E$ is an event, the indicator function of $E$ is the random variable
$$
1_E(\omega)= \begin{cases}1, & \omega \in E, \\ 0, & \omega \notin E .\end{cases}
$$
(The corresponding function in analysis is often called the characteristic function and denoted $\chi_E$. Probabilists never use the term characteristic function for the indicator function because the term characteristic function has another meaning. The term indicator function has no ambiguity.)



Example Let $(\Omega, \mathcal{F}, \mathbb{P})$ be the probability space for infinite tossings of a coin as in the previous section. Let
$$
\begin{aligned}
& X_n\left(\omega_1, \omega_2, \ldots\right)=\omega_n= \begin{cases}1, & \text { if } n \text {th flip heads, } \\
0, & \text { if } n \text {th flip tails. }\end{cases} \\
& S_n=X_1+\cdots+X_n=\# \text { heads on first } n \text { flips. }
\end{aligned}
$$
Then $X_1, X_2, \ldots$, and $S_1, S_2, \ldots$ are discrete random variables. If $\mathcal{F}_n$ denotes the $\sigma$-algebra of events that depend only on the first $n$ flips, then $S_n$ is also a random variable on the probability space $\left(\Omega, \mathcal{F}_n, \mathbb{P}\right)$. However, $S_{n+1}$ is not a random variable on $\left(\Omega, \mathcal{F}_n, \mathbb{P}\right)$.

# Example1

 If $X$ is a random variable and
$$
g:(\mathbb{R}, \mathcal{B}) \rightarrow \mathbb{R}
$$
is a Borel measurable function, then $Y=g(X)$ is also a random variable.

# Example2

Recall that the Cantor function is a continuous function $F:[0,1] \rightarrow[0,1]$ with $F(0)=0, F(1)=1$ and such that $F^{\prime}(x)=0$ for all $x \in[0,1] \backslash A$ where $A$ denotes the "middle thirds" Cantor set. 

Extend $F$ to $\mathbb{R}$ by setting $F(x)=0$ for $x \leq 0$ and $F(x)=1$ for $x \geq 1$. 

Then $F$ is a distribution function. 

A random variable with this distribution function is continuous, since $F$ is continuous. However, such a random variable has no density.



# Normal Distribution

Example A random variable $X$ has a normal distribution with mean $\mu$ and variance $\sigma^2$ if it has density
$$
f(x)=\frac{1}{\sqrt{2 \pi \sigma^2}} e^{-(x-\mu)^2 / 2 \sigma^2}, \quad-\infty<x<\infty
$$
If $\mu=0$ and $\sigma^2=1, X$ is said to have a standard normal distribution. The distribution function of the standard normal is often denoted $\Phi$,
$$
\Phi(x)=\int_{-\infty}^x \frac{1}{\sqrt{2 \pi}} e^{-t^2 / 2} d t .
$$

# Univariate and multivariate random variable

**Definition:** Let $X$ be a [random variable](https://statproofbook.github.io/D/rvar) with possible outcomes $\mathcal X$. Then,

- $X$ is called a two-valued random variable or [random event](https://statproofbook.github.io/D/reve), if $\mathcal  X$ has exactly two elements, e.g. $\mathcal X=\{E,\overline E \}$ or $\mathcal X= \{\text{true},\text{false} \}$ or $\mathcal X=\{ 0,1 \}$;
  * A [random experiment](https://statproofbook.github.io/D/rexp) with two possible outcomes is called a [Bernoulli trial](https://statproofbook.github.io/D/bern).
- $X$ is called a univariate random variable or [random scalar](https://statproofbook.github.io/D/rvar), if $\mathcal  X$ is one-dimensional, i.e. (a subset of) the real numbers $\mathbb R$;
- $X$ is called a multivariate random variable or [random vector](https://statproofbook.github.io/D/rvec), if $\mathcal  X$ is multi-dimensional, e.g. (a subset of) the $n$-dimensional Euclidean space $\mathbb {R}^n$;
- $X$ is called a matrix-valued random variable or [random matrix](https://statproofbook.github.io/D/rmat), if $\mathcal  X$ is (a subset of) the set of $n×p$ real matrices $\mathbb R^{n \times p}$.

# Expectation

Definition If $X$ is a nonnegative random variable, the expectation of $X$, denoted $\mathbb{E}(X)$, is
$$
\mathbb{E}(X)=\int X d \mathbb{P}
$$
where the integral is the Lebesgue integral. If $X$ is a random variable with $\mathbb{E}(|X|)<\infty$, then we also define the expectation by
$$
\mathbb{E}(X)=\int X d \mathbb{P} .
$$
If $X$ takes on positive and negative values, and $\mathbb{E}(|X|)=\infty$, the expectation is not defined.
Other terms used for expectation are expected value and mean (the term "expectation value" can be found in the physics literature but it is not good English and sometimes refers to integrals with respect to measures that are not probability measures). The letter $\mu$ is often used for mean. If $X$ is a discrete random variable taking on the values $a_1, a_2, a_3, \ldots$ we have the standard formula from elementary courses:
$$
\mathbb{E}(X)=\sum_{j=1}^{\infty} a_j \mathbb{P}\left\{X=a_j\right\},
$$
provided the sum is absolutely convergent.
Lemma 2.1. Suppose $X$ is a random variable with distribution $\mu_X$. Then,
$$
\mathbb{E}(X)=\int_{\mathbb{R}} x d \mu_X
$$
(Either side exists if and only if the other side exists.)
Proof. First assume that $X \geq 0$. If $n, k$ are positive integers let
$$
A_{k, n}=\left\{\omega: \frac{k-1}{n} \leq X(\omega)<\frac{k}{n}\right\} .
$$
For every $n<\infty$, consider the discrete random variable $X_n$ taking values in $\{k / n: k \in \mathbb{Z}\}$,
$$
X_n=\sum_{k=1}^{\infty} \frac{k}{n} 1_{A_{k, n}} .
$$
Then,
$$
X_n-\frac{1}{n} \leq X \leq X_n
$$
Hence
$$
\mathbb{E}\left[X_n\right]-\frac{1}{n} \leq \mathbb{E}[X] \leq \mathbb{E}\left[X_n\right]
$$
But,
$$
\mathbb{E}\left[X_n-\frac{1}{n}\right]=\sum_{k=1}^{\infty} \frac{k-1}{n} \mathbb{P}\left(A_{k, n}\right)
$$

$$
\mathbb{E}\left[X_n\right]=\sum_{k=1}^{\infty} \frac{k}{n} \mathbb{P}\left(A_{k, n}\right)
$$
and
$$
\frac{k-1}{n} \mu_X\left[\frac{k-1}{n}, \frac{k}{n}\right) \leq \int_{\left[\frac{k-1}{n}, \frac{k}{n}\right)} x d \mu_X \leq \frac{k}{n} \mu_X\left[\frac{k-1}{n}, \frac{k}{n}\right) .
$$
By summing we get
$$
\mathbb{E}\left[X_n-\frac{1}{n}\right] \leq \int_{[0, \infty)} x d \mu_X \leq \mathbb{E}\left[X_n\right]
$$
By letting $n$ go to infinity we get the result. The general case can be done by writing $X=X^{+}-X^{-}$. We omit the details.

In particular, the expectation of a random variable depends only on its distribution and not on the probability space on which it is defined. If $X$ has a density $f$, then the measure $\mu_X$ is the same as $f(x) d x$ so we can write (as in elementary courses)
$$
\mathbb{E}[X]=\int_{-\infty}^{\infty} x f(x) d x
$$
where again the expectation exists if and only if
$$
\int_{-\infty}^{\infty}|x| f(x) d x<\infty
$$
Since expectation is defined using the Lebesgue integral, all results about the Lebesgue integral (e.g., linearity, Monotone Convergence Theorem, Fatou's Lemma, Dominated Convergence Theorem) also hold for expectation.

[^1]: or, more generally, to any topological space
[^2]: often called cumulative distribution function (cdf) in elementary courses
[^3]: More precisely, it is the density or Radon-Nikoydm derivative with respect to Lebesgue measure. In elementary courses, the term probability density function (pdf) is often used.
