---
title: Entropy Rate
tags:
  - Information Theory
categories: Mathematics
mathjax: true
date: 2023-11-11 21:13:48
---

Ref:


1. [EE 376A: Information Theory. Winter 2018. Lecture 4.](https://web.stanford.edu/class/ee376a/files/2017-18/lecture_4.pdf) - Stanford University
2. [EE 376A: Information Theory. Winter 2017. Lecture 4.](https://tselab.stanford.edu/mirror/ee376a_winter1617/Lecture_4.pdf) - Stanford University
3. Elements of Information Theory

<!--more-->

# Intro

The asymptotic equipartition property in [AEP](https://lyk-love.cn/2023/11/10/asymptotic-equipartition-property/) establishes that $n H(X)$ bits suffice on the average to describe $n$ **iid** random variables.

> Proof: we know $n$ bits can describe $2^n$ different symbols. So $n H(X)$ bits can describe   $2^{n H(X)}$different symbols, which is the number of "typical" symbols ($\left|A_\epsilon^{(n)}\right|$).



But what if the random variables are **dependent**? In particular, what if the random variables form a stationary process? We will show, just as in the i.i.d. case, that the entropy $H\left(X_1, X_2, \ldots, X_n\right)$ grows (asymptotically) linearly with $n$ at a rate $H(\mathcal{X})$, which we will call the **entropy rate** of the process. The interpretation of $H(\mathcal{X})$ as the best achievable data compression will await the analysis in Chapter 5.

# Notation

* a [stochastic process]() $X^n=\left(X_1, \ldots, X_n\right)$ denotes an indexed sequence of $n$ random variables. We also denote it as $\left\{X_i\right\}$. So
  $$
  P\left(X_1, X_2, \ldots, X_n\right) \triangleq P(X^n) \triangleq P(\{X_i\}) .
  $$
  

# Entropy Rate $H(\mathcal{X})$

If we have a sequence of $n$ random variables, a natural question to ask is: **How does the entropy of the sequence grow with $n$ ?** We define the entropy rate as this rate of growth as follows.

**Definition:** The entropy of a [stochastic process]() $\left\{X_i\right\}$ is defined by
$$
\begin{equation} \label{eq1}
H(\mathcal{X})=\lim _{n \rightarrow \infty} \frac{1}{n} H\left(X_1, X_2, \ldots, X_n\right)
\end{equation}
$$
<u>when the limit exists.</u>

***

We now consider some simple examples of stochastic processes and their corresponding entropy rates.

1. Typewriter.
   Consider the case of a typewriter that has $m$ equally likely output letters. The typewriter can produce $m^n$ sequences of length $n$, all of them equally likely, with probability $\frac{1}{m^n}$. Hence $P\left(X_1, X_2, \ldots, X_n\right)=\frac{1}{m^n}$, and since this is a [uniform distribution](), we have $H(X^n)=\log m^n$. The entropy rate is $H(\mathcal{X})=\log m$ bits per symbol.
2. $X_1, X_2, \ldots$ are **i.i.d.** random variables. Then

$$
H(\mathcal{X})=\lim \frac{H\left(X_1, X_2, \ldots, X_n\right)}{n}=\lim \frac{n H\left(X_1\right)}{n}=H\left(X_1\right),
$$

which is what one would expect for the entropy rate per symbol. The second equation is beacuse $\{X_i\}$ are iid.

Note that **this is exactly [AEP]()**. 

3. Sequence of independent but not identically distributed random variables. In this case,
   $$
   H\left(X_1, X_2, \ldots, X_n\right)=\sum_{i=1}^n H\left(X_i\right),
   $$
   but the $H\left(X_i\right)$ 's are all not equal. <u>We can choose a sequence of distributions on $X_1, X_2, \ldots$ such that the limit of $\frac{1}{n} \sum H\left(X_i\right)$ does not exist.</u> An example of such a sequence is a random binary sequence where $p_i=P\left(X_i=1\right)$ is not constant but a function of $i$, chosen carefully so that the limit in (4.10) does not exist. For example, let
   $$
   p_i= \begin{cases}0.5 & \text { if } 2 k<\log \log i \leq 2 k+1, \\ 0 & \text { if } 2 k+1<\log \log i \leq 2 k+2\end{cases}
   $$
   for $k=0,1,2, \ldots$
   Then there are arbitrarily long stretches where $H\left(X_i\right)=1$, followed by exponentially longer segments where $H\left(X_i\right)=0$. Hence, the running average of the $H\left(X_i\right)$ will oscillate between 0 and 1 and will not have a limit. Thus, $H(\mathcal{X})$ is not defined for this process.

# $H^{\prime}(\mathcal{X})$

We can also define a related quantity for entropy rate:
$$
\begin{equation} \label{eq2}
H^{\prime}(\mathcal{X})=\lim _{n \rightarrow \infty} H\left(X_n \mid X_{n-1}, \ldots, X_1\right)
\end{equation}
$$
<u>when the limit exists.</u>



The two quantities $H(\mathcal{X})$ and $H^{\prime}(\mathcal{X})$ correspond to two different notions of entropy rate. The first is the per symbol entropy of the $n$ random variables, and the second is the conditional entropy of the last random variable given the past. 

We now prove the important result that **for stationary processes both limits exist and are equal.**

# $H(\mathcal{X}) = H^{\prime}(\mathcal{X})$

**Theorem:** For a **stationary** stochastic process, the limits in $\eqref{eq1}$ and $\eqref{eq2}$ **exist and are equal**:
$$
\begin{equation} \label{eq3}
H(\mathcal{X})=H^{\prime}(\mathcal{X})
\end{equation}
$$

***

We first prove that
$$
\lim H\left(X_n \mid X_{n-1}, \ldots, X_1\right)
$$
exists.

## Theorem: Limit Exists

**Theorem:** For a **stationary** stochastic process, $H\left(X_n \mid X_{n-1}, \ldots\right.$, $\left.X_1\right)$ is nonincreasing in $n$ and has a limit $H^{\prime}(\mathcal{X})$.

**Proof:**

First,
$$
\begin{align}
& \quad H\left(X_{n+1} \mid X_1, X_2, \ldots, X_n\right) \nonumber \\
& \quad \leq H\left(X_{n+1} \mid X_n, \ldots, X_2\right) \label{eq3.1}\\
& \quad =H\left(X_n \mid X_{n-1}, \ldots, X_1\right) \label{eq3.2},
\end{align}
$$


* The inequality $\eqref{eq3.1}$ follows from the fact that [conditioning reduces entropy](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/?highlight=conditionin#theorem-conditioning-reduces-entropy).
* The equality follows from [the stationarity of the process](). 

Then, since $H\left(X_n \mid X_{n-1}, \ldots, X_1\right)$ is a decreasing sequence of nonnegative numbers, it has a limit, $H^{\prime}(\mathcal{X})$. **//Can't understand**



## Theorem: Cesáro mean

We now use the following simple result from analysis.

**Theorem: (Cesáro mean)** If $a_n \rightarrow a$ and $b_n=\frac{1}{n} \sum_{i=1}^n a_i$, then $b_n \rightarrow a$.

**Proof:** (Informal outline). Since most of the terms in the sequence $\left\{a_k\right\}$ are eventually close to $a$, then $b_n$, which is the average of the first $n$ terms, is also eventually close to $a$.

Formal Proof: Let $\epsilon>0$. Since $a_n \rightarrow a$, there exists a number $N(\epsilon)$ such that $\left|a_n-a\right| \leq \epsilon$ for all $n \geq N(\epsilon)$. Hence,
$$
\begin{aligned}
\left|b_n-a\right| & =\left|\frac{1}{n} \sum_{i=1}^n\left(a_i-a\right)\right| \\
& \leq \frac{1}{n} \sum_{i=1}^n\left|\left(a_i-a\right)\right| \\
& \leq \frac{1}{n} \sum_{i=1}^{N(\epsilon)}\left|a_i-a\right|+\frac{n-N(\epsilon)}{n} \epsilon \\
& \leq \frac{1}{n} \sum_{i=1}^{N(\epsilon)}\left|a_i-a\right|+\epsilon
\end{aligned}
$$
for all $n \geq N(\epsilon)$. Since the first term goes to 0 as $n \rightarrow \infty$, we can make $\left|b_n-a\right| \leq 2 \epsilon$ by taking $n$ large enough. Hence, $b_n \rightarrow a$ as $n \rightarrow \infty$.

## Final Proof

Proof of $\eqref{eq1}$:



By the [chain rule](https://lyk-love.cn/2023/10/15/chain-rules-for-entropy-relative-entropy-and-mutual-information/), we know ${H\left(X_1, X_2, \ldots, X_n\right)}=\sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right)$. Then
$$
\begin{align} 
& \quad \frac{H\left(X_1, X_2, \ldots, X_n\right)}{n} \nonumber \\ 
& \quad = \frac{1}{n} \sum_{i=1}^n H\left(X_i \mid X_{i-1}, \ldots, X_1\right) \label{eq3.3.0}
\end{align}
$$
That is, the entropy rate is the time average of the conditional entropies. But we know that the conditional entropies tend to a limit $H^{\prime}$. 

Hence, by [Theorem: Cesáro mean](), their running average has a limit, which is equal to the limit $H^{\prime}$ of the terms. 

Thus, by [Theorem: Limit Exists](),
$$
\begin{align}
H(\mathcal{X}) & =\lim \frac{H\left(X_1, X_2, \ldots, X_n\right)}{n} \nonumber \\
& = \lim H\left(X_n \mid X_{n-1}, \ldots, X_1\right) \label{eq3.3.1}\\
& =H^{\prime}(\mathcal{X}) \label{eq3.3.2}
\end{align}
$$

* Equations of $\eqref{eq3.3.1}$ are from $\eqref{eq3.3.0}$.
* Equation of $\eqref{eq3.3.2}$ is from [Theorem: Cesáro mean]().



The significance of the entropy rate of a stochastic process arises from the AEP for a stationary ergodic process. We prove the [general AEP]() in Section 16.8, where we show that for any stationary ergodic process,
$$
-\frac{1}{n} \log p\left(X_1, X_2, \ldots, X_n\right) \rightarrow H(\mathcal{X})
$$
with probability 1 . 

Using this, the theorems of Chapter 3 can easily be extended to a general stationary ergodic process. 

**We can define a typical set in the same way as we did** for the i.i.d. case in [AEP](https://lyk-love.cn/2023/11/10/asymptotic-equipartition-property/).

By the same arguments, we can show that the typical set has a probability close to 1 and that there are about $2^{n H(\mathcal{X})}$ typical sequences of length $n$, each with probability about $2^{-n H(\mathcal{X})}$. 

We can therefore **represent the typical sequences of length $n$ using approximately $n H(\mathcal{X})$ bits.** This shows the significance of the entropy rate as the average description length for a stationary ergodic process.

**The entropy rate is well defined for all stationary processes.** The entropy rate is particularly easy to calculate for **Markov chains**.

# Entropy Rate of a Markov Chain

Markov Chains. For a stationary Markov chain, the entropy rate is given by
$$
\begin{aligned}
H(\mathcal{X}) & =H^{\prime}(\mathcal{X})=\lim H\left(X_n \mid X_{n-1}, \ldots, X_1\right)=\lim H\left(X_n \mid X_{n-1}\right) \\
& =H\left(X_2 \mid X_1\right),
\end{aligned}
$$
where the conditional entropy is calculated using the given stationary distribution. Recall that the stationary distribution $\mu$ is the solution of the equations
$$
\mu_j=\sum_i \mu_i P_{i j} \quad \text { for all } j .
$$

We express the conditional entropy explicitly in the following theorem.
Theorem 4.2.4 Let $\left\{X_i\right\}$ be a stationary Markov chain with stationary distribution $\mu$ and transition matrix $P$. Let $X_1 \sim \mu$. Then the entropy rate is
$$
H(\mathcal{X})=-\sum_{i j} \mu_i P_{i j} \log P_{i j}
$$

**Proof:** $\quad H(\mathcal{X})=H\left(X_2 \mid X_1\right)=\sum_i \mu_i\left(\sum_j-P_{i j} \log P_{i j}\right)$. **//Can't Understand**

## Example: MMMC

Example 4.2.1 (MMMC) The entropy rate of the twostate Markov chain in [MMMC]() is
$$
H(\mathcal{X})=H\left(X_2 \mid X_1\right)=\frac{\beta}{\alpha+\beta} H(\alpha)+\frac{\alpha}{\alpha+\beta} H(\beta) .
$$

Remark: If the Markov chain is irreducible and aperiodic, it has a unique stationary distribution on the states, and any initial distribution tends to the stationary distribution as $n \rightarrow \infty$. In this case, even though the initial distribution is not the stationary distribution, the entropy rate, which is defined in terms of long-term behavior, is $H(\mathcal{X})$, as defined in (4.25) and (4.27).
4.3 EXAMPLE: ENTROPY RATE OF A RANDOM WALK ON A WEIGHTED GRAPH

## Example: Entropy Rate of A Random Walk on A Wenghted Graph

As an example of a stochastic process, let us consider a random walk on a connected graph (Figure 4.2). 

![image-20231111210126416](/Users/lyk/Library/Application Support/typora-user-images/image-20231111210126416.png)

Consider a graph with $m$ nodes labeled $\{1,2, \ldots, m\}$, with weight $W_{i j} \geq 0$ on the edge joining node $i$ to node $j$. (The graph is assumed to be undirected, so that $W_{i j}=W_{j i}$. We set $W_{i j}=0$ if there is no edge joining nodes $i$ and $j$.)

A particle walks randomly from node to node in this graph. The random walk $\left\{X_n\right\}, X_n \in\{1,2, \ldots, m\}$, is a sequence of vertices of the graph. Given $X_n=i$, the next vertex $j$ is chosen from among the nodes connected to node $i$ with a probability proportional to the weight of the edge connecting $i$ to $j$. Thus, $P_{i j}=W_{i j} / \sum_k W_{i k}$.

<u>In this case, the stationary distribution has a surprisingly simple form</u>, which we will guess and verify. The stationary distribution for this Markov chain assigns probability to node $i$ proportional to the total weight of the edges emanating from node $i$. Let
$$
W_i=\sum_j W_{i j}
$$
be the total weight of edges emanating from node $i$, and let
$$
W=\sum_{i, j: j>i} W_{i j}
$$
be the sum of the weights of all the edges. Then $\sum_i W_i=2 W$.



We now guess that **the stationary distribution** is
$$
\mu_i=\frac{W_i}{2 W}
$$

We verify that this is the stationary distribution by checking that $\mu P=\mu$. Here
$$
\begin{aligned}
\sum_i \mu_i P_{i j} & =\sum_i \frac{W_i}{2 W} \frac{W_{i j}}{W_i} \\
& =\sum_i \frac{1}{2 W} W_{i j} \\
& =\frac{W_j}{2 W} \\
& =\mu_j .
\end{aligned}
$$

Thus, **the stationary probability of state $i$ is proportional to the weight of edges emanating from node $i$.** This stationary distribution has **an interesting property of locality:** <u>It depends only on the total weight and the weight of edges connected to the node and hence does not change if the weights in some other part of the graph are changed while keeping the total weight constant.</u> We can now calculate the entropy rate as
$$
\begin{aligned}
H(\mathcal{X}) & =H\left(X_2 \mid X_1\right) \\
& =-\sum_i \mu_i \sum_j P_{i j} \log P_{i j} \\
& =-\sum_i \frac{W_i}{2 W} \sum_j \frac{W_{i j}}{W_i} \log \frac{W_{i j}}{W_i} \\
& =-\sum_i \sum_j \frac{W_{i j}}{2 W} \log \frac{W_{i j}}{W_i} \\
& =-\sum_i \sum_j \frac{W_{i j}}{2 W} \log \frac{W_{i j}}{2 W}+\sum_i \sum_j \frac{W_{i j}}{2 W} \log \frac{W_i}{2 W} \\
& =H\left(\ldots, \frac{W_{i j}}{2 W}, \ldots\right)-H\left(\ldots, \frac{W_i}{2 W}, \ldots\right) .

\end{aligned}
$$


If all the edges have equal weight, the stationary distribution puts weight $E_i / 2 E$ on node $i$, where $E_i$ is the number of edges emanating from node $i$ and $E$ is the total number of edges in the graph. In this case, the entropy rate of the random walk is
$$
H(\mathcal{X})=\log (2 E)-H\left(\frac{E_1}{2 E}, \frac{E_2}{2 E}, \ldots, \frac{E_m}{2 E}\right) .
$$

This answer for the entropy rate is so simple that it is almost misleading. Apparently, the entropy rate, which is the average transition entropy, depends only on the entropy of the stationary distribution and the total number of edges.

## Example: Random walk on a chessboard

Let a king move at random on an $8 \times 8$ chessboard. The king has eight moves in the interior, five moves at the edges, and three moves at the corners. Using this and the preceding results, the stationary probabilities are, respectively, $\frac{8}{420}$, $\frac{5}{420}$, and $\frac{3}{420}$, and the entropy rate is $0.92 \log 8$. The factor of 0.92 is due to edge effects; we would have an entropy rate of $\log 8$ on an infinite chessboard.

Similarly, we can find the entropy rate of rooks (log 14 bits, since the rook always has 14 possible moves), bishops, and queens. The queen combines the moves of a rook and a bishop. Does the queen have more or less freedom than the pair?

# Function of Markov Chains

Here is an example that can be very difficult if done the wrong way. It illustrates the power of the techniques developed so far. 

<u>Let $X_1, X_2, \ldots, X_n, \ldots$ be a **stationary** Markov chain, and let $Y_i=\phi\left(X_i\right)$ be a process each term of which is a function of the corresponding state in the Markov chain.</u> **What is the entropy rate $H(\mathcal{Y})$ ?** 

Such functions of Markov chains occur often in practice. In many situations, one has only partial information about the state of the system. 

It would simplify matters greatly if $Y_1, Y_2, \ldots, Y_n$ also formed a Markov chain, but in many cases, this is <u>not true</u>. 

Since the Markov chain is stationary, so is $Y_1, Y_2, \ldots, Y_n$, and the entropy rate is well defined. However, if we wish to compute $H(\mathcal{Y})$, we might compute $H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right)$ for each $n$ and find the limit. Since the convergence can be arbitrarily slow, we will never know how close we are to the limit. (We can't look at the change between the values at $n$ and $n+1$, since this difference may be small even when we are far away from the limit—consider, for example, $\sum \frac{1}{n}$.)



It would be useful computationally to have **upper and lower bounds** converging to the limit from above and below. We can halt the computation when the difference between upper and lower bounds is small, and we will then have a good estimate of the limit.



## Lower Bound

We already know that $H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right)$ converges monotonically to $H(\mathcal{Y})$ from above. For a lower bound, we will use $H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right)$. This is a neat trick based on the idea that $X_1$ contains as much information about $Y_n$ as $Y_1, Y_0, Y_{-1}, \ldots$


$$
\begin{equation} \label{eq7.1}
H\left(Y_n \mid Y_{n-1}, \ldots, Y_2, X_1\right) \leq H(\mathcal{Y})
\end{equation}
$$

**Proof:** We have for $k=1,2, \ldots$,
$$
\begin{aligned}
& H\left(Y_n \mid Y_{n-1}, \ldots, Y_2, X_1\right) \stackrel{(\mathrm{a})}{=} H\left(Y_n \mid Y_{n-1}, \ldots, Y_2, Y_1, X_1\right) \\
& \stackrel{(\text { b) }}{=} H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1, X_0, X_{-1}, \ldots, X_{-k}\right) \\
& \stackrel{(\text { c) }}{=} H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1, X_0, X_{-1}, \ldots,\right. \\
&\left.X_{-k}, Y_0, \ldots, Y_{-k}\right) \\
& \stackrel{(\mathrm{d})}{\leq} H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, Y_0, \ldots, Y_{-k}\right) \\
& \stackrel{(\mathrm{e})}{=} H\left(Y_{n+k+1} \mid Y_{n+k}, \ldots, Y_1\right),
\end{aligned}
$$
where (a) follows from that fact that $Y_1$ is a function of $X_1$, and (b) follows from the Markovity of $X$, (c) follows from the fact that $Y_i$ is a function of $X_i$, (d) follows from the fact that conditioning reduces entropy, and (e) follows by stationarity. Since the inequality is true for all $k$, it is true in the limit. Thus,
$$
\begin{aligned}
H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right) & \leq \lim _k H\left(Y_{n+k+1} \mid Y_{n+k}, \ldots, Y_1\right) \\
& =H(\mathcal{Y}) .
\end{aligned}
$$

The next lemma shows that the interval between the upper and the lower bounds decreases in length.

## Lemma1

$$
\begin{align} \label{eq7.2}
& H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right)-H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right) \nonumber \\
& \rightarrow 0 \nonumber .
\end{align}
$$



**Proof:** 

The interval length can be rewritten as
$$
\begin{aligned}
& H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right)-H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right) \\
& \quad=I\left(X_1 ; Y_n \mid Y_{n-1}, \ldots, Y_1\right) .
\end{aligned}
$$

By the properties of mutual information,
$$
I\left(X_1 ; Y_1, Y_2, \ldots, Y_n\right) \leq H\left(X_1\right),
$$
and $I\left(X_1 ; Y_1, Y_2, \ldots, Y_n\right)$ increases with $n$. Thus, $\lim I\left(X_1 ; Y_1, Y_2, \ldots\right.$, $\left.Y_n\right)$ exists and
$$
\lim _{n \rightarrow \infty} I\left(X_1 ; Y_1, Y_2, \ldots, Y_n\right) \leq H\left(X_1\right) .
$$

By the chain rule,
$$
\begin{aligned}
H(X) & \geq \lim _{n \rightarrow \infty} I\left(X_1 ; Y_1, Y_2, \ldots, Y_n\right) \\
& =\lim _{n \rightarrow \infty} \sum_{i=1}^n I\left(X_1 ; Y_i \mid Y_{i-1}, \ldots, Y_1\right) \\
& =\sum_{i=1}^{\infty} I\left(X_1 ; Y_i \mid Y_{i-1}, \ldots, Y_1\right)
\end{aligned}
$$

Since this infinite sum is finite and the terms are nonnegative, the terms must tend to 0 ; that is,
$$
\lim I\left(X_1 ; Y_n \mid Y_{n-1}, \ldots, Y_1\right)=0,
$$
which proves the lemma.




## Upper and Lower Bounds

Combining $\eqref{eq7.1}$  and $\eqref{eq7.2}$, we have the following theorem.

**Theorem:** If $X_1, X_2, \ldots, X_n$ form a stationary Markov chain, and $Y_i=\phi\left(X_i\right)$, then
$$
\begin{align} \label{eq7.3}
& \quad H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right) \nonumber \\
& \quad \leq H(\mathcal{Y}) \nonumber \\
& \quad \leq H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right) \nonumber 
\end{align}
$$
and
$$
\lim H\left(Y_n \mid Y_{n-1}, \ldots, Y_1, X_1\right)=H(\mathcal{Y})=\lim H\left(Y_n \mid Y_{n-1}, \ldots, Y_1\right) .
$$

In general, we could also consider the case where $Y_i$ is a stochastic function (as opposed to a deterministic function) of $X_i$. 

# Hidden Markov Model

Consider a Markov process $X_1, X_2, \ldots, X_n$, and define a new process $Y_1, Y_2, \ldots, Y_n$, where each $Y_i$ is drawn according to $p\left(y_i \mid x_i\right)$, conditionally independent of all the other $X_j, j \neq i$; that is,
$$
p\left(x^n, y^n\right)=p\left(x_1\right) \prod_{i=1}^{n-1} p\left(x_{i+1} \mid x_i\right) \prod_{i=1}^n p\left(y_i \mid x_i\right) .
$$

Such a process, called a hidden Markov model (HMM), is used extensively in speech recognition, handwriting recognition, and so on. The same argument as that used above for functions of a Markov chain carry over to hidden Markov models, and we can lower bound the entropy rate of a hidden Markov model by conditioning it on the underlying Markov state. The details of the argument are left to the reader.
