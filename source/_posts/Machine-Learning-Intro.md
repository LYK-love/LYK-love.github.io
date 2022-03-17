---
title: Machine Learning Intro
tags: Machine Learning
categories: Artificial Intelligence
mathjax: true
date: 2022-02-15 21:27:44
---


Outline

* 基本术语
* 模型评估和选择

<!--more-->



#  Basic Term

## Data

令$D = \{ x_1,x_2,..,x_m \}$表示包含m个示例的数据集，每个示例由d个属性描述，则每个示例$x_i=\{ x_{i1}, x_{i2}, \dots, x_{id} \}$是d维样本空间中的一个向量，$x_i \in \chi$, 其中$x_{ij}$是样本$x_i$在第j个属性的取值

![data set](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Artificial%20Intelligence/%E6%95%B0%E6%8D%AE%E9%9B%86.png)



* 上面的每条record就是一个**示例**（instance）或**样本**（ sample ）
* 上面的每个field称为一个**属性**（ attribute ）或**特征**（ feature ）,属性的取值就是属性值
* **属性空间**（attribute value）、**样本空间**( sample  space )、**输入空间**： 属性张成的空间，记为$\chi$
* **标记空间**、**输出空间**： 标记张成的空间，记为 $\gamma $ 
* 如果把属性作为坐标轴，每个示例都对应特征空间的一个点，称为**特征向量**（  feature  vector ）， 属性个数就是样本维度
* 样例（  Example ）:  示例+标记, 用$(x_i,y_i)$表示第i个样例，其中$y_i \in \gamma$是示例$x_i$的标记， $\gamma $ 是所有标记的集合，也就是输出空间
  * 如果把标记看作对象本身的一部分，那么示例也可以看作样本

* 训练集: 一组训练样例
* 测试集: 一组测试样例

## Task

根据标记的取值情况

* 分类任务:标记为离散值
  * 二分类:例如(好瓜,坏瓜)(正类,反类)(+1,-1)
  * 多分类:例如(冬瓜,南瓜,西瓜)
* 回归任务:标记为连续值
  * 例如,瓜的成熟度S
* 聚类任务:标记为空值,对示例进行自动分组( 即，要分的组也不知道)
  * 例如,本地瓜,外地瓜

建立一个从输入空间 $\chi$到输出空间$\gamma$的映射：$f : \ x \rightarrow y$, 对二分类任务，通常令$\gamma = \{-1,+1\}$  或$\{0,1\}$；对多分类任务，   $|\gamma|=2$; 对回归任务， $\gamma = R$





根据标记的完整情况

* (有)监督学习:所有示例都有标记
  * 分类、回归
* 无监督学习:所有示例都没有标记
  * 聚类
* 半监督学习:少量示例有标记,大量示例没标记
* 噪音标记学习:标记有,但是不完全准确

## Goal

机器学习技术的根本目标就是泛化能力

最理想的机器学习技术是学习到**概念**(人类学习,可理解的)

* 比如，“好瓜是某种色泽，某种根蒂，某种敲声的瓜“这样的**概念**，但是，未来是不确定的，你可能遇到没见过的瓜

但是现实中很困难,因此很多时候机器学习采用的是黑盒模型

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
