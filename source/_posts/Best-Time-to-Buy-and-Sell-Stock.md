---
title: Best Time to Buy and Sell Stock
tags: 
- Algorithm
- LeetCode
categories: 
- Computer Science
date: 2023-08-18 01:40:03
---

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the `ith` day, and an integer `k`.

Find the maximum profit you can achieve. You may complete at most `k` transactions: i.e. you may buy at most `k` times and sell at most `k` times.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

* [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
* [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
* [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
* [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

<!--more-->

# Intro

我们直接看最抽象的[188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/), 上文就是其题目.

**Example 1:**

```
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
```

**Example 2:**

```
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
```

在同一天买卖同一支股票并不影响结果.

# Solution

使用动态规划(DP).

* DP数组`dp[i][j][k]`: 在天数为[0,1,2,...,i]的这段时间内, 当天的持有股票状态为{j}, 且最大交易数为{k}的情况下, 能达到的最大利润.
  * i = {0, 1, ..., prices.length-1}
  * j = {0,1}, 表达当天是否持有股票. 0: 不持有, 1: 持有.
  * k = {0,1,2, ...., K}: 最大交易次数, 共有K+1种情况. 题目给定的最大交易次数为K.
* 返回值: 如果利润要最大, 最后一天结束时手里就不能有股票, 因此最后一天的`j = 0`. 因此返回值为`dp[prices.length-1, 0, K]`.
* DP函数`void buildDP(Integer[][][] memo, int i, int k, int[] prices)`: 对`dp[i][0][k], dp[i][1][k]`进行赋值. 
  * 你也可以把函数定义为`void buildDP(Integer[][][] dp, int i, int j, int k, int[] prices)`, 每次调用都对`dp[i][j][k]`进行赋值. 这样只会使解法更复杂, 因为j只有0和1两种情况.

```java
    public int maxProfit(int K, int[] prices) {

        /**
         * dp[i][j][k]: 在天数为[0,1,2,...,i]的这段时间内, 当天的持有股票状态为{j}, 且最大交易数为{k}的情况下, 能达到的最大利润.
         * i = {0, 1, ..., prices.length-1}
         * j = {0,1}, 表达当天是否持有股票. 0: 不持有, 1: 持有.
         * k = {0,1,2, ...., K}: 最大交易次数, 共有K+1种情况.
         */
        Integer[][][] dp = new Integer[prices.length][2][K+1];
        dp(dp, prices.length-1, K, prices);//得到dp[prices.length-1][0][K], 即在最后一天(i=len-1)且当天不持有股票的(j=0)情况下能达到的最大利润.
        int max = dp[prices.length-1][0][K];
        return max;
    }

    /**
     * 使用动态规划.
     * 对dp[i][0][k], dp[i][1][k]进行赋值.
     */
    private void dp(Integer[][][] dp, int i, int k, int[] prices)
    {
      //...
    }
```

## DP process

每次状态转移有三种选择:

* sell: 卖出当天手中的股票. `dp[i][0][k] = dp[i-1][0][k-1] + prices[i]`
* buy: 买下当天的股票. `dp[i][1][k] = dp[i-1][0][k-1] - prices[i]`
* rest: 不进行任何操作. `dp[i][j][k] = dp[i-1][j][k-1]`

事实上还可以有第四种操作: sell-buy, 即在当天进行相同次数的sell和buy, 得到的总利润不变, 但消耗最大交易次数. 即:

```python
dp[i][j][k] = dp[i-1][j][k-1]
```

然而, 由于`dp[i][j][k-1](sell-buy) <= dp[i][j][k](rest)`恒成立, 所以sell的利润永远不能超过rest. 所以这种情况被排除.

## Note: Change of k

注意k的变化:

这类题目规定: `(sell, buy)`等于一次交易. 只有buy占用交易次数, sell和rest均不占用. 

例如`[0,1,2]`这三天的最大交易次数为2, 那么可以进行2次buy + 2次sell.



假设`[0,1,2,3]`的最大交易次数为k:

1. 如果在第i=3天sell, 那么`[0,1,2]`的最大交易次数依然为`k`次, 因为第i=3天进行的sell不占用交易次数.

2. 如果在第i=3天buy,那么`[0,1,2]`的最大交易次数就变成`k-1`次, 因为第i=3天的buy会占用一个交易次数.

   

# Special Case: i = 0

在第0天时:

* 在当天不持有股票(i=0)的情况下, 无论k为多少, 利润都为0:

  ```
  dp[i][0][k] = 0;
  ```

  

* 在当天持有股票(j=1)的情况下:

  * 如果当天的最大交易次数k为正数, 那么可以通过q次buy和q-1次sell来使得当天能够持有股票, q <= k.  因此:

    ```java
    dp[i][1][k] = -prices[i].
    ```

  * 如果当天的最大交易次数k=0, 那么说明在当天不允许任何交易, 因此当天不可能持有股票, 这与j=1矛盾, 因此令利润为`null`:

    ```java
    dp[i][1][k] = null;
    ```

# Special Case: k = 0

如果第i天(i>0)的k=0, 说明[0,1,2,...,i]这段时间内不允许发生任何交易, 因此不能发生任何一次buy(因此也就不能有任何的sell).

* 如果j=0, 则[0,1,2,...,i]的最大利润就是[0,1,2,...,i-1]的最大利润, 因为不可能发生sell.

  ```
  dp[i][0][k] = dp[i-1][0][k];
  ```

   `dp[i][0][0]` 会一直递归到`dp[0][0][0] = 0`.

* 如果j=1, 说明第i天当天持有了股票, 由于这段时间内不可能发生buy, 所以这种情况不可能发生.

  ```java
  dp[i][1][k] = null
  ```

# Don't Have Stock Today(j=0)

如果第i天(i>0)天k>0, 那么在此期间可以发生buy和sell.

如果当天不持有股票(j=0), 有两种情况:

1. 昨天没有持有, 且今天rest. rest不消耗交易次数, 所以昨天的k和今天的一样.

   解释: 我昨天就没有持有，且截至昨天最大交易次数限制为 `k`；然后我今天选择 `rest`，所以我今天还是没有持有，最大交易次数限制依然为 `k`。

2. 昨天持有了股票, 今天sell了. sell不消耗交易次数, 所以昨天的k和今天的一样.

   解释: 我昨天持有股票, 且截至昨天最大交易次数限制为 `k`; 但是今天我 `sell` 了, 所以我今天没有持有股票了, 最大交易次数限制依然为 `k`.

```python
dp[i][0][k] = max(dp[i-1][0][k], dp[i-1][1][k] + prices[i])
              max( 今天选择rest,        今天选择 sell       )
```

# Have Stock Today(j=1)

如果第i天(i>0)天k>0, 那么在此期间可以发生buy和sell.

如果当天持有股票(j=0), 有两种情况:

1. 昨天持有了股票, 且今天rest. sell不消耗交易次数, 所以昨天的k和今天的一样.

   解释: 我昨天就持有着股票, 且截至昨天最大交易次数限制为 `k`; 然后今天选择 `rest`，所以我今天还持有着股票，最大交易次数限制依然为 `k`.

2. 昨天没有持有, 今天buy了. buy消耗交易次数, 所以昨天的k比今天的少一次(截至今天最多交易k次, 今天要buy, 消耗一次, 所以截至昨天就只能最多交易k-1次).

   解释: 我昨天本没有持有, 且截至昨天最大交易次数限制为 `k - 1`; 但今天我选择 `buy`, 所以今天我就持有股票了, 最大交易次数限制为 `k`.

```python
dp[i][1][k] = max(dp[i-1][1][k], dp[i-1][0][k-1] - prices[i])
              max( 今天选择rest),         今天选择 buy         )
```



# Code

```java
/**
 * 188. Best Time to Buy and Sell Stock IV
 */
public class Solution188 {
    public int maxProfit(int K, int[] prices) {

        /**
         * dp[i][j][k]: 在天数为[0,1,2,...,i]的这段时间内, 当天的持有股票状态为{j}, 且最大交易数为{k}的情况下, 能达到的最大利润.
         * i = {0, 1, ..., prices.length-1}
         * j = {0,1}, 表达当天是否持有股票. 0: 不持有, 1: 持有.
         * k = {0,1,2, ...., K}: 最大交易次数, 共有K+1种情况.
         */
        Integer[][][] dp = new Integer[prices.length][2][K+1];
        buildDP(dp, prices.length-1, K, prices);//得到memo[prices.length-1][0][K], 即在最后一天(i=len-1)且当天不持有股票的(j=0)情况下能达到的最大利润.
        int max = dp[prices.length-1][0][K];
        return max;
    }

    /**
     * 使用动态规划.
     * 对memo[i][0][k], memo[i][1][k]进行赋值.
     */
    private void buildDP(Integer[][][] memo, int i, int k, int[] prices)
    {
        if( i < 0 || k < 0 ) return; //k is the number of max transaction, k can't be negative. So is i.
        if(memo[i][0][k] != null ) return;

        if(i == 0)
        {

            //在当天不持有股票(i=0)的情况下, 无论k为多少, 利润都为0.
            memo[i][0][k] = 0;

            //
            //如果当天的最大交易次数k>0, 那么可以通过q次buy和q-1次sell来使得当天能够持有股票, q <= k. memo[i][1][k] = -prices[i].
            //如果当天的最大交易次数k=0, 那么说明在当天不允许任何交易, 因此当天不可能持有股票. memo[i][1][k] = null;
            memo[i][1][k] = k>0 ? -prices[i]: null;

        }
        else
        {
            //DP, 得到第i-1天, 最大交易次数为k, k-1时的最大利润.
            buildDP(memo, i-1, k, prices);
            buildDP(memo, i-1, k-1, prices);

            if(k==0)
            {
                //如果第i天(i>0)的k=0, 说明[0,1,2,...,i]这段时间内不允许发生任何交易, 因此不能发生任何一次buy(因此也就不能有任何的sell).
                //如果j=0, 则[0,1,2,...,i]的最大利润就是[0,1,2,...,i-1]的最大利润, 因为不可能发生sell. memo[i][0][0] 会一直递归到memo[0][0][0] = 0.
                //如果j=1, 说明第i天当天持有了股票, 由于这段时间内不可能发生buy, 所以这种情况不可能发生. memo[i][1][k] = null
                memo[i][0][k] = memo[i-1][0][k];
                memo[i][1][k] = null;
            }
            else
            {
                //如果第i天(i>0)天k>0, 那么在此期间可以发生buy和sell.

                //如果当天不持有股票(j=0), 有两种情况:
                // 1. 昨天没有持有, 且今天rest. rest不消耗交易次数, 所以昨天的k和今天的一样, 因此求memo[i-1][0][k]
                // 2. 昨天持有了股票, 今天sell了. sell不消耗交易次数, 所以昨天的k和今天的一样, 因此求memo[i-1][1][k] + prices[i]
                memo[i][0][k] = Math.max(memo[i-1][0][k], memo[i-1][1][k] + prices[i]);

                //如果当天持有股票(j=0), 有两种情况:
                // 1. 昨天持有了股票, 且今天rest. sell不消耗交易次数, 所以昨天的k和今天的一样, 因此求memo[i-1][1][k]
                // 2. 昨天没有持有, 今天buy了. buy消耗交易次数, 所以昨天的k比今天的少一次(截至今天最多交易k次, 今天要buy, 消耗一次, 所以截至昨天就只能最多交易k-1次), 因此求memo[i-1][0][k]
                memo[i][1][k] = Math.max(memo[i-1][1][k], memo[i-1][0][k-1] - prices[i]);
            }
        }
        return;
    }
}
```

