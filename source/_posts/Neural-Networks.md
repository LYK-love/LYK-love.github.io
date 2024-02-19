---
title: Neural Networks
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2023-12-08 19:43:54
---


Source: 

1. [The spelled-out intro to neural networks and backpropagation: building micrograd](https://www.youtube.com/watch?v=VMj-3S1tku0&feature=youtu.be)
2. [Stanford CS231N, Lecture 4](https://youtu.be/d14TUNcbn1k?si=fGVVrRpYIhqbBKBt)



Other useful resources:

1. [StatQuest's Neural Networks videos](https://www.youtube.com/watch?v=IN2XmBhILt4&list=PLblh5JKOoLUICTaGLRoHQDuF_7q2GfuJF&index=75)

2. [Efficient backprop](http://yann.lecun.com/exdb/publis/pdf/lecun-98b.pdf). You need do download it via

   ```sh
   wget http://yann.lecun.com/exdb/publis/pdf/lecun-98b.pdf
   ```



The python script and jupyter notebook used in this article can be found at [here](https://github.com/LYK-love/Machine-Learning-Basic).




This article is a step-by-step explanation of neural networks which are extensively used in machine learning. It only involves the most basic case where the input of a neuron is a vector (1-D tensor)and output of a neuron is a scalar (0-D tensor). But the idea holds for higher, please reter to [Derivatives, Backpropagation, and Vectorization](https://lyk-love.cn/2024/01/25/derivatives-backpropagation-and-vectorization/) for details.

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
  
* **NN** is short for a neural network.

* **FP** is short for forward pass, or foreward propagation.

* **BP** is short for backward pass, backward propagation or **backpropagation**.

# Article organization

The math model of neural network is **computational graph**, every operation of NN, including FP, BP and other fancy operations (like stop gradient in PyTorch) can be intuitively implemented and visualized on computational graph.

Thus, in this article, we take a view of **computational graph** to understand neural network. The organization is as follows:

1. To prepare, we first introduce the basic concepts of gradient.

2. We start from defining the `Value` class, a `Value` object is represent a single node in computational graph. Our implementation is highly similar to **PyTorch's** `Tensor` class.

3. Next, we illustrate the idea of **back propagation** and how to back propagate through the total graph.

4. In addition, since back propagation depends on concrete computation operations, we then introduce how to define each operation and let it support BP.

5. Now we know the idea of **back propagation** and support it in `Value` class. We use the later to build the components of neural networls, i.e.,

   1. We build a neoron first.
   2. Then we use neuron to build a linear layer.
   3. At last, we organize layers to form a multilayer perceptron (MLP).

6. Finally, we know FP, BP, how a NN is organized. We then show how to **train** this NN. We also orgainze our NN in a more modular way: letting all components inherit from a `Module` class.



# Basic concepts

## Neural networks

A **neoral network (NN)** is a function that maps input data to output data. For example, given a dataset with $n$ data points (or samples) $(x_1, y_{1}), \dots, (x_n, y_n)$, the neural network acts as a function, say $f$, that expressing the "relationship" between  $x$ and $y$:
$$
f_\theta: X \rightarrow \hat Y,
$$
where 

* $X, Y, \hat Y$ are the sets of all $x_i, y_i, \hat y_i$, $i \in \{1,2,\cdots, n \}$.
* $\hat y_i$ is the output value of the NN corresponding to input data $x_i$.
* $y_i$ is the value in the dataset corresponding to data $x_i$.
* $\theta$ is the set of all parameters of the NN. The parameters are all weights and biases.

## Loss function

The goal of a neural network is to **minimize the value of a [loss function]()** 
$$
\text{Loss}(y, \hat y) = \cdots .
$$
Since the loss function, the architecture of the NN, and the dataset are all given. What we can do is modifying (or **optimizing**) its parameters $\theta$. The **optimization** process is called **training** the NN.

## Derivative

Given a function $f(x) = 3x^2 - 4x + 5$,

```python
def f(x):
    return 3*(x**2) - 4*x + 5
```

It has plot:

```python
xs = np.arange(-5,5, 0.25)
ys = f(xs)

xs
plt.plot(xs,ys)
```

![Figure 1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%201.png)

The derivative equation of function $f$ w.r.t. variable $x$ is
$$
\begin{equation} \label{derivative}
f^\prime(x) = \frac {\partial f} {\partial x}=\lim _{h \rightarrow 0} \frac{f(x+h)-f(x)}{h} .
\end{equation}
$$
In this example, the derivative equation of $f(x)$ w.r.t. variable $x$ is $6x-4$. When $x=2/3$, the derivative becomes $0$. 

The physical meaning of $\frac {\partial f} {\partial x}$ is that "when $x$ changes a little bit, how much will $f$ change".

You can test it:

```python
hs = np.arange(0.0001,0.0, -0.00001)
x = 2/3
for h in hs:
    val = (f(x+h) - f(x)) / h
    print (f"h={h}, value={val}")
```

The output is:

```
h=0.0001, value=0.0002999999981767587
h=9e-05, value=0.0002699999976682774
h=8e-05, value=0.00023999999765322852
h=7.000000000000001e-05, value=0.0002099999983430832
h=6.000000000000001e-05, value=0.0001800000000902931
h=5.000000000000001e-05, value=0.00014999999464748723
h=4.000000000000001e-05, value=0.000119999987724384
h=3.000000000000001e-05, value=8.99999926436597e-05
h=2.0000000000000012e-05, value=5.9999982759961734e-05
h=1.0000000000000013e-05, value=3.0000002482211093e-05
```

As $h$ decreases, the value approaches $0$, which is the derivative value $f^\prime(2/3) = 0$.

## Help functions

For better understanding, we use these functions to visualize our computational graph:

```python
def trace(root):
  # builds a set of all nodes and edges in a graph
  nodes, edges = set(), set()
  
  # USE DFS to get all the nodes and edges
  def build(v):
    if v not in nodes:
      nodes.add(v)
      for child in v._prev:
        edges.add((child, v))
        build(child)
  build(root)
  return nodes, edges

def draw_dot(root):
  dot = Digraph(format='svg', graph_attr={'rankdir': 'LR'}) # LR = left to right
  
  nodes, edges = trace(root)
  for n in nodes:
    uid = str(id(n))
    # for any value in the graph, create a rectangular ('record') node for it
    dot.node(name = uid, label = "{ %s | data %.4f | grad %.4f }" % (n.label, n.data, n.grad), shape='record')
    if n._op:
      # if this value is a result of some operation, create an op node for it
      dot.node(name = uid + n._op, label = n._op)
      # and connect the op node to the node.
      dot.edge(uid + n._op, uid)

  for n1, n2 in edges:
    # connect n1 to the op node of n2, instead of n2.
    # For example, we have edge (a,e) in edges, rather than draw edge (a,e) in the graph, we instead draw edge (a,*), '*' is the op node of e.
    dot.edge(str(id(n1)), str(id(n2)) + n2._op)

  return dot
```

# Value class

Now we implement a basic `Value` class which shares the most fundamental features of `Tensor` in PyTorch.

```python
class Value:
    def __init__(self, data, _children=(), _op='', label=''):
        self.data = data
        self.grad = 0.0
        self._prev = set(_children)
        self._op = _op
        self.label = label
    def __repr__(self):
        return f"Value(data={self.data})"

    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data + other.data, (self, other), '+')
        return out

    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data * other.data, (self, other), '*')        
        return out
     pass
```

Each `Value` object is a node in the computational graph. If it's computed via an operation, such as `__add__`, `__mul__`, `__neg__`, `__true_div__` (not defined yet), it should set it's the operand(s) generating it as its predessor(s). This predecessorr relationship is implemented by the `self._prev` in each `Value` object.

```sh
a = Value(3, label='a')
b = Value(-2, label='b')
c = Value(1, label='c')
d = a+b; d.label='d'
e = c * d; e.label='e'
draw_dot(e)
```

The visualized computational graph is:

![Figure 2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%202.png)



For now we haven't implement the gradient computation yet, so in the previous graph each node doesn't have a gradient value. Let's see how gradient calculation is implemented in the computational graph.

## Gradient of each node

Now let's see the gradient value of each variable. We define a function $L = (ab+c)f$, and compute its gradient value with respect to variable `a`, `b`, `c`, etc.

```python
def lol():
  
  h = 0.001
  
  a = Value(2.0, label='a')
  b = Value(-3.0, label='b')
  c = Value(10.0, label='c')
  e = a*b; e.label = 'e'
  d = e + c; d.label = 'd'
  f = Value(-2.0, label='f')
  L = d * f; L.label = 'L'
  L1 = L.data
  
  a = Value(2.0, label='a')
  b = Value(-3.0, label='b')
  b.data += h
  c = Value(10.0, label='c')
  e = a*b; e.label = 'e'
  d = e + c; d.label = 'd'
  f = Value(-2.0, label='f')
  L = d * f; L.label = 'L'
  L2 = L.data
  
  print((L2 - L1)/h)
  
lol()
```

We set `h=0.001`. When we add `h` to `b`, the value of `(L2 - L1)/h` is `-3.99999999...`. If we continue to decrease `h`, we'll find that the value approaches `4.0`, which is exactly the gradient value
$$
\frac {\partial L} {\partial b}|_{b=-3.0} = af,
$$
since `a=2.0, f=-2.0`, $\frac {\partial L} {\partial b}|_{b=-3.0} = -4.0$.

# Backpropagation

## The idea of backpropagation

We now know that given a function $L$ and a variable $x$, we can calculate the gradient via equation $\eqref{derivative}$. However, a more efficient way is to leverage the [chain rule](https://lyk-love.cn/2024/01/25/derivatives-backpropagation-and-vectorization/#chain-rule) in Calculous:
$$
\frac{d z}{d x}=\frac{d z}{d y} \cdot \frac{d y}{d x} .
$$
The intuition here is that, given a function $L(x,y,z) = (x+y) z$, let $u = x+y$, then this function transforms to $L(u,z) = uz$, for computing the gradient of $x,z$, we can calculate $\frac{df}{d u} = z$ first, then leverage the chain rule to calculate

$$
\begin{align}
\frac{d L}{d x}=\frac{d L}{d u} \cdot \frac{d u}{d x} \label{chain_rule}\\
\frac{d L}{d y}=\frac{d L}{d u} \cdot \frac{d u}{d y} \nonumber .
\end{align}
$$
The gradient that have been already computed, i.e., $\frac{d L}{d u}$ in equation $\eqref{chain_rule}$, is called the **upstream gradient** of node `x` or `y`, since it's to be multiplied with the **local gradient** $\frac{d u}{d x}$ or $\frac{d u}{d y}$.

The **gradient** of `x` or `y` is **local gradient  * upstream gradient**.

In summary:

1. The **upstream gradient** of node $x$ or $y$: $\frac{d L}{d u}$.
2. The **local gradient** of node $x$ or $y$: $[\frac {\partial u} {x}, \frac {\partial u} {y}]^T$
3. The **gradient** of node $x$ or $y$: $[\frac {\partial L} {x}, \frac {\partial L} {y}]^T$. 

In order to leverage chain rule, we must do derivation of the computational graph **in a backward manner**. In other words, we must calculate $\frac{d L}{d u}$ before calculating $\frac{d u}{d x}$ and $\frac{d u}{d y}$. 

In this sense, the derivation process is called **back(ward) propagation**. 

* A detailed illustration is [--> here](https://gregorygundersen.com/blog/2018/04/15/backprop/).



One thing to notify is that the derivative of a variable with respect to itself is 1, i.e., for variable $y$,
$$
\frac{d}{d y} y=1 .
$$
Take the `e` node in the [previous section]() as an example, we have function $L = (a+b)c$ and variable $e = (a+b)c$, thus $\frac {\partial L} {\partial e} = \frac {\partial e} {\partial e} = 1$.



So we set the last node of the computational graph to have gradient=1.0 (you can think it as local gradient=1.0 and there's no upstream gradient).



We implement this in python by:

1. Add `grad` attribute to `Value` object.
2. For each computation operation, such as add, multiplication, division (not defined yet), etc, we implement the back propagate process as `_backward` method.

```python
class Value:
    def __init__(self, data, _children=(), _op='', label=''):
        self.data = data
        self.grad = 0.0
        self._backward = lambda: None
        self._prev = set(_children)
        self._op = _op
        self.label = label
    def __repr__(self):
        return f"Value(data={self.data})"

    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data + other.data, (self, other), '+')

        def _backward():
            self.grad += 1.0 * out.grad
            other.grad += 1.0 * out.grad
        out._backward = _backward
        return out

    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data * other.data, (self, other), '*')

        def _backward():
            self.grad += other.data * out.grad
            other.grad += self.data * out.grad
        out._backward = _backward

        return out
    pass
```

Each operation node Recall that in computational graphs, a node is a function. During backward propagation, w

corresponds to a "local gradient", that 

For instance, the multiplication operation $L=ab$ has gradient $\frac {\partial L} {\partial a}= b, \frac {\partial L} {\partial b}= a$, so the

```python
a = Value(3, label='a')
b = Value(-2, label='b')
c = Value(1, label='c')
d = a+b; d.label='d'
e = c * d; e.label='e'
draw_dot(e)
```

![Figure 3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 3.png)

We backpropagate through node `e`:

```python
e.grad = 1.0 # The last node should have gradient = 1.0
e._backward()
draw_dot(e)
```

![Figure 4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 4.png)

The gradient of node `d` is `1.0`, which equals to the value of node `c`; the gradient of node `c` is `1.0`, which equals to the value of node `d`. 



Moreover, the addition operation $L=a+b$ has gradient $\frac {\partial L} {\partial a}= 1, \frac {\partial L} {\partial b}= 1$, so that we backpropagate through node `d`

```python
d._backward()
draw_dot(e)
```

![Figure 5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 5.png)



To back progapate the whole computational graph, we need to call `backward()` for each node (if we can) mannually.

```python
e.backward()
d.backward()
c.backward() # We can ommit this since d c / d c = 1, where d is the partial derivation symbol.
a.backward() # We can ommit this since d a / d a = 1, where d is the partial derivation symbol.
b.backward() # We can ommit this since d a / d a = 1, where d is the partial derivation symbol.
draw_dot(e)
```



In this section, we defined the `_backward` method for operations `__add__` and `__mul__`. It can be implied that we can define the  `_backward` method for whatever operation we want to compute it's gradient as long as it's feasible, i.e., the operation itself is **first-order differentiable**.

However, we must call the `_backward` method for each node manually in some fixed order, we can't back propagate `c` before back propagate `e`. Is there any way to automate this process so that we can do back propagation only once and calculate the gradient for the whole graph?

## Backpropagate through the whole graph

The solution is simple:

1. Remember that the last node itself must set its gradient to 1.0.
2. Sort all the nodes in the computational graph in a topological order. 
3. From the last node to the first node in the computational graph, call their `_backward` method seperately.

Here's the code:

```python
class Value:
  pass

	def backward(self):
        topo = []
        visited = set()
        def build_topo(v):
            if v not in visited:
                visited.add(v)
                for child in v._prev:
                    build_topo(child)
                topo.append(v)
        build_topo(self)

        self.grad = 1.0
        for node in reversed(topo):
            node._backward()
```



We can call this `backward` method to the last node of any computational graph without the heavy manual work.

```python
a = Value(7, label='a')
b = Value(-2, label='b')
c = Value(1, label='c')
d = a+b; d.label='d'
e = c * d; e.label='e'
f = e + a; f.label="f"
draw_dot(f)
```

![Figure 6](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 6.png)

```python
f.grad = 1.0 
f.backward()
draw_dot(f)
```

![Figure 7](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 7.png)

# Operations to be back propagated

Now we define more commonly used operations and add `_backward` support to them. 

## Operations can be set on arbitary abstraction level

Note that the operation can be set at arbitary abstraction level.

For example, for [tanh function](https://lyk-love.cn/2024/01/25/activation-functions/#tanh):
$$
\begin{aligned}
\tanh (x)=\frac{e^{2 x}-1}{e^{2 x}+1}
\end{aligned}
$$
with derivative
$$
\frac{d}{d x} \tanh (x)=1-\tanh (x)^2 =1-\frac{\left(e^x-e^{-x}\right)^2}{\left(e^x+e^{-x}\right)^2} .
$$
We can either define tanh outside of `Value` class, and define operations divisiontogether with exponent.



### Low level

We can build tahh from low level through defining exp, addition and other low level operations. We don't have to define tanh in the `Value` class.

```python
class Value:
    pass

    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data + other.data, (self, other), '+')

        def _backward():
            self.grad += 1.0 * out.grad
            other.grad += 1.0 * out.grad
        out._backward = _backward
        return out

    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data * other.data, (self, other), '*')

        def _backward():
            self.grad += other.data * out.grad
            other.grad += self.data * out.grad
        out._backward = _backward

        return out
    def __pow__(self, other):
        assert isinstance(other, (int, float)), "only supporting int/float powers for now"
        out = Value(self.data**other, (self,), f'**{other}')

        def _backward():
            self.grad += other * (self.data ** (other - 1)) * out.grad
        out._backward = _backward

        return out

    def __truediv__(self, other): # self / other
        return self * other**-1

    def exp(self):
        x = self.data
        out = Value(math.exp(x), (self, ), 'exp')

        def _backward():
            self.grad += out.data * out.grad # NOTE: in the video I incorrectly used = instead of +=. Fixed here.
        out._backward = _backward

        return out
```

Create the graph:

```python
def tanh(x):
    out = ((x*2).exp() - 1) / ((x*2).exp() + 1)
    return out

x =  Value(2.0, label='x')
o = tanh(x)
draw_dot(o)
```

![Figure 8](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 8.png)

Start back propagation:

```python
o.grad = 1.0
o.backward()
draw_dot(o)
```

![Figure 9](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 9.png)

### High livel

We can define the `_backward` for tanh instead:

```python
class Value:
    pass
    
    def tanh(self):
        x = self.data
        t = (math.exp(2*x) - 1)/(math.exp(2*x) + 1)
        out = Value(t, (self, ), 'tanh')

        def _backward():
            local_grad = (1 - t**2)
            self.grad += local_grad * out.grad
        out._backward = _backward
        return out
```

Cteate the graph:

```python
x =  Value(2.0, label='x')
o = x.tanh()
draw_dot(o)
```

![Figure 10](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 10.png)



Start back propagation:

```python
o.grad = 1.0
o.backward()
draw_dot(o)
```

![Figure 11](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 11.png)

## Operation zoo

### Addition

$$
\begin{aligned}
\frac{d}{d x}\left(x+y\right) = 1 \\
\frac{d}{d y}\left(x+y\right) = 1
\end{aligned}
$$

```python
    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data + other.data, (self, other), '+')

        def _backward():
            self.grad += 1.0 * out.grad
            other.grad += 1.0 * out.grad
        out._backward = _backward
        return out
    def __radd__(self, other): # other + self
        return self + other
```

### Multiplication

$$
\begin{aligned}
\frac{d}{d x}\left(xy\right) = y \\
\frac{d}{d y}\left(xy\right) = x
\end{aligned}
$$



```python
    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other) # Wrap the other operand to be `Value`
        out = Value(self.data * other.data, (self, other), '*')

        def _backward():
            self.grad += other.data * out.grad
            other.grad += self.data * out.grad
        out._backward = _backward
    def __rmul__(self, other): # other * self
        return self * other        
```

### Negation

We achieve negation through multiplication:
$$
-x = x \cdot (-1) .
$$

```python
    def __neg__(self): # -self
        return self * -1
```

### Substraction

We achieve substraction through addition and negation:
$$
x - y = x  + (-y)
$$

```python
    def __sub__(self, other): # self - other
        return self + (-other)
```



### Exponential function

$$
\frac{d}{d x}\left(e^x\right) = e^x .
$$

So the local graddient is just the data of the output.

```python
def exp(self):
        x = self.data
        out = Value(math.exp(x), (self, ), 'exp')

        def _backward():
            local_gradient = out.data
            self.grad += local_gradient * out.grad
        out._backward = _backward
```

### Power

$$
\frac{d}{d x} \left(x^n\right) = n x^{n-1} .
$$



```python
    def __pow__(self, other):
        assert isinstance(other, (int, float)), "only supporting int/float powers for now"
        out = Value(self.data**other, (self,), f'**{other}')

        def _backward():
            self.grad += other * (self.data ** (other - 1)) * out.grad
        out._backward = _backward

        return out
```

### Division

We achieve division through power:
$$
x / y = x \cdot y^{-1} .
$$

```python
def __truediv__(self, other): # self / other
        return self * other**-1
```

### tanh

As before, tanh is

```python
     def tanh(self):
        x = self.data
        t = (math.exp(2*x) - 1)/(math.exp(2*x) + 1)
        out = Value(t, (self, ), 'tanh')

        def _backward():
            local_grad = (1 - t**2)
            self.grad += local_grad * out.grad
        out._backward = _backward
```



### Relu

The derivative of relu at x=0 is set to 0.

```python
    def relu(self):
        out = Value(0 if self.data < 0 else self.data, (self,), 'ReLU')

        def _backward():
            local_grad = 1 if out.data > 0 else 0
            self.grad += (out.data > 0) * out.grad
        out._backward = _backward

        return out
```



# Neuron

![Neuron](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Neuron.png)

[--> Image source](https://towardsdatascience.com/the-basics-of-neural-networks-neural-network-series-part-1-4419e343b2b)



Now we know backpaopagation, it's time to investigate Neural networks. In this section, we are going to implement a single neuron conducting computation 
$$
\hat y = g(\sum_{i=1}^{n} w_i x_i + b)
$$
where the input is a vector $x$ with length $n$, the output is a scalar $y$, the <u>activation function</u> is denoted as $g$, the parameters can be solit into two parts:

1. A weight vector $w$, should have length $n$ as well.
2. A bias $b$, which is a scaler.



We also implement the `parameters` method to get all the $n+1$ parameters of this neuron, i.e., the $n$  weights and one bias.

```python
class Neuron():
  
  def __init__(self, nin):
      '''
      nin: the dimension of input data point, which is a vector.
      
      Here we initialize the weights and thr bias via a uniform distribution. In practice it's up to you to choose the initialization method, sometimes a normal distribution is better, sometimes we set them to be all zero, there are also more complicated methods such as [Xavier](https://cs230.stanford.edu/section/4/).
      '''
      self.w = [Value(random.uniform(-1,1)) for _ in range(nin)]
      self.b = Value(random.uniform(-1,1))
      
  def __call__(self, x):
      '''
      w * x + b, where "*" is dot product
      Then apply tanh as the activation function.
      The output is a scalar.
      '''
      act = sum(w_i * x_i for w_i, x_i in zip(self.w, x)) + self.b
      out = act.tanh()
      return out
  
  def parameters(self):
    return self.w + [self.b]
```

The compututational graph of a neuron is like:

```python
x = [2.0, 3.0, -1.0]
n = Neuron(len(x))
o = n(x)
draw_dot(o)
```

![Figure 12](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure%2012.png)

We can backpropagate it:

```python
o.backward()
draw_dot(o)
```

![Figure 13](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 13.png)

# Layer

In the same way, we define a layer (or **linear layer** since every neuron performs linear transformation):

```python
class Layer():
  
  def __init__(self, nin, nout):
      '''
      nin: the dimension of input data point, which is a vector.
      nout: the dimension of the output, which equals to the number of the neurons in the layer since each neuron outputs a scalar as one element of the output vector.
      '''
      self.neurons = [Neuron(nin) for _ in range(nout)]
  
  def __call__(self, x):
    outs = [n(x) for n in self.neurons]
    return outs[0] if len(outs) == 1 else outs # If the output is a vector with length=1, then we output its scalar version instead.
  
  def parameters(self):
    return [p for neuron in self.neurons for p in neuron.parameters()]
```

# Multilayer perceptron

Despite it's fancy name, a multilayer perceptron (MLP) is just a combination of linear layers, it'sorganized in at least three layers:

* Input Layer
* Hidden Layer(s)
* Output Layer

Below is a simple MLP with one input layer (dimension=3), two hidden layers (dimension=4 for each), one output layer (dimension=1):

![MLP](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/MLP.png)

```python
class MLP():
  
  def __init__(self, nin, nouts):
    '''
    nin: the dimension of input data point, which is a vector.
    nouts: the list of the `nout` of each layer.
    '''
    
    # sz: the size of the MLP.
    # For example, if input vector has dimension=3, we have 3 layers with dimension=4,4,1 separately, then 
    # total size of the MLP is [3,4,4,1], i.e., we add a first layer with size (3,4).
    sz = [nin] + nouts 
    self.layers = [Layer(sz[i], sz[i+1]) for i in range(len(nouts))]
  
  def __call__(self, x):
    for layer in self.layers:
      x = layer(x)
    return x
  
  def parameters(self):
    return [p for layer in self.layers for p in layer.parameters()]
```



Now we create the computational graph for MLP:

```python
x = [2.0, 3.0, -1.0]
n = MLP(3, [4, 4, 1])
o = n(x)
draw_dot(o)
```



Note that the graph has already been very huge:

![Figure 14](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 14.png)

As before, we can easily back propagate it:

```python
o.backward()
draw_dot(o)
```

![Figure 15](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 15.png)

One glimpse into it:

![Figure 16](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Neural%20Networks/Figure 16.png)



# Training process

```python
def train(n, episodes=20, learning_rate=-0.1):
    '''
    n: the neural network
    episodes: the times of the training
    learning_rate: the step size of each gradient descent step
    '''
    for k in range(episodes):

        # forward pass
        ypred = [n(x) for x in xs]
        loss = sum((yout - ygt) ** 2 for ygt, yout in zip(ys, ypred))  # The loss function is simply the MSE loss.

        # backward pass
        # n.zero_grad()
        for p in n.parameters():
            p.grad = 0.0
        loss.backward()

        # update
        for p in n.parameters():
            p.data += -learning_rate * p.grad

        print(k, loss.data)
```

During each training iteration, we do forward pass and backward pass, then use the gradient to update the parameters. 

```python
if __name__ == '__main__':
    xs = [
        [2.0, 3.0, -1.0],
        [3.0, -1.0, 0.5],
        [0.5, 1.0, 1.0],
        [1.0, 1.0, -1.0],
    ]
    ys = [1.0, -1.0, -1.0, 1.0]

    n = MLP(3, [4, 4, 1])
    train(n)
```

Output:

```
0 3.0023652813181076
1 7.829656796657114
2 7.873495186948614
3 7.898971556682395
4 7.915750651920874
5 7.927679560403236
6 7.93661348136074
7 7.943562957166411
8 7.949127470610182
9 7.9536859717913115
10 7.957490110712908
11 7.960713728194046
12 7.963480863718541
13 7.965882448401477
14 7.967986690055242
15 7.969845771638371
16 7.9715003073212936
17 7.972982387122015
18 7.9743177063547
19 7.975527086007134
```



We must flash the gradients before doing BP. Otherwise the gradients in each iteration will accumulate. This can be implemented as a function `zero_grad`, which is what PyTorch did.

# Module

At last, to be more compatible with PyTorch, we organize our NN, let all componnets (`Neuron`, `Layer` and `MLP`) inherit a base `Module` class:

```python
class Module:
    def zero_grad(self):
        for p in self.parameters():
            p.grad = 0

    def parameters(self):
        return []
      
class Value:
  pass
class Neuron(Module):
  pass
class Layer(Module):
  pass
class MLP(Module):
  pass
```



