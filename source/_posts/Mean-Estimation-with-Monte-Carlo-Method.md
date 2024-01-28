---
title: Mean Estimation with Monte Carlo Method
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
date: 2024-01-27 17:10:23
---


Source:

1. [Shiyu Zhao. *Chapter 5: Monte Carlo Methods. Mathematical Foundations of Reinforcement Learning*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning).

<!--more-->

# Mean estimation problem

Consider a random variable $X$ that can take values from a finite set of real numbers denoted as $\mathcal{X}$, suppose that our task is to calculate the mean or expected value[^1] of $X$, i.e., $\mathbb{E}[X]$.

Two approaches can be used to calculate $\mathbb{E}[X]$.

## Model based case

The first approach is model-based. Here, the model refers to the probability distribution of $X$. If the model is known, then the mean can be directly calculated based on the definition of the expected value:
$$
\mathbb{E}[X]=\sum_{x \in \mathcal{X}} p(x) x
$$

## Model free case

The second approach is model-free. When the probability distribution (i.e., the model) of $X$ is unknown, suppose that we have some samples $\left\{x_1, x_2, \ldots, x_n\right\}$ of $X$. Then, the mean can be approximated as
$$
\mathbb{E}[X] \approx \bar{x}=\frac{1}{n} \sum_{j=1}^n x_j .
$$

When $n$ is small, this approximation may not be accurate. However, as $n$ increases, the approximation becomes increasingly accurate. When $n \rightarrow \infty$, we have $\bar{x} \rightarrow \mathbb{E}[X]$.

This is guaranteed by the [law of large numbers (L.L.N.)](): the average of a large number of samples is close to the expected value.

This is called the **Monte Carlo** method.

# Law of large numbers
For a random variable $X$, suppose that $\left\{x_i\right\}_{i=1}^n$ are some i.i.d. samples. Let $\bar{x}=$ $\frac{1}{n} \sum_{i=1}^n x_i$ be the average of the samples. Then,
$$
\begin{aligned}
\mathbb{E}[\bar{x}] & =\mathbb{E}[X], \\
\operatorname{var}[\bar{x}] & =\frac{1}{n} \operatorname{var}[X] .
\end{aligned}
$$

The above two equations indicate that $\bar{x}$ is an unbiased estimate of $\mathbb{E}[X]$, and its variance decreases to zero as $n$ increases to infinity.

The proof is given below.

First, $\mathbb{E}[\bar{x}]=\mathbb{E}\left[\sum_{i=1}^n x_i / n\right]=\sum_{i=1}^n \mathbb{E}\left[x_i\right] / n=\mathbb{E}[X]$, where the last equability is due to the fact that the samples are identically distributed (that is, $\mathbb{E}\left[x_i\right]=\mathbb{E}[X]$ ).

Second, $\operatorname{var}(\bar{x})=\operatorname{var}\left[\sum_{i=1}^n x_i / n\right]=\sum_{i=1}^n \operatorname{var}\left[x_i\right] / n^2=(n \cdot \operatorname{var}[X]) / n^2=$ $\operatorname{var}[X] / n$, where the second equality is due to the fact that the samples are independent, and the third equability is a result of the samples being identically distributed (that is, $\operatorname{var}\left[x_i\right]=\operatorname{var}[X]$ ).

[^1]: In this RL serie, we use the terms expected value, mean, and average interchangeably.
