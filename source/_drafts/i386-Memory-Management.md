---
title: i386 Memory Management
tags:
---

[之前]()介绍了常见的内存虚拟化机制, 即分段, 分页和端页式三种方法. 现在我们来看看现实世界中的对内存虚拟化的实现. 我将以IA-32架构( 即x86架构 )为例, 介绍其内存虚拟化的实现. 

我们知道, 内存虚拟化的内容基本上是:

1. address translation
2. some memory protection features

# Address Translation

在启用了虚拟化技术之后, 地址被分为virtual address(VA) 和 physical address(PA). 对于分段式, VA就是分段地址; 对于分页式, VA就是分页地址. 由MMU做VA和PA的转换. 

然而i386采用段页式的虚拟化方式, 因此需要分段 -> 分页 -> 物理 两阶段转换:

1. Segment translation:  **logical address --> linear address**.
2. Page translation:  **linear address --> physical address**. 
   * 注意, 如果系统没有开启分页( 下图`PG?` ), 即只是分段式, 那么linear address就是physical address, 不需要Page translation.

![i386 Address Translation Overview](/Users/lyk/Library/Application Support/typora-user-images/image-20230228163709761.png)

可以看到, i386定义了三种地址:

1.  logical address: 48-bit. Included in the machine language instructions to specify the address of an operand or of an instruction.是由16-bit代码寄存器`CS`和32-bit指令指针寄存器`EIP`拼接得到的.
   * 因此, 在分段式视角下, 逻辑地址被看作由两部分组成:
     * segment selector: value stored in `CS`
     * segment offset: value stored in `EIP`
2.  linear address: 32-bit. 是逻辑地址到物理地址的中间层. 逻辑地址被Segment translation转化成线性地址. 
   * 如果系统没有开启分页机制, 那么linear address就是physical address; 如果系统开启了分页机制, 则线性地址需要再Page translation为物理地址.
   * Linear addresses are usually represented in hexadecimal notation: from `0x00000000` to `0xffffffff`.
3.  physical address: 32-bit. 内存中的地址, CPU通过总线, 使用physical address来对内存进行寻址.
    * [我们知道](https://lyk-love.cn/2022/08/06/Computer-I:O-Device/?highlight=%E5%9C%B0%E5%9D%80%E7%A9%BA%E9%97%B4), OS通过controller处理外部设备, controller只和Device Register交互. 为此, 要么在physical address中分配一部分地址空间给外设; 要么使用额外的指令来对外设进行寻址. 一般选择第一种方法, 因此, 物理内存对地址空间不一定是连续的, 部分地址空间可能被分配给了外设.



* NOTE: 在内存虚拟化中我们将物理地址映射成虚拟地址. 本文的“逻辑地址”, “线性地址”都是Intel的规定, 是一个具体实现; 而“虚拟地址”是一个抽象的说法, 它们不是一个维度的概念. 如果非要把它们对应的话, 由于虚拟地址在实现中是通过将物理地址空间**分页** ( 而不分段 )而得到的, 因此**在只分页, 不分段( 或者效果等同于不分段 ) 的系统中, 虚拟地址就是线性地址**. 

  * 后文的Flat Archetecture会讲到, Flat Archetecture的效果等同于不开启分段, 而Linux就采用Flat Archetecture. 因此**在Linux中, 虚拟地址就是线性地址**

    

# Segment Translation

内存虚拟化只有那么些思想, 因此实现五花八门, 底层都是相通的.

## Logical Address -> Linear Address

逻辑地址转化为线性地址的步骤如下:

1. 在分段视角下, 48位的逻辑地址包含:
   1. 16位的段选择符( 位于16-bit 段寄存器 )
   2. 32位的段内偏移量( 位于32-bit eip ) 
2. MMU首先通过段选择符的INDEX字段得到段描述符在段描述符表中的**索引**, 再通过GDTR/LDTR得到段描述符表的**基址**, 从段描述符表中找到对应的**段描述符**.
3. 从段描述符中取出32位的**基址**(`BASE`), 与逻辑地址中32位的**段内偏移量**(`OFFSET`)相加, 就得到32位**线性地址**.





![Segment Translation](/Users/lyk/Library/Application Support/typora-user-images/image-20230228170731554.png)

##  Descriptors

段描述符( segment descriptor )之于分段, 就相当于页表项( PTE )之于分页. 也就是说, 段描述符存储了逻辑地址到线性地址的映射.

* Descriptors are created by compilers, linkers, loaders, or the operating system, not by applications programmers.



下图描述了两种常见的段描述符结构, 段描述符大小为8-byte. (因为一行画不下, 就画了两行, 每行32bit)

![General Segment-Descriptor Format](/Users/lyk/Library/Application Support/typora-user-images/image-20230301153716892.png)

下面介绍各个字段, 其中最重要的是`BASE`, `LIMIT`和`Granularity bit`.

* BASE: 32-bit, 段的基地址. 
  * 从图上可以看到, 段描述符的BASE字段不是连续的.CPU需要把三个BASE字段concatenate起来形成完整的BASE字段( 8 + 8  + 16 bit)
    * 这么设计好蠢啊, 不知道原因是什么?
  * 因为BASE是32-bit, 它对应的地址空间就是4GB

* LIMIT: 20-bit, 段限界, 即段的大小. 
  * 和BASE一样, CPU需要把2个LIMIT字段concatenate起来形成完整的LIMIT字段( 4 + 16 bit)
  * 段的大小 = LIMIT字段的值 * 数据单元大小. 后者根据granularity bit定义.
  
* G(*Granularity*): 1-bit, 定义了LIMIT字段使用的数据单元的大小.
  * `0`: 以字节为基本单元. 因此段大小的上限为 $1$B * $2^{20}$  = $1$ MB.
  * `1`: 以4KB( 事实上, 这是分页模式下的页的大小 )为基本单元.  因此段大小的上限为 $4$KB * $2^{20}$ = $4$ GB.
  
* TYPE: Distinguishes between various kinds of descriptors.

* DPL(Descriptor Privilege Level): Used by the protection mechanism (refer to Chapter 6).

* Segment-Present bit: If this bit is zero, the descriptor is not valid for use in address transformation; the processor will signal an exception when a selector for the descriptor is loaded into a segment register. Figure 5-4 shows the format of a descriptor when the present-bit is zero. The operating system is free to use the locations marked AVAILABLE. Operating systems that implement segment-based virtual memory clear the present bit in either of these cases:
  * When the linear space spanned by the segment is not mapped by the paging mechanism.
  * When the segment is not present in memory.
  
* A: ACCESSED
  
* AVL: May be used by the operating system, but it is ignored by Linux.
  
* DPL(*Descriptor Privilege Level*): used to restrict accesses to the segment. It represents **the minimal CPU privilege level requested for accessing the segment.** Therefore, a segment with its DPL set to 0 is accessible only when the CPL is 0—that is, in Kernel Mode. While a segment with its DPL set to 3 is accessible with every CPL value.
  
* P(*Segment-Present flag*): 有效位

  * `0`: 该段不在内存中
  * `1`: 该段在内存中. Linux always sets this flag (bit 47) to 1, because it never swaps out whole segments to disk.

  ​           



MMU在计算线性地址的过程中，可以根据段限界和段的存取权限(也称访问权限)判断是否地址越界或 访问越权(访问越权是指对指定单元所进行的操作类型不符合存取权限，例如，对存取权限为“只读”的 页面进行了写操作)，以实现存储保护。



## Descriptor Tables

段描述符表(Descriptor Tables)之于分段, 正如页表之于分页. 

Descriptor Table有两种:

* The global descriptor table (GDT)
* A local descriptor table (LDT)

#### Structure

段描述符表就是段描述符(8-byte)的数组, 它的长度是可变的, 最大含有$8192 \ (2^{13})$个元素 ( 因此[Selector](#Selectors)的INDEX长度为13bit).

* GDT的第一个元素(INDEX=0)是不被CPU使用的.



![Descriptor Tables](/Users/lyk/Library/Application Support/typora-user-images/image-20230228174056096.png)



#### GDTR & LDTR

CPU从段选择符的`INDEX`字段得到段描述符的索引, 就可以从段描述符表中得到对应的段描述符. 但是, 在此之前, CPU需要知道段描述符表的地址.



CPU通过GDTR和LDTR寄存器分别得到GDT和LDT的地址.

* These registers **store the base addresses of the tables** in the linear address space and store the segment limits.
* The instructions `LGDT` and `SGDT` give access to the GDTR; the instructions `LLDT` and `SLDT` give access to the LDTR.



## Selectors

The selector portion of a logical address identifies a descriptor by specifying a descriptor table and indexing a descriptor within that table.

![Format of a Selector](/Users/lyk/Library/Application Support/typora-user-images/image-20230228173203378.png)

* Index: Selects one of 8192 descriptors in a descriptor table. The processor simply multiplies this index value by 8 (the length of a descriptor), and adds the result to the base address of the descriptor table in order to access the appropriate segment descriptor in the table.

* Table Indicator: Specifies to which descriptor table the selector refers. **A zero indicates the GDT; a one indicates the current LDT.**

* Requested Privilege Level: Used by the protection mechanism. (Refer to Chapter 6.)



* Because the first entry of the GDT is not used by the processor, a selector that has an index of zero and a table indicator of zero (i.e., a selector that points to the first entry of the GDT), can be used as a null selector. The processor does not cause an exception when a segment register (other than CS or SS) is loaded with a null selector. It will, however, cause an exception when the segment register is used to access memory. This feature is useful for initializing unused segment registers so as to trap accidental references.

## Segment Registers

![Segment Registers](/Users/lyk/Library/Application Support/typora-user-images/image-20230228211231582.png)

之前介绍过6个段寄存器: CS, SS, DS, ES, FS, GS. 它们都只有16-bit. 但是, 硬件的细节是不一定要全部暴露给软件的. 

- cs: code segment register, which points to a segment containing program instructions
  - It includes 2-bit field for CPU's [Current Privilege Level](https://en.wikipedia.org/wiki/Privilege_level) (CPL), Linux uses only levels 0 and 3 for Kernel Mode and User Mode
- `ss`: stack segment register, which points to a segment containing the current program stack
- `ds`: data segment register, which points to a segment containing global and static data
- `es`, `fs`, and `gs`: general purpose registers, which may refer to arbitrary data



段寄存器只有16-bit, 存放一个Selector( 即上图的"VISIBLE SELECTOR"). 但是, 由于程序的局部性, 大多数指令都会重复地访问某些段, 为此可以把descriptor也缓存在段寄存器, CPU就不需要每次都重新根据selector计算descriptor了.

因此, 80×86 processor对于每个段寄存器, 都增加了一个额外的nonprogrammable register, 后者大小为8B, 对用户不可见,



因此, 当一个segment selector被load到段寄存器时, CPU会自动地根据它(`INDEX`, `TYPE` 等信息)从段描述符表中取得segment descriptor, 然后把它存在对应的nonprogrammable register.





# Page Translation

i386的分页机制采用两级页表

![image-20230302124948478](/Users/lyk/Library/Application Support/typora-user-images/image-20230302124948478.png)









## Page Frame

Linear Address:

* 31-22 bit: DIR
* 21-12 bit: PAGE
* 11-0 bit: OFFSET

整体来看, 前20 bits是VPN, 后12bits是页内偏移. 

* 由于采用两级页表, $2^{10}$个页表作为二级页表的PTE. $2^{10}$个二级页表作为一级页表( 称作页目录, page directory )的页表项, 在这里也可以称为页目录项( page directory entry, PDE )
* `DIR`: PD中的PDE的索引
* `PAGE`: PT中的PTE的索引



寻址步骤为:

1. 先提取出DIR, 从PD中找到PDE, 即二级页表

2. 提取出`PAGE`, 从二级页表中找到PTE

3. 得到PTE中的PFN

4. 提取出`OFFSET`

5. PA = `OFFSET` + PFN

   

VPN的前10bits是二级页表

page directory

![image-20230302124924616](/Users/lyk/Library/Application Support/typora-user-images/image-20230302124924616.png)

## Linear Address

## Page Tables

## Page-Table Entries

### Page Frame Address

### Present Bit

### Accessed and Dirty Bits

### Read/Write and User/Supervisor Bits

## Page Translation Cache

# Combining Segment and Page Translation

![80306 Addressing Machanism](/Users/lyk/Library/Application Support/typora-user-images/image-20230301151816796.png)



## "Flat" Architecture

When the 80386 is used to execute software designed for architectures that don't have segments, it may be expedient to effectively "turn off" the segmentation features of the 80386. The 80386 does not have a mode that disables segmentation, but the same effect can be achieved by initially loading the segment registers with selectors for descriptors that **encompass the entire 32-bit linear address space**. Once loaded, **the segment registers don't need to be changed**. The 32-bit offsets used by 80386 instructions are adequate to address the entire linear-address space.

在80386采用的段页式模型中, 我们无法“关闭”分段机制. 但是, 可以通过一些设置, 使得模型达到和关闭分段一样的效果. 

我们令所有的段都映射到相同的32-bit线性地址空间( That is, they start at 0 and end at the end of memory) , 则所有的descriptor的`BASE=0x00000000`, `LIMIT=0xFFFFF`, 即整个内存只有一个段.

在Flat Architecture下, 可以有不同的selector和不同的descriptor, 但不同的descriptor选中的都是同一个段(`BASE=0x00000000`, `LIMIT=0xFFFFF`)





(

????

因此只要段寄存器加载了某个selector( 如之前提到的, unprogrammable register也会加载对应的descriptor), 则在程序运行期间, 段寄存器的内容不需要改变, 因为只有整个内存只有一个段, 

不可能有新的descriptor和selector.)



我们之前提到, 逻辑地址 = `[CS:EIP]` (or `[selector: base]`). CPU通过selector找到descriptor的`offset`, 将其与`base`相加, 得到线性地址:

* 线性地址 = `base` + `offset`

然而, 由于Flat Architecture下, offset永远为0, 因此**线性地址其实就是`base`, 也就是`EIP`.** 

当然我们也可以查看CS, 把CS和线性地址拼起来, 就是逻辑地址.



## Segments Spanning Several Pages

## Pages Spanning Several Segments

On the other hand, segments may be smaller than the size of a page. For example, consider a small data structure such as a semaphore. Because of the protection and sharing provided by segments (refer to Chapter 6), it may be useful to create a separate segment for each semaphore. But, because a system may need many semaphores, it is not efficient to allocate a page for each. Therefore, it may be useful to cluster many related segments within a page.

## Non-Aligned Page and Segment Boundaries

80386架构不强制要求段和页的边界的对应. 也就是说一个页可能包括一个段的结尾和另一个段的开头; 一个段可以包括一个页的结尾和另一个页的开头.

The architecture of the  permits segments to be 

## Aligned Page and Segment Boundaries

Memory-management software may be simpler, however, if it enforces some correspondence between page and segment boundaries. For example, if segments are allocated only in units of one page, the logic for segment and page allocation can be combined. There is no need for logic to account for partially used pages.

## Page-Table per Segment

An approach to space management that provides even further simplification
 of space-management software is to maintain a one-to-one correspondence between segment descriptors and page-directory entries, as Figure 5-13 illustrates. Each descriptor has a base address in which the low-order 22 bits are zero; in other words, the base address is mapped by the first entry of a page table. A segment may have any limit from 1 to 4 megabytes. Depending on the limit, the segment is contained in from 1 to 1K page frames. A task is thus limited to 1K segments (a sufficient number for many applications), each containing up to 4 Mbytes. The descriptor, the corresponding page-directory entry, and the corresponding page table can be allocated and deallocated simultaneously.

# Linux Implementation

**Linux就采用Flat Architecture. 事实上, 64-bit Linux只支持Flat Architecture, 不支持其它的分段策略.** 



Linux操作系统为了使它能够移植到绝大多数流行的处理器平台，就是把所有段基址设为全0的、 段限长设为**全1**





x86_64架构下Linux中每个应用程序(进程)可见的线性地址空间如下(注：分段机制在64位模式下已不产生实际作用)：

该架构支持48位线性地址(高16位仅做符号扩展，不参与地址转换)到40位物理地址(最多52位，由CPU实现决定)的映射。48位线性空间共256T，分为两个128T区间，分别分布在完整的64位空间的两端。





其中，低128T为用户空间，映射用户程序代码、数据、堆栈和共享库，物理内存随着程序的运行由内核动态分配。而高128T则为内核空间：direct mapping区映射整个物理内存空间，便于内核访问所有物理内存；vmalloc space区间为内核调用vmalloc时使用的线性空间，物理内存动态分配且物理上不保证连续；virtual memory map是内核标识内存页信息的数组，供内存管理功能使用；kernel text & module区存放内核和模块的代码及数据。此外，也可以参考内核代码的说明：

```
linux/Documentation/x86/x86_64/mm.txt:

0000000000000000 - 00007fffffffffff (=47 bits) user space, different per mm
hole caused by [48:63] sign extension
ffff800000000000 - ffff80ffffffffff (=40 bits) guard hole
ffff880000000000 - ffffc7ffffffffff (=64 TB) direct mapping of all phys. memory
ffffc80000000000 - ffffc8ffffffffff (=40 bits) hole
ffffc90000000000 - ffffe8ffffffffff (=45 bits) vmalloc/ioremap space
ffffe90000000000 - ffffe9ffffffffff (=40 bits) hole
ffffea0000000000 - ffffeaffffffffff (=40 bits) virtual memory map (1TB)
... unused hole ...
ffffff0000000000 - ffffff7fffffffff (=39 bits) %esp fixup stacks
... unused hole ...
ffffffff80000000 - ffffffffa0000000 (=512 MB)  kernel text mapping, from phys 0
ffffffffa0000000 - ffffffffff5fffff (=1525 MB) module mapping space
ffffffffff600000 - ffffffffffdfffff (=8 MB) vsyscalls
ffffffffffe00000 - ffffffffffffffff (=2 MB) unused hole
```





# Real Mode

Real-address mode (often called just "real mode") is the mode of the processor immediately after RESET. 

In real mode the 80386 appears to programmers as a fast 8086 with some new instructions. Most applications of the 80386 will use real mode for initialization only.



实模式既没有分段, 也没有分页(



在实模式下, 逻辑地址应该是32-bit. 但为了与保护模式兼容, 实模式的**逻辑地址**被设计为48-bit:

1. 高16-bit: BASE
2. 低32-bit: OFFSET
   * 高16-bit: 补零, 用于把地址扩大到48-bit.
   * 低16-bit: effective offset, 真正的offset.



实模式下的线性地址是32-bit, 由于实模式没有分页, 因此**实模式下的线性地址就是物理地址.** 

## Address Translation

实模式下的48-bit物理地址转化为32-bit线性地址的过程为:

![Real-Address Mode Address Formation](/Users/lyk/Library/Application Support/typora-user-images/image-20230302113258595.png)

如图, 逻辑地址 = `[BASE:OFFSET]`, 将16-bit `BASE`

和16-bit `EFFECTIVE OFFSET `都扩展到20-bit.  `BASE`的低位补4个`0`; `EFFECTIVE OFFSET `的高位补4个`0`, 二者相加, 就得到20-bit的线性地址. 

* 注意到, 两个20-bit相加可能产生向第20位的进位. 在8086中, 该进位是被截断的. 在80386中, 该进位会被存在线性地址的第20位( 也就是说线性地址会有21-bit, 最高位存储这个carry ).

将32-bit线性地址的高位补12个`0`, 就得到了32-bit的线性地址.





# Ref 

* [i386 manual](https://github.com/NJU-ProjectN/i386-manual), or there is a copy of the HTML version of the manual found in [6.858 in MIT](https://css.csail.mit.edu/6.858/2014/readings/i386/toc.htm). 
  * Chapter 5  Memory Management
* https://notes.shichao.io/utlk/ch2/
* https://rootw.github.io/2017/08/%E5%9C%B0%E5%9D%80%E6%98%A0%E5%B0%84/

*325462*

# Implementation

采取Linux的Flat Mode



## Translate logic address to linear address in Real Mode

Translate logic address to linear address in Real Mode

```java
    /**
     * Translate logic address to linear address in Real Mode.
     * @param logicAddr 48-bit = 16-bit segment_selector + 32-bit offset
     * 32-bit offset:
     *  * higher 16 bits: '0'
     *  * lower 6 bits: effective_offset
     *
     * MMU need to:
     *  1. (16-bits段寄存器左移4位 + offset的低16-bits) = 20-bit linear address
     *  2. 将20-bit 线性地址高位补0到32-bit
     *
     * @return 32-bits Linear Address in Real Mode.
     *  In real mode, the effective linear address is just 20-bit, and we need to extend it to 32-bit ( for compatibility with protection mode )
     *  by adding 12 higher order '0'.
     *
     */
    private String _toRealLinearAddr(String logicAddr) {
        String base = logicAddr.substring(0,16);
        String effective_offset = logicAddr.substring(32,48);

        //imple digits
        String ZERO_4 = "0000"; //4-bit '0', used to extend 16-bit base and effective_offset to 20-bit.
        String ZERO_12 = "000000000000"; //12-bit `0`, used to extend 20-bit address to 32-bit( for ALU process)

        String base32 = ZERO_12 + base + ZERO_4;
        String effective_offset_32 = ZERO_12 + ZERO_4 + effective_offset;

        //wrap them to be processed by ALU
        DataType src1 = new DataType(base32);
        DataType src2 = new DataType(effective_offset_32);


        String sum_32 = new ALU().add(src1, src2).toString();

        //我们采取8086的做法， 第20位的进位被截断， 因此有效线性地址只有20位
        String effective_linear_address = sum_32.substring(12);

        //extend 20-bit effective_linear_address to 32-bit linear address
        String linear_address = ZERO_12 + effective_linear_address;

        assert linear_address.equals(toRealLinearAddr(logicAddr));

        return linear_address;
    }
```

## Translate logic address to linear address in Segmentation Mode

```java
    /**
     * Translate logic address to linear address in Segmentation Mode
     * @param logicAddr 48-bit = 16-bit selector + 32-bit offset
     *
     * 16-bit selector = 13-bit descriptor index + 3-bit control bits
     *
     * MMU need to:
     * 1. extract the 13-bit descriptor index
     * 2. get the base address of descriptor table( aka DT, usually GDT) according to descriptor table register( aka DTR, usually DTR or DTR). This step is not implemented here for simplicity.
     * 3. get the descriptor from DT in the memory according to the index.
     * 4. Then we extract the 32-bit BASE field from the descriptor.
     * 5. extract the 32-bit OFFSET field from the logic address.
     * 6. add BASE and OFFSET, the result is the 32-bit linear address
     * @return 32-bits 线性地址
     */
    private String _toSegLinearAddr(String logicAddr) {
        int segDesIndex = getSegIndex(logicAddr);//段描述符索引 or 选择段表项
        String base = String.valueOf(Memory.getMemory().getBaseOfSegDes(segDesIndex));
        String offset = logicAddr.substring(16, 48);

        String linear_address = new ALU().add(new DataType(base), new DataType(offset)).toString();
        assert linear_address.equals(toSegLinearAddr(logicAddr));
        return linear_address;
    }
```

## Translate linear address to physical address in Page Mode

```java
   /**
     * Translate linear address to physical address in Page Mode
     * 段页式下的线性地址转物理地址. 高20位是VPN, 低12位是offset
     * @Official
     * @param linearAddr 32位
     * @return 32-bits 物理地址
     */
    private String _toPagePhysicalAddr(String linearAddr) {
        String VPN = linearAddr.substring(0,20);
        String offset = linearAddr.substring(20,32);
        String PFN;
        int VPN_int  = Integer.parseInt(Transformer.binaryToInt("0"+VPN));

        //get PFN from VPN
        //这里简化了页表结构， 只采用了一级页表
        if(TLB.isAvailable)
        {
            //如果采用了TLB，则查TLB
            int TLB_line_idx = TLB.getTLB().read(VPN_int);

            //由于Address Translation已经把要读取的所有页都加载到页表和TLB了， 因此这里的TLB不可能miss
            if( TLB_line_idx == -1)
            {
                //TLB miss, 到内存中查页表
                System.out.println("这句话不可能被打印， 之前Address Translation已经确保TLB hit了");
                PFN = get_PFN_bits_from_memory(VPN_int);
            }
            else
            {   //TLB hit
                //其实也可以直接根据TLB_line_idx， 反而更快， 但是TLB line的getter是私有的...
                PFN = String.valueOf(TLB.getTLB().get_PFN_from_VPN(VPN_int));
            }

        }
        else
        {
            //到内存中查页表
            PFN = get_PFN_bits_from_memory(VPN_int);

        }
        String physical_address = PFN + offset;

        assert physical_address.equals(toPagePhysicalAddr(linearAddr));
        return physical_address;

    }

```



## Real load

```java
    /**
     * Nn real mode, load data from disk to memory 
     *
     * @param pAddr In real mode, linear address = physical address
     * @param len   segment size
     */
    public void real_load(String pAddr, int len) {
        write(pAddr,len,disk.read(pAddr,len));//直接向memory写disk的数据
    }
```



## Seg load

```java
    /**
     * 加载段数据并填写GDT.
     * 加载段数据这一步只在分段式下进行. 在段页式下不用从磁盘中加载数据.
     * @param segIndex 段索引
     */
    public void _seg_load(int segIndex) {
        SegDescriptor segDes = getSegDescriptor(segIndex);
        boolean new_granularity;

        if(Memory.PAGE)
        {
            //段页式. 开启分页之后, 一个段是4GB, 加载段的代价很大. 因此加载数据的任务交给page_load来完成,
            // seg_load跳过加载数据这一步, 它的作用在开启分页之后仅仅是填写GDT，
            new_granularity = true;
        }
        else
        {
            //段式, 基本单位为1B, 由于LIMIT为20-bit, 因此一个段的最大值为1B * 2^{20} = 1MB. 在这里遵循Linux的做法, base永远是0,  LIMIT永远是全1, 即的大小永远是最大值1MB.
            //事实上这样做之后内存中也只有一个段. 不同的descriptor选则的段是同一个, BASE=0,  LIMIT= 全1

            //使用段基址作为访问磁盘的地址，用段限长(即段大小)作为读取的长度
            //由于base永远是0, LIMIT永远是全1, 因此base = 0, len = 1024 * 1024
            String base = String.valueOf(segDes.base);
            byte[] data_from_disk = Disk.getDisk().read(base, 1024 * 1024 );

            //从磁盘加载的数据默认放在内存的物理地址0
            write("00000000000000000000000000000000", 1024*1024, data_from_disk );
            new_granularity = false;

        }

        //除了加载数据，还需要填好全局描述符表GDT. 我们采取Flat Mode， 每个由MMU装载进入GDT的段， 其段基址均为全0，其限长均为全1，未开启分页时粒度为false，开启分页后粒度为true
        //当然, 测试中也会出现base和limit不等于上述值的情况
        segDes.validBit = true;
        segDes.granularity = new_granularity;
        segDes.base = "00000000000000000000000000000000".toCharArray();// 32-bit '0'
        segDes.limit = "11111111111111111111".toCharArray();// 20-bit '1'
    }
```



## Page load

```java
      /**
         * 更新页. 不考虑16MB内存用满的情况.
         * 本程序中没有分页式, 只有段页式
         * 如果有TLB. 则还会更新TLB
         *
         * 采用Linux架构, linear address = 20-bit VPN + 12-bit offset
         * @Official
         * @param VPN 虚拟页号
         *
         */
    public void _page_load(int VPN) {

        //使用VPN对应的FRAME(在内存中不存在)的起始物理地址(即offset全0) 作为访问磁盘的起始地址,
        //用页大小(2^{12} bit = 4 * 1024 bit )作为读取的长度
        //则physical_address_start = 20-bit VPN + 12-bit '0'
        //对于十进制的VPN, 左移12bit相当于乘2^{12} = 4 * 1024
        //因此对于十进制的VPN, 对应的Frame的起始地址就是VPN * 4 * 1024.
        int len = 4 * 1024;

        String physical_address_start = Transformer.intToBinary(String.valueOf(VPN * len));
        byte[] data_from_disk = disk.read(physical_address_start, len);

        //在页表中寻找一个空闲的Frame, 即寻找valid=false的Frame, 将数据写入Frame
        //如果仅有页表的存在，我们就需要遍历整个页表来找出空闲的物理页框号，这个过程比较复杂。而且，在现代操作系统中，每个进程都对应着一张页表，
        // 而系统中往往运行着非常多的进程，把每个进程的页表都遍历一遍显然不太现实。
        //因此，一些计算机系统采用了反向页表来来解决这个问题。为了降低实验难度，我们不模拟反向页表，
        //而是简单地使用了一个有效位数组:
        int updated_PFN;

        for(int i =0;;i++)
        {
            if(!pageValid[i])
            {
                updated_PFN = i;
                pageValid[updated_PFN] = true;
                break;
            }
        }

        //将数据写入该Frame.
        //同理, 对于十进制的PFN, 对应的Frame的起始地址就是PFN * 4 * 1024.
        String physical_address_start_frame = Transformer.intToBinary(String.valueOf(updated_PFN * len));
        write(physical_address_start_frame, len, data_from_disk);

        //二进制PFN
        String PFN_bits = physical_address_start_frame.substring(0,20);

        //update Page Table
        PageItem updated_PTE = new PageItem();
        updated_PTE.pageFrameNumber = PFN_bits.toCharArray();
        updated_PTE.isInMem = true;
        pageTbl[VPN] = updated_PTE;

        //update TLB
        if(TLB.isAvailable)
        {
            TLB.getTLB().set(VPN, PFN_bits.toCharArray());
        }
    }
```



##

# TODO

IO地址分陪

DT

