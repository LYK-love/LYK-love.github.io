---
title: 机器学习导论：Chapter4
tags: 机器学习导论
categories: Machine Learning
---

# 多分类任务

## LDA: 有监督降维

* 目标：最大化类间距离和最小化类内距离

* 最大化目标：

* 广义瑞利商（  ）
  $$
  J = \frac {w^\mathrm T S_b w}{w^\mathrm T S_2 w}
  $$

* 令$w^\mathrm T S_w w=1$​, 最大化瑞利商等价形式为
  $$
  \min\limits_w  -w^\mathrm T S_b \\
  \mathrm{s.t.} \quad w^\mathrm T S_w w=1
  $$
  

* 运用拉格朗日乘子法
  $$
  S_b w = \lambda S_w w
  $$
  

### revist: 拉格朗日乘子法

* 对


$$
w=\lambda^{-1}S_w^{-1}S_b w = \lambda^{-1}S_w^{-1}(\mu_0 - \mu_1)(\mu_0 - \mu_1)^{\mathrm T}w
$$

* 结果
  $$
  w=S_w^{-1}(\mu_0 - \mu_1)
  $$
  

* 求解

  由于矩阵求逆的复杂度为$O(n^3)$  --奇异值分解
  $$
  S_w = \mathrm U \sum \mathrm V^{ T }
  $$

* LDA的贝叶斯决策论解释

  * 两类数据同先验、 满足高斯分布且协方差相等时, LDA达到最优分类

### LDA推广： 多分类任务

* 优化目标
  $$
  \max\limits_\mathrm W \frac{ \tr ( \mathrm W^\mathrm T S_b \mathrm W  ) }{\tr ( \mathrm W^\mathrm T S_w \mathrm W  )}
  $$

### 总结

* 主要建模思想：
  * 寻找线性超平面，使得同类样例的投影点尽可能接近，异类样例的投影点尽可能远离
  * 得到广义瑞利商形式，设计巧妙
  * 得到最优解，是个闭式解
* 历史地位
  * LDA能用于分类任务，但因为其目标函数不直接对应经验风险，性能不如直接优化经验风险的方法
  * 因LDA投影点有效地得到类别区分方向，保留大量类别之前的判别信息，LDA成为数据降维最主流的方法之一

# 多分类任务

## 多分类学习

* 多分类学习方法
  * 常用技巧：利用二分类学习器解决多分类问题
    * 对问题进行拆分，为拆出的每个二分类任务训练一个分类器
* 拆分策略
  * 一对一
  * 一对其余
  * 多对多
