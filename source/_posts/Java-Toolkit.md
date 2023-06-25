---
title: Java Toolkit
tags:
  - Linux
  - Java
categories: Toolkit
date: 2022-09-13 15:13:52
---


Outline:

* JDK
* Maven

<!--more-->

# JDK

## 安装jdk

mac:

mac建议到[oracle官网](https://www.oracle.com/java/technologies/downloads/#java11-mac)下载jdk



linux一般用命令行安装，因此推荐openjdk



Ubuntu:

查找合适的openjdk版本:

```shell
# ubuntu
apt-cache search openjdk
```

安装:

```
sudo apt-get install upgrade
```



```shell
sudo apt-get install openjdk-8-jdk
```

* 如果search和install都没反应，应该先更新软件源

Manjaro:

查找合适的openjdk版本:

```shell
yay search jdk
```



```shell
yay install openjdk-8-jdk
```





(3) 配置环境变量, 编辑如下文件:

```
vim ~/.bashrc
```

在最后一行加:

```
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
```

## 查找JDK

查看jdk版本：

```shell
java -version
```



查找jdk:

```shell
whereis java
```

输出为

```
java: /usr/bin/java /usr/share/java /usr/share/man/man1/java.1.gz
```



查看jdk真实位置（上面的都是软链接）：

```shell
ls -l /usr/bin/java
```

输出为：

```
lrwxrwxrwx 1 root root 22 Mar 30 16:07 /usr/bin/java -> /etc/alternatives/java
```



```
ls -l /etc/alternatives/java
```

输出为：

```shell
lrwxrwxrwx 1 root root 46 Mar 30 16:07 /etc/alternatives/java -> /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java
# 以上就是jdk位置
```

## 配置jdk环境变量

### linux

对于linux:  编辑`/etc/profile`, 或 `~/.bashrc`, ` .zshrc`等：

```
vim /etc/profile # 这里可以选择任意的shell配置文件，
```

```shell
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64 # 这里填jdk位置
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=$PATH:${JAVA_HOME}/bin
```



使配置文件生效：

```
source /etc/profile
```

### mac

mac的jdk安装位置和linux不同



查询当前的java的安装版本

```shell
cd /Library/Java/JavaVirtualMachines
ls
```



配置`.zshrc`

```bash
# jdk 版本切换， on mac
# jdk-17.0.2.jdk   jdk1.8.0_321.jdk jdk-11.0.14.jdk 
export JAVA_8_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_321.jdk/Contents/Home
export JAVA_11_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.14.jdk/Contents/Home
export JAVA_17_HOME=/Library/Java/JavaVirtualMachines/jdk-17.0.2.jdk/Contents/Home



alias jdk8='export JAVA_HOME=$JAVA_8_HOME'
alias jdk11='export JAVA_HOME=$JAVA_11_HOME'
alias jdk17='export JAVA_HOME=$JAVA_17_HOME'
```

```shell
source ~/.bash_profi
```



切换jdk版本

```shell
jdk11
java -version
```

# Maven

maven配置文件位置： `～/.m2/settings.xml`

加入阿里云仓库：

```xml
        <!-- 阿里云仓库 -->
        <mirror>
            <id>alimaven</id>
            <mirrorOf>central</mirrorOf>
            <name>aliyun maven</name>
            <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
        </mirror>
```

