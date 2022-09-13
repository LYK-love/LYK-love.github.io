---
title: Programming Language Basic
tags: Compilers
categories: Computer Science
mathjax: true
date: 2022-09-12 16:30:33
---


Outline:

* The Static/Dynamic Distinction
* Environments and States
* Name
* Variable
* ...

<!--more-->

# The Static/Dynamic Distinction

If a language uses a policy that <u>allows the compiler to decide an issue</u> then we say that the language uses a **static** policy or that the issue can be decided <u>at compile time</u>.

* static: 某件事在编译期就被决定
* dynamic: 在运行期就被决定



以上是抽象的static/dynamic概念, 一个语言可以在一个方面是static的, 另一个方面又是dynamic的. 

例如:

* 对于Type System, 静态类型语言的类型在编译期就决定, 而动态类型语言的类型在运行期才能决定. 
  * 事实上, 由于类型系统最受关注, 我们叙述一门语言特性的时候, 经常省略掉定语“类型系统”, 直接说“XX语言是静态/动态的”.

* 对于变量的内存分配, 如果一个变量是静态变量( `class variable` in Java ):

  ```java
  public class Foo{
    public static int x;
  }
  ```

  变量`x`的内存分配已经确定了, 所有`Foo`的instance都共享这一个变量. 

# Environments and States

![Environments and States](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Compilers/Programming%20Language%20Basic/Environments%20and%20States.png)

- environment: 从**name**到**variable**的映射, 来区分同一作用域内同名的不同变量. 例如:

  ```c++
  int x = 1;
  
  void f()
  {
  	int x = 3;
  	cout << x << endl;
  }
  ```

  `f()`中的**变量名**`x`被environment映射到变量`x = 3`. 而`f`外的**变量名**`x`被environment映射到变量`x = 31`.

  * 当然, **变量`variable`, 或者说左值`lvalue`, 就是一块具有值的内存的location**, 所以“映射到变量”, 其实就是“映射到location”
  * 绝大多数PL的environment是**动态**的, 否则也无法区分同一作用域内同名的不同变量了.

  

- state: 从**location**到**value**的映射. 即lvalue到rvalue的映射

  * 大部分PL的state是**动态**的, 因为只有程序运行时才能得到value. 但也有**编译期决定的值,** 也就是静态的state, 比如const:

    ```
    const a = 1000
    ```

    这里`a`的值在编译期就决定了, 是1000. 

  * 当然, Macro的值也是编译器决定的: 
  
    ```c
    #define ARRAYSIZE 1000
    ```
  
    不过,macro不是变量, 只是个文本替换而已, 不能纳入name - variable - value的范畴

# Name

## name

* name: 这里的name是抽象的概念, 它指程序中的**一段有意义的文本**. 
  $$
  \mathrm{name} = \{ \mathrm{variable \  name}, \mathrm{macro \  name}, \mathrm{expression \  name}, \mathrm{keyword} \}
  $$

## identifer

* identifer: name的子集, 它的文本是<u>符号</u>形式的, 标识了一个程序中的**实体**
  $$
  \mathrm{identifer} = \{ \mathrm{variable \  name}, \mathrm{macro \  name} \}
  $$

  * identifer不包括expression name, 因为expression name是一段文本而不是一个符号; 也不包括`keyword`, 因为`keyword`并不标识什么实体, 在编程模型中也不发挥什么作用.

  * 例如:

    ```java
    class Foo{
    
    }
    
    class Bar{
    Foo foo;
    }
    
    Bar bar = new Bar();
    bar.foo; //expression name
    ```

    这里的`bar`和`foo`都是variable name( identifer ), 但`bar.foo`是一个expression name

## macro name

* macro name: macro的文本名字, 由于macro是预处理器面对的东西, 是一个文本上的替换, 对编译器是透明的, 对于程序而言不算“真正的”实体. 因此macro不属于变量, macro name也不是variable name.

## variable name

* variable name: 变量的文本名字, 它和identifier的唯一区别就是不含macro name.

  * 严格地说, 由于name只对编译器有用, 变量名作为一个文本, 其用处就是帮助编译器找到对应的变量. 从这个意义上讲, <u>变量名其实要包括变量的类型,</u>

    *  对于普通变量:

      ```c
      int x = 1; 
      double y = 0.43
      ```

      具体的变量名应该是`int x`, `double y`

    * 对于函数, 它的变量名就是Function Signature. 

  * 当然这样讲太啰嗦了, 因此通常我们就说变量名时不说类型.

# Variable

* variable: 这里的“变量”是比较抽象的说法, 它是一块具有值的内存的location( 也就是一个地址/指针 ), 或者说左值`lvalue`. 因此任何在内存中实际存在, 或者说对程序可见的“实体”都可以称为“变量”. ( Macro在编译前就被替换了,  也无所谓什么内存, 肯定不是变量  ). 

* 注意, **“变量是指针”**这个说法比较拗口. 所以我们一般就**用变量指向的值来代表该变量**, 也就是说一般省略掉“变量是指针”这一事实

  * 比如对于`int x = 3`, 我们就说`x`是个int类型的变量. 不会说“`x`是个lvalue, 它指向的rvalue是int类型的3”
  * 同理, 对于`int *p = new Obj()`, 我们就说`p`是个指针变量, 不会说"`p`是个lvalue, 它指向的rvalue是一个指针, 该指针又指向了对象"
  * 对于Java这样的“所有变量都是引用(指针)”的语言, 我们就说某某变量是个引用, 不会说“该变量是个lvalue, 它指向的rvalue是一个指针, 该指针又指向了对象”

* 常规的“变量”:

  ```c
  int x = 3;
  ```

  `x`是个变量名, 它被environment映射到一个具体的变量( OR location), 为了叙述方便, 我们通常直接说"变量`x`". 

  * 我们使用变量名`x`, 也就是通过它找到对应的那个**变量**或者说**左值**, 为了方便我们就将其称为**变量`x`**,  它就是个地址, 我们需要使用它的内容, 也就是它对应的右值value.

* **函数**也可以看作变量:

  ```c
  #define ARRAYSIZE 1000
  void f() 
  {
  	...
  	int x = ARRAYSIZE;
  }
  ```

  `f`是一个变量名, 当然严谨地说, 它的name是它的函数signature: `void f()`. 和常规的“变量”一样, 我们定义一个函数时, 会创建这个函数名对应的实体( 为了方便, 该实体就称为函数`f` ), 并为其分配内存. 

* 在将类型作为first-class member的语言中, **类型**也可以看做变量, 例如在Zig中:

  ```zig
  const std = @import("std");
  const assert = std.debug.assert;
  
  test "types are values" {
      const T1 = u8;
      const T2 = bool;
      assert(T1 != T2);
  
      const x: T2 = true;
      assert(x);
  }
  ```

  ```zig
  const std = @import("std");
  
  fn List(comptime T: type) type { //类型可以作为参数和返回值传递
      return struct {
          items: []T,
          len: usize,
      };
  }
  
  pub fn main() void {
      var buffer: [10]i32 = undefined;
      var list = List(i32){
          .items = &buffer,
          .len = 0,
      };
  
      std.debug.print("{d}\n", .{list.items.len});
  }
  ```

  可以看到, 所有的基本数据类型, 和用户自定义**类型**, 都是**`type`类型的变量**, 类型甚至可以作为参数和返回值传递. 这就把类型和变量的地位等同起来了.

# Assignment and getValue

变量其实是一个指针,  是一个lvalue.

* 变量的**赋值**, 也就是把一个rvalue copy到变量( 即lvalue )指向的空间, 即将原有的rvalue擦除，而以一个新值来替代.

* 变量的**取值**, 就是把变量( 即lvalue)所指向的空间的rvalue取出来. 

  * 注意, 只有lvalue可以取值, rvalue本身就是值. 
  * 我们所谓的“使用变量”, 其实是**使用变量指向的值**, 也就是lvalue对应的rvalue. 所以“使用变量”要先对变量取值
  * **对于Java这样的所有变量皆引用的语言, 其“使用变量”实际上是先得到rvalue( 一个指针/引用 ), 然后使用rvalue所指向的值(对象).**

* 例子:

  ```
  int x = 3; //变量赋值
  
  sum(x, 5); //使用变量
  ```

  1. 把rvalue 3 copy到了变量`x`指向的空间. 以后访问lvalue `x`, 得到的值就是3
  2. 使用了变量`x`. 也就是对`x`先进行取值, 得到rvalue 3, 作为sum的第一个argument

# Declaration, Definition and Initialization

声明和定义都是对变量而言. 表达式是个rvalue, 不存在“声明”, 都是“定义”.

对于C/CPP而言, Declaration, Definition and Initialization有明确区分, 对于其他语言就不一定了.

* Declaration: 使一个variable name为程序所知, 并且规定其<u>type</u>

  ```c++
  extern int x; // 在c/cpp中, 需要加extern来做到只声明不定义
  ```

* Definition: 真的创建该variable, 即为该变量申请一块内存. 

  * 定义时, **变量会被赋值**, **此时的赋值称为“初始化”.**

    * 可以手动赋值, 也就是“显示初始化”:

      ```c++
      int x = 1; // 声明并定义, 并显式初始化
      extern int k = 1//声明并定义k.  任何包含了显式初始化的声明即成为定义，这样写语法上没错，但会抵消extern的作用
      ```

    * 也可以不手动赋值,则会“隐式初始化”, 其赋的值要取决于具体情况:

      ```c++
      int x; // 声明并定义, 不显式初始化
      ```

  * 很多时候我们把声明和定义写在一起. 为了方便, **声明+定义统称为定义**:

    ```c
    int x = 1;
    ```

* Initialization: 定义时, **变量会被赋值**, **此时的赋值称为“初始化”**

  * 可以手动赋值, 也就是“显示初始化”:

    ```c++
    int x = 1; // 声明并定义, 并显式初始化
    ```

  * 也可以不手动赋值,则会“隐式初始化”, 其赋的值要取决于具体情况:

    ```c++
    int x; // 声明并定义, 不显式初始化
    ```

* **函数也是变量**, 因此对函数的声明就是写下**函数签名**( 别忘了Function Signature就是函数的variable name ), 使该函数名为程序所知. 对函数的定义也就是创建该函数实体, 为函数分配内存, 并赋值, **赋的“值”( rvalue )就是其函数实现**.在C/CPP中, 我们经常把变量/函数的声明和定义分开

# Parameter and Argument

* parameter: 形式参数, 函数本身的参数

* argument: 实际参数, 函数调用方传入的参数

  ```python
  a = 1
  
  def f(b):
  	return b*2
  print( f(a) )
  ```

  这里的`a`是argument, `b`是parameter

* 函数的参数是可以是lvalue(变量), 也可以是rvalue( 表达式, 常量... ).

# Parameter Passing

## Call by Value

```c++
int a = 3;
void f( int b ){
 b = b * 2;
}
```

变量名`a`对应变量`a` ( lvalue `a`), 它其实是个形如`0X432...`的地址, 在`0X432...`处存储了值`3`. lvalue `b`也同理, 是个形如`0X872...`

按值传递就是取出lvalue `a`  的rvalue, 然后赋值到lvalue `b`. 即取出`0X432...`的值, 然后赋值到`0X872...`



* Call by Value: 得到argument的**rvalue**, 然后赋值给parameter. 函数内部操作的是parameter, 其值的改变不会影响原来的argument.

  *  如果argument是个variable, 即一个lvalue  就会对其取值,得到rvalue
  * 如果argument是个expression, 则会对其求值, 得到结果(rvalue)


## Call by Reference

```c++
int a = 3;
void f( int& b ){
 b = b * 2;
}
```

按引用传递就是直接把`a`的lvalue copy给`b` , 现在`b`的lvalue就是`0X432...` ( `b`原来的的lvalue就没有了 ). 对`b`的操作其实就是对`a`的操作.



* Call by Reference: 直接将argument的lvalue copy给parameter, 不会取argument的rvalue

* 在Java中所有变量都是引用( 参见前文, 这话的实际意思是, 变量指向的rvalue是一个指针 ), 所有参数都是**按值传递**. 由于rvalue是一个指针, 按值传递又会赋值rvalue, 最终效果就是把指针赋值给了parameter. 对parameter的更改也就会导致对同一对象的更改.

  

# Static Scope and Block Structure

绝大部分语言的Scope是**静态的**, 语言被组织为一个个的block:

* C使用花括号:

  ```
  {
   ...
  }
  
  {
   ...
  }
  ```

* Awk使用`begin`, `end`:

  ```
  begin
  		...
  end
  ```

# Procedures, Functions and Methods

我们经常把Procedure, Function和Method混用, 严格来讲它们是不同的:

* Function: 返回某个类型的值的函数
* Procedure: 没有返回值的函数
* Method: Function, 但是是某个对象的成员



C中只有Function, 但是通过`void f()`, Function也就可以看做Procedure. 

Java作为纯OO语言只有Method.

# Explicit Access Control

OO语言会有:

* public
* protected
* private

# Aliasing

对于按引用传递的语言, 或者Java这样的类似按引用传递( 按值传递 + 变量即引用 )的语言, 由于直接传递了指向对象的指针, 因此可能会有两个变量指向同一个对象:

```java
String[] cars = {"Volvo", "BMW", "Ford", "Mazda"};

void f( String[] a, String[] b ){
	a[0] = "Tesla"
	b[0] = a[0] + "Haha"
}
```



这种情况称为Aliasing, 分析Aliasing对于编译器的Optimization非常重要:

```python
x = 2;
```

对于如上语句, 只有当编译器确定`x`所引用的对象没有Aliasing时, `x`才能直接被替换为`2`
