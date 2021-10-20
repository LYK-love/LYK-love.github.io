---
title: OS 程序和进程
tags: jyyOS
categories: OS
date: 2021-10-18 18:25:53
---


程序 == 进程

<!--more-->

#   程序

* 程序就是可执行的二进制文件

  * Linux支持多种可执行文件格式

  * ELF( Executable Linkable Format)是其中最常用的

    * .o .out都是ELF

    ```shell
    vim a.c                                                                     
    gcc -c a.c  // 汇编并编译                                 
    file a.o                                                                   
    a.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped //可见.o是ELF
    gcc a.o  //链接                                
    file ./a.out                               
    ./a.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=e37d8d4cf587a2d3d1a245cbd8443a8fe4f0a453, for GNU/Linux 4.4.0, not stripped
    //可见.oou是ELF
    ```

## ELF文件

我们主要讨论ELF文件

查看当前所有进程：

`ps -ax  | less`

* linux的所有面临都是文件，`vim /bin/ls` ,可以看到其内容（二进制部分显示异常，但可以看到字符串常量， 命令的说明都是字符串常量）

* `xxd`可以看到文件以“7f 45 4c 46”（即 x7f ELF）开头

  i.e. `xxd /bin/ls | less  `

### 解析ELF文件

* `readelf`

  * `-h`：查看header（元数据）
  * `-l`：查看程序运行
  * 如果需要用代码解析，`/usr/include/elf.h 提供了定义 `

* 尝试写一段最小的不依赖标准库的代码

  ```C
  1 #include<stdio.h> //hello.c
    2 int main()
    3 {
    4     printf("Hello world!\n");                                                                                    
    5 }     
  ```

  * 如果`gcc -o hello.out hello.c`（编译并链接）， 再` ./hello.out`，能正常输出结果。

  * 如果

    `gcc -c hello.c` 后

    `ld hello.o  `,会报错：

    ```shell
    ld: warning: cannot find entry symbol _start; defaulting to 0000000000401000
    ld: hello.o: in function `main':
    hello.c:(.text+0xf): undefined reference to `puts'
    ```

    * 首先， `puts`函数是编译器优化的结果（我们没有用`puts`，用的是`printf`）
      * 编译器在`-o0`下依然会进行一些编译优化：

    * `_start`是linker默认的入口，入口可以用`-e`指定，如`ld -e main hello.o`，就不会有`——start`的报错

* 如果

  ```c
  #include<stdio.h>                                                                                              
   int main()
   {}
            
  ```

  `gcc -c hello.c  `

  `objdump -d hello.o`（查看二进制代码）

  `ld -e main hello.o `，没有报错，链接成功

  `file a.out`，得到`a.out: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, not stripped`，确实是ELF文件

  `./a.out  `，得到`segmentation fault`，还是报错。

  **因为标准库为我们做了很多工作！**

### gdb调试

* gdb调试

  * `r`: 运行

  * `starti`从第一条指令开始执行程序

  * `layout asm`更方便地查看汇编
  * `si`单步执行
  * `bt`（backtrace），查看调用栈
  * `info register`查看寄存器状态
  * `info inferiors`:显示所有进程
  * `!cat /proc/[pid]/maps`: 内存映射信息
  * `！ [instruction]`:执行shell命令

* `objdump -d a.out`： `0000000000401000 <main>:`，

  `readelf -a hello.out | less `： ` Entry point address:        0x401000`

  二者一致

* OS**加载程序，并初始化运行环境**，从`_start`开始运行

  `starti`: `0x00007ffff7fce090 in _start () from /lib64/ld-linux-x86-64.so.2`,这个库是OS的

  `info inferiors`:

  ```
   Num  Description       Connection           Executable        
  * 1    process 7669      1 (native)           /home//a.out 
  ```

  `!pmap 7669`:

  ```
  7669:   /home/a.out
  0000555555554000      4K r---- a.out
  0000555555555000      4K r-x-- a.out
  0000555555556000      4K r---- a.out
  0000555555557000      8K rw--- a.out   //加载好了a.out
  00007ffff7fc7000     16K r----   [ anon ]
  00007ffff7fcb000      8K r-x--   [ anon ]
  00007ffff7fcd000      4K r---- ld-2.33.so
  00007ffff7fce000    144K r-x-- ld-2.33.so
  00007ffff7ff2000     36K r---- ld-2.33.so
  00007ffff7ffb000     16K rw--- ld-2.33.so //加载好了ld-2.33.so
  00007ffffffde000    132K rw---   [ stack ]
  ffffffffff600000      4K --x--   [ anon ]
  
  ```

  OS先加载好了a.out，再加载ld-2.33.so，ld-2.33.so是OS提供的最初始的加载器，它会加载libc，再调用libc的初始化，再调用main

* main的开始/结束并不是程序的开始/结束！

  利用gcc的`__attribute__`:

  ```c
  1 #include<stdio.h> //a.c
    2 
    3 __attribute__((constructor))void hello(){
    4     printf("Hello,World!\n");                                                                                    
    5 }
    6 
    7 __attribute__((destructor))void goodbye(){
    8     printf("Bye,cruel OS World!\n");
    9 }
   10 
   11 int main(){}
                        
  ```

  `gcc a.c`

  `./a.out`

  得到：

  ```
  Hello,World!
  Bye,cruel OS World!
  ```

### strace

strace - trace system calls and signals

* `strace ./a.out`

* `strace` 在系统调用执行之前就能显示它

  ```
  write(1, "Hello,World!\n", 13Hello,World!)          = 13
  ```

   后面的“Hello,World!”是系统调用的结果

用`strace`查看之前的a.c

* `strace`输出到标准错误输出， 可以用`strace ./a.out > /dev/null `将标准输出丢弃（这样就不会看到系统调用`write`的结果）可以看到

  ```
  write(1, "Hello,World!\nBye,cruel OS World!"..., 33) = 33
  ```

   两个`write`合成了一个

  * `/dev/null`下的所有文件都会被丢弃

### gcc

```
.c --> (preprocess) ---> .i ---> (compile) ---> .s --->(assembly) ---> .o ---> (link) ---> .out
```

* `strace -f gcc a.c 2>&1 | grep execve  `查看`execve`系统调用

  ```
  //太长了
  ```

  gcc：

  1. 先调用`cc1`（编译器，c到汇编）

  2. 再调用`as`（汇编器，实际上gcc会检索多个as，找到可用的那个）

  3. 再调用`collect2`（收集构造函数和析构函数，并生成它们的调用函数; 然后负责链接）

  4. 再调用`ld`

  

### GUI

* GUI和普通程序没什么不同
  * 使用 `strace xedit \bin\ls`，鼠标不断移动，看系统调用栈的变化

