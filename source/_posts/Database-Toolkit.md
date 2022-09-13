---
title: Database Toolkit
date: 2022-09-13 15:20:30
tags:
---


Outline:

* Mysql
* Mongodb
* Database Tools

<!--more-->

# Mysql

## Install

manjaro:

```shell
yay -S mysql
```

---



mac:

```
brew install mysql
```

---

ubuntu:

这里只针对ubuntu 20.04， Ubuntu 源仓库中最新的 MySQL 版本号是 MySQL 8.0

```shell
sudo apt update
sudo apt install mysql-server
```

---

安装完成后，MySQL 服务将会自动启动。想要验证 MySQL 服务器正在运行，输入：

```shell
sudo systemctl status mysql
```

---

输出应该显示服务已经被启用，并且正在运行：

```
● mysql.service - MySQL Community Server
     Loaded: loaded (/lib/systemd/system/mysql.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2020-04-28 20:59:52 UTC; 10min ago
   Main PID: 8617 (mysqld)
     Status: "Server is operational"
     ...
```

## Config

### mysql允许远程访问

mysql默认绑定本地环回地址（127.0.0.1），无法公网通信(即使你的用户是允许远程登录的用户(如`%`)):

```
tcp 0 0 127.0.0.1:3306 0.0.0.0:* LISTEN 3783/mysqld
```

需要修改mysql的配置文件`/etc/mysql/my.conf`，在bind-address后面增加远程访问IP地址， 或者禁掉该字段

* mysql配置文件，在ubuntu20.04的Ver 8.0.29-0ubuntu0.20.04.3上，位于`/etc/mysql/mysql.conf.d/mysqld.cnf`

```
bind-address=127.0.0.1  139.196.197.138
```

* 可以直接把改字段注释掉
* 也可以添加可访问mysql服务器的ip，用空格隔开



重启mysql服务

```
service mysql restart
```

# Mongodb

## Install

由于 MongoDB 修改了软件授权协议，  官方仓库已经删除了此软件包。请注意从代码编译 mongodb 需要 ~160GB 磁盘空间，需要花费几个小时时间。因此我们最好安装`-bin`版本

```
yay -S mongodb
```



注意： 只有先启动`mongod`， 才能正确启动`mongo`

### 报错

可能有报错：

```
> mongo
connecting to: mongodb://127.0.0.1:27017
2018-09-27T21:11:14.779+0800 W NETWORK  [main] Failed to connect to 127.0.0.1:27017, reason: Connection refused
2018-09-27T21:11:14.780+0800 E QUERY    [main] Error: couldn't connect to server 127.0.0.1:27017, connection attempt failed :
connect@src/mongo/shell/mongo.js:234:13
@(connect):1:6
exception: connect failed
```

出现以上原因，可能是data目录下的mongod.lock文件的问题。可以使用命令修复：

```csharp
[root@localhost mongodb]# ./bin/mongod --repair
```

 然后重新打开一个窗口，启动mongodb

## Config

配置文件路径： `\etc\mongodb.conf`. 

* 其中`dbpath`为数据库的路径

## Commands

启动

```ruby
$ systemctl start mongodb.service
```

查看状态:

```lua
sudo systemctl status mongodb
```

重启:

```text
sudo systemctl restart mongodb
```

停止:

```text
sudo systemctl stop mongodb
```

重载服务:

```text
sudo systemctl daemon-reload
```

设置开机启动:

```
sudo systemctl enable mongodb
```



# Database Tools

## mycli

好用的命令行mysql界面,[项目地址](https://github.com/dbcli/mycli)

```shell
# 通用
pip install -U mycli
```

or

```shell
# on Arch
yay -S mycli
```

or

```shell
# Only on macOS
brew update && brew install mycli  
```

or

```shell
# Only on debian or ubuntu
sudo apt-get install mycli 
```



