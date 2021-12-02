---
title: OS Introduction
tags: Modern  Operating Systems
categories: 
date: 2021-10-05 20:28:21
---

ref：

《Modern  Operating Systems 》

《Operating Systems Three Easy pieces 》



<!--more-->

# Intro

* appearances can be deceiving.
  * The program that users interact with, usually called the **shell** when it is text based and the GUI when it uses icons, is actually not part of the operating system, although it uses the operating system to get its work done

## Main Components

### Hardware

The hardware consists of chips, boards, disks, a keyboard, a monitor, and similar physical objects.

### Software

On top of the hardware is the software. Most computers have two modes of operation: **kernel mode** and **user mode**.

* OS runs on the bare hardware and provides the base for all the other software

####  **kernel mode** 

* the most fundamental piece of software, runs in **kernel mode** (also called supervisor mode). In this mode it has <u>complete access</u> to all the hardware and can execute any instruction the machine is capable of executing. 

####  user mode

* The rest of the software runs in **user mode**, in which <u>only a subset of the machine instructions is available</u>.
  * In particular, those instructions that affect control of the machine or do I/O )Input/Output" are forbidden to user-mode programs

* The user interface program, **shell** or **GUI**, is the <u>lowest level of user-mode software</u>, and allows the user to start other programs

* user mode 和 kernel mode 的区别并不严格

  * in embedded systems (which
    may not have kernel mode) or interpreted systems (such as Java-based systems that use interpretation, not hardware, to separate the components).
  * Also, in many systems there are programs that run in user mode but help the operating system or perform privileged functions

  * 总之， Everything running in **kernel mode** is clearly part of the **operating system**, but some programs running outside it are arguably also part of it, or at least closely associated with it



# WHAT IS OPERATING SYSTEM

##  The OS as an Extended Machine

* **top-down view: operating system as primarily providing abstractions to application programs**
  * The architecture (instruction set, memory organization, I/O, and bus structure) of most computers at the machine-language level is primitive and awkward to program, especially for input/output.即： 计算机的底层是丑陋和复杂的， 需要**抽象**出中间层才能方便使用
* **This abstraction is the key to managing all this complexity（圣经！）**. Good abstractions turn a nearly impossible task into two manageable ones. The first is defining and implementing the abstractions. The second is using these abstractions to solve the problem at hand
* **The job of the operating system is to create good abstractions and then implement and manage the abstract objects thus created**
* OS的真正用户是APP(和APP开发者)， 而end users使用的是UI（shell or GUI）提供的抽象。
  * While the abstractions at the user interface may be **similar** to the ones provided by the operating system, this is not always the case.
    * 如Windows Desktop和command prompt采用了Windows提供的相同的system abstractions。 Linux的Gnome、KDE和X Window System看起来差别很大，实际上也采用了相同的system abstractions

## The OS as a Resource Manager

* **bottom-up view: the operating system is there to manage all the pieces of a complex system**

* Resource management includes **multiplexing** (sharing) resources in two different ways: in time and in space

# HISTORY OF OPERATING SYSTEMS

## The first true digital computer 

was designed by the English mathematician **Charles Babbage** (1792–1871)

* Babbage realized that he would need software for his analytical engine, so he hired a young woman named **Ada Lovelace**

《信息简史》里讲了他们的故事，向他们致敬！

## The First Generation (1945–55): Vacuum Tubes
  * 用插板（后来是穿孔卡片）
## The Second Generation (1955–65): Transistors and Batch Systems

  * **Batch Systems：** The idea behind it was to collect a tray full of jobs in the input room and then read them onto a magnetic tape using a small (relatively) inexpensive computer, such as the **IBM 1401**, which was quite good at reading cards, copying tapes, and printing output, but not at all good at numerical calculations. Other, much more expensive machines, such as the **IBM 7094**, were used for the real computing
  * 用IBM 140把卡片翻译成磁带， 用7094处理磁带，把结果打印到磁带上， 再将结果磁带交给1401**离线**打印（不需要7094了）
  * 典型：FMS（ the Fortran Monitor System ）和 IBSYS( IBM's system for the 7094 ). 主要用于科学计算

## The Third Generation (1965–1980): ICs and Multiprogramming

  * By the early 1960s, most computer manufacturers had two distinct, incompatible, product lines：

    1. 大型机（类似7094），用于科学、工业上的数值计算
    2. 商业机， 用于银行、保险公司等的磁带排序和印刷

  * System/360

    * IBM推出的一系列software-compatible machines,拥有同样的架构和指令集，彼此只有价格、性能不同。

      * IBM 360 was the first major computer line to use (small-scale) ICs, 带来了价格和性能上的巨大提升

      * 360还有很多后继，如370, 4300, 3080,  3090， zSeries之类
      
        

  * OS/360: 360的操作系统

    * 360的"a family of compatible computers"迅速流行。但是，这对软件（尤其是OS）的编写产生了巨大困难。
      * The original intention was that all software, including the operating system, OS/360, had to work on all models。
      * OS/360项目开发到最后,就如同“a herd of prehistoric beasts stuck in a tar pit”
    * OS/360引入了许多新技术，包括
      * **multiprogramming**：  内存分区， 可以多任务, 避免单任务阻塞使得CPU idle 
      * **spooling** (from Simultaneous Peripheral Operation On Line)： 直接将任务从卡片读到磁盘上，输出反之。 再也不需要磁带了 ）

  * CTSS(Compatible Time Sharing System)

    * developed at M.I.T. on a specially modified 7094

    * **timesharing**, a variant of multiprogramming, in which each user has an online terminal。 即多用户。提高开发速度。
    * 由于缺乏必要的protection hardware。 CTSS没有流行

  * MULTICS (MULTiplexed Information and Computing Service)

    * M.I.T., Bell Labs, and General Electric研发（最后只有MIT坚持）， 目的是设计一款“computer utility”。 类似国家电力系统，支持同时间许多人的timesharing，MULTICS被设想为房子那样大的计算设施。

    * 由于采用PL/I语言和太过有野心，MULTICS没有预期的那样成功
    * MULTICS的概念就是当今的**云计算**

  * minicomputers

    * starting with the DEC PDP-1 in 1961
    * culminating in the PDP-11

  * UNIX

    *  Ken Thompson，one of the computer scientists at Bell Labs who had worked on the MULTICS project, subsequently found a small PDP-7 minicomputer that no one was using and set out to write a stripped-down, one-user version of MULTICS. This work later developed into the UNIX operating system
    * Two major versions developed:
      * System V, from AT&T
      * BSD (Berkeley Software Distribution) from the University of California at Berkeley
      * POSIX
        * 为了让程序能运行在所有UNIX系统，IEEE定义了一个UNIX标准，称为POSIX.
        * POSIX defines a minimal system-call interface that conformant UNIX systems must support. 
        * 很多其他的OS也支持OS

  * MINIX

    * in 1987, the author released a small clone of UNIX, called MINIX, for educational purposes.
    * 相当稳定

  * Linux

    * Linus Torvalds为了得到一个完全免费的MINIX,在其基础上开发了LINUX

  ## The Fourth Generation (1980–Present): Personal Computers

由于LSI (Large Scale Integration) circuits的发展，个人计算机成为了可能，它和minicomputer的差距主要是价格上的

  * CP/M (Control Program for Microcomputers)
    * a disk-based OS for 8080, the first general-purpose 8-bit CPU invented by Intel
    * 由于Intel不认为CP/M有什么未来，就允许作者Kildall拿着专利自立门户，后者成立了Digital Research。
* DOS (Disk Operating System)
  * In the early 1980s, IBM designed the **IBM PC** and looked around for software to run on it. People from IBM contacted **Bill Gates** to license his BASIC interpreter. They also asked him if he knew of an operating system to run on the PC. Gates suggested that IBM contact Digital Research, then the world’s dominant operating systems company。 Kildall拒绝了， 盖茨就找了Seattle Computer Products， 购买了DOS，将其与BASIC捆绑卖给IBM, 后者想要一些修改，盖茨就雇了其DOS的作者Tim Paterson作为他的新公司MS的雇员。
  * The revised system was renamed MS-DOS (MicroSoft Disk Operating System) and quickly came to dominate the IBM PC market.
  * By the time the successor to the IBM PC, the IBM PC/AT, came out in 1983 with the Intel 80286 CPU, MS-DOS was firmly entrenched and CP/M was on its last legs. MS-DOS was later widely used on the 80386 and 80486.
* GUI
  * 早期的微电脑的OS，包括CP/M, MS-DOS等都基于用户从键盘输入命令。
  * **Engelbart** 发明了GUI  ( Doug Engelbart at Stanford Research Institute in the 1960s ), complete with windows, icons, menus, and mouse. 
  * These ideas were adopted by researchers at **Xerox PARC** and incorporated into machines they built.

* MAC
  * Jobs拜访PARC的时候看到了GUI，回去后开始开发带GUI的Apple，第一代"Lisa"失败了， 第二代“Mac”成功了
* MAC OS X
  * 1999,Apple采用了新内核，它CMU研发的微内核，而后者被最初设计用来替代BSD UNIX的内核
  * 因此， MAC OS X是个UNIX操作系统
* Windows
  * 微软开发的MS-DOS的后继， 深受Mac成功的影响，因此带有GUI。事实上它更像是运行在MS-DOS上的shell
* Windows 95
  * 有十年时间， 1985-1995，Windows 只是一个MS-DOS上的图形环境
  * Win95是95年发行的独立版本，拥有更多的操作系统的特性， 只将MS-DOS用于启动和运行旧的MS-DOS程序
  *  However, starting in 1995 a freestanding version, **Windows 95**, was released that incorporated many operating system features into it, using the underlying MS-DOS system only for booting and running old MS-DOS programs.
* Windows 98 
  * 98年发行的Win95的轻微修改版。 这两个版本都还含有大量的Intel16位汇编代码
* Windows NT(where the NT stands for New Technology)
  * 和Windows 95兼容， 但是是a full 32-bit system
  * 采用了很多VAX VMS的思想（ 因为主设计者也是后者的设计者之一 ）
  * Version 5 of Windows NT was renamed **Windows 2000** in early 1999. It was intended to be the successor to both Windows 98 and Windows NT 4.0
  * 由于Win2000也没有足够成功， MS发行了Windows Me (Millennium Edition)
* Windows XP
  * 发行于2001
  * a slightly upgraded version of Windows 2000
  * 基本取代了之前所有版本
* service packs
  * Windows 2000之后，MS将Windos系列分成客户-服务器两台产品线。前者基于XP和其后继， 后者包含了Server 2003 and Windows 2008。 嵌入式的产品线后来也出现了。
  * All of these versions of Windows forked off their variations in the form of service packs.
* Vista
  * Then in January 2007, Microsoft finally released the successor to Windows
    XP, called Vista
* Windows 7
  * 相比Vista没有很多新特性，但是更稳定更不吃资源
*  Windows 8
  * Win7的后继，2012发行。

# COMPUTER HARDWARE REVIEW

## PROCESSORS

* basic cycle of CPU: 取指、译指、执行
* 每个CPU都有自己特殊的指令集。ARM处理器不能执行x86程序
* 由于对内存的存取所花的时间比执行一条指令还要长，CPU内部会有寄存器。
* 许多寄存器对有用出现**可见**
  * PC
  * 栈指针，指向内存中的栈顶。栈含有每个程序的帧。栈帧含有： 输入的参数、局部变量、没有保存进寄存器的临时变量
  * PSW(Program Status Word): 包含状态码位。 用户程序通常能读整个PSW，但仅仅只能写其中的一部分
* 为了提供性能，CPU通常有流水线和超标量。
  * 流水线会把底层的复杂度暴露给上层，令人头疼
  * 超标量： 多个指令同时被取指和译指，然后放到一个Holding buffer里，每当一个执行单元空闲时，就去Holding buffer中找它能处理的指令。该设计的一个后果是：指令不一定按顺序执行。而执行结果能不能和顺序实现的CPU相同，取决于硬件。
* 除了嵌入式系统中的少数，CPU都有 user mode和kernel mode. 当运行在kernel mode， CPU可以执行指令集提供的每一条指令和硬件提供的所有特性。 在
  * 桌面机和服务器上，OS都运行在kernel mode.
  * 在大部分嵌入式系统中，OS一部分运行在kernel mode, 剩余部分运行在 user mode
  * 用户程序永远运行在 user mode，只能执行一小部分指令和一小部分硬件特性。  “设置PSW的mode bit以进入 kernel mode”也是被禁止的
* 为了获得OS的服务，用户程序会发起system call,即陷入kernel并启动OS
  * the  TRAP  instruction switched from user mode to kernel mode and starts the OS.执行结束后，控制会返还到TRAP的下一条指令
  * 计算机的trap不仅有用于执行system call的指令，还有别的

### Multithread and Multicore Chips

* multithreading: 允许CPU拥有两个线程并且在**纳秒**级的时间里切换。 **多线程并不是并行**，因为同一时间还是只有一个程序在CPU上运行
  *  如果一个程序要读取内存（花的时间比较长），那么多线程的CPU可以切换到另一个程序
  * 多线程带来的问题是：每一个线程都会被OS视为独立的CPU. 考虑一个双CPU的系统，每个CPU有两个线程。当有两个线程的任务时，OS可能会把它们全部交给同一个CPU上的两个线程，而这是很浪费的
* 许多CPU芯片上还有多个(几十个)processors or **cores**  使用多核芯片需要一个多处理器的OS
* GPU拥有上千个core, 适用于许多并行执行的小规模计算， 在顺序计算上并不突出。

## MEMORY

内存是分层的

* 最顶层是寄存器，和CPU一样快，因此访问它们没有延迟
* cache，有L1和L2，差别是timing 。访问L1没有延迟，访问L2有1-2个时钟周期的延迟
* 主存， the work house of memory system,也被称为RAM
* ROM: 也是random-access memory，但是是只读的，不属于main memory
* EEPROM和flash也是非易失性，但有写入次数限制
* CMOs：记录了时间日期。还记录了一些配置参数，比如该从哪个盘启动。CMOs里自带一个小电池，因此虽然是易失性的，短了点也能工作。

## Disks

普通磁盘就不介绍了

* SSD(Solid State Disks): 没有移动的磁头，也没有盘片，事实上它使用flash存储数据。它们和磁盘唯一的相似处就是，他们都是非易失的。 **SSD不是磁盘**
* **虚拟内存**即内存映射，这由CPU的一部分，称为**MMU**( Memory Management Unit )完成



## I/O Devices

#### controller and devices

##### controller

OS不仅需要管理CPU和Memory，还需要管理I/O devices，I/O devices由两部分组成：控制器和设备本身。

  * **controller**是一个或一组芯片，位于南桥，向OS提供一个更“简单”（相对直接控制设备而言）的接口

    * 比如，OS可能命令“read sector 11,206 from disk 2”。controller需要将将线性的扇区号映射为实际的cylinder, sector, and head，考虑到外侧柱面比内侧多、坏的删区要被重映射为其它山区等等，这个映射会很复杂。
    * 然后controller要决定磁臂停在哪个扇区。 It has to wait until the proper sector has rotated under the head and then start reading and storing the bits as they come off the drive, removing the preamble and computing the checksum. Finally, it has to assemble the incoming bits into words and store them in memory. 
    * To do all this work, controllers often contain small embedded computers that are programmed to do their work.
##### device

  * device的接口相当简单，便于标准化。因此any SATA disk controller可以处理any SATA disk. 

    * **SATA** stands for Serial ATA and AT A in turn stands for AT Attachment. In case you are curious what AT stands for, this was IBM’s second generation ‘‘Personal Computer Advanced Technology’’ built around the then-extremely-potent 6-MHz 80286 processor that the company introduced in 1984.
    * SATA是目前许多电脑的磁盘标准。由于实际的device interface隐藏在controller interface后， OS只能看到后者，也就无需处理前者的细节
##### disk driver
  * 由于controller各不相同，需要软件来控制，每个软件控制一个controller，称为**disk driver**

    * driver talks to a controller, giving it commands and accepting responses

    * 每个controller厂商需要为每个操作系统提供一个driver

    * driver需要被置入OS中，在kernel mode工作。 事实上它能在kernel外工作，windows和linux都对此提供了支持，但大多数driver还是在kernel内。

      * only very few current systems, such as MINIX 3, run all drivers in user space. Drivers in user space must be allowed to access the device in a controlled way, which is not straightforward
      * 有三种把driver放入OS的方法：
        * 使内核和新driver重新连接，然后重启。Many older UNIX systems work like this. 
        * 进入OS文件，告诉它它需要那个driver，然后重启。在启动时，OS找到那个driver然后加载它。 Windows works this way.
        * 许多操作系统都支持在运行时接受新驱动并安装，不需要重启。 热插拔的设备，如USB and IEEE 1394 devices, 需要这种方式
##### device register
* controller事实上与它的寄存器们（称为**device register**）直接交互. driver从OS得到命令，将其翻译后写入device registers。

* For example, a minimal disk controller might have registers for specifying the disk address, memory address, sector count, and direction (read or write). 

* To activate the controller, the driver gets a command from the operating system, then translates it into the appropriate values to write into the device registers. The collection of all the device registers forms the **I/O port** space, a subject we will come back to in Chap. 5.

* device registers会被映射到OS的地址空间或者一个特殊的I/O port space
  * 前者不需要特殊的I/O instructions，可以被像普通内存数据一样读写，但是消耗了地址空间（  device registers的地址无法被其他程序使用，因此是安全的 ） 
  * 后者不消耗地址空间（每个寄存器被映射为一个port address）但需要额外的instructions

#### I/O

* IO有三种方式：
  1. **busy waiting**：用户程序发起system call,  kernel将其转换为procedure call交给相应的driver. Driver启动IO设备并且对设备轮询。IO结束后，driver将数据（如果有的话）返回，OS将控制返还给调用者
     * 占用了CPU的全部时间
  2. **interrupt**：driver开启设备，要求它在完成时发出中断. At that point the driver returns. The operating system then blocks the caller if need be and looks for other work to do.
  3. **DMA**(Direct Memory Access): DMA芯片可以在避免CPU持续干预的情况下控制内存和一些controller之间的数据传输
     * CPU启动DMA芯片，告诉它how many bytes to transfer, the device and memory addresses involved, and the direction, and lets it go. 当DMA芯片工作结束时，会发出中断（和方法二一样）
  
* 中断的过程：
  1. driver通过向contoller的device  registers写入来告诉controller要做什么。controller然后便启动device
  2. When the controller has finished reading or writing the number of bytes it has been told to transfer, it signals the interrupt controller chip **using certain bus lines**
  3. 如果中断控制器准备好接受新中断（ 如果它在处理一个更高优先级的中断，就不会ready ）,it asserts a pin on the CPU chip telling it
  4. 中断控制器把**device number**放在总线上，CPU就可以read并且知道是哪个设备刚刚finished
     * 一旦CPU决定接受中断, PC和PSW会被压栈，CPU会切换到内核态
     * The device number may be used as an index into part of memory to find the address of the interrupt handler for this device. This part of memory is called the **interrupt vector**
     * 一旦 interrupt handler启动，它就将PC和PSW出栈并保存，并向设备询问。当所有的handeller结束后，就退回到终端前执行的程序
  
* 中断可能会在其它interrupt handler运行时发生。 因此CPU可以disable interrupts and then reenable them later。当CPU disable interrupts时，设备依然持续发出中断信号，但CPU不会接受。 

* 由于多个中断可能同时发生，每个设备都有（通常是静态的）中断优先级来决定在disable结束后，哪个中断先被接受。

## Buses



* 单总线架构用于original IBM PC,  为了更快的IO速度和CPU-to-memory traffic，额外的总线被引入。 形成了现代的x86系统
* This system has many buses (e.g., cache, memory, PCIe, PCI, USB, SATA, and DMI), each with a different transfer rate and function. The operating system must be aware of all of them for configuration and management. 

* The main bus is the **PCIe** (Peripheral Component Interconnect Express) bus.

  * The PCIe bus was invented by Intel as a successor to the older PCI bus, which in turn was a replacement for the original ISA (Industry Standard Architecture) bus. 
  * 2004年PCIe刚发明时，流行**shared bus architecture**，许多设备用一条线传输数据，因此需要一个arbiter
  * PCI使用**parallel bus architecture**，即将每个数据字分多条线传输。 比如32-bit数据需要32根并行的线
  * PCIe使用**serial bus architecture**，把数据包装成一个message， 点对点传输（一次连接称为一个**lane**）。也支持并行，如可以并行地传32个**lane**


* the CPU talks to memory over a fast **DDR3** bus, to an external graphics device over PCIe and to all other devices via a **hub** over a **DMI** (Direct Media Interface) bus. The hub in turn connects all the other devices, using the Universal Serial Bus to talk to  USB devices, the SATA bus to interact with hard disks and DVD drives, and PCIe to transfer Ethernet frames.
	* PCI接口的设备另外放在一个hub processor 内
* Moreover, each of the cores has a dedicated cache and a much larger cache that is shared between them. Each of these caches introduces another bus. 
每个core有一个专用cache，所有core共享一个更大的cache，每个cache拥有自己的总线

* The **USB** (Universal Serial Bus) was invented to attach all the slow I/O devices, such as the keyboard and mouse, to the computer.

* **SCSI** (Small Computer System Interface) bus 用于需要高带宽的设备，如服务器和工作站

* is a high-performance bus intended for fast disks, scanners, and other devices needing considerable bandwidth. Nowadays, we find them mostly in servers and workstations

* Intel 和 MS设计了**plug and play**系统，可以自动收集IO设备信息，集中分配中断优先级和I/O（设备的）寄存器地址

  * 在此之前，这些都要手动分配

## Booting the Computer

* **BIOS**（Basic Input Output System）：PC主板上的一个程序
  * The BIOS contains low-level I/O software, including procedures to read the keyboard, write to the screen, and do disk I/O, among other things. 
  * Nowadays, it is held in a **flash RAM**, which is nonvolatile but which can be updated by the operating system when bugs are found in the BIOS.

1. 计算机开机时，BIOS启动，它会检查RAM和键盘等基础外设的连接和响应情况
   * It starts out by scanning the PCIe and PCI buses to detect all the devices attached to them. 
   * 如果设备和上次启动时不一样，新的设备将被配置
2. 通过CMOS中的启动设备列表，BIOS找到启动设备，后者的第一个扇区将被读进内存并执行，该扇区有一个检查partition table的程序。 
   * partition table位于该扇区末尾，决定哪个扇区是active partition
3. 一个secondary boot loader被从active partition读入。
4. 该loader从active partition读入OS并启动
5. OS问询BIOS，得到配置信息，对每个设备，OS检查自己是否有对应驱动，若没有，则通知用户去下载。
6. 当所有设备驱动都齐备时，OS将它们加载进kernel. 并初始化分区表，启动各种程序....(如登陆程序和GUI)

# The OS Zoo

## Mainframe Operating Systems

* mainframes：体型巨大，高I\O capacity
* 用途：
  * batch： 不需要用户在场交互，即可处理程序
  *  transaction processing,
  * and timesharing
* **Timesharing** systems，允许许多远程用户同时登陆一台主机处理任务, such as querying a big database.
* 正被UNIX的各种变体（如LINUX）取代

## Server Operating Systems

* They serve multiple users at once over a network and allow the users to share hardware and software resources.

* Typical server operating systems are Solaris, FreeBSD, Linux and Windows Server 201x.

## Multiprocessor Operating Systems

* 把多个CPU连接称为一个系统。属于server OS的变体，增加了通信、连通性等功能
* Many popular operating systems, including Windows and Linux, run on multiprocessors



## Personal Computer Operating Systems

* 无需多言

## Handheld Computer Operating Systems

* A handheld computer，又称**PDA**(Personal Digital Assistant),是一个可以边手持边操作的小型计算机
* Google’s Android and Apple’s iOS

## Embedded Operating Systems

* 和Handheld Computer OS区别在于：嵌入式OS中无法自主安装软件 ---- 软件都写在ROM里，这也意味着不需要提供app之间的保护

## Sensor-Node Operating Systems

* 每个节点都是个小型计算机，通过一个基站进行无线通信

* Each sensor node is a real computer, with a CPU, RAM, ROM, and one or more environmental sensors. It runs a small, but real operating system, usually one that is event driven, responding to external events or making measurements periodically based on an internal clock.
* 所有程序写在ROM里

## Real-Time Operating Systems

* **hard real-time system**: actions absolutely **must** occur at a certain moment (or within a certain range)
  * 如工业、航空、军事

* **soft real-time system**: ddl没那么死
* The categories of handhelds, embedded systems, and real-time systems overlap considerably

## Smart Card Operating Systems

* 没想到吧，smart card也有一个OS!
  * 有小型CPU和ROM
* Some smart cards are Java oriented

# OS Concepts

## Processes

* A process is fundamentally a container that holds all the information needed to run a program
* **address space**: 进程可操作的一块内存。 包括了可执行的程序、程序的数据和栈指针
* **process table**: an array of structures, one for each process currently in existence
  * 大多数OS都有，储存了每个进程的所有信息,不只是地址空间
* **core image**:    address space of  a ( suspended ) process
* **ID**:
  *  **UID**: each  person authorized to used a system is assigned a UID by the system administrator
    * 每个进程都拥有其创建者的UID， 子进程的UID就是父进程的UID
  * **GID**： users can be members of groups

## Address Space

* 每个进程都拥有其可操作的地址空间，而**address space**是和物理内存**解耦**（借助虚拟内存）的
* 虽然避免内存中的进程互相干扰是硬件需要提供的机制，但该机制在软件层需要由OS控制

## File

* **File & Directory**: OS把底层千奇百怪的存储设备抽象成文件系统，并使用**directory**概念来管理
  * 对文件和目录的许多操作都需要`syscall`
* **pathname**: 文件在 directory hierarchy 中有**pathname**, 后者最顶层是**root directory**, 由`/`表示。 从根目录开始的路径叫做**绝对路径**。 而每个进程又有自己当时的**working directory**， 其中的路径名不需要从根目录开始,例如对于绝对路径`C:\Docs\sub\javac`, 当前工作目录是`C:\Docs`
  * 绝对路径：`C:\Docs\sub\javac`
  * 相对路径：`sub\javac` ; 也可写成：`.\sub\javac`
  * `.`表示当前目录，`..`表示上级目录
*  **file descriptor**在文件被读写前，它首先要被打开，此时需要检验许可，若许可成功，则系统返回一个**file descriptor**用于后续操作； 否则返回一个error code

* **mount**: 将CD-ROM上的file system挂载到root file system.
  *  此时原有节点的数据不能被访问，因为这个节点已经被挂载了。由于挂在节点一般是空节点，这一般不会造成影响
* **special file**：OS将I/O设备抽象为special file ，使得它可以用处理普通文件的`syscall`来处理这类设备，special file分两种，都挂载到`/dev`目录下
  * block special file：用于由随机寻址块组成的设备 .i.e 磁盘
  * character special file: 用于输入\输出字符流的设备 .i.e 键盘

* **pipe**： 用于进程间通信的伪文件，通过它，UNIX进程间通信就像是普通的文件读写
  * pipe的实现很像文件的实现，一个进程要想知道其输出文件是一个真实的文件还是一个pipe，只能使用`syscall`

## Protection

* protection code: each file in UNIX are protected by assigning each one a 9-bit binary protection code, which consists of three 3-bit fields, one for the owner, one for the owner's group, one for everyone else. 

  * 例如`rwxr-x--x`意味着拥有者可读可写可执行， 群组可读可执行，其他人可执行

# Ontogeny Recapitulates Phylogeny

* 达尔文有个理论，“胚胎的成长会浮现其种族的演化”，这在计算机领域是很形象的。一个思想可能会因为技术创新而变得火热，然后湮没无闻，可思想本身是不死的。因此新技术的发展，其内核几乎总是一些“老旧”的思想。一项技术的发展所要经历的不同阶段，几乎也总是计算机发展史上的不同思想的重现
* 因此，不要歧视所谓的“obsolete idea”

# System Calls

* 对`syscall`的调用一般是高度依赖于机器的，并且是汇编语言，但会提供一个**procedure library**来允许在高级语言中调用`syscall`
* 每个单CPU的计算机同时只能处理一条指令， 如果一个user mode的程序需要system service， 它就会执行a trap instruction 来将控制权交给OS, 后者完成任务后再将控制权交还
  * 因此`syscall`和普通的procedure call没什么区别，只是前者会陷入kernel mode

* System call执行步骤：
  1. 参数压栈
  2. 参数压栈
  3. 参数压栈
  4. 使用普通的procedure call调用library procedure, 
  5. library procedure将 system-call number放入OS所期望的地方（通常是个寄存器）
  6. library procedure执行`TRAP`, 陷入kernel mode。 并从内核层的固定地址开始执行
     * TRAP指令和 procedure call的区别在于能陷入内核层，并且TRAP不能跳转到任意位置，只能跳转到固定位置，或者跳转到其参数中给定的位置
  7. 内核层检查system-call number, 并分发给对应的handler
  8. handler执行
  9. handler执行完毕后，控制*可能会*交还给user space的library procedure
     * system call也可以阻塞caller，比如在等待用户输入时。 此时OS会去执行其它进程
  10. library procedure以通常的procedure call返回的方式返回user program
  11. user program像对待任何library procedure一样，清除栈顶

## System Calls for Process Management

* `fork`是POSIX中唯一的创建新进程的方法，它会创建一个和父进程完全相同的子进程，并返回子进程在父进程中的**PID**( PID在子进程中为0 )

* 当一条指令被输入时。shell会fork出一个新的子进程，这个子进程必须执行这条用户指令，它首先会调用`exec` system call( 实际上该system call名字不一定叫`exec` )

  * `exec(command,parameters,0)`
  * 其参数分别为：要执行的文件名； 参数数组的指针； 环境数组的指针
  * 执行`exec`会导致该子进程的整个**core image**被`exec`第一个参数（即文件名）所指向的文件所替换

* 例子：执行`cp file1 file2`

  1. shell `fork`出子进程,子进程执行`cp`这个文件，将源和目的文件的名字传给它

     * 程序就是文件，`cp`既是程序，当然也是个文件

  2. `cp`的内容是:

     `main( argc, argv, envp )`

     * `argc`: 参数数量，包括程序名在内，这里是3
     * `argc`：参数名（都是字符串）指针. `argv[0]`指向string "cp" 
     * `envp`: 环境指针， 一个string的键值对数组，这里没有环境要传递，因此是0

* UNIX进程在内存中分三段：

  * **text segment**: i.e., the program code  
  * **data segment**: i.e., the variables 向上增长
  * **stack segment**： 向下增长

## System Calls for Directory Management

* `mkdir`, `rmdir`: create and remove empty directories
* `link`: allow the same file to appear under 2 or more names
  * UNIX系统有一个i-node组成的表，每个i-node记录了这个文件的一些信息， 而UNIX File都有一个File number，是i-node的索引。 一个directory就是一个（ i-number, ASCII name ）pair的集合. `link`做的就是创建一个新的directory,它只有一个pair，其ASCII name可能不同，但i-number 是已有的文件的

## Miscellaneous System Calls

* `chmod`: 改变文件的九位protection code
* `chdir`: 改变文件的工作目录
* `kill`

## The Windows Win32 API

* UNIX的system call和library几乎是一一对应的， 但是Windows把它们解耦了，开发者们面对的是**WIn32 API**
* **WIn32 API**极其庞大和复杂，因此很难区分哪个调用了system call哪个没有

# OS Structure

## Monolithic Systems

* 整个OS作为一个单一程序运行在kernel mode
* OS是一个procedures的集合， 每一个procedure都可以自由调用其它任何procedure，完全没有信息隐藏
* 当计算机启动时，不仅OS会被加载， 许多OS还支持loadable extensions,比如I/O驱动和文件系统。 它们在UNIX中称为 share libraries, 在Windows中称为DLLs

## Layered Systems

* OS由层级结构组成，每一层使用下一层的服务
* 最早是THE system,由Dijkstra研发
  * Layered system只是个设计目标，由于每个层最终都链接到一起，实际上整个OS是一个单一的程序

| Layer | Function                                  |
| ----- | ----------------------------------------- |
| 5     | The operator (用户操作进程 )              |
| 4     | User programs                             |
| 3     | I/O management  3层以上不用处理IO细节     |
| 2     | Operator-process communication            |
| 1     | Memory management                         |
| 0     | processor allocation and multiprogramming |

* Layered system的理念后来在MULTICS体现。 后者是由一系列同心环组成，内环拥有更大的权限，外环若要使用内环的服务，需要系统调用

## Microkernels

* Layered system的设计者可以划分kernel-user的界限，传统的Layered system全部运行在kernel，而这是不必要的。microkernel的理念是将OS分离为不同模块，其中只有一个 --- 称作microkernel 运行在内核层，其余的运行在用户层，以实现高可靠性
* 除了OS X( based on Mach microkernel ), 通常的桌面OS都不用microkernel
* 著名的有塞班和MINIX 3
* MINIX 3的结构：
  * 内核层： system call handler和时钟的驱动（ 因为调度器经常要与时钟交互 ）
  * 用户层（从下到上）：
    1. Drivers：各种设备驱动，由于不在内核层，因此无法直接对I/O port sapce操作，也无法直接发起I/O commands,只能构造一个structure发给内核
    2. servers：为上层提供各种服务，其中有个**reincarnation server** 工作是检查其它server和driver的工作情况，若不正常，就自动替换，不需要任何用户干预。 
    3. User programs
* 也可将微内核的理念看作  “*mechanism*和*policy*分离”。 mechanism指的是机器自动执行的那部分， policy指的是需要用户指定的那部分， 内核层只需要管理mechanism

## Client-Server Model

不解释了

## Virtual Machines

## VM/370

* 将multiprogramming和extended machine with a more convenient interface解耦
* 使用VM monitor（又称为hypervisor），它运行在硬件上，向上提供虚拟机。
* 虚拟机提供的不是extened machine，而是**硬件**， 没有任何抽象
  * 其实虚拟机是将机器硬件抽象成了虚拟硬件提供给宿主机，实现了物理硬件的虚拟化。但是虚拟机不会给宿主机提供任何抽象API，它提供的还是硬件资源（尽管是虚拟的）。
  *  这部分详见“OS VMM”，我的另一篇文章
* 由于每个虚拟机对应一块真实的硬件，所以每个虚拟机能运行独立的OS，比如OS/360, CMS( Conversational Monitor System )等
* 当一个CMS程序发起系统调用，系统会内陷到CMS( 而不是VM/370 ), 而CMS会发起普通的硬件指令调用， 这将会内陷到VM/370， 后者执行这些指令

## Virtual Machine Rediscovered

* 虚拟化的前提是CPU支持虚拟化，而许多研究使得不支持虚拟化的CPU也能虚拟化（比如x86）
* Bochs: 解释器，使得CPU“能够”虚拟化，很慢。 后来有许多改进，这类软件称为machine simulator
* type2 hypervisor：建立在type1 hypervisor之上，即建立在一个宿主机OS之上。而type1 hypervisor建立在纯粹的硬件上

## Exokernels

* 与传统的虚拟机不同的地方在于，exokernels为每个虚拟机分配资源，虚拟机知道自己被分配了多少资源。
  * 这就避免了建立映射的损耗。传统的虚拟机都认为自己拥有整个硬件，因此得为它们建立映射层

# Summary

计算机科学的发展日新月异，只有刻苦坚持，才能走在别人前面
