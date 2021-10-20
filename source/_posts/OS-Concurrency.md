---
title: OS Concurrency
tags: jyyOS
categories: OS
date: 2021-10-18 18:26:03
---


Outline:

* 多处理器编程的困难
* 用状态机理解并发算法
* 并发控制：互斥、同步

<!--more-->

# 多处理器编程

Current：exsiting, happening, or done at the *same* time. 程序的不同部分可以按不同顺序执行，且最终得到正确的结果

## 多任务OS的并发

（假设系统只有一个CPU）

OS可以同时加载多个进程

* 每个进程都有独立的进程，互不干扰
  * 即使是root权限的进程，也不能直接访问操作系统内核的内存

* 每隔一段时间，就切换到另一个进程

----

* 并发性的来源： **进程会调用OS的API**
  * `write（fd,buf,11 TiB）`（ TiB宏）
  *  `write`的实现是OS的一部分
    * `x86-64`应用程序执行`syscall`后就进入OS执行
      * 类似中断处理程序
    * 此时OS允许`write`到以南的时候，让另一个进程执行
      * 另一个进程执行了`read(fd,buf,512 MiB)`读取同一文件
      * **OS代码并发了**： OS API实现需要考虑并发
        * 虽然进程在地址空间中是独立的，但是OS中的对象是被进程共享的

## 典型的并发系统

* 并发： 多个执行流可以不按照一个特定的顺序执行
* 并行：允许多个执行流真正地同时执行
  * 需要多个处理器

| 处理器数量 | 共享内存？ | 典型的并发OS                 | 并发？并行？ |
| ---------- | ---------- | ---------------------------- | ------------ |
| 单         | 共享内存   | OS内核/多线程程序            | 并发不并行   |
| 多         | 共享内存   | OS内核/多线程程序/GPU Kernel | 并发、并行   |
| 多         | 不共享内存 | 分布式系统（消息通信）       | 并发、并行   |

## 线程

线程： A single process can contain multiple threads, all of  which  are  executing  the same  program.   These  threads **share** the same global memory (data and heap segments), but each thread has its own stack (automatic variables).

多个执行流并发/并行执行，且**共享内存**

* 两个执行流共享代码和所有全局变量（数据区、堆区）
  * i.e. C++中，数据区就是全局/静态区
* 线程间指令的执行顺序是不确定（*non-deterministic*）的

* 共享：共享代码区(当前进程的代码)、数据区和堆，但不共享寄存器和栈

### POSIX Threads

POSIX为我们提供了线程库（pthreads）

* 使用`pthread_create` 创建并运行线程
* 使用`pthread_join` 等待某个线程结束
* `man 1 pthreads`

## 多处理器编程的困难

* 原子性： 即使是`i++`，也会被分成几个指令
* 顺序性：**代码**的编译器优化
* 可见性： **CPU**可以不按顺序执行指令。没有前后依赖就会被优化（并行执行）

# 并发程序的执行：状态机视角

## 程序 = 有限状态机 = 有向图

图论是理解程序的重要工具

不确定(non-deterministic)的指令可能有多个状态

* 获取处理器的”时间戳“用于精确定时
  * `rdtsc/rdtscp`

* 机器提供的”真“随机数
  * `rdrand`
* `syscall`
  * 一般用于唯一不确定性的来源
  * `read`

## 状态机模型：应用

* 在硬件上的应用： 高性能处理器实现
  * 超标量处理器
    * 同一时间执行多条指令

### Time - Travel Debugging

* 程序执行随时间渐进：$s_0 \rarr s_1 \rarr \dots$​
* 记录所有$s_i$的开销太大（$s_i$​由内存和寄存器组成）
* **记录初始状态，和每条指令前后状态的diff**

* `si/rsi`

### Record & Replay

确定的程序不需要任何记录，只需要再执行一次

* 只需记录non-deterministic指令的**效果**（side-effect），就可实现重放

----------------------



* Jacking
  * 把阻塞式`syscall`改造成非阻塞式的
  * 当线程陷入`syscall`时,执行`Jacking` 程序
  * 由`Jacking` 程序来检查资源使用情况，以决定是否**执行进程**或**传递控制权给另一个进程**
* 用户级线程ULT
* 用户控件运行的线程库，提供多线程应用程序的开发和运行支撑环境
* 任何应用程序均需通过线程库进行程序设计，再与线程库连接后运行
* 线程管理的所有工作都由应用程序完成，内核完全没有意识到现成的存在

### 内核级线程的特点

* 进程中的一个线程被阻塞了，内核能调度同一进程

### 多线程实现混合式策略的特点

-------------------

# 并发控制：互斥

互斥（mutual exclusion）

```c
typedef struct{
...
}lock_tl
void lock(lock_t *lk);//试图获得锁的独占访问，成功获得后返回
void unlock(lock_t *lk);//释放锁的独占空间
```

我们假设CPU有三种指令：

1. load： mem -> reg
2. store: reg -> mem
3. 本地计算： 线程的寄存器做一些计算，结果存入寄存器

## 共享内存上互斥的困难

* load和store的缺陷（一个只能看，一个只能写）

* 现代处理器load/store可能在执行时被乱序

```C
void critical_section(){
    while(1)
        if(!locked){
            locked = 1;
            break;
        }
        //进入临界区
        locked = 0;

}
```

*   实现互斥只需**同时完成**
*   `time ./hello.out  `：查看程序运行所需时间

*   `xchg` : OS提供的syscall， 保证原子性，实现互斥

## 实现互斥：自旋锁

```c
int table =KEY;
void lock()
{
    while(1)
    {
        int got = xchg(&table,NOTE)
        if(got == KEY) break;


    }
}

void unlock()
{
    xchg(&table,KEY)

}
```

## RISC-V

考虑原子操作：

* atomic test-and-set
  * `reg = load(x);	if(reg == XX) {store(x,YY)};`
* lock xchg
  * `reg = load(x); store(x, XX)`
* lock add
  * `t = load(x); t++; store(x,t)`

---

它们本质都是：

1. load（x）
2. 设置处理器局部（寄存器）状态
3. store（x）

---

### LR/SC

只要lr/sc满足顺序/可见性。原子性/ lr到sc之间的区域就是原子的

```c
void do_lrsc
{
    while(1){
        t = lr(x);
        t = f1/f2(t); // 不同线程可执行不同操作
        if(sc(x,t)==SUCC){
            break;
        }
    }
}
```



## 数据竞争

两个不同线程的两个操作访问同一段内存，且至少有一个是store，其中没有原子操作间隔

## 并发编程简单准则

*  数据竞争 = undefined behavior
*  使所有线程间共享的变量都被同一把互斥锁保护
   * 避免数据竞争

#  多处理器并发

* 实现正确的自旋锁（在多处理器下）：关终端+ 自旋
  * 降低性能，只能用于保护一段较短的临界区

# 并发控制：同步

让线程在某件事发生时汇聚在同一点

## 条件变量：生产者 - 消费者问题

```C
#include "threads.h"
 int done;
 int nworkers = 4;

 void workload(){
     asm volatile("lock addq $1, &0": "=m"(done));
 }

 int main()
 {
     for( int i=0; i < nworkers; i++ )
     create(workload);
     while(done != nworkers) ;
     printf("All done\n");

 }
```

一个条件变量代表一个“条件”

* 条件发生后`signal()`唤醒等待的线程
* 和互斥锁联合使用

* 条件变量不满足时wait spin， 一旦条件可能满足，就唤醒所有等待的人

```C
mutex_lock(&big_lock);
while(!(cond)){
    wait(&cv, &big_lock);
}
assert(cond); //一定为真
//其他需要原子性的操作
mutex_unlock(&big_lock);
```

## 信号量

= 互斥锁+条件变量

* 有时很难设计，此时还是使用条件变量更靠谱

* e.g.: 哲学家吃饭问题

