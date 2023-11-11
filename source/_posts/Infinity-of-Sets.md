---
title: Infinity of Sets
tags:
  - Set Theory
  - Measure Theory
categories: Mathematics
mathjax: true
date: 2023-11-03 23:52:21
---


在数学中, 无穷和极限是相当令人困惑的概念. 

本文介绍"无穷(infinity)"这一概念, "无穷集合"所具有的反常性质, 以及现代集合公理系统(ZFC)对于无穷集合的处理.

这也引申出measure theory(测度论)这一领域的动机: 在ZFC系统下, 在处理无穷集合时, 传统的基于直觉的测度定义不再适用. 现代的测度理论首先规定"可测集合(measurable sets)"这一概念, 对于可测集合进行其测度的讨论.

最后, 本文给出两个例子, 即大名鼎鼎的Hilbert's paradox of the Grand Hotel和Banach–Tarski Paradox. 以揭示两个事实:

1. 无穷集合具备和有穷集合不同的性质, 有些性质甚至是相当反直觉的.
2. ZFC公理系统(包括选择公理Axiom of choice)会推导出一些反直觉的结论.

Ref: [An Introduction to Measure Theory - Terence Tao](https://terrytao.files.wordpress.com/2012/12/gsm-126-tao5-measure-book.pdf)

<!--more-->

# The Problem of Measure

One of the most fundamental concepts in Euclidean geometry is that of the measure $m(E)$ of a solid body $E$ in one or more dimensions. 

In one, two, and three dimensions, we refer to this measure as the **length, area, or volume** of $E$ respectively. 

In the classical approach to geometry, the measure of a body was often computed by partitioning that body into finitely many components, moving around each component by a rigid motion (e.g. a translation or rotation), and then reassembling those components to form a simpler body which presumably has the same area. 

One could also obtain lower and upper bounds on the measure of a body by computing the measure of some inscribed or circumscribed body; this ancient idea goes all the way back to the work of Archimedes at least. Such arguments **can be justified by an appeal to geometric intuition**, or simply by postulating the existence of a measure $m(E)$ that can be assigned to all solid bodies $E$, and which obeys a collection of geometrically reasonable axioms. One can also justify the concept of measure on “physical” or “reductionistic” grounds, viewing the measure of a macroscopic body as the sum of the measures of its microscopic components.

With the advent of analytic geometry, however, Euclidean geometry became reinterpreted as the study of Cartesian products $R^d$ of the real line $R$.

Using this analytic foundation rather than the classical geometrical one, it was no longer intuitively obvious how to define the measure $m(E)$ of a general[^1] subset $E$ of $R^d$; we will refer to this (somewhat vaguely defined) problem of **writing down the “correct” definition of measure** as **the problem of measure**.

对一, 二, 三维物体的测度, 我们有很符合直觉和还原论的定义. 但是问题一旦涉及到高维($R^d$), 直觉就会break down. 特别是无穷这一概念的引入, 会造成理解上的巨大困难.

从直觉上看, the physical intuition of defining the measure of a body $E$ to be **the sum of the measure of its component “atoms” runs into an immediate problem**: a typical solid body would consist of an infinite (and uncountable) number of points, each of which has a measure of zero; and the product $∞ · 0$ is indeterminate. 

To make matters worse, **two bodies that have exactly the same number of points, need not have the same measure.** 

For instance, in one dimension, the intervals $A := [0, 1]$ and $B := [0, 2]$ are in one-to-one correspondence (using the bijection $x → 2x$ from $A$ to $B$), but of course $B$ is twice as long as $A$. So one can disassemble A into an uncountable number of points and reassemble them to form a set of twice the length.

Of course, one can point to the infinite (and uncountable) number of components in this disassembly as being the cause of this breakdown of intuition, and restrict attention to just **finite partitions**. But one still runs into trouble here for a number of reasons, the most striking of which is the **Banach-Tarski paradox**, which shows that the unit ball $B := {(x,y,z) ∈ R^3 : x^2 +y^2 +z^2 ≤ 1}$ in three dimensions can be disassembled into a finite number of pieces (in fact, just five pieces suffice), which can then be reassembled (after translating and rotating each of the pieces) to form two disjoint copies of the ball $B$.

现有的ZFC公理系统包括了选择公理, 这会推导出一些违背直觉的结果. 例如Banach-Tarski paradox. 不过, 这样病态(pathological)的集合在实际应用(即使是数学上的应用)也很少被涉及.

因此我们可以定义"可测集合(measurable sets)"这一概念, 规定哪些集合是可测的, 然后只对可测集合应用测度理论.



The problem of measure then divides into several subproblems:

1. What does it mean for a subset E of Rd to be measurable?
2. If a set E is measurable, how does one define its measure?
3.  What nice properties or axioms does measure (or the con- cept of measurability) obey?
4. Are “ordinary” sets such as cubes, balls, polyhedra, etc. measurable?
5. Does the measure of an “ordinary” set equal the “naive geo- metric measure” of such sets? (e.g. is the measure of an a × b rectangle equal to ab?)

These questions are somewhat open-ended in formulation, and there is no unique answer to them; in particular, one can expand the class of measurable sets at the expense of losing one or more nice properties of measure in the process (e.g. finite or countable addi- tivity, translation invariance, or rotation invariance). However, there are two basic answers which, between them, suffice for most applica- tions. The first is the concept of Jordan measure (or Jordan content) of a Jordan measurable set, which is a concept closely related to that of the Riemann integral (or Darboux integral). This concept is el- ementary enough to be systematically studied in an undergraduate analysis course, and suffices for measuring most of the “ordinary” sets (e.g. the area under the graph of a continuous function) in many branches of mathematics. However, when one turns to the type of sets that arise in analysis, and in particular those sets that arise as limits (in various senses) of other sets, it turns out that the Jordan concept of measurability is not quite adequate, and must be extended to the more general notion of Lebesgue measurability, with the corre- sponding notion of Lebesgue measure that extends Jordan measure. With the Lebesgue theory (which can be viewed as a completion of the Jordan-Darboux-Riemann theory), one keeps almost all of the de- sirable properties of Jordan measure, but with the crucial additional property that many features of the Lebesgue theory are preserved un- der limits (as exemplified in the fundamental convergence theorems of the Lebesgue theory, such as the monotone convergence theorem (Theorem 1.4.44) and the dominated convergence theorem (Theorem 1.4.49), which do not hold in the Jordan-Darboux-Riemann setting).

As such, they are particularly well suited3 for applications in analysis, where limits of functions or sets arise all the time.

#  Extended real numbers

在测度论中, 某些集合会具有无穷的测度, 为了方便处理, 我们定义扩展的实数域$\overline{\mathbb{R}}$. 

It is convenient to use the extended real numbers
$$
\overline{\mathbb{R}}=\{-\infty\} \cup \mathbb{R} \cup\{\infty\} .
$$

**This allows us**, for example, to talk about sets with **infinite measure** or non-negative functions with infinite integral. 

The extended real numbers are totally ordered in the obvious way: $\infty$ is the largest element, $-\infty$ is the smallest element, and real numbers are ordered as in $\mathbb{R}$. 

我们定义$\overline{\mathbb{R}}$上的运算规则:

1. 加法和乘法均满足交换律和结合律(law of commutation and association).
   $$
   +∞ + x = x + +∞ = +∞ \\
   +∞ · x = x · +∞ = +∞ \\
   +∞ + x · y = +∞ + (x · y) = +∞
   $$

2. 无穷乘以0等于0:
   $$
   +∞ · 0 = 0 · +∞ = 0
   $$

3. 加法和乘法在涉及无穷时不满足消去律(law of cancellation). $+∞ − +∞$ and $+∞/ + ∞$ are indeterminate. So we cannot deduce $x = y$ from $+∞+x = +∞+y$ or from $+∞·x = +∞·y$. This is related to the fact that the forms (one cannot assign a value to them without breaking a lot of the rules of algebra).



# Hilbert's paradox of the Grand Hotel

[Hilbert's paradox of the Grand Hotel](https://en.wikipedia.org/wiki/Hilbert%27s_paradox_of_the_Grand_Hotel)

> Hilbert imagines a hypothetical hotel with rooms numbered 1, 2, 3, and so on with no upper limit. This is called a [countably infinite](https://en.wikipedia.org/wiki/Countable_set) number of rooms. Initially every room is occupied, and yet new visitors arrive, each expecting their own room. A normal, finite hotel could not accommodate new guests once every room is full. However, it can be  shown that the existing guests and newcomers — even an infinite number  of them — can each have their own room in the infinite hotel.

Hilbert's paradox of the Grand Hotel揭露了这样一个事实: 无穷集合的性质和有穷集合并不相同. 无穷集合会具有一些**与我们直觉相悖的性质.**

# Banach–Tarski Paradox

Banach–Tarski Paradox的介绍可以看[这个视频](https://www.youtube.com/watch?v=s86-Z-CbaHA).

[Banach-Tarski and the Paradox of Infinite Cloning](https://www.quantamagazine.org/how-a-mathematical-paradox-allows-infinite-cloning-20210826/)



不过, The Banach–Tarski Paradox是选择公理的结果. 虽然违背直觉, 但是不采用其他选择公理的其他系统会推导出更荒谬的结果, 因此一般来说, 我们还是承认选择公理.

[^1]: One can also pose the problem of measure on other domains than Euclidean space, such as a Riemannian manifold, but we will focus on the Euclidean case here for simplicity, and refer to any text on Riemannian geometry for a treatment of integration on manifolds.
