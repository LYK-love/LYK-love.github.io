---
title: L8 logn search
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2022-02-12 12:00:00
---


# Binary Search Generalized

Outline：

* Red-Black Tree

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# Balanced Binary Search Tree

## binary search tree

* Def
  * 2-Tree
  * 左子树的所有值比根节点小，右子树的所有值比根节点大（如果properly drawn的话，会很清楚 ）

## Red-Black Tree

* Def (基于二叉搜索树，附加一些性质)
  * If T is a **binary search tree** in which each node has a color, red or black, and  all external nodes are black, then T is a **red-black tree** if and only if:
    * [Color constraint] No red node has a red child
    * [Black height constraint] The **black length** of all external paths from a given node *u* is the same(the black height of *u*)
    * The root is black
  * **Almost**-red-black tree(ARB tree)
    * Root is red, satisfying the other constraints

### Recursive Definition of RBT

(a red black tree of black height  *h* is denoted as $RB_h$

* Def:
  * An external node is an $RB_0$​ tree, and the node is black.
  * A binary tree is an $ARB_h$( $h \ge 1$ )tree if:
    * Its root is red,and
    * Its left and right subtrees are each an $RB_{h-1}$ tree.
  * A binary tree is an $RB_h$ tree if:
    * Its root is black, and
    * Its left and right subtrees are each either an $RB_{h-1}$​ tree or an $ARB_{h}$​ tree.​

### Properties of Red-Black Tree

* The **black height** of any $RB_h$ tree or $ARB_h$ is well-defined and is *h*.
* Let *T* be an $RB_h$ tree, then:
  * *T* has at most $2^h-1$ internal black nodes.
  * *T* has at most $4^h-1$ in internal nodes.
  * The depth of any black node is at most twice its black depth.
* Let A be an $ARB_h$ tree, then:
  * *A* has at least $2^h-2$ internal black nodes.
  * *A* has at most $\frac{4^h}{2}-1$ internal nodes.
  * The depth of any black node is at most twice its black depth.

### Bound on Depth of Node in RBT

* Let *T* be a red-black tree with *n* internal nodes. Then no node has black depth greater than $log(n+1)$, which means that the height of *T* in the usual sense is at most $2log(n+1)$​.
  * Proof:
  * Let *h* be the black height of *T*. The number of internal nodes, *n*, is at least the number of internal black nodes, which is at least $2^h-1$​, so $h \le log(n+1)$​​. The node with greatest depth is some external node. All external nodes are with black depth *h*. So, the depth is at most $2h$​.

## Deletion

* Logical: 删除节点的内容
* Structural：删除节点，整棵树做修复

### Complexity of Operations on RBT

* With reasonable implementation
  * A new node can be inserted correctly in a red-black tree with *n* nodes in $\Theta(logn)$​ time in the worst-case
  * Repairs for deletion do $O(1)$ structural changes, but may do $O(logn)$color changes
