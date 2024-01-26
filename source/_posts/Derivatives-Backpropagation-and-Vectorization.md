---
title: Derivatives, Backpropagation, and Vectorization
tags:
  - Machine Learning
categories: Mathematics
mathjax: true
date: 2024-01-25 21:30:05
---


Source:

1. [Derivatives, Backpropagation, and Vectorization](http://cs231n.stanford.edu/handouts/derivatives.pdf)
2. [Wikipedia: chain rule](https://en.wikipedia.org/wiki/Chain_rule)
3. [Wikipedia: quptient rule](https://en.wikipedia.org/wiki/Quotient_rule)

<!--more-->

# Tensors

> The word tensor is used in different ways in different fields; you may have seen the term before in physics or abstract algebra. The machine learning definition of a tensor as a $D$ dimensional grid of numbers is closely related to the definitions of tensors in these other fields.

In machine learning,

1. a 0-D tensor is a scalar, 
2. a 1-D tensor is a vector, 
3. a 2-D tensor is a matrix,
4. a 3-D and higher dimensional tensor is just called "tensor".

# Chain rule

If $h=f \circ g$ is the function such that $h(x)=f(g(x))$ for every $x$, then the chain rule is, in Lagrange's notation,
$$
h^{\prime}(x)=f^{\prime}(g(x)) g^{\prime}(x) .
$$
or, equivalently,
$$
h^{\prime}=(f \circ g)^{\prime}=\left(f^{\prime} \circ g\right) \cdot g^{\prime} .
$$

The chain rule may also be expressed in Leibniz's notation. If a variable $z$ depends on the variable $y$, which itself depends on the variable $x$ , then $z$ depends on $x$ as well, via the intermediate variable $y$. In this case, the chain rule is expressed as
$$
\frac{d z}{d x}=\frac{d z}{d y} \cdot \frac{d y}{d x}
$$
and
$$
\left.\frac{d z}{d x}\right|_x=\left.\left.\frac{d z}{d y}\right|_{y(x)} \cdot \frac{d y}{d x}\right|_x
$$
for indicating at which points the derivatives have to be evaluated.

#  Quotient rule

Let $h(x)=\frac{f(x)}{g(x)}$, where both $f$ and $g$ are differentiable and $g(x) \neq 0$. The quotient rule states that the derivative of $h(x)$ is
$$
h^{\prime}(x)=\frac{f^{\prime}(x) g(x)-f(x) g^{\prime}(x)}{g(x)^2} .
$$

# Scalar case

Given a function $f: \mathbb{R} \rightarrow \mathbb{R}$, the derivative of $f$ at a point $x \in \mathbb{R}$ is defined as:
$$
f^{\prime}(x)=\lim _{h \rightarrow 0} \frac{f(x+h)-f(x)}{h}
$$

In this scalar case, the derivative of the function $f$ at the point $x$ tells us how much the function $f$ changes as the input $x$ changes by a small amount $\varepsilon$ :
$$
f(x+\varepsilon) \approx f(x)+\varepsilon f^{\prime}(x)
$$

For ease of notation we will commonly assign a name to the output of $f$, say $y=f(x)$, and write $\frac{\partial y}{\partial x}$ for the derivative of $y$ with respect to $x$. We can write this relationship as
$$
x \rightarrow x+\Delta x \Longrightarrow y \rightarrow \approx y+\frac{\partial y}{\partial x} \Delta x
$$

You should read this as saying "changing $x$ to $x+\Delta x$ implies that $y$ will change to approximately $y+\Delta x \frac{\partial y}{\partial x}$ ". This notation is nonstandard, but I like it since it emphasizes the relationship between changes in $x$ and changes in $y$.



In the scalar case suppose that $f, g: \mathbb{R} \rightarrow \mathbb{R}$ and $y=f(x), z=g(y)$; then we can also write $z=(g \circ f)(x)$, or draw the following computational graph:
$$
x \stackrel{f}{\rightarrow} y \stackrel{g}{\rightarrow} z
$$

The (scalar) chain rule tells us that
$$
\frac{\partial z}{\partial x}=\frac{\partial z}{\partial y} \frac{\partial y}{\partial x}
$$
This equation makes intuitive sense. The derivatives $\frac{\partial z}{\partial y}$ and $\frac{\partial y}{\partial x}$ give:
$$
\begin{aligned}
& x \rightarrow x+\Delta x \Longrightarrow y \rightarrow \approx y+\frac{\partial y}{\partial x} \Delta x \\
& y \rightarrow y+\Delta y \Longrightarrow z \rightarrow \approx z+\frac{\partial z}{\partial y} \Delta y
\end{aligned}
$$

Combining these two rules lets us compute the effect of $x$ on $z$ : 

1. if $x$ changes by $\Delta x$ then $y$ will change by $\frac{\partial y}{\partial x} \Delta x$, so we have $\Delta y=\frac{\partial y}{\partial x} \Delta x$. 
2. If $y$ changes by $\Delta y$ then $z$ will change by $\frac{\partial z}{\partial y} \Delta y=\frac{\partial z}{\partial y} \frac{\partial y}{\partial x} \Delta x$ which is exactly what the chain rule tells us.

# Gradient: Vector in, scalar out

This same intuition carries over into the vector case. Now suppose that $f$ : $\mathbb{R}^N \rightarrow \mathbb{R}$ **takes a vector as input and produces a scalar**. The derivative of $f$ at the point $x \in \mathbb{R}^N$ is now called the **gradient**, and it is defined as:
$$
\nabla_x f(x)=\lim _{h \rightarrow 0} \frac{f(x+h)-f(x)}{\|h\|}
$$

The gradient  $\nabla_x f(x) \in \mathbb{R}^N$ , or $\frac{\partial y}{\partial x}$, is a vector of partial derivatives:
$$
\frac{\partial y}{\partial x}=\left(\frac{\partial y}{\partial x_1}, \frac{\partial y}{\partial x_2}, \ldots, \frac{\partial y}{\partial x_N}\right)
$$
where $x_i$ is the $i$ th coordinate of the vector $x$, which is a scalar, so each partial derivative $\frac{\partial y}{\partial x_i}$ is also a scalar.



If we set $y=f(x)$ then we have the relationship
$$
x \rightarrow x+\Delta x \Longrightarrow y \rightarrow \approx y+\frac{\partial y}{\partial x} \cdot \Delta x
$$

The formula changes a bit from the scalar case to account for the fact that **$x, \Delta x$, and $\frac{\partial y}{\partial x}$ are now vectors** in $\mathbb{R}^N$ while **$y$ is a scalar**. In particular when multiplying $\frac{\partial y}{\partial x}$ by $\Delta x$ we use the **dot product**, which combines two vectors to **give a scalar**.

# Jacobian: Vector in, Vector out

Now suppose that $f: \mathbb{R}^N \rightarrow \mathbb{R}^M$ **takes a vector as input and produces a vector as output**. Then the derivative of $f$ at a point $x$, also called the **Jacobian matrix**, is the **$M \times N$ matrix of partial derivatives**. If we again set $y=f(x)$ then we can write:
$$
\frac{\partial y}{\partial x}=\left(\begin{array}{ccc}
\frac{\partial y_1}{\partial x_1} & \cdots & \frac{\partial y_1}{\partial x_N} \\
\vdots & \ddots & \vdots \\
\frac{\partial y_M}{\partial x_1} & \cdots & \frac{\partial y_M}{\partial x_N}
\end{array}\right)
$$

The Jacobian tells us the relationship between each element of $x$ and each element of $y$ : the $(i, j)$-th element of $\frac{\partial y}{\partial x}$ is equal to $\frac{\partial y_i}{\partial x_j}$, so it tells us <u>the amount by which $y_i$ will change if $x_j$ is changed by a small amount.</u>



Just as in the previous cases, the Jacobian tells us the relationship between changes in the input and changes in the output:
$$
x \rightarrow x+\Delta x \Longrightarrow y \rightarrow \approx y+\frac{\partial y}{\partial x} \Delta x
$$

Here $\frac{\partial y}{\partial x}$ is a $M \times N$ matrix and $\Delta x$ is an $N$-dimensional vector, so the product $\frac{\partial y}{\partial x} \Delta x$ is a matrix-vector multiplication resulting in an $M$-dimensional vector: 
$$
\mathbb{R}^{M \times N} \cdot \mathbb{R}^{N \times 1} \rightarrow \mathbb{R}^{M \times 1} .
$$


The *chain rule* can be extended to the vector case using Jacobian matrices. Suppose that $f: \mathbb{R}^N \rightarrow \mathbb{R}^M$ and $g: \mathbb{R}^M \rightarrow \mathbb{R}^K$. Let $x \in \mathbb{R}^N, y \in \mathbb{R}^M$, and $z \in \mathbb{R}^K$ with $y=f(x)$ and $z=g(y)$, so we have the same computational graph as the scalar case:
$$
x \stackrel{f}{\rightarrow} y \stackrel{g}{\rightarrow} z
$$

The chain rule also has the same form as the scalar case:
$$
\frac{\partial z}{\partial x}=\frac{\partial z}{\partial y} \frac{\partial y}{\partial x}
$$

However now **each of these terms is a matrix**: $\frac{\partial z}{\partial y}$ is a $K \times M$ matrix, $\frac{\partial y}{\partial x}$ is a $M \times N$ matrix, and $\frac{\partial z}{\partial x}$ is a $K \times N$ matrix; the multiplication of $\frac{\partial z}{\partial y}$ and $\frac{\partial y}{\partial x}$ is matrix multiplication.

# Generalized Jacobian: Tensor in, Tensor out

Suppose now that $f: \mathbb{R}^{N_1 \times \cdots \times N_{D_x}} \rightarrow \mathbb{R}^{M_1 \times \cdots \times M_{D_y}}$. Then:

1. the input to $f$ is a $D_x$-dimensional tensor of shape $N_1 \times \cdots \times N_{D_x}$, and 
2. the output of $f$ is a $D_y$-dimensional tensor of shape $M_1 \times \cdots \times M_{D_y}$. 

If $y=f(x)$ then the derivative $\frac{\partial y}{\partial x}$ is a *generalized Jacobian*, which is an object with shape
$$
\left(M_1 \times \cdots \times M_{D_y}\right) \times\left(N_1 \times \cdots \times N_{D_x}\right)
$$

Note that we have separated the dimensions of $\frac{\partial y}{\partial x}$ into two groups: 

1. the first group matches the dimensions of $y$ and 
2. the second group matches the dimensions of $x$. 



With this grouping, we can think of the generalized Jacobian as generalization of a matrix, where each "row" has the same shape as $y$ and each "column" has the same shape as $x$.

Now if we let $i \in \mathbb{Z}^{D_y}$ and $j \in \mathbb{Z}^{D_x}$ be vectors of integer indices, then we can write
$$
\left(\frac{\partial y}{\partial x}\right)_{i, j}=\frac{\partial y_i}{\partial x_j}
$$

Note that **$y_i$ and $x_j$ are scalars, so the derivative $\frac{\partial y_i}{\partial x_j}$ is also a scalar**. Using this notation we see that like the standard Jacobian, the generalized Jacobian tells us the relative rates of change between all elements of $x$ and all elements of $y$.

The generalized Jacobian gives the same relationship between inputs and outputs as before:
$$
x \rightarrow x+\Delta x \Longrightarrow y \rightarrow \approx y+\frac{\partial y}{\partial x} \Delta x
$$

The difference is that now $\Delta x$ is a tensor of shape $N_1 \times \cdots \times N_{D_x}$ and $\frac{\partial y}{\partial x}$ is a generalized matrix of shape $\left(M_1 \times \cdots \times M_{D_y}\right) \times\left(N_1 \times \cdots \times N_{D_x}\right)$. The product $\frac{\partial y}{\partial x} \Delta x$ is therefore a <u>generalized matrix-vector multiply</u>, which results in a tensor of shape $M_1 \times \cdots \times M_{D_y}$.

The generalized matrix-vector multipy follows the same algebraic rules as a traditional matrix-vector multiply:
$$
\left(\frac{\partial y}{\partial x} \Delta x\right)_j=\sum_i\left(\frac{\partial y}{\partial x}\right)_{i, j}(\Delta x)_i=\left(\frac{\partial y}{\partial x}\right)_{j,:} \cdot \Delta x
$$

The only difference is that <u>the indicies $i$ and $j$ are not scalars; instead they are vectors of indicies</u>. In the equation above the term $\left(\frac{\partial y}{\partial x}\right)_{j,:}$ is the $j$ th "row" of the generalized matrix $\frac{\partial y}{\partial x}$, which is a tensor with the same shape as $x$. We have also used the convention that the dot product between two tensors of the same shape is an elementwise product followed by a sum, identical to the dot product between vectors.

The *chain rule* also looks the same in the case of tensor-valued functions. Suppose that $y=f(x)$ and $z=g(y)$, where $x$ and $y$ have the same shapes as above and $z$ has shape $K_1 \times \cdots \times K_{D_z}$. Now the chain rule looks the same as before:
$$
\frac{\partial z}{\partial x}=\frac{\partial z}{\partial y} \frac{\partial y}{\partial x}
$$

The difference is that now $\frac{\partial z}{\partial y}$ is a generalized matrix of shape $\left(K_1 \times \cdots \times K_{D_z}\right) \times$ $\left(M_1 \times \cdots \times M_{D_y}\right)$, and $\frac{\partial y}{\partial z}$ is a generalized matrix of shape $\left(M_1 \times \cdots \times M_{D_y}\right) \times$ $\left(N_1 \times \cdots \times N_{D_x}\right)$; the product $\frac{\partial z}{\partial y} \frac{\partial y}{\partial x}$ is a generalized matrix-matrix multiply, resulting in an object of shape $\left(K_1 \times \cdots \times K_{D_z}\right) \times\left(N_1 \times \cdots \times N_{D_x}\right)$. Like the generalized matrix-vector multiply defined above, the generalized matrixmatrix multiply follows the same algebraic rules as the traditional matrix-matrix multiply:
$$
\left(\frac{\partial z}{\partial x}\right)_{i, j}=\sum_k\left(\frac{\partial z}{\partial y}\right)_{i, k}\left(\frac{\partial y}{\partial x}\right)_{k, j}=\left(\frac{\partial z}{\partial y}\right)_{i,:} \cdot\left(\frac{\partial y}{\partial x}\right)_{:, j}
$$

In this equation the indices $i, j, k$ are vectors of indices, and the terms $\left(\frac{\partial z}{\partial y}\right)_{i \text {, }}$ and $\left(\frac{\partial y}{\partial x}\right)_{:, j}$ are the $i$ th "row" of $\frac{\partial z}{\partial y}$ and the $j$ th "column" of $\frac{\partial y}{\partial x}$ respectively.

# Backward Propagation with Tensors

In the context of neural networks, a layer $f$ is typically a function of (tensor) inputs $x$ and weights $w$; the (tensor) output of the layer is then $y=f(x, w)$. The layer $f$ is typically embedded in some large neural network with **scalar loss** $L$.

During backpropagation, we assume that we are given $\frac{\partial L}{\partial y}$ (its an [upstram gradient value](https://lyk-love.cn/2023/12/08/neural-networks/) and has been already computed in the upstram neoron) and our goal is to compute $\frac{\partial L}{\partial x}$ and $\frac{\partial L}{\partial w}$. By the chain rule we know that
$$
\frac{\partial L}{\partial x}=\frac{\partial L}{\partial y} \frac{\partial y}{\partial x} \quad \frac{\partial L}{\partial w}=\frac{\partial L}{\partial y} \frac{\partial y}{\partial w}
$$

Therefore one way to proceed would be to form the (generalized) Jacobians $\frac{\partial y}{\partial x}$ and $\frac{\partial y}{\partial w}$ and use (generalized) matrix multiplication to compute $\frac{\partial L}{\partial x}$ and $\frac{\partial L}{\partial w}$.



However, there's a problem with this approach: the Jacobian matrices $\frac{\partial y}{\partial x}$ and $\frac{\partial y}{\partial w}$ are typically far too large to fit in memory.

As a concrete example, let's suppose that: the layer $f$ is a linear layer that takes as input a minibatch of $N$ vectors, each of dimension $D$, and produces a minibatch of $N$ vectors, each of dimension $M$. 

Then $x$ is a matrix of shape $N \times D, w$ is a matrix of shape $D \times M$, and $y=f(x, w)=x w$ is a matrix of shape $N \times M$.
$$
f: \mathbb{R}^{N \times D} \rightarrow \mathbb{R}^{N \times M}
$$
The Jacobian $\frac{\partial y}{\partial x}$ then has shape $(N \times M) \times(N \times D)$. 



In a typical neural network we might have $N=64$ and $M=D=4096$; then $\frac{\partial y}{\partial x}$ consists of $64 \cdot 4096 \cdot 64 \cdot 4096$ scalar values; this is more than 68 billion numbers; using 32-bit floating point, this Jacobian matrix will take 256 GB of memory to store. Therefore **it is completely impossible to try and explicitly store and manipulate the Jacobian matrix**.

However it turns out that for most common neural network layers, we can derive expressions that compute the product $\frac{\partial y}{\partial x} \frac{\partial L}{\partial y}$ **without explicitly forming the Jacobian $\frac{\partial y}{\partial x}$**. Even better, we can typically derive this expression **without even computing an explicit expression for the Jacobian $\frac{\partial y}{\partial x}$**; in many cases we can work out a small case on paper and then infer the general formula.



Let's see how this works out for the case of the linear layer $f(x, w)=x w$. Set $N=1, D=2, M=3$. Then we can explicitly write
$$
\begin{align}
y & =\left(\begin{array}{lll}
y_{1,1} & y_{1,2} & y_{1,3}
\end{array}\right)=x w \nonumber \\
& =\left(\begin{array}{ll}
x_{1,1} & x_{1,2}
\end{array}\right)\left(\begin{array}{lll}
w_{1,1} & w_{1,2} & w_{1,3} \nonumber \\
w_{2,1} & w_{2,2} & w_{2,3}
\end{array}\right) \nonumber \\
& =\left(\begin{array}{l}
x_{1,1} w_{1,1}+x_{1,2} w_{2,1} \nonumber \\
x_{1,1} w_{1,2}+x_{1,2} w_{2,2} \nonumber \\
x_{1,1} w_{1,3}+x_{1,2} w_{2,3}
\end{array}\right)^T \label{eq_3}
\end{align}
$$

During backpropagation we assume that we have access to $\frac{\partial L}{\partial y}$ (it's the upstream gradient) which technically has shape $(1) \times(N \times M)$; however for notational convenience we will instead think of it as a matrix of shape $N \times M$. Then we can write
$$
\frac{\partial L}{\partial y}=\left(\begin{array}{lll}
d y_{1,1} & d y_{1,2} & d y_{1,3}
\end{array}\right)
$$

Our goal now is to derive an expression for $\frac{\partial L}{\partial x}$ in terms of $x, w$, and $\frac{\partial L}{\partial y}$, without explicitly forming the entire Jacobian $\frac{\partial y}{\partial x}$.



We know that $\frac{\partial L}{\partial x}$ will have shape (1) $\times(N \times D)$, but as is typical for representing gradients we instead view $\frac{\partial L}{\partial x}$ as a matrix of shape $N \times D$. 

We know that each element of $\frac{\partial L}{\partial x}$ is a scalar giving the partial derivatives of $L$ with respect to the elements of $x$ :
$$
\frac{\partial L}{\partial x}=\left(\begin{array}{ll}
\frac{\partial L}{\partial x_{1,1}} & \frac{\partial L}{\partial x_{1,2}}
\end{array}\right)
$$

Thinking one element at a time, the chain rule tells us that
$$
\begin{aligned}
\frac{\partial L}{\partial x_{1,1}} & =\frac{\partial L}{\partial y} \frac{\partial y}{\partial x_{1,1}} \\
\frac{\partial L}{\partial x_{1,2}} & =\frac{\partial L}{\partial y} \frac{\partial y}{\partial x_{1,2}}
\end{aligned}
$$



Viewing these derivatives as generalized matrices, $\frac{\partial L}{\partial y}$ has shape $(1) \times(N \times M)$ and $\frac{\partial y}{\partial x_{1,1}}$ has shape $(N \times M) \times(1)$; their product $\frac{\partial L}{\partial x_{1,1}}$ then has shape $(1) \times(1)$. If we instead view $\frac{\partial L}{\partial y}$ and $\frac{\partial y}{\partial x_{1,1}}$ as matrices of shape $N \times M$, then their generalized matrix product is simply the dot product $\frac{\partial L}{\partial y} \cdot \frac{\partial y}{\partial x_{1,1}}$.
Now we compute
$$
\begin{aligned}
& \frac{\partial y}{\partial x_{1,1}}=\left(\begin{array}{lll}
\frac{\partial y_{1,1}}{\partial x_{1,1}} & \frac{\partial y_{1,2}}{\partial x_{1,1}} & \frac{\partial y_{1,3}}{\partial x_{1,1}}
\end{array}\right)=\left(\begin{array}{lll}
w_{1,1} & w_{1,2} & w_{1,3}
\end{array}\right) \\
& \frac{\partial y}{\partial x_{1,2}}=\left(\begin{array}{lll}
\frac{\partial y_{1,1}}{\partial x_{1,2}} & \frac{\partial y_{1,2}}{\partial x_{1,2}} & \frac{\partial y_{1,3}}{\partial x_{1,2}}
\end{array}\right)=\left(\begin{array}{lll}
w_{2,1} & w_{2,2} & w_{2,3}
\end{array}\right)
\end{aligned}
$$
where the final equality comes from taking the derivatives of $\eqref{eq_3}$ with respect to $x_{1,1}$.
We can now combine these results and write
$$
\begin{aligned}
\frac{\partial L}{\partial x_{1,1}} & =\frac{\partial L}{\partial y} \cdot \frac{\partial y}{\partial x_{1,1}}=d y_{1,1} w_{1,1}+d y_{1,2} w_{1,2}+d y_{1,3} w_{1,3} \\
\frac{\partial L}{\partial x_{1,2}} & =\frac{\partial L}{\partial y} \cdot \frac{\partial y}{\partial x_{1,2}}=d y_{1,1} w_{2,1}+d y_{1,2} w_{2,2}+d y_{1,3} w_{2,3}
\end{aligned}
$$

This gives us our final expression for $\frac{\partial L}{\partial x}$ :
$$
\begin{aligned}
\frac{\partial L}{\partial x} & =\left(\begin{array}{ll}
\frac{\partial L}{\partial x_{1,1}} & \frac{\partial L}{\partial x_{1,2}}
\end{array}\right) \\
& =\left(\begin{array}{l}
d y_{1,1} w_{1,1}+d y_{1,2} w_{1,2}+d y_{1,3} w_{1,3} \\
d y_{1,1} w_{2,1}+d y_{1,2} w_{2,2}+d y_{1,3} w_{2,3}
\end{array}\right)^T \\
& =\frac{\partial L}{\partial y} x^T
\end{aligned}
$$

This final result $\frac{\partial L}{\partial x}=\frac{\partial L}{\partial y} x^T$ is very interesting because it allows us to efficiently compute $\frac{\partial L}{\partial x}$ **without explicitly forming the Jacobian $\frac{\partial y}{\partial x}$**. We have only derived this formula for the specific case of $N=1, D=2, M=3$ but it in fact holds in general.

By a similar thought process we can derive a similar expression for $\frac{\partial L}{\partial w}$ without explicitly forming the Jacobian $\frac{\partial y}{\partial w}$. You should try and work through this as an exercise.
