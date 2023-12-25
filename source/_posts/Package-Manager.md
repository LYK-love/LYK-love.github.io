---
categories:
- Software Engineering
date: 2022-09-13 14:58:06
tags: Linux
title: Package Manager
---

Outline:

* For Linux
* For OSX
* For Languages

<!--more-->

# For Linux

## apt

更新软件源

```
apt-get update
apt-get upgrade
```



查看系统已安装的包：

```shell
apt list --installed 
```



## pacman

同步存储库数据库，并且更新系统的所有软件包，但不包括不在软件库中的“本地安装的”包：

```
pacman -Syu
```

- `S` 代表同步
- `y` 代表更新本地存储库
- `u` 代表系统更新



# For OSX

## brew

brew安装的软件位置千奇百怪, 但都会在`/opt/homebrew/opt`留下软链接

* 事实上, brew可能把

安装：

```shell
/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"
```







* 查看brew版本:

  ```
  brew --version
  ```


---



* 查看安装的软件版本:

  ```
  brew info [name]
  ```

* 查看某软件的可安装版本:

  ```
  brew search [name]
  ```

  

* brew可以对它安装的软件进行版本切换. 在最新的3.x版本使用`link`:

  ```shell
  brew unlink go && brew link go@1.13
  ```

  低版本的brew使用的是`switch`, here is [Doc](https://babygoat.github.io/2019/06/19/Golang-mac%E4%B8%8A%E5%88%87%E6%8F%9B%E5%A4%9A%E5%80%8Bgo%E7%89%88%E6%9C%AC/)

---



* 查看brew安装的符号路径: 一般都位于`/opt/homebrew/opt`

  ```
  brew  --prefix <package>
  ```



* 查看brew安装的软件的实际路径:

  ```
  brew list <package>
  ```

  





## npm

### 换源

国内优秀npm镜像：

淘宝npm镜像

- 搜索地址：[http://npm.taobao.org/](https://link.jianshu.com?t=http://npm.taobao.org/)
- registry地址：[http://registry.npm.taobao.org/](https://link.jianshu.com?t=http://registry.npm.taobao.org/)

cnpmjs镜像

- 搜索地址：[http://cnpmjs.org/](https://link.jianshu.com?t=http://cnpmjs.org/)
- registry地址：[http://r.cnpmjs.org/](https://link.jianshu.com?t=http://r.cnpmjs.org/)



 1.临时使用

```python
npm install express --registry https://registry.npm.taobao.org
```



2.持久使用

```python
npm config set registry https://registry.npm.taobao.org
```

配置后可通过下面方式来验证是否成功:

```shell
npm config get registry
```





# Dreamerv3-torch
Pytorch implementation of [Mastering Diverse Domains through World Models](https://arxiv.org/abs/2301.04104v1). DreamerV3 is a scalable algorithm that outperforms previous approaches across various domains with fixed hyperparameters.

- 
- 