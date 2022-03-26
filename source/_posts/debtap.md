---
title: debtap
categories: Toolkit
date: 2022-02-10 06:02:24
---


A tool to traverse deb package.

ref: [here](https://www.jianshu.com/p/900dc8a0ecff)

<!--more-->

# install

1. install

2. before update: 国外源非常慢，需要换源：

   1. `sudo nvim /usr/bin/debtap`

   2. `：%s/ftp.debian.org/mirrors.ustc.edu.cn/g `

      `：%s/archive.ubuntu.com/mirrors.ustc.edu.cn/g`

3. update debtap： `sudo debtap -u`

# usage

* `sudo debtap [file_name].deb`
  注意： 安装时会提示输入包名，以及license。包名随意，license就填GPL吧 上述操作完成后会在deb包同级目录生成`xxx.tar.xz`文件

* 静默模式

  `-q `略过除了编辑元数据之外的所有问题。

  `debtap -q xxx.deb`

* 略过所有的问题（不推荐）

  `debtap -Q xxx.deb`
  
* 安装转换好的本地包

  `sudo yay -U xxx.tar.xz`





