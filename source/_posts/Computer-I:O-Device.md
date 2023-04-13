---
title: Computer I/O Device
tags: Hardware
categories: Computer Science
date: 2022-08-06 13:11:23
---


Outline: 

* Device Controller
* Device Driver
* Driver

<!--more-->

# Device Controller

OS不会直接处理外部设备, OS处理的是device controller

  * **controller**是一个或一组**芯片**，位于南桥，向OS提供一个更“简单”（相对直接控制设备而言）的接口
    * 比如，OS可能命令“read sector 11,206 from disk 2”。controller需要将将线性的扇区号映射为实际的cylinder, sector, and head，考虑到外侧柱面比内侧多、坏的删区要被重映射为其它山区等等，这个映射会很复杂。
    * 然后controller要决定磁臂停在哪个扇区。 It has to wait until the proper sector has rotated under the head and then start reading and storing the bits as they come off the drive, removing the preamble and computing the checksum. Finally, it has to assemble the incoming bits into words and store them in memory. 
    * To do all this work, controllers often contain small embedded computers that are programmed to do their work.

# Device Register

* controller不和device直接交互, 而是和controller的寄存器们( 称为**device register** )交互. driver从OS得到指令，将其翻译后写入device registers。

* For example, a minimal disk controller might have registers for specifying the disk address, memory address, sector count, and direction (read or write). 

* To activate the controller, the driver gets a command from the operating system, then translates it into the appropriate values to write into the device registers. The collection of all the device registers forms the **I/O port** space, a subject we will come back to in Chap. 5.

* **device registers会被映射到OS的地址空间或者一个特殊的I/O port space**
  * 前者不需要特殊的I/O instructions，可以被像普通内存数据一样读写，但是消耗了地址空间（  device registers的地址无法被其他程序使用，因此是安全的 ） 
  * 后者不消耗地址空间（每个寄存器被映射为一个port address）但需要额外的instructions

# Driver

> driver talks to a controller, giving it commands and accepting responses

各种设备都暴露**物理接口**, 通过**总线**连接到计算机, 最终到达计算机的Controller被统一传输. OS在kernel层面通过driver来控制controller. 

虽然通过controller, 可以抽象数据的读取. 但是由于总线的传输需要遵守**数据传输协议**, <u>不同的数据传输协议就对应着不同的driver</u>. OS需要调用相应的driver来解析从controller读出的数据.

**因此,  OS不需要关心物理硬件(总线, 物理接口), 只需要关心driver.**

* 总线, 物理接口, 数据传输协议的内容参见[Transport Buses, Tranfer Protocals and Physical Interfaces](https://lyk-love.cn/2023/04/13/Transport-Buses-Tranfer-Protocals-and-Physical-Interfaces/)



* 每个controller厂商需要为每个操作系统提供一个driver

* driver一般在kernel mode工作

  * 由于各种driver互不相同，每个计算机需要的都不一样. 因此driver一般都以内核模块的形式安装到OS, 很少直接编译到内核中

  * 事实上也有运行在user mode的driver：

    > only very few current systems, such as MINIX 3, run all drivers in user space. Drivers in user space must be allowed to access the device in a controlled way, which is not straightforward


