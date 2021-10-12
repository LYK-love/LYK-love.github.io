---
title: L9 Hashing
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-08-02 08:47:15
---


Outline:

* The searching problem
  * The ambition of hashing
* Hashing
  * Brute force table: direct addressing
  * Basic idea of hashing
* Collision Handling for Hashing
  * Closed address hashing
  * Open address hashing
* Amortized Analysis
  * Array doubling

<!--more-->

# The searching problem

## Cost for Searching

* Brute force
  * $O(n)$
* Balanced BST
  * $O(logn)$
* **Hashing --- almost constant time**
  * $O( 1 + \alpha)$
* "Mission impossible"
  * $O(1)$​

# Hashing

* universe of keys: 所有可能的键
* actual keys：实际的键

## Brute force table: direct addressing

*  给所有 universe keys 都分配一个位置。 用超多的空间

## Basic idea of hashing

* Index distribution
  * Hash Function $H(x) = k$
* Collision handling

# Collision Handling for Hashing

* 规定*m*为哈希表大小， *n*为表中元素个数

## Closed address hashing

*  也称为Chaining
  * Each address is a **linked list**
  * Insert to the head of the list( 链表不是常数时间寻址 )

* Assumption - simple uniform hashing
  * For $j=0,1,2,\dots, m-1$​​, the average length of the list at $E[j]$​​​ is *n/m*

### Unsuccessful Search

* The average cost for an unsuccessful search

  * Any key that is not in the table is equally likely to hash to any of the *m* address

  * Total cost $\Theta(1+n/m)$​

    * The average cost to determine that the key is not in the $E[h(k)]$ is the cost to search to the end of the list, which is *n/m*

    * *1*是算哈希， *n/m*是链表平均长度

### Successful Search

* For successful search( assuming that $x_i$ is the $i^{th}$  element inserted into the table, $i=1,2,\dots,n$ )

  * For each *i*, the probability of that $x_i$​ is searched is *1/n*

  * For a specific $x_i$​​, the number of elements examined in a successful search is *t+1*, where *t* is the number of elements inserted into the same list as $x_i$, **after** $x_i$​​​​​​ has been inserted(即链表里在该元素之前的元素的个数). 
    $$
    1 + \frac 1 n \sum\limits_{i=1}^{n}{(1+t)}
    $$
    
  * And for any *j*, the probability of that $x_j$ is inserted into the same list of $x_i$ is *1/m*. So, the cost is:
  
    
    $$
    1 + \frac 1 n \sum\limits_{j=i+1}^{n}{\frac 1 m}
    $$
  
* The average cost of a successful search:

  * Define $\alpha = n/m$ as *load factor*, The average cost of a successful search is:
    $$
    \frac 1 n { ( 1 + \sum\limits_{j = i + 1}^n {\frac 1 m} )} = 1 + \frac 1 {nm} {\sum\limits_{i = 1}^n {(n-i)}} = 1 + \frac 1 {nm} \sum_{i=1}^{n-1}i = 1 + \frac {n-1} {2m} = 1 + \frac \alpha 2 - \frac \alpha {2n} = \Theta( 1 + \alpha )
    $$
    



## Open address hashing

* All elements  are stored in the  hash table
  * No linked list is used
  * The *load factor* $\alpha$ can't be larger than 1
* Collision is settled by "rehashing"
  * A function is used to get a new hashing address for each collided address
    * The hash table slots are *probed* successively, until a valid location is found.
* Th probe sequence can be seen as a permutation of $(0,1,2,\dots,m-1)$

### Commonly Used Probing

* Linear probing:

  * Given an ordinary hash function *h'*, which is called an auxiliary hash function, the hash function is:( clustering may occur )
    $$
    h(k,i) = (h'(k)+i)\quad mod \quad m \quad ( i = 0,1, \dots, m-1 )
    $$

* Quadratic Probing:

  * Given auxiliary function *h'* and nonzero auxiliary constant $c_1$ and $c_2$​, the hash function is: (secondary clustering may occur)
    $$
    h(k,i) = (h'(k)+c_1 i + c_2 i^2)\quad mod \quad m \quad ( i = 0,1, \dots, m-1
    $$
    



* Double hashing:

  * Given auxiliary functions *h_1* and *h_2*, the hash function is:
    $$
    h(k,i) = (h_1(k)+i h_2(k))\quad mod \quad m \quad ( i = 0,1, \dots, m-1
    $$
    

#### Equally Likely Permutations

* Assumption
  * Each key is equally likely to have any of the *m!* permutations of $(1,2,\dots,m)$​ as​ its probe sequence
* Note
  * Both linear and quadratic probing have only *m* distinct probe sequence, as determined by the first probe.(m个格子的合法排列)

### Unsuccessful Search

* The average number of probes in an unsuccessful search is at most $1/(1-\alpha )$​ $(\alpha = n/m < 1)$

  * Assuming uniform hashing

    The probability of  the first probed position being  occupied is *n/m*, and that of the $j^{th}(j>1)$ position occupied is $\frac {n-j+1}{m-j+1}$​​. So the probability of the number of probed no less than *i* will be:(概率论知识)
    $$
    \frac n m \cdot \frac {n-1} {m-1} \cdot {n-1} {m-2} \cdots \cdot \frac {n-i+2} {m-i+2} \le { (\frac n m )}^{i-1} = \alpha ^{i-1}
    $$
    

    The average number of probe is: $\sum\limits _{i=1} ^ \infty {\alpha ^ {i - 1}} = \sum\limits _{i=0} ^ \infty {\alpha ^ {i }} = \frac {1} {1-\alpha}$​ （其实上界是m，因为一共m个格子。 这里做了放大，但这个放大得到的上界还是比较 tight的）

### Successful Search

* The average number of probes in an successful search is at most $\frac  1 \alpha ln \frac 1 {1-\alpha}$ ($\alpha = n /m <1$​)​

  * Assuming uniform hashing

    To search for the $(i+1)^{th}$ inserted element in the table, the cost is the same as that for inserting it when there are just *i* elements in the table. At that time, $\alpha = \frac i m$. So the cost is( 用 unsuccessful的结论 )  $\frac 1 {1- \frac i m}$ = $\frac m {m-i}$​,
    $$
    \frac 1 n \sum\limits_{i=0}^{n-1} \frac m {m-i} = \frac m n \sum\limits _{i=0}^{n-1} \frac 1 {m-i} = \frac 1 \alpha \sum\limits _{i=m-n+1}^{m} \frac 1 i \le \frac 1 \alpha \int _{m-n} ^m {\frac {dx} x} = \frac 1 \alpha ln \frac m {m-n} = \frac 1 \alpha ln \frac 1 {1-\alpha}
    $$
    

# Amortized Analysis

## Array doubling

*  顾名思义

### Worst-case Analysis

* For *n* execution of insertion operations

  * Note that the expansion is required during the $i^{th}$​ operation only if $i = 2^{th}$​, and the cost of the $i^{th}$​ operation $ c_i = i $​( if *i - 1* is exactly the power of 2 ) or $c_i = 1 $ ​(otherwise)​

  So the total cost is: $\sum\limits _{i=1} ^n c_{i} \le n + \sum\limits _{j=0} ^{\lfloor logn \rfloor} 2^j < n + 2n = 3n$

### Amortized Analysis- Why?

* Unusually expensive operations
* Relation between expensive and usual operations
  * Each piece of the doubling cost corresponds to some previous insert

### Amortized Analysis- How?

* **Amortized equation:**

  *amortized cost = actual cost + accounting cost*

* Design goals for accounting cost

  * In **any** legal sequence of operations, the sum of the accounting costs is **nonnegative**
  * The amortized cost of each operation is fairly regular, in spite of the wide fluctuate possible for the actual cost of individual operations

* Examples:

  1. Multi-pop Stacks

  |           | Amortized | Actual | Accounting |
  | --------- | --------- | ------ | ---------- |
  | Push      | 2         | 1      | 1          |
  | Multi-pop | 0         | k      | -k         |

    * 相当于每个元素在出生的时候就要记下它死亡的时候的代价

  2. Binary Counter

  |       | Amortized | Actual | Account |
  | ----- | --------- | ------ | ------- |
  | Set 1 | 2         | 1      | 1       |
  | Set 0 | 0         | 1      | -1      |

  

### Amortized Analysis - Array Doubling

|                     | Amortized | Actual | Account |
| ------------------- | --------- | ------ | ------- |
| Insert ( normal )   | 3         | 1      | 2       |
| Insert ( doubling ) | 3         | k+1    | -k + 2  |

* *k* is the number of elements upon doubling
* *-k+2*: 清除前k个元素的代价, 新插入的元素要付出2的代价 

