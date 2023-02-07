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

* manjaro:

  ```shell
  yay -S mysql
  ```

  

* mac:

  ```
  brew install mysql
  ```


* Ubuntu:这里只针对Ubuntu 20.04. Ubuntu 源仓库中最新的 MySQL 版本号是 MySQL 8.0

  ```shell
  sudo apt update
  sudo apt install mysql-server
  ```


---

* Start mysql server:

  ````sh
  sudo systemctl start mysql
  ````

* Check status of mysql-server:

  ```sh
  systemctl status mysql
  ```

  

## Unintall

on Ubuntu:

1. First, remove already installed mysql-server using-- `sudo apt-get remove --purge mysql-server mysql-client mysql-common`
2. Then clean all files `sudo apt-get autoremove`





## Config

### mysql允许远程访问

mysql默认绑定本地环回地址（127.0.0.1），无法公网通信(即使你的用户是允许远程登录的用户(如`%`):

```
tcp 0 0 127.0.0.1:3306 0.0.0.0:* LISTEN 3783/mysqld
```

1. 需要修改mysql的配置文件, 该文件的位置依平台的不同而变化. 它在ubuntu20.04中位于:

   ```
   /etc/mysql/mysql.conf.d/mysqld.cnf
   ```

   

2. 我们需要修改`bind-address`字段:

   1. 可以在其后面添加可访问mysql服务器的ip，用空格隔开:

      ```
      bind-address=127.0.0.1  139.196.197.138 <other-ip>
      ```

   2. 或者直接把该字段注释掉

3. 重启mysql服务:

   ```sh
   service mysql restart
   ```

# Connection



* 远程连接:

  ```
  mysql -h 192.168.5.116 -P 3306 -u root -p123456
  ```

  

简单来说，`locahost` 一般意味着使用的是 `Unix Domain Socket` ，此时是不会经过网络防火墙的。

如果 `skip_name_resolve` 配置关闭，那么 `127.0.0.1` 这类地址也会被解析成 `locahost`



如果不指定主机或者使用 `-hlocalhost` ，实际上会有限尝试使用 Unix Domain Socket 连接 (实际还需要保证没有使用 `--protocol=TCP` 参数)，默认的是 `/var/lib/mysql/mysql.sock` ，如果 Sock 地址修改了，也可以通过 `-S PATH` 参数指定。

也就是说，在通过 mysql 客户端访问数据库时，如果指定了 `-h<IP>` 参数，那么会通过 TCP/IP 方式连接数据库。

最简单的，如果要要强制使用 TCP/IP 连接到本地服务器，那就使用 IP 地址 `127.0.0.1` 而不是主机名 `localhost` 



通过 TCP/IP 方式进来的连接，MySQL 服务器接收到的来源主机是 `127.0.0.1`；如果采用的是 UNIX Domain Socket 方式，那么 MySQL 服务器接收到的来源主机是 `localhost` 。

另外，对于 TCP/IP 方式来说，如果关闭了 `skip_name_resolve` 选项，那么会尝试将获取到的 IP 地址解析成域名。

> `skip_name_resolve` 参数在调优时，一般建议开启，也就是说禁止域名解析，可以通过如下命令查看是否开启。
>
> ```
> SHOW VARIABLES LIKE '%skip_name_resolve%';
> ```
>
> 修改时，可以直接在 `my.cnf` 配置文件的 `[mysqld]` 字段中添加 `skip-name-resolve` 即可。



在 MySQL 中 `localhost` 一般是用来标示 Unix Domain Socket ，如果将 `skip_name_resolve` 关闭，那么 `127.0.0.1` 也可能会被反解析成 `localhost` 。

## Problems

### 空密码无法用Datagrip连接

1. 首选当然是设一个密码
2. 也可以将Datagrip配置中的密码的保存方式更改为Never

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



