---
title: Linux Netwoking
tags: Linux
categories: Computer Science
---



# 基本概念

## 网络接口

每个硬件网卡(一个MAC)对应一个网络接口，其工作完全由相应的驱动程序控制。

此外，还存在虚拟网络接口, 比如本地环回接口( lo)，它们并不对应硬件网卡，不会从从外界接收和发送数据包，而是在系统内部接收和发送数据包，因此虚拟网络接口不需要驱动程序。

```
$ ip route show                                                                         
default via 172.31.0.1 dev en0
127.0.0.0/8 via 127.0.0.1 dev lo0
127.0.0.1/32 via 127.0.0.1 dev lo0
169.254.0.0/16 dev en0  scope link
172.31.0.0/17 dev en0  scope link
172.31.0.1/32 dev en0  scope link
172.31.115.202/32 dev en0  scope link
224.0.0.0/4 dev en0  scope link
255.255.255.255/32 dev en0  scope link
```

* eth: ethernet的简写，指以太网接口。
  * 设备后面的"0"、"1"表示第1、2个物理设备。 比如eth0，表示第一块物理网卡。 如果电脑有两块网卡，第二块就是eth1。下同
  * 这个名字在Mac中是`en0`，在某些Linux发行版中是` enp0sx`

* wifi:wifi是无线局域网，wifi0一般指无线网络接口。
* ath: Atheros的简写，指Atheros芯片所包含的无线网络接口。
* lo: local的简写，指本地环回( loopback )接口





虚拟网络接口的应用范围非常广泛。最着名的当属“lo”了，基本上每个linux系统都有这个接口。

　　虚拟网络接口并

　　虚拟网络接口和真实存在的网络接口在使用上是一致的。
