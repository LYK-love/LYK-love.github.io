---
title: Spring ORM
tags: 
---

# Hibernate

配置：

* `org.hibernate.Session`接口
* 获得`org.hibernate.SessionFactory`对象
  * `org.springframework.orm.hibernate4.LocalSessionFactoryBean`
* 定义映射关系：XML、注解（JPA、Hibernate）

* `Srssion`接口
* 获得`SessionFactory`对象



三类查询：

* HQL:hibernate query language，即hibernate提供的面向对象的查询语言
  ```mysql
  select/update/delete…… from …… where …… group by …… having …… order by …… asc/desc
  ```

  

* QBC查询: query by criteria 完全面向对象的查询

* 本地SQL查询



`@Repository`的作用

* `@Component`

* 转换成Spring的统一异常

  ```java
  @Bean
    public BeanPostProcessor persistenceTranslation(){
      return new PersistenceExceptionTranslationPostProcessor();
    }
  ```

  

# MyBatis

* `application-**.yml`中的配置
  * 配置数据源
  * `mapper-locations`指定
* 定义接口（使用注解`@Mapper`）
* `mapper/***Mapper.xml`

# JPA

JPA的宗旨是为POJO提供持久化标准规范
JPQL（Java Persistence Query Language)
JPQL就是一种查询语言，具有与 SQL 相类似的特征
JPA语法大全

## EntityManager

配置：

* javax.persistence.EntityManager
* 实体管理器工厂（entity manager factory）
  * `org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean`
  * `org.springframework.orm.jpa.vendor.HibernateJpaVendorAdapter`

* `EntityManager`不是线程安全的， 每次会创建一个代理类
  * `@PersistenceUnit`
  * `@PersistenceContext`: 并不会注入`EntityManager`， 因为它不是线程安全的。 注入的是一个代理， 通过代理关联到当前事物上下文的真正的`EntityManager`

## Spring Data JPA

```xml
<dependency>
            <groupId>org.springframework.data</groupId>
            <artifactId>spring-data-jpa</artifactId>
            <version>1.3.2.RELEASE</version>
 </dependency>
```



* 加注解`@EnableJpaRepositories`
  * 会扫描`org.springframework.data.repository.Repository`接口
* 继承接口`org.springframework.data.jpa.repository.JpaRepository`



编写自定义的查询方法：

* 定义查询方法，无需实现
  * 领域特定语言（domain-specific language，DSL)，spring data的命名约定
  * 查询动词 + 主题 + 断言
  * 查询动词：get、read、find、count
* 声明自定义查询
  不符合方法命名约定时，或者命名太长时： `@Query(“select ...”)`
* 使用EntityManager直接低层实现
  * 接口名+Impl的实现类
