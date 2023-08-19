---
title: Tricks about Coordinates
tags:
  - Algorithm
categories:
  - Computer Science
mathjax: true
date: 2023-08-19 22:14:25
---

Tricks when manipulating coordinates in algorithms.

<!--more-->


# Coordinates Mapping

For a 2-D coordinate (x,y), 0 <= x < M, 0 <= y < N. $N,M \in \mathbb{N}$.

We can map it into 1-D coordinate:
$$
\text{Let} \ S = \{ (x, y)| \ 0 \le x < M, 0 \le y < N. \ x, y \in \mathbb{N}\}, \\
\forall (x,y) \in S, \ f(x,y) = Nx + y
$$


Code:

```java
int linearMap(int x, int y, int M, int N)
{
	int t = x * N + y;
	return t;
}
```

## Theorem: Bijective Function

$f(x,y)$ is a **bijective function**.



**Proof:**

We know that $S = \mathrm{Dom}(f)$. Let $T = \mathrm{Ran}(f)$. So $f: S \rightarrow T$.

According to [XX](https://en.wikipedia.org/wiki/Bijection), if $X$ and $Y$ are [finite sets](https://en.wikipedia.org/wiki/Finite_set) with the same cardinality, and $f: X \rightarrow Y$, then the following are equivalent:

1. *f* is a bijection.
2. *f* is a [surjection](https://en.wikipedia.org/wiki/Surjection).
3. *f* is an [injection](https://en.wikipedia.org/wiki/Injection_(mathematics)).

The proof follows this.



Let $t = f(x, y) \in \mathbb{N}, t \in T$.

1. Prove the equipotential(等势) of $S$ and $T$.

   We have:
   $$
   \begin{align}
   \max(t) &= f(\max (x), \max (y)) = N(M-1) + (N-1) = MN - 1 \\
   \min(t) &= f(\min (x), \min (y)) = 0
   \end{align}
   $$
   So $T = \{0,1,\cdots,MN-1\}$, and $|T| = MN$. 

   We can easily know that $|S| = MN$. 

   So
   $$
   |T| = |S|
   $$

2. Prove $f$ is an injective(单射) function.

   We use contradiction, if $\exists (x_1,y_1), (x_2,y_2) \in S, (x_1,y_1) \ne (x_2,y_2)$
   $$
   t = x_1 N + y_1 = x_2 N + y_2
   $$
   Then $N = \frac {y_2 - y_1}{x_1 - x_2}$.

   While $|y_2 - y_1| \le N-1$, $1 \le |x_1 - x_2| \le M-1$. We have $\max(\frac {y_2 - y_1}{x_1 - x_2}) = N-1 < N$. 

   Thus $N < N$. This is impossible. So two elements in $S$ can't map to the same element in $t$. Thus  $f$ is an injective function.

3. Because (1) and (2), $f$ is a bijective function. QED.

# Move Points in a Linear Space

以二维平面为例, 二维平面上的点$(x,y)$ 张成了线性空间$S = \{ (x, y)| x, y \in \mathbb{R}\}$. 

在二维平面中移动一个单位长度 = 通过给对应维度的值加/减 1. 可以用数组实现:

```java
class DirectionMatrix{
    private int[] left = new int[]{-1,0};
    private int[] right = new int[]{1,0};
    private int[] down = new int[]{0,-1};
    private int[] up = new int[]{0,1};

    private int[][] directions = { left, right, down, up };

    public int[] moveLeft(int x, int y)
    {
        x += left[0];
        y += left[1];
        return new int[]{ x, y };
    }


    public int[] moveRight(int x, int y)
    {
        x += right[0];
        y += right[1];
        return new int[]{ x, y };
    }
    public int[] moveDown(int x, int y)
    {
        x += down[0];
        y += down[1];
        return new int[]{ x, y };
    }
    public int[] moveUp(int x, int y)
    {
        x += up[0];
        y += up[1];
        return new int[]{ x, y };
    }

}
```



