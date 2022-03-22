---
title: Linux Hardware Basic
tags: Linux
categories: Computer Science
date: 2022-02-18 18:47:11
---


Outline:

*  History
*  Hardware File Name
*  Partition
*  BIOS & UEFI
*  File System

介绍了Linux系统的硬件基本知识，更多内容参见我的《OS Introduction》

<!--more-->

# History

* Unix 的前身是由贝尔实验室(Bell lab.)的 Ken Thompson 利用汇编语言写成的, 后来在 1971-1973 年间由
* Dennis Ritchie 以 C 程序语言进行改写,才称为 Unix。
* 1977 年由 Bill Joy 释出 BSD (Berkeley Software Distribution),这些称为 Unix-like 的操作系统。
* 1984 年由 Andrew Tanenbaum 开始制作 Minix 操作系统,该系统可以提供原始码以及软件;
* 1984 年由 Richard Stallman 提倡 GNU 计划,倡导自由软件(Free software), 强调其软件可以『自由的取得、
* 复制、修改与再发行』 ,并规范出 GPL 授权模式, 任何 GPL(General Public License)软件均不可单纯仅贩卖
  其软件,也不可修改软件授权。
* 1991 年由芬兰人 Linus Torvalds 开发出 Linux 操作系统。简而言之, Linux 成功的地方主要在于:Minix(Unix),
  GNU, Internet, POSIX 及虚拟团队的产生。符合 Open source 理念的授权相当多,比较知名的如 Apache / BSD / GPL / MIT 等。

## Feature

* Linux是藉由 Minix 操作系统开发的,， 属于 Unix like ,没有版权纠纷
* Linux 支持 POSIX ,因此很多 Unix 上的程序可以直接在 Linux 上运作



# Hardware File Name

Linux中一切皆文件，磁盘文件名形如` /dev/sd[a-z] `，虚拟机可能会使用 `/dev/vd[a-z]` 

# Partition

分区就是对分区表进行配置，通常分区是以Cylinder为单位的『连续』磁盘空间。 现代也可以用sector为单位

分区表有两种格式： MBR, GPT





## MBR

MBR磁盘分区是一种使用最为广泛的分区结构，它也被称为DOS分区结构，但它并不仅仅应用于Windows系统平台，也应用于Linux，基于X86的UNIX等系统平台。它位于磁盘的0号扇区（一扇区等于512字节），是一个重要的扇区（简称MBR扇区）



主要分区与延伸分区最多可以有四个(硬盘的限制)
延伸分区最多只能有一个(操作系统的限制)
逻辑分区是由延伸分区持续切割出来的分区槽;
能够被格式化后,作为数据存取的分区槽为主要分区与逻辑分区。延伸分区无法格式化;
逻辑分区的数量依操作系统而不同,在 Linux 系统中 SATA 硬盘已经可以突破 63 个以上的分区限制;

### 0号扇区结构

在MBR分区表中，一个分区最大的容量为2T，且每个分区的起始柱面必须在这个硬盘的前2T内。你有一个3T的硬盘，根据要求你至少要把它划分为2个分区，且最后一个分区的起始扇区要位于硬盘的前2T空间内。如果硬盘太大则必须改用GPT



标准MBR结构：

![MBR Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/Linux/%20arch)



MBR扇区(0号扇区)由四部分组成：

* 主引导记录（MBR）：一段引导代码，占MBR分区的前446字节，负责整个系统启动。如果引导代码被破坏，系统将无法启动。

* Windows磁盘签名：占引导代码后面的4字节，是Windows初始化磁盘写入的磁盘标签，如果此标签被破坏，则系统会提示“初始化磁盘”。

* MBR分区表：4个16字节的“磁盘分区表”(DPT), 可以分出四个主分区
  * 所谓的『分区』就是配置分区表
  * 可以将一个主分区作为**扩展分区**， 扩展分区可以继续分出**逻辑分区**

* MBR结束标志：占MBR扇区最后2个字节，一直为“55 AA”， 检验主引导记录是否有效

### 主分区（MBR）

分区表示例，假设该硬盘的挂载文件名为`/dev/sda `， 分区的挂载文件名为`[硬盘文件名][分区id]`

![Primary Partition Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/Linux/Primary%20Partition%20Arch.png)

分区的文件名为硬盘名 + 后缀

* 例如，上述四个主分区的挂载文件名为：

  P1:/dev/sda1
  P2:/dev/sda2
  P3:/dev/sda3
  P4:/dev/sda4



一个硬盘，只能有4个主分区， 

（恢复分区也占一个分区）

（微软引导占一个）

（微软OS占一个C盘分区）

（剩下的一个主分区可以做扩展分区，做出最多4个逻辑分区）

在这样的情况下，是没法双系统的，因为4个主分区已经用完了

* MBR用32位寻址，每个bit代表512字节，因此只能支持2T硬盘

### 扩展分区和逻辑分区

示例： 这里有两个主分区P1,P2, P2被用作扩展分区

![Extended Partion Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/Linux/Extended%20Partion%20Arch.png)





* 主分区最多有4个，为了获得更多的分区，可以将一个主分区变成**扩展分区**，在扩展分区内进行**逻辑分区**



* 利用扩展分区的第一个扇区，可以分出逻辑扇区， 逻辑分区的分区信息存放在**扩展引导记录**（**EBR**）中

  * 这里的EBR仅仅指EBR分区， 包括分区表和结束标志“55 AA”，<u>没有引导代码</u>
  * 逻辑分区位于扩展分区内，其磁柱范围也当然在扩展分区的磁柱范围内，上例中就是101-401

  

* **最多有1个扩展分区**（OS规定）



* [分区id]的前4都保留给主分区和扩展分区。 因此逻辑分区的分区id从5开始。上例中各分区文件名如下：

  > P1:/dev/sda1
  > P2:/dev/sda2
  > L1:/dev/sda5
  > L2:/dev/sda6
  > L3:/dev/sda7
  > L4:/dev/sda8
  > L5:/dev/sda9



* 逻辑分区的数量依操作系统而不同, 在 Linux 系统中 SATA 硬盘已经可以突破 63 个以上的分区限制

## GPT

全局唯一标识分区表（GUID Partition Table）

可以有很多主分区，也就不需要扩展分区和逻辑分区了



最大硬盘容量9.4ZB

 缺点是浪费更多的磁盘空间



## GPT分区表结构

简言之，前512字节保留，用于MBR。后512字节用于GPT Header，然后是分区表， 分区表在磁盘尾部又会备份一遍



![GPT Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/Linux/GPT%20Arch)



* LBA0: MBR相容区块

  前512字节（0号扇区）有个保护MBR（用于防止不识别GPT的硬盘工具错误识别并破坏硬盘中的数据），这个MBR中只有一个类型为0xEE的分区，以此来表示这块硬盘使用GPT分区表。不能识别GPT硬盘的操作系统通常会识别出一个未知类型的分区，并且拒绝对硬盘进行操作；能够识别GPT分区表的操作系统会检查保护MBR中的分区表，如果分区类型不是0xEE或者MBR分区表中有多个项，也会拒绝对硬盘进行操作



* LBA1： GPT表头记录

  GPT头位于GPT磁盘的第二个磁盘，也就是1号扇区，该扇区是在创建GPT磁盘时生成，GPT头会定义分区表的起始位置，分区表的结束位置、每个分区表项的大小、分区表项的个数及分区表的校验和等信息。



* LBA2～33： 实际记录分区信息处

  分区表位于GPT磁盘的2-33号磁盘，一共占用32个扇区，能够容纳128个分区表项。每个分区表项大小为128字节。因为每个分区表项管理一共分区，所以Windows系统允许GPT磁盘创建128个分区



* LBA34到-34： 分区区域

  GPT分区区域就是用户使用的分区，也是用户进行数据存储的区域。分区区域的起始地址和结束地址由GPT头定义。



* LBA-33~-2: 分区表备份

  

* LBA-1： GPT头备份

  GPT头有一个备份，放在GPT磁盘的最后一个扇区，但这个GPT头备份并非完全GPT头备份，某些参数有些不一样。复制的时候根据实际情况更改一下即可。

# BIOS & UEFI

计算机启动时，首先加载硬件驱动程序， 硬件驱动程序有：

* BIOS：对应分区格式MBR， 读取MBR分区
  *  BIOS模式又称为`Legacy`
* UEFI： 对应分区格式GPT， 读取EFI分区



## BIOS

![image-20220220150724579](/home/lyk/snap/typora/49/.config/Typora/typora-user-images/image-20220220150724579.png)

BIOS是写入到主板上的一个程序。主板上还有硬件CMOS， 是记录各项硬件参数且嵌入在主板上的储存器；

* BIOS是开机时,计算机会执行的第一个程序



从开机到启动OS的过程为：

1. BIOS:开机主动执行，通过CMOS中的启动设备列表,得到要启动的硬盘, 读取该硬盘的第一个扇区（MBR扇区）
2. MBR扇区:可开机硬盘的第一个扇区内的主要启动记录区块,内含开机管理程序MBR;
3. 开机管理程序(boot loader): 这里是446字节的MBR， 由LILO或GRUB设置，因此能够读取OS的核心文件。
4. 核心文件: 加载OS

可以看到boot leader这个程序很小，只有446字节，主要任务有:

* 提供选单: 用户可以选择不同的开机项目,这也是多重引导的重要功能!
* 载入核心文件: 直接指向可开机的程序区段来开始操作系统;
* 转交其他 loader:将开机管理功能**转交给其他 loader** 
  * 这意味着计算机**可以有多个boot loader**。boot leader 除了安装在MBR中的这一份，还可以安装在每个分区的启动扇区



## UEFI

UEFI (Unified Extensible Firmware Interface) 是BIOS的进化版，也称为UEFI BIOS

* UEFI对应分区格式GPT, 启动后读取EFI分区（EFI system partition， aka **ESP**）
  * EFI是UEFI的1.0版本

* UEFI用C编程，BIOS用汇编编程。 因此UEFI非常强大



BIOS缺点：

* BIOS不知道GPT,还需要GPT 提供兼容模式才能够读写这个磁盘装置
* BIOS仅为 16 位的程序，功能太简单



UEFI 可以直接取得 GPT 的分区表,但保险起见，你最好依旧拥有BIOS boot的分区槽支持, 同时,为了与 windows 兼容,并且提供其他第三方厂商所使用的 UEFI 应用程序储存的空间,你必须要格式化一个 vfat 的文件系统, 大约提供 512MB 到 1G 左右的容量,以让其他 UEFI 执行较为方便



### ESP

EFI系统分区（EFI system partition）:GPT硬盘分区模式中的系统启动分区

* FAT16或FAT32格式的物理分区，
* 其分区标识是EF (十六进制) 而非常规的0E或0C。
* 该分区在Windows操作系统下一般是不可见的。
* ESP分区是一个独立于操作系统之外的分区，操作系统被引导后就不再依赖它。分区内存放引导管理程序、驱动程序、系统维护工具等。支持 EFI 模式的电脑需要从ESP启动系统，EFI固件可从ESP加载EFI启动程序和应用程序

# boot loader

A boot loader loads and starts the Linux kernel

* Can pass boot parameters to the Linux kernel, such as **device information** 
* Can optionally load an Initial Root Disk 
* Can boot other operating systems as well 



Common Boot loaders: 

* LILO: Linux Loader 
* GRUB: Grand Unified Boot Loader 



 Generally configured in `/dev/sda`, unless other boot loader is usd（存疑）

## LILO

LILO:

* A Program that configures the MBR according to the configuration file.  Must be run as root with the lilo command. 



lilo command Syntax: 

* `lilo [-v] [-v] [-C config-file] [-t] `
* Configuration file: `/etc/lilo.conf`

## GRUB

详见《GRUB》

GRUB 

* Program stored in MBR (first stage) and in /boot/grub (1.5th and second stage) 
* Understand file system structure; no need to activate a configuration as with LILO 
* Configuration file `/boot/grub/grub.conf `
* Installed in MBR with `grub-install`



# File System

## Windows

普通磁盘：

* NTFS

* 比NTFS更早：fat32（磁盘最大32G,单个文件最大4G）, fat16



U盘：exfat

## Linux

ext1,2,3,4



如果不指定挂载，那么子目录就在父目录所在的分区上
