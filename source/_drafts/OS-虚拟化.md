---
title: OS 虚拟化
tags: Operating Systems Three Easy pieces 
categories: OS
---

# CPU虚拟化

## 进程

* **进程是虚拟化的CPU**

* 进程映像包括:

  * 进程控制块( PCB)
  * 进程程序块
  * 进程数据块
  * 内核栈
    * 在`x86`上，执行`TRAP`时， CPU会将一些寄存器保存到该进程的内核栈上， 从`TRAP`返回将弹出这些值，并恢复`user mode`

* 进程状态图：

  * 三状态：

    ![image-20220124225452048](/home/lyk/snap/typora/46/.config/Typora/typora-user-images/image-20220124225452048.png)

  * 七状态：

    ![image-20220124225549353](/home/lyk/snap/typora/46/.config/Typora/typora-user-images/image-20220124225549353.png)

* 父进程与子进程没有撤销时的相互依赖关系。即儿子死了爹可以活着,爹死了,儿子也可以活着,
  其父进程变为:init进程。

## 进程API

### fork（）

```c
//5_1.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{
    printf( "hello world (pid: %d)\n", (int) getpid()  );
    int rc = fork();
    if(rc < 0)
    {
        fprintf( stderr, "fork failed \n" );
        exit(1);
    }
    else if(rc == 0)
    {
        printf("hello, I am child (pid: %d)\n", (int)getpid());
    }
    else{
        printf("hello, I am parent of %d (pid: %d)\n", rc, (int)getpid() );
    }
    return 0;
}
```

```
hello world (pid: 5951)
hello, I am child (pid: 5957)
hello, I am parent of 5957 (pid: 5951)
```

* `fork()`创建进程

* 子进程不会从` main()`开始执行，而是从`fork()`处返回，就像它自己调用了`fork()`

* 子进程几乎完全拷贝了父进程，拥有和父进程相同的地址空间，寄存器，PC等，但它从`fork()`获得的返回值不同

* `fork()`返回值：

  * ERRORS： -1

  *  子进程： 0

  * 父进程：  新创建的子进程的PID

    

### wait（）

```c
//5_2.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    printf( "hello world (pid: %d)\n", (int) getpid()  );
    int rc=fork();
    if(rc < 0)
    {
        fprintf( stderr, "fork failed \n" );
        exit(1);
    }
    else if(rc == 0)
    {
        printf("hello, I am child (pid: %d)\n", (int)getpid());
    }
    else{
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int)getpid() );
    }
    return 0;

}
```

```
hello world (pid: 6747)
hello, I am child (pid: 6762)
hello, I am parent of 6762 (wc: 6762) (pid: 6747)
```



* `wait()`会在子进程运行结束后才返回
* 如果父进程先运行，它会马上调用`wait()`

### exec（）

```c
//5_3.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


int main()
{
    printf( "hello world (pid: %d)\n", (int) getpid()  );
    int rc = fork();
    if(rc < 0)
    {
        fprintf( stderr, "fork failed \n" );
        exit(1);
    }
    else if(rc == 0)
    {
        printf("hello, I am child (pid: %d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");//program: "wc"(word count)
        myargs[1] = strdup("5_3.c");//argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp( myargs[0], myargs );
        printf("this shouldn't print put");
    }
    else{
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int)getpid() );
    }
    return 0;
}
```



```
hello world (pid: 7615)
hello, I am child (pid: 7634)
 32  98 810 5_3.c
hello, I am parent of 7634 (wc: 7634) (pid: 7615)
```

`exec()`:  replaces the current process image with a new process imag. 将当前进程的内容替换为不同的程序（`wc`）

* 对`exec()`的成功调用永远不会返回，因为子进程的内容是新的程序
* `execvp(const char *file, char *const argv[])`: one of `exec()` family
  * The initial argument for these functions is the name of a file that is to be executed.
  * The **char** ***const** **argv[]** argument is an array of pointers to null-terminated strings that represent the argument list available to  the new  program.  The first argument, by convention, should point to the <u>filename associated with the file being executed</u>.  The array of pointers **must** be terminated by a null pointer.( 因此有`arg[2] = NULL` )

#### 插叙 Shell

* `fork()`和`exec()`分离，使得程序可以在`fork()`之后，`exec()`之前运行代码
* `shell`的workflow：
  1. 显示一个`prompt`,等待用户输入
  2. 用户输入，是一个命令，由一个可执行程序和若干参数组成
  3. `shell`找到该可执行程序。调用`fork()`创建新进程
  4. `shell`可能执行某些代码，当
  5. 调用`exec()`执行这个可执行程序
  6. 调用`wait()`等待该命令完成
  7. 子进程执行结束后，shell从`wait()`返回，继续步骤1
* shell实现重定向：对于`$> wc 5_2.c > [filename].txt`, wc的输出结果被重定向到`[filename].txt`
  * 在`fork()`之后，`exec()`之前先关闭standard output, 打开文件`[filename].txt`, 由于UNIX系统会从零开始寻找可用的文件描述符，因此`STDOUT_FILENO`会成为第一个可用的文件描述符，作为子进程输出的目标
  * 详见《OS 持久性 》
* UNIX pipe也用类似方式实现，但使用`pipe()`系统调用,将前一个进程的输入作为后一个进程的输出：`grep -o foo fole | wc -l`

## Limited directed execution

*   OS首先（在启动时）设置`trap table`并开启时钟中断 （都是特权操作），然后仅在受限模式下运行进程。 只在执行特权操作，或者当进程需要切换时，才需要OS干预

### OS重获CPU控制权

*   如果一个进程在CPU上运行，那么OS无法运行。 因此OS需要重获CPU的控制权
  * 等待系统调用： 进程通过`syscall`主动放弃CPU, 比如`yield`
  * 时钟中断： 时钟设备可以产生中断，产生中断时，当前进程停止，OS中的 interrupt handler运行，此时OS重获CPU控制权
    * 硬件在发生中断时需要为当前进程保存状态

### context switch

* 上下文切换（ `context switch`）: OS获得控制权后，需要觉得是否切换进程，如果要切换，那么需要上下文切换
  * OS为当前进程保存状态，并为即将执行的进程恢复状态
    * "状态": 寄存器，在该进程的内核栈中
    * 事实上，除了寄存器，cache, TLB和其他硬件的状态也被切换，因此context switch的成本可能非常高昂
  * 本质上是为了确保最后从陷阱返回时，不是返回到之前运行的进程，而是继续执行另一个进程

## 插叙 系统调用

*  我们对系统调用的调用，实际上是对C lib中对应函数的函数调用，这些函数遵循了内核的调用约定（如将参数推到栈，执行`TRAP`，返回控制权等）实现了系统调用。 当然，这些C lib中的函数是汇编写的

![image-20220107045440357](/home/lyk/snap/typora/46/.config/Typora/typora-user-images/image-20220107045440357.png)

## 插叙 中断

中断处理过程：

1. 保护CPU状态
2. 分析被中断进程的PSW中断码字段，识别中断源
3. 分别处理发生的中断事件

## Thread Scheduling

### workload

* Def: a fully-operational scheduling discipline
* 我们目前对work load做出如下假设：
  1. 每个工作运行相同的时间（工作就是进程）
  2. 所有的工作同时到达
  3. 一旦开始，所有工作保持运行直到完成
  4. 所有工作只使用CPU（即，不执行IO操作）
  5. 所有工作的运行时间已知

### scheduling metrics

* 性能指标：
  * 周转时间： 任务完成 - 任务到达
  * 响应时间：任务首次运行（服务时间） - 任务到达 
    * 用于度量**交互性**，因为分时系统的用户会面对终端，这要求终端交互性好
*  公平

### 处理器调度层次

* 高级调度（长程调度、作业调度）: 决定能否加入到执行的进程池中
* 中级调度（平衡负载调度）： 决定主存中的可用进程集合
* 低级调度（短程调度、 进程调度）：决定哪个进程占用处理器执行

### 优化周转时间算法

用于批处理作业。下述三个算法都面向“周转时间”，但是当衡量其“响应时间”时，下述算法表现都不好。 对于SJF而言，只要短进程源源不断来,
长进程就饿死

#### FCFS

* First Come First Service: 非抢占,直到某个进程运行结束,依次调度接下来的,偏爱长作业
  * 推翻假设1后（可能出现长作业），该算法fail

#### SJF

* Shortest Job First: 非抢占，先运行最短的任务
  * 再推翻假设2,运行进程不同时到达，此时短任务可能会晚到达，由于算法非抢占，短任务必须等待长任务执行完，该算法fail

#### STCF

* Shortest Time-to-Completion First: 最短完成时间优先: 抢占式SJF,推翻了假设3

### 优化响应时间算法

用于分时系统

#### RR

*   Round Robin:抢占,time slice结束时,当前进程放入就绪队列,然后切换到队列中的下个进程
  * “抢占”是指进程之间。 在同一time slice内，进程不抢占
  * time slice必须是时钟中断周期的倍数
  * time slice太短也不好，因为context switch有成本
* 该算法在“周转时间”表现不佳

### 结合IO的STCF

* 推翻假设4,现在运行程序执行IO。此时假设有两个工作A和B,每项占用`50ms`CPU，但每A运行`10ms`会发起`10ms`的IO请求，而B只使用CPU
* 此时可以把A的每个`10ms`工作视为独立的工作，因此系统先调度`10ms`的A，然后调度`50ms`的B，而`10ms`后新的A会提交，因此会抢占B执行，这样做实现了overlap
* overlap： 一个进程在另一个进程等待IO时使用CPU

### MLFQ

 推翻假设5后，进程运行时间不可知，之前的算法失效

* Multi-Level Feedback:多级反馈调度:  **抢占式**,每当进程被抢占时就降级

  *  建立多个不同优先级的就绪进程队列，多个就绪进程队列之间按照优先级调度
  * 高优先级的就绪进程, 分配的时间片短
  * 同一就绪进程队列中的进程的优先数和时间片相同, 按照FCFS调度
  * 工作进入系统时放在最高优先级
  * 一旦工作用完了其在某一层中的时间片，它就被抢占，自己移入低一级队列
    * 进程只有被抢占后才降级，因此如果一共只有一个进程，该进程不会降级

  

  

  

  

* problem： 如果短工作不断到来，长进程可能饿死
  * 改进： 经过一段时间S, 将系统中所有工作重新加入最高优先级队列

### 比例份额

确保每个工作获得一定比例的CPU时间，实现公平性

份额调度最大的缺点在于难以确定份额，即依赖假设5

#### 彩票调度

* 每个进程持有一定数量的彩票，该进程的彩票数占总彩票数的百分比代表它占有某个资源的份额
* CPU每个时间片随即抽取一个数，拥有该数对应彩票的进程会被调度一个时间片
  * 例如工作A和B分别有75, 25个彩票，对应数字0 - 74, 75 - 99.
  * OS抽取数字序列为：63, 85, 70, 39, 76, 17, 95
  * 工作调度次序为：A, B, A, A, B, A, B
* **随机**， 优点是实现简单，不依赖任何全局量
* PROBLEM：基于概率，因此有可能出现异常情况

#### 步长调度

* 每个进程都具有步长(`stride`), 和一个行程（`pass`）值。 
  * 步长： 一个大数 / 进程的彩票数
  * 初始时所有行程值为0
* 每次调度当前具有最小行程值的进程，每当进程运行一个时间片后后， 行程值 += 步长
  * 进程在时间片内不被抢占

```c
current = remove_min(queue); //pick client with min pass
schedule(current);// use resource for quantum
current -> pass += current -> stride;// compute next pass using stride
insert( queue, current );// put back into the queue
```



* 例子：假设A,B,C彩票数分别为100,50,250, 其步长值分别为100, 200, 40

  1. 初始时所有步长为零，随即调度工作，假设A被调度，执行一个时间片，更新其行程值为100. 然后选择B, 运行后更新其行程值为200； 然后选择C,运行后更新其行程值为40

  2. 然后算法选择最小的工作，它会再调度2次C, C的行程值增加到120. 然后调度A ...

  | 行程值（A） （步长 = 100） | 行程值（A） （步长 = 100） | 行程值（A） （步长 = 100） | 被调度进程 |
  | -------------------------- | -------------------------- | -------------------------- | ---------- |
  | 0                          | 0                          | 0                          | A          |
  | 100                        | 0                          | 0                          | B          |
  | 100                        | 200                        | 0                          | C          |
  | 100                        | 200                        | 40                         | C          |
  | 100                        | 200                        | 80                         | C          |
  | 100                        | 200                        | 120                        | A          |
  | 200                        | 200                        | 120                        | C          |
  | 200                        | 200                        | 160                        | C          |
  | 200                        | 200                        | 200                        | ...        |
  |                            |                            |                            |            |

  可以看到，在这段时间内， A, B, C分别调度2, 1， 4次，与其彩票数占比相符合

* 彩票调度只能在概率上实现比例（因此有概率翻车），而步长调度可以直接控制比例

* PROBLEM： 步长调度需要维护全局状态：行程值。 如果中途有新进程加入，则新进程的行程值为0,它会独占CPU



### HRRN

* HRRN(highest response radio next)高响应比优先**: 非抢占式**
  * 响应比 = (等待时间+服务时间) / 服务时间



### 多处理器调度

#### 缓存一致性

* 一种方案： 总线窥探（`bus snooping`）: 内个缓存都监听链接所有缓存和内存的总线，在发现内存访问。 

#### 同步问题

* 加锁

#### 缓存亲和度

* 同意进程在同一CPU运行时，由于有cache而运行得快

#### SQMS

* 单队列调度（Single-Queue Multiprocessor Scheduling）：所有工作放入一个全局的单调队列。每个CPU从队列中拿取工作

  * 当然，可以将工作以时间片为单位存储进队列，这样CPU每次都运行一个time slice的工作

* 缓存亲和度问题：  假设有CPU 0-3, 队列中工作序列为A,B,C,D,E, 则：

  | CPU0               | CPU1 | CPU2 | CPU3 |
  | ------------------ | ---- | ---- | ---- |
  | A                  | B    | C    | D    |
  | E                  | A    | B    | C    |
  | D                  | E    | A    | B    |
  | C                  | D    | E    | A    |
  | 可以看到亲和度很差 |      |      |      |

  

  

#### MQMS



* 多队列调度（Multi-Queue Multiprocessor Scheduling）: 每个CPU拥有自己的队列。 不同队列可以采用不同的调度规则。OS依据一些启发式规则将新工作放入某个队列
  * 每个CPU之间调度相互独立



#  内存虚拟化

## Address Space

### Address Space of Linux process

* `ld`, `ls`等命令实际上会调用`execve( /usr/bin/COMMAND_NAME )`

  * `execve()`接受只绝对路径

* 进程的地址空间 == 内存中若干连续的“段”

* `mmap`可以将内存中的某一段映射到文件中的某一段

  * 进程中的代码和数据是`mmap`从内存中映射的

  * 可以接受文件描述符

    ```
    void *mmap(void *addr, size_t len, int prot, int flags,
               int fildes, off_t off);
    ```

    

* 查看进程的地址空间： `pmap`

  * 动态链接的程序比静态链接的小，并且链接地快， 用`pmap`分别查看其内容:
    * 静态链接程序的地址空间中有其链接库的内容（二进制文件的代码、数据、bss等）
    * 动态链接程序的地址空间中只有其链接库的指针
    * 可以看到地址空间的高位有三个段：`vvar`, `vdso`, `vsyscall`，用于`virtual system call`
      * `virtual system call`: 不陷入内核的系统调用
  * `pmap`实际上打印了`\proc\PID\maps`的一部分信息
    * 通过`strace pmap XX`可以看到`pmap`调用了`openat( XX, \proc\PID\maps )`

## 内存操作API

## Address Translation

## Link & Load

### static link

* 需求： 允许引用其他文件（C标准称为编译单元`compilation unit`）里定义的符号
  *  C不阻止你随便声明符号的类型
  *  但类型不匹配是`undefined behavior `
* 使用`-Wl,--verbose`可以将`--verbose`传递给`ld`
  * 可以看到`ld script`

```c
//a.c

int foo(int a , int b)
{
    return a + b;
}
```



```c
//b.c
int x = 100;
int y = 200;
```

```c
#include<stdio.h>

extern int x,y;

// extern int foo(int a, int b);
extern int foo;可以看到
int main()
{
    // printf("%d + %d = %d\n", x, y, foo(x,y) );
    printf("%x\n", foo );
    foo = 1;
}
```

```makefile
//Makefile
CFLAGE := -Os

a.out: a.o b.o main.o
		gcc -static -Wl,--verbose a.o b.o main.o
a.o: a.c
		gcc $(CFLAGS) -c a.c
b.o: b.c
		gcc $(CFLAGS) -c b.c

main.o: main.c
		gcc $(CFLAGS) -c main.c
clean:
		rm -f *.o a.out
```

* 刚编译完程序的时候，`main.o`不能运行，因为其外部符号都“留空”
  * `objdump -d a.o` 
  * （符号地址还没有解析，暂时是全零）
* 链接后`objdump -d a.out | grep main` 可以看到其外部符号已经被正确赋值

### static load

静态ELF加载器：加载a.out时执行

* ELF文件中有若干个ELF program header， 描述了文件到内存的映射。

* 静态ELF加载器根据ELF program header,将文件中指定部分移动到内存

  * 遍历ELF中的各个`program header`，然后`read`/ `mmap`

* OS在`execve`时执行：

  * OS在kernel mode调用`mmap`

    (进程还未准备好时，由内核直接执行系统调用)

  * 映射好`a.out`代码、数据、堆、栈、vvar、vdso、vsyscall

* 加载完成后，静态链接的程序就从ELF entry开始执行：

  ```shell
   readelf -h a.out                             
  ELF Header:
    Magic:   7f 45 4c 46 02 01 01 03 00 00 00 00 00 00 00 00 
    Class:                             ELF64
    Data:                              2's complement, little endian
    Version:                           1 (current)
    OS/ABI:                            UNIX - GNU
    ABI Version:                       0
    Type:                              EXEC (Executable file)
    Machine:                           Advanced Micro Devices X86-64
    Version:                           0x1
    Entry point address:               0x401670 //ELF entry 0x401670
    Start of program headers:          64 (bytes into file)
    Start of section headers:          795088 (bytes into file)
    Flags:                             0x0
    Size of this header:               64 (bytes)
    Size of program headers:           56 (bytes)
    Number of program headers:         10
    Size of section headers:           64 (bytes)
    Number of section headers:         32
    Section header string table index: 31
  
  ```

  ```
  gdb a.out  
  ...
  (gdb) starti
  Starting program: /home/lyk/Documents/Hexo/LYK-love.github.io/source/_drafts/Test/a.out 
  
  Program stopped.
  0x0000000000401670 in _start () //可以看到，确实是0x401670
  
  ```

* 查看该进程的地址空间：

  ```
  (gdb) info inferiors
    Num  Description       Connection           Executable        
  * 1    process 15776     1 (native)           /home/lyk/Documents/Hexo/LYK-love.github.io/source/_drafts/Test/a.out 
  (gdb) !cat /proc/15776/maps
  00400000-00401000 r--p 00000000 103:08 3802167                           .../LYK-love.github.io/source/_drafts/Test/a.out
  00401000-00482000 r-xp 00001000 103:08 3802167                           .../LYK-love.github.io/source/_drafts/Test/a.out
  00482000-004a9000 r--p 00082000 103:08 3802167                           .../LYK-love.github.io/source/_drafts/Test/a.out
  004aa000-004b1000 rw-p 000a9000 103:08 3802167                           .../LYK-love.github.io/source/_drafts/Test/a.out
  004b1000-004b2000 rw-p 00000000 00:00 0                                  [heap]
  7ffff7ff9000-7ffff7ffd000 r--p 00000000 00:00 0                          [vvar]
  7ffff7ffd000-7ffff7fff000 r-xp 00000000 00:00 0                          [vdso]
  7ffffffde000-7ffffffff000 rw-p 00000000 00:00 0                          [stack]
  ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
  (gdb) 
  
  ```

  可看到的确有上述内容

### dynamic link & load

* 需求： 节约内存
* Linux系统会共享动态链接库的一个副本（可以用`size`查看内存占用）

* 实现动态加载（代码）：

  * 编译成`Position Independent Code`( PIC )
    * 引用代码全部使用PC相对寻址
    * x86已经是这样了
  * 把代码`mmap`进进程的地址空间

* 实现动态加载（代码+数据+允许访问其他动态链接库导出的符号）：

  * 编译成`Position Independent Code`( **PIC** )
    * 引用代码全部使用PC相对寻址
    * x86已经是这样了
  * 对于其他动态链接库导出的符号，可以在数据区维护一张表，每次引用该符号时就**查表**。在运行时给相应的表项赋值
  * 把代码`mmap`进进程的地址空间

* ELF文件都有 `Global Offset Table`GOT， 即上述的“表”

  * Lazy Symbol Resolution: 不一次性加载GOT的所有符号

## Segmaentation

## Free Space Management

## Paging

## 超越物理内存： 机制

## 超越物理内存： 策略

## VAX/VMS虚拟内存系统

## 内存虚拟化总结

