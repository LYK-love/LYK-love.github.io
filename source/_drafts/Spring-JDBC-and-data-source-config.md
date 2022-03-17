---
title: Spring JDBC and data source config
tags:
---



# 业务与访问持久化数据解耦

* 数据访问对象 （data  access object）DAO or Repository

![image-20220303195016590](/home/lyk/.config/Typora/typora-user-images/image-20220303195016590.png)

#  异常体系

![image-20220303195759488](/home/lyk/.config/Typora/typora-user-images/image-20220303195759488.png)

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

## 配置数据源

四种方式：

* 通过JNDI查找的数据源
* 连接池的数据源
* 通过JDBC驱动程序定义的数据源
* 配置嵌入式数据源

### JNDI

* JAVA命名与目录接口 Java Naming and Directory Interface
* 在Web容器中配置JNDI参数，定义一个数据源
* Spring中配置数据源

## JDBC

## 连接池

* 用于生产环境

## 嵌入式数据源

* \<jdbc:embeded-database\>
* 内存数据库，用于做测试
