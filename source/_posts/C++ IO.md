---
title: C++ I/O
categories: "Language"
tags: "C++"
---

Outline：

* IO
  * 控制台对象
  * 文件流
  * 字符串流
* 重定向

<!--more-->

# IO

* 类的层次结构：
  * 层次结构的顶部是`ios`类，它充当虚基类。不能被实例化
  * 其他类：
    * 控制台类：`istream`,`ostream`,`iostream` 它们用于将程序连接到控制台
    * 文件流：`ifstream`,`ofstream`,`fstream` 用于将程序连接到文件
    * 字符串流：`istringstream`,`ostringstream`,`stringstream`



C++ 标准输入输出包含在头文件 <iostream> 中，使用输入输出流库需要引入此头文件
标准库中有 4 个 I/O 相关对象：

* 处理输入的 `istream`对象 `cin`
* 处理输出的 `ostream` 对象 `cout`
* 另外两个 `ostream` 对象 `cerr` 和` clog`

也可以通过引入头文件 `<cstdio>` 或 `<stdio.h>` 使用 `printf` 和 `scanf`

## 控制台对象

### istream对象： cin

`istream`类无法实例化，但是系统已经创建了此类的一个名为`cin`的对象，存储中<iostream>

* 流提取符 `>>` ,以空白字符或输入结束字符作为终止

  > 输入结束（End-Of-File，EOF）字符：在 Windows 的命令行中，用 `Ctrl + Z` 表示，在类 UNIX 系统的命令行中，用 `Ctrl (Command) + D` 表示

* 读入一个字符

  ```
  char ch ;
  cin.get(ch);
  ```

* 放回一个字符,可能会有问题

  ```
  cin.unget();
  ```

* 删除连续的空白字符:

  `cin >> std::ws;`

  

* 忽略一行中剩余的字符，**丢弃定界符（delimiter）**

  ```c++
  cin.ignore(
      std::numeric_limits<std::streamsize>::max(), 
      '\n'
  ); 
  ```

* 示例:

输入十个数字:

```C++
  int nums[10];
  for( int i = 0 ; i < 10 ; i++ )
  {
  	cin >> nums[i];
  }
```

输入未知个数的数字并求和:

```
  int sum = 0;
  while( cin >> num )
  {
  sum += num;
  }
```

* `int stoi(string)` : 把字符串转换成整数

* 用gets()输入字符数组 （方便，常用）

````C++
char ch[100];
gets(ch);
````


读入一个完整的行（从标准输入读，一直读到遇到换行符），把读到的内容存入括号中指定的字符数组里，并用空字符’\0’取代行尾的换行符’\n’。读入时不需要考虑换行符。

### ostream对象： cout、cerr和clog

`ostream`类无法实例化，但是系统已经创建了此类的三个对象：`cout`、`cerr`和`clog`，存储于<iostream>

* `cout`绑定到`cin`,意味着每次通过`cin`输入数据时，`cout`都会被刷新（清空）
* `cerr`和`clog`都被设计为向console发送错误，但`cerr`每次操作后立即刷新其内容，`clog`手机错误消息，当程序终止或显示刷新时才刷新

* 流插入符`<<`

## 文件流

### < fstream >

* 要在C++进行文件处理,需要引入头文件`<fstream>`

### < ifstream >

* 读取文件

  ```C++
  ifstream fin(file_path);
  if (!fin.is_open()) {
      cerr << "file not found" << endl;
  }
  ```


* `ifstream` 的构造函数还可以传入一个 mode 参数，包括但不限于（不同的 mode 可以用按位或运算符 | 组合在一起）：
  * `ios_base::binary` 以二进制方式读取文件
  * `ios_base::app` 在文件末尾追加
  * `ios_base::trunc `丢弃文件中原有的内容

### < ofstream >

* 写入文件

  ```C++
  ofstream fout(file_path);
  if (!fin.is_open()) {
      cerr << "file not found" << endl;
  }
  ```

* `ofstream` 的构造函数还可以传入一个 mode 参数，包括但不限于（不同的 mode 可以用按位或运算符 | 组合在一起） ：

  * `ios_base::app` 在文件末尾追加

  * `ios_base::trunc` 丢弃文件中原有的内容

### < fstream >

* 兼具 `ifstream` 和 `ofstream` 的功能

## 字符串流

* 使用 string 需要引入头文件 <string>
* 字符串流在`<sstream>`
* 跟 Java 不同，string 是**可修改内容**的

# 重定向

* `rdbuf()`

`rdbuf() `函数定义在`<ios>`头文件中，专门用于实现 C++ 输入输出流的重定向。

值得一提的是，`ios `作为 `istream `和` ostream` 类的基类，`rdbuf() `函数也被继承，因此` cin` 和 `cout` 可以直接调用该函数实现重定向。

`rdbuf()` 函数的语法格式有 2 种，分别为：

```c++
streambuf * rdbuf() const;
streambuf * rdbuf(streambuf * sb);
```

> `streambuf` 是 C++ 标准库中用于表示缓冲区的类，该类的指针对象用于代指某个具体的流缓冲区。

其中，第一种语法格式仅是返回一个指向当前流缓冲区的指针；第二种语法格式用于将 `sb` 指向的缓冲区设置为当前流的新缓冲区，并返回一个指**向旧缓冲区的对象**。

举个例子：

```C++
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    //打开 in.txt 文件，等待读取
    ifstream fin("in.txt");
    //打开 out.txt 文件，等待写入
    ofstream fout("out.txt");
    streambuf *oldcin;
    streambuf *oldcout;
    char a[100];
    //用 rdbuf() 重新定向，返回旧输入流缓冲区指针
    oldcin = cin.rdbuf(fin.rdbuf());
    //从input.txt文件读入
    cin >> a;
    //用 rdbuf() 重新定向，返回旧输出流缓冲区指针
    oldcout = cout.rdbuf(fout.rdbuf());
    //写入 out.txt
    cout << a << endl;
    //还原标准输入输出流
    cin.rdbuf(oldcin); // 恢复键盘输入
    cout.rdbuf(oldcout); //恢复屏幕输出
    //打开的文件，最终需要手动关闭
    fin.close();
    fout.close();
    return 0;
}
```



仍以前面创建好的 in.txt 文件为例，执行此程序后，控制台不会输出任何数据，而是会在该项目的目录下生成一个 out.txt 文件，其中就存有该程序的执行结果：

C++
http://c.biancheng.net/cplus/

### 命名空间

* `cin` 和 `cout` 是 C++ 标准库内置**对象**而不是关键字

* 标准库的所有标识符都在命名空间 `std` 中

```
using namespace std;  // 直接使用 cin、coutusing std::cin;  // 直接使用 cin、cout，而来自标准库的其他符号需要加上 std:: 前缀using std::cout; 
```

### 格式化

#### cout格式化输出

* 需要引入头文件 <iomanip>

示例:

* 输出不同进制

  ```
  cout << showbase      << hex << 26 << ' '      << oct << 26;// 输出：0x1a 032
  ```

* 浮点数输出指定精度

  ```
  cout << setprecision(5) << 3.1415926535;// 输出：3.1416
  ```

* 输出指定宽度,右对齐

  ```
  cout << setw(6) << right << 10;
  ```

* 输出年月日

  ```
  int year = 2021, month = 3, day = 26;cout << year << '-'      << setw(2) << setfill('0') << month << '-'      << setw(2) << setfill('0') << day;// 输出：2021-03-26
  ```

* 资源和工具

  •资源

  •https://en.cppreference.com/w/

  •https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5

  •工具

  •http://cpp.sh/

