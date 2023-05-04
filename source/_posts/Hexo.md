---
title: Hexo
tags:
  - Hexo
categories:
  - - Toolkit
date: 2023-05-04 21:29:03
---


本文介绍如何构建并配置Hexo站点.

<!--more-->

Refs:

* [Hexo官网](https://hexo.io/zh-cn/)
* 比较全的[Hexo + Next搭建教程](https://www.yuque.com/skyrin/coding/tm8yf5#xgq4yz), 其中有些内容有点老了

# Intro

My Dependency Version:

* Next Version: 8.15.1

* Hexo Version:  6.2.0

* hexo-cli Version: 4.3.0



Hexo是流行的静态博客框架, 同类的还有Hugo和Jekyl. Hexo的优点是对各种插件的支持更好, 自定义起来更方便, 同时使用更傻瓜, 可以更专注写作. 缺点是使用了npm, 因此无论是文章的编译还是网站的运行都比较慢.

我使用Hexo构建网站, 并且搭配Next主题.

Hexo的目录是`<hexo-dir>/`, 主题的目录是`<hexo-dir>/themes/next`.

Hexo的配置文件(aka `Hexo _config.yml`)位于`<hexo-dir>/_config.yml`, 主题(aka `Next _config.yml`)的配置文件位于`<hexo-dir>/themes/next/_config.yml`.



在本文中, 除非特殊说明, 否则编辑的都是Hexo配置文件( `<hexo-dir>/config.yml` ).

# Hexo Commands

| 命令                    | 描述                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `hexo init [folder]`    | 初始化网站                                                   |
| `hexo new [layout]`     | 新建文章, 默认是“post”, 我通过`default_layout: draft`设置为新建到“draft” |
| `hexo publish [layout]` | 发布草稿                                                     |
| `hexo g[enerate]`       | 生成静态文件.                                                |
| `hexo s[erver]`         | 启动本地服务器. 服务器会监听文件变化并自动更新               |
| `hexo d[eploy]`         | 在安装了deploy git 插件后, 可以生成本地文件并远程部署到GitPage. 再也不用`hexo d -g`了 |
| `hexo clean`            | 清理数据库和静态文件                                         |
| `hexo list`             | 列出站点信息                                                 |
| `hexo version`          | 版本信息                                                     |
| **`hexo d -g`**         | 生成并部署                                                   |

# Build Site with Hexo

1. 安装 Hexo:

   ```
   npm install -g hexo-cli
   ```

2. 在本地指定文件夹 `<folder>` 中建立项目:

   ```shell
   hexo init <folder>
   cd <folder>
   npm install
   ```

3. 新建完成后，指定文件夹 `<folder>` 的目录如下：

   ```plain
   .
   ├── _config.yml
   ├── package.json
   ├── scaffolds
   ├── source
   |   ├── _drafts
   |   └── _posts
   └── themes
   ```

   | 文件/文件夹  | 作用                                                         |
   | ------------ | ------------------------------------------------------------ |
   | _config.yml  | 网站的[配置](https://hexo.io/zh-cn/docs/configuration.html)文件 |
   | package.json | 应用程序的信息                                               |
   | scaffolds    | [模版](https://hexo.io/zh-cn/docs/templates.html)文件夹。当您新建文章时，Hexo 会根据 scaffold 来建立文件 |
   | source       | [资源文件夹](https://hexo.io/zh-cn/docs/asset-folders.html)是存放用户资源的地方。除 *posts 文件夹之外，开头命名为*  (下划线)的文件 / 文件夹和隐藏的文件将会被忽略。Markdown 和 HTML 文件会被解析并放到 public 文件夹，而其他文件会被拷贝过去 |
   | themes       | [主题](https://hexo.io/zh-cn/docs/themes.html)文件夹。Hexo 会根据主题来生成静态页面 |

4. 安装主题, 见下文


## Deploy to GitPage

GitPage 允许你将你的博客创建为一个 GitHub Project，通过 `your-account.github.io` 这样的特殊项目名称与 GitPage 进行关联，然后，你只需要像平时一样 commit 你的博文到 GitHub 上就 OK 了，GitPage 会自动将你的更新部署出去.

>  注意, 私有仓库的Gitpages也是可以公共访问的, 所以千万不要把含有敏感信息的私有仓库作为GitPages



1. 安装 deploy git 插件实现一键自动部署:

   ```sh
   npm install hexo-deployer-git --save
   ```

2. 在 GitHub 创建一个名为`<username>.github.io.git`的仓库。

3. 在主题配置文件`_config.yml`中修改仓库地址, 注意, 为了后文说的多主机同步. 我的仓库有两个分支. `master`用于存放生成的网页文件, `hexo`存放源文件. 部署当然是push网页文件, 也就是`master`分支:

   ```yaml
   deploy:
     type: git
     repo:
       github: git@github.com:LYK-love/LYK-love.github.io.git
     branch: master
   ```

4. GitPage可以关联到项目的任意分支, 我们要到仓库的Settings -> Code and automation -> Pages里, 把Pages关联到master分支. 这样我们部署到master的网页文件就可以同步到Pages上.

5. 执行`hexo d`即可部署到 GitHub 仓库。

6. 新增或修改主题配置后部署时请执行 `hexo clean && hexo d` 



注：`hexo-deployer-git`使用ssh而非 http，所以请先确保您已经在 GitHub 添加了公钥.



## Domain Name Config

1. 首先你需要去域名注册商（阿里云腾讯云等）买一个域名
2. 在根站点下`source`目录中添加`CNAME`文件，文件内容为您购买的域名`xxx.com`，不要添加`www`、`mail`等子域例如`www.xxx.com`或`mail.xxx.com`
3. 前往域名控制台解析此域名到`github.io`，根据 gitpage 的自定义域名要求，他们建议解析到`github.io`的数字 ip 地址，即`151.101.129.147`
4. 在控制台设置域名解析，添加 A 记录指向 `151.101.129.147` 即可
5. 命令行执行`hexo d`发布站点到 GitHub 库，这时在 Git 库应该就能看到 CNAME 文件，至此自定义域名设置完毕，现在使用`xxx.com`即可访问站点

# Hexo Doc

## Version

1. 查看本地Hexo版本:

   ```sh
   hexo version
   ```

2. 查看有哪些落后的版本:

   ```sh
   npm outdated
   ```

## Install

```sh
npm install -g hexo-cli
```



如果想要安装指定版本的Hexo, 网络上没有这类教程. 事实上这个需求本身也是很奇怪的. 

如果一定要这样做的话, 可以copy一份对应版本的Hexo的`package.json`, 然后`npm install`

## Upgrade

1. 安装hexo时需要安装hexo-cli(它包含了hexo在内的一大堆依赖), 而升级hexo只需升级所有插件:

   ```sh
   npm install -g npm-upgrade
   ```

   * `npm-upgrade`: 升级作为`dependency`的hexo

2. 查看是否更新成功:

   ```shell
   hexo version
   ```

## Uninstall

* Uninstall:

  ```sh
  npm uninstall hexo
  ```


# Markdown Engine

`hexo-renderer-markdown-it`的[默认配置](https://github.com/hexojs/hexo-renderer-markdown-it)是无法正确给标题添加anchor的, 需要做一些修改, 并将配置添加到Hexo中.



编辑 `Hexo _config.yml`,  插入以下内容:

```yaml
# Config of hexo-renderer-markdown-it
markdown:
  preset: 'default' # 渲染器默认预设 # "commonmark": 使用严格 CommandMark 规定. # "default": 默认配置, 类似于 GFM # "zero": 禁用所有预设.
  render:
    html: true
    xhtmlOut: false # 将 HTML 内容渲染为 XHTML 的形式 (XHTML 语法非常严格, 比如原 HTML 中的 <br> 标签必须要使用 <br/> 这样的形式进行 "自闭和") 可能会出现兼容性问题.
    langPrefix: 'language-'
    breaks: true # true 则将所有换行渲染为 <br> 标签 # 这种行为不属于 CommandMark 和 GFM.
    linkify: true # true 则自动解析链接并添加为 <a> 标签, false 则将链接渲染为文本.
    typographer: false # 默认 true # 自动转义各种排版用字符, 如 ©. 这甚至会转义掉LaTex中的字符, 所以不能开启
    quotes: '“”‘’' # 当 typographer 定义为 true 时的自动转换引号的行为, quotes: '“”‘’' 则表示将 "123" '123'转换为 “123” ‘123’
  enable_rules:
  disable_rules:
  plugins:
  anchors:
    level: 1 # 开始创建锚点的等级, 默认为2,表示从 H2 开始创建一直到 H6(最后).
    collisionSuffix: '' # 如果遇到重复的锚点 ID 为其添加数字编号时在这个数字后添加的后缀.
    permalink: true #  默认为false, 需要更改为true, 来创建一个除标题外带有固定地址的的锚点标签.
    permalinkClass: 'header-anchor'
    permalinkSide: 'left' # 设定为 right 则会在标题后添加固定链接.
    permalinkSymbol: '' # 更改为空字符串
    case: 0 # 转换锚点 ID 中的字母为大写或小写 # "0" 不转换, "1" 为小写, "2" 为大写. “不转换”是为了方便手写Anchor
    separator: '-' # 用于替换空格的符号. # 默认为 "-"
  # images:
  #   lazyload: false
  #   prepend_root: false
  #   post_asset: false
```



当然你也可以直接更改依赖的代码, 但是这样做无法进行版本管理, 所以**不推荐**:

1. 进入包目录:

   ```
   cd [hexo-site]/node_modules/hexo-renderer-markdown-it
   ```

2. 编辑`index.js`:

   ```java
   hexo.config.markdown.anchors = Object.assign({
     level: 2,
     collisionSuffix: '',
     permalink: true, //更改为true
     permalinkClass: 'header-anchor',
     permalinkSide: 'left',
     permalinkSymbol: '', //更改为空字符串
     case: 0,
     separator: '-'
   }, hexo.config.markdown.anchors);
   ```

## Render Anchor

如前所述, 只需要使用`hexo-renderer-markdown-it`, 并修改其配置文件, 就可以使文章Header自带Anchor, 实现页面内跳转.



例子: 

Markdown的一个标题: 

```markdown
// in markdown:
# Ha ha
dadads
```

会被Hexo渲染成:

```html
//in html
<id = "ha-ha">
<h1>dadads</h1>
```

* 空格会被转换为连字符, 大写会被转换为小写.
  * 由于我在`hexo-renderer-markdown-it`中的配置, 空格会被转换为`-`, 而大小写是**不转换**的

---

如果有重名的标题(即使处于不同的标题层次), 就会在html的标签的id属性中予以区分:

```markdown
// in markdown:
# haha
dadads

# Heihei
## Haha //重名了
asa
```

```html
//in html
<id = "haha-1">
<h1>dadads</h1>

<id = "haha-2"> //用数字后缀区分了
<h1>asa</h1>
```



因此, 只需要在markdown中写:

```
[显示的内容](#标题)
```

生成的Html是:

```
<a href="标题">显示的内容</a>
```

这就引用了对应的标题:

```
# 标题
```

可以看到, 这是基于Html的标签id匹配的, 而Markdown标题生成的Html标签的id和标题级别没有关系, 只和标题名字有关系. 所以

```markdown
[显示的内容](#KKK)
```

可以引用到:

```markdown
# Haha
## KKK
```

中的二级标题`KKK`



由于空格会被转换为`-`, 因此如果标题为:

```markdown
# Traditional Dead Lift
```

则应该这样引用:

```markdown
[显示的内容](#Traditional-Dead-Lift)
```

# Customization

## 网页加载加速

使用[hexo-filter-optimize](https://github.com/theme-next/hexo-filter-optimize)来提升网页加载速度:

1. 下载插件:

   ```
   npm install hexo-filter-optimize
   ```

2. 编辑配置文件:

   ```yaml
   filter_optimize:
     enable: true
     # remove the surrounding comments in each of the bundled files
     remove_comments: false
     css:
       # minify all css files
       minify: true
       # bundle loaded css files into one
       bundle: true
       # use a script block to load css elements dynamically
       delivery: true
       # make specific css content inline into the html page
       #   - only support the full path
       #   - default is ['css/main.css']
       inlines:
       excludes:
     js:
       # minify all js files
       minify: true
       # bundle loaded js files into one
       bundle: true
       excludes:
     # set the priority of this plugin,
     # lower means it will be executed first, default of Hexo is 10
     priority: 12
   ```

   

# Writing

* 默认新建的文章都是posts, 改成新建为drafts:

  ```yaml
  default_layout: draft
  ```

  这样`hexo new`新建的文章就都是drafts了.

* 文章可以有多个category, 分类具有顺序性和层次性, 有`3`种不同的编写方式

  ```yaml
  # 第一种
  categories:
    - Java
    - Servlet
  # 第二种
  categories: [Java, Servlet]
  # 第三种
  categories:
    -[Java]
    -[Servlet]
  ```

  前一、二种书写方式的作用一致，表示该文章分类于`Java/Servlet`下，起到了子分类的作用

  第三种书写方式起到了多分类的作用，表示该文章分类于`Java`和`Servlet`下

* 标签没有层次性:

  ```
  categories:
  - Diary
  tags:
  - PS3
  - Games
  ```

# Configuring Author

Edit Hexo config file and set the value of `author` to your nickname.

```yaml
Hexo config file
# Site
author:
```

# Configuring Description

Edit Hexo config file and set the value of `description` to your description, which can be a sentence you like.

```yaml
Hexo config file
# Site
description:
```

# Enabling Theme

Like all Hexo themes, after you download it, open Hexo config file, find `theme` option, and change its value to `next` (or another theme directory name).

Edit **Hexo config file**:

```yaml
theme: next
```

Now you have installed NexT theme and enabled it. The following steps will help you verify whether NexT is enabled correctly.

# Bugs

* `hexo g` 会生成静态文件, 但是，如果你的目录下有失效的软链接， 就不会生成文件。 因此请删除所有的失效软链接

  * ref：[ Fixing Hexo Not Generating Files ](https://chrisbergeron.com/2020/12/24/fixing-hexo-not-generating-files/#:~:text=If%20you%E2%80%99re%20having%20trouble%20with%20Hexo%20not%20generating,l%20-exec%20test%20%21%20-e%20%7B%7D%20%3B%20-print)

* hexo的markdown源代码避免出现**跨级标题结构**， 这里的*跨级*指的是不能从一个一级标题直接跟三级标题；二级标题后紧跟的子标题级别必须是三级标题

* 文章的Front-matter是YAML格式, 因此冒号后面必须有一个英文空格:

  ```markdown
  title: XX
  categories: XX
  tags: XX
  ```

  否则报错:

  > YAMLException: can not read a block mapping entry; a multiline key may not be an implicit key

* 极其罕见的Bug: Hexo和Next分别更新, 结果Latex不能显示, hexo g巨慢, 页面闪烁, back2top小箭头图表消失等等等等...

  由于JS项目的复杂性, 依赖版本问题几乎很难解决, 因此**遇到这种Bug就不要仔细研究了, 直接重装Hexo和Next吧.**

