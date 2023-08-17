---
title: T4 BFS and DFS
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-08-23 09:51:20
---


Outline:

* BFS

  * skeleton
  
  * 证明: $v.dis = \delta(s,v)$
  
  * BFS树
  * 应用
  
* DFS

  * s → all

  
  
  <!--more -->

# BFS

## skeleton

* BFS-WRAPPER(G)

  ```c++
  foreach node v in G do
  	v.color := WHITE; v.parent := null; v.dis := +∞;
  foreach node v in G do
      if v.color = WHITE then
          BFS(v);
  ```

  

* BFS(G)

  ```c++
  Initialize an empty queue queNode;
  v.color := GRAY;
  v.dis := 0;
  queNode.ENQUE(v);
  while queNode != empty do
      w := queNode.DEQUE();
  	foreach neighbor x of w do:
  		if x.color := WHITE then
              x.color := GRAY;
  			x.parent := w;
  			x.dis := w.dis + 1;
  			queNode.ENQUE(x);
  	<processing of node w>;
  	w.color := BLACK;
  ```


## 证明: $v.dis = \delta(s,v)$

**变量$v.dis$​记录了源点$s$​到节点$v$​最短路径的长度**,对所有节点依据$dis$ 进行了等价类划分

记源点$s$到节点$v$的最短路径长度为$\delta(s,v)$,.现在证明$v.dis = \delta(s,v)$：



  * **引理5.1** 对于有向或无向图$G$, 对任意边$uv$​, 有$\delta(s,v) \leq \delta(s,u)+1$​​.

    证明: 

    如果源点$s$到$u$可达, 则由于$uv$的存在, $s$到$v$同样可达. 所以$s$到$v$最短路径长度必然不超过任意一条$s$到$v$的路径长度(包括$s$到$u$再到$v$这条路径), 所以$\delta(s,v) \leq \delta(s,u)+1$.  若$s$到$u$不可达, 则$\delta(s,u)=\infty$, 不等式同样成立（当然，若$s$到$v$也不可达，此时是 $\infty \leq \infty  + 1$，同样成立）.

    

  * **引理5.2** 从节点$s$​开始BFS, 在遍历结束时, 对每个可达结点$v$​, 有 $v.dis \geq \delta(s,v)$​​.

    证明:

    采用数学归纳法,对队列上的操作个数归纳, 即证明: 无论队列上执行了多少个操作,  该不变式总是成立: 对于任意$v$, $v.dis \geq \delta(s,v)$.

    初始情况是队列执行第一个操作, 即将源点$s$放入队列中. 此时$s.dis \geq \delta(s,s)=0$. 对于其他任意节点$v$, $v.dis = +\infty \geq \delta(s,v)$. 所以初始情况下结论成立.

    由于出队操作对结论没有影响( 出队不会更改 $v.dis$), 只需要关注入队操作. 假设在处理节点$u$时, 发现白色邻居$v$. 根据归纳假设, 有$u.dis \geq \delta(s,u)$. 对于$v$, 有:
    $$
    \begin{equation}
    \begin{aligned}
    v.dis = u.dis + 1( BFS的实现 ) \\
    
    \quad \quad  \geq \delta(s,u)+1 ( 归纳假设 ) \\
    
    \geq \delta(s,v) ( 引理5.1 )
    \end{aligned}
    \end{equation}
    $$
    

    由于$v.dis$的值一经赋值后不再变化. 所以我们通过归纳法证明了对每个节点$v$, 有 $v.dis \geq \delta(s,v)$​

    ***

    为了证明相等关系的另一半 $v.dis \leq \delta(s,v)$​, 首先要对BFS过程进行更细致的刻画.

    

  * **引理5.3** 假设在BFS过程中, 队列中的元素为$<v_1, v_2, \dots, v_r>$  ( $v_1$是队头, $v_r$​ 是队尾 ). 我们有:

    $v_i.dis \leq v_{i+1}.dis$ ( $1 \leq i \leq r+1 $ ) , $ v_r.dis \leq v_1.dis+1 $​

    证明:

    采用数学归纳法,对队列上的操作归纳. 初始情况下, 队列中只有源点$s$, 结论显然成立. 下面要证明队列任意执行一个操作(出队或入队), 上述结论总是成立.

    假设队头元素$v_1$​**出队**, 则$v_2$成为新的队头元素. 根据归纳假设, 有

    $v_r.dis \leq v_1.dis + 1 \leq v_2.dis + 1$

     从$v_2$到$v_r$​​的所有元素的小于等于关系依然成立. 所以执行一个出队操作后, 要证明的结论保持成立.

    假设有一个新元素$v_{r+1}$入队, 此时必然从队首取出一个节点进行处理, 记为$u$. 在处理$u$时, 我们发现了白色邻居$v_{r+1}$并将它放到队列尾部. 此时$v_{r+1}.dis=u.dis+1$. 在$u$出队前的时刻, $u$是队头, $v_1$是队列中的第二个元素, 所以$u.dis \leq v_1.dis$. 根据上面的分析, 有  $v_{r+1}.dis = u.dis +1 \leq v_1.dis  + 1$.

     在$u$ 出队之前,$v_{r+1}$未入队时, $u$是队头, $v_r$​是队尾. 同样根据归纳假设, 有

    $$
    v_r.dis \leq u.dis+1=v_{r+1}.dis
    $$
    对于队列中其他元素而言, 不等关系未受影响.
    
    
    
    综上, 基于归纳法我们证明了, BFS过程中的任意时刻:
    $$
    \begin{align}
    v_i.dis &\leq v_{i+1}.dis, \ 1 \leq i \leq r+1 \nonumber \\
    v_r.dis &\leq v_1.dis+1 \nonumber
    \end{align}
    $$
    



* **定理5.1** 假设从图$G$中的源点$s$开始对整个图完成BFS, 则对任意节点$v$, $v.dis = \delta(s,v)$, 且从$s$到$v$由TE组成的路径就是$s$到$v$的最短路径(不一定是唯一的最短路径)

  证明: 

  采用反证法, 假设存在一些节点, 它们的dis值不等于源点到它们的最短路径值. 在这些节点中, 取源点到其距离最短的节点, 记为 $v$ (显然$v$不可能为$s$ ). 根据引理5.2, 有$v.dis > \delta(s,v)$. 注意$s$到$v$​必然可达, 否则$ \delta(s,v) = + \infty \geq v.dis$​

  考察$s$到$v$的最短路径. 记$u$为该路径上在$v$前面的节点, 则 $\delta(s,v)=\delta(s,u)+1$. 根据选取$v$的特定方式, 有$u.dis=\delta(s,u)$ (易证). 由此, 有:
  $$
  v.dis > \delta(s,v) = \delta(s,u)+1=u.dis+1
  $$
  下面考察节点$u$刚从队头出队的时刻. 此时节点$v$可能有三种颜色.

  * 如果$v$为白色, 则根据BFS框架, 将赋值$v.dis=u.dis+1$, 这与$v.dis > u.dis+1$矛盾
  * 如果$v$为灰色,则记它作为节点$w$的白色邻居被放到队尾, 且 $v.dis = w.dis+1$. 由于$w$比$v$更早离开队列, 所以根据引理5.3, 有$v.dis=w.dis+1 \leq u.dis+1$, 这与$v.dis > u.dis+1$矛盾
  * 如果$v$为黑色, 则在$u$之前它已离开队列, 所以 $v.dis\leq u.dis$, 这与$v.dis > u.dis+1$矛盾

  证毕.

  



## BFS树

对于边$uv$

|      | 有向                       | 无向                                |
| ---- | -------------------------- | ----------------------------------- |
| TE   | $v.p = u; v.dis = u.dis+1$ | 同左                                |
| BE   | $0 <= v.dis < u.dis$       | nil                                 |
| DE   | nil                        | nil                                 |
| CE   | $v.dis \leq u.dis+1$​       | $v.dis = u.dis$​ 或$v.dis = u.dis+1$​ |

* 有向图

  * TE: 当遍历节点 $v$ 时，发现其白色邻居 $v$,  则 $uv$​​​​​ 为TE.   在一个连通片内所有TE组成的子图**连通**且**无环**且包含了该连通片中所有节点. 如果忽略所有边的方向, 则这些TE组成当前连通片的一棵生成树,称为"BFS树"
  * BE: 当遍历节点$u$时,发现其黑色邻居 $v$, 且 $v$是$u$在BFS树中的祖先节点, 则$uv$​为BE. 对于BE $uv$, 有 $ 0 \leq v.dis < u.dis$​​.
  * DE: BFS不可能出现DE。反证假设$uv$为DE，那么考察在节点$u$刚出队列,即将处理它的所有邻居的时刻, 节点$v$的情况:
    *  节点$v$不可能是白色,否则$uv$为TE
    *  节点$v$不可能为灰色, 因为在此时$u$刚出队列, 而若$v$为灰色(正在队列中), 这和$u$是$v$在遍历树上的祖先节点矛盾
    *  节点$v$不可能是黑色, 在 节点$u$刚出队的时刻, 如果 节点$v$已经结束遍历, 这同样和$u$是$v$​在遍历树上的祖先节点矛盾
  * CE: 当遍历节点$u$​时,发现其灰色或者黑色邻居 $v$​, 且$v$​不是$u$​的祖先节点( 前面关于DE的讨论证明了必然不可能是子孙节点 ), 则$uv$​为CE. 对于CE, 有$v.dis \leq u.dis+1$​​

    *  与DFS类似, CE同样可能存在于两个不同的BFS树之间

* 无向图
  
  * TE: 与有向图的情况类似,  当遍历节点 $v$ 时，发现其白色邻居 $v$,  则 $uv$ 为TE.  对于TE$(u,v)$​, 有 $v.dis = u.dis+1$. 所有TE组成(当前连通片的)BFS遍历树, 我们为每条TE进行定向, 其方向就是遍历推进的方向.
  * BE: 不存在（证明易）
  * DE: 不存在（证明易）
  * CE: 当遍历节点$u$​​​时,发现其灰色邻居 $v$​​​(前面关于BE和DE的讨论证明了$v$​​​不可能是$u$​​​的祖先或子孙节点), 则$uv$​​​为CE. 对于CE, 有 $v.dis = u.dis$​​​ 或 $v.dis = u.dis+1$​
    * 注意, 此时节点$v$​不可能是白色,否则$uv$​为TE; 节点$v$​不可能是黑色, 否则由于无向边$uv$​的存在, 在处理$u$​时, 必然已处理过$uv$​, 此时的边$uv$​是二次遍历,直接被剔除, 不做处理.
  
  
  
  
  
* **推论5.1**, 对于BFS过程中的CE $uv$, 
  
  * 无向图 $v.dis = u.dis$ 或 $v.dis = u.dis+1$
  * 有向图 $v.dis \leq u.dis+1$​
  
  证明:( 书上有图)
  
  对于有向图的CE $uv$,我们考察$v.dis$最大可以比$u.dis$大多少. 注意, 节点$v$发现得越晚, $v.dis$越大. 由于图中有边$uv$的存在, 所以最迟将节点$u$出队列时, 必将访问节点$v$.  所以$v.dis \leq u.dis+1$​
  
  对于无向图的CE $uv$, 当处理$u$时, 根据前面的讨论, $v$只能是灰色, 即$v$在队列中. 根据引理5.3, 有$u.dis \leq v.dis \leq u.dis+1$. 所以$v.dis = u.dis$ 或 $v.dis = u.dis+1$

## 应用

### 二部图

给定无向图$G=(V,E)$, 我们称之为二分图， 如果存在顶点$V$的划分$V_1$, $V_2$ ( $V_1 \cap V_2= \emptyset, V_1 \cup V_2=V$ ), 使得图中任意的边均满足它的一个顶点在 $V_1$，另一个顶点在$V_{2}$（ 即，在$V_{1}$ 和 $V_{2}$ 内部， 任意一对顶点没有边相连 ）​​

（等价于二着色问题）

* 发现TE,推进着色； 发现非TE，检查着色
* DFS也可以

### k度子图

给定无向图$G$，定义图$G$的子图$H$​为*k*度子图，如果每个顶点的度均大于等于输入的参数*k* 

* 对于BFS中的点v，若v.d < k(  d为v的度数 )， 则v的邻居d--；
* DFS也可以

# DFS

## s → all

有向图G，问是否存在点s，s到所有点可达？ 

* “可达性”可使用SCC，因为SCC是可达性的等价类。求出G的收缩图后，又由于收缩图是有向**无环**图。 则检查每个顶点，若存在至少两个顶点出度为0，则不存在； 若仅存在一个出度为0的顶点，则从该顶点出发遍历

* 对于“all → s”，只需把图转置

