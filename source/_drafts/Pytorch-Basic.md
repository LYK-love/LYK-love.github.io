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



* number of elements in a tensor:

  ```
  x.numel()
  ```

  

* shape: We can access a tensor’s *shape* (the length along each axis) by inspecting its `shape` attribute. Because we are dealing with a vector here, the `shape` contains just a single element and is identical to the size.

  ```
  x.shape
  ```

* reshape: We can change the shape of a tensor without altering its size or values, by invoking `reshape`. For example, we can transform our vector `x` whose shape is (12,) to a matrix `X` with shape (3, 4). This new tensor retains all elements but reconfigures them into a matrix. <u>Notice that the elements of our vector are laid out one row at a time and thus `x[3] == X[0, 3]`.</u>

  ```shape
  
  X = x.reshape(3, 4)
  ```

  Note that specifying every shape component to `reshape` is redundant. Because we already know our tensor’s size, we can work out one component of the shape given the rest. For example, given a tensor of size $n$ and target shape $(h,w)$, we know that $w = n / h$. To automatically infer one component of the shape, we can place a `-1` for the shape component that should be inferred automatically. In our case, instead of calling `x.reshape(3, 4)`, we could have equivalently called `x.reshape(-1, 4)` or `x.reshape(3, -1)`.

# Data Manipulation

## operations

Among the most useful tools are the *elementwise* operations. These **apply a standard scalar operation to each element of a tensor.**

Most standard operators can be applied elementwise including *unary* operators like $e^x$.

```python
torch.exp(x)
```



Likewise, we denote *binary* scalar operators, which map pairs of real numbers to a (single) real number. The common standard arithmetic operators for addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and exponentiation (`**`) have all been *lifted* to elementwise operations for identically-shaped tensors of arbitrary shape.

```
x = torch.tensor([1.0, 2, 4, 8])
y = torch.tensor([2, 2, 2, 2])
x + y, x - y, x * y, x / y, x ** y
```
