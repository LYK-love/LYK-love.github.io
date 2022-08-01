---
title: OS Page Sheduling Algorithm
tags: OS Basic
categories: Computer Science
date: 2022-04-16 23:13:46
---




Outline:

* 各种页面调度算法...

<!--more-->

# OPT算法(Belady算法)

当要调入新页面时，替换掉距现在最长时间后再访问的页

OPT是页面替换算法的理想情况，无法实现，但可以用来衡量其他算法

[![OPT](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/OPT.png)

# FIFO算法

略

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/FIFO.png)

**FIFO算法的Belady异常**：更多的页框导致了更高的缺页率，页框为3和4的时候

![Belady异常](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/Belady%E5%BC%82%E5%B8%B8.png)

# LRU算法

淘汰**最近最少用**的那一页，即那些刚被使用过的页面，可以马上还要被使用到

* LRU算法实现比较困难

[![LRU](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/LRU.png)

# LFU算法

LFU: lest frequent usage, 最不常用

1. 淘汰最近一段时间内**访问次数较少**的页面，对OPT的模拟性比LRU更好
2. 算法过程：基于时间间隔中断，并给每一页设置一个计数器，时间间隔中断发生后，所有计数器清0，每访问页1次就给计数器加1，选择计数最小的页面淘汰

# CLOCK算法

每个页面设置一个**访问位**，再将内存中的页面都通过链接指针链接成一个循环队列， 设置一个指针指向下一个换页位置



工作流程

1. 页调入内存时，其访问位置为1，指针前移（如果内存之前没有页，现在调入一页，那么指针指向下一页）
2. 访问内存的页时，无论该页的访问位是1还是0，都将其访问位置为1，指针不动（因为没有增加新页）
3. 内存已满，又有页要调入内存（即要淘汰页面）时，从指针当前指向的页开始扫描循环队列
   1. 把所遇到的引用标志位是1的页面的访问位清0并跳过
   2. 把所遇到的引用标志位是0的页面淘汰，并换页，**指针前移**



CLOCK算法的例子

![CLOCK](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/CLOCK.png)

> 灰色和星号代表1，蓝色和无星号代表0

# 局部最佳页面替换算法(MIN)

假设进程在时刻t访问某页面，如果该页面不在内存中，导致一次缺页，把该页面装入一个空闲页帧。不论发生缺页与否，算法在每一步要考虑引用串，如果该页面在时间$[t, t + \tau ]$内未被再次引用，那么就移出；否则，该页被保留在进程驻留集中

* $\tau$为一个系统常量，间隔$[t, t + \tau ]$称作滑动窗口 。下面的示例中$\tau = 3$
* 间隔是闭区间



示例，假设t0时刻内存中已有页P4， 此时进程要访问P4:

 ![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/WS.png)

* 注意， 在t时刻遇到Px，时，要将其添加到驻留集（因为滑动窗口有左闭区间t，因此t时刻遇到的页一定不会在下一时刻被淘汰），那添加到驻留集的时间肯定是下一时刻（t+1）

# 工作集置换算法(WS)

工作集算法是局部最佳页面替换算法的模拟实现，**不向前查看页面引用串，而是基于程序局部性原理向后看**

工作集也就是向后看的滑动窗口( 记为$[t-\Delta, t]$ ) 所看到的页面集合， 记为$W[t-\Delta, t]$ 

* $\Delta$是系统常量,称为"工作集窗口尺寸". 工作集中所包含的页面数目称为"工作集尺寸"
* 下面的示例中Δ=3



 ![WS](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Virtualization/WS.png)

