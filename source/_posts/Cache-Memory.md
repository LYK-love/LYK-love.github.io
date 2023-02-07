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

# Elements of Cache Design

## Cache Addresses

## Cache Size
## Mapping Function Replacement Algorithms Write Policy
##  Line Size
## Number of Caches

# Cache Organization

![image-20221209220834951](/Users/lyk/Library/Application Support/typora-user-images/image-20221209220834951.png)





On power-up, the hardware sets all the valid bits in all the caches to "invalid". Some systems also set a valid bit to "invalid" at other times （电源启动的时候，硬件设置所有的真实位为“非真实”，一些系统也在其他时候设置一个真实位为非真实）

 

A data cache typically requires two flag bits per cache row entry: a valid bit and also a [dirty bit](http://en.wikipedia.org/wiki/Dirty_bit). The dirty bit indicates whether that block has been unchanged since it was read from main memory -- "clean" -- or whether the processor has written data to that block (and the new value has not yet made it all the way to main memory) -- "dirty".（一个数据缓存行一般需要两个标志位：真实位和脏位。脏位表明缓存块中的数据是否遭到修改并且没有被写入内存）。
