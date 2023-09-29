---
title: Double-Pointer DP Problems
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
date: 2023-09-26 21:23:59
---

Dynamic programming(DP) problems that typically use two pointers. E.g., `Integer[][] memo`.

* Edit Distance
* Longest Common Subsequence

<!--more-->

# Edit Distance

[72. Edit Distance](https://leetcode.com/problems/edit-distance/)

Given two strings `s1` and `s2`, return *the minimum number of operations required to convert `s1` to `s2`*.

You have the following three operations permitted on `s1`:

- Insert a character
- Remove a character
- Replace a character

**Example 1:**

```txt
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
```

**Example 2:**

```txt
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
```

## Solution

解决两个字符串的动态规划问题, 一般都是用两个指针 `m,n ` 分别指向两个字符串的最后, 然后一步步往前走, 缩小问题的规模.

* 状态空间: `Integer[][] memo = new Integer[M+1][N+1]`.
* `m = s1.length()`
* `n = s2.length()`
* `memo[m][n]`: m位的s1 和 n位的s2 的最小编辑距离.

```java
public int minDistance(String s1, String s2) {
        int M = s1.length(), N = s2.length();
        Integer[][] memo = new Integer[M+1][N+1]; //定义：s1[0, .., M-1] 和 s2[0, .., N-1] 的最小编辑距离是 memo[M][N]
        return dp(M,N, memo, s1,s2);
}
```



## DP process

考虑两个长为m, n的字符串s1[0,1,...,m-1], s2[0,1,...,m-1], 它们的末尾字符分别是`s1[m-1]`, `s2[n-1]`.

**Note: 这里的m,n是字符串长度, 因此在用于索引字符时要-1.**



「状态」就是指针 `m, n` 的位置, 根据末尾字符是否相等, 每个状态一或三种选择:

```python
if s1[m-1] == s2[n-1]:
    啥都别做（skip）
    m, n 同时向前移动
else:
    三选一：
        插入（insert）
        删除（remove）
        替换（replace）
```



* skip: 以`exection -> execution (skip)`为例. 原本m=8, n=9. 可以两边都往左跳4位, 直到m=4, n=5 (`s1 = "exec", s2 = "execu"`). 因此skip会导致`s1`, `s2` 均向左缩减一位:

  ```java
  memo[m][n] = dp(m-1,n-1,memo,s1,s2); //skip
  ```

* insert: 以`exection -> execution (insert 'u')`为例. 原本m=4, n=5 (`s1= "exec"`, `s2 = "execu"`), 那么插入后只需考虑"exec"和"exec", 即m=4, n=4. 因此insert会导致`s2`向左缩减一位:

  ```java
  memo[m][n] = dp(m,n-1,memo,s1,s2) + 1; //insert
  ```

* remove: 以`rose -> ros (remove 'e')`为例. 原本m=4, n =3 (`s1= "rose"`, `s2 = "ros"`), 那么删除后只需考虑"ros"和"ros", 即m=3, n=3. 因此remove会导致`s1`向左缩减一位:

  ```java
  memo[m][n] = dp(m-1,n, memo, s1,s2) + 1; //remove
  ```

* replace: 以`horse -> rorse (replace 'h' with 'r')`为例. 原本m=1, n =1 (`s1= "h"`, `s2 = "r"`), 那么删除后只需考虑""和"", 即m=0, n=0. 因此replace会导致`s1`, `s2` 均向左缩减一位:

  ```java
  memo[m][n] = dp(m-1,n-1, memo, s1,s2) + 1; //replace
  ```

## Proof

DP可以解出Edit Distance的答案, 但如何证明DP得到的答案是最短的Edit Distance?

Proof:

1. 假设Edit Distance有一个最优解x, 那么x一定可以用DP表示. 因为x的每一步都可以对应到DP中的一个动作.
2. DP必定能得到一个Edit Distance的解y.
3. 所以 x == y.

这个证明很粗糙, 之后查文献改进.

## Code

```java
//用两个指针 i, j 分别指向两个字符串的最后，然后一步步往前移动，缩小问题的规模。
    public int minDistance(String s1, String s2) {
        int M = s1.length(), N = s2.length();
        Integer[][] memo = new Integer[M+1][N+1]; //定义：s1[0, .., M-1] 和 s2[0, .., N-1] 的最小编辑距离是 memo[M][N]
        return dp(M,N, memo, s1,s2);
    }

    /**
     * memo[m][n]: m位的s1 和 n位的s2 的最小编辑距离.
     * m = s1.length()
     * n = s2.length()
     */
    private int dp(int m, int n, Integer[][] memo, String s1, String s2)
    {
        if(memo[m][n] != null)
            ;
        else
        {
            if(m==0)//s1.length() == 0
                memo[m][n] = n; // insert * n
            else if (n==0)//s2.length() == 0
                memo[m][n] = m; // remove * m
            else
            {
                //m,n是字符串长度, 因此在用于索引字符时要-1.
                if( s1.charAt(m-1) == s2.charAt(n-1) )
                    memo[m][n] = dp(m-1,n-1,memo,s1,s2); //skip
                else
                {
                    memo[m][n] = min(
                            dp(m,n-1,memo,s1,s2),//insert
                            dp(m-1,n, memo, s1,s2),//remove
                            dp(m-1,n-1,memo,s1,s2)//replace
                    )+1;
                }
            }
        }
        return memo[m][n];
    }

    int min(int a, int b, int c){
        return Math.min(a, Math.min(b, c));
    }
```



# Longest Common Subsequence

[1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)

Given two strings `text1` and `text2`, return *the length of their longest **common subsequence**.* If there is no **common subsequence**, return `0`.

A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted **without changing the relative order** of the remaining characters.

- For example, `"ace"` is a subsequence of `"abcde"`.

A **common subsequence** of two strings is a subsequence that is common to both strings.

## Solution

Longest Common Subsequence(最长共同子序列)和 [72. 编辑距离](https://leetcode.com/problems/edit-distance) 同为经典的双字符串动态规划问题. 两个指针 `i, j` 在两个字符串上游走, 这就是"状态"; 字符串中的每个字符都有两种"选择", 要么在 `lcs` 中, 要么不在.

状态空间: `Integer[][] memo = new Integer[M+1][N+1]`.

```java
public int minDistance(String s1, String s2) {

        int M = s1.length(), N =  s2.length();
        int lcs = longestCommonSubsequence(s1,s2);

        int res = (M - lcs) + (N - lcs);
        return res;
}
```



## DP process

考虑两个长为m, n的字符串s1[0,1,...,m-1], s2[0,1,...,m-1], 它们的末尾字符分别是`s1[m-1]`, `s2[n-1]`.

如果s1, s2的末尾字符相等, 那么该字符一定在lcs中, 我们只需求s1[0,1,...,m-2], s2[0,1,...,m-2]的lcs长度, 然后相加: 

```java
memo[m][n] = memo[m-1][n-1] +1;
```





如果s1, s2的末尾字符不相等, 那么s1[m-1], s2[n-1]至少有一个不在lcs中(仔细考虑这一点), 所以只需求`memo[m-1][n]`, `memo[m][n-1]`的最大值.

```java
memo[m][n] = Math.max(memo[m-1][n], memo[m][n-1]);
```

## Code

```java
public int minDistance(String s1, String s2) {

        int M = s1.length(), N =  s2.length();
        int lcs = longestCommonSubsequence(s1,s2);

        int res = (M - lcs) + (N - lcs);
        return res;
    }

    /**
     * ongest Common Subsequence(最长共同子序列)和 [72. 编辑距离](https://leetcode.com/problems/edit-distance) 同为经典的双字符串动态规划问题.
     * 两个指针 `i, j` 在两个字符串上游走, 这就是"状态";
     * 字符串中的每个字符都有两种"选择", 要么在 `lcs` 中, 要么不在.
     */
    int longestCommonSubsequence(String s1, String s2)
    {
        int M = s1.length(), N =  s2.length();
        if(M==0 || N==0) return 0;

        Integer[][] memo = new Integer[M+1][N+1]; //memo[m][n]: s1[0,1,...,m-1]和 s2[0,1,...,n-1]的lcs的长度.
        return dp(M, N, memo, s1, s2);
    }

    private int dp(int m, int n, Integer[][] memo, String s1, String s2)
    {
        if(memo[m][n] != null)
            ;
        else
        {
            if(m==0 || n ==0)
                memo[m][n] = 0;//如果s1或者s2长度为0, 则lcs长度自然就是0
            else
            {
                //m,n是字符串长度, 因此在用于索引字符时要-1.
                if(s1.charAt(m-1) == s2.charAt(n-1))//如果末尾字符s1[m-1]和s2[n-1]相等, 那么s1[m-1]和s2[n-1]必然在lcs中
                    memo[m][n] = dp(m-1,n-1,memo,s1,s2) + 1;
                else
                    memo[m][n] = Math.max(
                            dp(m-1,n,memo,s1,s2),
                            dp(m,n-1,memo,s1,s2)
                    );//如果末尾字符s1[m-1]和s2[n-1]相等, 那么s1[m-1]和s2[n-1]至少有一个不在lcs中
            }
        }

        return memo[m][n];
    }
```
