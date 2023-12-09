---
title: Neural Networks Basic
tags:
---



* Hidden layer.
* the base of log is e
* you can see nodes and edges are like neuron and synapses. This is the idea of "neural networks" back in 1940s.



[Neural Networks Pt. 1: Inside the Black Box](https://www.youtube.com/watch?v=CqOfi41LfDw&list=PLblh5JKOoLUICTaGLRoHQDuF_7q2GfuJF&index=74)

讲得太好了!



![image-20231207220416546](/Users/lyk/Library/Application Support/typora-user-images/image-20231207220416546.png)

Given x, y, f(x). f is the activation function.

y = f(x).

![image-20231207220518399](/Users/lyk/Library/Application Support/typora-user-images/image-20231207220518399.png)

Thus, the y-axis values of (x,f(x)) are the y-axias values of (x,y).

So we **draw the curve accdording to the activation function**.



Since all nodes (in one activation layer) share the same activation function, and they input different values(due to different weights and biases) into the dunction. We can treat this process as different activation nodes use **different parts** of x-axias of the activation function.

Then each activation node create a different curve.



![image-20231207221452560](/Users/lyk/Library/Application Support/typora-user-images/image-20231207221452560.png)



Then we add all curves together after sacaling and translating them, i.e., apply weights and biases, to get a final curve:

![image-20231207221645000](/Users/lyk/Library/Application Support/typora-user-images/image-20231207221645000.png)

![image-20231207221757265](/Users/lyk/Library/Application Support/typora-user-images/image-20231207221757265.png)



相当于每个node把activation function切一小段(切给定x取值范围的那段), 每个这样的片段就是一根更短的curve. 然后把这些curve拉伸(乘以weights)再相加形成一根curve, 把这根curve再平移(加上biases), 形成最终的curve.

最终的curve是非线性的, 可以在2-D平面上拟合任意的data points(除非违背了函数的基本单射条件), 而这些只需要weights和biases的值设置得合理就能实现.

但是, 如何设置weights和biases的值?

首先, NN的参数就是weights和biases, 所有的参数在网络创建时都会被设置一个初始值. 接着, 我们自然可以把整个NN当作一个函数$f$, 然后对所有参数(weights, biases)进行梯度下降. 但是这样做的实际复杂度很高.

在实践中, 我们依然是使用梯度下降优化参数的思想, 但是实际算法是Backpropagation.

# Backpropagation

bp从后往前更新一遍参数.

假设我们要更新最后一个参数, 也就是在bp刚开始的时候, 此时我们前面的所有参数都已经有了初始值了, 我们已经知道前面节点生成的两根曲线$f_3, f_4$, 和它们加权相加再加上b_3的新曲线 $f_3 = w_3 f_3 + w_4 f_4 + b+3$.

我们根据$f_3$和实际的data points $f$ 定义一个loss fuction$f_\text{loss}$, 然后对它的$b_3$参数进行Gradient Descent即可.
$$
\min_{b_3} f_\text{loss}
$$
这样, 我们就得到了优化后的参数$b_3$.



然后, b_3这个节点会生成一个新曲线



bp是从后往前扫一遍.

![image-20231207233135177](/Users/lyk/Library/Application Support/typora-user-images/image-20231207233135177.png)

