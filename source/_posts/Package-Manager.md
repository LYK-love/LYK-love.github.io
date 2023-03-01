---
title: Package Manager
tags: Linux
categories: Toolkit
date: 2022-09-13 14:58:06
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

## conda

 推荐`miniconda`， 直接去NJU MIRROR下载：

```shell
wget https://mirror.nju.edu.cn/anaconda/miniconda/Miniconda3-py39_4.9.2-Linux-x86_64.sh
```

* 清华源

然后安装：

```shell
bash /path/to/miniconda
```



重启终端，检查安装是否成功：

```shell
conda -V
```

### 换源

conda换源建议用nju源  （清华源早就不行了，建议别用）， [具体指导](https://mirrors.nju.edu.cn/help/anaconda)

1. 先执行 `conda config --set show_channel_urls yes` 生成用户目录下的 `.condarc` 文件

2. 编辑该文件：

   ```yaml
   channels:
     - defaults
   show_channel_urls: true
   default_channels:
     - https://mirror.nju.edu.cn/anaconda/pkgs/main
     - https://mirror.nju.edu.cn/anaconda/pkgs/r
     - https://mirror.nju.edu.cn/anaconda/pkgs/msys2
   custom_channels:
     conda-forge: https://mirror.nju.edu.cn/anaconda/cloud
     msys2: https://mirror.nju.edu.cn/anaconda/cloud
     bioconda: https://mirror.nju.edu.cn/anaconda/cloud
     menpo: https://mirror.nju.edu.cn/anaconda/cloud
     pytorch: https://mirror.nju.edu.cn/anaconda/cloud
     simpleitk: https://mirror.nju.edu.cn/anaconda/cloud
   ```

   即可添加 Anaconda Python 免费仓库。

3. 运行 `conda clean -i` 清除索引缓存，保证用的是镜像站提供的索引。

4. 运行 `conda create -n myenv numpy` 测试一下吧

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

  

# For Languages

## pip3

pip是python的一个包管理工具，python2:使用`pip`, python3使用`pip3`

* ( Python3下使用`pip` 默认用的是`pip3` )

### 安装

```shell
yay -S pip3
```



mac用户：`brew intall pip3`相当卡， 因此要用：

```
curl bootstrap.pypa.io/get-pip.py | python3
```



检查安装是否成功：

```shell
pip3 --version
```



### 换源

在 pip 命令中使用 **-i** 参数来指定镜像地址

```
pip3 install numpy -i https://mirrors.aliyun.com/pypi/simple/
```



如果需要配置全局的镜像地址，需要修改配置文件:

Linux/Mac os 环境中，配置文件在 ~/.pip/pip.conf（如不存在创建该目录和文件）：

```text
mkdir ~/.pip
```

打开配置文件 **~/.pip/pip.conf**，修改如下：

```text
[global]
index-url = https://mirrors.aliyun.com/pypi/simple/
[install]
trusted-host = https://mirrors.aliyun.com
```



查看镜像地址：

```python
pip3 config list  
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


