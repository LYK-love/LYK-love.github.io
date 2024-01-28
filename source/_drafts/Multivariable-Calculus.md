---
title: Multivariable Calculus
tags:
---

# Double integrals in polar coordinates

[Source](http://www.leadinglesson.com/double-integrals-in-polar-coordinates)

Consider a double integral $\iint_D f(x, y) d A$.

In polar coordinates, the differential area element $d A=r d r d \theta$.

Hence, $\iint_D f(x, y) d A=\iint_{\tilde{D}} f(r, \theta) r d r d \theta$, where $\tilde{D}$ is the region $D$ expressed in polar coordinates.



In polar coordinates, $x=r \cos \theta$ and $y=r \sin \theta$. Thus, $x^2+y^2=r^2$ In polar coordinates, the differential area element $d x d y=r d r d \theta$.

# Area of a circle

[Source](https://math.stackexchange.com/a/1863343)

## Solution on cylindrical coordinates

The area of a circle, $x^2+y^2=a^2$, in cylindrical coordinates is
$$
\int_0^{2 \pi} \int_0^a r d r d \theta=\pi a^2
$$



//

## Solution on cartesian coordinates

Think about how the cartesian variables $x$ and $y$ are bounded. If we have the equation
$$
x^2+y^2=r^2 \Rightarrow x= \pm \sqrt{r^2-y^2} \text { or } y= \pm \sqrt{r^2-x^2}
$$

And $|x|,|y|<r$. Note that this last condition also insures that the above square roots are real. Then this gives you bounds for your double integral, choosing to integrate $x$ first,
$$
\int_{-r}^r \int_{-\sqrt{r^2-y^2}}^{\sqrt{r^2-y^2}} \mathrm{~d} x \mathrm{~d} y=\int_{-r}^r 2 \sqrt{r^2-y^2} \mathrm{~d} y
$$

Which you can integrate using the substitution $y=r \sin (t) \Rightarrow \mathrm{d} y=r \cos (t) \mathrm{d} t$
$$
\begin{gathered}
2 \int_{-\frac{\pi}{2}}^{\frac{\pi}{2}} r^2 \cos ^2(t) \mathrm{d} t=\int_{-\frac{\pi}{2}}^{\frac{\pi}{2}} r^2(1+\cos (2 t)) \mathrm{d} t \\
=\left.r^2\left(t+\frac{1}{2} \sin (2 t)\right)\right|_{-\frac{\pi}{2}} ^{\frac{\pi}{2}}=r^2 \pi
\end{gathered}
$$

Note that I used the identity $\cos ^2(t)=1 / 2(1+\sin (2 t))$ to evaluate.
