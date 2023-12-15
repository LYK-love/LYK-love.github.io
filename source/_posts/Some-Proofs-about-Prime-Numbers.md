---
title: Some Proofs about Prime Numbers
tags:
  - Number Theory
categories:
  - Mathematics
mathjax: true
date: 2023-09-03 23:42:44
---


Ref: Daniel J. Velleman. (2019). *HOW TO PROVE IT* (3th ed., pp. 1-6). Cambridge University Press.

<!--more-->

For each integer $n$ from 2 to 10, the table below shows whether or not both $n$ and $2^n - 1$ are prime.

| n    | Is $n$ prime? | $2^n - 1$ | Is $2^n - 1$ prime? |
| ---- | ------------- | --------- | ------------------- |
| 2    | True          | 3         | True                |
| 3    | True          | 7         | True                |
| 4    | False         | 15        | False               |
| 5    | True          | 31        | True                |
| 6    | False         | 63        | False               |
| 7    | True          | 127       | True                |
| 8    | False         | 255       | False               |
| 9    | False         | 511       | False. 511=7\*73.   |
| 19   | True          | 1023      | False. 1023=31\*33. |



A surprising pattern emerges. It appears that $2^n - 1$ is prime in precisely those cases in which is prime!

基于此, 我们可以提出两个假设(Conjecture):

**Conjecture 1. Suppose $n$ is an integer larger than 1 and $n$ is prime. Then $2^n-1$ is prime.**

**Conjecture 2. Suppose $n$ is an integer larger than 1 and $n$ is not prime. Then $2^n-1$ is not prime.**

# Conjecture 1

Conjecture 1是错误的, 很容易证明. 

Let n=11, 11 is prime, but $2^{11}-1=2047=23 \cdot 89$, so $2^{11}-1$ is composite. Thus, 11 is a <u>counterexample</u> to Conjecture 1.

More counterexamples: Both 23 and 29 are prime, but:

$2^{23}-1=8,388,607=47 \times 178,481$

$2^{29}-1=536,870,911=$ $2,089 \times 256,999$

# Conjecture 2

However, Conjecture 2 is correct. Here is a proof of the conjecture:

Since $n$ is not prime, there are positive integers $a$ and $b$ such that $a<n, b<n$, and $n=a b$. Let $x=2^b-1$ and $y=1+2^b+2^{2 b}$ $+\cdots+2^{(a-1) b}$. Then

证明思路是构造两个特殊的数字$a, b$, 使得$xy = 2^n - 1$, 即x, y是 $2^n - 1$ 的因子. 然后证明x, y都是小于 $2^n - 1$ 且大于1的, 说明 $ 2^n - 1$ 是prime number.
$$
\begin{aligned}
x y & =\left(2^b-1\right) \cdot\left(1+2^b+2^{2 b}+\cdots+2^{(a-1) b}\right) \nonumber \\
& =2^b \cdot\left(1+2^b+2^{2 b}+\cdots+2^{(a-1) b}\right)-\left(1+2^b+2^{2 b}+\cdots+2^{(a-1) b}\right) \nonumber \\
& =\left(2^b+2^{2 b}+2^{3 b}+\cdots+2^{(a-1) b}+2^{a b}\right)-\left(1+2^b+2^{2 b}+\cdots+2^{(a-1) b}\right) \nonumber \\
& =2^{a b}-1 \nonumber \\
& =2^n-1 . \nonumber
\end{aligned}
$$
Since $b<n$, we can conclude that $x=2^b-1<2^n-1$. Also, since $a b=n>a$, it follows that $b>1$. Therefore, $x=2^b-1>2^1-1=1$, so $y<x y=2^n-1$. Thus, we have shown that $2^n-1$ can be written as the product of two positive integers $x$ and $y$, both of which are smaller than $2^n-1$, so $2^n-1$ is not prime.

# Theorem1

Euclid (circa $300 \mathrm{BCE}$ ) gave a proof of this fact in his *Elements*. 

**Theorem 1. There are infinitely many prime numbers.**

## Proof

Suppose there are only finitely many prime numbers. 反证法, 假设只有有限个质数.

Let $p, p_2, \cdots, p_n$ be a list of all prime numbers. 

Let $m=p_1 p_2 \cdots p_n+1$. Note that $m$  is not divisible by $p_1$, since dividing $m$ by $p_1$ gives a quotient of $p_2 p_3$. remainder of 1 .

Similarly, $m$ is not divisible by any of $p_2, p_3, \ldots, p$.  构造出一个m, m不能被任何一个质数整除.

We now use the fact that every integer larger than 1 is either prime or  be written as a product of two or more primes. (We'll see a proof in Chapter 6 - see Theorem 6.4.2.) Clearly $m$ is larger than 1, so $m$ is either prime or a product of primes. 根据质数分解定理(后面会说), 任何大于1的正整数要么是一个质数, 要么是若干个质数的积. m显然大于1, 因此要么是一个质数, 要么是若干个质数的积.



Suppose first that $m$ is prime. Note that $m$ is larger than all of the numbers in the list $p_1, p_2, \ldots, p_n$, so we've found a prime number not in this list. But this contradicts our assumption that this was a list of all prime numbers. 由于$p, p_2, \cdots, p_n$ 已经是由全部质数组成的列表, 所以m比全部质数还要大. 这和假设"m是质数"不符, 因此m不是质数. 那么m只可能是若干个质数的积.

Now suppose $m$ is a product of primes. Let $q$ be one of the primes in this product. Then $m$ is divisible by $q$. But we've already seen that $m$ is not divisible by any of the numbers in the list $p_1, p_2, \ldots, p_n$, so once again we have a contradiction with the assumption that this list included all prime numbers. 同样的, m不能被$p, p_2, \cdots, p_n$ 中的任何一个质数整除, 而$p, p_2, \cdots, p_n$ 已经是全体质数了, 因此m不可能是若干个质数的积.

Since the assumption that there are finitely many prime numbers has led to a contradiction, there must be infinitely many prime numbers. 因此, “质数数量是有限的”这个假设不成立, 所以质数数量是无限的.



# Mersenne Primes

Prime numbers of the form $2^n-1$ are called **Mersenne primes**, after Father Marin Mersenne (1588-1648), a French monk and scholar who studied these numbers. 

Although many Mersenne primes have been found, **it is still not known if there are infinitely many of them.** Mersenne prime的数量未知.

Many of the largest known prime numbers are Mersenne primes. As of February 2019, the largest known prime number is the Mersenne prime $2^{82,589,933}-1$, a number with $24,862,048$ digits.

Mersenne primes are related to perfect numbers, the subject of another famous unsolved problem of mathematics. 

A positive integer $n$ is said to be **perfect** if $n$ is equal to the sum of all positive integers smaller than $n$ that divide $n$. (For any two integers $m$ and $n$, we say that $m$ divides $n$ if $n$ is divisible by $m$; in other words, if there is an integer $q$ such that $n=q m$.) For example, the only positive integers smaller than 6 that divide 6 are 1,2, and 3, and $1+2+3=6$. Thus, 6 is a perfect number. 完美数(perfect number)是和所有小于它并能够整除它的数之和**相等**的正整数.

Euclid proved that if $2^n-1$ is prime, then $2^{n-1}\left(2^n-1\right)$ is perfect. Thus, every Mersenne prime gives rise to a perfect number. 每一个Mersenne prime都可以对应一个perfect number. 

Furthermore, about 2000 years after Euclid's proof, the Swiss mathematician Leonhard Euler (17071783), proved that **every even perfect number arises in this way**. (For example, note that $6=2^1\left(2^2-1\right.$ ) and $28=2^2\left(2^3-1\right)$.) 每个even perfect nomber都是$ 2^n - 1$的形式.

Because it is not known if there are infinitely many Mersenne primes, it is also not known if there are infinitely many even perfect numbers. It is also not known if there are any odd perfect numbers. 由于Mersenne prime的数量未知, 所以perfect number的数量也未知. 并且odd perfect number的存在也是未知的.

# Theorem 2

我们还有一个直觉的发现: 随着数字的增大, 质数似乎越来越稀疏. For example, there are 25 primes between 1 and 100, 16 primes between 1001 and 1100, and only six primes between 1,000,001 and 1,000,100.

这个假设我还不知道怎么证明, 但可以证明的是: 存在一段任意长的连续数列, 其中没有任何质数(也就是说, 质数之间的间隔可能很长):

**Theorem 2. For every positive integer $n$, there is a sequence of $n$ consequetive positive integers containing no primes.**

## Proof

Suppose $n$ is a positive integer. Let $x=(n+1) !+2$. We will show that none of the numbers $x, x+1, x+2, \ldots, x+(n-1)$ is prime. Since this is a sequence of $n$ consecutive positive integers, this will prove the theorem. 构造一个 $x=(n+1) !+2$, 证明序列$x, x+1, x+2, \ldots, x+(n-1)$ 中没有质数, 由于该序列长度为$n$, 且n是任意取的, 所以证明了Theorem 2. 



To see that $x$ is not prime, note that
$$
\begin{aligned}
x & =1 \cdot 2 \cdot 3 \cdot 4 \cdots(n+1)+2 \\
& =2 \cdot(1 \cdot 3 \cdot 4 \cdots(n+1)+1) .
\end{aligned}
$$
Thus, $x$ can be written as a product of two smaller positive integers, so $x$ is not prime.
Similarly, we have
$$
\begin{aligned}
x+1 & =1 \cdot 2 \cdot 3 \cdot 4 \cdots(n+1)+3 \\
& =3 \cdot(1 \cdot 2 \cdot 4 \cdots(n+1)+1),
\end{aligned}
$$
so $x+1$ is also not prime. In general, consider any number $x+i$, where $0 \leq i \leq n-1$. Then we have
$$
\begin{aligned}
x+i & =1 \cdot 2 \cdot 3 \cdot 4 \cdots(n+1)+(i+2) \\
& =(i+2) \cdot(1 \cdot 2 \cdot 3 \cdots(i+1) \cdot(i+3) \cdots(n+1)+1),
\end{aligned}
$$
so $x+i$ is not prime.
Theorem 2 shows that there are sometimes long stretches between one prime and the next prime. 

#  Twin Primes

[Theorem 2](#theorem-2)证明了质数之间可能存在很长的间隔, 但同样存在一些间隔比较小的质数. 例如: 质数 2 and 3只间隔1; 质数 5 and 7, 29 and 31, 7949 and 7951 只间隔2.

A **twin prime** is a [prime number](https://en.wikipedia.org/wiki/Prime_number) that is either 2 less or 2 more than another prime number.

当两个质数的间隔小于等于2时, 这对质数就被称为孪生质数.

It is not known whether there are infinitely many twin primes.



Recently, significant progress has been made on the twin primes question. In 2013, Yitang Zhang (1955–) proved that there is a positive integer d ≤ 70,000,000 such that there are infinitely many pairs of prime numbers that differ by d. 

![Yitang Zhang](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Number%20Theory/Some%20Proofs%20about%20Prime%20Numbers/Yitang%20Zhang.jpg)

(一位数学家, 这在中国比大熊猫还珍惜...)



Work of many other mathematicians in 2013–14 narrowed down the possibilities for d to d ≤ 246. Of course, if the statement holds with d = 2 then there are infinitely many twin primes.
