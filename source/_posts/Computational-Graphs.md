---
title: Computational Graphs
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-01-23 23:58:27
---


Source:

1. [Stanford CS231, Lecture 4](https://youtu.be/d14TUNcbn1k?si=fGVVrRpYIhqbBKBt)



This article is a theoratical explanation of [neural networks](https://lyk-love.cn/2023/12/08/neural-networks) in the perspective of computational graphs. In fact, neural networks are a kind of computational graph. In this article, we:

1. Illustrate the concept of computational graphs.
2. Represent neural networks as computation graphs. Use the latter as a visual ait to explain the forward propagation and backward propagation in neural networks.

<!--more-->

#  Computational Graphs

A computational graph is a directed graph where:

1. An **edge** (or **branch**) represents a function argument (and also data dependency). 
   * The value of an argument can have whatever type. It can be a scalar, a vector, a matrix or a tensor[^1].
2. A **node** represents a function. The incoming edges of a node are the parameters of the function.

Note: In this article, we call a node B is the "**upstream**" node of node A if there is an edge $A \rightarrow B$.

## Example

[-->Source](https://www.tutorialspoint.com/python_deep_learning/python_deep_learning_computational_graphs.htm)

Here is a simple mathematical equation:
$$
p=x+y
$$

We can draw a computational graph of the above equation as follows.

![Figure 1](https://www.tutorialspoint.com/python_deep_learning/images/computational_graph_equation1.jpg)

Let us take another example, slightly more complex. We have the following equation.
$$
g=(x+y)z
$$
The above equation is represented by the following computational graph.

![Figure 2](https://www.tutorialspoint.com/python_deep_learning/images/computational_graph_equation2.jpg)



# Neural networks as computational graphs

The **neural network**, which is extensively used in machine learning, is **a kind of computational graph**. Therefore,

## Forward propagation

Below is a computational graph representing $f(w, x)=\frac{1}{1+e^{-\left(w_0 x_0+w_1 x_1+w_2\right)}}$, where $x = [x_0, x_1]^T$. For illustation, a dumb node is added after the original last node to represent the output, denoted as $y$. We have $y = f(w,x)$.



The **forward propagation (FP)**, which has already been done in this figure, is the procedure for **evaluating (or assigning) the value of the  mathematical expression** represented by computational graphs.

![Figure 3](/Users/lyk/Library/Application Support/typora-user-images/image-20240123214300844.png)

Doing FP means we are passing the value from variables in forward  direction from the left (input) to the right where the output is.

## Local gradients and upstream gradients

Before discussing the backwark propagation, we must know how the backwark propagation is implemented in computational graphs.

In this section we take $f: (x, y) \rightarrow z$ as an example. The upstream node of node $f$ is denoted as $L$.

Recall that in computational graphs, a node is a function. During backward propagation, we have:

1. The **upstream gradient** of the node is the gradient from the upstream node, say $\frac {\partial L} {z}$.
2. The **local gradient** of a branch is the gradient of the current node with respect to the branch, say $\frac {\partial z} {x}$ and $\frac {\partial z} {y}$.
3. Therefore, the **(total) gradient** of a branch is the gradient of the upstream node with respect to the branch, say $\frac {\partial L} {x}$ and $\frac {\partial L} {y}$.

The chain rule of differentiation is
$$
\begin{aligned}
& \frac{\partial f}{\partial x}=\frac{\partial f}{\partial z} * \frac{\partial z}{\partial x} \\
& \frac{\partial f}{\partial y}=\frac{\partial f}{\partial z} * \frac{\partial z}{\partial y} .
\end{aligned}
$$
Each left side is the gradient for a branch, and each right side is the local gradient for this branch * upstream gradient for this branch.

Thus, we obtain that:

**Gradient for a branch = local gradient for this branch * upstream gradient for this branch.**



![Figure 4](/Users/lyk/Library/Application Support/typora-user-images/image-20240123225900960.png)

# Backwark propagation

**Important note**: although the backwark propagation process is to optimize the **parameters** of a neoral networks, such as weights and biases, in this article we will try to optimize the input data $x$. I know it's weird but that's the way they did in CS231.



The **backwark propagation (BP)** starts from the output node.

1. The gradient equation for the output node is $\frac {\partial y} {\partial f} = 1$, which is a constant. 
2. So the local gradient value of this node is always always 1. 
3. This node has no upstream gradient value. Therefore, we don't need to multiply it.
4. The gradient value of this node is 1.

![Figure 5](/Users/lyk/Library/Application Support/typora-user-images/image-20240123214458282.png)

Next, we compute the last but one node $1/x$. 

1. The gradient equation for this node is $\frac {\partial (1/x)} {\partial x} = -1/x^2$. 
2. Since we the assigned value of $x$ here is 1.37, the local gradient value of this node is -1/(1.37)^2=-0.53. 
3. Meanwhile, the upstream gradient value is 1. 
4. As a result, the gradient value of this node is: -0.53 * 1 = -0.53.



![Figure 6](/Users/lyk/Library/Application Support/typora-user-images/image-20240123213051158.png)

Now we move to the node $x+1$. 

1. The gradient equation for it is $\frac {\partial (x+1)} {\partial x} = 1$, which is a constant. 
2. So the local gradient value of it is always 1. 
3. Moreover, the  upstream gradient value is -0.53. 
4. As a result, the gradient value of this node is: -0.53 * 1 = -0.53.

![Figure 7](/Users/lyk/Library/Application Support/typora-user-images/image-20240123214936028.png)

We can keep doing the above process until we get the gradient value of the nodes of the first layer.

![Figure 8](/Users/lyk/Library/Application Support/typora-user-images/image-20240123220150999.png)

# At what abstraction level ?

When we create a computation graph. We can define every node **at whatever computational granuality** we want to. In the previous example most nodes represent basic level computations (+, -, *, /, $\exp()$, ... ). We can also define nodes with high level computation.

For instance, consider the sigmoid function part in previous example. The sigmoid function is:
$$
\sigma(x)=\frac{1}{1+e^{-x}} ,
$$
and its gradient equation is:
$$
\frac{d \sigma(x)}{d x}=\frac{e^{-x}}{\left(1+e^{-x}\right)^2}=\left(\frac{1+e^{-x}-1}{1+e^{-x}}\right)\left(\frac{1}{1+e^{-x}}\right)=(1-\sigma(x)) \sigma(x) .
$$
We can abstract these computations in one node, some people also call it a **gate**.

![Figure 9](/Users/lyk/Library/Application Support/typora-user-images/image-20240123222159906.png)

# Patterns in backwork flow

## Add gate

The "add gate" (or "add node" since it's too simple to become a gate) $x+y$ where $x$ and $y$ are its inputs can be seen as a gradient "distributor". 

The reason is that, since $\frac {\partial (x+y)} {\partial x} = \frac {\partial (x+y)} {\partial y} = 1$, the local gradient values of add gate for each branch are always 1, so the gradient value flowing to each branch is always: 

1 * (upstream gradient value) = upstream gradient value.

You can see that in the following figure. The upstream value is 2, and the gradient values flowing to each branch are all 2.



![Figure 10](/Users/lyk/Library/Application Support/typora-user-images/image-20240123222916577.png)

## Max gate

The "max gate" $\max(x+y)$ where $x$ and $y$ are its inputs can be seen as a gradient "router". It routes its gradient value to the branch with maximum input value, leaving the upstream gradient values for the left branches be 0.

The reason is that, taking $x$ for example, if $x$ has the maximal assigned value in all branches, then:

1. The gradient equation for this branch is  $\frac {\partial \max(x+y)} {x} = 1$, the local gradient value is always 1.
2. Next, the gradient value for this branch is 1 * (upstream gradient value) = upstream gradient value.
3. For any other branches, say $y$, since $\frac {\partial \max(x+y)} {y} = 0$. So the local gradient value is always 0. Therefore, the gradient value for this branch is always 0.

![Figure 11](/Users/lyk/Library/Application Support/typora-user-images/image-20240123223640350.png)

## Mul gate

The "mul gate" ("mul" is short for multiplication) $(x * y)$ where $x$ and $y$ are its inputs can be seen as a gradient "switcher". 

The reason is that, taking $x$ for example: 

1. The gradient equation for branch $x$ is  $\frac {\partial (x * y)} {x} = y$, the local gradient value is the assigned value of $y$.
2. The gradient value for this branch = (the the assigned value of $y$) * (upstream gradient value)

![Figure 12](/Users/lyk/Library/Application Support/typora-user-images/image-20240123224546148.png)

[^1]: Note that the concept "tensor" appears in machine learning does not equal to the concept in physics or math.
