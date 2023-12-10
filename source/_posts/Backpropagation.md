---
title: Backpropagation
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2023-12-08 19:43:54
---


Source: 

1. [Neural Networks Pt. 2: Backpropagation Main Ideas](https://www.youtube.com/watch?v=IN2XmBhILt4&list=PLblh5JKOoLUICTaGLRoHQDuF_7q2GfuJF&index=75)
2. [Backpropagation Details Pt. 1: Optimizing 3 parameters simultaneously](https://www.youtube.com/watch?v=iyn2zdALii8&t=936s)
3. [Backpropagation Details Pt. 2: Going bonkers with The Chain Rule](https://www.youtube.com/watch?v=GKZoOHXGcLo&t=643s)
4. [Forwardpropagation, Backpropagation and Gradient Descent with PyTorch](https://www.deeplearningwizard.com/deep_learning/boosting_models_pytorch/forwardpropagation_backpropagation_gradientdescent/#forwardpropagation-backpropagation-and-gradient-descent-with-pytorch)

<!--more-->

# Problem Formulation

Given dataset $(x,y)$ with $n$ data points $(x_1, y_{1}), \dots, (x_n, y_n)$, we can say that the relationship between $x$ and $y$ is function $f$:
$$
y = f_\text{observed}(x)
$$
where $x \in \{x_i, \cdots, x_n \}$, $y \in \{y_i, \cdots, y_n \}$.



We construct a predict function $f_\text{predict}$:
$$
\hat y = f_\text{predict}(x)
$$
where $x \in \{x_i, \cdots, x_n \}$,  $\hat y \in \{\hat y_{1}, \cdots, \hat y_n \}$. $\hat y$ are predicted values of $x$ (Or $\hat y_i$ is predicted value of $x_i$ )



Our goal is to get an "**optimal**" predict function such that, given data point $x$, the "difference" betwwen predicted value $\hat y$ and observed value $y$ is minimized.

We define the "difference" as **[loss function]()**:
$$
\text{Loss}(y, \hat y) = \cdots
$$
Note: the loss function is chosen in advance. It's a measurement function of how "optimal" or "close to the truth" our $\hat y$ is.

# Example Neural Network

Given below Neuro Network(NN), it has:

* One input layer(1 node), one output layer(1 node).
  * Dataset is $(x,y)$ where $x \in \{x_i, \cdots, x_n \}$, $y \in \{y_i, \cdots, y_n \}$.
  * The NN outputs $\hat y$.
* One hidden layer(2 nodes).
  * Each node on the hidden layer has the same loss function $\text{Act}(x)$.
* A loss function $\text{Loss}(y, \hat y)$ to evaluate it.

![Neura Network for BP](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Backpropagation/Neura Network for BP.png)

The NN represents a prediction function $f_\text{predict}$:
$$
\hat y \triangleq f_\text{predict} \triangleq y_{\text{green}}
$$
where

* $y_{\text{green}} = w_3 y_{\text{blue}} + w_4 y_{\text{orange}} + b_3$. 
* $y_{\text{blue}} =\text{Act}(w_1 x + b_1)$
* $y_{\text{orange}} = \text{Act} (w_2 x + b_2)$

Once the parameters are determined, the prediction function $f_\text{predict}$ is fixed.



Thus the problem becomes that:

**HOW to select parameters $w_1, w_2, \cdots, b_1,b_2,\cdots$ so that the prediction function $f_\text{predict}$ is optimal?**

# Forward Propagation

First, we **initialize the parameters randomly**. In practice, the biases are usually set to $0$ and the weights follow a norm distribution, i.e., $w \sim \text{Norm}(0,1)$.

Then we input data points to this NN.

Since parameters are fixed, the predicted values $\hat y$ and all inner-node values, e.g., $y_{\text{blue}}$, $y_{\text{orange}}$, are fixed as well.

# Back Propagation

Next, we **optimize these parameters using [Gradient Descent]()** in a backward order, this is called **Back propagation**.

Note: the effect of BP(Back Propagation) equals the **brute force Gradient Descent**. But BP reduces the computationity complexity.

## Recall: Gradient Descent

Recalling that the steps of Gradient Descent for optimizing parameters $\theta, \gamma, \cdots$ of function $f(\theta, \gamma, \cdots)$ are:

1. Compute the derivative equations
   $$
   \frac {\partial f} {\partial \theta}, \frac {\partial f} {\partial \gamma}, \cdots .
   $$
   They're called the **gradient** of function $f(\theta, \gamma, \cdots)$.

2. Randomly choose values for parameters $\theta, \gamma, \cdots$.

3. Plug the parameter values into the deriavatives(ahem, the Gradient).

4. Multiply each derivative value with a **learning rate** $\alpha$, this is the **step size** for the parameter
   $$
   \begin{aligned}
   \text{StepSize}(\theta) &= \frac {\partial f} {\partial \theta} \alpha . \\
   \text{StepSize}(\gamma) &= \frac {\partial f} {\partial \gamma} \alpha . \\
   &\cdots
   \end{aligned}
   $$
   
5. Update gradients
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

## Optimize the last layer

We first optimize the parameters $b_3, w_3, w_4$ on the last layer.

Note that since input values $\{x_1,\cdots,x_n\}$ and $\{y_{1},\cdots,y_n\}$ are fixed, the predicted values $\{\hat y_{1},\cdots, \hat y_n\}$ are fixed as well.

And we need to change parameters $b_3, w_3, w_4$ here.

So, the loss function $\text{Loss}(y, \hat y)$ can be written as $\text{Loss}(b_3, w_3,w_4)$.

Remember that using [Chain Rule](), the gradient of  $\text{Loss}(b_3, w_3,w_4)$ is 
$$
\begin{aligned}
\frac {\partial \text{Loss}} {\partial b_3} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial b_3} 
\\
\frac {\partial \text{Loss}} {\partial w_3} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial w_3} 
\\
\frac {\partial \text{Loss}} {\partial w_4} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial w_4} 
\end{aligned}
$$
Fun fact: **All the deriatives on this layer use the same deriative** $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$ !

So, we just need to solve the quation:

1. $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$ one time,
2. $\frac {\partial y_{\text{green}}} {\partial b_3}$, $\frac {\partial y_{\text{green}}} {\partial w_3}$, $\frac {\partial y_{\text{green}}} {\partial w_4}$ each for one time.

To get one gradient, we only need to perform **4 derivations**!

Then we use the gradient to perform *Gradient Descent*. Due to the forward propagation, the parameters values are already computed, thus we can **evaluate the value** of the gradient.

After that we calculate the step sizes, update parameters, and repeat. 

When the *Gradient Descent* finishes, the parameters $b_3, w_3, w_4$ are optimized.

## Optimize the middle layer

Afterwards, we optimize the parameter $b_1, b_2, w_1, w_2$ on the last layer.

The steps are the same. The loss function $\text{Loss}(y, \hat y)$ can now be written as $\text{Loss}(b_1, b_2, w_1,w_2)$.

The gradient of $\text{Loss}(b_1, b_2, w_1,w_2)$ is
$$
\begin{aligned}
\frac {\partial \text{Loss}} {\partial b_1} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}} 
\frac {\partial y_{\text{blue}}} {\partial b_1} 
\\
\frac {\partial \text{Loss}} {\partial w_1} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}} 
\frac {\partial y_{\text{blue}}} {\partial w_1} 
\end{aligned}
$$
plus
$$
\begin{aligned}
\frac {\partial \text{Loss}} {\partial b_2} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{orange}}} 
\frac {\partial y_{\text{orange}}} {\partial b_2} 
\\
\frac {\partial \text{Loss}} {\partial w_2} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{orange}}} 
\frac {\partial y_{\text{orange}}} {\partial w_2} .
\end{aligned}
$$


Fun Fact: derivative $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$ **has been computed before**! And derivatives $\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}}$, $\frac {\partial y_{\text{green}}} {\partial y_{\text{orange}}}$ are more or less **shared** here!

So, we just need to compute:

1.  $\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}}$, $\frac {\partial y_{\text{green}}} {\partial y_{\text{orange}}}$ each for one time.
2.  $\frac {\partial y_{\text{blue}}} {\partial b_1}$, $\frac {\partial y_{\text{blue}}} {\partial w_1}$, $\frac {\partial y_{\text{orange}}} {\partial b_2}$, $\frac {\partial y_{\text{orange}}} {\partial w_2}$ each for one time.
3.  We don't need to compute $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$. (Note: This means we don)

To get one gradient, we only need to perform **2 + 4 = 6 deriations**!

Then we **evaluate the value** of the gradient, calculate step sizes, update parameters, repeat, etc.

Note: During BP, the equation of $\frac {\partial y_{\text{blue}}} {\partial b_1}$ needn't to be computed again, but the evaluation of the value of $\frac {\partial y_{\text{blue}}} {\partial b_1}$ should be recomputed, but it's a quick operation since it's numerical.



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

# Conclusion

BP is just a computation technique of Gradient Descent for the NN stucture.

The advantage of BP is to reduce the **computation complexity** of derivation via:

1. Using the chain rule.
2. Propagating **backward**, not forward.

Consider a NN with $n$ layers: $\{1,\cdots,i-1, i, \cdots,n\}$.

Suppose at layer $i$, BP computes following devivations:
$$
\begin{aligned}
\frac {\partial \text{Loss}} {\partial b_3} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial b_3} 
\\
\frac {\partial \text{Loss}} {\partial w_3} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial w_3} 
\\
\frac {\partial \text{Loss}} {\partial w_4} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial w_4} 
\end{aligned}
$$
Using BP, due to chain rule, we only need to perform 4 times derivations.

Moreover, note that the equation $\frac {\partial \text{Loss}} {\partial y_{\text{green}}} $ **has been solved in this layer.** (Of cource we need to evaluate its value every time, but it's a numerical operation and it's quick. The derivation operation is expensive)

Suppose at sequent layer $i-1$, BP computes following devivations:
$$
\begin{aligned}
\frac {\partial \text{Loss}} {\partial b_1} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}} 
\frac {\partial y_{\text{blue}}} {\partial b_1} 
\\
\frac {\partial \text{Loss}} {\partial w_1} = 
\frac {\partial \text{Loss}} {\partial y_{\text{green}}} 
\frac {\partial y_{\text{green}}} {\partial y_{\text{blue}}} 
\frac {\partial y_{\text{blue}}} {\partial w_1} 
\end{aligned}
$$
**We don't need to solve** the equation $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$  **again**!

However, this convience only happens in backword propagation. If we use forward propagation to perform derivation, at layer $i-1$ we don't know $\frac {\partial \text{Loss}} {\partial y_{\text{green}}}$ , so we have to solve it, and at layer $i$ we need to solve it again!

# Future

https://arxiv.org/abs/2212.13345

