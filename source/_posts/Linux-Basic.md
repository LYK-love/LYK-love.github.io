---
title: Linux Basic
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



BIOS是写入到主板上的一个程序。主板上还有硬件CMOS， 是记录各项硬件参数且嵌入在主板上的储存器；

* BIOS是开机时,计算机会执行的第一个程序





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



boot loader用于加载OS内核， 由于每种OS的文件系统不一致，因此每种OS都有自己的boot loader

boot loader位于MBR中，最大只有446字节

常用的boot loader是grub（version2）

## 位置

每个文件系统都会保留一块启动扇区（boot sector）来安装该OS的boot loader， **即OS都会默认安装一份boot loader到自己的文件系统中**（位于根目录所在的文件系统的boot sector）

LInux安装时，可以选择将boot loader安装到MBR，如果安装了，则MBR和boot sector都会保留一份boot loader

Windows安装时默认会将boot loader也安装到MBR

## 功能



boot loader主要功能：

* 加载内核文件：直接指向可开机的程序区段来启动OS
* 提供选项：用户可以选择不同启动选项
* 转交其他loader： 将启动管理功能**转交给其他loader**

选项功能使得我们可以**选择不同的内核来启动**，而转交功能使我们可以**加载其他地方（也就是其他boot sector）的loader**

## 多boot loader

![image-20220504012023432](/Users/lyk/Library/Application Support/typora-user-images/image-20220504012023432.png)

如上图所示，我的 MBR 使用 Linux 的 grub2 这个开机管理程序，并且里面假设已经有了三个菜 单， 第一个菜单可以直接指向 Linux 的核心文件并且直接载入核心来开机;第二个菜单可以将开机管理程 控权交给 Windows 来管理，此时 Windows 的 loader 会接管开机流程，这个时候他就能够启动 windows 了。 第三个菜单则是使用 Linux 在 boot sector 内的开机管理程序，此时进入另一个grub

## 多重系统





**windows的loader不具有转交功能**，因此不能使用windows的loader启动linux的loader，也就是说，装多系统的时候，需要先装windows，再装linux

* 前文已提到，windows的boot loader会自动覆盖MBR扇区，那么如果后安装windows，启动扇区就被覆盖为windows的loader，而它无法转交给其他loader，即无法支持多系统





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

* A Program that configures the MBR according to the configuration file. 

  

  Must be run as root with the lilo command. 



lilo command Syntax: 

* `lilo [-v] [-v] [-C config-file] [-t] `
* Configuration file: `/etc/lilo.conf`

## GRUB

目前都是grub2

grub是主流的boot loader程序，由于MBR扇区太小，最大才446字节，因此grub的配置文件没有放在MBR，而是放在`/boot/grub`

详见《GRUB》

GRUB 

* Program stored in MBR (first stage) and in /boot/grub (1.5th and second stage) 
* Understand file system structure; no need to activate a configuration as with LILO 
* Configuration file `/boot/grub/grub.conf `
* Installed in MBR with `grub-install`



# kernel

内核文件:`/boot/vmlinuz`

内核源代码：`/usr/src/linux`



# 模块

内核模块：`/lib/modules/$(uname -r)/kernel`

模块文件都以`.ko`为后缀

Linux发行版一般都会将非必要的且可以编译为模块的内核功能编译成模块， 比如各种设备驱动程序.



linux内核可以动态加载内核模块，内核接管系统后，会尝试检测硬件并**挂载根目录**，来取得内核模块，这样才能利用它们提供的设备加载功能

* 不能把`/lib`和`/`放在不同的硬盘分区
* 由于担心影响到磁盘内的文件系统，启动过程中根目录一般以只读的形式挂载
* 因此，如果遇到OS不支持的新硬件，要么重新编译内核，并加入该硬件的驱动程序源码； 要么将该硬件的驱动程序编译成模块，在启动时加载该模块

## 模块依赖

一个模块A引用另一个模块B所导出的符号，则加载模块A之前必须先加载模块B，这称为模块依赖

模块依赖关系存放在`/lib/modules/$(uname -r)/modules.dep`， 要生成该文件，需要用`depmod`

### depmod

`depmod [-adeisvV][-m <文件>][--help][模块名称]`

* 不加任何参数：分析当前内核的模块依赖(模块位于`/lib/modules/$(uname -r)/kernel`)，并重新写入`modules.dep`
* `-A`:  查找比 `modues.dep` 内还要新的模块，找到了才会更新`modules.dep`

- `-a`: 检查所有模块，如果命令中没有文件名称，这个选项默认是开启的
- `-e`: 显示出目前已加载的不可执行的模块
- `-n`: 将结果 `modules.dep` 和各种映射文件输出到标准输出( `stdout` )，而不是写到`modules.dep`

## 模块操作

### 查看模块

列出模块

```
> lsmod
Module                  Size  Used by
ip6table_filter        16384  0
ip6_tables             32768  1 ip6table_filter
xt_recent              24576  0
binfmt_misc            24576  1
```

显示内容有：

* 模块名称
* 模块大小
* 依赖该模块的模块



查看模块信息：

```
modinfo kernel_module
```

* 参数可以是模块名，也可以是模块文件名

### 加载/删除模块



加载/删除模块推荐使用：

```
modprobe [模块名]
```

* 查找`modules.dep`的内容，得到模块依赖性，并加载模块

选项有：

* 默认是加载模块

* `-c`： 列出目前系统所有的模块（信息更多）
* `-f`: 强制加载该模块
* `-r`: 删除模块



普通方法：不会分析依赖树，因此很比较麻烦

* 加载模块：`insmod [模块文件名]`
* 删除模块: `rmmod [模块名/模块文件名]`

## 模块与普通程序的区别



|          | C程序    | Linux模块          |
| -------- | -------- | ------------------ |
| 所在空间 | user mod | kernel mode        |
| 入口     | main()   | module_init()指定; |
| 出口     | 无       | module_exit()指定; |
| 运行方式 | 直接运行 | inmod              |
| 调试方式 | gdb      | kdbug, kdb, kgdb等 |
|          |          |                    |

注意点：

* 不能使用C库来开发模块 
* 没有内存保护机制
* 小内核栈
* 要考虑并发

## 模块example

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
static int __init hello_init(void) 
{
	printk(KERN_INFO "Hello world\n");
	return 0; 
}

static void __exit hello_exit(void) 
{
	printk(KERN_INFO "Goodbye world\n"); 
}

module_init(hello_init); 
module_exit(hello_exit);
```

- `static int __init hello_init(void)`
- `static void __exit hello_exit(void)`
  - Static：声明该函数作用域为当前文件，因为这种函数在特定文件之外没有其它意义
  - `__init`: 标记该函数只在初始化期间使用。模块装载后，将 该函数占用的内存空间释放
  - `–  __exit`: 标记该代码仅用于模块卸载
- Init/exit
  * 宏: `module_init`/`module_exit`
  * 声明模块初始化及清除函数所在的位置
  * 装载和卸载模块时，内核可以自动找到相应的函数
    * `module_init(hello_init); `
    * `module_exit(hello_exit);`

## 模块传参

有些模块需要传递一些参数

* 参数在模块加载时传递 

  ```
  nsmod hello.ko test=2
  ```

* 在模块代码中， 需要使用`module_param`宏来声明:  `module_param(变量名称，类型, 访问许可掩码)`

* 支持的参数类型
   Byte, short, ushort, int, uint, long, ulong, bool, charp Array (module_param_array(name, type, nump, perm))



example

```c
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h>
#include <linux/moduleparam.h>

static int test; 
module_param(test, int, 0644);//参数声明

static int __init hello_init(void) 
{
    printk(KERN_INFO “Hello world test=%d \n” , test);
    return 0;
}

static void __exit hello_exit(void) 
{
    printk(KERN_INFO "Goodbye world\n"); 
}

MODULE_LICENSE("GPL"); 
MODULE_DESCRIPTION("Test"); 
MODULE_AUTHOR("xxx"); 

module_init(hello_init); 
module_exit(hello_exit);
```





## 模块导出符号

如果一个模块需要向其他模块导出符号(方法或全局变量)，需要使用:

```c
EXPORT_SYMBOL(name); 
EXPORT_SYMBOL_GPL(name);
```

* 符号必须在模块文件的全局部分导出，不能在函数部分导出。 更多信息可参考 <linux/module.h>文件



• Modules仅可以使用由Kernel或者其他Modules导出的符号, 不能使用Libc

• `/proc/kallsyms `: 保存了所有导出的符号

## 模块通信example

本实例通过两个模块来介绍模块之间的通信。 模块add_sub提供了两个导出函数add_integer() 和sub_integer()，分别完成两个数字的加法和减 法。模块test用来调用模块add_sub提供的两个 方法，完成加法或者减法操作。

- 1.add_sub模块
- 2.test模块 • 3.编译模块



`add_sub.h`：

```c
#ifndef _ADD_SUB_H
#define _ADD_SUB_H


long add_integer(long a,longb);

long sub_integer(long a, long b) ;

#endif
```



add_sub：

```c
#include <linux/ init.h>
#include<l inux /module.h>
#include "add_sub.h"
long add_integer(int a, int b)
{
    return a+b;

}
long sub integer (int a, int b)
{
    return a-b;
}

EXPORT SYMBOL(add_integer) ;
EXPORT SYMBOL(sub_integer) ;
MODULELICENSE ("Dual BSD/GPL") ;
```



## 模块编译

Makefile:

```
obj-m := hello.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
```



Module includes more files

```
obj-m:=hello.o

hello-objs := a.o b.o
```

 

# Initial RAM Filesystem

由于内核启动时需要挂载根目录，来加载其中的设备驱动程序。 假设根目录所在的设备为SATA硬盘，linux需要SATA的驱动才能读取SATA盘并挂载根目录，可是取得SATA的驱动又需要先读取SATA盘，挂载根目录。 为了解决这个问腿，boot loader不仅会读取内核文件， 还会读取一个虚拟文件系统文件(`/boot/initramfs.img`， 名称在不同的OS中可能不同 )，该文件会被读取到内存中并解压缩成一个根目录，并提供一个程序，通过该程序来加载启动过程中所需要的内核模块（比如上文提到的SATA驱动），然后initramfs会被释放，并挂载实际的根目录文件系统，接着内核会调用systemd来开始后续的正常启动流程

* 当然你可以将必须的驱动直接编译到内核中，也就避免了上述的矛盾，不需要initramfs了



initrd:

```shell
mkinitrd /boot/initrd.img $(uname  r)
```



initramfs:

```shell
mkinitramfs  o /boot/initrd.img $(uname -r)
```



```shell
update-initramfs -u
```



# Linux设备

Linux系统将设备分为3种类型，对应三种驱动

* 字符设备 -- Character Driver
* 块设备 -- Block Driver
* 网络接口设备 -- Network Driver



## 设备驱动的加载过程

以字符设备驱动为例，它的加载过程是：

1. 申请设备号：包括主设备号码和次设备号
2. 定义文件操作结构体`file_operations`
3. 创建并初始化定义结构体cdev
   1. cdev结构体描述字符设备
   2. 该结构体是所有字符设备的抽象，其包含了大量字符设备所共有的特性。
4. 将cdev注册到系统，并和对应的设备号绑定
5. 在/dev文件系统中用mknod创建设备文件，并将该文件绑定到设备号上
   1. 设定设备号:`device=scull`
   2. 定义主设备号:`major=15`
   3. 用户可以通过访问`/dev/scull`来访问当前的驱动设备

```shell
mknod /dev/${device}0 c $major 0
```

 

## mknod



 mknod: Create block or character device special files.

  - Create a block device:
    
    ```
    sudo mknod path/to/device_file b major_device_number minor_device_number
    ```
    
  - Create a character device:
    
    ```
    sudo mknod path/to/device_file c major_device_number minor_device_number
    ```
    
  - Create a FIFO (queue) device:
    
    ```
    sudo mknod path/to/device_file p
    ```
    
  - Create a device file with default SELinux security context:
    ```
    sudo mknod -Z path/to/device_file type major_device_number minor_device_number
    ```



example:

```
mknod /dev/zero15 c 1 5
```

意思是创建一个字符型设备文件`/dev/zero15 `, 设备号为：主设备号5， 副设备号1



## 设备号



一个字符设备或者块设备都有一个主设备号和次设备号

• 主设备号和次设备号统称为设备号。 主设备号用来表示一个特定的**驱动程序**

• 次设备号用来表示使用该驱动程序的各**设备**



### 申请和释放设备号

```c
int register_chrdev_region(dev_t first, unsigned int count, char *name);
int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
void unregister_chrdev_region(dev_t first, unsigned int count);
```

## cdev结构体

在linux内核中使用cdev结构体来描述 字符设备。该结构体是所有字符设备的抽象，其包含了大量字符设备所共有的特性



cdev结构体的初始化:

```c
struct cdev *my_cdev = cdev_alloc();
my_cdev->ops = &my_fops;
void cdev_init(struct cdev *cdev, struct file_operations *fops);

struct scull_dev {
   struct scull qset *data; /* Pointer to first quantum set */
   int quantum; /* the current quantum size */
   int qset; /* the current array size */
   unsigned long size; /* amount of data stored here */
   unsigned int access_ key; /* used by sculluid and scullpriv */
   struct semaphore sem; /* mutual exclus ion semaphore */
   struct cdev cdev;/* Char device structure*/
};
```





### 设备注册

* 将设备注册到系统中:

  ```c
  int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
  ```

* 释放一个已经注册的设备:

  ```c
  void cdev_del(struct cdev *dev);
  ```

  

 

# /proc

- /proc文件系统是内核模块和系统交互的两种主要方式之一
- /proc文件系统是一个伪文件系统。
- 通过/proc，可以用标准Unix系统调用(比如open()、 read()、write()、 ioctl()等等)**访问进程地址空间**
- 用户和应用程序可以通过/proc得到系统的信息，并可以改变内核的某些参数
- 可以用于调试程序或者获取指定进程状态



* create_proc_entry(): 创建一个文件 
* proc_symlink();: 创建符号链接
* proc_mknod(): 创建设备文件
* proc_mkdir(): 创建目录
* remove_proc_entry(): 删除文件或目录



# OS启动过程

从开机到启动OS的过程为：

1. BIOS:开机时主动加载，BIOS会通过加载CMOS中的信息，得到主机的硬件配置信息（包括启动设备的查找顺序、硬盘的大小与类型、系统时间...）; 得到这些信息后，BIOS会进行启动自我检测（ Power-on Self Test, POST ）, 然后开始执行硬件的初始化、设置PnP设备，再**定义出可启动的设备顺序**，接下来开始读取启动设备的MBR，其中安装了boot loader程序

   * 这里的MBR泛指启动扇区，GPT也有MBR扇区

   

2. MBR： BIOS读取MBR，**注意，每块硬盘的第一个扇区都是MBR扇区，所以如果有多个硬盘，也就是多个启动设备的话，读取的应该是“第一个启动设备的MBR”**（ 之前已经定义好了启动设备的顺序）

4. boot loader： BIOS加载MBR的boot loader程序，该程序用于读取kernel，将kernel解压缩到内存中; boot loader同时还会读取`initramfs`来加载一些必要的驱动，并挂载根目录

   * BIOS通过硬件的INT13中断来读取MBR，因此，只要BIOS能检测到硬盘，就一定能读取MBR（其中的内容就是boot loader）
   * 内核驱动位于根目录的`/lib/modules`，则内核需要先挂载根目录才能取得这些驱动，但是内核没有驱动又无法读取硬盘、挂载根目录。 因此boot loader除了读取内核，还要读取`initramfs`，后者会加载必要的驱动，来挂载根目录

5. kernel + initramfs：kernel先通过`initramfs`来加载必要的驱动程序，挂载根文件系统，并加载其中的驱动程序，然后测试硬件，获取硬件信息，此时硬件已经准备就绪了

   * kernel使用自己的检测程序测试硬件， 不一定使用BIOS检测到的信息。这意味着内核此时已经接管BIOS的工作 

6. systemd：内核调用第一个程序`systemd`


# VFS

VFS（Virtual Filesystem Switch）：虚拟文件系统或虚拟文件系统转换，是Linux文件系统的虚拟化，位于内核态，将底层异构的文件系统转换为统一的文件系统，使得可以通过统一的Posix接口访问

* 作为文件系统的抽象，VFS只存在于内存
* VFS起源于Unix， 所以VFS适用于所有Unix like OS
* VFS的整体组织与前文提到的VVFS相同，分为超级块、inode等



![VFS Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Arch.png)

## 分层

VFS在整个Linux系统中的分层视图如下：

![VFS Layer](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Layer.png)

Linux系统的User**使用GLIBC（POSIX标准、GUN C运行时库）作为应用程序的运行时库**，然后通过OS转换为系统调用SCI（system-call interface），SCI是操作系统内核定义的系统调用接口，这层抽象允许**用户程序的I/O操作转换为内核的接口调用**。VFS提供了一个抽象层，将POSIX API接口与不同存储设备的具体接口实现进行了分离，使得底层的文件系统类型、设备类型对上层应用程序透明。

## 接口适配示例

用户写入文件时，使用POSIX标准的write接口，然后陷入kernel mode，调用`sys_write()`系统调用（属于SCI层）。然后VFS层接受到该调用，转换为对给定文件系统、给定设备的操作



![VFS Function Call workflow](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Function%20Call%20workflow.png)

## 跨设备/文件系统示例

下面中，用户通过cp命令进行文件拷贝，用户不需要关心底层文件系统的实现，只需要通过VFS抽象层实现对不同文件系统的读写操作：

![VFS example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20example.png)

## VFS支持的系统调用

上述示例中提到VFS也有自己的文件模型，用来支持操作系统的系统调用。下面是VFS抽象模型支持的所有Linux系统调用：

- 文件系统相关：mount, umount, umount2, sysfs,  statfs,  fstatfs,  fstatfs64, ustat
- 目录相关：chroot，pivot_root，chdir，fchdir，getcwd，mkdir，rmdir，getdents，getdents64，readdir，link，unlink，rename，lookup_dcookie
- 链接相关：readlink，symlink
- 文件相关：chown， fchown，lchown，chown16，fchown16，lchown16，hmod，fchmod，utime，stat，fstat，lstat，acess，oldstat，oldfstat，oldlstat，stat64，lstat64，lstat64，open，close，creat，umask，dup，dup2，fcntl， fcntl64，select，poll，truncate，ftruncate，truncate64，ftruncate64，lseek，llseek，read，write，readv，writev，sendfile，sendfile64，readahead

## VFS支持的文件系统

- Disk-based 文件系统：Ext2, ext3, ReiserFS，Sysv, UFS, MINIX, VxFS，VFAT, NTFS，ISO9660 CD-ROM, UDF DVD，HPFS, HFS, AFFS, ADFS,
- Network 文件系统：NFS, Coda, AFS, CIFS, NCP
- 特殊文件系统：/proc，/tmpfs等



# Linux目录结构

* `/bin`:系统的二进制文件，比如各种命令
* `/boot`： 包含了启动所需的文件，如boot loader
* `/dev`:  设备对应的虚拟文件
* `/etc`: 系统和软件的配置文件
* `/lib`： 必要的共享库文件和内核模块
* `/media`: 外部设备通用挂载点的父目录
* `/mnt`: 临时文件系统的挂载点的父目录
* `/opt`：额外的软件包安装目录
* `/sbin`:只有管理员可以使用的命令的二进制文件，是与系统相关的命令，如`reboot`,`shutdown`等
* `/srv`: 系统提供的有关服务的数据
* `/usr`: Unix System Resources, 用于存放共享、只读的数据，子目录包括`/bin`, `/etc`, `/lib`, `/tmp`等，与根目录下的同名目录相比，`/usr`下的目录的数据是用于用户安装的软件的，而不是系统自带的。 还有`/include`, `/src`等目录，存放系统编程所需的头文件和源码等
* `/home`: 用户的家目录的父目录
* `/root`: root用户的家目录

# 包管理工具

以`apt-get`为例，Ubuntu采用集中式软件仓库，`apt`从`/etc/apt/sources.list`中找到镜像站点地址, 从`package.gz`中获取所有包信息。 `apt`在本地存有一份软件包的信息索引，可以检测软件列表和软件依赖

apt在安装时安装软件和相应依赖

# File System

## Windows

普通磁盘：

* NTFS

* 比NTFS更早：fat32（磁盘最大32G,单个文件最大4G）, fat16



U盘：exfat

## Linux

ext1,2,3,4



如果不指定挂载，那么子目录就在父目录所在的分区上
