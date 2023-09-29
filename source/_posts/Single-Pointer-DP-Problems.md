---
title: Single-Pointer DP Problems
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
date: 2023-09-27 22:53:12
---


Dynamic programming(DP) problems that typically use one pointer. E.g., `Integer[] memo`.

<!--more-->

# House Robber

[198. House Robber](https://leetcode.com/problems/house-robber/)



You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight **without alerting the police***.

 

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
```

**Example 2:**

```
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
```

## Solution

状态空间为`Integer[] memo = new Integer[nums.length]`.

DP有两个方向, 一种是从前向后DP(`memo[i] = dp(i+1)`), 这类问题一般可以表述为和下面类似的形式:

```
从第i天开始能获得的收益 = 第i天当天的收益 + 从第i+1天开始能获得的收益
```



另一种是从后向前DP(`memo[i] = dp(i-1)`), 这类问题一般可以表述为和下面类似的形式:

```
截至第i天能获得的收益 = 第i天当天的收益 + 截至第i-1天能获得的收益
```



这道题的解法属于前者.

 

用`memo[i]`表示从第i间房子开始能抢到的最大值. 当我在第`i`间房子时, 我有两种选择: 抢, 不抢. 而`memo[i]`也就等于: 当天的收益(如果抢的话) + ( `memo[i+1]` or `memo[i+2]`, 取决于第`i`天抢没抢).

```java
memo[i] = Math.max(
	nums[i] + dp(nums, start + 2), //抢, 去下下家.
	dp(nums, i + 1) // 不抢, 去下家
);
```

## Code

```java
public int rob(int[] nums) {
        Integer[] memo = new Integer[nums.length];// memo[i]: 从第i间房子开始, 能抢到的最大值.
        return dp(0,memo,nums);
    }

    private int dp(int start, Integer[] memo, int[] nums)
    {
        if(memo[start] != null)
            ;
        else
        {
            if(start == nums.length - 1)
                memo[start] = nums[start];
            else if( start == nums.length-2)
                memo[start] = Math.max(dp(start+1,memo, nums), nums[start]);
            else
                memo[start] = Math.max(dp(start+1,memo, nums), nums[start] + dp(start+2, memo, nums));
        }
        return memo[start];
    }
```

