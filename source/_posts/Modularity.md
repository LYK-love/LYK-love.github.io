---
categories: Computer Science
date: 2021-06-27 11:14:38
tags:
- Software Engineering Methodology
title: Modularity
---

Outline:

* Modularity
* Information Hiding

<!--more-->

# Modularity

* Computer systems are not monolithic:   计算机系统并非铁板一块, 它是可分的, 通常由大量互相交互的`模块`组成
  * they are usually composed of multiple, interacting modules.
* `Modularity` has long been seen as a key to cheap, high quality software.
* The goal of **system design** is to decide: 
  * – what the modules are; 
  * – what the modules should be; 
  * – how the modules interact with one-another.

## history

* 萌芽 
  * Wirth1971; Parnas1972;
* 形成 
  * Stevens1974; Parnas1978; Parnas1985
*  发展 
  * Eder1992; Hitz1995;
*  反思 
  * McConnell1996; Demarco2002

具体内容blabla一大堆,自己去看吧(っ °Д °;)っ

## Module

What is a module?

* Common view: a piece of code. Too limited. 
* Compilation unit, including related declarations and interface 编译单元, 包括相关的声明和接口, 这是狭隘的看法
* `David Parnas`: a unit of work.  工作单元
* **Collection of programming units** (procedures, classes, etc.) 
  * with a well-defined **interface and purpose** within the entire system
  * that can be **independently** assigned to a developer

## 模块化的作用

* **Management**: Partition the overall development effort 对整个开发过程做划分
  *  – Divide and conquer 分治策略(计算机经典思想无处不在)
* **Evolution**: Decouple parts of a system so that changes to one part are isolated from changes to other parts 对系统进行解耦, 使得对一个部分的改变不会影响其他部分
  * Principle of directness (clear allocation of requirements to modules, ideally one requirement (or more) maps to one module) 一个需求对应一个模块
  * Principle of continuity/locality (small change in requirements triggers a change to one module only) 小型改动只需对一个模块做修改
* **Understanding**: Permit system to be understood 
  * as composition of mind-sized chunks, e.g., the 7±2 Rule 把系统分成人脑可以理解的一个个区块
  * with one issue at a time, e.g., principles of locality, encapsulation, separation of concerns 使得人脑同一时间只需处理一个问题,
  *  Key issue: what criteria to use for modularization?
    * **Information Hiding**



# Interface && Implementation 

* The interface is <u>the visible surface of the capsule</u>
  * describes the essential characteristics of objects of the class which are visible to the exterior world
* The implementation is hidden in the capsule.
  * The implementation hiding means that data can only be manipulated, that is updated, within the class, but it does not mean hiding interface data.

## Interface

* Interface as a contract - whatever is published by a module that
  * Provided interface: clients of the module can depend on and
  * Required interface: the module can depend on from other modules
* Syntactic interfaces 
  * How to call operations 
    * List of operation signatures 
    * Sometimes also valid orders of calling operations
* Semantic interfaces 
  * What the operations do, e.g., 
    * Pre- and post-conditions 
    * Use cases

### ⾯向对象中的接⼝

* 对象之间交互的消息（⽅法名） 
* 消息中的所有参数 
* 消息返回结果的类型 
* 与状态⽆关的不变量 
* 需要处理的异常

## Interface vs. Implementation 

* Users and implementers of a module have different views of it.
* **Interface**: user’s view of a module.
* describes only what a user needs to know to use the module 
* makes it easier to understand and use 
* describes what services the module provides, but not how it’s able to provide them 
* 只提供用户需要的服务, 但不提供实现



## 类的职责 

* 什么是职责
  * 类或对象维护⼀定的状态信息 
  * <u>基于状态履行行为职能的能⼒</u>

* 职责的来源
  * 职责来源于需求,

* 职责的体现

* 封装Information Hiding



# Information

* **Information ->secrets** 
* what’s a “secret”? -> **Change** 
  * Representation of data  信息的表示
  * Properties of a device, other than required properties  设备的属性
  * Implementation of world models  整个模型的实现
  * Mechanisms that support policies 支持策略的机制

## 容易更改的架构元素

* **hardware dependencies** 硬件设备的依赖(还有外部的软件系统,经常变)
  * External software system
* **input and output formats** 输入和输出的格式
  * DB, Internet, UI, …
* **nonstandard language features and library routines**; 非标准语言特性和库子程序,比如各大os
  * Platform: os, middleware, framework…
* **difficult design and implementation areas** 包含复杂决策和实现的模块(尤其是那些写得很简陋的)
  * especially areas that might be developed poorly and require redesign or reimplementation;
  * Complex…, monitor, exception, log, … 异常类, log类等等
* **complex data structures**, data structures that are used by more than one class, or data structures you haven’t designed to your satisfaction;
  * Separate model from logic
* **complex logic**, which is almost as likely to change as complex data structures; 复杂的逻辑, 如果其依赖的数据结构变了, 那这部分基本也要变
  * Algorithm, schedule, time-critical, performance-critical, …
* **global variables**, which are probably never truly needed, but which always benefit from being hidden behind access routines; 全局变量, 尽量别用
  * Data Access Routines
* **data-size constraints** such as array declarations and loop limits; 数据大小的约束, 比如数组声明, 循环不变式之类
* and **business rules** such as the laws, regulations, policies, and procedures that are embedded into a computer system.

## Information Hiding

* Try to **localize future change** 
  * Hide system details likely to change independently  把容易独立改变的系统细节隐藏起来
  * Separate parts that are likely to have a different rate of change 区分不同有改变速率的部分
  * Expose in interfaces assumptions unlikely to change 把不可能改变的假设暴露在接口中



* the most common kind of secret is a design decision that you think might **change**.
* You then **separate** each design secret by assigning it to its own class, subroutine, or other design unit.
* Next you **isolate** (encapsulate) each secret so that if it does change, the change doesn’t affect the rest of the program.