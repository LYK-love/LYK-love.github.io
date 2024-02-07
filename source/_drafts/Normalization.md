---
title: Normalization
tags:
---

# Batch normalization

Input: $x: N \times D$

Output: $y: N \times D$

Learnable params: $\gamma, \beta : D$

Intermediates: 

* $\mu, \sigma: D$
* $\hat{x}: N \times D$

$$
\begin{aligned}
\mu_j & =\frac{1}{N} \sum_{i=1}^N x_{i, j} \\
\sigma_j^2 & =\frac{1}{N} \sum_{i=1}^N\left(x_{i, j}-\mu_j\right)^2 \\
\hat{x}_{i, j} & =\frac{x_{i, j}-\sigma_j}{\sqrt{\sigma_j^2+\varepsilon}} \\
y_{i, j} & =\gamma_j \hat{x}_{i, j}+\beta_j
\end{aligned}
$$
