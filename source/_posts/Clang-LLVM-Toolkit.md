---
title: Clang/LLVM Toolkit
tags:
  - Linux
  - Compiler
categories: Toolkit
date: 2022-09-13 15:16:26
---


Outline:

* LLVM

<!--more-->

# LLVM

## Install

这里讲一下Mac OSX怎么安装llvm/clang.

也可以手动编译LLVM/clang: [Doc](https://clang.llvm.org/get_started.html)



OSX自带了LLVM, 但是是苹果版的, 和开源版本不太一样, 我们希望使用开源版本的LLVM. 

1. 使用brew安装:

   ```sh
   brew upgrade && brew install llvm
   ```

   这会安装开源版本的LLVM. 注意, 主机中实际是两个版本的LLVM共存的, 我们不要使用系统的LLVM, 只用brew下载的LLVM.

   Linux中一般直接安装到`/usr/local`了. 但是由于Max也有一个LLVM, 不能把二者混淆, brew就会把LLVM装到别的位置

2. 查看brew安装的LLVM位置:

   ```sh
   cat $(brew --prefix llvm)
   ```

   * 这显示的是符号链接的位置(例如, `/opt/homebrew/opt/llvm`),  真实的llvm被安装在形如`/opt/homebrew/Cellar/llvm/14.0.6_1`的位置. 不过无关紧要

3. 把LLVM添加到`PATH`:

   ```sh
   # LLVM on MAC, mac已经自带了llvm, 但是位置很奇怪  Not Committed Yet
   MAC_LOCAL_LLVM_VERSION=14.0.6_1
   export LLVM_MAC_LOCAL_HOME=/opt/homebrew/Cellar/llvm/$MAC_LOCAL_LLVM_VERSION
   # brew目录下的llvm实际上是指向Mac local LLVM的符号链接, 为了方便, 还是用符号链接的路径吧
   export LLVM_HOME=/opt/homebrew/opt/llvm
   export PATH=$PATH:$LLVM_HOME/bin
   ```

4. 再添加两个环境变量, 让clang能找到LLVM:

   ```sh
   export LDFLAGS="-L($LLVM_HOME)/lib -Wl,-rpath,($LLVM_HOME)/lib"
   export CPPFLAGS="-I($LLVM_HOME)/include -I($LLVM_HOME)/include/c++/v1/"
   ```

5. 再把Clang的环境变量设置一下:

   ```sh
   export CC := /usr/local/opt/llvm/bin/clang
   export CXX := $(CC)++
   ```

   * 更好的办法是添加到`PATH`. 我这样设置, 命令行需要用`$(CC)`来调用clang

6. 测试安装是否成功:

   ```sh
   llvm-dis --version
   ```

   
