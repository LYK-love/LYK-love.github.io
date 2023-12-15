---
categories:
- Software Engineering
date: 2022-02-23 21:37:07
tags: Java
title: Java Class
---

Outline

* RTTI
* Class对象
* 类型转换前先做检查
* 反射
* 动态代理
* 空对象



ref ： Thinking in Java

<!--more-->

#  RTTI

* Java使用Class对象执行其RTTI
* Java类在必须时才加载
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

生成类对象的引用：

* ``Class.forName(String className)`静态方法: 返回该类的Class引用，具有副作用，如果该类还没有加载就会加载该类。该方法会抛出异常。

  ```java
  Class t = Class.forName("java.lang.Thread")
  ```

  * Params:
    className – the fully qualified name of the desired class.
  * Returns:
    the Class object for the class with the specified name.
  * Throws:
    LinkageError – if the linkage fails
    ExceptionInInitializerError – if the initialization provoked by this method fails
    ClassNotFoundException – if the class cannot be located

  

* `Class.class`（ **类字面常量** ）： 返回类对象的引用，**没有副作用**

* `object.getClass()`:  获得对象的**确切类型**的Class引用



类名：

`object.getName()`: 返回全限定名

`object.getSimpleName()`: 返回不含包名的类名

`object.getCanonicalName()`: 返回全限定名



创建对象：

`Class.newInstance()`实例方法：“虚拟构造器”，能且仅能调用该类的public无参数构造方法





# 类型转换前先做检查

Class引用可以指向别的Class对象，这个错误在编译期不会发现。 使用泛型语法可以在编译期执行类型检查：

```java
Class intClass = int.class;
Class<Integer> genericClass = int.class;
genericClass = Integer.class; // same thing

intClass = double.class; // 编译期不会报错
genericIntClass = double.class;  // illegal
```



判断类型是否兼容：

* ```java
  if( Object obj_a instanceof Class class_b){
  }
  ```

* ```java
  public boolean isInstance(Object o);
  ```



判断类型是否相等：

* `equals()`
* `==`



# Reflection

## 利用反射来查看类

`getDeclaredXX()` 方法可以无视访问权限

* 得到方法：

  - `Method getMethod(name, Class...)`：获取某个`public`的`Method`（包括父类）
  - `Method getDeclaredMethod(name, Class...)`：获取当前类的某个`Method`（不包括父类）
  - `Method[] getMethods()`：获取所有`public`的`Method`（包括父类）
  - `Method[] getDeclaredMethods()`：获取当前类的所有`Method`（不包括父类）

* 得到字段：

  - `Field getField(name)`：根据字段名获取某个public的field（包括父类）
  - `Field getDeclaredField(name)`：根据字段名获取当前类的某个field（不包括父类）
  - `Field[] getFields()`：获取所有public的field（包括父类）
  - `Field[] getDeclaredFields()`：获取当前类的所有field（不包括父类）

* 访问构造方法：

  - `getConstructor(Class...)`：获取某个`public`的`Constructor`；
  - `getDeclaredConstructor(Class...)`：获取某个`Constructor`；
  - `getConstructors()`：获取所有`public`的`Constructor`；
  - `getDeclaredConstructors()`：获取所有`Constructor`。

* 得到继承关系：

  - `Class getSuperclass()`：获取父类类型；
  - `Class[] getInterfaces()`：获取当前类实现的所有接口。

  通过`Class`对象的`isAssignableFrom()`方法可以判断一个向上转型是否可以实现。



例子： 打印类的方法和构造方法：

```java
public class ShowMethods {
    private static String usage = "Please input a Class";

    private static Pattern pattern = Pattern.compile("\\w+\\.");

    public static void println(String str){ System.out.println(str); }
    public static void print(String str){ System.out.print(str); }

    public static void main(String[] args)
    {
        if(args.length < 1)
        {
            println( usage );
        }
        int lines = 0;
        try{
            Class<?> c = Class.forName( args[0] );
            Method[] methods = c.getMethods();
            Constructor[] constructors = c.getConstructors();
            if(args.length == 1)
            {
                for( Method method: methods )
                {
                    println( pattern.matcher(method.toString()).replaceAll("") );
                }
                for(Constructor constructor: constructors )
                {
                    println( pattern.matcher( constructor.toString() ).replaceAll("") );
                }
                lines += methods.length + constructors.length;
            }
            else{
                ;
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
```

## 利用反射来修改类

反射可以绕过几乎所有障碍（访问权限）来得到类的信息、修改类，



即使只发布字节码文件，依然可以通过`javap`这样的反编译工具查看源代码

* `javap -p`: 显示所有成员，包括私有成员



下面给出两种防御措施，并给出破解方案, 基本思路是：

1.  只要得到对象，就可以调用`getClass()`得到其实际类型（破解了类访问权限），
2. 再用`getDeclaredXXX()`得到其所有字段/方法（破解了字段/方法访问权限）
3. 对非public字段/方法/构造方法的访问、修改，都要先`setAccessible(true)`
   * 有些jvm有security manager,可能会拒绝`setAccessible(true)`
4. 接下来就可以设置字段： `Field.set(Object, Object)`，其中第一个`Object`参数是指定的实例，第二个`Object`参数是待修改的值
   * `final`字段在被修改时是安全的， 运行时系统会在不抛任何异常的情况下接受修改尝试，但实际上不会发生任何修改

### 隐瞒类访问权限

#### 防御措施

接口A只有方法`f()`:

```java
package typeinfo.packageaccess;

public interface A {
    void f();
}

```







只暴露HiddenC一个类，它产生A类型（实际是C类型）的对象， 但是调用者无法调用A接口之外的方法， 因为类名C是不可见的， 因此理论上`g()`,`u()`等不应该能被调用

```java
class C implements A {
    public void f(){
        Utils.println( "public C.f()" );
    }

    public void g()
    {
        Utils.println("public C.g()");
    }

    void u(){ Utils.println("package C.u()"); }
    protected void v(){ Utils.println("protected C.v()"); }


    private void w(){
        Utils.println("private C.w()"  );
    }
}


public class HiddenC {
    public static A makeA(){ return new C(); }
}

```





#### 破解方案

得到a的实际类型，然后进行方法调用

```java
static void callHiddenMethod( Object a, String method_name ) throws Exception
{
        Method g = a.getClass().getDeclaredMethod(method_name);
        g.setAccessible(true);
        g.invoke(a);
}
```



#### 主程序

```java
package typeinfo.HiddenImplementation;
import typeinfo.packageaccess.*;
import java.lang.reflect.Method;

public class HiddenImplementation {

    public static void main(String[] args) throws Exception {
        A a = HiddenC.makeA();
        a.f();

        //编译期错误，找不到类型C
//        if( a instanceof C)
//        {
//            C c = (C)a;
//            c.g();
//        }
        
        //绕过了包访问权限！！！
        callHiddenMethod(a, "g");
        callHiddenMethod(a, "u");
        callHiddenMethod(a, "v");
        callHiddenMethod(a, "w");


    }
}

```





### 隐瞒字段访问权限

破解方法：

通过`getDeclaredField(field_name)` 就可以得到私有字段

后续可以`setAccessible(true)`，`set(Object, Object)`对字段进行修改（ final字段不可被修改，因此是安全的 ）

```java
		WithPrivateFinalField pf = new WithPrivateFinalField();        
		f = pf.getClass().getDeclaredField("s2");
        f.setAccessible(true);
        f.set(pf,"No, you're not!" );
        System.out.println(pf);
```



示例：

#### 防御措施

```java
class WithPrivateFinalField{
    private int i = 1;
    private final String s1 = "I'm totally safe";
    private String s2 = "Am I safe?";
    public String toString(){
        return "i = " + i + ", " + s1 + ", " + s2;
    }


}
```

#### 破解方案

```java
public class ModifyingPrivateFields {
    public static void main(String[] args) throws Exception
    {
        WithPrivateFinalField pf = new WithPrivateFinalField();
        System.out.println(pf);

        Field f = pf.getClass().getDeclaredField("i");
        f.setAccessible(true);
        f.setInt(pf,47);
        System.out.println(pf);

        f = pf.getClass().getDeclaredField("s1");
        f.setAccessible(true);
        f.set(pf,"No, you're not!" );
        System.out.println(pf);

        f = pf.getClass().getDeclaredField("s2");
        f.setAccessible(true);
        f.set(pf,"No, you're not!" );
        System.out.println(pf);
    }
}
```

#### javap查看源代码

可以看到，我们能看到private字段，因此保护是没有用的



```java
❯ javap  -p /home/lyk/Projects/java_learning/out/production/java_learning/WithPrivateFinalField.class
Compiled from "ModifyingPrivateFields.java"
class WithPrivateFinalField {
  private int i;
  private final java.lang.String s1;
  private java.lang.String s2;
  WithPrivateFinalField();
  public java.lang.String toString();
}
```



# 动态代理

```java
class DynamicProxyHandler implements InvocationHandler{
    private Object proxied;
    public DynamicProxyHandler(Object proxied)
    {
        this.proxied = proxied;
    }

    public Object invoke(Object proxy, Method method, Object[] args ) throws Throwable
    {
        System.out.println( "**** proxy: " + proxy.getClass() + ", method: " + method + ", args: " + args );
        if(args != null)
        {
            for(Object arg: args)
            {
                System.out.println("    " + arg);
            }
        }
        return method.invoke(proxied, args);

    }


}

public class SimpleDynamicProxy {
    public static void consumer(Interface iface)
    {
        System.out.println("do " + iface);
    }

    public static void main( String[] args )
    {
        RealObject realObject = new RealObject();
        consumer(realObject);
        Interface proxy = (Interface) Proxy.newProxyInstance(
                Interface.class.getClassLoader(),
                new Class[] { Interface.class  },
                new DynamicProxyHandler( realObject )
        );
        consumer(proxy);
    }
}
```

在运行期动态创建一个`interface`实例的方法如下：

1. 定义一个`InvocationHandler`实例，它负责实现接口的方法调用；

2. 通过

   ```
   Proxy.newProxyInstance()
   ```

   创建

   ```
   interface
   ```

   实例，它需要3个参数：

   1. 使用的`ClassLoader`，通常就是接口类的`ClassLoader`；
   2. 需要实现的接口数组，至少需要传入一个接口进去；
   3. 用来处理接口方法调用的`InvocationHandler`实例。

3. 将返回的`Object`强制转型为接口。

# 空对象

空对象，相比`null`好处是它更靠近数据，因为对象标识的是问题空间的实体

（ 感觉没啥用，增加了编程的复杂性 ）