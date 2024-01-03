---
title: The Shell Program
categories:
- Software Engineering
tags: 
- Shell
- Linux
date: 2022-07-15 12:00:00
---

Source:

1. Machtelt Garrels. *[Chapter 1. Chapter 1. Bash and Bash scripts](https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_01.html)*.
2. 蔡德明. *[第十一认识与学习Bash. 鸟哥的Linux私房菜](http://cn.linux.vbird.org/linux_basic/0320bash_1.php)*.

<!--more-->

# The concept of shell

In a high level,  "shell" program can refer to any program that lays between kernel mode and user mode. 

* The user interface program, **shell** or **GUI**, is the <u>lowest level of user-mode software</u>, and allows the user to start other programs --- 拙著 *OS Introduction* 

In this chapter we focus on the UNIX shell programs although Microsoft Windows OS has its shells such as Powershell.

The UNIX shell program is a interpreter, and the shell script executed by that program is interpreted. Thus, shell language is a interpreted language. 

In this case, different implementations of shell will create different dialects. But we don't need to worry about them since they're mainly the same.

## Shell types

* **sh** or Bourne Shell: the original shell still used on UNIX systems and in UNIX-related environments.  This is the  basic shell, a small program with few features.  While this is not the  standard shell, it is still available on every Linux system for  compatibility with UNIX programs.

  

* **bash** or Bourne Again shell: the standard GNU shell, intuitive and flexible.  Probably most advisable for beginning  users while being at the same time a powerful tool for the advanced and  professional user.  On Linux, **bash** is the standard shell for common users.  This shell is a so-called *superset* of the Bourne shell, a set of add-ons and plug-ins.  This means that the Bourne Again shell is compatible with the Bourne shell: commands that work in **sh**, also work in **bash**.  However, the reverse is not always the case.  All examples and exercises in this book use **bash**.

* **Zsh**: a modern shell with many fancy features. It's installed by OSX by default.

* Other unpopular shells: **csh** or C shell,  **tcsh** or TENEX C shell, **ksh** or the Korn shell.

* 在现代的 Linux 上，sh 已经被 bash 代替。 sh在Linux中是bash的一个符号链接； 在mac中是一个独立的程序

* The file `/etc/shells` gives an overview of known shells on a Linux system:

  ```shell
  ❯ cat /etc/shells
  /bin/sh
  /bin/bash
  /usr/bin/bash
  /bin/rbash
  /usr/bin/rbash
  ```
  
* Your default shell is set in the `/etc/passwd` file, like this line for user *lyk*:

  ```txt
  lyk:x:1000:1000:lyk,,,:/home/lyk:/bin/zsh
  ```

## Shell Session



Shell session 是终端中当前的状态，在终端中只能有一个 session。当我们打开一个新的终端时，总会创建一个新的 shell session。

就进程间的关系来说，session 由一个或多个进程组组成。一般情况下，来自单个登录的所有进程都属于同一个 session。我们可以通过下图来理解进程、进程组和 session 之间的关系：

![Shell Session Archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Toolkit/Shel%20lSession%20Archetecture)

会话是由会话中的第一个进程创建的，**一般情况下是打开终端时创建的 shell 进程**。该进程也叫 session 的领头进程。Session 中领头进程的 PID 也就是 session 的 SID。我们可以通过下面的命令查看 SID：

```
ps -o pid,ppid,pgid,sid,tty,comm
```

```
    PID    PPID    PGID     SID TT       COMMAND
   5745    5729    5745    5745 pts/4    zsh
   5785       1    5784    5745 pts/4    zsh
   5787       1    5784    5745 pts/4    zsh
   5789       1    5788    5745 pts/4    zsh
   5794    5789    5788    5745 pts/4    gitstatusd
   5844    5745    5844    5745 pts/4    ps

```

Session 中的每个进程组被称为一个 **job**，有一个 job 会成为 session 的前台 job(foreground)，其它的 job 则是后台 job(background)。每个 session 连接一个控制终端(control terminal)，控制终端中的输入被发送给前台 job，从前台 job 产生的输出也被发送到控制终端上。同时由控制终端产生的信号，比如 ctrl + z 等都会传递给前台 job。

一般情况下 session 和终端是一对一的关系，当我们打开多个终端窗口时，实际上就创建了多个 session。

Session 的意义在于多个工作(job)在一个终端中运行，其中的一个为前台 job，它直接接收该终端的输入并把结果输出到该终端。其它的 job 则在后台运行。

# Hot to switch shell 

Check availabe shells in the sysyem:

```shell
cat /etc/shells
```




Current shell:

```shell
echo $SHELL
```



set one shell  as default for your user:

```shell
chsh -s <full-path-to-shell>
```

# Shell and Syscall

由于系统调用`fork()`和`exec()`的分离，程序可以在`fork()`之后，`exec()`之前运行代码，方便了shell的工作

## shell workflow

* `shell`的workflow：
  1. 显示一个`prompt`,等待用户输入
  2. 用户进行输入，输入内容是一个命令，由一个可执行程序和若干参数组成
  3. `shell`找到该可执行程序。调用`fork()`创建新进程
  4. `shell`可能执行某些代码
  5. 调用`exec()`执行这个可执行程序
  6. 调用`wait()`等待该命令完成
  7. 子进程执行结束后，shell从`wait()`返回，继续步骤1

## shell 重定向

shell实现重定向：对于` wc 5_2.c > [filename].txt`, wc的输出结果被重定向到`[filename].txt`

步骤解释：

1. shell在`fork()`之后，`exec()`之前，会：

   1. 先用`open`打开文件`[filename].txt`, 给它分配一个文件描述符, 记为`STDOUT_FILENO`(一般是3，因为0，1，2都已被占用)
   2. 再关闭标准输出( fd = 1 )

   

2. shell使用`dup`/`dup2`来分配一个`STDOUT_FILENO`的复制，由于`dup`默认是分配未使用的最小的fd），此时fd=1已经关闭，所以就又分配了fd=1，它是`STDOUT_FILENO`的复制

3. shell执行指令，子进程准备输出，由于UNIX系统会从零开始寻找可用的fd(文件描述符)，因此`STDOUT_FILENO`会成为第一个可用的fd，作为子进程输出的目标



详见*OS Persistence*

* UNIX pipe也用类似方式实现，但使用`pipe()`系统调用,将前一个进程的输入作为后一个进程的输出：`grep -o foo fole | wc -l`





## Session 的创建和销毁

session的创建：

* 通常，新的 session 由系统登录程序创建，session 中的领头进程是运行用户登录 shell 的进程。新创建的每个进程都会属于一个进程组，当创建一个进程时，它和父进程在同一个进程组、session 中。



将进程放入不同 session 的惟一方法是使用 `setsid` 函数使其成为新 session 的领头进程。这还会将 session 领头进程放入一个新的进程组



session的销毁：

* 当 session 中的所有进程都结束时 session 也就消亡了。实际使用中比如网络断开了，session 肯定是要消亡的。
* 让 session 的领头进程退出。一般情况下 session 的领头进程是 shell 进程，如果它处于前台，我们可以使用 exit 命令或者是 ctrl + d 让它退出。或者我们可以直接通过 kill 命令杀死 session 的领头进程。
  * 原理是：当系统检测到挂断(hangup)条件时，内核中的驱动会将 SIGHUP 信号发送到整个 session。通常情况下，这会杀死 session 中的所有进程



session 与终端的关系：

* 如果 session 关联的是**伪终端**，这个伪终端本身就是随着 session 的建立而创建的，session 结束，那么这个伪终端也会被销毁。

  * 打开终端，会话开始；关闭终端，会话结束，会话内部的进程也会随之终止，不管有没有运行完。

    一个典型的例子就是，[SSH 登录](https://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html)远程计算机，打开一个远程终端执行命令。这时，网络突然断线，再次登录的时候，是找不回上一次执行的命令的。因为上一次 SSH 会话已经终止了，里面的进程也随之消失了

    为了解决这个问题，会话与窗口可以"解绑"：窗口关闭时，会话并不终止，而是继续运行，等到以后需要的时候，再让会话"绑定"其他窗口（见“ Terminal  Multiplexer”）

* 如果 session 关联的是 **tty**1-6，tty 则不会被销毁。因为该终端设备是在系统初始化的时候创建的，并不是依赖该会话建立的，所以当 session 退出，tty 仍然存在。只是 init 系统在 session 结束后，会重启 getty 来监听这个 tty



# Linux shell

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



## Navigating in the shell

* 根目录:  `/` is the “root” of the file system
*  A path that starts with `/` is called an *absolute* path. Any other path is a *relative* path.

  * Relative paths are relative to the current working directory, which we can see with the `pwd` command

  *  In a path, `.` refers to the current directory, and `..` to its parent directory:
* Most commands accept flags and options (flags with values) that start with `-` to modify their behavior
* 文件权限： File的权限与人们的直觉相符， 而对于Directory:
  * To enter a directory, a user must have “search” (represented by “execute”: `x`) 
  * To list its contents, a user must have read (`r`) permissions on that directory. 

## Connecting programs

*  `<`, `>`重定向（覆盖原文件内容）
* `<<`, `>>` append模式

## root

`su`： 切换到root

`sudo CMD`： 以root权限执行CMD, 注意只有第一条CMD具有root权限





One thing you need to be root in order to do is writing to the `sysfs` file system mounted under `/sys`. `sysfs` exposes a number of kernel parameters as files, so that you can easily reconfigure the kernel on the fly without specialized tools. **Note that sysfs does not exist on Windows or macOS.**

For example, the brightness of your laptop’s screen is exposed through a file called `brightness` under

```
/sys/class/backlight
```

By writing a value into that file, we can change the screen brightness. Your first instinct might be to do something like:

```
$ sudo find -L /sys/class/backlight -maxdepth 2 -name '*brightness*'
/sys/class/backlight/thinkpad_screen/brightness
$ cd /sys/class/backlight/thinkpad_screen
$ sudo echo 3 > brightness
An error occurred while redirecting file 'brightness'
open: Permission denied
```

* **注意**：`|`, `>`, and `<` 这些操作符是由shell提供的，  `echo`这些程序只接受输入、进行输出， 不知道这些操作符的存在， 因此shell首先用root权限运行`echo 3`， 再用默认权限（即shell的创建者）的权限打开`brightness`文件尝试写入， 而这需要root权限， 因此fail

  Using this knowledge, we can work around this:

  ```shell
  echo 3 | sudo tee brightness
  ```


## Command Parameters

Linux Command的命令行参数可分为长参数（long option）和短参数（short option），长参数形式类似于`--print-something`， 以`--`开头，单词间以`-`分开；短参数形式类似于`-p`，以`-`开头，后面跟单词缩写

### 短参数

在短参数中，字母的大写效果是不同的，比如大写 `T` 和小写 `t`的含义通常不同

```shell
command -p
```



短参数赋值：

```shell
command -p 10
```





多个短参数，可以用空格隔开:

```shell
command -a -b -c -d
```



多个短参数也可以合并在一起：

```shell
command -abcd
```



### 长参数

格式：

```shell
command --parameter
```



长参数赋值：

```shell
command --parameter=10
```



多个长参数，不能像多个短参数那样合并， 只能以空格隔开：

```shell
command --parameter1 --parameter2
```



**可以组合使用短参数和长参数**
例如：



```shell
command -abcd --parameter1 --parameter2
```

