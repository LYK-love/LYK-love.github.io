---
title: Structured World Models
tags:
---

* Supervised-learning: 训练速度快, 但是
  1. 不可持续, 因为没那么多数据
  2. 永远无法超过demonstration
* MFRL: 训练简单, 但是:
  * Sample efficiency
  * 不是人类学习的方式.
* MBRL:
  * Unstructured System.
  * lossy compression
* Gato: generalist agent. 就是multi-moda的transformer. 但是是supervised的, 虽然能transfer, 但没有证明说某一种representation可以帮助另一种representation的任务(比如, 训练了文本数据后, 对图像数据的任务并没有什么帮助)
* Dreamer: fixed parameter! Scaling!
* Structured World Models:在 图像 -> VAE -> RNN -> VAE的pipeline中插入一个structure的过程, 就是说输入虽然都是图像, 但根据任务的不同而采取不同的抽象表示($z_t$). 缺点是not task agnostic.
  * 并非多模态.



我觉得插入structure这一点很可行. 至于task agnostic.. 我不知道神经科学上的结论是什么, 是不是人类本来就对不同任务有不同的表示?

