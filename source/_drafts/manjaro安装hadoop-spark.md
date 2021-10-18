---
title: manjaro安装hadoop+spark
tags:
---

# Preparation

* `sudo pacman -Syu`

*  安装jdk：`yay -S jdk`

* 安装openssh：`yay -S openssh`

  * manjaro默认不安装openssh

* 创建hadooop用户并且更改hadoop用户密码

  ```shell
  //创建hadoop用户
  sudo adduser hadoop
  
  //更改hadoop用户密码
  sudo passwd hadoop
  ```

  * manjaro默认不安装`adduser`命令，需自己下载

* 以上的配置完成之后，使用hadoop用户

  ```
  su - hadoop
  ```

  切换成hadoop之后，设置ssh免密登录

  ```
  ssh-keygen -t rsa 
  
  cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys 
  
  chmod 640 ~/.ssh/authorized_keys 
  ```

  然后试试`ssh localhost`，查看是否能够免密登录

  > 如果遇到22端口被拒绝的情况，很有可能是ssh服务并没有开启。
  > 切换成exit退出当前用户，使用主用户
  > 输入`sudo service ssh start`进行服务的开启。如果显示没有该服务，那么可以确定系统并没有安装openssh, 去安装。

* Archlinux或者manjaro开启ssh服务命令:

  `systemctl enable sshd.service`     开机启动

  `systemctl start sshd.service`      立即启动

  `systemctl restart sshd.service`    立即重启

*  用户hadoop使用`su`可能会报错：

  `hadoop is not in the sudoers file.  This incident will be reported.`，需要在/etc/sudoers文件里给该用户添加权限 （[ref](https://www.cnblogs.com/MakeView660/p/12395542.html)）

* 