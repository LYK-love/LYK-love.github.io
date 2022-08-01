---
title: Coupling && Cohension
tags: Software Engineering Methodology
categories: Software Engineering
date: 2021-06-27 11:09:16
---

Outline:

* 耦合
* 内聚
* 耦合和内聚的度量

<!--more-->

本文所引用的设计原则参见 *Design Patterns*



> we want high cohesion and low coupling. 高内聚, 低耦合

# Coupling 

Coupling: the measure of **the strength** of association established by a connection from one module to another 耦合是对模块间联系的度量

* How complicated the connection is 
* Whether the connection refers to the module itself or something inside it 
  * Connections that address or refer to a module as a whole by its name yield **lower coupling** than connections referring to the internal elements of another module 相比引用另一整个模块, 引用另一个模块内部的成员 的耦合性更高

* 在结构化编程中，耦合是对某个标签或者地址的引用： A connection is a reference to some label or address defined elsewhere 

* 在面向对象编程中，按照模块的访问逻辑耦合可分为：

  * Component coupling （访问耦合）：模块间的依赖关系
  * Inheritance coupling （继承耦合）：模块间的继承关系（以及实现等等）

  

  

  

  

  

## Types of Coupling 

六种耦合, 由低到高（耦合性越低越好） ：

| 类型      | 耦合性       | 解释                                       | 例子                                                         |
| --------- | ------------ | ------------------------------------------ | ------------------------------------------------------------ |
| 内容耦合  | 最高（最坏） | 一个模块直接修改或者依赖于另一个模块的内容 | 程序跳转GOTO; 改变另一个模块的内部数据                       |
| 公共耦合, |              | 模块之间共享全局的数据                     | 全局变量                                                     |
| 重复耦合  |              | 模块之间有同样逻辑的重复代码               |                                                              |
| 控制耦合  |              | 传递了控制信息                             | 传递"显示星期天". 传递模块和接收模块必须共享同一个内部结构和逻辑 |
| 印记耦合  |              | 共享数据结构, 但是却只用了其中的一部分     | 传递了整个记录给另一个模块, 另一个模块却只需要一个字段       |
| 数据耦合  | 最低( 最好 ) | 两个模块的所有参数是同类型的数据项         | 传递一个整数给一个计算平方根的函数                           |

## 



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

## 访问耦合

### Principles of Component Coupling

降低访问耦合的设计原则：

* Global Variables Consider Harmful

* To be Explicit
* Don’t repeat
* Programming to Interface 

* Programming to Required Interface, not only Suffered Interface

* **Design by Contract** 
  * Contract of Module/ Class 
    * Required methods / Provided methods

  * Contract of Methods
    * `PreCondition` , `PostCondition`, `Invariant`

* **Interface Segregation Principle(ISP)**



*  Programming to Simpler Interface
*  Many client-specific interfaces are better than one general purpose interface **把接口变小**

* **The Law of Demeter**

## 继承耦合

### Principles of Inherit Coupling

* Liskov Substitution Principle （LSP）
* Favor Composition Over Inheritance



# Cohension



Cohension： 模块内部各个元素彼此结合的紧密程度的度量



## Types of Cohension

从低到高：

| 类型     | 内聚性     | 解释                                                         | 例子                                                         |
| -------- | ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 偶然内聚 | 最低       | 模块执行多个不相干的操作                                     |                                                              |
| 逻辑内聚 |            | 模块执行一系列相关操作, 每个操作的调用由其他模块来决定       | 把下列方法放在一个模块中: 开车去, 坐火车去, 坐飞机去         |
| 时间内聚 |            | 模块执行一系列与时间有关的操作                               | 把下列方法放在一个模块中: 起床, 刷牙, 洗脸, 吃早餐           |
| 过程内聚 |            | 模块执行一系列与步骤顺序有关的操作                           | 把下列方法放在一个模块中: 守门员传球给后卫, 后卫传球给中场, 中场传球给前锋, 前锋射门 |
| 通信内聚 |            | 模块执行一系列与步骤顺序有关的操作, 并且这些操作在相同的数据上进行 | 把下列方法放在一个模块中: 查书的名字, 查书的作者, 查书的出版商 |
| 功能内聚 |            | 模块只执行一个操作或达到一个单一的目的                       | 下列内容都作为独立模块: 计算平方根, 决定最短路径, 压缩数据   |
| 信息内聚 | 最高(最好) | 模块进行许多操作, 各个都有各自的入口点, 每个操作的代码相对独立, 而且所有操作都在相同的数据结构上完成 | 比如栈. 它包含相应的数据结构和操作. 所有的操作都是针对相同的数据结构 |





## Principles of Cohension

* Single Responsibility Principle( SRP )

# 耦合和内聚的度量

## Coupling Metrics 

模块间耦合性度量

### Coupling between object classes (CBO) 

对象类之间的耦合

* 一个类合作（即相关）的数量。当CBO增大时，不仅降低了可重用性，而且使其修改和修改后的测试变得复杂。所以，每个类的CBO值应当保持合理。这与在传统软件中减少耦合的一般原则是一致的。

* A count of the number of other classes: 访问本类或者含有被本类访问的方法或变量的其他类. ( 不包括继承 )
  *  which access a method or variable in this class, or 
  *  contain a method or variable accessed by this class 
  *  Not including Inheritance 
* Want to keep this low

### Data abstraction coupling (DAC) 

数据抽象耦合

*  The number of attribute having an ADT type dependent on the definitions of other classes 拥有<u>依赖于其他类的ADT</u>的属性的数量

*  Want to keep this low

### Ce and Ca (efferent and afferent coupling) 

传出耦合和传入耦合

* Ca: 传入耦合
  * The number of classes outside this category that depend upon classes within this category. 外部的依赖于这个category内部的类的类的数量

* Ce: 传出耦合
  * The number of classes inside this category that depend upon classes outside this category 这个category内部的依赖于外部类的类的数量
* Want to keep these low 

### Depth of the Inheritance tree (DIT) 

继承树深度

* the maximum length from the node to the root of the tree 这个类的节点到继承树根节点的最大距离

* as `DIT` grows, it becomes difficult to predict behavior of a class because of the high degree of inheritance DIT越大,这个类离根节点越远,类的行为就难以预测

* Positively, large DIT values imply that many methods may be reused

  好消息是, DIT越大, 意味着越多可重用的方法

### Number of children (NOC) 

子女数

* count of the subclasses immediately subordinate to a class  就是直接隶属于该节点的节点数
* as NOC grows, reuse increases `NOC`越大,重用越频繁
* as NOC grows, abstraction can become diluted `NOC`越大, 抽象性就越被稀释
* increase in NOC means the amount of testing will increase `NOC`增大意味着更多的测试

## Cohesion Metrics

模块内聚性度量

### Lack of cohesion in methods (LCOM)

* Definition:

一个类内的每种方法访问一个或多个属性（也称实例变量）。LCOM是访问一个或多个相同属性方法的数量。

```
Class Ck with n methods M1,…Mn

Ij is the set of instance variables used by Mj

There are n such sets I1 ,…, In

P = {(Ii, Ij) | (Ii ∩ Ij ) =  ∅} //P是访问一个类中不同属性的方法的度量, P越大, 内聚性越差

Q = {(Ii, Ij) | (Ii ∩ Ij ) ≠  ∅} //Q是访问一个类中相同属性的方法的度量,Q越大, 说明类中这样的方法越多, 内聚性越好

If all n sets Ii are ∅ then P = ∅

LCOM = |P| – |Q|, if |P| > |Q|

LCOM = 0 otherwise
```





* Want to keep this low 
* Many other versions of LCOM have been defined
* If `LCOM `>=1, then the class should be separated
