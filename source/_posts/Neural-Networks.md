---
title: Neural Networks
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2023-12-08 19:43:54
---


Source: 

1. [Stanford CS231, Lecture 4](https://youtu.be/d14TUNcbn1k?si=fGVVrRpYIhqbBKBt)
2. [Neural Networks Pt. 2: Backpropagation Main Ideas](https://www.youtube.com/watch?v=IN2XmBhILt4&list=PLblh5JKOoLUICTaGLRoHQDuF_7q2GfuJF&index=75)
3. [Backpropagation Details Pt. 1: Optimizing 3 parameters simultaneously](https://www.youtube.com/watch?v=iyn2zdALii8&t=936s)
4. [Backpropagation Details Pt. 2: Going bonkers with The Chain Rule](https://www.youtube.com/watch?v=GKZoOHXGcLo&t=643s)
5. [Forwardpropagation, Backpropagation and Gradient Descent with PyTorch](https://www.deeplearningwizard.com/deep_learning/boosting_models_pytorch/forwardpropagation_backpropagation_gradientdescent/#forwardpropagation-backpropagation-and-gradient-descent-with-pytorch)



This article is a step-by-step explanation of neural networks which are extensively used in machine learning. It only involves the most basic case where both the input and output of a neuron are **scalars** (1-D tensors). But the idea holds for other dimensions. For higher dimensions, please reter to [Derivatives, Backpropagation, and Vectorization](https://lyk-love.cn/2024/01/25/derivatives-backpropagation-and-vectorization/)

<!--more-->

# Notations

In this article we'll use following notations.

* The **gradient** of a multivariate function $f$ is a vector that contains all the partial derivatives of $f$  with respect to each of its variables. Suppose $f = f(x, y, z, \ldots)$, then the gradient would be a vector $\left[\frac{\partial f}{\partial x}, \frac{\partial f}{\partial y}, \frac{\partial f}{\partial z}, \ldots\right]^T$, where each component is the partial derivative of $f$ with respect to one of its variables.

  However, I'll also call **the partial derivative** of a function, denoted as $\frac {\partial f} {\partial w}$, where $f$ is a multivariable function and $w$ is a variable of $f$, **as a gradient**, denoted as $\nabla_w f$.

  To sum, **the terms "gradient" and the "derivative" or "partial derivative" are all interchangeable in this article**.

* **We refer gradient to gradient formula**. It's different from the **gradient value**, which is a value of the gradient). 
  * A gradient formula is a vector of partial derivative formulars.
  * A gradient value is a vector of partial derivative values. 
  * A gradient value is **evaluated** from the gradient formula.
  
* **NN** is short for a neural networ.

* **FP** is short for foreward propagation.

* **BP** is short for backward propagation or **backpropagation**.

* In a computational graph, a node B is the "**upstream**" node of node A if there is an edge $A \rightarrow B$.

* In a computational graph, 
  * The **(total) gradient** of a node, such as $[\frac {\partial L} {x}, \frac {\partial L} {y}]^T$, is the gradient of the upstream node with respect to all the branches.
  * The **upstream gradient** of a node, such as $\frac {\partial L} {z}$ is the gradient from the upstream node with respect to the one upstream branch.
  * The **local gradient** of a node, such as $[\frac {\partial z} {x}, \frac {\partial z} {y}]^T$, is the gradient of the the node with respect to all the branches.

# Computational Graphs

A computational graph is a **directed graph** where:

1. An **edge** (or **branch**) represents a function argument (and also data dependency). 
   * The value of an argument can have whatever type. It can be a scalar, a vector, a matrix or a tensor[^1].
2. A **node** represents a function, whose arguments are the incoming edges.

Note: In this article, we call 



In following sections I'll show the **foreward pass and backward pass** of computational graphs. These two operations themselves are meaningless since we didn't set a "goal" for computational graphs and doing them is for nothing. However, you'll see that the ideas of them are used for illustrating the **foreward propagation and backward propagation** used by neural networks.

## Some basic computational graphs

[-->Source](https://www.tutorialspoint.com/python_deep_learning/python_deep_learning_computational_graphs.htm)

Here is a simple mathematical equation:
$$
p=x+y
$$

We can draw a computational graph of the above equation as follows.

![Figure 1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%201.png)

Let us take another example, slightly more complex. We have the following equation.
$$
g=(x+y)z
$$
The above equation is represented by the following computational graph.

![Figure 2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%202.jpg)



# Forward pass

Below is a computational graph representing $f(w, x)=\frac{1}{1+e^{-\left(w_0 x_0+w_1 x_1+w_2\right)}}$ where all the parameters are scalar. The FP has already been done in this figure.

For illustation, **a dumb node is added** after the original last node to represent the output, denoted as $y$. We have $y = f(w,x)$. 



![Figure 3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%203.png)

**Doing forward pass means we are passing the value from variables in forward direction from the left (input) to the right where the output is.**

# Gradient during backward pass

Before discussing the backwark propagation, we must know how the backwark propagation is implemented in computational graphs.

In this section we take $f: (x, y) \rightarrow z$ as an example. The upstream node of node $f$ is denoted as $L$.

Recall that in computational graphs, a node is a function. During backward propagation, we have:

1. The **upstream gradient** of node $f$: $\frac {\partial L} {z}$.
2. The **local gradient** of node $f$: $[\frac {\partial z} {x}, \frac {\partial z} {y}]^T$
3. The **gradient** of node $f$: $[\frac {\partial L} {x}, \frac {\partial L} {y}]^T$. 

From the chain rule of derivatives:
$$
\begin{aligned}
& \frac{\partial z}{\partial x}=\frac{\partial L}{\partial z} . \frac{\partial z}{\partial x} \\
& \frac{\partial z}{\partial y}=\frac{\partial L}{\partial z} . \frac{\partial z}{\partial y} .
\end{aligned}
$$


Thus, we obtain that:

**Gradient  = local gradient  * upstream gradient.**



<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%204.png" alt="Figure 4"  />

The advantage of backward pass instead of forward pass is obvious. Take the above figure as an example. 

To get the gradient value of gradient $[\frac {\partial L} {x}, \frac {\partial L} {y}]^T$, we just need to **evaluate** the upstream gradient $\frac{\partial L}{\partial z}$ **once**, and then leverage it to calculate $\frac{\partial f}{\partial x}, \frac{\partial f}{\partial y}$.

However, if we use a forward pass to do this, we can't use chain rule to reduce our computation. The detailed reason is [--> here](https://gregorygundersen.com/blog/2018/04/15/backprop/).

# Backward pass

Note that in neural networks, the term "parameters" refer to the weights and biases instead of the input data. 

However, since its just backward pass instead of backward propagation, which is used in NNs, we optimize the input data $x$ in this section. I know it's weird but that's the way they did in [CS231](https://youtu.be/d14TUNcbn1k?si=fGVVrRpYIhqbBKBt).



Backward pass starts from the output node.

1. The local gradient of the dumb node is $\frac {\partial y} {\partial f} = 1$, which is a constant. 
2. So the local gradient value is always 1.
3. There's no upstream gradient for the dumb node. Therefore, we don't need to multiply it.
4. As a result, the gradient value of this node is 1.

![Figure 5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%205.png)

Next, we compute the last but one node $1/x$. 

1. The local gradient of this node is $\frac {\partial (1/x)} {\partial x} = -1/x^2$.
2. Since we evaluate $x=1.37$ here, the local gradient value of this node is -1/(1.37)^2=-0.53. 
3. Meanwhile, the upstream gradient value is 1. 
4. As a result, the gradient value of this node is: -0.53 * 1 = -0.53.



![Figure 6](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%206.png)

Now we move to the node $x+1$. 

1. The gradient equation of this node is $\frac {\partial (x+1)} {\partial x} = 1$, which is a constant. 
2. So the local gradient value is always 1.
3. Moreover, the  upstream gradient value is -0.53. 
4. As a result, the gradient value of this node is: -0.53 * 1 = -0.53.

![Figure 7](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%207.png)

We can keep doing the above process until we get the gradient value of the nodes at the first layer.

![Figure 8](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%208.png)



## At what abstraction level ?

When we create a computation graph. We can define every node **at whatever computational granuality** we want to. In the previous example most nodes represent basic level computations (+, -, *, /, $\exp()$, ... ). We can also define nodes with high level computation.

For instance, consider the sigmoid function part in previous example. The sigmoid function is:
$$
\sigma(x)=\frac{1}{1+e^{-x}} ,
$$
and its gradient is:
$$
\frac{d \sigma(x)}{d x}=\frac{e^{-x}}{\left(1+e^{-x}\right)^2}=\left(\frac{1+e^{-x}-1}{1+e^{-x}}\right)\left(\frac{1}{1+e^{-x}}\right)=(1-\sigma(x)) \sigma(x) .
$$
We can abstract these computations in one node, some people also call it a **gate**.

![Figure 9](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%209.png)

## Patterns in backward propagation

### Add gate

The "add gate" (or "add node" since it's too simple to become a gate) $x+y$ where $x$ and $y$ are its inputs can be seen as a gradient "distributor". 

The reason is that, since $\frac {\partial (x+y)} {\partial x} = \frac {\partial (x+y)} {\partial y} = 1$, the local gradient value of add gate is $[1,1]^T$, so the gradient value flowing to branches of add gate is always: 

1 * (upstream gradient value of add gate) = upstream gradient value of add gate.

You can see that in the following figure. The upstream value is $[2,2]^T$, and the gradient value flowing to its branches is $[2,2]^T$.



![Figure 10](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2010.png)

### Max gate

The "max gate" $\max(x+y)$ where $x$ and $y$ are its inputs can be seen as a gradient "router". It routes its gradient value to the branch with maximum input value, leaving the upstream gradient value for the other branches be 0.

The reason is that, taking $x$ for example, if $x$ has the maximal assigned value in all branches, then:

1. The gradient is  $\frac {\partial \max(x+y)} {x} = 1$, the local gradient value is always 1.
2. Next, the partial derivative value value for this branch is 1 * (upstream gradient value) = upstream gradient value.
3. For any other branches, say $y$, since $\frac {\partial \max(x+y)} {y} = 0$. So the local partial derivative value is always 0. Therefore, the partial derivative value for this branch is always 0.

![Figure 11](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2011.png)

### Mul gate

The "mul gate" ("mul" is short for multiplication) $(x * y)$ where $x$ and $y$ are its inputs can be seen as a gradient "switcher". 

The reason is that, taking $x$ for example: 

1. The partial derivative for branch $x$ is  $\frac {\partial (x * y)} {x} = y$, the local partial derivative value is the assigned value of $y$.
2. The partial derivative value for this branch = (the the assigned value of $y$) * (upstream partial derivative value)

![Figure 12](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2012.png)



## Gradients add at branches

![image-20240124152400923](/Users/lyk/Library/Application Support/typora-user-images/image-20240124152400923.png)

# For vectorized inputs

A vectorized example:
$$
f(x, W)=\|W \cdot x\|^2=\sum_{i=1}^n(W \cdot x)_i^2 .
$$
![image-20240124152552751](/Users/lyk/Library/Application Support/typora-user-images/image-20240124152552751.png)

Let
$$
\begin{aligned}
& q=W \cdot x=\left(\begin{array}{c}
W_{1,1} x_1+\cdots+W_{1, n} x_n \\
\vdots \\
W_{n, 1} x_1+\cdots+W_{n, n} x_n
\end{array}\right) \\
& f(q)=\|q\|^2=q_1^2+\cdots+q_n^2
\end{aligned}
$$
Then

![image-20240124153703728](/Users/lyk/Library/Application Support/typora-user-images/image-20240124153703728.png)

![image-20240124153730305](/Users/lyk/Library/Application Support/typora-user-images/image-20240124153730305.png)

Now we start back pass, the gradient and gradient value of the dumb node is always 1.

Always check: The gradient with respect to a variable should have the same shape as the variable

![image-20240124153749293](/Users/lyk/Library/Application Support/typora-user-images/image-20240124153749293.png)



We the gradient of $f$ w.r.t. $q_{i}$ is
$$
\begin{gathered}
\frac{\partial f}{\partial q_i}=2 q_i \\
\nabla_q f=2 q
\end{gathered}
$$
$q_i$ is the element on the $i$-th row of $q$.
$$
q=W \cdot x=\left(\begin{array}{c}
W_{1,1} x_1+\cdots+W_{1, n} x_n \\
W_{2,1} x_1+\cdots+W_{2, n} x_n \\
\vdots \\
W_{n, 1} x_1+\cdots+W_{n, n} x_n
\end{array}\right) .
$$




![image-20240124152951702](/Users/lyk/Library/Application Support/typora-user-images/image-20240124152951702.png)



The gradient of $q_k$ w.r.t. $W_{i,j}$ is
$$
\begin{aligned}
\frac{\partial q_k}{\partial W_{i, j}} & =\mathbf{1}_{k=i} x_j
\end{aligned}
$$
where $\mathbf{1}_{k=i}$ is the indicator function.



For instance, $\frac{\partial q_1}{\partial W_{1, 1}} =1 .x_1 = x_1$.

Therefore, the gradient of $f$ w.r.t. $W_{i,j}$ is
$$
\begin{aligned}
\frac{\partial f}{\partial W_{i, j}} & =\sum_k \frac{\partial f}{\partial q_k} \frac{\partial q_k}{\partial W_{i, j}} \\
& =\sum_k\left(2 q_k\right)\left(\mathbf{1}_{k=i} x_j\right) \\
& =2 q_i x_j
\end{aligned}
$$


![image-20240124153348965](/Users/lyk/Library/Application Support/typora-user-images/image-20240124153348965.png)

the gradient of $f$ w.r.t. $x_{i}$ is
$$
\begin{aligned}
\frac{\partial q_k}{\partial x_i} & =W_{k, i} \\
\frac{\partial f}{\partial x_i} & =\sum_k \frac{\partial f}{\partial q_k} \frac{\partial q_k}{\partial x_i} \\
& =\sum_k 2 q_k W_{k, i}
\end{aligned}
$$
Or 
$$
\nabla_x f=2 W^T \cdot q
$$
For instance, $\frac{\partial q_2}{\partial x_1} =W_{2, 1}$ sicne $W_{2,1}$ is exactly the coefficient of $x_1$ in the $2$-nd row of $q$:
$$
q=W \cdot x=\left(\begin{array}{c}
W_{1,1} x_1+\cdots+W_{1, n} x_n \\
W_{2,1} x_1+\cdots+W_{2, n} x_n \\
\vdots \\
W_{n, 1} x_1+\cdots+W_{n, n} x_n
\end{array}\right)
$$


Each row of $W$ selects the "weights" to some cpmponents of $x$.

## Pseudo node

https://github.com/intel/caffe/tree/master/src/caffe/layers



# Neural networks: problem Formulation

A **neoral network (NN)** is a function that maps input data to output data. For example, given a dataset with $n$ data points (or samples) $(x_1, y_{1}), \dots, (x_n, y_n)$[^2], the neoral network acts as a function, say $f$, that expressing the "relationship" between  $x$ and $y$:
$$
f_\theta: X \rightarrow \hat Y,
$$
where 

* $X, Y, \hat Y$ are the sets of all $x_i, y_i, \hat y_i$, $i \in \{1,2,\cdots, n \}$.
* $\hat y_i$ is the output value of the NN corresponding to input data $x_i$.
* $y_i$ is the value in the dataset corresponding to data $x_i$.
* $\theta$ is the set of all parameters[^2] of the NN. The parameters are all weights and biases.





The goal of a neural network is to **minimize the value of a [loss function]()** 
$$
\text{Loss}(y, \hat y) = \cdots .
$$
Since the loss function, the architecture of the NN, and the dataset are all given. What we can do is modifying its parameters $\theta$. The modifying process is called **training** the NN.



Training composes two processes:

1. **Forward propagation (FP)** is the process of **evaluating (or assigning) the value of mathmatiacl expressions** in the NN (The function $f$ can be decomposed to smaller functions).
2. **Backwark propagation (BP)** is the process of optimizing the **parameters** of the NN using [Gradient Descent]() **in a backward order**.

Neural networks are a kind of **computational graphs**. The FP and BP process can be explained via computational graphs intuitively in a visual way. So we introduced computational graphs at first.

# Neural networks

Given below neuro network, it has:

* One input layer(1 node), one output layer(1 node).
  * Dataset is $(x,y)$ where $x \in \{x_i, \cdots, x_n \}$, $y \in \{y_i, \cdots, y_n \}$.
  * The NN outputs $\hat y$.
* One hidden layer(2 nodes).
  * Each node on the hidden layer has the same loss function $\text{Act}(x)$.
* A loss function $\text{Loss}(y, \hat y)$ to evaluate it.
* An activation function $\text{Act}$.

![Figure 13](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2013.png)

The NN represents a prediction function $f_\text{predict}$. Note that
$$
\hat y \triangleq f_\text{predict} \triangleq y_{\text{green}}
$$
where

* $y_{\text{green}} = w_3 y_{\text{blue}} + w_4 y_{\text{orange}} + b_3$. 
* $y_{\text{blue}} =\text{Act}(w_1 x + b_1)$
* $y_{\text{orange}} = \text{Act} (w_2 x + b_2)$

Once the parameters are determined, the prediction function $f_\text{predict}$ is fixed.

Next is the **training** process, during which we leverage forward propagation and backward propagation to optimize parameter set $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$ to minimize the loss function $\text{Loss}(y, \hat y)$. 

This is achieved by converting the neoral network to a computational graph (discussed before) where

1. Every node represents a small computation of the NN. For example, a node can represent an simple operation like "multiply the weight", "add the bias", or complex operation like "compute the activation funcition". You can decompose the activation funcition into many nodes as well, since you freely choose your abstraction level to design your computational graph.
2. Every edge represents the argument of the function of its connecting node. **Here "arguments" are not just $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$, but also input data $x_i$ and the intermediate results of operations. But during backward propagation we only optimize $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$**. 
3. As before, we add a dumb node after the original last node $\text{Loss}(\cdots)$.



The converted computational graph is:

![Figure 14](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2014.png)

The nodes $\text{ActFunc1}, \text{ActFunc2}$ reprensent the same activation $\text{Act}$.



The green node in the graph is:

![Figure 15](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2015.png)

# Forward propagation

Since we have a computational graph, the forward propagation (FP) process is exactly the forward pass discussed before. 

Before FP, values are initialized and passed according to following principles:

1. First, we **initialize the parameters $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$ randomly**. In practice, the biases are usually set to $0$ and the weights follow a norm distribution, i.e., $w \sim \text{Norm}(0,1)$.
2. The edges in the first layer are initialized with the value of input data $x_i$ and $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$. 



1. Then we pass the values from the left (input) to the right where the output is. 

# Backward propagation

Like FP, the forward propagation (FP) process is exactly the backward pass discussed before. However we **not only need to calculate the gradient and evaluate gradient value** as in backward pass, we **also have to update the parameters $\theta = \{w_1, w_2, \cdots, b_1,b_2,\cdots\}$ using gradient**.

## Recall: Gradient Descent

Recalling that the steps of Gradient Descent for optimizing parameters $\theta, \gamma, \cdots$ of function $f(\theta, \gamma, \cdots)$ are:

1. Calculate the derivative (Gradient) of the function $f(\theta, \gamma, \cdots)$ with respect to parameters $\theta, \gamma, \cdots$.
   $$
   \frac {\partial f} {\partial \theta}, \frac {\partial f} {\partial \gamma}, \cdots .
   $$
   
2. Randomly choose values for parameters $\theta, \gamma, \cdots$.

3. Plug the parameter values into the deriavatives.

4. Multiply each derivative value with a **learning rate** $\alpha$, this is the **step size** for the parameter
   $$
   \begin{aligned}
   \text{StepSize}(\theta) &= \frac {\partial f} {\partial \theta} \alpha . \\
   \text{StepSize}(\gamma) &= \frac {\partial f} {\partial \gamma} \alpha . \\
   &\cdots
   \end{aligned}
   $$
   
5. Update deriatives
   $$
   \begin{aligned}
   \theta_\text{new} &= \theta_{\text{old}} + \text{Step Size} = \theta_{\text{old}} + \frac {\partial f} {\partial \theta} \alpha . \\
   \gamma_\text{new} &= \gamma_{\text{old}} + \text{Step Size} = \gamma_{\text{old}} + \frac {\partial f} {\partial \gamma} \alpha . \\
   &\cdots
   \end{aligned}
   $$
   
6. Repeat steps 3-5 until:

   1. Max iteration step number.
   2. Or the change of function value $f(\theta, \gamma, \cdots)$ is very small.

Note: Step2 has already been done in fordward propagation. So in BP we don't need to do it.

## The BP process

In this section we show the process of one iteration of BP.



First, we need to evaluate the gradient value
$$
[\frac {\partial \text{Loss}} {\partial b_3}, \frac {\partial \text{Loss}} {\partial w_3}, \frac {\partial \text{Loss}} {\partial w_4}, \frac {\partial \text{Loss}} {\partial b_1}, \frac {\partial \text{Loss}} {\partial w_1}, \frac {\partial \text{Loss}} {\partial b_2}, \frac {\partial \text{Loss}} {\partial w_2}]^T .
$$
(The sequence of elements doesn't matter)

1. As before, the gradient value of the dumb node is always 1. So the upstream gradient value for the $\text{Loss}$ nodeis always 1.

2. The gradient of the node $\text{Loss}$ is
   $$
   \frac {\partial \text{Loss}} {\partial y_{\text{green}}} = \frac {\partial \text{Loss}} {\partial y_{\text{green}}} . 1
   $$
   The local gradient is
   $$
   \frac {\partial \text{Loss}} {\partial y_{\text{green}}} .
   $$
   We can evaluate the local gradient since we've already evaluated the values of all the variables included in it during FP.

   As a result, we get the gradient value for the $\text{Loss}$ node.

3. Next, the gradient of the green node $(+)$ is:
   $$
   \begin{aligned}
   \frac {\partial \text{Loss}} {\partial b_3} 
   &= 
   \frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
   \frac {\partial y_{\text{green}}} {\partial b_3} 
   \\
   \frac {\partial \text{Loss}} {\partial y_{\text{blue}}} 
   & = 
   \frac {\partial \text{Loss}} {\partial y_{\text{green}}} \frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}} 
   \\
   \frac {\partial \text{Loss}} {\partial y_{\text{orangee}}} 
   & = 
   \frac {\partial \text{Loss}} {\partial y_{\text{green}}} \frac {\partial y_{\text{orange}}} {\partial y_{\text{orange}}} .
   \end{aligned}
   $$
   The local gradient is
   $$
   [\frac {\partial y_{\text{green}}} {\partial b_3}, \frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}}, \frac {\partial y_{\text{green}}} {\partial y_{\text{orange}}}]^T .
   $$
   We can evaluate the local gradient since we've already evaluated the values of all the variables included in it during FP.

   The upstream gradient value is evaluated in last step.

   As a result, we get the gradient value for the green node.

4. Repeating backward util we get the gradient value of the nodes on the first layer.



Now we have the gradient value of NN, we then multiply each partial derivative value to a learning rate $\alpha$ to form a step size. For every parameter, we substract the step size. Thus we finishing the update of patameters.

# Example

## Initialization

Given:

1. Loss function (called: softplus) $\text{Loss}(y, \hat y) = \sum_i^{n} (y - \hat y)^2$.
2. Activation function (called: sum of squared residuals) $\text{Act}(x) = \log (1 + e^x)$.
3. Learning rate $\alpha = 0.001$, which is used in Gradient Descent

```python
def softplus(x, beta=1.0):
    return (1.0 / beta) * np.log(1 + np.exp(beta * x))


def sum_of_squared_residuals(y_true_labels, y_pred_labels):
    assert len(y_true_labels) == len(y_pred_labels), "Input lists must have the same length"
    residuals = [true - pred for true, pred in zip(y_true_labels, y_pred_labels)]
    sum_squared_residuals = sum(residual ** 2 for residual in residuals)

    return sum_squared_residuals
def learning_rate():
    return 0.01
def activation_func(x):
    return softplus(x)
def loss_func(y_true, y_pred):
    return sum_of_squared_residuals(y_true, y_pred)
```

with observed $n$-data points($n=3$):

```python
x = [0.1, 0.53, 0.82]
y = [1.2, 3.2, 1.1]
xy_pairs = list(zip(x, y))
```


and uninitialized parameters:

```
w_1, w_2, w_3, w_4, b_1, b_2, b_3 
```

How to perform BP to optimize the last layer parameters $b_3, w_3,w_4$?

## Forward Paragapagion

Solution:

First we randomly initialize parameters:

```python
    np.random.seed(42)

    w_1 = np.random.normal(0, 1)
    w_2 = np.random.normal(0, 1)
    w_3 = np.random.normal(0, 1)
    w_4 = np.random.normal(0, 1)

    b_1 = 0
    b_2 = 0
    b_3 = 0
```



Second, we perfrom forward parapagation. 

Becasue:

* $y_{\text{green}} = w_3 y_{\text{blue}} + w_4 y_{\text{orange}} + b_3$. 
* $y_{\text{blue}} =\text{Act}(w_1 x + b_1)$
* $y_{\text{orange}} = \text{Act} (w_2 x + b_2)$,

we compute $y_{\text{blue}}, y_{\text{orange}}, y_{\text{green}}$ value for each input $x_i$:

```python
y_blue_values = y_blue(x,w_1,b_1)
y_orange_values = y_orange(x,w_1,b_1)
y_hat = y_green(y_blue_values, y_orange_values, w_3, w_4, b_3)
print(f"y_blue: {y_blue_values}")
print(f"y_orange: {y_orange_values}")
print(f"y_green: {y_hat}")
### Outputs
# y_blue: [0.718291262698181, 0.8334146592824242, 0.9173954367325202]
# y_orange: [0.718291262698181, 0.8334146592824242, 0.9173954367325202]
# y_green: [1.559208056553835, 1.8091085311575739, 1.9914071495536403]
```

## Back Propagation

Then we perform back propagation, take optimizing $b_3$ for example,

The derivative is
$$
\frac {\partial \text{Loss}} {\partial b_3} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial b_3}
$$
Since the loss function is determined:
$$
\text{Loss}(y, \hat y) = \sum_i^{n} (y - \hat y)^2 ,
$$
we get following drivatives
$$
\frac {\partial \text{Loss}} {\partial y_{\text{green}}}  = \sum_{i=1} ^ n -2 (y -  y_{\text{green}})^2 
\\
\frac {\partial y_{\text{green}}} {\partial b_3} = 1 .
$$

```python
def derivative1(y, y_green_values):
	return -2 * sum_of_squared_residuals(y, y_green_values)


def derivative2():
	return 1
```

Then we **plug** the values into the deriavatives to evalute the deriavatives:

```python
derivative1_value = derivative1(y, y_hat) # plug the value
derivative2_value = derivative2()
derivative_value = derivative1_value * derivative2_value
print(f"derivative1_value: {derivative1_value}")
print(f"derivative2_value: {derivative2_value}")
print(f"derivative_value: {derivative_value}")
##### output
derivative1_value: -5.716432424534343
derivative2_value: 1
derivative_value: -5.716432424534343
```



Then we calculate the step size, update the parameter $b_3$:

```python
step_size_for_b_3 = derivative_value * learning_rate()
new_b_3 = b_3 + step_size_for_b_3
print(f"step size: {derivative_value}")
print(f"updated b_3: {new_b_3}")
##### output
step size: -5.716432424534343
updated b_3: -0.05716432424534343
```



New loss func value:

```python
new_loss_func_value = loss_func(y, y_green(y_blue_values, y_orange_values, w_3, w_4, new_b_3))
print(f"new loss func value b_3: {new_loss_func_value}")
##### output
new loss func value b_3: 2.884057087700263
```

Then repeat the process.

# Future

https://arxiv.org/abs/2212.13345

 





[^1]: Note that the concept "tensor" appears in machine learning does not equal to the concept in physics or math.
[^2]: In neural networks, the word "parameters" typically refer to the weights and biases rather than the input data. 
