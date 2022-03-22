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

https://docs.spring.io/spring-javaconfig/docs/1.0.0.M4/reference/html/ch02s02.html

To declare a bean, simply annotate a method with the `@Bean` annotation. When JavaConfig encounters such a method, it will execute that method and register the return value as a bean within a `BeanFactory`. By default, the bean name will be the same as the method name (see [bean naming](https://docs.spring.io/spring-javaconfig/docs/1.0.0.M4/reference/html/ch02s02.html) for details on how to customize this behavior). The following is a simple example of a `@Bean` method declaration:

```
@Configuration
public class AppConfig {
    @Bean
    public TransferService transferService() {
        return new TransferServiceImpl();
    }
}
```





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

##  定制Bean

### Scope

对于Spring容器来说，当我们把一个Bean标记为`@Component`后，它就会自动为我们创建一个单例（Singleton），即容器初始化时创建Bean，容器关闭前销毁Bean。在容器运行期间，我们调用`getBean(Class)`获取到的Bean总是同一个实例。

还有一种Bean，我们每次调用`getBean(Class)`，容器都返回一个新的实例，这种Bean称为Prototype（原型），它的生命周期显然和Singleton不同。声明一个Prototype的Bean时，需要添加一个额外的`@Scope`注解：

```
@Component
@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE) // @Scope("prototype")
public class MailSession {
    ...
}
```

### 注入List

有些时候，我们会有一系列接口相同，不同实现类的Bean。例如，注册用户时，我们要对email、password和name这3个变量进行验证。为了便于扩展，我们先定义验证接口：

```
public interface Validator {
    void validate(String email, String password, String name);
}
```

然后，分别使用3个`Validator`对用户参数进行验证：

```
@Component
public class EmailValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (!email.matches("^[a-z0-9]+\\@[a-z0-9]+\\.[a-z]{2,10}$")) {
            throw new IllegalArgumentException("invalid email: " + email);
        }
    }
}

@Component
public class PasswordValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (!password.matches("^.{6,20}$")) {
            throw new IllegalArgumentException("invalid password");
        }
    }
}

@Component
public class NameValidator implements Validator {
    public void validate(String email, String password, String name) {
        if (name == null || name.isBlank() || name.length() > 20) {
            throw new IllegalArgumentException("invalid name: " + name);
        }
    }
}
```

最后，我们通过一个`Validators`作为入口进行验证：

```
@Component
public class Validators {
    @Autowired
    List<Validator> validators;

    public void validate(String email, String password, String name) {
        for (var validator : this.validators) {
            validator.validate(email, password, name);
        }
    }
}
```

注意到`Validators`被注入了一个`List<Validator>`，Spring会自动把所有类型为`Validator`的Bean装配为一个`List`注入进来，这样一来，我们每新增一个`Validator`类型，就自动被Spring装配到`Validators`中了，非常方便。

因为Spring是通过扫描classpath获取到所有的Bean，而`List`是有序的，要指定`List`中Bean的顺序，可以加上`@Order`注解：

```
@Component
@Order(1)
public class EmailValidator implements Validator {
    ...
}

@Component
@Order(2)
public class PasswordValidator implements Validator {
    ...
}

@Component
@Order(3)
public class NameValidator implements Validator {
    ...
}
```

### 可选注入

默认情况下，当我们标记了一个`@Autowired`后，Spring如果没有找到对应类型的Bean，它会抛出`NoSuchBeanDefinitionException`异常。

可以给`@Autowired`增加一个`required = false`的参数：

```
@Component
public class MailService {
    @Autowired(required = false)
    ZoneId zoneId = ZoneId.systemDefault();
    ...
}
```

这个参数告诉Spring容器，如果找到一个类型为`ZoneId`的Bean，就注入，如果找不到，就忽略。

这种方式非常适合有定义就使用定义，没有就使用默认值的情况。

### 创建第三方Bean

如果一个Bean不在我们自己的package管理之内，可以在`@Configuration`类中编写一个Java方法创建并返回它，注意给方法标记一个`@Bean`注解：

* @Compoenent类的依赖需要@Autowired
* @bean的method可以自动按类名/方法名装配，**不需要@Autowired**

https://www.logicbig.com/tutorials/spring-framework/spring-core/javaconfig-methods-inter-dependency.html#:~:text=Spring%20provides%20a%20mechanism%20where%20we%20can%20pass,just%20like%20a%20arbitrary%20method%27s%20dependencies%20are%20resolved



```
@Configuration
@ComponentScan
public class AppConfig {
    // 创建一个Bean:
    @Bean
    ZoneId createZoneId() {
        return ZoneId.of("Z");
    }
}
```

Spring对标记为`@Bean`的方法只调用一次，因此返回的Bean仍然是单例。

### @Bean method



![img](https://www.logicbig.com/tutorials/spring-framework/spring-core/javaconfig-methods-inter-dependency/images/bean-params.png)
， 

1. ## Injecting by type:

   If there's only one bean instance available to be injected to the injection target point then it will be injected successfully by type.

2. ## Injecting by name:

   If there are more than one instance of the same type available for a target injection point then there's a conflict (ambiguity). Spring doesn't know which particular instance to be injected in that case. If the name of parameter is same as bean's definition method (the method annotated with @Bean) name then the dependency is resolved by name.

   The bean's definition method can provide a different name than the method name by using `@Bean(name = ...)`, the injection point method's parameter name should match in that case as well.

3. ## Injecting by bean's name with matching @Qualifier:

   If there's an ambiguity then it can also be resolved if the injection point method parameter add a @Qualifier annotation with matching target bean's name.

4. ## Injecting by matching @Qualifiers

   Ambiguity can also be resolve by using @Qualifier on the both sides. This is important when a bean provider method has already indented to be exposed as a [@Qualifier per business logic sense](https://www.logicbig.com/tutorials/spring-framework/spring-core/inject-bean-by-name.html#qualifier-concept), so that a particular bean's implementation can be changed without updating all injection points.

### 初始化和销毁

有些时候，一个Bean在注入必要的依赖后，需要进行初始化（监听消息等）。在容器关闭时，有时候还需要清理资源（关闭连接池等）。我们通常会定义一个`init()`方法进行初始化，定义一个`shutdown()`方法进行清理，然后，引入JSR-250定义的Annotation：

```
<dependency>
    <groupId>javax.annotation</groupId>
    <artifactId>javax.annotation-api</artifactId>
    <version>1.3.2</version>
</dependency>
```

在Bean的初始化和清理方法上标记`@PostConstruct`和`@PreDestroy`：

```
@Component
public class MailService {
    @Autowired(required = false)
    ZoneId zoneId = ZoneId.systemDefault();

    @PostConstruct
    public void init() {
        System.out.println("Init mail service with zoneId = " + this.zoneId);
    }

    @PreDestroy
    public void shutdown() {
        System.out.println("Shutdown mail service");
    }
}
```

Spring容器会对上述Bean做如下初始化流程：

- 调用构造方法创建`MailService`实例；
- 根据`@Autowired`进行注入；
- 调用标记有`@PostConstruct`的`init()`方法进行初始化。

而销毁时，容器会首先调用标记有`@PreDestroy`的`shutdown()`方法。

Spring只根据Annotation查找*无参数*方法，对方法名不作要求。

### 使用别名

默认情况下，对一种类型的Bean，容器只创建一个实例。但有些时候，我们需要对一种类型的Bean创建多个实例。例如，同时连接多个数据库，就必须创建多个`DataSource`实例。

如果我们在`@Configuration`类中创建了多个同类型的Bean：

```
@Configuration
@ComponentScan
public class AppConfig {
    @Bean
    ZoneId createZoneOfZ() {
        return ZoneId.of("Z");
    }

    @Bean
    ZoneId createZoneOfUTC8() {
        return ZoneId.of("UTC+08:00");
    }
}
```

Spring会报`NoUniqueBeanDefinitionException`异常，意思是出现了重复的Bean定义。

这个时候，需要给每个Bean添加不同的名字：

```
@Configuration
@ComponentScan
public class AppConfig {
    @Bean("z")
    ZoneId createZoneOfZ() {
        return ZoneId.of("Z");
    }

    @Bean
    @Qualifier("utc8")
    ZoneId createZoneOfUTC8() {
        return ZoneId.of("UTC+08:00");
    }
}
```

可以用`@Bean("name")`指定别名，也可以用`@Bean`+`@Qualifier("name")`指定别名。

存在多个同类型的Bean时，注入`ZoneId`又会报错：

```
NoUniqueBeanDefinitionException: No qualifying bean of type 'java.time.ZoneId' available: expected single matching bean but found 2
```

意思是期待找到唯一的`ZoneId`类型Bean，但是找到两。因此，注入时，要指定Bean的名称：

```
@Component
public class MailService {
	@Autowired(required = false)
	@Qualifier("z") // 指定注入名称为"z"的ZoneId
	ZoneId zoneId = ZoneId.systemDefault();
    ...
}
```

还有一种方法是把其中某个Bean指定为`@Primary`：

```
@Configuration
@ComponentScan
public class AppConfig {
    @Bean
    @Primary // 指定为主要Bean
    @Qualifier("z")
    ZoneId createZoneOfZ() {
        return ZoneId.of("Z");
    }

    @Bean
    @Qualifier("utc8")
    ZoneId createZoneOfUTC8() {
        return ZoneId.of("UTC+08:00");
    }
}
```

这样，在注入时，如果没有指出Bean的名字，Spring会注入标记有`@Primary`的Bean。这种方式也很常用。例如，对于主从两个数据源，通常将主数据源定义为`@Primary`：

```
@Configuration
@ComponentScan
public class AppConfig {
    @Bean
    @Primary
    DataSource createMasterDataSource() {
        ...
    }

    @Bean
    @Qualifier("slave")
    DataSource createSlaveDataSource() {
        ...
    }
}
```

其他Bean默认注入的就是主数据源。如果要注入从数据源，那么只需要指定名称即可。

### 使用FactoryBean

我们在设计模式的[工厂方法](https://www.liaoxuefeng.com/wiki/1252599548343744/1281319170474017)中讲到，很多时候，可以通过工厂模式创建对象。Spring也提供了工厂模式，允许定义一个工厂，然后由工厂创建真正的Bean。

用工厂模式创建Bean需要实现`FactoryBean`接口。我们观察下面的代码：

```
@Component
public class ZoneIdFactoryBean implements FactoryBean<ZoneId> {

    String zone = "Z";

    @Override
    public ZoneId getObject() throws Exception {
        return ZoneId.of(zone);
    }

    @Override
    public Class<?> getObjectType() {
        return ZoneId.class;
    }
}
```

当一个Bean实现了`FactoryBean`接口后，Spring会先实例化这个工厂，然后调用`getObject()`创建真正的Bean。`getObjectType()`可以指定创建的Bean的类型，因为指定类型不一定与实际类型一致，可以是接口或抽象类。

因此，如果定义了一个`FactoryBean`，要注意Spring创建的Bean实际上是这个`FactoryBean`的`getObject()`方法返回的Bean。为了和普通Bean区分，我们通常都以`XxxFactoryBean`命名。
