---
title: L4 QuickSort
tags: 
- Algorithm
categories: 
- Computer Science
mathjax: true
date: 2021-07-21 10:40:58
---


Outline:

* **Inversion**

* **`InsertionSort`**
* **Analysis of `InsertionSort`**

* **`QuickSort`**
* **Analysis of `QuickSort`**

Ref:

* *算法设计与分析(Algorithm design and analysis)* by 黄宇

<!--more-->

# Inversion

* **Definition: Inversion**
  * $<x_i, x_j>$  is an <i>inversion</i> if $x_i > x_j$ , but $i < j$
  * Sorting == Eliminating inversions



# `InsertionSort`

## Worst Case

* <i>Local comparison</i> is done between is done between two adjacent elements
* At most **one** inversion is removed by a <i>local comparison</i>
* There do exist inputs with <i>n(n-1)/2</i> inversions, such as ( n, n-1, ...., 3, 2, 1 ) （最坏情况，inversion最多）
* **The worst-case behavior of any sorting algorithm that remove at most one inversion per key comparison must in $\Omega(n^2)$​​​**

## Average Case

* Computing the average number of inversions in inouts of size n ( n > 1 ):

  * Transpose:
    $$
    x_1, x_2,x_3,\dots,x_{n-1},x_n \\
    x_n,x_{n-1},\dots,x_3,x_2,x_1
    $$
    
  * For any    $i, j\quad(1 \leq j \leq i \leq n)$​ , the inversion $( x_i, x_j )$ is in exactly one sequence in a transpose pair
  * The number of inversions (xi, xj) on <i>n</i> distinct integers is <i>n(n-1)/2</i>
  * So, the average number of inversions in all possible inputs is <i>n(n-1)/4</i>, since exactly <i>n(n-1)/2</i> inversions appear in each transpose pair.
  * **The average behavior of any sorting algorithm that remove at most one inversion per key comparison  must in $\Omega(n^2)$**

# `QuickSort`

* 每次递归，`pivot`的位置一定是对的

## Worst Case: a Paradox

* For a range of <i>k</i> positions, <i>k - 1</i> keys are compared with the pivot( one is vacant )

  * if the pivot is the smallest, than the "large" segment has all the remaining <i>k - 1</i>, and the small segment is empty 最坏情况,每次问题的规模只减少1, 每次PARTITION代价是O(n)

  * If the elements in the array to be sorted has already ascending order( the **Goal** ), then the number os comparison that Partition has to do is:

    $n - 1 + n - 2 + ... + 1 = n(n-1)/2 ∈ O(n^2)$​

  * 考虑到所有输入等概率的情况,最坏情况的出现概率是很低的. 

  所有元素只跟pivot比,左右两边里的任意两两之间没有比过. 这样才能用递归来分析

## Analysis

3种方法

* Guess and Prove 归纳法
* Directly solve
* Indication random variable 

## Space Complexity

* Good news:
  * Partition is in-place  不占用额外的空间
* Bad news:
  * In the worst case, the depth of recursion will be <i>n - 1</i>
  * So, the largest size of recursion stack will be in O(n)
