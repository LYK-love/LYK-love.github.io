---
title: Central Processing Units
tags: Hardware
categories: Computer Science
date: 2022-09-08 00:41:56
---


Outline:

* Basic Concepts
* ...

<!--more-->

# Basic Concepts

## CPU (Package)

* CPU:(Central Processing Unit): 中央处理单元. CPU是一个很模糊的概念, 它一般指的是“CPU package”

  * 一个CPU可以有多个物理核. 如果开启了超线程, 一个物理核可以分成n个逻辑核, n为超线程的数量
  * 举例来说, AMD的桌面级CPU[Ryzen™ 5 5600G](https://www.amd.com/zh-hans/products/apu/amd-ryzen-5-5600g)是6核12线程, 这意味着它有6个物理核, 通过超线程最大可以达到12个逻辑核

* CPU package: 就是我们通常说的CPU, 它包含了外壳( 里面是一个或多个Die )和外面的镀金针脚等. 主板上的每个CPU插槽( socket )只能接受一个CPU Package

  * 这就是CPU Package:
    ![CPU Package](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/CPU/CPU%20Package.png)

* Linux上查看CPU信息:

  ```sh
  lscpu | grep 'CPU(s)'
  ```

## CPU Core

* CPU Core: 就是CPU的物理核 ( physical core )  , 是一个完整且独立的执行单元. 有独立的电路元件以及L1,L2缓存.
* Hyper-threading( 超线程 ), aka HT: 让一个core并发的执行多个控制流( 线程 ), 也就是把一个core虚拟化为多个虚拟核( Or 逻辑核 logical core )
  * 超线程在一个逻辑核等待指令执行的间隔把时间片分配到另一个逻辑核



## CPU Die

* CPU Die:  就是一个半导体( usually silicon )片, 它包含了任意数量的core
  * CPU Die之间通过片外总线（Infinity Fabric）互联, 并且不同CPU Die上的CPU内核不能共享CPU Cache. 
    * 同一个Die内的Core也许能共享某些Cache, 这取决于具体设计
* Die是处理器在生产过程中引入的概念. 总的来说，Die或者CPU Die指的是处理器在生产过程中，从晶圆( Silicon Wafer) 上切割下来的一个个小方块( 这也是消费者看到的CPU芯片都是方形的原因 ), 在切割下来之前，每个小方块（Die）都需要经过各种加工，将电路逻辑刻到该Die上

## CPU Cache

* 一般L1、L2为每个物理核独占.

* 曾经有过L4 Cache, 是个eDRAM,(Haswell/Broadwell:在Iris系列中)

### 缓存的设计

- exclusive：L1 cahce中的内容不能包含在L2中
- strictly inclusive：L1cache的内容一定严格包含在L2中。
- Third one（没有正式名字）:不要求L1的一定包含在L2中

## Multi-core

* Multi-core: 多核处理器, 就是有多个core的CPU ( 严谨地说, 是CPU Package ), 这些核心可以在同一个Die, 也可以在不同的Die. 现代CPU一般都有多个Die.

* 如下是AMD的64核/128线程CPU EPYC , 它含有4个Die:

  ![EPYC](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/CPU/EPYC.png)

## Multi-CPU

* 有些主板支持Multi-CPU, 顾名思义也就是多个CPU. 这需要主板上有多个CPU Socket, 多个CPU通过 QPI 链路相连.
* 多CPU属于并行技术了

## 核显, APU...

参见我的 [GPU](https://lyk-love.cn/2022/08/01/GPU/) 
