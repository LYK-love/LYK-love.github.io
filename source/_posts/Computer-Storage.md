---
title: Computer Storage
tags: Hardware
categories: Computer Science
mathjax: true
date: 2022-07-31 22:02:16
---


Outline:

* Basic Ideas:
  * Cache
  * Main Memory
  * VRAM
  * Disk
* Storage Material
  * RAM
  * ROM

<!--more-->

# Basic Ideas

计算机的存储架构是分层的：

![memory hierarchy](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/memory%20hierarchy.png)

* CPU registers: 也就是CPU的 *register file*， 对它的访问没有延迟
* cache memory: 有L1，L2， L3 ...，差别是timing 。访问L1没有延迟，访问L2有1-2个时钟周期的延迟
* main memory: 主存， the work house of memory system,也被称为RAM。 （当然更精确的说法是DRAM）
* disk: 硬盘，是一种外部存储设备，最慢

越上层速度越快，价格越贵，其容量也就越小



还有一种*虚拟内存*，这是进程视角下的内存， 包含了主存和一部分从硬盘中置换出来的存储空间, 由**MMU**( Memory Management Unit )完成。总之，虚拟内存是一个抽象的内存概念，和现实的存储结构没有关系。

## Cache

* Cache， 位于CPU内部的存储设备，其材质一般是SRAM. 一般有多级cache, 如L1/L2/L3

## Main Memory

* *main memory*（OR *system memory* ）：主存，也称为*system memory*. 在冯诺依曼架构中, 处理器( 包括ALU和Controller )与存储器进行数据交互, 这里我们把和CPU交互的RAM称为**主存**.
* 后面会提到， 主板上的内存条( *memory module*, 由DRAM组成 )的集合就是主存，提供给CPU一个统一的内存视图
  
* **在通常的语境下，我们说的RAM都是主存，也就是和CPU交互的DRAM**



* 板载内存( on-board memory )：焊接在电路板上的内存就是板载内存，它无法更换。 与之对应的是可插拔的内存条。
  * 对于系统RAM，除了板载内存，还可以用可插拔的内存条。 
  * 不过对于显存( VRAM )，目前已经不存在可插拔的显存了，所以所有**显存都是板载的**( 起码目前为止 )
  * 系统RAM的板载内存一般焊接在主板上，而显存一般焊接在显卡的PCB( **印刷电路板**，也就是显卡的“主板”)上

## VRAM

[显存的文档](https://zhuanlan.zhihu.com/p/462191421)

* *Video RAM (VRAM)*: 显存， 用作GPU的frame buffer. 广义地讲, 显存不是一种特定的RAM材质,  **任何用作主存的RAM( 也就是DRAM )都可以用作显存**。 事实上我们可以把和CPU交互的DRAM叫主存，和GPU交互的叫显存。 
  * 当然了，在带宽、延迟和速度方面，CPU和GPU的需求是不同的。因此VRAM的材质一般采用GDDR( 下文会介绍 )
  * VRAM主要存储纹理数据( texture data )，用于和GPU交互。 因此它也被称为 *Texture Memory*
  * 当显存不够用时，GPU将会不得不**从主存中分配内存来作为VRAM**。 甚至如果电脑采用集显，也就是和CPU集成到一起的GPU， GPU就没有自己的RAM。 GPU会将系统RAM的一部分作为VRAM，显而易见这很慢
  * 也有一些计算机使用“统一内存”， 即CPU和GPU都使用为GPU设计的RAM，在运行时为两个处理器动态分配。这样就避免了给GPU和CPU使用不同的内存。
    * 比如PlayStation 5和M1，统一使用GDDR
    * 作为一个额外的好处，如果CPU和GPU都需要相同的数据，就不需要在两套不同的内存中拥有两个副本。
  * 有些厂商会提供同一型号但是不同VRAM容量的显卡，其实一般来说，为了单单高一点VRAM就加钱没啥必要。。。
* 显存的指标：显存主要包括capacity、frequency和bandwidth这三个参数

## Disk

Disk：称为硬盘，是非易失的外部存储设备。因为早期的硬盘都是机械硬盘( HDD )，成盘状，所以称为硬“盘”

* 机械硬盘( HDD ):拥有磁头，扇区和盘片, 材料和ROM没关系. 

  * HDD比较重，而且运行时会呼呼地转，发出噪音. HDD价格低容量大，速度也远远慢于SSD. 适合存储一些音频、视频数据
  * 现在M.2 NVMe固态硬盘速度能达到3500MB/s，就算是普通的SATA SSD速度也能到550MB/s，而机械硬盘现在能到200MB/s就很不错了

* **固态硬盘**（ SSD， Solid State Disk )：

  * SSD**没有物理上的磁头和盘片，也没有扇区和磁道等概念**. SSD的存储原理和机械硬盘不同，它是闪存盘的matrix，用某种控制芯片将多个**NAND FLASH**颗粒整合,
    * Flash属于广义上的ROM( 见下文*ROM* ). 
  * 严格地讲，SSD不算Disk， 不过它在计算机架构中确实承担着Disk的职能( 外部存储设备 )，所以把SSD放入Disk一类

  * SSD价格贵, 速度快. 因为没有磁头, 寻道时间几乎为0. 因为没有机械部件, 因此抗震荡, 低功耗, 无噪音
  * 现在流行的使用MVMe协议的SSD

机械硬盘只能实现 50-120 MB/秒的写入速度，而固态硬盘能达到 550 MB/秒的 SATA 总线极限值



注意，虽然SSD材料是ROM，但磁盘和ROM是两个概念。 现代的磁盘包括了HDD和SSD， 已经不是一个材料概念，而是一个计算机架构中的抽象的功能的概念。 而ROM是一个材料的概念。不能把ROM和Disk混为一谈。

# Storage Material

## RAM

RAM（ random access memory ）： 是volatile（易失性）的存储材料， 也就是说断电就会丢失所有信息。 RAM常用来做计算机的内存，包括cache和主存等



RAM分为两类：

* SRAM: Static RAM， 更快更贵，一般用作Cache

- DRAM: Dynamic RAMS， 比SRAM慢，也更便宜，一般用作主存和显存



我们规定RAM芯片的基本存储单位是bit，对应的物理结构称为cell

### SRAM

SRAM 将每个bit存储在一个 *bistable* ( 双稳态 )的cell里。每个cell用一个 *six-transistor*电路实现。 



双稳态：

![bitable](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/bitable.png)


上图是一个双稳态电路，它永远保持在两个不同的电压状态，也就是在上图左（右）稳态。其他任何状态都是不稳定的——电路会从不稳定状态迅速地转移到其中一个稳定状态。

上图其实有个地方应该是有偏差的，也就是中间那个状态。原则上来说，当左右两边的作用力相同时，钟摆在垂直的时候也能无限期地保持平衡，但是当左右两边稍微发生一点扰动，这个状态就会变成左稳态或右稳态之一。而且一旦倒下，便不会有机会再站起来。我们称这个状态为亚稳态。

因为SRAM有双稳态的特性，**只要有电，它就会永远的保持它的值**。**即使有干扰来扰乱电压**，当干扰时，电路就会恢复到稳定值。但是没有电的话，双稳态的状态就不能保持了，意味着数据也就丢失了。这就是我们常说，电脑断电后内存数据就会丢失的原因。

### DRAM

DRAM将每个位存储为对一个电容的充电。DRAM可以制造得非常密集——每个单元由一个电容和一个访问晶体管组成。但是与SRAM不同的是，DRAM存储器的单元对干扰非常敏感。当电容的电压被扰乱之后，它就永远不会恢复了。

下图总结了SRAM和DRAM的区别： 

![Characteristics of DRAM and SRAM memory](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/Characteristics%20of%20DRAM%20and%20SRAM%20memory.png)

* SRAM的存取比DRAM快
* SRAM对干扰不敏感
* SRAM每单元使用更多晶体管，密集度低，比DRAM更贵，功耗更大

#### DRAM Structure

* DRAM芯片的每$w$个cell组成一个supercell，每$d$个supercell组成一个DRAM芯片的存储部分。
  * 即， 一个$d \times w$的DRAM总共存储了$d \times w $ bit
* supercell被组织成一个$r$行$c$列的长方形阵列，其中$r \times c = d$.  每个DRAM内使用$(i,j)$二维地址对supercell进行寻址( 即$(行号， 列号)$ )
  * 也就是说，DRAM的**寻址的基本单位**是supercell， DRAM没有提供机制给supercell内部的cell寻址



example：

![DRAM chip exp](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/DRAM%20chip%20exp.png)

* 上图展示了一个$16 * 8 $的DRAM芯片，其中含有$d = 16$个supercell，每个supercell包含$w = 8 $个cell，$r=4$行， $c=4$列
  * 每个supercell含有8个cell，相当于每个supercell存储了1 Byte， 即**该DRAM是按字节寻址的**

#### pin

* pin( 引脚 ): 对芯片的外部物理接口的抽象称呼，这里我们只讨论用于信息I/O的pin， 每个携带1 bit信号。 其实不是所有的pin都能用来信息I/O， 比如Vcc和GND，除了供电，就没有其他用处。



![DRAM pin](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/DRAM%20pin.png)

DRAM芯片通过pin来进行信息传输，上图给出了两组pin：

1. 8个data pin，能在芯片中I/O一个字节
2. 2个addr pin，能携带一个2 bit的地址，用于对supercell的寻址
   * 注意到，这个DRAM是4行4列的，所以一次只能对一维进行寻址

#### DRAM Addressing

每个DRAM芯片被连接到某个称为*memory controller*的电路。这个电路可一次向每个DRAM芯片I/O $w$位。*memory controller*读取supercell $(i,j)$的内容的步骤为：

1. *memory controller*会通过addr pin发送2 bit的行地址$i$

   * 这个操作称为*a RAS (row access strobe) request*

   * DRAM此时会选中supercell mateix的第$i$行，复制到内部行缓冲区:

     ![DRAM addressing 1](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/DRAM%20addressing%201.png)

2. 再发送2 bit的列地址$j$

   * 这个操作称为*a CAS (col access strobe) request*

   * DRAM此时会选中行缓冲区的第$j$列. 该元素就是supercell$(i,j)$的1 Byte内容 

     ![DRAM addressing 2](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/DRAM%20addressing%202.png)

3. DRAM然后会将这1 Byte内容通过8个data pin发送给*memory controller*



这个模型把DRAM的supercell组织成二维而不是一维数组，是为了降低芯片上addr pin的数量。 如果supercell被组织成一维数组，就需要$\log_216 = 4$个addr pin. 但是二维数组就需要如上所述的两次寻址，要花更多的时间

这里考虑最简情况，把一个DRAM芯片当做一个*memory module*。稍后我们会看到，一个*memory module*由多个DRAM组成，由 *memory module*和*memory controller*交互

#### Memory Module

* *memory module*: DRAM被组织成*memory module*，插到主板的插槽上
  * *memory module*也就是我们常说的**内存条** 
* *main memory*：主存，也称为*system memory*. 主板上内存条的集合，提供给计算机一个统一的内存视图，这就是主存
  * 此外还存在“显存”， 其实二者是一样的。 给CPU用的叫主存，给GPU用的叫显存



![Memory Module](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/Memory%20Module.png)

* 上图展示了一个容量为64 MB 的*memory module*, 由8个 8MB * 8 （ $d = 8* 1024 * 8, w = 8$ ）的DRAM芯片组成，按0～7编号。每个supercell存储$w = 8$ bit 信息。

* 我们假设一个word为8 Byte. 地址A $(i,j)$上的一个word 就由这8个DRAM的地址为$(i,j)$的supercell组成。 也就是说DRAM0的$(i,j)$存储A的第0个Byte, DRAM1的$(i,j)$存储A的第1个Byte, 以此类推 8个DRAM中读取的8个Byte被发送给*memory controller*， 组合成一个word，再发送给CPU

  

## Enhanced DRAMs

除了上述我们介绍的常规DRAM，还有很多变种的DRAM

### FPM DRAM

* *Fast page mode DRAM (FPM DRAM)*: 传统的DRAM在读取$(i,j)$ 数据时，会先将第$i$行copy到行缓冲区，然后读取第$j$列将其返回， 丢弃该行的其他元素。 如果workload是要读取第*i* 行的所有supercell，那么传统DRAM会在每个RAS/CAS后丢弃剩余数据，重新加载行缓冲区。这无疑是十分低效的。 FPM DRAM在完成$(i,j)$的RAS/CAS后， 不会丢弃剩余的元素。 因此对于第$i$行其他元素的RAS/CAS，可以直接返回结果

### EDO DRAM

* *Extended data out DRAM (EDO DRAM)*: 比FPM DRAM更先进， 可以把多个CAS缓冲CAS为一组，一起发送

  

### SDRAM

* *Synchronous DRAM (SDRAM)*： 传统DRAM， FPM DRAM， EDO DRAM都是以异步方式进行I/O的(使用RAS和CAS两个独立的信号)。 而SDRAM的I/O都在系统时钟的上升沿执行，这使得它可以同步地存取数据。 简言之，SDRAM比传统DRAM快很多
* SDRAM的材质分为双极性与CMOS。
* **主板上就用了一个CMOS硬件来记录时间和硬件配置参数**，比如该从哪个盘启动。该硬件很悲催，没有自己的名字，我们就称为CMOS。 CMOS里自带一个小电池，因此虽然是易失性的，断了电也能工作

### DDR SDRAM

* *Double Data-Rate Synchronous DRAM (DDR SDRAM)*：DDR SDRAM是SDRAM的增强版，在上升/下降沿都执行I/O
* 随着 *prefetch buffer*( 预取缓冲区，决定了有效带宽 ) 的大小，DDR已经分为DDR (2 bits), DDR2 (4 bits), DDR3 (8 bits), DDR4(  ) and  DDR5( 16 bits )
  * 注意， DDR4的prefetch和3一样，都是8 bit，但是DDR4提高了核心频率，所以总线速度得以提高
  * DDR的"Double Data-Rate"指的是会在系统时钟的**上升和下降沿都执行I/O**，并不意味着DDR的速度是SDRAM的两倍。 事实上，随着DDR技术的进步，速度差距是越来越大的。



|                      | SDRAM | DDR       | DDR2  | DDR3       | DDR4  |
| :------------------- | :---- | :-------- | :---- | :--------- | :---- |
| prefetch buffer size | 1 bit | 2 bit     | 4 bit | 8 bit      | 8 bit |
| 电压                 | 3.3   | 2.5 - 2.6 | 1.8   | 1.35 - 1.5 | 1.2   |

### GDDR

* *GDDR( Graphics Double Data Rate DRAM )*： 一般用作VRAM( 显存 )，带宽更高，速度更快， 支持并发读写（当然容量也更小）。 市面上常见的有GDDR6
* GDDR和主存的普通DDR的最大区别就是前者有一个**宽的“总线”**， 总线越宽，数据传输速率越高。 由于图形涉及并行操作大量数据，因此内存总线的宽度非常重要。

## ROM

ROM( Read-Only Memory ):  顾名思义是不可写的一种存储材质，它是**novolatile**( 非易失性)的， 数据不会随着断电而丢失。 

* 不过，“不可写”其实是生产工艺的限制，而不是什么设计上的特性。
*  后来ROM发展出了可擦写的存储材质EPROM和EEPROM，因为是可擦写的，所以严格来讲不算"Read-Only"， 但是它们确实是在ROM技术上发展出来的，因此也称为ROM。 后来在这两种技术的发展上又发展出了**NAND FLASH**闪存，这就是我们现在用的U盘中用到的技术，同样，因为其体积小，容量和速度均不错，现在手机存储中的emmc颗粒也是用的这种技术，所以有手机厂商就把手机的存储容量约定俗成为ROM，其继承ROM断电不丢失数据的特性，而且有着较快的速度。（但是是**可擦写**的哦）
  * EEPROM和flash都有写入次数限制

refs: CSAPP
