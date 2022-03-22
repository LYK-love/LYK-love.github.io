---
title: Modularity in OO
tags: Software Engineering Methodology
categories: Software Engineering
date: 2021-06-27 11:09:16
---


# 面向对象中的访问与耦合

**Structural methods vs OO methods in Coupling**

<!--more-->

* Coupling 

  * Coupling is the measure of the strength of association established by a connection from one module to another `耦合`是对模块间练习的度量

* Structural methods  结构化. 耦合`是对某个标签或者地址的引用

  * A connection is a reference to some label or address defined elsewhere 

* OO methods 面向对象

  * Component coupling （访问耦合） 
  * Inheritance coupling （继承耦合）

* 降低耦合的设计原则

  

# 访问耦合

## Principles of Component Coupling

降低访问耦合的设计原则

### Global Variables Consider Harmful

### To be Explicit

### Don’t repeat

### Programming to Interface 



* Programming to Required Interface, not only Suffered Interface
* **Design by Contract** 
  * Contract of Module/ Class 
    * Required methods / Provided methods
* Contract of Methods
  * `PreCondition` , `PostCondition`, `Invariant`

### Interface Segregation Principle(ISP)

接口分离原则

**Principles of Component Coupling**

*  Programming to Simpler Interface
*  Many client-specific interfaces are better than one general purpose interface 把接口变小

### The Law of Demeter

* You can play with yourself. 
* You can play with your own toys, but you can't take them apart 
* You can play with toys that were given to you. 
* You can play with toys you've made yourself.

# 继承耦合

## Principles of Inherit Coupling

### Liskov Substitution Principle (LSP)

“All derived classes must be substitutable for their base class” — *Barbara Liskov, 1988*
“Functions that use pointers or references to base classes must
be able to use objects of derived classes without knowing it.” — *R. Martin, 1996*

* LSP is about Semantics and Replacement 
  * Understand before you design
    * The meaning and purpose of every method and class must be clearly documented
    * Lack of user understanding will induce de facto violations of LSP
  * Replaceability is crucial 
    * Whenever any class is referenced by any code in any system, 
    * any future or existing subclasses of that class must be 100% replaceable

### LSP Summary

* Design by Contract 

* Advertised Behavior of an object: 

  * advertised Requirements (Preconditions) 

  * advertised Promises (Postconditions)

* Derived class services should **require no more and promise no less**

### Favor Composition Over Inheritance

* Favor Composition Over Inheritance 
* Use inherit for polymorphism 
* Use delegate not inherit to reuse code!

**Coad's Rules of Using Inheritance**

* Use inheritance only when all of the following criteria are satisfied: 
  *  A subclass expresses "is a special kind of" and not "is a role played by a"
  *  An instance of a subclass never needs to become an object of another class
  *  **A subclass extends, rather than overrides or nullifies, the responsibilities of its superclass**
  *  A subclass does not extend the capabilities of what is merely an utility class

## 内聚

### Single Responsibility Principle( SRP )

"A class should have only one reason to change"  — Robert Martin

* Class should have only one reason to change 
  *  Cohesion of its functions/responsibilities

* Several responsibilities 
  * mean several reasons for changes → more frequent changes 一个类职责越多，就越更改频繁。
* Sounds simple enough 
  * Not so easy in real life 
  * Tradeoffs with complexity, repetition, opacity（不透明性）

# 耦合和内聚的度量

## Coupling Metrics between classes

耦合性度量

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

## Measure class cohesion

内聚性度量

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
