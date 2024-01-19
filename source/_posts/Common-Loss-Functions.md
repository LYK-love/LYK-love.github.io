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

# Notations

TO make the context clear, in this article, we make the following regulations:

* The size of the dataset, i.e., the number of the datapoints, is denoted as $N$.
* The ground truth label value of the $i^{\text{th}}$ datapoint is $y_i$.
* The predicted value of the $i^{\text{th}}$ datapoint output by the model is $p_i$.
* When the task is a classification task, the ground truth value is often a label, i.e., $y_i \in \{0,1\}, \forall i$.
* When the task is a classification task, the number of classes is $C$. In addition, the ground truth label value and the prediction value of $c^{\text{th}}$ class of the $i^{\text{th}}$ datapoint is $y_{c}, p_{c}$.



# Cross Entropy

[--> Youtube: Cross Entropy](https://www.youtube.com/watch?v=6ArSys5qHAU)



Cross-entropy loss (often abbreviated as CE), or log loss, measures the performance of a <u>classification</u> model whose output is a probability value between 0 and 1 (usually produced by a [softmax function]()).

For the $i^{\text{th}}$ datapoint, the cross entropy is
$$
-\sum_{c=1}^C y_{c} \log \left(p_{c}\right) .
$$


When $N=2$, the cross-entropy can be calculated as:
$$
-[y \log (p)+(1-y) \log (1-p)]
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

## Problems

The main problem of cross entropy is that, even when the prediction is correct, i.e., `y_predicted == y_true`, the cross entropy isn't symmetric.

![A Problem of Cross Entropy](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/A%20Problem%20of%20Cross%20Entropy.png)

From this figure, if `y_predicted == y_true == 0.2`, their CE is `0.3218...`. If `y_predicted == y_true == 0.8`, their CE is `0.178514`. They're not equal!

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

# Dice Loss

[--> Source](https://medium.com/mlearning-ai/understanding-evaluation-metrics-in-medical-image-segmentation-d289a373a3f)

Dice Loss was originally designed for **binary classification** problems, particularly in the context of binary segmentation where you're often distinguishing between the foreground and the background.

## Dice Coefficient

It's derived from Dice Coefficient, which is a statistic used to gauge the similarity of two samples.

![img](https://miro.medium.com/v2/resize:fit:1400/1*tSqwQ9tvLmeO9raDqg3i-w.png)For the $i^{\text{th}}$ datapoint, the Dice Coefficient is
$$
\mathrm{Dice}=\frac{2 \times \sum_i \left(p_i \times y_i\right)}{\sum_i p_i+\sum_i y_i} .
$$

```python
def dice_coef(groundtruth_mask, pred_mask):
    intersect = np.sum(pred_mask*groundtruth_mask)
    total_sum = np.sum(pred_mask) + np.sum(groundtruth_mask)
    dice = np.mean(2*intersect/total_sum)
    return round(dice, 3) #round up to 3 decimal places
```



## Dice Loss

The Dice Loss is
$$
\mathrm{DL} = 1 - \mathrm{Dice} .
$$

```python
def dice_loss(groundtruth_mask, pred_mask):
	return 1 - dice_coef(groundtruth_mask, pred_mask)
```



# IoU

[--> Source](https://medium.com/mlearning-ai/understanding-evaluation-metrics-in-medical-image-segmentation-d289a373a3f)

![img](https://miro.medium.com/v2/resize:fit:1400/1*YYvTr7sBgbDNHrnVG2upqQ.png)

**Jaccard index**, also known as **Intersection over Union (IoU)**, is the area of the intersection over union of the predicted segmentation and the ground truth
$$
\mathrm{I o U}=\frac{T P}{T P+F P+F N}
$$




```python
def iou(groundtruth_mask, pred_mask):
    intersect = np.sum(pred_mask*groundtruth_mask)
    union = np.sum(pred_mask) + np.sum(groundtruth_mask) - intersect
    iou = np.mean(intersect/union)
    return round(iou, 3)
```

