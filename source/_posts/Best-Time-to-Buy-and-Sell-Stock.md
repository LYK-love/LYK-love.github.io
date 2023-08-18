---
title: Best Time to Buy and Sell Stock
tags: LeetCode
categories: Algorithm
date: 2023-08-18 01:40:03
---


You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

Find the maximum profit you can achieve. You may complete **at most K transactions**.

<!--more-->

* [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
* [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
* [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

# Intro

以[123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)为例:

You are given an array `prices` where `prices[i]` is the price of a given stock on the `ith` day.

Find the maximum profit you can achieve. You may complete **at most two transactions**.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).



题目允许在同一天买卖同一支股票.





用DP.

* dp数组`memo[j][j][k]`: 在i_{th}天能达到的最大利润. 
  * j={0,1}:当天是否持有股票.题目规定每天只能同时持有最大1支股票. 
  * k={0,1,K}: 最大交易次数K.
  * 题目规定了最大交易次数为2. 因此`0 <= k <= K = 2`
* 返回值: `memo[prices.length-1, 0, 2]`. 注意, 如果利润要最大, 最后一天结束时手里就不能有股票, 因此最后一天的`j = 0`



```java
    public int maxProfit(int[] prices) {
        int K = 3;
        Integer[][][] memo = new Integer[prices.length][2][K];
        int max = dp(memo, prices.length-1, 0, 2, prices);//在最后一天(i=len-1)且当天不持有股票的(j=0)情况下能达到的最大利润.
        return max;
    }

    /**
     * 使用动态规划.
     * 返回[0,...,day]这段时间内, 在第{day}天持有股票状态为{hasStock}, 且最大交易次数为{numOfMaxTransactions}的情况下, 能得到的最大利润.
     */
    private Integer dp(Integer[][][] memo, int day, int hasStock, int numOfMaxTransactions, int[] prices)
    {
    }
```

# Initialization

dp数组初始化:

```java
    private Integer dp(Integer[][][] memo, int day, int hasStock, int numOfMaxTransactions, int[] prices)
    {
      	//Initial condition
        if(day==0)
        {
            for( int k = 0; k <= numOfMaxTransactions; k++ )
            {
                memo[day][0][k] = 0;

                if(k >=1)
                    memo[day][1][k] = -prices[day];
                else
                    memo[day][1][k] = null; //在最多只能进行0次交易的情况下的情况下居然持有股票, 这是不可能的.
            }
        }
     //...
     }
```

在第0天时:

* 如果手中没有股票(`hasStock == 0`), 那么无论交易几次(买卖同一张股票)利润都为0.
* 如果手中有股票(`hasStock == 1`), 那么说明: buy的次数 - sell的次数 = 1. 
  * 如果最大交易次数>=1, 则利润为`-prices[day]`. 
  * 但如果最大交易次数 == 0 , 此时是不能发生任何交易的, 因此不存在buy, 这和`hasStock == 1`矛盾. 因此令利润为`null`.



同理, 在之后的DP过程中, 如果有`numOfMaxTransactions == 0 && hasStock == 1`, 则令`memo[day][1][1] = null`.

```java
//Initial condition
if(day==0)
{
	...
}

else if(numOfMaxTransactions == 0 && hasStock == 1)
            ;
else
  ...
```



# DP process

每次状态转移有三种选择:

* sell: 卖出当天手中的股票. `dp[i][0][k] = dp[i-1][0][k-1] + prices[i]`
* buy: 买下当天的股票. `dp[i][1][k] = dp[i-1][0][k-1] - prices[i]`
* rest: 不进行任何操作. `dp[i][j][k] = dp[i-1][j][k-1]`

事实上还可以有第四种操作: sell-buy, 即在当天进行相同次数的sell和buy, 得到的总利润不变, 但消耗最大交易次数. 即:

```python
dp[i][j][k] = dp[i-1][j][k-1]
```

然而, 由于`dp[i][j][k-1](sell-buy) <= dp[i][j][k](rest)`恒成立, 所以sell的利润永远不能超过rest. 所以这种情况被排除.

***

## Have Stock Today

```python
dp[i][0][k] = max(dp[i-1][0][k], dp[i-1][1][k] + prices[i])
              max( 今天选择rest,        今天选择 sell       )
```

解释：今天我没有持有股票，有两种可能，我从这两种可能中求最大利润：

1、我昨天就没有持有，且截至昨天最大交易次数限制为 `k`；然后我今天选择 `rest`，所以我今天还是没有持有，最大交易次数限制依然为 `k`。

2、我昨天持有股票，且截至昨天最大交易次数限制为 `k`；但是今天我 `sell` 了，所以我今天没有持有股票了，最大交易次数限制依然为 `k`。

## Don't Have Stock Today

```python
dp[i][1][k] = max(dp[i-1][1][k], dp[i-1][0][k-1] - prices[i])
              max( 今天选择rest),         今天选择 buy         )
```

解释：今天我持有着股票，最大交易次数限制为 `k`，那么对于昨天来说，有两种可能，我从这两种可能中求最大利润：

1、我昨天就持有着股票，且截至昨天最大交易次数限制为 `k`；然后今天选择 `rest`，所以我今天还持有着股票，最大交易次数限制依然为 `k`。

2、我昨天本没有持有，且截至昨天最大交易次数限制为 `k - 1`；但今天我选择 `buy`，所以今天我就持有股票了，最大交易次数限制为 `k`。

## Note: Change of k

注意k的变化:

这类题目规定: `(sell, buy)`等于一次交易. 而buy占用了交易次数. 例如`[0,1,2]`这三天的最大交易次数为2, 那么可以进行: 2次buy + 2次buy.

因此, 如果`[0,1,2,3]`的最大交易次数为k, 已知`day=3`必定sell(`dp[i-1][1][k] + prices[i]`), 那么对于`[0,1,2]`来说最大交易次数依然为`k`次, 因为它的交易是`k`次buy + `k-1`次sell. 

而如果已知`day=3`必定buy(`dp[i-1][0][k-1] - prices[i]`),那么`[0,1,2]`的最大交易次数就变成`k-1`次, 因为`day=3`会进行一次buy, 占用一个交易次数.

## Note: K=0

此外, 考虑`[0,...,day]`的最大交易次数为0的情况, 这说明在`[0,...,day]`不会进行任何一次buy, 因此:

* 在第`day`天不会sell(因为之前没有buy过):

  ```python
  if(k == 0):
  	dp[i][0][k] = dp[i-1][0][k]//不需要考虑在今天sell. 此时的 dp[i-1][1][k] == null
  else:
  	dp[i][0][k] = max(dp[i-1][0][k], dp[i-1][1][k] + prices[i])
  ```

* 第`day`天也不会buy:

  ```python
  if(k == 0):
  	dp[i][0][k] = max(dp[i-1][1][k], dp[i-1][0][k-1] - prices[i])
  else:
  	dp[i][0][k] = dp[i-1][1][k] //此时的 dp[i-1][1][k-1] == 0
  ```

  

# Code



```java
    private Integer dp(Integer[][][] memo, int day, int hasStock, int numOfMaxTransactions, int[] prices)
    {
        //Initial condition
        if(day==0)
        {
            for( int k = 0; k <= numOfMaxTransactions; k++ )
            {
                memo[day][0][k] = 0;

                if(k >=1)
                    memo[day][1][k] = -prices[day];
                else
                    memo[day][1][k] = null; //在最多只能进行0次交易的情况下的情况下居然持有股票, 这是不可能的.
            }
        }
        else if(numOfMaxTransactions == 0 && hasStock == 1)//在最多只能进行0次交易的情况下的情况下居然持有股票, 这是不可能的, 因此memo[day][1][1] = null.
            ;

        //DP process
        else if( memo[day][hasStock][numOfMaxTransactions] == null)
        {
            if(  numOfMaxTransactions == 0)//[0,...,day-1]的最大交易次数为0, 这说明在`[0,...,day]`不会进行任何一次buy, 因此在第day天不可能sell
                memo[day][0][numOfMaxTransactions] = dp(memo, day-1, 0, numOfMaxTransactions, prices);
            else
                memo[day][0][numOfMaxTransactions] = Math.max(dp(memo, day-1, 0, numOfMaxTransactions, prices), dp(memo, day-1, 1, numOfMaxTransactions,prices) + prices[day]);

            if(numOfMaxTransactions == 0)//[0,...,day-1]的最大交易次数为0, 这说明在`[0,...,day]`不会进行任何一次buy, 因此在第day天不可能buy
                memo[day][1][numOfMaxTransactions] = dp(memo,day-1,1,numOfMaxTransactions, prices);
            else
                memo[day][1][numOfMaxTransactions] = Math.max(dp(memo,day-1, 0, numOfMaxTransactions-1, prices) - prices[day], dp(memo,day-1,1,numOfMaxTransactions, prices));
        }
        else
            ;
        return memo[day][hasStock][numOfMaxTransactions];
    }
```

