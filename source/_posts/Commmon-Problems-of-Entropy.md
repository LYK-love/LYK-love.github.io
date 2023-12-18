---
title: Commmon Problems of Entropy
tags:
  - Information Theory
categories: Mathematics
mathjax: true
date: 2023-12-10 11:48:10
---

Common problems of Shannon entropy in information theory.

<!--more-->


# Theorem: Deterministic Distribution Minimizes The Entropy

What is the minimum value of $H\left(p_1, \ldots, p_n\right)=H(\mathbf{p})$ as $\mathbf{p}$ ranges over the set of $n$-dimensional probability vectors? Find all p's which achieve this minimum.

Solution:
We wish to find all probability vectors $\mathbf{p}=\left(p_1, \ldots, p_n\right)$ which minimize
$$
H(\mathbf{p})=-\sum_i p_i \log p_i .
$$

Now $-p_i \log p_i \geq 0$, with equality iff $p_i=0$ or 1 . Besides we know that $\sum_i p_i = 1$.

Hence the only possible probability vectors which minimize $H(\mathbf{p})$ are those with $p_i=1$ for some $i$ and $p_j=0, j \neq i$. There are $n$ such vectors, i.e., $(1,0, \ldots, 0),(0,1,0, \ldots, 0), \ldots,(0, \ldots, 0,1)$, and the minimum value of $H(\mathbf{p})$ is 0 .

# Theorem: Uniform Distribution Maximizes The Entropy

Source:

1. [Why is Entropy maximised when the probability distribution is uniform?](https://stats.stackexchange.com/q/66108)
2. [Why does $\log (1+x)=x+O(x^2)$ when $𝑥 \rightarrow 0$? ](https://math.stackexchange.com/questions/1004880/why-does-log1x-x-ox2-when-x-to-0)

## Proof

Heuristically, the probability density function on $\left\{x_1, x_2, \ldots, x_n\right\}$ with maximum entropy turns out to be the one that corresponds to the least amount of knowledge of $\left\{x_1, x_2, \ldots, x_n\right\}$, in other words the Uniform distribution.

Now, for a more formal proof consider the following:
A probability density function on $\left\{x_1, x_2, \ldots, . x_n\right\}$ is a set of nonnegative real numbers $p_1, \ldots, p_n$ that add up to 1 . Entropy is a continuous function of the $n$-tuples $\left(p_1, \ldots, p_n\right)$, and these points lie in a compact subset of $\mathbb{R}^n$, so there is an $n$-tuple where entropy is maximized. We want to show this occurs at $(1 / n, \ldots, 1 / n)$ and nowhere else.

Suppose the $p_j$ are not all equal, say $p_1<p_2$. (Clearly $n \neq 1$.) We will find a new probability density with higher entropy. It then follows, since entropy is maximized at some $n$-tuple, that entropy is uniquely maximized at the $n$-tuple with $p_i=1 / n$ for all $i$.

Since $p_1<p_2$, for small positive $\varepsilon$ we have $p_1+\varepsilon<p_2-\varepsilon$. The entropy of $\left\{p_1+\varepsilon, p_2-\varepsilon, p_3, \ldots, p_n\right\}$ minus the entropy of $\left\{p_1, p_2, p_3, \ldots, p_n\right\}$ equals
$$
-p_1 \log \left(\frac{p_1+\varepsilon}{p_1}\right)-\varepsilon \log \left(p_1+\varepsilon\right)-p_2 \log \left(\frac{p_2-\varepsilon}{p_2}\right)+\varepsilon \log \left(p_2-\varepsilon\right)
$$

To complete the proof, we want to show this is positive for small enough $\varepsilon$. Rewrite the above equation as
$$
\begin{aligned}
-p_1 \log \left(1+\frac{\varepsilon}{p_1}\right) & -\varepsilon\left(\log p_1+\log \left(1+\frac{\varepsilon}{p_1}\right)\right)-p_2 \log \left(1-\frac{\varepsilon}{p_2}\right) \\
& +\varepsilon\left(\log p_2+\log \left(1-\frac{\varepsilon}{p_2}\right)\right)
\end{aligned}
$$

Recalling that $\log (1+x)=x+O\left(x^2\right)$ for small $x$, the above equation is
$$
-\varepsilon-\varepsilon \log p_1+\varepsilon+\varepsilon \log p_2+O\left(\varepsilon^2\right)=\varepsilon \log \left(p_2 / p_1\right)+O\left(\varepsilon^2\right)
$$
which is positive when $\varepsilon$ is small enough since $p_1<p_2$.

## Simpler Proof

Recalling that [$H(X) \leq \log |\mathcal{X}|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/?highlight=jens#theorem-hx-leq-log-mathcalx) with equality if and only  has a uniform distribution over $\mathcal X$.

Then for any r.v. $X$, it's maximum entropy is $\log |\mathcal X|$, and is achieved by a uniform distribution over $\mathcal X$.

# Drawing with and without replacement

Drawing with and without replacement. An urn contains $r$ red, $w$ white, and $b$ black balls. **Which has higher entropy**, drawing $n \geq 2$ balls from the urn with replacement or without replacement? 



**Solution:**

Let random variable $X_i$ denotes the outcome color of the $i-$th ball. The alphabate of all $X_i$ is the same: $\mathcal X = \{0,1,2\}$, where

1. $X_i=0$ if the ball is red, 
2. $X_i=1$ if the ball is white
3. $X_i=2$ if the ball is black.

Let $p_{X_i}$ denote the PMF of $X_i$. 

**For the case with replacement:**

For all $X_i \in X_1, \cdots, X_n$, Since the total number of red, white, black balls are $r, w, b$,
$$
p(X_i) = \begin{cases} 
    \frac{r}{r + w + b} & \text{if } X = 1 \\
    \frac{w}{r + w + b} & \text{if } X = 2 \\
    \frac{b}{r + w + b} & \text{if } X = 3 .
\end{cases}
$$
$p(X_i)$ doesn't change during the drawing process, so all $p(X_i)$ are independant(because of the replacement). 

Due to [Theorem: Entropy is additive for independent r.v.](https://lyk-love.cn/2023/10/15/shannon-entrophy/?highlight=shann#entropy-is-additive-for-independent-r.v.), 
$$
H\left(X_1, X_2, \cdots, X_k\right)=H\left(X_1\right)+H\left(X_2\right)+\cdots+H\left(X_k\right) .
$$
**For the case without replacement:**

the picks are not independent anymore, due to [the chain rule for joint entropy](https://lyk-love.cn/2023/10/15/shannon-entrophy/?highlight=shan#chain-rule-for-joint-entropy), we have
$$
\begin{aligned}
H\left(X_1, X_2, \cdots, X_k\right) & =H\left(X_1\right)+H\left(X_2 \mid X_1\right)+\cdots+H\left(X_k \mid X_1, \cdots, X_k-1\right) .
\end{aligned}
$$

Meanwhile, due to [Theorem: Theorem: Conditioning reduces entropy](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-conditioning-reduces-entropy), we have:
$$
H\left(X_1\right)+H\left(X_2 \mid X_1\right)+\cdots+H\left(X_k \mid X_1, \cdots, X_k-1\right) \leq H\left(X_1\right)+H\left(X_2\right)+\cdots+H\left(X_k\right)
$$
**Hence, the sample with replacement has higher entropy.**

