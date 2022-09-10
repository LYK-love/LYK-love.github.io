---
title: Popular Compilers
tags: Compilers
categories: Toolkit
date: 2022-05-05 03:41:07
---




Outline:

* GCC
* Clang/LLVM
* MinGw
* Crgwin
* MSVC

<!--more-->



# GCC

[Official](https://gcc.gnu.org/)

* GCC： GNU Compiler Collection，是GNU开发的编译器， 用于Unix && Unix like的OS
  * 原名为GNU C Compiler，因为它原本只能处理C. 经过发展，现在的GCC已经可以处理如下语言: 
    * [C](https://gcc.gnu.org/c99status.html),
    * [C++](https://gcc.gnu.org/projects/cxx-status.html),
    * Objective-C
    * [Fortran](https://gcc.gnu.org/fortran/)
    * Ada
    * Go
    * D
  * GCC是Linux和BSD家族的OS的标准编译器。 OSX用的是apple clang
    * 一般来讲，符号链接`cc`指向了平台的默认编译器. Linux上`cc`指向gcc, OSX上指向的是clang
  * gcc配套的调试工具是gdb, 使用的链接器是`ld`, 一般用`make`构建
  * gcc生成的代码**不跨平台**





## Command Options

[官网 GCC Command Options](https://web.mit.edu/rhel-doc/3/rhel-gcc-en-3/invoking-gcc.html#:~:text=GCC%20Command%20Options%20When%20you%20invoke%20GCC%2C%20it,consists%20of%20object%20files%20output%20by%20the%20assembler.)

### Overall Options

```
gcc [option] [file]
```

* 注意，`[option]`和`[file]`中间可以不加空格，比如可以`gcc -l[library]`
* `gcc xx.c`默认会把文件输出到当前目录下的`a.out`
* `gcc`编译cpp文件时只会默认链接C标准库，不默认链接CPP标准库. 因此编译CPP文件需要加选项`-lstdc++`, 要么就使用`g++`编译
* 编译完之后，用其他的机器调试可能是不行的，因为file的路径一般是不一样的。



| option           | Description                            |
| ---------------- | -------------------------------------- |
| `-c`             | 只汇编不链接，生成可重定向目标文件`.o` |
| `-S`             | 只编译不汇编，生成汇编代码`.s`         |
| `-E`             | 只预处理不编译，生成预处理后文件`.i`   |
| `-o [file]`      | 将编译后文件输出到[file]               |
| `-v`             | 打印编译器内部各编译过程的命令行信息   |
| `-DMACRO[=DEFN]` | 定义MACRO宏(针对#define)               |
| `--help`         |                                        |
| `--version`      |                                        |



### Options for Debugging

| option     | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| `-g`       | 在每一个编译完的二进制码上打上文件名和行号的标签，供gdb使用  |
| `-O/On[n]` | 在程序编译、链接过程中进行优化处理. 0 级不优化,默认是2级. 优化和调试不兼容，所以不要同时使用-g 和-O 选项 |
| `-D`       | 在预处理时添加#define指令, 比如`-DAA=2`相当于在添加了`#define AA 2` |

* 编译优化：
  1. 对于不同版本的gcc，`n`的取值范围及其对应的优化效果可能并不完全相同，比较典型的范围是0-2或0-3.
  2. 不同的优化级别对应不同的优化处理工作。例如：优化选项“-O1”主要进行线程跳转和延迟退栈两种优化；优化选项“-O2”除了完成所有的“-O1”级别的优化之外，还要进行一些额外的调整工作，例如处理器指令调度等；优化选项“-O3”则还包括循环开展和其他一些与处理器特性相关的优化工作。
* 源代码的语句编译成的汇编码可能是多条语句，是一对多的关系
* 调试器：在执行编译后的二进制码，二进制码会被打标签，记录哪一个源代码的哪一行编译而来的。
* 调试的时候仍然使用的是本地编译好的二进制文件

### Options for Directory Search

| option          | Description                                                  |
| --------------- | ------------------------------------------------------------ |
| `-Idir`         | 在**头文件**的搜索路径列表中添加dir目录, 其优先级比系统头文件目录高. 如果有多个 `-I` 选项，按从左到右的顺序搜索，最后才是系统头文件目录 |
| `-iquotedir`    | 和`-I dir`相同，但只对用引号括起来的头文件有效，如`#include "file";` |
| `--sysroot dir` | 用 `dir` 作为头文件和库的根目录, 例如, 如果编译器正常情况下在`/usr/include` 找头文件，在 `/usr/lib` 中找库文件, 开启该选项之后，更改为`dir/usr/include and dir/usr/lib` |
| `-Ldir`         | 在**库文件**的搜索路径列表中添加dir目录                      |
|                 |                                                              |

### Options for Linking


| option         | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| `-static`      | 只链接静态库                                                 |
| `-shared`      | 这是默认选项. 链接静态和动态库, 动态库优先                   |
| `-l [library]` | 链接名为[library]的库文件. `-l`和`[library]`之间可以没有空格. 比如`-lm`就链接了名为`libm.a`的库文件 |
|                |                                                              |

### Options for Warning

| option    | Description                                                  |
| --------- | ------------------------------------------------------------ |
| `-Wall`   | 会在标准输出上打印warning信息                                |
| `-w`      | 关闭所有warning                                              |
| `-werror` | 把所有的warning信息转换为错误信息，并在warning发生时终止编译过程 |



### Options for Archtecture

| option                 | Description                                                  |
| ---------------------- | ------------------------------------------------------------ |
| -mieee-fp/-mno-ieee-fp | 使用/不使用IEEE标准进行浮点数的比较                          |
| -msoft-float           | 输出包含浮点库调用的目标代码                                 |
| -mshort                | 将int类型作为16位处理，相当于short int                       |
| -mrtd                  | 强行将函数参数固定的函数用ret NUM返回，节省调用函数的一条指令 |
| -mcpu=type             | 针对不同的CPU使用相应的CPU指令。可选择的type有i386、i486、pentium、i686等 |



## Searching Header File

gcc 在编译时查找头文件的顺序：

1. 先查找`-I`指定的目录

2. 然后找gcc的环境变量 `C_INCLUDE_PATH`，`CPLUS_INCLUDE_PATH`，`OBJC_INCLUDE_PATH`

3. 再找默认目录(取决于OS，有些OS中这些目录不存在)：

   ```
   /usr/include
   /usr/local/include
   ```

4. gcc的一系列自带目录, 例如:

   ```
   /usr/include/c++/4.8.5
   ```

## Searching Library File

库文件就是编译好的二进制文件(`.o`)， 相比头文件，使用库文件可以避免暴露源代码，并且减少编译时间。 对库文件的链接分为静态链接和动态链接





gcc 在编译时查找库文件的顺序：

1. 先查找`-L`指定的目录

2. 再找gcc的环境变量`LIBRARY_PATH`

3. 再找默认目录( 同上，取决于OS)：

   ```
   /lib
   /lib64
   
   /usr/lib
   /usr/lib64
   
   /usr/local/lib
   /usr/local/lib64
   ```


## g++

`g++`: GNU的CPP编译器，其实就是把`gcc`的前端换掉，后端不变

* gcc会根据文件后缀名`.c/.cpp`将文件分别当作C/CPP来编译. `g++`统一将文件当作CPP编译

* `gcc`编译cpp文件时只会默认链接C标准库，不默认链接CPP标准库. `g++`默认页链接CPP标准库

* `g++`的命令选项和`gcc`相同




# Clang/LLVM

[Clang官网](https://clang.llvm.org/)

* Clang+LLVM： LLVM是一个可以**跨平台**的编译器后端。 Clang是支持LLVM的编译器前端。Clang+LLVM组合是一个完整的编译器tool chain（暴打gcc）

  * Clang：Clang是LLVM的C, Objective-C, and C++语言的前端，且也只支持这几种语言

  * Clang/LLVM使用的调试工具是`LLDB`,  链接器是`lld`, 构建工具是`CMAKE`

  * **clang和clang++的关系相当于gcc和g++的关系**，一般我们用clang++编译CPP，当然也可以用`clang -lstdc++`

  * OSX上的clang是Apple Clang， 这是个clang的发行版，具体有啥区别我也不知道

    





## Clang/LLVM vs gcc

* clang的调试信息非常简洁明了，gcc尽管随着不断发展，也在这方面赶上clang，但还有一定差距
* clang/LLVM的源代码用CPP书写，结构清晰, 几乎是编译器架构的教科书。 gcc是C写的，而且用了一种类似Lisp的编程范式，有大量的元编程，非常难懂
* 对于CPP文件，clang的编译速度比gcc快。 不过对于c文件，二者没什么差别。 
* Linux内核的代码里面有很多奇奇怪怪的语法，是和gcc妥协写的，clang目前好像还不能编译linux内核。 另外，对于CPP模板元编程的报错信息，clang比gcc优雅很多

| Criteria                         | gcc                                                          | Clang/LLVM                                                   |
| -------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| License                          | GNU GPL                                                      | Apache 2.0                                                   |
| Supported language standards     | C++23 in experimental stage, C++20 fully complaint.  [gcc官网上的CPP标准支持情况](https://gcc.gnu.org/projects/cxx-status.html) | C++17 support available. C++20和23都只是部分支持 [Clang官网上的CPP标准支持情况](https://clang.llvm.org/cxx_status.html) |
| Generated Code Characteristics   | Efficient with a lot of compiler options to play around with | Efficient due to the SSA form used by LLVM backend           |
| Language independent type system | No                                                           | Yes (One of the design goal for LLVM)                        |
| Build tool                       | Make based                                                   | CMake                                                        |
| Parser                           | Previously Bison LR. Now recursive descent.                  | Hand-written recursive descent                               |
| Linker                           | LD                                                           | lld                                                          |
| Debugger                         | GDB                                                          | LLDB                                                         |

* 查看编译器支持的CPP标准:

  ```c++
  // test.cpp
  #include<iostream>                                                                                                                                                                                                using namespace std;
  int main(){
    //也有人会打印__STDC_VERSION__, 但这个宏不是被所有编译器支持的， 比如g++就不支持
    cout << __cplusplus << endl;
  }
  ```

  ```
  clang++ test.cpp -lstdc++ -o test && ./test
  ```

  ```
  g++ test.cpp -lstdc++ -o test && ./test
  ```

* 截至目前，Gcc对CPP23标准的支持只是实验性的，参见官网:

  > C++23 features are available since GCC 11. To enable C++23 support, add the command-line parameter `-std=c++2b` to your `g++` command line. Or, to enable GNU extensions in addition to C++23 features, add `-std=gnu++2b`.
  >
  > **Important**: Because the ISO C++23 standard is still evolving, GCC's support is **experimental**. No attempt will be made to maintain backward compatibility with implementations of C++23 features that do not reflect the final standard.


## LLVM Basic

创建一个C语言文件test.c

```c
#include <stdio.h>
int main() {
  printf("hello world\n");
  return 0;
}
```



1. 编译生成可执行文件：

   ```sh
   clang test.c -o test
   ```

2. 运行可执行文件

3. 生成llvm字节码文件：

   ```sh
   clang -O1 -emit-llvm test.c -c -o test.bc
   ```

4. 生成LLVM 的汇编代码 .ll 文件(可视化字节码文件):

   ```sh
   clang -O1 -emit-llvm test.c -S -o test.ll
   ```

5. 运行字节码文件：

   ```sh
   lli test.bc
   ```

    .ll文件也可以用lli来执行

6. 将 .bc 文件转化为 .ll 文件:

   ```sh
   llvm-dis test.bc
   ```

7. 将 .ll 文件转化为 .bc 文件:

   ```sh
   llvm-as test.ll
   ```

8. 编译字节码文件为汇编文件：

   ```sh
   llc test.bc -o test.s
   ```

9. 将 .bc 或 .ll 文件转化为本机平台的汇编代码：

   ```sh
   llc test.bc
   llc test.ll
   ```

   





 ``


 ``


 ``
 ``





# MinGw

MinGW: Minimalist GNU For Windows. Window平台的编译器, 事实上它不只是一个编译器, 还包含了Linux(事实上是GNU)的一系列工具(包括编译器GCC和开发工具gawk, bison等),  使用MinGw可以在Win上使用类似Linux的开发工具链来构建Windows应用. 而且交叉编译Linux和WIndows代码也更方便

* MinGw包含了一系列头文件和库文件, 允许人们在没有第三方动态链接库的情况下使用 GCC（GNU Compiler C）产生 Windows32 程序。
* 
* MinGW把源码中Unix-like OS API调用通过头文件翻译替换成相应的Windows API调用的编译环境
* MinGW与Linux下广泛使用的GNU近乎完全兼容，这意味着，在Linux下如何编译源代码，在MinGW中也可以以完全相同的方式编译. 本质上讲，MinGw是为了给那些因为不喜欢使用Unix/Unix like而使用WIn的人一个和GNU大体相符的编译环境的

# Cygwin

* Cygwin: 一个Windows下Unix-like模拟环境，具体说就是Unix-like接口（OS API，命令行）重定向层，其目的是不修改软件源码仅重新编译就可以将Unix-like系统上的软件移植到Windows上（这个移植也许还算不上严格意义上的无缝移植）
  * Cygwin是让Windows拥有Unix-like环境的软件, 它里面安装了GCC, 作为其编译器
  * Cygwin可以比MingW移植更多的软件到Windows上，对Linux接口模拟比MingW全面
  * Cygwin模拟的Unix-like环境依然不是真实的Unix-like环境， 比如说，Cygwin依然只能打开exe文件，没法打开elf文件



 # MSVC

* MSVC: 微软开发的WIndows native的编译器和运行时, MSVC只能编译出WIndows平台的应用



