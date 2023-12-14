---
title: Covariance Matrix
tags:
---



# $(Z_1,Z_2) \sim \mathcal N(0,K_z)$

三个变量的协方差可以用协方差矩阵来表示。假设有三个变量 $X, Y, Z$, 它们的样本数据分别为 $x_1, x_2, \ldots, x_n, y_1, y_2, \ldots, y_n$ $, z_1, z_2, \ldots, z_n$, 则它们的协方差矩阵为:
$$
\left[\begin{array}{lll}
\operatorname{cov}(X, X) & \operatorname{cov}(X, Y) & \operatorname{cov}(X, Z) \\
\operatorname{cov}(Y, X) & \operatorname{cov}(Y, Y) & \operatorname{cov}(Y, Z) \\
\operatorname{cov}(Z, X) & \operatorname{cov}(Z, Y) & \operatorname{cov}(Z, Z)
\end{array}\right]
$$

其中, $\operatorname{cov}(X, Y)$ 表示 $X$ 和 $Y$ 之间的协方差, 定义为:
$$
\operatorname{cov}(X, Y)=\frac{1}{n} \sum_{i=1}^n\left(x_i-\bar{x}\right)\left(y_i-\bar{y}\right)
$$

同理, $\operatorname{cov}(X, Z)$ 和 $\operatorname{cov}(Y, Z)$ 分别表示 $X$ 和 $Z$ 之间的协方差以及 $Y$ 和 $Z$ 之间的协方差。而 $\operatorname{cov}(X, X)$, $\operatorname{cov}(Y, Y)$ 和 $\operatorname{cov}(Z, Z)$ 则分别表示 $X, Y$ 和 $Z$ 的方差, 定义为:
$$
\operatorname{cov}(X, X)=\frac{1}{n} \sum_{i=1}^n\left(x_i-\bar{x}\right)^2
$$


# $\text{Var}(Z_1 + Z_2)$

对于两个正态分布的随机变量 $Z_1$ 和 $Z_2$, 其联合正态分布 $N\left(0, K_z\right)$ 的协方差矩阵为 $K_z$ 。如果我们考虑它们的和 $Z_1+Z_2$, 该变量的方差可以通过以下方式计算:
$$
\operatorname{Var}\left(Z_1+Z_2\right)=\operatorname{Var}\left(Z_1\right)+\operatorname{Var}\left(Z_2\right)+2 \cdot \operatorname{Cov}\left(Z_1, Z_2\right)
$$

在这里, $\operatorname{Var}\left(Z_1\right)$ 和 $\operatorname{Var}\left(Z_2\right)$ 分别是 $Z_1$ 和 $Z_2$ 的方差, $\operatorname{Cov}\left(Z_1, Z_2\right)$ 是它们的协方差。

如果 $Z_1$ 和 $Z_2$ 是相互独立的, 那么它们的协方差为零, 上述方差简化为:
$$
\operatorname{Var}\left(Z_1+Z_2\right)=\operatorname{Var}\left(Z_1\right)+\operatorname{Var}\left(Z_2\right)
$$

但是, 如果 $Z_1$ 和 $Z_2$ 不是相互独立, 那么需要考虑协方差的贡献。在你的问题中, $Z_1$和 $Z_2$ 的协方差矩阵是 $K_z$, 因此:
$$
\begin{aligned}
& \operatorname{Var}\left(Z_1+Z_2\right)=\operatorname{Var}\left(Z_1\right)+\operatorname{Var}\left(Z_2\right)+2 \cdot \operatorname{Cov}\left(Z_1, Z_2\right)=K_{z 11}+K_{z 22}+ \\
& 2 \cdot K_{z 12}
\end{aligned}
$$

其中, $K_{z 11}$ 和 $K_{z 22}$ 是 $Z_1$ 和 $Z_2$ 的方差, $K_{z 12}=K_{z 21}$ 是它们的协方差。
