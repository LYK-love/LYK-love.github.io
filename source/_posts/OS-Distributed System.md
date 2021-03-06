---
title: OS Distributed System
tags: OS Basic
categories: Computer Science
date: 2021-12-06 21:27:15
---


Outline:

* 通信
* NFS
* AFS

ref: *Operating Systems Three Easy pieces*

<!--more-->

# 通信

*  现代网络核心原则： **通信是不可靠的**
* 有可靠的传输出协议进行消息传递
* 接下来的问题是： 使用什么样的抽象进行通信

## 通信抽象

### DSM

* 分布式共享内存（ `Distributed Shared Memory`  ）:   使不同机器上的同一个进程可以共享一个大的地址空间
  * 用户访问页面时，要么页面在本机，要么发生页错误，页错误处理程序请求其他计算机，获取页面
  * 属于操作系统抽象，给分布式系统提供内存抽象
* DSM很少被采用
  * 不够 Robunt：假如一台机器出现故障，整个地址空间就不可用了（ 比如一个链表的一个节点消失 ）
  * 性能：跨计算机访问资源开销很大，DSM系统的设计者必须小心地组织计算，以便几乎不发生任何通信， 而这与DSM的初衷（跨计算机通信）违背* 

### RPC

* DSM的失败表明： **OS抽象对分布式系统来说是个糟糕的选择**
* **PL抽象更有意义**
  * 最主要的抽象是远程过程调用（`Remote Procedure Call`）
* RPC的目标： 使在远程机器上执行代码的过程像调用本地函数那样直接
  * client： 进行过程调用
  * server： 只是定义了一些希望导出的例程。 其余的由RPC系统处理
* RPC系统：
  * 存根生成器(`stub generator`), 也称为协议编译器（ `protocol compiler` ）
  * 运行时库（ `run-time library` ）

#### Stub Generator

* `Stub Generator`  作为中介，与client和server交互
* 目的：消除将函数和参数打包成消息的复杂度

* 协议编译器的输入：server希望导出给client的一组调用：

  ```c
   interface{
   	int func1(int arg1);
   	int func2(int arg1, int arg2);
   }
  ```

  `stub generator`接受这样的接口，并对 client 和 server 生成一些不同的代码片段（ `stub` ）

* `client stub`: client链接此`client stub`，调用它进行RPC,，客户端只能看到函数调用，在`stub`内部有如下操作：

  *  创建 `message  buffer` ： 一个字节数组
  * 将所需信息打包到 `message  buffer`， 也称为消息的序列化（`serialization`）
  *  将消息发送到目标RPC server
    * 与RPC server的通信，以及使其运行所需的细节都由RPC运行时库处理
  * 等待回复
  * 解包返回代码和其他参数（反序列化）

* `server stub`:

  *  解包消息，即反序列化
  * 调用实际函数
  * 打包结果，放入一个回复缓冲区
  * 发送回复

* 问题：

  * 一个包如何发送复杂的数据结构：比如，如何解释一个指针
    * 通过众所周知的类型（`int`之类）
    * 使用更多信息注释数据结构
  * 并发性服务器组织方式：
    * 线程池

#### Run-time Library

运行时库处理RPC系统中大部分工作，这里讨论构建它时的一些困难

* 命名问题： 如何找到远程服务
  * 采用现有的命名系统（  `ip + port` ）
* RPC传输协议的构建
  * 为了效率，很多rpc采用UDP
  * 如果建立在不可靠的传输层上，RPC需要提供可靠性，比如提供超时/重试
* 字节序：
  * RPC包在其消息格式中指定字节序
* 是否向client暴露通信的异步性质，实现性能优化

# NFS

* 分布式文件系统
  * 由客户端文件系统 + 文件服务器组成
  * 提供对文件的透明访问

* Sun的NFS只是一个协议，允许不同的实现，这里讨论NFS v2
* 目的是“**简单快速的服务器崩溃恢复**”

## 无状态协议

* NFS采用“**无状态**”协议: 每个client操作都包含完成请求所需的全部信息
  * 有状态协议会在client和server间共享状态。 比如文件描述符，如果服务器发生错误，收到客户端第二次读取时将不知道`fd`指的是哪个文件
  * 有状态协议很难处理客户端崩溃情况，如果client在崩溃前用掉了一个`fd`， server将无法知道什么之后收回该`fd`
* **重试请求**：解决服务器没有及时回复的问题
*  **幂等**（`idempotent`）   操作： NFS的操作是幂等的，这就确保了它能简单地重试请求
  * 除了`READ`, `LOOKUP`, 就连`WRITE`也是幂等的
    * `WRITE`包含写入数据的偏移量，实现了其幂等性
  * 但是，有些操作无法幂等，比如`mkdir`，这也是NFS的bug

## 客户端缓存

客户端缓存可以提升性能，但会导致**缓存一致性问题**（ `cache consistency problem` ）

* 假设有客户端`C1`, `C2`, `C3`, 服务器`S`。 `C1`从`S`读取了文件`F`，并将副本存在本地缓存中， 而`C2`覆盖文件`F`，从未而改变其内容
  * 问题一： `C2`将它的写入缓存一段时间再发送，而这之前如果`C3`访问`F`，得到的还是未改变的`F`，这称为`update visibility`
    * client实现**关闭时刷新**` flush-on-close`（即`close-to-open`）: 当一个client写入文件并关闭文件时，将其所有更新刷新到服务器，这样`C3`从服务器你拿到的确保是最新的版本
  * 问题二： 即使`C2`立即发送其写入，`C1`的缓存依然是陈旧的（ ` stale cache` ）, 此时`C1`上的程序只能读取陈旧的缓存
    * CLIENT在打开文件时，会先发送`GETATTR`请求到服务器，检查其是否被更改，如果是，则删除缓存并重新请求
      * `GETATTR`返回文件信息，其中包括服务器上次修改文件的信息
* 可以想见，`GETATTR`请求会非常频繁，为此NFS设计了“属性缓存”，允许文件属性缓存在本地，3s后超时。 但这就使得NFS无法知道文件的确切版本，“陈旧缓存”问题无法彻底解决

## 写缓冲

* 为了确保服务器写入正确， 服务I其必须在完成写入后，才通知客户端写入成功
* 带来写入性能的瓶颈



# AFS

* 原则： 在**client的本地磁盘**进行**全文件缓存**

  * 后续`read()`, `write()`操作是严格本地的，被重定向到本地磁盘上
  * 当然，客户端每次操作前，会发送`TestAuth`给server, 查看文件是否被修改，这类似NFS的`GETATTR`
    * `AFS v2`引入**回调**， server向client承诺，当client缓存的文件被修改时， 会通知client. 这减少了网络通信

  

* AFS也采用关闭时刷新
* 最后关闭者胜出` last closer win`: 最后一个更新该文件的client的内容会被接受
  * AFS是基于文件的，而NFS是基于块的。 对后者而言，如果每个客户端都更新文件，会将不同的块的写入刷新到服务器，这样的文件内容没什么意义

## 崩溃恢复

* 回调可能会丢失，比如该client缓存的文件被另一个client改变，服务器发送回调时，前者还在重启。 
  * 此时前者必须发送`TestAuth`来验证缓存正确性。 
* 崩溃后的服务器恢复也更复杂。 因为回调被保存在server内存中。 因此server重启后，不知道server的情况。
  * 因此，server重启后，每个client都必须意识到server已崩溃。 比如，server重启后向每个client发送消息“不要信任你的缓存！”

