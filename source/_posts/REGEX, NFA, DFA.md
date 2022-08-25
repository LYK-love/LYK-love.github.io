---
title: REGEX, NFA, DFA
tags: Compilers
categories: Computer Science
mathjax: true
---

Outline:

* Def
* Common REGEX Regulation
* REGEX -> NFA
* NFA -> DFA
* Minimizing DFA
* DFA -> REGEX
* Prove DFA <=> REGEX

<!--more-->

# Def

## 正则

给定字母表 Σ, Σ 上的正则表达式由且仅由以下规则定义:

1. ε 是正则表达式;
2. ∀a ∈ Σ, a 是正则表达式;
3.  如果 s 是正则表达式, 则 (s) 是正则表达式;
4. 如果 s 与 t 是正则表达式, 则 s|t, st, s∗ 也是正则表达式。

## NFA

NFA( 不确定性有限状态机 ) 是一个五元组 A = (Σ, $S$, $s_0$ , δ, F ):

1. 字母表  Σ (ε $\notin$ Σ)

2. 有穷的状态集合 S

3. 唯一的初始状态 $s_0 \in S$ 
4. 状态转移函数 δ
   * $δ : S × (Σ ∪ {ε}) → 2^S$
   * 这里$2^S$定义为$S$的幂集
5. 接受状态集合 F ⊆ S

## DFA

DFA( 确定性有限状态机 )是一个五元组 A = (Σ, $S$, $s_0$ , δ, F ):

1. 字母表 Σ (ε $\notin$ Σ)
2. 有穷的状态集合 S
3. 唯一的初始状态 $s_0 \in S$ 
4. 状态转移函数 δ
5. 接受状态集合 F ⊆ $S$

* 约定: 所有没有对应出边的字符默认指向一个不存在的 `dead state`

# Common REGEX Regulation

 大部分语言的正则语法都差不多, 这里以Python中的为例.

## 精确匹配

* `\d`: 匹配一个数字
  * `'00\d'`可以匹配`'007'`，但无法匹配`'00A'`；
  * `'\d\d\d'`可以匹配`'010'`；
* `\w`: 匹配一个字母或数字.
  * `'\w\w\d'`可以匹配`'py3'`
* `.`: 匹配任意字符.
  - `'py.'`可以匹配`'pyc'`、`'pyo'`、`'py!'`...

---

## 匹配变长字符

* `*`: 任意个字符（包括0个).
* `+`: 至少一个字符
* `?`: 0个或1个字符.
* `{n}`: n个字符，用`{n,m}`表示n-m个字符



来看一个复杂的例子：`\d{3}\s+\d{3,8}`。

我们来从左到右解读一下：

1. `\d{3}`表示匹配3个数字，例如`'010'`；
2. `\s`可以匹配一个空格（也包括Tab等空白符），所以`\s+`表示至少有一个空格，例如匹配`' '`，`' '`等；
3. `\d{3,8}`表示3-8个数字，例如`'1234567'`。

综合起来，上面的正则表达式可以匹配以任意个空格隔开的带区号的电话号码。

如果要匹配`'010-12345'`这样的号码呢？由于`'-'`是特殊字符，在大部分语言的正则表达式中，要用`'\'`转义，所以，上面的正则是`\d{3}\-\d{3,8}`。

但是，仍然无法匹配`'010 - 12345'`，因为带有空格。所以我们需要更复杂的匹配方式。

---

## 范围匹配

要做更精确地匹配，可以用`[]`表示范围.

- `[0-9a-zA-Z\_]`: 匹配一个数字, 字母或者下划线
- `[0-9a-zA-Z\_]+`: 匹配至少由一个数字、字母或者下划线组成的字符串，比如`'a100'`, `'0_Z'`, `'Py3000'`等等
- `[a-zA-Z\_][0-9a-zA-Z\_]*`: 匹配由字母或下划线开头. 后接任意个由一个数字、字母或者下划线组成的字符串，也就是Python合法的变量；
- `[a-zA-Z\_][0-9a-zA-Z\_]{0, 19}`: 限制了变量的长度是1-20个字符（前面1个字符+后面最多19个字符）

* `A|B`: 匹配A或B
  * 所以`(P|p)ython`可以匹配`'Python'`或者`'python'`

* `^`: 行的开头
  * `^\d`表示必须以数字开头.

* `$`表示行的结束
  *  `\d$`表示必须以数字结束.
  * 你可能注意到了, `py`也可以匹配`'python'`, 但是加上`^py$`就变成了整行匹配, 就只能匹配`'py'`了.



# REGEX -> NFA

[ref](https://blog.csdn.net/weixin_44691608/article/details/110195743)

使用Thompson 构造法, 基本思想是 **按结构归纳**

* 对正则定义的每个规则，分别建立一个图的映射，因此所有正则表达式都可以表现为这些子图的组合

# NFA -> DFA

用子集构造法

[ref](https://blog.csdn.net/weixin_44691608/article/details/110213913)

```c
Subset-Construction(NFA)
    let Dtran be a table
    DFA_States = {ε-closure(NFA.s0)}  # DFA 状态集合的初始状态为 NFA 初始状态的闭包，并且未标记
    while (exist T in DFA_States not marked) { # 存在未标记的 DFA 状态
        mark T  # 标记 T，表示查过 T 状态的所有后续状态了
        for (a in Σ) { 
            Tc = ε-closure(move(T, a)) # 找到所有输入字符对应的下一个状态
            if (Tc not in DFA_States) { # 将状态加入到 DFA_States
                push Tc in DFA_States & unmarked Tc
            }# 如果新状态已经在Dtran中，那么不会添加新状态，只会添加[T, a]
            Dtran[T, a] = Tc
        }
    }
    return Dtran

```

简言之，根据连通性不断添加新状态，直到所有状态成为闭包



# Minimizing DFA

[ref](https://blog.csdn.net/weixin_44691608/article/details/110440659)

```C
Min-DFA(Dtran)
    let U = {S\F, F} # 初始的等价类有两个组，分别是非终止状态和终止状态
    for (G in U) { # 对等价类中每个组做划分
        while (G can be divided) {
            g1, g2, g3, ... = divide(G)
            remove G from U
            add g1, g2, g3, ... into U
        }
    }

```

1. 首先将上面的 DFA 分为非终止状态和终止状态两组，然后对每一组进行检查是否能够再做划分，若可则对划分后的组再划分，直到不可再划分
2. 最后根据划分后的组重建 Dtran 表并重绘 DFA 图

* `不可划分`：

  若对于组内所有状态，对于所有输入都有相同的输出状态，则称该组`不可再被划分`。

# Prove DFA <=> REGEX

验证DFA和其转化出的REGEX的等价性, 使用Kleene闭包

[ref](https://blog.csdn.net/weixin_44691608/article/details/110440659)

* 符号归约：

  假设有向图中节点编号为 $0$(初始状态)到 $n − 1$

  * $R_{ij}^k$ : 从节点 i 到节点 j、且中间节点编号不大于k的所有路径
  * $R_{ij}^{-1}$: 从节点 i 到节点 j、且不经过中间节点的所有路径
  * $\empty$: 路径不可达， 我们有 $\empty$ r = r $\empty$= $\empty$ 和 $\empty$|r = r
  * $\epsilon$: 空路径，即状态不发生变化的边（回到同一状态）

* Kleene闭包： $R_{ij}^{k} = R_{ij}^{k-1} (R_{ij}^{k})^* R_{ij}^{k-1} | R_{ij}^{k-1} $ ( 就是Floyd算法 )

* 步骤：

  * 动态规划思想，从$k=-1$开始不断迭代，直到有$R_{ij}^{n-1}$，其中 $i$ 和 $j$ 是起点和终点
  *  验证结果是否与原来的正则等价

  

