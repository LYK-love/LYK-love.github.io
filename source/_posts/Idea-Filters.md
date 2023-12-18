---
title: Idea Filters
date: 2023-12-11 23:24:22
tags: Digital Signal Processing
categoeirs: Electronic Engineering
mathjax: true
---

Source:

James McClellan, Ronald Schafer & Mark Yoder. (2015). IIR Filters. DSP First (2nd ed., pp. 394-457). Pearson.

<!--more-->


# Ideal Lowpass Filter

 (DSP First, Sec. 7-3.1)

- The ideal lowpass filter has the frequency response with unity gain for low frequencies and zero gain for high frequencies $H_{L P}\left(e^{j \omega}\right)= \begin{cases}1 & 0 \leq|\omega| \leq \omega_c \\ 0 & \omega_c<|\omega|<\pi\end{cases}$

- We know this answer! But now this is a system (impulse response) instead of a signal.

$$
h_{L P}[n]=\frac{1}{2 \pi} \int^{\omega_c}_{-{\omega_c}} e^{j \omega n} d \omega=\frac{e^{j \omega_c n}-e^{-j \omega_c n}}{2 j \pi n}=\frac{\sin \left(\omega_c n\right)}{\pi n} \triangleq \operatorname{sinc}\left(\omega_c n\right),-\infty<n<\infty
$$

- No obvious feedback difference equation, so this would be an "FIR" filter with infinite taps!
- Zero phase (good), but also non-causal (bad)

# Ideal Highpass Filter

- The ideal highpass filter has the frequency response with unity gain for high frequencies and zero gain for low frequencies,

$$
H_{H P}\left(e^{j \omega}\right)= \begin{cases}0 & 0 \leq|\omega| \leq \omega_c \\ 1 & \omega_c<|\omega|<\pi\end{cases}
$$

- Observe $H_{H P}\left(e^{j \omega}\right)=1-H_{L P}\left(e^{j \omega}\right)$
- Recall the DTFT of $\delta\left[n-n_0\right] \leftrightarrow e^{-j \omega n_0}$, so $\delta[n] \leftrightarrow e^{-j \omega 0}=1$
- By linearity of the DTFT,
$$
h_{H P}[n]=\delta[n]-\operatorname{sinc}\left(\omega_c n\right),-\infty<n<\infty
$$
- Many design techniques will use lowpass filters as examples, and tricks like this can be used to obtain highpass versions

# Ideal Bandpass Filter

- The ideal bandpass filter has the frequency response with unity gain for a band of frequencies and zero gain for others
$$
H_{B P}\left(e^{j \omega}\right)=\left\{\begin{array}{cc}
0 & 0 \leq|\omega| \leq \omega_{c 1} \\
1 & \omega_{c 1}<|\omega|<\omega_{c 2} \\
0 & \omega_{c 2}<|\omega|<\pi
\end{array}\right.
$$
- What is $h_{B P}[n]$ ?
- Could obtain from $h_{L P}[n]$ by applying frequency shift property twice, once to shift left and once to shift right and then add...
- Look for this problem in a Problem Set or exam!

# IIR Filter Design

 IIR filter design is an advanced topic

- Potentially helps us get around “infinite-FIR” implementations (pro)

- Usually has undesirable phase effects (con for comms and image systems)

- We have to worry about stability of IIR filters (con)

  • Readings in *DSP First
  \* • Sec. 10-7: Frequency response of (first-order) IIR filter

  • Sec. 10-12: Frequency response of second-order IIR filter • Sec. 10-13: Example of a (third-order) IIR lowpass filter

  ## Example

  Consider
  $$
  \begin{aligned}
  & y[n]=0.8 y[n-1]+x[n] \\
  & H(z)=\frac{1}{1-0.8 z^{-1}} \\
  & H\left(e^{j \omega}\right)=\frac{1}{1-0.8 e^{-j \omega}} .
  \end{aligned}
  $$
  ![image-20231211005405343](/Users/lyk/Library/Application Support/typora-user-images/image-20231211005405343.png)

  

  

  ![image-20231211005336947](/Users/lyk/Library/Application Support/typora-user-images/image-20231211005336947.png)

* Observation: Pole location drives peak response
* Pro: only two coefficients in difference equation
* Con: nonlinear phase (i.e. frequency-selective phase delay)
