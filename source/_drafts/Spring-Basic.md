---
title: Spring Basic
tags:
---



JavaBean是POJO的同义词。

为了降低Java开发的复杂性,Spring采取了以下4种关键策略:
基于POJO的轻量级和最小侵入性编程;
通过依赖注入和面向接口实现松耦合;
基于切面和惯例进行声明式编程;
通过切面和模板减少样板式代码。



容器是Spring框架的核心。Spring容器使用DI管理构成应用的组件,
它会创建相互协作的组件之间的关联。毫无疑问,这些对象更简单干
净,更易于理解,更易于重用并且更易于进行单元测试。
Spring容器并不是只有一个。Spring自带了多个容器实现,可以归为
两种不同的类型。bean工厂(由org.springframework. beans.
factory.eanFactory接口定义)是最简单的容器,提供基本的DI
支持。应用上下文
(由org.springframework.context.ApplicationContext
接口定义)基于BeanFactory构建,并提供应用框架级别的服务,例如
从属性文件解析文本信息以及发布应用事件给感兴趣的事件监听者。
虽然我们可以在bean工厂和应用上下文之间任选一种,但bean工厂对
大多数应用来说往往太低级了,因此,应用上下文要比bean工厂更受
欢迎。我们会把精力集中在应用上下文的使用上,不再浪费时间讨论
bean工厂。

# Bean

在基于Spring的应用中,你的应用对象生存于Spring容器(container)
中。Spring容器负责创建对象,装配它们,配置它们并
管理它们的整个生命周期,从生存到死亡(在这里,可能就是new到
finalize())。

Spring通过应用上下文(Application Context)装载bean的定义并把它
们组装起来。Spring应用上下文全权负责对象的创建和组装。Spring
自带了多种应用上下文的实现,它们之间主要的区别仅仅在于如何加
载配置。

## 使用应用上下文

Spring自带了多种类型的应用上下文。下面罗列的几个是你最有可能
遇到的。
`AnnotationConfigApplicationContext`:从一个或多个
基于Java的配置类中加载Spring应用上下文。
`AnnotationConfigWebApplicationContext`:从一个或
多个基于Java的配置类中加载Spring Web应用上下文。
`ClassPathXmlApplicationContext`:从类路径下的一个或
多个XML配置文件中加载上下文定义,把应用上下文的定义文件
作为类资源。
`FileSystemXmlapplicationcontext`:从文件系统下的一
个或多个XML配置文件中加载上下文定义。
`XmlWebApplicationContext`:从Web应用下的一个或多个
XML配置文件中加载上下文定义。

## bean的生命周期

![image-20220303201526805](/home/lyk/.config/Typora/typora-user-images/image-20220303201526805.png)

正如你所见,在bean准备就绪之前,bean工厂执行了若干启动步骤。
我们对图1.5进行详细描述:

1. Spring对bean进行实例化;
2. Spring将值和bean的引用注入到bean对应的属性中;
3. 如果bean实现了BeanNameAware接口,Spring将bean的ID传递给
   setBean-Name()方法;
4. 如果bean实现了BeanFactoryAware接口,Spring将调
   用setBeanFactory()方法,将BeanFactory容器实例传入;
5. 如果bean实现了ApplicationContextAware接口,Spring将调
   用setApplicationContext()方法,将bean所在的应用上下文的
   引用传入进来;
6. 如果bean实现了BeanPostProcessor接口,Spring将调用它们
   的post-ProcessBeforeInitialization()方法;
7. 如果bean实现了InitializingBean接口,Spring将调用它们的
   after-PropertiesSet()方法。类似地,如果bean使用init-
   method声明了初始化方法,该方法也会被调用;
8. 如果bean实现了BeanPostProcessor接口,Spring将调用它们
   的post-ProcessAfterInitialization()方法;
9. 此时,bean已经准备就绪,可以被应用程序使用了,它们将一直
   驻留在应用上下文中,直到该应用上下文被销毁;
10. 如果bean实现了DisposableBean接口,Spring将调用它的
    destroy()接口方法。同样,如果bean使用destroy-method声明
    了销毁方法,该方法也会被调用。
