---
title: L14 MST
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-08-10 16:16:04
---


Outline:

* Optimization Problem
* Greedy Strategy

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# Greedy Strategy for Optimization Problems

* Coin change Problem
  * [candidates] a finite set of coins, of 1,5,10 and 25 units, with enough number for each value
  * [constraints] Pay an exact amount by a selected set of coins
  * [optimization] a smallest possible number of coins in the selected set
* Solution by Greedy Strategy
* For each selection. choose the highest-valued coin as possible.

## Greedy Fails Sometimes

We have to pay 15 in total

* If the available types of coins are {1,5,12}
  * The greedy choice is {12,1,1,1}
  * But the smallest coins is {5,5,5}
* If the available types of coins are {1,5,10,25}
  * The greedy choice is always correct

## Greedy Strategy

* Expanding the partial solution **step by step**
* In each step, a selection is made from a  set of candidates. The choice made must be:
  * [**Feasible**] it has to satisfy the problem's constraints
  * [**Locally optimal**] it has to be the best local choice among all feasible choices on the step
  * [**Irrevocable**] the choice can't be revoked in subsequent steps

```
set greedy( set candidate )
	set  S =  空集；
	while not solution(S) and candidate =  空集
		select locally  optimizing x from candidate;
		candidate = candidate - {x};
		if feasible(x) then S = S ∪ {x};
	if solution(S) then return S
		else return("no solution")
```

# Undirected Weighted Graph and MST

求无向有权图G的最小生成树（默认G是连通图，对于非连通图，分别求连通片的MST即可）

* 图G的**生成树**T是其子图，满足
  1. T包含图G的所有顶点（即恰好有n-1条边）
  2. T是连通无环图，即一棵树
*  若T是图G的生成树， 且图中不存在其他比T的权小的生成树， 则称T为G的**最小生成树**

## Greedy Algorithms for MST

* Prim's algorithm
  * Difficult selecting: "best local optimization means **no cycle and small weight under limitation**"
  * Easy checking: doing nothing
* Kruskal's algorithm:
  * Easy selecting: smallest in primitive meaning
  * Difficult checking: **no cycle**

# Prim's algorithm

选顶点

## Correctness

* 归纳法

## MST Property

* A spanning tree *T* of a connected, weighted graph has MST property if and only if for any non-tree edge *uv*, $T \or {uv}$​​ contains a cycle in which *uv* is **one of** the maximum-weight edge.(  生成树再加一条边（这样一定会成环）*uv*时， *uv* 一定大于等于生成树中的所有边)
* **All the spanning trees having MST property have the same weight.**
  * Proof： 归纳法



* In a connected, weighted graph $G = (V,E, W)$, a  tree *T* is a minimum, spanning tree if and only if *T* has the MST property.

  *  Proof: 略

* Prim算法总能够得到图G的最小生成树

  * Proof： 暂时没看懂
## 实现

  Main Procedure:
```
primMST(G, n)
	initialize the priority pq as empty;
	Select vertex s to start the tree;
    Set its candidate edge to ( -1, s, 0 );
    insert(pq, s, 0 );
    while( pq is not empty )
    	v= getMin(pq); deleteMin(pq);
    	add the candidate edge of v to the tree;
    	updateFringe( pq, G, v );
    return;
```



Updating the Queue

```
updateFringe( pq, G, v )
	for all vertices w adjcent to v // 2m loops
		newWgt = w(v,w);
		if w.status is unseen then
			Set its candidate edge to (v, b, newWgt );
			insert( pq, w, newWgt )
		else
			if newWgt < getPriority(pq, w)
			Revise its candidate edge to (v, w, newWgt )
			decreaseKey( pq, w, newWgt )
```

## Complexity

* Operations on ADT priority queue:( for a graph with n vertices and m edges )

  * insert: n;
  * getMin: n
  * deleteMin: n
  * decreaseKey: m( appears in *2m* loops, but execute at most *m*  )

* So,( 抽象化代价 )
  $$
  T(n,m) = O(nT(getMin)+nT(deleteMin+insert)+mT(decreaseKey)
  $$

* Implementing priority queue using array. we can get $\Theta(n^2 + m)$

# Kruskal's algorithm

选边

## Correctness

归纳法

## 实现

判断加入一条边*uv*后是否成环，即判断*uv*两点是否连通，用**并查集**

```
kruskalMST( G, n, F )//outline
	int count;
	Build a minimizing priority queue pq, of edges of G, prioritized by weight.
	Initilize a Nuion-Find structure, sets , in which each vertex of S is in its own set.
	
	F = 空集；
	 while( isEmpty(pq) == false )
	 	vwEdge = getMin(pq); deleteMin(pq);
	 	int vSet = find(sets, vwEdge.from);
	 	int wSet = find(sets, vwEdge.to);
	 	if( vSet != wSet )
	 		Add vwEdge to F;
	 		union( sets, vSet, wSet )
	 return
```

## Complexity

* $\Theta(mlogm)$   (并查集代价忽略不计)

