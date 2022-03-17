---
title: Software System Design Intro
categories: Software Engineering
---

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



# 设计模式

* Expert designers know not to solve every problem from first principles, they reuse solutions : **"不要造轮子"**
* **HAS-A can be better than IS-A**
  1.  Composition gives you a lot more flexibility.
  2. Not only does it let you encapsulate a family of
     algorithms into their own set of classes, but it
     also lets you change behavior at runtime.

## 策略模式

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



## 简单工厂模式



策略模式解决的是**行为问题**, 工厂模式解决**对象创建问题**

![image-20220315145604053](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/simple%20factory%20pattern)

模式结构

* Factory：  工厂角色
* Product：抽象产品
* ConcreteProduct： 具体产品角色



例子：

![image-20220315145955575](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/simple%20factory%20user_manager)

简单工厂模式的缺点

* 当有新产品要加入到系统中时,必须修改工厂类,加入必要的处理逻辑,这违背了“开闭原则”

## 工厂方法模式

> 在工厂方法模式中,核心的工厂类不再负责所有产品的创建,而是将具体创建工作交给子类去做。这
> 个核心类仅仅负责给出具体工厂必须实现的接口,而不负责哪一个产品类被实例化这种细节,这使得
> **工厂方法模式可以在不修改工厂角色的情况下引进新产品**

![image-20220315150329091](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/factory%20method%20pattern)

很好地符合了“开闭原则”

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

### 缺点

* 添加新产品时，不仅要添加新的产品类，还要添加对应的具体工厂类，增加系统的复杂度



## 抽象工厂模式

> 抽象工厂模式(Abstract Factory Pattern):提供一个创
> 建一系列相关或相互依赖对象的接口,而无须指定它们
> 具体的类。抽象工厂模式又称为Kit模式,属于对象创建
> 型模式。

概念：

* 产品等级结构： 即产品的继承结构。 如抽象类是电视机， 而子类有海信电视机， TCL电视机， 则抽象电视机与具体品牌的电视机构成了一个产品等级结构
* 产品族：由同一个工厂生产的，位于不同产品等级结构中的一组产品。 如海尔是一个产品族， 海尔电视机属于电视机产品结构， 电冰箱位于电冰箱产品结构





![image-20220315151244481](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/abstract%20factory%20pattern)

模式结构：

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



## 建造者模式

> 建造者模式可以将一个复杂对象的构建与它的表示分离,使得同样的构建过程可以创建不同的表示.将部件和其组装过程分开,一步一步创建一个复杂的对象

![image-20220308144855351](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/builder%20pattern.png)

模式结构

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

## 原型模式

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

## 状态模式

>  状态模式(State Pattern) :允许一个对象在其内部状态改变时改变它的行为,对象看起来似乎修改了它的类。其别名为状态对象(Objects for States), 状态模式是一种对象行为型模式。



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



## 命令模式

>  命令模式(Command Pattern): 将一个请求封装为一个对象,从而使我们可用不同的请求对客户进行参数化; 对请求排队或者记录请求日志,以及支持可撤销的操作。命令模式是一种对象行为型模式,其别名为动作(Action)模式或事务(Transaction)模式



![image-20220308152816123](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/command%20pattern.png)

 模式结构

* 命令模式包含如下角色:
* Command: 抽象命令类
* ConcreteCommand: 具体命令类
* Invoker:  调用者
* Receiver:  接收者
* Client: 客户类

## 观察者模式

>观察者模式(Observer Pattern):定义对象间的一种一对多依赖关系,使得每当一个对象状态发生改变时,其相关依赖对象皆得到通知并被自动更新。观察者模式又叫做发布-订阅(Publish/Subscribe)模式、模型-视图(Model/View)模式、源-监听器(Source/Listener)模式或从属者(Dependents)模式。观察者模式是一种对象行为型模式。

![image-20220315142422314](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/observer%20pattern.png)



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

## 中介者模式

![image-20220315161423254](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/%E8%BD%AF%E4%BB%B6%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1/medicator%20pattern)

模式结构：

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
