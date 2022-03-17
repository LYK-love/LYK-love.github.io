---
title: Spring Cache Programing
tags:
---

# Spring Cache



## @Cacheable

@Cacheable是用来声明方法是可缓存的。将结果存储到缓存中以便后续使用相同参数调用时不需执行实际的方法。直接从缓存中取值。最简单的格式需要制定缓存名称。 
例如：

```
@Cacheable("books")
public Book findBook(ISBN isbn) {...}
```

在上面的代码片段中，findBook方法与名为books的缓存想关联。每次调用该方法时，将在缓存中检查该请求是否已执行，以免重复执行。虽然在大多数情况下，只有一个缓存被声明，注释允许指定多个名称，以便使用多个缓存。这种情况下，在执行方法之前，每个缓存都会检查之前执行的方法，只要有一个缓存命中，即直接从缓存中返回相关的值。 
即使没有实际执行缓存方法，所有其他不包含该值的缓存也将被更新。 
例如：

```
@Cacheable({"books", "isbns"})
public Book findBook(ISBN isbn) {...}
```

 

**默认key生成：** 
默认key的生成按照以下规则： 
\- 如果没有参数,则使用0作为key 
\- 如果只有一个参数，使用该参数作为key 
\- 如果又多个参数，使用包含所有参数的hashCode作为key

**自定义key的生成：** 
当目标方法参数有多个时，有些参数并不适合缓存逻辑 
比如：

```
@Cacheable("books")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)
```

其中checkWarehouse，includeUsed并不适合当做缓存的key.针对这种情况，Cacheable 允许指定生成key的关键属性，并且支持支持SpringEL表达式。（推荐方法） 
再看一些例子：

[![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```
@Cacheable(cacheNames="books", key="#isbn")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="#isbn.rawNumber")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="T(someType).hash(#isbn)")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="#map['bookid'].toString()")
public Book findBook(Map<String, Object> map)
```

[![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

 

**缓存的同步 sync：** 
在多线程环境下，某些操作可能使用相同参数同步调用。默认情况下，缓存不锁定任何资源，可能导致多次计算，而违反了缓存的目的。对于这些特定的情况，属性 sync 可以指示底层将缓存锁住，使只有一个线程可以进入计算，而其他线程堵塞，直到返回结果更新到缓存中。 
例：

```
@Cacheable(cacheNames="foos", sync="true")
public Foo executeExpensiveOperation(String id) {...}
```

 

**属性condition：** 
有时候，一个方法可能不适合一直缓存（例如：可能依赖于给定的参数）。属性condition支持这种功能，通过SpEL 表达式来指定可求值的boolean值，为true才会缓存（在方法执行之前进行评估）。 
例：

```
@Cacheable(cacheNames="book", condition="#name.length < 32")
public Book findBook(String name)
```

 

此外，还有一个unless 属性可以用来是决定是否添加到缓存。与condition不同的是，unless表达式是在方法调用之后进行评估的。如果返回false，才放入缓存（与condition相反）。 #result指返回值 例：

```
@Cacheable(cacheNames="book", condition="#name.length < 32", unless="#result.name.length > 5"")
public Book findBook(String name)
```

 

## @CachePut

如果缓存需要更新，且不干扰方法的执行,可以使用注解@CachePut。@CachePut标注的方法在执行前**不会去检查缓存中是否存在之前执行过的结果，而是每次都会执行该方法，并将执行结果以键值对的形式存入指定的缓存中**。

```
@CachePut(cacheNames="book", key="#isbn")
public Book updateBook(ISBN isbn, BookDescriptor descriptor)
```

注意：应该避免@CachePut 和 @Cacheable同时使用的情况。

## @CacheEvict

spring cache不仅支持将数据缓存，还支持将缓存数据删除。此过程经常用于从缓存中清除过期或未使用的数据。 
@CacheEvict要求指定一个或多个缓存，使之都受影响。此外，还提供了一个额外的参数allEntries 。表示是否需要清除缓存中的所有元素。默认为false，表示不需要。当指定了allEntries为true时，Spring Cache将忽略指定的key。有的时候我们需要Cache一下清除所有的元素。

```
@CacheEvict(cacheNames="books", allEntries=true)
public void loadBooks(InputStream batch)
```

清除操作默认是在对应方法成功执行之后触发的，即方法如果因为抛出异常而未能成功返回时也不会触发清除操作。使用beforeInvocation可以改变触发清除操作的时间，当我们指定该属性值为true时，Spring会在调用该方法之前清除缓存中的指定元素。

```
@CacheEvict(cacheNames="books", beforeInvocation=true)
public void loadBooks(InputStream batch)
```

 

## @CacheConfig

有时候一个类中可能会有多个缓存操作，而这些缓存操作可能是重复的。这个时候可以使用@CacheConfig

```
@CacheConfig("books")
public class BookRepositoryImpl implements BookRepository {

    @Cacheable
    public Book findBook(ISBN isbn) {...}
}
```

 

@CacheConfig是一个类级别的注解，允许共享缓存的名称、KeyGenerator、CacheManager 和CacheResolver。 
该操作会被覆盖。

## 开启缓存注解

java类配置：

```
@Configuration
@EnableCaching
public class AppConfig {
}
```

 

XML 配置：

[![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:cache="http://www.springframework.org/schema/cache"
    xsi:schemaLocation="
        http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/cache http://www.springframework.org/schema/cache/spring-cache.xsd">

        <cache:annotation-driven />

</beans>
```

[![复制代码](https://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

# EhCache

对比Redis, 跑在同一个进程上， 速度更快



# Redis

跨进程的
