---
title: Gas Station Problem
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
mathjax: true
date: 2023-08-21 21:13:07
---

There are `n` gas stations along a circular route, where the amount of gas at the `ith` station is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from the `ith` station to its next `(i + 1)th` station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays `gas` and `cost`, return *the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return* `-1`. If there exists a solution, it is **guaranteed** to be **unique**



[134. Gas Station](https://leetcode.com/problems/gas-station/)

<!--more-->

# Solution

枚举所有可能, 并通过寻找规律来去除冗余计算.



我们发现:

**如果选择站点`i`作为起点「恰好」无法走到站点`j`，那么`i`和`j`中间的任意站点`k`都不可能作为起点**.



**证明:**

假设`tank`记录当前油箱中的油量，如果从站点`i`出发（`tank = 0`），走到`j`时恰好出现`tank < 0`的情况，那说明走到`i, j`之间的任意站点`k`时都满足`tank >= 0`. 

Given sequence: $\mathrm{Tank}(i), \cdots, \mathrm{Tank}(k), \cdots, \mathrm{Tank}(j)$
$$
\forall k \in \{ i+1, ..., j-1\}, \ \mathrm{Tank}(k)\ge0
$$
序列从k开始为: 
$$
\mathrm{Tank}(k) \ge 0, \mathrm{Tank}(k+1) \ge 0, \cdots, \mathrm{Tank}(j) < 0
$$
而如果以k作为起点, 相当于在站点k时tank=0, 则序列从k开始变成:
$$
0, \mathrm{Tank}(k+1) - \mathrm{Tank}(k), \cdots, \cdots, \mathrm{Tank}(j) - \mathrm{Tank}(k)
$$
在新序列的每一个站点的油箱容量都比之前少. 已知$\mathrm{Tank}(j) < 0$, 则必定有$\mathrm{Tank}(j) - \mathrm{Tank}(k) \lt 0$. 因此$\forall k \in \{ i+1, ..., j-1\}$, $k$不可能作为起点.



此外, $j$也不能作为起点. 因为既然`j`是第一个恰好出现`tank < 0`的点, 必定有`gas[j-1] - cost[j-1] < 0`. 否则有`gas[j] - cost[j] >= 0`且`tank[j]<0`, 此时点j-1满足:

```
tank[j-1] = tank[i] - (gas[j-1] - cost[j-1] ) <= tank[j] < 0
```

与前提矛盾.



因此, 下一个可能的起始站点是`j+1`.

# Code

如果总油量小于总的消耗, 那么起点从0一直遍历到N-1都不符合条件. 因此预先排除掉这个无解的情况.

```java
public int canCompleteCircuit(int[] gas, int[] cost) {
        int N = gas.length;

        int sum = 0;
        for( int i = 0; i < N; i++ )
            sum += gas[i] - cost[i];
        if(sum < 0) // 总油量小于总的消耗，无解
            return -1;

        int start = 0;
        int tank = 0;
        for( int i = 0; i < N; i++ )
        {
            tank += gas[i] - cost[i];
            if(tank < 0)
            {
                // 
                // 所以可能的起点应该是 i + 1 
                start = i+1;
                tank=0;
                
                if( start == N-1 )
                    start = 0; //无法从 start 走到 N-1, 下一个可能的起点是N. 由于路线是循环的, 站点N也就是站点0.
            }
        }
        return start;
    }
```

* Complexity: $O(N)$. $N$ = number of gas stations.
