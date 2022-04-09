---
title: Hexo
Categories: Toolkit
date: 2022-03-27 02:28:03
---

Outline

* Feateues
* 多主机同步
* Bugs

<!--more-->

# Features

## latex支持

参见： https://www.jianshu.com/p/7ab21c7f0674

一定要卸载`hexo-renderer-marked`

## 主题

大多数 Hexo 主题的文档都是直接 `clone` 主题到对应的 `themes`目录中，然后配置 `_config.yml`。 但是主题是一个独立的git仓库， 有自己的 `.git` 项目文件夹

但是你在push本地仓库的时候，是不会push子仓库的。 因此其他主机clone你的hexo仓库的时候， 不会把主题文件夹clone下来( 比如`themes/next`为空 )， 这样生成的`index.html`也为空( 0kb ). 解决方案是使用`git submodule`. 每次把主题当作submodule来push， 其他主机也通过

1. 创建一份主题到自己的 Github （比如fork一份）

2. 创建一个 submodule。

   ```
   $ cd blog-hexo
   $ git submodule add https://github.com/LYK-love/hexo themes/hexo
   ```

   git 会将 `hexo` 主题作为一个项目子模块 clone 到 themes/hexo 中. 同时 hexo 项目中会自动生成一个 `.gitmodules` 文件, 这个配置文件中保存了项目 URL 与已经拉取的本地目录之间的映射.

   **.gitmodules 文件内容**

   ```
   $ cat .gitmodules
   [submodule "themes/next"]
   	path = themes/next
   	url = git@github.com:LYK-love/hexo.git
   ```



   

3. 更新 `_config.yml` 使用修改过的主题。

   ```
   theme: hexo
   ```

4. 这时，我们就拥有了两个独立的仓库，一个是 hexo 博客，另外一个是主题。

   ```
   $ cd blog-hexo
   $ git submodule
   # 6c40f5ec27e1889c5a0a0a999e847634a33aef1c themes/apollo (heads/master)
   ```

# 多主机同步

多主机同步主要的坑在于主题的管理

Ref:

* [ 在 hexo 中使用 git submodules 管理主题 ](https://juejin.cn/post/6844903751908605965)



使用 submodule 配置好之后，在不同电脑间进行同步就非常简单了

1.  如果是新主机， 则clone项目并安装依赖ç

   ```shell
   git clone https://github.com/LYK-love/LYK-love.github.io
   cd LYK-love.github.io
   npm install
   ```

   老主机只需pull项目:

   ```
   git pull
   ```

2. 注意clone和pull都不会拉取拉取项目中的子模块， 因此需要

   ```she l
   # 如果是新主机，首先要git submodule init
   git submodule update
   ```

   * `git submodule init` 初始化本地配置文件

     `git submodule update` 从该项目中抓取所有数据并检出父项目中列出的合适的提交

     上述两命令可以合并为`git submodule update --init`

   * 也可在 clone 时使用 `git clone --recursive` 命令, git 就会自动初始化并更新仓库中的每一个子模块.

3. **拉取含子模块的修改**

主题作为子模块添加到项目中后, 若主题作者有更新, 便可通过两种方法来拉取主题的更新内容.

1. 进入`themes` 下主题目录, 执行 `git fetch` 和 `git merge origin/master` 来 merge 上游分支的修改
2. 直接运行 `git submodule update --remote`, Git 将会自动进入子模块然后抓取并更新

更新后重新提交一遍, 子模块新的跟踪信息便也会记录到仓库中.

]



## Bugs

* `hexo g` 会生成静态文件, 但是，如果你的目录下有失效的软链接， 就不会生成文件。 因此请删除所有的失效软链接
  * ref：[ Fixing Hexo Not Generating Files ](https://chrisbergeron.com/2020/12/24/fixing-hexo-not-generating-files/#:~:text=If%20you%E2%80%99re%20having%20trouble%20with%20Hexo%20not%20generating,l%20-exec%20test%20%21%20-e%20%7B%7D%20%3B%20-print)
* h



# Bugs

