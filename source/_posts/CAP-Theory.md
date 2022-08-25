---
title: CAP Theory
tags: Distributed System
categories: Computer Science
mathjax: true
date: 2022-08-25 22:09:03
---


Outline:

* Intro
* Consistency
* Availability
* Partition Tolerance
* CAP: Tradeoff
* Yield && Harvest
* BASE Theory

<!--more-->

# Intro

In 2000, Dr. Eric Brewer 在 *Proceedings of the Annual ACM Symposium on Principles of Distributed Computing*[^1]上提出了CAP理论的猜想:

a shared-data system can have at most two of the three following properties: 

1. **C**onsistency: 
2. **A**vailability
3. tolerance to network **P**artitions. 

In 2002, Gilbert and Lynch[^2] 形式化地证明了该猜想.





CAP理论揭示出分布式系统不可能同时满足CAP这三者.



# Consistency

From Gilbert and Lynch[^2](https://codahale.com/you-cant-sacrifice-partition-tolerance/#fn:2):

> Atomic, or linearizable, consistency is the condition expected by most web services today. Under this consistency guarantee, there must exist a total order on all operations such that **each operation looks as if it were completed at a single instant**. This is equivalent to requiring requests of the distributed shared memory to act as if they were executing on a single node, responding to operations one at a time.

* 一致性( Consistency ): a system is consistent if **an update is applied to all relevant nodes at the same <u>logical time</u>.**
  * 也就是说系统各节点的状态是一致的, 对多个节点的操作从结果上看就好像是对一个节点的操作, 不存在状态不一致的节点. 这也要求操作的原子性.
  * 比如, 所有节点访问同一份最新的数据副本.
  * database replication不是强一致性的, 因为副本同步需要时间.
* 即使和全局的一致性是不可能的, 我们要求的只是相对而言的一致性( 即不一致状态的时间粒度很小, 小到没有影响 )
* 关于一致性的实现, 有强一致性算法和最终一致性算法

## Strong Consistency

//TODO

Paxos：我最喜欢的图灵奖获得者Leslie Lamport于90年提出，几乎所有强一致性算法鼻祖.

Raft(Paxos变种)：etcd使用

ZAB(Paxos变种)：ZooKeeper使用

## Eventual  Consistency Algorithm

DNS系统：域名解析，超过TTL逐步向上询问

Gossip算法：逆熵算法，Cassandra中使用

## Eventual Consistency

# Availability

Again from Gilbert and Lynch[^2]:

> For a distributed system to be continuously available, **every request received by a non-failing node in the system must result in a response**. That is, **any algorithm used by the service must eventually terminate** … [When] qualified by the need for partition tolerance, this can be seen as a strong definition of availability: even when severe network failures occur, every request must terminate.

- 可用性(Availability): 每个对non-failing node的请求一定能被响应.
  * 这里指的是<u>有效</u>的响应, 500服务器错误不是一次有效的响应.
- 绝对的可用性也是不可能的, 因为存在节点全部fail的情况



# Partition Tolerance

Once more, Gilbert and Lynch[2](https://codahale.com/you-cant-sacrifice-partition-tolerance/#fn:2):

> In order to model partition tolerance, **the network will be allowed to lose arbitrarily many messages sent from one node to another**. When a network is partitioned, all messages sent from nodes in one component of the partition to nodes in another component are lost. (And any pattern of message loss can be modeled as a temporary partition separating the communicating nodes at the exact instant the message is lost.)

- 分区容错性(Partition tolerance): 系统能够容忍任意的网络分区故障. 
  * 这里的网络分区故障是指, 网络分成许多区域, 不同区域间不能互通
  * 网络丢包可以被认为是暂时的分区故障; node failure也可以被认为是分区故障, 因为所有发送给它的数据包都会丢失
  * 当然也存在不需要分区容错性的系统, 比如单机系统. 不过对于分布式系统, 都存在分区问题.
- 只要是分布是

## P is Mandatory

**P is mandatory in distributed systems. You cannot not choose it.** 

我们可以假设一下, 如果有一个CA的系统, 它有三个节点$A, B, V$, 管理同一块数据. 由于网络分区, 节点被分裂为$\{A, B\}$和$\{C\}$, 此时有一个更新数据的写请求到达节点$C$. 此时$C$只有两种选择:

1. 接受这次写请求, 但是$A,B$ 在分区恢复前永远不知道数据已经被更新
2. 拒绝这次写请求, 直到分区恢复后再开始接受请求

选择1只能保证可用性, 选择2只能保证一致性. 但没法同时保持CA.



因此, 只要是分布式系统, 都**必须保持P**. 因此系统要么是CP, 要么是AP, 绝不可能是CA. 除非这个分布式系统能够在网络分区的情况下更新其他节点的状态, 但这是不可能的.



# CAP: Tradeoff

## Consistency > Availability

如果一个系统是CP的, 也就是提供一致性( C )而不是可用性( A ), 它将通过**拒绝响应一些请求**来保证其一致性( i.e. 原子读写, 事务) 

常见例子是大部分分布式数据库以及银行系统

## Availability > Consistency

如果一个系统是AP的, 也就是提供可用性( A ), 而不是一致性( C ), 它将对所有的请求做出响应，可能会返回旧的读和接受冲突的写.

有很多数据模型可以接受旧的读, 比如金融行业, 淘宝, 12306 ...

# Yield && Harvest

有许多种对分布式系统的度量, 其中很有名的是 Fox 和 Brewer在“Harvest, Yield, and Scalable Tolerant Systems”[^3]中提出的**yield** and **harvest**.

* **yield**: he probability of completing a request

  * yield与"正常运行时间"很接近，但在实践中更有用，因为并非所有的时间都有同等价值. yield直接映射到用户体验. 在没有请求的情况下宕机一秒钟, 会减少正常运行时间, 但对用户或yield没有影响

* **harvest**:  the fraction of the data reflected in the response, i.e. the completeness of the answer to the query.
  $$
  \mathrm{harvest}= \frac{\mathrm{total \ data}}{\mathrm{data \ available}}
  $$

  * 例如, 假设我们在一个搜索引擎上工作，我们可以想象每个词都有单独的索引。使用 "cute "一词的网页的索引在$A$节点上，使用 "婴儿 "一词的网页的索引在$B$节点上，而 "动物 "一词的索引在$C$机器上。那么，搜索 "cute baby animals"，结合来自节点$A,B,C$的结果，$\{A,B,C\}$将有100%的$\mathrm{harvest}$. 然而, 如果节点$BB$不可用，我们可能只返回 "cute animals"的结果，这将是一个66%的$\mathrm{harvest}$.
  * 例如, 一个存储文件版本的系统在一些节点瘫痪的情况下, 可以选择呈现它能找到的最新版本的文件，即使它知道这有可能不是它所存储的最新版本.



* 关键在于, yield和harvest之间存在trade off. 在设计系统时要根据业务来侧重其中一方. Replicated systems 倾向于把fault等价为 reduced yield, 因为请求被拒绝了(为了同步); partitioned systems 倾向于把fault等价为 reduced harvest, 因为能够接受相同数量的请求, 但是某些分区中的数据不见了.

  

# BASE Theory

CAP理论描述了分布式系统的理想状态, BASE理论是一个更妥协的理论, 在实践中更有用:

* **B**asically **A**vailable( 基本可用 ): 在出现故障时，允许部分可用性（基础可用）
* **S**oft State( 软状态 ): 允许出现中间状态，不同节点之间数据不一致
* **E**ventual Consistency( 最终一致性 ): 软状态不可持续, 在有限期限后应能保证数据的最终一致



# Refs

[^1]: Brewer. [Towards robust distributed systems.](http://www.cs.berkeley.edu/~brewer/cs262b-2004/PODC-keynote.pdf) Proceedings of the Annual ACM Symposium on Principles of Distributed Computing (2000) vol. 19 pp. 7—10 
[^2]: Gilbert and Lynch. [Brewer’s conjecture and the feasibility of consistent, available, partition-tolerant web services.](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.67.6951&rep=rep1&type=pdf) ACM SIGACT News (2002) vol. 33 (2) pp. 59
[^3]: Fox and Brewer. [Harvest, yield, and scalable tolerant systems.](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.24.3690&rep=rep1&type=pdf) Hot Topics in Operating Systems, 1999. Proceedings of the Seventh Workshop on (1999) pp. 174—178
