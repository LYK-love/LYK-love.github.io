---
title: 网络攻防实战 Web安全
tags:
---

* `Nmap -sS`

  * `-Ss`不完成三次握手，只需要server完成第二次握手就可确定存活

  * 由于未完成传输层交互，因此不会在应用层被记录
  * SYN洪泛：收到第二次握手报文后弃之不理，持续发送第一次握手的报文。
    * 传统的server资源分配都在第一次握手后，由于SYN，现在都在第三次握手后分配资源

* VPN：
* 协议代理：将整个数据包打包起来，发送到SERVER后，由SERVER解包
