---
title: Spring Microservice
tags: Spring
categories: Technology
---

# Microservice

- 应用程序分解为具有明确定义了职责范围的细粒度组件
- 完全独立部署，独立测试，并可复用
- 使用轻量级通信协议，HTTP和JSON，松耦合
- 服务实现可使用多种编程语言和技术
- 将大型团队划分成多个小型开发团队，每个团队只负责他们各自的服务

# Spring Boot 和 Spring Cloud

- Spring Boot提供了基于java的、面向REST的微服务框架
- Spring Cloud使实施和部署微服务到私有云或公有云变得更加简单

# Rest原则

- Representational State Transfer，表现层状态转移
- 资源（Resources），就是网络上的一个实体，标识：URI
- 表现层（Representation）：资源的表现形式， 有json、xml、html、pdf、excel
- 状态转移（State Transfer）：数据或资源在服务器和客户端之间的来回传送
- CS间的通信基于HTTP， HTTP协议的四个操作方式的动词：GET、POST、PUT、DELETE
* 对应CRUD：Create、Read、Update、Delete
- 满足REST原则的架构就是RESTful架构

## 内容协商

Content Negotiation：根据客户端请求的url扩展后缀、请求参数或者请求头来指定响应内容的类型

* 不符合要求的请求不会匹配到对应方法（见下文的注解，）



## 消息转换

以下注解都有可选的`value`字段，来指定请求路由的路径

### @RequestMapping

对请求进行路由，然后进行各种操作

实现了内容协商， 路径、请求类型、返回类型不匹配，均不会被匹配到对应的方法

* 此外，Spring还提供了@GetMapping、@PostMapping、@PutMapping、@DeleteMapping ， 它们是 @RequestMapping 的子集。 即`@GetMapping` = `@RequestMapping(method = RequestMethod.GET)。`

```java
@Target({ElementType.TYPE, ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Mapping
public @interface RequestMapping {
    String name() default "";

    //指定请求的实际地址
    @AliasFor("path")
    String[] value() default {};
    @AliasFor("value")
    String[] path() default {};
    //指定请求的method类型， GET、POST、PUT、DELETE等
    RequestMethod[] method() default {};
    //指定request中必须包含某些参数值是，才让该方法处理。
    String[] params() default {};
    //指定request中必须包含某些指定的header值，才能让该方法处理请求。
    String[] headers() default {};
    //指定处理请求的提交内容类型（Content-Type），例如application/json, text/html;
    String[] consumes() default {};
    //指定返回的内容类型，仅当request请求头中的(Accept)类型中包含该指定类型才返回；
    String[] produces() default {};
}
```

**示例说明：**

| 示例                                                         | 说明                                                         |
| ------------------------------------------------------------ | :----------------------------------------------------------- |
| @RequestMapping("/index")                                    | 默认为 GET 方法的路由 /index                                 |
| @RequestMapping(value="/index",method = RequestMethod.GET)   | 同上面一条                                                   |
| @RequestMapping(value="/add",method = RequestMethod.POST)    | 路由为 /add 的 POST 请求                                     |
| @RequestMapping(value="/add",method = RequestMethod.POST),consumes="application/json" | 路由为 /add 的 POST 请求，但仅仅处理 application/json 的请求 |
| @RequestMapping(value="/add",method = RequestMethod.POST),produces="application/json" | 路由为 /add 的 POST 请求，强调返回为 JSON 格式               |
| @RequestMapping(value="/add",method = RequestMethod.POST),params="myParam=xyz" | 路由为 /add 的 POST 请求，但仅仅处理头部包括 myParam=xyz 的请求 |
| @RequestMapping(value="/add",method = RequestMethod.POST),headers="Referer=http://www.xyz.com/" | 路由为 /add 的 POST 请求，但仅仅处理 来源为 www.xyz.com 的请求 |



### @ResponseBody

`@ResponseBody`： 方法注解，将方法返回的Java对象转换成JSON对象，写入 HTTP 响应体（ResponseBody）中.  转换需要外部的converter，Spring会从class路径里面找有对应转换能力的converter，

* coverter比如jackon：

  ```xml
          <dependency>
              <groupId>com.fasterxml.jackson.core</groupId>
              <artifactId>jackson-core</artifactId>
              <version>2.4.3</version>
          </dependency>
  ```




### @RequestBody

`@RequestBody`： 方法注解，读取HTTP请求体的数据，默认其编码类型为`application/json`，将其转换成java对象，作为方法的参数

* GET方式无请求体，所以没法用`@RequestBody`来处理

### @RestController

`@RestController`：类注解，相当于给类的每个方法加上`@ResponseBody`和`@Controller`

源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Controller
@ResponseBody
public @interface RestController {
    @AliasFor(
        annotation = Controller.class
    )
    String value() default "";
}

```

## 其他非REST注解

### @RequestParam vs @PathVariable

`@RequestParam` 和 `@PathVariable`都用于从请求URI中提取出数据，二者有细微差别



`@RequestParam`与将URI中的pattern转换为参数：

```java
@GetMapping("/foos/{id}")
@ResponseBody
public String getFooById(@PathVariable String id) {
    return "ID: " + id;
}
```

* `id`匹配的是`{id}`这个pattern

对应的请求为：

```
http://localhost:8080/spring-mvc-basics/foos/abc
----
ID: abc
```



`@PathVariable`直接对请求URI进行解码，得到参数：

```java
@GetMapping("/foos")
@ResponseBody
public String getFooByIdUsingQueryParam(@RequestParam String id) {
    return "ID: " + id;
}
```

对应的请求为：

```
http://localhost:8080/spring-mvc-basics/foos?id=abc
----
ID: abc
```





* SpringBoot starter：帮助管理依赖

  ```
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-starter-web</artifactId>
          </dependency>
  ```

  

* 通过parent来制定依赖版本（当然依赖包可以手动指定版本，这样会覆盖parent的版本）

  ```
      <parent>
           <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-parent</artifactId>
             <version>1.4.4.RELEASE</version>
             <relativePath/>
             <!-- lookup parent from repository -->
      </parent>
  ```

### @ExceptionHandler

`@ExceptionHandler` annotation is used for handling exceptions in specific handler classes and/or handler methods.

* 当其作用在方法时（肯定是Controller里的方法），作用域为所在的Controller

例如，可以自定义异常类：



```java
public class SpittleNotFoundException extends RuntimeException {

  private static final long serialVersionUID = 1L;
  
  private long spittleId;

  public SpittleNotFoundException(long spittleId) {
    this.spittleId = spittleId;
  }
  
  public long getSpittleId() {
    return spittleId;
  }
  
}
```



以下方法会抛出`SpittleNotFoundException`

```java
  public Spittle findOne(long id) {
    try {
    return jdbc.queryForObject(
        "select id, message, created_at, latitude, longitude" +
        " from Spittle" +
        " where id = ?",
        new SpittleRowMapper(), id);
    } catch (EmptyResultDataAccessException e) {
      throw new SpittleNotFoundException(id);
    }
  }
```



可以用`@ExceptionHandler`捕获该异常并处理：

```java
    @ExceptionHandler(SpittleNotFoundException.class)
    @ResponseStatus(HttpStatus.NOT_FOUND)
    public @ResponseBody
    Error spittleNotFound(SpittleNotFoundException e) {
        long spittleId = e.getSpittleId();
        return new Error(4, "Spittle [" + spittleId + "] not found");
    }
```

### @ControllerAdvice

`@ControllerAdvice`用于对异常集中处理，作用对象为TYPE，包括类、接口和枚举等，在运行时有效，并且可以通过Spring扫描为bean组件。其可以包含由@ExceptionHandler、@InitBinder 和@ModelAttribute标注的方法，可以处理多个Controller类，这样所有控制器的异常可以在一个地方进行处理

* 作用域是所有Controller

源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Component
public @interface ControllerAdvice {
    @AliasFor("basePackages")
    String[] value() default {};

    @AliasFor("value")
    String[] basePackages() default {};

    Class<?>[] basePackageClasses() default {};

    Class<?>[] assignableTypes() default {};

    Class<? extends Annotation>[] annotations() default {};
}
```





示例：

```java
@ControllerAdvice
public class ExceptionsHandler {

    @ExceptionHandler(CustomGenericException.class)//可以直接写@ExceptionHandler,不指明异常类，会自动映射
    public ModelAndView customGenericExceptionHnadler(CustomGenericException exception){ //还可以声明接收其他任意参数
        ModelAndView modelAndView = new ModelAndView("generic_error");
        modelAndView.addObject("errCode",exception.getErrCode());
        modelAndView.addObject("errMsg",exception.getErrMsg());
        return modelAndView;
    }

    @ExceptionHandler(Exception.class)//可以直接写@EceptionHandler，IOExeption继承于Exception
    public ModelAndView allExceptionHandler(Exception exception){
        ModelAndView modelAndView = new ModelAndView("generic_error");
        modelAndView.addObject("errMsg", "this is Exception.class");
        return modelAndView;
    }
}
```

* 然后所有Controller都会被这个类所影响

### @ResponseStatus

`@ResponseStatus`用于设置返回的HTTP响应报文的状态码:

```java
    @ExceptionHandler(SpittleNotFoundException.class)
    @ResponseStatus(HttpStatus.NOT_FOUND)
    public @ResponseBody
    Error spittleNotFound(SpittleNotFoundException e) {
        long spittleId = e.getSpittleId();
        return new Error(4, "Spittle [" + spittleId + "] not found");
    }
```

* 该方法返回的HTTP响应报文的状态码为404，而报文内容为自定义的值（这里是个自定义的Error对象）

## RestTemplate

ref: https://www.baeldung.com/rest-template

RestTemplate是Spring的模板类，在客户端上可以使用该类调用Web服务器端的服务，它支持REST风格的URL

- new RestTemplat()
- getForObject(),直接返回响应体， 没有状态头。指定返回类型，自动转换
- getForEntity()，返回ResponseEntity,有状态头和响应体，getBody()可以转换
- put()，传递的对象存在转换问题，String转成test/plain，MultiValueMap转成x-www-form-urlncoded，对象可能转成json，要看classpass类路径下有无库。
- delete（）,删除一个资源，一般提供资源路径即可
- postForObject()/postForEntity()/postForLocation
- - 因为需要返回值
  - postForLocation，只需要路径，不需要body，路径信息来源头部Location信息
- exchange(),可指定请求头信息
- - MultiValueMap headers;
  - HttpEntity<Object> requestEntity=new HttpEntity<Object>(headers);
  - ResponseEntity<Spitter> response = rest.exchange()



### **Get Plain JSON**

Let's start simple and talk about GET requests, with **a quick example using the \*getForEntity()\* API**:

```java
RestTemplate restTemplate = new RestTemplate();
String fooResourceUrl
  = "http://localhost:8080/spring-rest/foos";
ResponseEntity<String> response
  = restTemplate.getForEntity(fooResourceUrl + "/1", String.class);
Assertions.assertEquals(response.getStatusCode(), HttpStatus.OK);
```

**Notice that we have full access to the HTTP response**, so we can do things like check the status code to make sure the operation was successful or work with the actual body of the response:

```java
ObjectMapper mapper = new ObjectMapper();
JsonNode root = mapper.readTree(response.getBody());
JsonNode name = root.path("name");
Assertions.assertNotNull(name.asText());
```

We're working with the response body as a standard String here and using Jackson (and the JSON node structure that Jackson provides) to verify some details.

```java
RestTemplate restTemplate = new RestTemplate();
String fooResourceUrl
  = "http://localhost:8080/spring-rest/foos";
ResponseEntity<String> response
  = restTemplate.getForEntity(fooResourceUrl + "/1", String.class);
Assertions.assertEquals(response.getStatusCode(), HttpStatus.OK);
```

### **Retrieving POJO Instead of JSON**

We can also map the response directly to a Resource DTO:

```java
public class Foo implements Serializable {
    private long id;

    private String name;
    // standard getters and setters
}
```

Now we can simply use the *getForObject* API in the template:

```java
Foo foo = restTemplate
  .getForObject(fooResourceUrl + "/1", Foo.class);
Assertions.assertNotNull(foo.getName());
Assertions.assertEquals(foo.getId(), 1L);
```

### Use POST to Create a Resource

**In order to create a new Resource in the API, we can make good use of the \*postForLocation()\*, \*postForObject()\* or \*postForEntity()\* APIs.**

The first returns the URI of the newly created Resource, while the second returns the Resource itself.

#### postForObject()

##### post HttpEntity

postForObject本质上是将对象放入HttpEntity中，然后将对象POST给一个url，下面代码中所示的使用方法是最典型的一种：



```java
ClientHttpRequestFactory requestFactory = getClientHttpRequestFactory();
RestTemplate restTemplate = new RestTemplate(requestFactory);
 
HttpEntity<Foo> request = new HttpEntity<>(new Foo("bar"));//将对象装入HttpEntity中
Foo foo = restTemplate.postForObject(fooResourceUrl, request, Foo.class);
```

##### post JavaObject

实际上，如果不人为的将对象放入HttpEntity中，也可以直接使用RestTemplate去POST一个对象：



```java
Foo foo = new Foo("bar");
Foo foo = restTemplate.postForObject(fooResourceUrl, foo, Foo.class);
```



可以这么做的原因是,在RestTemplate的代码中，专门有一部分进行了POST对象的类型检测和转换  ：

```jsx
            if (requestBody instanceof HttpEntity) {
                this.requestEntity = (HttpEntity<?>) requestBody;
            }
            else if (requestBody != null) {
                this.requestEntity = new HttpEntity<Object>(requestBody);
            }
            else {
                this.requestEntity = HttpEntity.EMPTY;
            }
```

##### post JSON

如果需要post的对象是以JSON形式存储，则需要手动将JSON字符串转化成HttpEntity，具体做法如下：



```dart
String jsonString = "{\"id\":10,\"name\":\"test\"}";
HttpHeaders headers = new HttpHeaders();
headers.setContentType(MediaType.valueOf("application/json;UTF-8"));
HttpEntity<String> strEntity = new HttpEntity<String>(jsonString,headers);

RestTemplate restTemplate = new RestTemplate();
Foo foo = restTemplate.postForObject(url,strEntity,Foo.class);
System.out.println(jo2);
```





#### postForLocation()

Similarly, let's have a look at the operation that instead of returning the full Resource, just returns the *Location* of that newly created Resource:

```java
HttpEntity<Foo> request = new HttpEntity<>(new Foo("bar"));
URI location = restTemplate
  .postForLocation(fooResourceUrl, request);
Assertions.assertNotNull(location);
```

# Spring Cloud

Spring Cloud的工具集成：

- Spring Boot
- Spring Cloud Config
- Spring Cloud服务发现与Consul、Eureka集成
- 与Netflix Hystrix、Ribbon集成
- 与Netflix Zuul集成
- Spring Cloud Stream，与RabbitMQ、Kafka集成
- Spring Cloud Sleuth，与日志聚合工具Papertrail、跟踪工具Zipkin集成
- Spring Cloud Security



微服务划分：

- 可以从数据模型入手，每个域的服务只能访问自己的表
- 刚开始粒度可以大一点，不要太细，由粗粒度重构到细粒度是比较容易的
- 设计是逐步演化的



接口设计：

- 使用标准HTTP动词：GET、PUT、POST、DELETE，映射到CRUD
- 使用URI来传达意图
- 请求和响应使用JSON
- 使用HTTP状态码来传达结果



```xml
      <dependency>
        <groupId>org.springframework.cloud</groupId>
        <artifactId>spring-cloud-dependencies</artifactId>
        <version>Camden.SR5</version>
        <type>pom</type>
        <scope>import</scope>
      </dependency>
```

可以单独开发一个配置服务：

```xml
    <dependency>
      <groupId>org.springframework.cloud</groupId>
      <artifactId>spring-cloud-config-server</artifactId>
    </dependency>

    <dependency>
      <groupId>org.springframework.cloud</groupId>
      <artifactId>spring-cloud-starter-config</artifactId>
    </dependency>
```

```java
@SpringBootApplication
@EnableConfigServer //将该服务作为配置服务
public class ConfigServerApplication {
	public static void main(String[] args) {
		SpringApplication.run(ConfigServerApplication.class, args);
	}
}

```

# 微服务

- 基础设施即服务（Infrastructur as a Service , IaaS）
- 平台即服务（Platform as a Service, PaaS）
- 软件即服务（Software as a Service, SaaS）
- 函数即服务（Functions as a Service, FaaS），将代码块以“无服务器”（serverless）的形式部署，无须管理任何服务器基础设施
- 容器即服务（Container as a Service, CaaS），如亚马逊ECS(Amazon's Elastic Container Service）

## 微服务开发要考虑的问题

- 微服务划分、服务粒度、通信协议、接口设计、使用事件解耦微服务
- 配置管理：即把配置数据提供给对应的微服务，用spring cloud config来解决
- 服务注册、发现和路由：如何知道服务端的IP与端口号?要求每个微服务都要把信息注册(ip，端口 号)，到时候去服务中心找。Eureka
- 弹性、容错：用断路器模式来实现（（熔断））
- 负载均衡
- 可伸缩
- 日志记录和跟踪：整个处理路径经过多个微服务，知道每个服务的日志情况(Sleuth，日志聚合工 具
- 安全
- 构建和部署，基础设施即代码

### 单体应用程序的不足之处



**数据库的表**对所有模块**可见** 一个人的**修改**整个应用都要重新构建，测试与部署 **整体复制**分布式部署，不能拆分按需部署



Spring Boot，目的是简化spring的开发，提供了**基于**java的、**面向**REST的**微服务框架
** Spring Cloud使**实施和部署**微服务到私有云或公有云变得更加简单，spring cloud负责**服务治理** (配置服务，服务注册，日志跟踪等问题)

# Spring Cloud

```xml
	<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-config</artifactId>
  </dependency>
```



Spring Cloud使**实施和部署**微服务到私有云或公有云变得更加简单，spring cloud负责**服务治理** (配置服务，服务注册，日志跟踪等问题)

Spring Cloud的配置文件是`bootstrap.yml`, 与`application.yml`独立

* `bootstrap.yml`用于微服务配置，对其他微服务有影响
* `application.yml`是服务本身的配置，只作用于服务内部



用`nc`判断配置服务/数据库服务的端口是否可用，以便于继续往下启动其他服务:

```
#!/bin/sh

echo "********************************************************"
echo "Waiting for the configuration server to start on port $CONFIGSERVER_PORT"
echo "********************************************************"
while ! `nc -z configserver $CONFIGSERVER_PORT `; do sleep 3; done
echo ">>>>>>>>>>>> Configuration Server has started"

echo "********************************************************"
echo "Waiting for the database server to start on port $DATABASESERVER_PORT"
echo "********************************************************"
while ! `nc -z database $DATABASESERVER_PORT`; do sleep 3; done
echo ">>>>>>>>>>>> Database Server has started"

echo "********************************************************"
echo "Starting License Server with Configuration Service :  $CONFIGSERVER_URI";
echo "********************************************************"
java -Dspring.cloud.config.uri=$CONFIGSERVER_URI -Dspring.profiles.active=$PROFILE -jar /usr/local/licensingservice/@project.build.finalName@.jar

```







# 配置服务

```xml
	<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-config-server</artifactId>
  </dependency>
```



将配置信息解耦(服务配置信息与代码位置的几种情况):

* 配置信息硬编码 
* 分离的外部属性文件(单独的yml文件 
* 与物理部署分离，如外部数据库(把配置和jar包分离 
* 配置作为单独的服务提供



配置服务使用的存储库类型(4+4): 

* 共享的文件系统
* 源代码控制下的文件(git)
* 关系数据库
* nosql数据库







## server

启动类加注解:@EnableConfigServer:

```java
@SpringBootApplication
@EnableConfigServer //这意味着当前服务是配置服务，是数据提供端
public class ConfigServerApplication {
	public static void main(String[] args) {
		SpringApplication.run(ConfigServerApplication.class, args);
	}
}
```



在服务配置文件`application.yml`中规定配置数据所在的位置（可以在文件系统内，也可以在Internet）， 如:

```yml
####################################
#server:
#  port: 8888
#spring:
#  cloud:
#    config:
#      server:
#        encrypt.enabled: true
#        git:
#          uri: https://github.com/tzs919/config12.git
#          searchPaths: licensingservice




server:
  port: 8888
spring:
  profiles:
    active: native
  cloud:
    config:
      server:
        encrypt.enabled: true
        native:
        	# 指定配置文件位于本机文件系统（native）的classpath的config的licensingservice目录下
          searchLocations: classpath:config/licensingservice
          
```

* 注意，对配置的指定， 根本上是通过设置环境变量的方式。 因此，我们可以在外部（命令行、docker-compose.yml）中再次指定，以覆盖这里的配置



在微服务配置文件`bootstrap.yml`中声明服务名称：

```
spring:
  application:
    name: configserver

```





* 

## client

```xml
<!--        配置服务的client-->
        <dependency>
            <groupId>org.springframework.cloud</groupId>
            <artifactId>spring-cloud-config-client</artifactId>
        </dependency>
```



在微服务配置文件`bootstrap.yml`中指定配置服务的uri:

```yml
spring:
  application:
    name: licensingservice
  profiles:
    active:
      default
  cloud:
    config:
      uri: http://localhost:8888
```



## 对配置数据加密

属性加密：对称加密（共享密码）、非对称加密（公钥/私钥）



1. 下载并安装加密所需的Oracle JCE jar（jce_policy-8.zip）
   * JCE: Unlimited Strength Java Cryptography Extension
   * 将local_policy.jar、US_export_policy.jar复制到$JAVA_HOME/jre/lib/security目录
2. 在配置服务中加入环境变量`ENCRYPT_KEY`
   * Spring Boot Config Server启动时，如果发现设置了`ENCRYPT_KEY`，则自动添加两个端点：`/encrypt`和`/decrypt`
3. 将Config Server中要加密的属性的值的前面加上{cipher}前缀，其属性值也是被加密的
4. 将JCEjar打包成镜像， 然后将其作为基础镜像层，与 Config Server一起打包成新的镜像，相当于加解密服务和配置服务结合在一起
5. 启动该镜像，测试发现，该配置服务输出的配置信息中，被加密的属性的值，就是我们输入的被加密值， Client拿到后，需要再请求Config Server的`/devrypt`将该属性值解密





### 示例

这里使用对称加密，引入依赖：

```xml
        <dependency>
            <groupId>org.springframework.security</groupId>
            <artifactId>spring-security-rsa</artifactId>
        </dependency>
```



配置的数据库的帐号密码是：

```yml
			POSTGRES_USER: "postgres"
      POSTGRES_PASSWORD: "p0stgr@s"
```



Config Server：

```yml
...
spring.datasource.username: "postgres"
spring.datasource.password: "{cipher}7d6089040a0e135b6d7dbbe8025a8b14139a8105c182a82ec5b002a96b369670"
...
```

* 要把password加密，因此其值前面加了`cipher`前缀



Client Server收到该加密字段后，会向Server的`/decrypt`请求解密，得到密码`p0stgr@s`



### 配置数据自动更新

当配置数据发生变更。 config server会通知client， 而client需要相应该请求，这需要在使用配置数据的类上加上`@RefreshScope`

## 示例

一份完整的config server + client + database的docker-compose文件

```yaml
version: '2'
services:
  configserver:
    image: lyklove/johncarnell/tmx-confsvr:section12
    ports:
       - "8888:8888"
    environment:
      ENCRYPT_KEY:       "IMSYMMETRIC"
  database:
    image: lyklove/postgres:latest
    ports:
      - "5432:5432"
    environment:
      POSTGRES_USER: "postgres"
      POSTGRES_PASSWORD: "p0stgr@s" # 该值会被加密
      PASSWORD_AUTHENTICATION: "md5"
      POSTGRES_DB:       "eagle_eye_local"
  licensingservice:
    image: lyklove/johncarnell/tmx-licensing-service:section12
    ports:
      - "8080:8080"
    environment:
      PROFILE: "default"
      CONFIGSERVER_URI: "http://configserver:8888"
      CONFIGSERVER_PORT:   "8888"
      DATABASESERVER_PORT: "5432"
      ENCRYPT_KEY:       "IMSYMMETRIC"
```



# 服务发现

好处：

* 快速水平伸缩，而不是垂直伸缩。不影响客户端
* 提高应用程序的弹性



- pom.xml

- - `spring-cloud-starter-eureka-server`

- application.yml
- 引导类加注解@EnableEurekaServer



如何使用eureka开发服务发现? 开发eureka服务发现:

1. 加依赖spring-cluod-starter-eureka-server

2. 在启动类上加注解@EnableEurekaServer，表明这个微服务是服务发现

3. 编写application.yml文件，声明服务发现的端口号，客户端配置(是否注册到服务发现，这里是

   false;是否定期更新本地缓存的注册信息，这里是false)，服务端配置(注册成功后隔多长时间 对外提供服务;服务发现的url)

(注意服务发现甚至没有bootstrap) 注册服务开发中要做的:

1. 加依赖spring-cloud-starter-eureka

2. 编写application.yml，配置注册到eureka是否通过ip地址的方式、是否注册到服务发现、是否更新

   本地缓存注册表、服务发现的url

3. 编写bootstrap.yml，配置服务id，profile的active值，是否启用配置服务等。

4. 启动类加注解@EnableDiscoveryClient，@EnableEurekaClient

5. 调用其他微服务有三种方式:

   1. spring DiscoveryClient:建立访问对应微服务的Client类，并注入DiscoveryClient，通过 DiscoveryClient来获取服务实例信息并使用resttemplate进行调用。
   2. RestTemplate+Ribbon:在启动类中创建resttemplate的bean的方法上加注解 @LoadBalanced，然后创建负载均衡rule的bean，接着在访问其他微服务的Client类中注入 resttemplate，通过指定要调用的服务名进行调用。
   3. Feign:添加依赖spring-cloud-starter-feign，启动类添加注解@EnableFeignClients，然后 定义访问其他微服务的接口类，在接口上加注解@FeignClient("服务名")，并声明调用方法通 过@RequestMapping指定请求方法，返回值类型等信息





- pom.xml文件中的依赖

- - spring-cloud-starter-eureka

- bootstrap.yml、application.yml

- - 应用程序ID(ServiceId)、实例ID（6833e17cc88a:customerservice:8085）
  - eureka.client.fetchRegistry，本地缓存注册表，每隔30s客户端刷新
  - eureka.client.serviceUrl.defaultZone，可以有多个，逗号分隔

- - 启动类加注解：@EnableEurekaClient或@EnableDiscoveryClient
  - http://localhost:8761/eureka/apps/licensingservice  

- - Accept:application/json





# 负载均衡

如何使用选择具体的服务实例的策略(调用问题，轮询or随机)来选择调 用哪个服务实例，集成在客户端，从服务中心获取服务实例列表，实例会在客户端进行缓存，且**每隔一 段时间会重新更新**本地缓存数据

- Ribbon，主要提供客户侧的软件负载均衡算法

# 客户端弹性

远程服务发生错误或表现不佳导致的问题:客户端长时间等待调用返回



目标:让客户端**快速失败**，而不消耗数据库连接或线程池之类的宝贵资源，防止远程服务的问题向客户 端上游传播。

四种:

* 客户端负载均衡模式:Ribbon提供的负载均衡器，服务发现与服务之间的心跳出现问题时，会删 除该实例
* 断路器模式:监视调用失败的次数，快速失败
* 后备模式:远程服务调用失败，执行替代代码路径
* 舱壁隔离模式:线程池充当服务的舱壁



Hystrix:Hystrix是一个延迟和容错库，旨在隔离对远程系统，服务和第三方库的访问点，停止级联故 障，并在不可避免发生故障的复杂分布式系统中实现弹性



使用方法: 

加依赖：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
  <artifactId>spring-cloud-starter-hystrix</artifactId>
</dependency>
```



加注解：

启动类上加

```java
@EnableCircuitBreaker
```



