---
title: Fano's inequality
tags:
---



Fano's inequality $[113,114]$ is a useful tool widely employed in information theory to prove converse results for coding theorems (as we will see in the following chapters).

# Fano's Inequality

Theorem 2.10.1 (Fano's Inequality) For any estimator $\hat{X}$ such that $X \rightarrow Y \rightarrow \hat{X}$, with $P_e=\operatorname{Pr}(X \neq \hat{X})$, we have
$$
H\left(P_e\right)+P_e \log |\mathcal{X}| \geq H(X \mid \hat{X}) \geq H(X \mid Y) .
$$

This inequality can be weakened to
$$
1+P_e \log |\mathcal{X}| \geq H(X \mid Y)
$$
or
$$
P_e \geq \frac{H(X \mid Y)-1}{\log |\mathcal{X}|}
$$

Remark Note from (2.130) that $P_e=0$ implies that $H(X \mid Y)=0$, as intuition suggests.

Proof: We first ignore the role of $Y$ and prove the first inequality in (2.130). We will then use the data-processing inequality to prove the more traditional form of Fano's inequality, given by the second inequality in (2.130). Define an error random variable,
$$
E= \begin{cases}1 & \text { if } \hat{X} \neq X, \\ 0 & \text { if } \hat{X}=X\end{cases}
$$

Then, using the chain rule for entropies to expand $H(E, X \mid \hat{X})$ in two different ways, we have
$$
\begin{aligned}
H(E, X \mid \hat{X}) & =H(X \mid \hat{X})+\underbrace{H(E \mid X, \hat{X})}_{=0} \\
& =\underbrace{H(E \mid \hat{X})}_{\leq H\left(P_e\right)}+\underbrace{H(X \mid E, \hat{X}) .}_{\leq P_e \log |\mathcal{X}|}
\end{aligned}
$$

Since conditioning reduces entropy, $H(E \mid \hat{X}) \leq H(E)=H\left(P_e\right)$. Now since $E$ is a function of $X$ and $\hat{X}$, the conditional entropy $H(E \mid X, \hat{X})$ is equal to 0 . Also, since $E$ is a binary-valued random variable, $H(E)=$ $H\left(P_e\right)$. The remaining term, $H(X \mid E, \hat{X})$, can be bounded as follows:
$$
\begin{aligned}
H(X \mid E, \hat{X}) & =\operatorname{Pr}(E=0) H(X \mid \hat{X}, E=0)+\operatorname{Pr}(E=1) H(X \mid \hat{X}, E=1) \\
& \leq\left(1-P_e\right) 0+P_e \log |\mathcal{X}|,
\end{aligned}
$$
since given $E=0, X=\hat{X}$, and given $E=1$, we can upper bound the conditional entropy by the log of the number of possible outcomes. Combining these results, we obtain
$$
H\left(P_e\right)+P_e \log |\mathcal{X}| \geq H(X \mid \hat{X}) .
$$

By the data-processing inequality, we have $I(X ; \hat{X}) \leq I(X ; Y)$ since $X \rightarrow Y \rightarrow \hat{X}$ is a Markov chain, and therefore $H(X \mid \hat{X}) \geq H(X \mid Y)$. Thus, we have
$$
H\left(P_e\right)+P_e \log |\mathcal{X}| \geq H(X \mid \hat{X}) \geq H(X \mid Y) .
$$

Corollary For any two random variables $X$ and $Y$, let $p=\operatorname{Pr}(X \neq Y)$.
$$
H(p)+p \log |\mathcal{X}| \geq H(X \mid Y) .
$$

Proof: Let $\hat{X}=Y$ in Fano's inequality.
For any two random variables $X$ and $Y$, if the estimator $g(Y)$ takes values in the set $\mathcal{X}$, we can strengthen the inequality slightly by replacing $\log |\mathcal{X}|$ with $\log (|\mathcal{X}|-1)$.

Corollary Let $P_e=\operatorname{Pr}(X \neq \hat{X})$, and let $\hat{X}: \mathcal{Y} \rightarrow \mathcal{X}$; then
$$
H\left(P_e\right)+P_e \log (|\mathcal{X}|-1) \geq H(X \mid Y) .
$$

Proof: The proof of the theorem goes through without change, except that
$$
\begin{aligned}
H(X \mid E, \hat{X}) & =\operatorname{Pr}(E=0) H(X \mid \hat{X}, E=0)+\operatorname{Pr}(E=1) H(X \mid \hat{X}, E=1) \\
& \leq\left(1-P_e\right) 0+P_e \log (|\mathcal{X}|-1),
\end{aligned}
$$
since given $E=0, X=\hat{X}$, and given $E=1$, the range of possible $X$ outcomes is $|\mathcal{X}|-1$, we can upper bound the conditional entropy by the $\log (|\mathcal{X}|-1)$, the logarithm of the number of possible outcomes. Substituting this provides us with the stronger inequality.

Remark Suppose that there is no knowledge of $Y$. Thus, $X$ must be guessed without any information. Let $X \in\{1,2, \ldots, m\}$ and $p_1 \geq p_2 \geq$ $\cdots \geq p_m$. Then the best guess of $X$ is $\hat{X}=1$ and the resulting probability of error is $P_e=1-p_1$. Fano's inequality becomes
$$
H\left(P_e\right)+P_e \log (m-1) \geq H(X) .
$$

The probability mass function
$$
\left(p_1, p_2, \ldots, p_m\right)=\left(1-P_e, \frac{P_e}{m-1}, \ldots, \frac{P_e}{m-1}\right)
$$
achieves this bound with equality. Thus, Fano's inequality is sharp.
While we are at it, let us introduce a new inequality relating probability of error and entropy. Let $X$ and $X^{\prime}$ by two independent identically distributed random variables with entropy $H(X)$. The probability at $X=X^{\prime}$ is given by
$$
\operatorname{Pr}\left(X=X^{\prime}\right)=\sum_x p^2(x)
$$

We have the following inequality:

Lemma 2.10.1 If $X$ and $X^{\prime}$ are i.i.d. with entropy $H(X)$,
$$
\operatorname{Pr}\left(X=X^{\prime}\right) \geq 2^{-H(X)}
$$
with equality if and only if $X$ has a uniform distribution.
Proof: Suppose that $X \sim p(x)$. By Jensen's inequality, we have
$$
2^{E \log p(X)} \leq E 2^{\log p(X)},
$$
which implies that
$$
2^{-H(X)}=2^{\sum p(x) \log p(x)} \leq \sum p(x) 2^{\log p(x)}=\sum p^2(x) .
$$

Corollary Let $X, X^{\prime}$ be independent with $X \sim p(x), X^{\prime} \sim r(x), x, x^{\prime} \in$ $\mathcal{X}$. Then
$$
\begin{aligned}
& \operatorname{Pr}\left(X=X^{\prime}\right) \geq 2^{-H(p)-D(p \| r)}, \\
& \operatorname{Pr}\left(X=X^{\prime}\right) \geq 2^{-H(r)-D(r \| p)} .
\end{aligned}
$$




Proof: We have
$$
\begin{aligned}
2^{-H(p)-D(p \| r)} & =2^{\sum p(x) \log p(x)+\sum p(x) \log \frac{r(x)}{p(x)}} \\
& =2^{\sum p(x) \log r(x)} \\
& \leq \sum p(x) 2^{\log r(x)} \\
& =\sum p(x) r(x) \\
& =\operatorname{Pr}\left(X=X^{\prime}\right)
\end{aligned}
$$
where the inequality follows from Jensen's inequality and the convexity of the function $f(y)=2^y$.
The following telegraphic summary omits qualifying conditions.

# V2

Lemma 2.26 (Fano's inequality) Let $X$ and $Y$ be two random variables, correlated in general, with alphabets $\mathcal{X}$ and $\mathcal{Y}$, respectively, where $\mathcal{X}$ is finite but $\mathcal{Y}$ can be countably infinite. Let $\hat{X}:=g(Y)$ be an estimate of $X$ from observing $Y$, where $g: \mathcal{Y} \rightarrow \mathcal{X}$ is a given estimation function. Define the probability of error as
$$
P_e:=\operatorname{Pr}[\hat{X} \neq X]
$$

Then the following inequality holds
$$
H(X \mid Y) \leq h_b\left(P_e\right)+P_e \cdot \log _2(|\mathcal{X}|-1)
$$
where $h_{\mathrm{b}}(x):=-x \log _2 x-(1-x) \log _2(1-x)$ for $0 \leq x \leq 1$ is the binary entropy function (see Example 2.3).



Observation 2.27
- Note that when $P_e=0$, we obtain that $H(X \mid Y)=0$ (see (2.5.1)) as intuition suggests, since if $P_e=0$, then $\hat{X}=g(Y)=X$ (with probability 1) and thus $H(X \mid Y)=H(g(Y) \mid Y)=0$.
- Fano's inequality yields upper and lower bounds on $P_e$ in terms of $H(X \mid Y)$. This is illustrated in Fig. 2.4, where we plot the region for the pairs $\left(P_e, H(X \mid Y)\right)$ that are permissible under Fano's inequality. In the figure, the boundary of the permissible (dashed) region is given by the function
$$
f\left(P_e\right):=h_b\left(P_e\right)+P_e \cdot \log _2(|\mathcal{X}|-1),
$$
the right-hand side of (2.5.1). We obtain that when
$$
\log _2(|\mathcal{X}|-1)<H(X \mid Y) \leq \log _2(|\mathcal{X}|)
$$
$P_e$ can be upper and lower bounded as follows:
$$
0<\inf \{a: f(a) \geq H(X \mid Y)\} \leq P_e \leq \sup \{a: f(a) \geq H(X \mid Y)\}<1 .
$$

Furthermore, when
$$
0<H(X \mid Y) \leq \log _2(|\mathcal{X}|-1)
$$


only the lower bound holds:
$$
P_e \geq \inf \{a: f(a) \geq H(X \mid Y)\}>0 .
$$

Thus for all nonzero values of $H(X \mid Y)$, we obtain a lower bound (of the same form above) on $P_e$; the bound implies that if $H(X \mid Y)$ is bounded away from zero, $P_e$ is also bounded away from zero.



# Weaker 

- A weaker but simpler version of Fano's inequality can be directly obtained from (2.5.1) by noting that $h_b\left(P_e\right) \leq 1$ :
$$
H(X \mid Y) \leq 1+P_e \log _2(|\mathcal{X}|-1),
$$
which in turn yields that
$$
P_e \geq \frac{H(X \mid Y)-1}{\log _2(|\mathcal{X}|-1)} \quad(\text { for }|\mathcal{X}|>2)
$$
which is weaker than the above lower bound on $P_e$.
Proof of Lemma 2.26 Define a new random variable,
$$
E:=\left\{\begin{array}{l}
1, \text { if } g(Y) \neq X \\
0, \text { if } g(Y)=X
\end{array} .\right.
$$

Then using the chain rule for conditional entropy, we obtain
$$
\begin{aligned}
H(E, X \mid Y) & =H(X \mid Y)+H(E \mid X, Y) \\
& =H(E \mid Y)+H(X \mid E, Y) .
\end{aligned}
$$

Observe that $E$ is a function of $X$ and $Y$; hence, $H(E \mid X, Y)=0$. Since conditioning never increases entropy, $H(E \mid Y) \leq H(E)=h_b\left(P_e\right)$. The remaining term, $H(X \mid E, Y)$, can be bounded as follows:
$$
\begin{aligned}
H(X \mid E, Y) & =\operatorname{Pr}[E=0] H(X \mid Y, E=0)+\operatorname{Pr}[E=1] H(X \mid Y, E=1) \\
& \leq\left(1-P_e\right) \cdot 0+P_e \cdot \log _2(|\mathcal{X}|-1),
\end{aligned}
$$
since $X=g(Y)$ for $E=0$, and given $E=1$, we can upper bound the conditional entropy by the logarithm of the number of remaining outcomes, i.e., $(|\mathcal{X}|-1)$. Combining these results completes the proof.

Fano's inequality cannot be improved in the sense that the lower bound, $H(X \mid Y)$, can be achieved for some specific cases. Any bound that can be achieved in some cases is often referred to as sharp. ${ }^9$ From the proof of the above lemma, we can observe
${ }^9$ Definition. A bound is said to be sharp if the bound is achievable for some specific cases. A bound is said to be tight if the bound is achievable for all cases.



that equality holds in Fano's inequality, if $H(E \mid Y)=H(E)$ and $H(X \mid Y, E=1)=$ $\log _2(|\mathcal{X}|-1)$. The former is equivalent to $E$ being independent of $Y$, and the latter holds iff $P_{X \mid Y}(\cdot \mid y)$ is uniformly distributed over the set $\mathcal{X} \backslash\{g(y)\}$. We can therefore create an example in which equality holds in Fano's inequality.

Example 2.28 Suppose that $X$ and $Y$ are two independent random variables which are both uniformly distributed on the alphabet $\{0,1,2\}$. Let the estimating function be given by $g(y)=y$. Then
$$
P_e=\operatorname{Pr}[g(Y) \neq X]=\operatorname{Pr}[Y \neq X]=1-\sum_{x=0}^2 P_X(x) P_Y(x)=\frac{2}{3} .
$$

In this case, equality is achieved in Fano's inequality, i.e.,
$$
h_b\left(\frac{2}{3}\right)+\frac{2}{3} \cdot \log _2(3-1)=H(X \mid Y)=H(X)=\log _2 3 .
$$

To conclude this section, we present an alternative proof for Fano's inequality to illustrate the use of the data processing inequality and the FI Lemma.

Alternative Proof of Fano's inequality: Noting that $X \rightarrow Y \rightarrow \hat{X}$ form a Markov chain, we directly obtain via the data processing inequality that
$$
I(X ; Y) \geq I(X ; \hat{X}),
$$
which implies that
$$
H(X \mid Y) \leq H(X \mid \hat{X})
$$

Thus, if we show that $H(X \mid \hat{X})$ is no larger than the right-hand side of (2.5.1), the proof of (2.5.1) is complete.

Noting that
$$
P_e=\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x})
$$
and
$$
1-P_e=\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x}=x} P_{X, \hat{X}}(x, \hat{x})=\sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x),
$$
we obtain that
$$
\begin{aligned}
& H(X \mid \hat{X})-h_b\left(P_e\right)-P_e \log _2(|\mathcal{X}|-1) \\
& =\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x}) \log _2 \frac{1}{P_{X \mid \hat{X}}(x \mid \hat{x})}+\sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x) \log _2 \frac{1}{P_{X \mid \hat{X}}(x \mid x)} \\
& -\left[\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x})\right] \log _2 \frac{(|\mathcal{X}|-1)}{P_e}+\left[\sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x)\right] \log _2\left(1-P_e\right) \\
& =\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x}) \log _2 \frac{P_e}{P_{X \mid \hat{X}}(x \mid \hat{x})(|\mathcal{X}|-1)} \\
& +\sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x) \log _2 \frac{1-P_e}{P_{X \mid \hat{X}}(x \mid x)} \\
& \leq \log _2(e) \sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x})\left[\frac{P_e}{P_{X \mid \hat{X}}(x \mid \hat{x})(|\mathcal{X}|-1)}-1\right] \\
& +\log _2(e) \sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x)\left[\frac{1-P_e}{P_{X \mid \hat{X}}(x \mid x)}-1\right] \\
& =\log _2(e)\left[\frac{P_e}{(|\mathcal{X}|-1)} \sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{\hat{X}}(\hat{x})-\sum_{x \in \mathcal{X}} \sum_{\hat{x} \in \mathcal{X}: \hat{x} \neq x} P_{X, \hat{X}}(x, \hat{x})\right] \\
& +\log _2(e)\left[\left(1-P_e\right) \sum_{x \in \mathcal{X}} P_{\hat{X}}(x)-\sum_{x \in \mathcal{X}} P_{X, \hat{X}}(x, x)\right] \\
& =\log _2(e)\left[\frac{P_e}{(|\mathcal{X}|-1)}(|\mathcal{X}|-1)-P_e\right]+\log _2(e)\left[\left(1-P_e\right)-\left(1-P_e\right)\right] \\
& =0 \text {, } \\
&
\end{aligned}
$$
where the inequality follows by applying the FI Lemma to each logarithm term in (2.5.3).
