---
title: OS PROCESSES AND THREADS
tags: OS Basic
categories: OS
date: 2021-10-22 17:13:42
---


Outline:

* Process
* Threads(  只写到这两部分  ) 
* Interprocess Communication
* Scheduling
* Classical IPC problems
* Summary

ref: Modern Operation Systems

 <!--more-->

# Processes

* **multiprogramming**: CPU switch from program to program

* difference between a **process** and a **program** : 想象一个厨师做菜:
  *  program: recipe. That is, an algorithm expressed in some suitable notation.
  * processor: the chef
  * input data: the ingredients
  * process: the activity consisting of the chef reading the recipe, fetching the ingredients, and making the food
*  一个程序若运行两次，那么就是两个进程

## Process Creation

* Four principle events cause processes to be created：
  1. System initialization
     * 进程可分为foreground和background，前者与用户交互，后者又称为**daemon**,运行在后台
  2. Execution of a process-creation system call by a running process
  3. A user request to create a new process
     *  在交互式系统中，用户输入命令或者点击图标，都能创造进程并在里面运行程序
  4. Initiation of a batch job 
     * 只针对批处理系统，用户向系统提交batch jobs,系统若有空余资源，则接受任务，创建一个新进程来运行它，自身则继续接受输入队列中的下一个任务

* UNIX中，进程创建只有一种办法： `fork`. fork后父子进程拥有相同的资源（包括memory image, environment strings, open files）. 子进程然后执行`execve`或其他系统调用来改变自身的memory image 并运行新的程序。
  * `fork` - `execve`分两步的目的是让子进程在`fork`后，`execve`前将父进程的输入和输出重定向

* Win中， `CreateProcess`完成了`fork` - `execve`这两步
* 进程创建后，父子进程各自的address  space独立
  * UNIX：子进程的initial address space 是父进程的copy,然而这块内存是**copy-on-write**的。 每当二者之一要改变该内存，这块内存都会先copy,以确保改变只针对各自进程的private memory
  * WIN：父子进程的 address space 一开始就是不同的

### Process Termination

* Four conditions:
  1. Normal exit(voluntary)
     * 当进程结束其任务时，会发起系统调用通知OS来结束它
     * GUI进程被点击X而关闭也属于这类
  2. Error exit(voluntary)
     * 输入错误，比如没找到文件
  3. Fatal error(involuntary)
     * 程序错误
  4. Killed by another process(involuntary)
     * `kill` in UNIX. killer需要对killee有一定权限
     * 在有些系统中，杀死进程会将其所有子进程也杀死，UNIX和WIN都不这么做

## Process Hierarchies

* UNIX：a process and all of its children and further descendants together form a process group.
  * e.g.  一个keyboard signal会发给与这个keyboard相关的process group的所有成员，每个成员可以独立地处理signal
  * 当UNIX开机时， 一个`init`进程会存在于boot image,`init`读取一个记录了有多少terminal的文件，为每个terminal `fork`一个新进程，新进程等待用户login in,若login in成功，则该进程执行一个shell等待用户输入命令，命令又会创建新的进程。 整个系统的所有进程就形成了以`init`为根节点的树
* WINDOWS：不存在进程层次结构。 父进程会拥有子进程的**handler**，它可用来控制子进程，但handler可被自由传递，因此不存在层次结构

## Process States

*  进程等待输入时，会被block
* 3 states：
  1. Running( actually using the CPU at that instant )
  2. Ready( runnable; temporarily stopped to let another process to run )
  3. Blocked( unable to run until some external event happens)
     *  当所需的事件发生时，会转为Ready
* OS的Process model（只是逻辑上的）:
  * Schedule: 位于最底层，处理所有的中断和进程处理细节
  * Processes: 位于Scheduler之上。OS的其余部分都被组织为process形式

## Implementation of Processes

* To implement process model, the OS maintains a **process table**, with one entry per process.   每个entry存储了该进程被切换后要恢复所需的全部信息

* 每个I/O类都对应一个**interrupt vector**，指向其handler的地址

* 中断发生时，先由硬件来保存pc，等信息，然后计算机跳转到interrupt vector指向的内存，硬件的工作至此结束。接下来是软件的工作，先用汇编程序保存寄存器，设置栈指针，然后C程序执行相应的任务（for the specific interrupt type)，当其工作结束后，一些进程应该已经进入ready（因为它们所需的event发生了），接下来调度器决定接下来运行哪个进程。然后控制交还给汇编程序，加载新的进程：

  1. Hardware stacks program counter, etc.
  2. Hardware loads new program counter from interrupt vector
  3. .Assembly-language procedure saves registers
  4. Assembly-language procedure sets up new stack]
  5. C interrupt service runs( typically reads and buffs input )
  6. Scheduler decides which process is to run next.
  7. C procedures returns to the assembly code.
  8. Assembly-language procedure starts up new current process.

* CPU usage: ( probabilistic view ):

  CPU utilization = $1 - p^n$

  * *p*: CPU用于I/O等待的时间占比
  * *n*: 进程数
  * $p^n$: *n*个进程全都等待I/O的概率
  * 假设电脑拥有8GB内存，2GB用于OS, 每个user program占2GB， CPU I/O等待概率为80%， 则其CPU使用率为$1 - 0.8^3 $

# Threads

*  进程可拥有多个线程，所有线程共享进程的address space
*  进程是竞争关系，线程是合作关系

## Thread Usage

* 线程的优势：
  *  线程可以共享进程的address space
  * 线程比进程更轻量，创建和摧毁也更容易

* （单核下）Web server中， 一个dispatcher负责接受请求，并分发给相应的worker thread, 当worker thread被阻塞时（比如等待磁盘操作），其他线程可以执行，比如dispatcher,它可以继续接受请求

* 3 Designs to construct a server

  | Model                   | Characteristics                                              |
  | ----------------------- | ------------------------------------------------------------ |
  | Threads                 | Parallelism, blocking system calls                           |
  | Single-threaded process | No parallelism, blocking system calls( 系统在阻塞时无法接受请求 ) |
  | Finite-state machine    | Parallelism, nonblocking system calls ,interrupts            |

  

## The Classical Thread Model

* The  Thread Model is based on 2 independent concepts: **resource grouping** and **execution**

* Process用于资源分组， 而 Thread用于执行
  * 当一个线程打开一个文件，其他线程可以使用该文件。 这是合理的，因为进程才是资源分配的单位，这些线程都在一个进程下
  * each thread has its own stack

## POSIX Threads

* UNIX 线程标准库: **Pthreads**

## Implementing Threads in User Space

有两种实现线程的方式：user space and the kernel

将线程放入user  space，kernel不知道线程的存在，kernel只面对单线程的进程

* 可以在不支持多线程的OS上运行，因为kernel面对的都是单线程的进程
* 每个进程拥有run-time system,which is a collection of procedures that manage threads. 每个进程拥有各自的 **thread table**
* 进程运行在run-time system上层
* thread table在run-time system内
*  当线程执行可能使其阻塞的任务时，它会发起run-time system procedure，后者查看该进=线程是否应该被阻塞，若是，则保存其（线程自己的）寄存器，并在thread table里找到并加载新的ready的线程，并新线程的寄存器载入机器的寄存器。 这些都在用户层进行，避免了陷入内核层的开销

* 缺点：
  * 阻塞式系统调用很难实现
    * **没看懂**
  * 当一个进程发生**page fault**( 数据在硬盘中，而不在内存中 )时，OS会阻塞整个进程（因为OS眼中进程都是单线程的，它认为是这个线程发生了page fault），此时其他线程都无法运行
  * 在一个线程中没有clock signal( interrupt )， 因此无法对线程的使用时间进行调度，因此除非一个运行时的线程主动退出，否则其他线程无法运行

## Implementing Threads in the Kernel

没有run-time system, kernel有一个thread table记录**所有线程**（而非每个进程一个thread table），新线程的创建需要system call

* 所有可能阻塞线程的调用都被实现为系统调用
  * 当一个线程阻塞时，kernel可以运行该进程下的另一个线程，**也可以运行其他进程的线程**。 而在user space版的实现中，一个run-time system只能运行其自己的进程下的进程
* 由于创建和摧毁线程的代价高昂，在这个视线里广泛采用线程复用技术
  * 当线程被摧毁时，它只是被标记为 not runnable, 它的结构体没有被销毁

* 当一个线程发生page fault,OS可以切换到该进程的另一个线程

## Hybrid Implementations

* kernel面对kernel-level线程，而这些线程可能拥有多个user-level线程
* 可以在不支持多线程的OS上运行

## Scheduler Activations

让Threads in the user space拥有in kernel的功能，又能不失去太多性能的方案之一

* 当一个thread阻塞时，没有必要通知内核，由run-time system处理

* 为每个进程分配一个虚拟cpu,让run-time system将线程分配给虚拟cpu
* 当kernel知道一个thread阻塞时，它会告知run-time system, 让后者进行线程切换。 当线程又恢复到ready， kernel也会告知run-time system
  * “告知”机制被称为**upcall**
* 该方法的问题在于：upcall的原理是下层使用了上层的服务，违反了OS分层的原则

## Pop-Up Threads

* 当分布式系统接收到一个message时，它会创建一个 brand new thread来处理该message
  * 传统方法是，令一个thread一直等待请求。 而pop-up让OS直接创建新Thread,新进程**没有任何数据**，因此创建的开销非常小

## Making Single-Threaded Code Multithreaded

我们假设采用in user space的实现方案

* 困难：

  * 全局变量的数据竞争
  * 库函数不全都是reentrant. 比如假设向一块buffer内写入数据，此时切换到另一个thread,修改了buffer,在回到原tread,此时就会发生错误。write函数并不确保可重入
    * 方案
      1. 重写库函数， 不是个good idea
      2.  对每个procedure传入一个jacket,用一些位数来表明正在被使用的库函数。如果要切换到的新进程要使用原进程的库函数，而原进程的库函数还没有结束，该切换就被禁止。 这个方案极大地限制了并行

  * 线程各自的stack的管理， 由于kernel不知道多thread的存在（它们都在user space），那么很难在内存中正确地管理各个thread的stack

* 以上困难并非不可克服，但它们揭示了：在已有系统内加入多线程机制而不对系统本身做出改变是不可能的

# Interprocess Communication

TODO 急的话请催一催我QAQ

# Scheduling

# Classical IPC problems

# Summary

