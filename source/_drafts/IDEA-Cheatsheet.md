---
title: IDEA Cheatsheet
tags:
---

* mac的`setting`在`preferrence`里

* Git clone:

  File -> New -> Project from Version Control



# Config

IDEA中的`.iml`文件是项目标识文件，缺少了这个文件，IDEA就无法识别项目

生成`.iml`文件:

* 刷新一下Maven Project就会自动生成.iml文件
* 在缺少.iml文件项目下运行`mvn idea:module`
