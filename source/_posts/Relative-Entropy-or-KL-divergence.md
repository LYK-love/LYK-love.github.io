---
title: Relative Entropy (or KL divergence)
tags:
  - Information Theory
  - Statistics
  - Machine Learning
categories: Mathematics
mathjax: true
date: 2024-01-18 22:23:25
---


Source:

1. *Elements of Information Theory*
2. *An Introduction to Single-User Information Theory*

<!--more-->



# Definition

The *relative entropy* (or Kullback-Leibler divergence, KL divergence) $D(p||q)$ is a "measure" of the distance between the true distribution $p$ and the assumed distribution $q$. It's defined as:

$$
\begin{aligned}
D(p \| q) & =\sum_{x \in \mathcal{X}} p(x) \log \frac{p(x)}{q(x)} \\
& = \mathbb E _{X \sim p}(\log \frac{p(X)}{q(X)}) .
\end{aligned}
$$
In the above definition, we use the convention that:

1. $0 \log \frac{0}{0}=0$ and the convention (based on continuity arguments) that 
2. $0 \log \frac{0}{q}=0$ and $p \log \frac{p}{0}=$ $\infty$. 

Thus, if there is any symbol $x \in \mathcal{X}$ such that $p(x)>0$ and $q(x)=0$, then $D(p \| q)=\infty$.

## Notations

You may see some people use these symbols to represent relative entropy. They are interchangeable.
$$
D(p \| q), \mathrm{KL}(p \| q), \mathrm{D}_\mathrm{(KL)} (p \| q), \cdots
$$


# Properties of Relative Entropy

1. In general, relative entropy is asymmetric $(D(p \| q) \neq D(q \| p))$, and does not satisfy the triangle inequality. Therefore, it is **not** a metric.
2. $D(p \| p)=0$.
3. $D(p \| q) \geq 0$ for all distributions $p, q$ with equality holding iff $p=q$. 
4. $D(p(y \mid x) \| q(y \mid x)) \geq 0$ with equality if and only if $p(y \mid x)=q(y \mid x)$ for all $y$ and $x$ such that $p(x)>0$.

Property (3) is [proved using Jensen’s inequality](https://lyk-love.cn/2023/10/15/Jensen%E2%80%99s-Inequality/#theorem-information-inequality).

Property (4) is proved using property (3).

# Relative Entropy is Not Symmetric

In the following problem and solution, we give an **counterexample** of relative entropy's symmericity.



Relative entropy is not symmetric. Let the random variable $X$ have three possible outcomes $\{a, b, c\}$. Consider two distributions $p(x)$ and $q(x)$ on this random variable

| Symbol | $p(x)$ | $q(x)$ |
| ------ | ------ | ------ |
| a      | 1/2    | 1/3    |
| b      | 1/4    | 1/3    |
| c      | 1/4    | 1/3    |

Calculate $H(p), H(q), D(p \| q)$ and $D(q \| p)$. Verify that in this case $D(p \| q) \neq D(q \| p)$.
Solution:
$$
\begin{aligned}
H(p) & =\frac{1}{2} \log 2+\frac{1}{4} \log 4+\frac{1}{4} \log 4=1.5 \mathrm{bits} \\
H(q) & =3 \times \frac{1}{3} \log 3=1.58496 \mathrm{bits} \\
D(p \| q) & =\frac{1}{2} \log \frac{3}{2}+\frac{1}{4} \log \frac{3}{4}+\frac{1}{4} \log \frac{3}{4}=\log 3-1.5=0.08496 \mathrm{bits} \\
D(q \| p) & =\frac{1}{3} \log \frac{2}{3}+\frac{1}{3} \log \frac{4}{3}+\frac{1}{3} \log \frac{4}{3}=-\log 3+\frac{5}{3}=0.0817 \mathrm{bits}
\end{aligned}
$$
It is clear that $D(p \| q) \neq D(q \| p)$.

# Conditional Eelative Entropy

We define a conditional version of the relative entropy.

**Definition:** For joint probability mass functions $p(x, y)$ and $q(x, y)$, the conditional relative entropy $D(p(y \mid x) \| q(y \mid x))$ is the average of the relative entropies between the conditional probability mass functions $p(y \mid x)$ and $q(y \mid x)$ averaged over the probability mass function $p(x)$. More precisely,
$$
\begin{aligned}
D(p(y \mid x) \| q(y \mid x)) & =\sum_x p(x) \sum_y p(y \mid x) \log \frac{p(y \mid x)}{q(y \mid x)} \\
& =E_{p(x, y)} \log \frac{p(Y \mid X)}{q(Y \mid X)} .
\end{aligned}
$$


The notation for conditional relative entropy is not explicit since it omits mention of the distribution $p(x)$ of the conditioning random variable. However, it is normally understood from the context.

The relative entropy between two joint distributions on a pair of random variables can be expanded as the sum of a relative entropy and a conditional relative entropy. 

# For miltivariance Gaussian distributions

Suppose $p=\mathcal{N}\left(\mu_1, \Sigma_1\right)$ and $q=\mathcal{N}\left(\mu_2, \Sigma_2\right)$. Both are $n$=dimensoin [multivariate Gaussian distributions](https://lyk-love.cn/2024/01/18/multivariate-distributions/#multivariate-gaussian-distributions).

Their relative entropy (or KL divergence) is:
$$
\mathrm{KL}\left(p \| q\right) = 
\frac{1}{2}
\left[
\log \frac{\left|\Sigma_2\right|}{\left|\Sigma_1\right|}
-
n+\operatorname{tr}\left\{\Sigma_2^{-1} \Sigma_1\right\}
+
\left(\mu_2-\mu_1\right)^T \Sigma_2^{-1}\left(\mu_2-\mu_1\right)\right
]
$$
