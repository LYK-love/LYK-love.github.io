---
title: Probability Spaces
tags: Probability Theory
categories: Mathematics
mathjax: true
date: 2023-10-14 01:24:48
---



Ref:

1. [NOTES ON PROBABILITY by Greg Lawler](https://www.math.uchicago.edu/~lawler/probnotes.pdf)
2. [Probability_Theory by Kyle Siegrist](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/02%3A_Probability_Spaces)
3. [The Book of Statistical Proofs](https://statproofbook.github.io/)

<!--more-->

# Random Experiment

**Definition:** A random experiment is any repeatable procedure that [results in one](https://statproofbook.github.io/D/rvar) out of a w<u>ell-defined set of possible outcomes</u>.

- The set of possible outcomes is called [sample space](https://statproofbook.github.io/D/samp-spc).
- **A set of zero or more outcomes** is called a [random event](https://statproofbook.github.io/D/reve).
- A function that maps from events to probabilities is called a probility measure

Together, [sample space](https://statproofbook.github.io/D/samp-spc), [event space](https://statproofbook.github.io/D/eve-spc) and probility measure characterize a random experiment.

# Probability Space

**Definition:** A **probability space** is a measure space with total measure one. The standard notation is $(\Omega, \mathcal F, \mathbb P)$ where:

* the [sample space](https://statproofbook.github.io/D/samp-spc) $\Omega$.
* an [event space](https://statproofbook.github.io/D/eve-spc) $\mathcal{F} \subseteq 2^\Omega$.
* a [probability measure](https://statproofbook.github.io/D/prob-meas) $\mathbb P: \; \mathcal{F} \rightarrow [0,1]$, i.e. a function mapping from the [event space](https://statproofbook.github.io/D/eve-spc) to the real numbers, observing the [axioms of probability](https://statproofbook.github.io/D/prob-ax).

# $\Omega$

**Definition:** $\Omega$ is a set of all possible outcomes, which are denoted $\omega$ , from this experiment. 

*  $\Omega$ is sometimes called a **sample space** in elementary probability.

# $\mathcal F$

**Definition:** $\mathcal F$ is a $\sigma$-algebra (or $\sigma$-field, we will use these terms synonymously) of subsets of $\Omega$ . Sets in $\mathcal F$ are called **events**.

* $\mathcal F$ is sometimes called a **event space** in elementary probability.
* 简单地说, $\mathcal F$ is a set of events.
* Every event $E$ is a ertain subset of $\Omega$. 每个事件(event)都是若干个outcome的集合, 也就是$\Omega$的一个子集. 

## Event

对于某个event $E$, 它本身只是若干outcome的集合, 也就是说$E \subseteq \Omega$, $E \in \mathcal F$, 但我们如下"statement"来指代(或者说定义)它:

Suppose that $E \subseteq \mathcal F$ is a given event, and that the experiment is run, resulting in outcome $\omega \subseteq \Omega$,

1. If $\omega \in E$ then we say that $E$ occurs.
2. If $\omega \notin E$ then we say that $E$ does not occur.

$E$本身其实让statement成立所需的outcome, 即让indicator function
$$
1_E(\omega)= \begin{cases}1, & \omega \in E, \\ 0, & \omega \notin E .\end{cases}
$$
$1_E(\omega)= 1$成立的值, 其形式是$\omega$的集合 $w_i,w_j,w_k, ...$., 但我们用它来指代$1_E(\omega)$=1, 也就是"statement成立"这个事件.



例如: 掷一次骰子的结果有六种情况, $\omega = \{ 1,2,3,4,5,6\}$, 当我们说出statement:"骰子的结果是奇数" 时, 我们实际上就定义了一个event $A = \{ 1,3,5\}$. 它本身是让$1_{骰子的结果是奇数}(\omega)= 1$成立的值$\{1,3,5\}$, 但我们用它来指代"骰子的结果是奇数成立"这一事件.



# $\mathbb P$

A probability measure (or probability distribution) $\mathbb P$ is a <u>function</u> from $\mathcal F$ to $[0, 1]$ that satisifes the following axioms:

1. $\mathbb P(E) \ge 0$ for every event $E$.

2. $\mathbb P(\Omega) = 1$

3. If events $E_1, E_2, . . . \in \mathcal F$ are disjoint, 
   $$
   \mathbb P \left(\bigcup_{i}^\infty E_i\right) = \sum_{i}^\infty \mathbb P(E_i)
   $$
   We say "probability of $E$" for $\mathbb P(E)$. 

$\mathbb P(E)$ is a measure of the likelihood of event $E$ to occur. 

$\mathbb P(E)$ is often written as $p(E)$, $P(E)$ or $\text{Pr}(E)$.

# Discrete Probability Space

A **discrete probability space** is a probability space such that $\Omega$ is finite or countably infinite. In this case we usually choose F to be all the subsets of $\Omega$ (this can be written $\mathcal F = 2^\Omega$)

The probability measure $\mathbb P$ is given by a function 
$$
p : \Omega → [0, 1]
$$
with $\sum_{\omega \in \Omega} p(\omega) = 1$.



**Definition:** Probability is a measure of the likelihood of an event to occur.

The probability of an [event](https://en.wikipedia.org/wiki/Event_(probability_theory)) $A$ is written as $p(A)$, $P(A)$ or $\text{Pr}(A)$. 

后面我们会看到, 如果把实数域$\mathbb R$作为样本空间, 则 $(\mathbb{R}, \mathcal{B}, \mu)$ 也构成一个概率空间, 我们有:
$$
\mu_X(B)=\mathbb{P}\{X \in B\}=\mathbb{P}\left[X^{-1}(B)\right] .
$$




Note: $2^\Omega$是 $\Omega$ 的幂集(Power Set).

