---
title: Number of Islands
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
date: 2023-09-27 22:32:18
---

Problems like "given an 2D binary grid `grid` which represents a map of land and water, return *the number of islands*, an island is XXXX".


* [200. Number of Islandsopen](https://leetcode.com/problems/number-of-islands/)
* [1020. Number of Enclavesopen](https://leetcode.com/problems/number-of-enclaves/)
* [1254. Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/)
* [1905. Count Sub Islandsopen](https://leetcode.com/problems/count-sub-islands/)
* [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)

Ref: [labuladong 题解](https://labuladong.github.io/algo/di-san-zha-24031/bao-li-sou-96f79/yi-wen-mia-4f482/)

<!--more-->

# Number of Islands

[200. Number of Islands](https://leetcode.com/problems/number-of-islands/)



Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return *the number of islands*.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

**Example 1:**

```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

**Example 2:**

```
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

# Solution

岛屿问题的关键是"如何寻找岛屿", 这统统可以用DFS解决. 

比如说题目给你输入下面这个 `grid` 有四片岛屿，算法应该返回 4：

![img](https://labuladong.github.io/algo/images/%E5%B2%9B%E5%B1%BF/1.jpg)

记岛屿数量为`int cnt`. 我们的做法是: 每遇到一块新的陆地(land), 就将其标记为一个岛屿(`cnt++`), 然后对这个陆地进行DFS. 

```java
public int numIslands(char[][] grid) {
        int M = grid.length, N = grid[0].length;

        int cnt = 0;
        for(int row = 0; row < M; row++)
            for(int col = 0; col < N; col++)
            {
                if(isLand(grid[row][col]))
                {
                    cnt++;
                    dfs_and_mark(row,col, grid);
                }
            }
        return cnt;

    }
```



DFS的迭代项是该岛屿四周的方格, 每当DFS遇到一个land, 就把它淹没, 变成water. 这样一来, 对每个新land的DFS都能完全消除掉一个岛屿:

```java
private void dfs_and_mark(int row, int col, char[][] grid)
    {
        int M = grid.length, N = grid[0].length;

        if(isLand(grid[row][col]))
        {
            flood(row,col,grid);//Turn this land into water.
            
            //Then apply this method to surrounding grid. Notice the limit of grid's boundary
            if(row>=1) dfs_and_mark(row-1,col,grid);
            if(row <= M-2) dfs_and_mark(row+1,col,grid);
            if(col>=1) dfs_and_mark(row,col-1,grid);
            if(col <= N-2) dfs_and_mark(row,col+1,grid);
        }
    }
```

## Code

```java
public int numIslands(char[][] grid) {
        int M = grid.length, N = grid[0].length;

        int cnt = 0;
        for(int row = 0; row < M; row++)
            for(int col = 0; col < N; col++)
            {
                if(isLand(grid[row][col]))
                {
                    cnt++;
                    dfs_and_mark(row,col, grid);
                }
            }
        return cnt;

    }

    private boolean isLand(char ch)
    {
        return ch == '1';
    }

    private void flood(int row, int col, char[][] grid)
    {
        grid[row][col] = '0';
    }

    private void dfs_and_mark(int row, int col, char[][] grid)
    {
        int M = grid.length, N = grid[0].length;

        if(isLand(grid[row][col]))
        {
            flood(row,col,grid);//Turn this land into water.

            //Then apply this method to surrounding grid. Notice the limit of grid's boundary
            if(row>=1) dfs_and_mark(row-1,col,grid);
            if(row <= M-2) dfs_and_mark(row+1,col,grid);
            if(col>=1) dfs_and_mark(row,col-1,grid);
            if(col <= N-2) dfs_and_mark(row,col+1,grid);
        }
    }
```

