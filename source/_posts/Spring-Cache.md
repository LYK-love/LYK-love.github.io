---
title: Spring Cache
date: 2022-03-21 21:40:40
tags: Spring
categories: Technology
---

Outline:

* Basic Idea
* 启用Spring缓存支持
* 提供缓存管理器
* 应用缓存

ref: *Spring In Action*

 <!--more-->

# Basic Idea

缓存实际上是一种面向切面的行为。Spring将缓存实现为一个切面。

* 在使用XML声明缓存规则时,这一点非常明显:我们必须要将缓存通知绑定到一个切点上



缓存编程步骤：

1.  启用Spring缓存支持（java方式）： 提供缓存配置类，加上`@EnableCaching`
2.  提供缓存管理器：给配置类提供一个CacheManager`
3.  应用缓存：给需要缓存的方法加上对应的注解

<!--more-->

# 启用Spring缓存支持

Spring启用缓存支持有两种方式:

* 注解驱动的缓存：在一个配置类上添加 ` @EnableCaching`

  ```java
  import org.springframework.cache.CacheManager;
  import org.springframework.cache.annotation.EnableCaching;
  import org.springframework.cache.concurrent.ConcurrentMapCacheManager;
  
  @Configuration
  @EnableCaching
  public class CachingConfig {
        @Bean
      public CacheManager cacheManager() {
          return new ConcurrentMapCacheManager(); //这里还声明了一个ConcurrentMapCacheManager的Bean
      }
      
  }
  
  ```

  * 当你在配置类(@Configuration)上使用@EnableCaching注解时，会触发一个post processor，这会扫描**每一个**spring bean，查看是否已经存在注解对应的缓存。如果找到了，就会自动创建一个代理拦截方法调用，使用缓存的bean执行处理。. [参见](https://javabeat.net/enablecaching-spring/#:~:text=%40EnableCaching%20in%20Spring%20Framework.%20When%20you%20annotate%20your,method%20call%20and%20handle%20the%20caching%20behavior%20accordingly).

* XML声明的缓存： 用Spring cache命名空间中的`<cache:annotation-driven>`元素来启用注解驱动的缓
  存

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




本质上,`@EnableCaching`和`<cache:annotation-driven>`的工作方式是相同的。它们都会创建一个切面(aspect)并
触发Spring缓存注解的切点(pointcut)





# 配置CacheManager

Spring 内置的缓存管理器：

* `SimpleCacheManager`
* `NoOpCacheManager`
* `ConcurrentMapCacheManager`
* `CompositeCacheManager`
* `EhCacheCacheManager`



Spring Data的缓存管理器：

* `RedisCacheManager`(来自于Spring Data Redis项目)
* `GemfireCacheManager`

## EhCache

对比Redis, 跑在同一个进程上， 速度更快



```java
import net.sf.ehcache.CacheManager; //ehcache提供的CacheManager
import org.springframework.cache.ehcache.EhCacheCacheManager;//Spring提供的EhCacheCacheManager
import org.springframework.cache.ehcache.EhCacheManagerFactoryBean;


@Configuration
@EnableCaching
public class CachingConfig {
//      @Bean
//    public CacheManager cacheManager() {
//        return new ConcurrentMapCacheManager();
//    }

  @Bean
  //将ehCache提供的CacheManager注入到Spring的EhCacheManager
  public EhCacheCacheManager cacheManager(CacheManager cm) {
    return new EhCacheCacheManager(cm);
  }

  @Bean //这是个工厂Bean, 用来生成 Ehcache的CacheManager实例 ，后者被注入到cacheManager（Cacaemanager cm）
  public EhCacheManagerFactoryBean ehcache() {
    EhCacheManagerFactoryBean ehCacheFactoryBean =
        new EhCacheManagerFactoryBean();
    ehCacheFactoryBean.setConfigLocation(
        new ClassPathResource("spittr/cache/ehcache.xml"));
    return ehCacheFactoryBean;
  }

```

* `cacheManager()`方法通过传入Ehcache的`CacheManager`实例， 创建了一个`EhCacheCacheManager`实例
  * Spring和ehcache都定义了`CacheManager`类型，我们需要将 ehcache的`CacheManager`注入到Spring的`EhCacheCacheManager`
  * Spring提供了`EhCacheManagerFactoryBean`来生成EhCache的`CacheManager`。方法`ehcache()`会创建并返回一`EhCacheManagerFactoryBean`实例。因为它是一个工**厂bean**(即实现了Spring的`FactoryBean`接口),所以**注册在Spring应用上下文中的并不是EhCacheManagerFactoryBean的实例,而是Ehcache的CacheManager的实例**, 后者被注入到`EhCacheCacheManager`之中
* `EhCache`自身也需要配置（通过XML）， 我们在创建`EhCacheManagerFactoryBean`的过程中, 通过`setConfigLocation()`方法,传入`ClassPath-Resource`,来指定`EhCache` XML配置文件相对于根类路径(classpath)的位置。

### ehCache配置文件

[ehCache官方文档](http://ehcache.org/documentation/configuration)

```xml
<ehcache>
  <cache name="spittleCache" //声明了一个名为spittleCache的缓存
          maxBytesLocalHeap="50m" //最大的堆存储为50MB
          timeToLiveSeconds="100"> // 存活时间为100秒
  </cache>
</ehcache>
```

## Redis

优点：

* 对比EhCache， 可以实现跨进程的缓存

* 缓存的条目是键值对,其中key描述了产生value的操作和参数。因此, Redis作为key-value存储,非常适合存储缓存



Spring Data Redis提供了`RedisCacheManager`, 它与一个Redis Server协作,并通过`RedisTemplate`将缓存条目存储到Redis中







```java
@Configuration
@EnableCaching
public class CacheConfig {

    @Bean
    public CacheManager cacheManager(RedisTemplate redisTemplate) {
        return new RedisCacheManager(redisTemplate); //Redis缓存管理器Bean
    }

    @Bean //Redis连接工厂Bean， 这也是一个工厂Bean
    public RedisConnectionFactory redisCF() {
        return new JedisConnectionFactory(); //这里的工厂Bean的底层实现用的是JedisConnectionFactory
    }

    @Bean //Redis Template Bean
    public RedisTemplate<String, String> redisTemplate(RedisConnectionFactory cf) {
        RedisTemplate<String, String> redis = new RedisTemplate<>();
        redis.setConnectionFactory(cf);
        return redis;
    }
}

```

* `cacheManager()`方法通过传入`RedisTemplate`实例， 创建了一个`RedisCacheManager`实例
* 为了使用`RedisCacheManager`,我们需要`RedisTemplate`及`RedisConnection` Bean, 这同样用工厂Bean实现



## 使用多个缓存管理器

可以用Spring的`CompositeCacheManager`

```java
@Bean
public CacheManager cacheManager(net.sf.ehcache.CacheManager cm, 
		RedisTemplate<String, Object> redisTemplate) {
	
	CompositeCacheManager compositeCacheManager = new CompositeCacheManager();
	List<CacheManager> managers = new ArrayList<CacheManager>();
	managers.add(new EhCacheCacheManager(cm));
	managers.add(new RedisCacheManager(redisTemplate));
	compositeCacheManager.setCacheManagers(managers);//添加缓存管理器，按添加顺序查找，没找到再往下找
	return compositeCacheManager;
}
```

会从`EhCacheCacheManager`检查Ehcache, 然后从`RedisCacheManager`检查Redis

# 应用缓存

这里主要介绍用注解配置缓存

## @Cacheable

`@Cacheable(  cache_name )`

方法的结果会被存到指定的缓存中，下次采用<u>相同的参数</u>进行方法调用时，会使用缓存中的结果
例如：

```java
@Cacheable("spittleCache")
  Spittle findOne(long id);@Cacheable("books")
```

当findOne()被调用时,缓存切面会拦截调用并在缓存中查找之前
以名spittleCache存储的返回值。缓存的key是传递
到findOne()方法中的id参数。如果按照这个key能够找到值的话,
就会返回找到的值,方法不会再被调用。如果没有找到值的话,那么
就会调用这个方法,并将返回值放到缓存之中,为下一次调
用findOne()方法做好准备



**可以加到接口的方法上**， 这会导致所有实现该接口的类的对应方法都应用该注解

 

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



```java
@Cacheable(cacheNames="books", key="#isbn")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="#isbn.rawNumber")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="T(someType).hash(#isbn)")
public Book findBook(ISBN isbn, boolean checkWarehouse, boolean includeUsed)

@Cacheable(cacheNames="books", key="#map['bookid'].toString()")
public Book findBook(Map<String, Object> map)
```



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

@CachePut标注的方法在执行前**不会去检查缓存中是否存在之前执行过的结果，而是每次都会执行该方法，并将执行结果以键值对的形式存入指定的缓存中**。

```
@CachePut(cacheNames="book", key="#isbn")
public Book updateBook(ISBN isbn, BookDescriptor descriptor)
```

注意：应该避免@CachePut 和 @Cacheable同时使用的情况。

## @CacheEvict

移除缓存条目

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

## 用XML配置缓存

就是在XML里面指定缓存规则要应用到哪些方法， 避免在源代码里写`@Cacheable()`,  比较晦涩，不好用
