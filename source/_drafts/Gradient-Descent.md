---
title: Gradient Descent
tags:
---



Given somedata points and a curve(can be randomly chosen), we can use **Gradient Descent** to modify this curve, e.g., change it's parameters, to make it "closer" to these data points.



[Gradient Descent, Step-by-Step](https://www.youtube.com/watch?v=sDv4f4s2SB8)

Given a set of datapoints $(x_1,y_1), (x_2,y_2), \cdots, (x_n,y_n)$,

we need to draw a curve( called $\hat y$ ) to best fit the data points.



A common practice is to compute the sum of the squared residual:

$f(x) = \sum_i^n (y_i - \hat y_i)^2$, where $x = (x_1, x_2, \cdots,x_n)$, $y = (y_1, y_2, \cdots,y_n)$

Through minimizing it, our curve can fit the data points better.

This function is called **loss function**.

Whatever loss function we choose, we'll have some parameters; e.g., for $f(x) = Ax + Bx^2 + \cdots $, we have parameters $A, B, \cdots$.

Note that $x$, $y$ are given. And we need to **find parameters that minimize the loss function** $f(s)$.

如果f(x)只有两个参数A, B 那我们可以想象一个3D坐标系, 其中x,y轴分别是参数A,B的值, z轴是f(x)的值. 选择不同的x,y会导致f(x)值的变化.

(其实, 由于x已经是固定的常量, 此时的f(x)更应该写成f(A,B))

我们就是要选择一组(A,B)使得f(x) 或者说f(A,B)的值最小.

![image-20231207230315962](/Users/lyk/Library/Application Support/typora-user-images/image-20231207230315962.png)

 



![image-20231207224921418](/Users/lyk/Library/Application Support/typora-user-images/image-20231207224921418.png)

![image-20231207224114344](/Users/lyk/Library/Application Support/typora-user-images/image-20231207224114344.png)





1. Romdomly select a start point for each parameter.
2. Then use chain rule to get the deriative of each parameter. These deriatives all together are called a gradient.
3. Pick random values foe the parameters.
4. Plug the parameter values into the deriavatives(ahem, the Gradient).
5. Calculate the step sizes.
6. Calculate the new papameters: new papameter = old papameter - step size.
7. Iterate step 3-6 for "the maximum number of steps".



But if the dataset if very large, i.e., data points are too many, we'll need to take **very many** step.

Thus, a new method called Stochastic Gradient Descent(SGD) is used. 暂时不知道原理.
