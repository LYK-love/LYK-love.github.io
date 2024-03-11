---
title: Python Basic
categories:
- Software Engineering
tags: Python
date: 2022-08-20 12:00:00
---

Sources:

1. [廖雪峰的教程](https://www.liaoxuefeng.com/wiki/1016959663602400)

<!--more-->

# Basic

## Operators

### Mean

Py内置了`**`运算符来求幂次

* `pow(a,n)`: 求a的n次幂, 如果a和n都是int,则返回int

* `math.pow(a,n)`: 求a的n次幂, 但是会把参数转成浮点数进行运算, 浮点运算是会出错的. 对于比较大的数字, 肯定会出错, 所以不要用`math.pow()`

  ```
  >>> import math
  >>> 17 ** 127 % 120
  113
  >>> math.pow(17,127) % 120 //出错了
  96.0
  >>> pow(17,127) % 120
  113
  ```

### Slice

取一个list或tuple的部分元素是非常常见的操作。比如，一个list如下：

```
>>> L = list(range(99))
```



```
L[start:end] # 从下标start开始, 到end为止, 但不包括end.
L[:3] # 如果第一个索引是0, 还可以省略.
L[:]# 原样复制一个list：
# 由于倒数第一个元素索引为-1,因此正数第一个元素索引为`-len(L)`,也就是说,`L[-len(L):]` 可以复制一个list,等价于`L[0:len(L)]`,即`L[:]`.
L[-2:] # 正向sclice, 从倒数第二个开始.
L[-2:-1] # 正向sclice, 从倒数第二个开始, 不包括倒数第一个元素(-1).
L[:-1] # 正向sclice, 不包括倒数第一个元素(-1).

L = L[::-1] #反转list:`
```





前10个数，每两个取一个：

```
>>> L[:10:2]
[0, 2, 4, 6, 8]
```

所有数，每5个取一个：

```
>>> L[::5]
[0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95]
```



tuple也是一种list，唯一区别是tuple不可变。因此，tuple也可以用切片操作，只是操作的结果仍是tuple：

```
>>> (0, 1, 2, 3, 4, 5)[:3]
(0, 1, 2)
```

字符串`'xxx'`也可以看成是一种list，每个元素就是一个字符。因此，字符串也可以用切片操作，只是操作结果仍是字符串：

```
>>> 'ABCDEFG'[:3]
'ABC'
>>> 'ABCDEFG'[::2]
'ACEG'
```

### Star or Asterisk operator ( * )

https://www.geeksforgeeks.org/python-star-or-asterisk-operator/



```python
arr = ['sunday', 'monday', 'tuesday', 'wednesday']
 
# without using asterisk
print(' '.join(map(str,arr))) 
 
# using asterisk
print (*arr)
```

```
sunday monday tuesday wednesday
sunday monday tuesday wednesday
```





**Passing a  Function Using with an arbitrary number of keyword arguments**
Here a double asterisk( ** ) is also used as ***kwargs*, the double asterisks allow passing keyword arguments. This special  symbol is used to pass a keyword arguments and variable-length argument  lists. It has many uses, one such example is illustrated below

```python
# using asterisk
def addition(*args):
  return sum(args)
 
print(addition(5, 10, 20, 6))
```



**Passing a  Function Using with an arbitrary number of keyword arguments**
Here a double asterisk( ** ) is also used as ***kwargs*, the double asterisks allow passing keyword arguments. This special  symbol is used to pass a keyword arguments and variable-length argument  lists. It has many uses, one such example is illustrated below

```python
# using asterisk
def food(**kwargs):
for items in kwargs:
	print(f"{kwargs[items]} is a {items}")
	
	
food(fruit = 'cherry', vegetable = 'potato', boy = 'srikrishna')
```



```python
# using asterisk
def food(**kwargs):
  for items in kwargs:
    print(f"{kwargs[items]} is a {items}")
     
     
dict = {'fruit' : 'cherry', 'vegetable' : 'potato', 'boy' : 'srikrishna'}
# using asterisk
food(**dict)
```

```
cherry is a fruit
potato is a vegetable
srikrishna is a boy
```



## Control Flow

Python中, **空字符串**, 空容器, 数字0都被判断为False.

```
age = 3
if age >= 18:
    print('your age is', age)
    print('adult')
else:
    print('your age is', age)
    print('teenager')
```





`if`还可以简写：

```
if x:
    print('True')
```



for:

```
sum = 0
for x in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
    sum = sum + x
print(sum)
```



## Deconstructor

Python的列表和元组支持解构赋值.

```python
def parse():
    return 12,'me'
x,y = parse() # 把parse()看作一个元组,默认按下标顺序赋值
print(x,y)

输出为: 12 me
    
#---也可以这样:------------#
x,y = parse[0],parse[1]
print(x,y)

输出为: 12 me
    
```

## Comments

单行注释：

```python
# 单行注释
```



多行注释: 用三引号( `'`或`""` )

```python
'''
使用三个连续的单/双引号分别作为注释的开头和结尾
可以一次性注释多行内容或单行内容
'''
```

注意多行注释如果作为字符串出现，就应当看作字符串，而不是注释

## Help Doc

在 Python 中可以通过 `help()`内置函数或者`__doc__`属性查看某个函数的说明文档：

```python
# 查看 print() 内置函数的说明文档
print('--- 用 help()内置函数查看说明文档 ---')
help(print)
print('--- 用 __doc__ 属性查看说明文档 ---')
print(print.__doc__)
```



函数的说明文档就是一段**多行注释**，位于函数内部、所有代码的最前面：

```python
# 定义一个比较数字大小的函数
def num_max(num1, num2):
    """
    比较两个数字的大小
    :param num1:形参1，数字1
    :param num2:形参2，数字2
    :return:大的数字，max_num = num1 if num1 > num2 else num2
    """
    max_num = num1 if num1 > num2 else num2
    return max_num
```

## lambda

The basic syntax of a lambda function is:

```python
lambda arguments: expression
```

- **`lambda`**: This is the keyword that indicates the start of a lambda expression.
- **`arguments`**: The arguments to the function, separated by commas. These are optional; a lambda function can have zero arguments.
- **`expression`**: A single expression which is executed and its value is returned when the lambda function is called. This expression can use the arguments in any way.



Example:

```
sorted(b.items(), key=lambda kv: -kv[1])
```

is used to sort the items of a dictionary `b` by their values in descending order. Let's break down this expression to understand its components and how it works:

1. **`b.items()`**: This method returns a view object that displays a list of a dictionary's key-value tuple pairs. For example, if `b = {'one': 1, 'two': 2}`, then `b.items()` returns `[('one', 1), ('two', 2)]`.
2. **`sorted()`**: This is a built-in Python function that returns a new sorted list from the elements of any iterable (like lists, dictionaries, tuples). The `sorted()` function by default sorts in ascending order.
3. **`key=lambda kv: -kv[1]`**: This part specifies a function to be used as the key for sorting. The `lambda` function takes an argument `kv` (representing each key-value tuple from the dictionary) and returns `-kv[1]`, which is the negative value of the tuple's second element (the value in the key-value pair of the dictionary). The reason for returning the negative value is to sort the items in descending order based on the dictionary values.
   - `kv`: A tuple representing a key-value pair from the dictionary.
   - `kv[1]`: The value part of the pair. Since Python's `sorted()` function sorts in ascending order by default, using `-kv[1]` as the key inverts the sorting order to descending.

# Types

Python3 中有六个标准的数据类型：

- Number（数字）
  * In Python, floating-point numbers are implemented using **double precision (64-bit)** by default.
- String（字符串）, Python中没有字符类型
- List（列表）
- Tuple（元组）
- Set（集合）
- Dictionary（字典）



Python3 的六个标准数据类型中：

- 不可变数据类型：Number, String, Tuple
- 可变数据类型：List, Dictionary, Set

## Type Check

To determine a Python variable's type, Use the [`type()`](https://docs.python.org/library/functions.html#type) builtin function:

```py
>>> i = 123
>>> type(i)
<type 'int'>
>>> type(i) is int
True
>>> i = 123.456
>>> type(i)
<type 'float'>
>>> type(i) is float
True
```



### isinstance() 

To check if a variable is of a given type, use [`isinstance`](https://docs.python.org/library/functions.html#isinstance):

```py
>>> i = 123
>>> isinstance(i, int)
True
>>> isinstance(i, (float, str, set, dict))
False
>>> isinstance (a,(str,int,list))    # 是元组中的一个返回 True
True
```



- type() 不会认为子类是一种父类类型，不考虑继承关系。
- isinstance() 会认为子类是一种父类类型，考虑继承关系。

```python
isinstance(object, classinfo)
```

- object -- 实例对象。
- classinfo -- 可以是直接或间接类名、基本类型或者由它们组成的元组。

## string 

Python的字符串类型是`str`，是**不可变**的. 在内存中以Unicode表示，一个字符对应若干个字节.

如果要在网络上传输，或者保存到磁盘上，就需要把`str`变为以字节为单位的`bytes`

Python对`bytes`类型的数据用带`b`前缀的单引号或双引号表示：

```
x = b'ABC'
```

要注意区分`'ABC'`和`b'ABC'`，前者是`str`，后者虽然内容显示得和前者一样，但`bytes`的每个字符都只占用一个字节。



### Encoding

* char -> ascii int: `ord()`

  ```
  >>> ord('A')
  65
  >>> ord('中')
  20013
  ```

* ascii int -> char: `char()`

  ```
  >>> chr(66)
  'B'
  >>> chr(25991)
  '文'
  ```

* str -> ascii:

  ```python
  text = input("enter a string to convert into ascii values:")
  ascii_values = []
  for character in text:
      ascii_values.append(ord(character))
  ```

  Or: 列表生成式

  ```python
  def to_ascii(text):
      ascii_values = [ord(character) for character in text] 
      return ascii_values
  ```

  



### String format

使用字符串的`format()`方法，它会用传入的参数依次替换字符串内的占位符`{0}`、`{1}`, ...

```
>>> 'Hello, {0}, 成绩提升了 {1:.1f}%'.format('小明', 17.125)
'Hello, 小明, 成绩提升了 17.1%'
```



## Number

Python3 Number类型的子类型有: int, float, bool, complex( 复数 )

* int: Python不存在整数溢出, 如果数字过大就会自动转换成大整数类型计算. 非常方便

  十六进制: `hex()`: 这个函数会把int转成它的十六进制表示, 类型是str

* float
* bool
* complex



## List

* 反转列表:

  ```
  list.reverse()
  ```

  该方法没有返回值, 但是会对列表的元素进行反向排序

* str -> list:

  ```
  list("hahaha")
  ```

* list -> str:

  ```
  ''.join(list, ' ')
  ```

## Tuple

## Set

## Dictionary

**`b.items()`**: This method returns a view object that displays <u>a list of a dictionary's key-value tuple pairs</u>. For example, if `b = {'one': 1, 'two': 2}`, then `b.items()` returns `[('one', 1), ('two', 2)]`.



The `update()` method inserts the specified items to the dictionary.

The specified items can be a dictionary, or an iterable object with key value  pairs.

```
dictionary.update(iterable) 
```



```python
car = {
  "brand": "Ford",
  "model": "Mustang",
  "year": 1964
}

car.update({"color": "White"}) # add an item
car.update({"brand": "BMW"}) # change an item's value
```



# Function

## Define Fuction 

```python
def my_abs(x):
	if x>= 0:
		return x
	else:
		return -x
```

Note that a return statement without a value is equivalent to `return None` , `return None`可以简写为`return`.

```python
def fn():
	# ....
	return
	
# Equals to:
def fn():
	# .... 
	# No return statement
	
# Equals to:
def fn():
	# ....
	return None
```

## pass

如果想定义一个什么事也不做的空函数，可以用`pass`语句：

```
def nop():
    pass
```

`pass`语句什么都不做，那有什么用？实际上`pass`可以用来作为占位符，比如现在还没想好怎么写函数的代码，就可以先放一个`pass`，让代码能运行起来。

`pass`还可以用在其他语句里，比如：

```
if age >= 18:
    pass
```

缺少了`pass`，代码运行就会有语法错误。

## Parameter

###  Parameter Check

`parameter`形参, `argument`实参

调用函数时，如果参数个数不对，Python解释器会自动检查出来，并抛出`TypeError`：

```
>>> my_abs(1, 2)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: my_abs() takes 1 positional argument but 2 were given
```

但是如果参数类型不对，Python解释器就无法帮我们检查。试试`my_abs`和内置函数`abs`的差别：

```
>>> my_abs('A')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 2, in my_abs
TypeError: unorderable types: str() >= int()
>>> abs('A')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: bad operand type for abs(): 'str'
```

当传入了不恰当的参数时，内置函数`abs`会检查出参数错误，而我们定义的`my_abs`没有参数检查，会导致`if`语句出错，出错信息和`abs`不一样。所以，这个函数定义不够完善。

让我们修改一下`my_abs`的定义，对参数类型做检查，只允许整数和浮点数类型的参数。数据类型检查可以用内置函数`isinstance()`实现：

```
def my_abs(x):
    if not isinstance(x, (int, float)): ## 
        raise TypeError('bad operand type')
    if x >= 0:
        return x
    else:
        return -x
```

注意`isinstance() arg 2 must be a type or tuple of types`,就是说`(interesting,float)`不能用`[int,float]`代替

添加了参数检查后，如果传入错误的参数类型，函数就可以抛出一个错误：

```
>>> my_abs('A')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 3, in my_abs
TypeError: bad operand type
```

错误和异常处理将在后续讲到。

## The `global` statement

If you want to assign a value to a name defined at the top level of the program (`i.e.` not inside any kind of **scope** such as functions or classes), then you have to tell Python that the name is not local, but it is `global`. We do this using the `global` statement. It is impossible to assign a value to a variable defined outside a function without the global statement. 在全局区域定义,在局部要使用的时候,要用`global`关键字
You can use the values of such variables defined outside the function (assuming there is no variable with the same name within the function). However, this is not encouraged and should be avoided since it becomes unclear to the reader of the program as to where that variable's definition is. Using the `global` statement makes it amply clear(显式地声明,不写会报错,解释器会将这个变量看做未定义) that the variable is defined in an outermost block.

```python
x = 50
def func(): 
    global x
	print('x is', x) 
    x = 2 
    print('Changed global x to', x)
    
func()
print('Value of x is', x)
```

The global statement is used to declare that `x` is a global variable - hence, **when we assign a value to x inside the function, that change is reflected when we use the value of `x` in the main block**. 在函数里改变了全局变量x,x的值是会更改的.
You can specify more than one global variable using the same global statement e.g. 

`global x, y, z .`

### Default Argument Values

<u>Only those parameters which are at the end of the parameter list can be given default argument values.</u>

For example, def func(a, b=5) is valid, but def func(a=5, b) is not valid.

### Keyword Arguments   

If you have some functions with many parameters and you want to specify only some of them, then you can give values for such parameters by *naming* them - this is called `keyword arguments` - we use the name (keyword) **instead of the position** (which we have been using all along) to specify the arguments to the function.
There are two advantages - one, using the function is easier since we do not need to worry about the order of the arguments. Two, we can give values to only those parameters to which we want to, provided that the other parameters have *default argument values*.

```python
def func(a, b=5, c=10): 
print('a is', a, 'and b is', b, 'and c is', c)
func(3, 7) 
func(25, c=24) 
func(c=50, a=100)

Output:
$ python function_keyword.py 
a is 3 and b is 7 and c is 10 
a is 25 and b is 5 and c is 24 
a is 100 and b is 5 and c is 50
```

**How it works**:

In the second usage func(25, c=24) , the variable a gets the value of 25 due to the**position** of the argument. Then, the parameter c gets the value of 24 due to **naming** i.e. `keyword arguments`. The variable b gets the default value of 5 .

### VarArgs parameters

Sometimes you might want to define a function that can take any number of parameters, i.e. variable number of arguments, this can be achieved by using the stars. 可以传入任意数量的参数

```python
def total(a=5, *numbers, **phonebook): p
    rint('a', a)
#iterate through all the items in tuple 
for single_item in numbers: 
    print('single_item', single_item)
#iterate through all the items in dictionary 
for first_part, second_part in phonebook.items(): 		print(first_part,second_part)
    
print(total(10,1,2,3,Jack=1123,John=2231,Inge=1560))

Output:
$ python function_varargs.py 
a 10
single_item 1
single_item 2 
single_item 3 
Inge 1560 
John 2231 
Jack 1123 
None
```

**How it works**
When we declare a starred parameter such as `*`param , then all the positional arguments from that point till the end are collected as a `tuple` called 'param'.
Similarly, when we declare a double-starred parameter such as `**`param , then all the keyword arguments from that point till the end are collected as a `dictionary` called 'param'.

# Basic Functions

## input()

```
DPI = int(input("DPI = ") or 400 )
```

* `input()`返回的是`str`, 对于数字要手动转成`int`

## range()

`range()`生成一个整数序列, 再通过`list()`函数可以转换为list. 比如`range(5)`生成的序列是从0开始小于5的整数：

```
>>> list(range(5))
[0, 1, 2, 3, 4]
```

`range(101)`就可以生成0-100的整数序列



range( ) 可以倒序生成序列:

```python
# 从100加到1. 每次间隔-1. 也就是说100, 然后100-1 = 99, 然后99-1 = 98, 相当于递减
for i in range(100,0,-1):
    print(i)
```



## enumerate()

Python内置的`enumerate`函数可以把一个**list**变成索引-元素对，这样就可以在`for`循环中同时迭代索引和元素本身：

```
>>> for i, value in enumerate(['A', 'B', 'C']):
...     print(i, value)
...
0 A
1 B
2 C
```



# Advanced Features

## Iteration

在Python中，迭代是通过`for ... in`来完成的.

Python的`for`循环不仅可以用在list或tuple上，还可以作用在其他可迭代对象上。

list这种数据类型虽然有下标，但很多其他数据类型是没有下标的，但是，只要是可迭代对象，无论有无下标，都可以迭代，比如dict就可以迭代：

```
>>> d = {'a': 1, 'b': 2, 'c': 3}
>>> for key in d:
...     print(key)
...
a
c
b
```

因为dict的存储不是按照list的方式顺序排列，所以，迭代出的结果顺序很可能不一样。

默认情况下，dict迭代的是key。如果要迭代value，可以用`for value in d.values()`，如果要同时迭代key和value，可以用`for k, v in d.items()`。

由于字符串也是可迭代对象，因此，也可以作用于`for`循环：

```
>>> for ch in 'ABC':
...     print(ch)
...
A
B
C
```

所以，当我们使用`for`循环时，只要作用于一个可迭代对象，`for`循环就可以正常运行，而我们不太关心该对象究竟是list还是其他数据类型。

### Iterable

我们已经知道，可以直接作用于`for`循环的数据类型有以下几种：

一类是集合数据类型，如`list`、`tuple`、`dict`、`set`、`str`等；

一类是`generator`，包括生成器和带`yield`的generator function。

这些可以直接作用于`for`循环的对象统称为可迭代对象：`Iterable`。

可以使用`isinstance()`判断一个对象是否是`Iterable`对象：

```
>>> from collections.abc import Iterable
>>> isinstance([], Iterable)
True
>>> isinstance({}, Iterable)
True
>>> isinstance('abc', Iterable)
True
>>> isinstance((x for x in range(10)), Iterable)
True
>>> isinstance(100, Iterable)
False
```

而生成器不但可以作用于`for`循环，还可以被`next()`函数不断调用并返回下一个值，直到最后抛出`StopIteration`错误表示无法继续返回下一个值了。

可以被`next()`函数调用并不断返回下一个值的对象称为迭代器：`Iterator`。

### Iterator

可以使用`isinstance()`判断一个对象是否是`Iterator`对象：

```
>>> from collections.abc import Iterator
>>> isinstance((x for x in range(10)), Iterator)
True
>>> isinstance([], Iterator)
False
>>> isinstance({}, Iterator)
False
>>> isinstance('abc', Iterator)
False
```

生成器都是`Iterator`对象，但`list`、`dict`、`str`虽然是`Iterable`，却不是`Iterator`。

把`list`、`dict`、`str`等`Iterable`变成`Iterator`可以使用`iter()`函数：

```
>>> isinstance(iter([]), Iterator)
True
>>> isinstance(iter('abc'), Iterator)
True
```



你可能会问，为什么`list`、`dict`、`str`等数据类型不是`Iterator`？

这是因为Python的`Iterator`对象表示的是一个数据流，Iterator对象可以被`next()`函数调用并不断返回下一个数据，直到没有数据时抛出`StopIteration`错误。可以把这个数据流看做是一个有序序列，但我们却不能提前知道序列的长度，只能不断通过`next()`函数实现按需计算下一个数据，所以`Iterator`的计算是惰性的，只有在需要返回下一个数据时它才会计算。

`Iterator`甚至可以表示一个无限大的数据流，例如全体自然数。而使用list是永远不可能存储全体自然数的。

### 

## List Comprehensions

------

列表生成式即List Comprehensions，是Python内置的非常简单却强大的可以用来创建list的生成式。

举个例子，要生成list `[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]`可以用`list(range(1, 11))`：

```
>>> list(range(1, 11))
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```

但如果要生成`[1x1, 2x2, 3x3, ..., 10x10]`怎么做？方法一是循环：

```
>>> L = []
>>> for x in range(1, 11):
...    L.append(x * x)
...
>>> L
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```

但是循环太繁琐，而列表生成式则可以用一行语句代替循环生成上面的list：

```
>>> [x * x for x in range(1, 11)]
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```

写列表生成式时，把要生成的元素`x * x`放到前面，后面跟`for`循环，就可以把list创建出来，十分有用，多写几次，很快就可以熟悉这种语法。

for循环后面还可以加上if判断，这样我们就可以筛选出仅偶数的平方：

```
>>> [x * x for x in range(1, 11) if x % 2 == 0]
[4, 16, 36, 64, 100]
```

还可以使用两层循环，可以生成全排列：

```
>>> [m + n for m in 'ABC' for n in 'XYZ']
['AX', 'AY', 'AZ', 'BX', 'BY', 'BZ', 'CX', 'CY', 'CZ']
```

三层和三层以上的循环就很少用到了。

运用列表生成式，可以写出非常简洁的代码。例如，列出当前目录下的所有文件和目录名，可以通过一行代码实现：

```
>>> import os # 导入os模块，模块的概念后面讲到
>>> [d for d in os.listdir('.')] # os.listdir可以列出文件和目录
['.emacs.d', '.ssh', '.Trash', 'Adlm', 'Applications', 'Desktop', 'Documents', 'Downloads', 'Library', 'Movies', 'Music', 'Pictures', 'Public', 'VirtualBox VMs', 'Workspace', 'XCode']
```

`for`循环其实可以同时使用两个甚至多个变量，比如`dict`的`items()`可以同时迭代key和value：

```
>>> d = {'x': 'A', 'y': 'B', 'z': 'C' }
>>> for k, v in d.items():
...     print(k, '=', v)
...
y = B
x = A
z = C
```

因此，列表生成式也可以使用两个变量来生成list：

```
>>> d = {'x': 'A', 'y': 'B', 'z': 'C' }
>>> [k + '=' + v for k, v in d.items()]
['y=B', 'x=A', 'z=C']
```

最后把一个list中所有的字符串变成小写：

```
>>> L = ['Hello', 'World', 'IBM', 'Apple']
>>> [s.lower() for s in L]
['hello', 'world', 'ibm', 'apple']
```

### if ... else

使用列表生成式的时候，有些童鞋经常搞不清楚`if...else`的用法。

例如，以下代码正常输出偶数：

```
>>> [x for x in range(1, 11) if x % 2 == 0]
[2, 4, 6, 8, 10]
```

但是，我们不能在最后的`if`加上`else`：

```
>>> [x for x in range(1, 11) if x % 2 == 0 else 0]
  File "<stdin>", line 1
    [x for x in range(1, 11) if x % 2 == 0 else 0]
                                              ^
SyntaxError: invalid syntax
```

这是因为跟在`for`后面的`if`是一个筛选条件，不能带`else`，否则如何筛选？

另一些童鞋发现把`if`写在`for`前面必须加`else`，否则报错：

```python
>>> [x if x % 2 == 0 for x in range(1, 11)]
  File "<stdin>", line 1
    [x if x % 2 == 0 for x in range(1, 11)]
                       ^
SyntaxError: invalid syntax
```

这是因为`for`前面的部分是一个表达式，它必须根据`x`计算出一个结果。因此，考察表达式：`x if x % 2 == 0`，它无法根据`x`计算出结果，因为缺少`else`，必须加上`else`：

```python
>>> [x if x % 2 == 0 else -x for x in range(1, 11)]
[-1, 2, -3, 4, -5, 6, -7, 8, -9, 10]
```

上述`for`前面的表达式`x if x % 2 == 0 else -x`才能根据`x`计算出确定的结果。

可见，在一个列表生成式中，`for`前面的`if ... else`是表达式，而`for`后面的`if`是过滤条件，不能带`else`。



## Generator

通过列表生成式，我们可以直接创建一个列表。但是，受到内存限制，列表容量肯定是有限的。而且，创建一个包含100万个元素的列表，不仅占用很大的存储空间，如果我们仅仅需要访问前面几个元素，那后面绝大多数元素占用的空间都白白浪费了。

所以，如果列表元素可以按照某种算法推算出来，那我们是否可以在循环的过程中不断推算出后续的元素呢？这样就不必创建完整的list，从而节省大量的空间。在Python中，这种一边循环一边计算的机制，称为生成器：generator。

要创建一个generator，有很多种方法。第一种方法很简单，只要把一个列表生成式的`[]`改成`()`，就创建了一个generator：

```
>>> L = [x * x for x in range(10)]
>>> L
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
>>> g = (x * x for x in range(10))
>>> g
<generator object <genexpr> at 0x1022ef630>
```

创建`L`和`g`的区别仅在于最外层的`[]`和`()`，`L`是一个list，而`g`是一个generator。

我们可以直接打印出list的每一个元素，但我们怎么打印出generator的每一个元素呢？

如果要一个一个打印出来，可以通过`next()`函数获得generator的下一个返回值：

```
>>> next(g)
0
>>> next(g)
1
>>> next(g)
4
>>> next(g)
9
>>> next(g)
16
>>> next(g)
25
>>> next(g)
36
>>> next(g)
49
>>> next(g)
64
>>> next(g)
81
>>> next(g)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

我们讲过，generator保存的是算法，每次调用`next(g)`，就计算出`g`的下一个元素的值，直到计算到最后一个元素，没有更多的元素时，抛出`StopIteration`的错误。

当然，上面这种不断调用`next(g)`实在是太变态了，正确的方法是使用`for`循环，因为generator也是可迭代对象：

```
>>> g = (x * x for x in range(10))
>>> for n in g:
...     print(n)
... 
0
1
4
9
16
25
36
49
64
81
```

所以，我们创建了一个generator后，基本上永远不会调用`next()`，而是通过`for`循环来迭代它，并且不需要关心`StopIteration`的错误。

generator非常强大。如果推算的算法比较复杂，用类似列表生成式的`for`循环无法实现的时候，还可以用函数来实现。

比如，著名的斐波拉契数列（Fibonacci），除第一个和第二个数外，任意一个数都可由前两个数相加得到：

1, 1, 2, 3, 5, 8, 13, 21, 34, ...

斐波拉契数列用列表生成式写不出来，但是，用函数把它打印出来却很容易：

```
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        print(b)
        a, b = b, a + b
        n = n + 1
    return 'done'
```

*注意*，赋值语句：

```
a, b = b, a + b
```

相当于：

```
t = (b, a + b) # t是一个tuple
a = t[0]
b = t[1]
```

但不必显式写出临时变量t就可以赋值。

上面的函数可以输出斐波那契数列的前N个数：

```
>>> fib(6)
1
1
2
3
5
8
'done'
```

仔细观察，可以看出，`fib`函数实际上是定义了斐波拉契数列的推算规则，可以从第一个元素开始，推算出后续任意的元素，这种逻辑其实非常类似generator。

也就是说，上面的函数和generator仅一步之遥。要把`fib`函数变成generator，只需要把`print(b)`改为`yield b`就可以了：

```
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'
```

这就是定义generator的另一种方法。如果一个函数定义中包含`yield`关键字，那么这个函数就不再是一个普通函数，而是一个generator：

```
>>> f = fib(6)
>>> f
<generator object fib at 0x104feaaa0>
```

这里，最难理解的就是generator和函数的执行流程不一样。函数是顺序执行，遇到`return`语句或者最后一行函数语句就返回。而变成generator的函数，在每次调用`next()`的时候执行，遇到`yield`语句返回，再次执行时从上次返回的`yield`语句处继续执行。

举个简单的例子，定义一个generator，依次返回数字1，3，5：

```
def odd():
    print('step 1')
    yield 1
    print('step 2')
    yield(3)
    print('step 3')
    yield(5)
```

调用该generator时，首先要生成一个generator对象，然后用`next()`函数不断获得下一个返回值：

```
>>> o = odd()
>>> next(o)
step 1
1
>>> next(o)
step 2
3
>>> next(o)
step 3
5
>>> next(o)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

可以看到，`odd`不是普通函数，而是generator，在执行过程中，遇到`yield`就中断，下次又继续执行。执行3次`yield`后，已经没有`yield`可以执行了，所以，第4次调用`next(o)`就报错。

回到`fib`的例子，我们在循环过程中不断调用`yield`，就会不断中断。当然要给循环设置一个条件来退出循环，不然就会产生一个无限数列出来。

同样的，把函数改成generator后，我们基本上从来不会用`next()`来获取下一个返回值，而是直接使用`for`循环来迭代：

```
>>> for n in fib(6):
...     print(n)
...
1
1
2
3
5
8
```

但是用`for`循环调用generator时，发现拿不到generator的`return`语句的返回值。如果想要拿到返回值，必须捕获`StopIteration`错误，返回值包含在`StopIteration`的`value`中：

```
>>> g = fib(6)
>>> while True:
...     try:
...         x = next(g)
...         print('g:', x)
...     except StopIteration as e:
...         print('Generator return value:', e.value)
...         break
...
g: 1
g: 1
g: 2
g: 3
g: 5
g: 8
Generator return value: done
```

## 迭代器

### 小结

凡是可作用于`for`循环的对象都是`Iterable`类型；

凡是可作用于`next()`函数的对象都是`Iterator`类型，它们表示一个惰性计算的序列；

集合数据类型如`list`、`dict`、`str`等是`Iterable`但不是`Iterator`，不过可以通过`iter()`函数获得一个`Iterator`对象。

Python的`for`循环本质上就是通过不断调用`next()`函数实现的，例如：

```
for x in [1, 2, 3, 4, 5]:
    pass
```

实际上完全等价于：

```
# 首先获得Iterator对象:
it = iter([1, 2, 3, 4, 5])
# 循环:
while True:
    try:
        # 获得下一个值:
        x = next(it)
    except StopIteration:
        # 遇到StopIteration就退出循环
        break
```

# Error Handling

Python所有的错误都是从`BaseException`类派生的，常见的错误类型和继承关系看这里：

https://docs.python.org/3/library/exceptions.html#exception-hierarchy

## try

让我们用一个例子来看看`try`的机制：

```
try:
    print('try...')
    r = 10 / 0
    print('result:', r)
except ZeroDivisionError as e:
    print('except:', e)
finally:
    print('finally...')
print('END')
```

当我们认为某些代码可能会出错时，就可以用`try`来运行这段代码，如果执行出错，则后续代码不会继续执行，而是直接跳转至错误处理代码，即`except`语句块，执行完`except`后，如果有`finally`语句块，则执行`finally`语句块，至此，执行完毕。

上面的代码在计算`10 / 0`时会产生一个除法运算错误：

```
try...
except: division by zero
finally...
END
```

从输出可以看到，当错误发生时，后续语句`print('result:', r)`不会被执行，`except`由于捕获到`ZeroDivisionError`，因此被执行。最后，`finally`语句被执行。然后，程序继续按照流程往下走。

如果把除数`0`改成`2`，则执行结果如下：

```
try...
result: 5
finally...
END
```

由于没有错误发生，所以`except`语句块不会被执行，但是`finally`如果有，则一定会被执行（可以没有`finally`语句）。

你还可以猜测，错误应该有很多种类，如果发生了不同类型的错误，应该由不同的`except`语句块处理。没错，可以有多个`except`来捕获不同类型的错误：

```
try:
    print('try...')
    r = 10 / int('a')
    print('result:', r)
except ValueError as e:
    print('ValueError:', e)
except ZeroDivisionError as e:
    print('ZeroDivisionError:', e)
finally:
    print('finally...')
print('END')
```

`int()`函数可能会抛出`ValueError`，所以我们用一个`except`捕获`ValueError`，用另一个`except`捕获`ZeroDivisionError`。

此外，如果没有错误发生，可以在`except`语句块后面加一个`else`，当没有错误发生时，会自动执行`else`语句：

```
try:
    print('try...')
    r = 10 / int('2')
    print('result:', r)
except ValueError as e:
    print('ValueError:', e)
except ZeroDivisionError as e:
    print('ZeroDivisionError:', e)
else:
    print('no error!')
finally:
    print('finally...')
print('END')
```



Python的错误其实也是class，所有的错误类型都继承自`BaseException`，所以在使用`except`时需要注意的是，它不但捕获该类型的错误，还把其子类也“一网打尽”。比如：

```
try:
    foo()
except ValueError as e:
    print('ValueError')
except UnicodeError as e:
    print('UnicodeError')
```

第二个`except`永远也捕获不到`UnicodeError`，因为`UnicodeError`是`ValueError`的子类，如果有，也被第一个`except`给捕获了。



## raise

因为错误是class，捕获一个错误就是捕获到该class的一个实例。因此，错误并不是凭空产生的，而是有意创建并抛出的。Python的内置函数会抛出很多类型的错误，我们自己编写的函数也可以抛出错误。

如果要抛出错误，首先根据需要，可以定义一个错误的class，选择好继承关系，然后，用`raise`语句抛出一个错误的实例：

```
# err_raise.py
class FooError(ValueError):
    pass

def foo(s):
    n = int(s)
    if n==0:
        raise FooError('invalid value: %s' % s)
    return 10 / n

foo('0')
```

执行，可以最后跟踪到我们自己定义的错误：

```
$ python3 err_raise.py 
Traceback (most recent call last):
  File "err_throw.py", line 11, in <module>
    foo('0')
  File "err_throw.py", line 8, in foo
    raise FooError('invalid value: %s' % s)
__main__.FooError: invalid value: 0
```

只有在必要的时候才定义我们自己的错误类型。如果可以选择Python已有的内置的错误类型（比如`ValueError`，`TypeError`），尽量使用Python内置的错误类型。

最后，我们来看另一种错误处理的方式：

```
# err_reraise.py

def foo(s):
    n = int(s)
    if n==0:
        raise ValueError('invalid value: %s' % s)
    return 10 / n

def bar():
    try:
        foo('0')
    except ValueError as e:
        print('ValueError!')
        raise

bar()
```

在`bar()`函数中，我们明明已经捕获了错误，但是，打印一个`ValueError!`后，又把错误通过`raise`语句抛出去了，这不有病么？

其实这种错误处理方式不但没病，而且相当常见。捕获错误目的只是记录一下，便于后续追踪。但是，由于当前函数不知道应该怎么处理该错误，所以，最恰当的方式是继续往上抛，让顶层调用者去处理。好比一个员工处理不了一个问题时，就把问题抛给他的老板，如果他的老板也处理不了，就一直往上抛，最终会抛给CEO去处理。

`raise`语句如果不带参数，就会把当前错误原样抛出。此外，在`except`中`raise`一个Error，还可以把一种类型的错误转化成另一种类型：

```
try:
    10 / 0
except ZeroDivisionError:
    raise ValueError('input error!')
```

只要是合理的转换逻辑就可以，但是，决不应该把一个`IOError`转换成毫不相干的`ValueError`。

## assert

凡是用`print()`来辅助查看的地方，都可以用断言（assert）来替代：

```
def foo(s):
    n = int(s)
    assert n != 0, 'n is zero!'
    return 10 / n

def main():
    foo('0')
```

`assert`的意思是，表达式`n != 0`应该是`True`，否则，根据程序运行的逻辑，后面的代码肯定会出错。

如果断言失败，`assert`语句本身就会抛出`AssertionError`：

```
$ python err.py
Traceback (most recent call last):
  ...
AssertionError: n is zero!
```

程序中如果到处充斥着`assert`，和`print()`相比也好不到哪去。不过，启动Python解释器时可以用`-O`参数来关闭`assert`：

```
$ python -O err.py
Traceback (most recent call last):
  ...
ZeroDivisionError: division by zero
```

 注意：断言的开关“-O”是英文大写字母O，不是数字0。

关闭后，你可以把所有的`assert`语句当成`pass`来看.



# 注意事项

## 文件路径

Python中的相对路径，是相对于**当前被执行文件**的路径， 举例来说， 如果`main.py` 中`import`了`A.py`, 而 `A.py`中有相对路径`../path`, 则在运行`main.py`时， 该路径实际上是相对于`main.py`的， 而如果单独运行`A.py`，该路径才是相对于`A.py`的

# 小技巧

## 矩阵

转置矩阵

```python
def two_dimensional_array(m):
    row_nums = len(m)
    col_nums = len(m[0])
    print("m = ", m)
    print( "row_nums = {0}, col_nums = {1}".format( row_nums, col_nums ) )
    rows = []
    for j in range( 0, col_nums ):
        tmp = []
        for i in range( 0, row_nums ):
            
            tmp.append(m[i][j])
            #print( m[i][j] )
            if i == row_nums - 1:
                print(tmp)
                rows.append(tmp)
    res_m = [ rows[j] for j in range( 0, col_nums ) ]        
    return res_m

//输入 [[1, 'j'], [2, 'k'], [3, 'l'], [4, 'm'], [5, 'n']]
//输出 [[1, 2, 3, 4, 5], ['j', 'k', 'l', 'm', 'n']]

```

注意：

python二维数组可以`res_m = [ rows[j] for j in range( 0, col_nums ) ] `创建。也就是说，列表生成式可以由元素生成列表，而这个元素本身也可以是列表，所以最后会生成一个`二维列表`。

<!--more-->

二维列表可以用列表生成式：

```python
    l1 = [ 1,2,3,4,5 ]
    l2 = [ "j","k","l","m","n" ]
    l3 = [ l1,l2 ] // 方法一
    l4 = [ l3[i] for i in range(0,len(l3)) ] //方法二,列表生成式
    
    l5 = [].append(l1)
    l5.append(l1)
    l5.append(l2)  // 方法三
    
    //注意, "+"会把列表拼接起来, 而append()会把参数整个当作一个元素加到列表末尾
    l6 = l1  + l2 // 结果是[ 1,2,3,4,5, "j","k","l","m","n" ] , 可以看到仍是一维的
   
```



##