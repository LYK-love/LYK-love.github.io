---
title: EulerOS
tags: Linux
date: 2022-05-05 12:49:15
---


Outline：

Introduction for EulerOS， 用于Linux考试

<!--more-->



2019年EulerOS被推送到开源社区，名为openEuler



OpenEuler是一个开源的Linux发行版，支持Arm, x86, RISC-V等多种处理器架构

OpenEuler在多核调度技术，软硬件协同、轻量级虚拟化、指令集优化和智能优化引擎等方面做了增强

所有开发者、企业、商业组织都可以使用openEuler社区版本，也可以基于社区版本 发布自己二次开发的操作系统版本



线程间通信ITC：

* 互斥机制主要通过自旋锁实现，Euler提供了NUMA感知队列自旋锁实现互斥机制，减少了NUMA体系结构中使用自旋锁的开销
* 同步机制主要使用信号量实现，Euler提供了up和down原语
* Euler还增强了两种ITC机制：
  * 共享内存
  * 消息传递



openEuler内存页相关说明

- 页表一般存储在一个地址连续的内存中，且能随机访问，以快速查找页表中相应的记录。在open Euler中，各级页表的表项大小为**8B**

- 页表的查询通常由与用的硬件内存管理单元(Memory Management Unit，MMU)快速完成，然 后交给OS完成(建表、设置基址寄存器、访存管理)

- openEuler**将标准大页封装为一个伪文件系统**(hugetlbfs)提供给用户程序申请并访问。

- 操作系统需要依据一定的页置换策略决定将哪些页进行换出，openEuler采用Least Recently Used

  (**LRU**)最近最久未使用策略实现页选择换出。

- 页在未来被访问的概率只能预测，不能精准判断



毕昇JDK:一款针对ARM优化的高性能 OpenJDK 发行版，SpecJBB 提升20%

* ARM64优化 :dmb指令消除等提升新能
* 快速序列化技术:提升序列化，反序列化性能
* GC优化 :让系统减少卡顿





鲲鹏处理器是基于ARMv8-64位RISC指令集开发的通用处理器，使用大量寄存器：通用X0 - X30( 31个， 64位 ) + 特殊寄存器 + 系统寄存器

Euler还通过插件，对鲲鹏处理器做了优化，有：

* 对称/非对称加密
* 数字签名 
* 压缩解压缩等算法，用于加速SSL/TLS应用和数据压缩
