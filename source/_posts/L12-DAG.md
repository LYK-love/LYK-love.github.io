---
title: L12 DAG
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-08-03 16:00:06
---


Outline ：

* **Directed Acyclic Graph**
  * **Topological order**
  * **Critical path analysis**
* **Strongly Connected Component（SCC）**
  * **Strongly connected component and condensation**
  * **The algorithm**
  * **Leader of string connected component**

<!--more-->

# Directed Acyclic Graph

## Topological order for G=(V,E)

* **Topological number**

  * An assignment of distinct integer $1,2,..., n$ to the vertices of $V$
  * For every $vw \in E$​, the topological number of *v* is less than that of *w*.

* **Reverse topological order**

  * Defined similarly

    ("greater than")

* 引理： 如果$G=（V，E ）$为有向无环图，则G中必然存在拓扑排序

### 拓扑排序算法

*   在某个集合$A$ 上的关系$R$如果是自反的、反对称的和传递的，那么$R$是一个**偏序**
* 偏序集的有向图中没有长度大于一的环
* 拓扑序要求**全序且无环**
* 如果有向图$G=(V,E)$有环，则 $G$不存在拓扑排序
* 如果有向图$G=(V,E)$无环，则 $G$必定存在拓扑排序



* “尽头”与DFS

  * DFS就是沿某条路径一直往下走，直到某个“**尽头**”节点。

  * 假设 $i \rarr j$ 表示任务$i$的执行依赖任务 $j$ 的完成，则尽头节点不依赖其他任何节点，因而对它的拓扑序号的分配从依赖关系的角度看是自由的。该分配方式不会影响其他节点的执行。 比如，对于逆拓扑序而言，只要分配当前尚未分配的最小序号。

* 逻辑尽头

  * 当一个节点的所有后续节点均已处理完毕时， 该节点就成为逻辑上的**尽头**节点。
    * 逆拓扑排序时, 逻辑尽头节点的逆拓扑序号只需要分配当前未分配序号中最小的
  * 分配拓扑序号的过程就成为不断找到逻辑结点的过程,这与DFS适合
  	* 在DFS-WRAPPER中,开始遍历之前定义一个全局变量`globalNum`, 并初始化为 `n+1`
  	* 在DFS框架的"遍历后处理"处,嵌入对拓扑排序的处理:
  		* `globalNum := `globalNum` -1;
  		* `v.topoNum` := `globalNum`;
  

  ```c++
  TOPO-WRAPPER(G)
  
  globalNum = n+1;
  Color all nodes WHITE;
  foreach node v in G do
  	if v.color = WHITE then
  		TOPO-ORDER(v);
  ```

  ```C++
  TOPO-ORDER(v)
  
  v.color = GRAY;
  foreach neighbour w of v do
  	if w.color = WHITE then
  		TOPO-ORDER(w);
  		
  		
  globalNUM := globalNum - 1;
  v.topoNum := globalNum;
  v.color = BLACK;
  ```

* 判断能否形成拓扑序，除了判断全序之外，就是判断有没有环。 而判断**成环等价于遍历过程中遇到了灰色节点**

## Critical path analysis

### Critical path  in a  Task Graph

* **Earliest start time**( *est* ) for a task *v*

  * If *v* has no dependencies, the *est* is 0

  * If *v* has dependencies, the *est* is the maximum of the **earliest finish time** of its dependencies.

* **Earliest finish time**( left ) for a task *v*

  * For any task: *eft = est + duration*

* **Critical path** in a project is a sequence of tasks: $v_0, v_1,\dots,v_k$, satisfying:

  * $v_0$ has no dependencies;
  * For any $v_i$ ( i = 1,2,...,k), $v_{i-1}$ is a dependency of $v_i$, such that *est* of $v_i$ equals *eft* of $v_{i-1}$;
  * *eft* of $v_k$​​ is maximum for all tasks in the project.

* 在DFS框架中嵌入相应处理

  * 在"遍历前处理"处, 初始化该节点的最早开始时间, 并初始化关键路径相关信息

  * 在结束邻接节点的处理返回的时候,检查是否要更新当前节点目前已知的最早开始时间.以及是否需要更新关键路径的相关信息

  * 在"遍历后处理"处, 当前节点的*est*已确定, 则可以计算出当前节点的*eft*

    

```C++
CRITICAL-PATH(v) //该算法同样需要WRAPPER来调度
				 //逻辑尽头的est和est在其逻辑的关键路径中最小

v.color := GRAY
c.est := 0; v.CritDep := -1;
foreach neighbour w of v do
	if w.color = WHITE then
		CRITICAL-PATH(w);
	if w.eft >= v.est then
			v.est = w.eft //求efs的最大值
			v.CritDep := w;
			
v.eft := v.est + v.l;
v.color := BLACK;
```



### Analysis

* Complexity
  * $\Theta(n+m)$

# Strongly Connected Component（SCC）

## Strongly connected component and condensation

* Strongly connected: 一个有向图中的节点是强连通的, 如果它们互相可达

* condensation Graph: 把G中的每个强连通片收缩成一个点, **强连通片之间**的边收缩成一条有向边,则得到G的收缩图$G\darr$

  * 两个强连通片之间只能是**单向**可达(或者不可达)

  * condensation Graph是**DAG**

## The algorithm

## Leader of strong connected component

```
SCC(G)

Initiate the empty stack nodeStack;

Perform DFS on G. In the postorder processing of each vertex v, insert the statement "nodeStack.push(v)"; //第一轮DFS,标记尽头,并通过栈完成排序

Compute the transpose grapg Gt of G;

Color all nodes WHITE;

while nodeStack != empty do
	v := nodeStack.pop();
	Conduct DFS from v on Gt;
```



* Def:

  For a DFS, the first vertex discovered in a strong component $S_i$​​ is called the **leader** of $S_i$​​, 记为$l_i$​

* 推论：

  The leader of $S_i$ is the last vertex to finish among all vertices of $S_i$ ( **since all of them in the same DFS tree** )( 即: 首节点的活动区间包含同一个强连通片中所有其他节点的活动区间 )

  

* 引理：

  1. Each DFS tree of a digraph G contains **only complete** strong components of G, one or more.(即: 不可能一个强连通片中的节点一部分在某棵遍历树中,一部分不在)

  2. $l_i$​在第一轮遍历中被发现时(刚刚被处理,即将被染成灰色时), 不可能有路径通向某个灰色节点

     * Proof:

       反证法: 设$S_i$的首节点$l_i$刚被发现时, 有一条路径通向某个灰色节点*x*. 由于$l_i$是首节点, 所以*x*必然处于图的另一个强连通片$S_j$中(而不可能在$S_i$中). 所以存在一条 $ S_i$到$S_j$的路径. 由于在$l_i$刚被发现时,节点*x*为灰色, 所以*x*为$l_i$在DFS Tree中的祖先节点. 于是存在一条 $ S_j$到$S_i$的路径,所以$ S_i$和$S_j$​是强连通的, 矛盾.

  3. *x*(若有的话), 比$l_i$​先结束遍历, 即: *x.finishTime < l.finishTime*

     * *x*只能为白色或黑色

  4. 在第二轮DFS中，当一个白色节点从栈中被POP出来时，它一定是其所在强连通片的首节点

     * Proof

       第二轮DFS时，一个出栈的节点$l$​为白色， 则它必然是其所在强连通片$S_i$​的第一个出栈节点（ 否则就会在$S_i$​​的其它先出栈的节点进行第二轮DFS时被染成灰色 ）。 而在第一轮DFS时，最后一个入栈的节点就是最后结束的节点。 而首节点$l_i$​的活动区间包含其他节点的活动区间， 因而必然是最后结束的节点。 所以$l$必然是$l_i$



