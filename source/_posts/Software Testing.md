---
title:  Software Testing
tags: Software Testing
categories: Software Engineering
date: 2021-06-17 15:14:10
---


* Are you building it “right”?
* Are you building the “right” thing?

For more information, please read *Automatic Testing*

<!--more-->

# 软件测试的目的

- Test suite: a collective term for all the tests
- Unit test: a “micro-test” that tests a specific feature in isolation
- Integration test: a “macro-test” that runs a larger part of the system to check that different feature or components work *together*.
- Regression test: a test that implements a particular pattern that *previously* caused a bug to ensure that the bug does not resurface.
- Mocking: to replace a function, module, or type with a fake implementation to avoid testing unrelated functionality. For example, you might “mock the network” or “mock the disk”.



* 向开发者和用户展示软件满足了**需求**， 表明软件产品是一个合格的产品
  * 有效性测试
  
* 找出软件中的缺陷和不足
  * 缺陷测试
  
  

# 桩程序和驱动程序

* 桩程序是被测试部件的交互环境,它扮演被测试部件需要调用的其他系统部件。桩程序对其他系统部件的扮演仅限于规格相同，内部代码要简单地多,通常是直接返回固定数据或者按照固定规则返回数据。

* 驱动程序负责创建被测试部件的执行环境,并驱动和监控被测试部件执行测试用例的过程,判定测试用例的执行结果。

# 单元测试

略

# 集成测试

* 自顶而下集成测试

  ![自顶而下集成测试](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/image-20220125170602076.png)

* 自底向上集成测试

  ![自底向上集成测试](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/image-20220125170614394.png)

# 系统测试

* 单元测试、集成测试更加关注**技术**上的正确性,重在发现设计缺陷和代码缺陷。

* 系统测试则不同,它更关注不符合**需求**的缺陷和需求自身的内在缺陷。

  * 系统测试关注整个系统的行为,所以不依赖于桩程序和驱动程序。但是，使用一些测试工具可以让系统测试过程更加自动化。
  * 系统测试的功能测试计划以需求规格说明文档或用例文档为基础,主要使用随机测试和基于规格的测试技术设计功能测试用例。在测试非功能性需求时需要使用针对非功能需求的特定测试技术进行测试计划和测试用例设计。

* 根据测试目标的不同,有很多不同类型的系统测试:功能测试、非功能性测试、验收测试、安装测试等等。但是发生在软件测试阶段,完全由软件测试人员控制和执行的主要是功能测试和非功能性测试。

  

# 测试技术

* 测试用例的选择
* 随机测试
* 基于规格的技术-黑盒测试方法
* 基于代码的技术-白盒测试方法
* 特定测试技术

## 测试用例的选择

* 测试的目标是发现尽可能多的缺陷,并不绝对要求所有缺陷。
* 因为测试是有代价的,不仅要耗费桩程序、驱动人力等成本,更重要的是随着测试用例数量增多， 成本会直线上升
* 所以,软件测试人员需要仔细地选择用例在代价尽可能小的情况下发现足够多的缺陷[Zhu 1997 ]。
* 测试技术就是帮助软件人员设计和选择用例的。

## 随机测试

* 随机测试( 随机测试 `Ad hoc Testing` )是一种基于软件工程师直觉和经验的技术, 也许是实践中使用最为广泛的测试技术[SWEBOK2004].
* 随机测试根据软件工程师的技能， 直觉和对类似程序的经验[MyersI979] ,从所有可能的输入值中选择输入子集,建立测试用例。

## 黑盒测试方法
* 等价类划分
  * 有效等价类:是指对于程序的规格说明 合理、有意义的输入的数据构成的集合。利用有效等价类可检验程序是否实现了规格说明中所定的功能和性能。
  
  * 例子：
  
    | ID                                               | 输入                     | 预期输出     |
    | ------------------------------------------------ | ------------------------ | ------------ |
    | 1                                                | payment = 100; Total=50; | 50           |
    | 2                                                | payment = 100; Total=20; | 输入数据无效 |
    | 3                                                | payment = 50; Total=100; | 输入数据无效 |
    | 如图的规格说明，可以将输入数据划分为三个等价类： |                          |              |
  
    * 有效数据
    * 无效数据 payment<=0
    * 无效数据 payment<total
  
* 边界值分析

* 决策表

  ![决策表](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%BD%AF%E4%BB%B6%E5%B7%A5%E7%A8%8B/image-20220125172134640.png)

* 状态转换
  * 为对象建立`状态图`,描述测试对象的状态集合，输入集合和输入导致的状态转换集合。
  * 以`状态图`为基础,可建立测试对象的`转换表`. 状态转换表每一行都应该被设计为测试用例

## 白盒测试方法

* 语句覆盖
  * 语句覆盖设计测试用例的标准是确保被测试对象的每一行程序代码都至少执行一次
* 条件覆盖
  * 条件覆盖设计测试用例的标准是确保程序中每个判断的每个结果都至少满足一次
* 路径覆盖
  * 路径覆盖测试用例的标准是确保程序中每条独立执行路径都
    至少执行一次

## 特定测试技术

### 面向对象测试技术

* 给予状态图设计类的单元测试用例
* 基于协作设计类之间的集成测试用例

# 测试活动

## 测试计划

## 测试设计

## 测试执行

## 测试评价

* 测试用例日志
* 缺陷报告
* 测试度量
  * 缺陷数据
  * 测试覆盖率
    * 需求覆盖率
    * 模块覆盖率
    * 代码覆盖率
* 缺陷度量
  * 根据引入缺陷的阶段
    * 系统需求缺陷、设计缺陷和编码缺陷
  * 根据缺陷的影响力
    * 严重、一般和无影响

* 覆盖率
  * 需求覆盖率=被测试的需求数量/需求
    总数;
  * 模块覆盖率=被测试的模块数量/模块
    总数;
  * 代码覆盖率=被测试的代码行/代码行
    数总数。
