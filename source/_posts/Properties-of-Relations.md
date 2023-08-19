---
title: Properties of Relations
tags:
  - Discrete Mathematics
categories:
  - Mathematics
  - Computer Science
mathjax: true
date: 2023-08-20 01:01:06
---


Ref: Bernard Kolman, Robert C. Busby & Sharon Cutler Ros. (2014). Relations and Digraph. *Discrete Mathematical Structures* (6th ed., pp. 139-204). Pearson.

<!--more-->

# Properties of Relations

In many applications to computer science and applied mathematics, we deal with relations on a set $A$ rather than relations from $A$ to $B$.

# Reflexive and Irreflexive Relations

TL;DR: $R$ is reflexive if every element $a ∈ A$ is related to itself and it is irreflexive if no element is related to itself.



* reflexive(自反性): A relation R on a set A is **reflexive** if
  $$
  \forall a \in A, \ (a, a) \in R
  $$
  That is, if
  $$
  \forall a \in A, \ a \ R\  a
  $$

  

  

* irreflexive(反自反性): A relation $R$ on a set $A$ is **irreflexive** if$$
  $$
  \forall a \in A, \ a \ \not R \ a
  $$





***

**Example:** 

1. Let $\Delta=\{(a, a) \mid a \in A\}$, so that $\Delta$ is the relation of **equality** on the set $A$ . Then $\Delta$ is reflexive, since $(a, a) \in \Delta$ for all $a \in A$.
2. Let $R=\{(a, b) \in A \times A \mid a \neq b\}$, so that $R$ is the relation of **inequality** on the set $A$. Then $R$ is irreflexive, since $(a, a) \notin R$ for all $a \in A$.
3. Let $A=\{1,2,3\}$ , and let $R=\{(1,1),(1,2)\}$. Then $R$ is not reflexive since $(2,2) \notin R$ and $(3,3) \notin R$. Also, $R$ is not irreflexive, since $(1,1) \in R$.
4. Let $A$ be a nonempty set. Let $R=\varnothing \subseteq A \times A$, the empty relation. Then $R$ is not reflexive, since  $(a, a) \notin R$ for all $a \in A$ (the empty set has no elements). However, $R$ is irreflexive.

## Relation Matrix

We can identify a reflexive or irreflexive relation by its matrix as follows. 

<u>The matrix of a reflexive relation must have all 1’s on its main diagonal, while the matrix of an irreflexive relation must have all 0’s on its main diagonal.</u>

## Digraph



Similarly, we can characterize the digraph of a reflexive or irreflexive relation as follows. 

* <u>A reflexive relation has a cycle of length 1 at every vertex.</u>

* An irreflexive relation has no cycles of length 1. 



Another useful way of saying the same thing uses the equality relation $\Delta$ on a set $A$:

* $R$ is reflexive if and only if $ \Delta \subseteq  R$.
* $R$ is irreflexive if and only if $\Delta \cap R = ∅$.



Finally, we may note that if $R$ is reflexive on a set $A$, then $\mathrm{Dom}(R) = \mathrm{Ran}(R) = A$.

# Symmetric, Asymmetric, and Antisymmetric Relations

* symmetric(对称性): A relation $R$ on a set $A$ is **symmetric** if whenever $a \ R \ b$, then $b \ R \ a$. It then follows that R is not symmetric if we have some a and b ∈ A with a R b, but bR/a. 

* asymmetric(不对称性): A relation R on a set $A$ is **asymmetric** if whenever $a \ R \ b$,then $b \ \not R \ a$. It then follows that $R$ is not asymmetric if we have some a and b ∈ A with both $a \ R \ b$ and $b \ R \ a$.

  

* antisymmetric(反对称性): A relation R on a set A is **antisymmetric** if whenever $a \ R \ b$ and $b \ R \ a$, then $a = b$. The contrapositive(逆否命題) of this definition is that $R$ is antisymmetric if whenever $a \ne b$, then $a \ \not R \ b$ and $b \ \not R \ a$. 

  * It follows that R is not antisymmetric if we have $a$ and $b$ in $A$, $a \ne b$, and both $a \ R \ b$ and $b \ R \ a$.

  

***

**Example:**



Let$A=\mathbb{Z}$, the set of integers, and let
$$
R=\{(a, b) \in A \times A \mid a<b\}
$$


so that $R$ is the relation less than. Is $R$ symmetric, asymmetric, or antisymmetric?

**Solution:**

* Symmetry: If $a<b$, then it is not true that $b<a$, so $R$ is not symmetric.
* Asymmetry: If $a<b$, then $b \nless a$ ($b$  is not less than  $a$), so $R$ is asymmetric.
* Antisymmetry: If $a \neq b$, then either $a \nless b$ or $b \nless a$, so that $R$ is antisymmetric.

## Relation Matrix

We now relate symmetric, asymmetric, and antisymmetric properties of a relation to properties of its matrix. 

***

The matrix $\mathbf{M}_R=\left[m_{i j}\right]$ of a <u>symmetric</u> relation satisfies the property that
$$
\text { if } \quad m_{i j}=1, \text { then } \ m_{j i}=1 .
$$
Moreover, if $m_{j i}=0$, then $m_{i j}=0$. 

Thus $\mathbf{M}_R$ is a matrix such that <u>each pair of entries, symmetrically placed about the main diagonal, are either both 0 or both 1</u> . 

It follows that $\mathbf{M}_R=\mathbf{M}_R^T$, so that $\mathbf{M}_R$ is a symmetric matrix.

对称性: 如果有关系, 则必定对称. 关系矩阵等于其Transpose.

***

The matrix $\mathbf{M}_R=\left[m_{i j}\right]$ of an <u>asymmetric</u> relation $R$ satisfies the property that
$$
\text { if } \  m_{i j}=1 \text {, then } \  m_{j i}=0 .
$$
If $R$ is asymmetric, it follows that $m_{i i}=0$ for all $i$; that is, the main diagonal of the matrix $\mathbf{M}_R$ consists entirely of 0's. This must be true since the asymmetric property implies that if $m_{i i}=1$, then $m_{i i}=0$, which is a contradiction.

不对称性: 不能有任何对称.

***

Finally, the matrix $\mathbf{M}_R=\left[m_{i j}\right]$ of an <u>antisymmetric</u> relation $R$ satisfies the property that if $i \neq j$, then $m_{i j}=0$ or $m_{j i}=0$.

反对称性: 对称的一定在对角线(但对角线不一定对称). 逆否命题: 不在对角线上的两个元素绝对不对称.

在对角线说明两个元素是同一个元素. 

## Digraph

If R is a:

***

asymmetric relation:

* The digraph of R cannot simultaneously have an edge from vertex i to vertex j and an edge from vertex j to vertex i. 

* This is true for any i and j, and in particular if i equals j. 

  Thus there can be no cycles of length 1, and all edges are “one-way streets.” 不能有自环. 所有边都是单向边.

***

antisymmetric relation:

* For different vertices i and j there cannot be an edge from vertex i to vertex j and an edge from vertex j to vertex i.
* When i = j, no condition is imposed. Thus there may be cycles of length 1, but again all edges are “one way.” 可能有自环, 但所有边依然是单向边.

***

symmetric relation: 

* If two vertices are connected by an edge, they must always be connected in both directions.
* 在这种情况下所有边都是双向边. 我们在画图时把边合为一条, 方向省略. 这样的图称作graph(无向图), 其中的边都是undirected edge(无向边).

> An undirected edge between a and b, in the graph of a symmetric relation R, corresponds to a set {a, b} such that (a, b) ∈ R and (b, a) ∈ R. Sometimes we will also refer to such a set {a, b} as an **undirected edge** of the relation R and call a and b **adjacent vertices**.



A symmetric relation R on a set A is called **connected**(联通的) if <u>there is a path from any element of A to any other element of A</u>. This simply means that the graph of R is all in one piece. In the below Figure we show the graphs of two symmetric relations. 

The graph in Figure (a) is connected, whereas that in Figure (b) is not connected.

![image-20230819005851667](/Users/lyk/Library/Application Support/typora-user-images/image-20230819005851667.png)

# Transitive Relations

* transitive(传递性): We say that a relation $R$ on a set $A$ is transitive if whenever $a \ R \ b$ and $b \ R \ c$, then $a \ R \ c$. 
  * A relation $R$ on $A$ is not transitive if there exist $a, b$, and $c$ in $A$ so that $a \ R \ b$ and $b \ R \ c$, but $a \ \not R \ c$. If such $a, b$, and $c$ do not exist, then $R$ is transitive.

* 传递性的另外两个等价表述: 

  * If $a \ R^2 \ c$, then $a \R \ c$; that is, $R^2 \subseteq R$ (as subsets of $A \times A$ ). 

  * if $a$ and $c$ are connected by a path of length 2 in $R$, then they must be connected by a path of length 1 .

# THEOREM1

A relation $R$ is transitive if and only if:

If there is a path of length greater than 1 from vertex $a$ to vertex $b$, there is a path of length 1 from $a$ to $b$ (that is, $a$ is related to $b$ ). Algebraically stated, $R$ is transitive if and only if $R^n \subseteq R$ for all $n \geq 1$.



# THEOREM2

It will be convenient to have a restatement of some of these relational properties in terms of $R$ relative sets. We list these statements without proof.

Let $R$ be a relation on a set $A$. Then

1. Reflexivity of $R$ means that $a \in R(a)$ for all $a$ in $A$.
2. Symmetry of $R$ means that $a \in R(b)$ if and only if $b \in R(a)$.
3. Transitivity of $R$ means that if $b \in R(a)$ and $c \in R(b)$, then $c \in R(a)$.


