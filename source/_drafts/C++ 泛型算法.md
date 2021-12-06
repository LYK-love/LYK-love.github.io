---
title: C++ 泛型算法
tags:09op[0  ]
---

## 再探迭代器

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
| `back_insert_iterator`  | 创建一个使用`push_back`的迭代器，前提是提供有 push_back() 成员方法的容器（包括 vector、deque 和 list）。 |
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

### istream_iterator允许使用懒惰求值

* 当`istream_iterator`绑定到一个流时，标准库并不保证迭代器立即从流中读取数据。 具体实现可以直到使用迭代器时才真正读取。

## ostream_iterator

可以对任何具有`<<`运算符的类型定义`ostream_iterator`.  当创建`ostream_iterator`时，我们可以提供（可选的）第二个参数。它是一个**C风格字符串**， 在输出每个元素后都会打印此字符串

* 必须将`ostream_iterator`绑定带一个指定的流。 不允许空的或者表示尾后位置的`ostream_iterator`





