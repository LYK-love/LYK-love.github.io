---
title: Shell Script Searching Path
tags:
- shell
- Linux
categories: 
- Technology
- Toolkit
---

Outline:

* Command Name Seaching Sequence
* Append path to `PATH`
* Finding Commands in `PATH`
* Bad Practices

<!--more-->

# Command Name Seaching Sequence

[ref: Shell search PATH – finding and running commands](https://teaching.idallen.com/cst8207/19w/notes/400_search_path.html#:~:text=(Shells%20find%20and%20run%20commands.)&text=When%20you%20type%20the%20command,file%20named%20date%20to%20execute.)

Shell will **find and execute** command. The searching sequence of command name is:

1. 以相对/绝对路径执行指令，例如`/bin/ls `或`./ls `
2. 由 `alias` 找到该指令来执行
3. 由 bash 内置的( builtin)指令来执行.
4. 通过 `PATH` 这个变量的顺序搜寻到的第一个指令来执行.

在某一步骤找到command name后就会停止查找, 并且尝试执行.

因此, 如果一个command name不是一个可执行的路径, 也不是一个alias, 又不是一个builtin( 例如`alias`), 则shell会在搜环境变量`$PATH中`搜索该command name, 如果找到, 就执行; 找不到, 则报错"command not found".



* 由于`PATH` 是个环境变量, 因此它在任意的子session中都有效.
* Command not found == not found in `PATH`. 这只是意味着在`PATH`中找不到该command name. 可以将该command的路径添加到`PATH`来让shell能搜索到它.
* 可以看到, 如果一个command name是路径, 那么在step1就找到了, 不会尝试后面的步骤. **如果一个command name带有slash( `/` ), 则会被视作路径名.**
  * 对于当前目录的文件, 它的名字前面也必须带有`./`才能被识别为一个路径名.

# Append path to `PATH`

首先, `PATH`是由directories组成的列表[^1], shell会在`PATH`的每个目录中寻找目标file. 因此`PATH`中只能添加directory, 不能添加file.

将命令的路径加入环境变量`PATH`的步骤:

1. 声明变量`PATH`, 由于`PATH`是环境变量, 我们希望新的`PATH`也是环境变量, 因此要用`export PATH`
2. `PATH`的值为: 之前的`PATH`的值(采用`$`进行赋值),  再append 一个`:`, 因为环境变量之间通过冒号隔开, 再append要添加的file所在的**目录**的路径, 这里是`/home/to/operation_tools`. 

```shell
export PATH=$PATH:/home/to/operation_tools
```

# Finding Commands in `PATH`

Commands related to `PATH` and finding commands:

* `which`: tell which PATH directory contains a command
* `whereis`: locate commands in "standard" directories (ignores `PATH`). It also locates man pages for you, if any.

## `which`

The command `which` tells you which directory in your `$PATH` contains a command name:

```
$ echo "$PATH"
/usr/local/bin:/bin:/usr/bin
$ which date
/bin/date
$ which head
/usr/bin/head
```

**Only the first directory containing the command name is printed**.

## `whereis`

The command `whereis` may tell you that a command exists in some standard directory, but when you try to execute the command it may not be found, if the standard directory is not one of your shell’s `PATH` directories, or if you don’t have permission to execute the command:

```
$ fdisk
bash: fdisk: command not found
$ which fdisk                             # no output - not found in PATH
$ whereis fdisk
fdisk: /sbin/fdisk /usr/share/man/man8/fdisk.8.gz
$ echo "$PATH"
/bin:/usr/bin                             # PATH does not contain /sbin
$ PATH=$PATH:/sbin ; echo "$PATH"         # append :/sbin to PATH
/bin:/usr/bin:/sbin
$ which fdisk                             # now fdisk is found in PATH
/sbin/fdisk
$ fdisk                                   # now fdisk is found in PATH
Usage:
[...]
```

Most shells only look in `PATH`, not in any “standard” places. If you have a bad `PATH`, no non-built-in commands will be found.

## 6.2 `whereis` – where is this command (and man page) in the system*[Index![up to index](https://teaching.idallen.com/cst8207/19w/notes/common/toparrow.gif)](https://teaching.idallen.com/cst8207/19w/notes/400_search_path.html#TOC)*

The command `whereis` may tell you that a command exists in some standard directory, but when you try to execute the command it may not be found, if the standard directory is not one of your shell’s `PATH` directories, or if you don’t have permission to execute the command:

```
$ fdisk
bash: fdisk: command not found
$ which fdisk                             # no output - not found in PATH
$ whereis fdisk
fdisk: /sbin/fdisk /usr/share/man/man8/fdisk.8.gz
$ echo "$PATH"
/bin:/usr/bin                             # PATH does not contain /sbin
$ PATH=$PATH:/sbin ; echo "$PATH"         # append :/sbin to PATH
/bin:/usr/bin:/sbin
$ which fdisk                             # now fdisk is found in PATH
/sbin/fdisk
$ fdisk                                   # now fdisk is found in PATH
Usage:
[...]
```

Most shells only look in `PATH`, not in any “standard” places. If you have a bad `PATH`, no non-built-in commands will be found.



# Bad Practices

以下是一些错误的对`PATH`进行设置的例子.

## Current directory in `PATH`

**A leading or trailing colon in `PATH`, or two adjacent colons (`::`), indicate that the *current directory* is one of the directorie**s that the shell should try when looking for executable command names. This is a security risk and you must not do it:

```
$ echo "$PATH"
:/bin/:/usr/bin                          # EXTREME SECURITY RISK!

$ echo "$PATH"
/bin/::/usr/bin                          # MODERATE SECURITY RISK!

$ echo "$PATH"
/bin/:/usr/bin:                          # SECURITY RISK!
```

**Do not put the current directory (or any relative path directory) in `PATH` – it is a security risk.** You might accidentally execute a malicious program in the current directory.

> For example: If you put the current directory at the start of your `PATH`, e.g. `PATH=:/bin:/usr/bin`, then when you type `ls` the first program that is tried is `./ls` (the program named `ls` in the current directory) which might be a malicious program.

## Command names with slashes avoid `PATH`

[^1]: https://lyk-love.cn/2022/03/18/Shell-Script-Language/#Env-virable
