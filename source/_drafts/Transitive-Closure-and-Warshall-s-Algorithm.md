---
title: Transitive Closure and Warshall's Algorithm
tags:
  - Discrete Mathematics
categories:
  - [Mathematics]
  - [Computer Science]
mathjax: true
---

We will show that the transitive closure of $R$ (see Section 7) is just  R∞

# THEOREM 1

Let $R$ be a relation on a set $A$. Then the [connectivity relation](https://lyk-love.cn/2023/08/15/relations-and-digraphs/#paths-in-relations-and-digraphs) $R ^{\infty}$ is the **transitive closure** of R.



We recall that if $a$ and $b$ are in the set $A$, then $a \ R^{\infty} \ b$ if and only if <u>there is a path</u> in $R$ from $a$ to $b$. 

Now $R^{\infty}$ is certainly transitive since, if $a \ R^{\infty} \ b$ and $b \ R^{\infty} \ c$, the composition of the paths from $a$ to $b$ and from $b$ to $c$ forms a path from $a$ to $c$ in $R$, and so $a R^{\infty} c$. 证明了$R^{\infty}$是transitive relation.

To show that $R^{\infty}$ is the smallest transitive relation containing $R$, we must show that if $S$ is any transitive relation on $A$ and $R \subseteq S$, then $R^{\infty} \subseteq S$. 

Theorem 1 of Section 4 tells us that if $S$ is transitive, then $S^n \subseteq S$ for all $n$; that is, if $a$ and $b$ are connected by a path of length $n$, then $a S b$. It follows that $S^{\infty}=\bigcup_{n=1}^{\infty} S^n \subseteq S$. 

**It is also true that if $R \subseteq S$, then $R^{\infty} \subseteq S^{\infty}$, since any path in $R$ is also a path in $S$.** 

Putting these facts together, we see that if $R \subseteq S$ and $S$ is transitive on $A$, **then $R^{\infty} \subseteq S^{\infty} \subseteq S$.** This means that $R^{\infty}$ is the smallest of all transitive relations on $A$ that contain $R$.

We see that $R^{\infty}$ has several interpretations. From a geometric point of view, it is called the **connectivity relation**, since it specifies which vertices are connected (by paths) to other vertices. 

If we include the relation $\Delta$ (see Section 4 ), then $R^{\infty} \cup \Delta$ is the [reachability relation](https://lyk-love.cn/2023/08/15/relations-and-digraphs/#paths-in-relations-and-digraphs) $R^*$, which is frequently more useful. .

Let $A=\{1,2,3,4\}$, and let $R=\{(1,2),(2,3),(3,4),(2,1)\}$. Find the transitive closure of $R$.
