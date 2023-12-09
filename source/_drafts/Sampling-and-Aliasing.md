---
title: Sampling and Aliasing
tags: Digital Signal Processing
categoeirs: Electronic Engineering
mathjax: true
---

# Intro

This chapter is concerned with the conversion of signals between the analog (continuous-time) domain and the digital (discrete-time) domain, aka AD and DC.

The primary objective of our presentation is an understanding of the **sampling theorem** , which states that when the sampling rate is greater than twice the highest frequency contained in the spectrum of the analog signal, the original signal can be reconstructed exactly from the samples. 

As we noted in [Chapter 2](), a signal whose spectrum has a finite highest frequency is called a *bandlimited signal*, and, theoretically, such a signal can be sampled and reconstructed without error.



The process of converting from digital back to analog is called reconstruction . 

# Sampling

![image-20231204233002812](/Users/lyk/Library/Application Support/typora-user-images/image-20231204233002812.png)

* **analog** signals: aka *continuous-time* signals, both the signal amplitude and the time variable are assumed to be **real numbers** (not discrete values).

  * We denote the values of the continuous-time signal as $x(t)$, where t is a real number, and we assume that any value of x (t ) is also a real number.

* **digital** signams: aka *discrete-time* signals. It's represented mathematically by an indexed sequence of numbers.

  * When stored digitally, the signal values are held in memory locations, so they would be indexed by memory addresses.
  * We denote the values of the discrete-time signal as $x[n]$, where $n$ is the integer index indicating the order of the values in the sequence.

* A continuous time signal can be periodically sampled at time instants $t_n = nT_s$,
  $$
  x[n] = x(nT_s)
  $$
  where $T_s$ is the **sampling period**, and
  $$
  f = \frac 1 T_s \text{samples per second}
  $$
  is the **sampling frequency**.

  The individual values of $x[n]$ are called **samples** of the continuous-time signal.



## Sampling Sinusoidal Signals

If the continuous signal is a sinusoidal signal, e.g., of the form $A \cos (\omega t+\varphi)$, we can obtain
$$
\begin{aligned}
x[n] & =x\left(n T_s\right) \\
& =A \cos \left(\omega n T_s+\varphi\right) \\
& =A \cos (\hat{\omega} n+\varphi)
\end{aligned}
$$
where we have defined $\hat{\omega}$ to be **Normalized Radian Frequency**:
$$
\hat{\omega} \stackrel{\text { def }}{=} \omega T_s=\frac{\omega}{f_s}
$$

* Notes on units of frequency measures:

  * Digital frequency, $\hat \omega$ (somtimes denoted as $w_d$) has units of **radians** which are **dimensionless**.

    * Digital frequency in radians is measured $-\pi < \omega_d < \pi$ or $0 < \omega_d < 2\pi$.
    * One can define a normalized digital frequency, $\omega_d = 2 \pi f_d$, or $f_d = \frac {\omega_d} {2 \pi}$ and the corresponding range is $-\frac 1 2 < f_d < \frac 1 2$ or $0 < f_d < 1$.

  * Continuous frequency, $\omega$(sometimes dentoed as $w_c$), has units of **radians/second**.

    • To convert from radians to "linear" units, $\omega_c = 2 \pi f_c$, or $f_c = \frac {\omega_c} {2 \pi}$.

    • Regular frequency, e.g. $f_s$, has units of **Hertz** or **1/(second)**.

* To convert between “digital frequency” and continuous frequency, we need to know the sample rate or sampling period.
  $$
  
  $$
  





## The Concept of Aliases

The phenomenon of two different signals giving the same samples is called **aliasing**, which can happen if sampling frequency is not fast enough



Consider $x[n] = \cos( 0.4 \pi n)$, the same same signal values can be achieved by:

1. $x[n] = \cos( 2\pi n + 0.4 \pi n)$
2. $x[n] = \cos( 2\pi n - 0.4 \pi n)$
3. ...

Thus, we can write the following general formulas for all aliases of a sinusoid with frequency $\hat{\omega}_0$ :
$$
\hat{\omega}_0, \hat{\omega}_0+2 \pi \ell, 2 \pi \ell-\hat{\omega}_0 \quad(\ell=\text { integer })
$$
because the following signals have exactly the same values for all $n$ :
$$
\begin{aligned}
A \cos \left(\hat{\omega}_0 n+\varphi\right) & =A \cos \left(\left(\hat{\omega}_0+2 \pi \ell\right) n+\varphi\right) \\
& =A \cos \left(\left(2 \pi \ell-\hat{\omega}_0\right) n-\varphi\right)
\end{aligned}
$$

If we were to make a stem plot of all of these signals (with specific numbers for $A, \hat{\omega}, \varphi$, and $\ell$ ), we would **not be able to tell them apart**.

* The **principal alias** is defined to be the unique alias frequency in the interval $−π < \hat \omega ≤ π$ . In this case, the principal alias is $0.4π$.
* The aliases of a <u>negative</u> frequency are called <u>folded</u> aliases . In the folded case, the principal alias is $−0.4π$.
* Other aliases.





## Sampling and Aliasing

If we hope to reconstruct the original analog signal, it is necessary that the normalized frequency $\hat{\omega}_0$ be the principal alias, that is,
$$
\begin{equation} \label{eq_2.2.1}
-\pi< {\omega}_d=\omega_c T_s<\pi .
\end{equation}
$$

When $\eqref{eq_2.2.1}$ is not satisfied, we say that "aliasing has occurred ." Henceforth, when we use the term **aliasing**, we mean that when a signal is sampled, the resulting samples are identical to those obtained by sampling a lower frequency signal (corresponding to the principal alias). 



Since the original identity of the signal is ambiguous when aliasing occurs in sampling, it is not straightforward to reconstruct the original analog signal from its samples. 

Thus, it is generally desirable to avoid aliasing when designing a system that samples continuous-time signals.

## Spectrum of a Discrete-Time Signal

We have seen that it is sometimes very useful to represent a continuous-time sinusoidal signal by a spectrum plot consisting of spectrum lines. We should expect to see something similar in a spectrum plot for a discrete-time signal. 

The spectrum of a continuous-time sinusoid exhibits two spectrum lines at the frequencies $\pm \omega_c$ rad/s. 

The alias phenomenon changes the spectrum plot <u>because a given discrete-time sinusoidal sequence could correspond to an infinite number of different frequencies ${\omega}_d$.</u> 

Our approach is to take this into account by making a spectrum plot that **explicitly shows that there are many different discrete-time sinusoids that have the same samples**. 

Figure $4-5$ shows that we can do this by drawing the spectrum representation of the principal alias along with several more of the other aliases.



Spectrum with Aliases for $x[n] = \cos( 0.4 \pi n)$:

![Fig. 4-5](/Users/lyk/Library/Application Support/typora-user-images/image-20231204234422170.png)

The spectrum plot includes:

* a representation of the principal alias $x1 [n] = cos(0.4π n)$, and 
* two of the aliases $x_2 [n] = \cos(2.4π n)$ and $x_3 [n] = \cos(1.6π n)$. 
* Like the two-sided representation in (3.4) on p. 50, the spectrum of each discrete-time alias signal consists of a **positive** frequency component and a corresponding component at **negative** frequency.



## The Sampling Theorem

**Shannon Sampling Theorem**: A continuous-time signal $x(t)$ with frequencies no higher than $f_{\max }$ can be reconstructed exactly from its samples $x[n]=x\left(n T_s\right)$, if the samples are taken at a rate $f_s=1 / T_s$ that is greater than $2 f_{\max }$.

The minimum sampling rate of $2 f_{\max }$ is called the **Nyquist rate**.

> We can see examples of Nyquist rate sampling in many commercial products. For example, audio CDs use a sampling rate of $44.1 \mathrm{kHz}$ for storing music signals in a digital format. This number is slightly more than two times $20 \mathrm{kHz}$, which is the generally accepted upper limit for human hearing and perception of musical sounds. In all applications, the Nyquist rate is significant because we are usually motivated to use the lowest possible sampling rate in order to minimize system cost in terms of storage and processing speed per sample.

The Shannon theorem states that reconstruction of a sinusoid is possible if we have more than two samples per period. What happens when we don't sample fast enough? The simple answer is that aliasing occurs and reconstruction becomes difficult or impossible.



## Ideal Reconstruction



# Spectrum View of Sampling and Reconstruction
