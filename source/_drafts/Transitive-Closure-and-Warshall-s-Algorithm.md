---
title: Transitive Closure and Warshall's Algorithm
tags:
  - Discrete Mathematics
categories:
  - [Mathematics]
  - [Computer Science]
mathjax: true
---

We will show that the transitive closure of $R$ (see Section 7) is just  R∞

# THEOREM 1

Let $R$ be a relation on a set $A$. Then the [connectivity relation](https://lyk-love.cn/2023/08/15/relations-and-digraphs/#paths-in-relations-and-digraphs) $R ^{\infty}$ is the **transitive closure** of R.

## Proof

We recall that if $a$ and $b$ are in the set $A$, then $a \ R^{\infty} \ b$ if and only if <u>there is a path</u> in $R$ from $a$ to $b$. 

Now $R^{\infty}$ is certainly transitive since, if $a \ R^{\infty} \ b$ and $b \ R^{\infty} \ c$, the composition of the paths from $a$ to $b$ and from $b$ to $c$ forms a path from $a$ to $c$ in $R$, and so $a R^{\infty} c$. 如果 $a \ R^{\infty} \ b$ and $b \ R^{\infty} \ c$, 即a有一条路到b, b有一条路到c, 那么两条路连起来就是a到c, 因此有$a \ R^{\infty} \ c$, 说明$R^{\infty}$是transitive relation.

To show that $R^{\infty}$ is the smallest transitive relation containing $R$, we must show that if $S$ is any transitive relation on $A$ and $R \subseteq S$, then $R^{\infty} \subseteq S$. 接下来证明$R^{\infty}$是最小的传递关系. 证明思路是: 如果对于任意的传递关系$S$, 且$S$是$R$的超集, $R^{\infty}$都是S的子集, 那么$R^{\infty}$就是最小的传递关系.

Theorem 1 of Section 4 tells us that if $S$ is transitive, then $S^n \subseteq S$ for all $n$; that is, if $a$ and $b$ are connected by a path of length $n$, then $a \ S \ b$. It follows that $S^{\infty}=\bigcup_{n=1}^{\infty} S^n \subseteq S$. 如果S中存在一条长度为n的路径, 且S是传递的, 那么S中也存在一条长度为1的a到b的路径, 也就是$S^n \subseteq S$. 又由于n是从1到正无穷任意取的, 因此有$S^{\infty}=\bigcup_{n=1}^{\infty} S^n \subseteq S$ (1).

**It is also true that if $R \subseteq S$, then $R^{\infty} \subseteq S^{\infty}$, since any path in $R$ is also a path in $S$.** 对于任意的$a \ R^{\infty}\ b$, 由于R是传递关系, R中存在一条a到b的路径(R中的边的序列). 因为 $R \subseteq S$, 所以R中的所有边都包含在S中, 这包括了 $a \ R^{\infty}\ b$ 的那条路径的所有边, 这意味着a, b能在S中通过相同的路径连接, 也就是$a \ S^{\infty}\ b$. 所以有$R^{\infty} \subseteq S^{\infty}$ (2).



Putting these facts together, we see that if $R \subseteq S$ and $S$ is transitive on $A$, **then $R^{\infty} \subseteq S^{\infty} \subseteq S$.** This means that $R^{\infty}$ is the smallest of all transitive relations on $A$ that contain $R$. 结合(1)(2), 我们有$R^{\infty} \subseteq S^{\infty} \subseteq S$, 也就是说对于任意的传递关系S, 如果它是$R$的超集, 那么$R^{\infty}$一定是它的子集, 因此$R^{\infty}$就是最小的传递关系.

We see that $R^{\infty}$ has several interpretations. From a geometric point of view, it is called the **connectivity relation**, since it specifies which vertices are connected (by paths) to other vertices. 

If we include the relation $\Delta$ (see Section 4 ), then $R^{\infty} \cup \Delta$ is the [reachability relation](https://lyk-love.cn/2023/08/15/relations-and-digraphs/#paths-in-relations-and-digraphs) $R^*$, which is frequently more useful. .

## Example 1

Let $A=\{1,2,3,4\}$, and let $R=\{(1,2),(2,3),(3,4),(2,1)\}$. Find the transitive closure of $R$.

### Method 1 

![Figure 42](/Users/lyk/Library/Application Support/typora-user-images/image-20230908233952393.png)

The digraph of $R$ is shown in Figure 42. Since $R^{\infty}$ is the transitive closure, we can proceed geometrically <u>by computing all paths</u>. We see that from vertex 1 we have paths to vertices $2,3,4$, and 1 . Note that the path from 1 to 1 proceeds from 1 to 2 to 1 . Thus we see that the ordered pairs $(1,1),(1,2),(1,3)$, and $(1,4)$ are in $R^{\infty}$. Starting from vertex 2 , we have paths to vertices $2,1,3$, and 4 , so the ordered pairs $(2,1),(2,2),(2,3)$, and $(2,4)$ are in $R^{\infty}$. The only other path is from vertex 3 to vertex 4 , so we have

$R^{\infty}$=\{(1,1),(1,2),(1,3),(1,4),(2,1),(2,2),(2,3),(2,4),(3,4)\}

### Method 2

The matrix of $R$ is
$$
\mathbf{M}_R=\left[\begin{array}{llll}
0 & 1 & 0 & 0 \\
1 & 0 & 1 & 0 \\
0 & 0 & 0 & 1 \\
0 & 0 & 0 & 0
\end{array}\right]
$$
We may proceed algebraically and compute the powers of $\mathbf{M}_R$. Thus
$$
\begin{gathered}
\left(\mathbf{M}_R\right)_{\odot}^2=\left[\begin{array}{cccc}
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0
\end{array}\right], \quad\left(\mathbf{M}_R\right)_{\odot}^3=\left[\begin{array}{llll}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0
\end{array}\right], \\
\left(\mathbf{M}_R\right)_{\odot}^4=\left[\begin{array}{llll}
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0
\end{array}\right] .
\end{gathered}
$$
Continuing in this way, we can see that $\left(\mathbf{M}_R\right)_{\odot}^n$ equals $\left(\mathbf{M}_R\right)_{\odot}^2$ if $n$ is even and equals $\left(\mathbf{M}_R\right)_{\odot}^3$ if $n$ is odd and greater than 1 . Thus
$$
\mathbf{M}_R=\mathbf{M}_R \vee\left(\mathbf{M}_R\right)_{\odot}^2 \vee\left(\mathbf{M}_R\right)_{\odot}^3=\left[\begin{array}{cccc}
1 & 1 & 1 & 1 \\
1 & 1 & 1 & 1 \\
0 & 0 & 0 & 1 \\
0 & 0 & 0 & 0
\end{array}\right]
$$
and this gives the same relation as Method 1 . 



In Example 1 we did not need to consider all powers $R^n$ to obtain $R^{\infty}$. This observation is true whenever the set $A$​ is finite, as we will now prove. 注意到, 要得到$R^{\infty}$, 我们不需要计算所有的$R^n$. 这一结论对于所有的有限集合A都成立, 我们会在[THEOREM 2](#theorem-2)证明.



# THEOREM 2

Let $A$ be a set with $|A|=n$, and let $R$ be a relation on $A$. Then
$$
R^{\infty}=R \cup R^2 \cup \cdots \cup R^n .
$$
**In other words, powers of $R$ greater than $n$ are not needed to compute $R^{\infty}$.**

## Proof

![Figure 43](/Users/lyk/Library/Application Support/typora-user-images/image-20230909000411630.png)

Let $a$ and $b$ be in $A$, and suppose that $a, x_1, x_2, \ldots, x_m, b$ is a path from $a$ to $b$ in $R$; that is, $\left(a, x_1\right),\left(x_1, x_2\right), \ldots,\left(x_m, b\right)$ are all in $R$. If $x_i$ and $x_j$ are the same vertex, say $i<j$, then the path can be divided into three sections. First, a path from $a$ to $x_i$, then a path from $x_i$ to $x_j$, and finally a path from $x_j$ to $b$. The middle path is a cycle, since $x_i=x_j$, so we simply leave it out and put the remaining two paths together. **This gives us a shorter path** from $a$ to $b$ (see Figure 43).

1. 假设$a \ R^{\infty} \ b$, 即R中存在一条a->b的路径 $a, x_1, x_2, \ldots, x_m, b$ . 如果$a, x_i$ 或者 $x_i, b$ 或者$x_i$,  $x_j$ ( $i<j$ ) 出现重复, 即这部分成环, 则可以通过去掉该环来得到一条更短的a->b路径. 

2. Now let $a, x_1, x_2, \ldots, x_k, b$ be the shortest path from $a$ to $b$. 现在考虑a->b的**最短路径** $a, x_1, x_2, \ldots, x_k, b$.

3. If $a \neq b$, then all vertices $a, x_1, x_2, \ldots, x_k, b$ are distinct. Otherwise, the preceding discussion shows that we could find a shorter path.  如果a!=b, 那么$a, x_1, x_2, \ldots, x_k, b$ 的每一个点都不重复, 否则就可以通过上面的方法(1)得到一条更短的路径.

   Thus the length of the path is at most $n-1$ (since $|A|=n$ ). 因此, 如果a!=b, a->b的最短路径的长度不超过n-1.

4. If $a=b$, then for similar reasons, the vertices $a, x_1, x_2, \ldots, x_k$ are distinct, so the length of the path is at most $n$. 如果a=b, 那么$a, x_1, x_2, \ldots, x_k$的每一个点都不重复, 否则如果$a=x_k$, 那么进入(4)的递归; 如果$a=x_i, 1\le i <k$, 那么可以通过上面的方法(1)得到一条更短的路径. 所以如果a=b, a->b的最短路径的长度不超过n.

5. In other words, if $a \ R^{\infty} \ b$, then $a R^k b$, for some $k, 1 \leq k \leq n$. Thus $R^{\infty}=R \cup R^2 \cup \cdots \cup R^n$. 因此, 如果a->b的路径存在($a \ R^{\infty} \ b$), 那么a->b的长度小于等于n路径也必定存在($a \ R^{k} \ b, 1 \leq k \leq n$).



The methods used to solve Example 1 each have certain difficulties. The graphical method is impractical for large sets and relations and is not systematic. The matrix method can be used in general and is systematic enough to be programmed for a computer, but it is inefficient and, for large matrices, can be prohibitively costly. Fortunately, a more efficient algorithm for computing transitive closure is available. It is known as <u>Warshall's algorithm</u>, after its creator, and we describe it next.

# Warshall's Algorithm

