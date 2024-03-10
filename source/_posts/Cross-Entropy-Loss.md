---
title: Cross Entropy Loss
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-03-09 23:34:56
---


Source:

* Adjrej Karpathy's video [Building makemore Part 4: Becoming a Backprop Ninja](https://www.youtube.com/watch?v=q8SA3rM6ckI&list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ&index=5&t=5798s).

<!--more-->

# Cross Entropy

[--> Youtube: Cross Entropy](https://www.youtube.com/watch?v=6ArSys5qHAU)



Cross-entropy loss (often abbreviated as CE), or log loss, measures the performance of a <u>classification</u> model whose output is a probability value between 0 and 1 (usually produced by a [softmax function]()).



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



```python
import torch

def calculate_cross_entropy(y_true, y_predicted):
    '''
    :param y_predicted: The predicted, often by model, distribution of data point y.
    :param y_true: The true distribution of data point y.
    :return: the cross entropy of p_predicted, given the fact that the true distribution is y_true.
    Note: y_predicted and y_true are  multi-variance distributions if X is multidimensional.
    '''
    # Ensure that p_predict and y_true have the same length
    if y_predicted.shape != y_true.shape:
        raise ValueError("Tensors p_predict and y_true must have the same shape")

    # Avoid log(0) situation
    epsilon = 1e-15
    # Clamps all elements of p_predicted in input into the range [ min, max ] where min =epsilon, and max = 1 - epsilon.
    y_predicted = torch.clamp(y_predicted, epsilon, 1 - epsilon)

    # Calculate cross entropy
    cross_entropy = -torch.sum(y_true * torch.log(y_predicted))
    return cross_entropy
```



## Example

For example, consider following neural network, there're three data points "Setosa", "Virginica" and "Versicolor", each is a 2-D vector. The number of classes is $N = 3$ since softmax outputs 3 values.

![Example of NN with softmax](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/Example%20of%20NN%20with%20softmax.png)

| Petal | Sepal | Species    | $p$  | Cross Entropy                     |
| ----- | ----- | ---------- | ---- | --------------------------------- |
| 0.04  | 0.42  | Setosa     | 0.57 | $1 . ({-\log (p)}) + 0 + 0 =0.56$ |
| 1     | 0.54  | Virginica  | 0.58 | $ 0 + 1. {-\log (p)} + 0 =0.54$   |
| 0.50  | 0.37  | Versicolor | 0.52 | $0 + 0 + -\log (p)=0.65$          |

Take Sepal for Versicolor, when input is Versicolor ($[0.50, 0.37]$), the true label value of Versicolor is $1$ and that of others is all $0$.
$$
\begin{aligned}
y_{\text{Setosa}} = 0, \\
y_{\text{Virginica}} = 0, \\
y_{\text{Versicolor}} = 1,
\end{aligned}
$$
The output of softmax corresponding to Versicolor is $p_{\text{Versicolor}} = 0.52$.

Therefore, the cross entropy of this training is
$$
1 . ({-\log (p)}) + 0 + 0 =0.56 .
$$


## Property

![CE loss vs. model prediction](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/CE%20loss%20vs.%20model%20prediction.png)

The graph above shows the range of possible loss values given a true  observation (isDog = 1). As the predicted probability approaches 1, log  loss slowly decreases. As the predicted probability decreases, however, **the log loss increases rapidly**. 

Log loss **heavily penalizes those predictions that are confident and wrong**.

## Problems

The main problem of cross entropy is that, even when the prediction is correct, i.e., `y_predicted == y_true`, the cross entropy isn't symmetric.

![A Problem of Cross Entropy](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/A%20Problem%20of%20Cross%20Entropy.png)

From this figure, if `y_predicted == y_true == 0.2`, their CE is `0.3218...`. If `y_predicted == y_true == 0.8`, their CE is `0.178514`. They're not equal!

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

2. If $i=t$ (for the other classes):
   $$
   \frac{\partial L}{\partial z_k}=\hat{y}_i \triangleq \text{softmax}(z_i) .
   $$

To conclude:
$$
\frac{\partial L}{\partial z_i}= \begin{cases}\operatorname{softmax}\left(z_i\right)-1, & i=t \\ \operatorname{softmax}\left(z_i\right), & i \neq t\end{cases}
$$


