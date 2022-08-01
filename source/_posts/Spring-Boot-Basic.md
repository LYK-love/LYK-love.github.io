---
title: Spring Boot Intro
tags: Spring
categories: Technology
date: 2022-04-13 20:38:17
---


Outline:

* Spring Boot工程
* 常用配置
* Spring Boot Features

Spring Boot基于Spring提供了开箱即用的一组套件，可以简化spring开发，还提供了基于java的、面向REST的微服务框架

<!--more-->



# Spring Boot工程

Spring Boot工程目录结构：

```ascii
springboot-hello
├── pom.xml
├── src
│   └── main
│       ├── java
│       └── resources
│           ├── application.yml
│           ├── logback-spring.xml
│           ├── static
│           └── templates
└── target
```



Spring Boot要求`main()`方法所在的启动类必须放到根package下，命名不做要求，这里我们以`Application.java`命名，它的内容如下：

```java
@SpringBootApplication
public class Application {
    public static void main(String[] args) throws Exception {
        SpringApplication.run(Application.class, args);
    }
}
```

启动Spring Boot应用程序只需要加上注解`@SpringBootApplication`，该注解实际上又包含了：

- @SpringBootConfiguration
  - @Configuration
- @EnableAutoConfiguration
  - @AutoConfigurationPackage
- @ComponentScan

这样一个注解就相当于启动了自动配置和自动扫描

## application.yml

Spring Boot默认的配置文件是采用[YAML](https://yaml.org/)格式的`application.yml` ,当然你也可以继续沿用spring的`application.properties`

```yaml
spring:
  application:
    name: ${APP_NAME:unnamed}
  datasource:
    url: jdbc:hsqldb:file:testdb
    username: sa
    password:
    driver-class-name: org.hsqldb.jdbc.JDBCDriver
    hikari:
      auto-commit: false
      connection-timeout: 3000
      validation-timeout: 3000
      max-lifetime: 60000
      maximum-pool-size: 20
      minimum-idle: 1
```

### 配置的优先级

和其他程序一样， 命令行手动指定的优先级最高。  对于配置文件而言，优先级取决于其所在位置，按优先级从高到低：

1. 外置,在相对于应用程序运行目录的/config子目录里。
2. 外置,在应用程序运行的目录里。
3. 内置,在config包内。
4. 内置,在Classpath根目录



同一目录下，`application.yml` >  `application.properties`





### 环境变量

在配置文件中，我们经常使用如下的格式对某个key进行配置：

```yaml
app:
  db:
    host: ${DB_HOST:localhost}
    user: ${DB_USER:root}
    password: ${DB_PASSWORD:password}
```

这种`${DB_HOST:localhost}`意思是，首先从环境变量查找`DB_HOST`，如果环境变量定义了，那么使用环境变量的值，否则，使用默认值`localhost`。

这使得我们在开发和部署时更加方便，因为开发时无需设定任何环境变量，直接使用默认值即本地数据库，而实际线上运行的时候，只需要传入环境变量即可：

```shell
DB_HOST=10.0.1.123 DB_USER=prod DB_PASSWORD=xxxx java -jar xxx.jar
```



### yaml文件格式

- 使用缩进表示层级关系，不允许使用Tab键，只允许使用空格
- `#` 表示注释，从这个字符一直到行尾，都会被解析器忽略。
- 对象，键值对，使用冒号结构表示

- - animal: pets
  - hash: { name: Steve, foo: bar }

- 数组,一组连词线开头的行，构成一个数组

- - \- Cat
  - \- Dog
  - \- Goldfish
  - 行内表示法：animal: [Cat, Dog]

# 常用配置

* 让服务器监听不同的端口：

  ```shell
  server:
  port: 8000
  ```

* 使用https：

  1. 使用JDK的keytool工具来创建一个密钥存储(keystore)

     ```yaml
     keytool -keystore mykeys.jks -genkey -alias tomcat -keyalg RSA
     ```

  2. 配置文件如下：

     ```shell
     server:
     	port: 8443
     	ssl:
     		key-store:file:///path/to/mykeys.jks
     		key-store-password: letmein
     		key-password: letmein
     ```

     

    server.ssl.key-store 属性指向密钥存储文件的存放路径。这里用了一个file://开头的URL,
    从文件系统里加载该文件。你也可以把它打包在应用程序的JAR文件里,用classpath: URL来
    引用它。server.ssl.key-store-password和server.ssl.key-password设置为创建该文
    件时给定的密码。

## 配置单数据源

数据源配置可以用Bean， 但更方便的做法是通过配置文件,以Mysql为例：

```yaml
spring:
	datasource:
		url: jdbc:mysql://localhost/readinglist
		username: dbuser
		password: dbpass
```



通常你都无需指定JDBC驱动,Spring Boot会根据数据库URL识别出需要的驱动,但如果识别出问题了,你还可以设置spring.datasource.driver-class-name属性:

```yaml
spring:
	datasource:
		url: jdbc:mysql://localhost/readinglist
		username: dbuser
		password: dbpass
		driver-class-name: com.mysql.jdbc.Driver
```

在自动配置 DataSource Bean的时候,Spring Boot会使用这里的连接数据。 DataSource
Bean是一个连接池,如果Classpath里有Tomcat的连接池DataSource,那么就会使用这个连接池;
否则,Spring Boot会在Classpath里查找以下连接池:

* HikariCP
* Commons DBCP
* Commons DBCP 2

这里列出的只是自动配置支持的连接池,你还可以自己配置DataSource Bean,使用你喜欢的各种连接池




## 配置多数据源

配置多数据源和单数据源没什么区别，但是如果使用了Mybatis等ORM框架，记得要额外配置一下ORM的扫描规则。 大概步骤为：



1. （如果需要的话）引入新数据库的驱动的依赖
2. 在配置文件里面配置新的数据库连接
3. 新增配置类，在里面配置ORM框架的扫描规则
4. （如果需要的话）使用新的连接池

### 引入数据库驱动依赖

如果你新增的数据库数据源和目前的数据库不同，记得引入新数据库的驱动依赖，比如 MySQL 和 PGSQL。

```javascript
<dependency>
 <groupId>mysql</groupId>
 <artifactId>mysql-connector-java</artifactId>
 <scope>runtime</scope>
</dependency>

<dependency>
    <groupId>org.postgresql</groupId>
    <artifactId>postgresql</artifactId>
    <version>42.2.7</version>
</dependency>
```



### 配置数据库连接

因为数据源要有一个默认使用的数据源，最好在名称上有所区分（这里使用 **primary** 作为主数据源标识）

```properties
########################## 主数据源 ##################################
spring.datasource.primary.jdbc-url=jdbc:mysql://127.0.0.1:3306/demo1?characterEncoding=utf-8&serverTimezone=GMT%2B8
spring.datasource.primary.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.primary.username=root
spring.datasource.primary.password=

########################## 第二个数据源 ###############################
spring.datasource.datasource2.jdbc-url=jdbc:mysql://127.0.0.1:3306/demo2?characterEncoding=utf-8&serverTimezone=GMT%2B8
spring.datasource.datasource2.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.datasource2.username=root
spring.datasource.datasource2.password=

# mybatis
mybatis.mapper-locations=classpath:mapper/*.xml
mybatis.type-aliases-package=com.wdbyte.domain
```

注意，配置中的数据源连接 url 末尾使用的是 `jdbc-url`.

因为使用了 Mybatis 框架，所以 Mybatis 框架的配置信息也是少不了的，指定扫描目录 `mapper` 下的`mapper xml` 配置文件。

### 配置Mybatis的扫描路径

到目前为止， Mybatis 多数据源和单数据源写法唯一的区别就是 Mapper 接口使用不同的目录分开了，那么这个不同点一定会在数据源配置中体现

#### 主数据源

开始配置两个数据源信息，先配置主数据源，配置扫描的 `MapperScan` 目录为 `com.wdbyte.mapper.primary`

```javascript
/**
 * 主数据源配置
 *
 * @author niujinpeng
 * @website: https://www.wdbyte.com
 * @date 2020/12/19
 */
@Configuration
@MapperScan(basePackages = {"com.wdbyte.mapper.primary"}, sqlSessionFactoryRef = "sqlSessionFactory")
public class PrimaryDataSourceConfig {

    @Bean(name = "dataSource")
    @ConfigurationProperties(prefix = "spring.datasource.primary")
    @Primary
    public DataSource dataSource() {
        return DataSourceBuilder.create().build();
    }

    @Bean(name = "sqlSessionFactory")
    @Primary
    public SqlSessionFactory sqlSessionFactory(@Qualifier("dataSource") DataSource dataSource) throws Exception {
        SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
        bean.setDataSource(dataSource);
        bean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources("classpath:mapper/*.xml"));
        return bean.getObject();
    }

    @Bean(name = "transactionManager")
    @Primary
    public DataSourceTransactionManager transactionManager(@Qualifier("dataSource") DataSource dataSource) {
        return new DataSourceTransactionManager(dataSource);
    }

    @Bean(name = "sqlSessionTemplate")
    @Primary
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("sqlSessionFactory") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```

和单数据源不同的是这里把

- `dataSource`
- `sqlSessionFactory`
- `transactionManager`
- `sqlSessionTemplate`

都单独进行了配置，简单的 bean 创建，下面是用到的一些注解说明。

- `@ConfigurationProperties(prefix = "spring.datasource.primary")`：使用spring.datasource.primary 开头的配置。
- `@Primary` ：声明这是一个主数据源（默认数据源），多数据源配置时**必不可少**。
- `@Qualifier`：显式选择传入的 Bean。

#### 第二个数据源

第二个数据源和主数据源唯一不同的只是 `MapperScan` 扫描路径和创建的 Bean 名称，同时没有 `@Primary` 主数据源的注解。

```javascript
/**
 * 第二个数据源配置
 * 
 * @author niujinpeng
 * @website: https://www.wdbyte.com
 * @date 2020/12/19
 */
@Configuration
@MapperScan(basePackages = {"com.wdbyte.mapper.datasource2"}, sqlSessionFactoryRef = "sqlSessionFactory2")
public class SecondDataSourceConfig {

    @Bean(name = "dataSource2")
    @ConfigurationProperties(prefix = "spring.datasource.datasource2")
    public DataSource dataSource() {
        return DataSourceBuilder.create().build();
    }

    @Bean(name = "sqlSessionFactory2")
    public SqlSessionFactory sqlSessionFactory(@Qualifier("dataSource2") DataSource dataSource) throws Exception {
        SqlSessionFactoryBean bean = new SqlSessionFactoryBean();
        bean.setDataSource(dataSource);
        bean.setMapperLocations(new PathMatchingResourcePatternResolver().getResources("classpath:mapper/*.xml"));
        return bean.getObject();
    }

    @Bean(name = "transactionManager2")
    public DataSourceTransactionManager transactionManager(@Qualifier("dataSource2") DataSource dataSource) {
        return new DataSourceTransactionManager(dataSource);
    }

    @Bean(name = "sqlSessionTemplate2")
    public SqlSessionTemplate sqlSessionTemplate(@Qualifier("sqlSessionFactory2") SqlSessionFactory sqlSessionFactory) {
        return new SqlSessionTemplate(sqlSessionFactory);
    }
}
```

注意：因为已经在两个数据源中分别配置了扫描的 Mapper 路径，如果你之前在 SpringBoot 启动类中也使用了 Mapper 扫描注解，**需要删掉**。



### 连接池

其实在多数据源改造中，我们一般情况下都不会使用默认的 JDBC 连接方式，往往都需要引入连接池进行连接优化，不然你可能会经常遇到数据源连接被断开等报错日志。其实数据源切换连接池数据源也是十分简单的，直接引入连接池依赖，然后把创建 dataSource 的部分换成连接池数据源创建即可

下面以阿里的 Druid 为例，先引入连接池数据源依赖。

```javascript
<dependency>
   <groupId>com.alibaba</groupId>
   <artifactId>druid</artifactId>
</dependency>
```

添加 Druid 的一些配置。

```javascript
spring.datasource.datasource2.initialSize=3 # 根据自己情况设置
spring.datasource.datasource2.minIdle=3
spring.datasource.datasource2.maxActive=20
```

改写 dataSource Bean 的创建代码部分。

```javascript
@Value("${spring.datasource.datasource2.jdbc-url}")
private String url;
@Value("${spring.datasource.datasource2.driver-class-name}")
private String driverClassName;
@Value("${spring.datasource.datasource2.username}")
private String username;
@Value("${spring.datasource.datasource2.password}")
private String password;
@Value("${spring.datasource.datasource2.initialSize}")
private int initialSize;
@Value("${spring.datasource.datasource2.minIdle}")
private int minIdle;
@Value("${spring.datasource.datasource2.maxActive}")
private int maxActive;

@Bean(name = "dataSource2")
public DataSource dataSource() {
    DruidDataSource dataSource = new DruidDataSource();
    dataSource.setUrl(url);
    dataSource.setDriverClassName(driverClassName);
    dataSource.setUsername(username);
    dataSource.setPassword(password);
    dataSource.setInitialSize(initialSize);
    dataSource.setMinIdle(minIdle);
    dataSource.setMaxActive(maxActive);
    return dataSource;
}
```

这里只是简单的提一下使用连接池的重要性，Druid 的详细用法还请参考官方文档

## 配置日志

默认情况下,Spring Boot会用Logback(http://logback.qos.ch)来记录日志,并用INFO级别输
出到控制台。在运行应用程序和其他例子时,你应该已经看到很多INFO级别的日志了。



一般来说,你不需要切换日志实现;Logback能很好地满足你的需要。但是,如果决定使
用Log4j或者Log4j2,那么你只需要修改依赖,引入对应该日志实现的起步依赖,同时排除掉
Logback。
以Maven为例,应排除掉根起步依赖传递引入的默认日志起步依赖,这样就能排除
Logback了:

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter</artifactId>
	<exclusions>
		<exclusion>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-logging</artifactId>
		</exclusion>
	</exclusions>
</dependency>
```


在Gradle里,在 configurations下排除该起步依赖是最简单的办法:

```groovy
configurations {
	all*.exclude group:'org.springframework.boot',
	module:'spring-boot-starter-logging'
}
```

排除默认日志的起步依赖后,就可以引入你想用的日志实现的起步依赖了。在Maven里可
以这样添加Log4j:

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-log4j</artifactId>
</dependency>
```


在Gradle里可以这样添加Log4j:

```groovy
compile("org.springframework.boot:spring-boot-starter-log4j")
```



要完全掌握日志配置,可以在Classpath的根目录(src/main/resources)里创建logback.xml文
件。下面是一个logback.xml的简单例子:

```xml
<configuration>
<appender name="STDOUT" class="ch.qos.logback.core.ConsoleAppender">
<encoder>
<pattern>
%d{HH:mm:ss.SSS} [%thread] %-5level %logger{36} - %msg%n
</pattern>
</encoder>
</appender>
<logger name="root" level="INFO"/>
<root level="INFO">
<appender-ref ref="STDOUT" />
</root>
</configuration>
```


除了日志格式之外,这个Logback配置和不加logback.xml文件的默认配置差不多。但是,通
过编辑logback.xml,你可以完全掌控应用程序的日志文件。哪些配置应该放进logback.xml这个话
题不在本书的讨论范围内,请参考Logback的文档以了解更多信息。
即使如此,你对日志配置最常做的改动就是修改日志级别和指定日志输出的文件。使用了
Spring Boot的配置属性后,你可以在不创建logback.xml文件的情况下修改那些配置。
要设置日志级别,你可以创建以logging.level开头的属性,后面是要日志名称。如果根
日志级别要设置为WARN,但Spring Security的日志要用DEBUG级别,可以在application.yml里加入
以下内容:

```yaml
logging:
	level:
		root: WARN
		org:
			springframework:
			security: DEBUG
```


另外,你也可以把Spring Security的包名写成一行:

```yaml
logging:
	level:
		root: WARN
		org.springframework.security: DEBUG
```



现在,假设你想把日志写到位于/var/logs/目录里的BookWorm.log文件里。使用 logging.
path和loggin.file属性就行了:

```yaml
logging:
	path: /var/logs/
	file: BookWorm.log
	level:
		root: WARN
		org:
			springframework:
				security: DEBUG
```

假设应用程序有/var/logs/的写权限,日志就能被写入/var/logs/BookWorm.log。默认情况下,
日志文件的大小达到10MB时会切分一次。
与之类似,这些属性也能在application.properties里设置:

```
logging.path=/var/logs/
logging.file=BookWorm.log
logging.level.root=WARN
logging.level.root.org.springframework.security=DEBUG
```

如果你还是想要完全掌控日志配置,但是又不想用logback.xml作为Logback配置的名字,可
以通过logging.config属性指定自定义的名字:

```yaml
logging:
	config:
		classpath: logging-config.xml
```

虽然一般并不需要改变配置文件的名字,但是如果你想针对不同运行时Profile使用不同的日
志配置(见3.2.3节),这个功能会很有用。

## 配置HTTPS

1. 用JDK的keytool工具来创建一个密钥存储(keystore):

   ```shell
   keytool -keystore mykeys.jks -genkey -alias tomcat -keyalg RSA
   ```

2. 将生成的密钥（的路径）放在配置文件中:

   ```yaml
   server:
   	port: 8443
   	ssl:
   		key-store: file:///path/to/mykeys.jks
   ```

   

# Spring Boot Features

Spring Boot提供了许多Spring没有的新特性

## AutoConfiguration

Spring Boot提供了自动装配`XxxAutoConfiguration`，使得许多组件被自动化配置并创建,  这通过自动扫描+ 条件装配`@Conditional`实现, 步骤为:

1. 引入各种依赖（由于是spring boot， 因此一般是起步依赖 ）， 依赖中会有`XxxAutoConfiguration`类
2. Spring Boot启动时会自动扫描所有的`XxxAutoConfiguration`
3. 对于每个`XXAutoConfiguratio`, 它一般带有注解:
   * `@ConditionalOnClass（XX.class）`： 在classpath中能找XX；
   * `@EnableConfigurationProperties(XX.class)`： 在当前Bean的定义中能找到唯一的`DataSource`；
   * 各种`@Conditional`...
   * `@Import(XXConfiguration）`:注入某个配置类
4. 如果符合条件，该`XXConfiguration`就会被装配。而各种Bean的实际创建由其导入的`XXeConfiguration`完成
5. XXConfiguration一般会带有注解`@ConditionalOnMissingBean(XX.class)`，即不存在`XX`的Bean时，就会自动注入，这就完成了Bean的自动装配



### 自动配置的细节

例如，引入`spring-boot-starter-jdbc`后，启动时：

- `DataSourceAutoConfiguration`：自动创建一个`DataSource`，其中配置项从`application.yml`的`spring.datasource`读取
- `DataSourceTransactionManagerAutoConfiguration`：自动创建了一个基于JDBC的事务管理器
- `JdbcTemplateAutoConfiguration`：自动创建了一个`JdbcTemplate`

因此，我们自动得到了一个`DataSource`、一个`DataSourceTransactionManager`和一个`JdbcTemplate`



类似地，当我们引入`spring-boot-starter-web`时，自动创建了：

- `ServletWebServerFactoryAutoConfiguration`：自动创建一个嵌入式Web服务器，默认是Tomcat
- `DispatcherServletAutoConfiguration`：自动创建一个`DispatcherServlet`
- `HttpEncodingAutoConfiguration`：自动创建一个`CharacterEncodingFilter`
- `WebMvcAutoConfiguration`：自动创建若干与MVC相关的Bean
- ...

引入第三方`pebble-spring-boot-starter`时，自动创建了：

- `PebbleAutoConfiguration`：自动创建了一个`PebbleViewResolver`

### 条件装配的细节

我们观察`JdbcTemplateAutoConfiguration`，它的代码如下：

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnClass({ DataSource.class, JdbcTemplate.class })
@ConditionalOnSingleCandidate(DataSource.class)
@AutoConfigureAfter(DataSourceAutoConfiguration.class)
@EnableConfigurationProperties(JdbcProperties.class)
@Import({ JdbcTemplateConfiguration.class, NamedParameterJdbcTemplateConfiguration.class })
public class JdbcTemplateAutoConfiguration {
}
```

当满足条件：

- `@ConditionalOnClass`：在classpath中能找到`DataSource`和`JdbcTemplate`；
- `@ConditionalOnSingleCandidate(DataSource.class)`：在当前Bean的定义中能找到唯一的`DataSource`；

该`JdbcTemplateAutoConfiguration`就会起作用。实际创建由导入的`JdbcTemplateConfiguration`完成：

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnMissingBean(JdbcOperations.class)
class JdbcTemplateConfiguration {
    @Bean
    @Primary
    JdbcTemplate jdbcTemplate(DataSource dataSource, JdbcProperties properties) {
        JdbcTemplate jdbcTemplate = new JdbcTemplate(dataSource);
        JdbcProperties.Template template = properties.getTemplate();
        jdbcTemplate.setFetchSize(template.getFetchSize());
        jdbcTemplate.setMaxRows(template.getMaxRows());
        if (template.getQueryTimeout() != null) {
            jdbcTemplate.setQueryTimeout((int) template.getQueryTimeout().getSeconds());
        }
        return jdbcTemplate;
    }
}
```

创建`JdbcTemplate`之前，要满足`@ConditionalOnMissingBean(JdbcOperations.class)`，即不存在`JdbcOperations`的Bean。



### 覆盖自动装配

由于Spring Boot自动装配功能通过自动扫描+条件装配实现， 想要覆盖Spring Boot的自动配置,只需编写一个显式的配置。根据条件`@ConditionalOnMissingBean([XX.class])`， Spring Boot就不会再创建一个重复的Bean



## Starter Dependencies

```xml
<dependencies>
   <dependency>
       <groupId>org.springframework.boot</groupId>
       <artifactId>spring-boot-starter-web</artifactId>
   </dependency>
</dependencies>
```



starter是一组依赖集合，用户不需要再单独依赖，只需要依赖Starter，就可以**一站式**解决所需的依赖

* 简单来说，starter是帮用户简化配置的， 在“约定大于配置”的理念下，starter把繁琐的配置交给自己，而把简单的交给用户。 用户也可以覆盖默认配置

  * “约定大于配置”：starter使用ConfigurationProperties来保存配置，且配置都有默认值，用户可以覆盖
  * ConfigurationProperties还使得所有的配置属性被聚集到一个文件中（一般在resources目录下的`application.properties/yml`），这样我们就告别了Spring项目中XML地狱
* 注意，不同的starter是为了解决不同的依赖，所以它们内部的实现可能会有很大的差异，例如jpa的starter和Redis的starter可能实现就不一样![在这里插入图片描述](https://img-blog.csdnimg.cn/20190507163145255.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW9ob25nX2Jv,size_16,color_FFFFFF,t_70)

### parent

starter的版本号不需要指定，而是继承自父级依赖`spring-boot-starter-parent`， parent是一个特殊的starter，用于管理所有子starter的依赖, 也就是说，只需要指定parent的版本，不需要关心普通starter的版本

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>2.0.0.RELEASE</version>
</parent>
```



### 示例

普通soringboot项目的依赖：

```xml
<?xml version="1.0" encoding="UTF-8"?>
  <project xmlns="http://maven.apache.org/POM/4.0.0"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>springBootLearn</groupId>
    <artifactId>springBootLearn</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.0.0.RELEASE</version>
    </parent>

   <dependencies>
       <dependency>
           <groupId>org.springframework.boot</groupId>
           <artifactId>spring-boot-starter-web</artifactId>
       </dependency>
   </dependencies>
</project>
```





## devtools

gradle:

```groovy
compile "org.springframework.boot:spring-boot-devtools"
```



maven:

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-devtools</artifactId>
</dependency>
```



Spring Boot以依赖的形式引入了一组开发者工具,包括如下功能：

* 自动重启: 当Classpath里的文件发生变化时,自动重启运行中的应用程序。
* LiveReload支持:对资源的修改自动触发浏览器刷新。
* 远程开发:远程部署时支持自动重启和LiveReload。
* 默认的开发时属性值:为一些属性提供有意义的默认开发时属性值




当应用程序以完整打包好的JAR或WAR文件形式运行时,开发者工具会被禁用,所以没有必要在构建包前移除这个依赖

### 自动重启

激活了devtools后,Classpath里对文件做任何修改都会触发应用程序重启

为了让重启速度够快,不会修改的类(比如第三方JAR文件里的类)都加载到了基础类加载器里,而应用程序的代码则会加载到一个单独的**重启类加载器**里。检测到变更时,只有重启类加载器重启

有些Classpath里的资源变更后不需要重启应用程序。像Thymeleaf这样的视图模板可以直接编辑,不用重启应用程序。在/static或/public里的静态资源也不用重启应用程序,所以Spring Boot开发者工具会在重启时排除掉如下目录:/META-INF/resources、/resources、/static、/public和/templates。



可以设置`spring.devtools.restart.exclude`属性来覆盖默认的重启排除目录:

例如,只排除/static和/templates目录:

```yaml
spring:
	devtools:
		restart:
			exclude: /static/**,/templates/**
```




关闭自动重启:

```yaml
spring:
	devtools:
		restart:
			enabled: false
```



还可以设置一个触发文件,必须修改这个文件才能触发重启。例如,在修改名为.trigger的文件前你都不希望执行重启:

```yaml
spring:
	devtools:
		restart:
			trigger-file: .trigger
```




### LiveReoload

用于web页面，devtools集成了[LiveReload](http://livereload.com),  Sprign Boot启动时会启动一个内嵌的LiveReload服务器,在资源文件变化时会触发浏览器刷新

* 不过很少有人开发MVC，这功能也没啥用



 禁 用 内 嵌 的 LiveReload 服 务 器 ：

```yaml
spring:
	devtools:
		livereload:
			enabled: false
```

### 默认的开发时属性

有些配置属性通常在开发时设置,从来不用在生产环境里。比如视图模板缓存,在开发时最好关掉,这样你可以立刻看到修改的结果。但在生产环境里,为了追求更好的性能,应该开启视图模版缓存。默认情况下,Spring Boot会为其支持的各种视图模板(Thymeleaf、Freemarker、Velocity、Mustache和Groovy模板)开启缓存选项。但如果存在Spring Boot的开发者工具,这些缓存就会禁用



这就是说在devtools激活后,如下属性会设置为false:

* spring.thymeleaf.cache
* spring.freemarker.cache
* spring.velocity.cache
* spring.mustache.cache
* spring.groovy.template.cache

这样一来,就不用在开发时(在一个开发时使用的Profile配置里)禁用它们了 





## Spring Boot CLI

http://start.spring.io是Spring Boot提供的项目构建工具，位于Web端， 它的命令行访问工具是Spring Boot CLI

* Spring Boot CLI实际上会请求http://start.spring.io， 因此二者是一个东西



Spring Boot CLI也不是万能的，比如它无法指定root package name ( 默认是 "demo")





### 下载SpiringBoot Cli



Mac:

```shell
brew tap spring-io/tap
```

```shell
brew uninstall springboot
```

```shell
brew install spring-boot
```

### 使用



Initialize a new project using Spring Initializr (start.spring.io):

```
spring init
```

 

可以指定项目依赖：

```
$ spring init -dweb,jpa,security
```

* ` --dependencies `or `-d`
* `--build gradle`: 默认项目构建工具是maven，可以指定使用gradle
* `-packaging` or ` -p` : 默认构建为JAR包，可以指定构建为WAR包： `-p war`

* `-n, --name <String>`: Project name; infer application name



查看命令帮助：

```
$ spring help init
```

## Profiles

Profile本身是Spring提供的功能，它和@Conditional一样，属于条件装配，表示一个环境的概念，如开发、测试和生产这3个环境：

- native
- test
- production

或者按git分支定义master、dev这些环境：

- master
- dev

在启动一个Spring应用程序的时候，可以传入一个或多个环境，例如：

```
-Dspring.profiles.active=test,master
```



Spring Boot对Profiles的支持在于，可以在`application.yml`中配置多个环境：

```yaml
spring:
  application:
    name: ${APP_NAME:unnamed}
  datasource:
    url: jdbc:hsqldb:file:testdb
    username: sa
    password:
    dirver-class-name: org.hsqldb.jdbc.JDBCDriver
    hikari:
      auto-commit: false
      connection-timeout: 3000
      validation-timeout: 3000
      max-lifetime: 60000
      maximum-pool-size: 20
      minimum-idle: 1

pebble:
  suffix:
  cache: false

server:
  port: ${APP_PORT:8080}

---

spring:
  profiles: test

server:
  port: 8000

---

spring:
  profiles: production

server:
  port: 80

pebble:
  cache: true
```

注意到分隔符`---`，最前面的配置是默认配置，不需要指定Profile，后面的每段配置都必须以`spring.profiles: xxx`开头，表示一个Profile。上述配置默认使用8080端口，但是在`test`环境下，使用`8000`端口，在`production`环境下，使用`80`端口，并且启用Pebble的缓存

* 如果不指定任何Profile，那么Profile实际上是`default`，可以从Spring Boot启动日志看出



启用profile：

```yaml
spring:
	profiles:
	active:production
```



## Actuator

Actuator会把它能收集到的所有信息都暴露给JMX。此外，Actuator还可以通过URL挂载一些endpoint(作为web接口)，通过它们了解应用程序运行时的内部状况

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```

* Actuator默认把所有访问点暴露给JMX，但出于安全原因，只有`health`和`info`会暴露给Web, 所有默认端点增加了`/actuator`前缀

  * 例如，可以查看health: 	http://localhost:8080/actuator/health
  * 注意，这是Actuator 2.x 中的新特性， 在 Actuator 1.x中，默认开放所有端点，也没有/actuator前缀

* 要暴露更多endpoint给Web，需要在`application.yml`中加上配置：

  ```yaml
  management:
    endpoints:
      web:
        exposure:
          include: info, health, beans, env, metrics
  ```





Actuator 提供了 13 个接口，可以分为三大类：

- **应用配置类**：获取应用程序中加载的应用配置、环境变量、自动化配置报告等与Spring Boot应用密切相关的配置类信息。
- **度量指标类**：获取应用程序运行过程中用于监控的度量指标，比如：内存信息、线程池信息、HTTP请求统计等。
- **操作控制类**：提供了对应用的关闭等操作类功能

| HTTP 方法 | 路径            | 描述                                                         |
| --------- | --------------- | ------------------------------------------------------------ |
| GET       | /autoconfig     | 提供了一份自动配置报告，记录哪些自动配置条件通过了，哪些没通过 |
| GET       | /configprops    | 描述配置属性(包含默认值)如何注入Bean                         |
| GET       | /beans          | 描述应用程序上下文里全部的Bean，以及它们的关系               |
| GET       | /dump           | 获取线程活动的快照                                           |
| GET       | /env            | 获取全部环境属性                                             |
| GET       | /env/{name}     | 根据名称获取特定的环境属性值                                 |
| GET       | /health         | 报告应用程序的健康指标，这些值由HealthIndicator的实现类提供  |
| GET       | /info           | 获取应用程序的定制信息，这些信息由info打头的属性提供         |
| GET       | /mappings       | 描述全部的URI路径，以及它们和控制器(包含Actuator端点)的映射关系 |
| GET       | /metrics        | 报告各种应用程序度量信息，比如内存用量和HTTP请求计数         |
| GET       | /metrics/{name} | 报告指定名称的应用程序度量值                                 |
| POST      | /shutdown       | 关闭应用程序，要求endpoints.shutdown.enabled设置为true       |
| GET       | /trace          | 提供基本的HTTP请求跟踪信息(时间戳、HTTP头等)                 |

### /beans

 /beans接口会返回一个 JSON 文档，描述上下文里每个 bean 的情况，包括其 Java 类型以及注入的其它 bean

bean：Spring 应用程序上下文中的 Bean 名称或 ID。

resource：.class 文件的物理位置，通常是一个 URL，指向构建出的 JAR 文件。这会随着应用程序的构建和运行方式发生变化。

dependencies：当前 Bean 注入的 Bean ID 列表。

scope：Bean 的作用域（通常是单例，这也是默认作用域）。

type：Bean 的 Java 类型。

### /autoconfig

`/autoconfig`接口能告诉你为什么会有这个 bean ，或者为什么没有这个 bean



提供endpoint可访问，如：

* /health，查看这个微服务的健康状况 
* /bean，创建的bean 
* /env，查看环境变量信息
