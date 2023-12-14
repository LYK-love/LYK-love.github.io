---
title: z-Transforms
date: 2023-12-11 23:14:59
tags:
---




FIR convolution is equivalent to polynomial multiplication. 

In fact, common algebraic operations, such as multiplying, dividing, and factoring polynomials, can be interpreted as combining or decomposing LTI systems.

# $z$-Transfrom

A finite-length signal $x[n]$ consists of a set of signal values $\{x[0], x[1], \ldots, x[L-1]\}$ that can be represented by the relation
$$
x[n]=\sum_{k=0}^{L-1} x[k] \delta[n-k]
$$

Each term in the summation, $x[k] \delta[n-k]$, is the value $x[k]$ at the time index $n=k$ which is the only index where $\delta[n-k]$ is nonzero. The $z$-transform of the signal $x[n]$ in (9.1) is defined by the formula
$$
\begin{equation} \label{eq_z_transform}
X(z)=\sum_{k=0}^{L-1} x[k] (z^{-1})^k
\end{equation}
$$
where $z$, the **independent variable** of the $z$-transform $X(z)$, is a **complex number**. 

* $X(z)$ is simply a polynomial of degree $L-1$ in the variable $z^1$.

## $z$-Transform Pair

A $z$-transform pair is a sequence and its corresponding $z$-transform, which we denote as
$$
x[n] \stackrel{z}{\longleftrightarrow} X(z)
$$

We can emphasize the unique correspondence between a sequence $x[n]$ and its $z$-transform by writing
$$
\begin{array}{ccc}
n \text {-Domain } & \stackrel{z}{\longleftrightarrow} & z \text {-Domain } \\
x[n]=\sum_{k=0}^{L-1} x[k] \delta[n-k] & \stackrel{z}{\longleftrightarrow} & X(z)=\sum_{k=0}^{L-1} x[k] z^{-k}
\end{array}
$$

## For shifted impulse

Suppose that the signal is a shifted impulse (i.e., $x[n]=\delta\left[n-n_0\right]$ ). Then, applying the definition $\eqref{eq_z_transform}$, it follows that $X(z)=z^{-n_0}$, so we can write
$$
\begin{array}{|ccc|}
\hline n \text {-Domain } & \stackrel{z}{\longleftrightarrow} & z \text {-Domain } \\
x[n]=\delta\left[n-n_0\right] & \stackrel{z}{\longleftrightarrow} & X(z)=z^{-n_0} \\
\hline
\end{array}
$$

When the sequence is defined with a list of numerical values, we take the $z$-transform and get a general polynomial, as illustrated by the following example.

# Basic $z$-Transform Properties
In Section 9-1, we defined the $z$-transform, and showed for finite-length sequences that it is simple to go back and forth between the sequence $x[n]$ and its $z$-transform $X(z)$. In this section, we explore two universal transform properties that hold for the $z$-transform, and also show that when the $z$-transform is extended to the infinite-length case, these properties still hold.
## Linearity Property of the $z$-Transform

The $z$-transform is a linear transformation because it satisfies the superposition property. To show this, we use superposition (addition and scaling) to form a new sequence $x[n]=$ $a x_1[n]+b x_2[n]$ as the linear combination of $x_1[n]$ and $x_2[n]$, which are both assumed to have finite length less than or equal to $L$. Then we take the $z$-transform of the linear combination:
$$
\begin{aligned}
X(z) & =\sum_{n=0}^{L-1}\left(a x_1[n]+b x_2[n]\right) z^{-n} \\
& =a \sum_{n=0}^{L-1} x_1[n] z^{-n}+b \sum_{n=0}^{L-1} x_2[n] z^{-n} \\
& =a X_1(z)+b X_2(z)
\end{aligned}
$$

These steps are true because multiplication distributes over addition for real and complex numbers. Thus, the $z$-transform $X(z)$ has the same linear combination (addition and scaling) as used in the time domain.
## Time-Delay Property of the $z$-Transform

The second important property of the $z$-transform is that multiplication by the quantity $z^{-1}$ in the $z$-domain corresponds to a time shift by one index in the $n$-domain. First, we illustrate this property with a numerical example. Consider the length-6 signal $x[n]$ defined by the following table of values:

![image-20231211224842026](/Users/lyk/Library/Application Support/typora-user-images/image-20231211224842026.png)



The $z$-transform of $x[n]$ is the following fifth-degree polynomial (in $z^{-1}$ )
$$
X(z)=3+z^{-1}+4 z^{-2}+z^{-3}+5 z^{-4}+9 z^{-5}
$$

Recall that the signal values $x[n]$ are the coefficients of the polynomial $X(z)$ and that the exponents correspond to the time locations of the values. For example, the term $4 z^{-2}$ indicates that the signal value at $n=2$ is 4 (i.e., $x[2]=4$ ).
Now consider the effect of multiplying the polynomial $X(z)$ by $z^{-1}$ :
$$
\begin{aligned}
Y(z) & =z^{-1} X(z) \\
& =z^{-1}\left(3+z^{-1}+4 z^{-2}+z^{-3}+5 z^{-4}+9 z^{-5}\right) \\
& =0 z^0+3 z^{-1}+z^{-2}+4 z^{-3}+z^{-4}+5 z^{-5}+9 z^{-6}
\end{aligned}
$$

The resulting polynomial $Y(z)$ is the $z$-transform representation of a new signal $y[n]$, which is found by using the polynomial coefficients and exponents in $Y(z)$ to take the inverse $z$-transform and obtain the values of $y[n]$ at all time positions. Notice that there is now a term $4 z^{-3}$ which indicates that the signal value at $n=3$ is $y[3]=4$. The result is the following table of values for $y[n]$ :
![image-20231211224920522](/Users/lyk/Library/Application Support/typora-user-images/image-20231211224920522.png)

The general result is



Delay of $n_0$ samples:
$$
x\left[n-n_0\right] \quad \stackrel{z}{\longleftrightarrow} z^{-n_0} X(z)
$$
