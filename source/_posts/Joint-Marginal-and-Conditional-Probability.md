---
title: Joint, Marginal, and Conditional Probability
tags: 
- Probability Theory
- Statistics
categories: Mathematics
mathjax: true
date: 2023-10-14 01:22:01
---


Ref:

1. [Probability_Theory by Kyle Siegrist](https://stats.libretexts.org/Bookshelves/Probability_Theory/Probability_Mathematical_Statistics_and_Stochastic_Processes_(Siegrist)/02%3A_Probability_Spaces)
2. [The Book of Statistical Proofs](https://statproofbook.github.io/)

<!--more-->

# Joint Probability

**Definition:** Joint probability is the likelihood that two or more events will coincide.

Let $A, B$ be two arbitrary statements about [random variables](https://statproofbook.github.io/D/rvar), joint probability $p(A, B)$ is **a measure of the likelihood of the two events occurring together**.



# Marginal Probility

[-> Definition: Law of marginal probability](https://statproofbook.github.io/D/prob-marg)

**Definition:** 

Given a known joint distribution of two discrete random variables, say, $X$ and $Y$, the marginal distribution of either variable $-X$ for example - is the probability distribution of $X$ when the values of $Y$ are not taken into consideration.
$$
p_X\left(x_i\right)=\sum_j p\left(x_i, y_j\right), \text { and } p_Y\left(y_j\right)=\sum_i p\left(x_i, y_j\right)
$$



# Conditional Probability

**Definition:** Let $A, B$ be two events, The conditional probability of $A$ given $B$ is defined to be:
$$
\begin{equation} \label{eq_conditional_probability}
p(A|B) = \frac{p(A,B)}{p(B)}
\end{equation}
$$
where $p(B)$ is the [marginal probability](https://statproofbook.github.io/D/prob-marg) of $B$.

## Conditional Probability with Multiple Conditions

Also you can define conditional probability **with multiple conditions**.

Say I have two events,$A$ and $B$, and some observations $C$,  the conditional probability of $A$ given $B$ and $C$ is defined to be:
$$
P(A|B,C) = \frac{p(A,(B,C))}{p((B,C))}
$$
Since the intersection operation($\cap$) is communicative, we have $p(A,(B,C)) = p(A,B,C)$. So
$$
P(A|B,C) = \frac{p(A,B,C)}{p(B,C)}
$$

# Chain Rules

We can rearrange the formula for conditional probability $\eqref{eq_conditional_probability}$ to get the so-called product rule:
$$
P(A, B)=P(A \mid B) P(B)
$$

We can extend this for three variables:
$$
P(A, B, C)=P(A \mid B, C) P(B, C)=P(A \mid B, C) P(B \mid C) P(C)
$$
and in general to $n$ variables:
$$
P(A_1, A_2, \ldots, A_n)=P(A_1 \mid A_2, \ldots, A_n) P(A_2 \mid A_3, \ldots, A_n) P(A_{n-1} \mid A_n) P(A_n)
$$

In general we refer to this as the chain rule.



Note: for $P(A,B|C)$, we have
$$
P(A,B|C) = P( \ (A|C) | (B|C ) \ ).P(B|C) = P(A|B,C).P(B|C)
$$


# Proof: Probability under statistical independence

**Theorem:** Let $A$ and $B$ be two statements about [random variables](https://statproofbook.github.io/D/rvar). Then, if $A$ and $B$ are [independent](https://statproofbook.github.io/D/ind), [marginal](https://statproofbook.github.io/D/prob-marg) and [conditional](https://statproofbook.github.io/D/prob-cond) probabilities are equal:
$$
\begin{split}
p(A) &= p(A|B) \\
p(B) &= p(B|A) \; .
\end{split}
$$


**Proof:** If $A$ and $B$ are [independent](https://statproofbook.github.io/D/ind), then the [joint probability](https://statproofbook.github.io/D/prob-joint) is equal to the product of the [marginal probabilities](https://statproofbook.github.io/D/prob-marg):
$$
p(A,B) = p(A) \cdot p(B) \; .
$$


The [law of conditional probability](https://statproofbook.github.io/D/prob-cond) states that
$$
p(A|B) = \frac{p(A,B)}{p(B)} \; .
$$


Combining above, we have:
$$
p(A|B) = \frac{p(A) \cdot p(B)}{p(B)} = p(A) \; .
$$


Equivalently, we can write:
$$
p(B|A) = \frac{p(A,B)}{p(A)} = \frac{p(A) \cdot p(B)}{p(A)} = p(B) \; .
$$

# Mutual Exclusivity

**Definition:** Generally speaking, [random events](https://statproofbook.github.io/D/reve) are mutually exclusive, if they cannot occur together, such that their intersection is equal to the [empty set](https://statproofbook.github.io/P/prob-emp).

* Mutual Exclusivity仅适用于random events, 后者是取值只有两种的随机变量(也称为二元随机变量).

More precisely, a set of random events $A_1, A_2, \cdots, A_n$ is called mutually exclusive, if
$$
p(A_1, \cdots, A_n) = 0
$$


where $p(A_1, \cdots, A_n)$ is the [joint probability](https://statproofbook.github.io/D/prob-joint) of random events $A_1, A_2, \cdots, A_n$.

# Proof: Probability under mutual exclusivity

**Theorem:** Let $A$ and $B$ be two statements about [random variables](https://statproofbook.github.io/D/rvar). Then, if $A$ and $B$ are [mutually exclusive](https://statproofbook.github.io/D/exc), the [probability](https://statproofbook.github.io/D/prob) of their disjunction is equal to the sum of the [marginal probabilities](https://statproofbook.github.io/D/prob-marg):
$$
p(A \vee B) = p(A) + p(B) \; .
$$


**Proof:** If $A$ and $B$ are [mutually exclusive](https://statproofbook.github.io/D/exc), then their [joint probability](https://statproofbook.github.io/D/prob-joint) is zero:
$$
p(A,B) = 0 \; .
$$


The [addition law of probability](https://statproofbook.github.io/D/prob-marg) states that
$$
p(A \cup B) = p(A) + p(B) - p(A \cap B)
$$


which, in logical rather than set-theoretic expression, becomes
$$
p(A \vee B) = p(A) + p(B) - p(A,B) \; .
$$


Because the [union of mutually exclusive events is the empty set](https://statproofbook.github.io/D/exc) and the [probability of the empty set is zero](https://statproofbook.github.io/P/prob-emp), the [joint probability](https://statproofbook.github.io/D/prob-joint) term cancels out:
$$
p(A \vee B) = p(A) + p(B) - p(A,B) = p(A) + p(B) \; .
$$
