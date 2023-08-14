---
title: Trees
tags: Discrete Mathematics
categories: Algorithm
mathjax: true
date: 2023-08-14 00:05:36
---

A special type of relation called "tree" in Discrete Mathematics.

Ref: *Discrete Mathematical Structures*, Sixth Edition, Bernard Kolman, Robert C. Busby, Sharon Cutler Ross.

<!--more-->

# Definition

Let $A$ be a set, and let $T$ be a **relation** on $A$. We say that $T$ is a **tree** if there is a vertex $v_0$ in $A$ with the property that there **exists a <u>unique</u> path in $T$ from $v_0$ to every other vertex in $A$, but no path from $v_0$ to $v_0$.**

**(Tree是一种relation!)**

We show below that the vertex $v_0$ , described in the definition of a tree, is unique. It is often called the **root** of the tree $T$ , and T is then referred to as a **rooted tree**. We write $(T, v_0)$ to denote a rooted tree $T$ with root $v0$.

If $(T, v0)$ is a rooted tree on the set $A$, an element $v$ of $A$ will often be referred to as a **vertex in** $T$. This terminology simplifies the discussion, since it often happens that the underlying set $A$ of $T$ is of no importance.

## Properties

Let $(T, v_0)$ be a rooted tree. Then:

1. There are no cycles in $T$. 

   这意味着tree是Directed Acylic Graph(DAG, 有向无环图)的真子集. 因為有向無環圖中從一個點到另一個點有可能存在兩種路線, 因此有向無環圖未必能轉化成樹, 但任何有向樹均為有向無環圖.

2. $v_0$ is the only root of $T$.

3. Each vertex in $T$, other than $v_0$, has in-degree one, and $v_0$ has in-degree.

## Proof

*There are no cycles in $T$.* 



Suppose that there is a cycle  $q$  in  $T$ , beginning and ending at vertex  $v$ . By definition of a tree, we know that  $v \neq v_{0}$ , and there must be a path  $p$  from  $v_{0}$  to $v$ . Then  $q \circ p$  is a path from  $v_{0}$  to  $v$  that is different from  $p$ , and this contradicts the definition of a tree.

翻译: 如果有一条环$q$, 假设其起点和终点为$v$, 根据树的定义"no path from $v_0$ to $v_0$", 则 $v \neq v_{0}$ . 

又根据定义, 存在边$p$从v0出发到达$v$, 则  $q \circ p$ 也是一条从$v_0$到$p$的路径, 并且它不等于$p$. 这意味着从$v_0$到达$w_1$的路径不唯一, 与树的定义冲突.

***

*$v_0$ is the only root of $T$.*



If $ v_{0}^{\prime}$  is another root of  T , there is a path  p  from $ v_{0}$  to  $v_{0}^{\prime}$  and a path $q$  from  $v_{0}^{\prime}$  to  $v_{0}$  (since $ v_{0}^{\prime}$  is a root). Then  $q \circ p$  is a cycle from $ v_{0}$ to $ v_{0}$ , and this is impossible by definition. Hence the vertex  $v_{0}$  is the unique root.

***

*Each vertex in $T$, other than $v_0$, has in-degree one, and $v_0$ has in-degree.*



Let  $w_{1}$  be a vertex in  $T$  other than  $v_{0}$ . Then there is a unique path  $v_{0}, \ldots, v_{k}, w_{1}$  from  $v_{0}$  to $ w_{1}$  in $T$. This means that  $\left(v_{k}, w_{1}\right) \in T$ , so  $w_{1}$  <u>has in-degree at least one.</u> 

翻译: 假设 $w_{1}$  是不同于 $v_{0}$ 的点, 那么必定存在一条唯一的, 从$v_0$到$w_1$的路径 $v_{0}, \ldots, v_{k}, w_{1}$ . 因此有边$\left(v_{k}, w_{1}\right) \in T$ , 因此 $w_{1}$  <u>has in-degree at least one.</u> 



If the in-degree of  $w_{1}$  is more than one, there must be distinct vertices  $w_{2}$ and  $w_{3}$  such that  $\left(w_{2}, w_{1}\right) $ and $ \left(w_{3}, w_{1}\right)$  are both in  $T$ . If  $w_{2} \neq v_{0}$  and $ w_{3} \neq v_{0}$ , there are paths  $p_{2}$  from  $v_{0} $ to  $w_{2}$  and  $p_{3}$  from  $v_{0}$  to  $w_{3}$ , by definition. Then  $\left(w_{2}, w_{1}\right) \circ p_{2}$  and $ \left(w_{3}, w_{1}\right) \circ p_{3}$  are two different paths from  $v_{0}$  to  $w_{1}$ , and this contradicts the definition of a tree with root  $v_{0}$ . 

翻译: 假设$w_{1}$的in-degree大于1, 则必定有两个点$w_2, w3$使得  $\left(w_{2}, w_{1}\right) $ and $ \left(w_{3}, w_{1}\right)$  在该树中. 由于树只能有一个root $v_0$, 所以:

1. 如果$w_2$, $w3$均不为$v_0$, 则根据树的定义, 分别存在从$v_0$出发到达$w_2, w_3$的路径$p2$, $p3$. 那么就存在两条路径到达w_1, 分别为: $p2 \to(w_2, w_1)$ 和 $p3 \to (w3, w_1)$ . $p2$, $p3$都是从$v_0$出发的, 这意味着从$v_0$到达$w_1$的路径不唯一, 与树的定义冲突.
2. 如果Rw_2, w_3R中有一个是$v_0$, 假设$w_2$为$v_0$. 则存在两条路径到达$w_{1}$: $ (v0, w_1)$ 和 $p3 \to (w3, w_1)$. 同上, 与树的定义冲突.



Hence, <u>the in-degree of  $w_{1}$  is one</u>. We leave it as an exercise to complete the proof if  $w_{2}=v_{0}$  or  $w_{3}=v_{0}$  and to show that $ v_{0}$  has in-degree zero.

# Terminology

Ref: [Binary Trees by Nick Parlante](http://cslibrary.stanford.edu/110/BinaryTrees.html#:~:text=A%20binary%20tree%20is%20made,%22subtrees%22%20on%20either%20side.)

* **Root:** The root of a tree has no parent.
* **Parent:** A node with a child or children.
* **Child:** A node extended from another node (parent node).
* **Leaf:** A node without a child.
* Define **depth()** of node `A` in a tree rooted at  `X` to be length of path from `X` to `A`.
* Define **height()** of node `A` to be max depth of any node in the subtree rooted at `X`

# Kinds of Tree

## Binary Tree

A **binary tree** is either empty (represented by a null pointer), or is made of a single node, where the left and right pointers (recursive definition ahead) each point to a **binary tree**.

## Binary Search Tree

A **"binary search tree" (BST)** or "ordered binary tree" is a type of binary tree where the nodes are arranged in order: <u>for each node, all elements in its left subtree are less-or-equal to the node (<=), and all the elements in its right subtree are greater than the node (>).</u>

