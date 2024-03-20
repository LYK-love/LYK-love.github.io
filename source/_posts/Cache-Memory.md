---
title: Cache Memory
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2022-11-30 21:22:01
---

Outline:

<!--more-->

# Cache Memory Principles

程序访问的局部性原理：

* spatial locality：在相对较短的时间周期内，重复访问特定的信息

* temporal locality：在相对较短的时间周期内，访问相邻位置的数据



Given the following address streams, name the kind of locality they exploit:

```
0x31c4  | 0x31cc  | 0x31d4  | 0x31dc  | 0x31e4
```

Answer: spatial locality.

```
0x31c4  | 0x7808  | 0x31c4  | 0x7808  | 0x31c4
```

Answer: temporal locality.



Cache works like main memory, so it only sees physical addresses.

# Elements of Cache Design

## Cache Addresses

## Cache Size
## Mapping Function Replacement Algorithms Write Policy
##  Line Size
## Number of Caches

# Cache Organization

* 组号不会存储在Cache行中, 因为组号是系统默认分配的.
* 因此Cahce行大小 = 各种标识位 + Tag+ block

The capacity of the data array in a cache can be calculated using the total number of blocks and the size of each block. 



## Generic Cache Memory Organization

![image-20230220140706649](/Users/lyk/Library/Application Support/typora-user-images/image-20230220140706649.png)

Consider a computer system where each memory address has m bits that form $M = 2^m$ unique addresses. As illustrated in Figure 6.25(a), 

a cache for such a machine is organized as an array of $S = 2^s$ *cache sets*. Each set consists of $E$ *cache lines*. 

Each line consists of a data *block* of $B = 2^b$ bytes, a *valid bit* that indicates whether or not the line contains meaningful information, 

and $t = m − (b + s)$ **tag bits** (a subset of the bits from the current block’s memory address) that uniquely identify the block stored in the cache line.

In general, a cache’s organization can be characterized by the tuple $(S, E, B, m)$. The size (or capacity) of a cache, $C$, is stated in terms of the aggregate size of all the blocks. The tag bits and valid bit are not included. Thus, $C = S × E × B$.

***



![image-20230220140723458](/Users/lyk/Library/Application Support/typora-user-images/image-20230220140723458.png)

The parameters $S$ and $B$ induce a partitioning of the $m$ address bits into the three fields 

* The $s$ *set index bits* in A form an index into the array of $S$ sets. The first set is set 0, the second set is set 1, and so on. When interpreted as an unsigned integer, the set index bits tell us which set the word must be stored in. 
* Once we know which set the word must be contained in, the $t$ tag bits in A tell us which line (if any) in the set contains the word. A line in the set contains the word **if and only if the valid bit is set and the tag bits in the line match the tag bits** in the address A. 
* Once we have located the line identified by the tag in the set identified by the set index, then the $b$ *block offset bits* give us the offset of the word in the B-byte data block.
* 组号 = 块号 mod 每组行数. 也就是说, 第0, 4, 8, ...块在第0组‘ 第1, 5, 9, ...块在第1组







## Direct-Mapped Caches

Caches are grouped into different classes based on $E$, the number of cache lines per set. 

**A cache with exactly one line per set (E = 1) is known as a *direct-mapped* cache**



![image-20230220140155600](/Users/lyk/Library/Application Support/typora-user-images/image-20230220140155600.png)



### Set Selection

In this example, the set index bits $00001_2$ are interpreted as an integer index that selects set 1.

![Set selection in a direct-mapped cache](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141928582.png)



In this step, the cache:

1. extracts the $s$ set index bits from the middle of the address for $w$. 
2. These bits are interpreted as **an unsigned integer** that corresponds to **a set number**.  



### Line Matching and Word Selection

Now that we have selected some set $i$ in the previous step, the next step is to determine if a copy of the word $w$ is stored in one of the cache lines contained in set $i$. 

In a direct-mapped cache, this is easy and fast because <u>there is exactly one line per set.</u> 

A copy of $w$ is contained in the line **if and only if the valid bit is set and the tag in the cache line matches the tag** in the address of $w$.



在下图中, valit bit = 1,  且该cache line的tag bits和所给地址中的tag bits相同, 因此Cache hit. 反之则cache miss.



![Line matching and word selection in a direct-mapped cache](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141831370.png)

## Set Associative Caches

The problem with conflict misses in direct-mapped caches stems from the constraint that <u>each set has exactly one line</u> (or in our terminology, E = 1). A *set associative cache* relaxes this constraint so that each set holds more than one cache line. 

A cache with $1 < E < C/B$ is often called an **E-way set associative cache**. 



### Set Selection

![Set Selection in Set Associative Caches](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141655020.png)

Set selection is identical to a direct-mapped cache, with <u>the set index bits identifying the set</u>. Figure 6.33 summarizes this principle.

### Line Matching and Word Selection

![Line Matching and Word Selection in Set Associative Caches](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141013402.png)

Line Matching and Word Selection in Set Associative Caches

* A **conventional memory** is an array of values that <u>takes an address as input and returns the value stored at that address.</u> 
* An *associative memory*, on the other hand, is an array of (key, value) pairs that <u>takes as input the key and returns a value from one of the (key, value) pairs that matches the input key.</u> 
* Thus, we can think of each set in a set associative cache as a small associative memory where the keys are the concatenation of the tag and valid bits, and the values are the contents of a block.
* Figure 6.34 shows the basic idea of line matching in an associative cache. An important idea here is that **any** line in the set **can** contain any of the memory blocks that map to that set. So the cache **must search each line in the set** for a valid line whose tag matches the tag in the address. 



 **if there is an empty line**, then it would be a good candidate. 

But if there are no empty lines in the set, then we must **choose one of the nonempty lines** and hope that the CPU does not reference the replaced line anytime soon.



## Fully Associative Caches

A *fully associative cache* consists of a single set (i.e., E = C/B) that contains all of the cache lines.

![Fully Associative Caches](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141301248.png)

### Set Selection

![Set Selection in Fully Associative Caches](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141432658.png)

Set selection in a fully associative cache is trivial because there is only one set, summarized in Figure 6.36. Notice that there are no set index bits in the address, which is partitioned into only a tag and a block offset.

根本没有set index

### Line Matching and Word Selection

Line Matching and Word Selection in Fully Associative Caches

![Line Matching and Word Selection in Fully Associative Caches](/Users/lyk/Library/Application Support/typora-user-images/image-20230220141412164.png)

Line matching and word selection in a fully associative cache work the same as with a set associative cache, as we show in Figure 6.37. The difference is mainly **a question of scale.**



* a question of scale:

  Because the cache circuitry must search for many matching tags in parallel, it is difficult and expensive to build an associative cache that is both large and fast. As a result, fully associative caches are only appropriate for small caches, such as the translation lookaside buffers (TLBs) in virtual memory systems that cache page table entries (Section 9.6.2).



On power-up, the hardware sets all the valid bits in all the caches to "invalid". Some systems also set a valid bit to "invalid" at other times （电源启动的时候，硬件设置所有的真实位为“非真实”，一些系统也在其他时候设置一个真实位为非真实）

 

A data cache typically requires two flag bits per cache row entry: a valid bit and also a [dirty bit](http://en.wikipedia.org/wiki/Dirty_bit). The dirty bit indicates whether that block has been unchanged since it was read from main memory -- "clean" -- or whether the processor has written data to that block (and the new value has not yet made it all the way to main memory) -- "dirty".（一个数据缓存行一般需要两个标志位：真实位和脏位。脏位表明缓存块中的数据是否遭到修改并且没有被写入内存）。

# Performance

## AMAT

AMAT (Average Memory Access Time) is a metric used to calculate the average time it takes to access memory, taking into account the hit and miss rates of cache memory. It's given by the formula:
$$
\text { AMAT }=\text { Hit Time }+(\text { Miss Rate } \times \text { Miss Penalty })
$$
- Hit Time: The time it takes to access the first level of cache (L1), where data is most quickly accessible.
- Miss Rate: The fraction of memory accesses that are not found in the cache.
- Miss Penalty: The additional time it takes to retrieve the data from a lower level of cache or main memory after a miss occurs in the initial cache level.



The formula for AMAT in a two-level cache system can be expressed as:
$$
\begin{aligned}
& \text { AMAT }=\text {L1 Hit Time }+(\text { L1 Miss Rate } \times \text { L1 Miss Penalty }) \\
& \text { L1 Miss Penalty } = \text {L2 Hit Time }+(\text { L2 Miss Rate } \times \text { L2 Miss Penalty }) \\
\end{aligned}
$$


Example:

Use the following system characteristics to answer the questions below.

L1 cache latency: 2 cycles

L1 cache hit ratio: 95.0%

Memory latency: 40 cycles

Instruction mix: 40.0% loads and stores

To improve performance you add another level of cache. You have two options:

|           | L2 Cache A | L2 Cache B |
| --------- | ---------- | ---------- |
| Hit ratio | 80.0%      | 90.0%      |
| Latency   | 10 cycles  | 15 cycles  |

What is the *speedup* of **System A over System B**? (If system A is better, then this should be above 1, if system B is better then this should be below 1).

Assume 0 time for instruction fetch (for instance, there is a very good instruction prefetcher) and assume that all instructions other than loads and stores complete with a CPI of 1. Also assume that the two systems are running the same program.

Hint: you need to calculate the CPI for each system.

Answer: 1.0113636363636367

Solution:

```
>>> AMAT1 = (2 + 0.05 * (10 + 0.2 * 40)) * 0.4 + 0.6
>>> AMAT2 = (2 + 0.05 * (15 + 0.1 * 40)) * 0.4 + 0.6
>>> Speedup = AMAT2 / AMAT1
>>> Speedup
1.0113636363636367
>>> AMAT1
1.7599999999999998
>>> AMAT2
1.7800000000000002
```





# Why index with the middle bits?

Cache将物理地址中中间(而不是高位)的几位作为Cache Line的组号, 这是为了提高Cache效率, 使得Cache尽快加载尽可能多的Cache Line

考虑如下情况, 一个4路组Cache将物理地址的高两位作为组号:

![image-20230224161509761](/Users/lyk/Library/Application Support/typora-user-images/image-20230224161509761.png)

我们看到, 这会导致连续的主存块被映射到相同的组. 例如, 在上图中, 第0,1, 2,3个块都被映射到第0组; 第4,5, 6,7个块都被映射到第1组...

如果一个程序拥有比较好的空间局部性, 那么在该程序运行期间, Cache可能只会加载几个组, 剩下几个组的Cache line一直不会被加载.

因此我们将物理地址的中间几位作为组号, 如上图, 此时第0,4, 8,12个块都被映射到第0组, 则当程序运行时, 尽可能多的Cache Line会被加载.



You may be wondering why caches use the middle bits for the set index instead of the high-order bits. There is a good reason why the middle bits are better. Figure 6.31 shows why. If the high-order bits are used as an index, then some contiguous memory blocks will map to the same cache set. For example, in the figure, the first four blocks map to the first cache set, the second four blocks map to the second set, and so on. If a program has good spatial locality and scans the elements of an array sequentially, then the cache can only hold a block-size chunk of the array at any point in time. This is an inefficient use of the cache. Contrast this with middle-bit indexing, where adjacent blocks always map to different cache sets. In this case, the cache can hold an entire C-size chunk of the array, where C is the cache size

# Line Replacement policies

Some options:

1. Random

2. FIFO (first-in first-out)

3. LRU (least recently used): replace the line that has been referenced the fewest times over some past time window. 

   “访问”指的是访问对应内存. 仅仅将block从主存中取出来, 而没有“访问”它. 就不算“访问”.

4. NMRU (not most recently used) = LRU for 2-way set-associative caches.

   NMRU simply identifies one or more cache lines that are not the most recently used.

# 写操作策略

## Write through
 为保证 Cache 与主存的一致性，往 Cache 写入时同时也要往主存写入 但降低写入速度，容易产生瓶颈



The benefits of a write-through cache policy include:

- **Less Metadata in the Cache**: Indeed, a write-through policy requires less metadata to be maintained within the cache. Specifically, there's no need to keep track of whether a cache line has been modified or not (i.e., no dirty bit required) because all writes are immediately reflected in the lower-level memory. This simplifies the design and management of the cache.
- **Easier to Handle Faults in the Cache**: Write-through policies simplify fault recovery and error handling. Since all writes are immediately propagated to the main memory, the system can recover more easily from faults, such as power failures or system crashes, with minimal data loss. The immediate consistency between the cache and the memory ensures that the most recent writes are not lost, simplifying recovery processes.

## Write back
在 Cache 中增加一位(脏位)表示是否被修改过，若“脏”，则替换整个块时前将其写回 减少写入操作，但会有不必要的麻烦(如输出时会取得主存中未修改的数据) 策略:输出时候强制修改主存

# Questions

COA22 06

> Q: 为什么 Cache 可以采用直写策略，而修改页面内容时总是采用回写策略?

Answer:

1. 因为采用直写策略时需要同时写快速存储器和慢速存储器，而写磁盘比写主存慢很多，所以在

Cache-主存层次，Cache 可以采用直写策略，而在主存-外存(磁盘)层次，修改页面内容时总是采用回写策略。

***

![image-20230225191658506](/Users/lyk/Library/Application Support/typora-user-images/image-20230225191658506.png)

***

![image-20230225191713106](/Users/lyk/Library/Application Support/typora-user-images/image-20230225191713106.png)



***

![image-20230225231434651](/Users/lyk/Library/Application Support/typora-user-images/image-20230225231434651.png)

***

![image-20230225234729675](/Users/lyk/Library/Application Support/typora-user-images/image-20230225234729675.png)

***

![image-20230225235137362](/Users/lyk/Library/Application Support/typora-user-images/image-20230225235137362.png)



不要忘了Valid Bit

***

![image-20230225235736774](/Users/lyk/Library/Application Support/typora-user-images/image-20230225235736774.png)

注意, 每个循环都要读一次写一次. 

***

2015 mid

![image-20230226010637925](/Users/lyk/Library/Application Support/typora-user-images/image-20230226010637925.png)

时间 = Cache访问时间 + 主存访问时间 * Cache miss概率

Cache miss概率 = 指令丢失概率 + 数据丢失概率

数据丢失概率 = ( 30% + 10 * 2 ) * 5%

## Question 1

se the following characteristics to answer the questions below.

Block size: 64 B

Total blocks: 65536

Associativity: 16-way Set associative

Address size: 35 bits

Meta data: 3 bits per block

------

Give the following answers in bytes unless otherwise noted.

What is the capacity of the *data* array?  4194304

How many tags are required? 4194304

What is the capacity of the SRAM (including the tags and extra meta data)? 4358144.0

How many *bits* are read on each access to the cache? Assume all ways are accessed in parallel. 8512



Solution:

1. The capacity of the *data* array = Total blocks \* Block size = 65536 \* 64 B = 4194304 B.

2. Since there are 65536 blocks, each block needs a tag, there are 65536 tags in total.

3. Since Block size = 64 B, the offset takes 6 bits. Meanwhile, there are 65536 blocks and each set has 16 blocks, so there are 65546 / 16 = 4096 sets. Thus, the set number takes 12 bits. Because the address size is 35 bits, the tag size is 35 - 12 - 6 = 17 bits. Each block contains:

   1. 17 bits tag.
   2. 3 bits meta data.
   3. 64 B data.

   There are 65536 blocks. So the SRAM size is 65536 \* (64 + 20/8) = 4358144.0

4. Sicne each set has 16 ways (blocks), and accessing each way will read 64 B + 18 b + 3 b = 532 b data, all ways are accessed in parallel, we obtain that total bits read per access is 532 \* 16 = 8512.
