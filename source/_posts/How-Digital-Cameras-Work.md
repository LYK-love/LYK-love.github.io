---
title: How Digital Cameras Work
categories: Potpourri
mathjax: true
date: 2022-08-21 18:48:46
tags:
---




Outline:

* Pixel's Color
* Bayer Array
* Interpolation/Approximation
* Other applications of interpolation

<!--more-->

# Pixel's Color

在[Resolution on Screen](https://lyk-love.cn/2022/08/14/Resolution-on-Screen/#more)中, 我介绍了Pixel的概念. 我们也知道颜色是由红, 绿, 蓝 三原色组成的:

![read, green, blue](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/red%2C%20green%2C%20blue.png)

每个像素都有颜色和亮度. 但是感光元件只能衡量亮度, 无法衡量光的波长(颜色), 要想感知色彩，需要在每个感光元件前加滤色片( filter ), 滤色片是**单色**的.

感光元件的材料有CCD (charge coupled device), and CMOS (complementary metal oxide semiconductor )



* 对于显示屏来说, 每个像素(感光元件)都是由三个红, 绿, 蓝的单色子像素(子感光元件)组成的. 

* 数码图像和显示器一样, 每个像素也由三个单色的子像素构成

* 对于相机来说, 每个像素只是**单色**的, 缺失的另两种颜色从邻居“借来”
  * 照理来说可以像显示器一样, 将三个不同颜色的像素作为子像素合并为一个像素. 但是这样做效率很低, 对于相机而言不可接受.
  * 上面说法有个前提, 那就是感光元件使用Bayer Array.

# Bayer Array

## Uneven Distribution of Filters

相机的每个像素都有一个单色对Filter. 令人惊讶的是, **Filter的数量是不均匀的**.

其实, 人眼对于色彩的感知是不均匀的. 人眼的锥体( 大概6 million )有50%对绿色敏感, 25%对蓝色和红色敏感:

![human eyes' color sensor distribution](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/human%20eyes%27%20color%20sensor%20distribution.png)





---

[Bryce Bayer](https://en.wikipedia.org/wiki/Bryce_Bayer)根据这点发明了Bayer Array. 其中绿色Filter占50%, 红色和蓝色Filter各占25%:

![Bayer Array 1](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Bayer%20Array%201.png)

![Bayer Array 2](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Bayer%20Array%202.png)



由于简单好用, Bayer Array被绝大多数相机镜头采纳

## Mind the Gap

下面介绍一下Bayer Array的成像步骤:



这是一张花的图片:

![flower](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower.png)

---

框起来的区域:

![flower area](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20area.png)



我们要对框起来的区域使用bayer filter, 也就是单色的filter:

![flower filter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20filter.png)

---

这是输出的红色像素:

![flower filter red](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20filter%20red.png)

可以看到, 拥有红色Filter的像素大概占50%

---

这是绿色像素:

![flower filter green](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20filter%20green.png)

大概25%.

---

这是蓝色像素:

![flower filter blue](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20filter%20blue.png)

大概25%.

---

将这三张像素图拼起来, 再结合它们对应的颜色:

<center class="half">
    <img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20filter%20composed.png" width="200"/><img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Bayer%20Array%203.png" width="200"/>
</center>



就得到了:

![flower output](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/flower%20output.png)

可以看到, 结果图片还是很模糊的, 这是因为Bayer Array的像素都是单色的, 还缺失另外两原色. 对此, 我们需要采用数学手段, “猜出” 另外两原色. 

# Interpolation/Approximation

猜色问题可以抽象为: 已知两个点, 如何“猜出”它们的中间点. 这就是一个近似/插入问题.

对此, 我们有很多方法.

## Nearest-neighbor

最简单的方法就是向邻居“借”颜色. 也就是中间点的取值 == 离中间点最近的点的取值.



在1维图像上, 就是这样:

![Nearest-neighbor 1D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Nearest-neighbor%201D.png)



二维图像是这样:

![Nearest-neighbor 2D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Nearest-neighbor%202D.png)

---

对于相机的场景, 假设左图为原图, 右图采用了最近邻:

<center class="half">
    <img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20exp.png" width="200"/><img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20Nearest-neighbor.png" width="200"/>
</center>

---

最近邻的优点是没有引入任何的虚拟值. 缺点是形成的图像成块状, 不够连续.

## Linear

线性建模就是把已知点用直线连起来.



1维:

![Linear 1D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Linear%201D.png)



2维:

![Linear 2D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Linear%202D.png)

---

对于之前的相机的例子:

<center class="half">
    <img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20exp.png" width="200"/>
  <img src="https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20Linear.png" width="200"/>
</center>

---

线性近似相比最近邻, 没有那么“blocky”. 但是如果图像有sharp edge, 用线性近似会把边界模糊掉

## Quadratic

既然一阶的线性多项式效果不好, 不妨试试二阶. 二阶多项式需要三个点:

![Quadratic](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Quadratic.png)

*图中的黄色点就是二阶近似生成的*



很可惜, 二阶近似没法使用, 因为:

1. 图中可以看到, 二阶近似产生的中间值很可能过高或过低. 
2. 二阶方程没有拐点, 曲线不够平滑

## Cubic

再试试四阶近似, 这需要四个点:

![Cubic](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Cubic.png)



1维:

![Cubic 1D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Cubic%201D.png)



3阶近似的效果不错. 但由于每次只考虑4个点,  前四个点的3阶方程曲线, 和后四个点的曲线, 可能会有比较大的差异. 所以在某些情况下, 3阶近似效果一般.



## Catmull-Rom Splines

这是对3阶近似的一个改进. 依然需要4个点, 设为$x_{-1},x_0, x_1, x_2$, 假设要求$x_0, x_1$的中间点, $x_0, x_1$中间曲线的三阶近似方程为:
$$
\begin{align}
f(x) = ax^3 + bx^2 + cx + d \nonumber \\
f'(x) = 3ax^2 + 2bx + c \nonumber \\
f'(x) = 3ax^2 + 2bx + c \nonumber
\end{align}
$$
我们已经知道了$f(x_0), f(x_1)$, Catmull-Rom Splines要求设3阶方程在$x_0, x_1$处的斜率分别是直线$x_{-1}x_1, x_0x_2$的斜率. 也就是：
$$
\begin{align}
f'(x_0) = \frac {y_1 - y_{-1}}{2} \nonumber \newline
f'(x_1) = \frac {y_2 - y_0}{2} \nonumber
\end{align}
$$


![Catmull-Rom Splines](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Catmull-Rom%20Splines.png)

---

1维:

![Catmull-Rom Splines 1D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Catmull-Rom%20Splines%201D.png)

---

2维:

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Catmull-Rom%20Splines%202D.png)

---

相机:

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20exp.png)

![camera pixels Catmull-Rom Splines](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/camera%20pixels%20Catmull-Rom%20Splines.png)

可以和普通的3阶近似做对比. 

实践证明, Catmull-Rom Splines方法效果更好, 因此大部分相机都使用该算法.

# General Case

对于像素填充问题, 我们只需要在两个点之间近似一个中间点就好了. 对于更一般的情况, 即在两个点之间近似一条曲线, 我们还有更多的方法.

## Half-Cosine

取余弦函数曲线的一半, 它具有如下的“优秀”特性:

1. 平滑
2. 两端点处导数为0. 因此不会生成比已有值更高/低的近似值

![Half-Cosine](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Half-Cosine.png)



1维:

![Half-Cosine 1D](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/Half-Cosine%201D.png)



不过, 由于$\cos(\pi/4) = 1/2$, 对于求离散点的中点的情况, 其结果和线性近似一样. 所以对于相机像素的近似, 没必要用cos近似

## Smoothstep

此外还可以将高阶多项式近似继续推广. Smoothstep只用于奇数阶多项式, 为了不产生过高/过低的估计值, 它假设段点处的高阶导数为0.



假设$x \in [0,1], y \in [0,1]$, 已知$f(0), f(1)$

3阶Smoothstep就是3阶多项式, 并且其$f'(0) = f'(1) = 1$

5阶Smoothstep就是5阶多项式, 并且其$f''(0) = f''(1) = f'(0) = f'(1) = 1$

以此类推



# Other applications of interpolation

## Damping motion

前面介绍的近似方法可以应用在很多场景. 考虑一个点的直线运动的近似, 只有起点和终点两个已知点. 我们可以用:

1. 最近邻
2. 如果信息足够多的话, 已知点足够多, 比如有7个, 最近邻可以“好看”一点
3. Half Cosine
4. 3阶Smoothstep
5. 5阶Smoothstep
6. 7阶Smoothstep

![velocity exp](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/How%20Digital%20Cameras%20Work/velocity%20exp.png)

可以看出不同的近似方法的差别

# Ref

https://datagenetics.com/blog/may12018/index.html
