---
title: Shell
tags:

---

# Using the shell

When you launch your terminal, you will see a *prompt* that often looks a little like this:

```
missing:~$ 
```

* 主机名: `missing` 
* 当前工作目录: `~` (short for “home”). 
* The `$` tells you that you are not the root user \



The most basic command is to execute a program with arguments:

```shell
echo hello
```

* shell对命令的解析:
  * 按空格分隔
  * 第一个单词是命令名字,以后的每个单词都是命令的参数
  * If you want to provide an argument that contains spaces or other special characters (e.g., a directory named “My Photos”), you can either quote the argument with `'` or `"` (`"My Photos"`), or escape just the relevant characters with `\` (`My\ Photos`)



shell是一个programming environment, just like Python or Ruby. 当shell执行一条和其所有关键字都不匹配的命令时,它会查询*environment variable* ( called `$PATH` ),它列出了所有shell在查询命令时应查找的目录( 以 `:`分割 )

```
missing:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
missing:~$ which echo
/bin/echo
missing:~$ /bin/echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```

* We can also bypass `$PATH` entirely by giving the *path* to the file we want to execute.

* 目录 以 `:`分割 

## Navigating in the shell

* 根目录:  `/` is the “root” of the file system

*  A path that starts with `/` is called an *absolute* path. Any other path is a *relative* path.

  * Relative paths are relative to the current working directory, which we can see with the `pwd` command

  *  In a path, `.` refers to the current directory, and `..` to its parent directory:

* Most commands accept flags and options (flags with values) that start with `-` to modify their behavior

* Directory的命令权限问题:

  * To enter a directory, a user must have “search” (represented by “execute”: `x`) 
  
* 

