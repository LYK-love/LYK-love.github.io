---
title: Cross Entropy Loss
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-03-09 23:34:56
---


Sources:

* Adjrej Karpathy's video [Building makemore Part 4: Becoming a Backprop Ninja](https://www.youtube.com/watch?v=q8SA3rM6ckI&list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ&index=5&t=5798s).

<!--more-->

# Cross entropy

The cross entropy loss $L$ of a sample is
$$
L = -\sum_{i=1}^C y_{i} \log \left(\hat y_{i}\right) .
$$

where $\hat{y}_i$ is the predicted probability for class $i$, usually obtained by applying the softmax function to the logit of $i$, denoted as $z_i$:
$$
\hat y_i = \text{softmax}(z_i)  =\frac{e^{z_i}}{\sum_{j=1}^C e^{z_j}} .
$$

For classification tasks where there is only **one true class** for a sample, i.e., $y_c \in \{0,0, \cdots, 1, 0, \cdots \}$, suppose the index of the true class of the input data point is $t$, we obtain
$$
L=- (0 + \cdots + 0+1 \cdot \log (\hat y_t) + 0 + \cdots+0) = - \log (\hat y_t)
$$

Note that, in this case, $L$ is only related to $\hat y_t$:
$$
\hat{y}_t=\frac{e^{z_t}}{\sum_{j=1}^C e^{z_j}} .
$$



# Derivation of cross entropy

**Question**: What is the gradient (more strictly, the derivation) of the cross-entropy loss w.r.t. a logit $z_k$ ?



To get the gradient, we need to differentiate the loss $L$ with respect to $z_i$:



Using the expression for $L$ and $\hat{y}_i$, we get:
$$
\frac{\partial L}{\partial z_i}=\frac{\partial L}{\partial \hat{y}_t} \cdot \frac{\partial \hat{y}_t}{\partial z_i}
$$

Given $L=-\log \left(\hat{y}_t\right)$, we have:
$$
\frac{\partial L}{\partial \hat{y}_t}=-\frac{1}{\hat{y}_t}
$$

For $\frac{\partial \hat{y}_t}{\partial z_k}$, there are two cases to consider:

1. When $i=t$, the derivative of the softmax function w.r.t. $z_k$ is:
   $$
   \frac{\partial \hat{y}_t}{\partial z_i}=\frac{e^{z_i} \sum_{j=1}^C e^{z_j}-e^{z_i} e^{z_i}}{\left(\sum_{j=1}^C e^{z_j}\right)^2}=\frac{e^{z_i}}{\sum_{j=1}^C e^{z_j}}\left(1-\frac{e^{z_i}}{\sum_{j=1}^C e^{z_j}}\right)=\hat{y}_t\left(1-\hat{y}_t\right) .
   $$

2. When $i \neq t$, the derivative of the softmax function w.r.t. $z_k$ is:
   $$
   \frac{\partial \hat{y}_t}{\partial z_i}=\frac{ e^{z_i} (0- e^{z_k})}{\left(\sum_{j=1}^C e^{z_j}\right)^2}=-\frac{e^{z_i}}{\sum_{j=1}^C e^{z_j}} \cdot \frac{e^{z_i}}{\sum_{j=1}^C e^{z_j}}=-\hat{y}_t \hat{y}_i .
   $$



Putting it all together, the gradient of the loss w.r.t. $z_k$ is:

1. If $i=t$ (for the true class):
   $$
   \frac{\partial L}{\partial z_k}=\hat{y}_i-1 \triangleq \text{softmax}(z_i) - 1 .
   $$

2. If $i \neq t$ (for the other classes):
   $$
   \frac{\partial L}{\partial z_k}=\hat{y}_i \triangleq \text{softmax}(z_i) .
   $$

To conclude:
$$
\frac{\partial L}{\partial z_i}= \begin{cases}\operatorname{softmax}\left(z_i\right)-1, & i=t \\ \operatorname{softmax}\left(z_i\right), & i \neq t\end{cases}
$$

