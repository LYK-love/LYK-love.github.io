---
title: P, NP and NP-Completeness
tags: Computational Theory
categories: Computer Science
mathjax: true
date: 2024-02-02 00:24:37
---


Source:

1. [CMU CS651: P, NP, and NP-Completeness](https://www.cs.cmu.edu/~avrim/451/lectures/lect1102.pdf)

<!--more-->

# Reductions and Expressiveness

**Definition**: We say that an algorithm runs in *Polynomial Time* if, for some constant $c$, its running time is $O\left(n^c\right)$, where $n$ is the size of the input.

In the above definition, "size of input" means "number of bits it takes to write the input down". So, to be precise, when defining a problem and asking whether or not a certain algorithm runs in polynomial time, it is important to say how the input is given.



**Definition**: A problem $A$ is *poly-time reducible* to problem $B$ (written as $A \leq_p B$ ) if we can solve problem $A$ in polynomial time given a polynomial time black-box algorithm for problem $B$[^1]. Problem $A$ is poly-time equivalent to problem $B\left(A={ }_p B\right)$ if $A \leq_p B$ and $B \leq_p A$.

For instance, we gave an efficient algorithm for Bipartite Matching by showing it was poly-time reducible to Max Flow. Notice that it could be that $A \leq_p B$ and yet our fastest algorithm for solving problem $A$ might be slower than our fastest algorithm for solving problem $B$ (because our reduction might involve several calls to the algorithm for problem $B$, or might involve blowing up the input size by a polynomial but still nontrivial amount).

# Decision Problems and Karp Reductions

We consider decision problems: problems whose answer is YES or NO. E.g., "Does the given network have a flow of value at least $k$ ?" or "Does the given graph have a 3-coloring?" For such problems, we split all instances into two categories: YES-instances (whose correct answer is YES) and NO-instances (whose correct answer is NO). We put any ill-formed instances into the NO category.

In this lecture, we seek *reductions* (called **Karp reductions**) that are of a special form:

**Many-one reduction (a.k.a. Karp reduction) from problem $A$ to problem $B$** : To reduce problem $A$ to problem $B$ we want a function $f$ that maps arbitrary instances of $A$ to instances of $B$ such that:

1. if $x$ is a YES-instance of $A$ then $f(x)$ is a YES-instance of $B$.
2. if $x$ is a NO-instance of $A$ then $f(x)$ is a NO-instance of $B$.
3. $f$ can be computed in polynomial time.

So, if we had an algorithm for $B$, and a function $f$ with the above properties, we could using it to solve $A$ on any instance $x$ by running it on $f(x)$[^2].

# P

**P is the set of decision problems solvable in polynomial time.**

E.g., the decision version of the network flow problem: "Given a network $G$ and a flow value $k$, does there exist a flow $\geq k$ ?" belongs to P.

# NP

**NP** is the set of decision problems that **have polynomial-time verifiers**. Specificially, problem $Q$ is in NP if there is a polynomial-time algorithm $V(I, X)$ such that:

- If $I$ is a YES-instance, then there exists $X$ such that $V(I, X)=Y E S$.
- If $I$ is a $N O$-instance, then for all $X, V(I, X)=N O$.

Furthermore, $X$ should have length polynomial in size of $I$ (since we are really only giving $V$ time polynomial in the size of the instance, not the combined size of the instance and solution).

The second input $X$ to the verifier $V$ is often called a witness. E.g., for 3-coloring, the witness that an answer is YES is the coloring. For factoring, the witness that $N$ has a factor between 2 and $k$ is a factor. For the Traveling Salesman Problem: "Given a weighted graph $G$ and an integer $k$, does $G$ have a tour that visits all the vertices and has total length at most $k$ ?" the witness is the tour. All these problems belong to NP. Of course, any problem in $\mathbf{P}$ is also in $\mathbf{N P}$, since $V$ could just ignore $X$ and directly solve $I$. So, $\mathbf{P} \subseteq \mathbf{N P}$.

A huge open question in complexity theory is whether $\mathbf{P}=\mathbf{N P}$. It would be quite strange if they were equal since that would mean that any problem for which a solution can be easily verified also has the property that a solution can be easily found. So most people believe $\mathbf{P} \neq \mathbf{N P}$. But, it's very hard to prove that a fast algorithm for something does not exist. So, it's still an open problem.

Loosely speaking, NP-complete problems are the "hardest" problems in NP, if you can solve them in polynomial time then you can solve any other problem in NP in polynomial time. Formally,

# NP-complete

Definition: Problem $Q$ is **NP-complete** if:

1. $Q$ is in NP, and
2. For any other problem $Q^{\prime}$ in $\mathbf{N P}, Q^{\prime} \leq_p Q$ using Karp reductions.

So if $Q$ is NP-complete and you could solve $Q$ in polynomial time, you could solve any problem in NP in polynomial time. If $Q$ just satisfies part (2) of the definition, then it's called **NP-hard**.



A common application of reductions is in proving NP-completeness. If $A$ is a known NP-complete problem and $A \leq B$ (i.e., $A$ can be polynomially reduced to $B$ ), and $B$ is in NP, then $B$ is also NP-complete, indicating $B$ is at least as hard as some of the hardest problems in NP.







![Figure 5.23: The beginnings of the family tree ofNP-complete problems.](/Users/lyk/Library/Application Support/typora-user-images/image-20240201163213887.png)

[^1]: You can loosely think of $A \leq_p B$ as saying "$A$ is no harder than $B$, up to polynomial factors."
[^2]: Why Karp reductions? Why not reductions that, e.g., map YES-instances of $A$ to NO-instances of $B$ ? Or solve two instances of $B$ and use that answer to solve an instance of $A$ ? Two reasons. Firstly, Karp reductions give a stronger result. Secondly, using general reductions (called Turing reductions) no longer allows us to differentiate between NP and co-NP, say; see Section 8 for a discussion.
