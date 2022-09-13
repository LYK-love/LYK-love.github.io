---
title: Unix Toolkit
tags: Linux
categories: Toolkit
date: 2022-02-19 14:04:37
---


介绍了Unix, Unix Like主机的常用操作

OS可以是各种LINUX发行版和Mac OSX，因此你可以看到各种包管理工具（yay,apt,yum, brew...）, 选自己用的就好

<!--more-->

# SSH

## 配置ssh免密登陆

主机上生成 ssh key：

```
ssh-keygen -t rsa
```

* 腾讯云的服务器不会默认生成ssh key， 所以也不会有`~/.ssh`文件夹， 其他主机也无法通过ssh连接（`ssh-copy-id`）也不行。 因此腾讯云服务器需要先生成ssh key，才能使用

* (这种情况很罕见)如果主机没有安装ssh，需要先安装`openssh-server`:

  ```shell
  apt install openssh-server
  ```

  

查看`~/.ssh`:

```ssh
❯ ls -l ~/.ssh
total 20
-rw-r--r-- 1 lyk lyk   27  2月 10 15:44 config
-rw------- 1 lyk lyk 2602  2月  9 17:18 id_rsa
-rw-r--r-- 1 lyk lyk  571  2月  9 17:18 id_rsa.pub
-rw------- 1 lyk lyk 3926  2月 19 12:58 known_hosts
-rw------- 1 lyk lyk 3182  2月 19 12:41 known_hosts.old

```

* authorized_keys: 存放远程免密登录的公钥,主要通过这个文件记录多台机器的公钥。(没有则手动创建该文件)

* id_rsa: 生成的私钥文件

* id_rsa.pub: 生成的公钥文件

* known_hosts: 已知的主机公钥清单





服务器上配置ssh免密登陆：

* 将本地 id_rsa.pub 文件的内容拷贝至远程服务器的 ~/.ssh/authorized_keys
  * 如果服务器没有`~/.ssh`，则需要自己创建
* 也可以`ssh-copy-id user@host `

## 本机到本机的免密登陆

本机到本机也是需要配置免密登陆的，但是`root@localhost`需要额外配置，`/etc/ssh/sshd_config`中有一个属性为`PermitRootLogin` ,默认值no不允许进行密码登录，我们需要将其改为yes.：

```shell
vim /etc/ssh/sshd_config
```



然后重启ssh服务:

ubuntu：

```shell
sudo service ssh restart
```

manjaro:

```shell
systemctl restart sshd.service
```

mac:

```shell
sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist
```





ssh会因为各种各样的原因失败，排查ssh问题的命令:

```shell
sshd -T
```



如果远程主机的公钥发生了变化, 那么需要重新纪录远程主机的公钥，这需要先把原来的记录清空：

```bash
ssh-keygen -R [remote-host-ip]
```



# User Config

## 配置用户

详见后文 *用户操作*



添加用户：

```
sudo adduser [username]
```







## 赋予新用户sudo权限

用adduser创建后的新用户是不能使用sudo的，因为还没有赋予相关root权限，执行以下代码赋予权限

```shell
sudo usermod -a -G adm username
sudo usermod -a -G sudo username
```


或者将用户加到sudoers文件中:



```shell
#添加sudo文件的写权限,命令是:
chmod u+w /etc/sudoers
#编辑sudoers文件
vim /etc/sudoers
#在 root ALL=(ALL) ALL,下面添加lyk ALL=(ALL) ALL 
lyk ALL=(ALL) ALL

#最后删除sudo文件的写权限
chmod u-w /etc/sudoers
```







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

`pbcopy` on OSX can Copy data from stdin to the clipboard.

```sh
nvim a
# write thoughtful response
cat a | pbcopy
# cmd tab
# paste to slack
rm a
```

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

## 用户操作

### 创建新用户

```shell
sudo adduser [username]
```



### 切换用户

```shell
sudo su [username]
```

### 修改用户密码

```shell
sudo passwd user
```

### 删除用户

`sudo userdel username`: 仅仅删除用户，不删除用户的home目录文件

* `-r`: 删除用户的home目录文件

当需要删除用户时可以使用以下指令

### 查看用户组

```shell
cat /etc/group
```



