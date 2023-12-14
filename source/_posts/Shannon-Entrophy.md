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
2. *An Introduction to Single-User Information Theory*

<!--more-->

# Entropy

Entropy is a fundamental concept in information theory. It's **a measure of the average uncertainty in the random variable**. It is **the number of bits on average required to describe the random variable**.

![Relationship between entropy and mutual information](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Statistics/Information%20Theory/Shannon%20Entropy/Relationship%20between%20entropy%20and%20mutual%20information.png)

Note: 

* joint entropy $H(X,Y)$ 可想象成把两个区域并联, 即 $H(X)$的部分 加上 $H(Y)$中挖掉$H(X)$的部分.
  $$
  H(X,Y) = H(X) + H(X|Y) .
  $$
  
* conditional entropy $H(Y|X)$ 可想象成把$H(Y)$的区域**挖掉** 和$H(X)$相关 的部分, 也就是所谓的[Theorem: Conditioning reduces entropy](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-conditioning-reduces-entropy)).
  $$
  H(Y|X) = H(Y) - I(X;Y) .
  $$

* mutual information $I(X:Y)$ 可想象成$H(X)$ 和 $H(Y)$ 的交集:
  $$
  I(X;Y) = H(X) - H(X|Y) = H(Y) - H(Y|X) .
  $$
  

## Shannon Entropy

Definition: The entropy of a discrete random variable $X$ with pmf $P_X(\cdot)$ is denoted by $H(X)$ or $H\left(P_X\right)$ and defined by
$$
H_b(X):=-\sum_{x \in \mathcal{X}} P_X(x) \cdot \log _2 P_X(x) \quad \text { (bits) }
$$
The formula for information entropy was introduced by Claude E. Shannon in his 1948 paper "[A Mathematical Theory of Communication](https://dl.acm.org/doi/pdf/10.1145/584091.584093?casa_token=wqoh-zFX88sAAAAA:1_6aYy6mdwnp-V-k9SdBhQYm_1k254fdb3UQtftXA_odjAacK01ilqwAZ2P9WJgACwvd7OS_Khf4)".

* **Label-invariance**: Entropy is label-invariant, meaning that **it depends only on the probability distribution** and not on the actual values that the random variable $X$.
  * E.g.,$H(5X) = H(X)$ because $5X$ and $X$ share the same probability distribution.
* Notably, $H (X)$ is itself a random variable, because $X$ is a random variable.
* Symbol convention:
  1. $\log$ is assumed to be $\log_2$ unless otherwise indicated.
  2. (在 $\log$函数 底为2时)Entropy的单位是bit.
  3. $H(X)$的下标取决于使用的$\log$函数的底. 因此$H(X), H_2(X), H_b(X)$是相同的($b$代表二进制的比特). 如果 $\log$函数 使用其它底, 设为$a$, 那么必须清楚地在文中说明: $H_a(X) = \sum_x p(x) \log _a \frac{1}{p(x)}$.



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

**Definition:** The joint entropy $H(X, Y)$ of random variables $(X, Y)$ is defined by
$$
\begin{aligned}
H(X, Y) & :=-\sum_{(x, y) \in \mathcal{X} \times \mathcal{Y}} P_{X, Y}(x, y) \cdot \log _2 P_{X, Y}(x, y) \\
& = \mathbb E\left[\log _2 \frac {1} {P_{X, Y}(X, Y)} \right] .
\end{aligned}
$$

The conditional entropy can be similarly defined as follows.



# Conditional Entropy

**Definition**: Given two jointly distributed random variables $X$ and $Y$, the conditional entropy $H(Y \mid X)$ of $Y$ given $X$ is defined by
$$
H(Y \mid X):=\sum_{x \in \mathcal{X}} P_X(x)\left(-\sum_{y \in \mathcal{Y}} P_{Y \mid X}(y \mid x) \cdot \log _2 P_{Y \mid X}(y \mid x)\right),
$$
where $P_{Y \mid X}(\cdot \mid \cdot)$ is the conditional pmf of $Y$ given $X$.
This equation can be written into three different but equivalent forms:
$$
\begin{aligned}
H(Y \mid X) 
& =-\sum_{(x, y) \in \mathcal{X} \times \mathcal{Y}} P_{X, Y}(x, y) \cdot \log _2 P_{Y \mid X}(y \mid x) \\
& =\mathbb E\left[\log _2 \frac {1} {P_{Y \mid X}(Y \mid X)} \right] \\
& =\sum_{x \in \mathcal{X}} P_X(x) \cdot H(Y \mid X=x)
\end{aligned}
$$
where $H(Y \mid X=x):=-\sum_{y \in \mathcal{Y}} P_{Y \mid X}(y \mid x) \log _2 P_{Y \mid X}(y \mid x)$.

* $\sum_{x, y} p(x, y)$也可写作$\sum_{x \in \mathcal X} \sum_{y \in \mathcal Y} p(x, y)$.

* The first line equals $-\sum_{(x, y) \in \mathcal{X} \times \mathcal{Y}} P_Y(y) \cdot P_{Y|X}(y|x) \cdot \log _2 P_{Y \mid X}(y \mid x)$, and $\sum_{x,y} \triangleq \sum_x \sum_y$. We can extract the $\sum_x$ outside, resulting in
  $$
  -\sum_{x \in \mathcal{X}} P_X(x) \sum_{y \in \mathcal Y} P(y|x) \cdot \log _2 P_{Y \mid X}(y \mid x) 
  = \sum_{x \in \mathcal{X}} P_X(x) \cdot H(Y \mid X=x) .
  $$

* The probability distributions for the expectation and in the function itself are not the same! If you are unhappy with that, just remember that for any arbitrary function, $\mathbb{E}[f(X, Y)]=\sum_{x, y} p(x, y) f(x, y)$, and in this case, that arbitrary function is $\log \frac{1}{p(y \mid x)}$.

The relationship between joint entropy and conditional entropy is exhibited by the fact that the entropy of a pair of random variables is the entropy of one plus the conditional entropy of the other.

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

# Theorem: Function reduces entropy

Let $X$ be a discrete random variable. That **the entropy of a function** of $X$ is less than or equal to **the entropy of** $X$ by justifying the following steps:
$$
\begin{aligned}
H(X, g(X)) & \stackrel{(a)}{=} H(X)+H(g(X) \mid X) \\
& \stackrel{(b)}{=} H(X) ; \\
H(X, g(X)) & \stackrel{(c)}{=} H(g(X))+H(X \mid g(X)) \\
& \stackrel{(d)}{\geq} H(g(X)) .
\end{aligned}
$$

Thus $H(g(X)) \leq H(X)$.
Explanation:

1. $H(X, g(X))=H(X)+H(g(X) \mid X)$ by the chain rule for entropies.

2. $H(g(X) \mid X)=0$ is because: Since for any particular value of $X, g(X)$ is fixed, then $p(g(X)=g(x)|X=x) = 1$. By definition of conditional entropy:
   $$
   H(X,g(X)) = 
   -\sum_{(x, g(x)) } p(x, g(x)) \cdot \log _2 p[g(x) \mid x] = -\sum_{(x, g(x)) } p(x, g(x)) \cdot 0 = 0
   $$
   Meanwhile, if $H(Y|X) = 0$, we can also say $Y$ is a function(or injection) of $X$.

3. $H(X, g(X))=H(g(X))+H(X \mid g(X))$ again by the chain rule.

4. $H(X \mid g(X)) \geq 0$, with equality iff $X$ is a function of $g(X)$, i.e., $g(\cdot)$ is one-to-one. Hence $H(X, g(X)) \geq$ $H(g(X))$.

Combining (1)-(4), we obtain $H(X) \geq H(g(X))$.



# Properties of Joint Entropy and Conditional Entropy

## $H(Y|X) \le H(Y)$

$H(Y|X) \le H(Y)$( see [->proof](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-conditioning-reduces-entropy) ) with equality holding iff $X$ and $Y$ are **independent**.

## Entropy is additive for independent r.v.

*Entropy is additive for independent random variables; i.e.,*
$$
\begin{aligned}
H\left(X, Y\right) 
& =\mathbb{E}\left[\log \frac{1}{p\left(X,Y\right)}\right] \\
& =\mathbb{E}\left[\log \frac{1}{p\left(X\right) p\left(Y\right)}\right] \\
& =\mathbb{E}\left[\log \frac{1}{p\left(X\right)}\right]+\mathbb{E}\left[\log \frac{1}{p\left(Y\right)}\right] \\
& =H\left(X\right)+H\left(Y\right) .
\end{aligned}
$$

* The 2nd line holds since $X,Y$ are independent.

If $X$ and $Y$ are not independent, we can use [chain rule](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) to compute $H(X,Y)$.

## Conditional entropy is lower additive

Conditional entropy is lower additive; i.e.,
$$
H\left(X_1, X_2 \mid Y_1, Y_2\right) \leq H\left(X_1 \mid Y_1\right)+H\left(X_2 \mid Y_2\right) .
$$
Equality holds iff
$$
P_{X_1, X_2 \mid Y_1, Y_2}\left(x_1, x_2 \mid y_1, y_2\right)=P_{X_1 \mid Y_1}\left(x_1 \mid y_1\right) P_{X_2 \mid Y_2}\left(x_2 \mid y_2\right)
$$
for all $x_1, x_2, y_1$ and $y_2$.

Proof: Using the [chain rule](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) for conditional entropy and the fact that conditioning reduces entropy, we can write
$$
\begin{aligned}
H\left(X_1, X_2 \mid Y_1, Y_2\right) & =H\left(X_1 \mid Y_1, Y_2\right)+H\left(X_2 \mid X_1, Y_1, Y_2\right) \\
& \leq H\left(X_1 \mid Y_1, Y_2\right)+H\left(X_2 \mid Y_1, Y_2\right) \\
& \leq H\left(X_1 \mid Y_1\right)+H\left(X_2 \mid Y_2\right)
\end{aligned}
$$

For the 2nd line, equality holds iff $X_1$ and $X_2$ are conditionally independent given $\left(Y_1, Y_2\right)$ : $P_{X_1, X_2 \mid Y_1, Y_2}\left(x_1, x_2 \mid y_1, y_2\right)=P_{X_1 \mid Y_1, Y_2}\left(x_1 \mid y_1, y_2\right) P_{X_2 \mid Y_1, Y_2}\left(x_2 \mid y_1, y_2\right)$. 

For the 3rd line, equality holds iff $X_1$ is conditionally independent of $Y_2$ given $Y_1$ (i.e., $P_{X_1 \mid Y_1, Y_2}\left(x_1 \mid y_1, y_2\right)=$ $P_{X_1 \mid Y_1}\left(x_1 \mid y_1\right)$ ), and $X_2$ is conditionally independent of $Y_1$ given $Y_2$ (i.e., $P_{X_2 \mid Y_1, Y_2}\left(x_2 \mid y_1\right.$, $\left.\left.y_2\right)=P_{X_2 \mid Y_2}\left(x_2 \mid y_2\right)\right)$. 

Hence, the desired equality condition of the lemma is obtained.

## Others

Suppose that $X$ is a random variable whose entropy $H(X)$ is $k$ bits. Suppose that $Y(X)$ is
a **deterministic** function that takes on a different value for each value of $X$.

1. $H(Y ) = k \quad \text{bits}$ also.
2. The conditional entropy of Y given X: $H(Y|X) = 0$ because of determinism.
3. The conditional entropy of X given Y : $H(X|Y) = 0$ also.
4. The joint entropy $H(X, Y) = H(X) + H(Y|X) = k \quad \text{bits}$.



Suppose now that the deterministic function $Y(X)$ is not invertible; in other words,
different values of $X$ may correspond to the same value of $Y(X)$. In that case, 

1. The new distribution of $Y$ has lost entropy and so $H(Y) < k \quad \text{bits}$.
2. Now knowledge of Y no longer determines $X$, and so the conditional entropy $H(X|Y)$
   is no longer zero: $H(X|Y) > 0$.



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

## Properties of Relative Entropy

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

It can be expressed in terms *relative entropy* between their joint distribution $p_{X, Y}$ and the product of their marginal distributions $p_X \cdot p_Y$
$$
\begin{aligned}
I(X ; Y) & =\sum_{x, y} p(x, y) \log \frac{p_{X, Y}(x, y)}{p_X(x) \cdot p_Y(y)} \\
& =D\left(p_{X, Y} \| p_X \cdot p_Y\right) .
\end{aligned}
$$




## Properties of Mutual Information

### Basics

1. $I(X ; Y)=\sum_{x \in \mathcal{X}} \sum_{y \in \mathcal{Y}} P_{X, Y}(x, y) \log _2 \frac{P_{X, Y}(x, y)}{P_X(x) P_Y(y)}$.

2. $I(X ; Y)=I(Y ; X)=H(Y)-H(Y \mid X)$.
3. $I(X ; Y)=H(X)+H(Y)-H(X, Y)$.

4. $I(X ; Y) \leq H(X)$ with equality holding iff $X$ is a function of $Y$ (i.e., $X=f(Y)$ for some function $f(\cdot))$.
5. $I(X ; Y) \geq 0$ with equality holding iff $X$ and $Y$ are independent.
6. $I(X ; Y) \leq \min \left\{\log _2|\mathcal{X}|, \log _2|\mathcal{Y}|\right\}$.



Proof:

Properties 1, 2, 3, and 4 follow immediately from the definition. 

Property 5 is a direct consequence of $D(p \| q) \geq 0$, since $I(X:Y) = D\left(p_{X, Y} \| p_X \cdot p_Y\right)$ .

Property 6 holds iff $I(X ; Y) \leq \log _2|\mathcal{X}|$ and $I(X ; Y) \leq \log _2|\mathcal{Y}|$. 

To show the first inequality, we write $I(X ; Y)=H(X)-$ $H(X \mid Y)$, use the fact that $H(X \mid Y)$ is nonnegative and apply [Theorem: $H(X) \le |\mathcal X|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/#theorem-hx-leq-log-mathcalx). A similar proof can be used to show that $I(X ; Y) \leq \log _2|\mathcal{Y}|$.

The relationships between $H(X), H(Y), H(X, Y), H(X \mid Y), H(Y \mid X)$, and $I(X ; Y)$ can be illustrated by the Venn diagram in the above figure.



### $I(X:Y) = I(Y:X)$

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

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/VennInfo3Var.svg/256px-VennInfo3Var.svg.png)

> Venn diagram of information theoretic measures for three variables $x, y$, and $z$, represented by the lower left, lower right, and upper circles, respectively. 
>
> The conditional mutual informations $I(x ; z \mid y), I(y ; z \mid x)$ and $I(x ; y \mid z)$ are represented by the yellow, cyan, and magenta regions, respectively.

The conditional mutual information, denoted by $I(X ; Y \mid Z)$, is defined as the common uncertainty between $X$ and $Y$ under the knowledge of $Z$ :
$$
I(X ; Y \mid Z):=H(X \mid Z)-H(X \mid Y, Z)
$$

可以这么想像: $I(X;Y)$ 就是 $H(X)$ 和 $H(Y)$ 的交集, 再挖掉其中 $H(Z)$ 的部分就是$I(X;Y|Z)$. 对应于图中粉色部分.

## Joint Mutual Information

Lemma: Defining the joint mutual information between $X$ and the pair $(Y, Z)$  by
$$
I(X ; Y, Z):=H(X)-H(X \mid Y, Z),
$$
we have
$$
I(X ; Y, Z)=I(X ; Y)+I(X ; Z \mid Y)=I(X ; Z)+I(X ; Y \mid Z) .
$$
$X$ 和 $(Y,Z)$的互信息 = $X$ 和 $Y$ 的互信息 + 在$Y$ 已知的情况下 $X$ 和 $Z$ 的互信息. 

可以这么想像: 把$H(Y), H(Z)$ 连成一块得到$H(Y,Z)$, $I(X;Y,Z)$ 就是 $H(X)$ 和 $H(Y,Z)$ 的交集. 对应于图中黄, 灰, 粉三块区域的并集.

Proof: Without loss of generality, we only prove the first equality:
$$
\begin{aligned}
I(X ; Y, Z) & =H(X)-H(X \mid Y, Z) \\
& =H(X)-H(X \mid Y)+H(X \mid Y)-H(X \mid Y, Z) \\
& =I(X ; Y)+I(X ; Z \mid Y) .
\end{aligned}
$$

The above lemma can be read as follows: the information that $(Y, Z)$ has about $X$ is equal to the information that $Y$ has about $X$ plus the information that $Z$ has about $X$ when $Y$ is already known.

# Properties of Entropy and Mutual Information for Multiple Random Variables

## Chain rule for joint entropy

**Theorem**: Let $X_1, X_2, \ldots, X_n$ be drawn according to $P_{X^n}\left(x^n\right):=P_{X_1, \ldots, X_n}\left(x_1, \ldots, x_n\right)$, where we use the common superscript notation to denote an $n$-tuple: $X^n:=\left(X_1, \ldots, X_n\right)$ and $x^n:=\left(x_1, \ldots, x_n\right)$.

Then
$$
H\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right),
$$
where $H\left(X_i \mid X_{i-1}, \ldots, X_1\right):=H\left(X_1\right)$ for $i=1$. (The above chain rule can also be written as:
$$
H\left(X^n\right)=\sum_{i=1}^n H\left(X_i \mid X^{i-1}\right)
$$
where $X^i:=\left(X_1, \ldots, X_i\right)$.)

> For example, for three random variables $X$, $Y$ , and $Z$,
> $$
> \begin{aligned}
> H(X, Y, Z) & =H(X)+H(Y, Z \mid X)   \\
> & =H(X)+H(Y \mid X)+H(Z \mid X, Y) 
> \end{aligned}
> $$

***

Proof:

From [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) ,
$$
H\left(X_1, X_2, \ldots, X_n\right)=H\left(X_1, X_2, \ldots, X_{n-1}\right)+H\left(X_n \mid X_{n-1}, \ldots, X_1\right)
$$

Once again, applying [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) to the first term of the right-hand side of this equation, we have
$$
H\left(X_1, X_2, \ldots, X_{n-1}\right)=H\left(X_1, X_2, \ldots, X_{n-2}\right)+H\left(X_{n-1} \mid X_{n-2}, \ldots, X_1\right)
$$

The desired result can then be obtained by repeatedly applying [chain rule for 2 r.v.](https://lyk-love.cn/2023/10/15/Shannon-Entrophy/#chain-rule-for-entropy2-variables) .

## Chain rule for conditional entropy

Theorem:
$$
H\left(X_1, X_2, \ldots, X_n \mid Y\right)=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1, Y\right) .
$$

***

Proof:

The theorem can be proved similarly to [Chain Rule for Entropy(2 Variables)](https://lyk-love.cn/2023/10/15/shannon-entrophy/?highlight=shann#chain-rule-for-entropy2-variables).
If $X^n=\left(X_1, \ldots, X_n\right)$ and $Y^m=\left(Y_1, \ldots, Y_m\right)$ are jointly distributed random vectors (of not necessarily equal lengths), then their joint mutual information is given by
$$
I\left(X_1, \ldots, X_n ; Y_1, \ldots, Y_m\right):=H\left(X_1, \ldots, X_n\right)-H\left(X_1, \ldots, X_n \mid Y_1, \ldots, Y_m\right) .
$$

## Chain rule for mutual information

Theorem:
$$
I\left(X_1, X_2, \ldots, X_n ; Y\right)=\sum_{i=1}^n I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right),
$$
where $I\left(X_i ; Y \mid X_{i-1}, \ldots, X_1\right):=I\left(X_1 ; Y\right)$ for $i=1$.

***

Proof:

This can be proved by first expressing mutual information in terms of entropy and conditional entropy, and then applying the chain rules for entropy and conditional entropy.

## Independence bound on entropy

Theorem:
$$
H\left(X_1, X_2, \ldots, X_n\right) \leq \sum_{i=1}^n H\left(X_i\right) .
$$

Equality holds iff all the $X_i$ 's are independent of each other.[^8]

***

Proof:

By applying the chain rule for entropy,
$$
\begin{aligned}
H\left(X_1, X_2, \ldots, X_n\right) & =\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) \\
& \leq \sum_{i=1}^n H\left(X_i\right) .
\end{aligned}
$$

Equality holds iff each conditional entropy is equal to its associated entropy, that iff $X_i$ is independent of $\left(X_{i-1}, \ldots, X_1\right)$ for all $i$.

## Bound on mutual information

Theorem: If $\left\{\left(X_i, Y_i\right)\right\}_{i=1}^n$ is a process satisfying the conditional independence assumption $P_{Y^n \mid X^n}=\prod_{i=1}^n P_{Y_i \mid X_i}$, then
$$
I\left(X_1, \ldots, X_n ; Y_1, \ldots, Y_n\right) \leq \sum_{i=1}^n I\left(X_i ; Y_i\right),
$$
with equality holding iff $\left\{X_i\right\}_{i=1}^n$ are independent.

***

Proof:

From the independence bound on entropy, we have
$$
H\left(Y_1, \ldots, Y_n\right) \leq \sum_{i=1}^n H\left(Y_i\right) .
$$

By the conditional independence assumption, we have
$$
\begin{aligned}
H\left(Y_1, \ldots, Y_n \mid X_1, \ldots, X_n\right) & =E\left[-\log _2 P_{Y^n \mid X^n}\left(Y^n \mid X^n\right)\right] \\
& =E\left[-\sum_{i=1}^n \log _2 P_{Y_i \mid X_i}\left(Y_i \mid X_i\right)\right] \\
& =\sum_{i=1}^n H\left(Y_i \mid X_i\right) .
\end{aligned}
$$

Hence,
$$
\begin{aligned}
I\left(X^n ; Y^n\right) & =H\left(Y^n\right)-H\left(Y^n \mid X^n\right) \\
& \leq \sum_{i=1}^n H\left(Y_i\right)-\sum_{i=1}^n H\left(Y_i \mid X_i\right) \\
& =\sum_{i=1}^n I\left(X_i ; Y_i\right),
\end{aligned}
$$
with equality holding iff $\left\{Y_i\right\}_{i=1}^n$ are independent, which holds iff $\left\{X_i\right\}_{i=1}^n$ are independent.



[^8]: This condition is equivalent to requiring that $X_i$ be independent of $\left(X_{i-1}, \ldots, X_1\right)$ for all $i$. The equivalence can be directly proved using the chain rule for joint probabilities, i.e., $P_{X^n}\left(x^n\right)=$ $\prod_{i=1}^n P_{X_i \mid X_1^{i-1}}\left(x_i \mid x_1^{i-1}\right) ;$ it is left as an exercise.
