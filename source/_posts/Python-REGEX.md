---
categories:
- Software Engineering
date: 2022-08-26 00:43:35
tags: Python
title: Python REGEX
---

Outline:

* re模块
* 切分字符串
* 分组
* 贪婪匹配
* 编译

<!--more-->

# re模块

Python提供`re`模块，包含所有正则表达式的功能。由于Python的字符串本身也用`\`转义，所以要特别注意：

```
s = 'ABC\\-001' # Python的字符串
# 对应的正则表达式字符串变成：
# 'ABC\-001'
```

因此我们强烈建议使用Python的`r`前缀，就不用考虑转义的问题了：

```python
s = r'ABC\-001' # Python的字符串
# 对应的正则表达式字符串不变：
# 'ABC\-001'
```

先看看如何判断正则表达式是否匹配：

```
>>> import re
>>> re.match(r'^\d{3}\-\d{3,8}$', '010-12345')
<_sre.SRE_Match object; span=(0, 9), match='010-12345'>
>>> re.match(r'^\d{3}\-\d{3,8}$', '010 12345')
>>>
```

`match()`方法判断是否匹配，如果匹配成功，返回一个`Match`对象，否则返回`None`。常见的判断方法就是：

```python
test = '用户输入的字符串'
if re.match(r'正则表达式', test):
    print('ok')
else:
    print('failed')
```

# 切分字符串

用正则表达式切分字符串比用固定的字符更灵活，请看正常的切分代码：

```
>>> 'a b   c'.split(' ')
['a', 'b', '', '', 'c']
```

嗯，无法识别连续的空格，用正则表达式试试：

```
>>> re.split(r'\s+', 'a b   c')
['a', 'b', 'c']
```

无论多少个空格都可以正常分割。加入`,`试试：

```
>>> re.split(r'[\s\,]+', 'a,b, c  d')
['a', 'b', 'c', 'd']
```

再加入`;`试试：

```
>>> re.split(r'[\s\,\;]+', 'a,b;; c  d')
['a', 'b', 'c', 'd']
```

如果用户输入了一组标签，下次记得用正则表达式来把不规范的输入转化成正确的数组。

# Group in Regex

**A group is a part of a regex pattern enclosed in parentheses `()` metacharacter**. We create a group by placing the regex pattern inside the set of parentheses `(` and `)` . 

For example:

1. the regular expression `(cat)` creates a single group containing the letters ‘c’, ‘a’, and ‘t’.

2. `^(\d{3})-(\d{3,8})$`分别定义了两个组，可以直接从匹配的字符串中提取出区号和本地号码：

   ```
   >>> m = re.match(r'^(\d{3})-(\d{3,8})$', '010-12345')
   >>> m
   <_sre.SRE_Match object; span=(0, 9), match='010-12345'>
   >>> m.group(0)
   '010-12345'
   >>> m.group(1)
   '010'
   >>> m.group(2)
   '12345'
   ```



如果正则表达式中定义了组，就

* 

### Access Each Group Result Separately

可以在`Match`对象上用`group()`方法提取出子串来。`group(0)`永远是原始字符串. `group(1)`, `group(2)`……表示第1, 2, ……个子串。



**Example**

```python
# Extract first group
print(result.group(1))

# Extract second group
print(result.group(2))

# Target string
print(result.group(0))
```

提取子串非常有用。来看一个更凶残的例子：

```
>>> t = '19:05:30'
>>> m = re.match(r'^(0[0-9]|1[0-9]|2[0-3]|[0-9])\:(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-9]|5[0-9]|[0-9])\:(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-9]|5[0-9]|[0-9])$', t)
>>> m.groups()
('19', '05', '30')
```

这个正则表达式可以直接识别合法的时间。但是有些时候，用正则表达式也无法做到完全验证，比如识别日期：

```
'^(0[1-9]|1[0-2]|[0-9])-(0[1-9]|1[0-9]|2[0-9]|3[0-1]|[0-9])$'
```

对于`'2-30'`，`'4-31'`这样的非法日期，用正则还是识别不了，或者说写出来非常困难，这时就需要程序配合识别了。

### Regex Capture Group Multiple Times

In earlier examples, we used the search method. It will return only the first match for each group. But what if a string contains the multiple occurrences of a regex group and you want to extract all matches.

In this section, we will learn how to capture all matches to a regex group. To capture all matches to a regex group we need to use the [finditer()](https://pynative.com/python-regex-findall-finditer/#h-finditer-method) method.

The finditer() method finds all matches and returns an iterator yielding match objects matching the regex pattern. Next, we can iterate each Match object and extract its value.

**Note**: Don’t use the [findall()](https://pynative.com/python-regex-findall-finditer/) method because it returns a list, the group() method cannot be applied. If you try to apply it to the findall method, you will get AttributeError: ‘list’ object has no attribute ‘groups.’

So always use finditer if you wanted to capture all matches to the group.

**Example**

```python
import re

target_string = "The price of ice-creams PINEAPPLE 20 MANGO 30 CHOCOLATE 40"

# two groups enclosed in separate ( and ) bracket
# group 1: find all uppercase letter
# group 2: find all numbers
# you can compile a pattern or directly pass to the finditer() method
pattern = re.compile(r"(\b[A-Z]+\b).(\b\d+\b)")

# find all matches to groups
for match in pattern.finditer(target_string):
    # extract words
    print(match.group(1))
    # extract numbers
    print(match.group(2))
```

### Extract Range of Groups Matches

One more thing that you can do with the `group()` method is to have the matches returned as a tuple by specifying the associated group numbers in between the `group()` method’s parentheses. This is useful when we want to extract the range of groups.

For example, get the first 5 group matches only by executing the `group(1, 5`).

Let’s try this as well.

**Example**

```python
import re

target_string = "The price of PINEAPPLE ice cream is 20"
# two pattern enclosed in separate ( and ) bracket
result = re.search(r".+(\b[A-Z]+\b).+(\b\d+)", target_string)

print(result.group(1, 2))
# Output ('PINEAPPLE', '20')
```

# 贪婪匹配

最后需要特别指出的是，Py的正则匹配默认是贪婪匹配，也就是匹配尽可能多的字符。举例如下，匹配出数字后面的`0`：

```
>>> re.match(r'^(\d+)(0*)$', '102300').groups()
('102300', '')
```

由于`\d+`采用贪婪匹配，直接把后面的`0`全部匹配了，结果`0*`只能匹配空字符串了。

必须让`\d+`采用非贪婪匹配（也就是尽可能少匹配），才能把后面的`0`匹配出来，加个`?`就可以让`\d+`采用非贪婪匹配：

```
>>> re.match(r'^(\d+?)(0*)$', '102300').groups()
('1023', '00')
```



再例如: 在给定string中匹配出ipv4地址, 即类似于`192.168.1.53`这样的一组子串.



```python
r'\d+(.\d+)+' #试图匹配192.168.1.53类型的字符串，然而因为其将小括号内视为一个group，因此只会返回.53（只匹配小括号内且只返回最后一个符合的项）
r'\d+(?:.\d+)+' #正确写法，?:即声明这不是一个group
```



# 编译

当我们在Python中使用正则表达式时，re模块内部会干两件事情：

1. 编译正则表达式，如果正则表达式的字符串本身不合法，会报错；
2. 用编译后的正则表达式去匹配字符串。

如果一个正则表达式要重复使用几千次，出于效率的考虑，我们可以预编译该正则表达式，接下来重复使用时就不需要编译这个步骤了，直接匹配：

```
>>> import re
# 编译:
>>> re_telephone = re.compile(r'^(\d{3})-(\d{3,8})$')
# 使用：
>>> re_telephone.match('010-12345').groups()
('010', '12345')
>>> re_telephone.match('010-8086').groups()
('010', '8086')
```

编译后生成Regular Expression对象，由于该对象自己包含了正则表达式，所以调用对应的方法时不用给出正则字符串。