---
title: Spring NoSQL
tags:
---

# NoSQL

* NoSQL(Not Only SQL) ，指的是非关系型的数据库
* 没有声明性查询语言
* 没有预定义的模式
* 键-值对存储、列存储、文档存储、图形数据库

# MongoDB

MongoDB 是由C++语言编写的，是一个基于分布式文件存储的开源数据库系统。
文档存储一般用类似json的格式存储，存储的内容是文档型的。这样也就有机会对某些字段建立索引，实现关系数据库的某些功能



实体类不需要 Serializable, 因为默认已经配置了

## MongoDB 概念

| SQL术语/概念 | MongoDB术语/概念 | 解释/说明       |
| ------------ | ---------------- | --------------- |
| database     | database         | 数据库          |
| table        | collection       | 数据库表/集合   |
| row          | document         | 数据记录行/文档 |
| column       | field            | 数据字段/域     |

## MongoDB Shell命令使用

mongosh
MongoDB Shell是MongoDB自带的交互式Javascript shell,用来对MongoDB进行操作和管理的交互式

## 常用命令

* `show dbs`
* `show collections`





环境基于jdbc驱动编程
Spring data mongodb

# Redis

* key-value的Hash表结构，value是某数据结构 
* 内存数据库（缓存）
* 集群
* 主从（master/slave）复制
* 数据持久化
* 注意key、value区分大小写





## Redis数据类型

* String
* Linked Lists
  * 队列lpush/rpop
  * 阻塞等待：BRPOP和BLPOP
* Hashes
* Sets

## Redis命令

rpush mylist 15
lrange mylist 0 -1    -1是列表的最后一个元素，-2是列表的倒数第二个元素，依此类推。
rpush mylist 1 2 3 4 5 "foo bar“
lpush mylist 1 2 3 4 5
rpop key
lpop key
brpop tasks 5

hmset user name tao age 10
hgetall user
hget user name

sadd myset 1 2 3
smembers myset



## 连接到Redis

JedisConnectionFactory



## 使用RedisTemplate

RedisTemplate
StringRedisTemplate



## RedisTemplate的子API

* 使用简单的值
  `opsForValue()`----ValueOperations
  set、get
* 使用List类型的值
  `opsForList()`----ListOperations
  rightPush、leftPop、range
* 在Set上执行操作
  `opsForSet()`----SetOperations
  add、difference、union、intersect
* 绑定到某个key上
  `boundListOps("cart")`



## 指定序列化器

* 默认处理：`JdkSerializationRedisSerializer`
* `StringRedisSerializer`
* `Jackson2JsonRedisSerializer`
