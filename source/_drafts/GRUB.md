---
title: GRUB
tags: 
---











。。

这篇文章对GRUB的基本概念，常用配置，以及GRUB rescue 的操作做了介绍[
Home](https://www.archlinux.org/)

- [Packages](https://www.archlinux.org/packages/)
- [Forums](https://bbs.archlinux.org/)
- [Wiki](https://wiki.archlinux.org/)
- [Bugs](https://bugs.archlinux.org/)
- [Security](https://security.archlinux.org/)
- [AUR](https://aur.archlinux.org/)
- [Download](https://www.archlinux.org/download/)

[Jump to content](https://wiki.archlinux.org/title/GRUB_(简体中文)#content)

Toggle sidebar

### Search

- [Create account](https://wiki.archlinux.org/index.php?title=Special:CreateAccount&returnto=GRUB+(简体中文))

### Personal toolsexpandedcollapsed

## Navigation menu

- [Page](https://wiki.archlinux.org/title/GRUB_(简体中文))
- [Discussion](https://wiki.archlinux.org/index.php?title=Talk:GRUB_(简体中文)&action=edit&redlink=1)

- [Read](https://wiki.archlinux.org/title/GRUB_(简体中文))
- [View source](https://wiki.archlinux.org/index.php?title=GRUB_(简体中文)&action=edit)
- [View history](https://wiki.archlinux.org/index.php?title=GRUB_(简体中文)&action=history)



# GRUB (简体中文)

**翻译状态：**本文是 [GRUB](https://wiki.archlinux.org/title/GRUB) 的[翻译](https://wiki.archlinux.org/title/ArchWiki:Translation_Team_(简体中文))。上次翻译日期：2021-12-16。如果英文版本有所[更改](https://wiki.archlinux.org/index.php?title=GRUB&diff=0&oldid=685092)，则您可以帮助同步翻译。

相关文章

- [Arch boot process (简体中文)](https://wiki.archlinux.org/title/Arch_boot_process_(简体中文))
- [Master Boot Record (简体中文)](https://wiki.archlinux.org/title/Master_Boot_Record_(简体中文))
- [GUID Partition Table (简体中文)](https://wiki.archlinux.org/title/GUID_Partition_Table_(简体中文))
- [Unified Extensible Firmware Interface (简体中文)](https://wiki.archlinux.org/title/Unified_Extensible_Firmware_Interface_(简体中文))
- [GRUB Legacy (简体中文)](https://wiki.archlinux.org/title/GRUB_Legacy_(简体中文))
- [GRUB/EFI examples (简体中文)](https://wiki.archlinux.org/title/GRUB/EFI_examples_(简体中文))
- [GRUB/Tips and tricks (简体中文)](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文))
- [Multiboot USB drive](https://wiki.archlinux.org/title/Multiboot_USB_drive)

[GRUB](https://www.gnu.org/software/grub/) ，即 GRand Unified Bootloader（大一统启动加载器），是一个 [多重启动加载器](https://wiki.archlinux.org/title/Boot_loaders_(简体中文))，承自[PUPA](https://www.nongnu.org/pupa/)项目。该项目致力于开发一个新的启动加载器来取代如今叫做[GRUB Legacy](https://wiki.archlinux.org/title/GRUB_Legacy)的启动加载器。后者已经难以维护，而 GRUB 从头重写了代码，实现了模块化和增强了移植性[[1\]](https://www.gnu.org/software/grub/grub-faq.html#q1)。 如今的 GRUB 也被称作 GRUB 2，而 GRUB Legacy 表示诸0.9x版本。

**注意：** 在整篇文章中，`*esp*`表示[EFI系统分区](https://wiki.archlinux.org/title/EFI_system_partition_(简体中文))（即 ESP）的挂载点。

## Contents



- 1BIOS 系统
  - [1.1GUID分区表 (GPT) 特殊操作](https://wiki.archlinux.org/title/GRUB_(简体中文)#GUID分区表_(GPT)_特殊操作)
  - [1.2主引导记录 (MBR) 特殊操作](https://wiki.archlinux.org/title/GRUB_(简体中文)#主引导记录_(MBR)_特殊操作)
  - [1.3安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装)
- 2UEFI 系统
  - [2.1安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装_2)
- 3配置
  - 3.1生成 grub.cfg
    - [3.1.1生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)
    - 3.1.2探测其他操作系统
      - [3.1.2.1MS Windows](https://wiki.archlinux.org/title/GRUB_(简体中文)#MS_Windows)
    - [3.1.3额外的参数](https://wiki.archlinux.org/title/GRUB_(简体中文)#额外的参数)
    - [3.1.4LVM](https://wiki.archlinux.org/title/GRUB_(简体中文)#LVM)
    - [3.1.5阵列](https://wiki.archlinux.org/title/GRUB_(简体中文)#阵列)
    - [3.1.6/boot 加密](https://wiki.archlinux.org/title/GRUB_(简体中文)#/boot_加密)
  - 3.2定制 grub.cfg
    - 3.2.1启动菜单条目示例
      - 3.2.1.1GRUB 命令
        - [3.2.1.1.1"关机" 菜单项](https://wiki.archlinux.org/title/GRUB_(简体中文)#"关机"_菜单项)
        - [3.2.1.1.2"重启" 菜单项](https://wiki.archlinux.org/title/GRUB_(简体中文)#"重启"_菜单项)
        - [3.2.1.1.3"UEFI固件设置" 菜单项](https://wiki.archlinux.org/title/GRUB_(简体中文)#"UEFI固件设置"_菜单项)
      - 3.2.1.2EFI 可执行文件
        - [3.2.1.2.1UEFI Shell](https://wiki.archlinux.org/title/GRUB_(简体中文)#UEFI_Shell)
        - [3.2.1.2.2gdisk](https://wiki.archlinux.org/title/GRUB_(简体中文)#gdisk)
        - [3.2.1.2.3Chainload 一个统一的内核镜像](https://wiki.archlinux.org/title/GRUB_(简体中文)#Chainload_一个统一的内核镜像)
      - 3.2.1.3多系统启动
        - [3.2.1.3.1GNU/Linux](https://wiki.archlinux.org/title/GRUB_(简体中文)#GNU/Linux)
        - [3.2.1.3.2UEFI/GPT 模式下安装的 Windows](https://wiki.archlinux.org/title/GRUB_(简体中文)#UEFI/GPT_模式下安装的_Windows)
        - [3.2.1.3.3BIOS/MBR 模式下安装的 Windows](https://wiki.archlinux.org/title/GRUB_(简体中文)#BIOS/MBR_模式下安装的_Windows)
      - [3.2.1.4使用标签](https://wiki.archlinux.org/title/GRUB_(简体中文)#使用标签)
- 4使用 GRUB 命令行
  - [4.1分页支持](https://wiki.archlinux.org/title/GRUB_(简体中文)#分页支持)
  - 4.2使用命令行引导操作系统
    - [4.2.1链式加载一个分区的 VBR](https://wiki.archlinux.org/title/GRUB_(简体中文)#链式加载一个分区的_VBR)
    - [4.2.2链式加载磁盘的 MBR 或未分区磁盘的 VBR](https://wiki.archlinux.org/title/GRUB_(简体中文)#链式加载磁盘的_MBR_或未分区磁盘的_VBR)
    - [4.2.3链式加载 UEFI 模式下安装的 Windows/Linux](https://wiki.archlinux.org/title/GRUB_(简体中文)#链式加载_UEFI_模式下安装的_Windows/Linux)
    - [4.2.4正常载入](https://wiki.archlinux.org/title/GRUB_(简体中文)#正常载入)
  - [4.3使用救急控制台](https://wiki.archlinux.org/title/GRUB_(简体中文)#使用救急控制台)
- [5GRUB removal](https://wiki.archlinux.org/title/GRUB_(简体中文)#GRUB_removal)
- 6疑难解答
  - [6.1不支持的文件系统](https://wiki.archlinux.org/title/GRUB_(简体中文)#不支持的文件系统)
  - [6.2Intel BIOS 不能引导 GPT](https://wiki.archlinux.org/title/GRUB_(简体中文)#Intel_BIOS_不能引导_GPT)
  - [6.3启用调试信息](https://wiki.archlinux.org/title/GRUB_(简体中文)#启用调试信息)
  - [6.4出现 “msdos-style” 错误消息](https://wiki.archlinux.org/title/GRUB_(简体中文)#出现_“msdos-style”_错误消息)
  - 6.5UEFI 异常
    - [6.5.1常见安装错误](https://wiki.archlinux.org/title/GRUB_(简体中文)#常见安装错误)
    - [6.5.2在固件启动管理器中创建一个GRUB条目](https://wiki.archlinux.org/title/GRUB_(简体中文)#在固件启动管理器中创建一个GRUB条目)
    - [6.5.3启动时进入了救急控制台](https://wiki.archlinux.org/title/GRUB_(简体中文)#启动时进入了救急控制台)
    - [6.5.4GRUB UEFI 无法载入](https://wiki.archlinux.org/title/GRUB_(简体中文)#GRUB_UEFI_无法载入)
    - [6.5.5缺省/后备启动路径](https://wiki.archlinux.org/title/GRUB_(简体中文)#缺省/后备启动路径)
  - [6.6"Invalid signature"（无效签名错误）](https://wiki.archlinux.org/title/GRUB_(简体中文)#"Invalid_signature"（无效签名错误）)
  - [6.7引导过程卡死](https://wiki.archlinux.org/title/GRUB_(简体中文)#引导过程卡死)
  - [6.8其他系统不能自动发现 Arch Linux](https://wiki.archlinux.org/title/GRUB_(简体中文)#其他系统不能自动发现_Arch_Linux)
  - [6.9在 chroot 环境下安装时遇到警告](https://wiki.archlinux.org/title/GRUB_(简体中文)#在_chroot_环境下安装时遇到警告)
  - [6.10GRUB 载入非常慢](https://wiki.archlinux.org/title/GRUB_(简体中文)#GRUB_载入非常慢)
  - [6.11error: unknown filesystem（未知文件系统错误）](https://wiki.archlinux.org/title/GRUB_(简体中文)#error:_unknown_filesystem（未知文件系统错误）)
  - [6.12grub-reboot 不能重新设定](https://wiki.archlinux.org/title/GRUB_(简体中文)#grub-reboot_不能重新设定)
  - [6.13不能在旧的 BTRFS 上进行安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#不能在旧的_BTRFS_上进行安装)
  - [6.14未找到 Windows 8/10](https://wiki.archlinux.org/title/GRUB_(简体中文)#未找到_Windows_8/10)
  - [6.15VirtualBox EFI 模式](https://wiki.archlinux.org/title/GRUB_(简体中文)#VirtualBox_EFI_模式)
  - [6.16Device /dev/xxx not initialized in udev database even after waiting 10000000 microseconds](https://wiki.archlinux.org/title/GRUB_(简体中文)#Device_/dev/xxx_not_initialized_in_udev_database_even_after_waiting_10000000_microseconds)
  - [6.17GRUB 救急与加密启动](https://wiki.archlinux.org/title/GRUB_(简体中文)#GRUB_救急与加密启动)
- [7参阅](https://wiki.archlinux.org/title/GRUB_(简体中文)#参阅)

## BIOS 系统

### GUID分区表 (GPT) 特殊操作

BIOS/[GPT](https://wiki.archlinux.org/title/GPT)配置中，必须使用 [BIOS 启动分区](https://www.gnu.org/software/grub/manual/grub/html_node/BIOS-installation.html#BIOS-installation)。GRUB将`core.img`嵌入到这个分区。

**注意：**

- 在尝试分区之前请记住不是所有的系统都支持这种分区方案，请参阅 [GUID 分区表](https://wiki.archlinux.org/title/Partitioning#GUID_Partition_Table)。
- 此额外分区只由 GRUB 在 BIOS/GPT 分区方式中使用。对于 BIOS/MBR 分区方式，GRUB 会把`core.img`放到 [MBR 后面的间隙(post-MBR)](https://wiki.archlinux.org/title/Arch_boot_process_(简体中文)#BIOS)中去。而在 GPT 分区表中是不能保证在第一个分区之前有这样一个可以使用的间隙的。
- [UEFI](https://wiki.archlinux.org/title/UEFI) 系统也不需要这额外分区，因为它不需要嵌入启动扇区。UEFI 系统需要有[EFI系统分区](https://wiki.archlinux.org/title/EFI_system_partition_(简体中文))。

安装 GRUB 前，在一个没有文件系统的磁盘上，创建一个1兆字节（使用 [fdisk](https://wiki.archlinux.org/title/Fdisk) 或 [gdisk](https://wiki.archlinux.org/title/Gdisk) 和参数`+1M`）的分区，将分区类型设置为 GUID `21686148-6449-6E6F-744E-656564454649`。

- 对于 [fdisk](https://wiki.archlinux.org/title/Fdisk)，选择分区类型 `BIOS boot`。
- 对于 [gdisk](https://wiki.archlinux.org/title/Gdisk)，选择分区类型代码 `ef02`。
- 对于 [parted](https://wiki.archlinux.org/title/Parted)， 在新创建的分区上设置/激活 `bios_grub` 标记。

这个分区可以处于磁盘的前 2TB 空间中的任意位置，但需要在安装 GRUB 之前创建好。分区建立好后，按下面的命令安装启动管理器。

第一个分区之前的空间也可以用作 BIOS 启动分区，但是这会违反 GPT 对齐规范。因为这个分区不会经常访问，所以性能的影响很小，只不过有些分区工具会发出警告。可以在 [fdisk](https://wiki.archlinux.org/title/Fdisk) 或 [gdisk](https://wiki.archlinux.org/title/Gdisk) 中创建一个从 34 扇区开始，一直到 2047扇区的分区，然后按照上述方式设置类型。为了让其它分区对齐，可以最后再创建此分区。

### 主引导记录 (MBR) 特殊操作

一般来说，如果使用兼容 DOS 的分区对齐模式，[MBR](https://wiki.archlinux.org/title/MBR) 512 字节结束位置和第一个分区之间都有 31KB 的空闲空间。不过，为了提供足够的空间嵌入 GRUB 的`core.img`文件，建议将这个空间设置为 1 到 2 MB ([FS#24103](https://bugs.archlinux.org/task/24103))。 建议使用支持 1 MB [分区对齐](https://wiki.archlinux.org/title/Partitioning#Partition_alignment)的分区软件来分区, 因为这样也能满足非 512 字节扇区磁盘分区的需求（这一点就与嵌入`core.img`没有关系了）。

### 安装

[安装](https://wiki.archlinux.org/title/Install) 软件包 [grub](https://archlinux.org/packages/?name=grub)。如果之前安装过 [grub-legacy](https://aur.archlinux.org/packages/grub-legacy/)AUR，安装完成后 [grub](https://archlinux.org/packages/?name=grub) 会取代它。然后运行

```
# grub-install --target=i386-pc /dev/sdX
```

其中 `*/dev/sdX*` 是要安装 GRUB 的**磁盘**(**不是分区**)，比如磁盘 `/dev/sda`、`/dev/nvme0n1`或者`/dev/mmcblk0`，而 **不是** 分区 `/dev/sda1`，你可以查看[Device file#Block device names](https://wiki.archlinux.org/title/Device_file#Block_device_names)来获得块设备命名方案的详细描述。

现在你需要 [生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)。

如果你的 `/boot` 使用了 [LVM](https://wiki.archlinux.org/title/LVM_(简体中文))（逻辑分卷管理器），GRUB 可以安装到多个物理磁盘上。

**提示：** 对于安装 GRUB 的其他方式，例如安装到一个U盘上，可以参考 [GRUB/Tips and tricks (简体中文)#其它安装方式](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#其它安装方式)。

`grub-install` 命令的详细信息请参考 [grub-install(8)](https://man.archlinux.org/man/grub-install.8) 和 [GRUB 手册](https://www.gnu.org/software/grub/manual/grub/html_node/BIOS-installation.html#BIOS-installation)。

## UEFI 系统

**注意：**

- 建议阅读并理解[统一可扩展固件界面 (UEFI)](https://wiki.archlinux.org/title/Unified_Extensible_Firmware_Interface_(简体中文))，[Partitioning (简体中文)#GUID 分区表](https://wiki.archlinux.org/title/Partitioning_(简体中文)#GUID_分区表) 和 [Arch boot process (简体中文)#UEFI](https://wiki.archlinux.org/title/Arch_boot_process_(简体中文)#UEFI)这几个页面。
- 使用UEFI安装时，一定要让安装介质以UEFI模式启动，否则 *efibootmgr* 将无法添加 GRUB UEFI 启动项。 但即使在 BIOS 模式工作时，安装到[后备启动路径](https://wiki.archlinux.org/title/GRUB_(简体中文)#缺省/后备启动路径)仍然可行，因为这一过程用不到 NVRAM。
- 要从一个磁盘上使用 UEFI 模式启动，磁盘上必须要先有一个 EFI 分区。按照 [EFI system partition#Check for an existing partition](https://wiki.archlinux.org/title/EFI_system_partition#Check_for_an_existing_partition) 上说的来查看你是否已经有一个 EFI 分区，如若没有，就创建一个。

### 安装

**注意：**

- 不同硬件厂商的 UEFI 实现方式不一样，下面描述的步骤应该可以在一大类 UEFI 系统上面正常应用。对于用了下面的方法却遇到问题的用户，请将在特定的硬件上所遇到的问题的细节，以及可能的解决办法分享出来。这些案例可以添加到页面 [GRUB/EFI examples (简体中文)](https://wiki.archlinux.org/title/GRUB/EFI_examples_(简体中文)) 上面。

- 本节假设您正在 x86_64 系统上安装 GRUB。对于 IA32 （32 位） UEFI 系统（不要和 32 位 CPU 相混淆）， 将`x86_64-efi`替换成`i386-efi`。

首先[安装](https://wiki.archlinux.org/title/安装)软件包 [grub](https://archlinux.org/packages/?name=grub) 和 [efibootmgr](https://archlinux.org/packages/?name=efibootmgr)。其中“GRUB”是启动引导器，“efibootmgr”被 GRUB 脚本用来将启动项写入 NVRAM。



**提示：**

确保你在安装 grub你和运行指令的系统是你想用 GRUB 引导的系统。也就是说如果你是用安装介质启动进入了安装环境中，你需要在 `chroot` 之后再运行 `grub-install`。如果因为某些原因不得不在安装的系统之外运行 `grub-install`，在后面加上 `--boot-directory=` 选项来指定挂载 `/boot` 目录的路径，例如 `--boot-directory=/mnt/boot`。



然后按照下列步骤安装 GRUB：

1. [挂载 EFI 系统分区](https://wiki.archlinux.org/title/EFI_system_partition#Mount_the_partition)，在本节之后的内容里，把 `*esp*` 替换成挂载点。
2. 选择一个启动引导器标识，这里叫做 `GRUB`。这将在 `*esp*/EFI/` 中创建一个与标识同名的目录来储存 EFI 二进制文件，而且这个名字还会在 UEFI 启动菜单中表示 GRUB 启动项。
3. 执行下面的命令来将 GRUB EFI 应用 `grubx64.efi` 安装到 `*esp*/EFI/GRUB/`，并将其模块安装到 `/boot/grub/x86_64-efi/`。

```
# grub-install --target=x86_64-efi --efi-directory=esp --bootloader-id=GRUB
```

上述安装完成后 GRUB 的主目录将位于 `/boot/grub/`。注意上述例子中，`grub-install` 还将[在固件启动管理器中创建一个条目](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#在固件启动管理器中创建_GRUB_条目)，名叫 `GRUB`。-- 然而，如果你的启动条目已满，这个命令会执行失败；你需要使用 efibootmgr 来删除不必要的条目。

在配置完成后，记得[#生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)。

**提示：** 如果你使用了 `--removable` 选项，那 GRUB 将被安装到 `*esp*/EFI/BOOT/BOOTX64.EFI` （当使用 `i386-efi` 时是 `*esp*/EFI/BOOT/BOOTIA32.EFI`），此时即使 EFI 变量被重设或者你把这个驱动器接到其他电脑上，你仍可从这个驱动器上启动。通常来说，你只要像操作 BIOS 设备一样在启动时选择这个驱动器就可以了。如果和 Windows 一起多系统启动，注意 Windows 通常会在那里安装一个 EFI 可执行程序，这只是为了重建 Windows 的 UEFI 启动项。

**注意：**

- `--efi-directory` 和 `--bootloader-id` 是 GRUB UEFI 特有的。`--efi-directory` 替代了已经废弃的 `--root-directory`。
- 您可能注意到在 `grub-install` 命令中没有一个 <device_path> 选项，例如 `/dev/sda`。事实上即使提供了 <device_path>，也会被 GRUB 安装脚本忽略，因为 UEFI 启动加载器不使用 MBR 启动代码或启动扇区。

如果遇到问题，查看 [UEFI 故障排查](https://wiki.archlinux.org/title/GRUB_(简体中文)#UEFI_异常)。参见[GRUB/Tips and tricks (简体中文)#UEFI 延伸阅读](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#UEFI_延伸阅读)。

## 配置

完成安装之后，GRUB 在每次启动的时候载入配置文件 `/boot/grub/grub.cfg`。你可以使用工具来[#生成 grub.cfg](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成_grub.cfg)，或者可以手动[#定制 grub.cfg](https://wiki.archlinux.org/title/GRUB_(简体中文)#定制_grub.cfg)。

### 生成 grub.cfg

本节只讲述如何编辑配置文件 `/etc/default/grub`。更多信息请见 [GRUB/Tips and tricks (简体中文)](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文))。

请记住，每当修改 `/etc/default/grub` 或者 `/etc/grub.d/` 中的文件之后，都需要再次[生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)。

#### 生成主配置文件

安装后,需要生成主配置文件 `/boot/grub/grub.cfg`。配置文件的生成过程受到 `/etc/default/grub` 中的选项和 `/etc/grub.d/` 下脚本的影响。

如果你没有进行额外配置，自动生成程序会在当前启动的系统的根文件系统中侦测配置文件。所以请确保系统已经启动或者已经通过 chroot 进入。

**注意：**

- 请记住，每当修改 `/etc/default/grub` 或者 `/etc/grub.d/` 中的文件之后，都需要再次生成 `/boot/grub/grub.cfg`。
- 默认的文件路径是 `/boot/grub/grub.cfg`，而非 `/boot/grub/i386-pc/grub.cfg`。
- 如果你是在 chroot 或者 systemd-nspawn 容器中运行 grub-mkconfig，可能会报 grub-probe 无法获取 "canonical path of /dev/sdaX" 错误而无法正常执行。此时可以尝试使用 arch-chroot，参见 [BBS post](https://bbs.archlinux.org/viewtopic.php?pid=1225067#p1225067)。
- 如果你在使用了 LVM 的 chroot 环境中安装 GRUB，`grub-mkconfig` 会无限期挂起。参见 [#Device /dev/xxx not initialized in udev database even after waiting 10000000 microseconds](https://wiki.archlinux.org/title/GRUB_(简体中文)#Device_/dev/xxx_not_initialized_in_udev_database_even_after_waiting_10000000_microseconds)。

使用 grub-mkconfig 工具来生成 `/boot/grub/grub.cfg`：

```
# grub-mkconfig -o /boot/grub/grub.cfg
```

自动生成脚本默认将在生成的配置文件中为所有已安装的 Arch Linux [内核](https://wiki.archlinux.org/title/Kernels_(简体中文))添加一个条目。

**提示：**

- 每次安装或者移除一个[内核](https://wiki.archlinux.org/title/Kernels_(简体中文))后，你都需要重新运行一次 grub-mkconfig 命令。
- 若要管理多个 GRUB 条目，比如既使用 [linux](https://archlinux.org/packages/?name=linux) 又使用 [linux-lts](https://archlinux.org/packages/?name=linux-lts) 内核，相关的提示可以参见 [GRUB/Tips and tricks (简体中文)#多个启动条目](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#多个启动条目)。

如果想要自动为其他操作系统添加条目，请见[#探测其他操作系统](https://wiki.archlinux.org/title/GRUB_(简体中文)#探测其他操作系统)。

如果想要添加自定义条目，你可以编辑 `/etc/grub.d/40_custom` 文件，然后重新生成 `/boot/grub/grub.cfg`。或者你可以创建 `/boot/grub/custom.cfg` 文件然后把条目添加进这里面。修改 `/boot/grub/custom.cfg` 文件后不用再运行 grub-mkconfig 程序，因为 `/etc/grub.d/41_custom` 文件已经在生成的主配置文件中添加了相关的 `source` 语句来引用 `/boot/grub/custom.cfg`。

**提示：** `/etc/grub.d/40_custom` 可以用做创建 `/etc/grub.d/*nn*_custom` 文件的模板，其中 `*nn*` 为优先级，规定脚本文件的执行顺序。而脚本文件的执行顺序决定了其所添加的条目在 GRUB 启动菜单中的位置。`*nn*` 应当比 `06` 大，以此保证重要的脚本能够优先执行。

如要参考自定义菜单条目的例子，请看[#启动菜单条目示例](https://wiki.archlinux.org/title/GRUB_(简体中文)#启动菜单条目示例)。

#### 探测其他操作系统

想要让 grub-mkconfig 探测其他已经安装的系统并自动把他们添加到启动菜单中，[安装](https://wiki.archlinux.org/title/Install) 软件包 [os-prober](https://archlinux.org/packages/?name=os-prober) 并 [挂载](https://wiki.archlinux.org/title/File_systems_(简体中文)#挂载文件系统) 包含其它系统的磁盘分区。然后重新运行 grub-mkconfig。如果你得到以下输出：`Warning: os-prober will not be executed to detect other bootable partitions`，你需要编辑`/etc/default/grub`并取消下面这一行的注释，如果没有相应注释的话就在文件末尾添加上：

```
GRUB_DISABLE_OS_PROBER=false
```

然后运行 grub-mkconfig 再试一次。

**注意：** 记得每次运行 grub-mkconfig 之前都把包含其他操作系统的分区挂载上，以免忽略了这些操作系统的启动项。

**提示：** 你可能想让grub记住你上次选择的启动项，参见[GRUB/Tips and tricks (简体中文)#调用之前的启动条目](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#调用之前的启动条目)

##### MS Windows

[os-prober](https://archlinux.org/packages/?name=os-prober) 通常能自动发现包含 Windows 的分区。当然在载入默认的 Linux 驱动的情况下，NTFS 分区也不是总能够被探测到。如果 GRUB 没能发现它，尝试安装 [NTFS-3G](https://wiki.archlinux.org/title/NTFS-3G)，然后重新挂载这个分区再试一次。

加密的 Windows 分区需要在解密之后才能挂载。对于 BitLocker，可以使用 [dislocker](https://aur.archlinux.org/packages/dislocker/)AUR。这足够 [os-prober](https://archlinux.org/packages/?name=os-prober) 来添加正确的启动条目了。

#### 额外的参数

如想为 Linux 镜像添加额外的参数，你可以在 `/etc/default/grub` 中设置 `GRUB_CMDLINE_LINUX` 和 `GRUB_CMDLINE_LINUX_DEFAULT` 变量。生成普通启动项时，这两个参数的值会合并在一起传给内核。生成 recovery 启动项时, 仅使用 `GRUB_CMDLINE_LINUX` 参数。

两个参数不是一定要一起用。例如要系统支持[休眠](https://wiki.archlinux.org/title/休眠)后恢复,可以使用 `GRUB_CMDLINE_LINUX_DEFAULT="resume=UUID=*uuid-of-swap-partition* quiet"`，其中 `*uuid-of-swap-partition*` 是你的交换分区的 [UUID](https://wiki.archlinux.org/title/Persistent_block_device_naming_(简体中文)#by-uuid)。这样在生成 recovery 启动项时，将不会启用 resume 功能，也不会有 `quiet` 参数来省略启动时的内核信息。而其他的普通启动项会包含它们。

grub-mkconfig 默认使用根文件系统的 [UUID](https://wiki.archlinux.org/title/UUID)，要禁用此设置，取消 `GRUB_DISABLE_LINUX_UUID=true` 前的注释。

要生成 GRUB recovery 启动项，需要确保在 `/etc/default/grub` 中 `GRUB_DISABLE_RECOVERY` 没有设置为 `true`。

更多信息请参考[Kernel parameters (简体中文)](https://wiki.archlinux.org/title/Kernel_parameters_(简体中文))。

#### LVM

[![Merge-arrows-2.png](https://wiki.archlinux.org/images/c/c9/Merge-arrows-2.png)](https://wiki.archlinux.org/title/File:Merge-arrows-2.png)**This article or section is a candidate for merging with [#安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装).**[![Merge-arrows-2.png](https://wiki.archlinux.org/images/c/c9/Merge-arrows-2.png)](https://wiki.archlinux.org/title/File:Merge-arrows-2.png)

**Notes:** grub-mkconfig 能自动检测是否需要 `lvm` 模块，没有必要专门在`GRUB_PRELOAD_MODULES` 中标明。将警告移动到[#安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装) & [#Installation_2](https://wiki.archlinux.org/title/GRUB_(简体中文)#Installation_2) 或创建一个[Known issues section](https://wiki.archlinux.org/title/Help:Style#"Known_issues"_section) 并在里面写明。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

**警告：** GRUB 不支持 thin-provisioned 逻辑卷。

如果你的 `/boot` 或者 `/` 分区使用了 [LVM](https://wiki.archlinux.org/title/LVM)，确保 `lvm` 模块已经预先加载好。

```
/etc/default/grub
GRUB_PRELOAD_MODULES="... lvm"
```

#### 阵列

[![Merge-arrows-2.png](https://wiki.archlinux.org/images/c/c9/Merge-arrows-2.png)](https://wiki.archlinux.org/title/File:Merge-arrows-2.png)**This article or section is a candidate for merging with [#安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装).**[![Merge-arrows-2.png](https://wiki.archlinux.org/images/c/c9/Merge-arrows-2.png)](https://wiki.archlinux.org/title/File:Merge-arrows-2.png)

**Notes:** grub-mkconfig 能自动检测是否需要 `mdraid09` 以及 `mdraid1x` 模块，不需要在 `GRUB_PRELOAD_MODULES` 里面标明。将两个 grub-install 写到一个注意事项里，然后把它移动到[#安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装)；将那些 `set root` 语句转移到 [#定制 grub.cfg](https://wiki.archlinux.org/title/GRUB_(简体中文)#定制_grub.cfg)。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

GRUB 可以很方便地操作 [RAID](https://wiki.archlinux.org/title/RAID_(简体中文)) 卷，你只需加载 GRUB 模块 `mdraid09` 或者 `mdraid1x` 就可以像其他卷一样进行操作了。

```
/etc/default/grub
GRUB_PRELOAD_MODULES="... mdraid09 mdraid1x"
```

例如 `/dev/md0` 写成：

```
set root=(md/0)
```

而 RAID 卷上的分区（如 `/dev/md0p1`）则是：

```
set root=(md/0,1)
```

如要在 `/boot` 分区使用 RAID1 时（或者 `/boot` 位于使用了 RAID1 的根分区之中）安装 GRUB，对于 BIOS 系统，直接在各个驱动器上运行 grub-install 即可，就像这样：

```
# grub-install --target=i386-pc --debug /dev/sda
# grub-install --target=i386-pc --debug /dev/sdb
```

上例中 `/boot` 所在的 RAID 1 序列位于 `/dev/sda` 和 `/dev/sdb` 上。

**注意：** GRUB 支持从 [Btrfs](https://wiki.archlinux.org/title/Btrfs) RAID 0/1/10 启动，但 **不支持** RAID 5/6。对 RAID 5/6，你可以使用 [mdadm](https://wiki.archlinux.org/title/Mdadm)，这个 GRUB 是支持的。

#### /boot 加密

GRUB 还专门支持从加密的 `/boot` 启动。这需要解锁一个 [LUKS](https://wiki.archlinux.org/title/LUKS) 块设备，来读取配置文件以及载入 [initramfs](https://wiki.archlinux.org/title/Arch_boot_process_(简体中文)#initramfs) 和[内核](https://wiki.archlinux.org/title/Kernels_(简体中文))。这个选项试图解决[未加密的 boot 分区](https://wiki.archlinux.org/title/Dm-crypt/Specialties#Securing_the_unencrypted_boot_partition)问题。

**提示：** `/boot` **不需要** 专门放到一个单独的分区，它也可以就留在系统的根目录 `/` 下面。

**警告：** GRUB 2.0.6 仅对 LUKS2 headers 提供了有限的支持，参见 [GRUB bug #55093](https://savannah.gnu.org/bugs/?55093)。

- Argon2i (*cryptsetup* default) 与 Argon2id PBKDFs 是不受支持的，但是 PBKDF2 可以.
- *grub-mkimage*/*grub-install* 不支持创建一个可以解密 LUKS2 的镜像。请查看[grub-git](https://aur.archlinux.org/packages/grub-git/)AUR下方的评论以获得详细信息。

要启用这个功能，正常使用 [LUKS](https://wiki.archlinux.org/title/LUKS) 将 `/boot` 所在的分区加密，然后在 `/etc/default/grub` 中添加如下选项：

```
/etc/default/grub
GRUB_ENABLE_CRYPTODISK=y
```

grub-install 使用这个选项来生成 `core.img`，所以在修改这个选项之后要重新[安装 grub](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装)。

如果没有进一步的修改，你需要两次输入一个密码：第一次是为了让 GRUB 在启动伊始解锁 `/boot` 的挂载点，第二次是在 initramfs 的要求下解锁根文件系统。你可以用 [keyfile](https://wiki.archlinux.org/title/Dm-crypt/Device_encryption#With_a_keyfile_embedded_in_the_initramfs) 来避免密码输入过程。

**警告：**

- 如果你想要 [生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)，确保 `/boot` 已经挂载好了。
- 为了进行与 `/boot` 的挂载点有关的系统更新，确保在进行更新之前已经对加密的 `/boot` 进行了解锁和挂载。如果使用了独立的 `/boot` 分区，这个可以通过使用 [crypttab](https://wiki.archlinux.org/title/Crypttab) 和一个 [keyfile](https://wiki.archlinux.org/title/Dm-crypt/Device_encryption#With_a_keyfile_embedded_in_the_initramfs) 在启动的时候自动完成。

**注意：**

- 如果你使用了特别的键盘映射，默认安装的 GRUB 是不知道的。这关系到如何输入密码来解锁 LUKS 块设备。请查阅 [GRUB/Tips and tricks (简体中文)#为早期启动手动配置核心映像](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#为早期启动手动配置核心映像)
- 如果你遇到问题没法显示输入密码的界面（与 cryptouuid, cryptodisk相关的错误，或者 "device not found"），可以试着重新安装 GRUB，并在 `grub-install` 命令的尾部加上 `--modules="part_gpt part_msdos"`。

**提示：** 你可以使用 [pacman hooks](https://bbs.archlinux.org/viewtopic.php?id=234607) 来在升级时涉及到 `/boot` 中的文件的时候自动挂载它。

### 定制 grub.cfg

[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)**This article or section needs expansion.**[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)

**Reason:** 添加指导如何编写一个定制的 `/boot/grub/grub.cfg`。[User:Eschwartz/Grub](https://wiki.archlinux.org/title/User:Eschwartz/Grub) 中有一个草稿可以查阅。 (Discuss in [Talk:GRUB (简体中文)#Manually generate grub.cfg](https://wiki.archlinux.org/index.php?title=Talk:GRUB_(简体中文)&action=edit&redlink=1))

这一节讲述如何在 `/boot/grub/grub.cfg` 中手工创建 GRUB 启动条目，而非使用 grub-mkconfig。

基础的 GRUB 配置文件使用如下的设置：

- `(hd*X*,*Y*)` 为磁盘 *X* 上的分区 *Y*，分区编号从 1 开始，磁盘编号从 0 开始。
- `set default=*N*` 为在用户选择时间内没有进行选择时的默认启动条目。
- `set timeout=*M*` 即在使用默认条目启动前，等待用户自行选择的时间为 *M* 秒。
- `menuentry "title" {entry options}` 为一个标题为 `title` 的启动条目。
- `set root=(hd*X*,*Y*)` 设置 `\boot` 分区，即内核和 GRUB 模块存储的位置。（`\boot` 不一定要位于一个独立的分区，可能是根分区(`/`) 下面的一个目录。）

#### 启动菜单条目示例

**提示：** 在使用由 grub-mkconfig 所生成的 `/boot/grub/grub.cfg` 时，这些启动条目仍然是可以用的。将它们添加到 `/etc/grub.d/40_custom` 中然后[重新生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)，或者将它们添加到 `/boot/grub/custom.cfg`中。

若要管理多个 GRUB 条目，比如既使用 [linux](https://archlinux.org/packages/?name=linux) 又使用 [linux-lts](https://archlinux.org/packages/?name=linux-lts) 内核，相关的提示可以参见 [GRUB/Tips and tricks (简体中文)#多个启动条目](https://wiki.archlinux.org/title/GRUB/Tips_and_tricks_(简体中文)#多个启动条目)。

对于 [Archiso](https://wiki.archlinux.org/title/Archiso) 和 [Archboot](https://wiki.archlinux.org/title/Archboot) 启动菜单条目，参见 [Multiboot USB drive#Boot entries](https://wiki.archlinux.org/title/Multiboot_USB_drive#Boot_entries).

##### GRUB 命令

###### "关机" 菜单项

```
menuentry "System shutdown" {
	echo "System shutting down..."
	halt
}
```

###### "重启" 菜单项

```
menuentry "System restart" {
	echo "System rebooting..."
	reboot
}
```

###### "UEFI固件设置" 菜单项

```
if [ ${grub_platform} == "efi" ]; then
	menuentry 'UEFI Firmware Settings' --id 'uefi-firmware' {
		fwsetup
	}
fi
```

##### EFI 可执行文件

在启用了 UEFI 模式时，GRUB 可以 chainload 其它 EFI 可执行文件。

**提示：** 如要让这些启动条目仅在 GRUB 处于 UEFI 模式的时候显示，只需把它们放到下面的 `if` 语句中：

```
if [ ${grub_platform} == "efi" ]; then
	放入仅 UEFI 显示的启动条目
fi
```

###### UEFI Shell

要启动 [UEFI Shell](https://wiki.archlinux.org/title/Unified_Extensible_Firmware_Interface_(简体中文)#UEFI_Shell)，你可以将它放在 [EFI 系统分区](https://wiki.archlinux.org/title/EFI_system_partition_(简体中文))的根目录里，然后添加如下菜单条目：

```
menuentry "UEFI Shell" {
	insmod fat
	insmod chain
	search --no-floppy --set=root --file /shellx64.efi
	chainloader /shellx64.efi
}
```

###### gdisk

下载 [gdisk EFI application](https://wiki.archlinux.org/title/Gdisk#gdisk_EFI_application) 然后复制 `gdisk_x64.efi` 到 `*esp*/EFI/tools/`。

```
menuentry "gdisk" {
	insmod fat
	insmod chain
	search --no-floppy --set=root --file /EFI/tools/gdisk_x64.efi
	chainloader /EFI/tools/gdisk_x64.efi
}
```

###### Chainload 一个统一的内核镜像

如果你有一个按照 [Secure Boot](https://wiki.archlinux.org/title/Secure_Boot) 或者其他方法生成的 *.efi* 文件，你可以把它添加到启动菜单里。例如：

```
menuentry "Arch Linux " {
	insmod fat
	insmod chain
	search --no-floppy --set=root --fs-uuid FILESYSTEM_UUID
	chainloader /EFI/Linux/Arch-linux.efi
}
```

##### 多系统启动

###### GNU/Linux

假设另一个发行版位于 `sda2`：

```
menuentry "Other Linux" {
	set root=(hd0,2)
	linux /boot/vmlinuz (add other options here as required)
	initrd /boot/initrd.img (if the other kernel uses/needs one)
}
```

或者让 GRUB 根据 UUID 或文件系统标签查找正确的分区：

```
menuentry "Other Linux" {
        # 假设 UUID 为 763A-9CB6
	search --no-floppy --set=root --fs-uuid 763A-9CB6

        # 按照 label OTHER_LINUX 来搜索（确保分区 label 是精确的）
        #search --no-floppy --set=root --label OTHER_LINUX

	linux /boot/vmlinuz （按需求在这里添加其他的选项，例如： root=UUID=763A-9CB6 ）
	initrd /boot/initrd.img （如果其他的内核需要的话）
}
```

如果其他发行版已经有一个有效的`/boot`文件夹，并安装了GRUB、`grub.cfg`、kernel和initramfs，可以指示GRUB在启动时即时加载这些其他`grub.cfg`文件。例如，对于`hd0`和第四个GPT分区：

```
menuentry "configfile hd0,gpt4"  {
    insmod part_gpt
    insmod btrfs
    insmod ext2
    set root='hd0,gpt4'
    configfile /boot/grub/grub.cfg
}
```

选择此条目时，GRUB会从另一卷加载`grub.cfg`文件并显示该菜单。在`configfile`返回后，文件中的命令所做的任何环境变量改变将不会被保留。按`Esc`返回到第一个GRUB菜单。

###### UEFI/GPT 模式下安装的 Windows

这个模式寻找 Windows 的启动加载器的位置，然后当用户选择了相应的菜单条目的时候，通过链式载入的方法在 GRUB 之后加载它。这里主要的任务是找到 EFI 系统分区然后从上面运行启动加载器。

**注意：** 这个启动项仅在 UEFI 模式下才起作用，而且 Windows 和 UEFI 的位数必须相同。如果 GRUB 是 BIOS 模式，这个方法无效。参考 [Dual boot with Windows#Windows UEFI vs BIOS limitations](https://wiki.archlinux.org/title/Dual_boot_with_Windows#Windows_UEFI_vs_BIOS_limitations) 和 [Dual boot with Windows#Bootloader UEFI vs BIOS limitations](https://wiki.archlinux.org/title/Dual_boot_with_Windows#Bootloader_UEFI_vs_BIOS_limitations)。

```
if [ "${grub_platform}" == "efi" ]; then
	menuentry "Microsoft Windows Vista/7/8/8.1 UEFI/GPT" {
		insmod part_gpt
		insmod fat
		insmod chain
		search --no-floppy --fs-uuid --set=root $hints_string $fs_uuid
		chainloader /EFI/Microsoft/Boot/bootmgfw.efi
	}
fi
```

其中 `$hints_string` 和 `$fs_uuid` 由下述两个命令得到。

`$fs_uuid` 命令检测 EFI 系统分区的 UUID：

```
# grub-probe --target=fs_uuid esp/EFI/Microsoft/Boot/bootmgfw.efi
1ce5-7f28
```

或者你可以（以 root 身份）运行 `blkid` 然后从结果中找到 EFI 系统分区的 UUID。

`$hints_string` 命令可以确定 EFI 系统分区的位置，在当前的例子中是 harddrive 0：

```
# grub-probe --target=hints_string esp/EFI/Microsoft/Boot/bootmgfw.efi
--hint-bios=hd0,gpt1 --hint-efi=hd0,gpt1 --hint-baremetal=ahci0,gpt1
```

这两个命令都是假设 Windows 使用的 ESP 是挂载在`$esp`上的。当然，Windows的 EFI 文件路径可能有变,因为这就是Windows....

###### BIOS/MBR 模式下安装的 Windows

**注意：** GRUB 支持直接启动 `bootmgr`，如今启动 BIOS/MBR 模式下安装的 Windows 时不再需要[链式加载](https://www.gnu.org/software/grub/manual/grub.html#Chain_002dloading)分区启动扇区了。

**警告：** `bootmgr` 位于**系统分区**(**system partition**)，而不是 Windows 系统所在的分区（通常为 `C:` 盘）。系统分区的[文件系统标签](https://wiki.archlinux.org/title/Persistent_block_device_naming_(简体中文)#by-label) 是 `System Reserved` 或者 `SYSTEM` 而且这个分区的容量只有大概 100 到 549 MB。详情参考 [Wikipedia:System partition and boot partition](https://en.wikipedia.org/wiki/System_partition_and_boot_partition)。

本节假设你的 Windows 分区是 `/dev/sda1`。如果分区不同，需要对每一处 `hd0,msdos1` 进行修改。

**注意：** 这些菜单条目仅在 BIOS 启动模式下可用，不能在 UEFI 模式下安装的 GRUB 上使用。参考 [Dual boot with Windows#Windows UEFI vs BIOS limitations](https://wiki.archlinux.org/title/Dual_boot_with_Windows#Windows_UEFI_vs_BIOS_limitations) 和 [Dual boot with Windows#Bootloader UEFI vs BIOS limitations](https://wiki.archlinux.org/title/Dual_boot_with_Windows#Bootloader_UEFI_vs_BIOS_limitations)。

在所有例子里，`*XXXXXXXXXXXXXXXX*`是指文件系统的 UUID，可以通过 `lsblk --fs` 命令得到。

对于 Windows Vista/7/8/8.1/10：

```
if [ "${grub_platform}" == "pc" ]; then
	menuentry "Microsoft Windows Vista/7/8/8.1/10 BIOS/MBR" {
		insmod part_msdos
		insmod ntfs
		insmod ntldr     
		search --no-floppy --fs-uuid --set=root --hint-bios=hd0,msdos1 --hint-efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1 XXXXXXXXXXXXXXXX
		ntldr /bootmgr
	}
fi
```

对于 Windows XP：

```
if [ "${grub_platform}" == "pc" ]; then
	menuentry "Microsoft Windows XP" {
		insmod part_msdos
		insmod ntfs
		insmod ntldr     
		search --no-floppy --fs-uuid --set=root --hint-bios=hd0,msdos1 --hint-efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1 XXXXXXXXXXXXXXXX
		ntldr /ntldr
	}
fi
```

**注意：** 在某些情况下，可能在安装 Windows 8 之前就已经安装了GRUB。启动 Windows 时可能会出现`\boot\bcd` 报错（错误代码为 `0xc000000f`）。要修复这个问题，可以进入 Wondows Recovery Console（安装磁盘中的 `cmd.exe`）然后运行：

```
X:\> bootrec.exe /fixboot
X:\> bootrec.exe /RebuildBcd
```

**不要** 使用 `bootrec.exe /Fixmbr`，因为那会将 GRUB 清除掉。或者你可以用 Troubleshooting 菜单里的 Boot Repair 函数，它不会清除 GRUB 而且可以修复大部分错误。而且最好是保证连接电脑的介质 **只有** 目标硬盘和你的可启动介质，如果你连接了其他的设备，Windows 很可能会没法修复启动信息。

##### 使用标签

通过使用`search`的`--label`选项，可以使用人类易于阅读的文件系统标签。首先请[确保你的文件系统有唯一标签](https://wiki.archlinux.org/title/Persistent_block_device_naming#by-label)；

然后你就可以使用标签来添加一个条目：

```
menuentry "Arch Linux, session texte" {
  search --label --set=root archroot
  linux /boot/vmlinuz-linux root=/dev/disk/by-label/archroot ro
  initrd /boot/initramfs-linux.img
}
```



## 使用 GRUB 命令行

MBR 太小,不足以存储所有的 GRUB 模组，所以 MBR 里面只有启动目录和一些很基本的命令。GRUB 的主要功能通过 `/boot/grub` 里的模组实现，按需加载。出现错误时，GRUB 可能不能引导启动（比如磁盘分区发生了变化）。这时候，一般会出现命令行界面。

GRUB 不止提供一个 shell，如果 GRUB 不能读取到启动目录配置，但是能找到磁盘，你很可能会进入 "正常" shell：

```
grub>
```

如果有更严重的问题（比如 GRUB 找不到必须的文件了），GRUB 就可能会让你进入 "救急" shell：

```
grub rescue>
```

救急模式下的 shell 是正常 shell 的一个严格的子集，其支持的功能更少。如果不幸进入了救急模式的 shell 里，首先尝试加载 normal 模块，然后启动正常 shell：

```
grub rescue> set prefix=(hdX,Y)/boot/grub
grub rescue> insmod (hdX,Y)/boot/grub/i386-pc/normal.mod
rescue:grub> normal
```

### 分页支持

GRUB 支持对长输出进行分页（比如运行 `help` 的输出）。不过只能在正常 shell 中支持，在救急 shell 中则不支持。开启分页支持需要在 GRUB 命令行中键入：

```
sh:grub> set pager=1
```

### 使用命令行引导操作系统

```
grub> 
```

可以使用 GRUB 命令行引导操作系统，一个典型的应用场景是通过“chainloading”来引导储存在一个驱动器或者分区中的 Windows 或 Linux 系统。

ChainLoading 的意思是用当前的启动加载器去载入另一个启动加载器，所以叫做**链式**加载。

要被加载的另一个启动加载器可能嵌入在一个有分区表的磁盘的头部 (MBR)，或在一个未分区磁盘或者一个分区的头部 (VBR)，也可能在使用 UEFI 的情形下是一个 EFI 可执行文件。

#### 链式加载一个分区的 VBR

```
set root=(hdX,Y)
chainloader +1
boot
```

X=0,1,2... Y=1,2,3...

比如链式加载一个位于首磁盘,首分区上的 Windows：

```
set root=(hd0,1)
chainloader +1
boot
```

同样也可以使用 GRUB 链式加载另一个分区引导扇区上的 GRUB。

#### 链式加载磁盘的 MBR 或未分区磁盘的 VBR

```
set root=hdX
chainloader +1
boot
```

#### 链式加载 UEFI 模式下安装的 Windows/Linux

```
insmod fat
set root=(hd0,gpt4)
chainloader (${root})/EFI/Microsoft/Boot/bootmgfw.efi
boot
```

`insmod fat` 用来加载 FAT 文件系统模块，以访问 EFI 系统分区上的 Windows 启动加载器。 `(hd0,gpt4)` 或 `/dev/sda4` 是该示例中的 EFI 系统分区。 `chainloader` 一行中的条目用来指定需要被链式加载的 .efi 文件。

#### 正常载入

请参考[#使用救急控制台](https://wiki.archlinux.org/title/GRUB_(简体中文)#使用救急控制台)中的例子。

### 使用救急控制台

请先阅读[#使用 GRUB 命令行](https://wiki.archlinux.org/title/GRUB_(简体中文)#使用_GRUB_命令行)。如果无法进入正常的命令行，请尝试使用 Live CD 或者其他救急磁盘引导，然后修正配置错误，重新安装 GRUB。不过有些时候我们手上没有此类救急磁盘，这时救急控制台就可以派上用场了。

GRUB 应急控制台里可用的命令有 `insmod`，`ls`，`set` 和 `unset`。这个例子里用了 `set` 和 `insmod`。`set` 用来修改变量，`insmod` 用来载入模组以添加功能。

首先，用户必须知道启动分区 (`/boot`) 所在位置（是一个独立的分区或者是根目录下的子目录），然后设置：

```
grub rescue> set prefix=(hdX,Y)/boot/grub
```

其中 X 是物理驱动器的编号，而 Y 是分区的编号。

**注意：** 如果启动分区是个独立的分区，要在路径中省略 `/boot`（例如键入 `set prefix=(hdX,Y)/grub`）。

通过加载 `linux` 模组来扩展命令行的功能：

```
grub rescue> insmod i386-pc/linux.mod
```

或者直接

```
grub rescue> insmod linux
```

这个模组会启动对我们熟悉的 `linux` 和 `initrd` 命令的支持。

比如要启动 Arch Linux：

```
set root=(hd0,5)
linux /boot/vmlinuz-linux root=/dev/sda5
initrd /boot/initramfs-linux.img
boot
```

如果 `/boot` 在单独分区上（例如在用 UEFI 的时候），适当地进行修改：

**注意：** 因为 boot 是一个单独的分区而不是根分区的一部分，你得手动把它的地址写清楚，格式和前面的 prefix 一样。

```
set root=(hd0,5)
linux (hdX,Y)/vmlinuz-linux root=/dev/sda6
initrd (hdX,Y)/initramfs-linux.img
boot
```

**注意：** 如果你在执行 `linux` 命令的时候遇到了 `error: premature end of file /YOUR_KERNEL_NAME`，你可以尝试用 `linux16` 来替代。

成功启动 Arch Linux 后，用户可以修正 `grub.cfg` 然后重新安装 GRUB。

为了完全修正错误和重新安装 GRUB，可能需要修改 `/dev/sda`。详情请参考[#安装](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装)（BIOS）或者[#安装_2](https://wiki.archlinux.org/title/GRUB_(简体中文)#安装_2)（UEFI）章节。

## GRUB removal

[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)**This article or section needs expansion.**[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)

**Reason:** 从 BIOS 启动迁移到 UEFI 不是需要移除 GRUB 的唯一例子。本节要么需要包含如何移除为 UEFI 启动安装的 GRUB，要么就应当被删除掉，因为它实在太简短了。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

在迁移到 GPT/UEFI 后，你可能想要移除 [MBR 启动代码](https://wiki.archlinux.org/title/Partitioning#Master_Boot_Record_(bootstrap_code))，只需 [使用 dd](https://wiki.archlinux.org/title/Dd#Remove_bootloader):

```
# dd if=/dev/zero of=/dev/sdX bs=440 count=1
```

## 疑难解答

### 不支持的文件系统

GRUB 不支持 [F2FS](https://wiki.archlinux.org/title/F2FS_(简体中文)) 文件系统。如果根目录分区是一个不支持的文件系统，那就需要为 `/boot` 单独分区，并使用一个支持的文件系统。某些情况下，GRUB 的开发版 [grub-git](https://aur.archlinux.org/packages/grub-git/)AUR 可能已经支持了那个文件系统。

如果将 GRUB 和一个不支持的文件系统一起用，它将无法提取到你的驱动器的 [UUID](https://wiki.archlinux.org/title/UUID)，只能使用传统的名称 `/dev/*sdXx*` 来代替，而这个名称是可能会变化的。此时你可能需要手动编辑 `/boot/grub/grub.cfg`，将 `root=/dev/*sdXx*` 改为 `root=UUID=*XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX*`。你可以使用 `blkid` 命令来获取你的设备的 UUID ，参见 [Persistent block device naming (简体中文)](https://wiki.archlinux.org/title/Persistent_block_device_naming_(简体中文))。

### Intel BIOS 不能引导 GPT

[![Tango-go-next.png](https://wiki.archlinux.org/images/f/f0/Tango-go-next.png)](https://wiki.archlinux.org/title/File:Tango-go-next.png)**This article or section is a candidate for moving to [Arch boot process#Troubleshooting](https://wiki.archlinux.org/title/Arch_boot_process#Troubleshooting).**[![Tango-go-next.png](https://wiki.archlinux.org/images/f/f0/Tango-go-next.png)](https://wiki.archlinux.org/title/File:Tango-go-next.png)

**Notes:** 这个问题不仅仅只是GRUB或者GPT分区的问题。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

[![Tango-inaccurate.png](https://wiki.archlinux.org/images/d/d6/Tango-inaccurate.png)](https://wiki.archlinux.org/title/File:Tango-inaccurate.png)**The factual accuracy of this article or section is disputed.**[![Tango-inaccurate.png](https://wiki.archlinux.org/images/d/d6/Tango-inaccurate.png)](https://wiki.archlinux.org/title/File:Tango-inaccurate.png)

**Reason:** 除非使用混合MBR，否则GPT磁盘的保护性MBR中不会有 "1007 KiB分区"，而且也没有理由认为会这样。在GPT上，默认情况下，保护性MBR中只有一个分区 --`0xEE`-- 这虽然违反了规范，但仍然可以用 "fdisk "或 "parted "标记为可启动。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

一些 Intel 的 BIOS 要求至少有一个 MBR 方案下的可启动分区，导致 GPT 方案下的启动设置无效。

可以使用（例如）fdisk 来将一个 GPT 分区标记为可启动分区（最好就设在你为 GRUB 创建的那个 1007 KB 的分区上），这样就可以绕过这个问题了。可以使用 fdisk 执行下面的命令来实现这个操作：针对目标磁盘运行 fdisk，比如 `fdisk /dev/sda`，然后按 `a` 键，按下对应的数字来选择想要设置可启动标志的分区（可能是 1 号），最后按 `w` 键，将变更写入 MBR。

**注意：** 必须使用 `fdisk` 或者类似于它的工具来设置可启动标记，而不能用 Gparted 等工具，因为它们不会在 MBR 里面设置可启动标记。

使用 cfdisk 的步骤也差不多，只需 `cfdisk /dev/sda`，在需要的硬盘上选择可启动标记（在左侧），然后保存退出。

使用最近版本的 parted，你可以使用 `disk_toggle pmbr_boot` 选项，之后检查一下那个分区的 Disk Flags 是显示为 pmbr_boot。

```
# parted /dev/sdx disk_toggle pmbr_boot
# parted /dev/sdx print
```

更多信息请参考[此处](https://www.rodsbooks.com/gdisk/bios.html)。

### 启用调试信息

**注意：** 每当你[#生成主配置文件](https://wiki.archlinux.org/title/GRUB_(简体中文)#生成主配置文件)的时候，这个设定就会被覆盖掉。

在 `grub.cfg` 中添加：

```
set pager=1
set debug=all
```

### 出现 “msdos-style” 错误消息

```
grub-setup: warn: This msdos-style partition label has no post-MBR gap; embedding will not be possible!
grub-setup: warn: Embedding is not possible. GRUB can only be installed in this setup by using blocklists.
            However, blocklists are UNRELIABLE and its use is discouraged.
grub-setup: error: If you really want blocklists, use --force.
```

这个错误可能当你在 VMware 容器里面安装 GRUB 的时候出现。请阅读[相关链接](https://bbs.archlinux.org/viewtopic.php?pid=581760#p581760)。这种情况是因为首分区直接从 MBR 后开始（即第 64 个扇区），而不是和正常的那样在 MBR 后面有 1MB（2048个扇区）的间隙。请参阅[#主引导记录 (MBR) 特殊操作](https://wiki.archlinux.org/title/GRUB_(简体中文)#主引导记录_(MBR)_特殊操作)。

### UEFI 异常

#### 常见安装错误

- 如果你在将 sysfs 或者 procfs 与 grub-install 一起使用的时候，遇到要求你必须运行 `modprobe efivarfs` 的问题，尝试 [Unified Extensible Firmware Interface (简体中文)#挂载 efivarfs](https://wiki.archlinux.org/title/Unified_Extensible_Firmware_Interface_(简体中文)#挂载_efivarfs)。
- 如果不用 `--target` 或者 `--directory` 选项，grub-install 不知道应该安装哪一个固件。此时 `grub-install` 会输出 `source_dir does not exist. Please specify --target or --directory`。
- 如果在运行 grub-install 以后，被告知你的分区不是一个 EFI 分区，那这个分区很可能不是 `Fat32`。

#### 在固件启动管理器中创建一个GRUB条目

[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)**This article or section needs expansion.**[![Tango-view-fullscreen.png](https://wiki.archlinux.org/images/3/38/Tango-view-fullscreen.png)](https://wiki.archlinux.org/title/File:Tango-view-fullscreen.png)

**Reason:** 提供一个 efibootmgr 命令。 (Discuss in [Talk:GRUB (简体中文)](https://wiki.archlinux.org/title/Talk:GRUB_(简体中文)))

`grub-install`会自动尝试在启动管理器中创建一个菜单项。如果没有，请参见[UEFI#efibootmgr](https://wiki.archlinux.org/title/UEFI#efibootmgr)，了解使用`efibootmgr`来创建菜单项的说明。问题也可能在于你没有以UEFI模式启动CD/USB，参见[UEFI#Create UEFI bootable USB from ISO](https://wiki.archlinux.org/title/UEFI#Create_UEFI_bootable_USB_from_ISO)。

#### 启动时进入了救急控制台

如果 GRUB 直接就启动到了救急控制台下，而且没报错，这可能是因为如下两种原因：

- 可能是因为 `grub.cfg` 丢失或者位置不对。如果 GRUB UEFI 安装时设定了 `--boot-directory` 参数，而 `grub.cfg` 文件却不在那里，就会发生这样的问题。
- 如果启动分区的分区号发生了变化（这个分区号会被直接编码到 `grubx64.efi` 文件中），也会出现这个问题。

#### GRUB UEFI 无法载入

下面是一个正常的 UEFI 的示例：

```
# efibootmgr -v
BootCurrent: 0000
Timeout: 3 seconds
BootOrder: 0000,0001,0002
Boot0000* GRUB HD(1,800,32000,23532fbb-1bfa-4e46-851a-b494bfe9478c)File(\EFI\GRUB\grubx64.efi)
Boot0001* Shell HD(1,800,32000,23532fbb-1bfa-4e46-851a-b494bfe9478c)File(\shellx64.efi)
Boot0002* Festplatte BIOS(2,0,00)P0: SAMSUNG HD204UI
```

如果启动后，屏幕直接变黑，几秒后就跳到了下一个启动项，根据[相关链接](https://bbs.archlinux.org/viewtopic.php?pid=981560#p981560)的说法是，将 GRUB 移动到 root 分区上可能会解决这个问题。必须先删除启动项，然后在移动 GRUB 后重建。操作之后上述命令的输出中，GRUB 条目应该像这样：

```
Boot0000* GRUB HD(1,800,32000,23532fbb-1bfa-4e46-851a-b494bfe9478c)File(\grubx64.efi)
```

#### 缺省/后备启动路径

一些 UEFI 固件在显示 UEFI NVRAM 启动条目之前，需要在一个已知的位置上有一个可启动文件。如果是这种情况， `grub-install` 会说明 `efibootmgr` 添加了一个启动 GRUB 的条目，但这个条目不会在 VisualBIOS 启动顺序选择器中显示。解决方法是把 GRUB 安装到缺省/后备启动路径当中：

```
# grub-install --target=x86_64-efi --efi-directory=esp --removable
```

或者你可以把已经安装好的 GRUB EFI 执行文件移动到缺省/后备路径中：

```
# mv esp/EFI/grub esp/EFI/BOOT
# mv esp/EFI/BOOT/grubx64.efi esp/EFI/BOOT/BOOTX64.EFI
```

### "Invalid signature"（无效签名错误）

如果在启动 Windows 时出现了 "invalid signature" 错误（比如在重新分区或者添加了新硬盘后），删除 GRUB 的设备配置，然后让它重建一个：

```
# mv /boot/grub/device.map /boot/grub/device.map-old
# grub-mkconfig -o /boot/grub/grub.cfg
```

`grub-mkconfig` 此时就应该生成了新的启动项了，包括 Windows。确认能启动成功后，再将备份文件 `/boot/grub/device.map-old` 删除。

### 引导过程卡死

如果在 GRUB 载入内核并初始化 ramdisk 后引导过程卡死了，又没有错误信息的话，请尝试移除 `add_efi_memmap` 这个内核参数。

### 其他系统不能自动发现 Arch Linux

有人发现有些发行版不能使用 `os-prober` 自动发现 Arch Linux。据说如果 `/etc/lsb-release` 文件存在的话，可以提高探测能力。这个文件和和更新工具可以在 [lsb-release](https://archlinux.org/packages/?name=lsb-release) 包中找到。

### 在 chroot 环境下安装时遇到警告

当位于 chroot 环境里，要在 LVM 系统上安装 GRUB 的时候（比如在安装系统的时候），你可能会收到一个这样的警告：

```
/run/lvm/lvmetad.socket: connect failed: No such file or directory
```

或者

```
WARNING: failed to connect to lvmetad: No such file or directory. Falling back to internal scanning.
```

这是因为在 chroot 环境里面 `/run` 是不可用的。只要每个步骤都做对了，这些警告不会影响系统启动，你可以放心继续进行下一步的系统安装。

### GRUB 载入非常慢

当磁盘空间很小的时候 GRUB 的载入时间可能会很长。如果你遇到了这样的问题，检查一下你的 `/boot` 或者 `/` 分区是不是有足够的剩余空间。

### error: unknown filesystem（未知文件系统错误）

因某些原因，GRUB 可能会不能启动并输出 `error: unknown filesystem`。如果你确定所有的 [UUID](https://wiki.archlinux.org/title/UUID) 都对了而且所有的文件系统都是有效而且被 GRUB 支持的，问题的原因可能是你的 [BIOS 启动分区](https://wiki.archlinux.org/title/GRUB_(简体中文)#GUID分区表_(GPT)_特殊操作)不在驱动器的前 2 TB 空间里 [[2\]](https://bbs.archlinux.org/viewtopic.php?id=195948)。 选择一个分区工具调整这个分区，让它完全在前 2 TB 空间中，然后重新安装和配置 GRUB。

这个错误也可能是因为一个 [ext4](https://wiki.archlinux.org/title/Ext4) 文件系统拥有 `large_dir` 特性，或者设置了 `metadata_csum_seed`。

**警告：** 当你在`/boot`中启用文件系统特性时，请确保grub支持你的 [文件系统](https://wiki.archlinux.org/title/文件系统) 特性。

### grub-reboot 不能重新设定

GRUB 好像不能写入 BTRFS 格式的根分区[[3\]](https://bbs.archlinux.org/viewtopic.php?id=166131)。如果你使用 grub-reboot 来启动到另一个启动条目，就会没法更新其 on-disk 环境。要么换一个启动条目来运行 grub-reboot（例如在不同发行版之间切换的时候），要么考虑换个文件系统。你可以通过运行 `grub-editenv create` 来重设一个 "sticky" 条目，然后在 `/etc/default/grub` 中设置 `GRUB_DEFAULT=0`（不要忘了运行 `grub-mkconfig -o /boot/grub/grub.cfg`）。

### 不能在旧的 BTRFS 上进行安装

如果一个驱动器在没有创建分区表的情形下被格式化成 BTRFS（比如 /dev/sdx)，之后又创建了一个分区表，那么会有部分 BTRFS 格式保留下来。大部分功能和操作系统都不会注意这个，但是 GRUB 则无法安装，即使使用 --force 参数也不行。

```
# grub-install: warning: Attempting to install GRUB to a disk with multiple partition labels. This is not supported yet..
# grub-install: error: filesystem `btrfs' does not support blocklists.
```

你可以把整个驱动器置零来解决问题，但还有一个办法既简单又能保留你的数据，那就是用 `wipefs -o 0x10040 /dev/sdx` 命令来擦掉 BTRFS superblock。

### 未找到 Windows 8/10

Windows 8/10 如果启用了 "Hiberboot", "Hybrid Boot" 或 "Fast Boot"，可能会导致 Windows 分区无法被挂载。所以 `grub-mkconfig` 无法找到安装的 Windows。在 Windows 里禁用 Hiberboot，然后它就可以被添加到 GRUB 菜单了。

### VirtualBox EFI 模式

对于Virtual Box 6.1及之前的版本，将 GRUB 安装到[缺省/后备启动路径](https://wiki.archlinux.org/title/GRUB_(简体中文)#缺省/后备启动路径)。

也可参考 [VirtualBox (简体中文)#以 EFI 模式安装](https://wiki.archlinux.org/title/VirtualBox_(简体中文)#以_EFI_模式安装)。

### Device /dev/xxx not initialized in udev database even after waiting 10000000 microseconds

如果 grub-mkconfig 卡住然后显示如下错误信息：

```
WARNING: Device /dev/*xxx* not initialized in udev database even after waiting 10000000 microseconds
```

你需要使用下列命令为 chroot 环境提供 `/run/lvm/` 访问支持：

```
# mkdir /mnt/hostlvm
# mount --bind /run/lvm /mnt/hostlvm
# arch-chroot /mnt
# ln -s /hostlvm /run/lvm
```

参见 [FS#61040](https://bugs.archlinux.org/task/61040) 和 [workaround](https://bbs.archlinux.org/viewtopic.php?pid=1820949#p1820949)。

### GRUB 救急与加密启动

在使用加密启动，而你没法键入正确的密码的时候，就会进入 GRUB 救急命令行。

这个救急命令行只有有限的功能，可以使用下面的命令来完成启动：

```
grub rescue> cryptomount <分区>
grub rescue> insmod normal
grub rescue> normal
```

更好的介绍参见 [这个帖子](https://blog.stigok.com/2017/12/29/decrypt-and-mount-luks-disk-from-grub-rescue-mode.html)。

## 参阅

- [Wikipedia:GNU GRUB](https://en.wikipedia.org/wiki/GNU_GRUB)
- [官方 GRUB 手册](https://www.gnu.org/software/grub/manual/grub.html)
- [GRUB 的 Ubuntu wiki 页面](https://help.ubuntu.com/community/Grub2)
- [描述为 UEFI 系统编译的 GRUB wiki 页面](https://help.ubuntu.com/community/UEFIBooting)
- [Wikipedia:BIOS Boot partition](https://en.wikipedia.org/wiki/BIOS_Boot_partition)
- [怎样配置 GRUB](https://web.archive.org/web/20160424042444/http://members.iinet.net/~herman546/p20/GRUB2 Configuration File Commands.html#Editing_etcgrub.d05_debian_theme)
- [Detecting efi files and booting them from grub](https://archived.forum.manjaro.org/t/detecting-efi-files-and-booting-them-from-grub/38083)

[Categories](https://wiki.archlinux.org/title/Special:Categories): 

- [Boot loaders (简体中文)](https://wiki.archlinux.org/title/Category:Boot_loaders_(简体中文))
- [GNU (简体中文)](https://wiki.archlinux.org/title/Category:GNU_(简体中文))

- This page was last edited on 7 February 2022, at 19:52.
- Content is available under [GNU Free Documentation License 1.3 or later](http://www.gnu.org/copyleft/fdl.html) unless otherwise noted.

- [Privacy policy](https://terms.archlinux.org/docs/privacy-policy/)
- [About ArchWiki](https://wiki.archlinux.org/title/ArchWiki:About)
- [Disclaimers](https://wiki.archlinux.org/title/ArchWiki:General_disclaimer)













# 配置grub

1. `grub install`将一些配置文件复制到`/boot/grub`中

我们首先要运行 fdisk -l来确认到底是硬盘的标识；

这个过程主要是确认硬盘的标识是哪个调备，到底是/dev/hda还是/dev/hdb还是其它的；

[root@localhost ~]# fdisk -l

Disk/dev/hda: 80.0 GB, 80026361856 bytes
255heads, 63 sectors/track, 9729 cylinders
Units= cylinders of 16065 * 512 = 8225280 bytes

 Device Boot   Start    End   Blocks  Id System
/dev/hda1 *     1     970  7791493+  7 HPFS/NTFS
/dev/hda2      971    9729  70356667+  5 Extended
/dev/hda5      971    2915  15623181  b W95 FAT32
/dev/hda6      2916    4131  9767488+ 83 Linux
/dev/hda7      4132    5590  11719386  83 Linux
/dev/hda8      5591    6806  9767488+ 83 Linux
/dev/hda9      6807    9657  22900626  83 Linux
/dev/hda10     9658    9729   578308+ 82 Linux swap / Solaris

如果通过fdisk -l出现有/dev/hda字样的，我们就要用下面的命令来安装；

[root@localhost ~]# grub-install /dev/hda
Installationfinished. No error reported.
Thisis the contents of the device map /boot/grub/device.map.
Checkif this is correct or not. If any of the lines is incorrect,
fix itand re-run the script `grub-install'.

(fd0) /dev/fd0
(hd0) /dev/hda

如果是您fdisk -l出现的有/dev/hdb呢，那就如下运行；

[root@localhost ~]# grub-install /dev/hdb

如果既有/dev/hda和/dev/hdb就安装到/dev/hda中；

[root@localhost ~]# grub-install /dev/hda

值得注意的是如果您有一个/boot分区，应该用如下的办法来安装；

[root@localhost ~]#grub-install--root-directory=/boot /dev/hda

[root@localhost~]#grub-install --root-directory=/boot /dev/hdb

***\*注解：\****具体是/dev/hda还是/dev/hdb，请以fdisk-l为准；如果两个都有，就看您把/boot分区是放在第一块硬盘还是第二块硬盘上了，以实际情况为准；

2. ***\*、设定\**\**GRUB\**\**的\**\**/boot\**\**分区并写入\**\**MBR\**\**；；\**\**
   \****
   在Linux中，GRUB软件包的安装，及在配置过程中安装grub到 /boot中还是不够的，还要把GRUB，写入MBR才行；有时我们重新安装了Windows，Windows会把MBR重写，这样GRUB就消失了；如果您出现这样的情况，就要进行这个过程；

   [root@localhost ~]# grub

   会出现***\*grub>\****提示符，这是grub命令行模式，如果能在开机中出现提示符，没有引导不起来的系统，除非您的系统破坏的极为严重。如果仅仅是GRUB被破坏了，GRUB命令行是能让操作系统引导起来的；

   接着看例子，我们要找到 /boot/grub/stage1的，在grub>后面输入；

   grub> find /boot/grub/stage1
   (hd0,6) 
   (fd0) 注：这个是软驱；现在很少用软驱了，如果您有这方面的需要，自己看GRUB的DOC吧；

   ***\*注解：\****

   (hd0,6) 这是/boot所在的分区；不要误解为是Linux的/所在的分区，这是值得注意的；
   (fd0) 注：这个是软驱；现在很少用软驱了，如果您有这方面的需要，自己看GRUB的DOC吧；

   grub>root (hd0,6)  注：这是/boot所在的分区；
   grub>setup(hd0)  注：把GRUB写到MBR上；

   ***\*注解：\****

   上面这步骤是根据 find /boot/stage1而来的，仔细看一下就明白了；现在我们一般安装很少会把/boot分区列为一个单独的分区；不过有的弟兄可能也喜欢这么做；所以还是有必要说一下为好；

# menu.lst

对于GRUB来说，如果没有配置menu.lst，无论是Linux版本的GRUB，还是WINGRUB，都会有命令行可用，通过命令行是一样能把操作系统引导起来的；有些弟兄总以为menu.lst配置错了，或者在机器启动后出现grub>命令行模式就要重新安装系统，其实根本没有这个必要；只要学会GRUB的命令行的用法，根本没有必要重装系统；

menu.lst 位于/boot/grub目录中，也就是/boot/grub/menu.lst文件；您可以用vi或您喜欢的编辑器来编辑他；如果您不会用vi，还是去学习一下吧；简单的用法怎么也得会，对不对？毕竟这个文档不是讲vi的用法的；

有的弟兄会说，我没有menu.lst怎么办？那就创建一个；用下面的命令；

[root@localhost ~]# touch /boot/grub/menu.lst


然后我们再做一个/boot/grub/menu.lst的链接/boot/grub/grub.conf

[root@localhost ~]# cd /boot/grub
[root@localhost~]# ln -s menu.lst grub.conf

现在我们来写GRUB的menu.lst了，因为/boot/grub/grub.conf是/boot/grub/menu.lst的链接文件，改哪个都行。链接文件相当于Windows的快捷方式，这样可能能更好的理解；

***\*
1\**\**、\**\**menu.lst\**\**的写法之一；\****

首先我们看一下我的Fedora 4.0中的/boot/grub/menu.lst的内容；

default=0 
timeout=5
\#splashimage=(hd0,6)/boot/grub/splash.xpm.gz
hiddenmenu
titleFedora Core (2.6.11-1.1369_FC4)
    root (hd0,6)
    kernel /boot/vmlinuz-2.6.11-1.1369_FC4 ro root=LABEL=/
    initrd /boot/initrd-2.6.11-1.1369_FC4.img
titleWinXp
    rootnoverify (hd0,0)
    chainloader +1

***\*注解：\****

default=0


default=0 是默认启动哪个系统，从0开始；每个操作系统的启动的定义都从title开始的，第一个title在GRUB的启动菜单上显示为0,第二个启动为1，以此类推；

timeout=5


注：表示在开机后，GRUB画面出现几秒后开始以默认启动；如果在启动时，移动上下键，则解除这一规则；
\#splashimage=(hd0,6)/boot/grub/splash.xpm.gz 注：GRUB的背景画面，这个是可选项；我不喜欢GRUB的背景画面，所以加#号注掉，也可以删除；

hiddenmenu

***\*注解：\****隐藏GRUB的启动菜单，这项也是可选的，也可以用#号注掉；

一般的情况下对Linux操作系统的启动，一般要包括四行；title行；root行；kernel行；initrd行；

***\*
1\**\**）在\**\**menu.lst\**\**中\**\**，通过\** \**root (hd[0-n],y)\**\**来指定\**\**/boot\**\**所在的分区；\****

title XXXXX 注：title后面加一个空格，title是小写的，后面可以自己定义；比如FC4，自己定义一个名字就行；
root (hd[0-n],y) ，在本例中，我们看到的是root (hd0,6) ,root(hd[0-n],y)表示的是/boot所在的分区；有时我们安装Linux的时候，大多是不设置/boot的，这时/boot和/所在的同一个分区；这个root(hd[0-n],y)很重要，因为/boot目录中虽然有grub目录，最为重要的是还有kernel和initrd文件，这是Linux能启动起来最为重要东西；

有的弟兄会问，root (hd[0-n],y)是怎么来的？

***\*请参考：\****[《在Linux系统中存储设备的两种表示方法》](http://www.linuxsir.org/main/?q=node/127)
***\*
2\**\**）在\**\**menu.lst\**\**中，\**\**kernel\**\**命令行的写法；\****

kernel 一行，是通指定内核及Linux的/分区所在位置；

比如例子中是；

kernel /boot/vmlinuz-2.6.11-1.1369_FC4 roroot=LABEL=/


在这里以kernel起始，指定Linux的内核的文件所处的绝对路径；因为内核是处在/boot目录中的，如果/boot是独立的一个分区，则需要把boot省略；如果/boot是独立的分区，这行要写成:

kernel /vmlinuz-2.6.11-1.1369_FC4 roroot=LABEL=/ 

因为/boot所处的分区已经在title下一行root (hd[0-n],y)中指定了，所以就无需要再指明内核处在哪个分区了；另外Linux系统的硬盘分区的挂载配置文件在/etc/fstab，原理是通过mount /dev/hd[a-z]X /boot来进行的；您可以对照着来理解；

ro 表示只读；root=LABEL=/来表示Linux的根所处的分区。LABEL=/这是硬盘分区格式化为相应文件系统后所加的标签；如果您不了解什么是标签，也可以直接以/dev/hd[a-z]X或者/dev/sd[a-z]X来表示；就看您的Linux是根分区是在哪个分区了。比如我的是在/dev/hda7，那这里就可以写成root=/dev/hda7；

如果查看系统运行所挂载的分区，请用 df -lh来查看，就能明白是不是/boot是独立的分区，或者查看/etc/fstab也能知道；

[root@localhost ~]# df -lh
Filesystem      容量 已用 可用 已用% 挂载点
/dev/hda7       11G 9.2G 1.2G 90% /
/dev/shm       236M   0 236M  0% /dev/shm

在这个例子中，我们可以发现 /boot并没有出现只有/dev/hda7，这表示/boot并不是独立的一个分区；所有的东西都包含在/中；于是我们在/boot中查看内核版本；

[root@localhost ~]# ls /boot/vmlinuz*
/boot/vmlinuz-2.6.11-1.1369_FC4 注：看到内核vmlinuz所处的目录；

于是我们就可以这样kernel这行了；

kernel/boot/vmlinuz-2.6.11-1.1369_FC4 ro root=/dev/hda7


***\*
3\**\**）\**\**initrd\**\**命令行的写法；\****

如果是/boot独立一个分区，initrd一行要把/boot中省略；如果/boot不是处于一个分区，而是和Linux的/分区处于同一分区，不应该省略；

比如我们在2）中用的例子；现在拿到这里，我们应该首先查看 /boot中的initrd的文件名到底是什么；

[root@localhost ~]# ls /boot/initrd*
/boot/initrd-2.6.11-1.1369_FC4.img

如果是通过df -lh得知或查看/etc/fstab也行，得知/boot是独立的分区；这时initrd应该写成；

initrd /initrd-2.6.11-1.1369_FC4.img

如果是 /boot不是独处一个分区，而是在/同一处一个分区，则要写成；

initrd /boot/initrd-2.6.11-1.1369_FC4.img

***\*
4\**\**）\**\**menu.lst\**\**第一种写法的总结和实践；\****

在这里，我们只说重要的，不重要的就一带而过了；
***\*
1\**\**］用\**\**fdisk -l\**\**；\**\**df-lh\**\**；\**\**more /etc/fstab\**\**来确认分区情况；\**\**
\****
我们过fdisk -l；df -lh ; more /etc/fstab来确认/boot所在的分区，及Linux的根分区所在位置；

比如我们确认/boot和Linux的/分区同处一个分区；

[root@localhost ~]# df -lh
Filesystem      容量 已用 可用 已用% 挂载点
/dev/hda7       11G 9.2G 1.2G 90% /
/dev/shm       236M   0 236M  0% /dev/shm

然后我们/etc/fstab中,查看/分所在的分区或分区标签是什么；

[root@localhost ~]# more /etc/fstab
\# Thisfile is edited by fstab-sync - see 'man fstab-sync' for details
LABEL=/        /           ext3  defaults    1 1
/dev/devpts      /dev/pts        devpts gid=5,mode=620 0 0
/dev/shm        /dev/shm        tmpfs  defaults    0 0
/dev/proc       /proc         proc  defaults    0 0
/dev/sys        /sys          sysfs  defaults    0 0
LABEL=SWAP-hda1    swap          swap  defaults    0 0
/dev/hdc        /media/cdrecorder    auto  pamconsole,exec,noauto,managed 0 0

经过上面的df -lh和more/etc/fstab的对照中得知，/boot并是独处一个分区，而是和/在同一个分区；这个Linux系统安装在/dev/hda7上，文件系统（此分区）的标签为LABEL=/，/boot也是处于/dev/hda7，/dev/hda7也可以说是 root (hd0,6)；
***\*
2]\**\**查看内核\**\**vmlinuz\**\**的和\**\**initrd\**\**文件名的全称；\****

[root@localhost ~]# ls -lh /boot/vmlinuz*
-rw-r--r-- 1 root root 1.6M 2005-06-03 /boot/vmlinuz-2.6.11-1.1369_FC4
[root@localhost~]# ls -lh /boot/initrd*
-rw-r--r-- 1 root root 1.1M 11月 26 22:30 /boot/initrd-2.6.11-1.1369_FC4.img

***\*
3]\**\**开始写\**\**menu.lst\**\**；\****

我们根据上面所提到的，可以写成如下的样子；

default=0 
timeout=5
titleFC4
    root (hd0,6)
    kernel /boot/vmlinuz-2.6.11-1.1369_FC4 ro root=LABEL=/ 
    initrd /boot/initrd-2.6.11-1.1369_FC4.img

也可以写成；

default=0 
timeout=5
titleFC4
    root (hd0,6)
    kernel /boot/vmlinuz-2.6.11-1.1369_FC4 ro root=/dev/hda7
    initrd /boot/initrd-2.6.11-1.1369_FC4.img

***\*注解：\****上面两个不同之处在于一指定Linux的根/所在的分区时，一个是用了文件系统的标签，另一个没有用标签；
