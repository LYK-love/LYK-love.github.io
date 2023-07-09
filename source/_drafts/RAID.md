---
title: RAID
tags: Computer Architecture
categories: Computer Science
mathjax: true
---

# Intro

存储系统的Hierarchy是Cache -> Main Memory -> Disk, 因此最慢的Disk易成为存储系统的瓶颈. 要提高Disk的性能, 最简单的办法是提高Disk数量. 

* 一个显然的好处是, 通过增加磁盘数, 多个IO request可能可以独立地被对应磁盘处理, 实现IO request的并行化, 提高效率.

## RAID

**RAID** (Redundant Array of Independent Disks, 独立冗余磁盘阵列)是一个规范的磁盘组织标准[^1].

The RAID scheme consists of seven levels, zero through six. 

These levels <u>do not</u> imply a hierarchical relationship but designate different design architectures that share three common characteristics:

1. RAID is a set of physical disk drives viewed by the operating system as a single logical drive. 即在逻辑上被视作一个盘

2. Data are distributed across the physical drives of an array in a scheme known as **striping**, described subsequently.
   * 称为“条带化”
3. **Redundant** disk capacity is used to store **parity** information, which guarantees data recoverability in case of a disk failure.
   * 这是因为使用多个物理盘后, 出错的概率也会大大增加, 为此需要设置纠错机制.

## Measure: I/O performance

根据实际使用场景的不同, I/O performance有两种标准:

1. data transfer capacity, or ability to move data. 适用于需要大量数据传输的场景
2. I/O request rate, or ability to satisfy I/O requests, since these RAID levels inherently perform differently relative to these two metrics. 适用于transaction-oriented enviroment, 在这种情况下, 用户需要尽快地得到反映, 因此响应速率是最重要的.

## RAID Levels

在接下来的讨论中, 我们假定一共有$N$个数据盘.

![RAID Levels](/Users/lyk/Library/Application Support/typora-user-images/image-20230211203015208.png)

RAID 2,4有明显缺陷(详见其各自目录的“Drawback”), 不能应用.

RAID 3, 4好像没什么缺陷, 不知为何也没有广泛应用

常用的RAID只有:  RAID levels 0, 1, 5, and 6.

# RAID Level 0

![RAID 0 (Nonredundant)](/Users/lyk/Library/Application Support/typora-user-images/image-20230211211527108.png)

严格来说, RAID 0不属于RAID, 因为其没有使用冗余磁盘( 即不满足RAID的“R”(Redundant) ), 因此也没有纠错机制, RAID 0适用于一些追求performance and capacity than reliability的场景.

RAID 0实现了磁盘阵列(条件1)和**数据条带化**(条件2).

## Stripping



![Data Mapping for a RAID Level 0 Array](/Users/lyk/Library/Application Support/typora-user-images/image-20230211203536307.png)



如图, data are *striped* across the available disks. 

* 整个RAID array被视作一个逻辑盘, 后者被切分为一个个“strip”. These strips may be physical blocks, sectors, or some other unit.  

* Strips会被按顺序映射到RAID array中连续的物理盘. 例如, strip 0被映射到Physical disk 0, strip 3被映射到Physical disk 3.

* 逻辑上连续的strip序列就被称为**stripe.** 



假设磁盘数为$n$, 即一条stripe含$n$个strip. Striping的好处是假如一个I/O request需要$m$个连续的strip( $m < n$), 则由于这些strip处于不同盘, 它们会被并行地读写, 只需花读写1个strip的时间.

## Strip Size

不同的Strip Size决定了不同的I/O performance. 

* Strip小, 则同一个I/O request可以被切分为更多的strip, **在更多的磁盘上并行访问**, 提高data transfer capacity
  * RAID 2, 3采用很小的strip, 通常是byte or word
* Strip大, 则一个I/O request可以只包括一个strip, 被一个磁盘单独处理, 多个磁盘可以**并行地处理不同的request**, 提高I/O request rate
  * RAID 4~6采用较大的strip, 每个strip都是一个数据块(block)
  * RAID 0, 1的strip大小看个人选择



# RAID Level 1

Feature: **Mirrored**

![RAID 1 (Mirrored)](/Users/lyk/Library/Application Support/typora-user-images/image-20230211211457816.png)

RAID 1使用了冗余磁盘, 它和RAID 2~6的区别是: RAID 1将**冗余磁盘用作备份**, 而RAID 2~6将冗余磁盘用作数据校验.

* In RAID 1, each logical strip is mapped to two separate physical disks. 
* 对于$N$个数据盘, RAID 1需要$N$个冗余盘
* 即每个disk都有一个备份

优点:

1. A read request can be serviced by either of the two disks that contains the requested data, whichever one involves the minimum seek time plus rotational latency.
   * In a transaction-oriented environment, RAID 1 can achieve high I/O request rates if the bulk of the requests are reads. In this situation, the performance of RAID 1 can approach **double** of that of RAID 0. 因为两个read request可以被两组盘并行处理.
2. write request需要同时更新两个对应的strip, 其时间取决于两个磁盘中较慢的那个. 但是, RAID 1**没有“write penalty”**. 在RAID 2~6中, 由于引入了数据校验, 在write时还需要计算校验位, 并写入校验位.
3. Recovery from a failure is simple. When a drive fails, the data may still be accessed from the second drive.
4. 数据可用性高于RAID 2,3,4,5, 仅低于RAID 6



缺点: High cost

# RAID Level 2

Feature: **Redundant via Hamming code**

![RAID 2 (Redundancy through Hamming code)](/Users/lyk/Library/Application Support/typora-user-images/image-20230211212437432.png)



* RAID 2,  3 采用**并行访问技术**( parallel access technique ), 所有的磁盘都参与每一次I/O request, 极大地提高了数据传输率.
  * 缺点是会降低I/O request rate, 因为整个RAID同一时间只能处理一个request. 
    * 这意味着RAID 2, 3在网络服务中不适用. 因为在后者的场景中要求告诉处理大量的I/O request.
*  如前所述, RAID 2, 3的**strip很小, 通常是byte or word.**
* RAID 2采用冗余磁盘存储**校验位**. RAID 2会根据每个磁盘上的对应bits计算error-correcting code( 一般采用hamming code ), 后者的每一位会被存储在multiple parity disks的对应位置上. 



## Pros&&Cons

RAID 2面对read和write都需要<u>访问所有磁盘</u>: 

* On a single read,  requested data and the associated error-correcting code are delivered to the array controller. If there is a single-bit error, the controller can recognize and correct the error instantly, so that the read access time is not slowed. 
* On a single write, all data disks and parity disks must be accessed for the write operation.



此外, RAID 2的cost依然很大, 考虑hamming code中纠错码占用的位数:
$$
2^{K}-1 \geq M+K
$$

* $K$: hamming code的位数

* $M$: 原数据的位数

例如对上图中$M=4$的情况, $2^3 - 1 \ge 4 + 3$, 因此$K=3$, 需要占3位. 因此需要3个冗余盘, cost较高.

## Big Drawback

由于读和写的效率都比较低, RAID 2只适用于磁盘容易出错的环境. 但现代磁盘一般都不太容易出错, 所以RAID 2很少应用.



# RAID Level 3

Feature: **Bit-interleaved parity**

![RAID 3 (Bit-interleaved parity)](/Users/lyk/Library/Application Support/typora-user-images/image-20230225144915645.png)



* RAID 3和RAID 2一样, 采用小的strip 和 并行访问技术
* RAID 3相比RAID 2唯一的区别就是, RAID 3 只使用一个冗余盘, 用来**做奇偶校验( 而RAID 2采用多个盘计算Hamming Code)**
* <u>Instead of an error- correcting code, a simple parity bit is computed for the set of individual bits in the same position on all of the data disks.</u>



* redundancy: In the event of a drive failure, the parity drive is accessed and data is reconstructed from the remaining devices. Once the failed drive is replaced, the missing data can be restored on the new drive and operation resumed. 即通过校验盘上的数据来恢复出错的数据

* performance: 由于采用了很小的strip和并行化技术. RAID3的数据传输率非常高, 一个I/O request需要所有磁盘共同传输. 但相应的, 同一时间只能执行一次I/O request

## Data reconstruction

Data reconstruction is simple. Consider an array of five drives in which $X_0$ through $X_3$ contain data and $X_4$ is the parity disk. 

**The parity for the $i$th bit is calculated as follows:**
$$
X_4(i) = X_3(i) \oplus X_2(i) \oplus X_1(i) \oplus X_0(i)
$$
where $\oplus$ is exclusive-OR function.

Suppose that drive $X_1$ has failed. If we add $X_4(i) \oplus X_1(i)$ to both sides of the preceding equation, we get:
$$
X1(i) = X4(i) ⊕ X3(i) ⊕ X2(i) ⊕ X0(i)
$$


* In the event of a disk failure, all of the data are still available in what is referred to as **reduced mode**. 
  * In this mode, for reads, the missing data are regenerated on the fly using the exclusive-OR calculation. 
* When data are written to a reduced RAID 3 array, <u>consistency of the parity must be maintained for later regeneration.</u> 



# RAID Level 4

Feature: Block-interleaved parity

![RAID 4 (Block-level parity)](/Users/lyk/Library/Application Support/typora-user-images/image-20230225144940531.png)

* **RAID 4~6采用了独立访问技术( independent access technique ), 即允许磁盘独立写, 每个磁盘可以独立地并行处理I/O request, 提高I/O request rate.**
* **RAID 4~6采用较大的strip.**

* RAID 4和RAID 3一样, 只多使用1个盘, 做奇偶校验
  * **RAID 4和RAID 3的区别: strip大小; 独立访问和并行访问技术**

* RAID 4 有 **write penalty** , 每个写请求都需要同时更新目标磁盘和校验盘

## Data reconstruction

假设我们有5个磁盘, $X_0, X_1, X_2, X_3$ 是数据盘, $X_4$是校验盘. 现在对$X_1$的某个strip进行写入. 

$X_4$上的相应strip上的第$i$个bit的更新方式如下:
$$
X_4(i) = X_3(i) \oplus X_2(i) \oplus X_1(i) \oplus X_0(i)
$$
After the update, with potentially altered bits indicated by a prime symbol:
$$
\begin{aligned}
\mathrm{X} 4^{\prime}(i) & =\mathrm{X} 3(i) \oplus \mathrm{X} 2(i) \oplus \mathrm{X} 1^{\prime}(i) \mathrm{X} 0(i) \\
& =\mathrm{X} 3(i) \oplus \mathrm{X} 2(i) \oplus \mathrm{X} 1^{\prime}(i) \oplus \mathrm{X} 0(\mathrm{i}) \oplus \mathrm{X} 1(i) \oplus \mathrm{X} 1(i) \\
& =\mathrm{X} 3(i) \oplus \mathrm{X} 2(i) \oplus \mathrm{X} 1(i) \oplus \mathrm{X} 0(\mathrm{i}) \oplus \mathrm{X} 1(i) \oplus \mathrm{X} 1^{\prime}(i) \\
& =\mathrm{X} 4(i) \oplus \mathrm{X} 1(i) \oplus \mathrm{X} 1^{\prime}(i)
\end{aligned}
$$
上述等式的最后一行表明: RAID 4的每次写操作, 都要读取原数据盘( $X_1$ )和原校验盘( $X_4$ ), 然后更新数据盘(  $X_1'$ )和校验盘( $X_4'$ ) 



即: 每次写操作都需要**两次读和两次写**磁盘

如果某个I/O request write涉及多个数据盘, 则校验位依然可以被一次计算出, 即依然是只读/写一次校验盘.

## Big Drawback

In any case, every write operation **must involve the parity disk**, which therefore can **become a bottleneck.** ( 校验盘成为 RAID 4 的瓶颈 )



# RAID Level 5

![RAID 5 (Block-level distributed parity)](/Users/lyk/Library/Application Support/typora-user-images/image-20230225145000573.png)



RAID 5 is organized in a similar fashion to RAID 4. The difference is that **RAID 5 distributes the parity strips across all disks.** 

A typical allocation is a round-robin scheme, as illustrated in Figure 6.6f. For an *n-*disk array, the parity strip is on a different disk for the first *n* stripes, and the pattern then repeats.

* The distribution of parity strips across all drives **avoids the potential I/O bottle-neck found in RAID 4.**
  * 对于每个条带，每个盘轮流做校验盘.  防止 I/O 瓶颈的出现.
* 由于RAID 5只是把RAID 4的校验盘按strip拆分开, 分布到各个盘上, 因此RAID 5和RAID 4都是只采用一个冗余盘. 即总共采用$N+1$个磁盘
* RAID 5在最坏情况下依然需要**两读两写**.
  * e.g.: 要写入上图的block12, 则需要读原来的block12和P(12-15), 再写入block12和P(12-15)

# RAID Level 6

![RAID 6 (Dual redundancy)](/Users/lyk/Library/Application Support/typora-user-images/image-20230225145021200.png)



* 在RAID 5的基础上再加一个校验盘 Q, 和 P 分开独立进行计算

* In the RAID 6 scheme, **two different parity calculations** are carried out and stored in separate blocks on different disks. 

* Thus, a RAID 6 array whose user data require ***N* disks consists of *N* + 2 disks.**
* RAID 3, 4, 5 只能处理一个盘出错的情况，或者两个盘出错的间隔时间要小于处理时间. 而RAID 6可以处理至多三个盘出错的情况

# Questions

* RAID1和RAID 4,5哪个更可靠?

  Answer: RAID1更可靠. 

  RAID1 对所有的数据进行了备份，其中一份磁盘数据出错，通过另一份就可以很方便的 恢复.

  而RAID 4,5 采用了奇偶校验, 无法发现偶数个位的出错. 因此如果两块磁盘的同一个对应位置同时出错，便无法恢复

***

Q:

> 假定在一个使用RAID5的系统中，采用先更新数据块、再更新校验快的信息更新方式。如果在更新数据块和更新校验块的操作之间突然发生了断电现象，那会出现什么问题?
>
> 是否可以通过更改信息更新方式来避免这一问题的发生?如果可以的话，请说明如何更改及更改后的方式如何发挥作用。



Answer: 

* 问题: 数据块更新了，而校验快没有更新，导致校验快与数据块不匹配，无法通过校验位对其他数据块进行 恢复操作。
* 解决方法: 可以先更新校验块，如果断电了，可以通过已更新的校验块来恢复数据块

***

![image-20230225195628949](/Users/lyk/Library/Application Support/typora-user-images/image-20230225195628949.png)

***

![image-20230225195839067](/Users/lyk/Library/Application Support/typora-user-images/image-20230225195839067.png)

![image-20230225195849055](/Users/lyk/Library/Application Support/typora-user-images/image-20230225195849055.png)



[^1]: The term RAID was originally coined in a paper by a group of researchers at the University of California at Berkeley [PATT88].3 The paper outlined vari- ous RAID configurations and applications and introduced the definitions of the RAID levels that are still used. 
