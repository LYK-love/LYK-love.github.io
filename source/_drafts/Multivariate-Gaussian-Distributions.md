---
title: Multivariate Gaussian Distributions
tags:
  - Statistics
categories: Mathematics
mathjax: true
date: 2024-01-18 22:34:32
---

Source:

1. [The Multivariate Gaussian Distribution](https://cs229.stanford.edu/section/gaussians.pdf)

<!--more-->

# Notations

The notations of this article is exactly the same as these in [](). For the multi variate case, we add additional rules:

1. The multivariate normal distribution of a $n$-dimensional random vector $X = \left[X_1, \ldots, X_n\right]^{\mathrm{T}}$ can be written in the following notation:
   $$
   X \sim \mathcal{N}({\mu}, {\Sigma})
   $$
   or to make it explicitly known that $X$ is $k$-dimensional,
   $$
   X \sim \mathcal{N}_k({\mu}, {\Sigma})
   $$

2. The PDF[^1] $f_X(x)$ is often denoted as $p_X(x), $ $f_X\left(x ; \mu, \sigma^2\right)$ or $p_X\left(x ; \mu, \sigma^2\right)$ where $X = \left[X_1, \ldots, X_n\right]^{\mathrm{T}}$. We sometimes also omit the subscript $X$ so that we can write things like $f(x:\mu,\sigma^2)$.

# Multivariate Gaussian distributions

In statistics, a multivariate normal (or Gaussian) distribution is a generalization of the [one-dimensional (univariate) normal distribution]() to higher dimensions. 

We use $X \sim \mathcal{N}({\mu}, {\Sigma})$ to denote that a $n$-dimensional random vector $X = \left[X_1, \ldots, X_n\right]^{\mathrm{T}}$ follows the multivariate Gaussian distribution with mean=$\mu$ and standard deviation=$\Sigma$.



The PDF for $X$ is:
$$
f_X(x; {\mu}, {\Sigma}) 
= 
\frac{1}{(2 \pi)^{n / 2}|\Sigma|^{1 / 2}} \exp \left(-\frac{1}{2}(x-\mu)^T \Sigma^{-1}(x-\mu)\right)
$$

By definition,

1. $\mu$ is the $n$-dimensional mean vector
   $$
   {\mu}=\mathrm{E}[{X}]=\left(\mathrm{E}\left[X_1\right], \mathrm{E}\left[X_2\right], \ldots, \mathrm{E}\left[X_k\right]\right)^{\mathrm{T}},
   $$

2. $\sigma^2$ is the [covariance matrix]() $\Sigma \in \mathbf{S}_{++}^n$[^2]
   $$
   \Sigma_{i, j}=\mathrm{E}\left[\left(X_i-\mu_i\right)\left(X_j-\mu_j\right)\right]=\operatorname{Cov}\left[X_i, X_j\right]
   $$
   such that $1 \leq i \leq k$ and $1 \leq j \leq k$. The inverse of the covariance matrix is called the precision matrix, denoted by $\boldsymbol{Q}=\boldsymbol{\Sigma}^{-1}$.


We also obtain that:

- $\det({\Sigma})$ is the determinant of the covariance matrix.
- ${\Sigma}^{-1}$ is the inverse of the covariance matrix.
- The quardratic term $({x} - {\mu})^\top {\Sigma}^{-1} ({x} - {\mu})$ represents the *Mahalanobis distance* from $X$ to the mean ${\mu}$, squared.

# What is $\Sigma$?

Lemma: For any random vector $X$ with mean $\mu$ and covariance matrix $\Sigma$,
$$
\Sigma := E\left[(X-\mu)(X-\mu)^T\right]=E\left[X X^T\right]-\mu \mu^T .
$$

In the definition of multivariate Gaussians, we required that the covariance matrix $\Sigma$ be symmetric positive definite (i.e., $\Sigma \in \mathbf{S}_{++}^n$ ). 

Why does this restriction exist? As seen in the following proposition, the covariance matrix of any random vector must always be symmetric positive semidefinite:

#  The covariance matrix

The concept of the *covariance matrix* is vital to understanding multivariate Gaussian distributions. Recall that for a pair of random variables $X$ and $Y$, their **covariance** is defined as
$$
\begin{aligned}
\operatorname{Cov}[X, Y]
& = E[(X-E[X])(Y-E[Y])] \\
& = E[XY- X  E[Y] - Y E(X) + E(X)E[Y])] \\ 
& = E[X Y] - E[X] E[Y] - E[X] E[Y] + E[X] E[Y] \\
& = E[X Y] - E[X] E[Y] .
\end{aligned}
$$

When working with multiple variables, the covariance matrix provides a succinct way to summarize the covariances of all pairs of variables. 

In particular, the **covariance matrix**, which we usually denote as $\Sigma$, is the $n \times n$ matrix whose $(i, j)$ th entry is $\operatorname{Cov}\left[X_i, X_j\right]$.

# Why $\Sigma$ must be symmetric positive definite? 

Lemma: Suppose that $\Sigma$ is the covariance matrix corresponding to some random vector $X$. Then $\Sigma$ is symmetric positive semidefinite.



**Proof**: The symmetry of $\Sigma$ follows immediately from its definition. Next, for any vector $z \in \mathbf{R}^n$, observe that
$$
\begin{aligned}
z^T \Sigma z & =\sum_{i=1}^n \sum_{j=1}^n\left(\Sigma_{i j} z_i z_j\right) \\
& =\sum_{i=1}^n \sum_{j=1}^n\left(\operatorname{Cov}\left[X_i, X_j\right] \cdot z_i z_j\right) \\
& =\sum_{i=1}^n \sum_{j=1}^n\left(E\left[\left(X_i-E\left[X_i\right]\right)\left(X_j-E\left[X_j\right]\right)\right] \cdot z_i z_j\right) \\
& =E\left[\sum_{i=1}^n \sum_{j=1}^n\left(X_i-E\left[X_i\right]\right)\left(X_j-E\left[X_j\right]\right) \cdot z_i z_j\right] .
\end{aligned}
$$

Then, observe that the quantity inside the brackets is of the form $\sum_i \sum_j x_i x_j z_i z_j=\left(x^T z\right)^2 \geq 0$ (see problem set \#1). Therefore, the quantity inside the expectation is always nonnegative, and hence the expectation itself must be nonnegative. We conclude that $z^T \Sigma z \geq 0$.

From the above proposition it follows that $\Sigma$ must be <u>symmetric positive semidefinite</u> in order for it to be a valid covariance matrix. However, in order for $\Sigma^{-1}$ to exist (as required in the definition of the multivariate Gaussian density), then $\Sigma$ must be **invertible** and hence full rank. Since any full rank symmetric positive semidefinite matrix is necessarily symmetric positive definite, it follows that $\Sigma$ must be **symmetric positive definite**.

# What if all elements are independent?

If all the elements $X_i$ in $X$ is independent to others, then the parameters ($\mu$ and $\Sigma$) of the PDF of $X$ are:
$$
\begin{aligned}
&\mu = [\mu_1, \mu_2, \cdots, \mu_n]^T ,
\\

&\Sigma = \left[\begin{array}{cccc}
{\sigma_1^2} & 0 & \cdots & 0 \\
0 & {\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {\sigma_d^2}
\end{array}\right] .
\end{aligned}
$$
You can see that the covariance matrix $\Sigma$ is a diagonal matrix.

Let's prove it.

## Proof: Step1

Recalling that for independent random variables $X_1,X_2, \cdots, X_n$, their joint probability is the product of each probability (-->[Source]()):
$$
f_{X_1, X_2, \cdots, X_n}(x_1,x_2,\cdots, x_n) = f_{X_1}(x_1) \cdot f_{X_2}(x_2)  \cdots  f_{X_n}(x_n)
$$
 So, the PDF of normal variable $X = \left[X_1, \ldots, X_n\right]^{\mathrm{T}}$ can be represented as:
$$
\begin{align}
f_{X}(X) 
& := f_{X_1, X_2, \cdots, X_n} (x_1,x_2,\cdots, x_n) \label{eq_independent} \\
& =  f_{X_1}(x_1) \cdot f_{X_2}(x_2)  \cdots  f_{X_n}(x_n) . \nonumber
\end{align}
$$
Recalling that for any [univariate normal variable]() $X_i$ ($i \in \{1,2,\cdots,n\}$), its PDF is:
$$
f_{X_i}(x_i)=\frac{1}{\sigma_i \sqrt{2 \pi}} e^{-\frac{1}{2}\left(\frac{x_i-\mu_i}{\sigma_i}\right)^2}
$$
Therefore, we obtain:
$$
\begin{aligned}
f_{X}(X) =
f_{X_1}(x_1) \cdot f_{X_2}(x_2)  \cdots  f_{X_n}(x_n) 
& = 
\frac{1}{\sigma_1 \sqrt{2 \pi}} e^{-\frac{1}{2}\left(\frac{x_1-\mu_1}{\sigma_1}\right)^2}
\cdot
\frac{1}{\sigma_2 \sqrt{2 \pi}} e^{-\frac{1}{2}\left(\frac{x_2-\mu_2}{\sigma_2}\right)^2}
\cdots
\frac{1}{\sigma_n \sqrt{2 \pi}} e^{-\frac{1}{2}\left(\frac{x_n-\mu_n}{\sigma_n}\right)^2}
\\
& = 
\frac{1}{{(2 \pi)}^{n/2} \sigma_1 \sigma_2 \cdots \sigma_n } 
\exp(
-\frac{1}{2} 
[(\frac{x_1-\mu_1}{\sigma_1})^2 + (\frac{x_2-\mu_2}{\sigma_2})^2 + \cdots + (\frac{x_n-\mu_n}{\sigma_n})^2]
)

\end{aligned}
$$


The basic idea of our proof is to leverage the fact that the denifition of PDF of $X$
$$
f_X(x)
= 
\frac{1}{(2 \pi)^{n / 2}|\Sigma|^{1 / 2}} \exp \left(-\frac{1}{2}(x-\mu)^T \Sigma^{-1}(x-\mu)\right)
$$
equals to the joint probalility of all the independent elements of $X$,
$$
\begin{aligned}
f_{X_1}(x_1) \cdot f_{X_2}(x_2)  \cdots  f_{X_n}(x_n) 
= 
\frac{1}{{(2 \pi)}^{n/2} \sigma_1 \sigma_2 \cdots \sigma_n } 
\exp(
-\frac{1}{2} 
[(\frac{x_1-\mu_1}{\sigma_1})^2 + (\frac{x_2-\mu_2}{\sigma_2})^2 + \cdots + (\frac{x_n-\mu_n}{\sigma_n})^2]
)

\end{aligned}
$$
to construct the $\mu$ and $\Sigma$, which are what we want.

## Proof: Step2

Consider matrix
$$
\left[\begin{array}{cccc}
{\sigma_1^2} & 0 & \cdots & 0 \\
0 & {\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {\sigma_d^2}
\end{array}\right] ,
$$
it has two properties:

First, 
$$
\left|
\begin{array}{cccc}
{\sigma_1^2} & 0 & \cdots & 0 \\
0 & {\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {\sigma_d^2}
\end{array} 
\right| 
^{1/2}

= \sigma_1 \sigma_2 \cdots \sigma_n .
$$
Second, 
$$
\left(\frac{x_1-\mu_1}{\sigma_1}\right)^2+\left(\frac{x_2-\mu_2}{\sigma_2}\right)^2+\cdots+\left(\frac{x_d-\mu_1}{\sigma_d}\right)^2 

=
\left[x_1-\mu_1, x_2-\mu_2, \cdots, x_d-\mu_d\right]

\left[\begin{array}{cccc}
\frac{1}{\sigma_1^2} & 0 & \cdots & 0 \\
0 & \frac{1}{\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & \frac{1}{\sigma_d^2}
\end{array}\right]

\left[\begin{array}{c}
x_1-\mu_1 \\
x_2-\mu_2 \\
\vdots \\
x_d-\mu_d
\end{array}\right]
.
$$


Thus,
$$
f_{X}(X) 
=
\cdots
=
\frac{1}{
{(2 \pi)}^{n/2} 
\left|
\begin{array}{cccc}
{\sigma_1^2} & 0 & \cdots & 0 \\
0 & {\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {\sigma_d^2}
\end{array} 
\right| 
^{1/2}
} 

\exp(
-\frac{1}{2} 
[
\left[x_1-\mu_1, x_2-\mu_2, \cdots, x_n-\mu_n\right]

\left[\begin{array}{cccc}
\frac{1}{\sigma_1^2} & 0 & \cdots & 0 \\
0 & \frac{1}{\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & \frac{1}{\sigma_d^2}
\end{array}\right]

\left[\begin{array}{c}
x_1-\mu_1 \\
x_2-\mu_2 \\
\vdots \\
x_d-\mu_d
\end{array}\right]]
) .
$$


Compare this equation and the PDF of $f_X(x)$, we can consctrct our parameters as
$$
\begin{aligned}
&\mu = [\mu_1, \mu_2, \cdots, \mu_n]^T ,
\\

&\Sigma = \left[\begin{array}{cccc}
{\sigma_1^2} & 0 & \cdots & 0 \\
0 & {\sigma_2^2} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {\sigma_d^2}
\end{array}\right] .
\end{aligned}
$$

## Other gains

One useful ovservation drawn from this section is that if $Z \sim \mathcal{N}(0, I)$, then $Z$ can be thought of as a collection of $n$ independent standard normal random variables (i.e., $Z_i \sim \mathcal{N}(0,1)$), because
$$
\begin{aligned}
& \mu = O ,
\\

& \Sigma = \left[\begin{array}{cccc}
{1} & 0 & \cdots & 0 \\
0 & {1} & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & {1}
\end{array}\right] .
\end{aligned}
$$


# Isocontours

One way to understand a multivariate Gaussian conceptually is to understand the shape of its isocontours. For a function $f: \mathbf{R}^2 \rightarrow \mathbf{R}$, an isocontour is a set of the form
$$
\left\{x \in \mathbf{R}^2: f(x)=c\right\} .
$$
for some $c \in \mathbf{R}{ }^4$.

## Shape of isocontours

What do the isocontours of a multivariate Gaussian look like? As before, let's consider the case where $n=2$, and $\Sigma$ is **diagonal**, i.e.,
$$
x=\left[\begin{array}{l}
x_1 \\
x_2
\end{array}\right] \quad \mu=\left[\begin{array}{l}
\mu_1 \\
\mu_2
\end{array}\right] \quad \Sigma=\left[\begin{array}{cc}
\sigma_1^2 & 0 \\
0 & \sigma_2^2
\end{array}\right]
$$

The PDF is
$$
f(x ; \mu, \Sigma)=\frac{1}{2 \pi \sigma_1 \sigma_2} \exp \left(-\frac{1}{2 \sigma_1^2}\left(x_1-\mu_1\right)^2-\frac{1}{2 \sigma_2^2}\left(x_2-\mu_2\right)^2\right) .
$$

Now, let's consider the level set consisting of all points where $p(x ; \mu, \Sigma)=c$ for some constant $c \in \mathbf{R}$. In particular, consider the set of all $x_1, x_2 \in \mathbf{R}$ such that
$$
\begin{aligned}
c & =\frac{1}{2 \pi \sigma_1 \sigma_2} \exp \left(-\frac{1}{2 \sigma_1^2}\left(x_1-\mu_1\right)^2-\frac{1}{2 \sigma_2^2}\left(x_2-\mu_2\right)^2\right) \\
2 \pi c \sigma_1 \sigma_2 & =\exp \left(-\frac{1}{2 \sigma_1^2}\left(x_1-\mu_1\right)^2-\frac{1}{2 \sigma_2^2}\left(x_2-\mu_2\right)^2\right) \\
\log \left(2 \pi c \sigma_1 \sigma_2\right) & =-\frac{1}{2 \sigma_1^2}\left(x_1-\mu_1\right)^2-\frac{1}{2 \sigma_2^2}\left(x_2-\mu_2\right)^2 \\
\log \left(\frac{1}{2 \pi c \sigma_1 \sigma_2}\right) & =\frac{1}{2 \sigma_1^2}\left(x_1-\mu_1\right)^2+\frac{1}{2 \sigma_2^2}\left(x_2-\mu_2\right)^2 \\
1 & =\frac{\left(x_1-\mu_1\right)^2}{2 \sigma_1^2 \log \left(\frac{1}{2 \pi c \sigma_1 \sigma_2}\right)}+\frac{\left(x_2-\mu_2\right)^2}{2 \sigma_2^2 \log \left(\frac{1}{2 \pi c \sigma_1 \sigma_2}\right)} .
\end{aligned}
$$

Defining
$$
r_1=\sqrt{2 \sigma_1^2 \log \left(\frac{1}{2 \pi c \sigma_1 \sigma_2}\right)} \quad r_2=\sqrt{2 \sigma_2^2 \log \left(\frac{1}{2 \pi c \sigma_1 \sigma_2}\right)},
$$
it follows that
$$
\begin{equation} \label{ellipse}
1=\left(\frac{x_1-\mu_1}{r_1}\right)^2+\left(\frac{x_2-\mu_2}{r_2}\right)^2 .
\end{equation}
$$

Equation $\eqref{ellipse}$ **is the equation of an axis-aligned ellipse**, with center $\left(\mu_1, \mu_2\right)$, where the $x_1$ axis has length $2 r_1$ and the $x_2$ axis has length $2 r_2$.
## Length of axes

To get a better understanding of how the shape of the level curves vary as a function of the variances of the multivariate Gaussian distribution, suppose that we are interested in



The figure on the left shows a heatmap indicating values of the density function for an axis-aligned multivariate Gaussian with mean $\mu=\left[\begin{array}{l}3 \\ 2\end{array}\right]$ and diagonal covariance matrix $\Sigma=$ $\left[\begin{array}{cr}25 & 0 \\ 0 & 9\end{array}\right]$. Notice that the Gaussian is centered at $(3,2)$, and that the isocontours are all elliptically shaped with major/minor axis lengths in a 5:3 ratio. 

The figure on the right shows a heatmap indicating values of the density function for a non axis-aligned multivariate Gaussian with mean $\mu=\left[\begin{array}{l}3 \\ 2\end{array}\right]$ and covariance matrix $\Sigma=\left[\begin{array}{cc}10 & 5 \\ 5 & 5\end{array}\right]$. Here, the ellipses are again centered at $(3,2)$, but now the major and minor axes have been rotated via a linear transformation (because its covariance matrix isn't diagonal), the values of $r_1$ and $r_2$ at which $c$ is equal to a fraction $1 / e$ of the peak height of Gaussian density.

First, observe that maximum of Equation (4) occurs where $x_1=\mu_1$ and $x_2=\mu_2$. Substituting these values into Equation (4), we see that the peak height of the Gaussian density is $\frac{1}{2 \pi \sigma_1 \sigma_2}$.
Second, we substitute $c=\frac{1}{e}\left(\frac{1}{2 \pi \sigma_1 \sigma_2}\right)$ into the equations for $r_1$ and $r_2$ to obtain
$$
\begin{aligned}
& r_1=\sqrt{2 \sigma_1^2 \log \left(\frac{1}{2 \pi \sigma_1 \sigma_2 \cdot \frac{1}{e}\left(\frac{1}{2 \pi \sigma_1 \sigma_2}\right)}\right)}=\sigma_1 \sqrt{2} \\
& r_2=\sqrt{2 \sigma_2^2 \log \left(\frac{1}{2 \pi \sigma_1 \sigma_2 \cdot \frac{1}{e}\left(\frac{1}{2 \pi \sigma_1 \sigma_2}\right)}\right)}=\sigma_2 \sqrt{2} .
\end{aligned}
$$

From this, it follows that the axis length needed to reach a fraction 1/e of the peak height of the Gaussian density in the $i$ th dimension grows in proportion to the standard deviation $\sigma_i$. Intuitively, this again makes sense: the smaller the variance of some random variable $x_i$, the more "tightly" peaked the Gaussian distribution in that dimension, and hence the smaller the radius $r_i$.

# Linear Linear transformation interpretation

Theorem: Let $X \sim \mathcal{N}(\mu, \Sigma)$ for some $\mu \in \mathbf{R}^n$ and $\Sigma \in \mathbf{S}_{++}^n$. Then, there exists a matrix $B \in \mathbf{R}^{n \times n}$ such that if we define $Z=B^{-1}(X-\mu)$, then $Z \sim \mathcal{N}(0, I)$.



Proof:

1. As before said, if $Z \sim \mathcal{N}(0, I)$, then it can be thought of as a collection of $n$ independent standard normal random variables (i.e., $Z_i \sim \mathcal{N}(0,1)$ ). 
2. Furthermore, if $Z=B^{-1}(X-\mu)$ then $X=B Z+\mu$ follows from simple algebra. 
3. Consequently, the theorem states that any random variable $X$ with a multivariate Gaussian distribution can be interpreted as the result of applying a linear transformation $(X=$ $B Z+\mu)$ to some collection of $n$ independent standard normal random variables $(Z)$.



[^1]: Probability density function
[^2]: Recall from the section notes on linear algebra that $\mathbf{S}_{++}^n$ is the space of symmetric positive definite $n \times n$ matrices, defined as

$$
\mathbf{S}_{++}^n =
\{
A \in \mathbf{R}^{n \times n}: A=A^T
\ \text{and} \quad 
x^T A x>0 
\quad \text{for \ all} \ 
x \in \mathbf{R}^n \ \text{such \ that} \ x \neq 0
\} .
$$

