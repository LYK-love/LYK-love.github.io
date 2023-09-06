---
title: How to Install Linux
tags: Linux
categories: Computer Science
date: 2023-09-07 02:34:24
---


In this tutorial, we will guide you through the steps required to  to install Linux(e.g., Ubuntu, Archlinux, Manjaro,...) on your Laptop or PC.

<!--more-->

如果你是Linux新手, 建议先根据[Install Ubuntu desktop](https://ubuntu.com/tutorials/install-ubuntu-desktop#1-overview)安装一次Ubuntu, 这篇教程写得很好, Ubuntu的安装过程也比其他distro简单许多. 直接尝试其他更复杂的distro(arch, gentoo,...)是一件吃力不讨好的事, ubuntu可以让你迅速地积累经验.

安装Linux有如下步骤:

1. Download an Linux Image. 下载你想要的Linux发行版的镜像.
2. Create a Bootable USB Disk. 使用系统盘制作工具, 将镜像写入USB stick(U盘), 将其制作为系统盘.
3. 对电脑做一些修改, 比如更改BIOS, 更改Windows(如果你电脑已经安装了Windows的话)设置等等, 以适配Linux.
4. Boot from USB flash drive. 插入U盘, 开机进入BIOS, 更改启动顺序为U盘启动. 现在开机后进入的就不再是原有的操作系统(e.g., Windows), 而是U盘中的Linux镜像
5. Installation Setup. 现在已经进入了该Linux的安装页面, 根据流程走即可.
6. Configure your Linux. 在Linux安装完成后, 安装一些常用软件以及进行一些配置(时区, 输入法, 网络, ...).

下面介绍的是在原有Windows系统的基础上如何额外安装Linux系统(即: 双系统). 这也是大多数人采用的方式. 

如果你只需要安装Linux, 那么删减一些环节即可(e.g., 不需要在windows中给linux磁盘分区.).



# Download an Linux Image

不做赘述.

# Create a Bootable USB Disk.

[-> ref](https://lyk-love.cn/2023/09/07/How-to-Create-a-Bootable-USB-Stick/)

# Some Preparations

## Disk Partition

在Windows下给要安装的Linux预留出磁盘空间.

## Modify BIOS

这里我假设你电脑的启动方式是UEFI. 事实上, 已经很少有BIOS启动的电脑了.

[->关于BIOS和UEFI的介绍](https://lyk-love.cn/2022/02/18/linux-hardware-basic/#bios-uefi)

> BIOS是写入到主板上的一个程序.
>
> 因为BIOS是写在主板里的, 一般来说不同品牌的主板也就有不同的BIOS.
>
> UEFI (Unified Extensible Firmware Interface) 是BIOS的进化版, 也称为UEFI BIOS. 现在常见的主板BIOS都是UEFI BIOS. **我们说的BIOS也一般指的是UEFI BIOS.**

插入制作好的系统盘, 按电源键开机, 在电脑logo(其实是主板logo)出现前狂按电脑进BIOS的快捷键, 进入BIOS.

常见主板的BIOS快捷键:

* 七彩虹: Del
* Dell: F2
* MSI: F12



在BIOS中, 需要更改系统的[启动顺序(BOOT SEQUENCE)](https://www.techopedia.com/definition/3326/boot-sequence#:~:text=Boot%20sequence%20is%20the%20order,to%20start%20the%20boot%20sequence.), 把插入的系统盘放到第一位(经典Kinston SanDisk....); 并且关闭Security Boot选项(位于Security之类的地方).

> Boot sequence is <u>the order in which a computer searches for nonvolatile data storage devices containing program code to load the operating system (OS)</u>. Typically, a Macintosh structure uses ROM and Windows uses BIOS to start the boot sequence. 

在最近几年(2020年以后), 许多电脑都使用NVMe协议的M.2 SSD, 这些电脑的硬盘驱动的SATA Operation很大概率是RAID(但这不意味着这些电脑真的组了RAID):

![RAID ON in BIOS](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/RAID%20ON%20in%20BIOS.png)



但许多Linux系统(e.g, Ubuntu) 都只能在AHCI下识别出来, 因此需要在BIOS中把Sata Operation从RAID改为AHCI. 

> 在Dell电脑的BIOS中, 这属于"Storage", AHCI选项名为"AHCI/SATA".

在RAID模式下, Linux无法识别并挂载硬盘, 所以会有诸如"ERROR: Failed to mount '/dev/loop0'"的报错.

在AHCI模式下, Linux可以识别硬盘; 但Windows不行, 会导致蓝屏. 解决方法很简单([->ref](https://blog.csdn.net/shenxianhui1995/article/details/86580473)):

1. 不要在BIOS中禁用Security Boot. 先开机进入windows, 在cmd中输入`msconfig`.

   ![enable AHCI on Windows_1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/enable%20AHCI%20on%20Windows_1.png)

2. 在"引导"页面将"引导选项"改为"安全引导-最小", 然后重启电脑.

   ![enable AHCI on Windows_2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/enable%20AHCI%20on%20Windows_2.png)

3. 重启时狂按快捷键进入BIOS, 将RAID改为AHCI.

4. 然后继续, 进入系统.

5. 此时就能正常启动Windows. 在Windows中, 重复刚才的操作, 把"安全引导-最小"的勾选取消, 然后重启电脑.

   ![enable AHCI on Windows_3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/enable%20AHCI%20on%20Windows_3.png)

6. 此时Windows就能正常启动了. 进入BIOS查看发现, 硬盘驱动已经设置为AHCI, 并且也已经禁用Security Boot.



## Block BitLocker

[BitLocker](https://learn.microsoft.com/en-us/windows/security/operating-system-security/data-protection/BitLocker/)是一种磁盘加密技术, 在Win10, Win11中是默认启用的. 开启BitLocker会导致Linux无法访问磁盘内容, 因此需要在Windows中先关闭BitLocker, 再进行Linux的安装.

不过很多Linux(e.g., Ubuntu)的安装程序中都会直接提示"You need to turn off BitLocker...", 因此BitLocker并不会对Linux安装产生多大干扰.

![BitLocker is enabled](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/BitLocker%20is%20enabled.png)

> From [BitLocker & Ubuntu installation](https://ubuntu.com/tutorials/install-ubuntu-desktop#13-additional-installing-ubuntu-alongside-windows-with-BitLocker):
>
> If you plan to install Ubuntu side by side with Windows, you need to take into consideration the operational setup on your computer.
>
> - If you are not using BitLocker, Ubuntu will be able to see the correct hard drive structure, including any partitions and data stored on it. This allows the guided wizard to correctly map the data, and safely make adjustments to accommodate the additional installation of Ubuntu alongside Windows.
> - If you are using BitLocker, **the hard drive contents will not be accessible**, and they will appear as random noise. This means that the Ubuntu installer cannot correctly map data, and the additional installation cannot be safely performed without data loss… Additionally, some manufacturers ship systems with BitLocker enabled but the hard drive contents not yet encrypted. In this case the Ubuntu installer will also not be able to correctly map data.



Turn off BitLocker([->ref](https://www.asus.com/support/FAQ/1047461/)):

1. Boot the computer, enter windows. 由于之前设置了优先从U盘启动, 要想启动windows, 你要么把U盘拔下来(这样就轮到windows启动), 要么在启动后的grub页面手动选择启动windows(windows启动项名为"windows boot manager").
2. In windows "settings", on the Device encryption field, set the option to **[Off]**

![Turn off BitLocker_1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/Turn%20off%20BitLocker_1.png)

2. Confirm whether you need to turn off device encryption, select **[Turn off]** to disable the device encryption function

![Turn off BitLocker_2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/How%20to%20Install%20Linux/Turn%20off%20BitLocker_2.png)



# Boot from USB flash drive

现在, 由于已经设置了从U盘启动, 并且在BIOS中做好了各种适配Linux的设置, 我们(在插入U盘的情况下)可以启动电脑, 在grub页面可以看到有多个启动项, 第一顺位是系统盘中的Linux, 之后是Windows. 选择Linux, 接下来就进入了Linux的安装程序.

# Installation Setup

不做赘述.

有几个注意点:

* 有些Linux distro需要设置分区, 其实没必要设置swap分区.
* 如果要选择安装驱动(driver), 尽量选择安装专有驱动(priority driver)而不是开源驱动(open source driver). 比如说你有NVIDIA显卡, 那么NVIDIA的官方驱动就比开源社区自己开发的驱动要好很多.

# Configure Linux

[Arch Linux 详细安装教程](https://zhuanlan.zhihu.com/p/596227524)
