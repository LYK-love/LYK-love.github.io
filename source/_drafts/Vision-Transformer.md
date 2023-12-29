---
title: Vision Transformer
tags:
---

Source:

1. [Vision Transformer Quick Guide - Theory and Code in (almost) 15 min](https://youtu.be/j3VNqtJUoz0?si=zl5uRy9hNiA9Henz)
2. [Colab Notebook](https://colab.research.google.com/drive/1P9TPRWsDdqJC6IvOxjG2_3QlgCt59P0w?usp=sharing#scrollTo=w0a8TAbg3KQd)
3. [ViT paper](https://arxiv.org/abs/2010.11929)
4. [PyTorch implementation of ViT  and its variations](https://github.com/lucidrains/vit-pytorch)





![Model overview](/Users/lyk/Library/Application Support/typora-user-images/image-20231227231845140.png)

We split an image into **fixed-size patches**, linearly embed each of them, add position embeddings, and feed the resulting sequence of vectors to a standard Transformer encoder.

 In order to perform classification, we use the standard approach of adding an extra learnable “classification token” to the sequence. 



* Just use the encoder part of the Transformer.
