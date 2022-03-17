---
title: Spring Boot Custom Configuration
tags:
---



# 覆盖 Spring Boot 自动配置

security的默认配置下，密码是在应用程序每次运行时随机生成后写入日志的,你需要查
找日志消息(默认写入标准输出)
 ,找到此类内容:

```
Using default security password: d9d8abe5-42b5-4f20-a32a-76ee3df658d9


```



再重申一次,想要覆盖Spring Boot的自动配置,你所要做的仅仅是编写一个显式的配置。
Spring Boot会发现你的配置,随后降低自动配置的优先级,以你的配置为准

* 通过@ConditionalOnMissingBean



## 禁用模版缓存

* 禁用模版缓存：

  ```yml
  spring:
  	thymeleaf:
  		cache: false
  ```

  或者用环境变量：

  ```shell
   export spring_thymeleaf_cache=false
  ```

  

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

# 通过属性文件外置配置

事实上,Spring Boot自动配置的Bean提供了300多个用于微调的属性。当你调整设置时,只
要在环境变量、Java系统属性、JNDI(Java Naming and Directory Interface)、命令行参数或者属
性文件里进行指定就好了。
要了解这些属性,让我们来看个非常简单的例子。你也许已经注意到了,在命令行里运行阅
读列表应用程序时,Spring Boot有一个ascii-art Banner。如果你想禁用这个Banner,可以将
spring.main.show-banner属性设置为false。有几种实现方式,其中之一就是在运行应用程
序的命令行参数里指定:
$ java -jar readinglist-0.0.1-SNAPSHOT.jar --spring.main.show-banner=false
另一种方式是创建一个名为application.properties的文件,包含如下内容:
spring.main.show-banner=false
或者,如果你喜欢的话,也可以创建名为application.yml的YAML文件,内容如下:
spring:
main:
show-banner: false
还可以将属性设置为环境变量。举例来说,如果你用的是bash或者zsh,可以用export命令:
$ export spring_main_show_banner=false
请注意,这里用的是下划线而不是点和横杠,这是对环境变量名称的要求。
实际上,Spring Boot应用程序有多种设置途径。Spring Boot能从多种属性源获得属性,包括
如下几处。
(1) 命令行参数
(2) java:comp/env里的JNDI属性
(3) JVM系统属性
(4) 操作系统环境变量

(5) 随机生成的带random.*前缀的属性(在设置其他属性时,可以引用它们,比如${random.
long})
(6) 应用程序以外的application.properties或者appliaction.yml文件
(7) 打包在应用程序内的application.properties或者appliaction.yml文件
(8) 通过@PropertySource标注的属性源
(9) 默认属性
这个列表按照优先级排序,也就是说,任何在高优先级属性源里设置的属性都会覆盖低优先
级的相同属性。例如,命令行参数会覆盖其他属性源里的属性。
application.properties和application.yml文件能放在以下四个位置。
(1) 外置,在相对于应用程序运行目录的/config子目录里。
(2) 外置,在应用程序运行的目录里。
(3) 内置,在config包内。
(4) 内置,在Classpath根目录。
同样,这个列表按照优先级排序。也就是说,/config子目录里的application.properties会覆盖
应用程序Classpath里的application.properties中的相同属性。
此外,如果你在同一优先级位置同时有application.properties和application.yml,那么application.
yml里的属性会覆盖application.properties里的属性。
禁用ascii-art Banner只是使用属性的一个小例子。让我们再看几个例子,看看如何通过常用
途径微调自动配置的Bean。

## 配置嵌入式服务器

无论出于什么原因,让服务器监听不同的端口,你所要做的就是设置server.port属性。

要是只改一次,可以用命令行参数:

```shell
$ java -jar readinglist-0.0.1-SNAPSHOT.jar --server.port=8000
```



但如果希望端口变更时间更长一点,可以在其他支持的配置位置上设置 server.port。例
如,把它放在应用程序Classpath根目录的application.yml文件里:
server:
port: 8000
除了服务器的端口,你还可能希望服务器提供HTTPS服务。为此,第一步就是用JDK的
keytool工具来创建一个密钥存储(keystore):

```shell
$ keytool -keystore mykeys.jks -genkey -alias tomcat -keyalg RSA
```

该工具会询问几个与名字和组织相关的问题,大部分都无关紧要。但在被问到密码时,一定
要记住你的选择。在本例中,我选择letmein作为密码。
现在只需要设置几个属性就能开启嵌入式服务器的HTTPS服务了。可以把它们都配置在命令
行 里 , 但 这 样 太 不 方 便 了 。 可 以 把 它 们 放 在 application.properties 或 application.yml 里 。 在
application.yml中,它们可能是这样的:

```yaml
server:
	port: 8443
	ssl:
		key-store: file:///path/to/mykeys.jks
```





## 配置日志

大多数应用程序都提供了某种形式的日志。即使你的应用程序不会直接记录日志,你所用的
库也会记录它们的活动。
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

## 配置数据源

虽然你可以显式配置自己的DataSource Bean,但通常并不用这么做,只需简单地通过属性
配 置数据库的 URL和 身份 信息就可以 了。举例来 说,如果你 用的是 MySQL数 据库, 你 的
application.yml文件看起来可能是这样的:

```yaml
spring:
	datasource:
		url: jdbc:mysql://localhost/readinglist
		username: dbuser
		password: dbpass
```


通常你都无需指定JDBC驱动,Spring Boot会根据数据库URL识别出需要的驱动,但如果识
别出问题了,你还可以设置spring.datasource.driver-class-name属性:

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

这里列出的只是自动配置支持的连接池,你还可以自己配置DataSource Bean,使用你喜欢
的各种连接池。
你也可以设置spring.datasource.jndi-name属性,从JNDI里查找DataSource:

```yaml
spring:
	datasource:
	jndi-name: java:/comp/env/jdbc/readingListDS
```

一旦设置了spring.datasource.jndi-name属性,其他数据源连接属性都会被忽略,除
非没有设置别的数据源连接属性。
有很多影响Spring Boot自动配置组件的方法,只需设置一两个属性即可。但这种配置外置的
方法并不局限于Spring Boot配置的Bean。让我们看看如何使用这种属性配置机制来微调自己的应
用程序组件。

###  配置多数据源

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





连接配置：

既然有多个数据源，因为数据库用户名密码可能不相同，所以是需要配置多个数据源信息的，直接在 `properties/yml` 中配置即可。这里要注意根据配置的属性名进行区分，同时因为数据源要有一个默认使用的数据源，最好在名称上有所区分（这里使用 **primary** 作为主数据源标识）。

```javascript
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



### **多数据源配置**

上面你应该看到了，到目前为止和 Mybatis 单数据源写法唯一的区别就是 Mapper 接口使用不同的目录分开了，那么这个不同点一定会在数据源配置中体现。

#### **主数据源**

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

#### **第二个数据源**

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

#### **连接池**

其实在多数据源改造中，我们一般情况下都不会使用默认的 JDBC 连接方式，往往都需要引入连接池进行连接优化，不然你可能会经常遇到数据源连接被断开等报错日志。其实数据源切换连接池数据源也是十分简单的，直接引入连接池依赖，然后把创建 dataSource 的部分换成连接池数据源创建即可。

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

## 应用程序Bean的配置外置

如创建一个单独的Bean,为它加上
@ConfigurationProperties注解,让这个Bean收集所有配置属性

类上加了@ConfigurationProperties注解,这说明该
Bean的属性应该是(通过setter方法)从配置属性值注入的。说得更具体一点,prefix属性说明
ReadingListController应该注入带amazon前缀的属性。



综合起来,我们指定ReadingListController的属性应该从带 amazon前缀的配置属性中
进行注入。 ReadingListController只有一个setter方法,就是设置 associateId属性用的setter
方法。因此,设置Amazon Associate ID唯一要做的就是添加amazon.associateId属性,把它加
入支持的任一属性源位置里即可。
例如,我们可以在application.properties里设置该属性:
amazon.associateId=habuma-20
或者在application.yml里设置:
amazon:
associateId: habuma-20
或者,我们可以将其设置为环境变量,把它作为命令行参数,或把它加到任何能够设置配置属性
的地方。



开启配置属性： 从技术上来说,@ConfigurationProperties注解不会生效,除
非先向Spring配置类添加@EnableConfigurationProperties注解。但通常无需这么
做,因为Spring Boot自动配置后面的全部配置类都已经加上了 @EnableConfigura-
tionProperties 注解。因此,除非你完全不使用自动配置(那怎么可能?)
 ,否则就无需显式地添加@EnableConfigurationProperties。



,Spring Boot的属性解析器非常智能,它会自动把驼峰规则的属性和使用
连 字 符 或 下 划 线 的 同 名 属 性 关 联 起 来 。 换 句 话 说 , amazon.associateId 这 个 属 性 和
amazon.associate_id以及amazon.associate-id都是等价的。用你习惯的命名规则就好。



## 使用Profile进行配置

。在这个例子中,我们就能为SecurityConfig加上@Profile注解:
```java
@Profile("production")
@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
...
}
```

这里用的@Profile注解要求运行时激活production Profile,这样才能应用该配置。如果
production Profile没有激活,就会忽略该配置,而此时缺少其他用于覆盖的安全配置,于是应
用自动配置的安全配置。
设置spring.profiles.active属性就能激活Profile,任意设置配置属性的方式都能用于
设置这个值。例如,在命令行里运行应用程序时,可以这样激活production Profile:

```shell
$ java -jar readinglist-0.0.1-SNAPSHOT.jar --spring.profiles.active=production
```


也可以向application.yml里添加spring.profiles.active属性:

```yaml
spring:
	profiles:
	active:production
```

还可以设置环境变量,将其放入application.properties。

但由于Spring Boot的自动配置替你做了太多的事情,要找到一个能放置@Profile的地方还
真不怎么方便。幸运的是,Spring Boot支持为application.properties和application.yml里的属性配置
Profile。
为了演示区分Profile的属性,假设你希望针对生产环境和开发环境能有不同的日志配置。在
生产环境中,你只关心WARN或更高级别的日志项,想把日志写到日志文件里。在开发环境中,
你只想把日志输出到控制台,记录DEBUG或更高级别。
而你所要做的就是为每个环境分别创建配置。那要怎么做呢?这取决于你用的是属性文件配
置还是YAML配置。

60
 第 3 章
 自定义配置
全配置用在开发环境刚刚好。在这个例子中,我们就能为SecurityConfig加上@Profile注解:
@Profile("production")
@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
...
}
这里用的@Profile注解要求运行时激活production Profile,这样才能应用该配置。如果
production Profile没有激活,就会忽略该配置,而此时缺少其他用于覆盖的安全配置,于是应
用自动配置的安全配置。
设置spring.profiles.active属性就能激活Profile,任意设置配置属性的方式都能用于
设置这个值。例如,在命令行里运行应用程序时,可以这样激活production Profile:
$ java -jar readinglist-0.0.1-SNAPSHOT.jar --
spring.profiles.active=production
也可以向application.yml里添加spring.profiles.active属性:
spring:
profiles:
active:production
还可以设置环境变量,将其放入application.properties,或者使用3.2节开头提到的各种方法。
但由于Spring Boot的自动配置替你做了太多的事情,要找到一个能放置@Profile的地方还
真不怎么方便。幸运的是,Spring Boot支持为application.properties和application.yml里的属性配置
Profile。
为了演示区分Profile的属性,假设你希望针对生产环境和开发环境能有不同的日志配置。在
生产环境中,你只关心WARN或更高级别的日志项,想把日志写到日志文件里。在开发环境中,
你只想把日志输出到控制台,记录DEBUG或更高级别。
而你所要做的就是为每个环境分别创建配置。那要怎么做呢?这取决于你用的是属性文件配
置还是YAML配置。

### 使用特定于Profile的属性文件

如果你正在使用application.properties,可以创建额外的属性文件,遵循application-{profile}.
properties这种命名格式,这样就能提供特定于Profile的属性了。
在日志这个例子里,开发环境的配置可以放在名为application-development.properties的文件
里,配置包含日志级别和输出到控制台:
```
logging.level.root=DEBUG
```

对于生产环境,application-production.properties会将日志级别设置为WARN或更高级别,并将
日志写入日志文件:

```
logging.path=/var/logs/
logging.file=BookWorm.log
logging.level.root=WARN
```



与此同时,那些并不特定于哪个Profile或者保持默认值(以防万一有哪个特定于Profile的配
置不指定这个值)的属性,可以继续放在application.properties里:

```yaml
amazon.associateId=habuma-20
logging.level.root=INFO
```

### 使用多Profile YAML文件进行配置

如果使用YAML来配置属性,则可以遵循与配置文件相同的命名规范,即创建application-
{profile}.yml这样的YAML文件,并将与Profile无关的属性继续放在application.yml里。
但既然用了YAML,你就可以把所有Profile的配置属性都放在一个application.yml文件里。举
例来说,我们可以像下面这样声明日志配置:

```yaml
logging:
level:
root:INFO

---

spring:
profiles: development
logging:
level:

root: DEBUG
---

spring:
profiles:production
logging:
path: /tmp/
file: BookWorm.log
level:
root: WARN
```

如你所见,这个application.yml文件分为三个部分,使用一组三个连字符(---)作为分隔符。
第二段和第三段分别为spring.profiles指定了一个值,这个值表示该部分配置应该应用在哪
个 Profile 里 。 第 二 段 中 定 义 的 属 性 应 用 于 开 发 环 境 , 因 为 spring.profiles 设 置 为
development。与之类似,最后一段的spring.profile设置为production,在production
Profile被激活时生效。

另一方面,第一段并未指定spring.profiles ,因此这里的属性对全部Profile都生效,或
者对那些未设置该属性的激活Profile生效。



除了自动配置和外置配置属性,Spring Boot还有其他简化常用开发任务的绝招:它自动配置了一个错误页面,在应用程序遇到错误时显示

## 定制应用程序错误页面

