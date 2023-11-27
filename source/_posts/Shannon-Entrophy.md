---
title: Shannon Entrophy
tags:
  - Information Theory
  - Statistics
categories: Mathematics
mathjax: true
date: 2023-10-15 02:23:22
---


Ref:

1. *Elements of Information Theory*
2. [EE 376A: Information Theory](https://web.stanford.edu/class/ee376a/) from Stanford University
3. [Probability_Theory by Kyle Siegrist](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/02%3A_Probability_Spaces)
4. [The Book of Statistical Proofs](https://statproofbook.github.io/D/ent)

<!--more-->

# Entropy

Entropy is a fundamental concept in information theory. It's **a measure of the average uncertainty in the random variable**. It is **the number of bits on average required to describe the random variable**.



For a discrete random variable $X$ with alphabet $\mathcal X$ and probability mass function $p(x) \triangleq \operatorname{Pr}[X=x]$, we define entropy as
$$
H_b(X)=\mathbb{E}\left[\log _2 \frac{1}{p(X)}\right]=\sum_{x \in \mathcal X} p(x) \log _2 \frac{1}{p(x)} .
$$
The formula for information entropy was introduced by Claude E. Shannon in his 1948 paper "[A Mathematical Theory of Communication](https://dl.acm.org/doi/pdf/10.1145/584091.584093?casa_token=wqoh-zFX88sAAAAA:1_6aYy6mdwnp-V-k9SdBhQYm_1k254fdb3UQtftXA_odjAacK01ilqwAZ2P9WJgACwvd7OS_Khf4)".

* **Label-invariance**: Entropy is label-invariant, meaning that it depends only on the probability distribution and not on the actual values that the random variable $X$.
* Notably, $H (X)$ is itself a random variable, because $X$ is a random variable.

## Symbol Convention

* $\log$ is assumed to be $\log_2$ unless otherwise indicated.

* (在 $\log$函数 底为2时)Entropy的单位是bit.

* $H(X)$的下标取决于使用的$\log$函数的底. 因此$H(X), H_2(X), H_b(X)$是相同的($b$代表二进制的比特). 如果 $\log$函数 使用其它底, 设为$a$, 那么必须清楚地在文中说明: $H_a(X) = \sum_x p(x) \log _a \frac{1}{p(x)}$.

* Given a probability distribution $p$ and a random variable $X$, $X \sim p$, then $H(X)$ can also be expressed as $H(p)$. 

  Therefore, the entropy of all random variables $X,Y,Z,…$ that follow the distribution $p$ is $H(p)$. This is **unambiguous** because random variables that follow the same probability distribution have the same entropy.

* $\mathbb{E}(X)$是随机变量$X$的期望, $\mathbb{E}(X) = \sum_{x \in \mathcal X} X.p(x)$. 这里的随机变量是随机变量$X$的函数$g(X) = \log_2 \frac{1}{p(X)}$, 所以有:
  $$
  \mathbb{E}(g(X)) = \sum_{x \in \mathcal X} g(x)p(x) = \sum_{x \in \mathcal X} p(x) \log _2 \frac{1}{p(x)} .
  $$

  * 有时我们会省略$x \in \mathcal X$为$x$, 即: $H_b(X)=\sum_{x} p(x) \log _2 \frac{1}{p(x)} .$
  * $\mathbb{E}_{X \sim p}(X)$: denotes that  $X \sim p$.

## Properties

**Lemma1:** $H(X) \geq 0$.

**Proof:** 

$\quad 0 \leq p(x) \leq 1$ implies that $\log \frac{1}{p(x)} \geq 0$.

***

**Lemma2:**  $H_b(X)=\left(\log _b a\right) H_a(X)$.

**Proof:** 

Since $\log_a b  = \frac{\log_c b}{\log_c a}$.

Then $\log _b p=\log _b a \log _a p$.

So $H_2(X) = \sum_x p(x) \log _2 \frac{1}{p(x)} = \log_2 a . \sum_x p(x) \log _a \frac{1}{p(x)} = ( \log_2 a)H_a(X)$.

## Example: For Bernoulli Distribution

![Figure 2.1: H(p) vs p](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Statistics/Information%20Theory/Shannon%20Entropy/Figure%202.1-%20H%28p%29%20vs%20p.png)

Here we discuss the entropy of random variable $X$ if $X \sim \text{Bern}(p)$ (**Bernoulli distribution**).

In this scenario, $X \in \{0,1\}$ and $\operatorname{Pr}[X=0]=p$, so we can compute the entropy of the distribution (dropping the base 2 ) as
$$
H(X)=\mathbb{E}\left[\log \frac{1}{p(X)}\right]=p \log \frac{1}{p}+(1-p) \log \frac{1}{1-p} .
$$
we get the curve in figure 2.1 which reaches a maximum of 1 when $p=0.5$.

我们可以以抛硬币为例, 对于一个正常的硬币, 其每面的概率都是0.5, 令$X$为硬币朝上那面的值, $X \in X \in \{0,1\}$, $p = 0.5$.

此时有 $H(X)=0.5(1)+0.5(1)=1$. 





What about for a coin that almost always lands tails $(X=0)$, with $p=0.999$ ? 

With this heavily-biased coin, we get $H(X)=0.999 \log \frac{1}{0.999}+0.001 \log \frac{1}{0.001} \approx 0.011$.

From this example, we can see that we gain more information from more surprising events (i.e., $\log \frac{1}{p(x)} \uparrow$ as $p(x) \downarrow$ ), but they also happen less often. 

# Example: Uniform Distribution

For a discrete random variable $X$ with a uniform distribution over $n$ outcomes, each with probability $P(X=x_i)=\frac{1}{n}$, the entropy $H(X)$ is calculated as follows:
$$
\begin{aligned}
H(X) 
&=−\sum_{i=1}^{n}P(X=x_i) \log P(X=x_i) \\
&= n \cdot  \frac{1}{n} \cdot \log \frac{1}{\frac{1}{n}} \\
&= 1 \cdot \log n \\
&= \log n
\end{aligned}
$$


# Joint Entropy

There is nothing really new in this definition because $(X,Y)$ can be considered to be a single vector-valued random variable.

**Definition:** If $(X, Y ) ∼ p(x, y)$, the **joint entropy** $H (X, Y )$ is defined as
$$
H\left(X, Y\right)=\mathbb{E}\left[\log \frac{1}{p\left(X, Y\right)}\right] = \sum_{x \in \mathcal X}\sum_{y \in \mathcal Y} p(x,y) \log _2 \frac{1}{p(x,y)} .
$$
If $X$ and $Y$ are independent, we can show that
$$
\begin{aligned}
H\left(X, Y\right) & =\mathbb{E}\left[\log \frac{1}{p\left(X\right) p\left(Y\right)}\right] \\
& =\mathbb{E}\left[\log \frac{1}{p\left(X\right)}\right]+\mathbb{E}\left[\log \frac{1}{p\left(Y\right)}\right] \\
& =H\left(X\right)+H\left(Y\right) .
\end{aligned}
$$

But if $X$ and $Y$ are not independent, we can use [chain rule](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) to compute $H(X,Y)$.

# Conditional Entropy

**Definition:** If $(X, Y ) ∼ p(x, y)$, the **conditional entropy** $H(X|Y)$ is defined as
$$
H\left(Y | X\right)=\mathbb{E}\left[\log \frac{1}{p\left(Y | X\right)}\right] .
$$
And we can prove
$$
\mathbb{E}\left[\log \frac{1}{p\left(Y | X\right)}\right] = \sum_{x \in \mathcal X}p(x) H(Y|X=x) .
$$


So that
$$
H\left(Y | X\right)=\mathbb{E}\left[\log \frac{1}{p\left(Y | X\right)}\right] = \sum_{x \in \mathcal X}p(x) H(Y|X=x) .
$$

* Property: $H(Y|X) \le H(Y)$, see [->proof](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-conditioning-reduces-entropy).

## Proof

Let's start by looking at $H(Y \mid X)$.
$$
\begin{equation} \label{eq3.1}
\begin{aligned}
H(Y \mid X) & =\mathbb{E}\left[\log \frac{1}{p(y \mid x)}\right] \\
& =\sum_{x, y} p(x, y) \log \frac{1}{p(y \mid x)}
\end{aligned}
\end{equation}
$$
$\sum_{x, y} p(x, y)$也可写作$\sum_{x \in \mathcal X} \sum_{y \in \mathcal Y} p(x, y)$.



Note that the probability distributions for the expectation and in the function itself are not the same! If you are unhappy with that, just remember that for any arbitrary function, $\mathbb{E}[f(X, Y)]=\sum_{x, y} p(x, y) f(x, y)$, and in this case, that arbitrary function is $\log \frac{1}{p(y \mid x)}$.
Okay, so let's go back to $\eqref{eq3.1}$
$$
\begin{equation}\label{eq3.2}
\begin{aligned}
H(Y \mid X) & =\sum_{x, y} p(x, y) \log \frac{1}{p(y \mid x)} \\
& =\sum_x p(x) \sum_y p(y \mid x) \log \frac{1}{p(y \mid x)} \\
& =\sum_x p(x) H(Y \mid X=x)
\end{aligned}
\end{equation}
$$
This is a measure of, on average, how much extra information you get by observing a second variable $Y$, given that you have already observed the first variable $X$.



# Chain Rule for Entropy(2 Variables)

Note: 本文仅探讨2-3个随机变量的变量的entropy的Chain Rule, 更general的chain rule的探讨请参见[*Chain Rules for Entropy, Relative Entropy and Mutual Information*](https://lyk-love.cn/2023/10/15/Chain-Rules-for-Entropy-Relative-Entropy-and-Mutual-Information/).


$$
\begin{equation} \label{eq4}
H(X, Y)=H(X)+H(Y \mid X) .
\end{equation}
$$


## Proof: Short

简短证明, 只使用数学期望.


$$
\begin{aligned}
H(X, Y) & =\mathbb{E}\left[\log \frac{1}{p(x) p(y \mid x)}\right] \\
& =\mathbb{E}\left[\log \frac{1}{p(x)}\right]+\mathbb{E}\left[\log \frac{1}{p(y \mid x)}\right] \\
H(X, Y) & =H(X)+H(Y \mid X)
\end{aligned}
$$

## Proof: Long

复杂证明, 从$\log$函数出发.



By definition, we have
$$
\begin{aligned}
H(X, Y) & =-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(x, y) \\
\end{aligned}
$$
According to Bayes' theorem $\log p(x, y) = \log p(x) \log p(y | x)$, 
$$
-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(x, y) =-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log [p(x) p(y \mid x)]
$$


Since $\log_b ac = \log_b a + \log_b c$
$$
-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log [p(x) p(y \mid x)] = -\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(x)-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(y \mid x)
$$


Because $p(x)$ is a marginal probability, $p(x) = \sum_{y \in \mathcal{Y}} p(x, y)$. We have


$$
-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(x)-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(y \mid x) \\=-\sum_{x \in \mathcal{X}} p(x) \log p(x)-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(y \mid x)
$$
By definition:
$$
-\sum_{x \in \mathcal{X}} p(x) \log p(x)-\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} p(x, y) \log p(y \mid x) =H(X)+H(Y \mid X)
$$
Q.E.D.

# Chain Rule for Entropy(3 Variables)

Equation $\eqref{eq4}$ is the chain rule for entropy for <u>two</u> random variables, but it can easily be extended to more variables. For example, for three random variables $X$, $Y$ , and $Z$,
$$
\begin{align}
H(X, Y, Z) & =H(X)+H(Y, Z \mid X) \label{eq4.1}  \\
& =H(X)+H(Y \mid X)+H(Z \mid X, Y) \label{eq4.2} 
\end{align}
$$
Note: $H(Y,Z \mid X)$指的是以$X$为条件, $H(Z \mid X, Y)$指的是以$X,Y$为条件.



The first setp, which is $\eqref{eq4.1}$, comes from directly applying the chain rule for two variables.

To understand the second setp, which is $\eqref{eq4.2}$, we must know the conclusion from $\eqref{eq3.2}$:
$$
\begin{aligned}
H(Y \mid X) & =\mathbb{E}\left[\log \frac{1}{p(y \mid x)}\right] \\
& =\sum_{x, y} p(x, y) \log \frac{1}{p(y \mid x)}
\end{aligned}
$$


Substitute it into $\eqref{eq4.1}$:
$$
\begin{aligned}
H(Y, Z \mid X) & =\sum_x p(x) H(Y, Z \mid X=x) \\
& =\sum_x p(x) H(Y \mid X=x)+\sum_x p(x) H(Z \mid Y, X=x) \\
& =H(Y \mid X)+H(Z \mid Y, X)
\end{aligned}
$$
Q.E.D.



# Relative Entropy

The *relative entropy* is a measure of the distance between two distribu- tions. In statistics, it arises as an expected logarithm of the likelihood ratio. The relative entropy D(p||q) is a measure of the inefficiency of assuming that the distribution is q when the true distribution is p.



**Definition:** The relative entropy or <u>Kullback-Leibler distance</u> between two probability mass functions $p(x)$ and $q(x)$ is defined as
$$
\begin{aligned}
D(p \| q) & =\sum_{x \in \mathcal{X}} p(x) \log \frac{p(x)}{q(x)} \\
& = \mathbb E _{X \sim p}(\log \frac{p(X)}{q(X)}) .
\end{aligned}
$$
In the above definition, we use the convention that $0 \log \frac{0}{0}=0$ and the convention (based on continuity arguments) that $0 \log \frac{0}{q}=0$ and $p \log \frac{p}{0}=$ $\infty$. Thus, if there is any symbol $x \in \mathcal{X}$ such that $p(x)>0$ and $q(x)=0$, then $D(p \| q)=\infty$.

We will soon show that relative entropy is always nonnegative and is zero if and only if $p=q$. However, it is not a true distance between distributions since **it is not symmetric** and does not satisfy the triangle inequality. Nonetheless, it is often useful to think of relative entropy as a "distance" between distributions.

## Properties

1. In general, relative entropy is asymmetric $(D(p \| q) \neq D(q \| p))$, and does not satisfy the triangle inequality. Therefore, it is **not** a metric.
2. $D(p \| p)=0$.
3. $D(p \| q) \geq 0$ for all distributions $p, q$ with equality holding iff $p=q$. 
4. $D(p(y \mid x) \| q(y \mid x)) \geq 0$ with equality if and only if $p(y \mid x)=q(y \mid x)$ for all $y$ and $x$ such that $p(x)>0$.

Property (3) is [proved using Jensen’s inequality](https://lyk-love.cn/2023/10/15/Jensen%E2%80%99s-Inequality/#theorem-information-inequality).

Property (4) is proved using property (3).



## Relative Entropy is Not Symmetric

In the following problem and solution, we give an **counterexample** of relative entropy's symmericity.



Relative entropy is not symmetric. Let the random variable $X$ have three possible outcomes $\{a, b, c\}$. Consider two distributions $p(x)$ and $q(x)$ on this random variable

| Symbol | $p(x)$ | $q(x)$ |
| ------ | ------ | ------ |
| a      | 1/2    | 1/3    |
| b      | 1/4    | 1/3    |
| c      | 1/4    | 1/3    |

Calculate $H(p), H(q), D(p \| q)$ and $D(q \| p)$. Verify that in this case $D(p \| q) \neq D(q \| p)$.
Solution:
$$
\begin{aligned}
H(p) & =\frac{1}{2} \log 2+\frac{1}{4} \log 4+\frac{1}{4} \log 4=1.5 \mathrm{bits} \\
H(q) & =3 \times \frac{1}{3} \log 3=1.58496 \mathrm{bits} \\
D(p \| q) & =\frac{1}{2} \log \frac{3}{2}+\frac{1}{4} \log \frac{3}{4}+\frac{1}{4} \log \frac{3}{4}=\log 3-1.5=0.08496 \mathrm{bits} \\
D(q \| p) & =\frac{1}{3} \log \frac{2}{3}+\frac{1}{3} \log \frac{4}{3}+\frac{1}{3} \log \frac{4}{3}=-\log 3+\frac{5}{3}=0.0817 \mathrm{bits}
\end{aligned}
$$
It is clear that $D(p \| q) \neq D(q \| p)$.

## Conditional Eelative Entropy

We define a conditional version of the relative entropy.

**Definition:** For joint probability mass functions $p(x, y)$ and $q(x, y)$, the conditional relative entropy $D(p(y \mid x) \| q(y \mid x))$ is the average of the relative entropies between the conditional probability mass functions $p(y \mid x)$ and $q(y \mid x)$ averaged over the probability mass function $p(x)$. More precisely,
$$
\begin{aligned}
D(p(y \mid x) \| q(y \mid x)) & =\sum_x p(x) \sum_y p(y \mid x) \log \frac{p(y \mid x)}{q(y \mid x)} \\
& =E_{p(x, y)} \log \frac{p(Y \mid X)}{q(Y \mid X)} .
\end{aligned}
$$


The notation for conditional relative entropy is not explicit since it omits mention of the distribution $p(x)$ of the conditioning random variable. However, it is normally understood from the context.

The relative entropy between two joint distributions on a pair of random variables can be expanded as the sum of a relative entropy and a conditional relative entropy. 



# Mutual Information

Given two random variables $X$ and $Y$, we want to define a measure of the information that $Y$ provides about $X$ when $Y$ is observed, but $X$ is not. We call this measure mutual information, which is defined as:
$$
I(X ; Y) \triangleq H(X)-H(X \mid Y)
$$

## Mutual Information and Relative Entropy

Mutual information between two random variables $X, Y$ can be expressed in terms relative entropy between their joint distribution $p_{X, Y}$ and the product of their marginal distributions $p_X \cdot p_Y$
$$
\begin{aligned}
I(X ; Y) & =\sum_{x, y} p(x, y) \log \frac{p_{X, Y}(x, y)}{p_X(x) \cdot p_Y(y)} \\
& =D\left(p_{X, Y} \| p_X \cdot p_Y\right) .
\end{aligned}
$$
We will prove Property 3 using Jensen's inequality and thereby prove Theorem 1.



## Property: Symmetric

Expanding $H(X)-H(X \mid Y)$, we have:
$$
\begin{aligned}
H(X)-H(X \mid Y) & =\mathbb{E}\left[\log \frac{1}{p(X)}\right]-\mathbb{E}\left[\log \frac{1}{p(X \mid Y)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X \mid Y)}{p(X)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X \mid Y) p(Y)}{p(X) p(Y)}\right] \\
& =\mathbb{E}\left[\log \frac{p(X, Y)}{p(X) p(Y)}\right] \\
& =H(Y)-H(Y \mid X)
\end{aligned}
$$


Then
$$
I(X ; Y) \triangleq H(X)-H(X \mid Y)=H(Y)-H(Y \mid X)
$$


So **mutual information is symmetric**.

## Definition

It is for this reason that we call this quantity mutual information-because $I(X ; Y)$ does not "prefer" $X$ or $Y$. Formally, mutual information is defined as:
**Definition: Mutual Information**
$$
\begin{aligned}
I(X;Y) & \triangleq H(X)+H(Y)-H(X, Y) \\
& =H(X)-H(X \mid Y) \\
& =H(Y)-H(Y \mid X) \\
& = \mathbb E[\log \frac{p(X,Y)}{p(X)p(Y)}].
\end{aligned}
$$


## Relationship between entropy and mutual information

The meaure of entropy, relative entropy and mutual information can be visualized in the figure below:



![Relationship between entropy and mutual information](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Statistics/Information%20Theory/Shannon%20Entropy/Relationship%20between%20entropy%20and%20mutual%20information.png)

## Properties

### $I(X ; X)=H(X)$

Now let’s ask an interesting question: How much does X tell us about itself? In other words, what is I (X; X)? Using our first definition, we have:
$$
I (X; X) = H (X) − H (X|X)
$$


We note that $H(X \mid X)=0$, because in the expectation, $X$ can only take on one fixed, given value with probability 1 . Therefore, $H(X \mid X)=\log 1=0$. Thus:
$$
I(X ; X)=H(X)
$$
Meaning that $X$ tells us everything about itself!

### $I(X ; Y) \geq 0$

For any two random variables, $X, Y$,
$$
I(X ; Y) \geq 0
$$
with equality if and only if $X$ and $Y$ are independent.



**Proof:** 

1. We know that $I(X ; Y)=D(p(x, y) \| p(x) p(y))$.
2. See [property 3 of Relative Entropy](https://lyk-love.cn/2023/10/15/shannon-entrophy/#properties-1), $D(p \| q) \geq 0$ for all distributions $p, q$ with equality holding iff $p=q$.
3. So $I(X ; Y)=D(p(x, y) \| p(x) p(y)) \geq 0$, with equality if and only if $p(x, y)=p(x) p(y)$ (i.e., $X$ and $Y$ are independent).

***

**Corollary:**
$$
I(X ; Y \mid Z) \geq 0,
$$
with equality if and only if $X$ and $Y$ are conditionally independent given $Z$.



## Conditional Mutual Information

Definition: The conditional mutual information of random variables $X$ and $Y$ given $Z$ is defined by
$$
\begin{aligned}
I(X ; Y \mid Z) & =H(X \mid Z)-H(X \mid Y, Z) \\
& =E_{p(x, y, z)} \log \frac{p(X, Y \mid Z)}{p(X \mid Z) p(Y \mid Z)} .
\end{aligned}
$$

