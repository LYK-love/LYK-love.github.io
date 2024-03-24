---
title: Initiazlization Methods of Neural Networks
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
---



Paper: [Delving Deep into Rectifiers:
Surpassing Human-Level Performance on ImageNet Classification](https://arxiv.org/pdf/1502.01852.pdf)



[Kaiming initialization](https://pytorch.org/docs/stable/nn.init.html)

The method is described in Delving deep into rectifiers: Surpassing human-level performance on ImageNet classification He, K. et al. (2015). The resulting tensor will have values sampled from $\mathcal{N}\left(0, \operatorname{std}^2\right)$ where
$$
\text{std} =\frac{\text { gain }} {\sqrt{ \mathrm{fan\_mode}} }
$$

Also known as He initialization.



| nonlinearity      | gain                                           |
| ----------------- | ---------------------------------------------- |
| Linear / Identity | $1$                                            |
| Conv{1,2,3}D      | $1$                                            |
| Sigmoid           | $1$                                            |
| Tanh              | $\frac {5} {3}$                                |
| ReLU              | $\sqrt {2}$                                    |
| Leaky Relu        | $\sqrt{\frac{2}{1+\text{ negative\_slope}^2}}$ |
| SELU              | $\frac {3} {4}$                                |

[torch.std](https://pytorch.org/docs/stable/generated/torch.std.html)

[torch.var](https://pytorch.org/docs/stable/generated/torch.var.html)

[Bessel's Correction](https://mathcenter.oxford.emory.edu/site/math117/besselCorrection/)



```python
# BatchNorm parameters

# gamma
bngain = torch.ones((1, n_hidden))

# beta
bnbias = torch.zeros((1, n_hidden))

# BatchNorm layer
# -------------------------------------------------------------
bnmeani = hpreact.mean(0, keepdim=True)
bnstdi = hpreact.std(0, keepdim=True)
hpreact = bngain * (hpreact - bnmeani) / bnstdi + bnbias
```

