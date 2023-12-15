---
categories:
- Software Engineering
date: 2021-06-17 15:45:06
tags: C++
title: C++面向对象-Part3
---

Outline:

* Template
* Exception
* IO处理
* 右值引用
* 移动构造
* 外部模板
* Lambda表达式
* 联合初始化

<!--more-->

# 模板

* 多态的一种形式

* 源代码复用机制

* 参数化模块

  * 对程序模块(如: 类, 函数)加上`类型参数`
  * 对不同类型的数据实施相同的操作
  
* 多态的一种形式

* C++
  * 类属函数( 模板函数 )
  * 类属类( 模板类 )

## 类属函数

* 同一函数对不同类型的数据完成相同的操作

* 宏实现
  * `#define max(a,b) ( (a)>(b) ? (a) : (b) )`
  * 缺陷: 宏没有类型检查
  
* 函数重载
  * `int max(int, int)` `double max(double,double)`
  * 缺陷:
    *  需要定义的重载函数太多
    * 定义不全

* 函数指针
  * `void sort( void*, unsigned int , unsigned int, int(*cmp)( coid*, void* ) )`
  *  缺陷
    * 需要定义额外参数
    * 大量指针运算
    * 实现起来复杂
    * 可读性差

* 函数模板

  ```c++
  template< typename T >
  void sort( T A[], unsigned int num )
  {
      for( int i = 1; i < num ; i++ )
          for( int j = 0 ; j < num - i; j++ )
          {
              if( A[j] > A[j+1] )
              {
                  T t = A[j];
                  A[j] = A[j+1];
                  A[j+1] = t;
              }
          }
      
  }
  ```

  *  不需要显式传参, 因为T具体是什么类型可以通过传递的参数推导出来
  * 必须重载操作符

* 函数模板定义了一类重载的函数

* 编译系统自动实例化函数模板

* 函数模板的参数

  * 可有多个类型参数, 用逗号分隔  

    ```c++
    template < typename T1, typename T2 >
    void f( T1 a, T2 b )
    {}
    ```

    

  *  可带普通参数

    * 必须列在类型参数之后
  
* 调用时需显式实例化
  ```C++
  template< typename T, int size >
  void f(T a)
  {
       T temp[size];
     ...
       f<int,10>(1);
  }

* 模板特化

  * 定义一个具有特定类型(而不是模板类型)的函数

  * 必须在头部之前使用 `template<>`,  以显示这是前面定义的模板函数的特化
  * 编译器首先匹配`普通函数`,再匹配`模板特化`, 再匹配`模板函数` 
  
* 类模板中的静态成员属于实例化后的类

* 模板是一种**源代码复用**的机制

  * 实例化: 生成具体的函数/类

  * 函数模板的实例化
    * 隐式实现
    * 根据具体模板函数调用
    
  * 类模板的实例化
    * 创建对象时显式指定
    
  * 是否实例化模板的某个实例由使用点来决定;如果未使用到一个模板的某个实例, 则编译系统不会生成相应实例的代码

  * 如果在模块A中要使用模块B中定义的某模块的实例, 而在模块B中未使用这个实例, 则模块A无法使用这个实例

  * **C++中模板的完整定义通常放在头文件中**

    * 编译方法有两种：包含式和独立编译式。独立编译理论最有，但对模板并不适用，`export`可以实现独立编译，但没有主流编译器支持，它也在新标准中被废止

      包含式：声明文件包含在定义文件中，定义文件包含在应用程序文件中，只编译应用程序文件

    ```
    ```

    

    

*  模板元编程

  ```c++
  template< int N >
  class Fib
  {
      public:
      enum{ value + Fib< N - 1>:: value + Fib< N - 2 >:: value };
  };
  
  template<>
  class Fib<0>
  {
      enum { value = 1 };
  };
  
  template<>
  class Fib<1>
  {
      enum { value = 1 };
  };
  
  int main()
  {
      cout << Fib<8>::value << endl;
  }
  ```

  这段程序在**编译器**就能出结果. 元编程就是编写一个程序, 这个程序可以生成更多的程序

# 异常

* 错误
  * 语法错误
    * 编译系统
  * 逻辑错误
    * 测试
* 异常
  * 运行环境造成
    * 内存不足，文件操作失败等
  * 异常处理
* 特征
  * 可以预见
  * 无法避免
* 作用
  * 提高程序*Robuntness*
* 常见处理方法
  * 函数参数
    * 返回值
    * 引用参数
  * 逐层返回
* 缺陷
  * 程序结构不清楚

* C++异常处理机制
  * 一种专门、清晰描述异常处理过程的机制
* 处理机制
  * `try`
    * 监控  ` try { <语句序列> } `
  * `throw`
    * 抛掷异常对象    `throw <表达式>`
  * `catch`
    * 捕获异常并处理 ` catch ( <类型>  [ < 变量> ]) { 语句序列 }`
* `catch`
  * 类型: 异常类型精确匹配
  * 变量: 存储异常对象, 可省
  * 一个`try`语句块后面可跟多个`catch`语句块, 用于捕获不同类型的异常进行处理

* 定义异常类
  * 注意`catch` 块顺序

```c++
class FileErrors{};

class NonExist: public FileErrors{};
class NonExist: public FileErrors{};
class WrongFormat: public FileErrors{};
class DiskSeekError: public FileErrors{};

```



例题:

```C++
class MyExceptionBase
{}; //对象切片

class MyExceptionDerived: public MyExceptionBase
{
};

void f( MyExceptionBase& e )
{
    throw e;
}

int main()
{
    MyExceptionDerived e;
    try{
        f(e);
    } catch ( MyExceptionDerived& e  )
    {
        cout << "MyExceptionDerived" << endl; 
    }
    catch( MyExceptionBase& e )
    {
        cout << "MyExceptionBase" << endl; 
    }
    return 0;

}
```

这段代码会输出`"MyExceptionBase" `, 因为`throw`抛出对象是**拷贝构造**, 而父类的拷贝构造函数不是虚函数,所以会调用父类的拷贝构造函数, 进行对象切片,`throw`的结果是一个父类对象

* 特例

  * 无参数`throw`

    * 将捕获到的异常对象重新抛掷出去

      `catch(int)  {throw }`

  * catch( ... )

    * 默认异常处理

* `Use destructors to prevent resource leaks`

  ```c++
  template< typename T >
  class auto_ptr
  {
      public:
  
      auto_ptr( T *p = nullptr )
      :ptr( p )
      {}
  
      ~auto_ptr() {delete ptr;}
      T* operator ->() const { return ptr; }
      T& operator *() const {return *ptr;} 
  
      private:
      T* ptr;
  
  };
  ```

  

```C++
//WINDOW_HANDOW是一个指针类型


template< typename T >
class auto_ptr
{
    public:

    auto_ptr( T *p = nullptr )
    :ptr( p )
    {}

    ~auto_ptr() {delete ptr;}
    T* operator ->() const { return ptr; }
    T& operator *() const {return *ptr;} 

    private:
    T* ptr;

};

Class WindowHandle
{
    public:
    WindowHandow( WINDOW_HANDLE handler )
    :w(handle)
    {}

    ~WindowHandle()
    {
        destroyWindow(w);
    }

    operator WINDOW_HANDLE() { return w; } //类型转换操作符， 这样就不用重载 * 和 -> 了

    private:
    WINDOW_HANDLE w;
    WindowHandle( const WindowHandle&  );
    WindowHandle & operator = ( const WindowHandle& );

};
```

# IO处理

* 操作符`<<`和`>>`重载

  * 对自定义类的对象的IO

  * 全局(友元)函数重载

  * **将全局函数虚化**

    * 全局函数是静态绑定,无法实现多态, 但是, 可以让全局函数调用虚函数, 实现虚化

      ```c++
      class CPoint2D
      {
          double x,y;
          public:
          ...
          virtual void display( ostream& out )
          { out << x << ',' << y << endl; }
      };
      
      ostream& operator << ( ostream& out , CPoint2D& a )
      {
          a.display( out );
          return out;
      }
      
      class CPoint3D: public CPoint2D
      {
          double z;
          public:
          ...
          void display( ostream& out )
          {
              CPoint2D:: display();
              out << ',' << z << endl;
      
          }
      
      };
      ```


Never treat arrays polymorphically!

不要在数组中放多态！

比如说， 你想用父类的数组存放子类的对象， 当你遍历数组时，  `arr[i]` 实际上是 `i * 数组元素大小`， 而数组元素大小是编译期决定的， 而实际对象类型可能比静态类型大， 所以会数组越界。

# 右值引用

*  有名称的、可以获取到存储地址的表达式即为左值；反之则是右值

其实 C++98/03 标准中就有引用，使用 "&" 表示。但此种引用方式有一个缺陷，即正常情况下只能操作 C++ 中的左值，无法对右值添加引用。举个例子：

```C++
int num = 10;
int &b = num; //正确int &c = 10; //错误
```

如上所示，编译器允许我们为` num `左值建立一个引用，但不可以为 10 这个右值建立引用。因此，C++98/03 标准中的引用又称为**左值引用**。

注意，虽然 C++98/03 标准不支持为右值建立非常量左值引用，但允许使用**常量左值引用引用右值**(但不能修改)。也就是说，常量左值引用既可以操作左值，也可以操作右值，例如：

```
int num = 10;const int &b = num;const int &c = 10;
```

我们知道，右值往往是没有名称的，因此要使用它只能借助引用的方式。这就产生一个问题，实际开发中我们可能需要对右值进行修改（实现移动语义时就需要），显然左值引用的方式是行不通的。

为此，C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。

需要注意的，和声明左值引用一样，右值引用也必须**立即进行初始化操作**，且**只能使用右值进行初始化**，比如：

```C++
int num = 10;
//int && a = num;  //右值引用不能初始化为左值int && a = 10;
```

和常量左值引用不同的是，右值引用还可以对右值进行修改。例如：

```C++
int && a = 10;
a = 100;
cout << a << endl;
```

程序输出结果为 100。

另外值得一提的是，C++ 语法上是支持定义常量右值引用的，例如：

```
const int&& a = 10;//编译器不会报错
```

但这种定义出来的右值引用并无实际用处。一方面，右值引用主要用于移动语义和完美转发，其中前者需要有修改右值的权限；其次，常量右值引用的作用就是引用一个不可修改的右值，这项工作完全可以交给常量左值引用完成。

* In C++ , non-const references can bind to l-values and const references can bind to l-values or r-values, but there is nothing that can bind to a non-const r-value.

```C++
class A{
    int val;
    void setVal(int x)
    { val = x ; }
    
};
A getA(){ return A(); } //返回的是个右值

int main()
{
    int a = 1;
    int &ra = a; //OK
    const A &ca = getA(); //OK
    A &aa = getA(); //ERROR
    
    
}
```

* An `r-value reference` can bind to an `r-value`
  * 将一个右值变成有内存的变量, 也就是 **可以操纵右值**

```c++
int main()
{
    int a = 1;
    int &ra = a; //OK
    const A &cRa = getA(); //OK
    A &&aa = getA(); //ok!!!
    aa.setVal(2); //OK
    
    
}
```



# 移动构造

当类中拥有指针类型的成员变量时，拷贝构造函数中需要以深拷贝（而非浅拷贝）的方式复制该指针成员。

举个例子：

```C++
#include <iostream>using namespace std;
class demo
{
    public:   
 		demo()
            :num(new int(0))
            {      
                cout<<"construct!"<<endl;   
            }    
    
    	//拷贝构造函数  
    	demo(const demo &d)
            :num(new int(*d.num))
            {      cout<<"copy construct!"<<endl;   }   
    
    	~demo()
        {      
            cout<<"class destruct!"<<endl;   
        }
    
    private:   
    	int *num;
};

demo get_demo()
{    
    return demo();
}

int main()
{    
    demo a = get_demo();    
    return 0;
}
```

> 如上所示，我们为 demo 类自定义了一个拷贝构造函数。该函数在拷贝 `d.num` 指针成员时，必须采用深拷贝的方式，即拷贝该指针成员本身的同时，还要拷贝指针指向的内存资源。否则一旦多个对象中的指针成员指向同一块堆空间，这些对象析构时就会对该空间释放多次，这是不允许的。

可以看到，程序中定义了一个可返回 demo 对象的 get_demo() 函数，用于在 main() 主函数中初始化 a 对象，其整个初始化的流程包含以下几个阶段：

1. 执行 get_demo() 函数内部的 demo() 语句，即调用 demo 类的默认构造函数生成一个匿名对象；
2. 执行 return demo() 语句，会调用拷贝构造函数复制一份之前生成的匿名对象，并将其作为 get_demo() 函数的返回值（函数体执行完毕之前，匿名对象会被析构销毁）；
3. 执行 a = get_demo() 语句，再调用一次拷贝构造函数，将之前拷贝得到的临时对象复制给 a（此行代码执行完毕，get_demo() 函数返回的对象会被析构）；
4. 程序执行结束前，会自行调用 demo 类的析构函数销毁 a。


注意，目前多数编译器都会对程序中发生的拷贝操作进行优化，因此如果我们使用 VS 2017、codeblocks 等这些编译器运行此程序时，看到的往往是优化后的输出结果：

```
construct!
class destruct!
```

而同样的程序，如果在 Linux 上使用`g++ demo.cpp -fno-elide-constructors`命令运行（其中 demo.cpp 是程序文件的名称），就可以看到完整的输出结果：

```
construct!        <-- 执行 demo()
copy construct!    <-- 执行 return demo()
class destruct!     <-- 销毁 demo() 产生的匿名对象
copy construct!    <-- 执行 a = get_demo()
class destruct!     <-- 销毁 get_demo() 返回的临时对象
class destruct!     <-- 销毁 a
```

如上所示，利用拷贝构造函数实现对 a 对象的初始化，底层实际上进行了 2 次拷贝（而且是深拷贝）操作。当然，对于仅申请少量堆空间的临时对象来说，深拷贝的执行效率依旧可以接受，但如果临时对象中的指针成员申请了大量的堆空间，那么 2 次深拷贝操作势必会影响 a 对象初始化的执行效率。

> 事实上，此问题一直存留在以 C++ 98/03 标准编写的 C++ 程序中。由于临时变量的产生、销毁以及发生的拷贝操作本身就是很隐晦的（编译器对这些过程做了专门的优化），且并不会影响程序的正确性，因此很少进入程序员的视野。

那么当类中包含指针类型的成员变量，使用其它对象来初始化同类对象时，怎样才能避免深拷贝导致的效率问题呢？C++11 标准引入了解决方案，该标准中引入了右值引用的语法，借助它可以实现移动语义。



所谓移动语义，指的就是以移动而非深拷贝的方式初始化含有指针成员的类对象。简单的理解，移动语义指的就是将其他对象（通常是临时对象）拥有的内存资源“移为已用”。

以前面程序中的 demo 类为例，该类的成员都包含一个整形的指针成员，其默认指向的是容纳一个整形变量的堆空间。当使用 get_demo() 函数返回的临时对象初始化 a 时，我们只需要将临时对象的 `num `指针直接浅拷贝给` a.num`，然后修改该临时对象中 `num` 指针的指向（通常令其指向 NULL, **防止原对象被析构**），这样就完成了` a.num` 的初始化。

> 事实上，对于程序执行过程中产生的临时对象，往往只用于传递数据（没有其它的用处），并且会很快会被销毁。因此在使用临时对象初始化新对象时，我们可以将其包含的指针成员指向的内存资源直接移给新对象所有，无需再新拷贝一份，这大大提高了初始化的执行效率。

例如，下面程序对 demo 类进行了修改：

```C++
#include <iostream>
using namespace std;

class demo
{
    public:    
    demo()
        :num(new int(0))
        {        cout<<"construct!"<<endl;    }    
    
    demo(const demo &d)
        :num(new int(*d.num))
     	{        cout<<"copy construct!"<<endl;    }    
    
    //添加移动构造函数    
    demo(demo &&d)
        :num(d.num)
        {        d.num = NULL;        cout<<"move construct!"<<endl;    }    
    
    ~demo(){        cout<<"class destruct!"<<endl;    }
    
    private:    
    int *num;

};


demo get_demo()
{    return demo();}


int main()
{    
    demo a = get_demo();    
    return 0;
}
```

可以看到，在之前 demo 类的基础上，我们又手动为其添加了一个构造函数。和其它构造函数不同，此构造函数使用右值引用形式的参数，又称为移动构造函数。并且在此构造函数中，`num `指针变量采用的是浅拷贝的复制方式，同时在函数内部重置了` d.num`，有效避免了“同一块对空间被释放多次”情况的发生。

在 Linux 系统中使用`g++ demo.cpp -o demo.exe -std=c++0x -fno-elide-constructors`命令执行此程序，输出结果为：

```c++
construct!
move construct!
class destruct!
move construct!
class destruct!
class destruct!
```



通过执行结果我们不难得知，当为 demo 类添加移动构造函数之后，使用临时对象初始化 a 对象过程中产生的 2 次拷贝操作，都转由移动构造函数完成。

我们知道，非` const` 右值引用只能操作右值，程序执行结果中产生的临时对象（例如函数返回值、lambda 表达式等）既无名称也无法获取其存储地址，所以属于右值。当类中同时包含拷贝构造函数和移动构造函数时，如果使用临时对象初始化当前类的对象，编译器会**优先调用移动构造函数**来完成此操作。只有当类中没有合适的移动构造函数时，编译器才会退而求其次，调用拷贝构造函数。

> 在实际开发中，通常在类中自定义移动构造函数的同时，会再为其自定义一个适当的拷贝构造函数，由此当用户利用右值初始化类对象时，会调用移动构造函数；使用左值（非右值）初始化类对象时，会调用拷贝构造函数。



* 如果使用左值初始化同类对象，但也想调用移动构造函数完成，有没有办法可以实现呢？

默认情况下，左值初始化同类对象只能通过拷贝构造函数完成，如果想调用移动构造函数，则必须使用右值进行初始化。C++11 标准中为了满足用户使用左值初始化同类对象时也通过移动构造函数完成的需求，新引入了 `std::move()` 函数，它可以将左值强制转换成对应的右值，由此便可以使用移动构造函数。

# 外部模板

# Lambda表达式

* A mechanism for specifying a `function object`

  | 捕获列表  | 解释                                                         |
  | --------- | ------------------------------------------------------------ |
  | []        | Capture nothing                                              |
  | [&]       | Capture any referenced variable by reference                 |
  | [=]       | Capture any referenced variable by making a copy             |
  | [=, &foo] | Capture any referenced variable by making a copy, but capture variable foo by reference |
  | [bar]     | Capture bar by making a copy; don't copy anything else       |

  

* 语法：

```c++
[capture list] (参数) mutable noexcept/throw() -> return type
{
  function body
};
```

1. [capture list]
   [ ] 方括号用于向编译器表明当前是一个 lambda 表达式，其不能被省略。在方括号内部，可以注明当前 lambda 函数的函数体中可以使用哪些“外部变量”。

> 所谓外部变量，指的是和当前 lambda 表达式位于同一作用域内的所有非static局部变量
>
> lambda可以直接使用局部static变量和全局变量

2. (参数)
   和普通函数的定义一样，lambda 匿名函数也可以接收外部传递的多个参数。和普通函数不同的是，如果不需要传递参数，可以连同 () 小括号一起省略；

3. `mutable`
   此关键字可以省略，如果使用则之前的 () 小括号将不能省略（参数个数可以为 0）。默认情况下，对于以值传递方式引入的外部变量，不允许在 lambda 表达式内部修改它们的值（可以理解为这部分变量都是 `const` 常量）。而如果想修改它们，就必须使用 mutable 关键字。

注意，对于以值传递方式引入的外部变量，lambda 表达式修改的是拷贝的那一份，并不会修改真正的外部变量；

4. `noexcept/throw()`
   可以省略，如果使用，在之前的 () 小括号将不能省略（参数个数可以为 0）。默认情况下，lambda 函数的函数体中可以抛出任何类型的异常。而标注 `noexcept `关键字，则表示函数体内不会抛出任何异常；使用 throw() 可以指定 lambda 函数内部可以抛出的异常类型。

   值得一提的是，如果 lambda 函数标有` noexcept `而函数体内抛出了异常，又或者使用 throw() 限定了异常类型而函数体内抛出了非指定类型的异常，这些异常无法使用 try-catch 捕获，会导致程序执行失败（本节后续会给出实例）。

5. `-> 返回值类型`
   指明 lambda 匿名函数的返回值类型。如果 lambda 函数体内只有一个 return 语句，或者该函数返回 void，则编译器可以自行推断出返回值类型，此情况下可以直接省略`-> 返回值类型`。

6. 函数体
   和普通函数一样，lambda 匿名函数包含的内部代码都放置在函数体中。该函数体内除了可以使用指定传递进来的参数之外，还可以使用**指定的外部变量**以及**全局范围内的所有全局变量**。

需要注意的是，**外部变量会受到以值传递还是以引用传递方式引入的影响**，而**全局变量则不会**。换句话说，在 lambda 表达式内可以使用任意一个全局变量，必要时还可以**直接修改它们的值**。

> 其中，红色标识的参数是定义 lambda 表达式时必须写的，而绿色标识的参数可以省略。

比如，如下就定义了一个最简单的 `lambda` 匿名函数：

`[]{}`

显然，此 lambda 匿名函数未引入任何外部变量（[] 内为空），也没有传递任何参数，没有指定 mutable、`noexcept` 等关键字，没有返回值和函数体。所以，这是一个没有任何功能的 lambda 匿名函数。

## [外部变量]

| 外部变量格式      | 功能                                                         |
| ----------------- | ------------------------------------------------------------ |
| []                | 空方括号表示当前 lambda 匿名函数中不导入任何外部变量。       |
| [=]               | 只有一个 = 等号，表示以值传递的方式导入所有外部变量；        |
| [&]               | 只有一个 & 符号，表示以引用传递的方式导入所有外部变量；      |
| [val1,val2,...]   | 表示以值传递的方式导入 val1、val2 等指定的外部变量，同时多个变量之间没有先后次序； |
| [&val1,&val2,...] | 表示以引用传递的方式导入 val1、val2等指定的外部变量，多个变量之间没有前后次序； |
| [val,&val2,...]   | 以上 2 种方式还可以混合使用，变量之间没有前后次序。          |
| [=,&val1,...]     | 表示除 val1 以引用传递的方式导入外，其它外部变量都以值传递的方式导入。 |
| [this]            | 表示以值传递的方式导入当前的 this 指针。                     |

>  注意，单个外部变量不允许以相同的传递方式导入多次。例如 [=，val1] 中，val1 先后被以值传递的方式导入了 2 次，这是非法的。

【例 1】lambda 匿名函数的定义和使用。

```C++
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{    
    int num[4] = {4, 2, 3, 1};    
    
    //对 a 数组中的元素进行排序    
    sort(num, num+4, [=](int x, int y) -> bool{ return x < y; } );    
    for(int n : num)
    {        
        cout << n << " ";    
    }    
    
    return 0;
}
```

程序执行结果为：

```1 2 3 4
1 2 3 4
```



程序第 9 行通过调用 sort() 函数实现了对` num` 数组中元素的升序排序，其中就用到了 lambda 匿名函数。而如果使用普通函数，需以如下代码实现：

```c++
#include <iostream>
#include <algorithm>
using namespace std;

//自定义的升序排序规则
bool sort_up(int x,int y)
{return  x < y;}

int main()
{    
    int num[4] = {4, 2, 3, 1};    
    
    //对 a 数组中的元素进行排序    
    sort(num, num+4, sort_up);    
    for(int n : num)
    {        
        cout << n << " ";    
    }    
    
    return 0;
}
```

此程序中 sort_up() 函数的功能和上一个程序中的 lambda 匿名函数完全相同。显然在类似的场景中，使用 lambda 匿名函数更有优势。

除此之外，虽然 lambda 匿名函数没有函数名称，但我们仍可以为其手动设置一个名称，比如：

```C++
#include <iostream>
using namespace std;

int main()
{    
    //display 即为 lambda 匿名函数的函数名    
    auto display = [](int a,int b) -> void{cout << a << " " << b;};  
    
    //调用 lambda 函数    
    display(10,20);    
    return 0;
}
```

程序执行结果为：

```
10 20
```



可以看到，程序中使用 `auto `关键字为 lambda 匿名函数设定了一个函数名，由此我们即可在作用域内调用该函数。

【例 2】值传递和引用传递的区别

```C++
#include <iostream>
using namespace std;
//全局变量
int all_num = 0;
int main()
{    
    //局部变量    
    int num_1 = 1;    
    int num_2 = 2;    
    int num_3 = 3;    
    cout << "lambda1:\n";    
    auto lambda1 = [=]{        
        //全局变量可以访问甚至修改       
        all_num = 10;        
        //函数体内只能使用外部变量，而无法对它们进行修改        
        cout << num_1 << " "             
            << num_2 << " "             
            << num_3 << endl;  }; 
    lambda1();    
    cout << all_num <<endl;  
    
    
    cout << "lambda2:\n";    
    auto lambda2 = [&]{        
        all_num = 100;        
        num_1 = 10;        
        num_2 = 20;        
        num_3 = 30;        
        cout << num_1 << " "             
            << num_2 << " "             
            << num_3 << endl;    
    };    
    
    lambda2();    
    cout << all_num << endl;    
    return 0;
}
```

程序执行结果为：

lambda1:

```
1 2 3
10
```


lambda2:

```
10 20 30
100
```



可以看到，在创建 lambda1 和 lambda2 匿名函数的作用域中，有 `num_1`、`num_2` 和 `num_3` 这 3 个局部变量，另外还有 `all_num` 全局变量。

其中，lambda1 匿名函数是以 [=] 值传递的方式导入的局部变量，这意味着默认情况下，此函数内部无法修改这 3 个局部变量的值，但全局变量 `all_num` 除外。相对地，lambda2 匿名函数以 [&] 引用传递的方式导入这 3 个局部变量，因此在该函数的内部就可以访问这 3 个局部变量，还可以任意修改它们。同样，也可以访问甚至修改全局变量。



当然，如果我们想在 lambda1 匿名函数的基础上修改外部变量的值，可以借助 mutable 关键字，例如：

```C++
auto lambda1 = [=]() mutable{    
    num_1 = 10;    
    num_2 = 20;    
    num_3 = 30;    
    //函数体内只能使用外部变量，而无法对它们进行修改    
    cout << num_1 << " "         
        << num_2 << " "        
        << num_3 << endl;
};
```

由此，就可以在 lambda1 匿名函数中修改外部变量的值。但需要注意的是，这里修改的仅是 `num_1`、`num_2`、`num_3` 拷贝的那一份的值，真正外部变量的值并不会发生改变。

【例 3】执行抛出异常类型

```C++
#include <iostream>
using namespace std;

int main(){    
    auto except = []()throw(int) {
        throw 10;    
    };    
    
    try {        
        except();    
    }    
    catch (int) {        
        cout << "捕获到了整形异常";    
    }    
    
    return 0;}
```

程序执行结果为：

```
捕获到了整形异常
```



可以看到，`except `匿名数组中指定函数体中可以抛出整形异常，因此当函数体中真正发生整形异常时，可以借助 `try-catch `块成功捕获并处理。

在此基础上， 再看一下反例：

```C++
#include <iostream>
using namespace std;

int main(){    
    auto except1 = []()noexcept{        
        throw 100;    };    
    
    auto except2 = []()throw(char){        
        throw 10;    
    };    
    
    try{        
        except1();        
        except2();    
    }
    catch(int){        
        cout << "捕获到了整形异常"<< endl;   
    }   
    return 0;
}
```

此程序运行会直接崩溃，原因很简单，`except1` 匿名函数指定了函数体中不发生任何异常，但函数体中却发生了整形异常；`except2 `匿名函数指定函数体可能会发生字符异常，但函数体中却发生了整形异常。由于指定异常类型和真正发生的异常类型不匹配，导致` try-catch `无法捕获，最终程序运行崩溃。

> 如果不使用 `noexcept `或者 `throw()`，则 lambda 匿名函数的函数体中允许发生任何类型的异常。

## sort

```c++
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

class Foo
{
public:
    int a;
    int b;

    Foo():a(0), b(0){}
    ~Foo(){}

    Foo(int a, int b)
    {
        this->a = a;
        this->b = b;
    }

    // 规定对象排序的算法：先按照 a 从小到大排序；如果 a 相等，则按照 b 从小到大排序
    bool operator<(const Foo &bar)
    {
        if (this->a < bar.a)
        {
            return true;
        }
        else if (this->a == bar.a)
        {
            return this->b < bar.b;
        }
        return false;
    }

    // 规定对象排序的算法：先按照 a 从大到小排序；如果 a 相等，则按照 b 从大到小排序
    bool static decrease(const Foo &foo1, const Foo &foo2)
    {
        if (foo1.a > foo2.a)
        {
            return true;
        }
        else if (foo1.a == foo2.a)
        {
            return foo1.b > foo2.b;
        }
        return false;
    }

    friend inline ostream & operator<<(ostream &out, Foo &foo)
    {
        out << foo.a << " " << foo.b << endl;
        return out;
    }
};

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    minstd_rand0 generator(seed);    // minstd_rand0 is a standard linear_congruential_engine

    vector<Foo> myVec(10, Foo());

    for (Foo &foo : myVec)           // 随机赋值
    {
        foo.a = generator() % 5;
        foo.b = generator() % 5;
        cout << foo;
    }

    sort(myVec.begin(), myVec.end()); // 排序一：默认从小到大，调用 operator <
    cout << endl << "after sorting using operator <" << endl;
    for (Foo &foo : myVec)
    {
        cout << foo;
    }

    sort(myVec.begin(), myVec.end(), Foo::decrease);  // 排序二：按照 Foo::decrease 的规则从大到小排序
    cout << endl << "after sorting using Foo::decrease()" << endl;
    for (Foo &foo : myVec)
    {
        cout << foo;
    }

    // 排序三：使用 lambda 的方式进行排序，排序的方法和 Foo::decrease 一样
    sort(myVec.begin(), myVec.end(), [](const Foo &foo1, const Foo &foo2)
    {                                                 
        
        if (foo1.a > foo2.a)
        {
            return true;
        }
        else if (foo1.a == foo2.a)
        {
            return foo1.b > foo2.b;
        }
        return false;
    }   );
    cout << endl << "after sorting using lambda" << endl;
    for (Foo &foo : myVec)
    {
        cout << foo;
    }

    system("pause");
    return 0;
}

```





# Uniform Initialization

```C++
vector<int> vec = {1,2,3};

//Compiler will translate {} as initializer_list<int>
template class vector<T>
{
    //....
    vector( initializer_list<T> list )
    {
        for( auto it = list.begin(); it != list.end(); ++it )
            push_back(*it);  
    }
    
}
```