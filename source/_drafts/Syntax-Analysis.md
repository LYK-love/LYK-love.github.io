---
title: Syntax Analysis
tags: Compilers Principles, Techniques, and Tools
categories: Compilers 
mathjax: true
---

Outline:

* Intro
* Context-Free Syntax
* Syntax Design
* Top - Down Syntax Analysis
* Down - Top Syntax Analysis
* LR Syntax Analysis: SLR
* LR Syntax Analysis: Stronger

<!--more-->

# Intro

*  语法分析器的作用：
  * 验证（词法分析器输出的）词法单元串可以由源语言的文法生成 
  * 报告语法错误
  * 从常见的错误中恢复
* 语法分析器类型：
  * 通用：效率太低
  * 自底向上
  * 自顶而下
    * 后两种方法中，总是从左向右扫描语法分析器的输入
* 语法错误的处理
  * 程序可能有不同层次的错误：
    * 词法错误：如标识符拼写错误
    * 语法错误：如花括号确实
    * 语义错误：如算子和操作数的类型不匹配
    * 逻辑错误： 这样的程序可能是well formed， 但没有正确反映程序员的意图
  * 语法分析器要处理语法错误
* 错误恢复策略
  * panic模式的恢复：一旦发现错误就不断丢弃输入中的符号，一次丢弃一个符号，直到找到`synchronizeing token`集合中的某个元素为止
    * `synchronizeing token`： 通常是界限符（`;`），在源程序中是清晰、无二义的
  * 短语层次的恢复: 发现错误后，在余下的输入上进行局部性纠正
  * 错误产生式： 加入能够产生错误的错误产生式，一旦该产生式被调用，语法分析器就能检查到预期的错误，，据此得到诊断信息
  * 全局纠正：效率太低

# Context-Free Syntax

*  上下文无关文法 (`CFG`) 包含四个部分

  * `terminal`:组成串的基本符号  ( == 词法单元名字)
  * `non-terminal`:表示串的集合的语法变量
    * 在程序设计语言中通常对应于某个程序构造,比如`stmt` (语句)
  * `start symbol`:某个被指定的`non-terminal`
    * 它对应的串的集合就是文法的语言
  *  `production`:描述将`terminal`和`non-terminal`组成串的方法
    *  `head` (左部) → `body` (右部)
    *  `head`是一个`non-terminal`,右部是一个符号串
    * 例子:`expression  → expression + term`

  * 符号约定：
    * 具有相同`head`的一组`production` $A \rarr \alpha_1, \dots, A \rarr \alpha_k$可以写作$A \rarr \alpha_1 | \alpha_2 | \dots | \alpha_k$, 我们把$\alpha_1 | \alpha_2 | \dots | \alpha_k$称作$A$的不同可选体
    * 第一个产生式的头就是开始符号

## derivation

* 推导：
  * 将待处理的串中的某个非终结符号替换为这个非终结符号的某个产生式的体
  * 从**开始符号**出发,不断进行上面的替换,就可以得到文法的不同**句型**
* 推导的正式定义
  * 如果A → γ是一个产生式,那么αAβ => αγβ
  * 最左 (右) 推导:α(β) 中**不包含**非终结符号
    * 总是选择每个句型的最左（右）非终结符
*  句型 (Sentential form)
  *  如果$S \Rightarrow^*  α$,那么α就是文法S的句型
  * 可能既包含非终结符号,又包含终结符号,也可以是空串
* 句子 (Sentence)
  *  文法的句子就是不包含非终结符号的句型
* 语言
  * 文法$G$的语言就是$G$的句子的集合,记为$L(G)$
  * $w$在$L(G)$中当且仅当$w$是$G$的句子,即$S$
* 推导的图形表示形式
  * 根结点的标号是文法的**开始符号**
    * 每个叶子结点的标号是非终结符号、终结符号或ε
    * 每个内部结点的标号是非终结符号
    * 每个内部结点表示某个产生式的一次应用
      * 结点的标号为产生式头,其子结点从左到右是产生式的体
* 树的叶子组成的**序列**是根的文法符号的一个句型
* 一棵语法分析树可对应多个推导序列
  * 但只有**唯一的最左推导及最右推导**
* 上下文无关文法比正则表达式的能力更强
* 任何正则语言都可以表示为上下文无关文法的语言
*  任何正则语言都必然有一个NFA,对于该NFA构造如下的上下文无关文法:
  *  对NFA的每个状态i,创建非终结符号Ai
  * 如果有i在输入a上到达j的转换,增加产生式Ai → aAj
  * 如果i在输入ε上到达j,那么增加产生式Ai → Aj
  * 如果i是一个接受状态,增加产生式Ai → ε
  * 如果i是开始状态,令Ai为所得文法的开始符号

# Syntax Design

* 文法能够描述程序设计语言的大部分语法
  * 但不是全部,比如,标识符的先声明后使用则无法用上下文无关文法描述
  * 因此语法分析器接受的语言是程序设计语言的**超集**; 必须通过语义分析来剔除一些符合文法、但不合法的程序

# Top - Down Syntax Analysis

#  Down - Top Syntax Analysis

# LR Syntax Analysis: SLR

# LR Syntax Analysis: Stronger

