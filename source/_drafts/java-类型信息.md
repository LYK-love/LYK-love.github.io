---
title: java 类型信息
tags: java
categories: language
---



#  RTTI

* Java使用Class对象执行其RTTI
* jAVA类在必须时才加载
  * 当程序创建第一个对类的**静态成员**的引用时，就会加载这个类
    * 因此构造器也是静态成员

## 类加载

* 加载  -> 验证 -> 准备 -> 解析 -> 初始化 -> 使用 -> 卸载
* 类加载只有一次

### 初始化

1. 静态变量初始化
   * `static final`变量不会初始化，直接赋值
2. 静态变量赋值
3. 执行静态代码块

```java
public class TestClassLoader
{
    public static int k=0;
    static TestClassLoader t1 = new TestClassLoader("t1");
    public static TestClassLoader t2 = new TestClassLoader("t2");
    public static int i = print("i");
    public static int n = 99;
    public int j = print("j");

    static{
        print("静态块");
    }
    public TestClassLoader(String str)
    {

        System.out.println((++k)+ ": " + str + " i=" + i + " n=" + n );
        ++i;
        ++n;
    }

    public static int print(String str)
    {
        System.out.println((++k)+ ": " + str + " i=" + i + " n=" + n );
        ++n;
        return ++i;
    }
    public static void main(String[] args)
    {
        new TestClassLoader("init");
    }
}
```

上述程序输出为：

```
1: j i=0 n=0
2: t1 i=1 n=1
3: j i=2 n=2
4: t2 i=3 n=3
5: i i=4 n=4
6: 静态块 i=5 n=99
7: j i=6 n=100
8: init i=7 n=101
```



* Class loader: 

  * 先检查这个类的`Class`对象是否被加载

    

    * 若未加载

  * 一旦`Class`对象加载入内润，就被用来创建该类的所有对象

# Class对象

# 类型转换前先做检查

# 注册工厂

# 反射

# 动态代理

# 空对象

# 接口与类型信息



java中，所有的类型转换都在运行时进行正确性检查，
