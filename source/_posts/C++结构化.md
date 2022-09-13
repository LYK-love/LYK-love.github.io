---
title: C++结构化
categories: "Language"
tags: "C++"
---

Outline:

* Preface
* Prigramming
  * Data Type
  * Variable
  * ...



ref: *C++ Primer*, *Effective C++*, *More Effective C++*, *Effective Modern C++*

<!--more-->

# Preface

**G = ( VN , VT , P , Z )**

VN : `non-terminal`,非终结符号

VT:终结符号 

P:规则 

Z：target，目标

高级程序设计语言都是有理论保障的，否则不能保证得到正确结果。

# Programming 

看待程序设计的两个观点：

* The **Science** of programming: 从科学的角度。从这个角度看，许多bug是来自数据流而不是程序本身。
* The **Art** of programming:从艺术的角度。程序设计要时刻注意所处的设计环境。



Von-Neumann structure: 计算器、存储器、控制器、IO

Programming Paradigm

* Procedure:  最经典的就是 程序 = 数据结构 + 算法
* Object-Oriented: OO是对人来说的， 依然在冯诺依曼架构里。
* Functional: 典型的就是 f( g(x) )  =  g( f( x ) ),  在java程序中，如果函数有副作用，那这个式子是不成立的，而函数式就要确保函数没有副作用，这就能满足数学上的表达。这种没有副作用的场景是非常多的，比如说分布式计算就依赖于此
* Logical: 规则 + 条件 → automatic proof



## 基本数据类型 built-in datatype

* `char`,`int` , `float` , `double`

* Modifiers: long , short , signed , unsigned

  * `char` 只能用`signed`,`unsigned`修饰
  * `float`不能被修饰
  * `double`只能用`long`修饰
  * `int`可以用四种修饰符组合修饰

* 省略表示

* 操作符`sizeof`

* ANSI C++: `wcchar_t`,`bool`

* typedef

  * 为**已有**的类型定义一个同义词：

  `typedef int INT32;`

  `typedef int A[8];`
  
* `using`也是类型别名

### 类型别名

* 不是宏替换！

  ```C++
  typedef char *pstring;
  const pstring cstr = nullptr; //cstr是指向char的常量指针
  ```

  * `pstring`的基本数据类型是**指针**，（ ***不是声明符的一部分** ），const修饰的是指针。 因此`cstr`是常量指针

### 生命周期

* 自动局部变量：在函数调用时产生，在函数终止时消亡。可以显示使用`auto`（写不写都一样）来强调。 如果未显式初始化，自动局部变量会包含以前使用的**垃圾值**
* 静态局部变量： 生命周期是整个程序的生命周期。
* 全局变量：生命周期同上。 如果未显式初始化， 全局变量和静态局部变量会被初始化为默认值

## 初始化方式

* 列表初始化： 当用于内置类型的变量时，如果使用列表初始化且初始值存在丢失信息的风险，则编译器将报错（ 即无法窄化转换 ）

  ```C++
  	long double ld = 3.141325242;
  	int a{ ld }, b = { ld }; //编译错误
  	int c(ld), d = ld; //只会warning
  ```


### 复合类型

复合类型指基于其他类型定义的类型

* 一条声明语句由一个**基本数据类型**和一个**声明符列表**（ *declarator* ）组成，每个声明符命名了一个变量并指定该变量为与基本数据类型有关的某个类型

  * `*`和`&`都是类型修饰符,属于声明符的一部分,不会修饰本次定义的全部变量

    ```c++
    int *p1,p2; //p1是指针,p2是int
    ```

* 一条声明语句只能有一个基本类型

* 引用必须初始化，而且无法重新绑定

### const限定符

* `const`对象一旦创建后其值就不能再改变,因此`const`对象**必须初始化**

* `const`对象的常量特征仅仅在执行改变其值的时候才会起作用,因此`const`对象可以执行不改变内容的操作(如类型转换)

* 默认状态下,`const`对象仅在文件内有效.

  * 当多个文件内出现同名的`const`变量时, 实际等同于在不同文件中分别定义了独立的变量
  * 如果要在多个文件中共享`const`对象,则必须在变量**定义**之前添加`extern`.  即: 无论声明和定义都添加`extern`,这样只需定义一次

  ```c++
  //file1.cpp
  extern const int bufSize = fcn();
  
  //file1.h
  extern const int bufSize; //这个声明使用了extern,指明 bufSize并非本文件独有,它的定义将在别处出现
  ```

#### 初始化和对constd引用 

引用的类型必须与所引用对象的类型一致，但初始化常量引用时允许用任意表达式作初始值，只要该表达式的结果能转换成引用的类型即可。尤其，允许为一个常量引用绑定非常量的对象、字面值，甚至是个一般表达式

  * 原因：常量引用绑定到另一种类型上时，编译器会将代码改成绑定到临时量对象。而对于非常量引用，既然要使用非常量引用，就肯定想通过它改变绑定对象的值，可是引用绑定的是临时量，改变它是没有意义的，因此C++视这种行为为非法
  
    * 临时量：当编译器需要一个空间来暂存表达式的求职结果时临时创建的一个未命名的对象
    
    ```C++
        double dval = 3.14;
    
        const int &ri = dval;
    
    
    //编译器会将代码改成：
        const int tmp = dval; //tmp是临时量
        const int &r1 = tmp
    ```


#### 顶层、底层const

* **对常量的引用**（reference to const）:引用一个常量
* 常量指针（const pointer）:指针本身是一个常量
  * 意味着必须初始化
* **顶层**（ top-level ）const: 表示任意的对象是一个常量，这对任何数据结构都适用
  * 算术类型、类、指针等
* **底层**（low-level） const: 与指针、引用等复合类型的基本类型（base type）部分有关
  * 指针既可以是底层又可以是顶层
* 当执行拷贝时，顶层const不受影响，而拷入和拷出对象必须有相同的底层const之歌，或者两个对象的数据类型必须能够转换

### constexpr

+ 常量表达式：值不会改变且在编译期间就能得到计算结果的表达式

  * 字面值、用常量表达式初始化的const对象...

+ 一个对象（or 表达式）是不是`constexpr`由其数据类型和初始值共同决定

  * 初始值为`constexpr`, 数据类型为`const`

  ```C++
  const int max_files = 20;
  const int limit = max_files + 1;
  
  //以下两个不是
  int staff_size = 27; //数据类型不是const
  const int sz = get_size(); // 值直到运行期才能获取
  ```

+ 允许将变量声明为`constexpr` 以便由编译器检查其值是否为`constexpr`. 声明为`constexpr`的变量一定是一个常量，且必须用`constexpr`初始化

+ 尽管引用和指针都能定义成`constexpr`，它们的初始值却受到严格限制。一个`constexpr`指针的初始值必须`nullptr` 或`0`， 或者是存储与某个固定地址的对象

+ `constexpr`指针的`constexpr`只对指针有效，与指针所指对象无关。也就是说，`constexpr`把它所定义的对象置为了顶层`const`

## auto

* `auto`让编译器通过初始值来推断变量的类型，因此，`auto`定义的变量必须有初始值

* 使用引用实际上是使用引用的对象，因此引用类型被作为初始值时，真正参与初始化的是引用对象的值。此时`auto`的类型是**引用对象的类型**

* `auto`忽略顶层`const`,  保留底层`const`

  ```C++
  int i = 0;
  const int ci=i, &cr=ci;
  auto b = ci; //b是整数（ ci的顶层const被忽略 ）
  auto c = cr; //c是正是整数（ cr是ci的别名，后者是顶层const ）
  auto d = &i; //d是整形指针
  auto e = &ci; //e是底层const（ 对常数对象取地址是一种底层const ）
  ```

* 如果希望推断出类型是顶层`const`，需要明确指出

  ```C++
  const auto f =ci
  ```

## decltype

*  选择并返回操作数的数据类型，编译器只分析表达式得到类型，不实际计算其值
* 返回表达式的类型，包括顶层`const`和引用
  * 引用从来都作为所指对象的同义词，只有在此处是例外

## 表达式

* 组成

  * operand
  * operator
  * others

* 求值

  * 优先级

  * 结合性

  * 类型转换约定: 所有计算,规定的都是*同类型*计算. 对于混合运算,我们采取类型转换.有**默认类型转换**( Type Coercion ,  可以查文档) , 也可以强制地改变类型转换约定( Type Casting )( 这可以让你从宽的往窄的地方转, compiler会给一个`warning`,结果你自己负责 ). 我们也可以自己定义各种混合类型的计算.

    * 类型转换是按照计算顺序**逐个**进行的

    * 类型转换精度: 浮点数不能精确表达整数,会有精度损失. 因此`int`默认转成`double`(一定能得到正确答案) 而不是`float`

      

  * 求值次序

    * 取决于Compiler,不是嘴上说说的

    * token:具有独立意义的最小语法单位

    * 代码由编译器翻译为机器码,而编译器中一个重要的功能就是`Optimization`,因此

      `x = 1 + 2 + 3;` 和 `a = 1 + 2 ; x = a + 3` 性能是一样的,所以**没必要为了性能而写出很晦涩的表达式,其实性能都一样**

  * overflow:

    * 加法: 判断结果是否为`0`或者`负数`
    * 减法: 看作加法 ,但是要注意补码特征的问题,如 `min` (`10000...`)取反加一之后还是 `min` 
    * 乘法: 也要注意补码特征问题
    * 除法: 不能除以0.   `-min / -1`有问题,别的都没问题

* 种类

  注意表达式不是语句. `x=1`是表达式,加上**分号**之后`x=1;`才是**表达式语**句. `1`是表达式, `1;`是表达式语句

  * 算数
  * 关系和逻辑
  * 赋值

  * 逗号
  * 字位运算符

* 操作符可重载

  ​	增加语言灵活性. 

  ​	*不是所有操作符都能重载,比如逗号*

  ​	重载后的操作符不能与原来语义相违背,比如`&&`重载后会失去`短路效果`,所以一般不重载`&&`

* 赋值表达式

  *左值 = 右值表达式*

  * 左值: 可以出现在赋值表达式左部的*表达式*,具有存放数据的**确定**地址
  * 类型不同时,先计算右值表达式的值,再转换为左值类型,如`double d = 5/2`,右边会先计算出`2`,然后转为`2.0`

* 算术表达式

  * 增量和简练操作符
    * 前增量(前减量) `++a `     *// 前增量的结果是左值*
    * 后增量(后减量) `--a`
    * 提高编译后的执行效率

* 条件运算符表达式

  * `<exp1>?<exp2>:<exp3>`

  * 唯一的三目运算符
  * 只计算一个分量
  * 如果<exp2>和<exp2>的值类型相同,且均为左值,则该条件运算符表达式为左值表达式
  * 可嵌套
    * sign(x) `x > 0 ? 1 : x==0? 0 : -1`
    * 就近原则

* 逗号表达式

  * `<exp1>,<exp2>,<exp3>...<expn>`

  * `<expn>`的值作为该逗号表达式的值

    ```
    int a,b,c;
    	d = ( a = 1 , b = a + 2 , c = b + 3);
    cout << d << endl; // 6
    ```

  * 如`<expn>`为左值,则该逗号表达式为左值表达式

* 字位运算符表达式

  * 对整型数二进制位(bit)的操作,将整型数看作二进制序列

  * 与同一个对象异或两次,结果不变( 结合性 )

* 移位运算符表达式

## 语句

* 表达式语句

* IO语句

  * `cin`,`cout`
  * `>>`,`<<`可重载 .   现在它们变成操作符了. `cin<<x`是一个表达式

* 控制流语句

  * 顺序,选择,重复

  * switch是顺序执行的，所以写成`case  1: ... ; case 2:... ;`并没有什么意义,因为`1`和`2`只是个标记,编译器看不懂, 要是写成`case 2:... ;case  1: ... `,就会先执行`2`,再执行`1`.

    

***

* switch的实现与优化: Table_Driven.

  >
  >
  >实现一个哈希表(用枚举),这是一个指针数组。实际上value（就是每条case的地址）是不连续的。但是数组中顺序地存了指向它们的指针，所以逻辑上是连续的。比如两条case的代码地址分别是`08 04 87 f5` `08 04 87 f5`,这是不连续的,设数组起始地址为`08 04 89 e4`,它们分别是前二个元素,那么数组元素的地址分别为`08 04 89 e4` `08 04 89 e8`,我们访问数组的元素,就能连续地间接访问case的代码.

* 表驱动的思想在很多地方都有.

* `Framework`,在C++中是用`宏`完成的(因为这属于编辑`edit`的工作),后来为了简便,用IDE封装了操作

* 函数也是用表驱动的,每个函数都在表里面.注意实现取决于编译器.C的编译器不支持重载,所以`void f(int)`和`void f()`在表中是一个东西,没法作出区分; C++编译器生成的表是把函数签名(而非单纯的函数名)作为表项的(要经过一系列转换),所以上述两个函数是两个不同的表项(签名不同),也就是支持重载.

* 程序中的指令放在`EIP`里. 这是有意义的,因为无论是代码还是数据还是堆区栈区其实都是二进制的,都可以被机器执行,有些恶意代码可以跳转到栈区去,让程序崩溃.因此用了`EIP`,不在其中的指令不能执行,后来有了偷代码的攻击,于是我们把`R+X`也封了,这样小偷就不知道要偷那里的代码.

  ## 函数

* 原则

  * 定义不允许嵌套
  * 先定义后使用

* 函数的执行

  * 建立被调用函数的栈空间
  * 参数传递
    * 值传递( call by value )
    * 引用传递( call by reference): reference是别名,所以改变宽宽当然会改变陆昱宽
  * 保存调用函数的运行状态
  * 将控制转交被调函数

所有局部变量一定要初始化才能用,因为栈区不会清零

* 函数原型

  * 遵循先定义后使用原则

  * 自由安排函数定义位置

  * 语句

    

  * 只需参数类型,无需参数名称

  * 编译器检查

* 函数-重载

  * 原则
    * 名同,参数不同(个数,类型,顺序)
    * 返回值类型不作为区别重载函数的依据
  * 匹配原则
    * 严格
    * 内部转换
    * 用户定义的转换 `void f(long); void f(double)`
    * 当产生问题的时候,有可能你的程序逻辑没问题,而是你的相互使用的库有问题

## String

### String的相关操作(0) --- IO

* 读入，以空白字符或 EOF 作为结束标志

  ```
  cin >> s;
  ```

* 读入一行，以**换行符**或**指定的字符**作为结束标志，**丢弃定界符（delimiter）**

```c++
getline(cin, s);       // 以换行符为结束标志getline(cin, s, ',');  // 以 , 为结束标志
```



### String的相关操作(1) --- 长度:

* str.size() 和 str.length()，含义相同

* str.capacity() 表示分配的存储空间的大小

* str.empty() 判断 str 是否为空字符串 ""

### string 的相关操作 (2) – 获取 char

* `str[index]`
  * 0 ≤ index ≤ str.length()

  * index == str.length() 返回末尾的 \0，不应该修改！

* `str.at(int index)`
  * 0 ≤ index ＜ str.length()

* `str.front()`

* `str.back()`

### string 的相关操作 (3) – 连接

* `s1 = s2 + s3`

* `s1.append(s2)` 或 `s1 += s2`

### string 的相关操作 (4) – 其他

* 查找

  * str.find("ab"); // 从前向后的第一个 ab

  * str.find("ab", 2); // 从下标 2 开始的第一个 ab

  * str.rfind("ab"); // 从后向前的第一个 ab

  * str.rfind("ab", 2); // 从下标 2 开始从后向前第一次找到 ab

如果找不到，会返回 `string::npos`

### string 的相关操作 (5) – 与数值互转

* 子串

  * `string s2 = s.substr(pos, n); `// **与** **Java** **不同：**从 pos 开始取 n 个字符

* 比较

  * <、<=、>、>=、==、!=

  * `s1.compare(s2)` 相等时返回 0；s1 < s2 时返回 -1；s1 > s2 时返回 1

* 字符串转换为 int

  * int v = std::stoi(str);

  * 字符串转换为 long、long long、float 和 double 分别为 stol、stoll、stof 和 stod

  * ```c++
    #include <iostream>
    #include <sstream>
    
    int main()
    {
        std::string str = "668";
        int num = 0;
    
        std::istringstream ss(str);
        ss >> num;
    
        std::cout << num;
        return 0;
    }
    
    ```

  * 

  * ```C++
    #include <iostream>
    #include <stdlib.h>
    
    int main()
    {
        std::string str = "668";
        std::cout << atoi(str.c_str());
        return 0;
    }
    ```





* 数值转换为字符串
  * string s = std::to_string(42);

### string 的相关操作 (6) – split 

```C++
std::vector<std::string> split(const std::string &s,                                const char delimiter) {    std::vector<std::string> ans;    std::istringstream iss(s);    std::string token;    while (std::getline(iss, token, delimiter)) {        ans.push_back(token);    }    return ans;}
```

#### 

```c++
std::vector<std::string> split(const std::string &s, const std::string &delim) {    std::vector<std::string> ans;    int begin = 0, end = std::string::npos;    do {        int end = s.find(delim, begin);        if (end != std::string::npos) {            ans.push_back(s.substr(begin));        } else {            ans.push_back(s.substr(begin, end - begin));            begin = end + delim.length();        }    } while (end != std::string::pos);    return ans;}
```

**注意!** 

* 跟 Java 不同，C++ 的 string **几乎**是一个**字节容器**

```
string s = "中国";cout << s.length() << endl;
```

输出是4,因为里面是四个字节

* `'\0'`会特殊对待

  ```C++
  char bytes[] = {     'a', 'b', 'c', '\0’,     'd', 'e', 'f'};string s(bytes, 0, 7);cout << s.length() << endl;cout << s << endl;
  ```

   长度是3,输出是`abc`,也就是遇到`\0`会截断



### 





## 程序组织

* 逻辑结构
* 物理结构
  * 多个源文件组成
  * main唯一
* 工程文件
  * 外部文件
  * 外部变量

### namespace

### 编译预处理

* 与作用域, 类型, 接口等概念格格不入
  * 潜伏于环境
  * 穿透于作用域

#### #include

  * make interface definitions available
  * compose source text

#### #define

  * Symbolic constants    `const`
  * Open subroutines `inline`
  * Generic subroutines  `template` //这三种复用都是源代码层次的，即 可以看到细节的
  * Generic "types"  `template`
  * Renaming  `namespace`   // 以上五点，C++中已经有了替换的方法，而下面三点，C++中还没有合适的替代方法：
  * String concatenation
  * Special purpose syntax
  * General macro processing

  ```C++
# define MAX(x,y) x >= y ? x : y //不加括号的后果12 * MAX(2,3)    12 * 2 >= 3 ? 2 : 3# define MIN(x,y) ((x) < (y) ? (x) : ( y));//这样可以实现泛型，前提是类类里面重载了“<”运算符
  ```

  缺点：

  * 重复计算，因为宏不是函数
  * 没有类型检查，太宽松了

  注意：

```c++
#define ADD(x,y) {x+y;}int x=0,y=1;if( x == 0 )    ADD(x,y);  //会报错,因为花括号后面有分号else    cout << "HI";//但如果写成:#define ADD(x,y) x+y;cout << ADD(x+y) << endl; //会报错//只能写成:#define ADD(x,y)  do{ x + y ; } while(0);
```



  #### 选择性编译

* version  control

```C++
# ifndef MY_PRINT_VERSION	#define MY_PRINT_VERSION 1# endif# if MY_PRINTF_VERSION == 1void printf( char *str ){ ... }#elif MY_PRINTF_VERSION == 2int printf( char *fmt , char *args,... ){ ... }#endif
```

* Commenting out code

  #### #pragma

* Control of layout

* Informing the compiler

##  数组

* 特征

  * 相同类型
  * 连续存储

* 一维数组

  * 类型定义

  * 函数接口

    * 元素个数须通过参数**显式**给出, 不能通过`sizeof`取得. 

      传入的`len`不能保证真的是数组长度,C++是允许数组越界的

      * 字符串

```C++
void  f( int a[16] ){	int len = sizeof(a);  //这是错误的}//必须写成:void  f( int a[16] , int size)			
```

``` c++
char s1[] = "abc"; // == char s1 = {'a','b', 'c','\0'}char s2[] = {'a','b', 'c' };
```

```C++
//找到arr中的第一个负数#include<iterator>int arr[] = {0,1,2,3,4,5.-1};int *pbeg = begin(arr), *pend = end(arr);while( pbeg!= pend && *pend  >= 0)	++pbeg;
```

### 删除所有数组所有元素

```
int remove(int * arr, int target, int n){	int front = 0, back = 0, targetCnt = 0;	for(; back < n; back++){		if(arr[back] == target){			targetCnt++;		}else{			arr[front] = arr[back];			front++;		}	}	return targetCnt;}int main(int argc, char const *argv[]){	int a1[] = {1, 2, 3, 4, 0, 6, 6, 6, 7, 8, 6, 4, 5};	int l1 = 1;	l1 -= remove(a1, 6, l1);	for(int i = 0; i < l1; i++){		std::cout << a1[i] << " ";	}	std::cout << std::endl;	system("pause");	return 0;}
```



### 多维数组

* 定义
* 存储组织,C++中一定要知道数组的`layout`(内存布局). C++中的多维数组只是一维数组的不断迭代,和java中的容器等是不一样的
* 参数传递
  * 缺省第一维( C++里没有`ragged array`)

```C++
int arr[][3] = {{1} , {2,3} , {4,5,6} }cout << arr[0][1] << endl; //java中这会报错,但是C++中这是允许的,会得到一个未定义的值. 1的后面是两个未定义的值,再往后是2,3和一个未定义的值,然后是4,5,6. 也就是说真的有3 * 3 = 9 个元素. 这和java中的ragged array不同.
```

* 升/降维处理

## Struct

* 赋值 --- 同类型
* alignment. 契合硬件,提升效率
* 参数传递

```C++
struct B{    char b; //1    int a; //4    short c; //2};cout << sizeof(B) << endl; //答案是12,因为会对齐
```

## union

* 共享存储空间

  ```C++
  union C{	char b; //1	int a; //4	short c; //2};cout << sizeof(C) << endl; //答案是4
  ```

  ```C++
  union Matrix{	struct 	{		double a11, a12, a13;		double a21, a22, a23;		double a31, a32, a33;	};	double _element[3][3];};	Matrix m;	int i, j;	for (i = 0; i < 3; i++)		for (j = 0; j < 3; j++)			m._element[i][j] = (i + 1) * (j + 1);	m.a11 = 0;	m.a22 = 0;	m.a33 = 0;	for (i = 0; i < 3; i++)		for (j = 0; j < 3; j++)			cout << m._element[i][j] << endl;
  ```

  

## 指针

* 管理地址信息
* 调用代码

### 指针定义与基本操作

* 用`typedef` 定义一个指针类型

  `typedef int* Pointer;`

  `pointer p,q` // p, q均为指针变量

  注意: 指针其实不是一个类型,所以`  int *p,q `中, q不是指针

* 赋值

  `int *p = (int*) 0xKN231232`  现在没人用这个了

* 操作符

  `&`取地址

  `*`间接取内容

  注意: C++中, `NULL`是`0`; 

  * ANSI C: #define NULL( (void*) 0 )   (用 ((void\*)0)来置换NULL,这种方式有很大漏洞 )

    C++: #define NULL 0 ( 即用 0 去置换NULL )

  *空指针并不一定用与整数0同样的二进制模式表示,可由实现者采用任何选定的方式表示*

  * 现在空指针都用`nullptr`赋值

* 同类型指针比较

* 输出

  * 特例: 原因是操作符重载

    ```C++
    char *p = "ABCD";cout << p; //p指向的字符串,即"ABCD"cout << *p; // p指向的字符,即'A'//对于int*之类的就不会这样
    ```

* 例: 将某块内存清零

  ```C++
  void memset( void *pointer, unsigned size ){    char *p = (char*) pointer;//必须要类型转换,不然p是void的指针,无法进行操作    for( int k = 0 ; k < size ; k++ )        *p++ = 0;     }
  ```

  

* 常量指针与指针常量

  * **常量指针**, 即 指针指向一个常量. ( 也可以指向一个变量, 但指针不知道.所以常量指针就是一个**只读的指针**,可以**消除函数副作用** )

    ```C++
    const  int c = 0;const int *cp;int y = 1;int *q;cp = &c;q = &y;*cp = 1; // 不行,指针还没有绑定*q = 2;cp = &y; //可以,常量指针可以指向一个变量,这样的用法非常常见,不能通过指针来修改y,只能用y来修改yq = &c;// 不可以. 变量指针不能指向一个常量//如果硬要让变量指针指向常量,可以用 const_cast<int>,这种方法不太好://假设你有一个 const A a = 8; 你需要把a传入一个 // void fun( A *x) 中,如果你确保fun不会更改a的话,那可以在传参的时候写 fun( const_cast<A *>&a ).//这是在函数给定的情况下的被逼无耐之举, 有条件的话,应该把fun写成 void fun( const A *x)// 没事干不要用 const_cast<>
    ```

    * **常量替换**在编译期间发生,类似于宏替换.

      ```C++
      const int a = 5;int *p = (int *)&a; //让p指向与a相同的内存空间cout << &a << ", " << p << endl;*p = 10; // 照说a的值也应该改变，实际却没有,这就是常量折叠.cout << a << ", " << *p << endl;// 这个"常量折叠"就是在编译器进行语法分析的时候，将常量表达式计算求值，并用求得的值来替换表达式，放入常量表。可以算作一种编译优化。// 我只是改了这个地址内容,但是a还是5,// 因为编译器在优化的过程中，会把碰见的const全部以内容替换掉// （跟宏似的: #define PI 3.1415,用到PI时就用.1415代替），// 这个出现在预编译阶段；但是在运行阶段，它的内存里存的东西确实改变了!!!// 简单来说就是, 常量a的内存空间里面的内容在运行期间会被更改为10, 但是编译器在预编译阶段,已经用a的值(这个时候a的值还是5) 来替换a这个名字,类似于宏替换. 所以a这个名字的值永远是5,但它代表的内存空间的值可能被改变.输出是:0x61fe14, 0x61fe145, 10
      ```

      

    * **常量指针**,就是说指针本身是一个常量, 因此必须在定义的时候初始化.

      `<类型> * const <指针变量>`

    * 数组的最后一个元素的后一个元素的指针是空指针`nullptr`

### 指针数组

* main函数:

  ```C++
  int main( int argc, char* argv[], char* env[] ){    cout << argc << endl;    for( int i=0; i != argc ; i++ )    {        cout << argv[i] << endl;    }      cout << env << endl;      return 0;  }
  ```

  `argc`:参数个数

  `argv`:命令行参数

  `env`:环境参数

  

### 多级指针

* 编写一个函数，交换两个字符串

  ```C++
  int main( int argc, char* argv[], char* env[] ){    char *p1 = "abcd";    char *p2 = "1234";    cout << p1 << "  " << p2 << endl;    swap( &p1, &p2 );    cout << p1 << "  " << p2 << endl;    return 0;  }
  ```

  

### 动态变量

* 申请(当然是堆区)
  * `new <类型名>`
  * `new <类型名> [ <整形表达式> ]`
  * `new`和`malloc`都能申请堆区内存. 当为类的对象分配内存时,`new`会执行构造函数,而`malloc`只会申请内存,不会执行构造函数. 因此C++中尽量用`new`而不是`malloc`
  * 申请内存也有可能失败. 因此对于内存申请,一定要判断是否成功,即异常处理
* 归还
  * 操作符
    * `new` --- `delete`  会调用析构函数
    * `delete []`
    * 申请的指针,不要改变它的值,这是因为申请空间使用的是`cookie`的方式. 如果硬要改变,那得创建一个副本,然后更改副本. 总之,不能更改申请的指针