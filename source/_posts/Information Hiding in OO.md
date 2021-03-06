---
title: Information Hiding in OO
tags: Software Engineering Methodology
categories: Software Engineering
date: 2021-06-27 11:09:53
---

# 封装类的职责 

<!--more-->

* 回顾结构化设计的信息隐藏
  * Each module hides the **implementation** of an important design decision (secrets) so that only the constituents of that module know the details

* Design Secrets need to hide…
  * **Primary** Secret: **Responsibility** Change 
    * Hidden information that was specified to the software designer
    * From SRS
  * Secondary Secret: **Implementation** Change
    * The implementation decisions made by the designer when implementing the module designed to hide the primary secret
    * 变化；

## 类的职责 

### 什么是职责？
* 类或对象维护⼀定的状态信息 
* <u>基于状态履行行为职能的能⼒</u>

### 职责来源于哪？

* 职责来源于需求
* 业务类 
  * Sales、Order
* 辅助类 
  * View、Data、exception、transaction

### 职责的体现

* 封装

### 封装

* 信息隐藏 
* 分为接⼝和实现 
  * The interface is the visible surface of the capsule.
    * describes the essential characteristics of objects of the class which are visible to the exterior world
  * The implementation is hidden in the capsule.
    * The implementation hiding means that data can only be manipulated, that is updated, within the class, but it does not mean hiding interface data.

### ⾯向对象中的接⼝
* 对象之间交互的消息（⽅法名） 
* 消息中的所有参数 
* 消息返回结果的类型 
* 与状态⽆关的不变量 
* 需要处理的异常

### 实现的细节
* Data 
* Structure 
* Other object 
* Type 
* Ch

## 类的封装

### 封装实现的细节

* 封装数据和⾏为 
* 封装内部结构 
* 封装其他对象的引⽤ 
* 封装类型信息 
* 封装潜在变更



## 封装的源头 --- ADT

*  ADT = Abstract Data Type 
  * A concept, not an implementation 
  * A set of (homogeneous) objects together with a set of operations on those objects 
  * No mention of how the operations are implemented 不关心操作的实现
  * Example: 栈
* Encapsulation = data abstraction + type 
  * data abstraction: group data and operation 
  * Type: hiding implementation, make usage correctly 

## Why type?

* A type may be viewed as a set of clothes (or a suit of armor) that protects an underlying untyped representation from arbitrary or unintended use.
* It provides a protective covering that hides the underlying representation and constrains the way objects may interact with other objects.
* In an untyped system untyped objects are naked in that the underlying representation is exposed for all to see.

# 为变更⽽设计

## OCP

Open/Closed Principle (OCP)

* Software entities should be open for extension, but closed for modification 

*  Be open for extension 

  * module's behavior can be extended

*  Be closed for modification 

  * source code for the module must not be changes

* 统计数据表明，修正bug最为频繁，但是影响很⼩；新增需求数量⼀般，但造成了绝⼤多数影响

* Modules should be written so they can be extended without requiring them to be modified

  

* RTTI is Ugly and Dangerous! 
  * RTTI = Run-Time Type Information 执行时期的类型信息
  * If a module tries to dynamically cast a base class pointer to several derived classes, any time you extend the inheritance hierarchy, you need to change the module 将一个多态指针转换为其实际指向对象的类型。 
  * 破坏了面向对象的纯洁性
  * recognize them by type switch or if-else-if structures

##   多态

 ## DIP

Dependency Inversion Principle 

依赖倒置，懂得都懂
