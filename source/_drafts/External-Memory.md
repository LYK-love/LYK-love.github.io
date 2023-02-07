---
title: External Memory
tags:
---



# Introduction

本章介绍外部存储设备, 它们位于Memory Hierarchy的最底层, 因此容量最大, 速度最慢. 外部存储设备一般是非易失的

# Magnetic Disk

这里介绍的磁盘是“*rotating disks* ”, 区别于之前的 flash-based solid state disks (SSDs), 后者是不会旋转的

rotating disks由基材)构成的圆形 片

• ...... • 

力

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
* sector: Each track is partitioned into a collection of *sectors*. 
  * Each sector contains an equal number of data bits (**typically 512 bytes**) encoded in the magnetic material on the sector. 
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
  * 平均寻道时间为越过一半磁道的时间:

* *Rotational latency.* Once the head is in position over the track, the drive waits for the first bit of the target sector to pass under the head. The perfor- mance of this step depends on both the position of the surface when the head arrives at the target track and the rotational speed of the disk. In the worst case, the head just misses the target sector and waits for the disk to make a full rotation. Thus, the maximum rotational latency, in seconds, is given by

Tmax rotation = 1 × 60 secs RPM 1 min

The average rotational latency, Tavg rotation, is simply half of Tmax rotation.

* *Transfer time.* When the first bit of the target sector is under the head, the drive can begin to read or write the contents of the sector. The transfer time for one sector depends on the rotational speed and the number of sectors per track. Thus, we can roughly estimate the average transfer time for one sector in seconds as



![image-20221208165038536](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165038536.png)



![image-20221208165045590](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165045590.png)



![image-20221208165117511](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165117511.png)



![image-20221208165130382](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165130382.png)



![image-20221208165137984](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165137984.png)



![image-20221208165143992](/Users/lyk/Library/Application Support/typora-user-images/image-20221208165143992.png)



# RAID

# Solid State Drives

# Optical Memory

# Magnetic Tape
