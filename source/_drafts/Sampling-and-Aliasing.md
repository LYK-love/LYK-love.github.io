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

  * We denote the values of the continuous-time signal as $x(t)$, where $t$ is a real number, and we assume that any value of $x(t)$ is also a real number.
    $$
    \begin{aligned}
    x(t) 
    &= A \cos (\omega_c t+\varphi) \\
    &= A \cos (2 \pi f_c t+\varphi)
    \end{aligned}
    $$
    

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
& =A \cos \left(\omega_c n T_s+\varphi\right) \\
& =A \cos ({\omega}_d n+\varphi)
\end{aligned}
$$
where we have defined ${\omega}_d$ to be **Normalized Radian Frequency**:
$$
{\omega}_d \stackrel{\text { def }}{=} \omega_c T_s=\frac{\omega_c}{f_s}
$$

* Notes on units of frequency measures:

  * **Digital frequency**, Normalized Radian Frequency, $\omega_d$ (somtimes denoted as $w_d$) has units of **radians** which are **dimensionless**.
  * Digital frequency in radians is measured $-\pi < \omega_d < \pi$ or $0 < \omega_d < 2\pi$.
    * One can define a normalized digital frequency, $\omega_d = 2 \pi f_d$, or $f_d = \frac {\omega_d} {2 \pi}$ and the corresponding range is $-\frac 1 2 < f_d < \frac 1 2$ or $0 < f_d < 1$.
  * **Continuous frequency**, $\omega$(sometimes dentoed as $w_c$), has units of **radians/second**.
* To convert from radians to "linear" units, $\omega_c = 2 \pi f_c$, or $f_c = \frac {\omega_c} {2 \pi}$.
  * **Regular frequency**, e.g. $f_s$, has units of **Hertz** or **1/(second)**.

* To convert between “digital frequency” and continuous frequency, we need to know the sample rate or sampling period.
  $$
  w_d = w_c T_s = \frac {w_c}{f_s}
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

Suppose that we start with a continuous-time sinusoid, $x(t)=A \cos \left(\omega_0 t+\varphi\right)$, whose spectrum consists of $t w o$ spectrum lines at $\pm \omega_0$ with complex amplitudes of $\frac{1}{2} A e^{ \pm j \varphi}$. 

The spectrum of the sampled discrete-time signal
$$
\begin{aligned}
x[n] & =x\left(n / f_s\right)=A \cos \left(\left(\omega_0 / f_s\right) n+\varphi\right) \\
& =\frac{1}{2} A e^{j \varphi} e^{j\left(\omega_0 / f_s\right) n}+\frac{1}{2} A e^{-j \varphi} e^{j\left(-\omega_0 / f_s\right) n}
\end{aligned}
$$
also has two spectrum lines at $\hat{\omega}= \pm \omega_0 / f_s$, but it also must contain all the aliases at the following discrete-time frequencies:
$$
\begin{array}{ll}
\hat{\omega}=\omega_0 / f_s+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots \\
\hat{\omega}=-\omega_0 / f_s+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots
\end{array}
$$

This illustrates the important fact that when a discrete-time sinusoid is derived by sampling, the alias frequencies all are based on the normalized value, $\omega_0 / f_s$, of the frequency of the continuous-time signal. 

The alias frequencies are obtained by adding integer multiples of $2 \pi$ radians to the frequency $\hat{\omega}=\omega_0 / f_s$.

## Example

The next sections show examples of sampling a continuous-time $100 \mathrm{~Hz}$ sinusoid of the form $x(t)=\cos (2 \pi(100) t+\pi / 3)$. The sampling frequency is varied to show the discrete-time spectrum for different cases, where $f_s$ is above or below the Nyquist rate in Figs. 4-8 through 4-11.

![image-20231209000650276](/Users/lyk/Library/Application Support/typora-user-images/image-20231209000650276.png)

> Over-sampling a $100 \mathrm{~Hz}$ sinusoid at $f_s=500$ samples/s. (a) Continuous-time spectrum; (b) time-domain plot, showing the samples $x[n]$ as gray dots, the original signal $x(t)$ as a continuous orange line, and the reconstructed signal $y(t)$ as a dashed black line, which is the $100 \mathrm{~Hz}$ sinusoid passing through the same sample points; and (c) discrete-time spectrum plot, showing the positive and negative frequency components of the original sinusoid at $\hat{\omega}= \pm 0.4 \pi \mathrm{rad}$, along with two aliases.

## Over-Sampling

In most applications, we try to obey the constraint of the sampling theorem by sampling at a rate higher than twice the highest frequency in order to avoid the problems of aliasing. This is called **over-sampling**. 

For example, when we sample the $100 \mathrm{~Hz}$ sinusoid, $x(t)=\cos (2 \pi(100) t+\pi / 3)$, at a sampling rate of $f_s=500 \mathrm{samples} / \mathrm{s}$, we are sampling at two and a half times the Nyquist rate. The time- and frequencydomain plots are shown in Fig. 4-8. With reference to the C-to-D and D-to-C blocks in Fig. 4-7, Fig. 4-8(a) shows the spectrum of the input signal $x(t)$, while Fig. 4-8(c) shows the spectrum of $x[n]=\cos (0.4 \pi n+\pi / 3)$, which is the output of the C-to-D converter. The time-domain plots of $x(t), x[n]$, and the reconstructed output $y(t)$ are all in Fig. 4-8(b).

For the continuous-time spectrum in Fig. 4-8(a), the frequency axis is measured in hertz. Note that the negative-frequency complex exponential component of the cosine is denoted with a $*$ at the top of its spectrum line to indicate that its complex value is the conjugate of the value of the positive frequency component. Figure 4-8(b) shows $x(t)$, $x[n]$, and $y(t)$ together, but its horizontal axis is labeled with time $(t)$ in milliseconds, so

input analog frequency of $100 \mathrm{~Hz}$ maps to $\hat{\omega}=2 \pi(100) / f_s=2 \pi(100) / 500=0.4 \pi$, so in Fig. 4-8(c) we plot spectrum lines at $\hat{\omega}= \pm 0.4 \pi$. Then we also draw all the aliases at
$$
\begin{array}{ll}
\hat{\omega}=0.4 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots \\
\hat{\omega}=-0.4 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots
\end{array}
$$

The D-to-C converter transforms the discrete-time spectrum to the continuous-time output spectrum. But there is one complication: the D-to-C converter must select just one pair of spectrum lines from all the possibilities given by (4.13). The selection rule is arbitrary, but in order to be consistent with real D-to-A converter operation, we must assert that the ideal D-to-C converter always selects the lowest possible frequency for each set of aliases. These are what we have called the principal alias frequencies, and in Fig. 4-8(c) these are the frequency components that fall inside the dashed box, that is, in the range $|\hat{\omega}|<\pi$. Since the frequency components inside the dashed box satisfy $|\hat{\omega}|<\pi$, the spectral lines for the output always lie between $-f_s /$ an $+f_s /$. When the principal alias frequencies in Fig. 4-8(c) are converted from $\hat{\omega}$ to analog frequency, the result is $f= \pm 0.4 \pi\left(f_s / 2 \pi\right)= \pm 100 \mathrm{~Hz}$ which is identical to Fig. 4-8(a).

In summary, for the over-sampling case where the original frequency $f_0$ is less than $f_s / 2$, the original waveform is reconstructed exactly. In the present example, $f_0=100 \mathrm{~Hz}$ and $f_s=500$, so the Nyquist condition of the sampling theorem is satisfied, and the output $y(t)$ equals the input $x(t)$ as shown in Fig. 4-8(b).
## Aliasing Due to Under-Sampling

![image-20231209000832841](/Users/lyk/Library/Application Support/typora-user-images/image-20231209000832841.png)

> Under-sampling a $100 \mathrm{~Hz}$ sinusoid at $f_s=80$ samples/s. (a) Continuous-time spectrum; (b) time-domain plot, showing the samples $x[n]$ as gray dots, the original signal $x(t)$ as a continuous orange line, and the reconstructed signal $y(t)$ as a dashed black line, which is a $20 \mathrm{~Hz}$ sinusoid passing through the same sample points; and (c) discrete-time spectrum plot, showing the positive and negative frequency components of the original sinusoid at $\hat{\omega}= \pm 2.5 \pi \mathrm{rad}$, along with two sets of alias components.

When $f_s<2 f_0$, the signal is under-sampled and we say that aliasing has occurred. For example, if $f_s=80 \mathrm{~Hz}$ and $f_0=100 \mathrm{~Hz}$, the sampling rate is below the Nyquist rate and we can show that aliasing confusion occurs. In Fig. 4-9(a), the spectrum of the analog input signal $x(t)$ is shown, along with an arrow indicating the sampling rate at $f_s=80 \mathrm{~Hz}$. The spectrum of the discrete-time signal (Fig. 4-9(c)) contains lines at $\hat{\omega}= \pm 2 \pi(100) / f_s= \pm 2 \pi(100) / 80= \pm 2.5 \pi$, as predicted by the frequency scaling equation (4.3). In order to complete the discrete-time spectrum we must also draw all the aliases at
$$
\begin{array}{ll}
\hat{\omega}=2.5 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots \\
\hat{\omega}=-2.5 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots
\end{array}
$$

In Fig. 4-9(b), the $100 \mathrm{~Hz}$ sinusoid (solid orange line) is sampled too infrequently to be recognized as the original $100 \mathrm{~Hz}$ sinusoid. When we examine the D-to-C process for this case, we use the lowest frequency spectrum lines from the discrete-time spectrum (Fig. 4-9(c)). These are the principal aliases at $\hat{\omega}= \pm 0.5 \pi$, so the output spectrum lines are at $f= \pm 0.5 \pi\left(f_s / 2 \pi\right)= \pm 80 / 4= \pm 20 \mathrm{~Hz}$. Alternatively, we can state this result in the time domain by observing that the same samples would have been obtained from a $20 \mathrm{~Hz}$ sinusoid. The reconstructed signal is that $20 \mathrm{~Hz}$ sinusoid shown as the black dashed line in Fig. 4-9(b). Notice that the alias frequency of $20 \mathrm{~Hz}$ can be found by subtracting $f_s$ from $100 \mathrm{~Hz}$.

The aliasing of sinusoidal components can have some dramatic effects. Figure 4-10 shows the case where the sampling rate and the frequency of the sinusoid are the same. In Fig. 4-10(b), we see that one sample is taken per period, and all the samples are the same value. In other words, $x[n]$ is DC, which is the same as a sinusoid with zero frequency. We can justify this result in the frequency domain (Fig. 4-10(c)) by noting that the discrete-time spectrum contains lines at $\hat{\omega}= \pm 2 \pi\left(100 / f_s\right)= \pm 2 \pi$, and also at the aliases separated by $2 \pi \ell$. Thus, two of the aliases land at $\hat{\omega}=0$, and the sum of these two is the value that is reconstructed by the D-to-C converter.
##  Folding Due to Under-Sampling

![image-20231209001319085](/Users/lyk/Library/Application Support/typora-user-images/image-20231209001319085.png)

> Under-sampling a $100 \mathrm{~Hz}$ sinusoid at $f_s=100$ samples/s. (a) Continuous-time spectrum; (b) time-domain plot, showing the samples $x[n]$ as gray dots, the original signal $x(t)$ as a continuous orange line, and the reconstructed signal $y(t)$ as a dashed black line, which is a $0 \mathrm{~Hz}$ sinusoid passing through the same sample points; and (c) discrete-time spectrum plot, showing the positive and negative frequency components of the original sinusoid at $\hat{\omega}= \pm 2 \pi \mathrm{rad}$, along with parts of two sets of alias components that are superimposed at $\hat{\omega}=0$ to give a $\mathrm{DC}$ value of $\frac{1}{2} e^{j \pi / 3}+\frac{1}{2} e^{-j \pi / 3}=\cos (\pi / 3)$.

Figure 4-11 shows the case where under-sampling leads to the type of aliasing called folding. Here the sampling rate is $f_s=125$ samples/s, which is between $f_0$ and $2 f_0$. Once again, Fig. 4-11(a) shows the spectrum of the continuous-time signal with spectrum lines at $\pm 100 \mathrm{~Hz}$. The discrete-time spectrum (Fig. 4-11(c)) is constructed by mapping $\pm 100 \mathrm{~Hz}$ to the two spectrum lines at $\hat{\omega}= \pm 2 \pi\left(100 / f_s\right)= \pm 1.6 \pi$, and then including all the aliases to get lines at
$$
\begin{array}{ll}
\hat{\omega}=1.6 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots \\
\hat{\omega}=-1.6 \pi+2 \pi \ell & \ell=0, \pm 1, \pm 2, \ldots
\end{array}
$$

In this case, an interesting thing happens. The two frequency components between $\pm \pi$ are $\hat{\omega}= \pm 0.4 \pi$, but the one at $\hat{\omega}=+0.4 \pi$ is an alias of the negative frequency component at $-1.6 \pi$, which is why this situation is called folding. The analog frequency of the reconstructed output is $f=0.4 \pi\left(f_s / 2 \pi\right)=f_s / 5=25 \mathrm{~Hz}$. An additional fact about folding is that phase of the reconstructed analog signal changes sign. 

If the original $100 \mathrm{~Hz}$ sinusoid had a phase of $\varphi=+\pi / 3$, then the phase of the component at $\hat{\omega}=-1.6 \pi$ would be $-\pi / 3$, and it follows that the phase of the aliased component at $\hat{\omega}=+0.4 \pi$ would also be $-\pi / 3$. After reconstruction, the phase of $y(t)$ would be $-\pi / 3$. It is possible to observe this "phase-reversal" in the time-domain plot of Fig. 4-11(b). 

The input signal (solid orange line) is going down at $t=0$, while the reconstructed output (black dashed line) is going up. 

This means that when we sample a $100 \mathrm{~Hz}$ sinusoid at a sampling rate of 125 samples/s, we get the same samples that we would have gotten by sampling a $25 \mathrm{~Hz}$ sinusoid, but with opposite phase. 

This is depicted in Fig. 4-11 by showing that the complex amplitude of the positive frequency component at $0.4 \pi$ is due to the negative frequency alias $(-1.6 \pi+2 \pi)$.

# Discrete-to-Continuous Conversion

The purpose of the ideal D-to-C converter is to interpolate a smooth continuous-time function through the given discrete-time samples $y[n]$. Thus, in the special case when $y[n]=A \cos \left(2 \pi f_0 n T_s+\varphi\right)$, and if $f_0<f_s / 2$, then according to the sampling theorem, the ideal converter should produce
$$
y(t)=A \cos \left(2 \pi f_0 t+\varphi\right)
$$

For sampled sinusoidal signals only, the ideal D-to-C converter in effect replaces $n$ by $f_s t$ in the cosine formula. On the other hand, if $f_0>f_s / 2$, then we know that aliasing or folding confusion has occurred, and the ideal D-to-C converter reconstructs a cosine wave with frequency equal to the principal alias frequency which is less than $f_s / 2$.


## Interpolation with Pulses

![image-20231209001505541](/Users/lyk/Library/Application Support/typora-user-images/image-20231209001505541.png)

> Ie 414 Four different pulses for D-to-C conversion. The sampling period is $T_s=5 \mathrm{~ms}$, or equivalently, $f_s=200 \mathrm{~Hz}$. The duration of the pulses is (a) $T_s$ for the square pulse, (b) $2 T_s$ for the triangular pulse, (c) $4 T_s$ for the cubic spline, and (d) infinite for the ideal pulse.

How does an actual D-to-C converter work? In this section, we explain how the D-toC converter does interpolation through the given discrete-time samples $y[n]$, and then describe a practical system that is nearly the same as the ideal D-to-C converter. These actual hardware systems, called D-to-A converters, approximate the behavior of the ideal D-to-C system as in (4.14).
A general formula that describes a broad class of D-to-C converters is given by the equation
$$
\begin{equation} \label{eq_interpolation}
y(t)=\sum_{n=-\infty}^{\infty} y[n] p\left(t-n T_s\right)
\end{equation}
$$
where $p(t)$ is the characteristic pulse shape of the converter. Equation (4.15) states that the output signal is produced by superimposing scaled and time-shifted pulses. In other words, at each sample time $t_n=n T_s$, a shifted pulse $p\left(t-n T_s\right)$ is emitted with an amplitude



Equation (4.15) requires that we choose the pulse waveform p(t). Unfortunately, we have not yet studied the mathematical tools needed to derive the optimal pulse shape for exact reconstruction of a waveform y (t ) from its samples y [n] = y (nTs ) as is predicted to be possible in the Shannon sampling theorem. This optimal pulse shape can be constructed during a mathematical proof of the sampling theorem. Nonetheless, we will demonstrate the plausibility of (4.15) by considering some simple examples that use suboptimal pulse shapes. Figure 4-14 shows four possible pulse waveforms for D-to-C conversion when fs = 200 Hz.

## Ideal Bandlimited Interpolation

So far in this section, we have demonstrated the basic principles of discrete-to-continuous conversion. We have shown that this process can be approximated very well by a sum of shifted pulses (4.15). One question remains: What is the pulse shape that gives "ideal D-to-C conversion"? The answer, which relies on the continuous-time Fourier Transform, is a sinc function which is given by the following equation:
$$
\begin{equation} \label{eq_sinc}
p(t)=\operatorname{sinc}\left(t / T_s\right)=\frac{\sin \left(\pi t / T_s\right)}{\left(\pi t / T_s\right)} \quad \text { for }-\infty<t<\infty
\end{equation}
$$

The infinite length of this sinc pulse implies that to reconstruct a signal at time $t$ exactly from its samples requires all the samples, not just those near time $t$. Figure 4-14(d) shows this pulse over the interval $-2.6 T_s<t<2.6 T_s$. It continues to decay outside this interval, but never does reach and stay at zero. Since $p(0)=1$ and $p\left(n T_s\right)=0$ for $n= \pm 1, \pm 2, \ldots$, this type of reconstruction is still an interpolation process, and it is called **bandlimited interpolation**, because it can be shown that using $\eqref{eq_sinc}$ in the interpolation formula $\eqref{eq_interpolation}$ is equivalent to selecting the principal alias components inside the gray boxes in Figs. 4-8 through 4-11. Using (4.18) to reconstruct from samples of a cosine wave always reproduces a cosine wave exactly. If the sampling rate satisfies the conditions of the sampling theorem, the reconstructed cosine wave is identical to the original signal that was sampled. If aliasing occurred in sampling, the ideal D-to-C converter reconstructs a cosine wave with the alias frequency that is less than $f_s / 2$.

# The Sampling Theorem

Shannon Sampling Theorem
A bandlimited continuous-time signal $x(t)$ with no spectral components at frequencies above $f_{\max }$ can be reconstructed exactly from its samples $x\left(n T_s\right)$, if the samples are taken at a rate $f_s=1 / T_s$ that is greater than $2 f_{\max }$.

![image-20231208235910026](/Users/lyk/Library/Application Support/typora-user-images/image-20231208235910026.png)

A block diagram representation of the sampling theorem is shown in Fig. 4-21 in terms of the ideal C-to-D and D-to-C converters that we have defined in this chapter. The sampling theorem states that if the input is composed of sinusoidal signals with frequencies $\left\{f_k\right\}$ and all those frequencies are in the range $0 \leq f_k \leq f_{\max }$, then the reconstructed signal is equal to the original signal that was sampled (that is, $y(t)=x(t)$, if $f_s>2 f_{\max }$ ).

Signals composed of sums of sinusoids such that all frequencies are limited to a "band of frequencies" of the form $0 \leq f \leq f_{\max }$ are called bandlimited signals.[^11] Such signals could be represented as
$$
\begin{equation} \label{eq_4.19}
x(t)=\sum_{k=0}^N x_k(t)
\end{equation}
$$
where each of the individual signals is of the form $x_k(t)=A_k \cos \left(2 \pi f_k t+\varphi_k\right)$ with $0 \leq$ $f_k \leq f_{\text {max }}$. As we have seen in Chapter 3 and Appendix $\mathrm{C}$, such an additive combination of sinusoids can produce an infinite variety of both periodic and nonperiodic signal waveforms. If we sample the signal represented by (4.19) we obtain
$$
\begin{equation} \label{eq_4.20}
x[n]=x\left(n T_s\right)=\sum_{k=0}^N x_k\left(n T_s\right)=\sum_{k=0}^N x_k[n]
\end{equation}
$$
where $x_k[n]=A_k \cos \left(\hat{\omega}_k n+\varphi_k\right)$ with $\hat{\omega}_k=2 \pi f_k / f_s$. Thus, if we sample a sum of continuous-time cosines, we obtain a sum of sampled cosines, and if we sample above the Nyquist rate, then $f_s>2 f_{\max } \geq 2 f_k$, and $\left|\hat{\omega}_k\right| \leq \pi$ for each $x_k[n]$.



The final step in the process of sampling followed by reconstruction in Fig. 4-21 is D-to-C conversion by interpolation with
$$
\begin{equation}  \label{eq_4.21}
y(t)=\sum_{n=-\infty}^{\infty} x[n] p\left(t-n T_s\right)
\end{equation}
$$
where for perfect reconstruction, $p(t)$ would be given by (4.18). This expression for the reconstructed output is a linear operation on the samples $x[n]$. This means that the total output $y(t)$ consists of the sum of the outputs due to each of the different components $x_k[n]$. We can see this by substituting $\eqref{eq_4.20}$ into $\eqref{eq_4.21}$ as in
$$
\begin{equation} \label{eq_4.22}
y(t)
=\sum_{n=-\infty}^{\infty}\left(\sum_{k=0}^N x_k[n]\right) p\left(t-n T_s\right)
=\sum_{k=0}^N\left(\sum_{n=-\infty}^{\infty} x_k[n] p\left(t-n T_s\right)\right)
\end{equation}
$$

And due to $\eqref{eq_interpolation}$:
$$
(\sum_{n=-\infty}^{\infty} x_k[n] p\left(t-n T_s\right)) = x_k(t) .
$$
 

Now since each individual sinusoid is assumed to satisfy the conditions of the sampling theorem, it follows that the D-to-C converter reconstructs each component perfectly, and therefore we conclude that
$$
y(t)=\sum_{k=0}^N x_k(t)=x(t)
$$

Thus, we have shown that the Shannon sampling theorem applies to any signal that can be represented as a bandlimited (finite) sum of sinusoids, and since it can be shown that most real-world signals can be represented as bandlimited signals, it follows that the sampling theorem is a very general guide to sampling all kinds of signals.



[^11]: The corresponding complex exponential signals would be limited to the band $−f_\max ≤ f ≤ f_\max$.
