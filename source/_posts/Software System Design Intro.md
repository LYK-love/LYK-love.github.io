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

