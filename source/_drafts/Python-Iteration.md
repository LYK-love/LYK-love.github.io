---
title: Python Iteration
tags:
---





# 同时迭代多个变量



## for i j in zip

Python表达式`for i, j in zip(iter_1, iter_2)` ，可以将两个迭代变量`iter_1` 和`iter_2` 的值有序地对齐，并对元素对进行迭代。我们在变量`i` 和`j` 中捕获相同位置的两个元素。

下面是一个将两个[列表](https://link.juejin.cn?target=https%3A%2F%2Fblog.finxter.com%2Fpython-lists%2F) `[1,2,3]` 和`[9,8,7,6,5]` 拉到一起的例子。

```css
for i, j in zip([1,2,3], [9,8,7,6,5]):
    print(i, j)

复制代码
```

输出

```
1 9
2 8
3 7
```



## for i, j in enumerate

Python 表达式`for i, j in enumerate(iterable)` 允许你使用变量`i` 作为计数器 (0, 1, 2, ...) 和变量`j` 来捕获可迭代的元素，在一个可迭代元素上进行循环。

下面是一个例子，我们把计数器的值`i=0,1,2` 赋给`lst` 中的三个元素。

```scss
lst = ['Alice', 'Bob', 'Carl']
for i, j in enumerate(lst):
    print(i, j)

复制代码
```

输出

```
0 Alice
1 Bob
2 Carl
复制代码
```

注意循环迭代的捕捉方式

- `i=0` 和 。`j='Alice'`
- `i=1` 和 , 和`j='Bob'`
- `i=2` 和 。`j='Carl'`



作者：方石剑
