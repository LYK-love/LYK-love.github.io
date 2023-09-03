---
title: Factorial Trailing Zeroes
tags:
  - Algorithm
  - LeetCode
categories:
  - - Mathematics
  - - Computer Science
mathjax: true
date: 2023-09-03 22:33:26
---


Given an integer `n`, return *the number of trailing zeroes in* `n!`.

Note that `n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1`.



[172. Factorial Trailing Zeroes](https://leetcode.com/problems/factorial-trailing-zeroes/)

Ref: [labuladong 题解](https://labuladong.github.io/article/slug.html?slug=factorial-trailing-zeroes)

<!--more-->

**Example 1:**

```
Input: n = 3
Output: 0
Explanation: 3! = 6, no trailing zero.
```

**Example 2:**

```
Input: n = 5
Output: 1
Explanation: 5! = 120, one trailing zero.
```

**Example 3:**

```
Input: n = 0
Output: 0
```



**Constraints:**

- `0 <= n <= 104`

# Solution

首先, 两个数相乘结果末尾有 0, 一定是因为两个数中有因子 2 和 5, 也就是说, 问题转化为：`n!` 最多可以分解出多少个因子 2 和 5?

***

首先, 对于任意的正整数n, 记n的因子2的数量为p, 因子5的数量q, 有:
$$
\forall n \in \mathbb{N^+}, p \ge q.
$$
即n的因子2的数量>=因子5的数量. 

**Proof**:

Since:
$$
\begin{align}
n &= 2p + 1, \nonumber \\
n &= 5q + c, c \in \{ 1,2,3,4\}, \nonumber \\
\end{align}
$$
Therefore:
$$
2p + 1 = 5q + c \nonumber \\
$$


So we have $p = 5/2 q + (c-1)/2$. 

Since c - 1 >= 0, q > 0, so $p = 5/2 q + (c-1)/2 > q$.

Q.E.D.

***

因此, n最多可以分解出多少个因子 2 和 5，主要取决于n能分解出几个因子 5, 因为因子 2 的数量永远比因子 5 的多.

那么问题转化为：`n!` 最多可以分解出多少个因子 5？

令 f(n) = n!的因子5的数量. 那么:

f(5) = 1, f(6, ..., 9) = f(5).

f(10) = 1 + 1, f(10, 11, ..., 14) = f(10).

f(15) = 1 + 1 + 1, f(16, 17, ..., 19) = f(15).

...

因此, 每有一个5的倍数小于等于n, 都能为f(n)提供1个5. 例如: n=11, 有两个小于等于11的数5, 10, 分别提供了一个因子5, 因此11!有两个trailing zero.

考虑 f(25) = 5 + 1. 因为小于等于25的5的倍数有5个, 提供了5个5, 但是25本身就是5 * 5, 因此还额外提供1个5, 因子5的数量为5 + 1. 同理, 对于30!, 因为小于等于30的5的倍数有6个, 其中25这个数能额外提供1个5, 因此因子5的数量为6 + 1. :

f(25) = 5 + 1, f(26, ... 29) = f(25).

f(30) = 6 + 1, f(31, ...34) = f(30).

...



考虑 f(125) = 25 + 5 + 1. 因为小于等于125的5的倍数有25个, 提供了25个5; 小于等于125的25的倍数有5个, 它们分别能额外提供1个5, 总共提供了5个5; 小于等于125的125的倍数有1个, 它在之前的基础上还能额外提供1个5, 总共提供了1个5.



因此, f(n) = 小于等于n的5的倍数的数量 + 小于等于n的25 (5^2)的倍数的数量 + 小于等于n的125 (5^3)的倍数的数量 + ... 

例如: f(130) = 130/5 (小于等于130的5的倍数的数量) + 130 / 25 (小于等于130的25的倍数的数量) + 130 / 125 (小于等于130的125的倍数的数量) + 130 / 625 (小于等于130的625的倍数的数量, 等于0. 后面也都是0, 不再算了)

f(130) = 26 + 5 + 1 + 0 = 32.

# Code

```java
    public int trailingZeroes(int n) {
        int res = 0;
        int divisor = 5;

        while( divisor <= n)
        {
            res += (n / divisor);
            divisor *= 5;
        }
        return res;
    }
```



