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

[-> wiki: Marginal distribution](https://en.wikipedia.org/wiki/Marginal_distribution)

**Definition:** Let $A, B$ be two arbitrary statements about [random variables](https://statproofbook.github.io/D/rvar) $X, Y$, 

$P(A)$ is the marginal probability of $A$ given $B$.
$$
p(A) = \sum _{j} p(a_i,b_j) = \sum _{j} p(X=x_i,Y=y_j)
$$
$p(A)$ is the [probability distribution](https://en.wikipedia.org/wiki/Probability_distribution) of $X$ when the values of $Y$ are not taken into consideration. 

This can be calculated by <u>summing the joint probability distribution over all values of $Y$</u>

Naturally, the converse is also true: the marginal distribution can be obtained for $Y$ by summing over the separate values of $X$:
$$
p(B) = \sum _{i} p(a_i,b_j)= \sum _{i} p(X=x_i,Y=y_j)
$$




# Conditional Probability

**Definition:** Let $A, B$ be two events , The conditional probability of $A$ given $B$ is defined to be:
$$
p(A|B) = \frac{p(A,B)}{p(B)}
$$
where $p(B)$ is the [marginal probability](https://statproofbook.github.io/D/prob-marg) of $B$.

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
