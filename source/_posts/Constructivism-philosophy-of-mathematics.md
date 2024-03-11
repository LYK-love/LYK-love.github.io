---
title: Constructivism (philosophy of mathematics)
tags:
  - Set Theory
  - Philosophy of Mathematics
categories: Mathematics
mathjax: true
date: 2023-11-04 02:04:16
---


结构主义(Constructivism)数学是一种数学哲学. 它折射出的是对于数学本质的思考以及对现有的以公理化集合论为基础的严谨但不适应人类直觉的数学体系的不满.

[->Sources: Intuitive mathematics - Marianne Freiberger](https://plus.maths.org/content/intuitionism)

<!--more-->

# Intro

[Source: wiki](https://en.wikipedia.org/wiki/Constructivism_(philosophy_of_mathematics))

In the [philosophy of mathematics](https://en.wikipedia.org/wiki/Philosophy_of_mathematics), **constructivism** asserts that it is necessary to find (or "construct") a specific  example of a mathematical object in order to prove that an example  exists. Contrastingly, in [classical mathematics](https://en.wikipedia.org/wiki/Classical_mathematics), one can prove the [existence](https://en.wikipedia.org/wiki/Existence) of a mathematical object without "finding" that object explicitly, by assuming its non-existence and then deriving a [contradiction](https://en.wikipedia.org/wiki/Contradiction) from that assumption. Such a [proof by contradiction](https://en.wikipedia.org/wiki/Proof_by_contradiction) might be called non-constructive, and a constructivist might reject it. The constructive viewpoint involves a verificational interpretation of  the [existential quantifier](https://en.wikipedia.org/wiki/Existential_quantifier), which is at odds with its classical interpretation.

# What is maths?

Brouwer's misgivings rested on his view on where mathematics comes from. Many mathematicians of the time (and of today) thought that **mathematics exists independently of humans in some kind of *[Platonic](https://en.wikipedia.org/wiki/Platonism)* realm of eternal truth, which we venture out to explore with our minds**. Another prominent school of the time, the *[formalists](https://en.wikipedia.org/wiki/Formalism_(philosophy_of_mathematics))*, had stripped mathematics of all intuition and turned it into a game of pure logic, which, so Brouwer thought, was devoid of meaning. 



In Brouwer's view maths was neither  independent of us,   nor an empty  game whose rules we can change at will. To him maths was a human  creation rooted in our intuition. Our perception of the passage of time, he thought, with one moment following on from the one before,  shapes  our  intuition of the natural numbers 1, 2, 3, etc, and of the infinity  they move towards. Along with other notable mathematicians, Brouwer  believed that the natural numbers formed the basis of all the  mathematics we have created. Therefore, all mathematical objects and  arguments should be regarded as mental constructions we build in the  privacy of our own minds, based on our intuition. Logic, according to  Brouwer, wasn't the essence of these private ideas, but it's what we  use, together with language, to communicate about them. 

# Features

构造主义数学拒绝使用无穷对象, 也不适用排中律.

# Non-constructive proofs

虽然看起来深奥, 但 Brouwer  的直觉主义观点对数学有着很深刻的影响. 如果数学的研究对象是心智结构，那么证明某个特定数学对象的存在性的唯一方法就是用心智想出一种构造方式，根据  Brouwer  的说法，“人类心智之外不存在数学实义”，如果你不能在脑海中构建一个对象，那么它就缺乏真实性。然而，许多数学证明并没有做到这一点: **它们通过逻辑的必然性表明了某些东西存在，但却没有告诉你如何找到它**.

这种非构造性的证明就像魔术一样，但也会让你觉得被欺骗了. 一个特别巧妙的例子是证明存在$a,b$ 两个无理数使得
$$
a^{b}
$$
是有理数. 



我们从考虑数字
$$
\sqrt 2 ^ {\sqrt 2}
$$
开始. 

1. 如果$\sqrt 2 ^ {\sqrt 2}$是有理数, 那么令$a=\sqrt 2, b=\sqrt 2$ (因为$\sqrt 2$是无理数), 我们就找到了满足要求的两个无理数. 

2. 如果$\sqrt 2 ^ {\sqrt 2}$是无理数, 令$a=\sqrt 2 ^ {\sqrt 2}, b=\sqrt 2$ 那么, 
   $$
   𝑎^𝑏=(\sqrt 2 ^ {\sqrt 2})^ {\sqrt 2} = \sqrt 2 ^ {\sqrt 2 \times \sqrt 2} = \sqrt 2 ^ { 2} = 2
   $$
   是有理数, 同样找到了满足要求的两个无理数.



尽管这个证明很优雅, 但是它不能告诉我们数字$a, b$到底是什么. 我们得到了两对数字:

1. $a=\sqrt 2, b=\sqrt 2$ 
2. $a=\sqrt 2 ^ {\sqrt 2}, b=\sqrt 2$ 

但哪个才是符合题目要求的$a, b$? 这个证明方式无法告诉我们答案.

# The Law of excluded middle

理论部分可以看[Lecture Notes on Constructive Logic: Overview](http://www.cs.cmu.edu/~crary/317-f18/lectures/01-overview.pdf).



The Law of excluded middle(排中律)可以用如下形式表述:
$$
(P \and ^ \neg P) = \text{True}
$$
假设$P$是一个命题（如"$𝑥$是有理数"), $\neg P$是其否命题（如 “*𝑥* 是无理数”）. 在经典逻辑中，$(p \and ^¬p)$（"要么$x$是有理数, 要么$x$是无理数"）这个命题总是正确的, **即使你不知道两个中哪一个是正确的**.

这是合理的, 如果其中某个不正确, 那么另一个一定是正确的, 但这让人很不满意. 如果我告诉你, 要么我明天来看你, 要么我不来, 你是不能责怪我撒谎的, 但你却会很生气.

排中律为数学家们提供了他们几乎每天都使用的基础技巧：**反证法**. 

反证法是说: 通过证明 $\neg P$是假的来说明原命题$P$是真的, 但这没有从正面构造一个明确的证明. 一个著名的例子就是对$\sqrt 2$是无理数的[证明](https://plus.maths.org/content/maths-minute-square-root-2-irrational).

对这个命题，拒绝排中律的证明思路和许多通过反证法得到的证明, 困扰并一直困扰着相当多的数学家.

# Constructivism v.s. Set Theory

[Source: 谈谈数学里的构造主义（constructivism）、直觉主义（intuitionism）和数学基础](https://zhuanlan.zhihu.com/p/22389755)

实际上，高中或者大学的某些数学之所以对一部分人困难，就是因为我们就放弃了构造主义！

首先，高中的数学和初中是很不一样的——并不是说初中研究了线性函数和二次函数，高中就研究三次四次函数，大学再研究五次六次函数。回头看来，两者最大的区别是，用的数学基础发生了重大变化——初中的数学，无所谓基础，所有的研究对象都是实数轴上的一次或者二次函数，所有的函数都可以在计算器上摁出来，其实在学生脑子里默默建构了构造主义的习惯。而高中开始，数学就慢慢地建立在集合论的基础上了。

集合论带来的，是非构造性。两个集合之间的映射, 定义起来并不平凡：

给定集合$X,Y$, 他们之间的一个映射是一个关系, 对于任意的$x \in X, $有唯一的$f(x) \in Y$, 这个关系记作
$$
f: X \rightarrow Y
$$


换句话讲, 映射$f: X \rightarrow Y$对应的是的一个满足如下条件的子集$R$:

$\forall x \in X$, 存在唯一的$y \in Y$, 使得$(x,y) \in R$.



这说明一个思想: 在集合论当中, **数学对象不是构造出来的, 而只是描述一个性质, 然后它可以被用来搜集对应的数学对象.** 也就是说啥, 集合论中的函数不一定能被写出来. 

真正理解这个定义的人，难免[痛恨](https://link.zhihu.com/?target=http%3A//mathoverflow.net/a/2367/82513) “一个映射/函数就是一个公式” 的常见误解（鄙人就曾经是痛恨者中的一员）。回过头来看，这种误解其实代表着构造主义和集合论的冲突。按照集合论的定义，实数轴上的实值函数，其实是$\mathbb R \times \mathbb R$的一类的子集，对每个 $x \in \mathbb R$“分配” 了一个值$y \in \mathbb R$ —— 有没有让人窥见选择公理的影子？大多数这样的函数，都是 “不可计算” 的。

就是这一点点非构造主义，以奇怪的形式把很多人绊倒在构造在集合论基础上的现代数学的门槛上。门槛本身在哪里并不重要——可能在集合论，也可能在数学分析，或者实变函数论，但归根结底都是那一点点非构造主义。

类似的例子还有抽象代数。很多人在初次学习的时候本能地拒绝 “一个群是一个集合加上一个满足某些条件的二元运算”  这样的抽象定义，但是能接受矩阵群的概念，本质上也是非构造主义在作祟。用面向对象编程的语言来说，矩阵和一个抽象的集合的元素的区别在于，矩阵群自带元素的 constructor 和 methods. 但是用抽象的集合给出的群，就好像只带着 virtual methods 的 object,  会被一些人脑子里的编译器拒绝。
