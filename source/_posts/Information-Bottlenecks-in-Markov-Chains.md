---
title: Information Bottlenecks in Markov Chains
tags:
  - Information Theory
categories: Mathematics
mathjax: true
date: 2024-01-25 16:07:38
---


Source:

1. Thomas M. Cover & Joy A. Thomas. (2006). *Chapter 8. Differential Entropy. Elements of Information Theory* (2nd ed., pp. 243-255). Wiley-Interscience.
2. Fady Alajaji & Po-Ning Chen. (2018). *Chapter 5. Differential Entropy and Gaussian Channels. An Introduction to Single-User Information Theory* (1st ed., pp. 165-218). Springer.

<!--more-->

# For discrete states

Suppose a (non-stationary) [Markov chain]() starts in one of $n$ states, necks down to $k<n$ states, and then back to $m>k$ states. Thus $X_1 \rightarrow X_2 \rightarrow X_3$, i.e., $p\left(x_1, x_2, x_3\right)=$ $p\left(x_1\right) p\left(x_2 \mid x_1\right) p\left(x_3 \mid x_2\right)$, for all $x_1 \in\{1,2, \ldots, n\}, x_2 \in\{1,2, \ldots, k\}, x_3 \in\{1,2, \ldots, m\}$.

Questions:

(a) Show that the dependence of $X_1$ and $X_3$ is limited by the bottleneck by proving that $I\left(X_1 ; X_3\right) \leq$ $\log k$.

(b) Evaluate $I\left(X_1 ; X_3\right)$ for $k=1$, and conclude that no dependence can survive such a bottleneck.



Solution:

(a) 

Since $X_1 \rightarrow X_2 \rightarrow X_3$, from the [data processing inequality](https://lyk-love.cn/2023/11/11/stationary-stochastic-processes-and-markov-chains/#data-processing-inequality) we have:
$$
I\left(X_1 ; X_3\right) \leq I\left(X_1 ; X_2\right) .
$$


By the definition of muual information, we know
$$
I\left(X_1 ; X_2\right) = H\left(X_2\right)-H\left(X_2 \mid X_1\right).
$$
Since entropy is non-negative, we ontain:
$$
I\left(X_1 ; X_2\right) = H\left(X_2\right)-H\left(X_2 \mid X_1\right) \le H(X_2).
$$
Meanwhile, let $\mathcal{X}_2$ denote the number of elements in the range of $X_2$, due to theorem [$H(X) \leq \log |\mathcal{X}|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/?highlight=entro#theorem-hx-leq-log-mathcalx), we have
$$
H(X_2) \le \mathcal{X}_2
$$
Finally,
$$
I\left(X_1 ; X_3\right) \leq I\left(X_1 ; X_2\right) = H\left(X_2\right)-H\left(X_2 \mid X_1\right) \leq H\left(X_2\right) \leq \log k .
$$


(b) For $k=1, I\left(X_1 ; X_3\right) \leq \log 1=0$. Hence $I\left(X_1 ; X_3\right)=0$. Hence, for $k=1, X_1$ and $X_3$ are

# For continual states
