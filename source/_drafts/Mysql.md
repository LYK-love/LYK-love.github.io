---
title: Mysql
tags:uubuin
---





d

union底层的实现是排序， 因此尽量用union all



not in底层是or运算，遇到空值有问题。 要换成exist



操作对数据量增加的敏感程度：

* 不大： 基于主键的查询

* 线性影响：
* 非线性影响：排序




# 数据库设计

 Normalization

* 1NF: Atomicity
* 2NF：  检查对key的完全依赖
* 3NF： 检查属性的独立性
