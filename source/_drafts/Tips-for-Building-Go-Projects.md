---
title: Tips for Building Go Projects
categories: Toolkit
---

# Go

## Installation(with brew)

On Mac with brew:

1. Update & Install Go:

   ```shell
   brew update&& brew install golang
   ```

2. Set Workspace:

   It’s considered best practice to use `$HOME/go` location for your workspace, so let’s do that!

   ```shell
   mkdir -p $HOME/go/{bin,src,pkg}
   ```

   We created two important folders `bin` and `src` that’ll be used for GO

3. Setup Environment and set Proxy:

   We’ll need to add to `.bashrc` or `.zshrc` (if you’re using zsh) with the following info. (Ex: `nano ~/.bashrc` )

   ```shell
   # Golang Path, 并配置了代理
   ## go命令行会使用modules，而一点也不会去GOPATH目录下查找
   export GO111MODULE=on 
   
   ## set mirroring, if you need to
   export GOPROXY=https://goproxy.io,direct
   ## or `export GOPROXY="https://goproxy.cn"`
   
   ## go install 会讲软件安装到$GOPATH/bin, 由于它被配置到环境变量,因此软件可以直接从命令行调用
   export GOPATH=$HOME/go
   export GOROOT="$(brew --prefix golang)/libexec"
   
   ## you can set as your own mirror
   ## export GO_BINARY_BASE_URL=https://golang.google.cn/dl/
   
   export PATH="$PATH:${GOPATH}/bin:${GOROOT}/bin"
   ```

   reload the settings with `source $HOME/.bashrc` (or `.zshrc` )

4. Feel free to start any project (make new folder) under `~/go/src` and go from there.



Note: 如果用GVM来安装Go, 就不需要步骤2和3了. GVM会自己创建GOPATH和GOROOT文件夹, 并动态地指定环境变量. 当然Mac好像用不了GVM, 所以还是用Brew吧

## 开发环境

Vs code打开输入：Command+Shift+P， 在弹出框内输入：Go:install/update Tools，工具全选，进行安装。

建议使用language server, go 的 langeage是[gopls](https://github.com/golang/vscode-go/wiki/settings#settings-for-gopls)



## Go Commands

* 下载,编译,安装到`$GOPATH/bin`, e.g.:

  ```
  go install github.com/nikitavoloboev/gitupdate@latest
  ```

  会下载gitupdate到`$GOPATH/bin`, 由于`$GOPATH/bin`已经被配置到环境变量,所以gitupdate可以在命令行直接执行

# GVM

[Doc](https://github.com/moovweb/gvm)

GVM是Go的版本管理工具, 就和NodeJS的nvm一样. GVM是一个独立的Shell脚本

其工作原理就是创建不同的GOROOT 和 GOPATH, 每次切换就改写这两个环境变量:

![img](https://upload-images.jianshu.io/upload_images/16549478-14229cd6451e2f3a.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

当然也可以手动操作, 每次创建目录然改环境变量来切换Go版本. GVM只是把这个过程简化



## 特别说明

**GVM就是个垃圾, Mac不要用GVM, 老老实实用brew吧**

由于 Go 1.5 使用了自举，也就是用 Go 写 Go，如果在系统环境完全没有 Go 命令的情况下，使用 `gvm install go` 会报错，可以参考 [gvm 文档相关说明](https://github.com/moovweb/gvm#a-note-on-compiling-go-15)，会要求先安装 Go 1.4，但是呢，对于高版本的 macOS 来说，安装 Go 1.4 是会失败的。

有人的做法是: https://github.com/moovweb/gvm/issues/360:

```
brew install go #使用 `brew install go` 先安装一个 Go
gvm install go1.15.5
gvm use go1.15.5 --default
brew uninstall go
```

亲测无效, 会卡在`gvm install go1.15.5`



我还找到了一个[国人的blog](https://soulteary.com/2022/05/12/better-golang-usage-on-m1-mac.html), 亲测也没用







## Installation

```
bash < <(curl -s -S -L https://raw.githubusercontent.com/moovweb/gvm/master/binscripts/gvm-installer)
```

但是我的电脑好像连不了这个url,无奈只能手动下载`gvm-installer`这个脚本然后执行

## Usage

```
gvm install go1.4
gvm use go1.4 [--default]
```

```
Usage: gvm install [version] [options]
    -s,  --source=SOURCE      Install Go from specified source.
    -n,  --name=NAME          Override the default name for this version.
    -pb, --with-protobuf      Install Go protocol buffers.
    -b,  --with-build-tools   Install package build tools.
    -B,  --binary             Only install from binary.
         --prefer-binary      Attempt a binary install, falling back to source.
    -h,  --help               Display this message.
```

## A Note on Compiling Go 1.5+

Go 1.5+ removed the C compilers from the toolchain and [replaced](https://docs.google.com/document/d/1OaatvGhEAq7VseQ9kkavxKNAfepWy2yhPUBs96FGV28/edit) them with one written in Go. Obviously, this creates a bootstrapping problem if you don't already have a working Go install. In order to compile Go 1.5+, make sure Go 1.4 is installed first.

```
gvm install go1.4 -B
gvm use go1.4
export GOROOT_BOOTSTRAP=$GOROOT
gvm install go1.5
```

## Uninstallatin

```shell
rm -rf ~/.gvm
```

