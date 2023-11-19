---
title: Design Pattern
tags: Software Engineering
categories: Computer Science
date: 2022-03-15 12:00:00
---



Outline:

* 类之间的关系
* 组合 > 继承
* Design Pattern
* 设计模式：创建型
* 设计模式： 结构型
* 设计模式：行为型



ref： 软件系统设计 --- 潘敏学； [Design Pattern Turotial](https://refactoring.guru/design-patterns/creational-patterns)

<!--more-->

#  类之间的关系

ref: https://www.jianshu.com/p/d1d45efcfac1

## 泛化(Generalization）

> 泛化表示一个更泛化的元素和一个更具体的元素之间的关系。泛化是用于对`继承`进行建模的`UML元素`。在Java中，用`extends`关键字表示。

**表示方式：**用实线空心箭头表示。

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/generalization)

 

## 实现(Realization)

> 实现是一种`类与接口`的关系，表示类是接口所有特征和行为的实现，在程序中一般通过`类实现接口`来描述。

**表示方式：**用虚线空心三角形箭头表示，实现类指向接口。

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/realization) 

## 依赖(Dependency)

>  是一种`使用`的关系，即一个类的实现需要另一个类的协助。在Java中，方法参数需要传入另一个类的对象，就表示依赖这个类。

**表示方式：**虚线箭头。

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/dependency)

**注意：**类A需要用到类B，类A指向类B。



```java
public class Student {
	public void read(Book book){
		System.out.println("读的书是：" + book.getName());
	}
	
	public void eat(Food food){
		System.out.println("吃的是：" + food.getName());
	}
}
```

## 关联(Association)

> 表示类与类之间的联接,它使一个类知道另一个类的属性和方法，这种关系比依赖更强、不存在依赖关系的偶然性、关系也不是临时性的，一般是长期性的。通常是将一个类的对象作为另一个类的成员变量.
>
> 在Java中，一个类的全局变量引用了另一个类，就表示关联了这个类

**表示方式：**实线箭头。

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/association)

**注意：**类A中用到类B属性，类A指向类B。

## 聚合(Aggregation)

> 概念：聚合是关联关系的一种，是强的关联关系。聚合是整体和个体之间的关系，即**has-a**的关系，整体与个体可以具有各自的生命周期，部分可以属于多个整体对象，也可以为多个整体对象共享。聚合和关联关系在语法上是一致的，只能从语义来区分

**表示方式：**尾部为空心菱形的实线箭头（也可以没箭头）

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/aggragation)



**注意：**类A中用到类B属性，类A指向类B。

 ```java
 public class People{
 	private Student student;
 	private Worker worker;
 	private Farmer farmer;
 
 	public People(Student student, Worker worker, Farmer farmer){
 		this.student = student;
 		this.worker = worker;
 		this.farmer = farmer;
 	}
 }
 ```



 

## 组合(Composition)

> 组合也是关联关系的一种。组合是一种整体与部分的关系，即contains-a的关系，比聚合更强。部分与整体的生命周期一致，整体的生命周期结束也就意味着部分的生命周期结束，组合关系不能共享。程序中组合和关联关系是一致的，只能从语义级别来区分。

**表示方式：**尾部为实心菱形的实现箭头（也可以没箭头）。

![img](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/composition)

**注意：**Head是Dog的一部分，Dog指向Head。

```java
public class Bird{
	private Wing wing;

	public People(){
		wing = new Wing();
}
```



# 组合 > 继承

* Expert designers know not to solve every problem from first principles, they reuse solutions : **"不要造轮子"**
* **HAS-A can be better than IS-A**
  1.  Composition gives you a lot more flexibility.
  2. Not only does it let you encapsulate a family of
     algorithms into their own set of classes, but it
     also lets you change behavior at runtime.
* 与继承关系相比，组合的主要优势在于不会破坏类的封装性，而且**继承是一种耦合度较大的静态关系，无法在程序运行时动态扩展**。在软件开发阶段，组合关系虽然不会比继承关系减少编码量，但是到了软件维护阶段，由于关联关系使系统具有较好的**松耦合性**，因此使得**系统更加容易维护**。当然，组合的缺点是**比继承关系要创建更多的对象**

# Design Pattern

> **设计模式(Design Pattern)**是**一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结**

基本要素：

1. 模式名称 (Pattern name)
2. 问题 (Problem)
3. 解决方案 (Solution)
4. 效果 (Consequences)

## Types

* 根据其目的(模式是用来做什么的)可分为创建型(Creational)，结构型(Structural)和行为型(Behavioral)三种：
  1. 创建型模式主要用于创建对象。
  2. 结构型模式主要用于处理类或对象的组合。
  3. 行为型模式主要用于描述对类或对象怎样交互和怎样分配职责。

* 根据范围，即模式主要是用于处理类之间关系还是处理对象之间的关系，可分为类模式和对象模式两种：
  1. 类模式处理类和子类之间的关系，这些关系通过继承建立，在编译时刻就被确定下来，是静态的
  2. 对象模式处理对象间的关系，这些关系在运行时刻变化，是动态的

![Design Pattern Classification](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Design%20Pattern%20Classification.png)

* 注： 模板方法为什么是行为性模式? 答案：子类控制父类的行为



# Creationnal  Patterns

## Singleton

太简单，不介绍了



## Simple Factory



策略模式解决**行为问题**, 而工厂模式解决**对象创建问题**

![image-20220315145604053](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/simple%20factory%20pattern)

### 模式结构

* Factory：  工厂角色
* Product：抽象产品
* ConcreteProduct： 具体产品角色



### 示例

![image-20220315145955575](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/simple%20factory%20user_manager)

简单工厂模式的缺点

* 当有新产品要加入到系统中时,必须修改工厂类,加入必要的处理逻辑,这违背了“开闭原则”

## Factory Method

> 在工厂方法模式中,核心的工厂类不再负责所有产品的创建,而是将具体创建工作交给子类去做。这个核心类仅仅负责给出具体工厂必须实现的接口,而不负责哪一个产品类被实例化这种细节,这使得**工厂方法模式可以在不修改工厂角色的情况下引进新产品**

![image-20220315150329091](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/factory%20method%20pattern)



###  code

抽象工厂类代码:

```java
public abstract class PayMethodFactory
{
	public abstract AbstractPay getPayMethod();
}
```



具体工厂类代码：

```java
public class CashPayFactory extends PayMethodFactory
{
	public AbstractPay getPayMethod()
	{
		return new CashPay();
	}
}
```



 客户类代码片段:

```java
PayMethodFactory factory;
AbstractPay payMethod; //在定义工厂和产品时都必须使用抽象层
factory=new CashPayFactory();
payMethod =factory.getPayMethod();
payMethod.pay();
```

为了提高系统的可扩展性和灵活性,在**定义工厂和产品时都必须使用抽象层**,如果需要更换产品类,只需要更换对应的工厂即可,其他代码不需要进行任何修改。

### 示例

![image-20220315150923939](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/factory%20method%20pattern%20logger)

### 优点

* 很好地符合了“开闭原则”

### 缺点

* 添加新产品时，不仅要添加新的产品类，还要添加对应的具体工厂类，增加系统的复杂度



## Abstract Factory

> 抽象工厂模式(Abstract Factory Pattern):提供一个创建一系列相关或相互依赖对象的接口,而无须指定它们具体的类。抽象工厂模式又称为Kit模式,属于**对象创建型模式**





![image-20220315151244481](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/abstract%20factory%20pattern)

### 概念 

* **产品等级结构**： 即产品的继承结构。 如抽象类是电视机， 而子类有海信电视机， TCL电视机， 则抽象电视机与具体品牌的电视机构成了一个产品等级结构
* **产品族**：由同一个工厂生产的，位于不同产品等级结构中的一组产品。 如海尔是一个产品族， 海尔电视机属于电视机产品结构， 电冰箱位于电冰箱产品结构

### 模式结构

* AbstractFactory
* AbstractProduct
* Product

## 模式分析

* 抽象工厂模式与工厂方法模式的区别：工厂方法模式针对的是一个产品等级结构，而抽象工厂模式则需要面对多个产品等级结构

### code

抽象工厂类：

```java
public abstract class AbstractFactory
{
	public abstract AbstractProductA createProductA();
	public abstract AbstractProductB createProductB();
}
```



具体工厂类：

```java
public class ConcreteFactory1 extends AbstractFactory
{
	public AbstractProductA createProductA()
	{
		return new ConcreteProductA1();
	}
	public AbstractProductB createProductB()
	{
		return new ConcreteProductB1();
	}
}
```



### 示例

产品结构为：

![image-20220315151837764](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/abstract%20factory%20method%20text%20%20and%20button)



抽象工厂模式：

![image-20220315151810392](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/abstract%20factory%20method%20text%20and%20button%20realization.png)



### 优点

* 增加或者替换产品族比较方便

### 缺点：

* 增加新的产品等级结构需要修改抽象工厂和所有的具体工厂类，**对“开闭原则”的支持呈现倾斜性**

## Builder

> 建造者模式可以**将一个复杂对象的构建与它的表示分离**,使得**同样的构建过程可以创建不同的表示**.将部件和其组装过程分开,**一步一步创建一个复杂的对象**
>
> 是一种对象创建型模式

![image-20220308144855351](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/builder%20pattern.png)



### 模式结构

* Builder:抽象建造者
* ConcreteBuilder:具体建造者
* Directo: :指挥者. 一方面它隔离了客户与生产过程;另一方面它负责控制产品的生成过程
* Product:产品角色

### code

抽象建造者:

```java
public abstract class Builder
{
	protected Product product=new Product();
	public abstract void buildPartA();
	public abstract void buildPartB();
	public abstract void buildPartC();
}

public Product getResult()
{
	return product;
}
```



Director:

```java
public class Director
{
	private Builder builder;
}

public Director(Builder builder)
{
	this.builder=builder;
}

public void setBuilder(Builder builder)
{
	this.builder=builer;
}

public Product construct()
{
	builder.buildPartA();
	builder.buildPartB();
	builder.buildPartC();
	return builder.getResult();
}
```



client:

```java
Builder builder = new ConcreteBuilder();
Director director = new Director(builder);
Product product = director.construct();
```

在客户端代码中,无须关心产品对象的具体组装过程， **只需确定具体建造者的类型**,建造者模式将复杂对象的构建与对象的表现分离开来,这样使得同样的构建过程可以创建出不同的表现



### 示例

KFC套餐,这里省略了抽象建造者

![Builder Pattern KFC example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Builder%20Pattern%20KFC%20example.png)

### 优点

* client不必知道产品的创建过程，**将产品本身与产品的创建过程解耦**
* <u>可以更加精细地控制产品的创建过程</u>
* 增加新的具体建造者无须修改原有类库的代码，指挥者类针对抽象建造者类编程，系统扩展方便，**符合“开闭原则”**

### 缺点

* 建造者模式所创建的产品一般具有较多的共同点,其组成部分相似,如果产品之间的差异性很大,则不适合使用建造者模式,因此其<u>使用范围受到一定的限制</u>
* 如果产品的内部变化复杂,可能会导致需要定义很多具体建造者类来实现这种变化,导致系统变得很庞大。

### 模式简化

* 省略抽象建造者角色: 如果系统中只需要一个具体建造者的话,可以省略掉抽象建造者。
* 省略指挥者角色: 在具体建造者只有一个的情况下,如果抽象建造者角色已经被省略掉,那么还可以省略指挥者角色,让Builder角色扮演指挥者与建造者双重角色。

## Prototype

> 原型模式(Prototype Pattern): 用原型实例指定创建对象的种类,并且通过复制这些原型创建新的对象。原型模式允许一个对象再创建另外一个可定制的对象,无须知道任何创建的细节
>
> 是一种对象创建型模式

![image-20220308152010781](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/prototype%20pattern.png)

### 模式结构

* Prototype:抽象原型类
* ConcretePrototype:具体原型类
* Client



一般而言,`clone()`方法满足:

* 对任何的对象x,都有`x.clone() !=x`,即克隆对象与原对象不是同一个对象。
* 对任何的对象x,都有`x.clone().getClass()==x.getClass()`,即克隆对象与原对象的类型一样。
* 如果对象x的equals()方法定义恰当,那么`x.clone().equals(x)`应该成立



Java提供的`clone()`方法默认是浅拷贝，可以override该方法实现不完全的深拷贝

* 要实现彻底的深拷贝是非常困难的

### 优点

* 可以快速创建很多相同或相似的对象，简化对象的创建过程，还可以保存对象的一些中间状态；

### 缺点

* 需要为每一个编写`clone()`，因此对已有类进行改造时，需要修改其源代码，违反了开闭原则
* 在实现深克隆时需要编写较为复杂的代码
  * 事实上几乎不存在完全的深拷贝，这要考虑到底层对象复杂的引用关系

### 适用环境

* <u>创建新对象成本较大</u>，新的对象可以通过原型模式对已有对象进行复制来获得；
* 系统要<u>保存对象的状态</u>，而对象的状态变化很小；
* 需要避免使用分层次的工厂类来创建分层次的对象，并且类的实例对象只有一个或很少的几个组合状态，<u>通过复制原型对象得到新实例可能比使用构造函数创建一个新实例更加方便</u>



# Structural Patterns

## Adatpter

> 适配器模式(Adapter Pattern) :将一个接口转换成客户希望的另一个接口,适配器模式使接口不兼容的那些类可以一起工作,其别名为包装器(Wrapper)。适配器模式**既可以作为类结构型模式,也可以作为对象结构型模式**
>
> 
>
> 在适配器模式中可以定义一个包装类,包装不兼容接口的对象,这个包装类指的就是适配器(Adapter),它所包装的对象就是适配者
> (Adaptee),即被适配的类
>
> 
>
> 适配器提供客户类需要的接口,适配器的实现就是把客户类的请求转化为对适配者的相应接口的调用。也就是说:当客户类调用适配器的方法时,在适配器类的内部将调用适配者类的方法,而这个过程对客户类是透明的,客户类并不直接访问适配者类。因此,适配器可以使由于接口不兼容而不能交互的类可以一起工作。这就是适配器模式的模式动机



模式结构：

* Target:  目标抽象类， 即
* Adapter： 适配器类
* Adaptee： 适配者类
* Client





### 类适配器

![Class Adapter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Class%20Adapter.png)

* Adapter多继承， 同时继承Target和Adaptee, 这需要语言支持多继承。
* 如果语言不支持多继承， 那么如果Target是接口的话，也可以选择<u>继承Adaptee,实现Target</u>



```java
public class Adapter extends Adaptee implements Target
{
	public void request()
	{
		specificRequest();
	}
}
```



### 对象适配器



![Object Adapter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Object%20Adapter.png)

* 不是继承`Adaptee`类，而是持有`Adaptee`的实例，以解决兼容性的问题。即持有`Adaptee`类，实现`Target`接口，完成`Adaptee—>Target`的适配
* 缺点是难以置换Aaptee的方法





```java
public class Adapter extends Target
{
	private Adaptee adaptee;
	public Adapter(Adaptee adaptee)
	{
		this.adaptee=adaptee;
	}
    
    public void request()
	{
		adaptee.specificRequest();
	}
}
```



### 优点

将目标类和适配者类解耦，通过引入一个适配器类来重用现有的适配者类，而无须修改原有代码。



增加了类的透明性和复用性，将具体的实现封装在适配者类中，对于客户端类来说是透明的，而且提高了适配者的复用性。



灵活性和扩展性都非常好，通过使用配置文件，可以很方便地更换适配器，也可以在不修改原有代码的基础上增加新的适配器类，完全符合“开闭原则’



由于适配器类是适配者类的子类，因此可以在适配器类中置换一些适配者的方法，使得适配器的灵活性更强

### 缺点

对于Java、C#等不支持多重继承的语言，使用有局限

### 默认适配器模式

> 默认适配器模式(Default Adapter Pattern)或缺省适配器模式:
>
> 当不需要全部实现接口提供的方法时，可先设计一个抽象类实现接口，并为该接口中每个方法提供一个默认实现(空方法)，那么该抽象类的子类可有选择地覆盖父类的某些方法来实现需求，它适用于一个接口不想使用其所有的方法的情况。因此也称为单接口适配器模式

![Default Adapter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Default%20Adapter.png)

### 双向适配器模式

> 在对象适配器的使用过程中，如果在适配器中同时包含对目标类和适配者类的引用，适配者可以通过它调用目标类中的方法，目标类也可以通过它调用适配者类中的方法，那么该适配器就是一个双向适配器



![Bio Adapter](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Bio%20Adapter.png)





## Composite

> 组合模式(Composite Pattern): 组合多个对象形成树形结构以表示“整体部分”的结构层次。组合模式对单个对象(即叶子对象)和组合对象(即容器对象)的使用具有一致性
>
> 又称为“整体部分”(Part-Whole)模式，
>
> 属于**对象的结构模式**，它将对象组织到树结构中,可以用来描述整体与部分的关系



### 模式动机

* 对于树形结构，当容器对象(如文件夹)的某一个方法被调用时，将遍历整个树形结构，寻找也包含这个方法的成员对象(可以是容器对象，也可以是叶子对象，如子文件夹和文件)并调用执行(递归调用)
* 由于容器对象和叶子对象在功能上的区别，在使用这些对象的客户端代码中必须有区别地对待容器对象和叶子对象，而实际上大多数情况下客户端希望一致地处理它们，因为对于这些对象的区别对待将会使得程序非常复杂
* 组合模式描述了如何将容器对象和叶子对象进行**递归组合**，使得用户在使用时无须对它们进行区分，可以一致地对待容器对象和叶子对象
* 事实上，Leaf类不可能实现Component类的`operation()`之外的方法，这样毫无意义。 因此**组合模式分为两种**：
  * 透明组合模式：把Leaf和Composite看成一个东西，Component类的所有方法都是抽象方法， 则Leaf必须实现所有这些方法
    * 好处：对Client而言， Leaf和Composite没有区别，可以直接针对Component抽象类编程
    * 坏处：Leaf的`operation()`之外的方法全都是无用方法，Leaf对这些方法的实现基本就是抛出异常。Client“透明”地处理Component时，（因为有Leaf存在）要么处理异常， 要么就用RTTI判断对象的实际类型，没有安全性，事实上也不可能透明
    * 因此，透明组合模式就是个笑话
  * 安全组合模式：Component是一个**接口**，仅拥有抽象方法`operation（）`。 Composite和Leaf都实现Component接口，这样这两个子类的行为就是合理的
    * 优点：Leaf和Composite的行为是合理的
    * 缺点：Leaf和Composite是两个不同的类型，使用的时候无法面向Component编程，即对Client不够透明
    * 推荐使用安全组合模式

### 模式结构

* Component: 抽象构件

  * client针对`Component`进行编程，无须知道它到底表示的是叶子还是容器，可以对其进行统一处理

  * 容器对象中既可以包含叶子，也可以包含容器，以此实现递归组合，形成一个树形结构
  * 抽象父类` Component`中，只有`operation （）`是抽象方法，其他方法都要提供实现， 否则Leaf类就要实现这些方法了（这是不可能的）
* Leaf:叶子构件
* Composite:容器构件
* Client:客户类

### 模式分析

- 组合模式的关键是定义了一个<u>抽象构件类</u>，它**既可以代表叶子，又可以代表容器**，而客户端针对该抽象构件类进行编程，<u>无须知道它到底表示的是叶子还是容器，可以对其进行统一处理</u>
- 同时容器对象与抽象构件类之间还建立了聚合关系，容器对象既可以包含叶子，也可以包含容器，以此实现递归组合，形成树形结构

### 透明组合模式

![Transparent Composite](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Transparent%20Composite.png)

Component：

```java
public abstract class Component //Leaf类必须实现所有抽象方法
{
	public abstract void add(Component c);
	public abstract void remove(Component c);
	public abstract Component getChild(int i);
	public abstract void operation();
}
```



Leaf:

```java
public class Leaf extends Component
{
	public void add(Component c) //这些方法都是无意义的，只能抛个异常
	{ //异常处理或错误提示 }
        
	public void remove(Component c)
	{ //异常处理或错误提示 }
        
    public Component getChild(int i)
	{ //异常处理或错误提示 }

    public void operation()
	{
		//实现代码
	}
}
```





### 安全组合模式

在Java AWT中使用了安全组合模式



![Composite Pattern safe-composite arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Composite%20Pattern%20safe-composite%20arch.png)

Component：

```java
public interface class Component //Leaf类只需要实现operation（）
{

	public abstract void operation();
}
```



Leaf:

```java
public class Leaf extends Component
{
    public void operation()
	{
		//实现代码
	}
}
```



### code

前面给出了Component和Leaf的代码，这里只需要给出Composite的代码



Composite:

```java
public class Composite extends Component
{
	private ArrayList list = new ArrayList();


	public void add(Component c)
	{
		list.add(c);
	}

	public void remove(Component c)
	{
		list.remove(c);
	}
	
	public Component getChild(int i)
	{
		(Component)list.get(i);
	}

	public void operation()
	{
		for( Object obj: list )
		{
			((Component)obj).operation();
		}
    }
}
```

### 示例( 透明组合模式 )

![Transparent Composite FileSystem](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Transparent%20Composite%20FileSystem.png)



## Bridge

>将抽象部分与它的实现 部分分离，使它们都可以独立地变化
>
>对象结构型模式



* 桥接模式将抽象部分与它的实现部分分离，使它们都可以独立地变化。它是一种对象结构型模式，又称为柄体(Handle and Body)模式或接口(Interface)模式。

* 桥接模式包含如下四个角色:抽象类中定义了一个实现类接口类型的对象并可以维护该对象;扩充抽象类扩充由抽象类定义的接口，它实现了在抽象类中定义的抽象业务方法，在扩充抽象类中可以调用在实现类接口中定义的业务方法;实现类接口定义了实现类的接口，实现类接口仅提供基本操作，而抽象类定义的接口可能会做更多更复杂的操作;具体实现类实现了实现类接口并且具体实现它，在不同的具体实现类中提供基本操作的不同实现，在程序运行时，具体实现类对象将替换其父类对象，提供给客户端具体的业务操作方法。
* 在桥接模式中，抽象化(Abstraction)与实现化(Implementation)脱耦，
  它们可以沿着各自的维度独立变化。



* 桥接模式的主要优点是分离抽象接口及其实现部分，是比多继承方案更好的解决方法，桥接模式还提高了系统的可扩充性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统，实现细节对客户透明，可以对用户隐藏实现细节;其主要缺点是增加系统的理解与设计难度，且识别出系统中两个独立变化的维度并不是一-件容易的事情。
* 桥接模式适用情况包括:需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系;抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响;一个类存在两个独立变化的维度，且这两个维度都需要进行扩展;设计要求需要独立管理抽象化角色和具体化角色;不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统。

 ### 模式动机

* 对于有**多个变化维度**的系统，采用**桥接模式**来进行设计系统中类的个数更少， 且系统扩展更为方便

* 桥接模式**将继承关系转换为关联关系**， 从而**降低了类与类之间的耦合**

### 模式结构

![bridge arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/bridge%20arch.png)



* Abstraction
* RefinedAbstraction：扩充抽象类
* Implementor： 扩充的维度类，这里用接口，也可以用抽象类
* ConcreteImplementor：维度类的实现类。 例如，若Implementor是“颜色”，则ConcreteImplementor可以是“红”、“黄”、“蓝”

### 模式分析

理解桥接模式，重点需要理解如何将**抽象化**(Abstraction)与**实现化**(Implementation)**解耦**

* 抽象化：将对象的共同性质抽取出来形成类
  * 比如，将不同颜色、形状的矩形抽象为“正方形类”
* 实现化：针对抽象化给出具体实现。 实现化产生的对象比抽象化更具体
  * 比如，对“矩形类”进行实例化，赋予其不同的属性（颜色、大小...）
* 抽象化与实现化解耦：将**抽象化和实现化之间的强关联转变成弱关联，将两个角色（维度类和抽象物体类）之间的继承关系改为关联关系**
  * 具体矩形类不需要继承“颜色类”，再继承“大小类”，这样会造成类的数量爆炸。
  * 取而代之的是，使用抽象矩形类，与“颜色类”和“大小类”**组合**

### cocde

Implementor：

```java
public interface Implementor {
  
	public void operationImpl(); 
}
```



Abstraction:

```java
public abstract class Abstraction 
{

  //引入了新的维度， 比如该Abstraction类是矩形类，Implementor是颜色类，
  //引入Implementor即使得矩形多了一个“颜色”维度
	protected Implementor impl;

	public void setImpl(Implementor impl) 
  {
		this.impl=impl; 
  }

	public abstract void operation(); 

}
```



RefinedAbstraction:

```java
public class RefinedAbstraction extends Abstraction {
	public void operation() 
  {
		//代码 
    impl.operationImpl(); 
    //代码
	}
}
```



### 示例

####  模拟毛笔

**蜡笔和毛笔是传统继承模式与桥接模式的最好比喻**



现需要提供<u>大中小3种型号</u>的画笔，能够绘制<u>5种不同颜色</u>

如果使用蜡笔，我们需要准备3*5=15支蜡笔，也就是说必须准备15个具体的蜡笔类

* 蜡笔相当于传统的使用继承体系来扩展对象， 每个具体蜡笔类继承自某个具体大小类，和具体的颜色类， 一共有15个具体蜡笔类
* 毛笔相当于桥接模式，使用组合来扩展对象。 只需要一个抽象毛笔类，它依赖大小类和颜色类。 只需要3 + 5个维度类 + 一个抽象毛笔类，使用时再使用具体的毛笔实现类



![bridge example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/bridge%20example.png)

#### 跨平台视频播放器

每个播放器都有两个维度的属性： 支持的视频格式， 支持的操作系统

通过Bridge模式，将两个维度与播放器类组合起来

![bridge example2.](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/bridge%20example2.png)



### 优点

* 分离抽象接口及其实现部分
* 与多继承对比：
  * 多继承违背了类的单一职责原则(“一个类只有一个变化的原因”， 即变化的维度)； 
  * 使用多继承，类的个数会过多
* 桥接模式提高了系统的可扩展性
  * 在两个变化维度中任意扩展一个维度，都不需要修改原有系统。
* 可以对用户隐藏实现细节，使得实现细节对客户透明

### 缺点

* 引入桥接模式会增加系统的复杂度
* 桥接模式<u>要求正确识别出系统中两个独立变化的维度，因此其使用范围具有一定的局限性</u>

### 适用环境

* 系统需要<u>在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承关系</u>，
  * 通过桥接模式可以使它们在抽象层建立一个关联关系
  * 抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一个实现化子类的对象进行组合
* <u>一个类存在多个独立变化的维度</u>，且这些维度都需要进行扩展
  * 也可以使用多继承，但会导致类的组合爆炸
* <u>不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统</u>

### 模式扩展

适配器模式与桥接模式的联用

桥接模式和适配器模式用于设计的不同阶段,桥接模式用于系统的初步设计，对于存在两个独立变化维度的类可以将其分为抽象化和实现化两个角色，使它们可以分别进行变化;而在初步设计完成之后，当发现系统与已有类无法协同工作时，可以采用适配器模式。但有时候在设计初期也需要考虑适配器模式，特别是那些涉及到大量第三方应用接口的情况。

## Decorator

> 装饰模式(Decorator Pattern) : **动态地给一个对象增加一些额外的职责**(Responsibility), 就增加对象功能来说，装饰模式比生成子类实现更为灵活
>
> 别名称为包装器(Wrapper)，与适配器模式的别名相同，但它们适用于不同的场合。根据翻译的不同，装饰模式也有人称之为“油漆工模式”
>
> 是一种对象结构型模式。



* 装饰模式可分为：
  * 透明装饰模式： 要求client完全面向抽象编程，client应该全部使用抽象构件类型
  * 半透明装饰模式:允许client声明具体装饰者类型的对象，调用在具体装饰者中新增的方法



### 模式结构

![Decotator Pattern arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Decotator%20Pattern%20arch.png)

* Component
* ConcreteComponent
* Decorator：抽象装饰类
* ConcreteDecorator

### 模式分析

* 使用装饰模式来实现扩展**比继承更加灵活**，**它以对客户透明的方式动态地给一个对象附加更多的责任**
  * 装饰模式可以在不需要创造更多子类的情况下，将对象的功能加以扩展

* 装饰模式的简化：如果只有一个具体构件类而没有抽象构件类，那么抽象装饰类可以作为具体构件类的直接子类。

### code

抽象装饰类：

```java
public class Decorator extends Component 
{
	private Component component;
  
	public Decorator(Component component) 
  {
		this.component=component; 
  }
  
	public void operation() 
  {
		component.operation(); 
  }
}
```



具体装饰类：

```java
public class ConcreteDecorator extends Decorator 
{
	public ConcreteDecorator(Component component) 
  {
		super(component); 
  }
  
	public void operation() 
  {
		super.operation();
		addedBehavior(); 
  }
  
	public void addedBehavior()
	{
		//新增方法 
  }
}
```

### 半透明装饰模式

半透明(semi-transparent)的装饰模式允许用户在客户端声明具体装饰者类型的对象，调用在具体装饰者中新增的方法

```java
Transform camaro;
camaro=new Car();
camaro.move();//这里依然属于面向抽象编程，move()是抽象的Transform类的方法
Robot bumblebee=new Robot(camaro); bumblebee.move();
bumblebee.say(); //这里使用了具体的Robot装饰类的方法，没有面向抽象编程
```

#### 示例

变形金刚在变形之前是一辆汽车，它可以在陆地上移动。当它变成机器人之后除了能够在陆地上移动之
外，还可以说话;如果需要，它还可以变成飞机，除了在陆地.上移动还可以在天空中飞翔。

![Decotator Pattern -semi-transparent-example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Decotator%20Pattern%20-semi-transparent-example.png)

### 透明装饰模式

在透明装饰模式中，要求**客户端完全针对抽象编程**，装饰模式的透明性要求客户端程序不应该声明具体构件类型和具体装饰类型，而应该全部声明为抽象构件类型。

```java
Cipher sc,cc,ac;
sc=new SimpleCipher(); 
cc=new ComplexCipher(sc); 
ac=new AdvancedCipher(cc);
```

#### 示例

存在多种字符串加密算法(Cipher)

* SImpleCipher:
* ComplexCipher
* AdvancedCipher



用户可以只选择一种加密算法，也可以多重加密



![Decotator Pattern example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Decotator%20Pattern%20example.png)

#### 优点

* 装饰模式与继承关系的目的都是要扩展对象的功能，但是**装饰模式可以提供比继承更多的灵活性**。
* 具体构件类与具体装饰类可以独立变化，用户可以根据需要增加新的具体构件类和具体装饰类，在使用时再对其进行组合，原有代码无须改变，符合“开闭原则”

#### 缺点

* 使用装饰模式进行系统设计时**将产生很多小对象**，这些对象的区别在于它们之间相互连接的方式有所不同，而不是它们的类或者属性值有所不同，同时还将产生很多具体装饰类。这些装饰类和小对象的产生将增加系统的复杂度，加大学习与理解的难度。

* 这种比继承更加灵活机动的特性，也意味着**装饰模式比继承更加易于出错**，错误排查也比较困难

#### 适用环境

* 在不影响其他对象的情况下，**以动态、透明的方式给单个对象添加职责**
* 需要**动态地给一个对象增加功能**，这些功能也可以动态地被撤销
* **当不能采用继承的方式对系统进行扩充或者采用继承不利于系统扩展和维护时**。 不能采用继承的情况主要有两类:
  1. 是系统中存在大量独立的扩展，为支持每一种组合将产生大量的子类，使得子类数目呈爆炸性增长;
  2. 类被定义为不能继承(如final类)

## Facade 

>外观模式(Facade Pattern):在外观模式中，外部与一个子系统的通信必须通过一个**统一的外观对**象进行，为子系统中的一组接口提供一组一致的更高层次的接口，使得子系统更容易使用
>
>又称为门面模式
>
>是一种对象结构型模式



![Facade Pattern arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Facade%20Pattern%20arch.png)

### 模式结构

* Facade
* SubSystem

### 模式分析

* 外观模式要求一个<u>子系统的外部与其内部的通信通过一个统一的外观对象进行</u>，外观类将客户端与子系统的内部复杂性分隔开，使得<u>client只需要与外观对象打交道，而不需要与子系统内部的很多对象打交道</u>
  * 是“<u>迪米特法则</u>”的体现，也降低了client与子系统类的耦合
  * 引入外观类可以降低系统的复杂度
  * 降低了子系统间的通信和相互依赖关系
* 提高了客户端使用的便捷性，使得客户端无须关心子系统的工作细节，通过外观角色即可调用相关功能

### code

Facade：

```java
public class Facade 
{
	private SubSystemA obj1 = new SubSystemA(); 
  private SubSystemB obj2 = new SubSystemB(); 
  private SubSystemC obj3 = new SubSystemC(); 
  
  public void method()
	{
		obj1.method(); obj2.method(); obj3.method();
	} 
}
```

### 示例

一个电源总开关可以控制四盏灯、一个风扇、一台空调和一台电视机的启动和关闭

![Facade Pattern example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Facade%20Pattern%20example.png)

### 优点

* <u>对客户屏蔽子系统组件</u>，<u>减少了客户处理的对象数目并使得子系统使用起来更加容易</u>
* 实现了子系统与客户之间的松耦合关系
* 降低了大型软件系统中的编译依赖性，并简化了系统在不同平台之间的移植过程
  * 因为编译一个子系统一般不需要编译所有其他的子系统。一个子系统的修改对其他子系统没有任何影响，而且子系统内部变化也不会影响到外观对象
* 只是提供了一个访问子系统的统一入口，并不影响用户直接使用子系统类

### 缺点

* <u>不能很好地限制客户使用子系统类</u>，如果对客户访问子系统类做太多的限制则减少了可变性和灵活性。
* 在不引入抽象外观类的情况下，当增加新的子系统或者移除子系统时需要修改外观类，**违背了“开闭原则”**

### 适用环境

* 当要为一个复杂子系统提供一个简单接口时可以使用外观模式。该接口可以满足大多数用户的需求，而且<u>用户也可以越过外观类直接访问子系统</u>
* <u>客户程序与多个子系统之间存在很大的依赖性</u>。引入外观类将子系统与客户以及其他子系统解耦，可以提高子系统的独立性和可移植性
* 在层次化结构中，可以使用外观模式定义系统中每一层的入口，层与层之间不直接产生联系，而通过外观类建立联系，降低层之间的耦合度



### 模式扩展

* **不要试图通过外观类为子系统增加新行为**，外观模式的用意是为子系统提供一个集中化和简化的沟通渠道，而不是向子系统加入新的行

  

## Flyweight

> 享元模式： **通过共享，实现大量的细粒度对象的复用**，以解决对象数量太多导致的性能问题
>
> 是一种对象结构性模式

分为复合享元模式和单纯享元模式

* 单纯享元模式： 就是所有享元对象都可以共享
* 复合享元模式： 存在复合享元对象，它是单纯和不可共享享元对象的组合，本身不能被共享。 但可以被分解为单纯享元对象，和一些不可共享的享元对象
* 默认是复合享元模式



复合享元模式：

![Flyweight Pattern complex-arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Flyweight%20Pattern%20complex-arch.png)



### 模式结构

* Flyweight:抽象享元类： 声明一个接口，通过它可以接受并作用于外部状态
* ConcreteFlyweight: 具体享元类
* UnsharedConcreteFlyweight:不可共享的具体享元类
* FlyweightFactory:享元工厂类，用于创建并管理享元对象

### 模式分析

* 享元模式是一个<u>考虑系统性能</u>的设计模式，通过使用享元模式可以节约内存空间，提高系统的性能。
* 享元模式的核心在于**享元工厂类**，享元工厂类的作用在于提供一个用于**存储享元对象的享元池**，用户需要对象时，首先从享元池中获取，如果享元池中不存在,则创建一个新的享元对象返回给用户，并在享元池中保存该新增对象。
* 享元模式以共享的方式高效地支持大量的细粒度对象
* 享元对象具有内部状态(Internal State)和外部状态(External State)
  * 内部状态是<u>存储在享元对象内部并且不会随环境改变而改变的状态</u>，因此可以共享。
  * 外部状态是<u>存储在client的，随环境改变而改变的、不可以共享的状态</u>
    * client在享元对象被创建之后并在需要被使用时，将外部状态传入到享元对象内部
    * 外部状态间相互独立



### code

FlyweightFactory:

```java
public class FlyweightFactory 
{
  //持有享元对象的序列
	private HashMap flyweights = new HashMap();
	public Flyweight getFlyweight(String key) 
  {
		if(flyweights.containsKey(key)) 
    {
      return (Flyweight)flyweights.get(key);
		} 
    
    else
    {
      Flyweight fw = new ConcreteFlyweight(); 
      flyweights.put(key,fw);
			return fw;
    }
  }
```



Flyweight

```java
public class Flyweight
{
	//内部状态作为成员属性
	private String intrinsicState;
  
	public Flyweight(String intrinsicState) 
  {
		this.intrinsicState = intrinsicState; 
  }
  
  //接受外部状态，并可能改变外部状态
	public void operation(String extrinsicState) 
  {
		...... 
  }
}
```



### 优点

* 可以极大减少内存中对象的数量，使得相同对象或相似对象在内存中只保存一份

* 外部状态相对独立，而且不会影响其内部状态，从而使得享元对象可以在不同的环境中被共享。

### 缺点

* 享元模式使得系统更加复杂，需要分离出内部状态和外部状态，这使得程序的逻辑复杂化。
* 为了使对象可以共享，享元模式需要将享元对象的状态外部化，而读取外部状态使得运行时间变长。

### 适用环境

* **一个系统有大量相同或者相似的对象**，由于这类对象的大量使用，造成内存的大量耗费。
* **对象的大部分状态都可以外部化**，可以将这些外部状态传入对象中。
* 使用享元模式需要维护一个存储享元对象的享元池，而这需要耗费资源，因此，**在多次重复使用享元对象时才值得使用享元模式。**

### 模式扩展

享元模式与其他模式的联用

* 在享元模式的享元工厂类中通常提供一个静态的工厂方法用于返回享元对象，使用简单工厂模式来生成享元对象。在一个系统中，通常只有唯一一个享元工厂，因此享元工厂类可以使用单例模式进行设计。
* 享元模式可以结合组合模式形成复合享元模式，统- -对享元对象设置外部状态。

## Proxy

> 代理模式(Proxy Pattern) :给某一个对象提供一个代理，并**由代理对象控制对原对象的引用**
>
> 是一种对象结构型模式



* 远程代理为一个位于不同的地址空间的对象提供一个本地的代表对象，它使得客户端可以访问在远程机器上的对象，远程机器可能具有更好的计算性能与处理速度，可以快速响应并处理客户端请求。
* 如果需要创建一个资源消耗较大的对象，先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建，这个小对象称为虚拟代理。虚拟代理通过使用一个小对象来代表一一个大对象，可以减少系统资源的消耗，对系统进行优化并提高运行速度 ---- 也就是**延迟初始化**
* 保护代理可以控制对一个对象的访问，可以给不同的用户提供不同级别的使用权限

![Proxy Pattern arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Proxy%20Pattern%20arch.png)

### 模式结构

* Subject:抽象主题角色
* Proxy:代理主题角色
* RealSubject:真实主题角色



Proxy和RealSubject都继承Subject， 使得可以面向抽象的Subject编程，而不必考虑具体的实现类是Proxy还是ReadSubject

Proxy持有ReadSubject对象，进行相应操作

### code

```java
public class Proxy implements Subject {
	private RealSubject realSubject = new RealSubject(); 
	public void preRequest() {......}
  
	public void request()
	{
		preRequest(); 
    realSubject.request(); 
    postRequest();
	}
  
	public void postRequest() {......}
}
```

### 优点

* 代理模式能够协调调用者和被调用者，在一定程度上降低了系统的耦合度。
* **远程代理**使得客户端可以访问在远程机器.上的对象，远程机器可能具有更好的计算性能与处理速度，可以快速响应并处理客户端请求。
* **虚拟代理**通过使用一个小对象来代表一-个大对象，可以减少系统资源的消耗，对系统进行优化并提高运行速度。
* **保护代理可以控制对真实对象的使用权限**



### 缺点

* 慢
* 复杂度高

### 模式细分

根据代理模式的使用目的，常见的代理模式有以下几种类型:

* 远程(Remote)代理: 为一个位于不同的地址空间的对象提供一个 本地的代理，对象，这个不同的地址空间可以是在同一台主机中，也可以在另一台主机中，远程代理又叫做大使(Ambassador)
* 虚拟(Virtual)代理:如果需要创建一个资源消耗较大的对象，先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建
  * 使用示例： 大图浏览的控制
    1. 用户通过浏览器访问网页时先**不加载真实的大图**，而是通过代理对象的方法来进行处理
    2. 在代理对象的方法中，**先使用一个线程向客户端浏览器加载一个小图片**，然后在后台**使用另一个线程来调用大图片的加载方法将大图片加载到客户端**。 当需要浏览大图片时，再将大图片在新网页中显示。
    3. 如果用户在浏览大图时加载工作还没有完成，可以再启动一个线程来显示相应的提示信息。通过代理技术结合多线程编程将真实图片的加载放到后台来操作，不影响前台图片的浏览
* Copy- on-Write代理: 是虚拟代理的一种，把复制(克隆)操作延迟到只有在客户端真正需要时才执行。一般来说，对象的深克隆是一个开销较大的操作，Copy-on-Write代理可以让这个操作延迟，只有对象被用到的时候才被克隆
* 保护(Protect or Access)代理: 给不同用户提供不同的使用权限，来控制对对象的访问
* 缓冲(Cache)代理: 为数据提供临时的存储空间，以便多个客户端可以共享数据。
* 防火墙(Firewall)代理: 保护对象不被恶意攻击
* 智能引用(Smart Reference)代理: 相当于智能指针，当一个对象被引用时，智能引用代理会进行一些额外的操作，比如，记录下此对象被调用的次数

# Behavioral Patterns

## Strategy

> 策略模式： 定义一系列可替换的算法，由client决定使用哪个



![Strategy Pattern arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Strategy%20Pattern%20arch.png)

### 模式结构

* 上下文（Context ) ： 拥有Strategy对象的一个引用； 被配置了具体策略 ConcreteStrategy
* 策略（Strategy）: 声明了所支持策略的接口。 Context利用这些被ConcreteStrategy定义的接口
* 具体策略（ConcreteStrategy）: 实现了Strategy声明 的接口，给出了具体的实现



模式逻辑：

* 上下文`Context`和`Strategy`的相互协作完成整个算法。 `Context`可能会通过提供方法让`Strategy`访问其数据；甚 至将自身的引用传给`Strategy`，供其访问其数据。 `Strategy`会在需要的时候访问`Context`的成员变量。
* 上下文`Context`将一些对他的请求转发给策略类来实现 ，客户（`Client`）通常创建`ConcreteStrategy`的对象，然 后传递给C`ontext`来灵活配置`Strategy`接口的具体实现； 这样`Client`就有可以拥有一个`Strategy`接口的策略族，其 中包含多种`ConcreteStrategy`的实现

### 适用环境

* 当很多相关类<u>只在它们的行为的实现上不一样</u>
* 当我们需要<u>同一个行为的不同实现</u>（变体）的时候
* 算法需要用到一些数据，而这些数据不应该被客户知道。我们可以通过策略模式隐藏复杂的算法和数据接口。
*  一个类定义了很多行为，这些行为作为一个`switch`选择语句的分支执行部分。策略模式可以消除这些分支选择

### 模式扩展

* `Strategy`可以是接口，也可以是类。如果是类，则可以抽象所有具体算法中公共的实现部分。
* 当然，我们也可以直接通过Context的子类来实现不同的 Context实现。不过这样算法的具体实现，就和算法的利用的 实现项目交织在一起，不利于理解和维护.
* 策略模式消除了类似根据策略类型的Switch语句。 
* 可以动态选择不同的策略 
  * 这需要客户必须提前知晓不同的策略
* Context和Strategy之间的通信有代价
* 策略模式会创建出较多的对象





## Command

>  命令模式(Command Pattern): 将一个请求封装为一个对象,从而可在请求client时传递参数; 对请求排队或者记录请求日志,以及支持可撤销的操作。
>
>  是一种对象行为型模式, aka动作(Action)模式或事务(Transaction)模式

client持有reciever和 invoker， 通过将receiver传给ConcreteCommand来构造command， 然后把command传给invoker， client只要调用`invoker`的`invoke（）`





![image-20220308152816123](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/command%20pattern.png)

 ### 模式结构

* 命令模式包含如下角色:
* Command: 抽象命令类
* ConcreteCommand: 具体命令类
* Invoker:  调用者
* Receiver:  接收者
* Client: 客户类

### 模式分析

* 命令模式的本质是对命令进行封装，**将发出命令的责任和执行命令的责任分开**
  * client负责发出命令。 client持有receiver和invoker，用receiver构造ConcreteCommand， 将command传给invoker，调用`invoker.invoke()`，发出命令
  * invoke负责执行命令。 invoker对象持有了command对象， command对象已经被注入了receiver对象。由 invoker执行command
* 每一个命令都是一个操作:请求的一方发出请求，要求执行一个操作; 接收的一方收到请求，并执行操作
  * Receiver有`doSomething()`方法，在`command.exeute()`中调用
* 命令模式**使请求本身成为一个对象**，这个对象和其他对象一样可以被存储和传递
  * 通过引入抽象命令接口（`Command`），且client针对`Command`接口编程
* 命令模式允许请求的一方和接收的一方独立开来，使得请求的一方不必知道接收请求的一方的接口、请如何接收、操作是否被执行、何时被执行、怎么被执行的 等问题

### code

通用Receiver类：

```java
public abstract class Receiver { 
    //抽象接收者，定义每个接收者都必须完成的业务 
    public abstract void doSomething(); 
}

```



具体的Receiver类ConcreteReciver1、ConcreteReciver2：

```java
public class ConcreteReciver1 extends Receiver{ 
    //每个接收者都必须处理一定的业务逻辑 
    public void doSomething(){ 
    } 
}
public class ConcreteReciver2 extends Receiver{ 
    //每个接收者都必须处理一定的业务逻辑 
    public void doSomething(){ 
    }
}
```




抽象的Command类：

```java
public abstract class Command { 
    //每个命令类都必须有一个执行命令的方法
    public abstract void execute(); 
}
```




调用者Invoker类：

```java
public class Invoker { 
    private Command command; 
    //受气包，接受命令 
    public void setCommand(Command _command){ 
        this.command = _command; 
    }
    //执行命令 
    public void invoke(){ 
      
        this.command.execute(); 
     
    }
}
```



具体的Command类ConcreteCommand1、ConcreteCommand2：

```java
public class ConcreteCommand1 extends Command { 
    //进行命令处理的Receiver
    private Receiver receiver;
  
    //通过构造函数来注入receiver
    public ConcreteCommand1(Receiver _receiver){ 
        this.receiver = _receiver; 
    }
    //必须实现一个命令 
    public void execute() { 
        //业务处理 
        this.receiver.doSomething(); 
    } 
}
public class ConcreteCommand2 extends Command { 
    //进行命令处理的Receiver
    private Receiver receiver;
  
    //通过构造函数来注入receiver
    public ConcreteCommand2(Receiver _receiver){ 
        this.receiver = _receiver; 
    }
    //必须实现一个命令 
    public void execute() { 
        //业务处理 
        this.receiver.doSomething(); 
    } 
}
```





Client：

```java
public class Client { 
    public static void main(String[] args) { 
        //首先声明调用者Invoker 
        Invoker invoker = new Invoker(); 
        //定义接收者 
        Receiver receiver = new ConcreteReciver1(); 
        //定义一个发送给接收者的命令 
        Command command = new ConcreteCommand1(receiver); 
        //把命令交给调用者去执行 
        invoker.setCommand(command); 
        invoker.invoke(); 
    } 
}
```

### 示例

遥控器（`Controller`）是client， 电视机（`Television`）是接收者，有三个具体命令类

* 这个示例是简化版的命令模式，没有invoker，也没有动态注入Receiver

![Command example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Command%20example.png)



### 优点

命令模式的优点

* 降低系统耦合度
* 可扩展性强，很容易加入新的命令类
* 可以比较容易地设计命令队列和宏命令（组合命令）
* 可以方便地实现请求的Undo和Redo

### 缺点

* 可能导致系统具有过多的命令类

### 适用环境

* 系统需要将请求调用者和请求接收者解耦，使得调用者和接收者不直接交互
* 系统需要在不同的时间指定请求、将请求排队和执行请求
* 系统需要支持命令的撤销(Undo)操作和恢复(Redo)操作
* 系统需要将一 组操作组合在一起，即支持宏命令



Unix的SHell编程的宏命令功能，可以将多条命令封装在一个命令对象中，这使用了命令模式



## State

>  状态模式(State Pattern) :允许一个对象在其内部状态改变时改变它的行为,对象看起来似乎修改了它的类。其别名为状态对象(Objects for States), 状态模式是一种**对象行为型模式**



状态模式描述了对象状态的变化以及对象如何在每一种状态下表现出不同的行为。

状态模式的关键是引入了一个**抽象类**来专门表示对象的状态,这个类我们叫做抽象状态类,而对象的每一种具体状态类都继承了该类,并在不同具体状态类中实现了不同状态的行为,包括各种状态之间的转换。



![image-20220308143955436](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/state%20pattern.png)

 结构：

* Context 环境类： 是拥有状态的对象。 有时候可以充当状态管理器(State Manager)的角色,可以在环境类中对状态进行切换操作
* State 抽象状态类（也可以是接口） : 可以将不同对象下的行为单独提取出来封装在具体的状态类中,使得环境类对象在其内部状态改变时可以改变它的行为,对象看起来似乎修改了它的类,而实际上是由于切换到不同的具体状态类实现的。
* ConcreteState: 具体状态类

### 示例

![image-20220308144112980](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/state%20pattern%20room.png)

### 缺点

* 状态模式的使用必然会增加系统类和对象的个数。
* 状态模式的结构与实现都较为复杂,如果使用不当将导致程序结构和代码的混乱。
* 状态模式对“**开闭原则**”的支持并不太好,对于可以切换状态的状态模式,增加新的状态类需要修改那些负责状态转换的源代码,否则无法切换到新增状态;而且修改某个状态类的行为也需修改对应类的源代码。



## Observer

>观察者模式(Observer Pattern): 通过建立对象间的一对多依赖关系, 使得每当一个对象状态发生改变时,其相关依赖对象皆得到通知并被自动更新
>
>又叫做发布-订阅(Publish/Subscribe)模式、模型-视图(Model/View)模式、源-监听器(Source/Listener)模式或从属者(Dependents)模式
>
>是一种**对象行为型模式**



![image-20220315142422314](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/observer%20pattern.png)



### 模式结构

* Subject: 目标
* ConcreteSubject:具体目标
* Observer:观察者
* ConcreteObserver: 具体观察者

### code

 抽象目标类：

```java
import java.util.*;
public abstract class Subject
{
	protected ArrayList observers = new ArrayList();
	public abstract void attach(Observer observer);
	public abstract void detach(Observer observer);
	public abstract void notify();
}
```



 具体目标类：

```java
public class ConcreteSubject extends Subject
{
	public void attach(Observer observer)
	{
		observers.add(observer);
	}

	public void detach(Observer observer)
	{
		observers.remove(observer);
	}

	public void notify()
	{
		for(Object obs:observers)
		{
			((Observer)obs).update();
		}
    }
}
```



抽象观察者：

```java
public interface Observer
{
	public void update();
}
```



具体观察者：

```java
public class ConcreteObserver implements Observer
{
	public void update()
	{
		//具体更新代码
	}
}
```



client代码:

```java
Subject subject = new ConcreteSubject();
Observer observer = new ConcreteObserver();
subject.attach(observer);
subject.notify();
```

### 示例

猫是老鼠和狗的观察目标，老鼠和狗是观察者，猫叫，则老鼠跑，狗也跟着叫

![observer example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/observer%20example.png)

### 优点

优点：

* 实现了表示层和数据逻辑层的分离
* 实现了Observer和Subject的解耦
* 支持广播通信
* 符合“开闭原则”

### 缺点

* 通知到所有直接和间接的Observer，耗时较大
* Observer和Subject可能发生循环依赖

## Mediator

> 中介者模式(Mediator Pattern): 用一个中介对象来封装一系列的对象交互,中介者使各对象不需要显式地相互引用,从而**使其松耦合**,而且可以独立地改变它们之间的交互
>
> 又称为调停者模式
>
> 是一种对象行为型模式

![image-20220315161423254](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/medicator%20pattern)

###  模式结构

* Medicator
* ConcreteMedicator
* Colleague
* ConcreteColleague

### code

抽象中介者类代码:

```java
public abstract class Mediator
{
	protected ArrayList colleagues;
	public void register(Colleague colleague)
	{
		colleagues.add(colleague);
	}
}
```



具体中介者类代码:

```java
public class ConcreteMediator extends Mediator
{
	public void operation()
	{
		......
		((Colleague)(colleagues.get(0))).method1();
		......
	}
}
```



抽象同事类代码：

```java
public abstract class Colleague
{
	protected Mediator mediator;
	public Colleague(Mediator mediator)
	{	
		this.mediator=mediator;
	}
	public abstract void method1();
}
```



```java
public class ConcreteColleague extends Colleague
{
	public ConcreteColleague(Mediator mediator)
	{
        super(mediator);
	}

	public void method1()
	{
		......
	}
    
   	public void method2()
	{
		mediator.operation1();
	} 
}
```



### 优点

中介者模式可以使对象之间的关系数量大大减少：

![image-20220315161530458](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/medicator%20pattern%20advantage.png)

### 缺点

* 具体中介者类可能会非常复杂，事实上这就是一个God Class

## Template Method

> 模板方法模式：定义一个操作中**算法的骨架**,而将一些步骤**延迟到子类中**,模板方法使得子类可以**不改变一个算法的结构即可重定义该算法的某些特定步骤**
>
> 是一种类行为型模式
>
> 
>
> 

* 模板方法模式是**基于继承**的代码复用基本技术

  * 只有继承，没有关联

* 在模板方法模式中,可以**将相同的代码放在父类中,而将不同的方法实现放在不同的子类中**

  * 具体子类的基本方法将覆盖父类中定义的基本方法, 子类的钩子方法也将覆盖父类的钩子方法, 从而可以通过在子类中实现的钩子方法对父类方法的执行进行约束, 实现子类对父类行为的**反向控制**

* 模板方法模式包含两个角色:

  * **模板方法**： 定义在抽象类中，是一系列基本方法的组合
  * **基本方法**： 实现算法某个具体步骤， 可分为：
    * 抽象方法
    * 具体方法
    * 钩子方法

  



![Template Method Pattern](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Template%20Method%20Pattern.png)

### 模式结构

* AbstractClass
* ConcreteClass

### code

钩子方法：

```java
public void template()
{
	open();
	display();
	if(isPrint())//根据钩子方法的返回值来执行逻辑
	{
		print();
	}
}

//不同的子类可以自定义这个函数的返回值，从而实现对template方法的反向控制
public boolean isPrint()
{
	return true;
}
```



抽象类代码:

```java
public abstract class AbstractClass
{
	public void templateMethod() //模板方法，是一系列基本方法的组合
	{
		primitiveOperation1();
		primitiveOperation2();
		primitiveOperation3();
	}
    
	public void primitiveOperation1() //基本方法—具体方法
	{
	//实现代码
	}
    
	public abstract void primitiveOperation2(); //基本方法—抽象方法，在子类中实现
    
	public void primitiveOperation3() //基本方法—钩子方法，由子类来定义其逻辑
	{
	}
}
```



子类代码：

```java
public class ConcreteClass extends AbstractClass
{
	public void primitiveOperation2()
	{
		//实现代码
	}
	public void primitiveOperation3()
	{
		//实现代码
	}
}
```

### 示例

在银行办理业务( `process()` )时，一般都包含几个基本步骤：

1. 首先需要取号排队: `takeNumber()`
2. 然后办理具体业务：`transact()`
3. 最后需要对银行工作人员进行评分`evaluate()`



无论具体业务是取款、存款还是转账，其基本流程都一样, 因此模板方法是`process()`，基本方法是`takeNumber() + transact() + evaluate()`



![Template Method Pattern example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Template%20Method%20Pattern%20example.png)

### 优点

* 模板方法模式**在一个类中抽象地定义算法，而由它的子类实现细节的处理**

* 代码复用

* 模板方法模式可以实现**反向控制**
  * 通过钩子方法
* 通过对修改子类来修改行为，符合“开闭原则”

### 缺点

* 每个不同的实现都需要定义一个子类，这会导致**类的个数增加**，系统更加庞大，设计也更加抽象
  * 但是也更加符合“单一职责原则”，类的内聚性更高

### 好莱坞原则

*“不要给我们打电话， 我们会给你打电话(Don 't call us, we’11 call you)*

* 好莱坞原则(Hollywood Principle)： 子类不显式调用父类的方法，而是通过覆盖父类的方法来实现某些具体的业务逻辑，**父类控制对子类的调用**

* 在模板方法模式中，好莱坞原则体现在:通过父类来调用子类， 子类不需要调用父类。 将某些步骤的实现写在子类中，由父类来控制整个过程

