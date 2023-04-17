---
title: Area and Volumn of Sphere
tags:
---





首先我们证明一下如何在球的表面积和体积之间建立联系。



显然，可以用微分的思想，我们把球的表面分成许多个小方格，然后连接球心和每个小方格的顶点，将整个球分成很多个“锥体”，求和即可。
$$
V=\sum\frac{1}{3}s_iR=\frac{1}{3}R\sum s_i=\frac{1}{3}SR
$$




- 当方格分的越多，计算结果就会越接近真实值。
- 这样我们就建立起了球的面积和体积之间的联系，可以知一求二。





# 球的表面积



## way 2

- 也可以用微分直接求球的表面积，先给出一个定理：球的表面积等于其外接棱柱的侧面积。

- 我们仍然可以将球的表面分成无穷多个小方格，然后假设球的某一条过球心的轴会向外发光。这时每个小方格都会在圆柱上留下投影，通过一些简单的平面几何的证明即可得到其长的比和宽的比互为倒数，所以其面积是一样的。

- 放个图可能会好理解一些：

  [![3B1B](https://images.cnblogs.com/cnblogs_com/pycr/1940520/o_210501131628%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202021-05-01%20205319.png)](https://images.cnblogs.com/cnblogs_com/pycr/1940520/o_210501131628屏幕截图 2021-05-01 205319.png)

# 球的体积

运用微分的思想，我们可以假设将球切成了很多很多片，每一片都可以近似于一个高无限趋近于 00 的圆柱。

![Volume of Sphere Derivation](https://cdn1.byjus.com/wp-content/uploads/2020/07/derivation-of-volume-of-sphere.png)

 The volume of the disc element, dV can be expressed by:

dV =(πr2)dy

dV =π (R2-y2) dy



Thus, the total volume of the sphere can be given by:
$$
\begin{array}{l}V = \int_{y=-R}^{y=+R}dV\end{array}
$$

$$
\begin{array}{l}V = \int_{y=-R}^{y=+R}\pi(R^{2}-y^{2})dy\end{array}
$$

$$
\begin{array}{l}V = \pi[R^{2}y  – \frac{y^{3}}{3}]_{y=-R}^{y=+R}\end{array}
$$


Now, substitute the limits:
$$
\begin{array}{l}V = \pi[(R^{3}-\frac{R^{3}}{3})-(-R^{3}+\frac{R^{3}}{3})]\end{array}
$$




Thus, the dimensional formula of volume of the sphere is
$$
V =\frac{\pi}{3}(4R^{3})
$$


- 



* useful web: https://byjus.com/maths/volume-of-sphere/
* 
