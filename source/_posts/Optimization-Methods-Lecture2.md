---
title: Optimization-Methods-Lecture2
tags: Optimization Methods
categories: Optimization Methods
mathjax: true
date: 2021-09-08 18:34:11
---


Outline：

* **Norms**
* **Analysis**
* **Functions**
* **Derivatives**
* **Linear Algebra**

<!--more-->

# **Norms**

## Inner product 

* Inner product on R^n^
  $$
  <x,y>=x^Ty=\sum\limits_{i=1}^{n}x_iy_i \in R^n
  $$

* Euclidean norm, or $l_2$ - norm
  $$
  ||x||_2=(x^Tx)^{1/2}=(x_1^2+\dots+x_n^2)^{1/2}, x \in R^n
  $$

* Cauchy-Schwartz inequality


$$
|x^Ty| \leq ||x||_2||y||_2,x,y \in R^n
$$

* Angle between nonzero vectors $x,y \in R^n$
  $$
  \angle (x,y) = cos^{-1}(\frac {x^Ty}{||x||_2||y||_2}),x,y \in R^n,\angle (x,y) \in (0,\pi
  $$

* Inner product on $R^{m\times n}, X,Y \in R^{m\times n} $​
  $$
  <X,Y>=\tr (X^TY)=\sum\limits_{i=1}^{m}\sum\limits_{j=1}^{n}X_{ij}Y_{ij}
  $$
  Here $\tr()$ denotes trace of a matrix

* Frobenius norm of a matrix $x \in R^{m \times n}$​ 和向量的二范数对应
  $$
  ||X||_F = (\tr(X^TX))^{1/2}=(\sum\limits_{i=1}^{m}\sum\limits_{j=1}^{n}X_{ij}^2)^{1/2}
  $$

* Inner product on $S^n$
  $$
  <X,Y>=tr(XY)=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}X_{ij}Y_{ij} = \sum\limits_{i=1}^{n}X_{ii}Y_{ii} + 2 \sum\limits_{i<j}X_{ij}Y_{ij}
  $$
  Here $S^n$​ denotes symmetrical matrices on $R^{n \times n}$

---

## Norms

* **A function** $f: R^n \rarr R$  **with dom** $f = R^n$​ **is called a norm if**

  *  $f$ is nonnegative: $f(x) \geq 0$  for all $x \in R^n$
  *  $f$ is definite( 正定的 ): $f(x)=0$  only if $x=0$
  *  $f$​ is homogeneous( 同质的 ): $f(tx)=|t|f(x)$ , for all $x \in R^n$​ and $t \in R$​
  *  $f$ satisfies the triangle inequality: $f(x+y) \leq f(x) + f(y)$ , for all $x,y \in R^n$​

* **Distance**

  * Between vectors $x$ and $y$ as the length of their difference, i.e.,
    $$
    \mathrm {dist}(x,y) = ||x-y||
    $$

  没有加下标， 表示抽象的范数

  ---

  

* **Unit ball**

  * The set of all vectors with norm less than or equal to one,
    $$
    \Beta = {x \in R^n \mid ||x|| \leq 1}
    $$
    is called the unit ball of the norm $||\cdot||$  ( 单位球不唯一， 还需要指定一个范数 )

  * The unit ball satisfies the following properties:

    * $\Beta$ is symmetric about the origin, i.e., $x \in \Beta$ if and only if $ -x \in \Beta $
    * $\Beta$ is convex
    * $\Beta$ is closed, bounded, and has nonempty interior

  * Conversely, if $C \subseteq R^n$​​​ is any set satisfying these three conditions, then it is the unit ball of a norm:
    $$
    ||x|| = (\sup\{t \geq 0 | tx \in C\})^{-1}
    $$

  ---

  

* Spme common norms on $R^n$

  * Sum-absolute-value, or $l_1$ - norm
    $$
    ||x||_1 = |x|_1 + \dots + |x|_n, x \in R^n
    $$

  * Chebyshev or $l_\infty$ - norm
    $$
    ||x||_{\infty} = \max\{|x_1|, \dots, |x_n|\}
    $$

  * $l_p$ - norm, $p \geq 1$
    $$
    ||x||_p = (|x_1|^p + \dots + |x_n|^p)^{1/p}
    $$

  * For $P \in S_{++}^n$ ( 对称的 $n \times n$ 的正定矩阵 ), $P$ - quadratic norm is 
    $$
    ||x||_P = (x^TPx)^{1/2}=||P^{1/2}x||_2
    $$

* 

---

* Some common norms on $R^{m \times n}$

  * Sum-absolute-value norm 对应向量的一范数

    $||X||_\mathrm{sav} = \sum\limits_{i=1}^m\sum\limits_{j=1}^n |X_{ij}|$​

  * Maximum-absolute-value norm 对应向量的无穷范数
    $$
    ||X||_{\mathrm{mav}} = \max\{ |X_{ij}| \mid i=1, \dots,m,j=1,\dots,n \}
    $$

* 

---

* **Equivalence of norms**

  * Suppose that $||\cdot||_a$ and $||\cdot||_b$  are norms on $R^n$ ,  there exist positive constants $\alpha$ and $\beta$ ,  for all $x \in R^n$
    $$
    \alpha ||x||_a \leq ||x||_b \leq ||x||_a
    $$

  * if $||\cdot||$  is any norm on $R^n$ ,  then there exists a quadratic norm $||\cdot||_P$ for which
    $$
    ||\cdot||_P \leq ||x|| \leq \sqrt{n}{ ||x||_P }
    $$

  holds for all $x$

---

* **Operator norms**  算子范数

  * Suppose $||\cdot||_a$ and $||\cdot||_b$  are norms on $R^m$ and $R^n$ ,  respectively. Operator norm of $X \in R^{m \times n}$ induced by  $||\cdot||_a$ and $||\cdot||_b$​​​  is
    $$
    ||X||_{a,b}=\sup\{||Xu||_a \mid ||u|| \leq 1\}
    $$

  * When $||\cdot||_a$   and $||\cdot||_b$  are Euclidean norms, the operator norm of $X$ is its maximum singular value ( 最大奇异值 ) ， and is denoted  $||X||_2$
    $$
    ||X||_2 = \sigma_{\max}(X) = ( \lambda_{\max}{ X^TX } )^1/2
    $$

   **Spectral norm**( 谱范数 ) or **$l_2$​ - norm**

  * The norm induced by the $l_{\infty}$​​ - norm on $R^m$​ and $R^n$​​  ,   denoted $||X||_\infty$​ is the max-row-sum norm,
    $$
    ||X||_\infty = \sup\{ ||Xu||_\infty \mid ||u||_\infty \leq 1 \} = \max_{i=1,\dots,m}\sum\limits_{j=1}^{n}|X_{ij}|
    $$

  * The norm induced by the $l_1$​​​ - norm on $R^m$​​​ and $R^n$​​​  ,   denoted $||X||_1$​​​​ is the max-column-sum norm,
    $$
    ||X||_1 = \max_{j=1,\dots,n}\sum\limits_{i=1}^{m}|X_{ij}|
    $$

* **Dual norm** 对偶范数

  * Let $$||\cdot||$$ be a norm $R^n$

  * The associated dual norm, denoted $||\cdot||_*$ ,  is defined as
    $$
    ||z||_* = \sup \{ z^Tx \mid  ||x|| \leq 1 \}
    $$

  * We have the **inequality**
    $$
    z^Tx \leq ||x|| ||z||_* \\
     \because z^T \frac{x}{||x||} \leq \sup \{ z^Tx \mid ||x|| \leq 1 \} = ||z||_* \\
    \therefore z^Tx=z^T \frac {x}{||x||}\cdot||x|| \leq ||z||_*||x|| 
    $$
    
  * The dual of Euclidean norm 二范数互为对偶
    $$
    \sup \{z^Tx \mid ||x||_2 \leq 1 \} = ||z||_2
    $$
  
  * The dual norm of the $l_{\infty}$ norm 无穷范数的对偶是一范数， 反之亦然
    $$
    \sup \{z^Tx \mid ||x||_{\infty} \leq 1 \} = ||z||_1
    $$
  
  * The  dual norm of  the dual norm 对偶范数的对偶范数是其本身
    $$
    ||\cdot||_{*_{*}} = ||\cdot||
    $$
  
  * The dual norm of $l_p$ - norm is the $l_q$ - norm such that
    $$
    \frac {1}{p} + \frac {1}{q} = 1
    $$
  
  * The dual of the $l_2$ - norm on $R^{m \times n}$​ is the **nuclear norm**( 核范数 )
    $$
    ||Z||_{2*} = \sup \{\tr(Z^TX) \mid ||Z|| \leq 1\} \\
    = \sigma_1(Z) + \dots + \sigma_r(Z) = \tr[ (Z^TZ)^{1/2} ] 
    $$

# Analysis

* **Interior and Open Set**

  * An element $x \in C \subseteq R^n$ is called an interior point of $C$ if there exists an $\varepsilon > 0$ for which 
    $$
    \{y \mid ||y-x||_2 \leq \varepsilon\} \subseteq C
    $$
    i.e., there exists a ball centered at $$x$$ that lies entirely in $C$​ ( 可以用任意范数，只要找到一个范数满足即可 )

  * The set of all points interior to $C$ is called the interior of $C$ and is denoted $\mathrm{int}C$

  * A set $C$ is open if $\mathrm{int}C=C $

* **Closed Set and Boundary**

  * A set $C \subseteq R^n$  is closed if its complement is open
    $$
    R^n \setminus C = \{ x \in R^n \mid x \notin C \}
    $$

  * The closure of a set $C$ is defined as
    $$
    \mathrm{cl \ } {C} = R^n \setminus \mathrm{int \ }(R^n \setminus C)
    $$

  * The boundary of the set $C$ is defined as
    $$
    \mathrm {bd \ C} = \mathrm { cl \ } C \setminus \mathrm {int \ } C
    $$


    * $C$ is closed if it contains its boundary. It is open if it contains no boundary points

---

* **Supremun and infimum**

  * The least upper bound or supremum of the set $C$ is denoted $\sup {C}$

  * The greatest upper bound or infimum of the set $C$​ is denoted $\inf {C}$​

  $$
  \inf C = -(\sup (-C))
  $$

  

# Functions

* **Notation**
  $$
  f: A \rarr B
  $$

  * $\mathrm {dom} f \subseteq A$

* **Continuity**

  * A function $f:R^n \rarr R^m $​ is continuous at $𝑥 \in \mathrm{dom} \ f$​ if for all $\varepsilon > 0$​ there exists a $\delta$​ such that
       𝑓 
  * is continuous if it is continuous at every point

* **Closed functions**

  * A function $f:R^n \rarr R $​  is closed if, for each$\alpha \in R$, the sublevel set 
    $$
    \{x \in 
    \mathrm{dom}f \mid f(x) \leq \alpha\}
    $$
    is closed. This is equivalent to $\mathrm{epi}f=\{ (x,t) \in R^{n+1} \mid x \in \mathrm{dom}f, f(x) \leq t \}$ is closed

# Derivatives

* **Def**

  * Suppose $f:R^n \rarr R $​  and $x \in \mathrm {int} \ \mathrm {dom}\ f$​​. The function $f$​ is **differentiable**( 可微的 ) at $x$​​ if there exists a matrix $Df(x) \in R^{m \times n}$​​ that satisfies
    $$
    \lim\limits_{z \in \mathrm{dom}f, z \neq x, z\rarr x} \frac {||f(z)-f(x)-Df(x)(z-x)||_2}{||z-x||_2}=0
    $$
    in which case we refer to $Df(x)$ **derivative** (or Jacobian) of $f$ at $x$

* $f$ is **differentiable** if $\mathrm{dom}f$  is open, and it is differentiable at every point

---

* **Def**

  * The affine function( 仿射函数 ) of $z$​ given by
    $$
    f(x) + Df(x)(z-x)
    $$
    is called the **first-order approximation** of $f$​ at (or near)  $x$
    $$
    Df(x)_{ij}= \frac{\partial f_i(x)}{\partial x_j} , i=1,\dots,m,j=1,\dots,n
    $$
    

## Gradient

* When *f* is real-valued (i.e., $ f:R^n \rarr R $)  the derivative $Df(x)$ is a $1 \times n$​ matrix (it is a row vector). Its transpose is called the **gradient** of the function:
  	
  $$
  \nabla f(x)=Df(x)^T
  $$
  which is a column vector (in $R^n$). Its components are the partial derivatives of 𝑓:
  $$
  \nabla f(x)_i=\frac{ \partial f(x) }{\partial x_i}, i=1,\dots,n
  $$
  
* The **first-order approximation** of $f$​​​​ at a point $x \in \mathrm {\ {int \mathrm {\ {dom  \ x}}}} $ can be expressed as ( the affine function of $z$​ )
  $$
  f(x) + \nabla f(x)^T(z-x)
  $$
  



##    常见凸函数

$$

$$

## 常见凹函数

* $log$

## 随机变量的期望

概率密度函数pdf概率质量函数pmf

## 高斯分布/正态分布

$$
x ~ N(\miu, \sigma^2)
$$

## 混合高斯分布

GMM

样本X的每个维度$X_i$服从一个高斯分布， 假设各个维度间独立同分布

那么我们有混合高斯分布$Z = {Z_1, Z_2, \dots, Z_n}$， 每次从中属性中选择一个维度，计算其高斯分布， 最后计算出所有高斯分布，线性组合起来



两步法：

## 推荐阅读

《Convex optimization》
