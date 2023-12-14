---
title: Structured World Model
tags:
---



Source:

* [Thomas Kipf - Learning Structured Models of the World @ UCL DARK](https://www.youtube.com/watch?v=oLKwRBeBRRA)
* [[PhD Thesis Defense] Learning Structured World Models From and For Physical Interactions](https://www.youtube.com/watch?v=8eof6F4-r0k)

# Important People

* [Thomas Kipf](https://tkipf.github.io/#footer)
* [Yunzhu Li](https://yunzhuli.github.io/)

# Slot centric neural networks

[*Object-Centric Learning with Slot Attention*](https://arxiv.org/abs/2006.15055)

Use attention,

![image-20231212213451552](/Users/lyk/Library/Application Support/typora-user-images/image-20231212213451552.png)

# Object-Factorized Representations

[*Contrastive Learning of Structured World Models*](https://arxiv.org/abs/1911.12247)

Goal: take into account the **compositional nature of visual scenes**, and hence we would like to learn a relational and object-oriented model of the environment that operates on a factored abstract state space $\mathcal{Z}=\mathcal{Z}_1 \times \ldots \times \mathcal{Z}_K$, where $K$ is the number of available object slots. We further assume an object-factorized action space $\mathcal{A}=\mathcal{A}_1 \times \ldots \times \mathcal{A}_K$. 

This factorization ensures that each object is independently represented and it allows for efficient sharing of model parameters across objects in the transition model. 

This serves as a strong inductive bias for better generalization to novel scenes and facilitates learning and object discovery. The overall C-SWM model architecture using object-factorized representations is shown in Figure 1.



![image-20231212213218696](/Users/lyk/Library/Application Support/typora-user-images/image-20231212213218696.png)

1. Decomposition -> Endoder -> Transition model and latent space -> Contrastive loss
2. GNN is not important and can be replaced with other models.
3. Constrastive loss can make the model only focus on states changeed by actions. But it's **hard to train**.

