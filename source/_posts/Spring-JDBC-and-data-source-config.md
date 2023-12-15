---
categories:
- Software Engineering
date: 2022-03-21 23:38:49
tags: Spring
title: Spring JDBC and data source config
---

Outline:

* Spring DAO
* DataSource
* JDBC

ref: *Spring In Action*

<!--more-->

# Spring DAO

* 数据访问对象 （data  access object）DAO  == Repository

## 异常体系

* SQLException
  * 发生异常时难以恢复
  * 难确定异常类型
  * 是一个check异常
* Hibernate异常
  * 定义了许多具体异常
  * 对业务对象的侵入
* Spring所提供的平台无关的持久化异常
  *  DataAccessException， 属于runtimeException,属于uncheck异常
  *  具体异常，方便定位问题
  * 隔离具体的数据库平台

## 模板方法模式

模板方法定义过程的主要框架，template

* 管理资源
* 事务控制
* 处理异常

变化的部分，回调（callback），自定义的数据访问代码



Spring提供的模板

* JdbcTemplate
* HibernateTemplate
* JpaTemplate

# DataSource

## 配置数据源



四种方式：

* 使用JNDI数据源

  * （Java 命名与目录接口（Java Naming and Directory Interface） ）

  * 在Web容器中配置JNDI参数，定义一个数据源

  * Spring中配置JNDI数据源

    ```XML
    <jee:jndi-lookup id=“dataSource”
      jndi-name=“/jdbc/**DS”
    resource-ref=“true”/>
    ```

    

* 连接池的数据源

* 通过JDBC驱动程序定义数据源

  * DriverManagerDataSource：注意没有进行池化处理
  * SingleConnectionDataSource:只有一个连接的池

* 使用Spring配置嵌入式数据源

  * `<jdbc:embedded-database>`
  * 可以创建数据表和初始化数据
  * 用于开发和测试



以JDBC为例：

```java
@Configuration
@ComponentScan
@PropertySource("jdbc.properties") //通过@PropertySource("jdbc.properties")读取数据库配置文件；
public class AppConfig {

    @Value("${jdbc.url}") //通过@Value("${jdbc.url}")注入配置文件的相关配置；
    String jdbcUrl;

    @Value("${jdbc.username}")
    String jdbcUsername;

    @Value("${jdbc.password}")
    String jdbcPassword;

    @Bean
    //创建一个DataSource实例，它的实际类型是HikariDataSource，创建时需要用到注入的配置；
    DataSource createDataSource() { 
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl(jdbcUrl);
        config.setUsername(jdbcUsername);
        config.setPassword(jdbcPassword);
        config.addDataSourceProperty("autoCommit", "true");
        config.addDataSourceProperty("connectionTimeout", "5");
        config.addDataSourceProperty("idleTimeout", "60");
        return new HikariDataSource(config);
    }

    @Bean
    //创建一个JdbcTemplate实例，它需要注入DataSource，这是通过方法参数完成注入的。
    JdbcTemplate createJdbcTemplate(@Autowired DataSource dataSource) {
        return new JdbcTemplate(dataSource);
    }
}
```

### 数据库配置文件

```yml
// jdbc.properties：
# 数据库文件名为testdb:
jdbc.url=jdbc:hsqldb:file:testdb

# Hsqldb默认的用户名是sa，口令是空字符串:
jdbc.username=sa
jdbc.password=
```

## 使用profile选择数据源

建立开发、测试、生产环境的不同数据源



配置文件+注解， 原理和SpringBoot一样， SpringBoot采用yml格式，比Spring的Profile简易很多，这里就不介绍Spring的了





# JDBC

## 使用步骤

如上文所示

1. 首先要创建并管理一个`DataSource`实例，表示数据库**连接池**；
2. 然后实例化一个`JdbcTemplate`来操作JDBC



`JdbcTemplate`查询的内部实现：

- 从全局`DataSource`实例获取`Connection`实例；
- 通过`Connection`实例创建`PreparedStatement`实例；
- 执行SQL语句，如果是查询，则通过`ResultSet`读取结果集，如果是修改，则获得`int`结果。

## Spring JDBC框架

* JDBC模板：资源管理和异常处理
* JdbcTemplate
* NamedParameterJdbcTemplate