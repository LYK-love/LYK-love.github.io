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

# Intro

存储器由一定数量的单元构成，每个单元可以被唯一标识，每个单元都有存储一个数值的能力。

- 地址：单元的唯一标识符（采用二进制）
- 地址空间：可唯一标识的单元总数
- 寻址能力：存储在每个单元中的信息的位数•大多数存储器是字节寻址的，而执行科学计算的计算机通常是64位寻址的



![image-20230812005129873](/Users/lyk/Library/Application Support/typora-user-images/image-20230812005129873.png)



# The Memory Hierarchy

计算机的存储架构是分层的：

![memory hierarchy](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/memory%20hierarchy.png)

* CPU registers: 也就是CPU的 *register file*， 对它的访问没有延迟
* cache memory: 有L1，L2， L3 ...，差别是timing 。访问L1没有延迟，访问L2有1-2个时钟周期的延迟
* main memory: 主存, the work house of memory system, 也被称为RAM.（当然更精确的说法是DRAM）
* disk: 硬盘，是一种外部存储设备，最慢

越上层速度越快，价格越贵，其容量也就越小



还有*虚拟内存* , 这是进程视角下的内存， 包含了主存和一部分从硬盘中置换出来的存储空间. 通过硬件**MMU**( Memory Management Unit )实现虚拟内存地址和物理内存地址的转换.

总之，虚拟内存是一个抽象的内存概念, 和现实的存储结构没有关系.



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

# Locality

# Storage Technologies

## RAM

RAM（ random access memory ）： 是volatile（易失性）的存储材料， 也就是说断电就会丢失所有信息。 RAM常用来做计算机的内存，包括cache和主存等



RAM分为两类：

* SRAM( Static RAM ):  “静态”是指**只要不掉电, 存储在SRAM中的数据就不会丢失**
  * 更快更贵，一般用作Cache( 包括TLB )

- DRAM( Dynamic RAM ): 在通电时还需要**进行周期性的刷新操作, 才能保证数据不丢失**
  * 比SRAM慢，也更便宜，一般用作主存和显存

---

下图总结了SRAM和DRAM的区别： 

![Characteristics of DRAM and SRAM memory](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/Characteristics%20of%20DRAM%20and%20SRAM%20memory.png)

* SRAM的存取比DRAM快
* SRAM对干扰不敏感
* SRAM每单元使用更多晶体管，密集度低，比DRAM更贵，功耗更大

---

我们规定RAM芯片的基本存储单位是bit，对应的物理结构称为cell

### SRAM

SRAM 将每个bit存储在一个 *bistable* ( 双稳态 )的cell里。每个cell用一个 *six-transistor*电路实现。 



双稳态：

![bitable](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Hardware/Computer%20Storage/bitable.png)


上图是一个双稳态电路，它永远保持在两个不同的电压状态，也就是在上图左（右）稳态。其他任何状态都是不稳定的——电路会从不稳定状态迅速地转移到其中一个稳定状态。

上图其实有个地方应该是有偏差的，也就是中间那个状态。原则上来说，当左右两边的作用力相同时，钟摆在垂直的时候也能无限期地保持平衡，但是当左右两边稍微发生一点扰动，这个状态就会变成左稳态或右稳态之一。而且一旦倒下，便不会有机会再站起来。我们称这个状态为亚稳态。

因为SRAM有双稳态的特性，**只要有电，它就会永远的保持它的值, 即使有干扰来扰乱电压, 当干扰时, 电路就会恢复到稳定值.**  

* 也就是说SRAM在通电时不需要刷新就能保存数据

但是, 如果没有电,  双稳态就不能保持, 意味着数据也就丢失了. 这就是“电脑断电后内存数据就会丢失”的原因.

### DRAM

DRAM将每个位存储为对一个电容的充电。DRAM可以制造得非常密集——每个单元由一个电容和一个访问晶体管组成。但是与SRAM不同的是，DRAM存储器的单元对干扰非常敏感.当电容的电压被扰乱之后，它就永远不会恢复了.

* DRAM加电时需要不断刷新, 才能保存数据

#### DRAM Structure

* DRAM芯片的每$w$个cell组成一个supercell，每$d$个supercell组成一个DRAM芯片的存储部分。
  * 即， 一个$d \times w$的DRAM总共存储了$d \times w $ bit
* supercell被组织成一个$r$行$c$列的长方形阵列，其中$r \times c = d$.  每个DRAM内使用$(i,j)$二维地址( 即$(行号， 列号)$  )对supercell进行寻址
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

**采用外部时钟与处理器同步，具有更高的数据传输速率**

* *Synchronous DRAM (SDRAM)*： 传统DRAM, FPM DRAM, EDO DRAM都是以异步方式进行I/O的( 使用RAS和CAS两个独立的信号 ). 而SDRAM的I/O都在系统时钟的上升沿执行，这使得它可以同步地存取数据. 简言之，SDRAM比传统DRAM快很多
  * SDRAM属于RAM, 因此也需要周期性刷新
* SDRAM的材质分为双极性与CMOS( Complementary Metal Oxide Semiconductor, 互补金属氧化物半导体 )
  * CMOS还被用于在数字影像领域. 市面上常见的数码产品, 其感光元件主要就是CCD或者CMOS, 尤其是低端摄像头产品, 而通常高端摄像头都是CCD感光元件.
* **主板上就用了一个CMOS芯片来记录时间和硬件配置参数**，比如该从哪个盘启动. 该硬件很悲催，没有自己的名字，我们就称为CMOS. CMOS里自带一个小电池, 因此虽然是易失性的，断了电也能工作

### DDR SDRAM

* *Double Data-Rate Synchronous DRAM (DDR SDRAM)*：双通道DDR SDRAM, 是SDRAM的增强版, 在上升/下降沿都执行I/O
* DDR 是一种特殊的 SDRAM，也采用外部时钟与处理器同步，但是与 SDRAM 相比，DDR 允许在一 个时钟周期内读/写两次数据，可以加快数据传输速率



* 随着 *prefetch buffer* ( 预取缓冲区，决定了有效带宽 ) 的增大，DDR已经分为DDR (2 bits), DDR2 (4 bits), DDR3 (8 bits), DDR4(  ) and  DDR5( 16 bits )
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
  * 因此, 闪存(Flash)依然是 ROM 的一种, 写入Flash时必须先擦除原有数据，因此写速度比读速度要慢不少.



refs: CSAPP



# Others

* PROM， 可编程只读存储器，**非易失，可以一次电写入，但之后无法修改**

* EPROM 可擦除可编程只读存储器，**可以写入多次，但需要通过紫外光**擦除整个芯片的信息，时间长，但是造价相对较低集成度高

* EEPROM:  电子 EPROM,可以**擦除单个字节**，消耗时间相对较短，但是造价贵且集成度低

* CD-ROM: 采用串行存储, 并非随机访问

# 内存的刷新策略

* 集中式刷新：
  * 方式：停止读写操作，刷新每一行
  * 缺点：刷新时无法操作内存

* 分散式刷新：
  * 方式：每个存储周期内，读写操作完成时进行刷新
  * 对集中式的改进：用户不会感受到内存停止
  * 缺点：会增加每个存储周期的时间

* 异步刷新：
  * 方式：每行各自以64ms间隔刷新；两个时间间隔内保证每一行被刷新一次
  * 优点：刷新不需要占用读写时间，效率高，常用

# 内存的模块组织策略

* 位扩展：地址线不变，数据线增加
  * 使用8个4*1b芯片组成4*8b存储器（注意此时每个地址都会同时选中八个芯片上的对应位置）

* 字扩展：数据线不变，地址线增加
  * 使用8个4*8b芯片组成32*8b存储器（高3位用于选片）

* 字、位扩展：数据线和地址线同时增加
  * 使用8个4*4b芯片组成16*8b存储器（高2位选片；每次同时选中两片）

# Questions

COA2022 05

> Q: 
>
> 已知某机主存容量为 64KB，按字节编址。假定用 1K×4 位的 DRAM 芯片构成该存储器，
>
> 请问:
>  a) 需要多少个这样的 DRAM 芯片?
>
>  b) 主存地址共多少位?哪几位用于选片?哪几位用于片内选址?

Answer:

* a): 

  1B=8bit

  所以 N=64KB/(1K*4it)=16*8=128 个

* b):

  按字节选址的话 64K=2^6*2^10=2^16B, 所以主存地址一共 16 位.

  由于片内为 1K 个地址，所以低 10 位为片内地址，高 16-10=6 位用于选片。

  注意，此处不能算为 128=27，所以高 7 位选片，低 16-7=9 位用于片内选址。因为片内的选址单元是 4 位，需要位扩展后才能按字节编址(整体上是字位扩展)，即选片时都是同 时选中 2 个芯片

***

> Q: 假定用 8K×8 位的 EPROM 芯片组成 32K×16 位的只读存储器，请问
>
> a) 数据寄存器(用于存放数据)最少应有多少位?
>
> b) 地址寄存器(用于存放地址)最少应有多少位?
>
> c) 共需要多少个 EPROM 芯片

Answer:

* a) 6 位，与每个寻址单元中数据的长度相同
* b) 32K=2^15bit 所以最少15位
* c) 32/8*16/8=8 个

1B=8bit

所以 N=64KB/(1K*4it)=16*8=128 个


***

![image-20230225223940002](/Users/lyk/Library/Application Support/typora-user-images/image-20230225223940002.png)

?? 为什么用后面的数字作为位元阵列的数量?

***

> Q:下列各类存储器中，不采用随机存取方式的是( )。
>
> A. EPROM 
>
> B. CD-ROM 
>
> C. DRAM 
>
> D. SRAM

Answer: B

随机存取是指 CPU 可对存储器的任一存储单元中的内容随机存取，而且**存取时间与存储单元的物理位置无关**。

A、C 和 D 均采用随机存取方式，CD-ROM 即光盘，采用**串行存取**方式。注意，CD-ROM 是只读型光盘存储器，其访问方式是顺序访问，不属于只读存储器 ROM。

***

> Q:
>
> 某容量为256MB的存储器由若干4M×8位的DRAM芯片构成，该DRAM 芯片的地址引脚和数据引脚总数是( )。
>
> A. 19 B. 22 C. 30 D. 36



4M×8 位的芯片数据线应为 8 根，地址线应为 log24M = 22 根，而 **DRAM 采用地址复用 技术**，地址线是原来的 1/2，且地址信号分行、列两次传送。地址线数为 22/2=11 根，所以地址引脚与数据引脚的总数为 11 +8= 19 根，选 A。此题需要注意 DRAM 采用的是传两次 地址的策略，所以**地址线为正常的一半**，这是很多考生容易忽略的地方。



* 回顾一下, 内存采用DRAM, 因此地址线复用. 地址线复用可以在线不变的情况下增大地址空间, 缺点是每次访问都需要两次传输, 降低速度. 内存需要更大的地址空间, 因此用DRAM; 
* 而Cache采用SRAM, 地址线不会复用. 这可以增大访问速度, 缺点是需要的地址线较多. 对于Cache最关键的是速度, 因此Cache使用SRAM( 或者说不复用地址线 )

***

![image-20230225230037825](/Users/lyk/Library/Application Support/typora-user-images/image-20230225230037825.png)

看不懂. 总之前面的数字代表的是地址线

***

![image-20230225230209721](/Users/lyk/Library/Application Support/typora-user-images/image-20230225230209721.png)

***

![image-20230225230232733](/Users/lyk/Library/Application Support/typora-user-images/image-20230225230232733.png)

先把word拼起来, 每行都是1word



***



![image-20230225230349734](/Users/lyk/Library/Application Support/typora-user-images/image-20230225230349734.png)

看不懂, 总之是低位表示芯片编号, 因此查到芯片编号. 接着由于一个周期只能访问一个芯片, 所以第三个周期到了第二个芯片, 但我没搞懂, 读取数据(8B)不需要时间吗?

***

![image-20230225230523504](/Users/lyk/Library/Application Support/typora-user-images/image-20230225230523504.png)

看不懂, 只需知道4次访问都不能在同一模块内
