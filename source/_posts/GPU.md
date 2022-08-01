---
title: GPU
tags: Hardware
categories: Computer Science
date: 2022-07-31 22:02:07
---


Outline:

* Preface：Graphic Card
* Basic Ideas
* Components of GPU

<!--more-->

# Preface：Graphic Card

[很详细的介绍显卡的文章](https://zhuanlan.zhihu.com/p/156083352)

* **显卡**( Video card、Display card、Graphics card )：由 GPU 、电路板（PCB）、显存、金手指、供电 & 显示接口以及散热等构成

![Graphic Card Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/GPU/Graphic%20Card%20Arch.png)

* 集显( 集成显卡,  严格地讲是“**集成CPU** ( Integretd CPU ),  因为不存在独立的显卡了)：指被和CPU被封装在一起的GPU。 GPU和CPU共享散热器和系统RAM。

  * 注意到集显下GPU没有独立的RAM，只能将系统RAM的一部分作为VRAM( 显而易见这很慢 )

* 独显( 独立显卡 )：顾名思义就是可插拔的独立的显卡。 通过插槽插入计算机的主板，并且通常需要比通过卡插槽提供的更多的功率。因此，它也可能有来自计算机电源的专用电源连接。



# Basic Ideas

Graphic Card( or Graphic Processing Unit, aka GPU)是专门用于绘制图像和处理图元数据的特定芯片，后来渐渐加入了其它很多功能 

* GPU是显卡的核心部分， GPU + 散热器+各种元件就构成了显卡。 当然我们经常把二者混为一谈
* 其实GPU就是为了处理图形计算任务而专门开发的硬件，是一种特殊的CPU。 电脑可以没有GPU，用普通的CPU也可以处理图形任务。 不过性能嘛。。。 给个例子， 顶级CPU 3990X 性能撕裂者勉强带得动前几代的《孤岛危机》
* 因此，GPU对于现代计算机是必要的



## GPU和CPU的区别

1. CPU被设计用于通用计算。 而GPU被设计为专门用于图形计算， 这些专用的功能会被直接集成到硬件中(起码在目前依然是这样)
2. CPU被设计为高效地执行**单线程**代码( SMT / Hyper-Threading等技术也改进了CPU的多线程能力 )； 而GPU天然被设计为高效地执行**多线程**代码。 也就是说，面对需要多线程的worload时，GPU的效率远高于CPU
3. GPU通过堆叠核心来扩展多线程性能, 所以核心数肯定比COU多。 AMD的高端CPU Epyc CPU是64核/128线程； 而Nvidia的最低端Pascal GPU就有384个内核。 

## GPU的性能度量

* GPU的性能和架构的关系很大。 因此不同架构的CPU之间，不能单凭核心数来比较性能。 

* 只有同一厂商的同一系列的GPU，才可以只用核心数比较。比如GTX 3070 和 GTX 3080 和 GTX 3080 Ti； 以及 [RX 5700 XT 和 RX 6700 XT]

# Components of GPU

GPU由核心( Core )、纹理映射单元( Texture Mapping Unit, TMU )、渲染输出( Render OutPut, ROP )和 显存( Video Random Access Memory, VRAM ) 组成。 粗略地说， GPU的最小功能单元是计算资源的块( block of computing resources )

VRAM在拙著*Computer Storage*介绍



GPU可以用如下标准来表示: [ 核心数 ]:[ 纹理映射单元数  ]:[ 渲染输出数 ]

* 比如4096:160:64

## 基本单元： SM/CU

![SM of ](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/GPU/SM%20of%20Pascal%20Multiprocessor.png)

( 这是一个AMD的Pascal Multiprocessor (SM) )



* GPU被构造成blocks of computing resources，block“可以看作”GPU的最小功能单元
  * Nvidia calls these blocks an **SM** (Streaming Multiprocessor), while AMD refers to them as a **CU**( Compute Unit ) .
  * 严格地讲，block并没有涵盖GPU所有的功能 ---- 比如 video decode engines, render outputs required for actually drawing an image on-screen, and the memory interfaces used to communicate with onboard VRAM。 

## Core

* GPU的核心( **Core** )是block的集合，比如AMD的APU( having 8 or 11 Vega Compute Units ), 这就拥有GPU的大多数功能了



* Each block contains a group of cores, a **scheduler**, a r**egister file**, **instruction cache**, **texture** and **L1 cach**e, and **texture mapping units**. 

  

## TMU

* **纹理映射单元**（**Texture mapping unit**，TMU）是GPU的一个部件，用于 纹理映射
* TMU的数量决定了GPU对于纹理映射workload的吞吐量和处理速度
* TMU曾就是一个独立的物理部件，现在已经集成到着色器中

## ROP

* 渲染输出( **Render OutPut**, ROP )（有时也称为光栅操作管线）是GPU的一个部件。 它将GPU的输出组装成图像在显示器上显示。
* ROP的数量乘以GPU的时钟速度可以控制像素填充率。ROPs的数量越多，意味着可以同时输出更多的像素。
* ROPs还可以处理抗锯齿
