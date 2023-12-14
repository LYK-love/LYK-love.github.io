---
title: Differential Entropy
tags:
---





# Differential Entropy

Definition Let $X$ be a random variable with cumulative distribution function $F(x)=\operatorname{Pr}(X \leq x)$. If $F(x)$ is continuous, the random variable is said to be continuous. Let $f(x)=F^{\prime}(x)$ when the derivative is defined. If $\int_{-\infty}^{\infty} f(x)=1, f(x)$ is called the probability density function for $X$. The set where $f(x)>0$ is called the support set of $X$.

Definition The differential entropy $h(X)$ of a continuous random variable $X$ with density $f(x)$ is defined as
$$
h(X)=-\int_S f(x) \log f(x) d x
$$
where $S$ is the support set of the random variable.
As in the discrete case, the differential entropy depends only on the probability density of the random variable, and therefore the differential entropy is sometimes written as $h(f)$ rather than $h(X)$.

## Example: Uniform distribution

Example 8.1.1 (Uniform distribution) Consider a random variable distributed uniformly from 0 to $a$ so that its density is $1 / a$ from 0 to $a$ and 0 elsewhere. Then its differential entropy is
$$
h(X)=-\int_0^a \frac{1}{a} \log \frac{1}{a} d x=\log a .
$$

Note: For $a<1, \log a<0$, and the differential entropy is negative. Hence, unlike discrete entropy, differential entropy can be negative. However, $2^{h(X)}=2^{\log a}=a$ is the volume of the support set, which is always nonnegative, as we expect.

## Example: Normal distribution

Example 8.1.2 (Normal distribution) Let $X \sim \phi(x)=\frac{1}{\sqrt{2 \pi \sigma^2}} e^{\frac{-x^2}{2 \sigma^2}}$. Then calculating the differential entropy in nats, we obtain
$$
\begin{aligned}
h(\phi) & =-\int \phi \ln \phi \\
& =-\int \phi(x)\left[-\frac{x^2}{2 \sigma^2}-\ln \sqrt{2 \pi \sigma^2}\right] \\
& =\frac{E X^2}{2 \sigma^2}+\frac{1}{2} \ln 2 \pi \sigma^2 \\
& =\frac{1}{2}+\frac{1}{2} \ln 2 \pi \sigma^2 \\
& =\frac{1}{2} \ln e+\frac{1}{2} \ln 2 \pi \sigma^2 \\
& =\frac{1}{2} \ln 2 \pi e \sigma^2 \quad \text { nats. }
\end{aligned}
$$

Changing the base of the logarithm, we have
$$
h(\phi)=\frac{1}{2} \log 2 \pi e \sigma^2 \quad \text { bits. }
$$

# JOINT AND CONDITIONAL DIFFERENTIAL ENTROPY

As in the discrete case, we can extend the definition of differential entropy of a single random variable to several random variables.

Definition The differential entropy of a set $X_1, X_2, \ldots, X_n$ of random variables with density $f\left(x_1, x_2, \ldots, x_n\right)$ is defined as
$$
h\left(X_1, X_2, \ldots, X_n\right)=-\int f\left(x^n\right) \log f\left(x^n\right) d x^n .
$$

Definition If $X, Y$ have a joint density function $f(x, y)$, we can define the conditional differential entropy $h(X \mid Y)$ as
$$
h(X \mid Y)=-\int f(x, y) \log f(x \mid y) d x d y .
$$

Since in general $f(x \mid y)=f(x, y) / f(y)$, we can also write
$$
h(X \mid Y)=h(X, Y)-h(Y) .
$$

But we must be careful if any of the differential entropies are infinite.
The next entropy evaluation is used frequently in the text.

## Entropy of a multivariate normal distribution

Theorem 8.4.1 (Entropy of a multivariate normal distribution) Let $X_1, X_2, \ldots, X_n$ have a multivariate normal distribution with mean $\mu$ and covariance matrix $K$. Then
$$
h\left(X_1, X_2, \ldots, X_n\right)=h\left(\mathcal{N}_n(\mu, K)\right)=\frac{1}{2} \log (2 \pi e)^n|K| \quad \text { bits, }
$$
where $|K|$ denotes the determinant of $K$.

Theorem 8.4.1 (Entropy of a multivariate normal distribution) Let $X_1, X_2, \ldots, X_n$ have a multivariate normal distribution with mean $\mu$ and covariance matrix $K$. Then
$$
h\left(X_1, X_2, \ldots, X_n\right)=h\left(\mathcal{N}_n(\mu, K)\right)=\frac{1}{2} \log (2 \pi e)^n|K| \quad \text { bits, }
$$
where $|K|$ denotes the determinant of $K$.



# Properties of Differential Entropy

Theorem 8.6.1
$$
D(f \| g) \geq 0
$$
with equality iff $f=g$ almost everywhere (a.e.).
Proof: Let $S$ be the support set of $f$. Then
$$
\begin{aligned}
-D(f \| g) & =\int_S f \log \frac{g}{f} \\
& \leq \log \int_S f \frac{g}{f} \quad \text { (by Jensen's inequality) }
\end{aligned}
$$
(by Jensen's inequality)
$$
\begin{aligned}
& =\log \int_S g \\
& \leq \log 1=0 .
\end{aligned}
$$

We have equality iff we have equality in Jensen's inequality, which occurs iff $f=g$ a.e.

Corollary $I(X ; Y) \geq 0$ with equality iff $X$ and $Y$ are independent.
Corollary $h(X \mid Y) \leq h(X)$ with equality iff $X$ and $Y$ are independent.

## Theorem: Chain rule for differential entropy

$$
h\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n h\left(X_i \mid X_1, X_2, \ldots, X_{i-1}\right) .
$$

Proof: Follows directly from the definitions.

## Corollary $h\left(X_1, X_2, \ldots, X_n\right) \leq \sum h\left(X_i\right)$

Corollary
$$
h\left(X_1, X_2, \ldots, X_n\right) \leq \sum h\left(X_i\right)
$$
with equality iff $X_1, X_2, \ldots, X_n$ are independent.
Proof: Follows directly from Theorem 8.6.2 and the corollary to Theorem 8.6.1.

Application (Hadamard's inequality) If we let $\mathbf{X} \sim \mathcal{N}(0, K)$ be a multivariate normal random variable, calculating the entropy in the above inequality gives us
$$
|K| \leq \prod_{i=1}^n K_{i i}
$$
which is Hadamard's inequality. A number of determinant inequalities can be derived in this fashion from information-theoretic inequalities (Chapter 17).

## Theorem: $h(X+c)=h(X)$

$$
h(X+c)=h(X)
$$

Translation does not change the differential entropy.
Proof: Follows directly from the definition of differential entropy.

## Theorem: $h(a X)=h(X)+\log |a|$

$$
h(a X)=h(X)+\log |a| .
$$

Proof: Let $Y=a X$. Then $f_Y(y)=\frac{1}{|a|} f_X\left(\frac{y}{a}\right)$, and
$$
\begin{aligned}
h(a X) & =-\int f_Y(y) \log f_Y(y) d y \\
& =-\int \frac{1}{|a|} f_X\left(\frac{y}{a}\right) \log \left(\frac{1}{|a|} f_X\left(\frac{y}{a}\right)\right) d y \\
& =-\int f_X(x) \log f_X(x) d x+\log |a| \\
& =h(X)+\log |a|,
\end{aligned}
$$
after a change of variables in the integral.
Similarly, we can prove the following corollary for vector-valued random variables.

## Corollary $h(A \mathbf{X})=h(\mathbf{X})+\log |\operatorname{det}(A) |$

$$
h(A \mathbf{X})=h(\mathbf{X})+\log |\operatorname{det}(A)| .
$$

We now show that the multivariate normal distribution maximizes the entropy over all distributions with the same covariance.

## Theorem: $h(\mathbf{X}) \leq \frac{1}{2} \log (2 \pi e)^n|K|$

Theorem 8.6.5 Let the random vector $\mathbf{X} \in \mathbf{R}^n$ have zero mean and covariance $K=E \mathbf{X X}^t$ (i.e., $K_{i j}=E X_i X_j, 1 \leq i, j \leq n$ ). 

Then $h(\mathbf{X}) \leq \frac{1}{2} \log (2 \pi e)^n|K|$, with equality iff $\mathbf{X} \sim \mathcal{N}(0, K)$.



Proof: Let $g(\mathbf{x})$ be any density satisfying $\int g(\mathbf{x}) x_i x_j d \mathbf{x}=K_{i j}$ for all $i, j$. Let $\phi_K$ be the density of a $\mathcal{N}(0, K)$ vector as given in (8.35), where we set $\mu=0$. Note that $\log \phi_K(\mathbf{x})$ is a quadratic form and $\int x_i x_j \phi_K(\mathbf{x}) d \mathbf{x}=$ $K_{i j}$. Then
$$
\begin{aligned}
0 & \leq D\left(g \| \phi_K\right) \\
& =\int g \log \left(g / \phi_K\right) \\
& =-h(g)-\int g \log \phi_K
\end{aligned}
$$
