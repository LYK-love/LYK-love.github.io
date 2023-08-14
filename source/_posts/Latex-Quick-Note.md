---
title: Latex Quick Note
categories: Toolkit
mathjax: true
date: 2021-07-23 15:39:08
---

Latex grammer.

<!--more-->

# How

在Typora中：

* 按住`ctrl + shift + m`
* 或者输入`$$`

# Latex syntax

[Ref](https://oeis.org/wiki/List_of_LaTeX_mathematical_symbols)



## 上下标

* 上标

  * 只有一个: `a^2`
  * 多个: `a^{1224}`

* 下标

  * 跟上标类似，只需要把^换成_

* 如果有多重下标或上标，必须用{ }进行准确的分割

  * `A_{bb_{cc}}`

  $$
  A_{bb_{cc}}
  $$

  

## 插入水平线

* `\overline`和`\underline`
  * `\overline{a+b+c} = \underline{a+b+c}`

$$
\overline{a+b+c} = \underline{a+b+c}
$$

## 平方根

* 语法为`\sqrt[n]` 未给出n则默认为2

  * `\sqrt[5]{ a }`

  $$
  \sqrt[5]{ a }
  $$

  

## 插入水平大括号

* 语法为`\overbrace` 和`\underbrace`
  * `\overbrace{2,3,4,\cdots,100}^{99}`

$$
\overbrace{2,3,4,\cdots,100}^{99}
$$

## 分式

* 语法为`\frac{}{} `
  * `\frac{abc}{defg}`

$$
\frac{abc}{defg}
$$

* 连续分式 `\cfrac{}{}`
  * `\cfrac{1} { a + \cfrac{1}b}`

$$
\cfrac{1} { a + \cfrac{1}b}
$$



##  导数

* `x'`

$$
x'
$$



## 积分

* 语法为`\int `
  * `\int_{a}^{b}{f(x)} = x^2`

$$
\int_{a}^{b}{f(x)} = x^2
$$

##  向量

* 单符号可以用`\vec`
* 多符号可以用`\overrightarrow` 和`\overleftarrow`
  * `\vec a = \overrightarrow{AB} = \overleftarrow{BA}`


$$
\vec a = \overrightarrow{AB} = \overleftarrow{BA}
$$

## 乘积

* `\prod`
  * `\prod_{i=1}^{n}{(1/i)}`

$$
\prod_{i=1}^{n}{(1/i)}
$$

## 箭头

* `\larr` `\rarr`

$$
\larr  \rarr
$$



## 微积分符号

| latex       | 显示效果    |
| ----------- | ----------- |
| `\partial`  | $\partial$  |
| `\nabla`    | $\nabla$    |
| `\infty`    | $\infty$    |
| `\int`      | $\int$      |
| `\iint`     | $\iint$     |
| \iiint`     | $\iiint$    |
| `\oint`     | $\oint$     |
| `\triangle` | $\triangle$ |

## 空格

Ref: https://blog.csdn.net/seaskying/article/details/51316607

| 描述         | latex        | 显示效果      | 说明           |
| ------------ | ------------ | ------------- | -------------- |
| 两个quad空格 | `a \qquad b` | $a \qquad  b$ | 两个*m*的宽度  |
| quad空格     | `a \quad b`  | $a \quad b$   | 一个*m*的宽度  |
| 大空格       | `a\ b`       | $a\ b$        | 1/3*m*宽度     |
| 中等空格     | `a\; b`      | $a\;b$        | 2/7*m*宽度     |
| 小空格       | `a\, b`      | $a\,b$        | 1/6 *m*宽度    |
| 没有空格     | `ab`         | $ab$          |                |
| 紧贴         | `a\!b`       | $a\!b$        | 缩进1/6*m*宽度 |

* \quad、1em、em、m代表当前字体下接近字符‘M’的宽度。

  

## 关系符与运算符

| 关系符与运算符 | latex                                  |
| -------------- | -------------------------------------- |
| 不等号         | `\ne`                                  |
| 大于等于号     | `\ge`                                  |
| 小于等于号     | `\le`                                  |
| 约等号         | `\approx`                              |
| 等价           | `\equiv`                               |
| 乘号           | `\times`                               |
| 除号           | `\div`                                 |
| 点乘           | `\cdot`                                |
| 加减号         | `\pm`                                  |
| 三角函数       | `\sin(a)  \cos(a)`                     |
| 求和号         | `\sum`( 需要加`\limits` )              |
| 积分号         | `\int`                                 |
| 极限           | `\lim`                                 |
| 对数log        | `log`                                  |
| 对数lg         | `lg`                                   |
| 对数ln         | `ln`                                   |
| 向下和向上取整 | `\lfloor x \rfloor`和`\lceil x \rceil` |
| 全等于         | `\equiv`                               |



* e.g. `f(1) = \lim_{x - > 1 }{f(x)} = \sin (log_{2}1)`

$$
f(1) = \lim_{x - > 1 }{f(x)} = \sin (log_{2}1)
$$

* `y = a\cdot x^2 + b\cdot x + c `

$$
y = a\cdot x^2 + b\cdot x + c
$$

## 特殊符号

| 特殊符号 |                        |
| -------- | ---------------------- |
| 省略号   | `\dots`                |
| 右箭头   | `\rightarrow` 或 `to`  |
| 左箭头   | `\leftarrow` 或 `gets` |
| 花括号   | `\{a\}`                |
| 插入文字 | `\text{apple}`         |
| 空格     | `\quad`                |

* e.g. `\{cddc\} = \text{addple }\dots`

$$
\{cddc\} = \text{addple }\dots
$$

## 集合运算符

| 集合运算符  |                        |                          |
| ----------- | ---------------------- | ------------------------ |
| 属于        | `\in`                  | $\in$                    |
| 不属于      | `\not\in`              | $\not\in$                |
| 包含于      | `\subset`或`\subseteq` | $\subset$ 或 $\subseteq$ |
| 真包含于    | `\subsetneqq`          | $\subsetneqq$            |
| 不包含于    | `\not\subset`          | $\not\subset$            |
| 交          | `\cap`                 | $\cap$                   |
| 并          | `\cup`                 | $\cup$                   |
| 闭包        | `\overline`            | $\overline A$            |
| 差          | `\setminus`            | $A\setminus B$           |
| 实数集合    | `\mathbb{R}`           | $\mathbb{R}$             |
| 空集        | `\emptyset`            | $\emptyset$              |
| 集合中的`|` | `\mid`                 | $\mid$                   |
| 包含        | `\supset`              | $\supset$                |
| 真包含      | `\supsetneqq`          | $\supsetneqq$            |
| 不包含      | `\not\supset`          | $\not\supset$            |
| 补集        | `\complement`          | $\complement$            |
|             |                        |                          |
|             |                        |                          |
|             |                        |                          |
|             |                        |                          |
|             |                        |                          |
|             |                        |                          |

## 逻辑符号

|                       |                      |                            |                            |
| --------------------- | -------------------- | -------------------------- | -------------------------- |
| `\forall`$ \forall$​​   | `\exists`  $\exists$​ | `\therefore`  $\therefore$​ | `\implies`  $\implies$     |
|| `\nexists` $\nexists$​ | `\exist \exist$​      | `\because`  $\therefore$​   | `\impliedby`  $\impliedby$​​ ||
| `\wedge` $\wedge$ | `\vee` $\vee$  | `\to`  $\to$               | `\gets`  $\gets$           |
| `\iff`  $\iff$        | `\ni`  $\ni$         | `\not\ni`  $\not\ni$       | `\neg`  $\neg$             |





