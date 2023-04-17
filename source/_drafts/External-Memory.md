---
title: External Memory
tags:
---



# Introduction

本章介绍外部存储设备, 它们位于Memory Hierarchy的最底层, 因此容量最大, 速度最慢. 外部存储设备一般是非易失的

# Magnetic Disk

这里介绍的磁盘是“*rotating disks* ”, 区别于之前的 flash-based solid state disks (SSDs), 后者是不会旋转的

rotating disks由基材)构成的圆形 片



## Disk Geometry

![Disk geometry](/Users/lyk/Library/Application Support/typora-user-images/image-20221129203831236.png)

* platter: Disks are constructed from *platters*. 
  * A disk will typically contain one or more of these platters encased in a sealed container.
  * 上图(a)是一个单盘片磁盘; (b)是一个多盘片磁盘.
  * 盘片一般由涂有**可磁化材料**的**非磁性材料**(基材)构成
    * 基材:铝、铝合金、玻璃
    * 玻璃基材的优势
      * 改善磁膜表面的均匀性，提高磁盘的可靠性
      * 显著减少整体表面瑕疵，以帮助减少读写错误 • 能够支持(磁头)较低的**飞行高度**
      * 更高的硬度，使磁盘转动时更加稳定
      * 更强的抗冲击和抗损伤能
  
* surface: Each platter consists of two sides, or *surfaces*, that are coated with magnetic recording material. 

* track: Each surface consists of a collection of concentric rings called *tracks*. 

  ![image-20230225210931815](/Users/lyk/Library/Application Support/typora-user-images/image-20230225210931815.png)

  注意, 我们一般把最外层track看作第0个track

* sector: Each track is partitioned into a collection of *sectors*. 
  * Each sector contains an equal number of data bits (**typically 512 bytes**) encoded in the magnetic material on the sector. 
  * 磁盘存储器的**最小读写单位为一个扇区**
  
* gap: Sectors are separated by *gaps* where no data bits are stored. Gaps store formatting bits that identify sectors.

* cylinder: a cylinder is **the collection of tracks** on all the surfaces that are **equidistant from the center of the spindle**. 
  * For example, if a drive has three platters and six surfaces, and the tracks on each surface are numbered consistently, then cylinder k is the collection of the six instances of track k.
  
* RPM: A rotating *spindle* in the center of the platter spins the platter at a fixed *rotational rate*, typically between 5,400 and 15,000 *revolutions per minute (RPM)*. 

* 

## Disk Capacity

## Disk Operation

* 磁头: Disks read and write bits stored on the magnetic surface using a read/write head connected to the end of an actuator arm, as shown in Figure 6.10(a). 



Disks read and write data in sector-size blocks. The *access time* for a sector has three main components: *seek time*, *rotational latency*, and *transfer time:*

* *Seek time.* To read the contents of some target sector, the arm first positions the head over the track that contains the target sector. The time required to move the arm is called the *seek time*. The seek time, Tseek, depends on the previous position of the head and the speed that the arm moves across the surface. The average seek time in modern drives, Tavg seek, measured by taking the mean of several thousand seeks to random sectors, is typically on the order of 3 to 9 ms. The maximum time for a single seek, Tmax seek, can be as high as 20 ms.
  * **平均寻道时间为越过一半磁道的时间**:

* *Rotational latency.* Once the head is in position over the track, the drive waits for the first bit of the target sector to pass under the head. The perfor- mance of this step depends on both the position of the surface when the head arrives at the target track and the rotational speed of the disk. In the worst case, the head just misses the target sector and waits for the disk to make a full rotation. Thus, the maximum rotational latency, in seconds, is given by

Tmax rotation = 1 × 60 secs RPM 1 min

**The average rotational latency, Tavg rotation, is simply half of Tmax rotation.**

* *Transfer time.* When the first bit of the target sector is under the head, the drive can begin to read or write the contents of the sector. The transfer time for one sector depends on the rotational speed and the number of sectors per track. Thus, we can roughly estimate the average transfer time for one sector in seconds as

  ![image-20230224170644594](/Users/lyk/Library/Application Support/typora-user-images/image-20230224170644594.png)
  
  * $\frac{b}{N}$: track数量
  * $\frac{1}{r}$: 旋转延迟, 也就是转一圈需要的时间
  * $T$ = 转所需数量的track的时间





平均访问时间 = **平均寻道时间 + 平均旋转延迟 + 数据传输时间**



当连续访问多个相邻的磁道时，跨越磁道:

* **对于每个磁道都需要考虑旋转延迟**
* 通常只需要考虑第一个磁道的寻道时间，但在明确知道跨越每 个磁道需要的时间时需要考虑



## Disk Scheduling

### SSTF

![image-20221208165038536](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165038536.png)

### FCFS

![image-20221208165045590](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165045590.png)

### SCAN



![image-20221208165117511](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165117511.png)



### C-SCAN

![image-20221208165130382](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165130382.png)



先一直右移到200, 再左移到0, 再右移到90

### LOOK

![image-20221208165137984](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165137984.png)

就是不用移动到起点和边缘track了

### C-LOOK

![image-20221208165143992](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165143992.png)

## Questions

> Q: 假设一个磁盘的平均寻道时间为 4ms，旋转速度为 15000 rpm， 每个扇区有 512byte 每个磁道 有 500 个扇区，如果我们需要读一个文件包含 2500 个扇区共 1.28Mbytes

Answer:

1. 假设是连续的, 则文件占据了 5 个连续的磁道 , 因此对于后4个track, 只需要计算旋转延迟, 不需要寻道时间
   对于情况1: 15000rpm=2500rps 1/2500=4ms 所以 t=2+4/2+4+4*(4/2+4)=34ms*
2. track是随机分布的, 因此每个track都要算寻道时间
3. 对于情况 2: 因为是随机的 t= 2500*(4+4/2+0.008)=15020ms

***

> Q: 考虑一个有N个磁道的磁盘，磁道编号由0到N-1，并假定所要求的扇区随机均匀分布在盘上。
>  a) 假设磁头当前位于磁道t上，计算越过的磁道数为j的概率。
>  b) 假设磁头可能出现在任意磁道上，计算越过的磁道数为k的概率。
>
> c) 计算越过的平均磁道数的期望:
> $$
> E[x]=\sum_{i=0}^{N-1}(i \times \operatorname{Pr}[x=i])
> $$

Answer:

* a) 考虑两个方向

  磁头到达每个磁道的几率为1/N 

  1:若 j-1<t<N-j 则概率为 2/N

  2:若 t<=j-1 或者 t>=N-j 则概率为 1/N

* ![image-20230225170531874](/Users/lyk/Library/Application Support/typora-user-images/image-20230225170531874.png)



\# todo

***

>  Q: 为一个磁盘系统定义如下参数:
>
> 
>
> TS = 寻道时间，即磁头定位在磁道上的平均时间
>
> r = 磁盘的旋转速度(单位:转/秒)
>
> n = 每个扇区的位数
>
> N = 一个磁道的容量(单位:位) TA = 存取一个扇区的时间
>
> 
>
> 请推导 TA 的表达式。



Answer: TA=TS+1/2r+n/rN

***

coa22_07

![image-20230225212449197](/Users/lyk/Library/Application Support/typora-user-images/image-20230225212449197.png)



![image-20230225212459700](/Users/lyk/Library/Application Support/typora-user-images/image-20230225212459700.png)

![image-20230225212508069](/Users/lyk/Library/Application Support/typora-user-images/image-20230225212508069.png)

最外层track为第0个

每当要读一个track, 都要付出平均旋转延迟(5ms). 因此完成任务三需要付出5\*3 = 15ms的平均旋转延迟( 因为读了track 220, 221, 222)



***

![image-20230225212814767](/Users/lyk/Library/Application Support/typora-user-images/image-20230225212814767.png)

***

Answer: C

> Q: 下列关于磁盘存储器的叙述中，错误的是( )
>
>  A. 磁盘的格式化容量比非格式化容量小
>
> B. 扇区中包含数据、地址和校验等信息
>
> C. 磁盘存储器的最小读写单位为 1 字节
>
> D. 磁盘存储器由磁盘控制器、磁盘驱动器和盘片组成 C

C错: 磁盘存储器的**最小读写单位为一个扇区**，即磁盘按块存取

A对: 磁盘存储数据之前 需要进行格式化，将磁盘分成扇区，并写入信息，因此磁盘的格式化容量比非格式化容量小， A 正确。

B对: 磁盘扇区中包含数据、地址和校验等信息，B 正确。

D对: 磁盘存储器由磁盘控制器、磁 盘驱动器和盘片组成，D 正确。

# RAID

# Solid State Drives

# Optical Memory

# Magnetic Tape

# 

