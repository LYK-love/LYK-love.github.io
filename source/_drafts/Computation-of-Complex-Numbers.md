---
title: Computation of Complex Numbers
tags:
---

# Polar Form of Complex Number

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9a/Arctangent_Arccotangent.svg/294px-Arctangent_Arccotangent.svg.png)



The argument of a complex number $z=a+ib$  is **not** $\arctan(\frac{𝑏}{𝑎})$. It is given by[^1]
$$
\arg z = \begin{cases}
\arctan (b/a) &\mbox{if }  a>0 &\\ 
\arctan (b/a)+\pi &\mbox{if }  a<0,b\geq 0 \\
\arctan (b/a)-\pi &\mbox{if }  a<0,b< 0 \\
\pi/2 &\mbox{if }  a=0,b> 0 \\
-\pi/2 &\mbox{if }  a=0,b< 0 \\
\mathrm{undefined} &\mbox{if }  a=0,b= 0 \\ 
\end{cases}
$$
So: he argument of $z = -2$ is not $\arctan(\frac{0}{-2}) = \arctan 0 = 0$, it's $\arctan(\frac{0}{-2}) + \pi = \pi$. You can just image the plot. 

# How to solve $z^3−1=0$

If $z^3−1=0$, then we are looking for the cubic roots of unity, i.e. the numbers such that $z^3=1$.

If you're using complex numbers, then every polynomial equation of degree $k$ yields exactly $k$ solution. So, we're expecting to find three cubic roots.[^2]



We know that any complex number, $a + b i$, can be written in modulus-argument form, $r(\cos \theta +i\sin \theta)$

So: $1=1( \cos 0 + i \sin 0 )$

So: $z^3=1( \cos (0+2k\pi) + i \sin (0+2k\pi) )$



Use **de Moivre's theorem**: $(\cos x+i \sin x )^k=\cos kx+i \sin kx$

Then: $z=\cos (\frac{2}{3}kπ)+i \sin(\frac{2}{3}kπ)$

Now we must consider every $k$ such that $−π \le\frac{2}{3}kπ < π$:

$k=0,z=1$

$k=1,z= \cos (\frac{2}{3}kπ)+i \sin(\frac{2}{3}kπ)= - \frac{1}{2} + \frac{\sqrt 3}{2}i$

$k=−1,z=cos(-\frac{2}{3}π)+i \sin(- \frac{2}{3}π)= - \frac{1}{2} - \frac{\sqrt 3}{2}i$

These values are called the cubic roots of unity.



[^1]: https://math.stackexchange.com/questions/2073065/how-does-arctan0-equal-pi
[^2]: https://socratic.org/questions/how-do-i-use-demoivre-s-theorem-to-solve-z-3-1-0
