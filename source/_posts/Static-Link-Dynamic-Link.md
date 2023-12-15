---
categories:
- Software Engineering
date: 2022-05-05 01:18:34
tags: Linux
title: Static Link && Dynamic Link
---

Outline:

* static link
* static load
* dynamic link && load

<!--more-->

## Link & Load

静态库： `.a`

动态库( aka 共享对象 ): `.so`

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

  ```txt
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

  ```txt
  gdb a.out  
  ...
  (gdb) starti
  Starting program: /home/lyk/Documents/Hexo/LYK-love.github.io/source/_drafts/Test/a.out 
  
  Program stopped.
  0x0000000000401670 in _start () //可以看到，确实是0x401670
  
  ```

* 查看该进程的地址空间：

  ```txt
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



静态链接缺点：导致复用性降低，磁盘过多被占用

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
  * 把代码`mmap`到进程的地址空间
* ELF文件都有 `Global Offset Table`GOT， 即上述的“表”

  * Lazy Symbol Resolution: 不一次性加载GOT的所有符号

# Example

编写两个简单的程序（fred.c, bill.c），将其编译为目标文件，并分别生成静态库和动态库。再编写程序调用之，说明库的使用。

1. 生成静态链接库
   1. `gcc -c h.c -o h.o`
   2. `ar cqs libh.a h.o`：ar是生成库的命令，cqs是参数，libh.a是生成的静态链接库须以lib开头，h是库名，a表示是静态链接库，h.o是刚生成的目标文件
2. 生成动态链接库
   1. `gcc -c h.c -o h.o`
   2. `gcc -shared -WI -o libh.so h.o`：生成动态链接库使用gcc来完成，-shared -WI是参数，libh.so是刚生成的静态链接库，必须以lib开头，h是库名，so表示动态链接库，h.o是刚生成目标文件。
3. 将生成的libh.a，libh.so拷贝到/usr/lib或/lib下
4. 编译带静态链接库的程序
   1. `gcc -c test.c -o test.o`
   2. `gcc test.o -o test -WI -Bstatic -lh`:-WI -Bstatic表示链接静态库，-lh中-l表示链接，h是库名即/usr/lib下的libh.a
5. 编译带动态链接库的程序
   1. `gcc -c test.c -o test.o`
   2. `gcc test.o -o test -WI -Bdynamic -lh`:-WI -Bdynamic表示链接动态库，-lh中-l表示链接，h是库名即/usr/lib下的libh.so
6. 运行./test得到结果