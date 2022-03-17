---
title: Using Shell
tags: shell
categories: Toolkit
---

Outline:

介绍了一些shell的常识

<!--more-->

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

## PATH

shell变量分为用户变量和环境变量。 `$PATH`是特殊的环境变量， 当shell执行一条和其所有关键字都不匹配的命令时,它会查询 `$PATH` , 它列出了所有shell在查询命令时应查找的目录( 以 `:`分割 )

```
missing:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
missing:~$ which echo
/bin/echo
missing:~$ /bin/echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```

* We can also bypass `$PATH` entirely by giving the *path* to the file we want to execute.

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

  

# Windows shell

windows中：命令和文件名(包括文件类型)不区分大小写. 即 cd 和 CD 一样， dir 和 DIR 一样。 Desktop 和 desktop 一样, *.pdf  和 *.PDF 一样

TAB键： 自动补完。 不区分大小写

`cd` ： change directory 改变目录

 `cd .. ` : go back to upper directory 回到上一级目录， 注意cd 和 .. 中间也可以没有空格

 `cd ../..` :  回到上两级目录

 `cd \` : 回到根目录

 `exit`: 退出

<!--more-->

 `dir` ： list the contents of current directory 浏览当前目录（结果按字母顺序排序）.  文件有<DIR>代表它也是个目录

`dir Desktop\SE` 查看SE的内容， 不会改变当前目录

 `dir Desktop\SE\*.pdf`   遍历并列出SE中以.pdf结尾的文件

注意文件名是区分空格的，所以`dir Desktop \SE` 或 `dir Desktop\ SE`  找不到东西

` dir /a `: show hidden directories as well 注意dir 和 /a 中间也可以没有空格

 `cls`： clear your screen

 `↑`键 ：access your command history

` /?` : to access help and options menu

 `mkdir`   制作目录

 `rmdir` 删除一个空的目录

 `rmdir *** /s` 删除一个有内容的目录

`Home`键： bring u to  to the beginning of the command

`End`键：反之

`Ctrl+left` : 一次左移一个词

——————————————————————————————————

-  `echo not sweet > apple.txt`  向 apple.txt中添加not sweet（这会覆盖txt的原内容）
-  如果不想覆盖，只想append， 那就用`echo not sweet >> apple.txt` 
-  `Desktop\test> dir > apple.txt`    向apple.txt中添加test的目录

-  总之 `Desktop\test> *** > apple.txt` 星号部分是向apple.txt中添加的内容，可以是文字，可以是命令， 说到命令，当然·`ttrib`也可以，`cls`也可以。不过把cls append进去很蠢，啥都不会发生。

—————————————————————————————————

 

 `type 文件名` ： 在CMD中打印该文件的内容

 `remove 被移动的 移动到的` ： 顾名思义，当然，连空文件和空目录也会移动

 `rename 原名 新名字` ： 注意文件类型也在名字里，所以一个 XX.txt如果更名为YY(不带.txt)，那么XX会从一个文本文档变成一个文件夹

—————————————————————————————————

` copy` 要被复制的 复制到的 ： 文件复制  

 `xcopy`: 也是复制，但比copy更好（功能更多） 。 xcopy默认只会复制source中的文件，而不包括目录（copy也是如此）。 通过/S 可以让xcopy复制目录和子目录，不包括空目录。， 但copy没有/S的功能，也就是说copy无法复制目录。

 

要打开应用程序，要么转到对应的目录，然后 `start ** .exe`, 要么直接用双引号括住绝对路径

` C:\Users\color 0B`   数字是背景颜色，字母是foreground or text

 `wmic logicaldisk get name` : see all the available command drives

` tree`关键字： 以树状列出目录及其内部目录…

D: 转到D盘根路径

# Browser

* F5刷新网页，重新显示当前页面内容；
* Ctrl+F5博客的系统使用了数据缓存技术。这虽然可以加快网页的打开速度，但却经常出错。比如留言成功再重新打开网页却可能看不到刚才的的留言内容，其原因就是IE会读取本机缓存区而不是从网络服务器中更新数据。这时可以按CTRL+F5的组合键来清除IE缓存，强行刷新网页，这样就可以看到当前网页的最新内容了；
* Shift+F5全部刷新，刷新当前打开的所有网页。
