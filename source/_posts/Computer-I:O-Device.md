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
* Devices
  * Transport Buses
  * Transfer Protocals
  * Physical Interfaces

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

在OS kernel层面, 使用device driver( 设备驱动 )来控制各种controller

* driver talks to a controller, giving it commands and accepting responses

* 每个controller厂商需要为每个操作系统提供一个driver

* driver一般在kernel mode工作

  * 由于各种driver互不相同，每个计算机需要的都不一样. 因此driver一般都以内核模块的形式安装到OS, 很少直接编译到内核中

  * 事实上也有运行在user mode的driver：

    > only very few current systems, such as MINIX 3, run all drivers in user space. Drivers in user space must be allowed to access the device in a controlled way, which is not straightforward



# Devices

计算机物理设备及其接口, 都被对应的device controller处理, OS通过driver来处理controller, 不需要关心真正的物理硬件

既然各种设备都通过物理接口, 由总线连接到计算机. 我们只需要关心**总线**以及**数据传输协议**就行了. 并且我还简要介绍了连接总线的**物理接口规范**.  注意到, 传输协议在软件层对应着不同的driver

## Transport Buses

ref: [讲总线的文章](https://www.cnblogs.com/liuzhengliang/p/5548451.html)

存储领域的总线ATA/SATA/PCIe/SCSI/SAS/FC， 对应**同名的物理接口**, 比如SATA接口, PCIe接口, SCSI接口....

此外，还有我们很熟悉的USB和雷电总线



注意, 有些人用"通道"来指总线

### ATA

* AT A（AT Attachment）：总的来说，ATA是一个总线技术，它并行传输数据, 总线位宽为 16bits. 因此ATA也称为**PATA**(Parallel ATA, 并行ATA ) 
  * In case you are curious what AT stands for, this was IBM’s second generation "Personal Computer Advanced Technology" built around the then-extremely-potent 6-MHz 80286 processor that the company introduced in 1984.
* ATA对应的物理接口就是ATA( or PATA )， 现在都没人用了

### SATA

* **SATA** ( **Serial ATA**, 串行ATA )对PATA进行了改进， 故名思义就是使用了串行, 规避了并行总线在高速下的串扰和同步问题
* 在2000 年发明
* SATA 只有 4 根线，分别为：发送数据线，接收数据线，电源线，地线。
* SATA 有两个标准，分别为 SATA 和 SATA II.  SATA 的有效带宽为 150MB/s ，数据速率为 1.5Gbps( 传输的数据经过了8B/10B 变换， 150MB/s*10=1.5Gbps) ， SATA II 的有效带宽为 300MB/s ，数据速率为 3Gbps 
* SATA配套的传输协议是AHCI, SATA和AHCI是HDD时代的产物, ATA总线的传输速率上限也就是几百MB, 所以SATA + AHCI在HDD时代是够用的, 虽然目前主流SSD依然支持它们, 但其实已经不够用了

### PCIe

* **PCIe( Peripheral Component Interconnect Express )**: 是一个比SATA快好几倍的总线, 2004年发明
  * PCIe是PCI的后继, 而PCI总线取代了更古老的ISA (Industry Standard Architecture)总线
    * 2004年PCIe刚发明时，流行**shared bus architecture**，许多设备用一条线传输数据，需要一个arbiter来调度
  * **PCIe可以连接各种设备**, 包括**显卡**、SSD（需要M.2接口或者PCIe接口）、无线网卡、有线网卡、声卡、视频采集卡、PCIe转接M.2接口、PCIe转接USB接口、PCIe转接Tpye-C接口
  * PCI使用**parallel bus architecture**，即将每个数据字分多条线传输。 比如32-bit数据需要32根并行的线
  * PCIe使用**serial bus architecture**，把数据包装成一个message， 点对点传输（一次连接称为一个**lane**）。
  * PICe也支持并行传输，按lane( 通道 )的个数可分为 x1 x2 x4 x8 x16 x32（最大可支持32个通道）
    * 如果PCI e x1接口的网卡插x16的插槽， 只占用一条lane
  * 微星的B450主板支持的就是PCI-E 3.0, B550支持PCI-E 4.0
  * 现在的PCIe 5.0 已经支持132GB/s 了
  * 此外，PCIe还对应着同名的传输协议( PCIe )



PCIe性能：

![PCIe Link Performance](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20IO%20Device/PCIe%20Link%20Performance.png)



PCIe 与 PCI 的区别:

| category | speed                                             |      | transport model                                              |      | hardware                 |
| -------- | ------------------------------------------------- | ---- | ------------------------------------------------------------ | ---- | ------------------------ |
| PCI      | PCI的工作频率分为33MHz和66MHz，最大吞吐率 266MB/s |      | PCI 是并行数据传输，一次传输4字节/8字节，半双工              |      | 传输PCI信号的是普通电平  |
| PCIe     | PCIe 1.0 x1 的吞吐率就达到了250MB/s               |      | PCIe是串行数据传输，全双工. 而且是**点对点传输**(当然也可以并行) |      | 传输PCIe信号的是差分电平 |

### SCSI

* SCSI( Small Computer System Interfae, 小型计算机系统专用接口 ) : 一种连接主机和外围设备的接口，支持包括硬盘、光驱及扫描仪在内的多种设备。SCSI 总线是一种**并行**总线，其优点是适应面广，性能高；缺点是价格昂贵，安装复杂

### SAS

* SAS( Serial Attached SCSI, 串行连接SCSI) : 串行化的SCSI. 和SATA总线类似, 都采用串行技术以获得更高的传输速度. 一般用于企业级硬盘

* SAS 的接口技术可以向下兼容SATA 。具体来说，二者的兼容性主要体现在物理层和协议层的兼容:

  * 在物理层，**SAS 接口和SATA 接口完全兼容**，SATA 硬盘可以直接使用在SAS 的环境中，
  * 从接口标准上而言，SATA 是SAS 的一个子标准，因此SAS 控制器可以直接操控SATA 硬盘，但是SAS 却不能直接使用在SATA 的环境中，因为SATA 控制器并不能对SAS 硬盘进行控制

  

### FC

* FC: 用于光纤

### USB

* **USB** (Universal Serial Bus, 通用串行总线) : 用于连接计算机的外部设备, 它们的I/O通常很慢
* 此外，USB还对应着同名的传输协议( USB )

### Thunder bolt

* 大名鼎鼎的雷电总线，由Intel研发，用于取代电脑上奇奇怪怪的各种总线( SCSI, SATA, USB, PCIe ... )，如果成功的话，以后电脑里只有一种总线了
  * 拿[Macbook 2021](https://support.apple.com/kb/SP854?viewlocale=zh_CN&locale=zh_CN)来说, 它拥有3个Type-C雷电4接口, 这里的
* 和USB一样，对应着同名的传输协议( Thunder bolt ). 我们说雷电的时候，既指总线也指协议，因为雷电总线好像只支持雷电协议

## Transfer Protocals

有了总线和对应的物理接口，还需要抽象的数据传输协议规范（ 就和计算机网络的协议一样 ）, 在软件层面，针对协议来编写驱动，来实现数据I/O

### AHCI

* AHCI( Serial ATA Advanced Host Controller Interface, 串行ATA高级主控接口/高级主机控制器接 ): 适配SATA和PCIe( 主要是适配SATA )， 是HDD时代的通信标准，速度比较慢

### NVMe

* NVMe( Non-Volatile Memory express, 非易失性内存主机控制器接口规范 )， 适配SATA和PCIe接口. 简而言之NVMe比AHCI快好几倍，是SSD时代的传输协议
  * NVMe建立在M.2接口上, 且使用PCIe总线
  * NVMe1.X只支持SSD,  从2.X开始也支持HDD了. 不过话说回来，现在谁还用HDD呢...

### PCIe

* 这个协议没有自己的名字，因为用于PCIe总线，就用PCIe来命名了...

### USB

* 和PCIe协议一样, 没有自己的名字... 
* USB协议目前发展到USB4

### Thunder bolt

* 和USB协议一样, 没有自己的名字... 一般称为雷电协议, 目前发展到雷电4( **Thunderbolt™4** )
* 雷电4相比USB4, 带宽更高, 兼容的传输协议也更多
  * 雷电4适配了PCIe协议和Displayport协议

## Physical Interfaces

总线需要连接到主板的物理接口上, 这里的“接口”指的是<u>物理尺寸和形状</u>, 内部的电路逻辑不做讨论



![接口, 总线和协议的关系](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20IO%20Device/%E6%8E%A5%E5%8F%A3%2C%20%E6%80%BB%E7%BA%BF%E5%92%8C%E5%8D%8F%E8%AE%AE%E7%9A%84%E5%85%B3%E7%B3%BB.png)

接口, 总线和协议的关系

### SATA Interface

* SATA接口只能接SATA总线. 这个接口比较悲催，没有自己的名字, 我们用它适配的总线( SATA )称呼它
* SATA2和SATA3总线对应不同的SATA2接口和SATA3接口

### PCIe Interface

* PCIe接口只能接PCIe总线. 这个接口和SATA接口一样, 也没有自己的名字....

### M.2 Interface

* M.2( 以前叫 NGFF( Next Generation Form Factor )，现在统一叫 M.2 了) 接口可以接SATA和 PCIe总线
* M.2接口有两种类型：Socket 2和Socket 3
  * Socket2只能接SATA总线, 可以等价于SATA接口
  * Socket3兼容Socket2, 并且能接PCIe总线

### Type A/B/C

常见的Type A/B/C也是一种物理接口

![Type A/B/C](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20IO%20Device/Type%20A%3AB%3AC.png)

* USB总线和雷电3总线一般都用Type C接口
* 不要把雷电3和Type C混为一谈，前者是总线/传输协议, 后者是物理接口

### HDMI

懂得都懂

