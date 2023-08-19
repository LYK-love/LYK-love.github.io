---
title: L11 Graph Traversal
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-08-03 10:03:57
---


Outline：

* **General DFS/BFS Skeleton**
* **Depth-First Search Trace**

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# General DFS/BFS Skeleton

* 在遍历过程中,节点会经历三种状态:

  * 白色: 节点尚未被遍历到

  * 灰色: 节点已经被遍历到,但对于它的遍历尚未结束

  * 黑色: 节点自身的遍历已经结束

```C++
dfs-wrapper( 用于不连通图,可以遍历所有连通片 )
for each v in G
	if v.color = WHITE://全部染成白色
			dfs(G,v);
		


dfs(G, v)
	Mark v as "discovered" //v被染成灰色
	<Preorder processing of v>
	For each vertex w that edge vw is in G:
		If w is “undiscovered”:
			<Exploratory peocessing of edge vw>
			dfs(G, w)
			<Backtrack processing of edge vw>
		Otherwise:
			"Check" vw without visiting w.
	<Postorder processing of v>
	Mark v as "finished" //v被染成黑色
```

```C++
bfs(G,s)
 Mark s as "discovered";
 enqueue(pending, s);
 
 while(pending is nonempty)
 	dequeue(pending, v);
 	For each vertex w that edge vw is in G:
 		If w is "undiscovered"
 			Mark w as "discovered" and enqueue(pending, w)
	Mark v as "finished"
```

* 图遍历算法的复杂度都是$\Theta（m+n）$​ (m为边数，n是顶点数),称为“线性时间”

# Depth-First Search Trace

DFS将边分为四种类型（四种染色）

* **T.E**: tree edge d 当检查$u$的所有邻居时， 如果发现一个白色邻居节点$v$并对$v$ 递归地DFS,此时将边$uv$标记为TE. 
  * 在图的某个连通片内部进行遍历时，所有TE组成的子图是连通的\无环的，且包含该连通篇中所有的点。
  * 如果忽略所有边的方向，则这些TE组成当前连通片的一棵生成树，称之为“ DFS树”。
  *  如果以开始遍历的点为根，则从根结点指向所有叶节点的方向，就是遍历过程推进的方向，根据这一方向可以为TE的两个节点定义父子关系，父子关系传递形成祖先、后继关系（ 父子关系 == 直接的祖先 \ 后继关系 ）
* **B.E**: back edge 当节点$u$的邻居 $v$  在前面的遍历过程中已经被访问到， 并且$v$ 是 $u$ 的祖先节点
* **D.E**: descendant edge 当节点$u$的邻居 $v$  在前面的遍历过程中已经被访问到， 并且$v$ 是 $u$ 的后继节点
* **C.E**: cross edge 以上三点都不是。 即$u$的邻居$v$不是白色节点，且二者无祖先或后继关系

## Time Relation on Changing Color(DFS)

* Keeping the order in which vertices are encountered for the first or last time

  * A global integer time: 离散计数器, 初始值为$0$, 每次节点变色加一,最终值为$2n$

  * Array *discoverTime*: the $i^{th}$​​ element records the vertex $v_i$ turns into gray

  * Array *finishTime*: the $i^{th}$ element records the vertex $v_i$​​ turns into black

  * The active interval for vertex $v$, denoted as ***active(v)***, is the duration while $v$ is gray, that is:

    **active($v$​) = [ discoverTime, finishTime ]**

  


### Properties of Active Intervals

* **定理4.1**
  * $w$ 是 $v$在DFS树中的后继节点, 当且仅当active($w$)$\subset$active($v$​). 若$w \neq v$, 则此处的包含为真包含
  * $w$​​ 和 $v$​​没有祖先后继关系,当且仅当active($w$​​)和active($v$​​​)互不包含
  
    If $v$ and $w$ have no ancestor/descendent relationship in the DFS forest, then their **active intervals** are disjoint.
  * **If $vw \in E_G$, then**
    * $vw$ is a **cross edge** iff. *active(w)* entirely precedes *active(v)*.
      * $w$只能是黑色或灰色。 如果是黑色，其结束时间一定早于$v$的开始时间，证毕。 如果是灰色，因为是CE，因此二者无祖先后继关系，因此二者活动区间互不包含，$w$ 先被遍历，因此 $w$的活动区间在$v$之前 ？？
    * $vw$ is a **descendant edge** iff. there is some third vertex $x$, such that $active(w) \subset active(x) \subset active(v)$.
    * $vw$ is a **tree edge** iff. $active(w) \subset active(v)$, and there is no third vertex x, such that *$vw$* is a **descendant edge** iff. there is some third vertex *x*, such that $active(w) \subset active(x) \subset active(v)$.
    * $vw$ is **back edge** $active(v)  \subset active(w)$.

### Ancestor and Descendant

* **[White Path Theorem]** $w$ is a descendant of $v$ in a DFS tree iff. at the time $v$ is discovered( just to be changing color into gray), there is a path in $G$ from $v$ to $w$ entirely of white vertices.

  证明:

  充分性: 如果节点 $v$是$w$的祖先,则考察从$v$到$w$的TE组成的路径, 在$v$​刚刚被发现的时刻, 该路径是一条白色路径.

  必要性: 已知节点$v$​到$w$​存在白色路径. 采用归纳法证明, 对白色路径长度$k$​做归纳. 初始情况, $k=0$​, 显然成立. 假设对于所有长度小于$k$​的白色路径结论成立. 下面考虑长度为$k$​的白色路径$P=v \rarr x_1 \rarr \dots \rarr x_i \dots \rarr w$​. 随着遍历的推进,假设节点$x_i$​是$P$​上第一个被遍历过程发现的节点, 基于节点$x_i$​, 将$P$​分为两小段: $P_1=v \rarr \dots \rarr x_i$​, $P_2=x_i \rarr \dots \rarr w$​. 由于$P_2$​是长度小于$k$​的白色路径, 所以$x_i$​是$w$​在遍历树中的祖先. 由定理4.1, 易知$v$​是$x_i$​在遍历树中的祖先, 则$v$​是$w$​在遍历树中的祖先
