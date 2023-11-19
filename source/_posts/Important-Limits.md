---
title: Important Limits
tags: Calculus
categories: Mathematics
mathjax: true
date: 2023-11-18 17:02:19
---

1. [Paul's Online Notes - Calculus](https://tutorial.math.lamar.edu/Classes/CalcI/CalcI.aspx)

<!--more-->

# L'Hospital's Rule

[->Source](https://tutorial.math.lamar.edu/classes/calci/lhospitalsrule.aspx)

Suppose that we have one of the following cases,
$$
\lim _{x \rightarrow a} \frac{f(x)}{g(x)}=\frac{0}{0} \quad \text { OR } \quad \lim _{x \rightarrow a} \frac{f(x)}{g(x)}=\frac{ \pm \infty}{ \pm \infty}
$$
where $a$ can be any real number, infinity or negative infinity. In these cases we have,
$$
\lim _{x \rightarrow a} \frac{f(x)}{g(x)}=\lim _{x \rightarrow a} \frac{f^{\prime}(x)}{g^{\prime}(x)}
$$

So, L'Hospital's Rule tells us that if we have an indeterminate form $0 / 0$ or $\infty / \infty$ all we need to do is differentiate the numerator and differentiate the denominator and then take the limit.

# $\lim _{x \rightarrow 0} \frac{\sin x}{x}$ 



So, we have already established that this is a 0/0 indeterminate form so let's just apply L'Hospital's Rule.
$$
\lim _{x \rightarrow 0} \frac{\sin x}{x}=\lim _{x \rightarrow 0} \frac{\cos x}{1}=\frac{1}{1}=1
$$
# $\lim _{x \rightarrow +\infty} \frac{x}{e^x}$

Since $\lim _{x \rightarrow \infty} \frac{x}{e^x}=\frac{\infty}{\infty}$ we use the L'Hopital law to get
$$
\lim _{x \rightarrow +\infty} \frac{x}{e^x}=\lim _{x \rightarrow +\infty} \frac{\frac{d x}{d x}}{d \frac{e^x}{d x}}=\lim _{x \rightarrow +\infty} \frac{1}{e^x}=0
$$


# $\lim _{x \rightarrow -\infty} {x}{e^x}$

At first glance, we can see when $x \rightarrow -\infty$, $x \rightarrow -\infty$ and $e^x \rightarrow 0$, thus we have $-\infty \cdot 0$ which is indeterminate.

Howver, we can first use $t = -x$ to substitude $x$
$$
\lim _{x \rightarrow -\infty} {x}{e^x} = \lim _{t \rightarrow +\infty} {-t}{e^{-t}}
$$
Then
$$
\lim _{t \rightarrow +\infty} {-t}{e^{-t}} = - \lim _{t \rightarrow +\infty} \frac {t}{e^{t}} = -\lim _{x \rightarrow +\infty} \frac{x}{e^x} = 0
$$




#  $\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{x^2}$ 

Sometimes we will need to apply L'Hospital's Rule more than once.

First
$$
\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{x^2}=\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{2 x} .
$$

Then
$$
\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{x^2}=\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{2 x}=\lim _{x \rightarrow \infty} \frac{\mathbf{e}^x}{2}=\infty .
$$



# Chain Rule

Suppose that we have two functions $f(x)$ and $g(x)$ and they are both differentiable.
1. If we define $F(x)=(f \circ g)(x)$ then the derivative of $F(x)$ is,
$$
F^{\prime}(x)=f^{\prime}(g(x)) g^{\prime}(x)
$$
2. If we have $y=f(u)$ and $u=g(x)$ then the derivative of $y$ is,
$$
\frac{d y}{d x}=\frac{d y}{d u} \frac{d u}{d x}
$$

Each of these forms have their uses, however we will work mostly with the first form in this class. 

To see the proof of the Chain Rule see the [Proof of Various Derivative Formulas section]() of the Extras chapter.

Now, let's go back and use the Chain Rule on the function that we used when we opened this section.

## Examples

Use the Chain Rule to differentiate $R(z)=\sqrt{5 z-8}$.



We've already identified the two functions that we needed for the composition, but let's write them back down anyway and take their derivatives.
$$
\begin{aligned}
f(z) & =\sqrt{z} & g(z) & =5 z-8 \\
f^{\prime}(z) & =\frac{1}{2 \sqrt{z}} & g^{\prime}(z) & =5
\end{aligned}
$$


So, using the chain rule we get,
$$
\begin{aligned}
R^{\prime}(z) & =f^{\prime}(g(z)) g^{\prime}(z) \\
& =f^{\prime}(5 z-8) g^{\prime}(z) \\
& =\frac{1}{2}(5 z-8)^{-\frac{1}{2}}(5) \\
& =\frac{1}{2 \sqrt{5 z-8}}(5) \\
& =\frac{5}{2 \sqrt{5 z-8}}
\end{aligned}
$$

And this is what we got using the definition of the derivative.
