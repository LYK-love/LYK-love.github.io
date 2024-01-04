---
title: Common Loss Functions
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-01-03 22:00:24
---


* Cross entropy
* Focal loss
* Hinge loss
* ...

<!--more-->

# Cross Entropy

[--> Youtube: Cross Entropy](https://www.youtube.com/watch?v=6ArSys5qHAU)



Cross-entropy loss (often abbreviated as CE), or log loss, measures the performance of a <u>classification</u> model whose output is a probability value between 0 and 1 (usually produced by a [softmax function]()).

Suppose there're $N$ classes ( $N \ge 2$), given a data point with true label value $y_c$, the predicted probability, i.e., the output of softmax function is , is $p_c$. Then its cross entropy is 
$$
-\sum_{c=1}^N y_c \log \left(p_c\right)
$$
When $N=2$, it's a binary classification cross-entropy can be calculated as:
$$
-(y \log (p)+(1-y) \log (1-p))
$$

Note: since in classification tasks one data point typocically has only one crorect class. i.e., $y_c \in \{0,0, \cdots, 1, 0, \cdots \}$, suppose the index of the true class of the input data point is $t$, we obtain
$$
\mathrm{CE}\left(p_t\right)=- 1. \log (p_t) = - \log (p_t)
$$




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

# Focal Loss

[--> *Focal Loss for Dense Object Detection*](https://arxiv.org/pdf/1708.02002v2.pdf)

A **Focal Loss** function addresses (extreme) **class imbalance** during  training in tasks like object detection. Focal loss applies a modulating term to the cross entropy loss in order to focus learning on hard  misclassified examples. 

Formally, the Focal Loss adds a factor $\left(1-p_t\right)^\gamma$ to the standard cross entropy criterion.
$$
\mathrm{FL}\left(p_t\right)=-\left(1-p_t\right)^\gamma \log \left(p_t\right)
$$

## Property

![FL loss vs. model prediction](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/FL%20loss%20vs.%20model%20prediction.png)

* Setting $\gamma>0$ reduces the relative loss for well-classified examples $\left(p_t>.5\right)$, putting more focus on hard, misclassified examples. Here there is tunable focusing parameter $\gamma \geq 0$.
* One typical use case is in object detection tasks. An image may contain 5 onjects whereas the the number of bounding boxes can be millions. Thus there're enormous <u>negative</u> datapoints. The model can easily learn to judge all data points to be false to achieve a high traing performance.
