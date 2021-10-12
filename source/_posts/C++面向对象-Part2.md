---
title: C++面向对象 Part2
tags: C++
categories: Language
date: 2021-05-26 19:04:52
---


# 多态

* 同一论域中一个元素可有多种解释
* 提高语言灵活性
* 程序设计语言
  * 一名多用  ----   函数重载
  * 类属    ----  template
  * OO程序设计  ----    虚函数



<!--more-->

# 操作符重载

* 函数重载( 见下文"函数匹配" )

  * 名同， 参数不同
  * 静态绑定
    * 歧义控制
      * 顺序
      * 更好匹配

* 操作符重载

* 动机

  操作符语义

  * `built_in`类型
  * 自定义数据类型

* 作用

  * 提高可读性
  * 提高可扩展性

## 函数匹配

 　　在大多数情况下我们都能确定某次调用应该选择哪个重载函数。然而当几个重载函数的形参数量相等，以及某些形参的类型可以由其他类型转换得来时，这项工作就不那么容易了。以下面这组函数及其调用为例：

```C++
void f();
void f(int);
void f(int, int);
void f(double, double=3.14);
f(5.6);
```

确定候选函数和可行函数

 　　函数匹配的第一步是选定本次调用对应的重载函数集，集合中的函数成为候选函数。候选函数具备两个特征：一是与被调用的函数**同名**，二是其声明在调用点**可见**。在这个例子中，有4个名为f的候选函数。

 　　第二步考察本次调用提供的实参，然后从候选函数中选出能被这组实参调用的函数，这些新选出的函数称为可行函数。可行函数也有两个特征：一是其形参数量与本次调用提供的实参**数量相等**。二是每个实参的类型与对应的形参**类型相同，或者能转换成形参的类型**。

 　　我们能根据实参的数量从候选函数中排除掉两个。不使用形参的函数和使用两个`int`形参的函数显然都不适合本次调用，这是因为我们的调用只提供了一个实参，而它们分别有0个和2个形参。

 　　使用一个`int`形参的函数和使用两个`double`形参的函数是可行的，它们都能用一个实参调用。其中最后那个函数本应该接受两个`double`值，但是因为它含有一个默认实参，所以只用一个实参也能调用它。

 　　在使用实参数量初步判别了候选函数后，接下来考察实参的类型是否与形参匹配。和一般的函数调用类似，实参与形参的含义可能是它们具有相同的类型，也可能是实参类型和形参类型满足转换规则。在上面的例子中，剩下的两个函数都是可行的：

 　　`f(int)`是可行的，因为实参类型double能转换成形参类型`int`
 　　`f(double,double)`是可行的，因为它的第二个形参提供了默认值，而第一个形参的类型正好是double，与函数使用的实参类型完全一致。

寻找最佳匹配（如果有的话）

 　　函数匹配的第三步是从可行函数中选择与本次调用最匹配的函数。在这一过程中，逐一检查函数调用提供的实参，寻找形参类型与实参类型最匹配的那个可行函数。最匹配的基本思想是，实参类型与形参类型越接近，它们匹配得越好。在我们的例子中，调用只提供了一个实参，它的类型是double。如果调用`f(int)`，实参将不得不从`double`转换成`int`。另一个可行函数`f(double,double)`则与实参精确匹配。精确匹配比需要类型转换的匹配更好。因此，编译器把f(6.5)解析成对含有两个`double`形参的函数的调用，并使用默认值填补我们未提供的第二个实参。

含有多个形参的函数匹配
 　　当实参的数量有两个或更多时，函数匹配就比较复杂了。对于前面那些名为f的函数，我们来分析如下的调用会发生什么情况：

​                          `f(42, 2.56);`

 　　选择可行函数的方法和只有一个实参的一样，编译器选择那些形参数量满足要求且实参类型和形参类型能够匹配的函数。此例中，可行函数包括`f(int, int)`和`f(double, double)`。接下来，编译器依次检查每个实参以确定哪个函数是最佳匹配。如果有且只有一个函数满足下列条件，则匹配成功：

* 该函数每个实参的匹配都不劣于其他可行函数需要的匹配
* 只有一个实参的匹配优于其他可行函数提供的匹配

 　　如果在检测了所以实参之后没有任何一个函数脱颖而出，则该调用是错误的。编译器将报告二义性调用的信息。

在上面的调用中，只考虑第一个实参时我们发现函数`f(int, int)`能精确匹配；要想匹配第二个函数，`int`类型必须转换成`double`类型。显然需要内置类型转换的匹配劣于 精确匹配，因此仅就第一个实参来说，`f(int, int)`比`f(double, double)`更好。

 　　接下来考虑第二个实参，此时`f(double, double)`是精确匹配，要想调用`f(int, int)`必须将2.56从`double`类型转换成`int`类型，因此仅就第二个实参来说，`f(double, double)`更好。

 　　编译器最终将因为这个调用具有二义性而拒绝其请求：因为每个函数函数各自在一个实参上实现了更好的匹配，从整体上无法匹配孰优孰劣。看起来我们似乎可以通过强制类型转换其中的一个实参来实参函数的匹配，但是在设计良好的系统中，不应该对实参进行强制类型转换。

实参类型转换
 　　为了确定最佳匹配，编译器将实参类型到形参类型的转换划分成几个等级，具体排序如下所示：
1.**精确匹配**，包括以下情况：
 　　实参类型和形参类型相同
 　　实参从数组类型或函数类型转换成对应的指针类型
 　　向实参添加顶层`const`或者从实参中删除顶层`const`
2.通过`const`转换实现的匹配
3.通过类型提升实现的匹配
4.通过算术类型转换或指针转换实现的匹配
5.通过类类型转换实现的匹配

需要类型提升和算术类型转换的匹配
 　　内置类型的提升和转换可能在函数匹配时产生意想不到的结果，幸运的是，在设计良好的系统中函数很少会含有下面例子类似的形参。
 　　分析函数前，我们应该知道小整型一般都会提升到`int`类型或更大的整数类型。假设有两个函数，一个接受`int`，另一个接受`short`，则只有当调用的是`short`类型的值时才会选择short版本的函数。有时候，即使实参是一个很小的整数值，也会直接将它提升成`int`类型；此时使用`short`版本反而会导致类型转换：

```C++
void ff(int);
void ff(short);
ff('a');  //char提升成int，调用ff(int)
```


 　　所有的算术类型转换的级别都一样。例如，从`int`向`unsigned int`的转换并不比`int`向`double`的转换级别高：

```c++
void mainip(long);
void mainip(float);
mainip(3.14);  //错误，二义性调用
```


 　　字面值3.14的类型是double，它既能转换成long也能转换成float。因为存在两种可能的算术类型转换，所以该调用具有二义性。

函数匹配和`const`实参
 　　如果重载函数的区别在于它们的引用类型的形参是否引用了`const`，或者指针类型的形参是否指向`const`，则当调用发生时编译器通过实参是否是常量来决定选择哪个函数：

```C++
Record lookup(Account &);    //函数的参数是Account的引用
Record lookup(const Account &);  //函数的参数是一个常量引用
const Account a;
Account b;

lookup(a);  //调用Record lookup(const Account &);
lookup(b);  //调用Record lookup(Account &);
```

 　　在第一个调用中，我们传入的是`const`对象a。因为不能把普通引用绑定到`const`对象上，所以此例中唯一可行的函数是以常量引用作为形参的那个函数，并且调用该函数与实参a精确匹配。
 　　在第二个调用中，我们传入的是非常量对象b。对于这个调用来说，两个函数都是可行的，因为我们既可以使用b初始化常量引用也可以用它初始化非常量引用。然而，用非常量对象初始化常量引用需要类型转换，接受非常量形参的版本则与b精确匹配。因此，应该选用非常量版本的函数。
 　　指针类型的形参也类似，如果两个函数的唯一区别是它的指针形参指向常量或非常量，则编译器能通过实参是否是常量决定选用哪个函数：如果实参是指向常量的指针，调用形参是`const*`的函数；如果实参是指向非常量的值，调用形参是普通指针函数。

## 操作符重载

* 可以作为成员函数重载
* 也可以作为全局函数重载
* 重载时,必须至少包含一个用户自定义类型的操作数( 否则你就会更改编译器定义的操作符语义,这是不允许的 )



* 不可重载的操作符
  + `.` `.*` `::` `?:`
*  基本原则
  * 方式
    * 类成员函数
    * **带有类参数**的全局函数
  * 遵循原有语法
    * 单目/双目
    * 优先级
    * 结合性

笨蛋写法:

```C++
class  Complex
{
    double real, imag;
    public:
    Complex()
    { real = 0 ; imag = 0; }
    Complex( double r , double i ) { real = r; imag = i; }
    Complex add( Complex &x );

};

int main()
{
    Complex a(1,2),b(2,4),c;
    c = a.add(b);


}
```

### 作为成员函数重载 

* 将运算符重载函数声明为类的成员函数时，二元运算符的参数只有一个，一元运算符不需要参数。之所以少一个参数，是因为这个参数是隐含的。

* 一般是内联函数

```C++

class Complex
{
    double real, imag;
    public:
    Complex()
    { real = 0 ; imag = 0; }
    Complex( double r , double i ) { real = r; imag = i; }
    Complex operator+ ( Complex &x)
    {
        Complex temp;
        temp.real = real + x.real;
		temp.real = imag + x.imag;

        return temp;
    }
    
    //重载一元负号，不需要参数
     complex operator -()    
    {
        return complex(-real, -image);
    }

};



int main()
{
    Complex a(1,2),b(2,4),c;
    c = a + b; //作为成员函数重载时, 左式会被转换为  c = a.operator+(b);

}
```

### 作为全局函数重载

将运算符重载函数声明为全局函数时，二元操作符就需要两个参数，一元操作符需要一个参数( 因为没有`this` ) . 而且其中必须有一个参数是自定义类型，好让编译器区分这是程序员自定义的运算符，防止程序员修改用于内置类型的运算符的性质。

```C++
class Complex
{
    double real, imag;
    public:
    Complex()
    { real = 0 ; imag = 0; }
    Complex( double r , double i ) { real = r; imag = i; }
    friend Complex operator+ ( Complex &x , Complex &y ); //友元函数



};

Complex operator+ ( Complex &x , Complex &y )
{
    Complex temp;
    temp.real = x.real + y.real;
    temp.imag = x.imag + y.imag;
    return temp;
}



int main()
{
    Complex a(1,2),b(2,4),c;
    c = a + b; //作为全局函数重载时,会被转换为 +(a,b)

}
```

#### `<<`

```c++
#include <iostream>
using namespace std;

class Point{
public:
    Point(){};
    Point (int x, int y): x(x),y(y) {};
    friend ostream &operator<<(ostream &out , const Point &a);  
private:
    int x,y;
};


ostream &operator<<(ostream &out , const Point &a){
    out << "<Point>( " << a.x << ", " << a.y << ")";
    return out;
}

int main() {
    Point a(2,4),b(5,3);
    Point c = a + b;
    cout << c << endl;    //转换为 
}
```

`<<`只能作为**全局函数**重载, 因为如果作为成员函数重载, 那么它的第一个参数必定是`this`,这显然是不合理的, `<<`的第一个参数应该是`cout`. 比如说, 对于`cout << c ` ,如果`<<`作为成员函数重载 , 那么应该会写成` c << cout `  这种形式,这是很离谱的.

`>>`同理, `<<`和>>都只能作为全局函数重载

* 注： 模板的`<<`重载， 只要加上`泛型参数`就行了

### 双目操作符重载

* 类成员函数

  * 格式

    ` <ret type> operator#( <arg> ) `

  * `this`隐含

  * 使用

    ```C++
    <class name> a, b;
    a # b;
    a.operator#(b); //等价
    ```

* 全局函数

  * 友元`friend <ret type> operator#( <arg1>, <arg2>)`

  * 格式`<ret type> operator#( <arg1>, <arg2>)`

  * 推荐所有的双目操作符都以**全局函数**重载, 因为可以实现交换律:

  * 通常只将那些不需要实现交换律的二元运算符重载为**成员函数**. 比如 赋值和复合赋值运算符`=`,`+=` , `-=` , `*=`, `/=`, `&=` \. 因为其左操作数( 成为宿主对象 ) 和右操作数( 成为参数对象 ) 的作用不相同, 在这些操作符中, 左操作数扮演的角色与右操作数不同. 左操作数代表左值, 右操作数代表右值, 操作的返回值一般为产生副作用后的宿主对象的值.

    ```C++
    class CL
    {
        int count;
        public friend CL operator+ ( int i , CL & a );
    	public friend CL operator+ ( CL & a , int i );
    };
    
    //可以实现交换律
    obj + 10;
    10 + obj;
    ```

    

  * 限制

    * `=` `()` `[]`  不能作为全局函数重载,只能作为成员函数重载
      * 原因: 
        * 对于`()` `[]`, 它们都需要先计算出左边对象的类型,再计算函数. 为了确保这件事,编译器规定这两个操作符只能作为成员函数重载( `this`总是优先被计算出 )
        * 对于`=` 由于以拷贝的方式初始化一个对象时，会调用拷贝构造函数；当给一个对象赋值时，会调用重载过的赋值运算符。因此`=`不能作为成员函数重载
    * 永远不要重载`&&`和`||` , 重载后无法实现短路

    



### 过度设计 = 错误设计

```C++
class Rational{
    public:
    	Rational(int,int);
    const Ration& operator*(const Rational &r) const;
    private:
    int n , d;
};

//operator* 的函数体
// 尝试1,这是一个栈区的构造函数,错在不能返回一个局部变量的引用或指针
return Rational( n* (r.n), d* ( r.d ));

//尝试2,这样是错的,因为对于 w = a*b*c ;  a*b的返回的对象是个匿名对象,再也找不到了,会造成内存泄漏. 也就是说,不能支持链式调用
Rational *result = new Rational( n*(r.n), d*(r.d) );
return *result; 

//尝试3,用一个类静态变量,实现支持链式调用,这样也是错的,因为
//if( (a*b) == (c*d) ) 对于这种写法来说是永真式,返回的永远是同一个
static Rational result; //设置一个类静态变量
result.n = n*(r.n);
result.d = d*(r.d);
return result;
```



可以看到,对于`const Ration& operator*(const Rational &r) const;`这种写法,实际上是错误的, 所以操作符重载的标准写法一直都是`Ration operator*(const Rational &r) `, 结尾的`const`没什么意义,所以也省略了.

### `a++` 和 `++a`

* `后缀运算符`返回的是`右值`, `前缀运算符`返回的是`左值`( 返回的就是a, prefix ++等价于a = a+1 )

为区别前置和后置运算符，C++编译器要求，需要在**后缀运算符重载函数中加参数**`int`，这个类型在此除了以示区别之外并不代表任何实际含义, 被称为哑整型参数`dummy interger parameter`；如果不加，编译器无法区分是前置++，还是后置++，导致报错。

```C++
class Counter
{
    int value;
    public:
        Counter() {value = 0 }
    
    //前置++运算符，需要引用返回，不需要参数。返回自增后的值，且返回的是一个左值 
        Counter& operator++() //++a
        {
            value++;
            return *this;
        }
    
    //后置++，不需要引用返回，需要参数区分。返回自增前的值，且返回的是一个右值
  
        Counter operator ++(int) //a++ //dummy argument
        {
            Counter tmp = *this;
            value++;
            return tmp;
        }
    
};
```

* 前缀运算符

  * 返回更改后的宿主对象( 宿主对象不能是常量 ), 这意味着我们不应该创建新对象, 而是应该更改宿主对象, 并返回宿主对象, 这意味着我们可以通过**引用返回**, C++允许级联这个运算符( `++++x` 和 `----x` ), 这意味着返回对象不能是常量, 必须是**左值**

* 后缀运算符

  * 需要哑元参数, 哑元参数的作用是创建一个唯一的前面来区分前缀和后缀运算符, 这在程序中被忽略

  * 返回对象是在更改前创建的临时对象,这意味着我们不能通过引用返回该对象. **返回的对象是常量( 右值 )** , 因为C++ 不允许级联操作, 例如 a++-- 或 a----



### `=`

*  当我们没有自己设计等号运算符的重载函数，编译器会自动生成一个**浅拷贝**的赋值运算符的重载函数。
  * **浅拷贝**：只是简单地将一个对象的内存数据赋值给另一个对象，如果这个对象成员变量引用了外部资源时（new），那么这两个对象的成员变量都指向这个空间，当这两个对象生存周期结束时，进行析构，那么就会崩溃，对同一块内存我们delete了两次
  * 逐个成员赋值( member-wise assignment )
  * 对含有对象成员的类, 该定义是递归的
* 赋值操作符重载不能被继承

对于如下代码,存在许多问题

```c++
class A
{
    int x,y;
    char *p;

    public:
        A( int i , int j , char *s )
        :x(i),y(j)
        {
            p = new char[ strlen(s) + 1 ];
            strcpy(p,s);
        }

        virtual ~A() { delete[] p; }
        
        A& operator =( A &a )
        {
            x = a.x;
            y = a.y;
            delete[] p;
            p = new char[ strlen(a.p) + 1 ];
            strcpy( p, a.p );
            return *this;
        }
};
```

* 问题一,对于:

```C++
A a,b;
b = a;
```

由于`new`会抛异常,当`new`发生错误的时候, 按理来说`b`是不变的, 但现在`b`的成员指针成为了空指针.

* 问题二, 无法支持自我赋值` s = s `, 这样会报错(  对于 `strcpy( p, a.p )`, `p` 和`a.p`都被删了 )

安全的写法是:

```C++
char *p2 = new char[ strlen(a.p) + 1  ];
strcpy(p2,a.p);
delete p;
p = p2;
return *this
```



* 赋值是一种不对称操作, 左操作数是一个接受操作副作用的佐治对象, 右操作数是一个不应该再处理过程中更改的右值对象. 必须指出, **要使用此操作符, 左操作数和右操作数必须已经存在.** 换言之, 此运算符不同于`拷贝构造函数`, 后者从现有对象创建新对象. 对于赋值运算符, 两个对象都必须存在. 我们只更改左对象, 使右对象是右对象的精确副本.
* 重载辅助运算符需要验证**宿主对象和参数对象不是同一个对象(地址不同)**. 如果对象是在堆中创建的, 这一点尤其重要. 由于在复制参数对象之前必须删除宿主对象, 如果两个对象相同, 则参数对象( 与宿主对象的物理地址相同 ) 也被删除了. 从而没有了要复制的内容.
* 赋值运算符是右向左结合的. 换言之,有 `z = y = x`, 这被解释为` z = ( y = x )` . 但是,C++要求z被看作对y的引用, 这就是返回的对象必须通过引用返回的原因.

```c++
A &A:: operator =( const A &right )
{
    if( *this != right ) //检查二者是不是同一个对象
    {
        number = right.number; // number是A的成员
    }
    return *this;
}
```









### `[]`

```C++
 class string
 {
     char *p;

     public:
        string( char *p1 )
        {
            p = new char[ strlen(p1) + 1 ];
            strcpy( p, p1 );
        }
     
     //更改器函数
     	char& operator [](int i)
        {
            return p[i];
        }

     //访问器函数
        const  char operator [](int i) const // const string * const this
        {
            return p[i];
        }

        virtual ~string(){
            delete[] p;
        }
 };


//匹配 char& operator [](int i)
string s( "aacd" );

//匹配 const char operator [](int i) const
const string cs("const");

s[2] = 'b';
cout << cs[0];

```

* 在下标操作符的重载中,由于不知道用户会调用哪个版本,所以应当**始终重载两个版本**

* 由于函数末尾`const`的作用实际上是改变参数列表( 将` string * const this ` 更改为`const string * const this`),所以编译器函数匹配时会精准匹配

#### 多维数组

```C++
class Array2D
{
public:
    class Arr1D
    {
        public:
        Array1D( int *p ) { this -> p = p; }
        int& operator[](int index) const { return p[index]; }
        private:
        int *p;
    };
    Array2D( int n1, int n2 ) { p = new int[n1 * n2] ; num1 = n1; num2 = n2; }
    virtual ~Array2D() { delete[] p; }
    Array1D operator[] ( int index ) { return p+ index * num2; } //隐式转换, 将 int* 转换为 Array1D
    const Array1D operator[] ( int index ) const {return p + index * num2; }
    private:
    int *p;
    int num1, num2;
};
```



如果构造函数只有一个参数, 那这个参数就可以用来隐式转换. 前提是构造函数前面没有`explicit`关键字 ,如果加了, 就代表这个构造函数只能显式调用, 不能隐式转换.

### `()`

`()`有三个用途: `优先级声明`, `函数调用`, `类型转换`. 后两者都可以重载

### `&`

```C++
	A* operator&()
	{
		return this;
	}

const A* operator&() const
{
    return this;
    
}
```





#### 函数调用操作符

* 实现了`函数对象`, 相当于更高级的函数指针. 函数对象可以**保存状态**

```C++
class Function
{
    double para;
    int lowerBound, upperBound;

    public:
    double operator() ( double , int, int );
};

Func f;
f( 2.4, 0 ,8 ) //函数对象
```

#### 类型转换运算符

* 减少混合计算中需要定义的操作符重载函数的数量
* 重载数值型，如`int`

```C++
class Rational
{
    public：
        Rational( int n1, int n2 )
        {
            n = n1;
            d = n2;
        }

//什么都不返回，没有返回值
//只能转换对象本身，所以不需要参数。因为只能对调用它的对象做类型转换，
//只能作为成员函数
        operator double()
        {
            return (double) (n/d);
        }

    private:
        int n,d;
};

```

### `->`

* `->`智能指针

  * `->`为二元运算符 , **重载的时候按一元操作符重载描述**, 编译器会在描述后对它重写. 

    ```C++
    A a;
    A -> f();
    a.operator->( f ); // ?????
    
    //编译器会将它改写为
    a.operator ->() ->f();
    ```

* 首先, 按照一元操作符描述, `a.operator->( f );` 会被描述为``a.operator ->()`. 实际上`a.operator ->()` 返回的是`a的指针`, 然后编译器将其改写, 再加上不重载的` -> f()`

* 实际上`a.operator ->()`可以返回一个也重载了`->`的对象, 然后`-> f()`再进行重载..... 你可以这么写, 但是非常蠢

### `new` 、`delete`

* `new`, `delete`
  * 频繁调用系统的存储管理, 影响效率( 实际上分配内存降低了系统的很大效率 )
  * 程序自身管理内存, 提高效率
  * 方法
    * 调用系统存储分配, 申请一块较大的内存
    * 针对该内存, 自己管理存储分配, 去配
    * 通过重载`new`与`delete`来实现
    * 重载的`new`和`delete`是静态成员. 由于它们肯定是静态的, 所以可加可不加`static`关键字
    * 重载的`new`和`delete`遵循类的访问控制,可继承

#### 重载`new`

* `void *operator new( size_t size, ...)`
  * 名: `operator new`
  * 返回类型: `void*`
  * 第一个参数: `size_t ( unsigned int )`
    * 系统自动计算对象的大小, 并传值给`size`
  * 其他参数: 可有可无
    * `A *p = new(...) A`, 表示传给new的其他实参
* `new`的重载可以有多个
* 如果重载了`new`, 那么通过`new`动态创建该类的对象时将不再调用内置的(预定义的)new
* 调用全局`new`:  `:: operator new`

* 定位`new`: 在栈上new出一块空间, 这样可以复用栈区地址

### 重载 `delete`

* `void operator delete( void*p, size_t size )`
  * 名: `operator delete`
  * 返回类型: `void`
  * 第一个参数: `void *`
    * 被撤销对象的地址
  * 第二个参数: 可有可无; 如果有,则必须是` size _t`类型
    * 被撤销对象的**实际**大小
* `delete`的重载只能有一个
* 如果重载了`delete`,那么通过`delete`撤销对象时将不再调用内置的(预定义的`delete`)
