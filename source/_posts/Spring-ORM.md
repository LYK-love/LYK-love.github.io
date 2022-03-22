---
title: Spring ORM
tags: Spring
categories: Technology
date: 2022-03-21 23:12:27
---


Outline:

* object-relational mapping
* Hibernate、MyBatis
* JPA (Java Persistence API)
* APPENDIX： 一些好用的ORM Tips

ref: *Spring In Action*

<!--more-->



| JDBC       | Hibernate      | JPA                                                      | MyBatis           |
| :--------- | :------------- | :------------------------------------------------------- | :---------------- |
| DataSource | SessionFactory | EntityManagerFactory                                     | SqlSessionFactory |
| Connection | Session        | 带有`@PersistenceContext`注解的<br>`EntityManager`代理类 | SqlSession        |



# Hibernate

## 配置

* 获得`org.hibernate.Session`接口的实现类, 这需要我们创建一个`LocalSessionFactoryBean`，它会自动创建一个`SessionFactory`

  * 在Hibernate中，`Session`是封装了一个JDBC `Connection`的实例，而`SessionFactory`是封装了JDBC `DataSource`的实例，即`SessionFactory`持有连接池，每次需要操作数据库的时候，`SessionFactory`创建一个新的`Session`，相当于从连接池获取到一个新的`Connection`

  * 在hibernate4，我们一般用：`org.springframework.orm.hibernate4.LocalSessionFactoryBean`

  

* Hibernate作为ORM框架，可以替代`JdbcTemplate`，但Hibernate仍然需要JDBC驱动，所以，我们需要引入JDBC驱动、连接池，以及Hibernate本身， 并配置DataSource

* 定义映射关系：XML、注解（JPA、Hibernate）



### 配置数据源等

创建DataSource、引入JDBC配置文件，以及启用声明式事务：

```java
@Configuration
@ComponentScan
@EnableTransactionManagement
@PropertySource("jdbc.properties")
public class AppConfig {
    @Bean
    DataSource createDataSource() {
        ...
    }
}
```



### SessionFactory

使用`org.springframework.orm.hibernate4.LocalSessionFactoryBean`

```java
    @Bean
    LocalSessionFactoryBean createSessionFactory(@Autowired DataSource dataSource) {
        var props = new Properties();//hibernateProperties属性配置了Hibernate如何进行操作的细节
        props.setProperty("hibernate.hbm2ddl.auto", "update"); // 表示自动创建数据库的表结构，生产环境不要使用
        props.setProperty("hibernate.dialect", "org.hibernate.dialect.HSQLDialect");//指示Hibernate使用的数据库是HSQLDB
        props.setProperty("hibernate.show_sql", "true"); //让Hibernate打印执行的SQL，这对于调试非常有用
        var sessionFactoryBean = new LocalSessionFactoryBean();
        sessionFactoryBean.setDataSource(dataSource);
        // 扫描指定的package获取所有entity class:
        sessionFactoryBean.setPackagesToScan("com.itranswarp.learnjava.entity");
        sessionFactoryBean.setHibernateProperties(props);
        return sessionFactoryBean;
    }
```



##  查询



三类查询：

* HQL:hibernate query language，即hibernate提供的面向对象的查询语言
  ```mysql
  select/update/delete…… from …… where …… group by …… having …… order by …… asc/desc
  ```

  

* QBC查询: query by criteria 完全面向对象的查询

* 本地SQL查询



## @Repository 的作用



* `@Component`

* 转换成Spring的统一异常

  ```java
  @Bean
    public BeanPostProcessor persistenceTranslation(){
      return new PersistenceExceptionTranslationPostProcessor();
    }
  ```




# MyBatis

* MyBatis是半自动的ORM，只负责把ResultSet自动映射到Java Bean，或者自动填充Java Bean参数，但仍需自己写出SQL

* 可以用注解或XML配置， 后者比较繁琐，不介绍了



* `application-**.yml`中的配置
  * 配置数据源
  * `mapper-locations`指定
* 定义接口（使用注解`@Mapper`）
* `mapper/***Mapper.xml`

## 配置

### 配置数据源等

### SqlSessionFactory



使用MyBatis的核心就是创建`SqlSessionFactory`，这里我们需要创建的是`SqlSessionFactoryBean`：

```
@Bean
SqlSessionFactoryBean createSqlSessionFactoryBean(@Autowired DataSource dataSource) {
    var sqlSessionFactoryBean = new SqlSessionFactoryBean();
    sqlSessionFactoryBean.setDataSource(dataSource);
    return sqlSessionFactoryBean;
}
```

因为MyBatis可以直接使用Spring管理的声明式事务，因此，创建事务管理器和使用JDBC是一样的：

```
@Bean
PlatformTransactionManager createTxManager(@Autowired DataSource dataSource) {
    return new DataSourceTransactionManager(dataSource);
}
```

### Mapper

和Hibernate不同的是，MyBatis使用Mapper来实现映射，而且Mapper必须是接口。我们以User类为例，在User类和users表之间映射的UserMapper编写如下：

```
public interface UserMapper {
	@Select("SELECT * FROM users WHERE id = #{id}")
	User getById(@Param("id") long id);
}
```





### @MapperScan

Mybatis将Mapper接口动态代理，生成实现类。 要识别到Mapper接口，有两种方法：

* 使用`@Mapper`标识Mapper接口， 比较繁琐：

  ```java
  @Mapper
  public interface UserDAO {
     //代码
  }
  
  ```

  

* 在某个配置类中启用`@MapperScan()`，并指定Mapper接口所在的包， 该包下的所有接口都会被动态代理：

  ```
  @MapperScan("com.itranswarp.learnjava.mapper")
  ...其他注解...
  public class AppConfig {
      ...
  }
  ```

  * 可以扫描多个包： `@MapperScan({"com.kfit.demo","com.kfit.user"})  `
  * 这个注解实际上会生成`MapperFactoryBean`，后者会自动创建包下所有Mapper的实现类

：

## Mapper语法

在定义了接口方法后，还需要明确写出查询的SQL, SQL的每个参数都与方法参数按名称对应

* 例如，方法参数id的名字通过注解`@Param()`标记为`id`，则SQL语句里将来替换的占位符就是`#{id}`

* 如果有多个参数，那么每个参数命名后直接在SQL中写出对应的占位符即可：

  ```
  @Select("SELECT * FROM users LIMIT #{offset}, #{maxResults}")
  List<User> getAll(@Param("offset") int offset, @Param("maxResults") int maxResults);
  ```

### SELECT

MyBatis将ResultSet的每一行转换为Domain实例， 转换规则当然是按列名和属性名对应。如果列名和属性名不同, 需要用别名：

* 对于SELECT语句：

  ```SQL
  -- 列名是created_time，属性名是createdAt:
  SELECT id, name, email, created_time AS createdAt FROM users
  ```

### INSERT

MyBatis插入时， 需要将对象的属性转换成列：

```java
@Insert("INSERT INTO users (email, password, name, createdAt) VALUES (#{user.email}, #{user.password}, #{user.name}, #{user.createdAt})")
void insert(@Param("user") User user);
```

* 在SQL中以`#{obj.property}`的方式写占位符





如果表的id是自增主键，那么，我们在SQL中不传入id，但希望获取插入后的主键，需要再加一个`@Options`注解：

```java
@Options(useGeneratedKeys = true, keyProperty = "id", keyColumn = "id")
@Insert("INSERT INTO users (email, password, name, createdAt) VALUES (#{user.email}, #{user.password}, #{user.name}, #{user.createdAt})")
void insert(@Param("user") User user);
```

* `keyProperty`：JavaBean 的属性
* `keyColumn`： 数据库的主键列名

### UPDATE 

执行UPDATE和DELETE语句相对比较简单，我们定义方法如下：

```java
@Update("UPDATE users SET name = #{user.name}, createdAt = #{user.createdAt} WHERE id = #{user.id}")
void update(@Param("user") User user);
```

### DELETE

```java
@Delete("DELETE FROM users WHERE id = #{id}")
void deleteById(@Param("id") long id);
```



## 使用Mapper

在Service层直接注入Mapper, 使用Mapper提供的方法

```java
@Component
@Transactional
public class UserService {
    // 注入UserMapper:
    @Autowired
    UserMapper userMapper;

    public User getUserById(long id) {
        // 调用Mapper方法:
        User user = userMapper.getById(id);
        if (user == null) {
            throw new RuntimeException("User not found by id.");
        }
        return user;
    }
}
```



# JPA

* JPA的宗旨是为POJO提供持久化标准规范
* JPQL（Java Persistence Query Language)
* JPQL就是一种查询语言，具有与 SQL 相类似的特征
* JPA语法大全



## 配置

步骤：

1. 配置数据源等
2. 创建`EntityManagerFactoryBean`， 它会生成一个`SessionFactory`
3. 将`SessionFactory`注入到`JpaTransactionManager`， 以实现声明式事务



* 使用Hibernate时，我们需要创建一个`LocalSessionFactoryBean`，并让它再自动创建一个`SessionFactory`。使用JPA也是类似的，我们需要创建一个`EntityManagerFactoryBean`，并让它再自动创建一个`EntityManagerFactory`，
  * `EntityManagerFactory`:  是个工厂Bean, 会创建创建`EntityManager`
    * `org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean`
    * ``org.springframework.orm.jpa.vendor.HibernateJpaVendorAdapter`
  * `javax.persistence.EntityManager`



* `EntityManager`不是线程安全的， Spring遇到标注了`@PersistenceContext`的`EntityManager`会自动注入代理，该代理会在必要的时候自动打开`EntityManager`。换句话说，多线程引用的`EntityManager`虽然是同一个代理类，但该代理类内部针对不同线程会创建不同的`EntityManager`实例。因此，标注了`@PersistenceContext`的`EntityManager`可以被多线程安全地共享。
  * `@PersistenceUnit`
  * `@PersistenceContext`

### 配置数据源等

在`AppConfig`中启用声明式事务管理，创建`DataSource`：

```java
@Configuration
@ComponentScan
@EnableTransactionManagement
@PropertySource("jdbc.properties")
public class AppConfig {
    @Bean
    DataSource createDataSource() { ... }
}
```

### EntityManagerFactory



```java
@Bean
LocalContainerEntityManagerFactoryBean createEntityManagerFactory(@Autowired DataSource dataSource) {
    var entityManagerFactoryBean = new LocalContainerEntityManagerFactoryBean();
    // 设置DataSource:
    entityManagerFactoryBean.setDataSource(dataSource);
    // 扫描指定的package获取所有entity class:
    entityManagerFactoryBean.setPackagesToScan("com.itranswarp.learnjava.entity");
    // 指定JPA的提供商是Hibernate:
    JpaVendorAdapter vendorAdapter = new HibernateJpaVendorAdapter();
    entityManagerFactoryBean.setJpaVendorAdapter(vendorAdapter);
    // 设定特定提供商自己的配置:
    var props = new Properties();
    props.setProperty("hibernate.hbm2ddl.auto", "update");
    props.setProperty("hibernate.dialect", "org.hibernate.dialect.HSQLDialect");
    props.setProperty("hibernate.show_sql", "true");
    entityManagerFactoryBean.setJpaProperties(props);
    return entityManagerFactoryBean;
}
```

### JpaTransactionManager

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



## 编写自定义的查询方法

* 定义查询方法，无需实现
  * 领域特定语言（domain-specific language，DSL)，spring data的命名约定
  * 查询动词 + 主题 + 断言
  * 查询动词：get、read、find、count
* 声明自定义查询
  不符合方法命名约定时，或者命名太长时： `@Query(“select ...”)`
* 使用EntityManager直接低层实现
  * 接口名+Impl的实现类





# 实体类

需要添加注解来告诉ORM如何把实体类映射到表记录

* **作为映射使用的JavaBean，所有属性都使用包装类型而不是基本类型**（ Mybatis是个例外，这是因为它不是全ORM框架 ）
* 如果一个JavaBean被用于映射，我们就标记一个`@Entity`。默认情况下，实体类User映射的表名是`user`，如果实际的表名不同，例如实际表名是`users`，可以追加一个`@Table(name="users")`表示
* 对于主键，还需要用`@Id`标识，自增主键再追加一个`@GeneratedValue`，以便Hibernate能读取到自增主键的值
* 每个属性到数据库列的映射用`@Column()`标识，`nullable`指示列是否允许为`NULL`，`updatable`指示该列是否允许被用在`UPDATE`语句，`length`指示`String`类型的列的长度（如果没有指定，默认是`255`）

示例：

```java
@Entity
public class User { //映射到表名user
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(nullable = false, updatable = false)
    public Long getId() { ... }

    @Column(nullable = false, unique = true, length = 100)
    public String getEmail() { ... }

    @Column(nullable = false, length = 100)
    public String getPassword() { ... }

    @Column(nullable = false, length = 100)
    public String getName() { ... }

    @Column(nullable = false, updatable = false)
    public Long getCreatedAt() { ... }
}
```

# Appendex

## MySQL与JAVA数据类型对应关系

| These MySQL Data Types                                       | Can always be converted to these Java types                  |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| `CHAR, VARCHAR, BLOB, TEXT, ENUM, and SET`                   | `java.lang.String, java.io.InputStream, java.io.Reader, java.sql.Blob, java.sql.Clob` |
| `FLOAT, REAL, DOUBLE PRECISION, NUMERIC, DECIMAL, TINYINT, SMALLINT, MEDIUMINT, INTEGER, BIGINT` | `java.lang.String, java.lang.Short, java.lang.Integer, java.lang.Long, java.lang.Double, java.math.BigDecimal` |
| `DATE, TIME, DATETIME, TIMESTAMP`                            | `java.lang.String, java.sql.Date, java.sql.Timestamp`        |

## MYSQL存URL最佳类型

MySQL 5.0.3及更高版本中VARCHAR的有效最大长度受最大行大小（65,535字节，在所有列之间共享）和使用的字符集的限制。

所以，存储url最佳类型为：

* `< MySQL 5.0.3 use TEXT`
* `>= MySQL 5.0.3 use VARCHAR(2083)`
