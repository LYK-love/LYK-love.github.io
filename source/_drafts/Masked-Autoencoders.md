---
title: Masked Autoencoders
tags:
---

Source:

* [Masked Autoencoders paper](https://arxiv.org/pdf/2111.06377.pdf)



![MAE architecture](/Users/lyk/Library/Application Support/typora-user-images/image-20231227230817613.png)



During pre-training, a large random subset of image patches (*e.g*., **75%**) is masked out. 



The encoder is applied to the small subset of *visible patches*. Mask tokens are introduced *after* the encoder, and the full set of encoded patches and mask tokens is processed by a small decoder that reconstructs the original image in pixels. After pre-training, the decoder is discarded and the encoder is applied to uncorrupted images (full sets of patches) for recognition tasks.

