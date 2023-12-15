---
categories: Computer Science
date: 2022-06-12 01:07:46
tags:
- Software Engineering Methodology
title: Design Principle
---

Outline：

* 单一职责原则
* 开闭原则
* 里氏代换原则
* 依赖倒转原则 
* 接口隔离原则 
* 合成复用原则 
* 迪米特法则

<!--more-->

# 单一职责原则

Single Responsibility Principle， aka `SRP`

> *"A class should have only one reason to change"  — Robert Martin*
>
> 一个对象应该只包含单一的职责，并且该职责被完整地封装在一个类中

* 一个类职责越多，就越更改频繁
  * 类的职责见*Modularity*

# 开闭原则

Open-Closed Principle, aka `OCP`

> 一个软件实体应该对扩展开放，对修改关闭。软件实体可以是一个软件模块、一个由多个类组成的局部结构或一个单独的类。



* Be open for extension 

  * module's behavior can be extended
* Be closed for modification 

  * source code for the module must not be changes
* RTTI is Ugly and Dangerous! 
  * RTTI = Run-Time Type Information 执行时期的类型信息
  * If a module tries to dynamically cast a base class pointer to several derived classes, any time you extend the inheritance hierarchy, you need to change the module 将一个多态指针转换为其实际指向对象的类型。 
  * 破坏了面向对象的纯洁性
  * recognize them by type switch or if-else-if structures
* 开闭原则是对单一职责原则的加强

# 里氏代换原则

Liskov Substitution Principle, aka `LSP`

> *“All derived classes must be substitutable for their base class” — *Barbara Liskov, 1988*
>
> *“Functions that use pointers or references to base classes must be able to use objects of derived classes without knowing it.” — *R. Martin, 1996*
>
> 所有引用基类(父类)的地方必须能透明地使用其子类的对象



* 通俗表达: 软件中如果能够使用基类对象，那么一定能够使用其子类对象

* 里氏代换原则是开闭原则的具体实现

* LSP is about Semantics and Replacement 

  * Understand before you design
    * The meaning and purpose of every method and class must be clearly documented
    * Lack of user understanding will induce de facto violations of LSP
  * Replaceability is crucial 
    * Whenever any class is referenced by any code in any system, 
    * any future or existing subclasses of that class must be 100% replaceable

  

* LSP Summary:

  * Design by Contract 
  * Advertised Behavior of an object: 

    * advertised Requirements (Preconditions) 

    * advertised Promises (Postconditions)

  * Derived class services should **require no more and promise no less**

# 依赖倒转原则 

Dependency Inversion Principle, aka `DIP`

> 高层模块不应该依赖于低层模块，他们都应该依赖抽象。抽象不应该依赖于细节，细节应该依赖于抽象。

* 另一种表述:要针对接口编程，而不要针对实现编程

* 依赖倒转原则是开闭原则的具体实现

# 接口隔离原则

Interface Segregation Principle, aka `ISP`

> 客户不应该依赖那些它不需要的接口

* 在接口拆分时需要满足单一职责原则

# 合成复用原则

Composite Reuse Principle， aka `CRP`

> 在系统中应该尽量多实用组合聚合关联关系，尽量少甚至不使用继承关系

# 迪米特法则

Law of Demter

> 在一个软件实体对其他实体的引用越少越好，或者说如果两个类不必彼此直接通信，那么这两个类就不应当发生直接的相互作用，而是通过引入一个第三者发生间接交互



* You can play with yourself. 
* You can play with your own toys, but you can't take them apart 
* You can play with toys that were given to you. 
* You can play with toys you've made yourself.

# 组合大于继承

* Favor Composition Over Inheritance 
* Use inherit for polymorphism 
* Use delegate not inherit to reuse code!

**Coad's Rules of Using Inheritance**

* Use inheritance only when all of the following criteria are satisfied: 
  *  A subclass expresses "is a special kind of" and not "is a role played by a"
  *  An instance of a subclass never needs to become an object of another class
  *  **A subclass extends, rather than overrides or nullifies, the responsibilities of its superclass**
  *  A subclass does not extend the capabilities of what is merely an utility class