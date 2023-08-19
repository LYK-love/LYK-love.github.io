---
title: L6 MergeSort
tags: 
- Algorithm
categories: 
- Computer Science
date: 2021-07-22 15:52:17
---


Oultline

* `MergeSort`
  * Worst-case analysis of `MergeSort`
  * More than sort: the `MergeSort` D&C
* Lower Bounds for <i>comparison-based sorting</i> ( `nlogn` )
  * Worst-case ( `Omega(nlogn)` )
  * Average-case (`nlogn - 1.443n` )

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# `MergeSort`





## Space Complexity of Merge

* A algorithm is "in space"
  * If the extra space it has to use is in Omega(1)
* Merge is **not** an in place algorithm
  * Since it needs O(n) extra space to store the merged sequence during the merging process



## Worst  case Complexity of `MergeSort`

* Observations
  * Worst case is that comparison is conducted between A[k-1] and B[m-1]
  * After each comparison, one element is inserted into Array C, **at least**
  * After entering Array C ,  an element will never be compared again
  * After last comparison, at least two elements( the two just compared ) have not yet been moved to Array C. So at most <i>n - 1</i> comparisons are done.
* **In worst case, <i>n - 1</i> comparisons are done, where  n = k + m**

## Optimality of Merge

* Any algorithm to merge two sorted arrays, each containing k = m = n/2 entries, by comparison of keys, does **at least**(如果算法笨的话可能有重复比较)  <i>n - 1</i> comparisons **in the worst case**.

  * Choose keys so that:

    b0 < a0 < b1 < a1 < ... < bi < ai< bi+1,..., < bm-1 < ak-1

  * Then the algorithm must  compare ai with bi for every i in [ 0, m - 1 ], and must compare ai with bi+1 for every i in [0, m - 1], so there are <i>n - 1</i> comparisons

* 先考虑最好情况,也就是两边数组大小不一样的时候,一个数组全部比完了,那么另一个数组的剩余部分就在这次比较后全部插入辅助数组中, 比较次数小于 <i>n - 1</i>

*  反之,最坏情况就是"其中一个数组比完了"这个情况不发生,也就是两个数组一直比到最后, 也就是两个数组的最后一个元素相互比较( "comparison is conducted between A[k-1] and B[m-1]" ), 这就要求k = m = n/2 

* 可能有人会疑惑, 如果两数组大小极度不均衡,但是较小数组的最后一个元素远大于较大数组的所有元素,这不也是比到最后吗? 也是 <i>n - 1 </i> 吗? 为什么最坏情况的构造里, 还要要求 k = m = n/2 呢? 

  * 因为对于这种情况,对于较小的数组,完全可以用折半查找来插入,不需要归并了.

  

## Worst case Analysis of `MergeSort`

* The recurrence equation for `MergeSort`
  * `W(n) = W( floor( n/2 ) ) + W( cell( n/2 ) ) + n - 1 (或者O(n))`
  * W (1) = 0
* The <i>Master Theorem</i> applies for the equation, so:
  * **W(n) ∈ `Omega(nlogn)`**
* 精细分析, 得出 <i>W(n) = nlogn - ( alpha - log alpha )n + 1</i>
  * <i>cell( nlogn  - n + 1 ) <= W(n) <= cell( nlogn - 0.914n)</i>

## The `MergeSort` D&C

* Counting the number of inversions

  * Brute force: O(n2)  蛮力做法
  * Can we use divide & conquer
    * In `O(nlogn)` => combination in O(n)

* `MergeSort` as the **carrier ** 用归并排序做

  * Sorted subarrays

    * A[ 0... k-1] and B[ 0 ... m-1 ]

  * Compare the <i>left</i> and the <i>right</i> elements

    * A[i] vs. B[j]

    

    * if A[i] > B[j]

      * (i,j) is an inversion

      * For all i'  > j

        ( i' , j) are inversions ( i' > i )

      * B[j] is selected

    * if A[i]] < B[j]

      * No inversions found
      * A[i] is selected

# Lower Bounds for <i>comparison-based sorting</i>

* Upper bound, e.g., **worst-case cost**  给定一个算法，输入不同，复杂度有一个上界（比如worst-case）
  * For **any** possible input, the cost of the **specific** algorithm A is no more than the <i>upper bound</i>
    * <i>Max{ Cost( i ) | i is an input }</i>
* Lower bound, e.g., comparison-based sorting  比如，对于所有可能的算法，每个算法都有一个worst-case, 这是个上界，对所有上界取下界,就是worst-case的下界。相应的， 所有可能的算法的所有可能的期望值，也就是average-case复杂度，的下界，就是average-case复杂度的下界
  * For **any** possible( comparison-based ) sorting algorithm A, the worst-case is no less than the <i>lower bound</i>
    * <i>Min{ Worst-case(a) | a is an algorithm }</i>

## Decision Tree for Sorting

* Decision tree is a **2-tree**( assuming no same keys )
* The action of Sort on a particular input corresponds to following on path in its decision tree from the root to leaf associated to the specific output
* Decision tree  是刻画所有 <i>comparison-based</i> 的排序的数学工具

## Characterizing the Decision Tree

* For a sequence of <i>n</i> distinct elements, there are <i>n!</i> different permutation

  * 叶节点是所有可能的输出,这是n个输入元素的所有可能的排列,因此是n!

  * So, the decision tree has at least <i>n!</i> leaves, and exactly n! leaves can be reached from the root
  * So, for the purpose of lower bounds evaluation, we use trees with exactly n! leaves.

* The number of comparison done in the **worst case** is the **height** of the tree

* The **average** number of comparison done is the **average** of lengths of all paths from the root  to a leaf.

* 变成了离散数学问题

## Lower Bound for Worst Case

* **Theorem**: Any algorithm to sort <i>n</i> items by comparisons of keys must do at least `cell(log n!)`. or approximately `cell(  nlogn - 1.443n)`, key comparisons in the worst case.
  * Lemma: let <i>L</i> be the number of leaves in a binary tree and h be its height. Then L <= 2^h   可用归纳法证明
    * 即高度为h，  h >= log L , L = n！,   所以  h >= log( n! )
  * log( n! ) >= ... >= log( (n/2)^ (n/2) ) = n/2log(n/2) ∈ **Omega( nlogn )**
* 因此，worst-case的下界为`nlogn`

## External Path Length( EPL )

* **EPL --- sum of path length to every leaf**
  * The  EPL <i>t</i> is recursively defined as follows:
  * [Base case] 0 for a  single external node
  * [Recursion] <i>t</i> is non-leaf with sub-trees <i>L</i> and <i>R</i>, then the sum of:
    * The external path length of <i>L</i>
    * the number of external node of <i>L</i> ( 每个完整的树作为子树时,节点的深度都要下沉1,所以递归合并时每个叶节点对应的路径长度都要加一 )
    * The external path length of <i>R</i>
    * the number of external node of <i>R</i>

## Lower Bound for Average Behavior

*  Since a decision tree with <i>L</i> leaves is a 2-tree,  the average path length from the root to leaf is <i>epl / L</i>
  * Recall that **<i>epl</i> >= <i>L log( L )</i>**
  * 每个输出对应的概率是 1 / L , 而所有代价的总和是<i>epl</i>, 所以平均情况复杂度在所有可能的输入等概率的前提下,是 <i>epl/L</i>, 因此求average case的下界,就是求<i>epl</i>的下界
* **Theorem**: The average number of comparisons done by an algorithm to sort <i>n</i> items by comparison of keys is at least <i>log(n!)</i>, which is about <i> nlogn - 1.443n </i>



* More Balanced 2-tree, Less EPL
  * 设一棵 决策树有两个节点,高度分别为h , k, h - k > 1( 即该树不平衡 ).  高度为h的节点有两个叶节点, 高度k的节点没有叶节点( 由于是2-tree, 不可能只有一个叶子节点 )
  * Assuming that <i>h - k > 1</i>>, when calculating <i>epl</i> , h + h + k is replaced by<i> ( h - 1 ) + 2( k + 1 )</i>. the net change in <i>epl</i> is k - h + 1 < 0, that is , the <i>epl</i> decreases
  * 因此,求<i>epl</i>的下界,就是求最平衡的树的<i>epl</i>, 最平衡的二叉树就是`完美二叉树. 由此可证明:  **<i>epl</i> >= <i>L log( L )</i>**

# `MergeSort` Has Optimal Average Performance

* The **average** number of comparisons done by an algorithm to sort <i>n</i> items by comparison of keys is at least about <i>nlogn - 1.443n</i>
* The **worst** complexity of `MergeSort` is in `Omega(nlogn)`( 之前已证 )
* So, `MergeSort` is optimal as for its average performance 
  * 首先, 归并排序的worst-case是`nlogn`, 而average-case必定小于等于worst-case, 即 `MergeSort`的average=case的上界是`nlogn`. 作为一个comparison sorting, 由于comparison sorting的average-case的下界是`nlogn`. 因此`MergeSort`的average-case的下界是`nlogn`. 夹逼得出, 所以`MergeSort`的average-case就是`nlog`级别
