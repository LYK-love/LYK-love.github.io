---
title: OS Virtualization
tags: OS Basic
categories: Computer Science
mathjax: true
date: 2022-04-16 22:38:59
---


Outline:

* CPU虚拟化
* 内存虚拟化

<!--more-->

# CPU虚拟化

## 进程

* **进程是虚拟化的CPU**

* 进程映像包括:

  * 进程控制块( PCB)
  * 进程程序块
  * 进程数据块
  * 内核栈
    * 在`x86`上，执行`TRAP`时， CPU会将一些寄存器保存到该进程的内核栈上， 从`TRAP`返回将弹出这些值，并恢复`user mode`

* 进程三状态图：

  ![Thread Status](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/Thread Status.png)

  

* Linux父进程与子进程在终止时没有相互依赖关系。即爹死了儿子也可以活着, 只是其父进程变为`init`进程( init 进程是系统的第一个进程，PID=1)

## 进程API

注意，`fork()`和`exec()`是分离的，这使得程序可以在`fork()`之后，`exec()`之前运行代码，最典型的例子是shell的workflow，参见*Using Shell*

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

## 插叙 Shell

* `fork()`和`exec()`分离，使得程序可以在`fork()`之后，`exec()`之前运行代码
* 

## Limited directed execution

OS首先（在启动时）设置`trap table`并开启时钟中断 （都是特权操作），然后仅在受限模式下运行进程。 只在执行特权操作，或者当进程需要切换时，才需要OS干预

### OS重获CPU控制权

如果一个进程在CPU上运行，那么OS无法运行。 因此OS需要重获CPU的控制权
* 等待系统调用： 进程通过`syscall`主动放弃CPU, 比如`yield`
* 时钟中断： 时钟设备可以产生中断，产生中断时，当前进程停止，OS中的 interrupt handler运行，此时OS重获CPU控制权
  * 硬件在发生中断时需要为当前进程保存状态

### context switch

上下文切换（ `context switch`）: OS获得控制权后，需要觉得是否切换进程，如果要切换，那么需要上下文切换
* OS为当前进程保存状态，并为即将执行的进程恢复状态
  * "状态": 寄存器，在该进程的内核栈中
  * 事实上，除了寄存器，cache, TLB和其他硬件的状态也被切换，因此context switch的成本可能非常高昂
* 本质上是为了确保最后从陷阱返回时，不是返回到之前运行的进程，而是继续执行另一个进程

## 插叙 系统调用

*  我们对系统调用的调用，实际上是对C lib中对应函数的函数调用，这些函数遵循了内核的调用约定（如将参数推到栈，执行`TRAP`，返回控制权等）实现了系统调用。 当然，这些C lib中的函数是汇编写的



## 插叙 中断

![Interruption](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/Interruption.png)

> 在指令执行周期最后增加一个微操作，以响应中断，CPU在完成执行阶段后，如果允许中断，则进入中断阶段

中断处理过程：

1. 保护CPU状态
2. 分析被中断进程的PSW中断码字段，识别中断源
3. 分别处理发生的中断事件

## Thread Scheduling

详见*OS Thread Sheduling Algorithm*

#  内存虚拟化

我们的编写和编译程序时假定内存从0开始，事实上，程序执行时，OS会决定其在物理内存中的实际加载地址

* 前者称为地址空间（虚拟空间），后者称为物理空间

## Address Space

### Address Space of Linux process

* `ld`, `ls`等命令实际上会调用`execve( /usr/bin/COMMAND )`

  * `execve()`只接受绝对路径

* 进程的地址空间 == 内存中若干连续的“段”

* `mmap`可以将内存中的某一段映射到文件中的某一段

  * 进程中的代码和数据是`mmap`从内存中映射的

  * 可以接受文件描述符

    ```c
    void *mmap(void *addr, size_t len, int prot, int flags,
               int fildes, off_t off);
    ```

    

* 查看进程的地址空间： `pmap`

  * 动态链接的程序比静态链接的小，并且链接得快， 用`pmap`分别查看其内容:
    * 静态链接程序的地址空间中有其链接库的内容（二进制文件的代码、数据、bss等）
    * 动态链接程序的地址空间中只有其链接库的指针
    * 可以看到地址空间的高位有三个段：`vvar`, `vdso`, `vsyscall`，用于`virtual system call`
      * `virtual system call`: 不陷入内核的系统调用
  * `pmap`实际上打印了`/proc/PID/maps`的一部分信息
    * 通过`strace pmap XX`可以看到`pmap`调用了`openat( XX, \proc\PID\maps )`

## Segmaentation

在MMU中引入不止一个基址/界限寄存器对，而是给每个逻辑段一对，这可以将每个段独立地载入物理内存。 由于只有已用的内存才在物理内存中分配空间，因此可以容纳巨大的地址空间

* 段：在内存空间中的一段连续定长（段有段界限）区域
* 引用非法地址就会引发段错误
* 分段会造成外部碎片



示例：该地址空间内分为代码、堆、栈三段，然后映射到物理内存

![Segmentation](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/Segmentation.png)

* 假设要引用虚拟地址100（在代码段中），MMU将代码段基址加上偏移量（100）得到实际的地址100 + 32KB = 32868
* 假设要引用虚拟地址4200（在堆中），因为堆在虚拟地址4K开始，那么物理地址中的偏移量其实是4200 - 4K, 所以物理地址应该是 4200 - 4K + 34KB
* 硬件还需要知道段的增长方向，因为有些段，如栈就是反向增长的。（哪些段会往哪边增长，这可以通过增加标记位，也可以约定俗成）假设要引用虚拟地址15KB（在栈中），地址空间中的偏移是1KB，这意味着栈增长了1KB，而物理内存中栈基址是28KB，增长1KB（反向地）就是27KB。因此对应物理内存27KB
* 访问非法的地址就会报segmentation fault



示例：按如上的计算方式，我们需要知道段段基址，那自然就需要先知道段号，一般会在地址空间中分出高位表示段号。 假设地址空间为14位，前两位表示段号

```c
# 段号掩码，二进制11刚好过滤出前两位段号
#define SEG_MASK 0x3000

# 段内偏移所在的位数
#define SEG_SHIFT 12

# 段内偏移的掩码，二进制的0xFFF刚好过滤出后十二位的段内偏移
#define OFFSET_MASK 0xFFF

int Bound[]; # 段界限寄存器
int Base[]; # 段基址寄存器


//得到段号
SegmentNum = ( VirtualAddress & SEG_MASK ) >> SEG_SHIFT;

//得到段内偏移
Offset = VirtualAddress & OFFSET_MASK;

if( Offset >=  Bound[ SegmentNum ]  )
{
    RaiseException（ PROTECTION_FAULT ）；
}
else
{
  	//得到物理地址
    PhysicalAddr = Base[ Segment ] + Offset;
  	//访问该地址
    Register = AccessMemory( PhysicalAddr );
}
```



### 共享

可以增加几位保护位，来表示段的权限，比如可以将代码段标记为只读， 同样的代码就可以被多个进程共享

## Free Space Management

由于分段会把内存分为不同大小的单元（即不规则的**内存块**），造成外部碎片，因此需要空闲空间管理算法对内存进行管理

* 这里我们只讨论解决外部碎片（即分段）的空闲空间管理算法，假定算法管理的是一块块连续的字节区域（即内存块）
* 这里只考虑堆中的内存分配，即`malloc`，`free`操作

### 空闲列表

```c
typedef struct node_t
{
    int size;
    struct node_t *next;
}node_t;
```



空闲列表就是一个链表，每个节点都记录了一块没有被分配的空间，假设有下面的 30 字节的堆:

![free list heap](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list heap.png)

这个堆对应的空闲列表会有两个元素，一个描述第一个 10 字节的空闲区域(字节 0~9)， 一个描述另一个空闲区域(字节 20~29):

![free list 1](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list 1.png)

很明显，任何大于 10 字节的分配请求都会失败(返回 NULL)，因为 没有足够的连续可用空间。 如果是小于10B的请求，那么就从列表的某个节点（比如第二个）中分割一块内存



但是，对于这个(小)堆，如果应用程序调用 free(10)，归还堆中间的空间，空闲列表会变成：

![free list 2](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list 2.png)



尽管整个堆现在完全空闲，但它似乎被分割成了 3 个 10 字节的区域。这时， 如果用户请求 20 字节的空间，简单遍历空闲列表会找不到这样的空闲块，因此返回失败. 为此，空闲列表应该能自动**合并**：

![free list 3](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list 3.png)



### 头块

头块：

```c
typedef struct  header_t{
    int size;
    int magic;
}header_t;
```



`free(void* ptr)`函数没有指定块大小的参数，因为它假定，对于给定的指针，内存分配库可以确定要释放空间的大小，从而将其放回free list

* 一般这通过分配**头块**来实现。 每次分配内存块时，在其前面分配一个头块，保存额外信息，这样在（通过指针，也就是内存块起始位置）释放该内存块的时候，通过查询指针前面的头块，就知道了内存块的信息，比如大小，然后根据这些信息来释放内存块（头块也顺便被释放）

  * 当然，这意味着malloc/free时，分配/释放的的内存大小，是想要分配/释放给用户的内存大小 + 头块大小

  整体逻辑如下（假定内存从低位向高位分配，所以头块在内存块的前面）：

  ```c
  void free(void *ptr)
  {
      header_t *header_ptr = (void*)ptr - sizeof(header_t); // 根据分配给用户的内存指针，减去头块大小，获得头块的指针
  
      //读取头块的信息
      //...
  
      //释放头块和内存块
      //...
  }
  ```

  



### 头块 + 空闲列表的实现

假定要管理4KB的内存块，它是个堆，先初始化堆，加入空闲列表的头节点（free list的节点大小是8B）：

```c
node_t *head = mmap( NULL, 4096, PRPT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0 );
head -> size = 4096 - sizeof(node_t);
head -> next = NULL;
```

* 执行这段代码之后，free list的状态只有一个节点，记录的空闲大小为 4088（因为已经分配了一个free list的节点，占了8B）
* head 指针指向这块区域的起始地址， 假设**位于16KB**(尽管任何虚拟地址都可以)。堆看起来如图 17.3 所示
* 假设有一个 100 字节的内存请求。为了满足这个请求，库首先要找到一个足够大小的块。因为目前只有一个 4088 字节的块，所以选中这个块。然后，这个块被分割(split) 为两块:一块足够满足请求(以及头块，如前所述)，一块是剩余的空闲块。假设记录头块为 8 个字节(一个整数记录大小，一个整数记录幻数)，堆中的空间如图 17.4 所示

![free list implementation 1](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list implementation 1.png)



至此，对于 100 字节的请求，库从原有的一个空闲块中分配了 **108** 字节，返回指向它的一个指针(在上图中用 ptr 表示)，并在其之前连续的 8 字节中记录头块信息，供未来的 free()函数使用。同时将列表中的空闲节点缩小为 3980 字节(4088−108)。



之后的内存分配以此类推



如果用户程序通过 `free(ptr)`归还一些内存，那无非是让head指向`ptr - 8`,读取8字节的头块，得到要释放的内存信息，然后释放头块+紧跟的内存块：

![free list implementation 2](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/free list implementation 2.png)

* 这个堆堆起始地址是16KB
* 假设要`free(16500)`（ 即16384( 16KB ) + 前一块的108 ），也就是图上的`sptr`指针, 则令head指向sptr前的头块，得到sptr（开头的）内存块的信息，然后删除头块和sptr内存块

## Paging

分页将一个进程的地址空间分割成固定大小的单元，称为page, 并将物理内存也分割成相同的固定大小的单元，称为frame, 每个frame装一个page, 将page和frame编号

* 虚拟页号（ virtual page number, VPN ）， 因为地址空间都属于虚拟内存（虚拟空间），因此称为“虚拟”页号
* 物理帧号（ physical  ）：因为帧都处于物理内存（物理空间）中，因此称为“物理”帧号

**每个进程都有一个页表(page table)**, 页表就是页表项的列表。 每个页表项( page table entry, PTE )存储了一个page到 frame 的映射（即虚拟页号到物理页号到映射）

* 页表项的索引就等于VPN， 比如VPN为2， 那就对应着页表中下标为2的PFN



页表基址寄存器（ page table base register ）: 存储了页表的起始位置的物理地址，用于访问PTE：

```c
// 得到VPN
VPN = ( VirtualAddress & VPN_MASK ) >> SHIFT;

// VPN就是PTE的索引，得到PTE在页表中的偏移，加上页表的起始地址，就是该PTE的物理地址
PTEAddr = PageTableBaseRegister + (VPN + sizeof(PTE));
```







对于一个虚拟地址，它由两部分组成： VPN + 业内偏移。 只要查询页表，找到PTE（VPN就是PTE的下标），读取PTE，将VPN转换为PFN，再加上业内偏移，就得到了物理地址：

![virtual address to physical address](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/virtual address to physical address.png)



```c
offset = VirtualAddress & OFFSET_MASK PhysAddr = (PFN << SHIFT) | offset
// Extract the VPN from the virtual address
VPN = (VirtualAddress & VPN_MASK) >> SHIFT

// Form the address of the page-table entry (PTE)
PTEAddr = PTBR + (VPN * sizeof(PTE))

// Fetch the PTE
PTE = AccessMemory(PTEAddr)
  
// Check if process can access the page 
if (PTE.Valid == False)
	RaiseException(SEGMENTATION_FAULT)
else if (CanAccess(PTE.ProtectBits) == False)
    RaiseException(PROTECTION_FAULT)
else
	// Access is OK: form physical address and fetch it offset = VirtualAddress & OFFSET_MASK
	PhysAddr = (PTE.PFN << PFN_SHIFT) | offset
	Register = AccessMemory(PhysAddr)
```

### TLB

*Translation Look_aside Buffer*

可以把部分PTE存入TLB，对每次内存访问，先查看TLB，看是否有期望的转换映射，有的话（TLB hit）就直接得到了PFN，不需要查页表。 没有的话(.TLB miss )就继续**查页表，得到PTE，然后将该PTE写入TLB，再重试查TLB的指令**，这次会命中(hit)，得到PFN



TLB存放了PTE集合，PTE只对页表有效，页表只对所属的进程有效，因此TLB只对所属进程有效。 context switch时，要刷新TLB

* 刷新TLB会导致每次上下午切换后，都会有大量TLB miss， 为此，TLB实际上会存储多个进程（即多个页表）的PTE，并增加一个地址空间标识符字段（相当于PID），不同进程的PTE就用地址空间标识符来区分
* 除此之外，TLB项还有一些其他的控制位，比如有效位
  * TLB的有效位和页表的有效位不同，如果PTE无效，表面该页没有被进程申请使用，访问该页是非法的；而TLB项无效，仅仅表明该TLB项不是有效的地址映射



```c

VPN = (VirtualAddress & VPN_MASK) >> SHIFT 
(Success, TlbEntry) = TLB_Lookup(VPN)
if (Success == True) // TLB Hit
	if (CanAccess(TlbEntry.ProtectBits) == True) //查TLB控制位，看该TLB项是否有效
		Offset = VirtualAddress & OFFSET_MASK 
		PhysAddr = (TlbEntry.PFN << SHIFT) | Offset 		//得到物理地址
		AccessMemory(PhysAddr)
	else
 		RaiseException(PROTECTION_FAULT) 10 //该TLB项无效，进入异常处理程序，其实一般就是进入下一步的页表读取步骤
 	
// TLB Miss，进入常规的页表读取步骤
else
	PTEAddr = PTBR + (VPN * sizeof(PTE)) 
  PTE = AccessMemory(PTEAddr)
	if (PTE.Valid == False) 
	RaiseException(SEGMENTATION_FAULT)
	else if (CanAccess(PTE.ProtectBits) == False) 
		RaiseException(PROTECTION_FAULT)
	else
		TLB_Insert(VPN, PTE.PFN, PTE.ProtectBits) RetryInstruction()
```





### 段页式

段页式就是将分段和分页结合，给进程的每个逻辑段分配一个页表。 此时段基址寄存器指向的就不是段的物理基址，而是段对应的页表的物理基址



示例， 假设 32 位虚拟地址空间包含 4KB 页面，并且地址空间分为 4 个段。在这个例子中，我们只使用 3 个段:代码，堆，栈

用地址空间的前两位表示段号。假设 00 是未使用的段，01 是代 码段，10 是堆段，11 是栈段。因此，虚拟地址如下所示:

![segment plus page](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/segment plus page.png)

当进程正在运行时，每个段的基址寄存器都包含该段的线性页表的物理地址。因此，系统中的每个进程现在都有 3 个与其关联的页表。在上下文切换时，必须更改这些寄存器，以反映新运行进程的页表的位置。

在 TLB 未命中时(假设硬件管理的 TLB，即硬件负责处理 TLB 未命中)，硬件使用分段位(SN)来确定段号（也确定了要用哪个基址和界限寄存器对）。然后硬件将段基址寄存器中的物理地址（就是页表的物理地址）与 VPN 结合起来， 形成页表项(PTE)的地址:

```c
SN = (VirtualAddress & SEG_MASK) >> SN_SHIFT 
VPN = (VirtualAddress & VPN_MASK) >> VPN_SHIFT 
AddressOfPTE = Base[SN] + (VPN * sizeof(PTE))
```

### 多级页表

多级页表就是把页表本身也分页，每个页就是页表的sublist.对页表页，用页目录(.page directory )来管理，页目录的每一项就是页目录项（.page directory entry， PDE ）, 它存储了**虚拟页号 - 页帧号的**映射，以及对应页表页的有效位。 我们只讨论两级页表，更高级的页表可以以此类推

* 注意，这里“虚拟页号 - 页帧号映射“中的页帧号，指的是**页表页的所在的页帧号**。因为页表分页了，每一页自然就是物理内存中的物理帧，PDE就是将虚拟页号转换成页表页的物理帧号，根据虚拟页号来读取页表页。 因此，实际上**PDE是“VPN - 页表页”的映射**
* “有效位”是面向页表页的，而一个页表页“有效”，指的是该页表页（就是PTE的集合）中至少一个PTE有效。 反之，一个无效的页表页就是所有PTE都无效，该页表页会被分配PDE，但不会再
* 好处是，假设一个页表有100项，可以每10项一页，分10页， 其中有七页都无效（即70个PTE都为空），按照传统的页表，我依然要分配100项的空间，但是按照多级页表，只需要为三页（30项）分配空间

### 反向页表

传统页表是每个进程一个，而反向页表是整个系统一个。每个PTE带有所属进程的标识符。 要搜索反向页表，需要借助散列表等数据结构



## 虚拟内存

通过设置交换空间，可以将内存容量（在逻辑上）扩大，用户看到的不是实际内存大小，而是虚拟内存大小

### 交换空间

可以在磁盘上分配一块空间用于用于物理页的移入和移出，这称为swap space，当然我们会假设OS以页为单位对swap space读取/写入

示例，假设一个 4 页的物理内存和一个 8 页的交换空间。3 个进程(进程 0、进程 1 和进程 2)主动共享物理内存。但 3 个中的每一个， 都只有一部分有效页在内存中，剩下的在硬盘的交换空间中。第 4 个进程(进程 3)的所有页都被交换到硬盘上，很明显它目前没有运行。有一块交换空间是空闲的。可以看出，使用交换空间让系统假装内存比实际物理内存更大：

![swap space](/Users/lyk/Documents/HexoPics/OS Basic/OS Virtualization/swap space.png)

### page fault

页错误实际上不算错误，页错误意思是找到的页不在物理内存中，需要从磁盘中换出来，但这个访问本身对用户来说是合法的。 Anyway，页错误的处理流程是：

```c
PFN = FindFreePhysicalPage()
if (PFN == -1) // no free page found
	PFN = EvictPage() // os必须为将要换入的页找到一个物理帧，如果没有这样的物理帧，我们将踢出一些 物理页 
DiskRead(PTE.DiskAddr, pfn) // sleep (waiting for I/O)
PTE.present = True
PTE.PFN = PFN
RetryInstruction()

// update page table with present // bit and translation (PFN)
// retry instruction
```

### 内核虚拟内存空间

**内核虚拟空间是每个用户地址空间的一部分**



可以把一部分页表放在内核的虚拟内存中，不会随着context switch而刷新，这样就提升了速度，也减少了用户空间的内存压力

* 放在内核虚拟空间的页表不会被切换，这也意味着其寄存器（基址/界限寄存器）不会被刷新

## page scheduling

详见*OS Page Sheduling Algorithm*
