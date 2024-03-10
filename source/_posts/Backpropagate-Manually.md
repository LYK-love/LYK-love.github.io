---
title: Backpropagate Manually
tags:
  - Machine Learning
categories: Computer Science
mathjax: true
date: 2024-03-04 23:52:07
---





How to back propagate through a neural network **manually**, i.e., without calling `loss.backward()`. This can accelerate one's understanding of back propagation.

This article is inspired by Adjrej Karpathy's video [Building makemore Part 4: Becoming a Backprop Ninja](https://www.youtube.com/watch?v=q8SA3rM6ckI&list=PLAqhIrjkxbuWI23v9cThsA9GvCAUhRvKZ&index=5&t=5798s).

The full code used in this article can be found [here](https://github.com/LYK-love/Machine-Learning-Basic/blob/main/makemore/makemore_part4_from_scratch.ipynb).

<!--more-->

# Note: The local gradient

The gradient of a variable has the same shape with the variable itself. For instance, if `y` has shape [32,1], then `y.grad` has shape [32,1].

However, in PyTorch a variable can be broadcasted to another shape, and it's the latter one that actually participates the computation. In this sense, the so-called "local gradient" of the variable is actually the local gradient of the broadcasted one, and has the same shape with the broadcasted one.

In this article, when I refer to "**local gradient**" of a variable, I refer to **the local gradient of the broadcasted one**, and it always **has the same shape with the broadcasted one**. One can say that t<u>he local gradient of a variable doesn't have to be the same shape as it</u>. This shouldn't be confusing.

After we get the local gradient (for the broadcasted one), we multiply it with the upstream gradient, **the result will have the shape as the broadcasted one**.

**We then accumulate and squeeze it to have the same shape with the originalvariable**.

For example, suppose we have an equation:

```python
f = x - y 
```

where 

* `f.shape`: torch.Size([32, 27])
* `x.shape`: torch.Size([32, 27])
* `y.shape`: torch.Size([32, 1])

PyTorch will broadcast `y` to be a [32,27] tensor, say `y_broadcasted` . The real computation is

```python
f = x - y_broadcasted # [32,27], [32,27] --> [32,27]
```

So the "local gradient" of `y` is in fact the local gradient of `y_broadcasted`, whose shape is **[32,27]**.

We then multiply it with the upstream gradient, i.e., the gradient of `f` with shape [32,27], to get the local gradient of `y` (or `y_broadcasted`).

After that, we have a gradient with shape [32,27]:

```python
gradient = - df # df is the gradient of f, with shape [32,27]
```



Since `y` is broadcasted into `y_broadcasted`. We squeeze it to get the gradient of `y`.

```python
gradient = gradient.sum(1, keepdims=True)
```

# Notations

* In my code, variable name `d{x}` means the gradident (aka grad) of variable x.

# Exercise 1 

Say we have following forward pass (written in PyTorch):

```python
# forward pass, "chunkated" into smaller steps that are possible to backward one at a time

emb = C[Xb] # embed the characters into vectors
embcat = emb.view(emb.shape[0], -1) # concatenate the vectors
# Linear layer 1
hprebn = embcat @ W1 + b1 # hidden layer pre-activation
# BatchNorm layer
bnmeani = 1/n*hprebn.sum(0, keepdim=True)
bndiff = hprebn - bnmeani
bndiff2 = bndiff**2
bnvar = 1/(n-1)*(bndiff2).sum(0, keepdim=True) # note: Bessel's correction (dividing by n-1, not n)
bnvar_inv = (bnvar + 1e-5)**-0.5
bnraw = bndiff * bnvar_inv
hpreact = bngain * bnraw + bnbias
# Non-linearity
h = torch.tanh(hpreact) # hidden layer
# Linear layer 2
logits = h @ W2 + b2 # output layer
# cross entropy loss (same as F.cross_entropy(logits, Yb))
logit_maxes = logits.max(1, keepdim=True).values
norm_logits = logits - logit_maxes # subtract max for numerical stability
counts = norm_logits.exp()
counts_sum = counts.sum(1, keepdims=True)
counts_sum_inv = counts_sum**-1 # if I use (1.0 / counts_sum) instead then I can't get backprop to be bit exact...
probs = counts * counts_sum_inv
logprobs = probs.log()
loss = -logprobs[range(n), Yb].mean()
```

How to back propagate it?



## loss

First, `loss` is the last node in the computational graph, and in PyTorch it's regulated to be a scalar. Therefore, we set it's grad to be `1`:

```python
dloss = 1
```

## logprobs

```python
loss = logprobs[range(n), Yb].mean()
```

where

* `Yb.shape` = torch.Size([n])
* `logprobs.shape` = torch.Size([n,k])

The grad of `logprobs` is

```python
dlogprobs = torch.zeros_like(logprobs)
dlogprobs[range(n), Yb] = - 1.0 / n * 1 # 1 is the remote gradient from `loss`
```

Explanation:

Say `n=3, logprobs.shape[1]=2`, and we choose a random `Yb` so thant the code equals to this formula:
$$
\begin{aligned}
& f\left(\left[\begin{array}{ll}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right],\left[\begin{array}{ll}
0 & 1 \\
1 & 0 \\
1 & 0
\end{array}\right]\right) \\
= & \operatorname{mean} \left(\left[\begin{array}{ll}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right] *\left[\begin{array}{ll}
0 & 1 \\
1 & 0 \\
1 & 0
\end{array}\right]\right) \\
= & \operatorname{mean}\left(\left[\begin{array}{l}
x_{12} \\
x_{21} \\
x_{31}
\end{array}\right]\right) \\
= & \frac{1}{3}\left(x_{12} + x_{21} + x_{31}\right)
\end{aligned}
$$
where 

* the $\operatorname{mean}$ function is to compute the mean of the column vector.
* $*$ is the element-wise multiplication.

The derivation is
$$
\begin{aligned} & \frac{d f}{d x_{12}}=\frac{d f}{d x_{21}}=\frac{d f}{d x_{31}}=\frac{1}{3}, \\ & \frac{d f}{d x_{i j}}=0,(i, j) \neq(1,2) \text { or }(2,1) \text { or }(3,1) \\
\end{aligned}
$$
Therefore, 
$$
\frac{d f}{d\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]}=\left[\begin{array}{cc}0 & \frac{1}{3} \\ \frac{1}{3} & 0 \\ \frac{1}{3} & 0\end{array}\right]
$$
So, for the general case, 

```python
loss = logprobs[range(n), Yb].mean()
```

where

* n= whatever value
* Yb.shape = torch.Size([n])
* logprobs.shape = torch.Size([n,c])

This result is intuitive: for those elements not selected by `Yb`, their gradient are all 0, since their changes don't affect the final loss.



## probs

```python
logprobs = probs.log()
```

We also have `probs.shape, logprobs.shape`: (torch.Size([32, 27]), torch.Size([32, 27]))

So we just need to compute the gradient element wise.

Because
$$
\begin{aligned} 
f{'}(x) = \ln x \\
\frac{d f}{d x}=\frac{1}{x}
\end{aligned}
$$
We have

```python
dprobs = (1.0 / probs) * dlogprobs
```

## counts_sum_inv

```python
probs = counts * counts_sum_inv
```

where

* `probs.shape`: torch.Size([32, 27])
* `counts.shape`: torch.Size([32, 27])
* `counts_sum_inv.shape`: torch.Size([32, 1])

The grad of `counts_sum_inv` is

```python
dcounts_sum_inv = (counts * dprobs).sum(1, keepdim=True) # counts_sum_inv.shape = [31,1], we nned to keep the shape
```



Explanation:

Suppose `counts` is a [3,2] tensor, `counts_sum_inv` is a [3,1] tensor. First, `counts_sum_inv` is broadcasted into a [3,2] tensor:


$$
\begin{aligned} 
{\left[\begin{array}{l}y_1 \\ y_2 \\ y_3\end{array}\right] \xrightarrow{\text { broadcasting }}\left[\begin{array}{ll}y_1 & y_1 \\ y_2 & y_2 \\ y_3 & y_3\end{array}\right]} \\ & 
\end{aligned}
$$
The actual calculation all happens for [3,2] tensors. The math formula represented by the code (after broadcasting) is


$$
\begin{aligned} 
& f\left(\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right],\left[\begin{array}{ll}y_1 & y_1 \\ y_2 & y_2 \\ y_3 & y_3\end{array}\right]\right) \\ 
&  =\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right] * \left[\begin{array}{ll}y_1 & y_1 \\ y_2 & y_2 \\ y_3 & y_3\end{array}\right] \\ & =\left[\begin{array}{ll}x_{11} y_1 & x_{12} y_1 \\ x_{21} y_2 & x_{22} y_2 \\ x_{31} y_3 & x_{32} y_3\end{array}\right] \\ &
\end{aligned}
$$
where

* $*$ is the element-wise multiplication



The graident of the broadcasted `counts_sum_inv` is:
$$
\begin{aligned}
& \frac{d f}{d\left[\begin{array}{ll}
y_1 & y_1 \\
y_2 & y_2 \\
y_3 & y_3
\end{array}\right]}=\left[\begin{array}{ll}
\frac{d\left(x_{11} y_1\right)}{d y_1} & \frac{d\left(x_{12} y_1\right)}{d y_1} \\
\frac{d\left(x_{21} y_2\right)}{d y_2} & \frac{d\left(x_{22} y_2\right)}{d y_2} \\
\frac{d\left(x_{31} y_3\right)}{d y_3} & \frac{d\left(x_{32} y_3\right)}{d y_3}
\end{array}\right] \\
& =
\left[\begin{array}{cc}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right]
\end{aligned}
$$
The gradient is 
$$
\left[\begin{array}{cc}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right]
\xrightarrow{\text { de-broadcasting }}
\left[\begin{array}{l}x_{11}+x_{12} \\ x_{21}+x_{22} \\ x_{31}+x_{32}\end{array}\right]
$$


where the "de-broadcasting" process is just squezzing the gradient to reshape it. Remember that when a variable is used multiple times, it's gradient should be the sum of all the seperate usage.

## counts_sum

```python
counts_sum_inv = counts_sum**-1 # if I use (1.0 / counts_sum) instead then I can't get backprop to be bit exact...
```

where

* `counts_sum.shape`: torch.Size([32, 1])
* `counts_sum_inv.shape`: torch.Size([32, 1])

So we just need to compute the gradient element wise.

Because
$$
\begin{aligned} 
f(x) =  x^{-1} \\
\frac{d f}{d x}= -1 \cdot x^{-2} .
\end{aligned}
$$


We have

```python
dcounts_sum = -1 * (counts_sum ** (-2)) * dcounts_sum_inv
```

## counts

```python
counts_sum = counts.sum(1, keepdims=True)
counts_sum_inv = counts_sum**-1 # if I use (1.0 / counts_sum) instead then I can't get backprop to be bit exact...
probs = counts * counts_sum_inv
logprobs = probs.log()
```

where:

* `counts_sum.shape`: torch.Size([32, 1])
* `counts_sum_inv.shape`: torch.Size([32, 1])
* `counts.shape`: torch.Size([32, 27])



First, we need to compute its gradient from `probs = counts * counts_sum_inv`. It's easy since we can calculate the gradient element-wise.

Then, we have to compute it's gradient from `counts.sum(1, keepdims=True)`. 

Finally, we add these two gradients together:

```python
dcounts = counts_sum_inv * dprobs # [32,1] * [32*27] (broadcasting) => [32,27] * [32*27] 
dcounts += torch.ones_like(counts) * dcounts_sum
```



Explanation of the gradient from `probs = counts.sum(1, keepdims=True)`:

Suppose `counts` is a 3\*2 matrix, 

For `counts.sum(1, keepdims=True)`, its formula is:
$$
\begin{aligned} & f\left(\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]\right) \\ & =\left[\begin{array}{l}x_{11}+x_{12} \\ x_{21}+x_{22} \\ x_{31}+x_{32}\end{array}\right]\end{aligned}
$$
We have
$$
\begin{aligned} & \frac{d f}{d\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]}=\left[\begin{array}{ll}\frac{d\left(x_1+x_{12}\right)}{d x_{11}} & \frac{d\left(x_{11}+x_{12}\right)}{d x_{12}} \\ \frac{d\left(x_{21}+x_{22}\right)}{d x_{21}} & \frac{d\left(x_{21}+x_{22}\right)}{d x_{22}} \\ \frac{d\left(x_{31}+x_{32}\right)}{d x_{31}} & \frac{d\left(x_{31}+x_{32}\right)}{d x_{32}}\end{array}\right] \\ &=\left[\begin{array}{ll}1 & 1 \\ 1 & 1\end{array}\right]\end{aligned}
$$

## norm_logits

```python
counts = norm_logits.exp()
```

where:

* `counts.shape`: torch.Size([32, 27])
* `norm_logits`: torch.Size([32, 27])

So we just need to compute the gradient element wise.

Because
$$
\begin{aligned} 
f(x) =  e^x \\
\frac{d f}{d x}= e^x .
\end{aligned}
$$
We have

```python
dnorm_logits = counts * dcounts # norm_logits: [32,27]. counts == norm_logits.exp()
```

## logit_maxes 

```python
norm_logits = logits - logit_maxes
```

where:

* `norm_logits.shape`: torch.Size([32, 27])
* `logits.shape`: torch.Size([32, 27])
* `logit_maxes.shape`: torch.Size([32, 1])



The process is the same as in [counts_sum_inv]():

1. First, broadcast `logit_maxes` to have shape [32, 27].
2. Calculate the gradient for the broadcasted `logit_maxes` (shape=[32,27]).
3. Multiply it with the upstream gradient `dnorm_logits` (shape=[32,27]).
4. Sequeeze the result along the second axis to have the same shape with the original `logit_maxes` (shape=[32,1]).



We have:

```python
dlogit_maxes = (-dnorm_logits).sum(1, keepdim=True) # dnorm_logits: [32,27]
```



## logits

```python
# cross entropy loss (same as F.cross_entropy(logits, Yb))
logit_maxes = logits.max(1, keepdim=True).values
norm_logits = logits - logit_maxes # subtract max for numerical stability
```

where:

* `norm_logits.shape`: torch.Size([32, 27])
* `logits.shape`: torch.Size([32, 27])
* `logit_maxes.shape`: torch.Size([32, 1])

First, we need to compute its gradient from `norm_logits = logits - logit_maxes`. 

1. The local gradient is easy to get since we can calculate the gradient element-wise, and the element-wise gradient is 1.
2. Then we mutiply it with the remote gradient `dnorm_logits`.



Second, we have to compute its gradient from `logit_maxes = logits.max(1, keepdim=True).values`.

Finally, we add these two gradients together: 

```python
dlogits = torch.ones_like(norm_logits) * dnorm_logits
dlogits += F.one_hot(logits.max(1).indices, num_classes=logits.shape[1]) * dlogit_maxes
```



Exlanation of the gradient from `logit_maxes = logits.max(1, keepdim=True).values`:

Suppose `logits.shape` is a [3,2] tensor, `logit_maxes` is a [3,1] tensor, and `x_11 > 2_12, x_21 < x_22, x32 < x32`. The math formula represented by the code is:
$$
\begin{aligned}
f\left(\left[\begin{array}{ll}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right]\right) & =\left[\begin{array}{l}
\max \left(x_{11}, x_{12}\right) \\
\max \left(x_{21}, x_{22}\right) \\
\max \left(x_{31}, x_{32}\right)
\end{array}\right] \\
& =\left[\begin{array}{l}
x_{11} \\
x_{22} \\
x_{32}
\end{array}\right] .
\end{aligned}
$$
To do the derivation, $f$ is broadcasted:
$$
\begin{aligned} 
{\left[\begin{array}{l}x_{11} \\ x_{22} \\ x_{32}\end{array}\right] 
\xrightarrow{\text { broadcasting }}
\left[\begin{array}{ll}x_{11} & x_{11} \\ x_{22} & x_{22} \\ x_{32} & x_{32}\end{array}\right]} \\ & 
\end{aligned}
$$


The local gradient is:
$$
\begin{aligned} 
& \frac{d f}{d\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]}
=
\left[\begin{array}{ll}
\frac{dx_{11}}{d x_{11}} & \frac{dx_{11}}{d x_{12}} \\ 
\frac{dx_{22}}{d x_{21}} & \frac{dx_{22}}{d x_{22}} \\ 
\frac{dx_{32}}{d x_{31}} & \frac{dx_{32}}{d x_{32}}
\end{array}\right] \\ 
&=

\left
[
\begin{array}{ll}
1 & 0 \\ 
0 & 1 \\ 
0 & 1
\end{array}\right
] .
\end{aligned}
$$

## h, W2, b2

```python
logits = h @ W2 + b2 # output layer
```

where:

* `logits.shape`: torch.Size([32, 27])
* `h.shape`: torch.Size([32, 64])
* `W2.shape`: torch.Size([64, 27])
* `b2.shape`: torch.Size([27])



For `h`, we can transpose `W2 ` and multiply with the upstream gradient `dlogits`:

```python
dh = dlogits @ W2.T # [32, 27] * [27,64] ==> [32,64]
```



```python
dW2 = h.T @ dlogits # [64, 32] * [32,27] ==> [64,27]
db2 = dlogits.sum(0, keepdim=False) # [32,27] 
```

## hpreact

```python
h = torch.tanh(hpreact) # hidden layer
```

where:

* `h.shape`: torch.Size([32, 64])
* `hpreact.shape`: torch.Size([32, 64])

Since `h` and `hpreact` have the same shape, we can just calculate the element-wise gradient.

Note that
$$
\begin{aligned} 
& \frac{d}{d x} \tanh (x)=\frac{\left(e^x+e^{-x}\right)\left(e^x+e^{-x}\right)-\left(e^x-e^{-x}\right)\left(e^x-e^{-x}\right)}{\left(e^x+e^{-x}\right)^2} \\ & =1-\frac{\left(e^x-e^{-x}\right)^2}{\left(e^x+e^{-x}\right)^2}=1-\tanh ^2(x)
\end{aligned}
$$


So:

```python
dhpreact = (1 - h**2) * dh
```

## bngain, bnbias, bnraw

```
hpreact = bngain * bnraw + bnbias
```

where:

* `hpreact.shape`: torch.Size([32, 64])
* `bngain.shape`: torch.Size([1, 64])
* `bnraw.shape`: torch.Size([32, 64])
* `bnbias.shape`: torch.Size([1, 64]))



```python
# bnraw and is dhpreact have the same shape [32,64]
dbngain = (dhpreact * bnraw).sum(0, keepdim=True)

# Since bnbias has shape [27,1], we should use `keepdim=True` to keep the shape.
dbnbias = dhpreact.sum(0, keepdim=True) 

# bngain (shape=[1, 64]) is broadcasted to have shape [32,64], then multiply with dhpreact(shape=[32,64])
dbnraw = bngain * dhpreact 
```



## bnvar_inv

```python
bnraw = bndiff * bnvar_inv
```

where:

* `bndiff.shape`: torch.Size([32, 64])
* `bnvar_inv.shape`: torch.Size([1, 64])
* `bnraw.shape`: torch.Size([32, 64])



The process is the same as in [counts_sum_inv]()

1. First, broadcast `bnvar_inv` to have shape [32, 64].
2. Calculate the gradient for the broadcasted `bnvar_inv` (shape=[32, 64]).
3. Multiply it with the upstream gradient `dbnraw` (shape=[32, 64]).
4. Sequeeze the result along the first axis to the same shape with the original `bnvar_inv` (shape=[1,64]).

## bnvar

```python
bnvar_inv = (bnvar + 1e-5)**-0.5
```

where:

* `bnvar_inv.shape`: torch.Size([1, 64])
* `bnvar.shape`: torch.Size([1, 64])

We calculate the gradient element-wise. Due to:

1. Power Rule: $f(x)=x^n$ then $f^{\prime}(x)=n x^{n-1}$, 
2. Chain Rule: $h(x)=f(g(x))$ then $h^{\prime}(x)=f^{\prime}(g(x)) g^{\prime}(x)$

We have:

```python
dbnvar = -0.5 * ((bnvar + 1e-5) ** -1.5) * dbnvar_inv
```



## bndiff2

```python
bnvar = 1/(n-1)*(bndiff2).sum(0, keepdim=True)
```

where:

* `bndiff2.shape`: torch.Size([32, 64])
* `bnvar.shape`: torch.Size([1, 64])



The process is the same as in [logits](), where the result of the function should be broadcasted in order to calculate the gradient.



Suppose `bndiff2` is a [3,2] tensor, `bnvar` is a [3,1] tensor. The math formula represented by the code is
$$
f\left(\left[\begin{array}{ll}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right]\right)=\left[\frac{1}{2}\left(x_{11}+x_{21}+x_{31}\right) \quad \frac{1}{2}\left(x_{12}+x_{22}+x_{32}\right)\right] .
$$
To do the derivation, $f$ is <u>broadcasted</u>:
$$
\begin{aligned} & {\left[\frac{1}{2}\left(x_{11}+x_{21}+x_{31}\right) \frac{1}{2}\left(x_{12}+x_{22}+x_{32}\right)\right] \xrightarrow{\text { broodcasting }}} \\ & {\left[\begin{array}{ll}\frac{1}{2}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{2}\left(x_{12}+x_{22}+x_{32}\right) \\ \frac{1}{2}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{2}\left(x_{12}+x_{22}+x_{32}\right) \\ \frac{1}{2}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{2}\left(x_{12}+x_{22}+x_{32}\right)\end{array}\right]} \\ & \end{aligned}
$$
The local gradient is:
$$
\begin{aligned} 
& \frac{d f}{d\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]}
=
\left[\begin{array}{ll}
\frac{1}{2} & \frac{1}{2} \\ 
\frac{1}{2} & \frac{1}{2} \\ 
\frac{1}{2} & \frac{1}{2}
\end{array}\right] .
\end{aligned}
$$


We have:

```python
dbndiff2 = torch.ones_like(bndiff2) * (1/(n-1)) * dbnvar
```

## bndiff

```python
bndiff2 = bndiff**2
# ...
bnraw = bndiff * bnvar_inv
```

where:

* `bndiff2.shape`: torch.Size([32, 64])
* `bndiff.shape`: torch.Size([32, 64])
* `bnvar_inv.shape`: torch.Size([1, 64])
* `bnraw.shape`: torch.Size([32, 64])

First, consider `bnraw = bndiff * bnvar_inv`, the process is the similar to [counts_sum_inv](). `bnvar_inv` has shape [1, 64], so it's broadcasted to have shape [32, 64].



Suppose `bndiff` is a [3,2] tensor, `bnvar_inv` is a [3,1] tensor. First, `bnvar_inv` is broadcasted into a [3,2] tensor:


$$
\begin{aligned} 
{\left[\begin{array}{l}y_1 \\ y_2 \\ y_3\end{array}\right] \xrightarrow{\text { broadcasting }}\left[\begin{array}{ll}y_1 & y_1 \\ y_2 & y_2 \\ y_3 & y_3\end{array}\right]} \\ & 
\end{aligned}
$$
The actual calculation all happens for [3,2] tensors. Since the process is similar, the details are omitted.



Second, consider `bndiff2 = bndiff**2`. The calculation of gradient is quite easy since `bndiff` and `bndiff2` have the same shape, we just need to do element-wise gradient calculation.

We have

```python
dbndiff = bnvar_inv * dbnraw
dbndiff += 2 * bndiff * dbndiff2
```

## bnmeani

```python
bndiff = hprebn - bnmeani
```

where:

* `bndiff.shape`: torch.Size([32, 64])
* `hprebn.shape`: torch.Size([32, 64])
* `bnmeani.shape`: torch.Size([1, 64])



The process is the same as in [counts_sum_inv]():

1. First, broadcast `bnmeani` to have shape [32, 64].
2. Calculate the gradient for the broadcasted `bnmeani` (shape=[32,64]).
3. Multiply it with the upstream gradient `dbndiff` (shape=[32,64]).
4. Sequeeze the result along the first axis to have the same shape with the original `bnmeani` (shape=[1,64]).

We have:

```python
dbnmeani = -dbndiff.sum(0, keepdim=True)
```

## hprebn

```python
bnmeani = 1/n*hprebn.sum(0, keepdim=True)
bndiff = hprebn - bnmeani
```

where:

* `bndiff.shape`: torch.Size([32, 64])
* `hprebn.shape`: torch.Size([32, 64])
* `bnmeani.shape`: torch.Size([1, 64])



First, consider `bndiff = hprebn - bnmeani`, it's element-wise gradient calculation.

Second, consider `bnmeani = 1/n*hprebn.sum(0, keepdim=True)`, the process is the same as in [logits](), where the result of the function should be broadcasted in order to calculate the gradient.

Suppose `hprebn` is a [3,2] tensor, `bnmeani` is a [3,1] tensor. The math formula represented by the code is
$$
f\left(\left[\begin{array}{ll}
x_{11} & x_{12} \\
x_{21} & x_{22} \\
x_{31} & x_{32}
\end{array}\right]\right)=\left[\frac{1}{3}\left(x_{11}+x_{21}+x_{31}\right) \quad \frac{1}{3}\left(x_{12}+x_{22}+x_{32}\right)\right] .
$$
To do the derivation, $f$ is <u>broadcasted</u>:
$$
\begin{aligned} 
& {\left[\frac{1}{3}\left(x_{11}+x_{21}+x_{31}\right) \frac{1}{3}\left(x_{12}+x_{22}+x_{32}\right)\right] \xrightarrow{\text { broodcasting }}} 
\\ 
& 
{\left[\begin{array}{ll}\frac{1}{3}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{3}\left(x_{12}+x_{22}+x_{32}\right) 
\\ 
\frac{1}{3}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{3}\left(x_{12}+x_{22}+x_{32}\right) 
\\ 
\frac{1}{3}\left(x_{11}+x_{21}+x_{31}\right) & \frac{1}{3}\left(x_{12}+x_{22}+x_{32}\right)\end{array}\right]} .
\end{aligned}
$$
The local gradient is:
$$
\begin{aligned} 
& \frac{d f}{d\left[\begin{array}{ll}x_{11} & x_{12} \\ x_{21} & x_{22} \\ x_{31} & x_{32}\end{array}\right]}
=
\left[\begin{array}{ll}
\frac{1}{3} & \frac{1}{3} \\ 
\frac{1}{3} & \frac{1}{3} \\ 
\frac{1}{3} & \frac{1}{3}
\end{array}\right] .
\end{aligned}
$$
We have:

```python
dhprebn = 1.0 * dbndiff.clone()
dhprebn += 1/n * dbnmeani
```

## embcat, W1, b1

```python
hprebn = embcat @ W1 + b1
```

where:

* `hprebn.shape`: torch.Size([32, 64])
* `embcat.shape`: torch.Size([32, 30])
* `W1.shape`: torch.Size([30, 64])
* `b1.shape`: torch.Size([64])



The process is the same as in [h, W2, b2](). We have

```python
dembcat = dhprebn @ W1.T
dW1 = embcat.T @ dhprebn
db1 = dhprebn.sum(0, keepdim=False)
```

## emb

```python
embcat = emb.view(emb.shape[0], -1) # concatenate the vectors
```

where:

* `embcat.shape`: torch.Size([32, 30])
* `emb.shape`: torch.Size([32, 3, 10])

Since `embcat = emb.view(emb.shape[0], -1)` doesn't change any value, the local gradient should be all 1. I can't write the math formula. **# TODO**

We have:

```python
demb = dembcat.view(emb.shape)
```

## C

```python
emb = C[Xb] # embed the characters into vectors
```

where:

* `emb.shape`: torch.Size([32, 3, 10])
* `C.shape`: torch.Size([27, 10])
* `Xb.shape`: torch.Size([32, 3])

I can't understand this ... **# TODO**

We have:

```python
dC = torch.zeros_like(C) # Can't understand
for k in range(Xb.shape[0]):
  for j in range(Xb.shape[1]):
    ix = Xb[k,j]
    dC[ix] += demb[k,j]
```

## Put everything together

```python
dloss = 1
dlogprobs = torch.zeros_like(logprobs)
dlogprobs[range(n), Yb] = - 1.0 / n # f(x) = ln x, df / dx = 1/x
dprobs = (1.0 / probs) * dlogprobs
dcounts_sum_inv = (counts * dprobs).sum(1, keepdim=True) # counts_sum_inv.shape = [31,1], we nned to keep the shape
dcounts_sum = -1 * (counts_sum ** (-2)) * dcounts_sum_inv
dcounts = counts_sum_inv * dprobs # [32,1] * [32*27] (broadcasting) => [32,27] * [32*27] 
dcounts += torch.ones_like(counts) * dcounts_sum
dnorm_logits = counts * dcounts # norm_logits: [32,27]. counts == norm_logits.exp()
dlogit_maxes = ((-1  * torch.ones_like(logit_maxes) ) * dnorm_logits ).sum(1, keepdim=True) # dnorm_logits: [32,27]
dlogits = torch.ones_like(norm_logits) * dnorm_logits
dlogits += F.one_hot(logits.max(1).indices, num_classes=logits.shape[1]) * dlogit_maxes # logits.max(1).indices extracts the tensor of indices of the maximum logit values along dimension 1 (across the 27 classes for each example).
dh = dlogits @ W2.T # [32, 27] * [27,64] ==> [32,64]
dW2 = h.T @ dlogits # [64, 32] * [32,27] ==> [64,27]
db2 = dlogits.sum(0, keepdim=False) # [32,27]. Since b2 has shape [27], we need to use `keepdim=False` to squeeze [27,1] to be [27]
dhpreact = (1 - h**2) * dh # d tanh(x) / d x = 1 - tanh(x)**2. Every tensor here has shape [32,64].
dbngain = (dhpreact * bnraw).sum(0, keepdim=True)
dbnbias = dhpreact.sum(0, keepdim=True) # Since bnbias has shape [27,1], we should use `keepdim=True` to keep the shape.
dbnraw = bngain * dhpreact # bngain (shape=[1, 64]) is broadcasted to have shape [32,64], then multiply with dhpreact(shape=[32,64])
dbnvar_inv = (bndiff * dbnraw).sum(0, keepdim=True)
dbnvar = -0.5 * ((bnvar + 1e-5) ** -1.5) * dbnvar_inv
dbndiff2 = torch.ones_like(bndiff2) * (1/(n-1)) * dbnvar
dbndiff = bnvar_inv * dbnraw
dbndiff += 2 * bndiff * dbndiff2
dbnmeani = -dbndiff.sum(0, keepdim=True)
dhprebn = 1.0 * dbndiff.clone()
dhprebn += 1/n * dbnmeani
dembcat = dhprebn @ W1.T
dW1 = embcat.T @ dhprebn
db1 = dhprebn.sum(0, keepdim=False)
demb = dembcat.view(emb.shape)
dC = torch.zeros_like(C) # Can't understand
for k in range(Xb.shape[0]):
  for j in range(Xb.shape[1]):
    ix = Xb[k,j]
    dC[ix] += demb[k,j]
```



# Exercise 2

Now we backprop through cross entropy in one time.

Recalling that the code of cross entropy is

```python
# cross entropy loss (same as F.cross_entropy(logits, Yb))

# First, we normalize the logits
logit_maxes = logits.max(1, keepdim=True).values
norm_logits = logits - logit_maxes # subtract max for numerical stability

# Then, we apply Softmax to the logits to get probabilities
counts = norm_logits.exp()
counts_sum = counts.sum(1, keepdims=True)
counts_sum_inv = counts_sum**-1 # if I use (1.0 / counts_sum) instead then I can't get backprop to be bit exact...
probs = counts * counts_sum_inv

# Last, we calculate the cross entropy loss for the probs.
# Note that after we get the cross entropy loss for each sample, we compute their mean since the final loss should be a scalar.
logprobs = probs.log()
loss = -logprobs[range(n), Yb].mean()
```

We now compute it in one line:

```python
loss_fast = F.cross_entropy(logits, Yb)
```

Meanwhile, we do backprop all in one time to get the gradient of `logits`. For logit $z_i$, its gradient is
$$
\frac{\partial L}{\partial z_i}= \begin{cases}\operatorname{softmax}\left(z_i\right)-1, & i=t \\ \operatorname{softmax}\left(z_i\right), & i \neq t\end{cases}
$$
The mathmatical explanation is [->here](https://lyk-love.cn/2024/03/09/cross-entropy-loss/)

We have:

```python
# For each sample, its `logits` is a 27-D vector for 27 classes.
# Suppose the index of the truth class of a sample is `t`. The index of one logit in the logits of a sample  is `i`, the logit is `z_i`, the gradient of logit z_i :
# 1. if i != t, softmax(z_i).
# 2. if i == t, softmax(z_i) - 1.

#  Apply softmax to each of thr 27 classes, i.e., along the axis = 1, to get the 27 `logit`s of this sample.
dlogits = F.softmax(logits, 1) 
dlogits[range(n), Yb] -= 1 # For the truth class t, it's  softmax(z_i) - 1.
dlogits /= n
```

# Exercise 3

Now we backprop through batch normalization in one time.

Recalling that the code of batch normalization is

```python
# BatchNorm layer
bnmeani = 1/n*hprebn.sum(0, keepdim=True)
bndiff = hprebn - bnmeani
bndiff2 = bndiff**2
bnvar = 1/(n-1)*(bndiff2).sum(0, keepdim=True) # note: Bessel's correction (dividing by n-1, not n)
bnvar_inv = (bnvar + 1e-5)**-0.5
bnraw = bndiff * bnvar_inv
hpreact = bngain * bnraw + bnbias
```

We now compute it in one line:

```python
hpreact_fast = bngain * (hprebn - hprebn.mean(0, keepdim=True)) / torch.sqrt(hprebn.var(0, keepdim=True, unbiased=True) + 1e-5) + bnbias
```



Meanwhile, we do backprop all in one time to get the gradient of `hprebn`. For input sample $x_i$, its gradient is
$$
\begin{aligned}
\frac{\partial L}{\partial x_i} 

& = \cdots \\
& =\frac{\gamma\left(\sigma^2+\varepsilon\right)^{-\frac{1}{2}}}{N}\left(N  \frac{\partial L}{\partial y_i}-\sum_{j=1}^N \frac{\partial L}{\partial y_j}-\frac{N}{N-1} \hat{x}_i \sum_{j=1}^N \frac{\partial L}{\partial y_j} \hat{x}_j\right ).
\end{aligned}
$$
The mathmatical explanation is [->here](https://lyk-love.cn/2024/03/09/batch-normalization/)

We have:

```python
dhprebn = bngain*bnvar_inv/n * (n*dhpreact - dhpreact.sum(0) - n/(n-1)*bnraw*(dhpreact*bnraw).sum(0))
```

