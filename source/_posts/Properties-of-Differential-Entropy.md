---
title: Properties of Differential Entropy
tags:
  - Information Theory
categories: Mathematics
mathjax: true
date: 2024-01-25 16:08:03
---


Source:

1. Thomas M. Cover & Joy A. Thomas. (2006). *Chapter 8. Differential Entropy. Elements of Information Theory* (2nd ed., pp. 243-255). Wiley-Interscience.
2. Fady Alajaji & Po-Ning Chen. (2018). *Chapter 5. Differential Entropy and Gaussian Channels. An Introduction to Single-User Information Theory* (1st ed., pp. 165-218). Springer.

<!--more-->

# Notations

* Note that the joint pdf $f_{X, Y}$ is also commonly written as $f_{X Y}$.

# Joint differential entropy

Defnition: If $X^n=\left(X_1, X_2, \ldots, X_n\right)$ is a continuous random vector of size $n$ (i.e., a vector of $n$ continuous random variables) with joint pdf $f_{X^n}$ and support $S_{X^n} \subseteq \mathbb{R}^n$, then its **joint differential entropy** is defined as
$$
\begin{aligned}
h\left(X^n\right) & :=-\int_{S_{X^n}} f_{X^n}\left(x_1, x_2, \ldots, x_n\right) \log _2 f_{X^n}\left(x_1, x_2, \ldots, x_n\right) d x_1 d x_2 \cdots d x_n \\
& =E\left[-\log _2 f_{X^n}\left(X^n\right)\right]
\end{aligned}
$$
when the $n$-dimensional integral exists.



By contrast, entropy and differential entropy are sometimes called *discrete entropy* and *continuous entropy*, respectively.

# Conditional differential entropy

**Definition**:Let $X$ and $Y$ be two jointly distributed continuous random variables with joint $\operatorname{pdf}^4 f_{X, Y}$ and support $S_{X, Y} \subseteq \mathbb{R}^2$ such that the conditional pdf of $Y$ given $X$, given by
$$
f_{Y \mid X}(y \mid x)=\frac{f_{X, Y}(x, y)}{f_X(x)}
$$
is well defined for all $(x, y) \in S_{X, Y}$, where $f_X$ is the marginal pdf of $X$. Then, the conditional differential entropy of $Y$ given $X$ is defined as
$$
h(Y \mid X):=-\int_{S_{X, Y}} f_{X, Y}(x, y) \log _2 f_{Y \mid X}(y \mid x) d x d y=E\left[-\log _2 f_{Y \mid X}(Y \mid X)\right],
$$
when the integral exists.
Note that as in the case of (discrete) entropy, the chain rule holds for differential entropy:
$$
h(X, Y)=h(X)+h(Y \mid X)=h(Y)+h(X \mid Y) .
$$

# Relative entropy

Definition: Let $X$ and $Y$ be two continuous random variables with marginal pdfs $f_X$ and $f_Y$, respectively, such that their supports satisfy $S_X \subseteq S_Y \subseteq \mathbb{R}$. Then, the **KL-divergence (or relative entropy)** between $X$ and $Y$ is written as $D(X \| Y)$ or $D\left(f_X \| f_Y\right)$ and defined by
$$
D(X \| Y):=\int_{S_X} f_X(x) \log _2 \frac{f_X(x)}{f_Y(x)} d x=E\left[\frac{f_X(X)}{f_Y(X)}\right]
$$
when the integral exists. The definition carries over similarly in the multivariate case: for $X^n=\left(X_1, X_2, \ldots, X_n\right)$ and $Y^n=\left(Y_1, Y_2, \ldots, Y_n\right)$ two random vectors with joint pdfs $f_{X^n}$ and $f_{Y^n}$, respectively, and supports satisfying $S_{X^n} \subseteq S_{Y^n} \subseteq \mathbb{R}^n$, the divergence between $X^n$ and $Y^n$ is defined as
$$
D\left(X^n \| Y^n\right):=\int_{S_{X^n}} f_{X^n}\left(x_1, x_2, \ldots, x_n\right) \log _2 \frac{f_{X^n}\left(x_1, x_2, \ldots, x_n\right)}{f_{Y^n}\left(x_1, x_2, \ldots, x_n\right)} d x_1 d x_2 \cdots d x_n
$$
when the integral exists.

# Mutual information

Definition: Let $X$ and $Y$ be two jointly distributed continuous random variables with joint pdf $f_{X, Y}$ and support $S_{X Y} \subseteq \mathbb{R}^2$. Then, the **mutual information** between $X$ and $Y$ is defined by
$$
I(X ; Y):=D\left(f_{X, Y} \| f_X f_Y\right)=\int_{S_{X, Y}} f_{X, Y}(x, y) \log _2 \frac{f_{X, Y}(x, y)}{f_X(x) f_Y(y)} d x d y,
$$
assuming the integral exists, where $f_X$ and $f_Y$ are the marginal pdfs of $X$ and $Y$, respectively.

Observation 5.13 For two jointly distributed continuous random variables $X$ and $Y$ with joint pdf $f_{X, Y}$, support $S_{X Y} \subseteq \mathbb{R}^2$ and joint differential entropy
$$
h(X, Y)=-\int_{S_{X Y}} f_{X, Y}(x, y) \log _2 f_{X, Y}(x, y) d x d y,
$$
then as in Lemma 5.2 and the ensuing discussion, one can write
$$
H\left(q_n(X), q_m(Y)\right) \approx h(X, Y)+n+m
$$
for $n$ and $m$ sufficiently large, where $q_k(Z)$ denotes the (uniformly) quantized version of random variable $Z$ with a $k$-bit accuracy.
On the other hand, for the above continuous $X$ and $Y$,
$$
\begin{aligned}
I\left(q_n(X) ; q_m(Y)\right) & =H\left(q_n(X)\right)+H\left(q_m(Y)\right)-H\left(q_n(X), q_m(Y)\right) \\
& \approx[h(X)+n]+[h(Y)+m]-[h(X, Y)+n+m] \\
& =h(X)+h(Y)-h(X, Y) \\
& =\int_{S_{X, Y}} f_{X, Y}(x, y) \log _2 \frac{f_{X, Y}(x, y)}{f_X(x) f_Y(y)} d x d y
\end{aligned}
$$
for $n$ and $m$ sufficiently large; in other words,
$$
\lim _{n, m \rightarrow \infty} I\left(q_n(X) ; q_m(Y)\right)=h(X)+h(Y)-h(X, Y) .
$$

Furthermore, it can be shown that
$$
\lim _{n \rightarrow \infty} D\left(q_n(X) \| q_n(Y)\right)=\int_{S_X} f_X(x) \log _2 \frac{f_X(x)}{f_Y(x)} d x
$$

Thus, mutual information and divergence can be considered as the true tools of information theory, as they retain the same operational characteristics and properties for both discrete and continuous probability spaces (as well as general spaces where they can be defined in terms of Radon-Nikodym derivatives[^1].

# Properties

The following properties hold for the information measures of continuous systems.

//TODO: Proves

## Nonnegativity of divergence

Nonnegativity of divergence: Let $X$ and $Y$ be two continuous random variables with marginal pdfs $f_X$ and $f_Y$, respectively, such that their supports satisfy $S_X \subseteq S_Y \subseteq \mathbb{R}$. Then
$$
D\left(f_X \| f_Y\right) \geq 0
$$
with equality iff $f_X(x)=f_Y(x)$ for all $x \in S_X$ except in a set of $f_X$-measure zero (i.e., $X=Y$ almost surely).
## Nonnegativity of mutual information

Nonnegativity of mutual information: For any two continuous jointly distributed random variables $X$ and $Y$,
$$
I(X ; Y) \geq 0,
$$
with equality iff $X$ and $Y$ are independent.
## Conditioning never increases differential entropy

For any two continuous random variables $X$ and $Y$ with joint pdf $f_{X, Y}$ and well-defined conditional pdf $f_{X \mid Y}$
$$
h(X \mid Y) \leq h(X),
$$
with equality iff $X$ and $Y$ are independent.
## Chain rule for differential entropy

For a continuous random vector $X^n=$ $\left(X_1, X_2, \ldots, X_n\right)$,
$$
h\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n h\left(X_i \mid X_1, X_2, \ldots, X_{i-1}\right),
$$
where $h\left(X_i \mid X_1, X_2, \ldots, X_{i-1}\right):=h\left(X_1\right)$ for $i=1$.

## Chain rule for mutual information

For continuous random vector $X^n=$ $\left(X_1, X_2, \ldots, X_n\right)$ and random variable $Y$ with joint $p d f f_{X^n, Y}$ and well-defined conditional pdfs $f_{X_i, Y \mid X^{i-1}}, f_{X_i \mid X^{i-1}}$ and $f_{Y \mid X^{i-1}}$ for $i=1, \ldots, n$, we have that
$$
I\left(X_1, X_2, \ldots, X_n ; Y\right)=\sum_{i=1}^n I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right),
$$
where $I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right):=I\left(X_1 ; Y\right)$ for $i=1$.
## Data processing inequality

For continuous random variables $X, Y$, and $Z$ such that $X \rightarrow Y \rightarrow Z$, i.e., $X$ and $Z$ are conditional independent given $Y$,
$$
I(X ; Y) \geq I(X ; Z) .
$$
## Independence bound for differential entropy

For a continuous random vector $X^n=\left(X_1, X_2, \ldots, X_n\right)$,
$$
h\left(X^n\right) \leq \sum_{i=1}^n h\left(X_i\right)
$$
with equality iff all the $X_i$ 's are independent from each other.
## Invariance of differential entropy under translation

For continuous random variables $X$ and $Y$ with joint pdf $f_{X, Y}$ and well-defined conditional pdf $f_{X \mid Y}$,
$$
h(X+c)=h(X) \quad \text { for any constant } c \in \mathbb{R},
$$
and
$$
h(X+Y \mid Y)=h(X \mid Y) .
$$

The results also generalize in the multivariate case: for two continuous random vectors $X^n=\left(X_1, X_2, \ldots, X_n\right)$ and $Y^n=\left(Y_1, Y_2, \ldots, Y_n\right)$ with joint pdf $f_{X^n, Y^n}$ and well-defined conditional pdf $f_{X^n \mid Y^n}$,
$$
h\left(X^n+c^n\right)=h\left(X^n\right)
$$
for any constant $n$-tuple $c^n=\left(c_1, c_2, \ldots, c_n\right) \in \mathbb{R}^n$, and
$$
h\left(X^n+Y^n \mid Y^n\right)=h\left(X^n \mid Y^n\right),
$$
where the addition of two n-tuples is performed component-wise.
## Differential entropy under scaling

For any continuous random variable $X$ and any nonzero real constant $a$,
$$
h(a X)=h(X)+\log _2|a| .
$$

## Joint differential entropy under linear mapping

Consider the random (column) vector $\underline{X}=\left(X_1, X_2, \ldots, X_n\right)^T$ with joint $p d f f_{X^n}$, where $T$ denotes transposition, and let $\underline{Y}=\left(Y_1, Y_2, \ldots, Y_n\right)^T$ be a random (column) vector obtained from the linear transformation $\underline{Y}=\mathbf{A} \underline{X}$, where $\mathbf{A}$ is an invertible (non-singular) $n \times n$ real-valued matrix. Then
$$
h(\underline{Y})=h\left(Y_1, Y_2, \ldots, Y_n\right)=h\left(X_1, X_2, \ldots, X_n\right)+\log _2|\operatorname{det}(\mathbf{A})|,
$$
where $\operatorname{det}(\mathbf{A})$ is the determinant of the square matrix $\mathbf{A}$.
## Joint differential entropy under nonlinear mapping

Consider the random (column) vector $\underline{X}=\left(X_1, X_2, \ldots, X_n\right)^T$ with joint pdf $f_{X^n}$, and let $\underline{Y}=\left(Y_1, Y_2, \ldots, Y_n\right)^T$ be a random (column) vector obtained from the nonlinear transformation
$$
\underline{Y}=\underline{g}(\underline{X}):=\left(g_1\left(X_1\right), g_2\left(X_2\right), \ldots, g_n\left(X_n\right)\right)^T,
$$
where each $g_i: \mathbb{R} \rightarrow \mathbb{R}$ is a differentiable function, $i=1,2, \ldots, n$. Then
$$
\begin{aligned}
h(\underline{Y}) & =h\left(Y_1, Y_2, \ldots, Y_n\right) \\
& =h\left(X_1, \ldots, X_n\right)+\int_{\mathbb{R}^n} f_{X^n}\left(x_1, \ldots, x_n\right) \log _2|\operatorname{det}(\mathbf{J})| d x_1 \cdots d x_n,
\end{aligned}
$$
where $\mathbf{J}$ is the $n \times n$ Jacobian matrix given by
$$
\mathbf{J}:=\left[\begin{array}{cccc}
\frac{\partial g_1}{\partial x_1} & \frac{\partial g_1}{\partial x_2} & \cdots & \frac{\partial g_1}{\partial x_n} \\
\frac{\partial g_2}{\partial x_1} & \frac{\partial g_2}{\partial x_2} & \cdots & \frac{\partial g_2}{\partial x_n} \\
\vdots & \vdots & \cdots & \vdots \\
\frac{\partial g_n}{\partial x_1} & \frac{\partial g_n}{\partial x_2} & \cdots & \frac{\partial g_n}{\partial x_n}
\end{array}\right] .
$$



**Observation**: Property [Differential entropy under scaling]() of the above Lemma indicates that for a continuous random variable $X, h(X) \neq h(a X)$ (except for the trivial case of $a=1$ ) and hence differential entropy is not in general invariant under invertible maps. This is in contrast to entropy, which is always invariant under invertible maps: given a discrete random variable $X$ with alphabet $\mathcal{X}$,
$$
H(f(X))=H(X)
$$
for all invertible maps $f: \mathcal{X} \rightarrow \mathcal{Y}$, where $\mathcal{Y}$ is a discrete set; in particular $H(a X)=$ $H(X)$ for all nonzero reals $a$.

On the other hand, for both discrete and continuous systems, mutual information and divergence are invariant under invertible maps:
$$
I(X ; Y)=I(g(X) ; Y)=I(g(X) ; h(Y))
$$
and
$$
D(X \| Y)=D(g(X) \| g(Y))
$$
for all invertible maps $g$ and $h$ properly defined on the alphabet/support of the concerned random variables. This reinforces the notion that mutual information and divergence constitute the true tools of information theory.

# Joint differential entropy of the multivariate Gaussian

If $\underline{X} \sim$ $\mathcal{N}_n\left(\underline{\mu}, \mathbf{K}_{\underline{X}}\right)$ is a Gaussian random vector with mean vector $\underline{\mu}$ and (positive-definite) covariance matrix $\mathbf{K}_{\underline{X}}$, then its **joint differential entropy** is given by
$$
h(\underline{X})=h\left(X_1, X_2, \ldots, X_n\right)=\frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right] .
$$

In particular, in the univariate case of $n=1,(5.2 .1)$ reduces to (5.1.1).
Proof Without loss of generality, we assume that $\underline{X}$ has a zero-mean vector since its differential entropy is invariant under translation by Property 8 of Lemma 5.14:
$$
h(\underline{X})=h(\underline{X}-\underline{\mu})
$$
so we assume that $\underline{\mu}=\underline{0}$.

Since the covariance matrix $\mathbf{K}_{\underline{X}}$ is a real-valued symmetric matrix, then it is orthogonally diagonizable; i.e., there exists a square $(n \times n)$ orthogonal matrix $\mathbf{A}$ (i.e., satisfying $\mathbf{A}^T=\mathbf{A}^{-1}$ ) such that $\mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^T$ is a diagonal matrix whose entries are given by the eigenvalues of $\mathbf{K}_{\underline{X}}$ (A is constructed using the eigenvectors of $\mathbf{K}_{\underline{X}}$; e.g., see [128]). As a result, the linear transformation $\underline{Y}=\mathbf{A} \underline{X} \sim \mathcal{N}_n\left(\underline{0}, \mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^{\underline{T}}\right)$ is a Gaussian vector with the diagonal covariance matrix $\mathbf{K}_{\underline{Y}}=\mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^T$ and has therefore independent components (as noted in Observation 5.17). Thus
$$
\begin{aligned}
h(\underline{Y}) & =h\left(Y_1, Y_2, \ldots, Y_n\right) \\
& =h\left(Y_1\right)+h\left(Y_2\right)+\cdots+h\left(Y_n\right) \\
& =\sum_{i=1}^n \frac{1}{2} \log _2\left[2 \pi e \operatorname{Var}\left(Y_i\right)\right] \\
& =\frac{n}{2} \log _2(2 \pi e)+\frac{1}{2} \log _2\left[\prod_{i=1}^n \operatorname{Var}\left(Y_i\right)\right] \\
& =\frac{n}{2} \log _2(2 \pi e)+\frac{1}{2} \log _2\left[\operatorname{det}\left(\mathbf{K}_{\underline{Y}}\right)\right] \\
& =\frac{1}{2} \log _2(2 \pi e)^n+\frac{1}{2} \log _2\left[\operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right] \\
& =\frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right],
\end{aligned}
$$
where (5.2.2) follows by the independence of the random variables $Y_1, \ldots, Y_n$ (e.g., see Property 7 of Lemma 5.14), (5.2.3) follows from (5.1.1), (5.2.4) holds since the matrix $\mathbf{K}_{\underline{Y}}$ is diagonal and hence its determinant is given by the product of its diagonal entries, and (5.2.5) holds since
$$
\begin{aligned}
\operatorname{det}\left(\mathbf{K}_{\underline{Y}}\right) & =\operatorname{det}\left(\mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^T\right) \\
& =\operatorname{det}(\mathbf{A}) \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right) \operatorname{det}\left(\mathbf{A}^T\right) \\
& =\operatorname{det}(\mathbf{A})^2 \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right) \\
& =\operatorname{det}\left(\mathbf{K}_{\underline{X}}\right),
\end{aligned}
$$
where the last equality holds since $(\operatorname{det}(\mathbf{A}))^2=1$, as the matrix $\mathbf{A}$ is orthogonal $\left(\mathbf{A}^T=\mathbf{A}^{-1} \Longrightarrow \operatorname{det}(\mathbf{A})=\operatorname{det}\left(\mathbf{A}^T\right)=1 /[\operatorname{det}(\mathbf{A})]\right.$; thus, $\left.\operatorname{det}(\mathbf{A})^2=1\right)$.
Now invoking Property 10 of Lemma 5.14 and noting that $|\operatorname{det}(\mathbf{A})|=1$ yield that
$$
h\left(Y_1, Y_2, \ldots, Y_n\right)=h\left(X_1, X_2, \ldots, X_n\right)+\underbrace{\log _2|\operatorname{det}(\mathbf{A})|}_{=0}=h\left(X_1, X_2, \ldots, X_n\right) .
$$

We therefore obtain using (5.2.6) that
$$
h\left(X_1, X_2, \ldots, X_n\right)=\frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right],
$$
hence completing the proof.
An alternate (but rather mechanical) proof to the one presented above consists of directly evaluating the joint differential entropy of $\underline{X}$ by integrating $-f_{X^n}\left(x^n\right)$ $\log _2 f_{X^n}\left(x^n\right)$ over $\mathbb{R}^n ;$ it is left as an exercise.

# Hadamard's inequality 

For any real-valued $n \times n$ positive-definite matrix $\mathbf{K}=\left[K_{i, j}\right]_{i, j=1, \ldots, n}$,
$$
\operatorname{det}(\mathbf{K}) \leq \prod_{i=1}^n K_{i, i},
$$
with equality iff $\mathbf{K}$ is a diagonal matrix, where $K_{i, i}$ are the diagonal entries of $\mathbf{K}$.
Proof Since every positive-definite matrix is a covariance matrix (e.g., see [162]), let $\underline{X}=\left(X_1, X_2, \ldots, X_n\right)^T \sim \mathcal{N}_n(\underline{0}, \mathbf{K})$ be a jointly Gaussian random vector with zero-mean vector and covariance matrix $K$. Then
$$
\begin{aligned}
\frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}(\mathbf{K})\right] & =h\left(X_1, X_2, \ldots, X_n\right) \\
& \leq \sum_{i=1}^n h\left(X_i\right) \\
& =\sum_{i=1}^n \frac{1}{2} \log _2\left[2 \pi e \operatorname{Var}\left(X_i\right)\right] \\
& =\frac{1}{2} \log _2\left[(2 \pi e)^n \prod_{i=1}^n K_{i, i}\right],
\end{aligned}
$$
where (5.2.7) follows from Theorem 5.18, (5.2.8) follows from Property 7 of Lemma 5.14 and (5.2.9)-(5.2.10) hold using (5.1.1) along with the fact that each random variable $X_i \sim \mathcal{N}\left(0, K_{i, i}\right)$ is Gaussian with zero mean and variance $\operatorname{Var}\left(X_i\right)=K_{i, i}$ for $i=1,2, \ldots, n$ (as the marginals of a multivariate Gaussian are also Gaussian e.g., cf. [162]).
Finally, from (5.2.10), we directly obtain that
$$
\operatorname{det}(\mathbf{K}) \leq \prod_{i=1}^n K_{i, i},
$$
with equality iff the jointly Gaussian random variables $X_1, X_2, \ldots, X_n$ are independent from each other, or equivalently iff the covariance matrix $\mathbf{K}$ is diagonal.

The next theorem states that among all real-valued size- $n$ random vectors (of support $\mathbb{R}^n$ ) with identical mean vector and covariance matrix, the Gaussian random vector has the largest differential entropy.

# Maximal differential entropy for real-valued random vectors

Let $\underline{X}=\left(X_1, X_2, \ldots, X_n\right)^T$ be a real-valued random vector with a joint pdf of support $S_{X^n}=\mathbb{R}^n$, mean vector $\underline{\mu}$, covariance matrix $\mathbf{K}_{\underline{X}}$ and finite joint differential entropy $h\left(X_1, X_2, \ldots, X_n\right)$. Then
$$
h\left(X_1, X_2, \ldots, X_n\right) \leq \frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}\left(\mathbf{K}_{\underline{\mathbf{x}}}\right)\right]
$$
with equality iff $\underline{X}$ is Gaussian; i.e., $\underline{X} \sim \mathcal{N}_n\left(\underline{\mu}, \mathbf{K}_{\underline{X}}\right)$.

Proof We will present the proof in two parts: the scalar or univariate case, and the multivariate case.
(i) Scalar case $(n=1)$ : For a real-valued random variable with support $S_X=\mathbb{R}$, mean $\mu$ and variance $\sigma^2$, let us show that
$$
h(X) \leq \frac{1}{2} \log _2\left(2 \pi e \sigma^2\right),
$$
with equality iff $X \sim \mathcal{N}\left(\mu, \sigma^2\right)$.
For a Gaussian random variable $Y \sim \mathcal{N}\left(\mu, \sigma^2\right)$, using the nonnegativity of divergence, we can write
$$
\begin{aligned}
0 & \leq D(X \| Y) \\
& =\int_{\mathbb{R}} f_X(x) \log _2 \frac{f_X(x)}{\frac{1}{\sqrt{2 \pi \sigma^2}} e^{-\frac{(x-\mu)^2}{2 \sigma^2}}} d x \\
& =-h(X)+\int_{\mathbb{R}} f_X(x)\left[\log _2\left(\sqrt{2 \pi \sigma^2}\right)+\frac{(x-\mu)^2}{2 \sigma^2} \log _2 e\right] d x \\
& =-h(X)+\frac{1}{2} \log _2\left(2 \pi \sigma^2\right)+\frac{\log _2 e}{2 \sigma^2} \underbrace{\int_{\mathbb{R}}(x-\mu)^2 f_X(x) d x}_{=\sigma^2} \\
& =-h(X)+\frac{1}{2} \log _2\left[2 \pi e \sigma^2\right] .
\end{aligned}
$$

Thus
$$
h(X) \leq \frac{1}{2} \log _2\left[2 \pi e \sigma^2\right],
$$
with equality iff $X=Y$ (almost surely); i.e., $X \sim \mathcal{N}\left(\mu, \sigma^2\right)$.
(ii). Multivariate case $(n>1)$ : As in the proof of Theorem 5.18, we can use an orthogonal square matrix $\mathbf{A}$ (i.e., satisfying $\mathbf{A}^T=\mathbf{A}^{-1}$ and hence $|\operatorname{det}(\mathbf{A})|=1$ ) such that $\mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^T$ is diagonal. Therefore, the random vector generated by the linear map
$$
\underline{Z}=\mathbf{A} \underline{X}
$$
will have a covariance matrix given by $\mathbf{K}_{\underline{Z}}=\mathbf{A} \mathbf{K}_{\underline{X}} \mathbf{A}^T$ and hence have uncorrelated (but not necessarily independent) components. Thus
$$
\begin{aligned}
h(\underline{X}) & =h(\underline{Z})-\underbrace{\log _2|\operatorname{det}(\mathbf{A})|}_{=0} \\
& =h\left(Z_1, Z_2, \ldots, Z_n\right) \\
& \leq \sum_{i=1}^n h\left(Z_i\right) \\
& \leq \sum_{i=1}^n \frac{1}{2} \log _2\left[2 \pi e \operatorname{Var}\left(Z_i\right)\right] \\
& =\frac{n}{2} \log _2(2 \pi e)+\frac{1}{2} \log _2\left[\prod_{i=1}^n \operatorname{Var}\left(Z_i\right)\right] \\
& =\frac{1}{2} \log _2(2 \pi e)^n+\frac{1}{2} \log _2\left[\operatorname{det}\left(\mathbf{K}_{\underline{Z}}\right)\right] \\
& =\frac{1}{2} \log _2(2 \pi e)^n+\frac{1}{2} \log _2\left[\operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right] \\
& =\frac{1}{2} \log _2\left[(2 \pi e)^n \operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)\right]
\end{aligned}
$$
where (5.2.13) holds by Property 10 of Lemma 5.14 and since $|\operatorname{det}(\mathbf{A})|=1,(5.2 .14)$ follows from Property 7 of Lemma 5.14, (5.2.15) follows from (5.2.12) (the scalar case above), (5.2.16) holds since $\mathbf{K}_{\underline{Z}}$ is diagonal, and (5.2.17) follows from the fact that $\operatorname{det}\left(\mathbf{K}_{\underline{Z}}\right)=\operatorname{det}\left(\mathbf{K}_{\underline{X}}\right)$ (as $\mathbf{A}$ is orthogonal). Finally, equality is achieved in both (5.2.14) and (5.2.15) iff the random variables $Z_1, Z_2, \ldots, Z_n$ are Gaussian and independent from each other, or equivalently iff $\underline{X} \sim \mathcal{N}_n\left(\underline{\mu}, \mathbf{K}_{\underline{X}}\right)$.
Observation 5.21 (Examples of maximal differential entropy under various constraints) The following three results can also be shown (the proof is left as an exercise):
1. Among all continuous random variables admitting a pdf with support the interval $(a, b)$, where $b>a$ are real numbers, the uniformly distributed random variable maximizes differential entropy.
2. Among all continuous random variables admitting a pdf with support the interval $[0, \infty)$, finite mean $\mu$, and finite differential entropy, the exponentially distributed random variable with parameter (or rate parameter) $\lambda=1 / \mu$ maximizes differential entropy.
3. Among all continuous random variables admitting a pdf with support $\mathbb{R}$, finite mean $\mu$, and finite differential entropy and satisfying $E[|X-\mu|]=\lambda$, where $\lambda>0$ is a fixed finite parameter, the Laplacian random variable with mean $\mu$, variance $2 \lambda^2$ and pdf
$$
f_X(x)=\frac{1}{2 \lambda} e^{-\frac{|x-\mu|}{\lambda}} \text { for } x \in \mathbb{R}
$$
maximizes differential entropy.

A systematic approach to finding distributions that maximize differential entropy subject to various support and moments constraints can be found in [83, 415].

# Information rates for stationary Gaussian sources

We close this section by noting that for stationary zero-mean Gaussian processes $\left\{X_i\right\}$ and $\left\{\hat{X}_i\right\}$, the differential entropy rate, $\lim _{n \rightarrow \infty} \frac{1}{n} h\left(X^n\right)$, the divergence rate, $\lim _{n \rightarrow \infty} \frac{1}{n} D\left(X^n \| \hat{X}^n\right)$, as well as their Rényi counterparts all exist and admit analytical expressions in terms of the source power spectral densities [154, 196, 223, 393], [144, Table4]. In particular, the differential entropy rate of $\left\{X_i\right\}$ and the divergence rate between $\left\{X_i\right\}$ and $\left\{\hat{X}_i\right\}$ are given (in nats) by
$$
\lim _{n \rightarrow \infty} \frac{1}{n} h\left(X^n\right)=\frac{1}{2} \ln (2 \pi e)+\frac{1}{4 \pi} \int_{-\pi}^\pi \ln \phi_X(\lambda) d \lambda,
$$
and
$$
\lim _{n \rightarrow \infty} \frac{1}{n} D\left(X^n \| \hat{X}^n\right)=\frac{1}{4 \pi} \int_{-\pi}^\pi\left(\frac{\phi_X(\lambda)}{\phi_{\hat{X}}(\lambda)}-1-\ln \frac{\phi_X(\lambda)}{\phi_{\hat{X}}(\lambda)}\right) d \lambda,
$$
respectively. Here, $\phi_X(\cdot)$ and $\phi_{\hat{X}}(\cdot)$ denote the power spectral densities of the zero-mean stationary Gaussian processes $\left\{X_i\right\}$ and $\left\{\hat{X}_i\right\}$, respectively. Recall that for a stationary zero-mean process $\left\{Z_i\right\}$, its power spectral density $\phi_Z(\cdot)$ is the (discrete-time) Fourier transform of its covariance function $K_Z(\tau):=E\left[Z_{n+\tau} Z_n\right]-$ $E\left[Z_{n+\tau}\right] E\left[Z_n\right]=E\left[Z_{n+\tau} Z_n\right], n, \tau=1,2, \ldots ;$ more precisely,
$$
\phi_Z(\lambda)=\sum_{\tau=-\infty}^{\infty} K_Z(\tau) e^{-j \tau \lambda}, \quad-\pi \leq \lambda \leq \pi,
$$
where $j=\sqrt{-1}$ is the imaginary unit number. Note that (5.2.18) and (5.2.19) hold under mild integrability and boundedness conditions; see [196, Sect. 2.4] for the details.



[^1]: This justifies using identical notations for both $I(\cdot ; \cdot)$ and $D(\cdot \| \cdot)$ as opposed to the discerning notations of $H(\cdot)$ for entropy and $h(\cdot)$ for differential entropy.

# 
