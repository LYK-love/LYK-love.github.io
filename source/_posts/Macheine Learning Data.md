---
title: Macheine Learning Data
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2023-12-22 22:46:52
---


The concepts of datasets, samples, labels in Machine Learning.

Source:

1. Mu Li et al. *[1. Introduction. Dive into Deep Learning](http://d2l.ai/chapter_introduction/index.html)*.

1. [Cross-validation: evaluating estimator performance](https://scikit-learn.org/stable/modules/cross_validation.html#cross-validation-evaluating-estimator-performance)

<!--more-->

# Requirements

Python: 3.12

OS: Ubuntu22.04, x86_64

Requirements:

```text
scikit-learn==1.3.2
matplotlib==3.8.2
```

# Data

> In order to work with data usefully, we typically need to come up with a suitable **numerical representation.** 

* Let $D = \{ x_1,x_2,..,x_m \}$ detotes the dataset of $m$ data points. Each data point (or example,  data instance, sample) $x_i$ is described as a set of attributes  (or features).  Say each data point has $d$ features, then it can be represented as a $d$-dimention vector
  $$
  x_i=\{ x_{i1}, x_{i2}, \dots, x_{id} \},
  $$
  

  where $x_{ij}$ is the value on the $j$-th feature of data point $x_i$, $d$ is called the *dimensionality* of $x_i$.

* In supervised learning, each sample has a special feature "label". The goal of supervised learning is to predict the value of the label.

* When the context is clear,we usually refer to "samples" as those with labels. It's not confusing.

* The splitting of the dataset: Doing well on the training data does not guarantee that we will do well on unseen data.  So we will typically want to 

* Partition of a dataset: Learning the parameters of a prediction function and testing it on the same data is a methodological mistake: a model that would just repeat the labels of the samples that it has just seen would have a perfect score but would fail to predict anything useful on yet-unseen data. This situation is called **overfitting**. To avoid it, it is common practice to <u>split the dataset into two partitions</u>: 
  1. the ***training dataset*** (or *training set*), for learning model parameters.
  2. the ***test dataset*** (or *test set*), which is held out for evaluation.
* The quality of data: We need the *right* data, which includes the comleteness of the features, the comleteness of the samples and ethics, etc.

  * Imagine applying a skin cancer recognition system in the wild that had never seen black skin before.

  * 例如, 如果某个诊断皮肤癌的系统从未见过黑人, 那么由于黑人在数据中没有被表示过, 即样本不完备, 可能形成误诊.

  * 再例如, ML模型可能无意中捕捉到历史上的不公正现象, 并将其自动化. 假设一个招聘系统学习其历史数据, 而该公司素来有歧视女性员工的传统, 该系统很可能会学习“选雇佣男性”这一倾向.

# Partition of a dataset

```python
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn import datasets
from sklearn import svm
from sklearn import metrics
```



Load the data from a dataset.

```python
# Load iris data.
# Each example is a 4-D vector, and each label is a 1-D scalar.
# 150 data points in total.
X, y = datasets.load_iris(return_X_y=True)
print(f"Shape of examples: {X.shape}")
print(f"Shape of labels: {y.shape}")
```



We can partition the dataset and use 60% of it as the training set, 40% as testing set:

```python
ratio_of_testing_set = 0.4

# `random_state` is used as a random seed to shuffle the dataset before splitting.
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=ratio_of_testing_set, random_state=0)
print(f"In Training Set, shape of samples{X_train.shape}, shape of labels: {y_train.shape}")
print(f"In Testing Set, shape of samples{X_test.shape}, shape of labels: {y_test.shape}")
```



Then we traing an model, say SVM, on the training set and evaluate it on the testing set:

```python
clf = svm.SVC(kernel='linear', C=1).fit(X_train, y_train)
score = clf.score(X_test, y_test)
print(f"Score of SVM on testing set, using {ratio_of_testing_set} of total dataset as testing set: {score}")
```

## Drawbacks

However, this method has two drawbacks

1. By partitioning the available data into three sets, we drastically reduce the number of samples which can be used for learning the model, 
2. and the results can **depend on a particular random choice** for the pair of (train, validation) sets. For instance, how to we know which part of dataset shoule be chosn as testing set, [0, 0.4], [0.3, 0.7] or [0.6, 1.0]? The  decision depends on the random seed `random_state`.

## Cross Validation

A solution to this problem is a procedure called [cross-validation](https://en.wikipedia.org/wiki/Cross-validation_(statistics)) (CV for short). 

The basic approach, called *k*-fold CV, is as follows:

1. the dataset is split into *k* smaller sets. 
2. Choose one set as the testing set.
3. The left  $k-1$ sets are merged as the traing set.
4. Use this partition to train and evalute our model, get one score. 
5. Then redo step 2-4 for $k$ times, each iteration choose a different set as the testing set.
6. The final score is the mean of all the scores in the iterations.
7. Evaluate the model on the testing set.

![A depiction of a 5 fold cross validation on a training set, while holding out a test set.](https://scikit-learn.org/stable/_images/grid_search_cross_validation.png)

```python
# Example of 5-fold cross validation.
fold_num = 5
scores = cross_val_score(clf, X, y, cv=fold_num, scoring='f1_macro')
print(f"Scores of SVM on testing set, using {fold_num}-fold cross validation:")

idx = 0
for score in scores:
    print(f"    {idx}. {score}")
    idx+=1

print(f"Accuracy(expectation of scores): {scores.mean():.2f}")
print(f"Standard deviation: {scores.std():.2f}")
```

This approach can be computationally expensive, but does not waste too much data

# Confusion Matrix

A confusion matrix is a table that is often used to evaluate the performance of a classification algorithm. It provides a summary of the number of correct and incorrect predictions made by a classifier on a dataset. The matrix has four entries, which are typically described as True Positive (TP), True Negative (TN), False Positive (FP), and False Negative (FN). These entries are organized in a table like this:

| Predicted \ Actual | Positive | Negative |
| ------------------ | -------- | -------- |
| Positive           | TP       | FP       |
| Negative           | FN       | TN       |

Here's what each term in the confusion matrix represents:

1. **True Positive (TP):** The classifier correctly predicted instances of the positive class. For example, the classifier correctly identified emails as spam.
2. **True Negative (TN):** The classifier correctly predicted instances of the negative class. For example, the classifier correctly identified non-spam emails.
3. **False Positive (FP):** Also known as a Type I error, this occurs when the classifier incorrectly predicts positive instances when the actual class is negative. For example, the classifier incorrectly identifying a non-spam email as spam.
4. **False Negative (FN):** Also known as a Type II error, this occurs when the classifier incorrectly predicts negative instances when the actual class is positive. For example, the classifier incorrectly identifying a spam email as non-spam.

From the confusion matrix, various performance metrics can be calculated to assess the performance of a classifier, including:

- **Accuracy:** (TP + TN) / (TP + TN + FP + FN)
- **Precision:** TP / (TP + FP)
- **Recall (Sensitivity or True Positive Rate):** TP / (TP + FN)
- **Specificity (True Negative Rate):** TN / (TN + FP)
- **F1 Score:** 2 * (Precision * Recall) / (Precision + Recall)

# ROC and AUC

```python
from matplotlib import pyplot as plt
from sklearn.datasets import load_breast_cancer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_curve, auc
```

ROC (Receiver Operating Characteristic): ROC is a graphical representation of a classification model's  performance across various discrimination thresholds.

The ROC curve is created by <u>plotting the true positive rate against the false positive  rate</u> for different threshold values.

```python
# Load breast cancer data.
# Each example is a 30-D vector, and each label is a 1-D scalar.
# 4-class classification
X, y = load_breast_cancer(return_X_y=True)
clf = LogisticRegression(solver="liblinear", random_state=0).fit(X, y)

y_hat = clf.predict_proba(X)[:, 1] # # Select all rows, but only the second column.

# Compute ROC curve
# fpr: false positive  rate
# tpr: true positive rate
fpr, tpr, thresholds = roc_curve(y, y_hat)
```



AUC (Area Under the ROC Curve): represents the <u>area</u> under the ROC curve. It provides a single scalar value that quantifies the classifier's ability to discriminate between  the positive and negative classes. 

* A higher AUC indicates better  discrimination. 
* The AUC value ranges from 0 to 1, where 0.5 suggests no  discrimination (similar to random guessing), and 1 indicates perfect  discrimination.

```python
# Compute AUC score
roc_auc = auc(fpr, tpr)

# Plot ROC curve
plt.figure(figsize=(8, 8))
plt.plot(fpr, tpr, label=f'AUC = {roc_auc:.2f}')
plt.plot([0, 1], [0, 1], linestyle='--', color='gray', label='Random')
plt.title('Receiver Operating Characteristic (ROC) Curve')
plt.xlabel('False Positive Rate (FPR)')
plt.ylabel('True Positive Rate (TPR)')
plt.legend()
plt.show()
```



