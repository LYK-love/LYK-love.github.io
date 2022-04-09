---
title: Software System Design Intro
categories: Software Engineering
---



Outline:

* 类之间的关系
* 组合 > 继承
* 设计模式：创建型
* 设计模式： 结构型
* 设计模式：行为型



ref： 软件系统设计 --- 潘敏学， [Design Pattern Turotial](https://refactoring.guru/design-patterns/creational-patterns)

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

> 概念：聚合关联关系的一种特例，是强的关联关系。聚合是整体和个体之间的关系，即**has-a**的关系，整体与个体可以具有各自的生命周期，部分可以属于多个整体对象，也可以为多个整体对象共享。程序中聚合和关联关系是一致的，只能从语义级别来区分。

**表示方式：**尾部为空心菱形的实线箭头（也可以没箭头）。

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

> 组合也是关联关系的一种特例。组合是一种整体与部分的关系，即contains-a的关系，比聚合更强。部分与整体的生命周期一致，整体的生命周期结束也就意味着部分的生命周期结束，组合关系不能共享。程序中组合和关联关系是一致的，只能从语义级别来区分。

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

# Creationnal  Patterns

## Singleton

太简单，不介绍了



## Simple Factory



策略模式解决的是**行为问题**, 工厂模式解决**对象创建问题**

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

> 在工厂方法模式中,核心的工厂类不再负责所有产品的创建,而是将具体创建工作交给子类去做。这
> 个核心类仅仅负责给出具体工厂必须实现的接口,而不负责哪一个产品类被实例化这种细节,这使得
> **工厂方法模式可以在不修改工厂角色的情况下引进新产品**

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

* 产品等级结构： 即产品的继承结构。 如抽象类是电视机， 而子类有海信电视机， TCL电视机， 则抽象电视机与具体品牌的电视机构成了一个产品等级结构
* 产品族：由同一个工厂生产的，位于不同产品等级结构中的一组产品。 如海尔是一个产品族， 海尔电视机属于电视机产品结构， 电冰箱位于电冰箱产品结构

### 模式结构

* AbstractFactory
* AbstractProduct
* Product

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



## Builder

> 建造者模式可以将一个复杂对象的构建与它的表示分离,使得同样的构建过程可以创建不同的表示.将部件和其组装过程分开,一步一步创建一个复杂的对象

![image-20220308144855351](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/builder%20pattern.png)

### 模式结构

* Builder:抽象建造者
* ConcreteBuilder:具体建造者
* Directo: :指挥者. 一方面它隔离了客户与生产过程;另一方面它负责控制产品的生成过程
* Product:产品角色

### 示例

```java
//抽象建造者
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

```java
//Director
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



```java
//客户端类代码
Builder builder = new ConcreteBuilder();
Director director = new Director(builder);
Product product = director.construct();
```

在客户端代码中,无须关心产品对象的具体组装过程， **只需确定具体建造者的类型**,建造者模式将复杂对象的构建与对象的表现分离开来,这样使得同样的构建过程可以创建出不同的表现



示例： KFC套餐

![image-20220308151001973](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/builder%20pattern%20KFC.png)

### 缺点

 建造者模式的缺点如下:

* 建造者模式所创建的产品一般具有较多的共同点,其组成部分相似,如果产品之间的差异性很大,则不适合使用建造者模式,因此其使用范围受到一定的限制。
* 如果产品的内部变化复杂,可能会导致需要定义很多具体建造者类来实现这种变化,导致系统变得很庞大。

### 简化

* 省略抽象建造者角色:如果系统中只需要一个具体建造者的话,可以省略掉抽象建造者。
* 省略指挥者角色:在具体建造者只有一个的情况下,如果抽象建造者角色已经被省略掉,那么还可以省略指挥者角色,让Builder角色扮演指挥者与建造者双重角色。

## Prototype

> 原型模式(Prototype Pattern):原型模式是一种对象创建型模式,用原型实例指定创建对象的种类,并且通过复制这些原型创建新的对象。原型模式允许一个对象再创建另外一个可定制的对象,无须知道任何创建的细节。

![image-20220308152010781](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/prototype%20pattern.png)

模式结构
• 原型模式包含如下角色:
• Prototype:抽象原型类
• ConcretePrototype:具体原型类
• Client:客户类



Java语言提供的`clone()`方法将对象浅拷贝了一份并返回给调用者。一般而言,`clone()`方法满足:

* 对任何的对象x,都有`x.clone() !=x`,即克隆对象与原对象不是同一个对象。
* 对任何的对象x,都有`x.clone().getClass()==x.getClass()`,即克隆对象与原对象的类型一样。
* 如果对象x的equals()方法定义恰当,那么`x.clone().equals(x)`应该成立。



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

> 组合模式(Composite Pattern):组合多个对象形成树形结构以表示“整体部分”的结构层次。组合模式对单个对象(即叶子对象)和组合对象(即容器对象)的使用具有一致性
>
> 组合模式又可以称为“整体部分”(Part-Whole)模式，属于**对象的结构模式**，它将对象组织到树结构中,可以用来描述整体与部分的关系

模式动机：

* 对于树形结构，当容器对象(如文件夹)的某一个方法被调用时，将遍历整个树形结构，寻找也包含这个方法的成员对象(可以是容器对象，也可以是叶子对象，如子文件夹和文件)并调用执行(递归调用)
* 由于容器对象和叶子对象在功能上的区别，在使用这些对象的客户端代码中必须有区别地对待容器对象和叶子对象，而实际上大多数情况下客户端希望一致地处理它们，因为对于这些对象的区别对待将会使得程序非常复杂
* 组合模式描述了如何将容器对象和叶子对象进行**递归组合**，使得用户在使用时无须对它们进行区分，可以一致地对待容器对象和叶子对象
* 事实上，Leaf类不可能实现Component类的`operation()`之外的方法，这样毫无意义。 因此组合模式分为两种：
  * 透明组合模式：把Leaf和Composite看成一个东西，Component类的所有方法都是抽象方法， 则Leaf必须实现所有这些方法
    * 好处：对Client而言， Leaf和Composite没有区别，可以直接针对Component抽象类编程
    * 坏处：Leaf的`operation()`之外的方法全都是无用方法，Leaf对这些方法的实现基本就是抛出异常。Client“透明”地处理Component时，（因为有Leaf存在）要么处理异常， 要么就用RTTI判断对象的实际类型，没有安全性，事实上也不可能透明
    * 因此透明组合模式就是个笑话
  * 安全组合模式：Component是一个**接口**，仅拥有抽象方法`operation（）`。 Composite和Leaf都实现Component接口，这样这两个子类的行为就是合理的。
    * 优点：Leaf和Composite的行为是合理的
    * 缺点：Leaf和Composite是两个不同的类型，使用的时候无法面向Component编程，即对Clietn不够透明

### 模式结构

* Component:抽象构件: 

  * client针对`Component`进行编程，无须知道它到底表示的是叶子还是容器，可以对其进行统一处理

  * 容器对象中既可以包含叶子，也可以包含容器，以此实现递归组合，形成一个树形结构
  * 抽象父类` Component`中，只有`operation （）`是抽象方法，其他方法都要提供实现， 否则Leaf类就要实现这些方法了（这是不可能的）

* Leaf:叶子构件

* Composite:容器构件

* Client:客户类





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

在Java AWT中使用的组合模式就是安全组合模式





![Safe Composite](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Safe%20Composite.png)

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

>
>
>将抽象部分与它的实现 部分分离，使它们都可以独立地变化。它是一种对象 结构型模式



* 桥接模式将抽象部分与它的实现部分分离，使它们都可以独立地变化。它是一种对象结构型模式，又称为柄体(Handle and Body)模式或接口(Interface)模式。

* 桥接模式包含如下四个角色:抽象类中定义了一个实现类接口类型的对象并可以维护该对象;扩充抽象类扩充由抽象类定义的接口，它实现了在抽象类中定义的抽象业务方法，在扩充抽象类中可以调用在实现类接口中定义的业务方法;实现类接口定义了实现类的接口，实现类接口仅提供基本操作，而抽象类定义的接口可能会做更多更复杂的操作;具体实现类实现了实现类接口并且具体实现它，在不同的具体实现类中提供基本操作的不同实现，在程序运行时，具体实现类对象将替换其父类对象，提供给客户端具体的业务操作方法。
* 在桥接模式中，抽象化(Abstraction)与实现化(Implementation)脱耦，
  它们可以沿着各自的维度独立变化。



* 桥接模式的主要优点是分离抽象接口及其实现部分，是比多继承方案更好的解决方法，桥接模式还提高了系统的可扩充性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统，实现细节对客户透明，可以对用户隐藏实现细节;其主要缺点是增加系统的理解与设计难度，且识别出系统中两个独立变化的维度并不是一-件容易的事情。
* 桥接模式适用情况包括:需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系;抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响;一个类存在两个独立变化的维度，且这两个维度都需要进行扩展;设计要求需要独立管理抽象化角色和具体化角色;不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统。

 ### 模式动机

![image-20220331135738563](/Users/lyk/Library/Application Support/typora-user-images/image-20220331135738563.png)

对于有**两个变化维度**(即两个变化的原因)的系 统，采用**方案二**来进行设计系统中类的个数更少， 且系统扩展更为方便。设计方案二即是桥接模式 的应用。桥接模式**将继承关系转换为关联关系**， 从而**降低了类与类之间的耦合**，减少了代码编写 量

### 模式结构

![image-20220331135826259](/Users/lyk/Library/Application Support/typora-user-images/image-20220331135826259.png)



* Abstraction
* RefinedAbstraction
* Implementor
* ConcreteImplementor

### 模式分析

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

	protected Implementor impl;**

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

模拟毛笔

现需要提供大中小3种型号的画笔，能够绘制5种不同颜色，如果使用蜡笔，我们需要准备3*5=15支蜡笔，也就是说必须准备15个具体的蜡笔类。而如果使用毛笔的话，只需要3种型号的毛笔，外加5个颜料盒，用3+5=8个类就可以实现15支蜡笔的功能。本实例使用桥接模式来模拟毛笔的使用过程。

![image-20220331141000077](/Users/lyk/Library/Application Support/typora-user-images/image-20220331141000077.png)

### 优点



* 分离抽象接口及其实现部分。
* 桥接模式有时类似于多继承方案，但是多继承方案违背了类的单一职责原则(即一个类只有-一个变化的原因)，复用性比较差，而且多继承结构中类的个数非常庞大，桥接模式是比多继承方案更好的解决方法。
* 桥接模式提高了系统的可扩充性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统。
* 实现细节对客户透明，可以对用户隐藏实现细节。

### 缺点

* 桥接模式的引入会增加系统的理解与设计难度，由于聚合关联关系建立在抽象层，要求开发者针对抽象进行设计与编程。
* 桥接模式要求正确识别出系统中两个独立变化的维度，因此其使用范围具有一定的局限性。

### 适用环境

在以下情况下可以使用桥接模式:

* 如果一个系统需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系，通过桥接模式可以使它们在抽象层建立一个关联关系。抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一一个实现化子类的对象进行组合，即系统需要对抽象化角色和实现化角色进行动态耦合。
* 一个类存在两个独立变化的维度，且这两个维度都需要进行扩展。虽然在系统中使用继承是没有问题的，但是由于抽象化角色和具体化角色需要独立变化，设计要求需要独立管理这两者。
* 对于那些不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。

### 模式扩展

适配器模式与桥接模式的联用

桥接模式和适配器模式用于设计的不同阶段,桥接模式用于系统的初步设计，对于存在两个独立变化维度的类可以将其分为抽象化和实现化两个角色，使它们可以分别进行变化;而在初步设计完成之后，当发现系统与已有类无法协同工作时，可以采用适配器模式。但有时候在设计初期也需要考虑适配器模式，特别是那些涉及到大量第三方应用接口的情况。

## Decorator

> 装饰模式(Decorator Pattern) :动态地给一个对象增加一些额外的职责(Responsibility),就增加对象功能来说，装饰模式比生成子类实现更为灵活。其别名也可以称为包装器(Wrapper)，与适配器模式的别名相同，但它们适用于不同的场合。根据翻译的不同，装饰模式也有人称之为“油漆工模式”，它是一种对象结构型模式。



* 装饰模式用于动态地给- -个对象增加一些额外的职责， 就增加对象功能来说，装饰模式比生成子类实现更为灵活。它是-一种对象结构型模式。
* 装饰模式包含四个角色:抽象构件定义了对象的接口，可以给这些对象动态增加职责(方法) ;具体构件定义了具体的构件对象，实现了在抽象构件中声明的方法，装饰器可以给它增加额外的职责(方法) ;抽象装饰类是抽象构件类的子类，用于给具体构件增加职责，但是具体职责在其子类中实现;具体装饰类是抽象装饰类的子类，负责向构件添加新的职责。
* 使用装饰模式来实现扩展比继承更加灵活，它以对客户透明的方式动态地给一个对象附加更多的责任。装饰模式可以在不需要创造更多子类的情况下，将对象的功能加以扩展。



* 装饰模式的主要优点在于可以提供比继承更多的灵活性，可以通过一种动态的方
  式来扩展-一个对象的功能，并通过使用不同的具体装饰类以及这些装饰类的排列
  组合，可以创造出很多不同行为的组合，而且具体构件类与具体装饰类可以独立
  变化，用户可以根据需要增加新的具体构件类和具体装饰类;其主要缺点在于使
  用装饰模式进行系统设计时将产生很多小对象，而且装饰模式比继承更加易于出
  错，排错也很困难，对于多次装饰的对象，调试时寻找错误可能需要逐级排查，
  较为烦琐。
* 装饰模式适用情况包括:在不影响其他对象的情况下，以动态、透明的方式给单个对象添加职责;需要动态地给-一个对象增加功能，这些功能也可以动态地被撤销;当不能采用继承的方式对系统进行扩充或者采用继承不利于系统扩展和维护时。
* 装饰模式可分为透明装饰模式和半透明装饰模式:在透明装饰模式中，要求客户端完全针对抽象编程，装饰模式的透明性要求客户端程序不应该声明具体构件类型和具体装饰类型，而应该全部声明为抽象构件类型;半透明装饰模式允许用户在客户端声明具体装饰者类型的对象，调用在具体装饰者中新增的方法。



### 模式结构

![image-20220331142333746](/Users/lyk/Library/Application Support/typora-user-images/image-20220331142333746.png)

* Component
* ConcreteComponent
* Decorator：抽象装饰类
* ConcreteDecorator

### 模式分析

* 与继承关系相比，关联关系的主要优势在于不会破坏类的封装性，而且**继承是一种耦合度较大的静态关系，无法在程序运行时动态扩**
  **展**。在软件开发阶段，关联关系虽然不会比继承关系减少编码量，但是到了软件维护阶段，由于关联关系使系统具有较好的**松耦合性**，因此使得**系统更加容易维护**。当然，关联关系的缺点是**比继承关系要创建更多的对象**。
* 使用装饰模式来实现扩展比继承更加灵活，**它以对客户透明的方式动态地给一个对象附加更多的责任**。装饰模式可以在不需要创造更多子类的情况下，将对象的功能加以扩展。



* 简化：如果只有一个具体构件类而没有抽象构件类，那么抽象装饰类可以作为具体构件类的直接子类。

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

半透明(semi-transparent)的装饰模式允许用户在客户端声明具体装饰者
类型的对象，调用在具体装饰者中新增的方法。

```java
Transform camaro;
camaro=new Car();
camaro.move();
Robot bumblebee=new Robot(camaro); bumblebee.move();
bumblebee.say();
```

#### 示例

变形金刚在变形之前是一辆汽车，它可以在陆地上移动。当它变成机器人之后除了能够在陆地上移动之
外，还可以说话;如果需要，它还可以变成飞机，除了在陆地.上移动还可以在天空中飞翔。

![image-20220331143604092](/Users/lyk/Library/Application Support/typora-user-images/image-20220331143604092.png)

### 透明装饰模式

在透明装饰模式中，要求**客户端完全针对抽象编程**，装饰模式的透明性要求客户端程序不应该声明具体构件类型和具体装饰类型，而应该全部声明为抽象构件类型。

```java
Cipher sc,cc,ac;
sc=new SimpleCipher(); 
cc=new ComplexCipher(sc); 
ac=new AdvancedCipher(cc);
```

#### 示例

某系统提供了一个数据加密功能，可以对字符串进行加密。最简单的加密算法通过对字母进行移位来实现，同时还提供了稍复杂的逆向输出加密，还提供了更为高级的求模加密。用户先使用最简单的加密算法对字符串进行加密，如果觉得还不够可以对加密之后的结果使用其
他加密算法进行二次加密，当然也可以进行第三次加密。现使用装饰模式设计该多重加密系统。



![image-20220331144159672](/Users/lyk/Library/Application Support/typora-user-images/image-20220331144159672.png)



### 优点

* 装饰模式与继承关系的目的都是要扩展对象的功能，但是**装饰模式可以提供比继承更多的灵活性**。
* 可以**通过一种动态的方式来扩展一个对象的功能**，通过配置文件可以在运行时选择不同的装饰器，从而实现不同的行为
* **通过使用不同的具体装饰类以及这些装饰类的排列组合，可以创造出很多不同行为的组合**。可以使用多个具体装饰类来装饰同一对象，得到功能更
  为强大的对象。
* 具体构件类与具体装饰类可以独立变化，用户可以根据需要增加新的具体构件类和具体装饰类，在使用时再对其进行组合，原有代码无须改变，符合“开闭原则”

### 缺点

* 使用装饰模式进行系统设计时**将产生很多小对象**，这些对象的区别在于它们之间相互连接的方式有所不同，而不是它们的类或者属性值有所不同，同时还将产生很多具体装饰类。这些装饰类和小对象的产生将增加系统的复杂度，加大学习与理解的难度。

* 这种比继承更加灵活机动的特性，也同时意味着**装饰模式比继承更加易于出错**，排错也很困难，对于多次装饰的对象，调试时寻找错误可能需要逐级排查，较为烦琐。

### 适用环境

* 在不影响其他对象的情况下，**以动态、透明的方式给单个对象添加职责**。
* 需要**动态地给一个对象增加功能**，这些功能也可以动态地被撤销。
* **当不能采用继承的方式对系统进行扩充或者采用继承不利于系统扩展和维护时**。不能采用继承的情况主要有两类:第一类是系统中存在大量独立的扩展，为支持每一种组合将产生大量的子类，使得子类数目呈爆炸性增长;第二类是因为类定义不能继承(如final类)

## Facade 

>外观模式(Facade Pattern):外部与一个子系统的通信必须通过-一个统一的外观对象进行，为子系统中的一组接口提供一个- -致的界面，外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。外观模式又称为门面模式，它是一种对象结构型模式。

* 在外观模式中，外部与一个子系统的通信必须通过--个统-的外观对象进行，为子系统中的一-组接口提供一个一致的界面，外观模式定义了一一个高层接口，这个接口使得这一子系统更加容易使用。外观模式又称为门面模式，它是--种对象结构型模式。
* 外观模式包含两个角色:外观角色是在客户端直接调用的角色，在外观角色中可以知道相关的(一个或者多个)子系统的功能和责任，它将所有从客户端发来的请求委派到相应的子系统去，传递给相应的子系统对象处理;在软件系统中可以同时有一个或者多个子系统角色，每一个子系统可以不是-一个单独的类，而是一个类的集合，它实现子系统的功能。
* 外观模式要求一一个子系统的外部与其内部的通信通过-一个统-一的外观对象进行，外观类将客户端与子系统的内部复杂性分隔开，使得客户端只需要与外观对象打交道，而不需要与子系统内部的很多对象打交道。
* 外观模式主要优点在于对客户屏蔽子系统组件，减少了客户处理的对象数目并使得子系统使用起来更加容易，它实现了子系统与客户之间的松耦合关系，并降低了大型软件系统中的编译依赖性，简化了系统在不同平台之间的移植过程;其缺点在于不能很好地限制客户使用子系统类，而且在不引入抽象外观类的情况下，增加新的子系统可能需要修改外观类或客户端的源代码，违背了“开闭原则”。
* 外观模式适用情况包括:要为一一个复杂子系统提供一一个简单接口;客户程序与多个子系统之间存在很大的依赖性;在层次化结构中，需要定义系统中每-层的入口，使得层与层之间不直接产生联系。



![image-20220331150700925](/Users/lyk/Library/Application Support/typora-user-images/image-20220331150700925.png)

### 模式结构

* Facade
* SubSystem

### 模式分析

* 根据“单一职责原则”，在软件中将一个系统划分为若干个子系统有利于降低整个系统的复杂性，一个常见的设计目标是使子系统间
  的通信和相互依赖关系达到最小，而达到该目标的途径之一就是引入一个外观对象，它为子系统的访问提供了一个简单而单一的入口。
* 外观模式也是“迪米特法则”的体现，通过**引入一个新的外观类可以降低原有系统的复杂度，同时降低客户类与子系统类的耦合度**。
* 外观模式要求-一个子系统的外部与其内部的通信通过一个统-一的外观对象进行，外观类将客户端与子系统的内部复杂性分隔开，使得客户端只需要与外观对象打交道，而不需要与子系统内部的很多对象打交道。
* 外观模式的目的在于降低系统的复杂程度。
* 外观模式从很大程度上提高了客户端使用的便捷性，使得客户端无须关心子系统的工作细节，通过外观角色即可调用相关功能。

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

电源总开关

现在考察一个电源总开关的例子，以便进一步说明外观模式。为了使用方便，一一个电源总开关可以控制四盏灯、一个风扇、一台空调和一台电视机的启动和关闭。通过该电源总开关可以同时控制上述所有电器设备，使用外观模式设计该系统。

![image-20220331151303257](/Users/lyk/Library/Application Support/typora-user-images/image-20220331151303257.png)

### 优点

* 对客户屏蔽子系统组件，减少了客户处理的对象数目并使得子系统使用起来更加容易。通过引入外观模式，客户代码将变得很简单，与之关联的对象也
  很少。
* 实现了子系统与客户之间的松耦合关系，这使得子系统的组件变化不会影响
  到调用它的客户类，只需要调整外观类即可。
* 降低了大型软件系统中的编译依赖性，并简化了系统在不同平台之间的移植
  过程，因为编译一个子系统一般不需要编译所有其他的子系统。一-个子系统
  的修改对其他子系统没有任何影响，而且子系统内部变化也不会影响到外观
  对象。
* 只是提供了一个访问子系统的统一入口，并不影响用户直接使用子系统类。

### 缺点

* 不能很好地限制客户使用子系统类，如果对客户访问子系统类做太多的限制则减少了可变性和灵活性。
* 在不引入抽象外观类的情况下，增加新的子系统可能需要修改外观类或客户端的源代码，违背了“开闭原则”。

### 适用环境

* 当要为一-个复杂子系统提供一个简单接口时可以使用外观模式。该接口可以满足大多数用户的需求，而且用户也可以越过外观类直接访问子系统。
* 客户程序与多个子系统之间存在很大的依赖性。引入外观类将子系统与客户以及其他子系统解耦，可以提高子系统的独立性和可移植性。
* 在层次化结构中，可以使用外观模式定义系统中每一层的入口，层与层之间不直接产生联系，而通过外观类建立联系，降低层之间的耦合度。



```java
public class JDBCFacade {
	private Connection conn=null;
	private Statement statement=null;
  
	public void open(String driver,String jdbcUrl,String userName,String userPwd) 
  {
		...... 
  }
  
	public int executeUpdate(String sql) 
  { 
    ......
	}
  
	public ResultSet executeQuery(String sql) 
  {
		...... 
  }
  
	public void close() 
  { 
    ......
	} 
}
```

### 模式扩展

* **不要试图通过外观类为子系统增加新行为**，不要通过继承一个外观类在子系统中加入新的行为，这种做法是错误的。外观模式的用意是为子系统提供一个集中化和简化的沟通渠道，而不是向子系统加入新的行为，新的行为的增加应该通过修改原有子系统类或增加新的子系统类来实现，不能通过外观类来实现。
* 外观模式<u>创造出一个外观对象，将客户端所涉及的属于一个子系统的协作伙伴的数量减到最少，使得客户端与子系统内部的对象的相互作用被外观对象所取代</u>。外观类充当了客户类与子系统类之间的“第三者降低了客户类与子系统类之间的耦合度，外观模式就是实现代码重构以便达到“迪米特法则”’要求的一个强有力的武器。
* 外观模式最大的缺点在于违背了“开闭原则”，，当增加新的子系统或者移除子系统时需要修改外观类，可以通过引入抽象外观类在一定程度上解决该问题，客户端针对抽象外观类进行编程。对于新的业务需求，不修改原有外观类，而对应增加一个新的具体外观类，由新的具体外观类来关联新的子系统对象，同时通过修改配置文件来达到不修改源代码并更换外观类的目的。

## Flyweight

默认是复合享元模式：

![image-20220331153143006](/Users/lyk/Library/Application Support/typora-user-images/image-20220331153143006.png)



* 还有一种单纯享源模式，其中所有的享元对象都是可以共享的，即所有抽象享元类的子类都可共享，不存在非共享具体享元类。

### 模式结构

* Flyweight:抽象享元类
* ConcreteFlyweight:具体享元类
* UnsharedConcreteFlyweight:非共享具体享元类
* FlyweightFactory:享元工厂类

### 模式分析

* 享元模式是一个考虑系统性能的设计模式，通过使用享元模式可以节约内存空间，提高系统的性能。

* 享元模式的核心在于享元工厂类，享元工厂类的作用在于提供-一个用于存储享元对象的享元池，用户需要对象时，首先从享元池中获取，如果享元池中不存在,则创建- -个新的享元对象返回给用户，并在享元池中保存该新增对象。

* 享元模式以共享的方式高效地支持大量的细粒度对象，享元对象能做到共享的关键是区分内部状态(Internal State)和外部状(External State)。
  1. 内部状态是存储在享元对象内部并且不会随环境改变而改变的状态，因
     此内部状态可以共享。
  2. 外部状态是随环境改变而改变的、不可以共享的状态。享元对象的外部
     状态必须由客户端保存，并在享元对象被创建之后，在需要使用的时候再
     传入到享元对象内部。一个外部状态与另一个外部状态之间是相互独立的。



### code

FlyweightFactory:

```java
public class FlyweightFactory 
{
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
	public Flyweight(String intrinsicState) {
	this.intrinsicState = intrinsicState; }
	public void operation(String extrinsicState) 
  {
		...... 
  }
}
```



### 优点

* 享元模式的优点在于它可以极大减少内存中对象的数量，使得相同对象或相似对象在内存中只保存一-份。

* 享元模式的外部状态相对独立，而且不会影响其内部状态，从而使得享元对象可以在不同的环境中被共享。

### 缺点

* 享元模式使得系统更加复杂，需要分离出内部状态和外部状态，这使得程序的逻辑复杂化。
* 为了使对象可以共享，享元模式需要将享元对象的状态外部化，而读取外部状态使得运行时间变长。

### 适用环境

* **一个系统有大量相同或者相似的对象**，由于这类对象的大量使用，造成内存的大量耗费。
* **对象的大部分状态都可以外部化**，可以将这些外部状态传入对象中。
* 使用享元模式需要维护一-个存储享元对象的享元池，而这需要耗费资源，因此，**应当在多次重复使用享元对象**
  **时才值得使用享元模式。**

### 模式扩展

享元模式与其他模式的联用

* 在享元模式的享元工厂类中通常提供一个静态的工厂方法用于返回享元对象，使用简单工厂模式来生成享元对象。在一个系统中，通常只有唯一-- -个享元工厂，因此享元工厂类可以使用单例模式进行设计。
* 享元模式可以结合组合模式形成复合享元模式，统- -对享元对象设置外部状态。

## Proxy

> 代理模式(Proxy Pattern) :给某-一个对象提供一一个代理，并由代理对象控制对原对象的引用。代理模式的英文叫做Proxy或Surrogate,它是一种对象结构型模式



* 远程代理为一个位于不同的地址空间的对象提供-一个本地的代表对象，它使得客户端可以访问在远程机器上的对象，远程机器可能具有更好的计算性能与处理速度，可以快速响应并处理客户端请求。
* 如果需要创建-一个资源消耗较大的对象，先创建-一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建，这个小对象称为虚拟代理。虚拟代理通过使用-一个小对象来代表一一个大对象，可以减少系统资源的消耗，对系统进行优化并提高运行速度。
* 保护代理可以控制对一一个对象的访问，可以给不同的用户提供不同级别
  的使用权限。

![image-20220331154325874](/Users/lyk/Library/Application Support/typora-user-images/image-20220331154325874.png)

### 模式结构

* Subject:抽象主题角色
* Proxy:代理主题角色
* RealSubject:真实主题角色

### code

```java
public class Proxy implements Subject {
	private RealSubject realSubject = new RealSubject();
	public void preRequest() {......}
	public void request()
	{
		preRequest(); realSubject.request(); postRequest();
	}
	public void postRequest() {......}
}
```

### 优点

* 代理模式能够协调调用者和被调用者，在一定程度上降低了系统的耦合度。
* 远程代理使得客户端可以访问在远程机器.上的对象，远程机器可能具有更好的计算性能与处理速度，可以快速响应并处理客户端请求。
* 虚拟代理通过使用一个小对象来代表一-个大对象，可以减少系统资源的消耗，对系统进行优化并提高运行速度。
* 保护代理可以控制对真实对象的使用权限。



### 缺点

* 慢

### 模式环境

根据代理模式的使用目的，常见的代理模式有以下几种类型:

* 远程(Remote)代理:为一个位于不同的地址空间的对象提供一一个 本地的代理，对象，这个不同的地址空间可以是在同一台主机中，也可以在另一台主机中，远程代理又叫做大使(Ambassador)
* 虚拟(Virtual)代理:如果需要创建一个资源消耗较大的对象，先创建一个消耗相对较小的对象来表示，真实对象只在需要时才会被真正创建。
* Copy- on-Write代理:它是虚拟代理的一种，把复制(克隆)操作延迟到只有在客户端真正需要时才执行。一般来说，对象的深克隆是一-个开销较大的操作，Copy-on-Write代理可以让这个操作延迟，只有对象被用到的时候才被克隆。



根据代理模式的使用目的，代理模式有以下几种类型(续) :

* 保护(Protect or Access)代理:控制对一个对象的访问，可以给不同的用户提供不同级别的使用权限。
* 缓冲(Cache)代理:为某一个目标操作的结果提供临时的存储空间，以便多个客户端可以共享这些结果。
* 防火墙(Firewall)代理:保护目标不让恶意用户接近。
* 智能引用(Smart Reference)代理:当一个对象被引用时，提供一些额外的操作，如将此对象被调用的次数记录下来等。

# Behavioral Patterns

## Strategy

> 策略模式定义了一系列可替换的算法，让client决定使用哪个



![image-20220308141217513](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/strategy%20pattern.png)

### 参与者

* 上下文（Context ) ： 拥有Strategy对象的一个引用； 被配置了具体策略 ConcreteStrategy；
* 策略（Strategy）: 声明了所支持策略的接口。 Context利用这些被ConcreteStrategy定义的接口。
* 具体策略（ConcreteStrategy）: 实现了Strategy声明 的接口，给出了具体的实现。

### 协作

* 上下文`Context`和`Strategy`的相互协作完成整个算法。 `Context`可能会通过提供方法让`Strategy`访问其数据；甚 至将自身的引用传给`Strategy`，供其访问其数据。 `Strategy`会在需要的时候访问`Context`的成员变量。
* 上下文`Context`将一些对他的请求转发给策略类来实现 ，客户（`Client`）通常创建`ConcreteStrategy`的对象，然 后传递给C`ontext`来灵活配置`Strategy`接口的具体实现； 这样`Client`就有可以拥有一个`Strategy`接口的策略族，其 中包含多种`ConcreteStrategy`的实现。

### 应用场景

* 当很多相关类只在它们的行为的实现上不一样。策略模式提供了一个很好的方式来配置某个类，让其具有上述多种实现之一。
* 当我们需要同一个行为的不同实现（变体）的时候。策略模式可以用作实现这些变体。
* 算法需要用到一些数据，而这些数据不应该被客户知道。我们可以通过策略模式隐藏复杂的算法和数据接口。
*  一个类定义了很多行为，这些行为作为一个`switch`选择语句的分支执行部分。策略模式可以消除这些分支选择

### 注意点

* `Strategy`可以是接口，也可以是类。如果是类，则可以抽象所有具体算法中公共的实现部分。
* 当然，我们也可以直接通过Context的子类来实现不同的 Context实现。不过这样算法的具体实现，就和算法的利用的 实现项目交织在一起，不利于理解和维护.
* 策略模式消除了类似根据策略类型的Switch语句。 
* 可以动态选择不同的策略 • 客户必须提前知晓各自不同的策略。 
* Context和Strategy之间的通讯是有代价的。Context提供了对 其成员变量的访问方式。可以有时候，对于某些具体的策略 的实现ConcreteStrategy可能并不需要全部的访问，这会存在一定的隐患。
* 策略模式会创建出较多的对象。





## Command

>  命令模式(Command Pattern): 将一个请求封装为一个对象,从而使我们可用不同的请求对客户进行参数化; 对请求排队或者记录请求日志,以及支持可撤销的操作。命令模式是一种对象行为型模式,其别名为动作(Action)模式或事务(Transaction)模式



client把receiver传给command， 然后把这个command传给invoker， client只要调用invoker的invoke（）



![image-20220308152816123](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/command%20pattern.png)

 ### 模式结构

* 命令模式包含如下角色:
* Command: 抽象命令类
* ConcreteCommand: 具体命令类
* Invoker:  调用者
* Receiver:  接收者
* Client: 客户类

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
```




}抽象的Command类：

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
    public void action(){ 
        this.command.execute(); 
    }
}
```



具体的Command类ConcreteCommand1、ConcreteCommand2：

```java
public class ConcreteCommand1 extends Command { 
    //对哪个Receiver类进行命令处理 
    private Receiver receiver; 
    //构造函数传递接收者 
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
    //哪个Receiver类进行命令处理 
    private Receiver receiver; 
    //构造函数传递接收者 
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







场景类Client：

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
        invoker.action(); 
    } 
}
```







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

>观察者模式(Observer Pattern):定义对象间的一种一对多依赖关系,使得每当一个对象状态发生改变时,其相关依赖对象皆得到通知并被自动更新。观察者模式又叫做发布-订阅(Publish/Subscribe)模式、模型-视图(Model/View)模式、源-监听器(Source/Listener)模式或从属者(Dependents)模式。观察者模式是一种**对象行为型模式**



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



客户端代码片段如下所示:

```java
Subject subject = new ConcreteSubject();
Observer observer = new ConcreteObserver();
subject.attach(observer);
subject.notify();
```

### 优缺点

优点：

* 实现了表示层和数据逻辑层的分离

## Mediator

> 中介者模式(Mediator Pattern): 用一个中介对象来封装一系列的对象交互,中介者使各对象不需要显式地相互引用,从而**使其耦合松散**,而且可以独立地改变它们之间的交互。中介者模式又称为调停者模式,它是一种对象行为型模式

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

中介者模式可以使对象之间的关系数量急剧减少：

![image-20220315161530458](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/medicator%20pattern%20advantage.png)

### 缺点

具体中介者类可能会非常复杂

## Template Method

> 模板方法模式的结构和用法也是面向对象设计的核心之一。模板方法模式是一种**类的行为型模式**,在它的结构图中只有类之间的继承关系,没有对象关联关系
>
> 模板方法模式是基于继承的代码复用基本技术,在模板方法模式中,可以将相同的代码放在父类中,而将不同的方法实现放在不同的子类中具体子类的基本方法将覆盖父类中定义的基本方法,子类的钩子方法也将覆盖父类的钩子方法,从而可以通过在子类中实现的钩子方法对父类方法的执行进行约束,实现子类对父类行为的**反向控制**
>
> 

* 在模板方法模式中,定义一个操作中算法的骨架,而将一些步骤延迟到子类中,模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。模板方法是一种类行为型模式
* 模板方法模式包含两个角色:在抽象类中定义一系列基本操作,这些基本操作可以是具体的,也可以是抽象的,同时,在抽象类中实现了一个模板方法,用于具体子类是抽象类的子类,以完成子类特定算法的步骤,也可以覆盖在父类中实现的具体基本操作



![Template Method Pattern](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Template%20Method%20Pattern.png)

### 模式结构

* AbstractClass
* ConcreteClass



模式分析：

* 模板方法: 定义在抽象类中， 定义一个算法的骨架;，是基本方法的组合
* 基本方法: **用于实现模板方法中的各个步骤**,是模板方法的组成部分。 如果抽象父类提供了默认实现，子类只需要继承就可以拥有这些方法， 子类也可以定义自己的实现
  * 抽象方法(Abstract Method)
  * 具体方法(Concrete Method)
  * 钩子方法(Hook Method)
    * 挂钩方法
    * 空方法

### code

钩子方法：

```java
public void template()
{
	open();
	display();
	if(isPrint())
	{
		print();
	}
}

public boolean isPrint()
{
	return true;
}
```



抽象类代码:

```java
public abstract class AbstractClass
{
	public void templateMethod() //模板方法
	{
		primitiveOperation1();
		primitiveOperation2();
		primitiveOperation3();
	}
    
	public void primitiveOperation1() //基本方法—具体方法
	{
	//实现代码
	}
    
	public abstract void primitiveOperation2(); //基本方法—抽象方法
    
	public void primitiveOperation3() //基本方法—钩子方法
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

实例二: 数据库操作模板

对数据库的操作一般包括连接、打开、使用、关闭等步骤，在数据库操作模板类中我们定义了connDB()、openDB()、useDB()、closeDB()四个方法分别对应这四个步骤。对于不同类型的数据库( 如SQL Server和Oracle)其操作步骤都一致，只是连接数据库connDB()方法有所区别，现使用模板方法模式对其进行设计：



![Template Method Pattern database](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/Template%20Method%20Pattern%20database.png)

### 优点

* 模板方法模式在一个类中抽象地定义算法，而由它的子类实现细节的处理



* 代码复用



* 模板方法模式导致一种反向的控制结构，通过一个父类调用其子类的操作，通过对子类的扩展增加新的行为，符合“开闭原则”

### 缺点

每个不同的实现都需要定义一个子类，这会导致类的个数增加，系统更加庞大，设计也更加抽象，但是更加符合“单一职责原则”，使得类的内聚性得以提高

### 好莱坞原则

*“不要给我们打电话， 我们会给你打电话(Don 't call us, we’11 call you)*

好莱坞原则(Hollywood Principle)： 子类不显式调用父类的方法，而是通过覆盖父类的方法来实现某些具体的业务逻辑，父类控制对子类的调用



在模板方法模式中，好莱坞原则体现在:子类不需要调用父类，而通过父类来调用子类，将某些步骤的实现写在子类中，由父类来控制整个过程

### 钩子方法

钩子方法的引入使得子类可以控制父类的行为

* 最简单的钩子方法就是空方法，也可以在钩子方法中定义一个默认的实现，如果子类不覆盖钩子方法，则执行父类的默认实现代码

* 比较复杂一点的钩子方法可以对其他方法进行约束，这种钩子方法通常返回一个boolean类型，即返回true或false,用来判断是否执行某一个基本方法

