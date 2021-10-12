---
title: Introduction to AI:Lecture2&3 Search
tags: Introduction to Artificial Intelligence
categories: Artificial Intelligence
---

# Search

* 推箱子问题，将地图变化到目标状态
* 采用Goal-based agents

## Tree Search

 用搜索树来存储搜索过程中的信息，搜索过程在Agent的脑中进行，不会影响外部environment

* 根节点： 地图初始状态
* （中间）节点：搜索过程中的地图状态（想象出来的，实际上地图不会改变）
* 叶节点：地图的目标状态

```C++
function TREE-SEARCH(problem , strategy) returns a solution, or failure

	initialize the  search tree using the initial state of problem 把地图的初始状态作为根节点

	loop do
		if there are no candidates for expansion then return failure
		choose a leaf node for expansion according to strategy
		if the node contains a goal state then return the corresponding solution
		else expand the node and add the resulting nodes to the search tree
	end
```

BFS: 空间复杂度高， 速度快

DFS: 空间复杂度低，速度慢
