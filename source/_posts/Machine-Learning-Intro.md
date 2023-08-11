---
title: Machine Learning Intro
tags:
- Machine Learning
- Machine Learning
categories: Computer Science
mathjax: true
date: 2022-02-15 21:27:44
---


Outline

* 基本术语
* 模型评估和选择

<!--more-->

# Key Components

## Data

> In order to work with data usefully, we typically need to come up with a suitable **numerical representation.** 

* **Each example (or *data point*, *data instance*, *sample*) typically consists of a set of attributes called *features* (sometimes called *covariates* or *inputs*),** based on which the model must make its predictions. 

  * In supervised learning problems, our goal is to predict the value of a special attribute, called the ***label*** (or *target*), that is not part of the model’s input.

  > E.g., If we were working with image data, each example might consist of an individual photograph (the features) and a number indicating the category to which the photograph belongs (the label). The photograph would be represented numerically as three grids of numerical values representing the brightness of red, green, and blue light at each pixel location. For example, a 200×200 color photograph would consist of 200×200×3=120000 numerical values.

* 定长向量(*fixed-length* vector):  样本的特征数量被称为维度(*dimensionality*). dimensionality固定的样本被称为定长的.

* 不定长向量(*varying-length* vector): 样本的*dimensionality*不固定. 例如图片和文字.

  * 以图片为例, 具有不同分辨率和形状的图片自然就具有不同的维度. 要可以对图片进行裁切(cropping), 将其裁切为一个标准格式来将其转换为fixed-length* vectors, 但这也会损失被裁切掉的信息.
  * 以文字为例, 对于某个电影的评论可能很简短(“it stinks!”), 可能连篇累牍.
  * 深度学习相比其他传统方法的一个优势就是它很擅长处理*varying-length* vectors.

* 数据的质量: We need the *right* data. 这包括了标签的正确性, 特征的完备性和样本的完备性和伦理等.

  * Imagine applying a skin cancer recognition system in the wild that had never seen black skin before.

  * 例如, 如果某个诊断皮肤癌的系统从未见过黑人, 那么由于黑人在数据中没有被表示过, 即样本不完备, 可能形成误诊.

  * 再例如, ML模型可能无意中捕捉到历史上的不公正现象, 并将其自动化. 假设一个招聘系统学习其历史数据, 而该公司素来有歧视女性员工的传统, 该系统很可能会学习“选雇佣男性”这一倾向.

    

## Models

机器学习中的"model"就是一个函数, 将输入的数据映射成一个"预测结果".

> By *model*, we denote the computational machinery for ingesting data of one type, and spitting out predictions of a possibly different type.



## Objective Functions

> In order to develop a formal mathematical system of learning machines, we need to have formal measures of how good (or bad) our models are. 

In machine learning, and optimization more generally, we call these . By convention, we usually define objective functions so that lower is better. This is merely a convention.

* **目标函数(objective functions)**: 用于衡量model好坏的函数, 在ML和optimization中被称为"目标函数".
  * Because lower is better, these functions are sometimes called **loss function**s.

* 常见的目标函数:

  * When trying to predict numerical values, the most common loss function is *squared error*, i.e., the square of the difference between the prediction and the ground truth target. 
  * For classification, the most common objective is to <u>minimize error rate</u>, i.e., the fraction of examples on which our predictions disagree with the ground truth. 

* **替代目标(surrogate objective)**: 由于一些限制(例如难以微分), 有些目标函数难以被优化 (e.g., error rate). 在这种情况下可以优化一个""替代目标"."

* 优化过程: During optimization, we think of the loss as a function of the model’s parameters, and treat the training dataset as a constant. We learn the best values of our model’s parameters by minimizing the loss incurred on a set consisting of some number of examples collected for training. 

* 数据集划分: Doing well on the training data does not guarantee that we will do well on unseen data.  So we will typically want to <u>split the available data into two partitions</u>: 

  * the ***training dataset*** (or *training set*), for learning model parameters.
  * the ***test dataset*** (or *test set*), which is held out for evaluation.

  想象一个学生参与考试, 该学生此前复习(training)了一些习题(训练集). 在考试(evaluation)时, 他对于复习过的习题可能会表现优异, 然而对于没见过的习题(测试集)的表现并不能保证.

* 过拟合(overfitting): When a model performs well on the training set but fails to generalize to unseen data, we say that it is *overfitting* to the training data.



## Optimization Algorithms

> Once we have got some data source and representation, a model, and a well-defined objective function, we need **an algorithm capable of searching for the best possible parameters for minimizing the loss function.** 



Popular optimization algorithms for deep learning are based on an approach called *gradient descent*. In short, at each step, this method checks to see, for each parameter, which direction the training set loss would move if you perturbed that parameter just a small amount. It then updates the parameter in the direction that lowers the loss.



## Data

> 

令$D = \{ x_1,x_2,..,x_m \}$表示包含m个示例的数据集, 每个example(or *data point*, *data instance*, *sample*)由$d$个属性描述, 则每个example被表示为$d$维样本空间中的一个向量$x_i=\{ x_{i1}, x_{i2}, \dots, x_{id} \}$, $x_i \in \chi$, 其中$x_{ij}$是样本$x_i$在第j个属性的取值

![data set](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Artificial%20Intelligence/%E6%95%B0%E6%8D%AE%E9%9B%86.png)



* Each ***example*** typically consists of a set of attributes called **features** (sometimes called *covariates* or *inputs*), based on which the model must make its predictions.

* Label/Target: example的一个属性, 表示该样本所属的分类. 

* Example(or *data point*, *data instance*, *sample*): Each feature–label pair is called an example.

* 

* 用$(x_i,y_i)$表示第i个样例，其中$y_i \in \gamma$是示例$x_i$的标记， $\gamma $ 是所有标记的集合，也就是输出空间

  * 上图的每条record就是一个示例(instance）或样本(sample)

  * In supervised learning problems, our goal is to predict the value of a special attribute, called the *label* (or *target*), that is not part of the model’s input.

  

* **属性空间**(attribute value),**样本空间**(sample  space),**输入空间**: 属性张成的空间，记为$\chi$
* **标记空间**, **输出空间**: label张成的空间，记为 $\gamma $ 
* 如果把属性作为坐标轴, 每个示例都对应特征空间的一个点, 称为**特征向量**(feature  vector), 属性个数就是样本维度
* 
  * 如果把标记看作对象本身的一部分，那么示例也可以看作样本
  * 
* 训练集: 一组训练样例
* 测试集: 一组测试样例

# Kinds of Machine Learning Problems(By Target Value)

根据label的取值情况, 可以将ML任务分类为:

## Classification

分类(Classification):标记为离散值.

* 二分类:例如“Can I eat that mashroom?”. 答案是yes or no.

  ![../_images/death-cap.jpg](http://d2l.ai/_images/death-cap.jpg)



* 多分类:例如"Is that a dog, cat or donky?". 答案是三者之一.



* 多标签分类(Tagging, aka *multi-label classification*): label具有多个类型要预测的类型, 类型间不是互斥的(exclusive),.例如一张图片中可能同时出现狗, 猫, 鸡和驴.

  ![../_images/stackedanimals.png](http://d2l.ai/_images/stackedanimals.png)



## Regression

回归(Regression):label为连续值

## Clustering

聚类(Clustering):标记为空值,对示例进行自动分组( 即: 要分的组也不知道)
* 例如,本地瓜,外地瓜



# Kinds of Machine Learning Problems(By Target)

根据标记的完整情况:

![image-20230802185408108](/Users/lyk/Library/Application Support/typora-user-images/image-20230802185408108.png)

* (有)监督学习:所有示例都有标记
  * 分类,回归.
* 半监督学习:少量示例有标记,大量示例没标记
* 无监督学习:所有示例都没有标记
  * 聚类
* 强化学习
* 噪音标记学习:标记有,但是不完全准确

***

* multi-label classification: The problem of learning to predict classes that are not mutually exclusive is called *multi-label classification*. Auto-tagging problems are typically best described as multi-label classification problems. 

* Sequence Learning: 

  * **Tagging and Parsing**. This involves annotating a text sequence with attributes. Here, the inputs and outputs are *aligned*, i.e., they are of the same number and occur in a corresponding order.

  * **Automatic Speech Recognition**. The challenge is that there are many more audio frames (sound is typically sampled at 8kHz or 16kHz) than text, i.e., there is no 1:1 correspondence between audio and text, since thousands of samples may correspond to a single spoken word. 

  * **Text to Speech**. This is the inverse of automatic speech recognition. 

  * **Machine Translation**. Unlike the case of speech recognition, where corresponding inputs and outputs occur in the same order, in machine translation, unaligned data poses a new challenge. Here the input and output sequences can have different lengths, and the corresponding regions of the respective sequences may appear in different orders. Consider the following illustrative example of the peculiar tendency of Germans to place the verbs at the end of sentences:

    ```txt
    German:           Haben Sie sich schon dieses grossartige Lehrwerk angeschaut?
    English:          Did you already check out this excellent tutorial?
    Wrong alignment:  Did you yourself already this excellent tutorial looked-at?
    ```




## Supervised Learning



![Supervised learning](http://d2l.ai/_images/supervised-learning.svg)



* **有监督学习(Supervised learning)** : Given a dataset containing both features and labels, <u>we (the supervisors) produce a model to predict the labels given input features</u>. 简言之: 

* 在有监督学习中, 我们把样本(example)规定为 feature–label pair. 如果上下文清晰, 即使是label值未知的inputs也可以用 *examples*来指代. 上图中的"Input", "Training inputs"均为没有label的特征集合.

  

  

  * Regression
  * Classification
  * 
  * Recommender Systems
  * Sequence Learning

## Unsupervised Learning

- Another important and exciting recent development in unsupervised learning is the advent of deep generative models. These models estimate the density of the data, either explicitly or *implicitly*. Once trained, we can use a generative model either to score examples according to how likely they are, or to sample synthetic examples from the learned distribution. Early deep learning breakthroughs in generative modeling came with the invention of *variational autoencoders* ([Kingma and Welling, 2014](http://d2l.ai/chapter_references/zreferences.html#id149), [Rezende *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id573)) and continued with the development of *generative adversarial networks* ([Goodfellow *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id92)). More recent advances include normalizing flows ([Dinh *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id575), [Dinh *et al.*, 2017](http://d2l.ai/chapter_references/zreferences.html#id576)) and diffusion models ([Ho *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id557), [Sohl-Dickstein *et al.*, 2015](http://d2l.ai/chapter_references/zreferences.html#id556), [Song and Ermon, 2019](http://d2l.ai/chapter_references/zreferences.html#id558), [Song *et al.*, 2021](http://d2l.ai/chapter_references/zreferences.html#id574)).
- Can we find a small number of prototypes that accurately summarize the data? Given a set of photos, can we group them into landscape photos, pictures of dogs, babies, cats, and mountain peaks? Likewise, given a collection of users’ browsing activities, can we group them into users with similar behavior? This problem is typically known as *clustering*.

## Self-Supervised Learning

A major development in unsupervised learning, has been the rise of *self-supervised learning*, techniques that leverage some aspect of the unlabeled data to provide supervision. For text, we can train models to “fill in the blanks” by predicting randomly masked words using their surrounding words (contexts) in big corpora without any labeling effort ([Devlin *et al.*, 2018](http://d2l.ai/chapter_references/zreferences.html#id58))! For images, we may train models to tell the relative position between two cropped regions of the same image ([Doersch *et al.*, 2015](http://d2l.ai/chapter_references/zreferences.html#id59)), to predict an occluded part of an image based on the remaining portions of the image, or to predict whether two examples are perturbed versions of the same underlying image. Self-supervised models often learn representations that are subsequently leveraged by fine-tuning the resulting models on some downstream task of interest.

## Reinforcement Learning

If you are interested in using machine learning to develop an agent that interacts with an environment and takes actions, then you are probably going to wind up focusing on *reinforcement learning*. This might include applications to robotics, to dialogue systems, and even to developing artificial intelligence (AI) for video games.

*Deep reinforcement learning*, which applies deep learning to reinforcement learning problems, has surged in popularity. The breakthrough deep <u>Q-network</u> that beat humans at Atari games using only the visual input ([Mnih *et al.*, 2015](http://d2l.ai/chapter_references/zreferences.html#id512)), and the AlphaGo program that dethroned the world champion at the board game Go ([Silver *et al.*, 2016](http://d2l.ai/chapter_references/zreferences.html#id260)) are two prominent examples.



Finally, at any given point, reinforcement learners might know of one good policy, but there might be many other better policies that the agent has never tried. The reinforcement learner must constantly choose whether to *exploit* the best (currently) known strategy as a policy, or to *explore* the space of strategies, potentially giving up some short-run reward in exchange for knowledge.



When the environment is fully observed, we call the reinforcement learning problem a ***Markov decision process***. When the state does not depend on the previous actions, we call the problem a ***contextual bandit problem***. When there is no state, just a set of available actions with initially unknown rewards, this problem is the classic ***multi-armed bandit problem***.



## 假设空间

* 假设空间( hypothesis space )：所有假设组成的空间。
  * 学习就是在假设空间中搜索的过程，搜索目标是找到与训练集匹配的假设

* 版本空间（ version space ）： 假设空间的子集，与训练集一致的假设集合
* 归纳偏好：学习过程中对某种类型假设的偏好称作归纳偏好
  * ”到底从版本空间中选择哪一个假设“
  * 可以认为是假设空间（事实上是版本空间）中对假设进行选择的启发式方法
  * 真实假设可以不在版本空间中，因为版本空间只是符合了训练集的假设

## NFL定理

No Free Lunch： 因为未来数据是不知道的,总有一种未来数据的分布让你失败

# 模型评估与选择

## 误差

“错误率”： 分类错误的样本数占样本总数的比例

精度： ，1 - 错误率



误差： 学习器的实际预测输出与样本的真实输出之间的差异

训练误差或**经验误差**： 学习器在训练集上的误差

测试误差或**泛化误差**： 学习器在新样本上的误差

## 过拟合& 欠拟合

* 过拟合： 模型把训练样本学得“太好”时，把训练样本自身的一些特点当作了所有潜在样本都会具有的一般性质。这样会致使泛化性能的下降



* 欠拟合：对训练样本的一般性质尚未学好。
  

## 评估方法

我们可以通过实验测试来对学习器的泛化误差进行评估并进而做出选择。 为此要选出测试集，然后以测试集上的“测试误差”来作为泛化误差的近似。 测试集要尽可能与训练集互斥



数据集规模有限，要分为训练集和测试集，有如下划分方法：

* 留出法： 直接将数据集划分为两个互斥集合
  *  测试/训练集要尽可能保持数据分布的一致性

* 交叉验证法
* 自助法

## 性能度量

性能度量是衡量模型泛化能力的评价标准，反映了任务需求



回归任务： 

* 均方误差



分类任务：

* 错误率，精度
* 查准率，查全率



下面主要介绍回归任务的性能度量

### 错误率和精度

* 错误率是分类错误的样本数占样本总数的比例， 精度相反

### 查准率，查全率和F1

查准率：预测出来的正例中正确的比率（分母是被认为为真的样例数）

查全率：正例被预测出来的比率（ 分母是确实为真的样例数 ） 



 混淆矩阵：真实标记和预测结果的组合：

![confusion matrix](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Artificial%20Intelligence/confusion%20matrix.png)

注意FP被认为是正例，实际是反例



可以根据学习器的预测结果对样例进行排序，并逐个把样本作为正例进行预测，则可以得到查准率-查全率曲线，简称“P-R”曲线

![P-R curve](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Artificial%20Intelligence/P-R%20curve.png)

如果一个学习器的P-R曲线被另一个的完全包住，我们可以认为前者的性能小于后者，但有时会发生曲线交叉的情况，此时需要设计综合考虑P,R的度量，比如“平衡点”

平衡点（Break-Even Point）是曲线上“查准率=查全率”时的取值，可用于度量P-R曲线有交叉的分类器性能高低

BEP太简单，更常用的是F1度量：


$$
F1 = \frac{2 \times P \times R}{P + R}
$$


比F1更一般形式的 $F_{\beta}$:
$$
F_{\beta} = \frac{ 1 + \beta^2 \times P \times R}{ ( \beta^2 \times P ) + R }
$$
$\beta$是启发值，可以表示模型对查准/查全率的偏好

*  $\beta = 1$: 标准 F1
*  $\beta > 1$:偏重查全率
*  $\beta 《 1$: 偏重查准率



### ROC

 ROC曲线纵轴是“真正例率”，横轴是“假正例率”
$$
TPR = \frac{ TP }{TP + FN} \\
 FPR = \frac{FP}{TN + FP}
$$






如果一个学习器的ROC曲线被另一个的完全包住，我们可以认为前者的性能小于后者，但有时会发生曲线交叉的情况，此时可以根据曲线下的面积大小进行比较，也就是**AUC**( Area Under Curve )

### AUC

![AUC curve](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Artificial%20Intelligence/AUC%20curve.png)

假设AUC曲线由$\{(x_1,y_1), (x_2,y_2), \dots, (x_m,y_m) \}$   的点按序连接而形成，则AUC可估算为：
$$
\mathrm{AUC} = \frac{1}{2} \sum\limits_{i=1}^{m-1}(x_{i+1} - x_i)(y_i + y_{i+1})
$$
AUC 衡量了样本预测的排序质量
$$
\mathrm{AUC} = 1 - l_{rank}
$$

### 代价错误敏感率

为了权衡不同类型错误所造成的不同损失，为错误赋予“非均等代价”（unequal cost）：

以二分类为例：可设定一个代价矩阵（cost matrix）

 

| 真实类别 | 预测 第0类  | 结果 第1类  |
| -------- | ----------- | ----------- |
| 第0类    | 0           | $cost_{01}$ |
| 第1类    | $cost_{10}$ | 0           |



其中用$cost_{ij}$表示将第$i$类预测为第$j$类的代价

在非均等代价下，我们所希望的不再是简单地最小化错误的次数，而是希望最小化**总体代价**（total cost）



（以上面二分类为例0为正例，1为负例）**代价敏感率**（cost-sensitive）错误率为：

$$
E(f ; D ; \cos t)=\frac{1}{m}\left\{\sum_{x_{i} \in D^{+}}\left\|\left(f\left(x_{i}\right) !=y_{i}\right)^{*} \cos t_{01}+\sum_{x_{i} \in D^{-}}\right\|\left(f\left(x_{i}\right)==y_{i}\right) * \cos t_{10}\right\}
$$
$D$:数据集      $D^+$ ：正样本数据集    $D^-$:负样本数据集

若令$cost_{ij}$的取值不限于0,1,则可以定义出多任务分类的代价敏感性能度量



### 代价曲线

在非均等代价下，ROC曲线不能直接反映出学习器的期望总体代价，可以用“**代价曲线**”

代价曲线图的横轴是取值为[0, 1]的正例概率代价,
$$
P(+) \cos t=\frac{p^{*} \cos t_{01}}{p^{*} \cos t_{01}+(1-p) \cos t_{10}}
$$
$p$：样例为正例的概率



纵轴为取值[0, 1]的归一化代价:
$$
\operatorname{cost}_{n o r m}=\frac{F N R * P * \cos t_{01}+F P R *(1-P) * \cos t_{10}}{p^{*} \cos t_{01}+(1-p) * \cos t_{10}}
$$


## 比较检验

### 二项检验

### T检验

### 交叉验证 T-检验

### 偏差与方差

对测试样本x,令$y_D$为$x$在数据集中的标记，$y$为$x$的真实标记, $f(x;D)$为训练集 $D$上学得模型$$在$x$上的预测输出。 以回归任务为例，学习期望为：
$$
\bar f(x) = E_D [ f(x;D) ] \\
$$
使用样本数目相同的不同训练集产生的方差为：
$$
var(x) = E_D [ ( f(x;D) - \bar f(x) )^2]
$$
噪声为：
$$
\epsilon^2 = E_D [ (y_D - y)^2 ]
$$
偏差定义为期望输出与真实标记的差别： $bias^2 = ( \bar f(x) - y )^2$, 为方便讨论，我们假设噪声的期望为0 ， 即$E_D [ (y_D - y)^2 ] = 0$. 对泛化误差分解：
$$
\begin{aligned}
E(f ; D)=& \mathbb{E}_{D}\left[\left(f(\boldsymbol{x} ; D)-y_{D}\right)^{2}\right] \\
=& \mathbb{E}_{D}\left[\left(f(\boldsymbol{x} ; D)-\bar{f}(\boldsymbol{x})+\bar{f}(\boldsymbol{x})-y_{D}\right)^{2}\right] \\
=& \mathbb{E}_{D}\left[(f(\boldsymbol{x} ; D)-\bar{f}(\boldsymbol{x}))^{2}\right]+\mathbb{E}_{D}\left[\left(\bar{f}(\boldsymbol{x})-y_{D}\right)^{2}\right] \\
&+\mathbb{E}_{D}\left[2(f(\boldsymbol{x} ; D)-\bar{f}(\boldsymbol{x}))\left(\bar{f}(\boldsymbol{x})-y_{D}\right)\right] \\
=& \mathbb{E}_{D}\left[(f(\boldsymbol{x} ; D)-\bar{f}(\boldsymbol{x}))^{2}\right]+\mathbb{E}_{D}\left[\left(\bar{f}(\boldsymbol{x})-y_{D}\right)^{2}\right]
\end{aligned}
$$


我们看到，**泛化误差 = 方差 + 偏差 + 噪声**

# Research Progres

- Novel methods for capacity control, such as *dropout* ([Srivastava *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id267)), have helped to mitigate overfitting. Here, noise is injected ([Bishop, 1995](http://d2l.ai/chapter_references/zreferences.html#id17)) throughout the neural network during training.
- Attention mechanisms solved a second problem that had plagued statistics for over a century: how to increase the memory and complexity of a system without increasing the number of learnable parameters. Researchers found an elegant solution by using what can only be viewed as a learnable pointer structure ([Bahdanau *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id10)). Rather than having to remember an entire text sequence, e.g., for machine translation in a fixed-dimensional representation, all that needed to be stored was a pointer to the intermediate state of the translation process. This allowed for significantly increased accuracy for long sequences, since the model no longer needed to remember the entire sequence before commencing the generation of a new sequence.
- Built solely on attention mechanisms, the Transformer architecture ([Vaswani *et al.*, 2017](http://d2l.ai/chapter_references/zreferences.html#id305)) has demonstrated superior *scaling* behavior: it performs better with an increase in dataset size, model size, and amount of training compute ([Kaplan *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id488)). This architecture has demonstrated compelling success in a wide range of areas, such as natural language processing ([Brown *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id473), [Devlin *et al.*, 2018](http://d2l.ai/chapter_references/zreferences.html#id58)), computer vision ([Dosovitskiy *et al.*, 2021](http://d2l.ai/chapter_references/zreferences.html#id60), [Liu *et al.*, 2021](http://d2l.ai/chapter_references/zreferences.html#id458)), speech recognition ([Gulati *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id551)), reinforcement learning ([Chen *et al.*, 2021](http://d2l.ai/chapter_references/zreferences.html#id552)), and graph neural networks ([Dwivedi and Bresson, 2020](http://d2l.ai/chapter_references/zreferences.html#id553)). For example, a single Transformer pretrained on modalities as diverse as text, images, joint torques, and button presses can play Atari, caption images, chat, and control a robot ([Reed *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id505)).
- Modeling probabilities of text sequences, *language models* can predict text given other text. Scaling up the data, model, and compute has unlocked a growing number of capabilities of language models to perform desired tasks via human-like text generation based on input text ([Brown *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id473), [Chowdhery *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id496), [Hoffmann *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id494), [Rae *et al.*, 2021](http://d2l.ai/chapter_references/zreferences.html#id489)). For instance, aligning language models with human intent ([Ouyang *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id565)), OpenAI’s [ChatGPT](https://chat.openai.com/) allows users to interact with it in a conversational way to solve problems, such as code debugging and note drafting.
- Multi-stage designs, e.g., via the memory networks ([Sukhbaatar *et al.*, 2015](http://d2l.ai/chapter_references/zreferences.html#id270)) and the neural programmer-interpreter ([Reed and De Freitas, 2015](http://d2l.ai/chapter_references/zreferences.html#id234)) allowed statistical modelers to describe iterative approaches to reasoning. These tools allow for an internal state of the deep neural network to be modified repeatedly, thus carrying out subsequent steps in a chain of reasoning, similar to how a processor can modify memory for a computation.
- A key development in *deep generative modeling* was the invention of *generative adversarial networks* ([Goodfellow *et al.*, 2014](http://d2l.ai/chapter_references/zreferences.html#id92)). Traditionally, statistical methods for density estimation and generative models focused on finding proper probability distributions and (often approximate) algorithms for sampling from them. As a result, these algorithms were largely limited by the lack of flexibility inherent in the statistical models. The crucial innovation in generative adversarial networks was to replace the sampler by an arbitrary algorithm with differentiable parameters. These are then adjusted in such a way that the discriminator (effectively a two-sample test) cannot distinguish fake from real data. Through the ability to use arbitrary algorithms to generate data, it opened up density estimation to a wide variety of techniques. Examples of galloping Zebras ([Zhu *et al.*, 2017](http://d2l.ai/chapter_references/zreferences.html#id341)) and of fake celebrity faces ([Karras *et al.*, 2017](http://d2l.ai/chapter_references/zreferences.html#id144)) are both testimony to this progress. Even amateur doodlers can produce photorealistic images based on just sketches that describe how the layout of a scene looks like ([Park *et al.*, 2019](http://d2l.ai/chapter_references/zreferences.html#id210)).
- Besides, while the diffusion process gradually adds random noise to data samples, *diffusion models* ([Ho *et al.*, 2020](http://d2l.ai/chapter_references/zreferences.html#id557), [Sohl-Dickstein *et al.*, 2015](http://d2l.ai/chapter_references/zreferences.html#id556)) learn the denoising process to gradually construct data samples from random noise, reversing the diffusion process. They start to replace generative adversarial networks in more recent deep generative models, such as in DALL-E 2 ([Ramesh *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id502)) and Imagen ([Saharia *et al.*, 2022](http://d2l.ai/chapter_references/zreferences.html#id504)) for creative art and image generation based on text descriptions.
- In many cases, a single GPU is insufficient to process the large amounts of data available for training. Over the past decade the ability to build parallel and distributed training algorithms has improved significantly. One of the key challenges in designing scalable algorithms is that the workhorse of deep learning optimization, stochastic gradient descent, relies on relatively small minibatches of data to be processed. At the same time, small batches limit the efficiency of GPUs. Hence, training on 1024 GPUs with a minibatch size of, say 32 images per batch amounts to an aggregate minibatch of about 32000 images. Recent work, first by Li ([2017](http://d2l.ai/chapter_references/zreferences.html#id166)), and subsequently by You *et al.* ([2017](http://d2l.ai/chapter_references/zreferences.html#id329)) and Jia *et al.* ([2018](http://d2l.ai/chapter_references/zreferences.html#id140)) pushed the size up to 64000 observations, reducing training time for the ResNet-50 model on the ImageNet dataset to less than 7 minutes. For comparison—initially training times were measured in the order of days.
- The ability to parallelize computation has also contributed to progress in *reinforcement learning*, This has led to significant progress in computers achieving superhuman performance on tasks like Go, Atari games, Starcraft, and in physics simulations (e.g., using MuJoCo), Where environment simulators are available. See, e.g., Silver *et al.* ([2016](http://d2l.ai/chapter_references/zreferences.html#id260)) for a description of how to achieve this in AlphaGo. In a nutshell, reinforcement learning works best if plenty of (state, action, reward) tuples are available. Simulation provides such an avenue.
- Deep learning frameworks have played a crucial role in disseminating ideas. The first generation of open-source frameworks for neural network modeling consisted of [Caffe](https://github.com/BVLC/caffe), [Torch](https://github.com/torch), and [Theano](https://github.com/Theano/Theano). Many seminal papers were written using these tools. By now, they have been superseded by [TensorFlow](https://github.com/tensorflow/tensorflow) (often used via its high level API [Keras](https://github.com/keras-team/keras)), [CNTK](https://github.com/Microsoft/CNTK), [Caffe 2](https://github.com/caffe2/caffe2), and [Apache MXNet](https://github.com/apache/incubator-mxnet). The third generation of tools consists of so-called *imperative* tools for deep learning, a trend that was arguably ignited by [Chainer](https://github.com/chainer/chainer), which used a syntax similar to Python NumPy to describe models. This idea was adopted by both [PyTorch](https://github.com/pytorch/pytorch), the [Gluon API](https://github.com/apache/incubator-mxnet) of MXNet, and [JAX](https://github.com/google/jax).

# Success Stories

- Intelligent assistants, such as Apple’s Siri, Amazon’s Alexa, and Google’s assistant, are able to answer spoken questions with a reasonable degree of accuracy. This includes menial tasks, like turning on light switches, and more complex tasks, like arranging barber’s appointments and offering phone support dialog. This is likely the most noticeable sign that AI is affecting our lives.
- A key ingredient in digital assistants is the ability to recognize speech accurately. Gradually, the accuracy of such systems has increased to the point of achieving human parity for certain applications ([Xiong *et al.*, 2018](http://d2l.ai/chapter_references/zreferences.html#id325)).
- Object recognition has likewise come a long way. Estimating the object in a picture was a fairly challenging task in 2010. On the ImageNet benchmark researchers from NEC Labs and University of Illinois at Urbana-Champaign achieved a top-5 error rate of 28% ([Lin *et al.*, 2010](http://d2l.ai/chapter_references/zreferences.html#id172)). By 2017, this error rate was reduced to 2.25% ([Hu *et al.*, 2018](http://d2l.ai/chapter_references/zreferences.html#id127)). Similarly, stunning results have been achieved for identifying birds and for diagnosing skin cancer.
- Prowess in games used to provide a measuring stick for human intelligence. Starting from TD-Gammon, a program for playing backgammon using temporal difference reinforcement learning, algorithmic and computational progress has led to algorithms for a wide range of applications. Unlike backgammon, chess has a much more complex state space and set of actions. DeepBlue beat Garry Kasparov using massive parallelism, special-purpose hardware and efficient search through the game tree ([Campbell *et al.*, 2002](http://d2l.ai/chapter_references/zreferences.html#id34)). Go is more difficult still, due to its huge state space. AlphaGo reached human parity in 2015, using deep learning combined with Monte Carlo tree sampling ([Silver *et al.*, 2016](http://d2l.ai/chapter_references/zreferences.html#id260)). The challenge in Poker was that the state space is large and only partially observed (we do not know the opponents’ cards). Libratus exceeded human performance in Poker using efficiently structured strategies ([Brown and Sandholm, 2017](http://d2l.ai/chapter_references/zreferences.html#id31)).
- Another indication of progress in AI is the advent of self-driving cars and trucks. While full autonomy is not quite within reach, excellent progress has been made in this direction, with companies such as Tesla, NVIDIA, and Waymo shipping products that enable at least partial autonomy. What makes full autonomy so challenging is that proper driving requires the ability to perceive, to reason and to incorporate rules into a system. At present, deep learning is used primarily in the computer vision aspect of these problems. The rest is heavily tuned by engineers.

# The Essence of Deep Learning

> 

| Decade |                              Dataset | Memory | Floating point calculations per second |
| -----: | -----------------------------------: | -----: | -------------------------------------: |
|   1970 |                           100 (Iris) |   1 KB |                    100 KF (Intel 8080) |
|   1980 |         1 K (house prices in Boston) | 100 KB |                     1 MF (Intel 80186) |
|   1990 | 10 K (optical character recognition) |  10 MB |                    10 MF (Intel 80486) |
|   2000 |                     10 M (web pages) | 100 MB |                      1 GF (Intel Core) |
|   2010 |                   10 G (advertising) |   1 GB |                    1 TF (Nvidia C2050) |
|   2020 |                 1 T (social network) | 100 GB |                    1 PF (Nvidia DGX-2) |

Note that random-access memory has not kept pace with the growth in data. At the same time, increases in computational power have outpaced the growth in datasets. 

Consequently, the sweet spot in machine learning and statistics **moved from (generalized) linear models and kernel methods to deep neural networks.** 

以前算力紧缺, 因此流行的是线性模型; 现在算力充足, 因此非线性模型, 神经网络得以流行.

This is also one of the reasons why many of the mainstays of deep learning, such as multilayer perceptrons ([McCulloch and Pitts, 1943](http://d2l.ai/chapter_references/zreferences.html#id187)), convolutional neural networks ([LeCun *et al.*, 1998](http://d2l.ai/chapter_references/zreferences.html#id162)), long short-term memory ([Hochreiter and Schmidhuber, 1997](http://d2l.ai/chapter_references/zreferences.html#id118)), and Q-Learning ([Watkins and Dayan, 1992](http://d2l.ai/chapter_references/zreferences.html#id312)), were essentially “rediscovered” in the past decade, after laying comparatively dormant for considerable time.



深度学习相比其他传统方法的优势在于它是端到端训练(*end-to-end training*)的. 深度学习不会单独地调整各个组件然后将其组合, 而是直接调整整个模型. 

> Arguably the most significant commonality in deep learning methods is *end-to-end training*. That is, rather than assembling a system based on components that are individually tuned, one builds the system and then tunes their performance jointly. 

For instance, in computer vision scientists used to separate the process of *feature engineering* from the process of building machine learning models. The Canny edge detector ([Canny, 1987](http://d2l.ai/chapter_references/zreferences.html#id35)) and Lowe’s SIFT feature extractor ([Lowe, 2004](http://d2l.ai/chapter_references/zreferences.html#id181)) reigned supreme for over a decade as algorithms for mapping images into feature vectors. In bygone days, the crucial part of applying machine learning to these problems consisted of coming up with manually-engineered ways of transforming the data into some form amenable to shallow models. 

Unfortunately, there is only so little that humans can accomplish by ingenuity in comparison with a consistent evaluation over millions of choices carried out automatically by an algorithm. When deep learning took over, these feature extractors were replaced by automatically tuned filters, yielding superior accuracy.



Beyond end-to-end training, we are experiencing a <u>transition from parametric statistical descriptions to fully nonparametric models</u>. When data is scarce, one needs to rely on simplifying assumptions about reality in order to obtain useful models. When data is abundant, these can be replaced by nonparametric models that better fit the data. To some extent, this mirrors the progress that physics experienced in the middle of the previous century with the availability of computers. Rather than solving parametric approximations of how electrons behave by hand, one can now resort to numerical simulations of the associated partial differential equations. This has led to much more accurate models, albeit often at the expense of explainability.

Another difference to previous work is <u>the acceptance of suboptimal solutions</u>, dealing with nonconvex nonlinear optimization problems, and the willingness to try things before proving them. This newfound empiricism in dealing with statistical problems, combined with a rapid influx of talent has led to rapid progress of practical algorithms, albeit in many cases at the expense of modifying and re-inventing tools that existed for decades.



# Appendix

## Popular ML datasets

* MNIST: digits written by employees of the US Census Bureau • ImageNet: millions of images from image search engine.
* AudioSet: YouTube sound clips for sound classification
* LibriSpeech: 1000 hours of English speech from audiobook
* Kinetics: YouTube videos clips for human actions classification
* KITTI: traffic scenarios recorded by cameras and other sensors
* Amazon Review: customer reviews and from Amazon online shopping • SQuAD: question-answer pairs derived from Wikipedia

More at https://en.wikipedia.org/wiki/List_of_datasets_for_machine-learning_research

## Where to Find Datasets

- [Paperswithcodes Datasets](https://paperswithcode.com/datasets): academic datasets with leaderboard
- [Kaggle Datasets](https://www.kaggle.com/datasets): ML datasets uploaded by data scientists
- [Google Dataset search](https://datasetsearch.research.google.com/): search datasets in the Web
- Various toolkits datasets: [tensorflow](https://www.tensorflow.org/datasets), [huggingface](https://huggingface.co/docs/datasets/)
- Various conference/company ML competitions
- [Open Data on AWS](https://registry.opendata.aws/): 100+ large-scale raw data
- Data lakes in your own organization
