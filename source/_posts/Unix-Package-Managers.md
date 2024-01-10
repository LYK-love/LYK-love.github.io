---
title: Unix Package Managers
categories:
- Software Engineering
tags: Linux
date: 2022-09-13 14:58:06
---

Outline:

* APT（Advanced Package Tool)
* pacman

<!--more-->

# apt

APT（Advanced Package Tool)

Note: you may have seen `sudo apt-get install package-name`, `apt-get` is a more complex and low level command line tool compared to `apt`. It's only advantage is its stability. Basically, `apt` is more preferrable and we can use `apt` all the time.



In Ubuntu, the information about software packages is stored in remote repositories.

* Update the local package index. Downloads the latest list of available packages from its configured software sources.

  ```
  sudo apt update
  ```

  Note: This command does not install or upgrade any packages; it only updates the information about what packages and versions are available.

* Upgrade installed packages on your system:

  ```sh
  sudo apt upgrade
  ```

  When you run this command, APT (Advanced Package Tool) looks at the latest package information obtained via `apt update` and upgrades those packages installed on your system to their latest versions. This can include updates to various applications and system components. `apt upgrade` will not remove any packages or install any that are not already installed.







更新软件源

```
apt-get update
apt-get upgrade
```



查看系统已安装的包：

```shell
apt list --installed 
```

# pacman

同步存储库数据库，并且更新系统的所有软件包，但不包括不在软件库中的“本地安装的”包：

```
pacman -Syu
```

- `S` 代表同步
- `y` 代表更新本地存储库
- `u` 代表系统更新

# brew

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

  
