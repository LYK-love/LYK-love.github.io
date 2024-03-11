---
title: Mutual Information
tags:
  - Information Theory
  - Statistics
  - Machine Learning
categories: Mathematics
mathjax: true
date: 2024-01-18 22:23:18
---


Sources:

1. *Elements of Information Theory*
2. *An Introduction to Single-User Information Theory*

<!--more-->



# Definition

Given two random variables $X$ and $Y$, we want to define a measure of the information that $Y$ provides about $X$ when $Y$ is observed, but $X$ is not. We call this measure mutual information, which is defined as:
$$
I(X ; Y) \triangleq H(X)-H(X \mid Y)
$$

It can be expressed in terms *relative entropy* between their joint distribution $p_{X, Y}$ and the product of their marginal distributions $p_X \cdot p_Y$
$$
\begin{aligned}
I(X ; Y) & =\sum_{x, y} p(x, y) \log \frac{p_{X, Y}(x, y)}{p_X(x) \cdot p_Y(y)} \\
& =D\left(p_{X, Y} \| p_X \cdot p_Y\right) .
\end{aligned}
$$

# Properties of Mutual Information

## Basics

1. $I(X ; Y)=\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} P_{X, Y}(x, y) \log _2 \frac{P_{X, Y}(x, y)}{P_X(x) P_Y(y)}$.

2. $I(X ; Y)=I(Y ; X)=H(Y)-H(Y \mid X)$.
3. $I(X ; Y)=H(X)+H(Y)-H(X, Y)$.

4. $I(X ; Y) \leq H(X)$ with equality holding iff $X$ is a function of $Y$ (i.e., $X=f(Y)$ for some function $f(\cdot))$.
5. $I(X ; Y) \geq 0$ with equality holding iff $X$ and $Y$ are independent.
6. $I(X ; Y) \leq \min \left\{\log _2|\mathcal{X}|, \log _2|\mathcal{Y}|\right\}$.



Proof:

Properties 1, 2, 3, and 4 follow immediately from the definition. 

Property 5 is a direct consequence of $D(p \| q) \geq 0$, since $I(X:Y) = D\left(p_{X, Y} \| p_X \cdot p_Y\right)$ .

Property 6 holds iff $I(X ; Y) \leq \log _2|\mathcal{X}|$ and $I(X ; Y) \leq \log _2|\mathcal{Y}|$. 

To show the first inequality, we write $I(X ; Y)=H(X)-$ $H(X \mid Y)$, use the fact that $H(X \mid Y)$ is nonnegative and apply [Theorem: $H(X) \le |\mathcal X|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-hx-leq-log-mathcalx). A similar proof can be used to show that $I(X ; Y) \leq \log _2|\mathcal{Y}|$.

The relationships between $H(X), H(Y), H(X, Y), H(X \mid Y), H(Y \mid X)$, and $I(X ; Y)$ can be illustrated by the Venn diagram in the above figure.

## $I(X:Y) = I(Y:X)$

Expanding $H(X)-H(X \mid Y)$, we have:
$$
\begin{aligned}
H(X)-H(X \mid Y) & =\mathbb{E}\left[\log \frac{1}{p(X)}\right]-\mathbb{E}\left[\log \frac{1}{p(X \mid Y)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X \mid Y)}{p(X)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X \mid Y) p(Y)}{p(X) p(Y)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X, Y)}{p(X) p(Y)}\right] \\
& =H(Y)-H(Y \mid X)
\end{aligned}
$$


Then
$$
I(X ; Y) \triangleq H(X)-H(X \mid Y)=H(Y)-H(Y \mid X)
$$


So **mutual information is symmetric**.

## $I(X ; X)=H(X)$

Now let’s ask an interesting question: How much does X tell us about itself? In other words, what is I (X; X)? Using our first definition, we have:
$$
I (X; X) = H (X) − H (X|X)
$$


We note that $H(X \mid X)=0$, because in the expectation, $X$ can only take on one fixed, given value with probability 1 . Therefore, $H(X \mid X)=\log 1=0$. Thus:
$$
I(X ; X)=H(X)
$$
Meaning that $X$ tells us everything about itself!

## $I(X ; Y) \geq 0$

For any two random variables, $X, Y$,
$$
I(X ; Y) \geq 0
$$
with equality if and only if $X$ and $Y$ are independent.



**Proof:** 

1. We know that $I(X ; Y)=D(p(x, y) \| p(x) p(y))$.
2. See [property 3 of Relative Entropy](https://lyk-love.cn/2023/10/15/shannon-entrophy/#properties-1), $D(p \| q) \geq 0$ for all distributions $p, q$ with equality holding iff $p=q$.
3. So $I(X ; Y)=D(p(x, y) \| p(x) p(y)) \geq 0$, with equality if and only if $p(x, y)=p(x) p(y)$ (i.e., $X$ and $Y$ are independent).

***

**Corollary:**
$$
I(X ; Y \mid Z) \geq 0,
$$
with equality if and only if $X$ and $Y$ are conditionally independent given $Z$.

# Conditional Mutual Information

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/VennInfo3Var.svg/256px-VennInfo3Var.svg.png)

> Venn diagram of information theoretic measures for three variables $x, y$, and $z$, represented by the lower left, lower right, and upper circles, respectively. 
>
> The conditional mutual informations $I(x ; z \mid y), I(y ; z \mid x)$ and $I(x ; y \mid z)$ are represented by the yellow, cyan, and magenta regions, respectively.

The conditional mutual information, denoted by $I(X ; Y \mid Z)$, is defined as the common uncertainty between $X$ and $Y$ under the knowledge of $Z$ :
$$
I(X ; Y \mid Z):=H(X \mid Z)-H(X \mid Y, Z)
$$

可以这么想像: $I(X;Y)$ 就是 $H(X)$ 和 $H(Y)$ 的交集, 再挖掉其中 $H(Z)$ 的部分就是$I(X;Y|Z)$. 对应于图中粉色部分.

# Joint Mutual Information

Lemma: Defining the joint mutual information between $X$ and the pair $(Y, Z)$  by
$$
I(X ; Y, Z):=H(X)-H(X \mid Y, Z),
$$
we have
$$
I(X ; Y, Z)=I(X ; Y)+I(X ; Z \mid Y)=I(X ; Z)+I(X ; Y \mid Z) .
$$
$X$ 和 $(Y,Z)$的互信息 = $X$ 和 $Y$ 的互信息 + 在$Y$ 已知的情况下 $X$ 和 $Z$ 的互信息. 

可以这么想像: 把$H(Y), H(Z)$ 连成一块得到$H(Y,Z)$, $I(X;Y,Z)$ 就是 $H(X)$ 和 $H(Y,Z)$ 的交集. 对应于图中黄, 灰, 粉三块区域的并集.

Proof: Without loss of generality, we only prove the first equality:
$$
\begin{aligned}
I(X ; Y, Z) & =H(X)-H(X \mid Y, Z) \\
& =H(X)-H(X \mid Y)+H(X \mid Y)-H(X \mid Y, Z) \\
& =I(X ; Y)+I(X ; Z \mid Y) .
\end{aligned}
$$

The above lemma can be read as follows: the information that $(Y, Z)$ has about $X$ is equal to the information that $Y$ has about $X$ plus the information that $Z$ has about $X$ when $Y$ is already known.

# Properties of Entropy and Mutual Information for Multiple Random Variables

## Chain rule for joint entropy

**Theorem**: Let $X_1, X_2, \ldots, X_n$ be drawn according to $P_{X^n}\left(x^n\right):=P_{X_1, \ldots, X_n}\left(x_1, \ldots, x_n\right)$, where we use the common superscript notation to denote an $n$-tuple: $X^n:=\left(X_1, \ldots, X_n\right)$ and $x^n:=\left(x_1, \ldots, x_n\right)$.

Then
$$
H\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right),
$$
where $H\left(X_i \mid X_{i-1}, \ldots, X_1\right):=H\left(X_1\right)$ for $i=1$. (The above chain rule can also be written as:
$$
H\left(X^n\right)=\sum_{i=1}^n H\left(X_i \mid X^{i-1}\right)
$$
where $X^i:=\left(X_1, \ldots, X_i\right)$.)

> For example, for three random variables $X$, $Y$ , and $Z$,
> $$
> \begin{aligned}
> H(X, Y, Z) & =H(X)+H(Y, Z \mid X)   \\
> & =H(X)+H(Y \mid X)+H(Z \mid X, Y) 
> \end{aligned}
> $$

***

Proof:

From [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) ,
$$
H\left(X_1, X_2, \ldots, X_n\right)=H\left(X_1, X_2, \ldots, X_{n-1}\right)+H\left(X_n \mid X_{n-1}, \ldots, X_1\right)
$$

Once again, applying [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) to the first term of the right-hand side of this equation, we have
$$
H\left(X_1, X_2, \ldots, X_{n-1}\right)=H\left(X_1, X_2, \ldots, X_{n-2}\right)+H\left(X_{n-1} \mid X_{n-2}, \ldots, X_1\right)
$$

The desired result can then be obtained by repeatedly applying [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) .

## Chain rule for conditional entropy

Theorem:
$$
H\left(X_1, X_2, \ldots, X_n \mid Y\right)=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1, Y\right) .
$$

***

Proof:

The theorem can be proved similarly to [Chain Rule for Entropy(2 Variables)](https://lyk-love.cn/2023/10/15/shannon-entrophy/?highlight=shann#chain-rule-for-entropy2-variables).
If $X^n=\left(X_1, \ldots, X_n\right)$ and $Y^m=\left(Y_1, \ldots, Y_m\right)$ are jointly distributed random vectors (of not necessarily equal lengths), then their joint mutual information is given by
$$
I\left(X_1, \ldots, X_n ; Y_1, \ldots, Y_m\right):=H\left(X_1, \ldots, X_n\right)-H\left(X_1, \ldots, X_n \mid Y_1, \ldots, Y_m\right) .
$$

## Chain rule for mutual information

Theorem:
$$
I\left(X_1, X_2, \ldots, X_n ; Y\right)=\sum_{i=1}^n I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right),
$$
where $I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right):=I\left(X_1 ; Y\right)$ for $i=1$.

***

Proof:

This can be proved by first expressing mutual information in terms of entropy and conditional entropy, and then applying the chain rules for entropy and conditional entropy.

## Independence bound on entropy

Theorem:
$$
H\left(X_1, X_2, \ldots, X_n\right) \leq \sum_{i=1}^n H\left(X_i\right) .
$$

Equality holds iff all the $X_i$ 's are independent of each other.[^8]

***

Proof:

By applying the chain rule for entropy,
$$
\begin{aligned}
H\left(X_1, X_2, \ldots, X_n\right) & =\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) \\
& \leq \sum_{i=1}^n H\left(X_i\right) .
\end{aligned}
$$

Equality holds iff each conditional entropy is equal to its associated entropy, that iff $X_i$ is independent of $\left(X_{i-1}, \ldots, X_1\right)$ for all $i$.

## Bound on mutual information

Theorem: If $\left\{\left(X_i, Y_i\right)\right\}_{i=1}^n$ is a process satisfying the conditional independence assumption $P_{Y^n \mid X^n}=\prod_{i=1}^n P_{Y_i \mid X_i}$, then
$$
I\left(X_1, \ldots, X_n ; Y_1, \ldots, Y_n\right) \leq \sum_{i=1}^n I\left(X_i ; Y_i\right),
$$
with equality holding iff $\left\{X_i\right\}_{i=1}^n$ are independent.

***

Proof:

From the independence bound on entropy, we have
$$
H\left(Y_1, \ldots, Y_n\right) \leq \sum_{i=1}^n H\left(Y_i\right) .
$$

By the conditional independence assumption, we have
$$
\begin{aligned}
H\left(Y_1, \ldots, Y_n \mid X_1, \ldots, X_n\right) & =E\left[-\log _2 P_{Y^n \mid X^n}\left(Y^n \mid X^n\right)\right] \\
& =E\left[-\sum_{i=1}^n \log _2 P_{Y_i \mid X_i}\left(Y_i \mid X_i\right)\right] \\
& =\sum_{i=1}^n H\left(Y_i \mid X_i\right) .
\end{aligned}
$$

Hence,
$$
\begin{aligned}
I\left(X^n ; Y^n\right) & =H\left(Y^n\right)-H\left(Y^n \mid X^n\right) \\
& \leq \sum_{i=1}^n H\left(Y_i\right)-\sum_{i=1}^n H\left(Y_i \mid X_i\right) \\
& =\sum_{i=1}^n I\left(X_i ; Y_i\right),
\end{aligned}
$$
with equality holding iff $\left\{Y_i\right\}_{i=1}^n$ are independent, which holds iff $\left\{X_i\right\}_{i=1}^n$ are independent.

