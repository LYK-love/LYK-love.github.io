---
title: Stationary Stochastic Processes and Markov Chains
tags:
  - Information Theory
  - Statistics
categories: Mathematics
mathjax: true
date: 2023-11-11 21:14:03
---


1. [EE 376A: Information Theory. Winter 2018. Lecture 4.](https://web.stanford.edu/class/ee376a/files/2017-18/lecture_4.pdf) - Stanford University
2. [EE 376A: Information Theory. Winter 2017. Lecture 4.](https://tselab.stanford.edu/mirror/ee376a_winter1617/Lecture_4.pdf) - Stanford University
3. Elements of Information Theory

<!--more-->

#  Stochastic Process

**Definition:** A stochastic process $\left\{X_i\right\}$ is an indexed sequence of random variables. In general, **there can be an arbitrary dependence** among the random variables. 

The process is characterized by the joint probability mass functions
$$
\operatorname{Pr}\left\{\left(X_1, X_2, \ldots, X_n\right)=\left(x_1, x_2, \ldots, x_n\right)\right\}=p\left(x_1, x_2, \ldots, x_n\right).
$$
with $\left(x_1, x_2, \ldots, x_n\right) \in \mathcal{X}^n$ for $n=1,2, \ldots$



# Stationary Stochastic Process

**Definition:** A stochastic process is said to be **stationary** if the joint distribution of any subset of the sequence of random variables is **invariant with respect to shifts in the time index**; that is,
$$
\begin{aligned}
& \operatorname{Pr}\left\{X_1=x_1, X_2=x_2, \ldots, X_n=x_n\right\} \\
& \quad=\operatorname{Pr}\left\{X_{1+l}=x_1, X_{2+l}=x_2, \ldots, X_{n+l}=x_n\right\}
\end{aligned}
$$
for every $n$ and every shift $l$ and for all $x_1, x_2, \ldots, x_n \in \mathcal{X}$.

# Markov Chain

> A Markov process or a Markov chain is **a stochastic process indexed by time, and  with the property that the future is independent of the past, given the  present.** 
>
> Markov processes, named for Andrei Markov, are among the most  important of all random processes. In a sense, they are the stochastic  analogs of [differential equations and recurrence relations](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/16%3A_Markov_Processes/16.01%3A_Introduction_to_Markov_Processes#rec), which are of course, among the most important deterministic processes.
>
> [Source: Introduction to Markov Processes](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/16%3A_Markov_Processes/16.01%3A_Introduction_to_Markov_Processes). 
>
> 本文只讨论时间和状态空间均为离散的情况的markov chain.



**Definition:** A discrete stochastic process $X_1, X_2, \ldots$ is said to be a **Markov chain** or a Markov process if for $n=1,2, \ldots$,
$$
\begin{aligned}
\operatorname{Pr}\left(X_{n+1}\right. & \left.=x_{n+1} \mid X_n=x_n, X_{n-1}=x_{n-1}, \ldots, X_1=x_1\right) \\
& =\operatorname{Pr}\left(X_{n+1}=x_{n+1} \mid X_n=x_n\right)
\end{aligned}
$$
for all $x_1, x_2, \ldots, x_n, x_{n+1} \in \mathcal{X}$.

## PMF of a Markov Chain

The joint probability mass function of the random variables can be written as
$$
p\left(x_1, x_2, \ldots, x_n\right)=p\left(x_1\right) p\left(x_2 \mid x_1\right) p\left(x_3 \mid x_2\right) \cdots p\left(x_n \mid x_{n-1}\right) \label{eq1}.
$$

Proof:

let's prove this expression with mathematical induction:

1. **Base Case (n = 2):** 
   $$
   \begin{equation} \label{eq1.1}
   p(x_1,x_2)=p(x_1)p(x_2∣x_1)p(x_1,x_2)=p(x_1)p(x_2∣x_1) 
   \end {equation}
   $$

2. **Inductive Step:** Assume the expression holds for $n=k$: 
   $$
   \begin{equation} \label{eq1.2}
   p(x_1,x_2,…,xk) = p(x_1)p(x_2∣x_1)p(x_3∣x_2)⋯p(x_k∣x_{k−1})
   \end{equation}
   $$

3. Now, consider $n=k+1$:
   $$
   \begin{align}
   p(x_1,x_2,…,x_{k+1}) 
   & = p(x_1,x_2,\cdots,x_k) p(x_{k+1}∣x_1,x_2,\cdots,x_k) \label{eq1.3.1} \\
   & = p(x_1,x_2,\cdots,x_k) p(x_{k+1}∣x_k) \label{eq1.3.2} \\
   & = p(x_1) p(x_2∣x_1)p(x_3∣x_2)⋯p(x_k∣x_{k−1}) \label{eq1.3.3}
   \end{align}
   $$
   * In $\eqref{eq1.3.2}$ we apply $p(x_{k+1}∣x_1,x_2,\cdots,x_k) = p(x_{k+1}∣x_k)$, which is the preperty of a Markov chain.
   * In $\eqref{eq1.3.3}$ we apply our assumtion in the aductive step.

4. This expression matches the assumed expression for $n=k$. Therefore, by mathematical induction, the expression holds for all $n$.

   Hence, the joint probability mass function of the Markov chain can be written as:






## Time Invariant

**Definition:** The Markov chain is said to be **time invariant** if the conditional probability $p\left(x_{n+1} \mid x_n\right)$ does not depend on $n$; that is, for $n=$ $1,2, \ldots$,
$$
\operatorname{Pr}\left\{X_{n+1}=b \mid X_n=a\right\}=\operatorname{Pr}\left\{X_2=b \mid X_1=a\right\} \quad \text { for all } a, b \in \mathcal{X} .
$$

**We will assume that the Markov chain is time invariant unless otherwise stated.**

If $\left\{X_i\right\}$ is a Markov chain, $X_n$ is called the state at time $n$.



A time invariant Markov chain is **characterized by its initial state and a probability transition matrix** $P=\left[P_{i j}\right], i, j \in\{1,2, \ldots, m\}$, where $P_{i j}=\operatorname{Pr}\left\{X_{n+1}=\right.$ $\left.j \mid X_n=i\right\}$.



If it is possible to go with positive probability from any state of the Markov chain to any other state in a finite number of steps, the Markov chain is said to be **irreducible**. If the largest common factor of the lengths of different paths from a state to itself is 1 , the Markov chain is said to **aperiodic**.

# Stationary Distribution

If the probability mass function of the random variable at time $n$ is $p\left(x_n\right)$, the probability mass function at time $n+1$ is
$$
p\left(x_{n+1}\right)=\sum_{x_n} p\left(x_n\right) P_{x_n x_{n+1}} .
$$

A distribution on the states such that the distribution at time $n+1$ is the same as the distribution at time $n$ is called a **stationary distribution**.



Stationary distribution is so called because <u>if the initial state of a Markov chain is drawn according to a stationary distribution,</u> **the Markov chain forms a stationary process.**



If the finite-state Markov chain is irreducible and aperiodic, the stationary distribution is **unique**, and from any starting distribution, the distribution of $X_n$ tends to the stationary distribution as $n \rightarrow \infty$. (//TO BE PROVED)

# Example: Mickey Mouse Markov Chain

We consider an example of two-state Markov chain, which we call Mickey Mouse Markov Chain [MMMC], in order to understand basic properties of Markov chains.

![image-20231111195856090](/Users/lyk/Library/Application Support/typora-user-images/image-20231111195856090.png)

The probability transition matrix of MMMC is:
$$
P=\left[\begin{array}{cc}
1-\alpha & \alpha \\
\beta & 1-\beta
\end{array}\right]
$$
Let the stationary distribution be represented by a vector $\mu$ whose components are the stationary probabilities of states 1 and 2 , respectively. 



**//Can't understand:**

Then the stationary probability can be found by solving the equation $\mu P=\mu$ or, more simply, by balancing probabilities. 

For the stationary distribution, the net probability flow across any cut set in the state transition graph is zero. Applying this to Figure 4.1, we obtain
$$
\mu_1 \alpha=\mu_2 \beta
$$

Since $\mu_1+\mu_2=1$, the stationary distribution is
$$
\mu_1=\frac{\beta}{\alpha+\beta}, \quad \mu_2=\frac{\alpha}{\alpha+\beta} .
$$

If the Markov chain has an initial state drawn according to the stationary distribution, the resulting process will be stationary. The entropy of the



state $X_n$ at time $n$ is
$$
H\left(X_n\right)=H\left(\frac{\beta}{\alpha+\beta}, \frac{\alpha}{\alpha+\beta}\right) .
$$

However, this is not the rate at which entropy grows for $H\left(X_1, X_2, \ldots\right.$, $\left.X_n\right)$. The dependence among the $X_i$ 's will take a steady toll.

