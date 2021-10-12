---
title: L15 Path in Graph
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-08-11 14:42:00
---


Outline:

* Single-source shortest paths( SSSP )

  * Dijkstra algorithm by example
  * Priority queue-based implementation
  * Proof of correctness

* All-pairs shortest paths( APSP )

  * Shortest path and transitive closure
  * Warshall algorithm for **transitive closure**
    * BF1, BF2, BF3 => Warshall algorithm
    * Floyd algorithm for shortest paths

  <!--more-->

  

#  Single-source shortest paths

## Dijkstra algorithm

* 懂得都懂
* 不能有负权边

## Priority queue-based implementation

```c++
void shortestPaths( EdgeList[] adjinfo, int n, int s, int[] parent, float[] fringeWgt )
    int[] status = new int[n+1];
	MinPQ pq = create( n, status, parent, fringeWgt );

	insert( pq, s, -1, 0 );
	while( isEmpty(pq) == false )
        int v = getMin(pq);
		deleteMin(pq);
		updateFringe( pq, adjinfo[v], v );
```

```C++
void updateFringe( MinPQ pq, EdgeList adjinfoOfV, int v )
    float myDist = pq.fringeWgt[v];
	EdgeList remAdj;
	remAdj = adjInfoOfV;
	while( remAdj != nil )
		EdgeInfo wInfo = first( remAdj );
		int w = wInfo.to;
		float newDist = myDist + wInfo.weight;
		if( pq.status[w] == unseen )
            insert( pq, w, v, newDist );
		else if( pq.status[w] = fringe )
            if( newDist < getPriority( pq, w ) )
                decreaseKey( pq. w. v. newDist );
		remAdj = rest(remAdj);
return;
            
```



## correctness

* 归纳法 + 反证

## The  Dijkstra Skeleton

* Single-source shortest path( SSSP )
* SSSP  + node weight constraint
  * E.g. in routing
* SSSP + capacity constraint
  * The "pipe problem"
  * The "electric vehicle problem"

# All-pairs shortest paths

* For **all** pairs of vertices in a graph, say, *u*, *v*:
  * Is there a path from *u* to *v*?
  * What is the shortest path from *u* to *v*?
* Reachability as a (reflexive) transitive closure of the adjacency relation
  * Which can be represented as a bit matrix

## Warshall algorithm for transitive closure

### Warshall algorithm

* BF0:  对每个点用Dijkstra

* BF1： Shortcut Algorithm $O(n^4)$​

* BF2:  Emurate all edges (x,v) $O(n^2m)$

  * v as the destination

  ```
  While any entry of R changed
  	for every edge(x,v)
  		r_uv = r_uv ∪ ( r_ux  ∩ r_xv )
  ```

* BF3: Length of the Path  $O(n^4)$​

  * Recursion
    * Reachable via at most k edges
  * Enumeration
    * Enumerate all path length
    * Enumerate all sources and destinations

```
for k=1 to n-1
	for all vertices u
		for all vertices v
			for all vertices x pointing to v
				r_{uv}^k = r_{uv}^{k-1} ∪ ( r_{ux}^{k-1} ∩ r_{xv} )
```

* Warshall Algorithm

  * $O(n^3)$

  ```C++
  void simplTransitiveClosure( boolean[][] A, int n, boolean[][] R )
      int i,j,k;
  	Copy A to R;
  	Set all main diagonal entries, r_{ii}, to true;
  	while( any entry of R changed during one complete pass )
          for( k=1; k <= n ; k++ )
              for(i=1; i<=n; i++)
                  for(j=1; j<=n;j++)
                      r_{ij} = r_{ij} ∪ ( r_{ik}∩ r_{kj} )
  ```

  

#### Correctness of the Warshall Algorithm

* 归纳法

## Floyd algorithm for shortest paths

* 和求可达性一模一样
* Basic formula:

$$
D^{(0)}[i][j] = w_{ij} \\
D^{(k)}[i][j]= min( D^{(k-1)}[i][j], D^{(k-1)}[i][k] + D^{(k-1)}[k][j] )
$$

* Floyd algorithm是一个框架，不只是一个算法

* 不能有**负权环**
