---
title: Transport Buses, Tranfer Protocals and Physical Interfaces
date: 2023-04-13 15:42:47
tags:
  - Hardware
categories: Electronic Engineering
---


Outline:

* Transport Buses
* Transfer Protocals
* Physical Interfaces

<!--more-->

[前面](https://lyk-love.cn/2022/08/06/Computer-I:O-Device)说过, OS通过调用Driver来处理外部设备. 而外部设备的连接是通过暴露自身**物理接口**, 通过**总线**, 按相应的**数据传输协议**连接到计算机的. 不同的数据传输协议就对应着不同的driver.

本文介绍常见的总线, 数据传输协议和物理接口.



注意, 总线, 数据传输协议和物理接口之间可能存在同名的对应. 

例如: 

* SATA是总线标准, 也是物理接口标准.
* USB是总线标准, 也是传输协议标准. 但USB不是物理接口标准;

# Transport Buses

ref: [讲总线的文章](https://www.cnblogs.com/liuzhengliang/p/5548451.html)

总线就是物理上的一根线(cable).

有很多种类型的总线.

* 存储领域的总线有: ATA/SATA/PCIe/SCSI/SAS/FC. 它们都对应**同名的Physical Interfaces**, 比如SATA接口, PCIe接口, SCSI接口. 

  * 例如: SATA总线的版本也对应着SATA接口的版本.

* 此外, 还有其他用途的总线, 例如我们很熟悉的USB和Thunder bolt.

  

注意, 有些人用"通道"来指总线

## ATA

* AT A（AT Attachment）：总的来说，ATA是一个总线技术，它并行传输数据, 总线位宽为 16bits. 因此ATA也称为**PATA**(Parallel ATA, 并行ATA ) 
  * In case you are curious what AT stands for, this was IBM’s second generation "Personal Computer Advanced Technology" built around the then-extremely-potent 6-MHz 80286 processor that the company introduced in 1984.
* ATA对应的物理接口就是ATA( or PATA )， 现在都没人用了

## SATA

https://www.techtarget.com/searchstorage/definition/Serial-ATA



![SATA cable](https://www.digitaltrends.com/wp-content/uploads/2020/09/sata-cables.jpg?fit=720%2C522&p=1)



* **SATA** ( **Serial ATA**, 串行ATA )对PATA进行了改进， 故名思义就是使用了串行, 规避了并行总线在高速下的串扰和同步问题

  * 在2000 年发明

* SATA 只有 4 根线, 分别为：发送数据线, 接收数据线, 电源线, 地线.

  

### SATA Types

SATA 有三个版本, 对应物理接口也有三个版本:

* SATA: 正式名稱爲**SATA 1.5Gb/s**, 是第一代SATA接口. 有效带宽为 150MB/s, 数据速率为 1.5Gbps( 传输的数据经过了8B/10B 变换, 150MB/s*10=1.5Gbps) .

* SATA II: 正式名稱爲**SATA 3Gb/s**, 是第二代SATA接口.  有效带宽为 300MB/s , 数据速率为 3Gbps.

* **SATA III**: 正式名稱爲**SATA 6Gb/s**, 是第三代SATA接口, 有效带宽为 600MB/s , 数据速率为 6Gbps.

   

  

* SATA配套的传输协议是AHCI. SATA和AHCI是HDD时代的产物, ATA总线的传输速率上限也就是几百MB, 所以SATA + AHCI在HDD时代是够用的, 虽然目前主流SSD依然支持它们, 但已经不够用了.

* SATA II向后兼容SATA I. SATA III向后兼容SATA I和SATA II. 但是, 由于低版本接口的数据传输率的限制, 使用低版本的接口时数据传输率也会降低.

  * 例子: 闪迪至尊极速固态硬盘支持SATA 6Gb/s接口并且当连接到SATA 6Gb/s 接口时，顺序读速度和写速度分别能达到550/520MB/s。但是，当连接到SATA 3 Gb/s 接口时，顺序读速度和顺序写速度则分别能达到285/275MB/s

## PCIe

![PCIe cable](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/PCIe%20cable.png)



* **PCIe( Peripheral Component Interconnect Express )**: 是一个比SATA快好几倍的总线, 2004年发明.
  * PCIe是PCI的后继, 而PCI总线取代了更古老的ISA (Industry Standard Architecture)总线
    * 2004年PCIe刚发明时，流行**shared bus architecture**，许多设备用一条线传输数据，需要一个arbiter来调度
  * **PCIe可以连接各种设备**, 包括**显卡**、SSD（需要M.2接口或者PCIe接口）、无线网卡、有线网卡、声卡、视频采集卡、PCIe转接M.2接口、PCIe转接USB接口、PCIe转接Tpye-C接口
  * PCI使用**parallel bus architecture**，即将每个数据字分多条线传输。 比如32-bit数据需要32根并行的线
  * PCIe使用**serial bus architecture**，把数据包装成一个message， 点对点传输（一次连接称为一个**lane**）。
  * PICe也支持并行传输，按lane( 通道 )的个数可分为 x1 x2 x4 x8 x16 x32（最大可支持32个通道）
    * 如果PCI e x1接口的网卡插x16的插槽， 只占用一条lane
  * 微星的B450主板支持的就是PCI-E 3.0, B550支持PCI-E 4.0
  * 现在的PCIe 5.0 已经支持132GB/s 了
  * PCIe是[NVMe](#NVMe)协议最常使用的总线.



### PCIePerformance

![PCIe Performance](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/PCIe%20Performance.png)



![PCIe Link Performance](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/PCIe%20Link%20Performance.png)

### PCIe vs PCI

PCIe 与 PCI 的区别:

| category | speed                                             |      | transport model                                              |      | hardware                 |
| -------- | ------------------------------------------------- | ---- | ------------------------------------------------------------ | ---- | ------------------------ |
| PCI      | PCI的工作频率分为33MHz和66MHz，最大吞吐率 266MB/s |      | PCI 是并行数据传输，一次传输4字节/8字节，半双工              |      | 传输PCI信号的是普通电平  |
| PCIe     | PCIe 1.0 x1 的吞吐率就达到了250MB/s               |      | PCIe是串行数据传输，全双工. 而且是**点对点传输**(当然也可以并行) |      | 传输PCIe信号的是差分电平 |

## SCSI

* SCSI( Small Computer System Interfae, 小型计算机系统专用接口 ) : 一种连接主机和外围设备的接口，支持包括硬盘、光驱及扫描仪在内的多种设备。SCSI 总线是一种**并行**总线，其优点是适应面广，性能高；缺点是价格昂贵，安装复杂

## SAS

* SAS( Serial Attached SCSI, 串行连接SCSI) : 串行化的SCSI. 和SATA总线类似, 都采用串行技术以获得更高的传输速度. 一般用于企业级硬盘

* SAS 的接口技术可以向下兼容SATA 。具体来说，二者的兼容性主要体现在物理层和协议层的兼容:

  * 在物理层，**SAS 接口和SATA 接口完全兼容**，SATA 硬盘可以直接使用在SAS 的环境中，
  * 从接口标准上而言，SATA 是SAS 的一个子标准，因此SAS 控制器可以直接操控SATA 硬盘，但是SAS 却不能直接使用在SATA 的环境中，因为SATA 控制器并不能对SAS 硬盘进行控制

  

## FC

* FC: 用于光纤

## USB

常见的USB logo: 

![USB logo](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/USB%20logo.png)



USB logo on devices:

![USB logo on devices](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/USB%20logo%20on%20devices.png)

* **USB** (Universal Serial Bus, 通用串行总线) : 用于连接计算机的外部设备, 它们的I/O通常很慢
* 此外, USB还对应着同名的传输协议( USB ). 
* USB是总线标准和传输协议标准, 但不是物理接口标准. 因此不存在“USB物理接口”.

## Thunderbolt

Thunderbolt-4 logo on cable:

![Thunderbolt-4 logo on cable](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/Thunderbolt-4%20logo%20on%20cable.png)



* Thunderbolt(雷电总线): 由Intel研发, 用于取代电脑上奇奇怪怪的各种总线( SCSI, SATA, USB, PCIe ... ). 如果协议能推广, 以后电脑里只需要一种总线.
  * [Macbook 2021](https://support.apple.com/kb/SP854?viewlocale=zh_CN&locale=zh_CN)拥有3个 Type-C Thunderbolt-4 物理接口.
  * 从雷电3开始, 使用Type-C物理接口.
* 和USB一样拥有同名的传输协议( Thunder bolt ). 我们说雷电的时候, 既可以指总线也可以指协议, 因为雷电总线好像只支持雷电协议.
* Thunderbolt是用于取代各种总线, 因此是各种总线的超集. 例如, Thunderbolt是USB的超集, 因此可以在Thunderbolt线上传输USB信号. 由于Thunderbolt 3, 4都使用Type-C接口, USB也常常使用Type-C接口, 因此在生活中, <u>一根Type-C Thunderbolt线就可以当作Type-C USB线来用.</u>
  * 反过来, Type-C USB线并不能替代Type-C Thunderbolt线.

# Transfer Protocals

有了总线和对应的物理接口, 还需要抽象的数据传输协议( 就和计算机网络的协议一样 ), 在软件层面，针对协议来编写驱动，来实现数据I/O.

## AHCI

* AHCI( Serial ATA Advanced Host Controller Interface, 串行ATA高级主控接口/高级主机控制器接 ): 适配SATA和PCIe( 主要是适配SATA ), 是HDD时代的通信标准，速度比较慢

## NVMe

* **NVMe**( Non-Volatile Memory express, 非易失性内存主机控制器接口规范 ):  适配**SATA和PCIe**接口. 简而言之NVMe比AHCI快好几倍，是**SSD**时代的传输协议.
  * **NVMe建立在[M.2接口](#M.2 Interface)上, 且使用[PCIe总线](#PCIe).**
    * 很多商家把NVMe和PCIe混用. NVMe是协议, 而PCIe是物理上的总线.
  * NVMe1.X只支持**SSD**,  从2.X开始也支持HDD. 不过现在很少有人用HDD了.

## USB

* 和PCIe协议一样, 没有自己的名字... 
* USB协议目前发展到USB4

## Thunder bolt

* 和USB协议一样, 没有自己的名字... 一般称为雷电协议, 目前发展到雷电4( **Thunderbolt™4** )
* 雷电4相比USB4, 带宽更高, 兼容的传输协议也更多
  * 雷电4适配了PCIe协议和Displayport协议

# Physical Interfaces

总线需要连接到主板的物理接口上, 这里的“接口”指的是<u>物理尺寸和形状</u>, 内部的电路逻辑不做讨论.



![接口, 总线和协议的关系](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/%E6%8E%A5%E5%8F%A3%2C%20%E6%80%BB%E7%BA%BF%E5%92%8C%E5%8D%8F%E8%AE%AE%E7%9A%84%E5%85%B3%E7%B3%BB.png)

## SATA Interface

* SATA接口只能接SATA总线. 这个接口比较悲催，没有自己的名字, 我们用它适配的总线( SATA )称呼它
* SATA2和SATA3总线对应不同的SATA2接口和SATA3接口

## PCIe Interface

* PCIe接口只能接PCIe总线. 这个接口和SATA接口一样, 也没有自己的名字....

## M.2 Interface

* M.2( 以前叫 NGFF( Next Generation Form Factor )，现在统一叫 M.2 ) 接口: 被设计为支持**NVMe**协议, 可以接SATA和PCIe总线.
* M.2接口有两种类型：Socket 2和Socket 3.
  * Socket2( aka SATA M.2 ): 只能接SATA总线, 可以等价于SATA接口.
  * Socket3( aka PCIe M.2): **兼容**Socket2, 并且能接PCIe总线.



### M.2 Slots

on motherboard:

![M.2 slots](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/M.2%20slots.png)



### M.2 Connector

#### SSD

on SSD:

![SSD with M.2 connector](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/SSD%20with%20M.2%20connector.png)

#### Wi-Fi Card

![Wi-Fi Card with M.2 connector](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/Wi-Fi%20Card%20with%20M.2%20connector.png)



#### GPU



![GPU with M.2 connector](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/GPU%20with%20M.2%20connector.png)

It seems amazing, but since M.2 can carry PCI Express, you can use a graphics card and connect it to a system. You can find M.2 adapters for full PCI Express 16x cards, where you can connect and use graphics cards. 



## Type A/B/C

常见的Type A/B/C也是物理接口

![Type A/B/C](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Transport%20Buses%2C%20Tranfer%20Protocals%20and%20Physical%20Interfaces/Type%20A%3AB%3AC.png)

* USB总线和雷电3总线一般都用Type C接口
* 不要把雷电3和Type C混为一谈，前者是总线/传输协议, 后者是物理接口

## HDMI

参见[Common HDMI Products](https://lyk-love.cn/2023/04/13/Common-HDMI-Products)

