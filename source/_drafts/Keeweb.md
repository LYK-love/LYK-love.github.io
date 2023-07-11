---
title: Keeweb
tags:
---



数据库文件: `XX.bak`

kee file: `XX.key`

Master password: `xxxxxx`



在拥有数据库文件的情况下:

* 如果启用了key file, 那么需要同时拥有key file和master password才能够解锁数据库文件.
* 如果不启用key file, 那么只需输入master password即可解锁数据库文件.

因此, 在开启key file的情况下, 不能把key file和数据库文件放在同一个设备(包括云服务), 否则别人一旦访问了该设备, 只要猜对master password就可以读取数据库文件, 获得你的隐私.

如果不开启key file, 那么安全性会降低. 他人在得到数据库文件后只要猜对密码, 不需要得到key file即可获得隐私.

一种practice是:

1. 数据库文件放在云存储.
2. key file放在本地.

不过开启keyfile也有一定的麻烦, 因此key file如果不放在云存储而是放在本地的话, 一旦key file丢失, 密码就都找不回来了.



