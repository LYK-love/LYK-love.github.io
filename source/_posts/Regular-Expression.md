---
title: Regular Expression
tags: Compilers
categories: Computer Science
mathjax: true
date: 2022-09-10 23:58:50
---


Outline:

* Intro
* Def
* Extension

<!--more-->

# Intro

- 每个正则表达式$r$可以描述一个语言$L(r)$, 也即其定义的正则集合( Regular Set)

  - 例如, C语言标识符的语言, 可以用如下正则表达式来表示:
    $$
    \mathrm{letter} \_ (\mathrm{letter}|\mathrm{digit})*
    $$

* 正则表达式不仅是数学工具, 也被各种编程语言所支持. 绝大部分语言的正则语法都差不多

# Def

给定字母表 $\sum$,  $\sum$ 上的正则表达式由且仅由以下规则定义:

1. $\epsilon$是正则表达式,它描述了语言$L(\epsilon) = \{ \epsilon \}$
2. $\forall a \in \sum$ , $a$是正则表达式, 它描述了语言$L(a) = \{ a \}$
3. 选择: $(r) | (s)$ 是正则表达式, $L((r) | (s))=L(r) \cup L(s)$
4. 连接: $(r)(s)$ 是正则表达式, $L((r)(s))=L(r)L(s)$
5. 闭包: $(r)^*$ 是正则表达式 , $L((r)^*)=(L(r))^*$
6. 括号: $(r)$ 是正则表达式, $L((r))=L(r)$



运算的优先级: $*$ > 连接符 > $|$

* $(a)|((b)*(c))$可以改写为 $a|b*c$

## Example

C语言的标识符集合:

* $\mathrm{letter}$: $A|B|\dots|Z|a|b|\dots|z|\_ $
* $\mathrm{digit}$: $0|1|\dots|9$
* $\mathrm{id}$: $\mathrm{letter} \_ (\mathrm{letter} \_ |\mathrm{digit})^*$



Pascal无符号数集合, 例如:1946, 11.28, 63.6E8, 1.99E−6

* $\mathrm{digit}$: $0|1|\dots|9$
* $\mathrm{digits}$: $\mathrm{digit} \ \mathrm{digit}^*$
* $\mathrm{optional \_ fraction}$: $. \mathrm{digits} | \epsilon$
* $\mathrm{optional \_ exponent}$: $(\mathrm{E} ( + | − | \epsilon ) \ \mathrm{digits} ) \ | \ \epsilon$ 
* $\mathrm{num}$: $\mathrm{optional \_ fraction}\  \mathrm{optional \_ exponent}$

# Extension

## 扩展正则

为了方便, 可以用现有的正则来匹配一些常见的语言:

* `\d`: 匹配一个数字
  * `'00\d'`可以匹配`'007'`，但无法匹配`'00A'`；
  * `'\d\d\d'`可以匹配`'010'`；
* `\w`: 匹配一个字母或数字.
  * `'\w\w\d'`可以匹配`'py3'`
* `.`: 匹配任意字符.
  - `'py.'`可以匹配`'pyc'`、`'pyo'`、`'py!'`...
* `\s`可以匹配一个空格(也包括Tab等空白符), 所以`\s+`表示至少有一个空格, 例如匹配`' '`，`' '`等；
* `\ws` = `(blank | tab | newline)+`

## 扩展运算符

* 一个或多个: $r^+$ , 等价于$rr^*$
* 零个或一个: $r?$ 等价于$\epsilon | r$
* 字符类: 
  * 字符`c`的字面值: `\c`
    * 只写`c`会被认为是一个正则
  * $[abc]$等价于$a|b|c$ , 即字符串$abc$中的任意一个字符
  * $[a - z]$等价于$a|b|\dots|z$
    * `[0-9a-zA-Z\_]`: 匹配一个数字, 字母或者下划线
    * `[0-9a-zA-Z\_]+`: 匹配至少由一个数字, 字母或者下划线组成的字符串，比如`'a100'`, `'0_Z'`, `'Py3000'`等等
    * `[a-zA-Z\_][0-9a-zA-Z\_]*`: 匹配由字母或下划线开头. 后接任意个由一个数字、字母或者下划线组成的字符串，也就是Python合法的变量
  * `^s`: 不在串$s$中的任意一个字符
* $r\{n\}$: n个$r$
  * `\d{3}`表示匹配3个数字, 例如`'010'`
* $r\{m,n\}$: 最少m个, 最多n个$r$的连接
  * `\d{3,8}`: 匹配3-8个数字
* `^`: 行的开头
  * `^\d`表示必须以数字开头.
* `$`表示行的结束
  *  `\d$`表示必须以数字结束.
  *  你可能注意到了, `py`也可以匹配`'python'`, 但是加上`^py$`就变成了整行匹配, 就只能匹配`'py'`了.

## Example

前面的例子的简化表示:

* $\mathrm{letter}$: $[\mathrm{A}-\mathrm{Z} \mathrm{a}-\mathrm{z}] $
* $\mathrm{digit}$: $[0-9]$
* $\mathrm{id}$: $\mathrm{letter} \_ (\mathrm{letter} \_ |\mathrm{digit})^*$



* $\mathrm{digit}$: $[0-9]$
* $\mathrm{digits}$: $\mathrm{digit}?$
* $\mathrm{num}$: $\mathrm{digits} \ (. \mathrm{digits})? \ (\mathrm{E}[+-]? \ \mathrm{digits})?$



