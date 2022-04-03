---
title: Spring microservice
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

- 表现层（Representation）：json、xml、html、pdf、excel

- 状态转移（State Transfer）：服务端--客户端

- HTTP协议的四个操作方式的动词：GET、POST、PUT、DELETE

- - CRUD：Create、Read、Update、Delete

- 如果一个架构符合REST原则，就称它为RESTful架构





* @ResponseBody： 方法注解，该方法的返回值是java对象， Spring会从class路径里面找converter，converter就是能够将这个java对象转换成JSON的依赖包

  * coverter比如jackon：

    ```xml
            <dependency>
                <groupId>com.fasterxml.jackson.core</groupId>
                <artifactId>jackson-core</artifactId>
                <version>2.4.3</version>
            </dependency>
    ```

    

  * 每个方法都打一个注解，太啰嗦了

* @RestController：类注解，相当于给类的每个方法加上@ResponseBody

  ```java
      @RequestMapping(method = RequestMethod.POST, consumes = "application/json", produces = "application/json)
  
  ```

  * 指定请求路由，不符合要求的请求不会匹配到这个方法

* @RequestBody： 把客户端发过来的JSON转换成java对象

  * `@RequestMapping(method = RequestMethod.GET, produces = "application/json")`



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

# Spring Cloud

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

