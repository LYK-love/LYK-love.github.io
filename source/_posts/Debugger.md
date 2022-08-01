---
title: Debugger
tags: Compilers
categories: Toolkit
date: 2022-05-05 03:40:59
---




Outline:

* GDB
* LLDB

<!--more-->



# GDB

[官网](https://sourceware.org/gdb/)

* GDB: GNU Debugger，是和GCC配套的Debugger， 当然现在也支持Clang/LLVM
  * 要使用GDB，需要GCC编译时开始`-g`选项，生成GDB所需的调试信息



* Debug步骤：
  1. 设置断点
  2. 监视变量值
  3. 单步执行
  4. 修改变量值

## commands

[GDB Tutorial](https://www.geeksforgeeks.org/gdb-command-in-linux-with-examples/)

Syntax:

```
gdb [-help] [-nx] [-q] [-batch] [-cd=dir] [-f] [-b bps] [-tty=dev] [-s symfile] [-e prog] [-se prog] [-c core] [-x cmds] [-d dir] [prog[core|procID]]
```



使用`gdb [executable-file]`打开文件进行调试



| command      | 解释                                                         |
| ------------ | ------------------------------------------------------------ |
| break/tbreak | 设置断点，可以是行号、函数名及地址(以*开头) </br> tbreak: 设置临时断点 |
| run          | 执行当前调试的程序                                           |
| list         | 列出源代码的一部分                                           |
| next         | 执行一条语句但不进入函数内部                                 |
| step         | 执行一条语句，是函数则进入函数内部                           |
| display      | 显示表达式的值                                               |
| print        | 临时显示表达式的值                                           |
| kill         | 中止正在调试的程序                                           |

# LLDB

* LLDB( LLVM Debugger ):是Clang/LLVM的配套Debugger. 在OSX上， Xcode的默认编译器就是Clang/LLVM，Debugger就是LLDB
* LLDB和GDB用法差不多，详见[GDB 和 LLDB command的差别](https://lldb.llvm.org/use/map.html)
