---
title: Frequency Response of FIR Filters
tags: Digital Signal Processing
categoeirs: Electronic Engineering
mathjax: true
---



In this chapter, we introduce the concept of the **frequency response** of an LTI FIR filter and show that the frequency response and impulse response are uniquely related.

It is remarkable that **for LTI systems, when the input is a complex sinusoid, the corresponding output signal is another complex sinusoid of exactly the same frequency, but with different magnitude and phase.**

# Sinusoidal Response of FIR Systems

Linear time-invariant systems behave in a particularly simple way **when the input is a discrete-time complex exponential**. To see this, consider an FIR system
$$
y[n]=\sum_{k=0}^M b_k x[n-k]
$$
and assume that the input is a complex exponential signal[^1] with normalized radian frequency $\hat{\omega}$, amplitude $A$, and phase $\phi$
$$
x[n]=A e^{j \varphi} e^{j \omega n} \quad-\infty<n<\infty
$$

For such inputs, the corresponding output is
$$
\begin{aligned}
y[n] & =\sum_{k=0}^M b_k A e^{j \varphi} e^{j \hat{\omega}(n-k)} \\
& =\left(\sum_{k=0}^M b_k e^{-j \hat{\omega} k}\right) A e^{j \varphi} e^{j \hat{\omega} n} \\
& =\mathcal{H}(\hat{\omega}) A e^{j \varphi} e^{j \hat{\omega} n} \quad-\infty<n<\infty
\end{aligned}
$$
where
$$
\mathcal{H}(\hat{\omega})=\sum_{k=0}^M b_k e^{-j \hat{\omega} k}
$$

Because we have represented the frequency of the complex exponential signal as the general symbol $\hat{\omega}$, we have obtained an expression (6.3) that is a function of $\hat{\omega}$. In other words, (6.3) describes the response of the LTI system to a complex exponential signal of any frequency $\hat{\omega}$. The quantity $\mathcal{H}(\hat{\omega})$ defined by (6.3) is therefore called the frequencyresponse function for the system. Generally, we shorten this to frequency response.

However, there is an issue of notation for the frequency response that is dictated by consistency with the $z$-transform (to be introduced in Chapter 9). In (6.3) the righthand side contains powers of the complex exponential $e^{j \hat{\omega}}$. This is true of many expressions for the frequency response. 

Therefore, we elect to **use the notation $H\left(e^{j \hat{\omega}}\right)$ instead of $\mathcal{H}(\hat{\omega})$** to emphasize the ubiquity of $e^{j \hat{\omega}}$. 

* The function $H\left(e^{j \hat{\omega}}\right)$ still depends on the variable $\hat{\omega}$. 



Furthermore, since the impulse response sequence of an FIR filter is the same as the sequence of filter coefficients, we can **express the frequency response in terms of either the filter coefficients $b_k$ or the impulse response $h[k]$,** that is,

Frequency Response of an FIR System:
$$
H\left(e^{j \hat{\omega}}\right)=\sum_{k=0}^M b_k e^{-j \hat{\omega} k}=\sum_{k=0}^M h[k] e^{-j \hat{\omega} k}
$$



Several important points can be made about (6.2) and (6.4). First of all, the precise interpretation of (6.2) is as follows: <u>When the input is a discrete-time complex exponential signal, the output of an LTI FIR filter is also a discretetime complex exponential signal</u> with a different complex amplitude, but the same frequency $\hat{\omega}$. The frequency response multiplies the complex exponential input signal, thereby changing the complex amplitude. 

While it is tempting to express this fact by the mathematical statement $y[n]=H\left(e^{j \hat{\omega}}\right) x[n]$, it is strongly recommended that this should never be done because it is too easy to forget that the mathematical statement is true only for complex exponential signals of frequency $\hat{\omega}$. The statement $y[n]=H\left(e^{j \hat{\omega}}\right) x[n]$ is meaningless for any signal other than signals of precisely the form $x[n]=A e^{j \varphi} e^{j \omega \hat{n}}$. It is very important to understand this point.

A second important point is that the frequency response $H\left(e^{j \hat{\omega}}\right)$ is complexvalued so it can be expressed either as $H\left(e^{j \hat{\omega}}\right)=\left|H\left(e^{j \hat{\omega}}\right)\right| e^{j \angle H\left(e^{j \hat{\omega}}\right)}$ or as $H\left(e^{j \hat{\omega}}\right)=$ $\Re\left\{H\left(e^{j \hat{\omega}}\right)\right\}+j \Im\left\{H\left(e^{j \hat{\omega}}\right)\right\}$. 

The magnitude and angle form of the frequency response is the most convenient form, since the complex multiplication needed in (6.2) is most conveniently accomplished in polar form. The effect of the LTI system on the magnitude $(A)$ and phase $(\varphi)$ of the input complex exponential signal is determined completely by the frequency response $H\left(e^{j \hat{\omega}}\right)$. Specifically, if the input is $x[n]=A e^{j \varphi} e^{j \hat{\omega} n}$, then using the polar form of $H\left(e^{j \hat{\omega}}\right)$ gives the result
$$
\begin{aligned}
y[n] & =\left(\left|H\left(e^{j \hat{\omega}}\right)\right| e^{j \angle H\left(e^{j \hat{\omega}}\right)}\right) A e^{j \varphi} e^{j \hat{\omega} n} \\
& =\left(\left|H\left(e^{j \hat{\omega}}\right)\right| \cdot A\right) e^{j\left(\angle H\left(e^{j \hat{\omega}}\right)+\varphi\right)} e^{j \hat{\omega} n}
\end{aligned}
$$

* The magnitude of $H\left(e^{j \hat{\omega}}\right)$ multiplies the signal amplitude $(A)$ which changes the size of the signal. Thus, $\left|H\left(e^{j \hat{\omega}}\right)\right|$ is usually referred to as the gain of the system.[^2] 

* The angle $\angle H\left(e^{j \hat{\omega}}\right)$ simply adds to the phase $(\varphi)$ of the input, thereby producing additional phase shift in the complex exponential signal.

## Examples

### EXAMPLE 6-1 Formula for the Frequency Response

Consider an LTI system for which the difference equation coefficients are $\left\{b_k\right\}=\{1,2,1\}$. Substituting into (6.3) gives
$$
H\left(e^{j \hat{\omega}}\right)=1+2 e^{-j \hat{\omega}}+e^{-j \hat{\omega} 2}
$$

To obtain formulas for the magnitude and phase of the frequency response of this FIR filter, we can manipulate the equation as follows:
$$
\begin{aligned}
H\left(e^{j \hat{\omega}}\right) & =1+2 e^{-j \hat{\omega}}+e^{-j \hat{\omega} 2} \\
& =e^{-j \hat{\omega}}\left(e^{j \hat{\omega}}+2+e^{-j \hat{\omega}}\right) \\
& =e^{-j \hat{\omega}}(2+2 \cos \hat{\omega})
\end{aligned}
$$

Since $(2+2 \cos \hat{\omega}) \geq 0$ for frequencies $-\pi<\hat{\omega} \leq \pi$, the magnitude is $\left|H\left(e^{j \hat{\omega}}\right)\right|=$ $(2+2 \cos \hat{\omega})$ and the phase is $\angle H\left(e^{j \hat{\omega}}\right)=-\hat{\omega}$.

### EXAMPLE 6-2 Complex Exponential Input

Consider the complex input $x[n]=2 e^{j \pi / 4} e^{j(\pi / 3) n}$ whose frequency is $\hat{\omega}=\pi / 3$. If this signal is the input to the system of Example 6-1, then we must evaluate the frequency response at the input frequency in order to use the frequency-domain method defined in (6.5). The evaluation gives: $\left|H\left(e^{j \pi / 3}\right)\right|=2+2 \cos (\pi / 3)=3$ and $\angle H\left(e^{j \pi / 3}\right)=-\pi / 3$. Therefore, the output of the system for the given input is
$$
\begin{aligned}
y[n] & =3 e^{-j \pi / 3} \cdot 2 e^{j \pi / 4} e^{j \pi n / 3} \\
& =(3 \cdot 2) \cdot e^{(j \pi / 4-j \pi / 3)} e^{j \pi n / 3} \\
& =6 e^{-j \pi / 12} e^{j \pi n / 3}=6 e^{j \pi / 4} e^{j \pi(n-1) / 3}
\end{aligned}
$$

Thus, for this system and the given input $x[n]$, the output is equal to the input multiplied by 3 , and the phase shift of $-\pi / 3$ corresponds to a delay of one sample.



# Superposition and the Frequency Response

The principle of superposition makes it very easy to find the output of an LTI system if the input is a sum of complex exponential signals. This is why the frequency response is so important in the analysis and design of LTI systems. As an example, suppose that the input to an LTI system is a cosine wave with a specific normalized frequency $\hat{\omega}_1$ plus a DC level,
$$
x[n]=A_0+A_1 \cos \left(\hat{\omega}_1 n+\varphi_1\right)
$$

If we represent the signal in terms of complex exponentials, the signal is composed of three complex exponential signals, with frequencies $\hat{\omega}=0, \hat{\omega}_1$, and $-\hat{\omega}_1$, so
$$
x[n]=A_0 e^{j 0 n}+\frac{A_1}{2} e^{j \varphi_1} e^{j \hat{\omega}_1 n}+\frac{A_1}{2} e^{-j \varphi_1} e^{-j \hat{\omega}_1 n}
$$

By superposition, we can determine the output due to each term separately and then add them to obtain the output $y[n]$ corresponding to $x[n]$. Because the components of the input signal are all complex exponential signals, it is easy to find their respective outputs if we know the frequency response of the system; we just multiply each component by $H\left(e^{j \hat{\omega}}\right)$ evaluated at the corresponding frequency to obtain
$$
y[n]=H\left(e^{j 0}\right) A_0 e^{j 0 n}+H\left(e^{j \hat{\omega}_1}\right) \frac{A_1}{2} e^{j \varphi_1} e^{j \hat{\omega}_1 n}+H\left(e^{-j \hat{\omega}_1}\right) \frac{A_1}{2} e^{-j \varphi_1} e^{-j \hat{\omega}_1 n}
$$

Note that we have used the fact that a constant signal is a complex exponential with $\hat{\omega}=0$. If we express $H\left(e^{j \hat{\omega}_1}\right)$ as $H\left(e^{j \hat{\omega}_1}\right)=\left|H\left(e^{j \hat{\omega}_1}\right)\right| e^{j \angle H\left(e^{j \hat{\omega}_1}\right)}$, then the algebraic steps[^3] in (6.6) show that $y[n]$ can finally be expressed as a modified cosine signal plus a constant.
$$
\begin{aligned}
y[n]= & H\left(e^{j 0}\right) A_0 e^{j 0 n}+H\left(e^{j \hat{\omega}_1}\right) \frac{A_1}{2} e^{j \varphi_1} e^{j \hat{\omega}_1 n}+H^*\left(e^{j \hat{\omega}_1}\right) \frac{A_1}{2} e^{-j \varphi_1} e^{-j \hat{\omega}_1 n} \\
= & H\left(e^{j 0}\right) A_0+\left|H\left(e^{j \hat{\omega}_1}\right)\right| e^{j \angle H\left(e^{j \hat{\omega}_1}\right)} \frac{A_1}{2} e^{j \varphi_1} e^{j \hat{\omega}_1 n} \\
& +\left|H\left(e^{j \hat{\omega}_1}\right)\right| e^{-j \angle H\left(e^{j \hat{\omega}_1}\right)} \frac{A_1}{2} e^{-j \varphi_1} e^{-j \hat{\omega}_1 n} \\
= & H\left(e^{j 0}\right) A_0+\left|H\left(e^{j \hat{\omega}_1}\right)\right| \frac{A_1}{2} e^{j\left(\hat{\omega}_1 n+\varphi_1+\angle H\left(e^{j \hat{\omega}_1}\right)\right)} \\
& +\left|H\left(e^{j \hat{\omega}_1}\right)\right| \frac{A_1}{2} e^{-j\left(\hat{\omega}_1 n+\varphi_1+\angle H\left(e^{j \hat{\omega}_1}\right)\right)} \\
= & H\left(e^{j 0}\right) A_0+\left|H\left(e^{j \hat{\omega}_1}\right)\right| A_1 \cos \left(\hat{\omega}_1 n+\varphi_1+\angle H\left(e^{j \hat{\omega}_1}\right)\right)
\end{aligned}
$$

Notice that the magnitude and phase change of the cosine input signal are taken from the positive frequency part of $H\left(e^{j \hat{\omega}}\right)$, but also notice that it was crucial to express $x[n]$​ as a sum of complex exponentials and then use the frequency response to find the output due to each complex component separately.



## EXAMPLE 6-3 Cosine Input
For the FIR filter with coefficients $\left\{b_k\right\}=\{1,2,1\}$, find the output when the input is
$$
x[n]=3 \cos \left(\frac{\pi}{3} n-\frac{\pi}{2}\right)
$$

The frequency response of the system was determined in Example 6-1 to be
$$
H\left(e^{j \hat{\omega}}\right)=(2+2 \cos \hat{\omega}) e^{-j \hat{\omega}}
$$

Note that $H\left(e^{-j \hat{\omega}}\right)=H^*\left(e^{j \hat{\omega}}\right)$, so $H\left(e^{j \hat{\omega}}\right)$ has conjugate symmetry. Solution of this problem requires just one evaluation of $H\left(e^{j \hat{\omega}}\right)$ at the frequency $\hat{\omega}=\pi / 3$ :
$$
\begin{aligned}
H\left(e^{j \pi / 3}\right) & =e^{-j \pi / 3}(2+2 \cos (\pi / 3)) \\
& =e^{-j \pi / 3}\left(2+2\left(\frac{1}{2}\right)\right)=3 e^{-j \pi / 3}
\end{aligned}
$$

Therefore, the magnitude is $\left|H\left(e^{j \pi / 3}\right)\right|=3$ and the phase is $\angle H\left(e^{j \pi / 3}\right)=-\pi / 3$, so the output is
$$
\begin{aligned}
y[n] & =(3)(3) \cos \left(\frac{\pi}{3} n-\frac{\pi}{3}-\frac{\pi}{2}\right) \\
& =9 \cos \left(\frac{\pi}{3}(n-1)-\frac{\pi}{2}\right)
\end{aligned}
$$

**Notice that the magnitude of the frequency response <u>multiplies</u> the amplitude of the cosine signal, and the phase angle of the frequency response <u>adds</u> to the phase of the cosine signal.** This problem could also be studied and solved with the dltidemo MATLAB GUI.



**If the input signal consists of the sum of many complex exponential signals, the frequency response can be applied to find the output due to each component separately, and the results added to determine the total output.** This is the principle of **superposition** at work. 

<u>If we can find a representation for a signal in terms of complex exponentials, the frequency response gives a simple and highly intuitive means for determining what an LTI system does to that input signal.</u> In the general case, if the input to an LTI system is a real signal and can be represented as
$$
\begin{aligned}
x[n] & =X_0+\sum_{k=1}^N\left(\frac{X_k}{2} e^{j \hat{\omega}_k n}+\frac{X_k^*}{2} e^{-j \hat{\omega}_k n}\right) \\
& =X_0+\sum_{k=1}^N\left|X_k\right| \cos \left(\hat{\omega}_k n+\angle X_k\right)
\end{aligned}
$$


then the corresponding output is $y[n]$ in $(6.7)$, if $H\left(e^{-j \hat{\omega}}\right)=H^*\left(e^{j \hat{\omega}}\right)$, which is true when the filter coefficients are real.
$$
\begin{aligned}
y[n] & =H\left(e^{j 0}\right) X_0+\sum_{k=1}^N\left(H\left(e^{j \hat{\omega}_k}\right) \frac{X_k}{2} e^{j \hat{\omega}_k n}+H\left(e^{-j \hat{\omega}_k}\right) \frac{X_k^*}{2} e^{-j \hat{\omega}_k n}\right) \\
& =H\left(e^{j 0}\right) X_0+\sum_{k=1}^N\left|H\left(e^{j \hat{\omega}_k}\right)\right|\left|X_k\right| \cos \left(\hat{\omega}_k n+\angle X_k+\angle H\left(e^{j \hat{\omega}_k}\right)\right)
\end{aligned}
$$

For $y[n]$ in (6.7), each individual complex exponential component in $x[n]$ has been modified by the frequency response evaluated at the frequency of that component.





EXAMPLE 6-4 Three Sinusoidal Inputs
For the FIR filter with coefficients $\left\{b_k\right\}=\{1,2,1\}$, find the output when the input is
$$
x[n]=4+3 \cos \left(\frac{\pi}{3} n-\frac{\pi}{2}\right)+3 \cos \left(\frac{7 \pi}{8} n\right)
$$

There are three frequencies, $0, \pi / 3$, and $7 \pi / 8$, so the output has three sinusoids at those same frequencies. The frequency response of the system was determined in Example 6-1, and is the same as the frequency response in Example 6-3. The input in this example differs from that of Example 6-3 by the addition of a constant (DC) term and an additional cosine signal of frequency $7 \pi / 8$. The solution by superposition therefore requires that we evaluate $H\left(e^{j \hat{\omega}}\right)$ at frequencies $0, \pi / 3$, and $7 \pi / 8$, giving
$$
\begin{aligned}
H\left(e^{j 0}\right) & =4 \\
H\left(e^{j \pi / 3}\right) & =3 e^{-j \pi / 3} \\
H\left(e^{j 7 \pi / 8}\right) & =0.1522 e^{-j 7 \pi / 8}
\end{aligned}
$$

Therefore, the output is
$$
\begin{aligned}
y[n] & =4 \cdot 4+3 \cdot 3 \cos \left(\frac{\pi}{3} n-\frac{\pi}{3}-\frac{\pi}{2}\right)+0.1522 \cdot 3 \cos \left(\frac{7 \pi}{8} n-\frac{7 \pi}{8}\right) \\
& =16+9 \cos \left(\frac{\pi}{3}(n-1)-\frac{\pi}{2}\right)+0.4567 \cos \left(\frac{7 \pi}{8}(n-1)\right)
\end{aligned}
$$

Notice that, in this case, the $\mathrm{DC}$ component is multiplied by 4 , the component at frequency $\hat{\omega}=\pi / 3$ is multiplied by 3 , but the component at frequency $\hat{\omega}=7 \pi / 8$ is multiplied by 0.1522 . Because the frequency-response magnitude (gain) is so small at frequency $\hat{\omega}=7 \pi / 8$, the component at this frequency is essentially filtered out of the input signal.





[^1]: hRecall tat this discrete-time signal could have been obtained by sampling the continuous-time signal $x(t)=A e^{j \varphi} e^{j \omega t}$. If $x[n]=x\left(n T_s\right)$, then $\omega$ and $\hat{\omega}$ are related by $\hat{\omega}=\omega T_s$, where $T_s$ is the sampling period.

[^2]: The gain can be less than or greater than 1 , even though the word suggests greater than.

[^3]: It is assumed that $H\left(e^{j \hat{\omega}}\right)$ has the conjugate-symmetry property $H\left(e^{-j \hat{\omega}}\right)=H^*\left(e^{j \hat{\omega}}\right)$, which is always true when the filter coefficients are real. (See Section 6-4.3.)
