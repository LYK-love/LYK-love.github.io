---
title: Hard Link && Symbol Link
tags: Linux
categories: Technology
date: 2022-05-05 02:07:49
---


Outline:

* link
* symlink

<!--more-->

# 硬链接( link )

对应的shell命令：`ln`

对应系统调用`link`

## 详解

* 硬链接只是对**同一个**inode创建了新的引用

  ```shell
  > ln far far2 
  > ls -i                                                                       
  
  2536724 far  2536724 far2  //inode number一样
  ```

  

* 事实上，文件名都只是对`inode`的链接

* 创建文件时，实际上是先创建`inode`，然后将人类可读的名称链接到该文件，并将这个键值对存入目录

* 不能创建目录的硬链接，因为会在目录树中成环

* `inode  number`在不同文件系统中不唯一，因此硬链接不能跨文件系统

* 硬链接会增加文件的引用计数，也就是`ls -l`里看到的那个

## code

Create a new link to (make a new name for) a file:

```c
#include <unistd.h>
int link(const char *oldpath, const char *newpath);
```

* Return: 0 if success; -1 if failure

  



Delete a name and possibly the file it refers to:

```
#include <unistd.h>
int unlink(const char *pathname);
```

* Return: 0 if success; -1 if failure





# 软链接( symlink )

也称为符号链接

对应shell命令：`ln -s`

```shell
ln -s  far far3  
```



对应系统调用`symlink`

## 详解

* 符号链接是一个**不同类型的文件**, 它的内容是被链接文件的文件名

  * `ls`显示，类型为`l`

* **OS将截获对符号链接文件的访问，,依据符号链接中的文件名去读真正的目标文件**

* 优点： 可链接目录， 可跨文件系统链接（因为只存储了目标路径）

* 缺点:**搜索文件路径**开销大,需要额外的空间查找存储路径

  

```shell
> ls -al
drwxr-xr-x 3 lyk lyk  4096 11月 26 22:14 .
drwxr-xr-x 4 lyk lyk  4096 11月 26 22:00 ..
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far2
lrwxrwxrwx 1 lyk lyk     3 11月 26 22:14 far3 -> far  //软链接，内容为目标文件名“far”，是三字节

```



## code

Create a symbolic link (named newpath which contains‏the‏sting‏”oldpath”):

```c
#include <unistd.h>
int symlink(const char *oldpath, const char *newpath);
```

* Return: 0 if success; -1 if failure



Read value of a symbolic link: 

```c
#include <unistd.h>
int readlink(const char *path, char *buf, size_t bufsiz);
```

* Return: the count of characters placed in the buffer if success; -1 if failure

