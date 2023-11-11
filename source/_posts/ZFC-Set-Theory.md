---
title: ZFC Set Theory
tags:
  - Set Theory
categories: Mathematics
mathjax: true
date: 2023-11-04 01:13:06
---

This post introduces set theory. The naive theory encountered some paradoxes during 19 century. As a result, people created axiomatic set theories. 

Among them, *ZFC* is the basic axiom system for modern (2000) set theory.

<!--more-->

# Set Theory

[Source: wiki](https://en.wikipedia.org/wiki/Set_theory)

**Set theory** is the branch of [mathematical logic](https://en.wikipedia.org/wiki/Mathematical_logic) that studies [sets](https://en.wikipedia.org/wiki/Set_(mathematics)), which can be informally described as collections of objects. Although  objects of any kind can be collected into a set, set theory, as a branch of [mathematics](https://en.wikipedia.org/wiki/Mathematics), is mostly concerned with those that are relevant to mathematics as a whole.

The modern study of set theory was initiated by the German mathematicians [Richard Dedekind](https://en.wikipedia.org/wiki/Richard_Dedekind) and [Georg Cantor](https://en.wikipedia.org/wiki/Georg_Cantor) in the 1870s. In particular, Georg Cantor is commonly considered the  founder of set theory. The non-formalized systems investigated during  this early stage go under the name of *[naive set theory](https://en.wikipedia.org/wiki/Naive_set_theory)*. After the discovery of [paradoxes](https://en.wikipedia.org/wiki/Paradoxes_of_set_theory) within naive set theory (such as [Russell's paradox](https://en.wikipedia.org/wiki/Russell's_paradox), [Cantor's paradox](https://en.wikipedia.org/wiki/Cantor's_paradox) and the [Burali-Forti paradox](https://en.wikipedia.org/wiki/Burali-Forti_paradox)), various [axiomatic systems](https://en.wikipedia.org/wiki/Axiomatic_system) were proposed in the early twentieth century, of which [Zermelo–Fraenkel set theory](https://en.wikipedia.org/wiki/Zermelo–Fraenkel_set_theory) (with or without the [axiom of choice](https://en.wikipedia.org/wiki/Axiom_of_choice)) is still the best-known and most studied.

Set theory is commonly employed as a foundational system for the  whole of mathematics, particularly in the form of Zermelo–Fraenkel set  theory with the axiom of choice.[[1\]](https://en.wikipedia.org/wiki/Set_theory#cite_note-FOOTNOTEKunen1980[httpsarchiveorgdetailssettheoryintrodu0000kunepagen13mode2up_xi]-1) Besides its foundational role, set theory also provides the framework to develop a mathematical theory of [infinity](https://en.wikipedia.org/wiki/Infinity), and has various applications in [computer science](https://en.wikipedia.org/wiki/Computer_science) (such as in the theory of [relational algebra](https://en.wikipedia.org/wiki/Relational_algebra)), [philosophy](https://en.wikipedia.org/wiki/Philosophy) and [formal semantics](https://en.wikipedia.org/wiki/Semantics_(computer_science)). Its foundational appeal, together with its [paradoxes](https://en.wikipedia.org/wiki/Paradoxes), its implications for the concept of infinity and its multiple  applications, have made set theory an area of major interest for [logicians](https://en.wikipedia.org/wiki/Logic) and [philosophers of mathematics](https://en.wikipedia.org/wiki/Philosophy_of_mathematics). Contemporary research into set theory covers a vast array of topics, ranging from the structure of the [real number](https://en.wikipedia.org/wiki/Real_number) line to the study of the [consistency](https://en.wikipedia.org/wiki/Consistency) of [large cardinals](https://en.wikipedia.org/wiki/Large_cardinal).



# Definition of Set

[Source: wiki](https://en.wikipedia.org/wiki/Set_(mathematics))

A **set** is the [mathematical model](https://en.wikipedia.org/wiki/Mathematical_model) for a collection of different things; a set contains *[elements](https://en.wikipedia.org/wiki/Element_(mathematics))* or *members*, which can be [mathematical objects](https://en.wikipedia.org/wiki/Mathematical_object) of any kind: numbers, symbols, points in space, lines, other geometrical shapes, variables, or even other sets. 

* The set with no element is the [empty set](https://en.wikipedia.org/wiki/Empty_set); a set with a single element is a [singleton](https://en.wikipedia.org/wiki/Singleton_(mathematics)).  
* A set may have a finite number of elements or be an [infinite set](https://en.wikipedia.org/wiki/Infinite_set). 

**Sets are uniquely characterized by their elements;** this means that two sets that have precisely the same elements are [equal](https://en.wikipedia.org/wiki/Equality_(mathematics)) (they are the same set).This property is called [extensionality](https://en.wikipedia.org/wiki/Axiom_of_extensionality). In particular, this implies that there is only one empty set.

Sets are ubiquitous in modern mathematics. Indeed, [set theory](https://en.wikipedia.org/wiki/Set_theory), more specifically [Zermelo–Fraenkel set theory](https://en.wikipedia.org/wiki/Zermelo–Fraenkel_set_theory), has been the standard way to provide rigorous [foundations](https://en.wikipedia.org/wiki/Foundations_of_mathematics) for all branches of mathematics since the first half of the 20th century.



# Naive Set Theory

[Source: wiki](https://en.wikipedia.org/wiki/Naive_set_theory)

**Naive set theory** is any of several theories of sets used in the discussion of the [foundations of mathematics](https://en.wikipedia.org/wiki/Foundations_of_mathematics). Unlike [axiomatic set theories](https://en.wikipedia.org/wiki/Set_theory#Axiomatic_set_theory), which are defined using [formal logic](https://en.wikipedia.org/wiki/Mathematical_logic#Formal_logical_systems), naive set theory is defined informally, in [natural language](https://en.wikipedia.org/wiki/Natural_language). 

朴素集合论是通过自然语言定义的, 而不是通过严谨的公理系统.

朴素集合论认为, 集合就是所有满足性质P(在该性质已经给定的情况下)的所有元素x所组成的集合. 也就是说一个集合S是根据一个性质P来定义的.



罗素悖论: 我有一个集合, 这个集合是由所有不属于它的元素构成的, 那这个集合是否存在？
$$
X = \{x | x \notin X\}
$$


理论上来说这个集合是不能存在的, 因为它要是存在, 那X的元素到底属不属于X?

罗素悖论证明了**不是所有的集合都可以存在**, 因此有必要建立公理化的集合论.

# Axiomatic Set Theory

[->Source](https://zh.wikipedia.org/wiki/%E5%85%AC%E7%90%86%E5%8C%96%E9%9B%86%E5%90%88%E8%AE%BA)

在[數學](https://zh.wikipedia.org/wiki/數學)中，**公理化集合论**是[集合論](https://zh.wikipedia.org/wiki/集合論)透過建立[一階邏輯](https://zh.wikipedia.org/wiki/一階邏輯)的嚴謹重整，以解決[樸素集合論](https://zh.wikipedia.org/wiki/朴素集合论)中出現的[悖論](https://zh.wikipedia.org/wiki/悖論)。集合論的基礎主要由[德國](https://zh.wikipedia.org/wiki/德國)[數學家](https://zh.wikipedia.org/wiki/數學家)[格奧爾格·康托爾](https://zh.wikipedia.org/wiki/格奥尔格·康托尔)在19世紀末建立。

公理化集合論**不直接定義集合和集合成員, 而是先規範可以描述其性質的一些公理.** 

# ZFC

ZFC = *Zermelo–Fraenkel set theory with the axiom of choice*.

ZFC(Zermelo–Fraenkel set theory with the axiom of choice) is the basic axiom system for modern (2000) set theory and is the most common [foundation of mathematics](https://en.wikipedia.org/wiki/Foundations_of_mathematics).

It's proposed in the early twentieth century in order to formulate a [theory of sets](https://en.wikipedia.org/wiki/Theory_of_sets) free of paradoxes such as [Russell's paradox](https://en.wikipedia.org/wiki/Russell's_paradox).

ZFC就是向ZF增加[选择公理](https://zh.wikipedia.org/wiki/选择公理). 选择公理曾饱受争议，因为[选择函数](https://zh.wikipedia.org/wiki/选择函数)的存在性是非构造性的；选择公理确立了选择函数的存在，而不说明如何构造这些函数。所以使用选择公理构造的一些集合，尽管可以证明其存在，但可能无法详细、描述性地构造出。因此，当一个结论依赖于选择公理时，有时会被明确地指出.



ZFC公理系统承认极限的存在, 承认选择公理, 承认排中律.

ZFC一般由一阶逻辑写出, 实际上包含了[无穷](https://zh.wikipedia.org/wiki/无穷)多个公理, 因为替代公理(axiom of replacement)实际上是[公理模式](https://zh.wikipedia.org/wiki/公理模式).



# Zermelo-Fraenkel Set Theory (ZF)

[Source: Stanford Encyclopedia of Philosophy](https://plato.stanford.edu/entries/set-theory/ZF.html)

## Axiom of Extensionality

$$
∀x∀y[∀z(z∈x↔z∈y)→x=y]
$$



This axiom asserts that when sets $x$ and $y$ have the same members, they are the same set.

## Axiom of the empty set

This axiom asserts the existence of the empty set:
$$
∃x¬∃y(y∈x
$$


Since it is provable from this axiom and the previous axiom that there is a unique such set, we may introduce the notation $∅$ to denote it.

## Axiom of pairs

This axiom asserts that given any sets $x$ and $y$, there exists a pair set of $x$ and $y$, i.e., a set which has only $x$ and $y$ as members:
$$
∀x∀y∃z∀w(w∈z↔w=x∨w=y)
$$


Since it is provable that there is a unique pair set for each given $x$ and $y$, we introduce the notation $\{x,y\}$ to denote it. In the particular case when $x=y$, the axiom asserts the existence of the *singleton* $\{x\}$, namely the set having $x$ as its unique member.

## Axiom of power set

This axiom asserts that for any set $x$, there is a set $y$ which contains as members all those sets whose members are also elements of $x$, i.e., $y$ contains all of the subsets of $x$:
$$
∀x∃y∀z[z∈y↔∀w(w∈z→w∈x)]
$$
Since every set provably has a unique ‘power set’, we introduce the notation $\mathcal P(x)$ to denote it. 



Note also that we may define the notion "$x$ is a subset of $y$ ($x⊆y$)" as: $∀z(z∈x→z∈y)$. Then we may simplify the statement of the Power Set Axiom as follows:
$$
∀x∃y∀z(z∈y↔z⊆x)
$$

## Axiom of union

This axiom asserts that for any given set $x$, there is a set $y$ which has as members all of the members of all of the members of $x$
$$
∀x∃y∀z[z∈y↔∃w(w∈x∧z∈w)]
$$


Since it is provable that there is a unique ‘union’ of any set $x$, we introduce the notation $⋃x$ to denote it.

## Axiom of infinity

This axiom asserts **the existence of an infinite set**, i.e., a set with an infinite number of members:
$$
∃x[∅∈x∧∀y(y∈x→⋃{y,{y}}∈x)]
$$


We may think of this as follows. Let us define "the union of x and y" ($x∪y$) as the union of the pair set of $x$ and $y$, i.e., as $⋃{x,y}$. Then the Axiom of Infinity asserts that there is a set $x$ which contains ∅ as a member and which is such that whenever a set $y$ is a member of $x$, then $y∪\{y\}$ is also a member of $x$. 

Consequently, this axiom guarantees the existence of a set of the following form:
$$
\{∅, \{ ∅ \}, \{ ∅, \{ ∅ \} \}, \{ ∅, \{ ∅ \}, \{ ∅, \{ ∅ \} \} \},…\}
$$


Notice that the second element, $\{∅\}$, is in this set because

1. the fact that $∅$ is in the set implies that $∅∪\{∅\}$ is in the set and
2. $∅∪\{∅\}$ just is $\{∅\}$. 



Similarly, the third element, $\{∅,\{∅\}\}$, is in this set because

1. the fact that {∅} is in the set implies that {∅}∪{{∅}} is in the set and
2. $\{∅\}∪ \{ \{ ∅ \} \}$ just is $\{ ∅, \{ ∅ \} \}$. 

And so forth.

## Axiom (schema) of separation

This is the *Separation Schema*, which is a formula-pattern that uses a metavariable (in this case $ψ$) to describe an infinite list of axioms – one axiom for each formula of the language of set theory with at least a free variable. 

Every instance of the Separation Schema asserts the existence of a set that contains the elements of a given set w that satisfy a certain condition, which is given by a formula $ψ$. 

That is, suppose that $ψ(x,u_1,…,u_k)$ is a formula of the language of set theory that has $x$ free and may or may not have $u_1,…,u_k$ free. Then the Separation Schema for the condition $ψ$ asserts:
$$
∀u1…∀uk[∀w∃v∀r(r∈v↔r∈w∧ψ(r,u1,…,uk))]
$$




In other words, given sets $w$ and $u_1,…,u_k$, there exists a set $v$ which has as members precisely the members $r$ of $w$ which satisfy the formula $ψ(r,u_1,…,u_k)$. 

## Axiom (schema) of replacement

This is the *Replacement Schema*, which is also a formula-pattern that uses a metavariable (in this case $ϕ$) to describe an infinite list of axioms -- one axiom for each formula of the language of set theory with at least two free variables. Suppose that $ψ(x, y, u_1,…,u_k)$  is a formula with $x$ and $y$ free, and in which $u_1,…u_k$ may or may not be free. Then the instance of the Replacement Schema given by $ϕ(x,y,u_1,…,u_k)$ is the following axiom:
$$
∀u1…∀uk[∀x∃!yϕ(x,y,u1,…uk)→ \\
∀w∃v∀r(r∈v↔∃s(s∈w∧ϕ(s,r,u1,…uk)))]
$$


In other words, if we know that $ϕ$ is a functional formula (which relates each set $x$ to a unique set y), then if we are given a set $w$, we can form a new set $v$ as follows: collect all of the sets to which the members of w are uniquely related by $ϕ$.

Note that the Replacement Schema can take you ‘out of’ the set $w$ when forming the set $v$. The elements of $v$ need not be elements of $w$. By contrast, the Separation Schema of Zermelo only yields subsets of the given set $w$.

## Axiom of regularity 

The final axiom asserts that every set is ‘well-founded’:
$$
∀x[x≠∅→∃y(y∈x∧∀z(z∈x→¬(z∈y)))]
$$
A member $y$ of a set $x$ with this property is called a ‘minimal’ element. This axiom rules out the existence of circular chains of sets (e.g., such as $x∈y∧y∈z∧z∈x$) as well as infinitely descending chains of sets (such as $… x3∈x2∈x1∈x0$).



# Axiom of Choice

Axiom of Choice: Let $\left(E_\alpha\right)_{\alpha \in A}$ be a family of nonempty sets $E_\alpha$, indexed by an index set $A$. Then we can find a family $\left(x_\alpha\right)_{\alpha \in A}$ of elements $x_\alpha$ of $E_\alpha$, indexed by the same set $A$.



This axiom is trivial when A is a singleton set, and from math- ematical induction one can also prove it without difficulty when A is finite. However, when A is infinite, one cannot deduce this axiom from the other axioms of set theory, but must explicitly add it to the list of axioms.

**在对测度论的研究中我们会发现, 如果我们接受“选择公理”，则我们必须接纳不可测集. 这是数学中令人遗憾的事实: 不是所有的集合都是Lebesgue可测的.**



