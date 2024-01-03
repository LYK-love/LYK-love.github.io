---
categories:
- Software Engineering
date: 2023-04-23 20:53:12
tags:
- shell
- Linux
title: Shell Script
---

Outline:

* Intro
* Shebang
* Execute Shell Script
* I/O redirection

<!--more-->

# Intro

[常见Shell指令](https://github.com/onceupon/Bash-Oneliner)

## scripts vs shell functions

Some differences between shell functions and scripts that you should keep in mind are:

- Functions have to be in the same language as the shell, while scripts can be written in any language. This is why including a shebang for scripts is important.
- Functions are loaded once when their definition is read. Scripts are loaded every time they are executed. This makes functions slightly faster to load, but whenever you change them you will have to reload their definition.
- Functions are executed **in the current shell environment**( 可以简单理解为， function的所在路径是当前路径 ) whereas scripts execute in their own process. Thus, functions can modify environment variables, e.g. change your current directory, whereas scripts can’t. Scripts will be passed by value environment variables that have been exported using [`export`](https://www.man7.org/linux/man-pages/man1/export.1p.html)
- As with any programming language, functions are a powerful construct to achieve modularity, code reuse, and clarity of shell code. Often shell scripts will include their own function definitions.

## Shell Programming Style

https://google.github.io/styleguide/shellguide.html

# Shebang

Note that scripts need not necessarily be written in bash to be called from the terminal. For instance, here’s a simple Python script that outputs its arguments in reversed order:

```shell
#!/usr/local/bin/python
import sys
for arg in reversed(sys.argv[1:]):
    print(arg)
```

* shebang: the character sequence consisting of `#!` at the beginning of a script in   a [Unix-like](https://en.wikipedia.org/wiki/Unix-like) operating system

  * shell会将shebang中`#!`之后的内容作为一个程序的路径，打开该程序， 将本script的路径当作参数传入( 即: 将整个script当作input传入shebang所指定的程序 ）

  

  * For example, if a script is named with the path *path/to/script*, and it starts with the following line, `#!/bin/sh`, then the program loader is instructed to run the program */bin/sh*, passing *path/to/script* as the first argument. In [Linux](https://en.wikipedia.org/wiki/Linux), this behavior is the result of both kernel and user-space code.[[9\]](https://en.wikipedia.org/wiki/Shebang_(Unix)#cite_note-9)

  * The shebang line is usually ignored by the interpreter, because the "#" character is a [comment](https://en.wikipedia.org/wiki/Comment_(computer_programming)) marker in many scripting languages; some language interpreters that do not use the hash mark to begin comments still may ignore the shebang line in recognition of its purpose.

## shebang with env

The shebang expects a full path to the interpreter to use so the following syntax would be incorrect:

```py
#!python
```

Setting a full path like this might work:

```py
#!/usr/local/bin/python
```

but would be non portable as python might be installed in `/bin`, `/opt/python/bin`, or wherever other location.

Using `env`

```py
#!/usr/bin/env python
```

is a method allowing a portable way to specify to the OS a full path equivalent to the one where `python` is first located in the `PATH`.



# Execute Shell Script



执行脚本文件：

1. 直接指定`sh`来执行该脚本，不需要shebang，也不需要脚本有执行权限（因为该脚本直接作为参数传给了sh).

   ```sh
   sh script_file_path
   ```

2. 需要写shebang来指定解释器, 并且要指定脚本路径.  

   必须加上`./`使得该command name被识别为一个路径名. 否则shell会继续在alias, builtin和`PATH`中搜索该command name. [^1]

   ```shell
   chmod +x script_file ##(chown, chgrp optionally)
   ./script_file
   ```

3. 使用`.`或`source`在当前shell session中执行该脚本

   ```shell
   source script_file
   ```

   or

   ```shell
   . script_file
   ```

   

   因此, 该方法可以用于刷新当前shell环境:

   ```shell
   source ~/.bashrc
   ```

4. Shell script是能在命令行直接输入的, 但仅会作用一次





注意: 方法1,2都是新开一个子shell session，在其中执行脚本，而方法3, 4是在当前shell session中执行脚本



# I/O redirection

一般情况下，每个 Linux 命令运行时都会打开三个文件：

- 标准输入文件(stdin)：stdin的文件描述符为0，Unix程序默认从stdin读取数据。
- 标准输出文件(stdout)：stdout 的文件描述符为1，Unix程序默认向stdout输出数据。
- 标准错误文件(stderr)：stderr的文件描述符为2，Unix程序会向stderr流中写入错误信息



* Discard the output

  ```shell
  $ command > /dev/null
  ```

  The file **/dev/null** is a special file that automatically **discards all its input**.

* Discard both output of a command and its error output,

  ```shell
  $ command > /dev/null 2>&1
  ```

  * a command normally writes its output to **STDOUT**
  * use standard redirection to redirect **STDERR** to **STDOUT** 
  * 这里`2>&1`将标准错误（2）合并到标准输出（1）， 而标准输出已经被重定向到了`/dev/null`, 因此总体效果是，标准错误和输出都被重定向到了`/dev/null`

* file descriptor:

  * **0** : STDIN
  * **1**: STDOUT
  * **2**: STDERR



| Sr.No. |                    Command & Description                     |
| :----: | :----------------------------------------------------------: |
|   1    | **pgm > file**<br>Output of pgm is redirected to file<br>会覆盖目标文件中原有的数据 |
|   2    |   **pgm < file**<br>Program pgm reads its input from file    |
|   3    |     **pgm >> file**<br>Output of pgm is appended to file     |
|   4    | **n > file**<br>Output from stream with descriptor **n** redirected to file |
|   5    | **n >> file**<br/>Output from stream with descriptor **n** appended to file |
|   6    | **n >& m**<br/>Merges output from stream **n** with stream **m** |
|   7    | **n <& m**<br/>Merges input from stream **n** with stream **m** |
|   8    | **<< tag**<br/>Standard input comes from here through next tag at the start of line |
|   9    | **\|**<br/>Takes output from one program, or process, and sends it to another |

## Here Document

Here Document 目前没有统一的翻译，这里暂译为”嵌入文档“。Here Document 是 Shell 中的一种特殊的重定向方式，它的基本的形式如下：

```
command << delimiter
document
delimiter
```

它的作用是**将两个 delimiter 之间的内容(document) 作为输入传递给 command**



注意：

- 结尾的delimiter 一定要顶格写，前面不能有任何字符，后面也不能有任何字符，包括空格和 tab 缩进。
- 开始的delimiter前后的空格会被忽略掉。


下面的例子，通过 wc -l 命令计算 document 的行数：

```shell
wc -l << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF
```



也可将 Here Document 用在脚本中，例如：

```shell
#!/bin/bash

cat << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF
```



[^1]: https://lyk-love.cn/2023/04/24/Shell-Script-Searching-Path/