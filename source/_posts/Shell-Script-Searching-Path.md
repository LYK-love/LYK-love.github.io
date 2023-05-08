---
title: Shell Script Searching Path
date: 2023-04-23 21:48:25
tags:
- shell
- Linux
categories: 
- Toolkit
---

Outline:

* Shell Script Searching Path
* Append path to `PATH`
* Bad Practices

<!--more-->


# Shell Script Searching Path

Shell will **find and execute** command. The searching sequence of command name is:

1. 将该command name看作一个文件的相对/绝对路径, 并执行该文件, 例如`/bin/ls `或`./ls `.
2. 由 `alias` 找到该指令来执行
3. 由 bash 内置的( builtin)指令来执行.
4. 通过 `PATH` 这个变量的顺序搜寻到的第一个指令来执行.

在某一步骤找到command name后就会停止查找, 并且尝试执行.

因此, 如果一个command name不是一个可执行的路径, 也不是一个alias, 又不是一个builtin( 例如`alias`), 则shell会在搜环境变量`$PATH中`搜索该command name, 如果找到, 就执行; 找不到, 则报错"command not found".



* 由于`PATH` 是个环境变量, 因此它在任意的子session中都有效.
* Command not found == not found in `PATH`. 这只是意味着在`PATH`中找不到该command name. 可以将该command的路径添加到`PATH`来让shell能搜索到它.
* 可以看到, 如果一个command name是路径, 那么在step1就找到了, 不会尝试后面的步骤. **一个command name被视作路径名 iff 该command name带有slash( `/` )**. 
  * 对于当前目录下的文件`file`, 它的路径名是`./file`, 而不是`file`. 后者不会让Shell将其视作路径.

# Append path to `PATH`

将命令的路径加入环境变量`PATH`的方法:

声明环境变量`PATH`, 值为之前的`PATH`的值(采用`$`进行赋值),  再append 一个`:`, 因为环境变量之间通过冒号隔开, 再append要添加的路径, 这里是`/home/to/operation_tools`. 

```shell
export PATH=$PATH:/home/to/operation_tools
```

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
