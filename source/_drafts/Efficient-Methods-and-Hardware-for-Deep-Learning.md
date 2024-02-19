---
title: Efficient Methods and Hardware for Deep Learning
tags:
---



[Stanford CS 231N, Lecture 15, Efficient Methods and Hardware for Deep Learning](https://youtu.be/eZdOkDtYMoo?si=AAkDMjEsgCJsGM0u)

* [--> Slides]()
* Lecturer: [Han Song](https://hanlab.mit.edu/)

<!--more-->

Methods:

1. Pruning
2. Quantization
3. Low Rank Approximation
4. Winograd Transformation



![image-20240208235611952](/Users/lyk/Library/Application Support/typora-user-images/image-20240208235611952.png)

# Pruning

![image-20240209000222444](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000222444.png)

![image-20240209000235669](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000235669.png)

## Pruning Neural Networks

![image-20240209000422895](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000422895.png)

[Han et al. NIPS’15]

## Retrain to Recover Accuracy



![image-20240209000301312](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000301312.png)

[Han et al. NIPS’15]

## Iteratively Retrain to Recover Accuracy

![image-20240209000328548](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000328548.png)

[Han et al. NIPS’15]



# Quantization

![image-20240209000504864](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000504864.png)



![image-20240209000641036](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000641036.png)



![image-20240209000650939](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000650939.png)

![image-20240209000714003](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000714003.png)



![image-20240209000725973](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000725973.png)



[Han et al. ICLR’16]



Before Trained Quantization: Continuous Weight

![image-20240209000827714](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000827714.png)

After Trained Quantization: Discrete Weight

![image-20240209000857107](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000857107.png)

# Low Rank Approximation

![image-20240208235905139](/Users/lyk/Library/Application Support/typora-user-images/image-20240208235905139.png)

Low Rank Approximation for Conv



Layer responses lie in a lowrank subspace
Decompose a convolutional layer with $d$ filters with filter size $k \times k \times c$ to

- A layer with d' filters $(k \times k \times c)$
- A layer with $d$ filter $\left(1 \times 1 \times d^{\prime}\right)$



# Winograd Transformation

## 3x3 DIRECT Convolutions

![image-20240209000002715](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000002715.png)

Direct convolution: we need 9xCx4 = 36xC FMAs for 4 outputs



## 3x3 WINOGRAD Convolutions

![image-20240209000052209](/Users/lyk/Library/Application Support/typora-user-images/image-20240209000052209.png)

Direct convolution: we need $9 \times C \times 4=36 \times C$ FMAs for 4 outputs 

Winograd convolution: we need 16xC FMAs for 4 outputs: $2.25 x$ fewer FMAs
