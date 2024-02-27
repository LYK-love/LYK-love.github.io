---
title: Difussion Models
tags:
---

Source:

* Paper: *denoising diffusion probabilistic models* (**DDPM**; [Ho et al. 2020](https://arxiv.org/abs/2006.11239)).
* [What are Diffusion Models?](https://lilianweng.github.io/posts/2021-07-11-diffusion-models/)
* [How diffusion models work: the math from scratch](https://theaisummer.com/diffusion-models/)

![img](https://lilianweng.github.io/posts/2021-07-11-diffusion-models/generative-overview.png)



Given a data-point $\mathbf{x}_0$ sampled from the real data distribution $q(x)\left(\mathbf{x}_0 \sim q(x)\right)$, one can define a forward diffusion process by adding noise. Specifically, at each step of the Markov chain we add Gaussian noise with variance $\beta_t$ to $\mathbf{x}_{t-1}$, producing a new latent variable $\mathbf{x}_t$ with distribution $q\left(\mathbf{x}_t \mid \mathbf{x}_{t-1}\right)$. This diffusion process can be formulated as follows:
$$
q\left(\mathbf{x}_t \mid \mathbf{x}_{t-1}\right)=\mathcal{N}\left(\mathbf{x}_t ; \boldsymbol{\mu}_t=\sqrt{1-\beta_t} \mathbf{x}_{t-1}, \mathbf{\Sigma}_t=\beta_t \mathbf{I}\right)
$$
Since we are in the multi-dimensional scenario $\mathbf{I}$ is the identity matrix, indicating that each dimension has the same standard deviation $\beta_t$. Note that $q\left(\mathbf{x}_t \mid \mathbf{x}_{t-1}\right)$ is still a normal distribution, defined by the mean $\boldsymbol{\mu}$ and the variance $\boldsymbol{\Sigma}$ where $\boldsymbol{\mu}_t=\sqrt{1-\beta_t} \mathbf{x}_{t-1}$ and $\boldsymbol{\Sigma}_t=\beta_t \mathbf{I}$ . $\boldsymbol{\Sigma}$ will always be a diagonal matrix of variances (here $\beta_t$ )

Thus, we can go in a closed form from the input data $\mathbf{x}_0$ to $\mathbf{x}_T$ in a tractable way. Mathematically, this is the posterior probability and is defined as:
$$
q\left(\mathbf{x}_{1: T} \mid \mathbf{x}_0\right)=\prod_{t=1}^T q\left(\mathbf{x}_t \mid \mathbf{x}_{t-1}\right)
$$

The symbol: in $q\left(\mathbf{x}_{1: T}\right)$ states that we apply $q$ repeatedly from timestep 1 to $T$. It's also called trajectory.

The data sample $\mathbf{x}_0$ gradually loses its distinguishable features as the step $t$ becomes larger. Eventually when $T \rightarrow \infty, \mathbf{x}_T$ is equivalent to an isotropic Gaussian distribution.

![img](https://lilianweng.github.io/posts/2021-07-11-diffusion-models/DDPM.png)

A nice property of the above process is that we can sample $\mathbf{x}_t$ at any arbitrary time step $t$ in a closed form using reparameterization trick. Let $\alpha_t=1-\beta_t$ and $\bar{\alpha}_t=\prod_{i=1}^t \alpha_i$ :
$$
\begin{array}{rlr}
\mathbf{x}_t & =\sqrt{\alpha_t} \mathbf{x}_{t-1}+\sqrt{1-\alpha_t} \boldsymbol{\epsilon}_{t-1} & ; \text { where } \boldsymbol{\epsilon}_{t-1}, \boldsymbol{\epsilon}_{t-2}, \cdots \sim \mathcal{N}(\mathbf{0}, \mathbf{I}) \\
& =\sqrt{\alpha_t \alpha_{t-1}} \mathbf{x}_{t-2}+\sqrt{1-\alpha_t \alpha_{t-1}} \overline{\boldsymbol{\epsilon}}_{t-2} & ; \text { where } \overline{\boldsymbol{\epsilon}}_{t-2} \text { merges two Gaussians (*). } \\
& =\cdots \\
& =\sqrt{\bar{\alpha}_t} \mathbf{x}_0+\sqrt{1-\bar{\alpha}_t} \boldsymbol{\epsilon} \\
q\left(\mathbf{x}_t \mid \mathbf{x}_0\right) & =\mathcal{N}\left(\mathbf{x}_t ; \sqrt{\bar{\alpha}_t} \mathbf{x}_0,\left(1-\bar{\alpha}_t\right) \mathbf{I}\right)
\end{array}
$$
(*) Recall that when we merge two Gaussians with different variance, $\mathcal{N}\left(\mathbf{0}, \sigma_1^2 \mathbf{I}\right)$ and $\mathcal{N}\left(\mathbf{0}, \sigma_2^2 \mathbf{I}\right)$, the new distribution is $\mathcal{N}\left(\mathbf{0},\left(\sigma_1^2+\sigma_2^2\right) \mathbf{I}\right)$. Here the merged standard deviation is
$$
\sqrt{\left(1-\alpha_t\right)+\alpha_t\left(1-\alpha_{t-1}\right)}=\sqrt{1-\alpha_t \alpha_{t-1}} \text {. }
$$

Usually, we can afford a larger update step when the sample gets noisier, so $\beta_1<\beta_2<\cdots<\beta_T$ and therefore $\bar{\alpha}_1>\cdots>\bar{\alpha}_T$.


$$
\begin{aligned}
q(\mathbf{x}_{t-1} \vert \mathbf{x}_t, \mathbf{x}_0) 
&= q(\mathbf{x}_t \vert \mathbf{x}_{t-1}, \mathbf{x}_0) \frac{ q(\mathbf{x}_{t-1} \vert \mathbf{x}_0) }{ q(\mathbf{x}_t \vert \mathbf{x}_0) } \\
&\propto \exp \Big(-\frac{1}{2} \big(\frac{(\mathbf{x}_t - \sqrt{\alpha_t} \mathbf{x}_{t-1})^2}{\beta_t} + \frac{(\mathbf{x}_{t-1} - \sqrt{\bar{\alpha}_{t-1}} \mathbf{x}_0)^2}{1-\bar{\alpha}_{t-1}} - \frac{(\mathbf{x}_t - \sqrt{\bar{\alpha}_t} \mathbf{x}_0)^2}{1-\bar{\alpha}_t} \big) \Big) \\
&= \exp \Big(-\frac{1}{2} \big(\frac{\mathbf{x}_t^2 - 2\sqrt{\alpha_t} \mathbf{x}_t \color{blue}{\mathbf{x}_{t-1}} \color{black}{+ \alpha_t} \color{red}{\mathbf{x}_{t-1}^2} }{\beta_t} + \frac{ \color{red}{\mathbf{x}_{t-1}^2} \color{black}{- 2 \sqrt{\bar{\alpha}_{t-1}} \mathbf{x}_0} \color{blue}{\mathbf{x}_{t-1}} \color{black}{+ \bar{\alpha}_{t-1} \mathbf{x}_0^2}  }{1-\bar{\alpha}_{t-1}} - \frac{(\mathbf{x}_t - \sqrt{\bar{\alpha}_t} \mathbf{x}_0)^2}{1-\bar{\alpha}_t} \big) \Big) \\
&= \exp\Big( -\frac{1}{2} \big( \color{red}{(\frac{\alpha_t}{\beta_t} + \frac{1}{1 - \bar{\alpha}_{t-1}})} \mathbf{x}_{t-1}^2 - \color{blue}{(\frac{2\sqrt{\alpha_t}}{\beta_t} \mathbf{x}_t + \frac{2\sqrt{\bar{\alpha}_{t-1}}}{1 - \bar{\alpha}_{t-1}} \mathbf{x}_0)} \mathbf{x}_{t-1} \color{black}{ + C(\mathbf{x}_t, \mathbf{x}_0) \big) \Big)}
\end{aligned}
$$
