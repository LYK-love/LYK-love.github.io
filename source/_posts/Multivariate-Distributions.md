---
title: Multivariate Distributions
tags:
  - Statistics
categories: Mathematics
mathjax: true
date: 2024-01-18 22:34:32
---


Source:

//

<!--more-->

# Multivariate Gaussian distributions

A $n$ dimensional random vector $X$ following Gaussian distribution is denoted as
$$
X \sim \mathcal{N} (\mu , \Sigma)
$$
where

* $\mu$ is the mean vector of the distribution, it's $n$-dimensional.
* $\Sigma=\operatorname{diag}\left(\sigma_1^2, \ldots, \sigma_n^2\right)$ is the $n \times n$ covariance matrix.

## PMF

It's probability density function is:
$$
f(X; \mathbf{\mu}, \mathbf{\Sigma}) 
= 
\frac{1}{\sqrt{(2\pi)^n \det(\mathbf{\Sigma})}} 
\exp
\left(-\frac{1}{2} (X- \mathbf{\mu})^\top \mathbf{\Sigma}^{-1} (X - \mathbf{\mu})\right)
$$


where $\exp$ denotes the exponential function.



We also obtain that:

- $\det(\mathbf{\Sigma})$ is the determinant of the covariance matrix.
- $\mathbf{\Sigma}^{-1}$ is the inverse of the covariance matrix.
- The term $(\mathbf{x} - \mathbf{\mu})^\top \mathbf{\Sigma}^{-1} (\mathbf{x} - \mathbf{\mu})$ represents the Mahalanobis distance from $X$ to the mean $\mathbf{\mu}$, squared.
