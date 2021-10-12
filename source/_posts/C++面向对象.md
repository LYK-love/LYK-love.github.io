---
title: C++面向对象
categories: Language
tags: C++

---

# 面向对象

面向对象的优势是可以`设计`出`可复用性`和`可维护性`更强的代码. OO和PO能做的事其实是一样的,OO甚至会更慢,因为多态必然造成性能的下降.

**OO只是设计层面的思想,和运行没有关系**

1. 弱耦合性: 代码更容易复用
2. 容易维护,主要是因为继承和多态,不点的接口,多种行为,类的内部可以自由修改(只要不改接口)

<!--more-->

例子:

* PO实现Stack:

```c++
#include<iostream>
using namespace std;
#define STACK_SIZE 100
struct Stack
{
    int top;
    int buffer[STACK_SIZE];
};

bool push( Stack &s , int i )
{
    if( s.top == STACK_SIZE - 1 )
    {
        cout << "stack is overflow!" << endl;
        return false;
    }
    else
    {
        s.top++;
        s.buffer[s.top] = i;
        return true;
    }
}

bool pop( Stack &s, int &i )
{
    if( s.top == -1 )
    {
        cout << "stack is empty" << endl;
        return false;
    }
    else
    {
        i = s.buffer[s.top];
        s.top--;
        return true;
    }
}

int main()
{
    Stack st1,st2;
    st1.top = -1;
    st2.top = -1;
    int x;
    push( st1,12 );
    pop( st1,x );
    cout << x << endl;
    return 0;
}
```

* OO实现Stack

  ```c++
  #include<iostream>
  using namespace std;
  #define STACK_SIZE 100
  
  class Stack
  {
      private:
      int top;
      int buffer[STACK_SIZE];
      public:
      Stack() {top =  -1 ;}
      bool push( int i );
      bool pop( int &i );
  };
  
  bool Stack::push( int i )
  {
   if( top == STACK_SIZE - 1 )
      {
          cout << "stack is overflow!" << endl;
          return false;
      }
      else
      {
          top++;
          buffer[top] = i;
          return true;
      }
  
  }
  bool Stack::pop( int &i )
  {
      if( top == -1 )
      {
          cout << "stack is empty" << endl;
          return false;
      }
      else
      {
          i = buffer[top];
          top--;
          return true;
      }
  }
  
  int main( void )
  {
      Stack st1,st2;
      int x;
      st1.push(12);
      st1.pop(x);
      cout << x << endl;
      return 0;
  }
  ```

  

C++ 成员函数都有一个隐含的`T *const this`,指向本对象( 也就是存储的是本对象的地址 )

* `getter`和`setter` 可以在类定义时定义,这样它们就成为`隐式内联函数`

## 成员初始化表

* 构造函数的补充
* 执行
  * **先于构造函数体**
  * **按类数据成员申明次序**

```C++
Class A
{
	int x;
	const int y;
	int &z;
	public:
		A():y(1),z(x),x(0) //先于构造函数体,按类数据成员声明顺序,所以x初始化为0,z引用x. 再x赋值为10,z也变为10.
			{ x = 100 }
};
```

成员初始化表: 构造函数在分配内存的时候直接用这个值来进行初始化

`x = 100`: 这是赋值,不是初始化. 构造函数先初始化x,然后复制为100.

* 在构造函数中尽量使用成员初始化取代赋值动作
  * `const`成员, `reference`成员, `对象成员`
  * 效率高
  * 数据成员太多时,不采用本条准则
    * 降低可维护性



**例题**

```C++
class CString
{
	char *p;
	int size;
public:
CString(int x): size(x), p(new char[size]) {}

};
```

错了! 因为p初始化的时候,`size`还没有初始化! 应该把`size`声明提前

## 析构函数

* `~<类名>()`
* 对象消亡时,系统自动调用( 释放对象持有的非内存资源和不属于这个对象的内存 )
* RAII vs GC:  
  * RAII: `Resource Accuisition Is Installization` 资源获取即初始化
  * 获得了一个资源,就像对待对象一样对待它

* `public`
  * 可定义为`private`



### `Const`成员

* `const`成员

  * `const`成员变量

  ```C++
  class A
  {
  	const int x;
      public
  		A( int i)
  		:x( i )
  		{
  		;
  		}
  };
  ```

  * `const`成员的初始化放在构造函数的**初始化表**中进行
  * `static const`: 类静态常量,这个常量放在`静态区`,只能在类定义外部初始化(而不是在构造函数内, 因为它不从属于某个对象)

### 静态成员

* 问题:同一个类的不同对象如何共享变量

* 

  ```C++
  class A
  {
  	int x,y;
  	static int shared;
  	
  	public:
  		static void f();//静态成员函数,只能存取静态成员变量, 遵循类访问控制
  		void q();
  
  };
  
  int A::shared = 0; //在函数定义的时候不需要写static; 不在构造函数内初始化
  void A::f()
  {
  	;
  }
  ```

  

* 静态成员的使用

  * 通过对象使用

    `A a; a.f();`

  * 通过类使用(不像某些语言一样用`A.f()`)

    `A::F()` 

* 单例:

  ```c++
  class Singleton
  {
      protected:
          Singleton();
          Singleton(const Singleton&);
      public:
          static Singleton* instance();
          static void destroy();
      private:
          static Singleton *m_instance;
  };
  
  Singleton *Singleton::m_instance = nullptr;
  Singleton *Singleton::instance()
  {
      return m_instance == nullptr?
                              m_instance = new Singleton : m_instance;
  
  }
  void Singleton::destroy()
  {
      delete m_instance;
      m_instance = nullptr;
  }
  ```
  
  

## 友元

在使用C++进行项目开发的过程中难免会使用友元及前置声明 下面就对它们进行讲解：

在此之前，先来了解下什么是友元函数？什么是友元类？什么是友元成员函数？为什么需要友元？

友元函数是指某些虽然不是类成员的函数却能够访问类的**所有成员**。友元类同理，只是友元类与友元函数最主要的区别是：一个是将某个函数作为类的友元，一个则是将整个类（所有成员函数）都作为其他类的友元。而友元成员函数顾名思义就是将某个类的某个成员函数作为其他类的友元。一般情况下，非成员函数是无法直接从外部访问类的私有或保护部分的，但是在有些开发中又需要非成员函数从外部访问该类的私有或保护部分，而友元可以实现。

类的友元函数：

```C++
class Base{
private:
    int Num;
public:
    Base(int n = 0):Num(n){}
    void setValue(int n){Num = n;}
    void show()const{std::cout << "BaseNum:" << Num << std::endl;}
    friend void setData(Base&,int);     //声明友元函数
};

void setData(Base& s1,int n){
    s1.Num = n;   //#1 可以直接访问
}
```



如果没有 `friend void setData(Base&,int)`;该行声明语句的话，类外部函数`setData`是无法访问类私有成员`Num`的，当有该行友元声明的话，`setData`函数将可以直接访问该类的私有部分`Num`成员，如代码中#1所示，这是编译器所允许的。
友元**类**：

```C++
class Base1;    //前置声明 因为Base1类在Base类后面定义的，而Base类提到了Base1类(声明友元类的时候)
                //所以必须让编译器知道有这个类 也可以省略该步 但是在声明友元类的时候应该这样写：
friend class Base1;
class Base
{
private:
    int Num;
public:
    Base(int n = 0):Num(n){}
    void setValue(int n){Num = n;}    //设置一个自定义新值
    void clearValue(){Num = 0;}       //将值置为0
    void show()const{std::cout << "BaseNum:" << Num << std::endl;}
    friend Base1;   //将Base1整个类作为该类(Base)的友元 即Base1的所有成员函数均是Base类的友元
};

class Base1
{
public:
    void setData(Base& s1,int n){s1.Num = n;}     //与Base::setValue函数功能相同 使用了友元特性
    void clearData(Base& s1){s1.clearValue();}    //与Base::clearValue函数功能相同 但没有使用到友元特性
};
```



当需要将一个类的所有成员函数作为另一个类的友元的话，可以将这个类直接作为另一个类的友元，这样**整个类的成员函数都将是另外一个类的友员**。如上面代码所示，因此Base1类中的`setData`和`clearData`函数都是Base类的友元，都可以直接从外部对Base类的私有或保护成员进行操作。因为Base1类在Base类后面定义的，在编译friend Base1;这句代码的时候，编译器并不知道Base1是个什么东西，所以必须在将Base1类放在Base类前面定义或者在Base类前面进行前置声明，上面代码正是这么做的。`class Base1;`这行代码就是前置声明。那么对于上面代码有没有其他方法可以省略前置声明并实现同样效果呢？答案是肯定的，在这里可以省略前置声明，但是必须要将friend Base1;改为friend class Base1;这样编译器就知道将Base1是一个类，然后将它设为友元。

有人可能会问了，能不能将Base1放在Base前面定义，然后前置声明一个class Base;呢？可以，但是必须要将Base1的函数定义部分去掉。如下所示：

```C++
class Base;    //对Base的前置声明 

class Base1{
public:
    void setData(Base& s1,int n);    //在这里不能定义函数
    void clearData(Base& s1);        //同上
};

class Base{
private:
    int Num;
public:
    Base(int n = 0):Num(n){}
    void setValue(int n){Num = n;}
    void clearValue(){Num = 0;}
    void show()const{std::cout << "BaseNum:" << Num << std::endl;}
    friend Base1;    //在此之前 编译器已经知道了Base1的完整定义 所以不用再对Base1进行前置声明
};

void Base1::setData(Base& s1,int n){
    s1.Num = n;
}

void Base1::clearData(Base& s1){
    s1.clearValue();
}
```



为什么不能在类中定义该函数呢？因为如果在Base1中定义了`setData`和`clearData`函数，而函数体中对Base类的成员进行操作了，这样就必须事先知道Base**类的完整定义**(让编译器知道类内部情况)，不然编译器<u>不知道Base类中有没有这些成员</u>，所以不允许这么做。但是能不能在类中定义`setData`和`clearData`函数并在Base1类前面进行前置声明Base类解决这个问题呢？不行！因为前置声明顾名思义只是提前声明，前置声明class Base;只是让编译器知道，有这么一个Base类将在后面进行定义，但是编译器并不知道该类的内部情况，所以编译器只允许在知道该**类的完整定义**后，才让对该类成员进行操作(就是定义对这个类的成员进行操作的函数)，否则不允许。( 所以不能定义函数,只能声明函数 )
到这里，相信聪明的你应该发现，Base1类中只有函数`setData`使用了友元特性，对Base类私有成员直接访问。而`clearData`函数的实现只是调用了Base类的公有方法`clearValue`，间接访问私有成员，但是这并不涉及到友元特性。所以这个函数没有必要成为Base类的友元。如果一个类中有几十个函数，而大部分都没有使用到友元特性，将他们都设置为友元的方法（即友元类）并不推荐，而只有当大部分成员函数都需要使用友元特性的时候，使用友元类将非常方便，而只有个别的成员函数涉及到友元特性的话，推荐使用下面这个友元方法，但是这种方法需要特别注意类的定义顺序。

友元**成员函数**：

```C++
class Base;    //对Base的前置声明 

class Base1{
public:
    void setData(Base& s1,int n);    //在这里不能定义函数
    void clearData(Base& s1);        //同上
};

class Base{
private:
    int Num;
public:
    Base(int n = 0):Num(n){}
    void setValue(int n){Num = n;}
    void clearValue(){Num = 0;}
    void show()const{std::cout << "BaseNum:" << Num << std::endl;}
    friend void Base1::setData(Base& s1,int n);    //声明友元成员函数
};

void Base1::setData(Base& s1,int n){
    s1.Num = n;
}

void Base1::clearData(Base& s1){
    s1.clearValue();
}
```

在声明友元类的时候，只要不在类内部定义函数，顺序无关紧要，只要添加后面定义的类的前置声明就好了。而友元成员函数就不行，因为在使用`friend void Base1::setData(Base& s1,int n);`这句代码进行声明友元成员函数的时候，提到了Base1**类的成员函数**，既然需要将这个类的`setData`函数设为友元，那么就必须提前知道Base1类的**完整定义**(了解类的内部情况)，那么就必须将Base1类放在Base类的前面进行定义，以便当编译器编译`friend void Base1::setData(Base& s1,int n);`这行代码的时候就已经知道Base1类的内部情况了，所以定义的顺序也至关重要，而且Base1类中的函数不能在类中定义，因为定义了的话，就需要知道Base的内部情况(类完整定义)那么就需要将Base放在Base1前面定义，而Base又需要将Base1放在Base前面，这将相互矛盾，所以最友善的解决方法就是Base1的函数不在类中定义，这也是至关重要的。

* 如果**类B提到了类A的成员函数,**那么需要提前知道类A的完整定义.
* 如果**类B的成员函数提到了类A**,那么只需要前置声明A.而B的函数定义要写在A的**类定义**后面

另外，使用前置声明时，例如将Base1放在Base前面定义，并且使用前置声明`class Base;`那么在Base1类成员部分中不能实例化Base类对象，因为实例化也涉及到构造函数，需要让编译器知道Base类的完整定义，使用前置声明`class Base;`是不行的！要么Base1类中不进行实例化Base类，要么就在Base1类成员部分定义一个Base类的指针，并且在Base1类**构造函数**中对该指针使用`new Base;`方法实例化，这样是可以的，因为只定义Base类指针，不需要了解Base类内部情况，只需要知道Base是一个什么类型就好了，如前面的前置声明class Base;就让编译器知道了，Base是一个类，而`Base*`是一个Base类的指针。如下代码：



```C++
class Base;    //对Base的前置声明 

class Base1{
public:
    void setData(Base& s1,int n);    //在这里不能定义函数
    void clearData(Base& s1);        //同上
    Base1(int n = 0);
private:
//      Base temp;         //error! 需要在此之前知道Base的完整定义
        Base* pTemp;       //OK! 只需要提前知道Base是什么类型就好了 前面class Base;已经告诉编译器
};

class Base{
private:
    int Num;
public:
    Base(int n = 0):Num(n){}
    void setValue(int n){Num = n;}
    void clearValue(){Num = 0;}
    void show()const{std::cout << "BaseNum:" << Num << std::endl;}
    friend void Base1::setData(Base& s1,int n);    //声明友元成员函数
};

void Base1::setData(Base& s1,int n){
    s1.Num = n;
}

void Base1::clearData(Base& s1){
    s1.clearValue();
}

Base1::Base1(int n){
    pTemp = new Base(n);     //实例化Base类
}

在C++中还有模版友元 这将在后面讲述。有些人可能会问了，C++友元会不会与面向对象思想相悖？不会！因为友元只能由类定义，例如需要将Base1声明为Base类的友元，那么就只能在Base类中进行声明，而不能在外部强加友情，因此，尽管友元被授予从外部访问类的私有部分和保护部分的权限，但他们并不与面向对象编程思想相悖，相反，他们提高了公有接口的灵活性。

```

# 继承

* 继承机制
  * 基于**目标代码**的复用
  * 对事物进行分类
    * 派生类是基类的具体化
    * 把事物(概念)以层次结构表示出来,有利于描述和解决问题
  * 增量开发

## 单继承

```C++

class Base
{
public:
  //对于C++类中定义的任何类型的函数，名字覆盖的规则都是一样的。
  virtual void func1(int x){cout << "func1(int) in Base ..." << endl;}
  void func2(){cout << "func2() in Base ..." << endl;}
  virtual void func3() = 0;
};
 
class Derived : public Base
{
public:
  void func1() {cout << "func1() in Derived..." << endl;}
  void func2(int x) {cout << "func2(int) in Derived..." << endl;}
  void func3() {cout << "func3() in Derived..." << endl;}
  void func3(int ) {cout << "func3() in Derived..." << endl;}
};
 
int main()
{
  Derived d;
  d.func1(3); //调用失败。编译器在Derived的作用域中找到了该函数名字，但是发现调用不匹配，不能通过编译
  d.func2();
  return 0;


```



* 派生类只能通过基类的类来访问基类的`protecteed` 成员,而不能通过基类的对象来访问.

* 当你在派生类中定义一个基类函数的重载版本后,基类中所有的重载函数在子类中不可见. 这是因为**编译器在面对函数调用时，首先是在作用域范围内查找该函数名（由内之外）， 如果找到了该函数名之后，编译器便停止查找，开始检查形参与实参的匹配是否合法， 如果不合法，不能通过编译**。( 因此,编译器在子类中找到了这个函数名,但是发现调用不匹配,于是不能通过编译 ).

  解决方法: 使用`using <基类>:: <成员名称>` 来将基类中的属性或者函数成员名称引入到子类中来, 也就是让基类中的函数名字在"编译器查找子类"作用域是可见的.

* 构造函数和析构函数不能被继承



派生类友元函数可以通过派生类对象访问基类的`protected` 成员, 但是不能通过基类对象访问基类的` protected` 成员. **友元不可传递!**



### 构造函数

* 派生类对象的初始化
  * 由基类和派生类共同完成
* 构造函数的执行次序
  * 基类的构造函数
  * 派生类对象成员类的构造函数
  * 派生类的构造函数
* 析构函数的执行顺序
  * 与构造函数相反

* 基类构造函数的调用
  * 缺省执行基类默认构造函数
  * 如果要执行基类的非默认构造函数,则必须在派生类构造函数的**成员初始化表**中指出

```C++
#include<iostream>
using namespace std;

class A{
    int x;
public:
    A(){ x = 0; }
    A(int i){ x = i; }
};

class B: public A{
    int y;
public:
    B(){ y = 0; }
    B( int i ) { y = i }
    B( int i, int j ): A(i)// 注意,实际上A的构造函数会先于B的构造函数执行
    { y = j; }
};

int main()
{
    B b1;//A::A()和执行B::B()
    B b2(1);//A::A()和执行B::B(int)
    B b3(0,1); //执行A::A(int) 和 B::B(int，int)

    return 0;
}

```





### Overload（重载）

　　重载的概念最好理解，在同一个类声明范围中，定义了多个名称完全相同、参数（类型或者个数）不相同的函数，就称之为Overload（重载）。重载的特征如下：

**（1）**相同的范围（在同一个类中）；
**（2）**函数名字相同；
**（3）**参数不同；
**（4）**virtual 关键字可有可无。

### Override（覆盖）

　　覆盖的概念其实是用来实现C++多态性的，即子类重新改写父类声明为virtual的函数。Override（覆盖）的特征如下：

**（1）**不同的范围（分别位于派生类与基类）；
**（2）**函数名字相同；
**（3）**参数列表完全相同；
**（4）**返回类型也必须一样

**（5）**基类函数必须有virtual 关键字。

### Overwrite（改写）

　　改写是指派生类的函数屏蔽（或者称之为“隐藏”）了与其同名的基类函数。正是这个C++的隐藏规则使得问题的复杂性陡然增加，这里面分为两种情况讨论：

**（1）**如果派生类的函数与基类的函数同名，但是参数不同。那么此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
**（2）**如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。那么此时，基类的函数被隐藏（注意别与覆盖混淆）。(编译器在当前类作用域内找到了找到了匹配的函数,于是不再去找基类的; 如果是虚函数,那么会查虚函数表 )

### 虚函数

c++语言中，基类必须将它的两种成员函数区分开来：一种是基类希望其派生类进行覆盖的函数，另一种是基类希望派生类直接继承而不要改变的函数。对于前者，基类通常将其定义为虚函数（virtual）。当我们使用指针或者引用调用虚函数时，该调用将被动态绑定。根据引用或者指针所绑定的对象类型不同，该调用可能执行基类的版本也可能执行某个派生类的版本。在某些时候基类希望它的派生类有权访问该成员，同时禁止其他用户访问。我们用受保护的（protected）访问运算符来说明这样的成员。

基类通过在其成员函数声明语句之前加上关键字virtual使得改函数执行动态绑定。任何构造函数之外的非静态函数都可以是虚函数。关键字virtual只能出现在类内部声明语句之前而不能用于类外部的函数定义。如果基类把一个函数声明成虚函数，则该函数在派生类中隐式地也是虚函数。

#### 虚函数的访问控制

* **编译器根据对象的静态类型来决定访问控制权限，并且进行形参的默认参数的赋值**

* 虚函数是在**运行时**查虚函数表,而访问控制发生在编译期而不是运行期, 因此在派生类中更改虚函数的访问控制实际上没有意义

（1） 编译器在决定调用函数时，如果该函数是虚函数才会在运行时确定调用什么函数（动态绑定），如果不是虚函数，那么在编译阶段就已经确定了调用的函数类型（静态绑定）。
        如下面的代码，基类与派生类都声明了函数f。但是在main函数的调用中编译器调用的是静态类型对应的函数，因为f函数并不是虚函数，虽然在基类与派生类中都声明了该函数。

```C++
class Base
{
public:
    void f(int i=0) {cout << "f() in Base..." << i << endl;}
};
class Derived:public Base
{
private:
    void f(int i=1){cout << "f() in derived..." << i << endl;}
};
int main(void)
{
    Base *b = new Derived();
    b->f();
    return 0;
}
```


（2）如下,基类定义虚函数为public，派生类覆盖了该虚函数，但是将其声明为private，这样当基类的指针绑定到派生类的对象时，使用该基类指针调用该虚函数时:

```C++
class Base
{
public:
    virtual void f(int i=0) {cout << "f() in Base..." << i << endl;}
};
class Derived:public Base
{
private:
    void f(int i=1){cout << "f() in derived..." << i << endl;}
};

int main(void)
{
    Base *b = new Derived();
    b->f();
    return 0;
}
//输出为： f() in derived 0 
```

【分析】首先分析为什么输出结果是f() in derived。 编译器在看到b对f进行调用时，此时编译器根据b的静态类型（也就是Base）来决定f函数是否可访问，并且进行形参的默认参数的赋值
        由于f是虚函数，那么具体调用哪个函数是在运行时确定的，于是在运行时查找Derived的虚函数表，得到虚函数f（此时的f已经被Derived类覆盖，于是调用的就是派生类的版本。）

也就是说,在编译期间,编译器根据静态类型来决定函数的访问权限,并进行函数匹配,现在匹配到了f,且参数列表符合,则匹配成功,并缺省参数赋值( 这一步详见下文 "绝对不要重新定义继承而来的缺省参数值"), 由于该函数是虚函数,则在运行期间,编译器决定调用子类的f.

* 类型相容
  * 类,类型
  * 类型相容,赋值相容
  * 问题: a, b是什么类型时, a  = b   合法?
    * `A a; B b;` ` class B: public A  `  ` A a = b;  `
      * 对象的身份发生变化
      * 属于派生类的属性已不存在( 切片, 也可以看成是因为拷贝构造函数 )  
    * `B* pb; A* pa = p;b`  `class B: public A` 可以用父类的指针指向子类
    * `B b;  A &a=b; class B: public A`  可以用父类的引用引用子类
      *  对象的身份没有变化



* 前期绑定( Early Binding )
  * 编译时刻
  * 依据对象的静态类型
  * 效率高, 灵活性差
* 动态绑定( Late Binding )
  * 运行时刻
  * 依据对象的实际类型(动态)
  * 灵活性高,效率低( 比静态绑定多一次寻址 )
* 注重效率
  * C++默认前期绑定
  * 后期绑定需显示指出  `virtual`



* 定义

  * `virtual`

    ```C++
     class A
     {
     	...
     public:
     	virtual void f();
     };
    ```

    * 动态绑定
      * 根据实际引用和指向的对象类型
    * 方法重定义

* 如基类中被定义为虚成员函数, 则派生类中对其冲定义的成员函数均为虚函数.
* 限制
  * 类的成员函数才可以是虚函数

#### 虚函数表

基类对象包含一个虚表指针，指向基类的虚函数表

派生类对象也将包含一个虚表指针，指向派生类虚函数表

如果派生类重写了基类的虚方法，该派生类虚函数表将保存重写的虚函数的(入口)地址，而不是基类的虚函数地址

如果基类中的虚方法没有在派生类中重写，那么派生类将继承基类中的虚方法，而且派生类中虚函数表将保存基类中未被重写的虚函数的地址，但如果派生类中定义了新的虚方法，则该虚函数的地址也将被添加到派生类虚函数表中

#### final，override

**1. override 重载**

　　当你在父类中使用了虚函数时候，你可能需要在某个子类中对这个虚函数进行重写，以下方法都可以：

```C++
class A
{
    virtual void foo();
}
class B :public A
{
    void foo(); //OK
    void foo() override; //OK
}
```

　　如果不使用override，当你手一抖，将**foo()**写成了**f00()**会怎么样呢？结果是编译器并不会报错，因为它并不知道你的目的是重写虚函数，而是把它当成了新的函数。如果这个虚函数很重要的话，那就会对整个程序不利。

　　所以，override的作用就出来了，它指定了子类的这个虚函数是重写的父类的，如果你名字不小心打错了的话，编译器是不会编译通过的：

```c++
class A
{
    virtual void foo();
};
class B :A
{
    virtual void f00(); //OK
    virtual void f0o()override; //Error 
};
```



* 显然, `override` 不能用来修饰非虚函数

**2.final**

　* **当不希望某个类被继承，或不希望某个虚函数被重写**，可以在类名和虚函数后添加final关键字，添加final关键字后被继承或重写，编译器会报错。

* `final`用于类或虚函数, 不能用来修饰非虚函数

例子如下：

```C++
class Base
{
    virtual void foo();
};
 
class A : Base
{
    void foo() final; // foo 被override并且是最后一个override，在其子类中不可以重写
    void bar() final; // Error: 父类中没有 bar虚函数可以被重写或final
};

class B final : A // 指明B是不可以被继承的
{
    void foo() override; // Error: 在A中已经被final了
};
 
class C : B // Error: B is final
{
};
```



PPT例子:

```C++
struct B
{
    virtual void f1(int) const;
    virtual void f2();
    void f3();
    virtual void f5(int) final;
};

struct D: B //默认的继承访问权限。struct是public继承的
{
    void f1(int) const override; //正确，f1与基类中的f1匹配
    void f2(int) override;//错误： B没有形如f2（int）的函数
    void f3() override;//错误， f3不是虚函数
    void f4() override;//错误： B没有名为f4的函数
    void f5(int);//错误， B已经将f5声明成final；
}
```





#### 纯虚函数和抽象类

* 纯虚函数
  * 声明时在函数原型后面加上`= 0`
  * 往往只给出函数声明,不给出实现
  * **往往**的意思是，对于`纯虚析构函数`,我们是要提供实现的
* 抽象类
  * 至少包含一个纯虚函数
  * 不能用于创建对象
  * 为派生类提供框架,派生类提供抽象基类的所有成员函数的实现
* 虚析构函数
* 确定`public inheritance`,是真正意义的" is a " 关系
* 不要定义与继承而来的非虚成员函数同名的成员函数



* 明智地运用`private Inheritance`  见下文"私有继承"

  * Implemented-in-term-of
    * 需要使用基类的protected成员,或重载虚函数
    * 不希望一个基类被客户使用
  * 在设计层面无意义,只用于**实现**层面. 

* **绝对不要重新定义继承而来的缺省参数值**( 写了也没用 )

  * 静态绑定
  * 效率
  * 话说这个机制是历史遗留问题, 给我们的启示是:尽量少用缺省参数值

  缺省参数值: 编译的时候,编译器如果看到这个函数没有参数,但有缺省参数值,当场就会把缺省参数值绑定到形参. 由于对象的`vtable`只会存虚函数的入口地址(不存缺省参数的原因是很少用,效率也差). 于是, 编译器会在编译期把缺省参数静态绑定上去. 因此,就会发生: 指向子类的父类引用调用了子类的虚函数(这是我们所期望的),但是其缺省参数值**居然是父类的**的情况.

  ```C++
  #include<iostream>
  using namespace std;
  
  class A 
  {
  public:
      virtual void f(int x = 0)
      {
          cout << "class A: " << x << endl;
      }
  };
  
  class B:  public A
  {
      private:
      virtual void f(int x = 1)
      {
          cout << "class B: " << x << endl;
      }
  };
  
  class C : public A
  {
  private:
      virtual void f(int x)
      {
          cout << "class C: " << x << endl;
      }
  };
  
  int main()
  {
      A* p_a;
      B b;
      p_a = &b;
      p_a->f();
  
      A* p_a1;
      C c;
      p_a1 = &c;
      p_a1->f(); //先找父类，再绑定缺省参数。 在运行期，再选中子类的函数。
      return 0;
  }
  
  //输出:
  class B: 0
  class C: 0
  
  ```

  

  

#### 三种函数

* 纯虚函数

  只有函数接口会被继承

  * 子类必须继承函数接口
  * 子类必须提供实现代码

* 一般虚函数

  函数的接口及缺省实现代码

  * 子类**必须**继承函数接口
  * **可以**继承缺省实现代码

* 非虚函数

  函数的接口和其实现代码会被继承

  * **必须**同时继承接口和实现代码



##### 纯虚析构函数

[原文](https://blog.csdn.net/yby4769250/article/details/7294733)

纯虚析构函数和普通纯虚函数的区别在于，**纯虚析构函数需要提供函数的实现**，而一般纯虚函数不能有实现，这样的原因在于，纯虚析构函数最终需要被调用，以析构基类对象，虽然是抽象类没有实体。而如果不提供该析构函数的实现，将使得在析构过程中，析构无法完成而导致析构异常的问题

```C++
Class A
{

  public:

  A(){}

  virtual ~A()=0;

}

A::~A(){} //提供了纯虚析构函数的实现

ClassB:public A
{

}


A *p =new B();

*Delete p;
```



`Delete p;`通过父类指针去析构子类对象, 分三种情况:

1. 父类如**A**的析构函数不是虚函数，这种情况下，将只会调用**A**的析构函数而不会调用子类的析构函数，前面的文章中有提到过，非虚函数是通过类型来寻址的，这样的析构将会导致析构畸形
2. 父类如**A**的析构函数是普通的虚函数，这种情况下，会很正常，从子类一直析构到基类，最后完成析构
3. 父类如**A**的析构函数是纯虚析构函数，如本文所提，正是重点，在这种情况之下，由于析构函数首先是虚函数，所以会按**2**的方法从子类一直析构到父类，但是，又由于父类的析构函数是纯虚函数，没有实现体，所以，当析构到父类时，由于没有实现体，所以导致父类无法析构，最终也导致了析构畸形，因此，特殊的地方就在于这里，纯虚析构函数需要提供一个实现体，以完成对象的析构

### 私有继承

在声明一个派生类时将基类的继承方式指定为private的，称为私有继承，用私有继承方式建立的派生类称为私有派生类(private derived class )， 其基类称为私有基类(private base class )。

私有基类的公用成员和保护成员在派生类中的访问属性相当于派生类中的私有成员，即派生类的成员函数能访问它们，而在派生类外不能访问它们。私有基类的私有成员在派生类中成为不可访问的成员，只有基类的成员函数可以引用它们。一个基类成员在基类中的访问属性和在派生类中的访问属性可能是不同的。私有基类的成员在私有派生类中的访问属性见表

* 虽然在派生类外不能通过派生类对象调用私有基类的公用成员函数，但在派生类外可以通过派生类的公共成员函数调用私有基类的公用成员函数(此时它是派生类中的私有成员函数，可以被派生类的任何成员函数调用)。这就是一种**委托**

| 私有基类中的成员 | 在私有派生类中的访问属性 |
| ---------------- | ------------------------ |
| 私有成员         | 不可访问                 |
| 公用成员         | 私有                     |
| 保护成员         | 私有                     |

* 私有继承类和基类的**接口不一样**,它们不是`is-a`关系,而是`has-a`关系
* 因此,私有继承不存在类型兼容和类型转换, 也就是不能用父类指向子类. 

```C++
class CHumanBeing
{
    ...
};
class CStudent: private CHumanBeing
{
    ...
};

CHumanBeing a; CStudent b;
eat(a);
eat(b); //Error
```

### 多继承

* 继承方式及访问控制的规定同单继承
* 派生类拥有所有基类的所有成员
* 多继承定义的时候是一个权限名对应一个基类，`class derived:public base1, public base2`.  不能是`class derived:public base1,base2`
* 基类的声明次序决定：
  * 对基类构造函数/析构函数的调用次序
  * 对基类数据成员的存储安排
* 名冲突
  * <基类名>：：<基类名称名>
* 虚基类
  * 如果直接基类有公共的基类，则该公共基类中的成员变量在多继承的派生类中有多个副本

```C++
class A
{
	int x;
	...
};
class B: A;
class C: A;
Class D: B,C;
```

* 类D拥有两个成员`B:: x` 和`C:: x`

  * D调用B和C, B调用A, C调用A. 所以A的构造函数会被调用两次. 实际上A的成员会被拷贝给B和C, 拷贝到不同子类的基类成员之间是**无关联**的

* 虚基类

  * 合并

    ```C++
    class A;
    Class B: virtual public A;
    class C: virtual public A;
    class D: B,C;
    ```

  

  1. 设定为虚基类后，系统知道base1和base2都是由base派生出的，所以它就统一先构造base，调用base的构造函数。
  2. 再按照顺序调用base1和base2的构造函数，只不过在此时，大家在构造时操作的都是同一个成员

* 注意

  * 虚基类的构造函数由最新派生出的类的构造函数调用
  * **虚基类的构造函数优先非虚基类的构造函数执行**
    * 解释: 设B,C虚继承A, D继承B,C, 则D的构造函数会先执行虚基类A的构造函数,再执行B和C的构造函数; 而在普通多继承中,D会调用B,C,它们再分别调用A. 二者是不同的.
  * 多继承形式下析构函数的执行顺序和构造函数的执行顺序相反。

#### 多继承下的构造函数

多继承形式下的构造函数和单继承形式基本相同，只是要在派生类的构造函数中调用多个基类的构造函数。以上面的 A、B、C、D 类为例，D 类构造函数的写法为：

```c++
D(形参列表): A(实参列表), B(实参列表), C(实参列表){
  //其他操作
}
```



基类构造函数的调用顺序和和它们在派生类构造函数中出现的顺序无关，而是**和声明派生类时基类出现的顺序相同**。仍然以上面的 A、B、C、D 类为例，即使将 D 类构造函数写作下面的形式：

```c++
D(形参列表): B(实参列表), C(实参列表), A(实参列表){
  //其他操作
}

```



是先调用 A 类的构造函数，再调用 B 类构造函数，最后调用 C 类构造函数。

从运行结果中还可以发现，

#### 命名冲突

当两个或多个基类中有同名的成员时，如果直接访问该成员，就会产生命名冲突，编译器不知道使用哪个基类的成员。这个时候需要在成员名字前面加上类名和域解析符`::`，以显式地指明到底使用哪个类的成员，消除二义性。

修改上面的代码，为 `BaseA` 和 `BaseB` 类添加 show() 函数，并将 Derived 类的 show() 函数更名为 display()：

```c++
#include <iostream>
using namespace std;
//基类
class BaseA
{
 public:    
 BaseA(int a, int b);    
 ~BaseA();public:    
 void show();
 protected:    
 int m_a;    
    int m_b;
};

BaseA::BaseA(int a, int b): m_a(a), m_b(b)
{    
    cout<<"BaseA constructor"<<endl;
}
BaseA::~BaseA()
{    
    cout<<"BaseA destructor"<<endl;
}
void BaseA::show()
{    
    cout<<"m_a = "<<m_a<<endl;    
    cout<<"m_b = "<<m_b<<endl;
}//基类
class BaseB
{
    public:    
    BaseB(int c, int d);    
    ~BaseB();    
    void show();
    protected:    
    int m_c;    
    int m_d;};
BaseB::BaseB(int c, int d): m_c(c), m_d(d)
{    
    cout<<"BaseB constructor"<<endl;
}
BaseB::~BaseB()
{    
    cout<<"BaseB destructor"<<endl;
}
void BaseB::show()
{    
    cout<<"m_c = "<<m_c<<endl;    
    cout<<"m_d = "<<m_d<<endl;
}//派生类
class Derived: public BaseA, public BaseB
{
 public:    
 Derived(int a, int b, int c, int d, int e);    ~Derived();
 public:    
 void display();
 private:    
 int m_e;
};

Derived::Derived(int a, int b, int c, int d, int e): BaseA(a, b), BaseB(c, d), m_e(e)
{    
    cout<<"Derived constructor"<<endl;
}
Derived::~Derived()
{    
    cout<<"Derived destructor"<<endl;
}
void Derived::display()
{    
    BaseA::show();  //调用BaseA类的show()函数
    BaseB::show();  //调用BaseB类的show()函数
    cout<<"m_e = "<<m_e<<endl;
}
    
    int main()
    {    
        Derived obj(1, 2, 3, 4, 5);    
        obj.display();    
        return 0;
    }
```

显式地指明了要调用哪个基类的 show() 函数。

