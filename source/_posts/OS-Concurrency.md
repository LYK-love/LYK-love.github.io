---
title: OS Concurrency
tags: Operating Systems Three Easy pieces 
categories: OS
---


Outline:

* 多处理器编程的困难
* 用状态机理解并发算法
* 并发控制：互斥、同步

<!--more-->

# Intro

Concurrent：exsiting, happening, or done at the *same* time. 程序的不同部分可以按不同顺序执行，且最终得到正确的结果

```C
//t0.c
#include<stdio.h>
#include<assert.h>
#include<pthread.h>// pthread 库不是 Linux 系统默认的库，连接时需要使用静态库 libpthread.a // 在编译中要加 -lpthread参数

void  *mythread( void *arg )
{
    printf("%s\n", arg);
    return NULL;
}

int main( int argc, char* argv[])
{
    pthread_t  p1,p2;
    int rc;
    printf( "main:begin\n" );

    char* ch1 = "A";
    char* ch2 = "B";
    rc = pthread_create( &p1, NULL, mythread, ch1 ); assert(rc==0); //C语言编译器允许隐含性的将一个通用指针转换为任意类型的指针，包括const *而C＋＋不允许将const 转换为非const*，所以不能直接传入"A"
    rc = pthread_create( &p2, NULL, mythread, ch2 ); assert(rc==0);

    rc= pthread_join( p1,NULL );
    rc= pthread_join( p2,NULL );
    printf("main:end\n");
}

```

该程序打印结果为：

```
main:begin
A
B
main:end
```

或者

```
main:begin
B
A
main:end
```

两次运行结果不一样

## 多任务OS的并发

（假设系统只有一个CPU）

OS可以同时加载多个进程

* 每个进程都是独立的进程，互不干扰
  * 即使是root权限的进程，也不能直接访问操作系统内核的内存

* 每隔一段时间，就切换到另一个进程

----

* 并发性的来源： **进程会调用OS的API**
  * `write（fd,buf,11 TiB）`（`TiB`宏）
  *  `write`的实现是OS的一部分
    * `x86-64`应用程序执行`syscall`后就进入OS执行
      * 类似中断处理程序
    * 此时OS允许`write`的同时，让另一个进程执行
      * 如：另一个进程执行了`read(fd,buf,512 MiB)`读取同一文件
      * **OS代码并发了**： `OS API`实现需要考虑并发
        * 虽然进程在地址空间中是独立的，但是OS中的对象是被进程共享的

## 并发与并行的区别

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

```c
//t1.c
//共享全局变量的后果
#include<stdio.h>
#include<pthread.h>
#include"mythreads.h"

static volatile int counter = 0;

void * mythread( void*arg )
{
    printf( "%s: begin\n", (char*)arg );
    int i;
    for( int i = 0 ; i < 1e7; i++ )
        counter++;
    printf("%s: done\n", (char*)arg);
    return NULL;
}

int main( int argc, char* argv[])
{
    pthread_t  p1,p2;
    int rc;
    printf( "main:begin ( counter = %d )\n", counter );

    char* ch1 = "A";
    char* ch2 = "B";
    Pthread_create( &p1, NULL, mythread, ch1 ); //C语言编译器允许隐含性的将一个通用指针转换为任意类型的指针，包括const *而C＋＋不允许将const 转换为非const*，所以不能直接传入"A"
    Pthread_create( &p2, NULL, mythread, ch2 ); 

    Pthread_join( p1,NULL );
    Pthread_join( p2,NULL );
    printf("main:done with both ( counter = %d )\n", counter);
}
```

```c
//mythreads.h
//把API封装起来，易于使用

#include<pthread.h>
// #include<assert.h>

void Pthread_create (pthread_t *__restrict __newthread,
			   const void* __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg)
{
    pthread_create( __newthread, __attr, __start_routine, __arg );
}
 void Pthread_join(pthread_t __th, void **__thread_return)
 {
     pthread_join( __th, __thread_return );
 }

 void *Malloc(unsigned size)
 {
    return malloc(size);
 }
```

输出为：

```
main:begin ( counter = 0 )
A: begin
B: begin
A: done
B: done
main:done with both ( counter = 12275324 )
```

可以看到结果不是200000, 而是12275324

再运行一次：

```
main:begin ( counter = 0 )
A: begin
B: begin
B: done
A: done
main:done with both ( counter = 10467369 )
```

**两次运行的结果都不一样！**



## 多处理器编程的困难

* 原子性： 即使是`i++`，也会被分成几个指令
* 顺序性：**代码**的编译器优化
* 可见性： **CPU**可以不按顺序执行指令。没有前后依赖就会被优化（并行执行）



### 并发术语

* 临界区( `critical section` )： 访问共享资源的一段代码
* 竞态条件( `race condition` )： 多个执行线程大致同时进入进阶区时，都试图更新共享资源的情况
* 不确定性( `indeterminate` )： 程序含有竞态条件，其输出不确定
* 同步原语( `synchronization primitive` ):硬件提供指令，在其上构建同步原语,实现**原子性**
* 互斥原语( `mutual exclusion` )： 线程应该使用互斥原语，以保证只有一个线程进入临界区，从而避免出现竞态，并产生确定的程序输出

# 并发与状态机

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

# Threading API

`man  -k pthread`



```C
//p212, 线程API
#include<stdio.h>
#include<pthread.h>
#include"mythreads.h"
#include<stdlib.h>

typedef struct myarg_t{
    int a;
    int b;
}myarg_t;

typedef struct myret_t{
    int x;
    int y;
}myret_t;



void * mythread( void*arg )
{
    myarg_t *m = (myarg_t *)arg;
    printf( "args: %d %d\n",  m -> a, m -> b );
    myret_t *r = Malloc(sizeof( myret_t ));
    r -> x = 1;
    r -> y = 2;
    return (void*) r;
}

int main( int argc, char* argv[])
{
    pthread_t  p;
    int rc;
    myret_t *m; //将返回值打包
    myarg_t args;//将参数打包

    args.a = 10;
    args.b = 20;
    Pthread_create( &p, NULL, mythread, &args ); 
    Pthread_join( p, ( void **) &m );//将线程返回值赋给m
    printf("returned: %d %d\n", m -> x, m -> y );
}
```

输出为：

```
args: 10 20
returned: 1 2
```



## 线程创建

` <pthread.h>`

```c
/* Create a new thread, starting with execution of START-ROUTINE
   getting passed ARG.  Creation attributed come from ATTR.  The new
   handle is stored in *NEWTHREAD.  */
extern int pthread_create (pthread_t *__restrict __newthread, //线程的指针
			   const pthread_attr_t *__restrict __attr, //线程具有的属性，包括栈大小，优先级等。 一般传入NULL
			   void *(*__start_routine) (void *),//线程要运行的函数的指针，接受void*参数，返回 void* //可以自由更改参数/返回类型
			   void *__restrict __arg) __THROWNL __nonnull ((1, 3));//函数的参数，可传入结构体，以实现传入多个参数
```

## 线程完成

```c
/* Make calling thread wait for termination of the thread TH.  The
   exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
   is not NULL.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pthread_join (pthread_t __th, void **__thread_return);
/*
第一个参数是线程的指针
第二个参数是线程运行的函数的返回值的指针
*/
```

## 锁

```c
//上锁和解锁
extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
 
//锁必须初始化，两种方式
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_init(*lock, NULL)

//锁使用完后必须销毁
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
```



```c
//mythread.h

 void Pthread_mutex_lock( pthread_mutex_t *mutex )
 {
     int rc = pthread_mutex_lock(mutex);
     assert( rc == 0 );
 }

void Pthread_mutex_unlock( pthread_mutex_t *mutex )
 {
     int rc = pthread_mutex_unlock(mutex);
     assert( rc == 0 );
 }

void Pthread_mutex_init( pthread_mutex_t *__mutex,
			       const void*__mutexattr )
{
    int rc = pthread_mutex_init(__mutex, NULL);
     assert( rc == 0 );
}

void Pthread_mutex_destroy( pthread_mutex_t *__mutex )
{
    int rc = pthread_mutex_destroy(__mutex);
     assert( rc == 0 );
}
```

使用锁：

```c
    pthread_mutex_t lock;
    Pthread_mutex_init( &lock ,NULL );//初始化锁

    Pthread_mutex_lock( &lock );//上锁， 如果锁已经被其他线程持有，那么该调用不会返回，直到获得该锁（意味着持有该锁的线程已经将锁释放）
    x = x +1;
    Pthread_mutex_unlock( &lock );
```



## 条件变量

```c
/* Wait for condition variable COND to be signaled or broadcast.
   MUTEX is assumed to be locked before.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
			      pthread_mutex_t *__restrict __mutex);
			      
/* Wake up one thread waiting for condition variable COND.  */
extern int pthread_cond_signal (pthread_cond_t *__cond);
```

```c
//条件变量也必须初始化，与锁类似，两种方式： 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_init( __cond, __cond_attr);
    
//销毁也类似
/* Destroy condition variable COND.  */
extern int pthread_cond_destroy (pthread_cond_t *__cond);
```



```c
//mythreads.h
void Pthread_cond_init( pthread_cond_t *__restrict __cond,
			      const void*__restrict __cond_attr )
{
    int rc = pthread_cond_init( __cond, __cond_attr);
     assert( rc == 0 );
}

void cond_destroy( pthread_cond_t *__restrict __cond )
{
    int rc = pthread_cond_destroy(__cond);
     assert( rc == 0 );
}
```



# Lock

* 锁的状态：
  * `available`
  * `acquired`
* 方法：
  * `lock()`: 尝试获取锁，如果锁是`available`，则获取锁，进入临界区
  * `unlock()`: 使锁`available`

* 锁提供了最小程度的调度控制
  * 线程由OS调度， 锁让程序员获得了一些控制权
* 通常用不同的锁保护不同的数据（ 细粒度的方案 ）

## 评价锁

* 有效性： 提供互斥
* 公平性`fairness`:  当锁可用时，是否每一个竞争线程有公平的机会抢到锁
  * 是否有竞争锁的线程会饿死`starve`?
* 性能` performance`

## 控制中断

最早提供的互斥解决方案之一，就是在临界区关闭中断：

```c
void lock(){
	DisableInterrupts();
}

void unlock(){
    EnableInterrupts();
}
```

假设在单CPU系统上，这段代码在临界区关闭中断，从而原子地执行，结束后又重新打开中断



* 缺点：

  * 需要允许所有线程执行特权操作（开关中断）
    * 即，需要信任机制不被滥用
  * 不支持多处理器
    * 中断的开关只是对CPU而言，如果一个多个线程运行在不同CPU上，其中一个CPU关闭中断，其他CPU依然响应中断，在其上的线程依然能进入临界区
  * 关中断导致**中断丢失**，可能导致严重的系统问题
    * 比如磁盘完成了读取请求，但CPU错失了该消息

* 因此，用**关中断来实现互斥原语**的情况很有限

  * 有些情况下OS自身会采用关中断的方式来保证访问数据的原子性，此时该用法是可行的，因为OS内部不存在信任问题

*  很多人热衷于研究不依赖硬件实现的锁机制，事实证明，只需很少的硬件支持，实现锁就会容易很多




## test-and-set

* `test-and-set instruction`,  也称为`atomic exchange`,  由硬件支持

*   先实现一个不依赖它的锁：

  ```c
  //想法是： 用一个flag来表示锁是否被占用
  
  typedef struct  lock_t( int flag; ) lock_t;
   
  void init( lock_t *mutex )
  {
      mutex -> flag = 0; // 0 -> lock is available
  }
  
  void lock( lock_t *mutex )
  {
      while( mutex -> flag == 1 )
          ; // spin-wait( do nothing )
      mutex -> flag = 1;
  }
  
  void unlock( lock_t *mutex )
  {
      mutex -> flag = 0;
  }
  ```

  * 这段代码有两个问题：

    * 正确性：

      | Thread`                            | Thread2                       |
      | ---------------------------------- | ----------------------------- |
      | ( 初始时，flag == 0 )  call lock() |                               |
      | while( flag == 1 )                 |                               |
      | interrupt: switch to Thread2       |                               |
      |                                    | call lock()                   |
      |                                    | while( flag == 1 )            |
      |                                    | **flag = 1;**                 |
      |                                    | interrupt: switch to Thread 1 |
      | **flag = 1( too ! )**              |                               |

    * 性能问题：

      * 这个锁是**自旋**的，一个线程自旋等待另一个线程释放锁，浪费时间
        * 对于单CPU，因为同一时间只有一个线程，且自旋的线程永远不会放弃CPU,本线程自旋时，持有锁的线程根本无法运行，也不可能释放锁
          * 需要抢占式的调度器（ ` preemptive scheduler` , 即不断通过时钟中断一个线程，运行其他线程 )

  

### 用test-and-set实现锁

  *  在x86上称为 `xchg`指令， 

    ```c
    int TestAndSet( int *old_ptr, int new )
    {
        int old = *old_ptr;
        *old_ptr = new;
        return old;
    }// 返回old_ptr指向的旧值，将old_ptr指向新值
    ```

    硬件保证，上述操作是原子的

  * 可以理解为：一个厕所门上挂着钥匙(`0`)，两个用户都有一个名牌(`1`)，用户每次进出厕所，需要拿手上的东西和门上的东西交换，用户需要拿到钥匙才能进厕所。 

    * 用户一拿名牌和钥匙交换，拿着钥匙进了厕所

    * 用户二拿名牌交换，此时门上是名牌，用户二没有拿到钥匙，无法进厕所

      * 他会一直交换：

        ```c
        while( TestAndSet( &lock -> flag, 1 ) == 1 )
        	; //spin
        ```

        

    * 用户一从厕所出来，拿名牌和手上的钥匙交换，此时门上又有钥匙了

  * 缺点：

    * 如上述

* 评价自旋锁：
  * 有效性：OK
    * 公平性：不提供任何公平性保证( 对`test-and-set`而言 )
    * 性能： 单核下很差，多核下还不错

## compare-and-exchange

* 某些系统提供了另一个硬件原语: ` compare-and-exchange `( on x86 )

  ```c
  //返回ptr指向的旧值，将ptr指向新值（如果旧值与期望值相等的话）
  int CompareAndExchange(  int *ptr, int expected, int new )
  {
      int actual = *ptr;
      if( actual == expected )
          *ptr = new;
      return actual;
  }
  ```

  该指令比`test-and-set`更强大

## fetch-and-add

```c
int FetchAndAdd( int *ptr )
{
    int old = *ptr;
    *ptr = old + 1;
    return old;
}

typedef struct lock_t
{
    int ticket;
    int turn;
} lock_t;

void lock_init( lock_t *lock )
{
    lock -> ticket = 0;
    lock -> turn = 0;
}

void lock(lock_t *lock)
{
    int myturn = FetchAndAdd( &lock->ticket );
    while( lock-> turn != myturn )
        ; //spin
}

void unlock( lock_t *lock )
{
    FetchAndAdd( &lock-> turn );
}
```

* 解释：`ticket`是一个全局的号码，`turn`是全局的轮次。 每个用户从ticket得到自己的`turn`， 每交易一次，`ticket++`. 只有到达自己的turn的用户才能进入临界区，每当一个用户从临界区出来， `turn++`
  * `myturn < turn`的用户只能自旋

* 本方法能保证所有线程都能抢到锁，只要一个线程获得了`ticket`，就能被调度
  * `test-and-set`无法保证

## 自旋过多的解决方案

* 我们已经实现了有效、公平（ 借助`ticket`）的锁，但自旋会导致性能降低
  * 自旋会重复检查一个不会改变的值，浪费CPU时间

### 方案一  yield

* 在要自旋的时候，放弃CPU

```c
void lock()
{
	while( TestAndSet(&flag, 1 ) == 1 )
		yield(); //give up the CPU
}
```

* 假定OS提供原语`yield()`，可以让线程从`running`变为`ready`
  * 本质上，就是`deschedule`
* 假设100个线程竞争1个锁，该方案会`yield`99次，比自旋99次好，但仍不够完美

### 方案二 使用队列： 休眠代替自旋

```c
1    typedef struct  lock_t {
2        int flag;
3        int guard;
4        queue_t *q;
5    } lock_t;
6
7    void lock_init(lock_t *m) {
8        m->flag = 0;
9        m->guard = 0;
10       queue_init(m->q);
11   }
12
13   void lock(lock_t *m) {
14       while (TestAndSet(&m->guard, 1) == 1)
15           ; //acquire guard lock by spinning
16       if (m->flag == 0) {
17           m->flag = 1; // lock is acquired
18           m->guard = 0;
19       } else {
20           queue_add(m->q, gettid());
21           m->guard = 0;
22           park();
23       }
24   }
25
26   void unlock(lock_t *m) {
27       while (TestAndSet(&m->guard, 1) == 1)
28           ; //acquire guard lock by spinning
29       if (queue_empty(m->q))
30           m->flag = 0; // let go of lock; no one wants it
31       else
32           unpark(queue_remove(m->q)); // hold lock (for next thread!)
33       m->guard = 0;
34   }
```



看不懂QAQ,为啥unpark的时候不把flag设为0啊，这样所有其他进程都无法获得锁

# Concurrent Data Structure Based on Lock

* 通过锁使得数据`thread safe`
* 可扩展性： 理想状态下的多线程的每个线程就和单线程一样快，二者的比值就是并发方法的**扩展性**

##  并发计数器

```c
1    typedef struct  counter_t {
2        int            value;
3        pthread_mutex_t lock;
4    } counter_t;
5
6    void init(counter_t *c) {
7        c->value = 0;
8        Pthread_mutex_init(&c->lock,  NULL);
9    }
10
11   void increment(counter_t *c) {
12       Pthread_mutex_lock(&c->lock);
13       c->value++;
14       Pthread_mutex_unlock(&c->lock);
15   }
16
17   void decrement(counter_t *c) {
18       Pthread_mutex_lock(&c->lock);
19       c->value--;
20       Pthread_mutex_unlock(&c->lock);
21   }
22
23   int get(counter_t *c) {
24       Pthread_mutex_lock(&c->lock);
25       int rc = c->value;
26       Pthread_mutex_unlock(&c->lock);
27       return rc;
28   }
```

* 性能一般

## 扩展并发计数器

* 懒惰计数器`sloopy counter`:  例如，在4CPU机器上，有四个局部计数器和一个全局计数器，每个计数器有一把锁。

  * 不同CPU上的计数器不会竞争
  * 为了保持全局计数器更新，如果局部值大于阈值S，局部值就要转移到全局值（此时要获取全局锁）
    * 阈值越大，可扩展性越好，但计时器精度更低

```c
1    typedef struct  counter_t {
2        int             global;            // global count
3        pthread_mutex_t glock;             // global lock
4        int             local[NUMCPUS];    // local count (per cpu)
5        pthread_mutex_t llock[NUMCPUS];    // ... and locks
6        int             threshold;         // update frequency
7    } counter_t;
8
9    // init: record threshold, init locks, init values
10   //       of all local counts and global count
11   void init(counter_t *c, int threshold) {
12       c->threshold = threshold;
13
14       c->global = 0;
15       pthread_mutex_init(&c->glock,  NULL);
16
17       int i;
18       for (i = 0; i < NUMCPUS; i++) {
19           c->local[i] = 0;
20           pthread_mutex_init(&c->llock[i],  NULL);
21       }
22   }
23
24   // update: usually, just grab local lock and update local amount
25   //        once local count has risen by 'threshold', grab global
26   //        lock and transfer local values to it
27   void update(counter_t *c, int threadID, int amt) {
28       pthread_mutex_lock(&c->llock[threadID]);
29       c->local[threadID] += amt;               // assumes amt > 0
30       if (c->local[threadID] >= c->threshold) { // 局部值大于阈值，transfer to global
31           pthread_mutex_lock(&c->glock);
32           c->global += c->local[threadID];
33           pthread_mutex_unlock(&c->glock);
34           c->local[threadID] = 0;//本地值清0, 注意到不会与其他cpu上的线程竞争，因此是安全的
35       }
36       pthread_mutex_unlock(&c->llock[threadID]);
37   }
38
39   // get: just return global amount (which may not be perfect)
40   int get(counter_t *c) {
41       pthread_mutex_lock(&c->glock);
42       int val = c->global;
43       pthread_mutex_unlock(&c->glock);
44       return val; // only approximate!
45   }
```

##   并发链表

```c
1    // basic node structure，单链表
2    typedef struct  node_t {
3        int                key;
4        struct  node_t        *next;
5    } node_t;
6
7    // basic list structure (one used per list)
8    typedef struct  list_t {
9        node_t                *head;
10       pthread_mutex_t    lock;
11   } list_t;
12
13   void List_Init(list_t *L) {
14       L->head = NULL;
15       pthread_mutex_init(&L->lock,  NULL);
16   }
17
18   int List_Insert(list_t *L, int key) {
19       pthread_mutex_lock(&L->lock);
20       node_t *new = malloc(sizeof(node_t));
21       if (new == NULL) {
22           perror("malloc");
23           pthread_mutex_unlock(&L->lock); //malloc失败，记得释放锁！
24           return -1; // fail
25       }
26       new->key = key;
27       new->next = L->head;
28       L->head = new;
29       pthread_mutex_unlock(&L->lock);
30       return 0; // success
31   }
32
33   int List_Lookup(list_t *L, int key) {
34       pthread_mutex_lock(&L->lock);
35       node_t *curr = L->head;
36       while (curr) {
37           if (curr->key == key) {
38               pthread_mutex_unlock(&L->lock); //在意外退出时unlock
39               return 0; // success
40           }
41           curr = curr->next;
42       }
43       pthread_mutex_unlock(&L->lock);
44       return -1; // failure
45   }
```

* 在开头lock,结尾unlock, 注意到`malloc`失败后也要记得unlock
  * 这种在代码中多次unlock的写法很丑陋！ 应该修改
    * 要么出错的地方不要放在临界区
    * 要么出错时break到主循环，在主循环内统一unlock
* 这是粗粒度的写法，可以更细粒度地优化：

```c
18   int List_Insert(list_t *L, int key) {
19      //local的数据，不需要锁保护
20       node_t *new = malloc(sizeof(node_t));
21       if (new == NULL) {
22           perror("malloc");
23           pthread_mutex_unlock(&L->lock); //出错时不在临界区，无需unlock
24           return -1; 
25       }
26       new->key = key;
27    	//just lock critical section !!!!!
28       pthread_mutex_lock(&L->lock);
29       new->next = L->head;
30       L->head = new;
31       pthread_mutex_unlock(&L->lock);
32       return 0; 
33   }

33   int List_Lookup(list_t *L, int key) {
    	 int rv = -1;// success / failure
34       pthread_mutex_lock(&L->lock);
35       node_t *curr = L->head;
36       while (curr) {
37           if (curr->key == key) {
38               rv=0;
39               break; // 跳出主循环，在主循环内统一unlock ！！！
40           }
41           curr = curr->next;
42       }
43       pthread_mutex_unlock(&L->lock);
44       return rv; // now both success and failure
45   }
```

## 扩展链表

* 过手锁`hand-overohand locking`: 每个节点都有一个锁，替代之前整个链表一个锁，遍历链表时，首先抢占下一个节点的锁，然后释放当前节点的锁
  * 开销巨大，未必比单锁快
* 注意控制流的变化导致函数返回和退出，这种情况下要**记得释放锁**

## 并发队列

粗粒度的锁很简单，接下来使用细粒度的锁

* 对队列头和尾各设置一个锁
  * 因为出队只访问`head`锁， 入队只访问`tail`锁， 两把锁使得出队和入对可以并发执行

```c
1    typedef struct  node_t {
2        int                 value;
3        struct  node_t     *next;
4    } node_t;
5
6    typedef struct  queue_t {
7        node_t            *head;
8        node_t            *tail;
9        pthread_mutex_t    headLock;
10       pthread_mutex_t    tailLock;
11   } queue_t;
12
13   void Queue_Init(queue_t *q) {
14       node_t *tmp = malloc(sizeof(node_t));
15       tmp->next = NULL;
16       q->head = q->tail = tmp;
17       pthread_mutex_init(&q->headLock,  NULL);
18       pthread_mutex_init(&q->tailLock,  NULL);
19   }
20
21   void Queue_Enqueue(queue_t *q, int value) {
22       node_t *tmp = malloc(sizeof(node_t));
23       assert(tmp != NULL);
24       tmp->value = value;
25       tmp->next = NULL;
26
27       pthread_mutex_lock(&q->tailLock);//入队只访问`tail`锁
28       q->tail->next = tmp;
29       q->tail = tmp;
30       pthread_mutex_unlock(&q->tailLock);
31   }
32
33   int Queue_Dequeue(queue_t *q, int *value) {
34       pthread_mutex_lock(&q->headLock);//出队只访问`head`锁
35       node_t *tmp = q->head;
36       node_t *newHead = tmp->next;
37       if (newHead == NULL) {
38           pthread_mutex_unlock(&q->headLock);
39           return -1; // queue was empty，这种写法（在子控制流unlock）很丑陋，应该像之前《重写并发链表》的 List_Lookup() 一样改造
40       }
41       *value = newHead->value;
42       q->head = newHead;
43       pthread_mutex_unlock(&q->headLock);
44       free(tmp);
45       return 0;
46   }
```

## 并发散列表

* 每个元素都是一个并发链表，也称为“散列桶”
  * 每个散列桶都有一个锁

```c
1    #define BUCKETS (101)
2
3    typedef struct  hash_t {
4        list_t lists[BUCKETS];
5    } hash_t;
6
7    void Hash_Init(hash_t *H) {
8        int i;
9        for (i = 0; i < BUCKETS; i++) {
10           List_Init(&H->lists[i]);
11       }
12   }
13
14   int Hash_Insert(hash_t *H, int key) {
15       int bucket = key % BUCKETS;
16       return List_Insert(&H->lists[bucket], key);
17   }
18
19   int Hash_Lookup(hash_t *H, int key) {
20       int bucket = key % BUCKETS;
21       return List_Lookup(&H->lists[bucket], key);
22   }
```

## Conclusion

* Knuth定律： **避免不成熟的优化**
  * 先最简单的方案，也就是加大锁（ `big kernel lock, BKL. in linux kernel` ）开始， 如果有性能问题再改进
* 控制流变化时记得获取和释放锁
* 增加并发并不一定能提高性能
  * 过手锁

# Conditional Variable

* 条件变量： 一个显示**队列**， 当`condition`不满足时，线程把自己加入队列，`waiting`该条件。 当另外某个线程改变该`condition`时，就可以**唤醒**`signal`一个或者多个（假唤醒）等待线程，让它们继续执行

  * `wait(  mutex )`: 该函数假定在`wait()`时， `mutex`是上锁状态。 `wait()`的职责是释放锁， 并让调用进程休眠（原子地）。 当线程被唤醒时（在另外某个线程`signal`它之后）它重新获取锁，再返回调用者

    * 这样使得`wait()`写起来很方便：

      ```c
           Pthread_mutex_lock(&m);
           while(done==0)
              Pthread_cond_wait(&c,&m);//wait释放锁，线程进入休眠。 当被signal时，wait获取锁，再返回调用者。 不用手写unlock\lock了
          Pthread_mutex_unlock(&m);
      ```

* 总结：`signal`和`wait`时总是持有锁 + 需要状态变量

  * `wait()`的语义强制要求调用时已经持有锁，因此不需要操心

```c
#include<stdio.h>
#include<pthread.h>
#include"mythreads.h"
#include<stdlib.h>

int done = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;


 void thr_exit()
 {
     Pthread_mutex_lock(&m);
     done = 1;
     Pthread_cond_signal(&c);
     Pthread_mutex_unlock(&m);
 }

 void thr_join()
 {
     Pthread_mutex_lock(&m);
     while(done==0)// 推荐使用while循环而不是if,原因之后解释
        Pthread_cond_wait(&c,&m);
    Pthread_mutex_unlock(&m);
 }

void * child( void*arg )
{
    printf( "child\n" );
    thr_exit();
    return NULL;
}

int main( int argc, char* argv[])
{
    pthread_t  p;
    
    printf("parent: begin\n");
    Pthread_create(&p, NULL,child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
```

* 情况一： parent创建出子进程后，自己继续运行（假设单核），然后马上调用`thr_join()` 等待子进程，此时它会先获取锁，检查子进程是否完成（还没有），然后调用`wait()`，让自己休眠。 子线程最终得以运行，打印出“child”， 并调用`thr_exit()`唤醒父进程， 而`exit()`及哦原子地设置`done`，向父进程`signal`， 最后父进程会运行，从`wait()`返回并持有锁， 释放锁， 打印出“parent: end”
* 情况二：子进程创建后立刻运行， 设置`done = 1`， 调用`signal()`唤醒其他线程（这里没有其他线程），然后结束。 副进程运行后，调用`thr_join()`时，发现`done`已经为1了，就直接返回

```
parent: begin
child
parent: end
```

* 状态变量`done`是**必要**的

  假如没有：

  ```c
   void thr_exit()
   {
       Pthread_mutex_lock(&m);
       Pthread_cond_signal(&c);
       Pthread_mutex_unlock(&m);
   }
  
   void thr_join()
   {
      Pthread_mutex_lock(&m);
      Pthread_cond_wait(&c,&m);
      Pthread_mutex_unlock(&m);
   }
  ```

  * 假如子线程立刻运行，且调用`thr_exit`，此时子进程`signal()`，条件变量上没有睡眠的线程。 副线程运行时，就会调用`wait（）`并卡在这里，没有线程会`signal（）`它

* 发信号和等待时加锁也是必要的

  假如没有：

  ```c
   void thr_exit()
   {
       done = 1;
       Pthread_cond_signal(&c);
   }
  
   void thr_join()
   {
       while(done==0)// 推荐使用while循环而不是if,原因之后解释
          Pthread_cond_wait(&c,&m);
   }
  
  ```

  * 如果副进程调用`thr_join()`,检查`done = 0`，试图睡眠，然而在调用`wait（）`前被中断， 子进程修改变量为1,发出`signal（）`，此时没有睡眠进程。 父进程再次运行时，就会卡在`wait()`，没有线程可以唤醒它

## 生产者/消费者（有界缓冲区）问题

## 覆盖条件

# 信号量

## 二值信号量（锁）

## 信号量用作条件变量

## 生产者/消费者（有界缓冲区）问题

## 读者 --- 写者锁

## 哲学家就餐问题

## 如何实现信号量

## Conclusion

# 常见并发问题

## 缺陷类型

## 非死锁缺陷

## 死锁缺陷

## Conclusion

# 基于事件的并发（Advanced）

## 事件循环

## select（）

## 为何更简单 ？ 无需锁

## 阻塞系统调用

## 状态管理

## Hard Problems

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

* 

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

