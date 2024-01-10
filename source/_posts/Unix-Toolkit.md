---
categories:
- Software Engineering
date: 2022-02-19 14:04:37
tags: Linux
title: Unix Toolkit
---

介绍了Unix, Unix Like主机的常用操作

OS可以是各种LINUX发行版和Mac OSX，因此你可以看到各种包管理工具（yay,apt,yum, brew...）, 选自己用的就好

<!--more-->



# User Config

#   Disk Config

`fdisk`：查看磁盘信息

```shell
sudo fdisk -l
```



卸载分区

```shell
#sudo umount  [磁盘路径]
sudo umount /dev/nvme0n1p11
```



将分区格式化为ext4类型

``` shell
#（这里分区为/dev/nvme0n1p11）
sudo mkfs.ext4  /dev/sdb1
```



##  挂载分区（临时）

挂载分区（ 这里挂载到到`/data`目录下 ）

```
#sudo mount  /dev/sdb1  /[目录名] （目录当然是已存在的）
sudo mount /dev/sdb1 /data
```

* 这个挂载是临时的，重新开机就会丢失。 如果要开机自动启动挂载， 需要编辑`/etc/fstab`



查看硬盘和挂载分区等信息

```
df  -h
```

这样就成功添加了一块硬盘并挂载到`/data`目录下了，



## 设置开机自动挂载

1. 查询UUID

```shell 
ls -al /dev/disk/by-uuid

#输出为：
...
... 88e7c2eb-82e6-48c2-a3d8-829c32468f1f -> ../../nvme0n1p11
...
```

可以查到对应分区`nvme0n1p11`的uuid为`88e7c2eb-82e6-48c2-a3d8-829c32468f1f`



2. 编辑`/etc/fstab`(用来存放文件系统的静态信息的文件)

```
sudo vim /etc/fstab
```

末尾加上UUID=刚刚复制的UUID /data ext defaults 0 0

```
UUID=刚刚复制的UUID /data ext4 defaults 0 0
```



# Start Using

不仅主机需要安装软件, 有时容器也需要安装某些软件( 尤其是传统Unix命令行工具包). 对于某些非常精简的容器, 可能连ping这样的基本命令都没有，需要手动安装这些基本的命令.

如果OS是Ubuntu（ 云服务器或容器 ）， 需要先：

```shell
apt-get update
```





* Terminal

  * [安装终端模拟器, Zsh, Zsh主题, Zsh插件以及各种美化](https://lyk-love.cn/2022/09/13/Terminal/)
  * [Tmux](https://lyk-love.cn/2022/09/13/Tmux/)

* Editor or IDE: 对于服务器而言, 大多数OS预装的vim都够用了. 自用的话还得是nvim

  * [Nvim Developing Environment](https://lyk-love.cn/2022/08/18/Nvim-Developing-%20Environment/)
  * [VSCode](https://lyk-love.cn/2022/09/13/VSCode/)

* [Package Manager](https://lyk-love.cn/2022/09/13/Package-Manager/)

* [Unix CLI Tools](https://lyk-love.cn/2022/09/13/Unix-CLI-Tools/?highlight=unix+t)

* [Traditional Unix CLI Tools](https://lyk-love.cn/2022/09/13/Traditional-Unix-CLI-Tools/)

* 各种开发环境:

  * [Java-Toolkit](https://lyk-love.cn/2022/09/13/Java-Toolkit/)
  * [Clang/LLVM Toolkit](https://lyk-love.cn/2022/09/13/Clang-LLVM-Toolkit/)

* 数据库: [Database Toolkit](https://lyk-love.cn/2022/09/13/Database-Toolkit/#more)

* 云原生工具安装: [Cloud Native Toolkit](https://lyk-love.cn/2022/09/13/Cloud-Native-Toolkit/)

  

# 常用操作

## clipboard

`pbcopy` and `pbpaste`on OSX can Copy&Paste data from stdin to the clipboard.

Open a terminal and run:

```bash
cat ~/Desktop/ded.html | pbcopy
```

The file is now in your clipboard.

To put it somewhere else (i.e. paste it) run:

```bash
pbpaste > ~/Documents/ded.html
```

Now you should have a copy of ded.html sitting in ~/Documents.

## xxd

[xxd](https://www.tutorialspoint.com/unix_commands/xxd.htm) - make a hexdump or do the reverse.



查看键盘输入的字符对应的16进制表示:

```sh
xxd -ps
```

### Example

输入 `<Ctrl+b> + c`，其会显示该输入的 hex codes 为：

```bash
^Bc
02630a
```

其中，`02` 代表 `<Ctrl+b>`，`63` 代表 `c`，而 `0a` 代表回车键



## Aliases

```
alias alias_name="command_to_alias arg1 arg2"
```

`alias`是一个`command`，接受**一个**参数， 因此`=`左右不能有空格

### example

```shell
# Make shorthands for common flags
alias ll="ls -lh"

# Save a lot of typing for common commands
alias gs="git status"
alias gc="git commit"
alias v="vim"

# Save you from mistyping
alias sl=ls

# Overwrite existing commands for better defaults
alias mv="mv -i"           # -i prompts before overwrite
alias mkdir="mkdir -p"     # -p make parent dirs as needed
alias df="df -h"           # -h prints human readable format

# Alias can be composed
alias la="ls -A"
alias lla="la -l"

# To ignore an alias run it prepended with \
\ls
# Or disable an alias altogether with unalias
unalias la

# To get an alias definition just call it with alias
alias ll
# Will print ll='ls -lh'
```

`alias`是面向session的，session关闭也使得`alias`失效， 要想使`alias`持久化，可以将其写在shell的启动文件，如 `.bashrc` or `.zshrc`



## clear

清屏：

```
clear
```



## 切换tty

1. CTRL + ALT + Fn

2. ```shell
   sudo chvt N # N: tty number, 1 represents the main tty
   ```





## 下载

```shell
# Download the contents of a URL to a file (named "foo" in this case):
wget https://example.com/foo

# Download the contents of a URL to a file (named "bar" in this case):
wget -O bar https://example.com/foo
```

## 主机操作

查看主机名：

```shell
hostname 
```



更改主机名：

```shell
vim /etc/hostname # 编辑该文件
```



添加域名映射：

```
vim /etc/hosts
```



## 时间

查看时间：

```shell
date
```

## 查看发行版

```shell
lsb_release -a
```

