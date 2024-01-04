---
title: Graph Based Segmentation
tags:
---



# Images as Graphs

Images as Graphs:
- A vertex for each pixel.
- An edge between each pair of pixels.
- Graph Notation: $G=(V, E)$ where $V$ and $E$ are the sets of vertices and edges, respectively.

- Each edge is weighted by the <u>affinity</u> or similarity between its two vertices.

## Measuring affinity

Let $i$ and $j$ be two pixels whose features are $\mathbf{f}_i$ and $\mathbf{f}_j$.

Pixel Dissimilarity:
$$
S\left(\mathbf{f}_i, \mathbf{f}_j\right)=\sqrt{\left(\sum_k\left(f_{i k}-f_{j k}\right)^2\right)}
$$

Pixel Affinity:
$$
w(i, j)=A\left(\mathbf{f}_{i, j}, \mathbf{f}_j\right)=e^{\left\{\frac{-1}{2 \sigma^2} S\left(\mathbf{f}_i, \mathbf{f}_j\right)\right\}}
$$

# Graph Cut

Cut $C=\left(V_A, V_B\right)$ is a partition of vertices $V$ of a graph $G=(V, E)$ into two disjoint subsets $V_A$ and $V_B$.

![image-20240103202744502](/Users/lyk/Library/Application Support/typora-user-images/image-20240103202744502.png)

Cut-Set: Set of edges whose vertices are in different subsets of partition.

Cost of Cut: Sum of weights of cutset edges.
$$
\operatorname{cut}\left(V_A, V_B\right)=\sum_{u \in V_A, v \in V_B} w(u, v)
$$


Criteria for Graph Cut:
- A pair of vertices (pixels) within a subgraph have high affinity.
- A pair of vertices from two different subgraphs have low affinity.

That is, minimize the cost of cut. Also called **Min-Cut**.

Each subgraph is an image segmentation.

## Problem with Min-Cut

There's a bias to cut small, isolated segments.

![image-20240103201752816](/Users/lyk/Library/Application Support/typora-user-images/image-20240103201752816.png)



Solution: Normalized Cut to flavor larger subgraphs.



## Measure of subgraph size

Compute how strongly vertices $V_A$ are associated with vertices $V$.
$$
\operatorname{assoc}\left(V_A, V\right)=\sum_{u \in V_A, v \in V} w(u, v)
$$
![image-20240103202205032](/Users/lyk/Library/Application Support/typora-user-images/image-20240103202205032.png)



## Normalized Cut (NCut)

Minimize Cost of Normalized Cut during Partition
$$
\operatorname{NCut}\left(V_A, V_B\right)=\frac{\operatorname{cut}\left(V_A, V_B\right)}{\operatorname{assoc}\left(V_A, V\right)}+\frac{\operatorname{cut}\left(V_A, V_B\right)}{\operatorname{assoc}\left(V_B, V\right)}
$$

Minimizing NCut has no known polynomial time solution. It is NP-Complete.

Fast eigenvector-based approximations exist [Shi 2000].
