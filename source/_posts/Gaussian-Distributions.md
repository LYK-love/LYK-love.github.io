---
title: Gaussian Distributions
tags:
  - Statistics
categories: Mathematics
mathjax: true
date: 2024-01-20 02:37:11
---


Source:

1. [The Multivariate Gaussian Distribution](https://cs229.stanford.edu/section/gaussians.pdf)

<!--more-->

# Notations

In this article we'll use followinng notations interchangeably.

* The PDF[^1] $f_X(x)$ is often denoted as $p_X(x), $ $f_X\left(x ; \mu, \sigma^2\right)$ or $p_X\left(x ; \mu, \sigma^2\right)$. We sometimes also omit the subscript $X$ so that we can write things like $f(x:\mu,\sigma^2)$.

* A normal distribution is also called a Gaussian distribution.

* Since a normal distribution is fully determined by its mean $\mu$ and variance $\sigma^2$ (or standard deviation $\sigma$), we often denote a normal distribution as
  $$
  \mathcal{N}(\mu,\sigma^2) .
  $$
  A random variable, say $X$, having this distribution is denoted as
  $$
  X \sim \mathcal{N}(\mu,\sigma^2) .
  $$

* The notation $X \sim \mathcal{N}(\mu,\sigma^2)$ can also be written as $X \sim \mathcal{N}(x:\mu_x,\sigma_x^2)$.

* We usually call a random variable $X$ having the <u>normal distribution</u> as:

  1. normal (or Gaussian) $X$
  2. normal (or Gaussian) variable $X$
  3. normal (or Gaussian) random variable $X$

* For a random variable having <u>standard normal distribution</u>, we often use the notation $Z$, i.e., $Z \sim \mathcal{N}(0, I)$. Meanwhile, $Z$ is also called:

  1. standard normal (or Gaussian) $Z$
  2. standard normal (or Gaussian) variable $Z$
  3. standard normal (or Gaussian) random variable $Z$

# Definition

In statistics, a **normal distribution** or **Gaussian distribution** is a type of <u>continuous probability distribution for a real-valued random variable</u>. 

We use $X \sim N\left(\mu, \sigma^2\right)$ to denote that a real-valued random variable $X$ follows the Gaussian distribution[^1] with mean=$\mu$ and standard deviation=$\sigma$.

The PMF for $X$ is:


$$
f_X(x)=\frac{1}{\sigma \sqrt{2 \pi}} e^{-\frac{1}{2}\left(\frac{x-\mu}{\sigma}\right)^2}
$$

By definition,

1. $\mu$ is the mean or expectation of the distribution
   $$
   \mathbb E[X] = \mu ,
   $$

2.  $\sigma^2$ is the variance of the distribution
   $$
   \mathrm{Var}(X) = \sigma^2 .
   $$



You can think of the coefficient in front, $\frac{1}{\sqrt{2 \pi} \sigma}$, as simply a constant "normalization factor" used to ensure that
$$
\frac{1}{\sqrt{2 \pi} \sigma} \int_{-\infty}^{\infty} \exp \left(-\frac{1}{2 \sigma^2}(x-\mu)^2\right)=1 .
$$


Notice the $x$ in the exponent of the PDF function. When $x$ is equal to the mean $(\mu)$ then $\mathrm{e}$ is raised to the power of 0 and the PDF is maximized.

## Explanation

![different_univariate_gaussian distributions](/Users/lyk/Documents/cache/different_univariate_gaussian distributions.png)

$\sigma$ describes the spread of the data points around the mean.

$\sigma$ defines the central location of the Gaussian distribution.

## Code

```python
import torch
def calculate_univariate_gaussian_distribution(x, mu, sigma):
    leading_coefficient = 1 / (sigma * torch.sqrt(torch.tensor(2 * torch.pi)))
    parameter_of_exp_function = -0.5 * (x - mu / sigma) ** 2
    return leading_coefficient * torch.exp(parameter_of_exp_function)
```



# Standard Normal

![standard_univariate_gaussian distribution](/Users/lyk/Documents/cache/univariate_gaussian distribution.png)

A normal distribution $\mathcal{N}(\mu,\sigma^2)$ is **standard** if $\mu = 0$ and $\sigma^2 = 1$.

The random variable that follows a normal distribution is often denoted as
$$
Z \sim \mathcal{N}(0,1) .
$$
$Z$ is called the stanard normal.

## Linear Transform

Given random variables $X$, $Y$. Suppose $X \sim N\left(\mu, \sigma^2\right)$ and $Y=a X+b$, i.e., $Y$ is a linear transform of $X$.

Then $Y$ also follows Gaussian distribution where:
$$
Y \sim \mathcal N\left(a \mu+b, a^2 \sigma^2\right)
$$

## Projection to Standard Normal

Given a normal random variable $X \sim N\left(\mu, \sigma^2\right)$. We can transform $X$ linearly into standard normal $Z$.
$$
\begin{align}
Z 
& =\frac{X-\mu}{\sigma} \label{eq_5_0} \\
& =\frac{1}{\sigma} X-\frac{\mu}{\sigma} \label{eq_5_1}\\
& =a X+b \label{eq_5_2}\\
& \sim \mathcal N\left(a \mu+b, a^2 \sigma^2\right) \label{eq_5_3} \\
& \sim \mathcal N\left(\frac{\mu}{\sigma}-\frac{\mu}{\sigma}, \frac{\sigma^2}{\sigma^2}\right) \label{eq_5_4} \\
& \sim \mathcal N(0,1) . \nonumber
\end{align}
$$

Explanation:

$\eqref{eq_5_0}$: Linear transform of $X$. Subtract by $\mu$ and diving by $\sigma$.

$\eqref{eq_5_1}$: Use algebra to rewrite the equation.

$\eqref{eq_5_2}$: Let $a=\frac{1}{\mu}, b=-\frac{\mu}{\sigma}$

$\eqref{eq_5_3}$: The linear transform of a normal variable is another normal variable, proved in [-->last section]().

$\eqref{eq_5_4}$: Substituting values in for $a$ and $b$.

 

[^1]: Probability density function
