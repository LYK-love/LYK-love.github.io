---
title: Modularity and Information Hiding
tags: Software Engineering Methodology
categories: Software Engineering
date: 2021-06-27 11:14:38
---


# 模块化与信息隐藏思想

## 动机

* **Design “Good” Software**

* 对于"Good"的定义：（`Beohm`）
  * Maintainability 可维护性
  * Extendibility 可扩展性 ( 包括可修改性 )
  * Understandability 易理解性
  * Reusability 可重用性

<!--more-->

## 发展

* 萌芽 
  * Wirth1971; Parnas1972;
* 形成 
  * Stevens1974; Parnas1978; Parnas1985
*  发展 
  * Eder1992; Hitz1995;
*  反思 
  * McConnell1996; Demarco2002

具体内容blabla一大堆,自己去看吧(っ °Д °;)っ

## 模块化与信息隐藏

### Modularity

* Computer systems are not monolithic:   计算机系统并非铁板一块, 它是可分的, 通常由大量互相交互的`模块`组成
  * they are usually composed of multiple, interacting modules.
*  `Modularity` has long been seen as a key to cheap, high quality software.
* The goal of **system design** is to decide: 
  * – what the modules are; 
  * – what the modules should be; 
  *  – how the modules interact with one-another.

### What is a module?

* Common view: a piece of code. Too limited. 
* Compilation unit, including related declarations and interface 编译单元, 包括相关的声明和接口, 这是狭隘的看法
* `David Parnas`: a unit of work.  工作单元
* **Collection of programming units** (procedures, classes, etc.) 
  * with a well-defined **interface and purpose** within the entire system
  * that can be **independently** assigned to a developer

### Why modularize a system

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

### Information

* **Information ->secrets** 
* what’s a “secret”? -> **Change** 
  * Representation of data  信息的表示
  * Properties of a device, other than required properties  设备的属性
  * Implementation of world models  整个模型的实现
  * Mechanisms that support policies 支持策略的机制

### the design areas that are most likely to change

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

### Hiding
* Try to **localize future change** 
  * Hide system details likely to change independently  把容易独立改变的系统细节隐藏起来
  * Separate parts that are likely to have a different rate of change 区分不同有改变速率的部分
  * Expose in interfaces assumptions unlikely to change 把不可能改变的假设暴露在接口中

### Information Hiding
* the most common kind of secret is a design decision that you think might **change**.
* You then **separate** each design secret by assigning it to its own class, subroutine, or other design unit.
* Next you **isolate** (encapsulate) each secret so that if it does change, the change doesn’t affect the rest of the program.

### Interface vs. Implementation 

* Users and implementers of a module have different views of it.
* **Interface**: user’s view of a module.
* describes only what a user needs to know to use the module 
* makes it easier to understand and use 
* describes what services the module provides, but not how it’s able to provide them 
* 只提供用户需要的服务, 但不提供实现

### What Is an Interface?
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

### Further Principles
* Explicit interfaces 

  * Make all dependencies between modules explicit (no hidden coupling) 模块间的依赖要清晰, 没有隐藏的耦合

* Low coupling - few interfaces 

  * Minimize the amount of dependencies between modules 尽量减少模块间的依赖, 让接口数变少

* Small interfaces  接口分离原则`ISP`, 接口越小越好

  * Keep the interfaces narrow 

    * Combine many parameters into structs/objects
    * Divide large interfaces into several interfaces

    

* High cohesion 高内聚

  * A module should encapsulate some well-defined, coherent piece of functionality (more on that later)

### Coupling and Cohesion
* Cohesion is a measure of the coherence of a module amongst the pieces of that module.
* Coupling is **the degree of interaction between modules**. 
* You want high cohesion and low coupling. 高内聚, 低耦合

# 结构化的模块化

## 耦合

### 模块之间

* Connection： 
  * A connection is a reference to some label or address defined elsewhere
* 联系的复杂度 
  * 数量 
  * 程度

### 结构化的耦合

* Coupling is the measure of the **strength of association** established by a connection from one module to another
  * How complicated the connection is 
  * Whether the connection refers to the module itself or something inside it 
    * Connections that address or refer to a module as a whole by its name yield **lower coupling** than connections referring to the internal elements of another module 相比引用另一整个模块, 引用另一个模块内部的成员 的耦合性更高
  * What is being sent or received ( 六种耦合, 由低到高 )  
    * Data Coupling   数据耦合
      * Connections that pass necessary data 
    * Stamp Coupling  印记耦合
      * Connections that pass data more than necessary 
    * Control Coupling  控制耦合
      * Connections that pass data and control elements  
    * Repeat Coupling 重复耦合
    * Common Coupling  公共耦合
    * Content Coupling 内容耦合
    * Obviously Stamp Coupling couples more Data Coupling 
    * Control Coupling also couples more than data coupling
      * Information Hiding



* 耦合的程度

| 类型      | 耦合性       | 解释                                       | 例子                                                         |
| --------- | ------------ | ------------------------------------------ | ------------------------------------------------------------ |
| 内容耦合  | 最高, 到最低 | 一个模块直接修改或者依赖于另一个模块的内容 | 程序跳转GOTO; 改变另一个模块的内部数据                       |
| 公共耦合, |              | 模块之间共享全局的数据                     | 全局变量                                                     |
| 重复耦合  |              | 模块之间有同样逻辑的重复代码               |                                                              |
| 控制耦合  |              | 传递了控制信息                             | 传递"显示星期天". 传递模块和接收模块必须共享同一个内部结构和逻辑 |
| 印记耦合  |              | 共享数据结构, 但是却只用了其中的一部分     | 传递了整个记录给另一个模块, 另一个模块却只需要一个字段       |
| 数据耦合  | 最低( 最好 ) | 两个模块的所有参数是同类型的数据项         | 传递一个整数给一个计算平方根的函数                           |

## 内聚

* Ways of achieving independent modules 
* **REDUCE** relationships between elements NOT IN the same module
* **INCREASE** relationships between elements IN same module 
* **BINDING** - a measure of cohesivness



* 内聚的程度

| 类型     | 内聚性         | 解释                                                         | 例子                                                         |
| -------- | -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 偶然内聚 | 最低, 由低到高 | 模块执行多个不相干的操作                                     |                                                              |
| 逻辑内聚 |                | 模块执行一系列相关操作, 每个操作的调用由其他模块来决定       | 把下列方法放在一个模块中: 开车去, 坐火车去, 坐飞机去         |
| 时间内聚 |                | 模块执行一系列与时间有关的操作                               | 把下列方法放在一个模块中: 起床, 刷牙, 洗脸, 吃早餐           |
| 过程内聚 |                | 模块执行一系列与步骤顺序有关的操作                           | 把下列方法放在一个模块中: 守门员传球给后卫, 后卫传球给中场, 中场传球给前锋, 前锋射门 |
| 通信内聚 |                | 模块执行一系列与步骤顺序有关的操作, 并且这些操作在相同的数据上进行 | 把下列方法放在一个模块中: 查书的名字, 查书的作者, 查书的出版商 |
| 功能内聚 |                | 模块只执行一个操作或达到一个单一的目的                       | 下列内容都作为独立模块: 计算平方根, 决定最短路径, 压缩数据   |
| 信息内聚 | 最高(最好)     | 模块进行许多操作, 各个都有各自的入口点, 每个操作的代码相对独立, 而且所有操作都在相同的数据结构上完成 | 比如栈. 它包含相应的数据结构和操作. 所有的操作都是针对相同的数据结构 |





## 思想的应用

* 低耦合处理 
  * 软件体系结构的分层设计中:
    * 不同层的模块之间仅能通过程序调⽤与数据传递实现交互,**不能共享数据**(例如 `Model` 层建⽴⼀个数据对象并将引⽤传递给 `Logic `层使⽤)否则会导致公共耦合。
    
  * 软件体系结构的逻辑包设计中:

    * 依据功能的特点将三个层次进⼀步划分为更小的包,⽽不是只使⽤ `Presentation`、 `Logic `和 `Model` 三个包,可以通过包分割实现接⼝最⼩化,这能去除不必要的耦合。

  * 软件体系结构的物理包设计中: 

  	* 将不同包的重复内容独⽴为单独的包以消除重复,避免产⽣隐式的重复耦合;

  * 详细设计中对象创建者的选择:

    * 如果两个对象 A、B 间已有⽐较⾼的耦合度了, 那么使⽤ A 创建 B 或者反之就不 会带来额外的耦合度。这就是表 12-4 内容的核 ⼼思想——不增加新的耦合。

    

  * 详细设计中选择控制⻛格:

  * 解除界⾯与逻辑对象的直接耦合。

    

* ⾼内聚处理 
  * 软件体系结构的分层设计中: 
    * 三个层次都是⾼内聚的,⼀个处理交互任务, ⼀个处理业务逻辑,⼀个处理数据持久化。
  * 软件体系结构的逻辑包设计中: 
    * 将三个层次进⼀步划分为更⼩的包,可以实 现每个更⼩的包都是⾼内聚的。
  * 详细设计中抽象类的职责: 
    * 要求状态与⽅法紧密联系就是为了达到⾼内聚 (信息内聚)。
  * 详细设计中使⽤控制⻛格:
    * 控制⻛格分离了控制逻辑,可以实现业务逻辑对 象的⾼内聚(功能内聚)。因为封装了控制逻辑,所以控制器对象承载了不 可避 免的顺序内聚、通信内聚和逻辑内聚,这就要求控制器对 象必须是受控的,也是它们为什么倾向于对外委托⽽不是⾃⼰进⾏业 务计算的原因。

# 结构化的信息隐藏

## Module Guide

### 模块的主要秘密 

主要秘密描述的是这个模块所要实现的**⽤户需求**。是设计者对⽤户需求的 实现的⼀次**职责分配**。有了这个描述以后，我们可以利⽤它检查我们是否 完成所有的⽤户需求，还可以利⽤它和需求优先级来决定开发的次序

### 模块的次要秘密 

次要秘密描述的是这个模块在实现职责时候所涉及的具体的**实现细节**。包 括数据结构，算法，硬件平台等信息。

### 模块的⻆⾊ 

描述了独⽴的模块在整个系统中所承担的⻆⾊，所起的作⽤。以及与哪 些模块有相关联的关系。

### 模块的对外接⼝

模块提供给别的模块的接⼝。

## 思想的应用

* 信息隐藏处理 
  * 在软件体系结构设计的分层设计中:
    * 经验表明软件系统的界⾯是最经常变化的, 其次是业务逻辑,最稳定的是业务数 据。这就是分层⻛格建⽴ `Prensentation`、 `Logic` 和 `Model `三个层次的原因,它 们体现了决策变化的划分类型,它们之间的 依赖关系符合各⾃的稳定性。
  * 在软件体系结构设计的逻辑包设计中:
    * 消除重复可以避免重复耦合,同时可以 避免同⼀个设计决策出现在多个地⽅—— 这意味着该决策没有被真正地隐藏 (这也是控制耦合⽐数据耦合差的原因)。
  * 在软件体系结构设计的物理包设计中:
    * 建⽴独⽴的安全包、通信包和数据库连接包,是为了封装各⾃的设计决策——安全处理、网络通信与数据库处理。
  * 在软件体系结构设计与详细设计中: 
    * 严格要求定义模块与类的接⼝,可以便利开发,更是为了实现信息隐藏。
  * 在详细设计中使⽤控制⻛格:
    * 专⻔⽤控制器对象**封装关于业务逻辑的设计决策**, ⽽不是将其拆散分布到整个对象⽹络中 去

