---
title: Software Construction
tags: Software Engineering
categories: Computer Science
date: 2021-06-17 15:14:00
---

Outline:

* Intro
* 软件构造活动
* Ideas

<!--more-->

# Intro

* 定义： 通过编码、验证、单元测试、集成测试和调试等工作的结合，生产可工作的、有意义的软件的详细创建过程

* 软件构造除了核心的编程任务之外， 还涉及详细设计（ 数据结构与算法设计 ）、单元测试、集成与集成测试、 以及其他活动。

* **软件构造是设计的延续**

  * 设计与实现是有区分的。 设计是规划软件构件方案的过程，是现实依据软件构件方案建造真正产品的过程；
  * 源程序是软件构建方案的最后一个规划， 不是产品本身， 真正的产品是运行于计算机上的由二进制代码组成的可执行程序。
  * 源程序的生产过程----编程， **属于设计活动**， 编译器完成的编译和连接才是依据规划建造软件产品的实现活动。

# 软件构造活动

## 详细设计

* 有些项目会将主要的详细设计工作分配在**软件构造阶段**完成。
* 不论是哪种项目，在软件构造阶段都不可避免的会涉及到详细设计的调整工作。 因为编程语言是软件设计的一个重要约束， 随着编程工作的进行和深入， 人们可能会发现与预想不一致的情况和更多的约束，这个时候就需要在软件构造阶段修改详细设计方案。
* 软件构造阶段详细设计使用的方法与技术与软件设计阶段是一样的，只是应用在更小的规模上。

## 程序代码的典型质量

* 易读性
* 易维护性
* 可靠性
* 性能
* 安全性

## 





## 调试

* Debugging is concerned with locating and
  repairing these errors
* 调试过程可以分为三个部分:重现问题、
  诊断缺陷和修复缺陷。

## 重现问题的方法

* 控制输入。
  * 找到相应的数据输入,能够重现绝大多数的问题。可以通过控制数据输入来重现问题意味着缺陷就发生在对该数据的处理代码之中。
  * 寻找能够重现问题的数据输入可以使用问题回溯推理、内存数据监控、记录输入数据日志等方法。
* 控制环境。
  * 有些问题是编译器、操作系统、数据库管理系统、网络管理系统等系统软件环境造成的,通过控制数据输入无法重现问题。这时就需要通过控制环境来重现问题。一定要记住的是,如果你进行各种手段诊断之后确信你的程序代码没有缺陷,就要警惕可能是软件环境造成了问题。
  * 控制环境以重现问题经常使用替换法,例如替换机器、操作系统、数据库管理系统等。

## 寻找和定位缺陷的方法

* 灵活使用编译器提示。
* 持续缩小嫌疑代码的范围。
* 检查刚刚修改过的部分。
* 警惕已出现缺陷和常见缺陷。
* 利用工具。

## 常见错误

* 内存或资源泄漏;
* 定时错误(没有考虑特殊情况) ;
* 逻辑错误;
* 存储错误(考虑磁盘已满,文件不存在等特例
* 编码错误(例如条件判断不够充分)) ;
* 集成错误(相互之间的考虑不相容)
* 内存溢出(超出本身限制);
* 循环错误(死循环或数目不合适) ;
* 转换错误(字符转换等出现问题) ;
* 条件错误;
* 硬编码长度/尺寸;
* 指针错误(超出范围,未赋值);
* 版本缺陷(对以前的不兼容) ;
* 分配释放错误(分配两次、未分配即释放、释放两次、分配未释放) 
* 多线程错误(同步);
* 不恰当重用带来的缺陷。

## 修复缺陷的注意点

* 一次只修复一 个缺陷。
* 修改前保留旧版本的备份,如果项目使用了配置管理系统,这个工作会由配置管理工具完成,否则就需要由程序员手动完成。
* 使用测试和评审验证修复的有效性。
* 检查和修复类似的缺陷,这可以在代码搜索、程序切片等工具的帮助下进行。

## 代码评审

* 代码评审对代码的系统检查,通常是通过同行专家评审来完成的。通过评审会议可以发现并修正之前忽略的代码错误,从而同时提高软件的质量和开发者的技巧。
* 代码评审一般分为正式评审、轻量级评审和结对编程。

## 实践经验

* 就算不能评审全部的代码,最少也要评审一部分( 20 -33% )代码,以促使程序员编写更好的代码。
* 一次评审少于200- 400行的代码。
* 目标为每小时低于300 -500 LOC的检查速率。
* 花足够的时间进行正确缓慢的评审,但是不要超过60- -90 分钟/每次。
* 确定代码开发者**在评审开始之前就已经注释了源代码**。
* 使用**检查列表**,因为它可以极大地改进代码开发者和评审者的工作。确认发现的缺陷确实得到修复了。
* 培养良好的代码评审文化氛围,在这样的氛围中搜索缺陷被看做是积极的活动。
* 采用轻量级,能用工具支持的代码评审。

## 集成与构建

* 在以分散的方式完成程序基本单位(例程、类)之后，软件构造还需要将这些分散单位集成和构建为
  构件、子系统和完整系统。
* 集成有`大爆炸式集成`和`增量式集成`两种方式。实践中增量式集成有着更好的效果。
* 构建将可读的源代码转换为标准的能在计算机上运行的可执行文件。构建过程需要配置管理工具的帮
  助。

## 构造管理

* 构造计划
  * 根据整个项目的开发过程安排, 定义要开发的构建与次序,选则构造方法,明确构造任务并分配给程序员。
* 度量
    * 类或者方法的复杂度、代码行、注释
* 配置管理
    * 对开发配置库建立使用规则, 完成代码单位或者修改是提交
    * 开发时要确保配置环境一致. 这点非常重要,因为企业用的配置都非常古老.

# 防御式编程

防御式编程用于提升代码的正确性和健壮性, 这两个性质可能会矛盾，因此要根据具体问题作出取舍

* 正确性(correctness):  软件按照需求正确执行任务的能力

  * **永不返回不准确的结果**，哪怕不返回结果也比返回不准确的结果好（无论如何，软件正常运行是最起码的要求，追求正确性不意味着软件可以崩溃）
  * 人身安全攸关的软件

* 健壮性(robustness): 软件**对于规范要求以外的输入情况的处理能力**

  * 要不断尝试采取某些措施，以保证软件可以持续地运转下去，哪怕有时做出一些不够准确的结果

  * 消费类应用软件

  



主要思想:

* 子程序应该不因传入错误数据而被破坏，哪怕是由其他子程序产生的错误数据

* 要承认程序都会有问题，都会被修改， 即：进行防御式编程时，不应该存在任何假设



特点：

* 区别于检查错误：防御性编程并不能排除所有的程序错误
* 区别于调试：防御式编程是一种防卫方式，而不是补救方式
* 区别于测试：测试不是防御式的，测试可以验证代码现在是 正确的，但不保证在经历修改之后不会出错





## 错误处理技术

**错误处理应该根据系统对正确性和健壮性的追求来定**

这里的错误处理技术有开发阶段的，也有用于生产环境的，在开发阶段，应该尽早地引入辅助代码， 当然为了追求效率，某些辅助代码不应该被包含进在生产环境(比如`assert`)



### assert

断言用于开发阶段，不应该被编译进生产环境

* 断言可以提升系统的正确性，断言处理的是代码中**不应发生的错误** 

### exception

异常：把代码中的错误或异常事件传递给调用方代码的一种技术

* 异常用于提升系统的健壮性，异常处理的是**预料中可能发生的错误， 由于程序代码或外部因素而发生， 是可以手动处理的**
  * 尤其是`RuntimeException`， 一般是编程问题引发的
* 不要滥用异常，**只有真正例外的情况下才抛出异常**（即其他技术无法解决的情况下）
* 异常会增加复杂度: 调用子程序的代码需要了解被调用代码中可能会抛出的异常，**弱化了封装性**



实践原则：

* 永远考虑异常的替换方案，不到迫不得已不要用异常
  * 使用异常的原因是迫不得已， 而不是因为语言提供了异常机制
* 不能用异常来推卸责任： **可以在局部处理就在局部处理掉**
* 避免在构造函数和析构函数中抛出异常，除非你在同一地方把它们捕获
  * C++中， 构造函数中的异常会造成资源泄露 
* 在恰当的抽象层次抛出异常：确保异常的抽象层次与子程序接口的抽象层次是一致的
* 如果系统要使用大量异常，那么需要将异常标准化



### error

error不是一种错误处理技术，它和exception的区别在于， error往往是系统内部发生了错误，这一般是无法手动处理的



Java Exception and Error：

![image-20220412171602879](/Users/lyk/Library/Application Support/typora-user-images/image-20220412171602879.png)

## 辅助代码

* 





# 实践方法



## 重构

* 为什么要重构?
  1. 因为无法预计到后续数年的修改，导致软件开发阶段的设计方案不能满足修改要求;
  2. 随着修改次数的增多,软件设计结构的质量越来越脆弱,很难继续维持可修改性。
* 什么是重构?
  * 修改软件系统的严谨方法,它在**不改变代码外部表现的情况下改进其内部结构**。
* 重构的时机?
  * 增加新的功能时。需要注意的是**重构发生在新功能增加完成之后,用来消除新功能所添加代码导致的坏味道( code smell );而不是发生在新功能添加之前**, 重构不改变代码外部行为,不是能够实现新功能添加的方法。
  * 发现了缺陷进行修复时。诊断缺陷时如果发现代码存在坏味道或者修复代码会引入坏味道,就需要进行重构。
  * 进行代码评审时。如果在评审代码时发现了坏味道,就需要进行重构。

## code smell

* **太长的方法**,往往意味着方法完成了太多的任务,不是功能内聚的,需要被分解为多个方法。[McConnell2004]认为如果方法代码长度超过了一个屏幕,就需要留心注意了。
* **太大的类**,往往意味着类不是单一职责的 ,需要被分解为多个类。
* **太多的方法参数**,往往意味着方法的任务太多或者参数的数据类型抽象层次太低,不符合接口最小化的低耦合原则,需要将其分解为多 个参数少的方法或者将参数包装成对象、结构体等抽象层次更高的数据类型。
* **多处相似的复杂控制结构**,例如多处相同类型的Case结构,往往意味着多态策略不足,需要使用继承树多态机制消除复杂控制结构。
* **重复的代码**,往往意味着隐式耦合,需要将重复代码提取为独立方法。一个类过多使用其他类的属性,往往意味着属性分配不正确或者协作设计不正
  确,需要在类间转移属性或者使用方法委托代替属性访问。
* **过多的注释**,往往意味着代码的逻辑结构不清晰或者可读性不好,需要进行逻辑结构重组或者代码重组。

## 测试驱动开发

* 测试驱动开发又被称为测试优先( Test First )的开发,随着极限编程方法的普遍应用而得到普及.
* 测试驱动开发要求程序员在编写一段代码之前，**优先完成该段代码的测试代码**。测试代码通常由测试工具自动装载执行,也可以由程序员手工执.行。完成测试代码之后,程序员再编写程序代码并在编程中重复执行测试代码,以验证程序代码的正确性。

## 结对编程

* Two programmers working side-by-side, collaborating on the same design, algorithm, code or test

* One programmer, the driver, has control of the keyboard/mouse and actively implements the program
* The other programmer, the observer, continuously observes the work of the driver to **identify tactical** (syntactic, spelling, etc.) **defects** and also thinks strategically about the direction of the work
* On demand, the two programmers can brainstorm any challenging problem
* The two programmers periodically switch roles, they work together as equals to develop software

### 原理

* Pair-Pressure 
  * Keep each other on task and **focused**
* Pair-Think 
  * Bring different prior experiences to the task
* Pair-Relaying 
  * Each, in turn, contributes to the best of their knowledge and ability Then, sit back and think while their partner fights on

* Pair-Reviews 
  * Continuous design and code reviews 
  * Ultimate in defect removal efficiency 
  * Removes programmers distaste for reviews 
  * 80% of all (solo) programmers don’t do them regularly or at all 
  * Defect prevention always more efficient than defect removal

* Pair Debugging 
  * Talking about problem in a pair can lead to a solution becoming obvious
* Pair-Learning 
  * Continuous reviews -> learn from partners techniques, knowledge of language, domain, etc.

# Construction Ideas

## A Decade of Advances in Software Construction

1. Design has Been Raised a Level
   * Programming has advanced through ability to create larger code aggregations 
     * Statements 
     * Routines 
     * Classes 
     * Packages
   * Real legacy of OO might well be larger aggregations
2. **Daily** Build and Smoke Test
   * Institutionalizes incremental integration 
   * Minimizes serious integration problems that used to be common
   * Lots of other benefits, too
3. Standard Libraries
   * Good programmers have always used libraries
   * Now provided with languages (Java, C++, .NET)
4. Visual Basic
   * Visual programming innovation 
   * The first development environment to make widespread use of COTS components
   * Only language to learn Ada’s syntax lessons (case statements, control statements, etc.)
   * Highly integrated environment
5. Open Source Software

* Great aid to programmers during development
* Reduced barriers to making code available 
* Opportunity to learn from available code 
* Improved ability to read code 
* Nice “community” of programmers

6. The Web, for Research

* FAQs 
* Discussion groups 
* Searchability in general

7. Widespread Use of Incremental Development( **增量开发** )

* Concepts were well known in 1990s 
* Practice is well established in 2000s

8. Test-First Development

* Shortens time to defect detection 
* Increases personal discipline 
* Complements daily build & smoke test

9. Refactoring as a Discipline

* Provides a discipline for making changes 
* Not so good as a total design strategy 
* Good example of incrementalism

10. Faster Computers

* Implications for optimization 
* Implications for programming languages 
* Implications for development

## Ten Realities of Modern Software Construction

1. “Construction” is a Legitimate Topic
2. Individual Variation Is Significant
3. Personal Discipline Matters

* Why Personal Discipline Matters 
  * Being realistic about predicting the future 
  * Areas where discipline matters 
    * Refactoring 
    * Prototyping 
    * Optimization 
    * Minimal-complexity designs specifically 
    * Managing complexity generally
  * Endpoints—Discipline and Courage 
    * Humphrey on PSP 
    * Beck on Extreme Programming

1. A Focus on Simplicity Works Better than a Focus on Complexity
   * **Focus on read-time convenience, not write-time convenience**
2. Defect-Cost Increase is Alive and Well
3. Importance of Design
4. Technology Waves Affect Construction Practices
5. Incremental Approaches Work Best

* Perspective on Incrementalism 
  * The pure waterfall model is not at all incremental or iterative—which is why it hasn’t worked very well
  * Spiral development is highly incremental and iterative, which is part of why it does work well
  * All projects will experience iteration at some point 
  * Think about where and when in your project you will get your incrementalism—cheaply, or expensively?

1. The Toolbox Metaphor Continues to be Illuminating
2. Software’s Essential Tensions

## Some of the Worst Construction Ideas of 1990s and 2000s



