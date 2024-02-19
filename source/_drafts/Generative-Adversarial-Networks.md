---
title: Generative Adversarial Networks
tags:
---

Source:

1. [Stanford CS 231N, Lecture 13, Generative Models](https://youtu.be/5WoItGTWV54?si=51wK-p1pcv2mJPeo)
   * [--> Slides](http://cs231n.stanford.edu/slides/2017/cs231n_2017_lecture13.pdf)

<!--more-->

PixelCNNs define tractable density function, optimize likelihood of training data:
$$
p_\theta(x)=\prod_{i=1}^n p_\theta\left(x_i \mid x_1, \ldots, x_{i-1}\right)
$$

VAEs define intractable density function with latent $\mathbf{z}$ :
$$
p_\theta(x)=\int p_\theta(z) p_\theta(x \mid z) d z
$$

Cannot optimize directly, derive and optimize lower bound on likelihood instead
What if we give up on explicitly modeling density, and just want ability to sample?
GANs: don't work with any explicit density function!
Instead, take game-theoretic approach: learn to generate from training distribution through 2-player game

# Training

Generator network: try to fool the discriminator by generating real-looking images Discriminator network: try to distinguish between real and fake images

Train jointly in minimax game

Minimax objective function:
$$
\min _{\theta_g} \max _{\theta_d}\left[\mathbb{E}_{x \sim p_{\text {data }}} \log D_{\theta_d}(x)+\mathbb{E}_{z \sim p(z)} \log \left(1-D_{\theta_d}\left(G_{\theta_g}(z)\right)\right)\right]
$$

Alternate between:
1. Gradient ascent on discriminator
$$
\max _{\theta_d}\left[\mathbb{E}_{x \sim p_{\text {data }}} \log D_{\theta_d}(x)+\mathbb{E}_{z \sim p(z)} \log \left(1-D_{\theta_d}\left(G_{\theta_g}(z)\right)\right)\right]
$$
2. Gradient descent on generator

$$
\min _{\theta_g} \mathbb{E}_{z \sim p(z)} \log \left(1-D_{\theta_d}\left(G_{\theta_g}(z)\right)\right)
$$


$$
\min _{\theta_g} \max _{\theta_d}[\mathbb{E}_{x \sim p_{\text {data }}} \log \underbrace{\log \underbrace{}_{\theta_d}(x)}_{\substack{\text { Discriminator output } \\
\text { for real data } x}}+\mathbb{E}_{z \sim p(z)} \log (1-\underbrace{\left.D_{\theta_d}\left(G_{\theta_g}(z)\right)\right)}_{\begin{array}{c}
\text { Discriminator output for } \\
\text { generated fake data } \mathrm{G}(\mathrm{z})
\end{array}}]
$$

Discriminator $\left(\theta_d\right)$ wants to maximize objective such that $D(x)$ is close to 1 (real) and $D(G(z))$ is close to 0 (fake)

Generator $\left(\theta_g\right)$ wants to minimize objective such that $D(G(z))$ is close to 1 (discriminator is fooled into thinking generated $G(z)$ is real)

# Projects

* [The GAN zoo](https://github.com/hindupuravinash/the-gan-zoo)
