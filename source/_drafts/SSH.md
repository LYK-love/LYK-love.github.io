---
title: SSH
tags:
---



## SSH escape sequences

Built in to the SSH client are multiple hidden commands that can be triggered with a so called *escape sequence*. These commands can be access by a combination of the tilde prefix (`~`) followed by the command.

For example `~?` print the help message containing all of the supported escape sequences:

```bash
david@remote-host:~$ ~?
Supported escape sequences:
 ~.   - terminate session
 ~B   - send a BREAK to the remote system
 ~R   - request rekey
 ~#   - list forwarded connections
 ~?   - this message
 ~~   - send the escape character by typing it twice
(Note that escapes are only recognized immediately after newline.)
```

Pay extra attention to the last line;

> *(Note that escapes are only recognized immediately after **newline**.)*



可以看到, `~.`的组合可以关闭当前ssh session.

# Local -> Remote

Now we config the capability of connecting the server from one's local machine.

On your local machine, run:

```sh
ssh-copy-id user@host
```

where `user` is your user account name on the remote server, and `host` is the hostname or ip address of the remote server.



Or you can copy your ssh public key `id_rsa.pub` of your local machine to `~/.ssh/authorized_keys` of the remote server.

# Remote -> Github

1. Generate ssh key on the server：

   ```sh
   ssh-keygen -t rsa
   ```

2. Look at `~/.ssh`:

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

   

Look at `~/.ssh`:

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


注意, ssh是对应Linux User的. 因此配置了本机当前用户和目标用户的ssh, 并不代表着配本机root用户到目标用户的ssh(因为当前用户的ssh公私药都存在`~/.ssh`而非/root/.ssh). 
例如: 配置本机当前用户与github的ssh后, 是无法执行`sudo git clone XXX`的. 因为root用户没有和github配置ssh.


服务器上配置ssh免密登陆：

* 将本地 `id_rsa.pub` 文件的内容拷贝至远程服务器的 ~/.ssh/authorized_keys
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

