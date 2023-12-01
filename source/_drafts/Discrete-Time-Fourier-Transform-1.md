---
title: Discrete Time Fourier Transform
tags: Digital Signal Processing
categoeirs: Electronic Engineering
mathjax: true
---

# DTFT

The concept of frequency response discussed in Chapter 6 emerged from analysis showing that if an input to an LTI discrete-time system is of the form $x[n]=e^{j \hat{\omega} n}$, then the corresponding output has the form $y[n]=H\left(e^{j \hat{\omega}}\right) e^{j \hat{\omega} n}$, where $H\left(e^{j \hat{\omega}}\right)$ is called the frequency response of the LTI system. This fact, coupled with the principle of superposition for LTI systems leads to the fundamental result that the frequency response function $H\left(e^{j \hat{\omega}}\right)$ is sufficient to determine the output due to any linear combination of signals of the form $e^{j \hat{\omega} n}$ or $\cos (\hat{\omega} n+\theta)$. 

For discrete-time filters such as the causal FIR filters discussed in [Chapter 6](), the frequency response function is obtained from the summation formula
$$
H\left(e^{j \hat{\omega}}\right)=\sum_{n=0}^M h[n] e^{-j \hat{\omega} n}=h[0]+h[1] e^{-j \hat{\omega}}+\cdots+h[M] e^{-j \hat{\omega} M}
$$
where $h[n]$ is the impulse response. 

In a mathematical sense, the impulse response $h[n]$ is **transformed** into the **frequency response** by the operation of <u>evaluating (7.1) for each value of $\hat{\omega}$</u> over the domain $-\pi<\hat{\omega} \leq \pi$. 

The operation of transformation (adding up the terms in (7.1) for each value $\hat{\omega}$ ) <u>replaces a function of a discrete-time index $n$ (a sequence) by a periodic function of the continuous frequency variable $\hat{\omega}$.</u> **And the time-domain representation $h[n]$ is replaced by the frequency-domain representation $H\left(e^{j \hat{\omega}}\right)$.**[^1] 

For this concept to be complete and useful, we need to know that the result of the transformation is unique, and we need the ability to go back from the frequency-domain representation to the time-domain representation. That is, we need an inverse transform that recovers the original $h[n]$ from $H\left(e^{j \hat{\omega}}\right)$.

## Forward DTFT

$$
\begin{equation} \label{eq_forward_DTFT}
X\left(e^{j \hat{\omega}}\right)=\sum_{n=-\infty}^{+\infty} x[n] e^{-j \hat{\omega} n}
\end{equation}
$$

Thus $X\left(e^{j \hat{\omega}}\right)$ is a function of frequency $\hat \omega$. 

The limits on the sum in $\eqref{eq_forward_DTFT}$ are shown as infinite so that the DTFT is defined for infinitely long signals as well as finite-length signals.[^2]

However, If $h[n]$ is the impulse response of an LTI system, note $h[n]$ my be finite length, then the DTFT of $h[n]$ is the frequency response  $H\left(e^{j \hat{\omega}}\right)$ of that system.



## DTFT of a Shifted Impulse Sequence



In Chapter 6, we showed that the sequence can be reconstructed from a frequency response represented in terms of powers of $e^{-j \hat{\omega}}$ as in (7.1) by simply picking off the coefficients of the polynomial since $h[n]$ is the coefficient of $e^{-j \hat{\omega} n}$. While this process can be effective if $M$ is small, there is a much more powerful approach to inverting the transformation that holds even for infinite-length sequences.

## Linearity of the DTFT

## Uniqueness of the DTFT

## DTFT of a Pulse

## DTFT of a Right-Sided Exponential Sequence

## Existence of the DTFT

## The Inverse DTFT

## Bandlimited DTFT

## Inverse DTFT for the Right-Sided Exponential

## The DTFT Spectrum

# Properties of the DTFT

## Linear Property

## Time-Delay Property

## Frequency-Shift Property

## Convolution and the DTFT

## Energy Spectrum and the Autocorrelation Function



[^1]: It is common in engineering to say that we "take the discrete-time Fourier transform" when we mean that we consider $X\left(e^{j \hat{\omega}}\right)$ as our representation of a signal $x[n]$.
[^2]: The infinite limits are used to imply that the sum is over all n, where x[n] ̸= 0. This often avoids unnecessarily awkward expressions when using the DTFT for analysis.

