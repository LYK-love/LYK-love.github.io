---
title: The Uniform Distribution Maximizes The Entropy
tags:
  - Information Theory
categories: Mathematics
mathjax: true
date: 2023-12-05 23:14:59
---




Source: 

1. [Why is Entropy maximised when the probability distribution is uniform?](https://stats.stackexchange.com/q/66108)
2. [Why does $\log (1+x)=x+O(x^2)$ when $𝑥 \rightarrow 0$? ](https://math.stackexchange.com/questions/1004880/why-does-log1x-x-ox2-when-x-to-0)

<!--more-->

# Proof

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

# Simpler Proof

Recalling that [$H(X) \leq \log |\mathcal{X}|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/?highlight=jens#theorem-hx-leq-log-mathcalx) with equality if and only  has a uniform distribution over $\mathcal X$.

Then for any r.v. $X$, it's maximum entropy is $\log |\mathcal X|$, and is achieved by a uniform distribution over $\mathcal X$.
