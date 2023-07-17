---
title: C++ 泛型算法
categories: Language
tags: C++
date: 2021-06-20 12:00:00
---





Outline：

* 概述
* 泛型算法概览
* 定制操作
* 再探迭代器
* 泛型算法结构
* 特定容器算法

<!--more-->

# 概述

* 头文件`<algorithm>`, `<numeric>`
* 泛型算法： 对不同类型容器的通用算法
* 大多数情况下，泛型算法操作迭代器，而不是直接操作容器
  * 泛型算法不依赖容器，但依赖于元素类型的操作，比如运算符重载

# 算法概览

## 只读算法

* `find`
* `accumulate`
  * 必须有合适的`+`运算符
    * `string sum = accumulate(v.cbegin(), v.cend(), string(""));`
    * `string sum = accumulate(v.cbegin(), v.cend(), "");`是错误的，因为`const char*`没有`+`运算符
* `equal`
  * 必须有合适的`==`运算符

## 写容器元素的算法

* `fill`接受一对迭代器表示范围 

  * `fill(vec.cbegin(), vec.cend() + vec.size()/2, 10 );`

* ``fill_n( dest, n , val )` 接受一个迭代器来指出单独的目的位置

* `copy( begin, end, dest )`

* `unique(begin, end)`

  * 重排输入范围，使得不重复的元素出现在容器的开始部分

  * 返回指向不重复区域之后一个位置的迭代器，

    * 若没有不重复区域，则返回尾后迭代器

    * 与`erase`搭配使用，删除重复的元素

  ```c++
  //按字典序排序words并删除重复单词
  
  void elimDups( vector<string> &words )
  {
      sort( words.begin(), words.end() );
  
      auto end_unique = unique( words.begin(),words.end() );
      words.erase( end_unique ,  words.end());
  }
  
  ```

  测试：

  ```c++
  int main()
  {
      istream_iterator<string> in_iter(cin), eof;
      ostream_iterator<string>out_iter( cout, " " );
      vector<string>vec(in_iter, eof);
      elimDups( vec );
      
      copy(vec.begin(), vec.end(), out_iter);
    
  }
  ```

  ```
  aaa bbb ddd ccc aaa //输入
  ```

  ```
  aaa bbb ccc ddd //输出
  ```

  

* 算法假定：

  * 很多算法操作两个序列， 它们接受接受第三个的迭代器来表示第二个序列的目标位置，这些算法都假定， 第二个序列至少与第一个序列一样长
    * 如`equal`， `copy`
      * 返回（递增后的）目的位置迭代器

*  一些算法接受一个单独的迭代器来指出一个单独的目的位置，这类算法不检查写操作，因此越界访问是`undefined behavior`

  * 比如，不能在空容器上调用`fill_n`
    * 可以用` fill_n(back_inserter(),10,0)`,每次通过此迭代器赋值时，赋值运算符被重载为调用`push_back`,这就不用担心越界访问

  

# 定制操作

## 谓词

* 定义： 返回值为`bool`的可调用对象
  * 一元谓词： 只接受一个参数
  * 二元谓词： 接受两个参数
* 可调用对象：可以对其使用调用运算符的对象或表达式
  * 函数和函数指针
  * 重载了函数调用运算符的类
  * lambda表达式
* 算法对接受的谓词有要求，为了绕过这个限制，可以使用lambda表达式
  * `find_if()`  接受一个一元谓词，但有时该谓词函数需要不止一个参数

## lambda的应用

* `for_each(begin,end, callable)`：接受一个可调用对象


# 再探迭代器

除了标准迭代器外，还有以下几种迭代器，头文件：`<iterator>`

* `insert iterator`
* `stream iterator`
* `reverse iterator`
* `move iterator`



## Insert Iterator

*  迭代器适配器, 接受一个容器，生成一个迭代器
* 调用容器操作向给定容器的指定位置插入一个元素

| 操作                  | 解释                                                         |
| --------------------- | ------------------------------------------------------------ |
| `it = t`              | 在`it` 指定的当前位置插入`t`. 假定 `c`是`it`绑定的容器，依赖于插入迭代器的不同种类， 此赋值会分别调用 `push_back(t)`，`push_front(t)`，`insert(t,p)`， 其中`p`为传递给`inserter`的迭代器位置 |
| `*it`, `++it`, `it++` | 空操作。 都返回`it`                                          |



| 迭代器适配器            | 功能                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `back_insert_iterator`  | 创建一个使用`push_back`的迭代器（这意味着不会发生越界访问，容器大小永远足够），前提是提供有 push_back() 成员方法的容器（包括 vector、deque 和 list）。 |
| `front_insert_iterator` | 创建一个使用`push_front`的迭代器，前提是提供有 push_front() 成员方法的容器（包括 list、deque 和 forward_list）。 |
| `insert_iterator`       | 在容器的指定位置之前插入新元素，前提是该容器必须提供有 insert() 成员方法。 |

 * 当调用`inserter(c, iter)`时，得到一个迭代器，接下来使用它时，会将元素插入到`iter`原来所指向的元素**之前**的位置， 即，如果`it`是由`inserter`生成的迭代器，则：

   ```c++
   *it = val;
   ```

   效果与下面的代码一样：

   ```c++
   it = c.inserter(it,val);//it指向新加入的元素
   ++it; //递增it使它指向原来的元素
   ```

* `front_inserter` 生成的迭代器与`inserter`生成的完全不同。当调用` front_inserter`时，元素总是插入到容器第一个元素之前：

  ```c++
      list<int> lst = {1,2,3,4};
      list<int> lst2, lst3 ; // empty list
      copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); //拷贝完成后， lst2包含4,3,2,1
      copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));//拷贝完成后， lst3包含1,2,3,4
  ```

  当调用`push_front(c)`时，得到一个插入迭代器，接下来会调用`push_front`

## iostream Insrator

`itstream`不是容器，但`STL`定义了可以用于这些IO类型对象的迭代器。`istream_iterator`读取输入流，` ostream_iterator`向一个输出流写数据。 这些迭代其将它们对应的流当作一个特定类型的元素序列来处理。 通过使用流迭代器，我们可以使用泛型算法从流对象读取数据以及向其写入数据。

* 可以为任何定义了`>>`和`<<`运算符的类型创建`istream_iterator`和`ostream_iterator`

### istream_iterator操作

当创建流迭代器时，必须指定迭代器将要读写的对象类型。 一个`istream_iterator`使用`>>`来读取流。 因此， `istream_iterator`**要读取的类型必须定义了输入运算符**。 

* 当创建一个`istream_iterator`时， 我们可以将它绑定到一个流。 当然，我们还可以默认初始化迭代器，这样就创建了一个**尾后迭代器**

```c++
    vector<int> vec;
    istream_iterator<int> in_iter(cin); //从cin读取int
    istream_iterator<int> eof; //istream尾后迭代器
    while( in_iter != eof )
    {
        vec.push_back(*in_iter++); //先后缀递增，返回迭代器的旧值。 再对旧值接引用，得到从流读取的前一个值，即原来指向的值
    }
```

该程序可以改写为：

```c++
    istream_iterator<int> in_iter(cin) ,  eof; //从cin读取int
    vector<int>  vec(in_iter, eof);
```

* 可以用一对表示元素范围的迭代器构造`vec`
* 这两个迭代器是`istream_iterator` , 这意味着元素范围是通过从关联的流中读取数据获得的， 这个构造函数从`cin`中读取数据，直至遇到文件尾或者遇到一个不是`int`的数据位置。 

####  使用算法操作流迭代器

  算法使用迭代器，而流迭代器至少支持某些迭代器操作，因此至少可以用某些算法来操作流迭代器

```c++
#include<numeric>

istream_iterator<int> in(cin), eof;
cout << accumulate(in, eof, 0) << endl;
```

#### istream_iterator允许使用懒惰求值

* 当`istream_iterator`绑定到一个流时，标准库并不保证迭代器立即从流中读取数据。 具体实现可以直到使用迭代器时才真正读取。

### ostream_iterator

可以对任何具有`<<`运算符的类型定义`ostream_iterator`.  当创建`ostream_iterator`时，我们可以提供（可选的）第二个参数。它是一个**C风格字符串**， 在输出每个元素后都会打印此字符串

* 必须将`ostream_iterator`绑定带一个指定的流。 不允许空的或者表示尾后位置的`ostream_iterator`

| 操作                             | 解释                                                         |
| -------------------------------- | ------------------------------------------------------------ |
| `ostream_iterator<T> out(os);`   | `out` 将类型为 `T`的值写入输出流`os`中                       |
| `ostream_iterator<T> out(os,d);` | `out` 将类型为 `T`的值写入输出流`os`中，每个值后面都输出一个`d`, `d`指向一个空字符结尾的字符数组 |
| `out = val`                      | 用`<<`运算符将`val` 写入到`out`所绑定的`ostream`中， `val`的类型必须与`out`可写的类型兼容（ 即为`T` ） |
| `*out` ,`++out`, `out++`         | 这些运算符存在，但不对`out`做任何改变。 均返回`out`          |

* 使用`ostream_iterator`输出值的序列

  ```c++
  int  main()
  {
      istream_iterator<int> in_iter(cin), eof;
      vector<int>vec(in_iter, eof);
      
      ostream_iterator<int>out_iter( cout, " " );//使用ostream_iterator输出值的序列
      for( auto e: vec )
      {
          *out_iter++ = e;
      }
      cout << endl;
      return 0;
  }
  ```

  事实上，`*`和`++`不对`ostream_iterator`对象做任何事，因此可以写成：

  ```c++
  for( auto e: vec )
      {
          out_iter = e;
      }
  ```

  但推荐前者，因为易于理解



* 当然，还可以通过`copy`来打印`vector`中的元素：

  ```c++
  copy(vec.begin(), vec.end(), out_iter);
  ```

  ##  


## reverse_iterator

* 与普通迭代器一样，只是是反向的

  * 除了`forward_list`之外，所有容器都支持反向迭代器

* 可以让算法透明地向前或向后处理容器：

  ```c++
  sort(vec.rbigin(). vec.rend());
  ```

* 除了流迭代器，其余迭代器都支持递减运算

* 反向迭代器的`base（）`可以返回对应的正向迭代器

  * 返回的正向迭代器的位置在原反向迭代器的后一位（按正序排列）

* 反向迭代器的删除：

  ```c++
  for( auto: rit: vec,begin(); vec.end();  )
  {
  	if( *tir == XX )
  		rit = decltype(rit)( erase( ++rit.base() ) );
      else{
          rit++;
      }
  }
  ```

  * `erase()`只接受正向迭代器，因此要`base（）`转换

  * 注意到`decltype(rit)`将正向迭代器转为反向迭代器时，会将位置往前移一位（与之前后移一位对应），避免了手动`++rit`

* 例子：打印最后一个逗号后的字符串

  ```c++
      string line("HELLO, MIKE!");
      auto rcomma = find( line.crbegin(), line.crend(), ',' );
      cout << string( line.crbegin(), rcomma ) << endl;
  ```

  输出为：

  ```
  !EKIM 
  ```

  想要正确输出`MIKE!`，要使用正向迭代器：

  ```c++
  cout << string(  rcomma.base(), line.cend() ) << endl;
  ```

  

# 泛型算法结构



* 任何算法都对其迭代器提供的操作有要求，这里将迭代器分为五类：

  | name           | 解释                                 | 例子                             |
  | -------------- | ------------------------------------ | -------------------------------- |
  | 输入迭代器     | 只读，不写；单遍扫描，只能递增       | `istream_iterator`               |
  | 输出迭代器     | 只写，不读; 单遍扫描，只能递增       | `ostream_iterator`               |
  | 前向迭代器     | 可读写，多遍扫描，只能递增           | `forward_list`上的迭代器         |
  | 双向迭代器     | 可读写，多遍扫描，可递增递减         | 很多                             |
  | 随机访问迭代器 | 可读写，多遍扫描，支持全部迭代器运算 | `vector`,`string`, `deque` . etc |

  

### 算法形参模式

大多数算法具有如下参数规范之一：

```python
alg(beg,end,other args);
alg(beg,end,dest, other args);
alg(beg,end,beg2,other args);
alg(beg,end,beg2,end2,other args);
```

* `dest`: 算法可以写入的目的位置的迭代器
  * 算法假定：目标空间足够容纳写入的数据
  * `dest`经常被绑定到一个插入迭代器或`ostream_iterator`

## 算法命名规范

### 一些算法使用重载形式传递一个谓词

```c++
unique(beg,end);
unique(beg,end,comp); // 使用comp比较元素
```

### _if版本的算法

接受一个元素值的算法通常有一个不同名（因此非重载）的`_if`版本，它接受一个谓词来代替元素值：

```c++
find( beg, end, val );
find_if( beg, end, pred ); //查找使得pred返回非零值的元素
```

### 区分拷贝元素和不拷贝的版本

默认情况下，重排元素的算法将重排后的元素写回给定的输入序列中。 这些算法还提供另一个版本，将元素写入一个指定的输出目的位置， 这些算法都在名字后面附加一个`_copy`

```c++
reverse(beg,end);// 翻转输入序列中元素的顺序
reverse(cbeg,cend,dest);// 将元素按逆序拷贝到dest
```

```c++
replace( lst.begin(), lst.end(), 0, 42 );//将序列中的所有0替换为42
replace_copy( lst.cbegin(), lst.cend(),back_inserter(vec), 0, 42 );//lst自身不变，vec包含list的一份拷贝，只是其中所有0被替换为42
```





一些算法同时提供`_copy`和`_if`版本，接受一个`dest`和一个谓词：

```
//从v1中删除奇数元素
remove_if( v1.begin(), v1.end(),
						[](int i){return i%2;});
//将偶数元素拷贝到v2,v1不变						
remove_copy_if( v1.begin(), v1.end(), back_inserter(v2),
						[](int i){return i%2;});
```

# 特定容器算法

`list`和`forward_list`定义了几个成员函数形式的算法，对于这类容器，应当优先使用使用成员函数版本的算法而不是通用算法

