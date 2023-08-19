---
title: L13 Undirected Graph
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-08-23 12:01:35
---


Outline:

* **UAG的DFS树**

* **UAG的DFS框架**

* **UAG的DFS应用**

  * **容错连通**

    * **寻找割点**

    * **寻找桥**

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# UAG的DFS树

UAG的遍历的主要差别就在于剔除二次遍历

* TE：当发现一个白色节点并递归地进行遍历时， 就将其连接的边标记为TE。 遍历过程中的TE组成遍历树， 这与DAG是类似的。 对于原本无向的边， 遍历过程为它做了定向( orientation ), 即遍历推进的方向。

* BE： 当遍历节点$u$并发现一条边指向灰色节点$v$时, 此时有两种本质不同的情况:

  若$vu$是TE, 则这是一次二次遍历,因而标识并剔除这一类型的遍历.

  若$v$是$u$的某个不是父节点的祖先节点, 则将$uv$标记为BE

* DE: 当遍历节点$u$​时, 发现一条边指向节点$v$​​时, 且$v$​是$u$​​在遍历树中的后继节点, 此时边$uv$为DE, 但这次遍历必然是二次遍历,应该被剔除. 这是因为根据DE的定义, 此时$v$不能是白色( 否则$uv$是TE ), 不能是灰色(可能是二次遍历的BE ), 因而只能是黑色, 即$v$已经结束了遍历, 它结束遍历前必然已经完成了边$vu$的遍历, 且根据$u$,$v$间的祖先后继关系, 边$vu$首次被遍历时标记为BE(可能是二次遍历的BE).

* CE: 不存在. 因为当遍历节点$u$时,发现一条边指向节点$v$. 根据CE的定义, $u$, $v$间没有祖先后继关系,所以与上面分析类似, 节点$v$只能是黑色, 它已经完成了遍历. 所以点$v$在结束遍历前必然已经访问过边$vu$. 当从$v$出发遍历$vu$时, $u$尚未被遍历, 为白色. 所以$vu$为TE, 这和$u$, $v$间没有祖先后继关系相矛盾.

# UAG的DFS框架

对于TE的处理于DAG一致, 此外还要处理BE的情况. 根据对BE的讨论,我们必须去除指向父结点的BE. 为此, 我们记录了每个节点的父节点.

算法框架直接将上述两种情况外的其他情况忽略, 因为其他情况都是二次遍历, <u>不需要处理</u>. 一个邻居节点只可能有3种情况:

* 白色: 即TE
* 灰色:
  * 灰色且不是父结点: 需要额外处理
  * 灰色且是父结点: 二次遍历
* 黑色:
  * DE: 二次遍历
  * CE: 二次遍历



```c++
DFS_UG(v, parent):


v.color := GRAY;
<Preorder processing of node v>;
foreach neighbour w of v do
	if w.color = WHITE then
		<Exploratory processing of TE vw>;
		DFS_UG(w,v);
		<Backtrack processing for TE vw>;
	else
		if w.color = GRAY and w != parent then
			<Check BE vw>;
<Postorder processing of node v>;
v.color := BLack;
```



# UAG的DFS应用

## 容错连通

* **定义4.7** 对于连通的无向图$G$, 如果其中任意去掉$k-1$个点, 图$G$仍然连通, 则称图$G$是$k$-点连通的. 类似的, 如果图中任意去掉$k-1$条边, 图$G$仍然连通, 则称图$G$是$k$-边连通的.

已知,当$k=1$时, $k$​-连通就退化为传统的无环连通. 另外, 我们更关注$k=2$​​的 特殊情况, 即去掉某个点或某条边后,剩下的图不再连通. 由此引入割点( articulation point )和桥( bridge )的概念.

* **定义4.8** 对于连通的无向图$G$​, 称节点$v$​为割点, 如果去掉点$v$​后, 图$G$​不再连通; 称边$uv$​为桥, 如果去掉边$uv$​后, 图$G$​​不再连通.

### 寻找割点

Brute Force: 遍历每个顶点, 检查剩下的图是否连通, 代价为$O(n(m+n))$, 这一方法源于割点的定义. 为了将代价改进到线性时间, 需要将割点的定义做等价变换.以支持更高效的找割点的算法.

割点的定义依赖一个**全局**的性质( 整个图是否连通 ), 这一性质难以高效地进行检测. 为此我们首先将割点的定义等价地变化为一个**局部**的性质, 利用部分节点之间的关系来完成割点的检测.



* **引理4.7** ( 割点基于路径的定义 )	节点$v$为割点, 当且仅当存在节点对$w$和$x$满足节点$v$出现在$w$到$x$的每一条路径上.

  证明略.

* **引理4.8** ( 割点基于DFS的定义 )	假设在一次DFS中, 节点$v$不是遍历树的根节点. 则节点$v$​为割点, 当且仅当在遍历树中, 存在节点$v$的某棵子树, 没有任何BE指向$v$的祖先节点.

  证明:

  必要性:	易证若节点$v$​的某棵子树,没有任何BE指向$v$​​的祖先节点, 则删掉$v$​后, 该子树将于图的其他部分断连, 所以$v$​是割点.

  充分性: 假设节点$v$为割点, 则根据引理4.7, 存在不同于$v$的两个节点$x$和$y$满足$v$出现在$x$到$y$的每一条路径上. 首先我们发现节点$x$和$y$中至少有一个是节点$v$在遍历树中的后继节点( 可通过反证法证明.  ). 所以必有某个点在遍历树中的后继节点, 而$v$必然不是叶节点. 同样可用反证法证明, 若$v$的任意子树均有BE指向$v$的祖先节点, 此时无论$x$和$y$哪一个是$v$的后继节点( 或者都是 ), 均可构造一条从$x$到$y$的不经过$v$的路径, 这和$v$出现在$x$到$y$的每一条路径上相矛盾.

  证毕.



* 根据引理4.8, 可以用算法操作来发现割点: 为每个节点维护一个变量`back`来判定它是否为割点:

  * 当$v$首次被发现时:
    $$
    v.back = v.discoverTime
    $$

  * 遍历过程中遇到一条从节点$v$指向节点$w$的BE:
    $$
    v.back=min\{v.back, w.discoverTime\}
    $$

  * 遍历节点$w$结束, 从$w$回退到$v$时:
    $$
    v.back=min\{v.back,w.back\}
    $$

  

  注意, $v.back$初始值为$v.discoverTime$, 且$v.back$的值只会减少. 其减少有两种情况:

  * 遍历过程遇到一条BE, 记为边$vw$. 处理完BE并回退时, $v.back$被减少为$w.discoverTime$. 由于BE指向的节点$w$是祖先节点, 所以$w.discoverTime$更小,这一更新使得$v.back$​的值减少.
  * 处理完TE$vw$回退时, 如果节点$w$​的`back`值有更新( 只可能减少 ), 这一更新随着回退被传递到回退的节点.



* 当从TE $vw$回退时, 如果$w.back \geq v.discoverTime$, 则节点$v$​​是割点.

  * **定理4.5**	ARTICULATION-POINT-DFS算法是正确的.

    证明:

    根据引理4.8, 要证明算法正确性, 只需证明当从TE $vw$回退时, 如果$w.back \geq v.discoverTime$, 则以$w$为根的某棵子树没有任何BE指向$v$的祖先节点. 根据`back`值的更新方法, 如果以$w$为根的某棵子树存在BE指向$v$的祖先, 则$v$的祖先的$discoverTime$会被赋值给$w$为根的子树中某个节点的`back`值, 	且随着遍历的回退过程, 这一$discoverTime$会以`back`遍历的方式传递给$w.back$. 由于祖先节点具有更小的$discoverTime$, 所以如果这样的一条BE存在, 则$w.back$一定小于$v.discoverTime$, 反之则说明这样的BE不存在.

  ```c++
  ARTICULATION-POINT-DFS(v):
  
  v.color := GRAY;
  time := time + 1;
  v.discoverTime := time;
  v.back := discoverTime;
  foreach neighbour w of v do
      if w.color = WHITE then
          w.back	:=  ARTICULATION-POINT-DFS(w);
  		if w.back >= v.discoverTime then
              Output v as an articulation point;
  		v.back = {v.back, w.back};
  	else
          if vw is BE then
              v.back = min{ v.back, w.discoverTime };
  return back;
  
  ```

  

### 寻找桥

基于UAG的DFS中,只会出现TE和BE, 对于BE, 删去它后图依然是连通的( 易证 ), 因此只需关注TE.

* **引理4.9** ( 桥基于DFS的定义 )	给定遍历树中的TE $uv$ ( $u$是$v$的父结点 ), $uv$是桥 当且仅当在以$v$为根的所有遍历树的子树中, 没有BE指向$v$​​的祖先节点( 不包括$v$, 包括$u$).

* $v.back$维护方式为:

  * 当$v$首次被发现时:
    $$
    v.back = v.discoverTime
    $$

  * 当遍历BE $vw$时, 
    $$
    v.back = min\{v.back,w.back\}
    $$
    
  * 当遍历节点$w$结束, 回退到$v$时, $v.back = min{v.back,w.back}$
  
* **定理4.6**	BRIDGE-DFS算法是正确的.

  证明略

```C++
BRIDGE-DFS(u):

v.color := GRAY;
time := time + 1;
v.discoverTime := time;
v.back := discoverTime;
foreach neighbour w of v do
    if w.color = WHITE then
    	v.back := min{ u.back, v.back };
    	if v.back > u.discoverTime then
    		Output uv as a bridge;
	else
		if uv is BE then
			u.back := min{u.back, v.discoverTime};

```

