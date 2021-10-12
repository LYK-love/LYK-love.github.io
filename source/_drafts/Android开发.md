---
title: Android开发
tags:Android
categories:Technology
---

Outline:

1. Android Intro
2. Android Basic
3. Fragment & Animation
4. Handler机制、 多线程与自定义View
5. Android网络
6. Android构建



# Fragment & Animation

* Fragment
  * app components, mini-activity
  * 可重用 UI 单元

## Why fragment

* Activity 模块化
* 相比 View，带有生命周期管理
* 可重用，灵活
* 可以动态添加和删除
* android.support.v4.app.Fragment(3.0下版本)
* android.app.Fragment
* 在各个版本的系统中行为都一致

## 生命周期

* onAttach/onDetach
* onCreate/onDestroy
* onCreateView/onDestroyView
* onActivityCreated
* onStart/onStop
* onResume/onPause

## 动态添加

* FragmentManager
  * 动态添加/删除/替换 Fragment
  * FragmentTransaction

* Fragment 容器
  * 定义 Fragment 的位置和大小

## Fragment/Activity通信

* 如何构造带参数的 Fragment
* 通过接口和回调

# Handler机制、 多线程与自定义View

# Android构建

## 什么是构建

* 构建 ！= 编译
*  构建：安卓源工程  ---->( 经过一系列处理，变为可分发状态 )  APK/AAR
  * 安卓源工程
    * 代码: java, kotlin, C
    * 资源： image, string
    * 配置：  依赖，签名等
  * APK: 应用安装包（zip）
  * AAR: 安卓库（zip）

* 依赖解析、代码生成、代码编译、资源编译...

## Why Gradle

* **依赖管理强大**
* **not xml, groovy dsl based** ,  极致灵活 
  * groovy是编程语言，比作为标记语言的xml强大多了
*  task , plugin, 定制方便、高效、强大

### Gradle Basics

1. 快速了解：[https](https://docs.gradle.org/current/userguide/userguide.html)[://docs.gradle.org/current/](https://docs.gradle.org/current/userguide/userguide.html)[userguide](https://docs.gradle.org/current/userguide/userguide.html)[/userguide.html](https://docs.gradle.org/current/userguide/userguide.html)

2. 基础的概念

   1. 整体理念
      1. 极致利用`Java OOP`
      2. 一切都是面向对象进行配置
      3. 语法上支持`groovy & kotlin`，`groovy`目前仍然是主流
      4. groovy: 语法更灵活，最终也是编译为`java byte code`，运行在`jvm`上

   2. Task
      1. 执行单位
      2. e.g `compileReleaseWithJavac`: 编译java代码的task
      3. e.g `packageRelease`: 打包apk的task

   3. Plugin
      1. 封装某个功能的单元
      2. `java plugin`: 构建`jar`，`android plugin`: 构建`apk/aar`



## 安卓构建流程

* 资源（ xml, png, values ） --->(AAPT)  产物（R.java; ARSC, compiled xml ;  compressed png）

  * `AAPT`: `Android Asset Packaging Tool`
    * `Android SDK`中的核心工具
    * 负责构建阶段的资源处理：编译、链接等

  * `Compiled XML`: 二进制
    * 体积变小，适合mobile phone

  * `ARSC`: 二进制，格式复杂
    * 存储了所有的资源中的字符串
    * 串联起资源id与具体资源：`R.layout.XXX` -> `res/layout-xxhdpi/main_activity.xml`

  * `R.java`: `R.XX.xxxx` -> `0x7fXXxxxx`
    * 存储了所有资源id
    * 串联起代码与资源id

  * `R.java` & `ARSC`: 一起来解决运行时的资源查找



* 代码（`java`, `kt`） --->(`ktc `& `javac`) `java class` ---> (` dx/R8 `)` dex`

  * 源码编译：

	* `javac`: JDK中的标准工具

	* `ktc`: `kotlin compiler`，`kotlin`语言已经成为了当前新增代码的首选

  * 代码转换：
  
  	* `dex`: 安卓平台真实的代码存储格式
  		* 所有的java class汇总生成`dex`文件，空间更优，更适合mobile

    * `dx`: `Android SDK`提供的最早的`jar/class` -> `dex`的工具，现已被取代

    * `R8`: 当前的`java/class` -> `dex`工具，支持java8语法

* ( ARSC, compiled res  ) +  ( XX.dex ) --------->(ZIP)  raw zip ---->(align/sign) apk

  * align: zip中的每一个entry都对齐4byte，获取更好的运行时性能

    sign: 添加签名信息



插件：  autoxcomplete

## 扩展

### 简单定制

### hook task

###  新增task

### Gradle  plugin

