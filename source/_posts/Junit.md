---
title: Junit
tags: Java
categories: Technology
date: 2023-08-14 22:04:16
---


How to use  [Junit5](https://junit.org/junit5/docs/current/user-guide), the java testing framework.

<!--more-->

# Introduction

##  What is JUnit 5?

Unlike previous versions of JUnit, JUnit 5 is composed of several different modules from three different sub-projects.

**JUnit 5 = \*JUnit Platform\* + \*JUnit Jupiter\* + \*JUnit Vintage\***

The **JUnit Platform** serves as a foundation for [launching testing frameworks](https://junit.org/junit5/docs/current/user-guide/#launcher-api) on the JVM. It also defines the `TestEngine` API for developing a testing framework that runs on the platform. Furthermore, the platform provides a [Console Launcher](https://junit.org/junit5/docs/current/user-guide/#running-tests-console-launcher) to launch the platform from the command line and the [JUnit Platform Suite Engine](https://junit.org/junit5/docs/current/user-guide/#junit-platform-suite-engine) for running a custom test suite using one or more test engines on the platform. First-class support for the JUnit Platform also exists in popular IDEs (see [IntelliJ IDEA](https://junit.org/junit5/docs/current/user-guide/#running-tests-ide-intellij-idea), [Eclipse](https://junit.org/junit5/docs/current/user-guide/#running-tests-ide-eclipse), [NetBeans](https://junit.org/junit5/docs/current/user-guide/#running-tests-ide-netbeans), and [Visual Studio Code](https://junit.org/junit5/docs/current/user-guide/#running-tests-ide-vscode)) and build tools (see [Gradle](https://junit.org/junit5/docs/current/user-guide/#running-tests-build-gradle), [Maven](https://junit.org/junit5/docs/current/user-guide/#running-tests-build-maven), and [Ant](https://junit.org/junit5/docs/current/user-guide/#running-tests-build-ant)).

**JUnit Jupiter** is the combination of the [programming model](https://junit.org/junit5/docs/current/user-guide/#writing-tests) and [extension model](https://junit.org/junit5/docs/current/user-guide/#extensions) for writing tests and extensions in JUnit 5. The Jupiter sub-project provides a `TestEngine` for running Jupiter based tests on the platform.

**JUnit Vintage** provides a `TestEngine` for running JUnit 3 and JUnit 4 based tests on the platform. It requires JUnit 4.12 or later to be present on the class path or module path.

# Add Dependency

[Ref](https://junit.org/junit5/docs/current/user-guide/#running-tests-build-maven)

* Supported Java Versions: Java 8 (or higher).



Add Junit5 dependency using Maven:

Edit in `pom.xml`:

```xml
<dependencies>
    <!-- ... -->
    <dependency>
        <groupId>org.junit.jupiter</groupId>
        <artifactId>junit-jupiter</artifactId>
        <version>5.9.2</version>
        <scope>test</scope>
    </dependency>
    <!-- ... -->
</dependencies>
```

# Create Tests

我们要测试的source code为:

```java
import java.util.stream.DoubleStream;

public class Calculator {

    static double add(double... operands) {
        return DoubleStream.of(operands)
                .sum();
    }

    static double multiply(double... operands) {
        return DoubleStream.of(operands)
                .reduce(1, (a, b) -> a * b);
    }
}
```



只需要写一个类, 其中使用Junit提供的Api进行测试

```java
class CalculatorTest{ //类名任意, 关键在于使用@Test等Junit提供的注解
    @Test
    @DisplayName("Add two numbers")
    void add() {
        assertEquals(4, Calculator.add(2, 2));
    }

    @Test
    @DisplayName("Multiply two numbers")
    void multiply() {
        assertAll(() -> assertEquals(4, Calculator.multiply(2, 2)),
                () -> assertEquals(-4, Calculator.multiply(2, -2)),
                () -> assertEquals(4, Calculator.multiply(-2, -2)),
                () -> assertEquals(0, Calculator.multiply(1, 0)));
    }
}
```

## IDEA Junit Support

[Create Junit Tests in IDEA](https://www.jetbrains.com/help/idea/junit.html#3135a84c)

IDEA提供了方便的Junit支持. 首先, 我们把源代码和测试类代码分别放在两个目录下, 前者标记为"Source Root", 后者标记为"Test Root".

![IDEA Junit Support1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Java/Junit/IDEA%20Junit%20Support1.png)



只要右击想要测试的类的类名, 在菜单中选择`Generate..` -> `Test`类, 即可在Test Root下生成测试类.

![IDEA Junit Support2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Java/Junit/IDEA%20Junit%20Support2.png)

# Annotations

Version: Junit5.

* `@BeforeEach`: 每个<u>test method</u>运行前都会执行一次`@BeforEach`方法. (如果一个测试类有N个测试方法, 则会运行N次)

* `@BeforeAll`: 在每个<u>test class</u>运行前都会执行一次`@BeforAll`方法.  (每个测试类只运行1次)

  * 在Junit4中, @BeforeEach and @BeforeAll的名字分别是@Before and @BeforeClass.

    
