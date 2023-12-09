---
title: Discrete Fourier Transform
tags: Digital Signal Processing
categoeirs: Electronic Engineering
mathjax: true
---

# Intro

This chapter builds on the definition and discussion of the DTFT in [Chapter 7](). The objective here is to define a *numerical Fourier transform* called the discrete Fourier transform (or DFT) that results from taking *frequency samples of the DTFT.* We show how the DFT can be used to compute a spectrum representation of any finite-length sampled signal very efficiently with the fast Fourier transform (FFT) algorithm. 

# Discrete Fourier Transform (DFT)

The DTFT of a discrete-time signal $x[n]$ can be viewed as a generalization of the spectrum concept introduced in Chapters 3 and 4, where discrete lines in the frequency domain represented sums of complex exponentials in the time domain. 

**DFT is a frequency-sampled version of the DTFT for a finite-length signal.** 

Two steps are needed to change the DTFT sum (7.2) into a computable form: 

1. the continuous frequency variable $\hat{\omega}$ must be **sampled**, 
   * even though $\hat{\omega}$ is a continuous variable, it does have a finite range $-\pi \leq \hat{\omega}<\pi$ so we can evaluate (7.2) at a finite set of frequencies, denoted by $\hat{\omega}_k$.
2. and the limits on the DTFT sum must be **finite**.
   * the DTFT sum has a finite number of terms when the signal duration is finite. We cannot compute the transform of an infinite-duration signal, but it is common to operate on finite sections of a very long signal.

## DTFT sampled at frequencies $\hat{\omega}_k$

For a finite-duration signal, the DTFT sampled at frequencies $\hat{\omega}_k$ is
$$
\begin{align}
X\left(e^{j \hat{\omega}_k}\right)
& =\sum_{n=0}^{L-1} x[n] e^{-j \hat{\omega}_k n} \label{eq_DTFT_sampled}\\
k & = 0,1, \ldots N-1 \nonumber
\end{align}
$$
where $L$ is the length of $x[n]$.

* The interval of frequency samples $\left\{\hat{\omega}_k\right\}$ can be any interval of length $2 \pi$. But usually we choose
  $$
  0 \leq \hat{\omega}_k<2 \pi
  $$
  and to evaluate $\eqref{eq_DTFT_sampled}$ at the $N$ equally spaced frequencies
  $$
  \begin{align}
  \hat{\omega}_k &= \frac{2 \pi k}{N} \label{eq_interval} \\
  k &= 0,1, \ldots, N-1 \nonumber.
  \end{align}
  $$

* Then we substitute $\eqref{eq_interval}$ into $\eqref{eq_DTFT_sampled}$, we obtain
  $$
  \begin{align}
  X\left(e^{j \frac{2 \pi k}{N}}\right) &= \sum_{n=0}^{L-1} x[n] e^{-j(2 \pi k / N) n} \label{eq_DTFT_sampled_2} \\
  k &= 0,1, \ldots, N-1 \nonumber.
  \end{align}
  $$
  Equation $\eqref{eq_DTFT_sampled_2}$ is a "finite Fourier sum" which is computable. 

The sum in  $\eqref{eq_DTFT_sampled_2}$ must be computed for $N$ different values of the discrete frequency index $k$. The index $n$ in the sum on the right is the counting index of the sum, and thus it <u>disappears</u> when the sum is computed. 

Since the left-hand side of  $\eqref{eq_DTFT_sampled_2}$  depends only on the frequency index $k$, we now define
$$
X[k]=X\left(e^{j \frac{2 \pi k}{N}}\right) .
$$

## $N$-point DFT of the finite $L$-length signal

The $N$-point[^3] **Discrete Fourier Transform (DFT)** of the finite $L$-length signal $𝑥[n]$ is defined as
$$
\begin{align}
X[k] & = \sum_{n=0}^{L-1} x[n] e^{-j(2 \pi / N) k n} \label{eq_DFT}\\
 k & =0,1, \ldots, N-1 \nonumber .
\end{align}
$$

* $N$: the number of frequency samples.
* $L$: signal length.
* **The DFT is discrete in both time/sample and frequency domain.**
* **The DTFT is discrete in only time domain.**

Typically, the values of $X[k]$ are complex, while the values of $x[n]$ are often real, but $x[n]$ in (8.4) could be complex.

***

## DFT for $N=L$

When $N=L$, $\eqref{eq_DFT}$ becomes
$$
\begin{align}
X[k] & = \sum_{n=0}^{N-1} x[n] e^{-j(2 \pi / N) k n} \label{eq_DFT_N_L}\\
 k & =0,1, \ldots, N-1 \nonumber .
\end{align}
$$

In practice, we usually use $\eqref{eq_DFT_N_L}$, instead of $\eqref{eq_DTFT_sampled_2}$, to compute DFT. 

But $\eqref{eq_DFT_N_L}$ assumes $N=L$, what if $N > L$? In this case we use [zero-padding]() to append zero-valued samples to the signal to make it longer to compute $\eqref{eq_DFT_N_L}$.

## Zero-Padding

**Sometimes, the sequence length of $x[n]$ is shorter than $N$ (i.e., $L<N$ ),** and $x[n]$ is nonzero only in the interval $0 \leq n \leq L-1$. In Example 8-1, $L=2$ and $N=4$.

In this case, we use  **zero-padding**:
$$
h_{\mathrm{zp}}[n]= \begin{cases}h[n] & n=0,1, \ldots, L-1 \\ 0 & n=L, L+1, \ldots, N-1\end{cases} .
$$


Now take the $N$-point DFT of $h_{\mathrm{zp}}[n]$ and then split the sum into two smaller summations:
$$
\begin{aligned}
H_{\mathrm{zp}}[k] & =\sum_{n=0}^{N-1} h_{\mathrm{zp}}[n] e^{-j(2 \pi / N) k n} \\
& =\sum_{n=0}^{L-1} h_{\mathrm{zp}}[n] e^{-j(2 \pi / N) k n}+\sum_{n=L}^{N-1} h_{\mathrm{zp}}[n] e^{-j(2 \pi / N) k n} \\
& =\sum_{n=0}^{L-1} h[n] e^{-j(2 \pi / N) k n} \\
H_{\mathrm{zp}}[k] & =H\left(e^{j(2 \pi / N) k}\right) \quad \text { for } k=0,1,2, \ldots, N-1
\end{aligned}
$$

* The second term in the second line is $0$ since $h_{\mathrm{zp}}[n] = 0$ for $n \ge L$.



Zero-padding is so common that most numerical DFT functions, or FFT functions, take a second argument e.g. `fft(x, N)`.

### EXAMPLE 8-1 Short-Length DFT

Given a sequence $x[n]=\{1,1\}$. We want to carry out a $4$-point DFT.

We can see that the sequence length of $x[n]$ is shorter than $N$ (i.e., $L<N$ ), and $x[n]$ is nonzero only in the interval $0 \leq n \leq L-1$. In this example, $L=2$ and $N=4$.

Thus we use zero-padding to addpend  $N-L$ zero samples to the nonzero samples of $x[n]$. 

Now we have

$x[n] = \{1,1,0,0\}$.



Now we conduct DFT using $\eqref{eq_DFT_N_L}$
$$
\begin{aligned}
X[0] & =x[0] e^{-j 0}+x[1] e^{-j 0}+x[2] e^{-j 0}+x[3] e^{-j 0} \\
& =1+1+0+0=2 \\
X[1] & =1 e^{-j 0}+1 e^{-j \pi / 2}+0 e^{-j \pi}+0 e^{-j 3 \pi / 2} \\
& =1+(-j)+0+0=1-j=\sqrt{2} e^{-j \pi / 4} \\
X[2] & =1 e^{-j 0}+1 e^{-j \pi}+0 e^{-j 2 \pi}+0 e^{-j 3 \pi} \\
& =1+(-1)+0+0=0 \\
X[3] & =1 e^{-j 0}+1 e^{-j 3 \pi / 2}+0 e^{-j 3 \pi}+0 e^{-j 9 \pi / 2} \\
& =1+(j)+0+0=1+j=\sqrt{2} e^{j \pi / 4}
\end{aligned}
$$

Thus, we obtain the four DFT coefficients[^2] $X[k]=\left\{2, \sqrt{2} e^{-j \pi / 4}, 0, \sqrt{2} e^{j \pi / 4}\right\}$.

## The Inverse DFT

There exists an inverse function of DFT, called **Inverse Discrete Fourier Transform** or **IDFT**.
$$
\begin{aligned}
\text{DFT}: x[n] \rightarrow X[k]. \\
\text{Inverse DFT} : X[k] \rightarrow x[n].
\end{aligned}
$$


IDFT converts $X[k]$ for $k=0,1, \ldots, N-1$ back into the sequence $x[n]$ for $n=0,1, \ldots, N-1$.

IDFT:
$$
\begin{align}
x[n] &=\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k n} \label{eq_IDFT}\\
n &=0,1, \ldots, N-1 \nonumber
\end{align}
$$

### Proof

Now we proof IDFT is the inverse function of DFT. 

Let $v[n]$ be a sequence produced by $\eqref{eq_IDFT}$,  $n=0,1, \ldots, N-1$. Then
$$
\begin{aligned}
v[n] & =\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi k / N) n} \\
& =\frac{1}{N} \sum_{k=0}^{N-1} \underbrace{\left(\sum_{m=0}^{N-1} x[m] e^{-j(2 \pi k / N) m}\right)}_{\text {Forward DFT, } X[k]} e^{j(2 \pi k / N) n} \\
& =\frac{1}{N} \sum_{m=0}^{N-1} x[m] \underbrace{\left(\sum_{k=0}^{N-1} e^{j(2 \pi k / N)(n-m)}\right)}_{=0, \text { except for } m=n} \\
& =x[n]
\end{aligned}
$$
The 2nd equation equation is because we apply the $\eqref{eq_DFT_N_L}$ and mark the index as $m$.

The 3rd equation equation is from the *Orthogonality Property of Periodic Discrete-Time Complex Exponentials*:

> Orthogonality Property of Periodic Discrete-Time Complex Exponentials
>
> Use the formula
> $$
> \sum_{k=0}^{N-1} \alpha^k=\frac{1-\alpha^N}{1-\alpha}
> $$
> to show that
> $$
> \begin{aligned}
> d[n-m] & =\frac{1}{N} \sum_{k=0}^{N-1} e^{j(2 \pi / N) n k} e^{j(2 \pi / N)(-m) k} \quad \text { (definition) } \\
> & =\frac{1}{N} \sum_{k=0}^{N-1} e^{j(2 \pi / N)(n-m) k} \quad \text { (alternate form) } \\
> & =\frac{1}{N}\left(\frac{1-e^{j(2 \pi)(n-m)}}{1-e^{j(2 \pi / N)(n-m)}}\right) \quad \text { (use (8.7)) } \\
> d[n-m] & = \begin{cases}1 & n-m=r N \\
> 0 & \text { otherwise }\end{cases}
> \end{aligned}
> $$
> where $r$ is any positive or negative integer including $r=0$.



Now we replace the 3ed line with $d[n-m]$:
$$
\begin{aligned}
v[n] =  \sum_{m=0}^{N-1} x[m] d[n-m]
\end{aligned}
$$
We know that $d[n-m] = 0$ when $n-m \ne rN$. And $n,m \in \{0,1,\cdots, N-1\}$, so the only non-zero value of $d[n-m]$ is $1$ when $n=m$.
$$
v[n] =  \sum_{m=0}^{N-1} x[m] =  0 +\cdots + x[m=n] + 0  = x[n].
$$
Q.E.D.



## DFT of Shifted Impulse

## Computing the DFT

## Matrix Form of the DFT and IDFT

# Properties of the DFT

- Some are inherited from the DFTF (and therefore z-transform)
- There are some properties that are unique to the DFT due to the finite-length signal assumption



## Periodicity

One surprising finding is that the DFT/IDFT "**behaves**" as if the signal is **periodic** and not finite
$$
X[k]=X[k+N],-\infty<k<\infty
$$
and
$$
x[n]=x[k+N],-\infty<k<\infty
$$
In other words, the DFT of $x[n]=\left\{\begin{array}{cc}0, & k<0 \\ x[k], & 0 \leq k<N \\ 0, & N \leq k<\infty\end{array}\right\}$ is is the same as DFT of $x[n]=x[k+N],-\infty<k<\infty$

### Proof: **DFT Periodicity for** $X[k]$

We have shown that the DFT of a finite $N$-point sequence <u>is a sampled version of the DTFT of that sequence</u>, that is,
$$
\begin{aligned}
X[k]=\sum_{n=0}^{N-1} x[n] e^{-j(2 \pi / N) k n} & =\left.X\left(e^{j \hat{\omega}}\right)\right|_{\hat{\omega}=(2 \pi k / N)} \\
& =X\left(e^{j(2 \pi k / N)}\right) \quad k=0,1, \ldots, N-1
\end{aligned}
$$

Since the DTFT $X\left(e^{j \hat{\omega}}\right)$ is always **periodic with a period of $2 \pi$**, the DFT $X[k]$ must also be periodic.

The definition of the DFT implies that the index $k$ always remains between 0 and $N-1$, but there is nothing that prevents the DFT summation $\eqref{eq_DFT_N_L}$ from being evaluated for $k \geq N$, or $k<0$. The frequency sampling relationship $\hat{\omega}_k=2 \pi k / N$ is still true for all integers $k$, so $\hat{\omega}_k+2 \pi=2 \pi k / N+2 \pi(N / N)=2 \pi(k+N) / N=\hat{\omega}_{k+N}$. In other words, the DFT coefficients $X[k]$ have a period equal to $N$, because
$$
X[k]=\underbrace{X\left(e^{j 2 \pi(k) / N}\right)=X\left(e^{j(2 \pi(k) / N+2 \pi)}\right)}_{\text {DTFT period is } 2 \pi}=X\left(e^{j 2 \pi(k+N) / N}\right)=X[k+N]
$$

### Proof: **IDFT Periodicity for** $X[k]$

It is less obvious that the IDFT summation implies periodicity. However, we can ask what happens when the IDFT sum $\eqref{eq_IDFT}$ is evaluated for $n<0$ or $n \geq N$. In particular, consider evaluating (8.5) at $n+N$ where $n$ is in the interval $0 \leq n \leq N-1$, that is,
$$
\tilde{x}[n+N]=\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k(n+N)}
$$

We have denoted the result in $\eqref{eq_IDFT}$ as $\tilde{x}[n+N]$ because we are testing to see what value is computed at $n+N$.
$$
\begin{aligned}
\tilde{x}[(n+N)] & =\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k(n+N)} \\
& =\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k(n)} e^{j(2 \pi / N) k(N)}  \\
& =\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k(n)}=x[n]
\end{aligned}
$$

In the 2nd line observe that $e^{j(2 \pi / N) k N}=e^{j 2 \pi k}=1$ for all $k$.

It can be shown that $\tilde{x}[n+r N]=x[n]$ when we evaluate at any point $n+r N$ where $r$ is an integer. In other words, the result from the IDFT sum is periodic in $n$ with period $N$ if (8.5) is evaluated outside the base interval $0 \leq n \leq N-1$. We can express this succinctly as follows:
$$
\frac{1}{N} \sum_{k=0}^{N-1} X[k] e^{j(2 \pi / N) k n}=\tilde{x}[n]=\sum_{r=-\infty}^{\infty} x[n+r N] \quad \text { for }-\infty<n<\infty
$$
where $x[n]$ is the original sequence whose DTFT was sampled as in (8.16). The infinite sum on the right-hand side, which involves shifted copies of the same signal, is illustrated in Fig. 8-7. 

![Fig. 8-7](/Users/lyk/Library/Application Support/typora-user-images/image-20231205162203900.png)

> Illustration of the infinite sum. 
>
> (a) A finite-length sequence x[n] of length 10. 
>
> (b) Shifted copies of x[n] that are summed to make up the inherent periodic sequence $x ̃[n]$ with period N = 10. The inherent periodic sequence $x ̃[n]$ continues with period N outside the range −10 ≤ n < 30.

This periodicity implies that the sequence $x[n]$ can be reconstructed exactly from $N$ samples of its DTFT $X\left(e^{j \hat{\omega}}\right)$ if it is a finite length- $N$ sequence. This could be termed the *Sampling Theorem for the DTFT*.

## I**nherent Time-Domain Periodicity of** **x** **[****n****] in the DFT

### The Time Delay Property for the DFT

As we showed in Chapter 7, the DTFT delay property is
$$
y[n]=x\left[n-n_d\right] \stackrel{\mathrm{DTFT}}{\longleftrightarrow} e^{-j \hat{\omega} n_d} X\left(e^{j \hat{\omega}}\right)
$$
when $y[n]=x\left[n-n_d\right]$ is a time-shifted version of $x[n]$. If we use frequency sampling, then we expect the DFT delay property would be
$$
Y[k]=\left.e^{-j \hat{\omega} n_d} X\left(e^{j \hat{\omega}}\right)\right|_{\hat{\omega}=(2 \pi k / N)}=e^{-j(2 \pi k / N) n_d} X[k]
$$

However, when the IDFT is applied to $X[k]$ and $Y[k]$ it is the inherent periodic signal $\tilde{x}[n]$ that is shifted by $n_d$ to give the inherent periodic signal $\tilde{y}[n]$. If we take the point of view that we only compute sequence values in the interval $0 \leq n \leq N-1$, then we are led to an unexpected result. We can see that might be an issue by noting that if $x[n]$ is nonzero over the entire interval $0 \leq n \leq N-1$, then there would not be room in that interval for $x\left[n-n_d\right]$. This is similar to the behavior already seen in Example 8-5 for a time-shifted impulse. For example, if $n_d=4$, then $x[n-4]$ is nonzero for $4 \leq n \leq$ $N+3$. This is illustrated in Fig. $8-8$ for the case $N=10$. Figure 8-8(a) shows an original 10 -point sequence $x[n]$. If we represent this sequence by its 10-point DFT $X[k]$, then we

![Fig. 8-8](/Users/lyk/Library/Application Support/typora-user-images/image-20231205162655470.png)

> Illustration of the time-shift property of the DFT. 
>
> (a) A finite-length sequence x[n] of length 10.
>
> (b) The inherent periodic sequence x ̃[n] for a 10-point DFT representation. (c) Time-shifted periodic sequence y ̃[n] = x ̃[n − 4] which is also equal to the IDFT of
>  Y[k] = e−j(2πk/10)(4)X[k]. (d) The sequence y[n] obtained by evaluating the 10-point IDFT of Y [k] only in the interval 0 ≤ n ≤ 9.

### For zero-Padding

![Fig. 8-9](/Users/lyk/Library/Application Support/typora-user-images/image-20231205162912366.png)

> Figure 8-9 Illustration of the time-shift property of the DFT with zero padding. (a) A finite-length sequence $x[n]$ of length 10 padded with 4 zeros. (b) The inherent periodic sequence $\tilde{x}[n]$ for a 14 -point DFT representation. (c) Time-shifted periodic sequence $\tilde{y}[n]=\tilde{x}[n-4]$ corresponding to $Y[k]=e^{-j(2 \pi k / 14)(4)} X[k]$. (d) The sequence $y[n]$ obtained by evaluating the 14-point IDFT of $Y[k]$ only in the interval $0 \leq n \leq 13$.

## The Convolution Property for the DFT

![image-20231205163113952](/Users/lyk/Library/Application Support/typora-user-images/image-20231205163113952.png)

- The periodicity of the DFT/IDFT also affects the convolution property
$$
y[n]=\sum_{m=0}^{M-1} h[m] x[n-m]
$$
- Recall that for $M$-length $h[m]$ and $L$-length $x[m]$, then $y[n]$ is length $(L+M-1)$
- We still have $Y[k]=H[k] X[k]$, but in the time/sample domain, we have
$$
\text { "circular convolution" } \tilde{y}[n]=\sum_{m=0}^{M-1} \tilde{h}[m] \tilde{x}[n-m]
$$
where $\tilde{h}[m]$ and $\tilde{x}[m]$ are the periodic extensions of the original signals
- We can obtain the regular convolution result by using $N$-point DFTs of $h[m]$ and $\boldsymbol{x}[\boldsymbol{m}]$, where $N>=L+M-1$
- If $h[\mathrm{~m}]$ and $x[\mathrm{~m}]$ are the same length $L$, then choosing $N=2 L$ is typical



![Fig. 8-10](/Users/lyk/Library/Application Support/typora-user-images/image-20231205163023159.png)

> Figure 8-10 Illustration of convolving two rectangular pulses with length-16 DFTs. (a) The inherent periodic signal $\tilde{h}[n]$ corresponding to the 16-point DFT $H[k]$ of a length-6 pulse. (b) The inherent periodic signal $\tilde{x}[n]$ corresponding to the 16-point DFT $X[k]$ of a length-10 pulse. (c) The inherent periodic signal $\tilde{y}[n]$ corresponding to $Y[k]=H[k] X[k] ; \tilde{y}[n]$ is also equal to the circular convolution defined in (8.31). (d) The 16 -point sequence $y[n]$ obtained by evaluating the 16-point IDFT of $Y[k]$ only in the interval $0 \leq n \leq 15$.

# The Fast Fourier Transform (FFT)





[^2]: The term "coefficient" is commonly applied to DFT values. This is appropriate because $X[k]$​ is the (complex amplitude) coefficient of $e^{j(2 \pi / N) k n}$​ in the IDFT (8.5).
[^3]: The terminology " $N$​-point DFT" means that the sequence $x[n]$​ is known for $N$​ time indices, and the DFT is computed at $N$​ frequencies in (8.2).

