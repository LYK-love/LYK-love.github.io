---
title: Gaussian Channel
tags:
---

The most important continuous alphabet channel is the Gaussian channel depicted in Figure 9.1. This is a time-discrete channel with output $Y_i$ at time $i$, where $Y_i$ is the sum of the input $X_i$ and the noise $Z_i$. The noise $Z_i$ is drawn i.i.d. from a Gaussian distribution with variance $N$. Thus,
$$
Y_i=X_i+Z_i, \quad Z_i \sim \mathcal{N}(0, N)
$$

The noise $Z_i$ is assumed to be independent of the signal $X_i$. This channel is a model for some common communication channels, such as wired and wireless telephone channels and satellite links. Without further conditions, the capacity of this channel may be infinite. If the noise variance is zero, the receiver receives the transmitted symbol perfectly. Since $X$ can take on any real value, the channel can transmit an arbitrary real number with no error.

If the noise variance is nonzero and there is no constraint on the input, we can choose an infinite subset of inputs arbitrarily far apart, so that they are distinguishable at the output with arbitrarily small probability of error. Such a scheme has an infinite capacity as well. Thus if the noise variance is zero or the input is unconstrained, the capacity of the channel is infinite.

The most common limitation on the input is an energy or power constraint. We assume an average power constraint. For any codeword $\left(x_1, x_2, \ldots, x_n\right)$ transmitted over the channel, we require that
$$
\frac{1}{n} \sum_{i=1}^n x_i^2 \leq P .
$$

This communication channel models many practical channels, including radio and satellite links. The additive noise in such channels may be due to a variety of causes. However, by the central limit theorem, the
