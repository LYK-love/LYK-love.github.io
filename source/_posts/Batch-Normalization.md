---
title: Batch Normalization
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-03-09 23:35:13
---


Source:

* Adjrej Karpathy's video [Building makemore Part 4: Becoming a Backprop Ninja](https://www.youtube.com/watch?v=q8SA3rM6ckI&list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ&index=5&t=5798s).
* Paper: *[Batch Normalization: Accelerating Deep Network Training by
  Reducing Internal Covariate Shift](https://arxiv.org/pdf/1502.03167.pdf)*
* PyTorch: [BatchNorm1d](https://pytorch.org/docs/stable/generated/torch.nn.BatchNorm1d.html#torch.nn.BatchNorm1d)

<!--more-->

# Batch Normalization

Given samples $\{x_i\}$ over a mini-batch: $\mathcal{B}=\left\{x_{1 \ldots N}\right\}$, the batch normalization is
$$
y_i = f(x_i, \mathcal{B})_{\gamma, \beta}=
\gamma \hat x_i +\beta = 
\gamma \frac{x_i-\mu}{\sqrt{\sigma^2+\epsilon}}+\beta .
$$
where:

- $y_i$ is the output of the batch normalization layer.
- $\hat x_i$ is the normalized input $x_i$
- $\epsilon$ is a small constant added for avoiding division by 0 error.
- $\gamma$ and $\beta$ are **parameters learned during training** for each feature, representing the scale and shift to be applied after normalization, respectively.

The detailed process is

$$
\begin{aligned} 
& \mu_{\mathcal{B}} \leftarrow \frac{1}{m} \sum_{i=1}^m x_i \quad \text { // mini-batch mean } 
\\ 
& \sigma_{\mathcal{B}}^2 \leftarrow \frac{1}{m-1} \sum_{i=1}^m\left(x_i-\mu_{\mathcal{B}}\right)^2 \quad \text { // mini-batch variance } 
\\ 
& \widehat{x}_i \leftarrow \frac{x_i-\mu_{\mathcal{B}}}{\sqrt{\sigma_{\mathcal{B}}^2+\epsilon}} \quad \text { // normalize } 
\\
& y_i \leftarrow \gamma \widehat{x}_i+\beta \equiv \mathrm{BN}_{\gamma, \beta}\left(x_i\right) \quad \text { // scale and shift } 

\end{aligned}
$$


# Derivation of batch norm

We have:
$$
\frac{\partial L}{\partial x_i}=\sum_{j=1}^N \frac{\partial L}{\partial y_j} \color{purple}{\frac{\partial y_j}{\partial x_i}} .
$$
$\frac{\partial L}{\partial y_j}$ is the upstream gradient, so it's already given here. 

Since $y_j = \gamma \hat x_j +\beta$. $y_j$ is a function of $\hat x_j$. We have
$$
\color{purple}{\frac{\partial y_j}{\partial x_i}} =\frac{\partial y_j}{\partial \hat{x}_j} \color{red}{\frac{\partial \hat{x}_j}{\partial x_i}},
$$
and
$$
\frac{\partial y_j}{\partial \hat{x}_j}=\gamma .
$$
So
$$
\color{purple}{\frac{\partial y_j}{\partial x_i}} = \gamma \color{red}{\frac{\partial \hat{x}_j}{\partial x_i}} .
$$
This means we only need to calculate $\frac{\partial \hat{x}_j}{\partial x_i}$. 



Recall that $\hat x_i = \frac{x_i-\mu}{\sqrt{\sigma^2+\epsilon}}$, we obtain:
$$
\begin{aligned} 
\color{red}{\frac{\partial \hat{x}_j}{\partial x_i}}
& = 
\frac{\partial}{\partial x_i}\left(\frac{x_j-\mu}{\sqrt{\sigma^2+\varepsilon}}\right) 
\\
& = 
\left(\delta_{i j}-\color{blue}{\frac{\partial \mu}{\partial x_i}}\right)\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}
+
\left(x_j-\mu\right) \left(-\frac{1}{2}\right)\left(\sigma^2+\varepsilon\right)^{-\frac{3}{2}}  \color{green}{\frac{\partial \sigma^2}{\partial x_i}} .
\end{aligned}
$$
where $\delta_{i j}$ is the *Kronecker delta* function:
$$
\delta_{i j}= \begin{cases}0 & \text { if } i \neq j \\ 1 & \text { if } i=j .\end{cases}
$$


Therefore, we compute the derivation $\frac{\partial \mu}{\partial x_i}$, $\frac{\partial \sigma^2}{\partial x_i}$.

For the former:
$$
\begin{aligned} 
\color{blue}{\frac{\partial \mu}{\partial x_i}} 
& =
\frac{\partial}{\partial x_i}\left(\frac{1}{N} (x_1+x_2+\cdots+x_i+\cdots+x_N ) \right) 
\\
& =
\frac{1}{N}(0+\cdots+1+\cdots+0)=\frac{1}{N}

\end{aligned}
$$


For the latter:
$$
\begin{aligned}
\color{green}{\frac{\partial \sigma^2}{\partial x_i}}
&= \frac{\partial}{\partial x_i}\left(\frac{1}{N-1} \sum_{k=1}^N\left(x_k-\mu\right)^2\right) \\
&= \frac{1}{N-1} \cdot \frac{\partial}{\partial x_i}\left(\left(x_1-\mu\right)^2+\cdots+\left(x_i-\mu\right)^2+\cdots\right) \\
&=\frac{1}{N-1}\left[2 (x_1-\mu\right) \frac{\partial(-\mu)}{\partial x_i}+2\left(x_2-\mu\right) \frac{\partial(-\mu)}{\partial x_i}+\cdots +2\left(x_i-\mu\right) \frac{\partial\left(x_i-\mu\right)}{\partial x_i}+\cdots] \\

&= \frac{1}{N-1}\left[2\left(x_1-\mu\right) \cdot \frac{-1}{N}+2\left(x_2-\mu\right) \cdot \frac{-1}{N}+\cdots+2\left(x_i-\mu\right) \cdot\left(1-\frac{1}{N}\right)+\cdots\right] \\
&=\frac{1}{N-1} \cdot 2[\underbrace{\sum_{k=1}^N\left(x_k-\mu\right.}_0) \cdot\left(\frac{-1}{N}\right)+x_i-\mu] \\
&= \frac{1}{N-1} \cdot 2 \cdot\left(x_i-\mu\right) \\
&= \frac{2}{N-1} \cdot\left(x_i-\mu\right)
\end{aligned}
$$


The transition from 3rd line to 4th line is because $\frac{\partial \mu}{\partial x_i} = \frac 1 N$.



So we have:
$$
\begin{aligned}
\color{red}{\frac{\partial \hat{x}_j}{\partial x_i}}
& =
\left(\delta_{i j}- \color{blue}{\frac{1}{N}} \right)\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}+\left(x_j-\mu\right) \left(-\frac{1}{2}\right) \left(\sigma^2+\varepsilon\right)^{-\frac{3}{2}} \color{green}{\frac{2}{N-1}\left(x_i-\mu\right)} \\

& =
\left(\delta_{i j} -\frac{1}{N}\right) \left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}-\frac{1}{N-1}\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}} \cdot \frac{x_i-\mu}{\sqrt{\sigma^2+\varepsilon}} \cdot \frac{x_j-\mu}{\sqrt{\sigma^2+\varepsilon}} \\
& =
\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}\left[\delta_{i j} -\frac{1}{N}-\frac{1}{N-1}\left(\hat{x}_i \cdot \hat{x}_j\right)\right] \\
& =
\color{red}{\frac{\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N}\left[N \cdot \delta_{i j}-1-\frac{N}{N-1}\left(\hat{x}_i\hat{x}_j\right)\right]} .
\end{aligned}
$$


As a result:
$$
\begin{aligned}
\frac{\partial L}{\partial x_i} 
& =
\sum_{j=1}^N \frac{\partial L}{\partial y_j} \color{purple}{\frac{\partial y_j}{\partial x_i}}
=
\sum_{j=1}^N \frac{\partial L}{\partial y_j} \frac{\partial y_j}{\partial \hat{x}_j} \color{red}{\frac{\partial \hat{x}_j}{\partial x_i}} 
\\
& =\sum_{j=1}^N \frac{\partial L}{\partial y_j} \cdot \gamma \cdot \color{red} {\frac{\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N}\left[N \cdot \delta_{i j}-1-\frac{N}{N-1}\left(\hat{x}_i \cdot \hat{x}_j\right)\right]} \\
& =\frac{\gamma\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N} \sum_{j=1}^N \frac{\partial L}{\partial y_j}\left[N \cdot \delta_{i j}-1-\frac{N}{N-1}\left(\hat{x}_i \cdot \hat{x}_j\right)\right] \\
& =\frac{\gamma\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N}\left[\left(N \sum_{j=1}^N \frac{\partial L}{\partial y_j} \delta_{i j}\right)-\left(\sum_{j=1}^N \frac{\partial L}{\partial y_j}\right)-\left(\frac{N}{N-1} x_i \sum_{j=1}^N \frac{\partial L}{\partial y_j} \hat{x}_j\right)\right] \\
& =\frac{\gamma\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N}\left(N  \frac{\partial L}{\partial y_i}-\sum_{j=1}^N \frac{\partial L}{\partial y_j}-\frac{N}{N-1} \hat{x}_i \sum_{j=1}^N \frac{\partial L}{\partial y_j} \hat{x}_j\right ).
\end{aligned}
$$





