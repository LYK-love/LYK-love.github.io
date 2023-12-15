---
categories:
- Software Engineering
date: 2023-04-02 20:36:12
tags: Linux
title: Parallel Desktop
---

Outline:

* Intro
* Download
* Use

<!--more-->

# Intro

* [PD](https://www.parallels.com/eu/): 支持M1 Mac的虚拟机工具
* [PD Runner](https://github.com/MikeWang000000/PD-Runner-Revived/tree/pdp): A tool for `Parallels Desktop` can start VMs **even expired** 
  * [Releases](https://github.com/MikeWang000000/PD-Runner-Revived/releases/tag/18.1.1r1). 会下载对应所有支持的PD版本的PD Patcher



# Download

* Parallels Desktop
  * [Releases](https://www.parallels.com/products/desktop/download/)

* PD Runner: 已改名为PD Patcher, 
  * [Releases](https://github.com/MikeWang000000/PD-Runner-Revived/releases/tag/18.1.1r1). 会下载对应所有支持的PD版本的PD Patcher.
  * PD的最新版本是18.2, 但PD Patcher只支持到PD 18.1.1. 因此, 需要到[PD官网]((https://www.parallels.com/products/desktop/download/))下载老版本的PD .

# Use

按照并打开PD Patcher后, 再启动PD, 即可绕过授权检查.



# Problems

# 虚拟机画面模糊

View -> Retina Resolution -> More Space

分辨率调高后, 原有的桌面图标会变小. 需要将图标放大:

Settings -> Display -> Scale 调到200%