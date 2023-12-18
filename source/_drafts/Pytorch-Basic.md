---
title: Pytorch Basic
tags:
- Machine Learning
- Machine Learning
- Pytorch
categories: Technology
mathjax: true
---

For all modern deep learning frameworks, the tensor class (ndarray in MXNet, Tensor in PyTorch and TensorFlow) resembles NumPy’s ndarray, with a few killer features added. First, the tensor class supports <u>automatic differentiation</u>. Second, <u>it leverages GPUs to accelerate numerical computation</u>, whereas NumPy only runs on CPUs. These properties make neural networks both easy to code and fast to run.



A tensor represents a (possibly multi-dimensional) array of numerical values. 

* With one axis, a tensor is called a *vector*. 
* With two axes, a tensor is called a *matrix*.
* With $k>2$ axes, we drop the specialized names and just refer to the object as a $k^{th}$ *order tensor*.

Each of these values is called an *element* of the tensor. 



# Data Manipulation

## Create a tensor

* Create a vector of <u>evenly spaced</u> values, starting at 0 (included) and ending at `n` (not included). By default, the interval size is 1.

  ```python
  x = torch.arange(12, dtype=torch.float32)
  # Output: tensor([ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10., 11.])
  ```

  Unless otherwise specified, new tensors are stored in main memory and designated for <u>CPU</u>-based computation.

* Creates a (3,4) tensor with elements drawn from a standard Gaussian (normal) distribution $\mathcal N(0,1)$.

  ```
  torch.randn(3, 4)
  ```

  * Recalling that for r.v. $X \sim \mathcal N(\mu, \sigma^2)$, if $Y = a + X$, then $Y \sim \mathcal N(a + \mu, \sigma^2)$; if $Z = a X$, then $Z \sim \mathcal N(a\mu, a^2\sigma^2)$. So we can create a tensor $\mathcal N(5,2)$:

    ```python
    X = torch.randn(3,4)
    mean = 5
    variance = 2
    Z = mean + torch.sqrt(torch.tensor(variance)) * X
    ```

* Create a tensor from a list:

  ```python
  torch.tensor([[2, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]])
  ```

  

* Create an all-zero or all-one tensor:

  ```
  torch.zeros((2, 3, 4))
  torch.ones((2, 3, 4))
  ```



* Get the number of elements in a tensor:

  ```python
  x.numel()
  ```

* shape: We can access a tensor’s *shape* (the length along each axis) by inspecting its `shape` attribute:

  ```python
  x.shape
  ```

* reshape: We can change the shape of a tensor without altering its size or values, by invoking `reshape`. For example, we can transform our vector `x` whose shape is (12,) to a matrix `X` with shape (3, 4):

  ```python
  X = x.reshape(3, 4)
  ```

  Note that specifying every shape component to `reshape` is redundant. Because we already know our tensor’s size, we can work out one component of the shape given the rest. For example, given a tensor of size $n$ and target shape $(h,w)$, we know that $w = n / h$. To automatically infer one component of the shape, we can place a `-1` for the shape component that should be inferred automatically. In our case, instead of calling `x.reshape(3, 4)`, we could have equivalently called `x.reshape(-1, 4)` or `x.reshape(3, -1)`.



## Operations

### unary operators

Most standard operators can be applied elementwise including *unary* operators like $e^x$.

```python
torch.exp(x)
```

### binary operators

```
x = torch.tensor([1.0, 2, 4, 8])
y = torch.tensor([2, 2, 2, 2])
x + y, x - y, x * y, x / y, x ** y
```



Also, remember that the `==` operator can compare the value of the objects. It's also elementwise for tensor.

```python
X == Y
```



### concatenate

The example below shows what happens when we concatenate two matrices along rows (axis 0) instead of columns (axis 1). We can see that the first output’s axis-0 length () is the sum of the two input tensors’ axis-0 lengths (); while the second output’s axis-1 length () is the sum of the two input tensors’ axis-1 lengths ().

```python
X = torch.arange(12, dtype=torch.float32).reshape((3,4))
Y = torch.tensor([[2.0, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]])
P = torch.cat((X, Y), dim=0) # Get a (3+3) * 4 tensor.
print(P.shape) # torch.Size([6, 4])
Q = torch.cat((X, Y), dim=1) # Get a (3) * (4+4) tensor.
print(Q.shape) # torch.Size([3, 8])
```

### Broadcasting

Even when shapes differ, we can still perform elementwise binary operations by invoking the *broadcasting mechanism*. 

Broadcasting works according to the following two-step procedure: 

1. expand one or both arrays by copying elements along axes with length 1 so that after this transformation, the two tensors have the same shape;
2. perform an elementwise operation on the resulting arrays.

```
a = torch.arange(3).reshape((3, 1))
b = torch.arange(2).reshape((1, 2))
```

## Saving Memory

If we write `Y = X + Y`, we dereference the tensor that `Y` used to point to and instead point `Y` at the <u>newly allocated memory</u>. 

```python
before = id(Y)
Y = Y + X
id(Y) == before
# False
```



Fortunately, performing in-place operations is easy. We can assign the result of an operation to a previously allocated array `Y` by using slice notation: `Y[:] = <expression>`. To illustrate this concept, we overwrite the values of tensor `Z`, after initializing it, using `zeros_like`, to have the same shape as `Y`.

```
Z = torch.zeros_like(Y)
print('id(Z):', id(Z))
Z[:] = X + Y
print('id(Z):', id(Z))
```

```
id(Z): 140381179266448
id(Z): 140381179266448
```

If the value of `X` is not reused in subsequent computations, we can also use `X[:] = X + Y` or `X += Y` to reduce the memory overhead of the operation.

```
before = id(X)
X += Y
id(X) == before
```

```
True
```



# Calculus

$$
f'(x) = \lim_{h \rightarrow 0} \frac{f(x+h) - f(x)}{h}.
$$





Define $u = f(x) = 3x^2-4x$, 

```python
def f(x):
    return 3 * x ** 2 - 4 * x
```

We can see that $f'(x) = 6x - 4$ and $f'(1) = 2$.



Now in pytorch, we evaluate numerical value of $f'(1)$ given $h = 10^{-1}, 10^{-2}, 10^{-3}, \cdots$.

```python
# np.arange(-1, -6, -1): Create an array of values ranging from -1 to -6 (exclusive) with a step of -1.
for h in 10.0**np.arange(-1, -6, -1): 
    print(f'h={h:.5f}, numerical limit={(f(1+h)-f(1))/h:.5f}')
```

As $h$ becomes smaller, the result approaches $2$:

```
h=0.10000, numerical limit=2.30000
h=0.01000, numerical limit=2.03000
h=0.00100, numerical limit=2.00300
h=0.00010, numerical limit=2.00030
h=0.00001, numerical limit=2.00003
```



## Plot

Define $u = f(x) = 3x^2-4x$, since:

1. $f'(x=1) = 3 * 1 -4 = 2$
2. $f(1) = -1$

So the tangent line at $x=3$ is $y = 2x-1$.

![../_images/output_calculus_7e7694_56_0.svg](http://d2l.ai/_images/output_calculus_7e7694_56_0.svg)

 

# Automatic Differentiation

Let’s assume that we are interested in differentiating the function with respect to the column vector . To start, we assign `x` an initial value.

Let $x = [0,1,2,3]^{\text{T}}$, $y = 2xx^{\text{T}}$. Note: y is the "<u>dot product</u>" of $x , x^{\text{T}}$.

```python
# Can also create x = torch.arange(4.0, requires_grad=True)

x = torch.arange(4.0) # tensor([0., 1., 2., 3.], requires_grad=True)
x.requires_grad_(True) # Store the gradient

y = 2 *  torch.dot(x, x) # tensor(28., grad_fn=<MulBackward0>)
```



We can now take the gradient of `y` with respect to `x` by calling its `backward` method. Next, we can access the gradient via `x`’s `grad` attribute.

```python
y.backward()
print(f"x.grad: {x.grad}")
# x.grad: tensor([ 0.,  4.,  8., 12.])
```

We already know that the gradient of the function $y = 2xx^{\text{T}}$ with respect $x$ to should be $4x$.
```python
print(x.grad == 4*x)
print(f"4*x = {4*x } when x = {x}")
print(f"x.grad = {x.grad } when x = {x}")
print(x.grad == 4*x)
```



PyTorch does not automatically reset the gradient buffer when we record a new gradient. Instead, the new gradient is added to the already-stored gradient. This behavior comes in handy when we want to optimize the sum of multiple objective functions. To reset the gradient buffer, we can call `x.grad.zero_()` as follows:

```python
x.grad.zero_()  # Reset the gradient
```



## Example: $y = \sum x_i$

```python
y = x.sum()
y.backward()
x.grad # x.grad: tensor([1., 1., 1., 1.])
```

# Documentation

While we cannot possibly introduce every single PyTorch function and class (and the information might become outdated quickly), the [API documentation](https://pytorch.org/docs/stable/index.html) and additional [tutorials](https://pytorch.org/tutorials/beginner/basics/intro.html) and examples provide such documentation. This section provides some guidance for how to explore the PyTorch API.

* To know which functions and classes can be called in a module, we invoke the `dir` function. For instance, we can query all properties in the module for generating random numbers:

  ```python
  print(dir(torch.distributions))
  ```

* For specific instructions on how to use a given function or class, we can invoke pytorch's `help` function. As an example, let’s explore the usage instructions for tensors’ `ones` function.

  ```python
  help(torch.ones)
  ```

  

# Debug

The core functionalities of PyTorch, including data loading, are  implemented in C++. While you interact with these utilities using  Python, the actual work is done in the C++ backend. This means that you  might not have direct access to the Python-level source code during  debugging.

![image-20231217145350730](/Users/lyk/Library/Application Support/typora-user-images/image-20231217145350730.png)
