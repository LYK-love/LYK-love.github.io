---
title: OS Basic
tags: OS Basic
categories: Computer Science
date: 2021-10-05 20:28:21
---

My understanding of OS

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

  (shell的概念详见*Shell Tools*)

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



# COMPUTER HARDWARE

![Computer Hardware overview](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Computer%20Hardware%20overview.png)



注意，这里只介绍现代计算机的基本结构，没有包括GPU和VRAM等组件， 也没有包括对各种存储介质的介绍( RAM, ROM, Disk)。

GPU的内容(不包括VRAM)详见拙著*GPU*

存储介质(包括Cache)和VRAM的内容详见拙著*Computer Storage*



## Top-view Example



假设计算机中存在`hello`程序:`echoh hello,world`

我们以在shell上输入`./hello`来执行`hello`程序为例， 在硬件视角下，程序执行步骤如下:

1. shell程序持续运行，等待用户输入，用户输入通过I/O bus传输到I/O bridge, 再传输到*system bus*, 经过*bus interface*传输到*reister file*. 然后沿上图的方向传输到内存

   ![Top-view Example 1](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Top-view%20Example%201.png)

1. 当用户输入Enter键，shell知道我们停止了输入，就把`hello`程序从磁盘中读到内存:

   ![Top-view Example 2](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Top-view%20Example%202.png)

3. 最后，内存中的数据被读到CPU， CPU执行该程序, 将结果输出到显示设备

   * 这一步(数据从内存传输到CPU)详见下文*Accessing Main Memory*

   ![Top-view Example 3](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Top-view%20Example%203.png)

   


我们也可以看到，硬盘到主存的data-movement是很频繁也很耗时间的，因此诞生出了Cache，这是CPU内的存储结构，采用SRAM。

## Buses

* *bus*: 总线。 就是一组传输地址、数据和控制信号的电线。 总线传输数据的基本单位是*word*， 在不同的硬件实现上，*word*的大小也不同，通常是4或8 Byte
  * 基于不同的总线设计， 数据和地址可以共享总线，也可以使用不同总线。 不同设备也可以共享总线。 总线传递控制信号，来对事务进行同步。
* 总线的类型：
  * *system bus*
  * *memory bus*
  * *I/O bus*： 被多个I/O设备共享

* original IBM PC最早使用了单总线架构,  为了更快的IO速度和CPU-to-memory traffic，额外的总线被引入。 形成了现代的x86系统
* This system has many buses (e.g., cache, memory, PCIe, PCI, USB, SATA, and DMI), each with a different transfer rate and function. The operating system must be aware of all of them for configuration and management. 

* The main bus is the **PCIe**  bus.



* the CPU talks to memory over a fast **DDR3** bus, to an external graphics device over PCIe and to all other devices via a **hub** over a **DMI** (Direct Media Interface) bus. The hub in turn connects all the other devices, using the Universal Serial Bus to talk to  USB devices, the SATA bus to interact with hard disks and DVD drives, and PCIe to transfer Ethernet frames.
  * PCI接口的设备另外放在一个hub processor 内
* Moreover, each of the cores has a dedicated cache and a much larger cache that is shared between them. Each of these caches introduces another bus. 
  每个core有一个专用cache，所有core共享一个更大的cache，每个cache拥有自己的总线
* Intel 和 MS设计了**plug and play**系统，可以自动收集IO设备信息，集中分配中断优先级和I/O（设备的）寄存器地址

  * 在此之前，这些都要手动分配

## CPU

### Components

CPU是计算机指令的执行单元。 由四部分组成:

1.  *program counter* (PC): 一个 *word-size storage (or register)*，也称为**栈指针**，永远指向当前正在执行的指令的地址
2. *register file*: 一个small storage device, 由一组word-size registers组成，每个寄存器都有其独特的名字
3. *arithmetic/logic unit* (ALU)： 用于计算
4. *bus interface*：一组电路，用于CPU和主存之间的数据传输

### Features

* 每个CPU都有自己特殊的指令集。ARM处理器不能执行x86程序
* 由于对内存的存取所花的时间比执行一条指令还要长，CPU内部会有寄存器。
* 许多寄存器对用户**可见**
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

### CPU Operations

basic cycle of CPU: 取指、译指、执行

### CPU Instructions

抽象地说， CPU指令分为四种：

-  *Load:* 从主存中copy一个byte或word到一个寄存器里， 这会覆盖寄存器里该位置上之前的值
-  *Store:* 从寄存器里copy一个byte或word到主存的某个位置，这会覆盖主存里该位置上之前的值
- *Operate:* 将两个寄存器里的值copy到ALO， 后者进行算数计算，并将结果存入一个寄存器，这会覆盖该寄存器里该位置上之前的值
- *Jump:* 该指令含有一个word， 记录了要跳转到的目标指令的位置。 CPU会copy该字段到PC，覆盖PC之前的值

### Multithread and Multicore Chips

* multithreading: 允许CPU拥有两个线程并且在**纳秒**级的时间里切换。 **多线程并不是并行**，因为同一时间还是只有一个程序在CPU上运行
  *  如果一个程序要读取内存（花的时间比较长），那么多线程的CPU可以切换到另一个程序
  * 多线程带来的问题是：每一个线程都会被OS视为独立的CPU. 考虑一个双CPU的系统，每个CPU有两个线程。当有两个线程的任务时，OS可能会把它们全部交给同一个CPU上的两个线程，而这是很浪费的
* 许多CPU芯片上还有多个(几十个)processors or **cores**  使用多核芯片需要一个多处理器的OS
* GPU拥有上千个core, 适用于许多并行执行的小规模计算， 在顺序计算上并不突出。

### Instruction Set

CPU指令集可以分为CISC和RISC两类.



x86和arm的那些历史就不讲了. 这里理清一些概念.

* x86和x86_64: x86是32位的, x86_64是x86的64位版本
* arm, arm64和aarh64: 顾名思义, arm是32位的, arm64是arm的64位版本. 并且arm64和aarh64合并了, 所以arm64和aarh64是一个东西. 
  * M1的指令集就是arm64. 低功耗的移动设备和嵌入式设备基本也都是arm架构.
* 因为桌面级CPU基本都是64位的, 要么是x86_64, 要么是arm64, 所以我们常说的x86, arm其实指代的是它们的64位版本.
* arm和x86: 简单来说, arm属于RISC, 功耗较低. x86属于CISC, 性能较高.



## Main Memeory 

* *main memory*（OR *system memory* ）：主存。 在冯诺依曼架构中，处理器( 包括ALU和Controller )与存储器进行数据交互。  

  * 我们通常就用RAM来指主存。 更精确地说，主存的材质是DRAM
  * 此外还存在显存(VRAM)， 宽泛地讲， 和CPU交互的是主存，和GPU交互的就是显存
  * **在通常的语境下，我们说的RAM都是主存，也就是和CPU交互的DRAM**

  

### Accessing Main Memory

数据通过bus( 总线， 见下文 )在CPU和主存间传输。 每一次CPU和主存间的数据传输就是一次*bus transaction*

整个过程的I/O类型是DMA(见下文*I/O Devices -> I/O -> DMA*)

* A *read transaction* transfers data from the main memory to the CPU. 
* A *write transaction* transfers data from the CPU to the main memory.



![Example bus structure that connects the CPU and main memory](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Example%20bus%20structure%20that%20connects%20the%20CPU%20and%20main%20memory.png)

上图展示了CPU和主存进行数据传输的基本模型。 包含了三个组件：CPU、 I/O bridge（ 是一个芯片组， 包含了*memory controller*）、主存。 CPU和 I/O bridge通过*system bus*连接，  I/O bridge和主存通过*memory bus*连接。 当然如同之前介绍的,  I/O bridge还会把*system bus*和*memory bus*连接到*I/O bus*，它由I/O设备共享



考虑如下指令:

```assembly
movq A,%rax # 将地址A指向的内容赋值给rax
```

CPU的*bus interface*会开始一个*write transaction*, 步骤为:

1. CPU将地址A放到系统总线上，  I/O bridge将该signal传递给*memory bus*

   ![Accessing Main Memory step 1](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Accessing%20Main%20Memory%20step%201.png)

2. 主存感知到*memory bus*上的信号(地址A)， 从DRAM中读取A处的数据x，写进*memory bus*，  I/O bridge会将其传递给*system bus*

   ![Accessing Main Memory step 2](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Accessing%20Main%20Memory%20step%202.png)

3. 主存感知到*memory bus*上的信号( 数据x )，从*memory bus*读数据，然后copy到%rax

   ![Accessing Main Memory step 3](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Basic/Accessing%20Main%20Memory%20step%203.png)






## Disk

* Disk：称为硬盘，是非易失的外部存储设备。





## I/O Devices

I/O设备的介绍详见拙著*Computer I/O Device*

### I/O

* IO有三种类型：
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

## Booting the Computer

计算机启动时，**首先加载**硬件驱动程序，硬件驱动程序有BIOS和UEFI， 这里简要介绍BIOS, 详见拙著*Linux Hardware Basic*



BIOS对应的磁盘分区格式是MBR



* **BIOS**（Basic Input Output System）：PC主板上的一个程序
  * The BIOS contains low-level I/O software, including procedures to read the keyboard, write to the screen, and do disk I/O, among other things. 
  * Nowadays, it is held in a **flash RAM**, which is nonvolatile but which can be updated by the operating system when bugs are found in the BIOS.

1. 计算机开机时，BIOS启动，它会检查RAM和键盘等基础外设的连接和响应情况
   * It starts out by scanning the PCIe and PCI buses to detect all the devices attached to them. 
   * 如果设备和上次启动时不一样，新的设备将被配置
2. 通过CMOS中的启动设备列表，BIOS找到启动设备，后者的第一个扇区将被读进内存并执行，检查该扇区是否是MBR扇区，是的话会加载其中的boot loader
3. 一段boot loader程序被从MBR扇区读入， boot loader是OS提供的，因此能够读取OS的核心文件
4. boot loader读取核心文件
5. 核心文件会加载OS
6. OS问询BIOS，得到配置信息，对每个设备，OS检查自己是否有对应驱动，若没有，则通知用户去下载。
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

## System Calls & Library Functions 

 系统调用和库函数都以C函数的形式出现 

系统调用：

* Linux内核的对外接口;
* 用户程序和内核之间唯一的接口;
* 提供最小接口 



库函数：

* 依赖于系统调用; 提供较复杂功能 
  * 例：标准I/O库

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



refs：

* *Modern  Operating Systems* 
* *Operating Systems Three Easy pieces* 
* *CSAPP*
