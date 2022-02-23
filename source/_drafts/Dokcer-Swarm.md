---
title: Dokcer Swarm
tags: Docker
categories: Container
---

Docker Swarm可以以Swarm模式对Docker节点上的多节点应用进行部署和管理

<!--more-->

curl cip.cc

curl ifconfig.me



# [Linux中普通用户配置sudo权限（带密或免密）](https://www.cnblogs.com/zhangwuji/p/9947768.html)

配置步骤如下：

1、登陆或切换到root用户下；

2、添加sudo文件的写权限，命令是:chmod u+w /etc/sudoers

3、编辑sudoers文件：vi /etc/sudoers

找到这行 root ALL=(ALL) ALL,在他下面添加xxx ALL=(ALL) ALL (注：这里的xxx是你的用户名)

你可以根据实际需要在sudoers文件中按照下面四行格式中任意一条进行添加：
youuser      ALL=(ALL)        ALL
%youuser      ALL=(ALL)        ALL
youuser      ALL=(ALL)        NOPASSWD: ALL
%youuser      ALL=(ALL)        NOPASSWD: ALL
第一行：允许用户youuser执行sudo命令(需要输入密码)。
第二行：允许用户组youuser里面的用户执行sudo命令(需要输入密码)。
第三行：允许用户youuser执行sudo命令,并且在执行的时候不输入密码。
第四行：允许用户组youuser里面的用户执行sudo命令,并且在执行的时候不输入密码。

4、撤销sudoers文件写权限,命令:chmod u-w /etc/sudoers
