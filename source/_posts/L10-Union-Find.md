---
title: L10 Union Find
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-07-31 15:47:58
---


Outline:

* Dynamic Equivalence Relation
  * Examples
  * Definitions
  * Brute force implementations
* Disjoint Set
  * Straightforward Union-Find
  * Weight Union + Straightforward 
  * Weight Union + Path-compressing Find

<!--more-->

# Problems

## Minimum Spanning Tree

* Kruskal's algorithm, greedy strategy
  * Select one edge
    * With the minimum weight
    * Not in the tree
  * Evaluate this edge
    * This edge will **NOT** result in a cycle
* Critical issue
  * How to know "**NO CYCLE**"?

## Maze Generation

## Black Pixels

## Jigsaw Puzzle

# Dynamic Equivalence Relation

* Equivalence
  *  等价关系( 自反对称传递 )
  * 等价类们形成了一个划分( **partition** )
* Dynamic equivalence relation
  * Changing in the process of computation
  * **IS** instruction: *yes* or *no* ( in the same equivalence class )
  * **MAKE** instruction: combining 2 equivalent classes, by relating 2 unrelated elements, and influencing the results of subsequent **IS** instructions.
  * Starting as equality relation

## Union-Find based Implementation

* Maze Generation
  * Randomly delete a wall and **union** 2 cells
  * Loop until you **find** the inlet and outlet are in one equivalent class
* The Kruskal's algorithm
  * **Find** whether u and v are  in the same equivalent class
  * If not, add the edge and **union** the 2 nodes
* Black Pixels
  * **Find** black pixel groups
  * How the **union** of black groups increases $\alpha$

## Implementation： Choices

n: 总元素个数， 

m： Find / Union 指令数



* Matrix( relation matrix )
  * Space in $\Theta(n^2)$,  and worst-case cost in $O(mn)$​ (mainly for row copying for MAKE)( m 条指令，最坏情况下每条$O(n)$的代价 )
* Array( for equivalence class ID )
  * Space in $\Theta(n)$​, and worst-case cost in $O(mn)$​ (mainly for search and change for MAKE )
* Forest of rooted trees
  * A collection of disjoint sets, supporting *Union* and *Find* operations
  * Not necessary to traverse all the elements in one set

## Union-Find ADT

### Using Rooted Tree

* **IS** $s_i \equiv s_j$:
  * $t = find(s_i)$
  * $u = find(s_j)$
  * $(t == u)$​ ?
* **MAKE** $s_i \equiv s_j$ :
  * $t=find(s_i)$
  * $u = find(s_j)$
  * $union(t,u)$

* Critical operation： 对rooted tree 的 assignment 和 lookup，  均称做 `link  operation`



### Worst-case Analysis

* Assuming each link operation takes $O(1)$
* 在根树极度不均衡时(变成一个链表), operations done: *n*( `makeSet`,  把每个元素实现为一个等价类),  *n-1*( *Union次数*) + *(m-n+1)n*(  共有m条指令,去掉*n-1*条,剩下的全部是*Find*,且查最深的那个), 因此是$\Theta(mn)$​
* 和蛮力策略代价一样,这是因为并查操作都太简单了,没有特殊约束.

### Weight Union

* Weight union( *wUnion* )
  * always have the tree with *fewer nodes* as subtree
* 解决树的平衡性问题,为什么不用*height*, 而要用*size*?
  * 其实也有用*height*的优化*Union*方案,这里没教
  * 由于在用*size*的方案中, "size小而height大"这种反例不可能出现,所以size方案是可行的

#### Worst case Analysis

*  任意次*wUnion*后, n个节点的根树的高度上界是 $\lfloor logn \rfloor$​
  * 证明用归纳法
* A  Union-Find program of size *m*, on a set of *n* elements, performs  $\Theta(m + n\lfloor logn \rfloor)$​​  link operations in the worst case if *wUnion* and *straight find* are used
* Proof:
  * At most *n-1* *wUnion* can be done, building a tree with height at most $\lfloor logn \rfloor$
  * Then, each *find* costs at most $\lfloor logn \rfloor + 1$
  * Each *wUnion* costs in $O(1)$, so, the upper bound on the cost of any combination of *m wUnion/find* operations is the cost of *m find* operations, that is $m(\lfloor logn \rfloor + 1) \in O(n+ m\lfloor logn \rfloor)$

### Path Compression Find

* *cFind* does **twice as many** link operations as the *find* does for a given node in a given tree(先查一遍查到根,再查一遍,把遇到的节点都挂到根下面)

####  Worst case Analysis

*  用平摊分析, *cFind*是昂贵操作
* (使用*wUnion*和*cFind*)代价是$O((n+m)log^*(n))$​
  * $log^*n$的反函数是n个2叠罗汉,后者增长很快,因此前者增长很慢, 可以近似看作常数
    * Log-star grows extremely slowly $\lim\limits _{n \rarr \infty} { \frac {log^* n} {log ^{(p)} n}}$, *p* is any nonnegative constant​​

*  平摊分析的细节不讲了
