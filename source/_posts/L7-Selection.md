---
title: L7 Selection
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-07-23 17:19:01
---


Outline

* Lower bound and **adversary argument**
* Selection - select the *median*
  * Expected linear time
  * Worst-case linear time
* A Lower bound for Finding the Median

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# Lower bound and adversary argument

* Adversary argument： 对一个算法而言是worst-case的input. 
* Adversary strategy: 指导你构造`adversary argument`的策略

## Finding max and min

* 对n个元素，找出最大和最小
  * Brute force： 先n-1次comparison找出最大， 拿出该元素，对其余n-1个元素进行n-2次comparison找出最小

* The strategy

  * Pair up the keys, and do <i>n/2</i> comparisons( if <i>n</i> odd, having E[n] uncompared ) 把数组一分为二，两两比较. 最大元素肯定在大的那边，最小元素肯定在小的那边
  * Doing findMax for larger key set and findMin for small key set respectively( if <i>n</i> odd, E[n] included in both sets )

* Number of comparisons

  * For even <i>n</i>: 
    $$
    n/2 + 2(n/2 - 1) = 3n/2 - 2
    $$

  * For odd n:

  $$
  （n-1）/2 + 2( (n-1)/2 - 1 + 1 ) = \rceil 3n/2 \rceil - 2
  $$

  


现在用`adversary argument`证明这个问题的下界是 $\frac32n - 2$​

### Unit of Information

* Max and Min
  * That *x* is *max* can only be known when it is sure sure that every key other than *x* has <u>lost some comparison</u>
  * That *y* is *min* can only be known when it is sure sure that every key other than *y* has <u>win some comparison</u>
* Each win or loss is counted as one unit of information
  * *Any* algorithm must have at least *2n - 2* units of information to be sure of specifying the *max* and *min*.
  * 因此，算法至少要获取 *2n - 2* 个信息元

### Adversary Strategy

* Construct an input to force the algorithm to do more comparisons as possible *构造一个输入,使得获取*2n - 2* 个信息元需要花费尽可能多的比较

  * To give away as few as possible units of new information with each comparison
    * It can be achieved that 2 units of new information are given away only when the status is N,N
    * It is **always** possible to give adversary response for other status so that at most one new unit of  information is given away, **without any inconsistencies**
    * So, the **Lower bound** is $n/2 + n - 2 $ ( for even n)

  
  $$
  n/2 \times 2 + ( n - 2 ) \times 1 = 2n - 2 (信息元)
  $$
  

  * 对所有算法而言,面对这个(adversary argument的)输入, 要尽可能少地比较,来凑足 2n-2个信息元. 算法最多能进行 $\frac {n}2$ 次信息元为2的比较, 而对于剩下的 n - 2 个信息元,算法只能进行信息元为1的比较

* The principle: let the key win if it never lose, or, let the key lose if it never win, and **change one value if necessary**

  

  

## Finding 2^nd^ max

* Brute force - using FindMax twice
  * $2n-3$ comparisons
* For a better algorithm
  * Collect some useful information from the first FindMax
* Observations
  * The key which **loses to a key other than max**  can not be the 2^nd^ largest key
  * To check "whether you lose to max?"

### Analysis

* Any algorithm that finds *secondLargest* must also find *max* before (  **n - 1** )

* The *secondLargest* can only be in those which lose directly to *max*
* On its path along which bubbling uo to the root of tournament tree, *max* beat $\lceil logn \rceil$ keys at most( 根据锦标赛树的数据结构可以证明 )
* Pick up  *secondLargest* (依然用FindMax)
* Total cost: $ n + \lceil logn \rceil - 2$​

* 下面解释为什么该算法是最优

### Weight Key

* Assigning a weight *w(n)* to each key

  * The initial values are all 1.

* Adversary strategy

  
#### Lower Bound by Adversary: Details

* Note: the sum of weights is always *n*

* Let *x* is *max*, then *x* is the only nonzero weighted key, that is $w(x) = n$​.

* By the adversary rules:
  $$
  w_k(x) \le 2w_{k - 1}(x)
  $$

* So, $K \le \lceil logn\rceil$​ 

  * 注意,之前算法的$\lceil logn\rceil$是从锦标赛树的数学性质得出的, 而这里的$\lceil logn\rceil$是下界证明

* 所以该问题的下界是$ n + \lceil logn \rceil - 2$

## Finding the Median: the Strategy

* Observation
  * If we can partition the problem the set of keys into 2 subsets: S1, S2, such that any key in S1 is smaller that that of S2, the median must located in the set with more elements
    * Adjusting the Rank
* Divide-and-Conquer

### Partitioning: Larger and Smaller

* **average-case O(n)**

* Dividing the array to be considered into two subsets: "small"  and "large", the one with more elements will be processed recursively 运用快排的思想进行分析，只对median所在的那侧进行递归

* 平均情况复杂度分析和快排一样，由于每次只对一侧进行递归， 所以在“所有输入各不相同，所有可能的输入等概率出现”的情况下，平均情况复杂度为：（ 在此情况下pivot在中间 ）
  $$
  n + n/2 + n/4 + \cdots \in O(n)
  $$
  

### Partition improved: the strategy

* **worst-case O(n)**
* 方法和解释见书上

$ W(n) <= 6( \frac n 5 ) + W( \frac n 5 ) + 4r + W(7R + 2)$

* 分析见书上

### Lower Bound by Adversary

#### Crucial Comparison

* A crucial comparison
  * Establishing the relation of some *x* to the median
* Def( for a comparison involving a key *x* )
  * **Crucial Comparison for x**: the first comparison between *x* and *y*, for some *y * >= median, or *x* < *y* for some *y* <= median
  * **Non-Crucial Comparison for x**: the first comparison between *x* and *y*, where *x* > median and  *y* < median, or vise versa

# Lower Bound for Selection Median Problem

* Theorem:

  * Any algorithm to find the **median** of n keys ( for odd n 偶数情况更复杂,但没什么新思想,所以不考虑 ) by comparison of keys must  do at least $3n/2 - 3/2$​​ comparisons in the worst case

* Argument

  * Adversary strategy构造这样一个输入: 中位数在最后, 而前N-1个元素,在两两比较时,比较的结果不能与之前的结果构成传递关系( 即 不会出现x > y, y > z,使得你可以节省一次x和z的比较 ), 

    * 算法对前N - 1个元素,要比较至少 ( N-1 )/ 2 次( 即两两都是没比过的元素进行比较,一共 (N - 1 )/ 2  组 ), 而最后一个树(它是中位数)需要和前N-1个元素比较,这就是最坏情况

    

* $ \frac {n - 1}  2 + n - 1 = \frac {3n} 2 - \frac 3 2$

