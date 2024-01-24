---
title: Variational Autoencoders
tags:
  - Machine Learning
categories:
  - Research
mathjax: true
date: 2024-01-19 00:14:34
---


Source:

1. [*Auto-Encoding Variational Bayes* (VAE)](https://arxiv.org/abs/1312.6114)
2. [*Early Visual Concept Learning with Unsupervised Deep Learning*](https://arxiv.org/abs/1606.05579)
3. [*DARLA: Improving Zero-Shot Transfer in Reinforcement Learning*](https://arxiv.org/abs/1707.08475)
4. [Understanding Variational Autoencoders (VAEs)](https://towardsdatascience.com/understanding-variational-autoencoders-vaes-f70510919f73)
5. [Understanding VQ-VAE (DALL-E Explained Pt. 1)](https://mlberkeley.substack.com/p/vq-vae)
6. [Youtube: Variational Autoencoder Loss Function](https://youtu.be/ywYuZrLENH0?feature=shared)
7. [Stanford CS 228: The variational auto-encoder](https://ermongroup.github.io/cs228-notes/extras/vae/)
8. https://www.cnblogs.com/wolfling/p/16452537.html

<!--more-->

# Auto-encoders

![Illustration of the dimensionality reduction principle with encoder and decoder.](https://miro.medium.com/v2/resize:fit:2000/1*UdOybs9wOe3zW8vDAfj9VA@2x.png)

[--> Image source](https://blog.keras.io/building-autoencoders-in-keras.html)

*Auto-encoder* is a data compression model where the compression and decompression functions are

1. data-specific
2. lossy, and 
3. *learned automatically from examples* rather than engineered by a human. (VAE is unsupervised)

For a $n$-dimensional datapoint, usually an image, $x \in \mathbb R^{n \times 1}$, the encoder encodes it to a latent variable $z \in \mathbb R^{m \times 1}$ ($m < n$), which was then used by the decoder to output the reconstructed datapoint $\hat x \in \mathbb R^{n \times 1}$.

## Loss function

![img](https://miro.medium.com/v2/resize:fit:1400/1*bY_ShNK6lBCQ3D9LYIfwJg@2x.png)

The loss function of autoencoder is called **reconstruction loss** and in practice it's the simple  [MSE (Mean Squared Error)]() loss:
$$
\mathrm{Reconstruction \ Loss} =  \| x -\operatorname{Dec}(\operatorname{Enc}(x)) \|_2^2=\sqrt{\sum_{i=1}^n\left(x_i- \hat x_i\right)^2} .
$$

Note: some people use Binary Symmetric Entropy (BCE) as the reconstruction loss. This is wrong because in BCE the input and output values are all 0 and 1, but in auto-encoders, the input values are grey scale values or RGB values, neither of them are in {0,1}. In fact they should be real values in [0,1].

## Dimensionality reduction

![img](https://miro.medium.com/v2/resize:fit:2000/1*F-3zbCL_lp7EclKowfowMA@2x.png)



# Variational auto-encoder

![img](https://miro.medium.com/v2/resize:fit:2000/1*ejNnusxYrn1NRDZf4Kg2lw@2x.png)

The variational auto-encoder (VAE) works exactly as autoencoder except that ...

You can see the architecture of VAE in Figure 2.

1. The encoder generates latent variable $z$ with probability distribution $q\left(z \mid x\right)$, and
2. The decoder generates reconstructed datapoint $\hat x$ with probability distribution $p\left(\hat x \mid z\right)$.
3. The encoder and decoder have different parameters. You can write $q\left(z \mid x\right)$ as $q_\theta\left(z \mid x\right)$ and write  $p\left(\hat x \mid z\right)$ as  $p_\gamma\left(\hat x \mid z\right)$ where $\theta$ and $\gamma$ represent the parameters of encoder and decoder. But it's redundant since we don't care about them in this section.

# Tricks

## Assumptions

Latent variable $z = [z_1, z_2, \cdots, z_m]^T$.

In VAE, we assume $q(z \mid x)=\mathcal{N}(\mu, \Sigma)$ where $\mu$ and $\Sigma$ are the mean and the covariance matrix of the latent variable $z$.

Also, we assume that all the elements of $z$ are indeoendent. As a result, $\Sigma$ is a diagonal matrix and every element $z_i$ ($i \in \{1,\cdots,m\}$) has a standard nomal distribution, i.e.,
$$
z_i \sim \mathcal N(0,1), i \in \{1,2,\cdots,m\}.
$$

## Reparameterization

For BP, $Z$ is converted to:
$$
z=\mu+\sigma \cdot \boldsymbol{\epsilon}
$$
where:

1. $z = [z_1, z_2, \cdots, z_m]^T$.
2. $\mu = [\mu_1, \mu_2, \cdots, \mu_m]^T$.
3. $\sigma = [\sigma_1, \sigma, \cdots, \sigma_m]^T$.

## Log var trick

Instead of using a variance vector, $\sigma = [\sigma_1, \sigma, \cdots, \sigma_m]^T$, we use the **log-var vector** to allow for positive and negative values: $\log \left(\sigma^2\right)$

Why can we do this?
$$
\begin{aligned}
\log \left(\sigma^2\right) & =2 \cdot \log (\sigma) \\
\log \left(\sigma^2\right) / 2 & =\log (\sigma) \\
\sigma & =e^{\log \left(\sigma^2\right) / 2}
\end{aligned}
$$

So, when we sample the points, we can do
$$
z=\mu+e^{\log \left(\sigma^2\right) / 2} \cdot \epsilon
$$


# Loss function of VAE

![img](https://miro.medium.com/v2/resize:fit:1400/1*Q5dogodt3wzKKktE0v3dMQ@2x.png)

## ELBO

The loss function of VAE is called **Evidence Lower BOund (ELBO)** loss:
$$
\mathrm{ELBO \ loss} = \mathrm{Reconstruction \ Loss} + \mathrm{KL \ divergence} .
$$
As you can see, the ELBO loss is simply the formarly discussed recontruction loss plus a [KL divergence](https://lyk-love.cn/2024/01/18/relative-entropy-or-kl-divergence/).

## Reconstruction loss

The reconstruction loss, written as
$$
\mathrm{Reconstruction \ Loss} = -\mathbb{E}_{z \sim q_w(z \mid x)}\left[\log p\left(\hat x \mid z\right)\right] ,
$$
**ensures good recostruction**. 



It's typicalley the simple MSE (Mean Squared Error) loss:
$$
\mathrm{Reconstruction \ Loss} =  \| x -\operatorname{Dec}(\operatorname{Enc}(x)) \|_2^2=\sqrt{\sum_{i=1}^n\left(x_i- \hat x_i\right)^2}
$$
where $\operatorname{Dec}$ and $\operatorname{Enc}$ represent decoder and encoder, and $\hat x$ is the reconstructed datapoint.

## KL divergence

The KL divergence is written as
$$
\mathrm{K L}\left[q\left(z \mid x \right) \| p(z)\right] .
$$
In VAE's case we have:

1. the encoder distribution (true distribution) $q(z \mid x)=\mathcal{N}(\mu, \Sigma)$ and 
2. the latent prior (assumed distribution) $p(z)=\mathcal{N}(0, I)$.

As a result, we obtain
$$
\mathrm{K L}\left[q\left(z \mid x \right) \| p(z)\right] = \mathrm {KL} \left [\mathcal{N}(\mu, \Sigma) \| \mathcal{N}(0, I)] \right .
$$
It's physical meaning is obvious: It **ensures latent space is continuous and follows stanard normal distribution**. 

//**TODO** What is the meaning of "follows stanard normal distribution"?

## Deriviation of KL-divergence

[Source: Deriving the KL divergence loss for VAEs](https://stats.stackexchange.com/a/370048)

Recalling the [KL divergence for $n$-dimensional Gaussians]() $p_1=\mathcal{N}\left(\mu_1, \Sigma_1\right)$ and $p_2=\mathcal{N}\left(\mu_2, \Sigma_2\right)$ is:
$$
\mathrm{KL}\left(p_1 \| p_2\right) = 
\frac{1}{2}
\left[
\log \frac{\left|\Sigma_2\right|}{\left|\Sigma_1\right|}
-
n+\operatorname{tr}\left\{\Sigma_2^{-1} \Sigma_1\right\}
+
\left(\mu_2-\mu_1\right)^T \Sigma_2^{-1}\left(\mu_2-\mu_1\right)\right
] .
$$


In the VAE case

1. the encoder distribution is $q(z \mid x)=\mathcal{N}(\mu, \Sigma)$ and 
2. the (assumed) latent prior is given by $p(z)=\mathcal{N}(0, I)$.

Both are multivariate Gaussians of dimension $n$.

Substitute the encoder distribution and latent prior into the preceeding fomular, we obtain:
$$
\begin{aligned}
\mathrm{KL}[q(z \mid x) \| p(z)]
& = \mathrm{KL}[\mathcal{N}(\mu, \Sigma) \| \mathcal{N}(0, I)] \\
& =\frac{1}{2}\left[\log \frac{\left|\Sigma_2\right|}{\left|\Sigma_1\right|}-n+\operatorname{tr}\left\{\Sigma_2^{-1} \Sigma_1\right\}+\left(\mu_2-\mu_1\right)^T \Sigma_2^{-1}\left(\mu_2-\mu_1\right)\right] \\
& =\frac{1}{2}\left[\log \frac{|I|}{|\Sigma|}-n+\operatorname{tr}\left\{I^{-1} \Sigma\right\}+(\overrightarrow{0}-\mu)^T I^{-1}(\overrightarrow{0}-\mu)\right] \\
& =\frac{1}{2}\left[-\log |\Sigma|-n+\operatorname{tr}\{\Sigma\}+\mu^T \mu\right] \\
& =\frac{1}{2}\left[-\log \prod_i \sigma_i^2-n+\sum_i \sigma_i^2+\sum_i \mu_i^2\right] \\
& =\frac{1}{2}\left[-\sum_i \log \sigma_i^2-n+\sum_i \sigma_i^2+\sum_i \mu_i^2\right] \\
& =\frac{1}{2}\left[-\sum_i\left(\log \sigma_i^2+1\right)+\sum_i \sigma_i^2+\sum_i \mu_i^2\right] \\
& = -\frac{1}{2} \sum_i \left[1+\log \left(\sigma^2\right)-\mu^2-\sigma^2\right]
\end{aligned}
$$
where $\mu_1=\mu, \Sigma_1=\Sigma, \mu_2=\overrightarrow{0}, \Sigma_2=I$.

```python
kl_div = -0.5 * torch.sum(1 + z_log_var 
                                      - z_mean**2 
                                      - torch.exp(z_log_var), 
                                      axis=1) # sum over latent dimension
```

