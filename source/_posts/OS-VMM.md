---
title: OS VMM
tags: OS Basic
categories: OS
date: 2021-11-26 21:12:17
---


Outline:

* 虚拟化CPU
* 虚拟化内存
* 总结

ref: Operating Systems Three Easy pieces

<!--more-->

# 虚拟化CPU

* VMM采用`limited directed execction`来运行虚拟机

  * 即： VMM跳转到第一条指令的地址，并让OS开始运行

* 多个虚拟机在一个CPU上`multiplexing`，需要执行`machine switch`，这类似进程的`context switch`

  * `machine switch`流程：VMM必须
    1. 保存整个OS的机器状态（ incluing registers, PC, 并且和上下文切换不同， VMM还要保存所有的特权硬件的状态 ）
    2. 恢复待运行OS的机器状态
    3. 然后跳转到待运行OS的PC

* 特权指令直接控制机器，因此VMM不允许OS直接执行特权指令。事实上VMM会先接受系统调用，然后将该系统调用**转发**给OS，后者返回后前者也随之返回。

  1. 当user program发出系统调用时，由于VMM控制了机器，因此VMM会陷入kernel mode

  2. VMM跳转到OS的`trap handler`，并让OS处理该system call
     * VMM知道OS的`trap handler`的位置，因为OS启动时会通过特权指令来安装自己的`trap handler`，因此会陷入VMM,此时VMM会记录该`trap handler`在内存中的位置

  3. OS完成后会通过`return`返回,这也是system call, 因此VMM真正从`trap`返回
     * `return`: 在X86上是`iret`

* 由于guest OS不可以无限制地访问硬件，因此它不能处于kernel mode。 一般而言，guest OS会处于某种特权更小的kernel mode

## 执行系统调用： traditional

1. 进程： 发出system call，陷入OS
2. 硬件： 切换到kernel mode,跳转到`trap handler`
   * 如前所述，OS启动时，会利用特权指令安装`trap handler`，因此硬件知道`trap handler`的地址
3. OS： 在kernel mode处理system call, 从`trap`返回
4. 硬件：切换到user mode
5. 进程：继续执行

## 执行系统调用：with  Virtualization

1. 进程： 发出system call，陷入OS
2. VMM：事实上进程陷入的是VMM, VMM将该system call转发给guest OS的`trap handler`
3. OS： 在kernel mode处理system call, 从`trap`返回（调用特权指令）
4. VMM：知道OS尝试返回，VMM真正从`trap`返回
5. 进程：继续执行

# 虚拟化内存

* OS将物理内存抽象为地址空间，使得每个进程有自己私有地址空间的假象

  * OS 页表： VPN to PFN

* VMM将机器内存抽象为物理内存，使OS有自己完全掌握机器内存的假象

  * 即： VMM管理OS的物理到机器内存映射

  * VMM页表：PFN to MFN（ 机器帧号 ）

* 硬件TLB： 当TLB未命中时，OS必须参与处理未命中



## TLB未命中流程： traditional

* OS TLB和VMM TLB都是TLB的软件管理程序，这里所指的TLB是硬件TLB

1. 进程： 从内存加载。 TLB未命中。 `TRAP`
2. OS：OS TLB 未命中处理程序：
   * 从VA提取VPN
   * 查找页表
   * 如果存在且有效，则取得PFN,更新TLB
   * 从`TRAP返回`
3. 进程： 继续执行，返回到导致`trap`的PC. 指令重试，导致TLB命中

## TLB未命中流程： with  Virtualization

* 由于VMM是机器的所有者，因此TLB未命中时， VMM会`TRAP`，它会立即跳转到OS TLB未命中处理程序。
* OS TLB查找页表，并**尝试**在TLB中安装VPN - PFN映射。 这也是一种特权指令，导致又一次`TRAP`VMM. 
* 此时，VMM给TLB事实上安装 **VPM - MFN** 映射（ 而不是 VPN - PFN映射）

----



1. 进程： 从内存加载。 TLB未命中。 `TRAP`
2. VMM ： ：事实上进程陷入的是VMM,。 VMM TLB未命中处理程序调用OS TLB 未命中处理程序
3. OS：OS TLB 未命中处理程序：
   * 从VA提取VPN
   * 查找页表
   * 如果存在且有效，则取得PFN,更新TLB，这是特权操作，导致`TRAP`
4. VMM：OS TLB陷入VMM, VMM用 VPM - MFN映射来更新TLB。 跳回OS
5. OS： 从`TRAP`返回
6. VMM：看到OS返回的特权指令， VMM真正返回
7. 进程： 继续执行，返回到导致`trap`的PC. 指令重试，导致TLB命中

## 硬件管理的TLB

之前讲的都是软件管理的TLB，之前文章提到，也有硬件管理的TLB

* 硬件管理TLB时，硬件在TLB miss时遍历页表并更新TLB ， VMM没有机会参与其中，因此无法在此时建立VPM - MFN映射
* 作为替代，VMM必须监视OS对每个页表的更改，并保留一个影子页表`shadow page table`. 它维护进程的**虚拟地址到机器地址**的映射。 每当os尝试安装进程的OS级页表时，VMM就会安装进程的影子页表，然后硬件将虚拟地址转换为机器地址，OS注意不到上述替换的发生
  * 也就是：OS页表里面存的是`VPN - MFN`映射。 硬件根据这个映射去物理内存（事实上是机器内存）寻找。 
  * 之前软件管理TLB时， `VPN - MFN`映射存在TLB上， 硬件根据这个映射去物理内存（事实上是机器内存）寻找。 

# 总结

* VMM的关键是**扩展`limited directed execction`概念，让VMM能够介入TRAP**

* VMM能够完全控制机器资源的分配方式

* 之前《现代操作系统》提到，VMM事实上**将物理资源直接分配给内存，没有任何抽象**。这话也没错。 在内存虚拟化层面，VMM偷偷把物理地址替换为了机器地址，OS确实在对物理硬件进行操作（他只是不知道这个映射; CPU虚拟化层面也类似。

  * 相比OS将物理硬件抽象为文件系统等漂亮的API, VMM仅仅将硬件资源抽象为虚拟的硬件资源，

    这两种资源使用上是一样的，因此“不是那么抽象”
