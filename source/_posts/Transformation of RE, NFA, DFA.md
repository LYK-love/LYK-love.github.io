---
title: Transformation of RE, NFA, DFA
tags: Compilers
categories: Computer Science
mathjax: true
date: 2023-02-8 15:44:25
---

Outline:

* REGEX -> NFA
* NFA -> DFA
* Minimizing DFA
* DFA -> REGEX
* Prove DFA <=> REGEX

<!--more-->

# RE -> NFA

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

# Prove DFA <=> RE

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

  

