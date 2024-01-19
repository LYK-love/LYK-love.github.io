---
title: Variational Autoencoders
tags:
---

Source
- Disentangled VAE's (DeepMind 2016): https://arxiv.org/abs/1606.05579
- Applying disentangled VAE's to RL: DARLA (DeepMind 2017): https://arxiv.org/abs/1707.08475
- Original VAE paper (2013): https://arxiv.org/abs/1312.6114
- [Understanding Variational Autoencoders (VAEs)](https://towardsdatascience.com/understanding-variational-autoencoders-vaes-f70510919f73)

[Understanding VQ-VAE (DALL-E Explained Pt. 1)](https://mlberkeley.substack.com/p/vq-vae)

Stanford CS228



# Intro

![Autoencoder: schema](https://blog.keras.io/img/ae/autoencoder_schema.jpg)[--> Source](https://blog.keras.io/building-autoencoders-in-keras.html)



# ELBO

![image-20240118214910704](/Users/lyk/Library/Application Support/typora-user-images/image-20240118214910704.png)

For a datapoint, say an image, $x$,

1. the encoder generates latent variable $z$ with probability distribution $q_w\left(z \mid x\right)$,
2. the decoder generates reconstructed datapoint $\hat x$ with probability distribution $p_w\left(\hat x \mid z\right)$,



When the model 
$$
\mathrm{ELBO} = 
-\mathbb{E}_{z \sim q_w(z \mid x[i])}\left[\log p_w\left(x^{[i]} \mid z\right)\right]
+
\mathbf{K L}\left(q_w\left(z \mid x^{[i]}\right) \| p(z)\right)
$$
where:

* The left term $-\mathbb{E}_{z \sim q_w(z \mid x[i])}\left[\log p_w\left(x^{[i]} \mid z\right)\right]$ is the reconstruction loss.
* The right term $\mathbf{K L}\left(q_w\left(z \mid x^{[i]}\right) \| p(z)\right)$ is the KL divergence between:
  * True probability distribution: $q_w(z \mid x)$.
  * Assumed (or predicted) probability distribution: $p_w(x \mid z)$. Because when the coder





## Deriviation of KL-divergence

[Source: Deriving the KL divergence loss for VAEs](https://stats.stackexchange.com/a/370048)



The encoder distribution is $q(z \mid x)=\mathcal{N}(z \mid \mu), \Sigma)$ where:

$x$ is an $n$-dimensional random vector.

$z$ is an $n$-dimensional random vector.

$\mu$ is the mean vector of the distribution, also $n$-dimensional.

$\Sigma=\operatorname{diag}\left(\sigma_1^2, \ldots, \sigma_n^2\right)$ is the $n \times n$ covariance matrix.



The latent prior is given by $p(z)=\mathcal{N}(0, I)$.



Both are multivariate Gaussians of dimension $n$, for which **in general** the $\mathrm{KL}$ divergence is:
$$
\mathrm{KL}\left[p_1 \| p_2\right]=\frac{1}{2}\left[\log \frac{\left|\Sigma_2\right|}{\left|\Sigma_1\right|}-n+\operatorname{tr}\left\{\Sigma_2^{-1} \Sigma_1\right\}+\left(\mu_2-\mu_1\right)^T \Sigma_2^{-1}\left(\mu_2-\mu_1\right)\right]
$$
where $p_1=\mathcal{N}\left(\mu_1, \Sigma_1\right)$ and $p_2=\mathcal{N}\left(\mu_2, \Sigma_2\right)$.



In the VAE case, $p_1=q(z \mid x)$ and $p_2=p(z)$, so $\mu_1=\mu, \Sigma_1=\Sigma, \mu_2=\overrightarrow{0}, \Sigma_2=I$. Thus:
$$
\begin{aligned}
\mathfrak{D}_{\mathrm{KL}}[q(z \mid x) \| p(z)] & =\frac{1}{2}\left[\log \frac{\left|\Sigma_2\right|}{\left|\Sigma_1\right|}-n+\operatorname{tr}\left\{\Sigma_2^{-1} \Sigma_1\right\}+\left(\mu_2-\mu_1\right)^T \Sigma_2^{-1}\left(\mu_2-\mu_1\right)\right] \\
& =\frac{1}{2}\left[\log \frac{|I|}{|\Sigma|}-n+\operatorname{tr}\left\{I^{-1} \Sigma\right\}+(\overrightarrow{0}-\mu)^T I^{-1}(\overrightarrow{0}-\mu)\right] \\
& =\frac{1}{2}\left[-\log |\Sigma|-n+\operatorname{tr}\{\Sigma\}+\mu^T \mu\right] \\
& =\frac{1}{2}\left[-\log \prod_i \sigma_i^2-n+\sum_i \sigma_i^2+\sum_i \mu_i^2\right] \\
& =\frac{1}{2}\left[-\sum_i \log \sigma_i^2-n+\sum_i \sigma_i^2+\sum_i \mu_i^2\right] \\
& =\frac{1}{2}\left[-\sum_i\left(\log \sigma_i^2+1\right)+\sum_i \sigma_i^2+\sum_i \mu_i^2\right]
\end{aligned}
$$
