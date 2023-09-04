---
title: Dungeon Game
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
---

The demons had captured the princess and imprisoned her in **the bottom-right corner** of a `dungeon`. The `dungeon` consists of `m x n` rooms laid out in a 2D grid. Our valiant knight was initially positioned in **the top-left room** and must fight his way through `dungeon` to rescue the princess.

<!--more-->

The knight has an initial health point represented by a positive integer. If at any point his health point drops to `0` or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only **rightward** or **downward** in each step.

Return *the knight's minimum initial health so that he can rescue the princess*.

**Note** that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

[174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)



**Example 1:**

![dungeon-grid-1](https://assets.leetcode.com/uploads/2021/03/13/dungeon-grid-1.jpg)

```
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
```

**Example 2:**

```
Input: dungeon = [[0]]
Output: 1
```

# Solution

这是一个典型的动态规划(DP)问题, 先规定几个变量:

```java
int minimumHP; //进入当前房间所需的初始生命值
int minimumHPForNextRoom; //进入下一个房间所需的初始生命值
int currentRoomValue = dungeon[row][col]; //当前房间的魔法具有的加/减血 效果
```

显然有: minimum HP + currentRoomValue == minimum HP for next room

> 翻译: 进入当前房间所需的最小初始生命值 + 当前房间的魔法具有的加/减血 效果 = 进入下一个房间所需的最小初始生命值

因此有: **minimum HP = minimum HP for next room - currentRoomValue**

> 翻译: 进入当前房间所需的最小初始生命值 = 进入下一个房间所需的最小初始生命值 - 当前房间的魔法具有的加/减血 效果

这就是我们的循环不变式. 

**Note:** the knight has an initial health point represented by a positive integer. So we must have: **minimum HP >= 1**.



建立DP数组`memo[][]`, `memo[row][col]`:= 进入坐标为`[row][col]`的房间所需的最小初始生命值. 问题的答案就是`memo[0][0]`的值:

```java
public int calculateMinimumHP(int[][] dungeon) {
        int m = dungeon.length, n=dungeon[0].length;
        Integer[][] memo = new Integer[m][n];
        dp(0,0, dungeon, memo);
        int minimumHP = memo[0][0];
        return minimumHP;
    }
private void dp(int row, int col, int[][] dungeon, Integer[][] memo)
{
	// ...
  int minimumHP; //进入当前房间所需的初始生命值
	int minimumHPForNextRoom; //进入下一个房间所需的初始生命值
	int currentRoomValue = dungeon[row][col]; //当前房间的魔法具有的加/减血 效果
  
  // ... 计算minimumHPForNextRoom
  minimumHP = minimumHPForNextRoom - currentRoomValue;
	memo[row][col] = minimumHP > 0 ? minimumHP : 1;//minimum HP >= 1.
}
```

`memo[row][col]` 的值依赖于`currentRoomValue` 和 `minimumHPForNextRoom`. 已知`currentRoomValue == dungeon[row][col]`, 接下来求`minimumHPForNextRoom`. 由于规定了每一步只能往右或者往下走, "下一个"房间有多种情况, 需要分类讨论`minimumHPForNextRoom`的值.

## Compute `minimumHPForNextRoom`

如果当前房间已经位于最右下角, 那么就没有下一个房间, 此时minimum HP for next room就等于1, 因为要保证从该房间离开时HP >= 1.

```java
// ... 计算minimumHPForNextRoom
if(row == m-1 && col == n-1)
{
	minimumHPForNextRoom = 1;
}
else
{
  ...
}
```



对于非最右下角的房间, 如果它位于最底端或者最右端, 那么下一步只有一种选择:

```java
if(row == m-1 && col == n-1)
{
	//...
}
else if(row+1 == m){ // Can't go downward
	//The next room must be the rightward room.
	//Since the bottom-right corner has been dealt with, the current room can't be the corner, so it always has a rightward room.
	dp(row, col+1, dungeon, memo);
	minimumHPForNextRoom = memo[row][col+1];
}
else if (col+1 == n) { // Can't go rightward
	//The next room must be the rightward room.
	dp(row+1, col, dungeon, memo);
	minimumHPForNextRoom = memo[row+1][col];
}
else
{
	//...
}
```



在上述情况之外, 下一步总是可以往右或者往下走, 所以进入下一个房间所需的最小初始生命值是 `min (memo[row+1][col], memo[row][col+1])`. 即:

```java
if(row == m-1 && col == n-1)
{
	//...
}
else if(row+1 == m){ // Can't go downward
	//...
}
else if (col+1 == n) { // Can't go rightward
	//...
}
else
{
	dp(row, col+1, dungeon, memo);
	dp(row+1, col, dungeon, memo);

	minimumHPForNextRoom = Math.min(memo[row][col+1], memo[row+1][col]);
}
```

# Code

```java
package Solutions;

/**
 * 174. Dungeon Game
 */
public class Solution174 {
    public int calculateMinimumHP(int[][] dungeon) {
        int m = dungeon.length, n=dungeon[0].length;
        Integer[][] memo = new Integer[m][n];
        dp(0,0, dungeon, memo);
        int minimumHP = memo[0][0];
        return minimumHP;
    }

    /**
     * 对memo[row][col]进行赋值. memo[row][col] = 进入当前房间所需的初始生命值(the knight's minimum initial health so that he can rescue the princess, which was in the bottom-right corner.)
     */
    private void dp(int row, int col, int[][] dungeon, Integer[][] memo)
    {
        int m = dungeon.length, n=dungeon[0].length;

        if(memo[row][col] != null)  return;



        int minimumHP; //进入当前房间所需的最小初始生命值
        int minimumHPForNextRoom; //进入下一个房间所需的最小初始生命值
        int currentRoomValue = dungeon[row][col]; //当前房间的魔法具有的加/减血 效果

        // minimum HP + currentRoomValue == minimum HP for next room
        // So: minimum HP = minimum HP for next room - currentRoomValue
        // Note: the knight has an initial health point represented by a positive integer. So we must have: minimum HP >= 1.

        // From current room, we have two choices: go downward or go rightward),
        // So: minimum HP for next room = min(minimum HP for rightward room, minimum HP for downward room)

        // Here we compute the minimum HP for next room:
        
        // For the bottom-right corner, since we need to let the knight be alive after saving the princess, the minimum HP for next room == 1.
        if(row == m-1 && col == n-1)
        {
            // minimumHP + currentRoomValue == 1
            // So minimumHP == 1 - currentRoomValue
            minimumHPForNextRoom = 1;
        }
        else if(row+1 == m){ // Can't go downward
            //The next room must be the rightward room.
            //Since the bottom-right corner has been dealt with, the current room can't be the corner, so it always has a rightward room.
            dp(row, col+1, dungeon, memo);
            minimumHPForNextRoom = memo[row][col+1];
        }
        else if (col+1 == n) { // Can't go rightward
            //The next room must be the rightward room.
            dp(row+1, col, dungeon, memo);
            minimumHPForNextRoom = memo[row+1][col];
        }
        else
        {
            dp(row, col+1, dungeon, memo);
            dp(row+1, col, dungeon, memo);

            minimumHPForNextRoom = Math.min(memo[row][col+1], memo[row+1][col]);
        }


        minimumHP = minimumHPForNextRoom - currentRoomValue;
        memo[row][col] = minimumHP > 0 ? minimumHP : 1;//minimum HP >= 1.
    }
}
```



