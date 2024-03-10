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
* The datapoint of index $i$ is $x_i \in \mathbb R^{d \times 1}$. The last dimenstion of it is denoted as $y_i \in \mathbb R^{1 \times 1}$.
* The predicted datapoint by the model is, corresponding to $x_i$, is $\hat x_i$. The last dimenstion of it is $\hat y_i$.
* The predicted value of the $i^{\text{th}}$ datapoint output by the model is $p_i$.
* When the task is a classification task, the ground truth value is often a 0/1 label, i.e., $y_i \in \{0,1\}, \forall i$.
* When the task is a classification task, the number of classes is $C$. In addition, the ground truth label value and the prediction value of $c^{\text{th}}$ class of the $i^{\text{th}}$ datapoint is $y_{c}, p_{c}$.

# Mean Squared Error

Mean squared error (MSE) loss is
$$
\mathrm{MSE \ Loss} = \| y_i - \hat y_i \|_2^2=\sqrt{\sum_{i=1}^n\left(y_i- \hat y_i\right)^2} .
$$


```python
import torch

def mse(y_true, y_predicted):
    # Mean Squared Error (MSE) between x and y
    mse = torch.mean((y_true - y_predicted) ** 2)
    print("Mean Squared Error between y and \hat y:", mse.item())
```

# Cross Entropy

See [*Cross Entropy Loss*]().

# Focal Loss

[--> *Focal Loss for Dense Object Detection*](https://arxiv.org/pdf/1708.02002v2.pdf)

A **Focal Loss** function addresses (extreme) **class imbalance** during  training in tasks like object detection. Focal loss applies a modulating term to the cross entropy loss in order to focus learning on hard  misclassified examples. 

Formally, the Focal Loss adds a factor $\left(1-\hat y_t\right)^\gamma$ to the standard [cross entropy]() criterion.
$$
\mathrm{FL}\left(\hat y_t\right)=-\left(1- \hat y_t\right)^\gamma \log \left( \hat y_t\right)
$$

## Property

(In the below figure, the notation $\hat y$ is replaced by $p$)

![FL loss vs. model prediction](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Common%20Loss%20Functions/FL%20loss%20vs.%20model%20prediction.png)



* Setting $\gamma>0$ reduces the relative loss for well-classified examples $\left(\hat y_t>.5\right)$, putting more focus on hard, misclassified examples. Here there is tunable focusing parameter $\gamma \geq 0$.
* One typical use case is in object detection tasks. An image may contain 5 onjects whereas the the number of bounding boxes can be millions. Thus there're enormous <u>negative</u> datapoints. The model can easily learn to judge all data points to be false to achieve a high traing performance.

```python
import torch

def focal_loss(y_true, y_predicted, alpha=0.25, gamma=2.0):
    # First calculate the cross entropy loss using the helper function
    ce_loss = calculate_cross_entropy(y_true, y_predicted)

    # Calculate p_t
    p_t = y_true * y_predicted + (1 - y_true) * (1 - y_predicted)

    # Calculate the modulating factor
    modulating_factor = (1 - p_t) ** gamma

    # Apply the alpha weighting
    alpha_factor = y_true * alpha + (1 - y_true) * (1 - alpha)

    # Calculate the final Focal Loss
    focal_loss = alpha_factor * modulating_factor * ce_loss
    return focal_loss
```



# Dice Loss

[--> Source](https://medium.com/mlearning-ai/understanding-evaluation-metrics-in-medical-image-segmentation-d289a373a3f)

Dice Loss was originally designed for **binary classification** problems, particularly in the context of binary segmentation where you're often distinguishing between the foreground and the background.

## Dice Coefficient

It's derived from Dice Coefficient, which is a statistic used to gauge the similarity of two samples.

![img](https://miro.medium.com/v2/resize:fit:1400/1*tSqwQ9tvLmeO9raDqg3i-w.png)For the $i^{\text{th}}$ datapoint, the Dice Coefficient is
$$
\mathrm{Dice}=\frac{2 \times \sum_i \left(\hat y_i \times y_i\right)}{\sum_i \hat y_i+\sum_i y_i} .
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
