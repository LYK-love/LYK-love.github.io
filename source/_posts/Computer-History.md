---
title: Computer History
tags: OS Basic
categories: Computer Science
date: 2022-09-12 16:30:01
---


介绍了计算机, 操作系统和编程语言的历史

Outline:

* The first true digital computer 
* The First Generation (1945–55): Vacuum Tubes
* The Second Generation (1955–65): Transistors and Batch Systems
* The Third Generation (1965–1980): ICs and Multiprogramming
* The Fourth Generation (1980–Present): Personal Computers

<!--more-->

# The first true digital computer 

was designed by the English mathematician **Charles Babbage** (1792–1871)

* Babbage realized that he would need software for his analytical engine, so he hired a young woman named **Ada Lovelace**

《信息简史》里讲了他们的故事，向他们致敬！

# The First Generation (1945–55): Vacuum Tubes



  * 编程语言就是二进制, 写在插板(后来是穿孔卡片)上, 也没有编译器

# The Second Generation (1955–65): Transistors and Batch Systems

  * **Batch Systems：** The idea behind it was to collect a tray full of jobs in the input room and then read them onto a magnetic tape using a small (relatively) inexpensive computer, such as the **IBM 1401**, which was quite good at reading cards, copying tapes, and printing output, but not at all good at numerical calculations. Other, much more expensive machines, such as the **IBM 7094**, were used for the real computing
  * 用IBM 140把卡片翻译成磁带， 用7094处理磁带，把结果打印到磁带上， 再将结果磁带交给1401**离线**打印（不需要7094了）
  * 典型：FMS（ the Fortran Monitor System ）和 IBSYS( IBM's system for the 7094 ). 主要用于科学计算
  * 这一时期诞生了高级语言: 
    * Fortran for scienti􏰁c computation
    * Cobol for business data pro cessing
    * Lisp for symb olic computation
  * 此时的编译器已经比较复杂了: the original fortran compiler was a multipass system that included a distinct scanner, parser, and register allocator, along with some optimizations [26, 27]. 

# The Third Generation (1965–1980): ICs and Multiprogramming

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
    *  Two major versions developed:
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

# The Fourth Generation (1980–Present): Personal Computers

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
  * However, starting in 1995 a freestanding version, **Windows 95**, was released that incorporated many operating system features into it, using the underlying MS-DOS system only for booting and running old MS-DOS programs.
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
* Windows 8
  * Win7的后继，2012发行。
