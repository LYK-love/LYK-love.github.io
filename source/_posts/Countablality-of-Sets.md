---
title: Countablality of Sets
tags:
  - Set Theory
categories: Mathematics
mathjax: true
date: 2023-11-03 22:21:34
---

在数学中, 有限大小的集合很好处理, 但无限大小的集合却并非如此. 本文探讨集合的可数性, 某些无限大小集合是不可数的, 例如全体实数$\mathbb R$和全体有理数$\mathbb R /\ \mathbb Q$.

Ref:

1. [*Concepts of Mathematics* from CMU](https://www.math.cmu.edu/~wgunther/127m12/notes/).

<!--more-->

# Intro

[Source: wiki](https://en.wikipedia.org/wiki/Countable_set)

In [mathematics](https://en.wikipedia.org/wiki/Mathematics), a [set](https://en.wikipedia.org/wiki/Set_(mathematics)) is **countable** if 

1. either it is [finite](https://en.wikipedia.org/wiki/Finite_set) 
2. or it can be made in [one to one correspondence](https://en.wikipedia.org/wiki/One_to_one_correspondence) (or  [bijection](Countably infinite definition	))with the set of [natural numbers](https://en.wikipedia.org/wiki/Natural_number) $\mathbb N$.

一个有限大小的集合必定是可数的. 但无限大小的集合既有可数的, 也有不可数的. 不可数集合是无限大小集合的子集.

有时我们会用"可数集"来指代"可数无穷集", 这样的指代应当是清晰的, 因为集合是否无穷很容易分辨.

# Countably Infinite Sets 	      

[->Source](https://mathinsight.org/definition/countably_infinite)

A set is countably infinite if its elements can be put in **one-to-one correspondence with the set of natural numbers**. That is we can build a [bijection](Countably infinite definition	) between itself and natural numbers

In other words, one can count off all elements in the set in such a way that, **even though the  counting will take forever, you will get to any particular element in a finite amount of time.**



For example, the set of integers {0,1,−1,2,−2,3,−3,…} is clearly infinite.  However, as suggested by the above arrangement,  we can count off all the integers.  Counting off every integer will take forever.  But, if you specify any integer, say −10,234,872,306, we will get to this integer in the counting process in a finite amount of time.

Sometimes, we can just use the term “countable” to mean countably  infinite.  But to stress that we are excluding finite sets, we usually  use the term countably infinite.

Countably infinite is in contrast to [uncountable](https://mathinsight.org/definition/uncountable), which describes a set that is so large, it cannot be counted even if we kept counting forever.

# Uncountable Sets

[->Source](https://mathinsight.org/definition/uncountable)


A set is uncountable if it contains so many elements that they cannot be put in one-to-one correspondence with the set of natural numbers. In other words, there is **no way** that one can count off all elements in the set in such a way that, even though the counting will take forever, **you will get to any particular element in a finite amount of time**.

Uncountable is in contrast to countably infinite or countable.

For example, the set of real numbers in the interval [0,1] is uncountable. There are a continuum of numbers in that interval, and that is too many to be put in a one-to-one correspondence with the natural numbers. One can show using Cantor's diagonal argument(见下文) that for any infinite list of numbers in the interval [0,1], there will always be numbers in [0,1] that are not on the list.



# Theorem: Rational Numbers are Countable

[An easy proof that rational numbers are countable](https://www.homeschoolmath.net/teaching/rational-numbers-countable.php)

Theorem: The [set](https://proofwiki.org/wiki/Definition:Set) $\mathbb Q $ of rational numbers is countable.

Proof:

我们只需证明, 对于全体有理数集合$\mathbb Q$中的任意有理数$x$, 我们可以在有限时间内索引到它.



我们知道, 有理数也就是分数. 我们先证明正有理数的情况, 将全体正有理数$+Q$以如下方式排列:

| -    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | ...  |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 1/1  | 1/2  | 1/3  | 1/4  | 1/5  | 1/6  | 1/7  | ...  |
| 2    | 2/1  | 2/2  | 2/3  | 2/4  | 2/5  | 2/6  | 2/7  | ...  |
| 3    | 3/1  | 3/2  | 3/3  | 3/4  | 3/5  | 3/6  | 3/7  | ...  |
| 4    | 4/1  | 4/2  | 4/3  | 4/4  | 4/5  | 4/6  | 4/7  | ...  |
| 5    | 5/1  | 5/2  | 5/3  | 5/4  | 5/5  | 5/6  | 5/7  | ...  |
| 6    | 6/1  | 6/2  | 6/3  | 6/4  | 6/5  | 6/6  | 6/7  | ...  |
| 7    | 7/1  | 7/2  | 7/3  | 7/4  | 7/5  | 7/6  | 7/7  | ...  |
| ...  | ...  | ...  | ...  | ...  | ...  | ...  | ...  | ...  |



接下来, 我们按照如下箭头的顺序来索引每个分数, 如果遇到重复的数则跳过(见绿色叉叉). 

![Arrangement of Rational Numbers](/Users/lyk/Documents/cache/Arrangement of Rational Numbers.jpg)

因此, 用如上的方式, 我们得到了全体正有理数$+Q$的一个排列:
$$
\frac{1}{1},\frac{2}{1}, \frac{1}{2}, \frac{1}{3}, \frac{3}{1}, \frac{4}{1}, \cdots
$$
对于任意有理数$x$, 我们将其表述成$x=\frac{p}{q}$的形式, 它都处于该列表中(位于第$p$行第$q$列), 我们可以在有限时间内从该序列中索引到$x$, 因此证明了全体正有理数组成的集合是可数的.

***

接着, 你可以把$0$放在该排列的最前面, 将每个正有理数的相反数放到它的后面, 这样就得到了全体有理数$Q$的一个排列:
$$
0, \frac{1}{1}, -\frac{1}{1}, \frac{2}{1}, -\frac{2}{1}, \frac{1}{2}, -\frac{1}{2}, \frac{1}{3}, -\frac{1}{3}, \cdots
$$
因此, 全体有理数组成的集合$Q$是可数的.

***

还可以将表格中正对角线以下的元素全部去掉, 这样剩下的元素就都属于$(0,1]$, 因此证明了$[0,1]$之间的全体有理数集合是可数的.



Georg Cantor showed that the number of real numbers is rigorously larger than a countably infinite set, and the postulate that this number, the so-called "continuum," is equal to aleph-1 is called the continuum hypothesis. Examples of nondenumerable sets include the real, complex, irrational, and transcendental numbers. 

# Theorem: Real Numbers are Uncountable

Theorem: The [set](https://proofwiki.org/wiki/Definition:Set) $\mathbb R$ of real numbers is [uncountable](https://proofwiki.org/wiki/Definition:Uncountable_Set).

Proof:

证明一个集合不可数 <==> 证明该集合和自然数集合$\mathbb N$之间不存在bijction.

> Source: [wiki](https://zh.wikipedia.org/zh-hans/%E4%B8%8D%E5%8F%AF%E6%95%B8%E9%9B%86)
>
> 一个无穷集合和[自然数集](https://zh.wikipedia.org/wiki/自然數集)之间要是不存在一个[双射](https://zh.wikipedia.org/wiki/双射)，那么它就是一个不可数集。集合的不可数性与它的[基数](https://zh.wikipedia.org/wiki/基数_(数学))密切相关：如果一个集合的基数大于[自然数](https://zh.wikipedia.org/wiki/自然数)的基数，那么它就是不可数的。

[Source](https://www.math.cmu.edu/~wgunther/127m12/notes/CSB.pdf)

We will instead show that $(0,1)$ is not countable. This implies the theorem because **if there were a bijection from $\mathbb{R}$ to $\mathbb{N}$, one could compose it with a bijection we have from $(0,1)$ to $\mathbb{R}$, and get that $(0,1)$ is countable.** For example, we can make a bijection between $0 . a_{0,0} a_{0,1} a_{0,2} a_{0,3} a_{0,4} \ldots \in (0,1)$ and $ a_{0,0} a_{0,1} a_{0,2} a_{0,3} a_{0,4} \ldots \in \mathbb R$.



We will go by contradiction. Suppose that $(0,1)$ is countable. Then, fix a bijection $f: \mathbb{N} \rightarrow(0,1)$. Then, for each natural number $n$ we have some decimal sequence that $n$ maps to
$$
\begin{aligned}
& 0 \mapsto 0 . a_{0,0} a_{0,1} a_{0,2} a_{0,3} a_{0,4} \ldots \\
& 1 \mapsto 0 . a_{1,0} a_{1,1} a_{1,2} a_{1,3} a_{1,4} \ldots \\
& 2 \mapsto 0 . a_{2,0} a_{2,1} a_{2,2} a_{2,3} a_{2,4} \ldots \\
& 3 \mapsto 0 . a_{3,0} a_{3,1} a_{3,2} a_{3,3} a_{3,4} \ldots \\
& 4 \mapsto 0 . a_{4,0} a_{4,1} a_{4,2} a_{4,3} a_{4,4} \ldots \\
& \vdots \quad \vdots \quad \\
&
\end{aligned}
$$

What we'd like to show **this is not actually a bijection**. Motivated by the idea that $\mathbb{N}$ is the "smallest" infinity, we must have that $(0,1)$ is "larger" if it's not equal. Therefore, we will try to **argue this is not a surjection**. To do this, we must **find something that the number doesn't hit.**



We denote the $i$ th digit of our new number as $b_i$.  

To define $b_i$, I look at $a_{i, i}$; that is the $i$ th digit of the decimal representation of $f(i)$. If $a_{i, i}$ is not 1 , we will make $b_i$ equal to 1 , and otherwise we will let it be 2 .
$$
\begin{aligned}
& 0 \mapsto 0 . a_{0,0} a_{0,1} a_{0,2} a_{0,3} a_{0,4} \ldots \\
& 1 \mapsto 0 . a_{1,0} a_{1,1} a_{1,2} a_{1,3} a_{1,4} \ldots \\
& 2 \mapsto 0 . a_{2,0} a_{2,1} a_{2,2} a_{2,3} a_{2,4} \ldots \\
& 3 \mapsto 0 . a_{3,0} a_{3,1} a_{3,2} a_{3,3} a_{3,4} \ldots \\
& 4 \mapsto 0 . a_{4,0} a_{4,1} a_{4,2} a_{4,3} a_{4,4} \ldots \\
& \vdots \quad \vdots \\
&
\end{aligned}
$$

As the end we will have defined a sequence $b_0, b_1, b_2, \ldots$ We can read this as a decimal, which we call $b$ :
$$
b:=0 . b_0 b_1 b_2 b_3 b_4 \cdots
$$

We claim **this is not on our list**. For instance, if it were $f(i)=b$ for some $i \in \mathbb{N}$. But, the $i$ th decimal digit of $f(i)$ is different then the $i$ th decimal digit of $b$ by the way we defined $b$, which means they are different numbers.
Thus $b$ is not on our list.

This proof method is called [Cantor's diagonal argument](https://en.wikipedia.org/wiki/Cantor%27s_diagonal_argument).

***

A more specific example([->Source](https://math.stackexchange.com/a/237414)):

Let $f(x)$ be:
$$
\begin{aligned}
& 0 \mapsto 0.12345 \ldots \\
& 1 \mapsto 0.32145 \ldots \\
& 2 \mapsto 0.87654 \ldots \\
& 3 \mapsto 0.28374 \ldots \\
& 4 \mapsto 0.67676 \ldots \\
& \vdots \quad \vdots \\
&
\end{aligned}
$$
Then I create the bew number using the given way.

Since $a_{0,0} = 1$, make $b_{0} = 2$. Since $a_{1,1} = 1$, make $b_{1} = 1$, etc.
$$
b := 0.21111...
$$
This new number, $0.21111...$ is not on my list. It's not the first number because it's different in  the first place, it's not the second number because it's different in  the second place, it's not the third number because it's different in  the third place, it's not the fourth number because it's different in  the fourth place, etc.

# Theorem: Irrational Numbers are Uncountable

Theorem: The [set](https://proofwiki.org/wiki/Definition:Set) $\mathbb R /\ \mathbb Q$ of [irrational numbers](https://proofwiki.org/wiki/Definition:Irrational_Number) is [uncountable](https://proofwiki.org/wiki/Definition:Uncountable_Set).

Proof:

1. From [Real Numbers are Uncountable](https://proofwiki.org/wiki/Real_Numbers_are_Uncountable), $\mathbb R$ is an [uncountable set](https://proofwiki.org/wiki/Definition:Uncountable_Set).
2. From [Rational Numbers are Countably Infinite](https://proofwiki.org/wiki/Rational_Numbers_are_Countably_Infinite) $\mathbb Q$is [countable](https://proofwiki.org/wiki/Definition:Countable_Set).
3. The result follows from [Uncountable Set less Countable Set is Uncountable](https://proofwiki.org/wiki/Uncountable_Set_less_Countable_Set_is_Uncountable).
