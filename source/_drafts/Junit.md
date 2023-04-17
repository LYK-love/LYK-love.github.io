---
title: Junit
tags:
---



* [Official Doc](https://junit.org/junit5/docs/current/user-guide/)

# Add Dependency

[Ref](https://junit.org/junit5/docs/current/user-guide/#running-tests-build-maven)

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

![image-20230402145336502](/Users/lyk/Library/Application Support/typora-user-images/image-20230402145336502.png)



只要右击想要测试的类的类名, 在菜单中选择`Generate..` -> `Test`类, 即可在Test Root下生成测试类.

![image-20230402145407353](/Users/lyk/Library/Application Support/typora-user-images/image-20230402145407353.png)
