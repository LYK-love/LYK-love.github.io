---
title: Chain Rules for Entropy, Relative Entropy and Mutual Information
tags:
  - Information Theory
  - Statistics
categories: Mathematics
mathjax: true
date: 2023-10-15 02:22:20
---


We now show that the entropy of a collection of random variables is the sum of the conditional entropies.



Note: 本文的证明还比较粗糙, 后面会改进.



Ref: *Elements of Information Theory*

<!--more-->

# Chain rule for entropy

Let $X_1, X_2, \ldots, X_n$ be drawn according to $p\left(x_1, x_2, \ldots, x_n\right)$. Then
$$
H\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) .
$$

## Proof: Short

By repeated application of the two-variable expansion rule for entropies, we have
$$
\begin{aligned}
H\left(X_1, X_2\right) & =H\left(X_1\right)+H\left(X_2 \mid X_1\right), \\
H\left(X_1, X_2, X_3\right) & =H\left(X_1\right)+H\left(X_2, X_3 \mid X_1\right) \\
& =H\left(X_1\right)+H\left(X_2 \mid X_1\right)+H\left(X_3 \mid X_2, X_1\right), \\
& \vdots \\
H\left(X_1, X_2, \ldots, X_n\right) & =H\left(X_1\right)+H\left(X_2 \mid X_1\right)+\cdots+H\left(X_n \mid X_{n-1}, \ldots, X_1\right) \\
& =\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) .
\end{aligned}
$$

## Proof: Long

We write $p\left(x_1, \ldots, x_n\right)=\prod_{i=1}^n p\left(x_i \mid x_{i-1}, \ldots, x_1\right)$ and evaluate
$$
\begin{aligned}
H & \left(X_1, X_2, \ldots, X_n\right) \\
& =-\sum_{x_1, x_2, \ldots, x_n} p\left(x_1, x_2, \ldots, x_n\right) \log p\left(x_1, x_2, \ldots, x_n\right) \\
& =-\sum_{x_1, x_2, \ldots, x_n} p\left(x_1, x_2, \ldots, x_n\right) \log \prod_{i=1}^n p\left(x_i \mid x_{i-1}, \ldots, x_1\right) \\
& =-\sum_{x_1, x_2, \ldots, x_n} \sum_{i=1}^n p\left(x_1, x_2, \ldots, x_n\right) \log p\left(x_i \mid x_{i-1}, \ldots, x_1\right) \\
& =-\sum_{i=1}^n \sum_{x_1, x_2, \ldots, x_n} p\left(x_1, x_2, \ldots, x_n\right) \log p\left(x_i \mid x_{i-1}, \ldots, x_1\right) \\
& =-\sum_{i=1}^n \sum_{x_1, x_2, \ldots, x_i} p\left(x_1, x_2, \ldots, x_i\right) \log p\left(x_i \mid x_{i-1}, \ldots, x_1\right) \\
& =\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) .
\end{aligned}
$$
We now define the conditional mutual information as the reduction in the uncertainty of $X$ due to knowledge of $Y$ when $Z$ is given.

# Chain rule for Mutual Information

Mutual information also satisfies a chain rule.
$$
I\left(X_1, X_2, \ldots, X_n ; Y\right)=\sum_{i=1}^n I\left(X_i ; Y \mid X_{i-1}, X_{i-2}, \ldots, X_1\right) .
$$


## Proof


$$
\begin{aligned}
I & \left(X_1, X_2, \ldots, X_n ; Y\right) \\
& =H\left(X_1, X_2, \ldots, X_n\right)-H\left(X_1, X_2, \ldots, X_n \mid Y\right) \\
& =\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right)-\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1, Y\right) \\
& =\sum_{i=1}^n I\left(X_i ; Y \mid X_1, X_2, \ldots, X_{i-1}\right) .
\end{aligned}
$$

# Chain Rule for Relative Entropy
The chain rule for relative entropy is used in Section 4.4 to prove a version of the second law of thermodynamics.


$$
D(p(x, y) \| q(x, y))=D(p(x) \| q(x))+D(p(y \mid x) \| q(y \mid x)) .
$$

## Proof

$$
\begin{aligned}
D( & p(x, y) \| q(x, y)) \\
& =\sum_x \sum_y p(x, y) \log \frac{p(x, y)}{q(x, y)} \\
& =\sum_x \sum_y p(x, y) \log \frac{p(x) p(y \mid x)}{q(x) q(y \mid x)} \\
& =\sum_x \sum_y p(x, y) \log \frac{p(x)}{q(x)}+\sum_x \sum_y p(x, y) \log \frac{p(y \mid x)}{q(y \mid x)} \\
& =D(p(x) \| q(x))+D(p(y \mid x) \| q(y \mid x)) .
\end{aligned}
$$

