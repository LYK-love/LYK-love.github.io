---
title: Batch Normalization
tags:
---



Paper: *[Batch Normalization: Accelerating Deep Network Training by
Reducing Internal Covariate Shift](https://arxiv.org/pdf/1502.03167.pdf)*

[BatchNorm1d](https://pytorch.org/docs/stable/generated/torch.nn.BatchNorm1d.html#torch.nn.BatchNorm1d)

Input: Values of $x$ over a mini-batch: $\mathcal{B}=\left\{x_{1 \ldots m}\right\}$; Parameters to be learned: $\gamma, \beta$

Output: $\left\{y_i=\mathrm{BN}_{\gamma, \beta}\left(x_i\right)\right\}$


$$
\begin{aligned} & \mu_{\mathcal{B}} \leftarrow \frac{1}{m} \sum_{i=1}^m x_i \quad \text { // mini-batch mean } \\ & \sigma_{\mathcal{B}}^2 \leftarrow \frac{1}{m} \sum_{i=1}^m\left(x_i-\mu_{\mathcal{B}}\right)^2 \quad \text { // mini-batch variance } \\ & \widehat{x}_i \leftarrow \frac{x_i-\mu_{\mathcal{B}}}{\sqrt{\sigma_{\mathcal{B}}^2+\epsilon}} \quad \text { // normalize } \\ & y_i \leftarrow \gamma \widehat{x}_i+\beta \equiv \mathrm{BN}_{\gamma, \beta}\left(x_i\right) \quad \text { // scale and shift } \\ & \end{aligned}
$$
