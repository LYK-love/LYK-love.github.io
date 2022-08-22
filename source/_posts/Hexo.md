---
title: Hexo
categories: Toolkit
date: 2022-03-27 02:28:03
---

Outline

* Feateues
* 多主机同步
* Bugs

<!--more-->

# Intro

Hexo版本: 6.2.0

Next版本: 8.12.3

* [Hexo官网](https://hexo.io/zh-cn/)
* [NeXt官网](https://hexo-next.readthedocs.io/zh_CN/latest), 里面有几乎全部的主题配置教程
* [最新版(v8)NeXt仓库](https://github.com/next-theme/hexo-theme-next)
* [Next官方的博客](https://theme-next.js.org/)
* [Awesome NexT](https://github.com/theme-next/awesome-next) : 有很多别人的Next博客, 非常值得借鉴



本文档参考了:

* 比较全的[Hexo + Next搭建教程](https://www.yuque.com/skyrin/coding/tm8yf5#xgq4yz), 其中有些内容有点老了



Hexo是流行的静态博客框架, 同类的还有Hugo和Jekyl. Hexo的优点是, 它的Next主题比较好看. 本文介绍Hexo + Next的配置.

主题文件都存放在`<hexo-dir>/themes/`, 例如Next主题就位于`<hexo-dir>/themes/next/_config.yml`. **但是**, 由于下面讲的多主机同步的原因, 实际起作用的主题配置文件是`<hexo>/_cofig.next.yml`



Hexo的配置文件位于Hexo目录的`_config.yml`

Next的配置目录位于`<hexo>/_cofig.next.yml`.

在主题配置中, 除非特殊说明, 编辑都是主题配置文件. 同理, 对于Hexo的配置, 除非特殊说明, 编辑的都是Hexo配置文件

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

# Hexo搭建

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

4. 下载主题: 由于下文说的多主机同步的原因, 我直接新开了一个[自己的主题仓库](https://github.com/LYK-love/Next)

   ```shell
   cd <your-hexo-site>
   git clone git@github.com:LYK-love/Next.git
   ```

5. 启用主题:

   编辑 hexo配置文件:

   ```yaml
   theme: next
   ```

# Hexo配置

## 部署到GitPage

GitPage 允许你将你的博客创建为一个 GitHub Project，通过 `your-account.github.io` 这样的特殊项目名称与 GitPage 进行关联，然后，你只需要像平时一样 commit 你的博文到 GitHub 上就 OK 了，GitPage 会自动将你的更新部署出去.

>  注意, 私有仓库的Gitpages也是可以公共访问的, 所以千万不要把含有敏感信息的私有仓库作为GitPages



1. 安装 deploy git 插件实现一键自动部署:

   ```plain
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



注：这里使用 ssh 协议而非 http，所以请先确保您已经在 GitHub 添加了公钥.

## 自定义域名



1. 首先你需要去域名注册商（阿里云腾讯云等）买一个域名
2. 在根站点下`source`目录中添加`CNAME`文件，文件内容为您购买的域名`xxx.com`，不要添加`www`、`mail`等子域例如`www.xxx.com`或`mail.xxx.com`
3. 前往域名控制台解析此域名到`github.io`，根据 gitpage 的自定义域名要求，他们建议解析到`github.io`的数字 ip 地址，即`151.101.129.147`
4. 在控制台设置域名解析，添加 A 记录指向 `151.101.129.147` 即可
5. 命令行执行`hexo d`发布站点到 GitHub 库，这时在 Git 库应该就能看到 CNAME 文件，至此自定义域名设置完毕，现在使用`xxx.com`即可访问站点

## 写作

* 默认新建文章都是posts, 改成新建为drafts:

  ```yaml
  default_layout: draft
  ```

  这样`hexo new`新建的就都是草稿了
  
* 往往一片文章会有多个类别标签，有`3`种不同的编写方式

  ```
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

# NeXt配置

[进阶配置](https://convivae.top/posts/hexo-bo-ke-cai-keng/)

* 设置站点图标:

  ```yaml
  favicon:
    # small: /images/favicon-16x16-next.png
    small: /images/white_flower1.jpg
    # medium: /images/favicon-32x32-next.png
    medium: /images/white_flower1.jpg
    # apple_touch_icon: /images/apple-touch-icon-next.png
    apple_touch_icon: /images/white_flower1.jpg
  ```

* 设置菜单: 真不知道about页面有啥用

  ```yaml
  menu:
    home: / || home
    # about: /about/ || user
    tags: /tags/ || tags
    categories: /categories/ || th
    archives: /archives/ || archive
    #schedule: /schedule/ || calendar
    #sitemap: /sitemap.xml || sitemap
    #commonweal: /404/ || heartbeat
  
  # Enable / Disable menu icons / item badges.
  menu_settings:
    icons: true
    badges: false
  ```

* 设置sidebar avatar, 并且让图片圆形显示

  ```yaml
  # Sidebar Avatar
  avatar:
    # Replace the default image and set the url here.
    url: /images/white_flower1.jpg
    # If true, the avatar will be displayed in circle.
    # 圆形显示
    rounded: true
    # If true, the avatar will be rotated with the cursor.
    rotated: false
  ```

  头像必须存放在`<next>/themes/source/images/`

  

  

* Schemes: 目前觉得Mist比较好看

  ```yaml
  # Schemes
  # scheme: Muse
  scheme: Mist
  # scheme: Pisces
  # scheme: Gemini
  ```

  

* 设置语言: 我使用默认的英语. 如果要使用汉语, 可以编辑主题配置文件:

  ```yaml
  language: zh-CN
  ```

  

* 首页文章显示摘要: 在文章中适当位置插入 `<!--more-->`，该位置之前的部分即为摘要，会显示在首页中.




* sidebar社交链接: 邮箱前要加`mailto:`, 这还是我用开发者工具查别人的网站发现的..( 其实mailto是html中发送email的代码 )

  ```yaml
  social:
    GitHub: https://github.com/LYK-love || fab fa-github
    E-Mail: mailto:191820133@smail.nju.edu.cn || fa fa-envelope
  ```

* sidebar社交链接的图案:

  ```yaml
  social_icons:
    enable: true
    icons_only: false
    transition: false
  ```

  

* 添加建站时间, 不加的话就会显示当前年份:

  ```yaml
  footer:
    # Specify the date when the site was setup. If not defined, current year will be used.
    since: 2021
  ```

* 关掉闪烁:

  ```yaml
  quicklink:
    enable: false
  ```
  
* Toc: Table of Contents in the Sidebar. 主要是sidebar里面的标题要不要自动进行数字编号. 默认为true. 我不喜欢编号：

  ```yaml
  toc:
    enable: true
    # Automatically add list number to toc.
    number: false
  ```

  

## 搜索服务

使用本地搜索，按以下步骤配置：

1. 安装 hexo-generator-searchdb 插件：加了这个之后,博客生成时间要慢好几秒, 不过也是值得的

   ```shell
   npm install hexo-generator-searchdb --save
   ```

2. 编辑Hexo配置文件 `_config.yml`：

   ```yaml
   search:
     path: search.xml
     field: post
     format: html
     limit: 10000
   ```

3. 编辑Next配置文件：

   ```yaml
   # Local search
   local_search:
     enable: true
   ```



## 百度统计

当然也可以添加Google统计, 都差不多

1. 开通百度统计帐号: 在 [**百度统计**](https://tongji.baidu.com/web/welcome/login) 注册帐号. 帐号注册成功后，在侧边栏`账户管理 -> 网站列表`，点击右侧`新增网站`按钮

2. 添加`网站域名/网站首页`信息后，点击`确定`按钮，百度统计会提供一段`JS`脚本用于嵌入

   ```javascript
   <script>
   var _hmt = _hmt || [];
   (function() {
     var hm = document.createElement("script");
     hm.src = "https://hm.baidu.com/hm.js?<app-id>";
     var s = document.getElementsByTagName("script")[0]; 
     s.parentNode.insertBefore(hm, s);
   })();
   </script>
   ```

3. 粘贴上面代码中的`<app-id>, 复制到主题配置文件:

   ```
   baidu_analytics: <app-id>
   ```

   * Next主题已对百度统计进行配置优化，因此只需要编辑配置文件, 填写`app-id`. 对于更一般的情况, 需要把上面的JS代码添加到网站全部页面的 `</head>` 标签前.

4. 如果代码安装正确，一般20分钟后，可以查看网站分析数据.





## Math

[Next数学公式支持官方文档](https://github.com/theme-next/hexo-theme-next/blob/master/docs/zh-CN/MATH.md)

目前Latex的渲染引擎有 [MathJax](https://www.mathjax.org/) 和 [Katex](https://khan.github.io/KaTeX/), `MathJax`完美支持Latex, `Katex`速度更快, 但是有些语法不支持. 综合来看还是选择Mathjax.

`NexT`默认使用的markdown渲染引擎是`hexo-renderer-marked`, 它支持`MathJax`, 但支持得不好. 

Next还支持两个渲染引擎:

- `hexo-renderer-pandoc`：很好地支持`MathJax`
- [hexo-renderer-kramed](https://github.com/sun11/hexo-renderer-kramed): 亲测它比`hexo-renderer-pandoc`**快一点**. 但是有bug, 需要自己配置. 由于它太老了,就不推荐了. 
- `hexo-renderer-markdown-it-plus/hexo-renderer-markdown-it`：支持`KeTex`
- [hexo-filter-mathjax](https://github.com/next-theme/hexo-filter-mathjax): 这是个server端端hexo渲染引擎. 要使用它,需要卸载掉其他latex引擎( 当然, 你得保留一个`hexo-renderer-marked` 来渲染markdown ). 它的缺点是有些语法不支持, 而且无法渲染目录里的LaTex.

 我们一般选择`hexo-renderer-pandoc`





### 支持MathJax

支持Latex步骤:

1. 卸载`hexo-renderer-marked`, 安装`hexo-renderer-pandoc`:

   ```shell
   npm un hexo-renderer-marked
   npm i hexo-renderer-pandoc --save
   ```

2. 额外需要安装[pandoc](https://github.com/jgm/pandoc/blob/master/INSTALL.md): for Mac

   ```shell
   brew install pandoc
   ```

3. 开启mathjax:

   ```yaml
   math:
     # Default (false) will load mathjax / katex script on demand.
     # That is it only render those page which has `mathjax: true` in front-matter.
     # If you set it to true, it will load mathjax / katex script EVERY PAGE.
     every_page: false
   
     # hexo-renderer-pandoc (or hexo-renderer-kramed) required for full MathJax support.
     mathjax:
       enable: true
       # See: https://mhchem.github.io/MathJax-mhchem/
       mhchem: true
   ```

   * `per_page`: 设置为false, 这样只会渲染添加了`mathjax: true`的文章
     * 在低版本的NeXt,这句话上面的注释是反的, 即“false”只会渲染指定文章. 

4. 在需要渲染Latex的文章的Front-matter里打开mathjax开关，如下：

   ```markdown
   ---
   title: index.html
   date: 2016-12-28 21:01:30
   tags:
   mathjax: true
   --
   ```

### 高级Mathjax特性

在新版本的 NexT 主题中，我们加入了公式自动编号和引用功能。下面简要介绍一下如何使用这项功能。

为了使用这项功能，一般来说，你必须把所使用的 LaTeX 公式放在 `equation` 环境里面，采用旧的方法（也就是说，仅仅把公式的每一边用两个 $ 符号包含起来）是无效的。如何引用公式？你只需要在书写公式的时候给公式一个 `\label{}` 标记（tag），然后在正文中，可以使用 `\ref{}` 或者 `\eqref{}` 命令来引用对应的公式。使用 `\eqref{}` 是推荐的方式，因为如果你使用 `\ref{}`，公式在文中的引用编号将没有圆括号包围。下面介绍几种常见的公式编号例子。

对于简单的公式，使用下面的方式给公式一个标记，

```
$$\begin{equation}\label{eq1}
e=mc^2
\end{equation}$$
```

然后，在正文中，你可以轻松引用上述公式，一个简单的例子如下：

```
著名的质能方程 $\eqref{eq1}$ 由爱因斯坦提出 ...
```

对于多行公式，在 `equation` 环境中，你可以使用 `aligned` 环境把公式分成多行，

```
$$\begin{equation}\label{eq2}
\begin{aligned}
a &= b + c \\
  &= d + e + f + g \\
  &= h + i
\end{aligned}
\end{equation}$$
```

要对齐多个公式，我们需要使用 `align` 环境。align 环境中的每个公式都有自己的编号：

```
$$\begin{align}
a &= b + c \label{eq3} \\
x &= yz \label{eq4}\\
l &= m - n \label{eq5}
\end{align}$$
```

在 `align` 环境中，如果你不想给某个或某几个公式编号，那么在这些公式后面使用 [`\nonumber`](https://tex.stackexchange.com/questions/17528/show-equation-number-only-once-in-align-environment) 命令即可。例如：

```
$$\begin{align}
-4 + 5x &= 2+y \nonumber  \\
 w+2 &= -1+w \\
 ab &= cb
\end{align}$$
```

有时，你可能会希望采用更加奇特的方式来标记和引用你的公式，你可以通过使用 `\tag{}` 命令来实现，例如：

```
$$x+1\over\sqrt{1-x^2} \tag{i}\label{eq_tag}$$
```

如果你想要了解更多信息，请访问 [MathJax 关于公式编号的官方文档](https://docs.mathjax.org/en/latest/input/tex/eqnumbers.html)。同时，你也可以阅读 [这篇文档](https://theme-next.org/docs/third-party-services/math-equations) 来获取更多细节信息。

## 字体

默认字体(`font: false`)是温软雅黑, 还挺好看的. 当然也可以自己改字体.

```yaml
font:
  enable: false
```

低版本的Next的`font: false`的中文巨丑, 将`font`设为true,之后比原来好看了..

但我也不知道新字体是啥

## 代码块

* 代码高亮: 这个网站可以预览所有高亮效果：[传送门](https://theme-next.js.org/highlight/)

  我使用highlight作为高亮引擎, 高亮用`arduino-light`

* 我没有设置代码块行号



主题配置文件:

```yaml
codeblock:
  # Code Highlight theme
  # All available themes: https://theme-next.js.org/highlight/
  theme:
    # light: default
    # dark: stackoverflow-dark
    light: arduino-light
    dark: arduino-light
  prism:
    light: vs
    dark: vs
  # Add copy button on codeblock
  copy_button:
    enable: true
    # Available values: default | flat | mac
    style: flat
```



Hexo项目配置文件:

```yaml
highlight:
  enable: true
  line_number: false
  auto_detect: false
  tab_replace: ''
  wrap: true
  hljs: false
prismjs:
  enable: false
  preprocess: true
  line_number: true
  tab_replace: ''
```



## 图像缩放

`NexT`集成了多种图像显示工具, 包括`FancyBox`和`MediumZoom`, 主要功能是图像缩放.

开启`MediumZoom`:

```
# A JavaScript library for zooming images like Medium.
# Warning: Do not enable both `fancybox` and `mediumzoom`.
# For more information: https://medium-zoom.francoischalifour.com
mediumzoom: true
```

## 图像懒加载

```
npm install hexo-lazyload --save
```

```
lazyload: true
```



## 访客人数&&文章阅读次数

`NexT`主题已集成了不蒜子的访客人数和文章阅读统计功能:

```yaml
# Show Views / Visitors of the website / page with busuanzi.
# Get more information on http://ibruce.info/2015/04/04/busuanzi
busuanzi_count:
  enable: true
  total_visitors: true
  total_visitors_icon: user fa fa-user
  total_views: true
  total_views_icon: eye fa fa-eye
  post_views: true
  post_views_icon: eye fa fa-eye
```

- 在首页显示文章的阅读次数
- 点击全文阅读显示阅读次数
- 在底部可以看见访客人数和文章阅读次数

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

   

## back2top button

back2top button非常好看, 默认是添加的:

```
back2top:
  enable: true
  # Back to top in sidebar. button默认出现在左下角, 如果这里为true,就会出现在sidebar里面(头像, 目录下面),很难察觉
  # 所以我设为false
  sidebar: false
  # Scroll percent label in b2t button.
  # 让to-top的小箭头随时显示数值, 我觉得这样破坏阅读体验, 所以为false
  scrollpercent: false
```



这里有个[插件](https://github.com/jiangtj-lab/hexo-cake-moon-menu), 不过已经不需要了. 自带的就很好看.



## 版权

选择`sidebar`, 会在sidebar出现一个小徽章, 不怎么碍眼. 如果选择`post`, 版权信息会出现在文章底部, 很难看.



```yaml
# Creative Commons 4.0 International License.
# See: https://creativecommons.org/about/cclicenses/
creative_commons:
  # Available values: by | by-nc | by-nc-nd | by-nc-sa | by-nd | by-sa | cc-zero
  license: by-nc-sa
  # Available values: big | small
  size: small
  sidebar: true
  post: false
  # You can set a language value if you prefer a translated version of CC license, e.g. deed.zh
  # CC licenses are available in 39 languages, you can find the specific and correct abbreviation you need on https://creativecommons.org
  language:
```



## 一些不想用的美化

以下美化我都不想用, 只是给出添加方式.

* 添加版权信息: 版权信息很丑, 所以我没加

  ```yaml
  creative_commons:
   
    license: by-nc-sa
   
    sidebar: true
   
    post: true
  ```

* 添加评论系统. 我不想加 

* 夜间模式: 这是永久的, 不能手动切换, 所以我也不想加. 

  ```
  darkmode: true
  ```

* Reading progress bar: 五颜六色的,影响观看:

  ```yaml
  reading_progress: Reading progress bar
  
    enable: false
  ```
  
  
  
  

# 多主机同步

多主机同步主要的坑在于主题的管理

Ref:

* [ 在 hexo 中使用 git submodules 管理主题 ](https://juejin.cn/post/6844903751908605965)

## 多分支

在安装插件后,`hexo d`会生成网页文件, 并将其部署到GitHub和GitPage. 但是不会把源文件也push到github. 我们需要:

1. 在Github建两个分支,分别管理生成的网页文件和源文件:

   * master: 用于存放`hexo d `部署的网页文件
   * hexo: 用于项目源文件, 包括文档源文件

2. 在Github仓库`->Settings->Branches->Default branch`中将默认分支设为`Hexo`. 这样每次手动push源文件,都到hexo分支.

   当然也可以每次都手动指定,这样很蠢:

   ```shell
   git push origin hexo
   ```

3. 而我们的`hexo d`会把生成的网页文件同步到master分支. 这是之前配置`hexo d`插件时设置的:

   ```yaml
   deploy:
     type: git
     repo:
       github: git@github.com:LYK-love/LYK-love.github.io.git
     branch: master
   ```


## 多主机同步的问题

我们看到, Hexo添加主题的一般流程是 `clone` 主题到对应的 `themes`目录中，然后编辑Hexo的配置文件. 但是, 主题是一个独立的github仓库, 有自己的 `.git` 文件夹, 也就是说**本地的主题项目是嵌套在Hexo项目内的字仓库**. 

**当push本地仓库时, 是不会push子仓库的**, 证据就是, 在github上查看网站项目仓库, 点进`<repository>/themes/`, 会发现`next`文件夹有个很奇怪的名字: `[next @ XXXXX`, 点击它, 会跳转到该主题文件夹对应的github项目. 这说明**本地的主题文件夹是一个子项目, 从来没有随着父项目一起被push到github上**.

因此, 当有新主机**clone**你的hexo仓库时( 比如它要参与多主机同步 ), 它clone下的主题文件夹是空的. 

比如, 我用next主题, 当我买了台新电脑, 想要在它上面同步我开发的hexo. clone下我的网站, 发现项目内`themes/next`为空. 这样就无法正确生成网站页面了. 

> 该Bug的表面结果是: hexo生成的`index.html`也为空( 0kb )



事实上,主题文件夹不仅不会被push, 每次主题更新时,都会被overwritten, 所以不要更改主题文件夹到任何内容.

对于**主题配置文件**. Next官方提供[Alternate Theme Config机制](https://theme-next.js.org/docs/getting-started/configuration)来让用户自定义主题配置:

1. 把主题配置文件复制到Hexo项目目录下, 取名为 `_config.[name].yml`. Replace `[name]` with the value of `theme` option in Hexo config file. For NexT theme, the file name is `_config.next.yml` by default
2. 现在主题的配置文件就会读取Hexo项目目录的`_config.[name].yml`, 而不是主题目录的`_config.yml`. 由于位于Hexo项目目录下, `_config.[name].yml`会随着每次的push被push到Hexo项目的仓库. 不用担心**子项目问题**
3. 多主机同步时, 新主机只需clone

对于其他文件, 比如CSS之类, 反正我是不会改的, 所以无所谓. 但是images文件存放了我自定义的图像, 所以也得改. 目前看来没有什么解决方案. 只能把图片存放在Hexo项目文件夹,然后每次更新主题, 都把图片copy进主题文件夹内.

下面介文的**@Deprecated 同步步骤**是被废弃的方案, 它使用git modules, 这种方案新建了主题仓库, 然后用git module同步整个主题文件夹, 问题在于这样做就**没法进行主题的更新**了, 因此废弃

## @New 同步步骤

老主机只需`git pull`就行了.



对于本地还没有hexo项目的新主机, 需要:

1. clone自己的Hexo项目并初始化:

   ```shell
   git clone https://github.com/LYK-love/LYK-love.github.io
   cd LYK-love.github.io
   npm install
   ```

2. 由于下文介绍的Next主题的Alternate Theme Config机制, 主题配置文件已经在Hexo项目文件夹中被我们clone下来了, 也就是说已经同步了, 万事大吉.

3. 但是, images等文件没有同步, 我把images放在Hexo项目文件夹下, 需要手动把它copy到主机文件夹的`source/images`中

   

## @Deprecated 同步步骤

**注: 该方案已经被废弃**

在Hexo多主机同步时, 我们当然希望自己的主题配置文件也同步. 

---

**Bad Practice**: 由于本地的主题项目没办法push, 新主机就只能每次只clone 自己Hexo项目, 然后重新clone官方的主题. 这样做是愚蠢的. 多台机子上开发, 每台的本地都是不同的主题项目, 每次生成网页文件,样式都不一样.

---

因此, 我们需要**有一个自己的主题项目, 来对主题也进行版本管理**. 可以fork官方主题项目, 但我为了方便, 直接创建了[自己的主题项目](https://github.com/LYK-love/Next).

### Old Hosts

对于已经加入多主机同步的主机来说, 如果本地更改了主题. 那么每次除了push Hexo项目文件, 还得把再把主题项目文件也push. 否则主题配置的更改是没法同步到Github的.

---

push子项目:

```shell
cd ./themes/next
git add . && git commit -m"XXX"
git push
```

---

要在pull Hexo项目时顺便拉取子项目( 主题项目 ), 这称为update submodule:

```shell
# 把项目的子项目也pull下来
git submodule update --init
```



当然也可以pull Hexo后手动再pull子项目,这样很蠢:

```shell
cd ./themes/next
git pull
```

### New Hosts

对于要加入多主机同步的新主机来说, 要把主题文件当作git submodule, 在初始化阶段, 先同步Hexo, 再同步主题.

1. clone自己的Hexo项目并初始化:

   ```shell
   git clone https://github.com/LYK-love/LYK-love.github.io
   cd LYK-love.github.io
   npm install
   ```

2. 将主题作为submodule添加进来:

   ```shell
   cd blog-hexo
   git submodule add https://github.com/LYK-love/next themes/next
   ```

   * `git submodule add <sub-module-registry>`:  git 会将主题项目( 也就是我的`next`项目 )作为一个submodule,  clone 到 `themes/hexo` 中. 

     * 同时 hexo 项目中会生成一个 `.gitmodules` 文件, 这个配置文件中保存了项目 URL 与已经拉取的本地目录之间的映射.

   * `.gitmodules 文件内容`:

     ```
     > cat .gitmodules
     [submodule "themes/next"]
     	path = themes/next
     	url = git@github.com:LYK-love/next.git
     ```

   

3. update submudule, 第一次update时要加`--init`选项:

   ```shell
   git submodule update --init
   ```

   * 也可在 clone 父项目时直接使用 `git clone --recursive` , git 也会pull所有的子项目.

4. 现在新主机已经加入多主机同步, 变成Old Hosts了.





## Bugs

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

  YAMLException: can not read a block mapping entry; a multiline key may not be an implicit key

* 如果表哥多了行/列,在显示时会很丑

* 极其罕见的Bug, 花了我大半天: Hexo和Next分别更新, 结果Latex不能显示, hexo g巨慢, 页面闪烁, back2top小箭头图表消失等等等等... 最好他居然神奇地好了. 我猜是package.json冲突了. 不过具体原因我也不知道... .气死我了.

# Hexo Upgrade

如果想要安装指定版本的Hexo, 网上都没有教程. 我的做法是抄一份指定版本的`package.json`然后`npm install`

1. 查看本地Hexo版本:

   ```sh
   hexo version
   ```

2. 查看有哪些落后的版本:

   ```sh
   npm outdated
   ```

3. 升级所有插件:

   ```sh
   npm install -g npm-upgrade
   ```

4. 升级作为`dependency`的hexo:

   ```sh
   npm-upgrade
   ```

   此时package.json里的hexo -> version字段依然是老版本, 只有"dependencies"字段是新版本

5. 升级hexo:

   ```shell
   npm install
   ```

6. 查看是否更新成功:

   ```shell
   hexo version
   ```

   

   

   
   
   

# NeXt Upgrade

NexT 每个月都会发布新版本

[安装文档](https://theme-next.js.org/docs/getting-started/installation.html)

NeXt < 8的版本好像没办法查看, 

Next >=8 之后, 每次`hexo s/d`时在命令行的输出里都有Next版本信息. 此外`hexo version`也会显示next版本.



Next更新步骤: 首先要更新到最新的Hexo

1. 备份old主题文件夹的文件. 由于该文件夹一般什么都不会改,所以不备份也没啥关系

2. 把旧主题文件夹rename为`next-old`

3. clone新的主题仓库:

   ```shell
   git clone https://github.com/next-theme/hexo-theme-next themes/next
   ```



当然, 如果已经采用了Alternate Theme Config的话, 就可以平滑地升级:

```
git pull
```



[https://hexo-next.readthedocs.io/zh_CN/latest]: 
