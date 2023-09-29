---
title: Count Prime Numbers
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
mathjax: true
date: 2023-09-29 14:55:50
---


[204. Count Primes](https://leetcode.com/problems/count-primes/)

Given an integer `n`, return *the number of prime numbers that are strictly less than* `n`.

<!--more-->

**Example 1:**

```
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```





# Terminology

A **prime number** (or a **prime**) is a [natural number](https://en.wikipedia.org/wiki/Natural_number) greater than 1 that is not a [product](https://en.wikipedia.org/wiki/Product_(mathematics)) of two smaller natural numbers. A natural number greater than 1 that is not prime is called a [composite number](https://en.wikipedia.org/wiki/Composite_number).[^1] 

$\mathbb{P}$: 全体质数集合.

# Bruce Force

Brute force: 写一个判断是否是素数的方法, 然后调用n次

```java
int countPrimes(int n) {
    int count = 0;
    for (int i = 2; i < n; i++)
        if (isPrime(i)) count++;
    return count;
}

// 判断整数 n 是否是素数
boolean isPrime(int n) {
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            // 有其他整除因子
            return false;
    return true;
}
```

Complexity: 1^2 + 2^2 + 3^2 + ... + (n-1)^ = $O(n^2)$

#  Sieve of Eratosthenes

Idea: 与其把{2, ..., n-1}的素数一个个找出, 不如{2, ..., n-1}的非素数全部去除, 剩下的都是素数.

例如: 

* 2 是一个素数，那么 2 × 2 = 4, 3 × 2 = 6, 4 × 2 = 8... 都不可能是素数了.
* 3 也是素数，那么 3 × 2 = 6, 3 × 3 = 9, 3 × 4 = 12... 也都不可能是素数了.

这算法叫做 Sieve of Eratosthenes[^2].

## Proof

注意到如果p是素数, 那么2 \* p, 3 \* p, ..., k \* p 都是合数(composite number), 设这种方法构造出的集合为$s_1$:
$$
s_1 = \{kp | p \in \mathbb{P}, k \in N \}
$$
令 $s_2$ 为: 小于n的全体合数的集合.



Then we have:
$$
s_1 \subset s_2
$$



由于质数分解定理, 所有的合数都可以用这种方法构造, 因此:
$$
s_2 \subset s_1
$$
So: 
$$
s_1 = s_2
$$


所以, **全体合数都可以用这种方法构造, 且这种方法构造出的数也都属于合数.**

自然, 这个定律对小于n的合数也成立. 因此 **小于n的全体合数都可以用这种方法构造, 且这种方法构造出的数也都属于小于n的合数.**

## Code

第一版代码:

```java
public int countPrimes(int n) {
        Boolean[] isPrime = new Boolean[n];
        Arrays.fill(isPrime, true);

        //Remove all composite numbers that are multiples of p and less than n.
        for(int p = 2; p * p < n; p++)
            if(isPrime[p])
                for(int m = 2 * p; m < n; m+=p)
                    isPrime[m] = false;

        int cnt = 0;
        for(int i = 2; i < n; i++)
        {
            if(isPrime[i]) cnt++;
        }
        return cnt;
    }
```



该代码还有两个可改进之处.

# Improvement1

我们有如下定理:

1. 对于任意的数字$m$, 有$m = pq$, 且易知 $p$, $q$至少有一个小于等于$\sqrt{m}$. 
2. 如果m是合数, 那么它可以写成若干个质数相乘的形式(即必定存在质因子):

> Prime factorization: 每个合数都可以写成几个[质数](https://baike.baidu.com/item/质数/263515?fromModule=lemma_inlink)相乘的形式，其中每个质数都是这个合数的因数.

**我们需要证明: For any composite number $m$, it has a prime factor p, $p \le \sqrt{n}$.** 

也就是说合数$m$在质数分解时必定能分解出一个小于等于$\sqrt {m}$的质数$p$.

## Proof

The prime factorization of compisite number $m$:  $m = p \times q_1 \times q_2 \times q_3 \times \cdots$, $p, q_1, q_2, ... \in \mathbb{P}$.

Let $q = q_1 \times q_2 \times q_3 \times \cdots, q_1, q_2, ... \in \mathbb{P}$, 

then $m = pq$.



1. If $p \le \sqrt{n}$, that's fine.

2. If $p > \sqrt{n}$, then we must have $q \le \sqrt{n}$. 

   Since $q = q_1 \times q_2 \times q_3 \times \cdots, \ q_1, q_2, ... \in \mathbb{P}$, we can swap the $p$ and any $q_k, k \in N$.

   So that the new $p$ satisfies $p \le \sqrt{n}$.



To sum, For any composite number $m$, it has a prime factor p, $p \le \sqrt{n}$.

## Implementation

下面这段代码的作用是“寻找合数m”, 它只需要找到一个$m$的质因子$p$, 就可以找到所有作为p的倍数的合数m.

```java
//Remove all composite numbers that are multiples of p and less than n.
	for(int p = 2; p * p < n; p++)
		if(isPrime[p])
			for(int m = 2 * p; m < n; m+=p)
  			isPrime[m] = false;
```



而根据上面的证明, 任何合数$m$都有一个小于等于$\sqrt {m}$的质因子$p$. 所以我们只需要在$[2, \sqrt {m}]$中寻找$p$.

Since $m < n$, $p$的范围也就是$[2, \sqrt {n}]$:

```java
//Remove all composite numbers that are multiples of p and less than n.
//Since we always have p <= \sqrt{n}, we just iterate p to  \sqrt{n}.
	for(int p = 2; p * p < n; p++)
		if(isPrime[p])
			for(int m = 2 * p; m < n; m+=p)
  			isPrime[m] = false;
```

## Code

```java
public int countPrimes(int n) {
        Boolean[] isPrime = new Boolean[n];
        Arrays.fill(isPrime, true);

        //Remove all composite numbers that are multiples of p and less than n.
        //Since we always have p <= \sqrt{n}, we just iterate p to  \sqrt{n}.
        for(int p = 2; p * p < n; p++)
            if(isPrime[p])
                for(int m = 2 * p; m < n; m+=p)
                    isPrime[m] = false;

        int cnt = 0;
        for(int i = 2; i < n; i++)
        {
            if(isPrime[i]) cnt++;
        }
        return cnt;
    }
```



# Improvement2

代码内层的 for 循环也可以优化. 我们之前的做法是:

```java
for(int m = 2 * p; m < n; m+=p)
	isPrime[m] = false;
```

这样可以把 `p` 的整数倍都标记为 `false`, 但是仍然存在计算冗余.

对于每个质数p, 我**们只需从`m = p * p`而不是`m = 2 * p`开始迭代.** 因为对于$\forall k < p$, `m = kp`已经在之前的`p = k`时被迭代过了. 

例如对于 `n = 25`, `p = 5` 的情况, 算法会标记 5 × 2 = 10，5 × 3 = 15 等等数字, 但  5 × 2和 5 × 3已经在之前`p = 2, p = 3`时被迭代过了.

## Code

```java
for(int m = p * p; m < n; m+=p)
	isPrime[m] = false;
```



# Final Code

```java
public int countPrimes(int n) {
        Boolean[] isPrime = new Boolean[n];
        Arrays.fill(isPrime, true);

        //Remove all composite numbers that are multiples of p and less than n.
        //Since we always have p <= \sqrt{n}, we just iterate p to  \sqrt{n}.
        for(int p = 2; p * p < n; p++)
            if(isPrime[p])
                for(int m = p * p; m < n; m+=p)
                    isPrime[m] = false;

        int cnt = 0;
        for(int i = 2; i < n; i++)
        {
            if(isPrime[i]) cnt++;
        }
        return cnt;
}
```



[^1]: https://en.wikipedia.org/wiki/Prime_number
[^2]: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
