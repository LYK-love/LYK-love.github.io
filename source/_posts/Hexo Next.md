---
title: Hexo Next
categories: 
- [Toolkit]
tags:
- Hexo
date: 2022-03-27 02:28:03
---

在[之前的文章](https://lyk-love.cn/2023/05/05/Hexo/)中, 我介绍了如何使用Hexo来构建静态站点. Hexo有很多主题, 其中我认为最好看最好用的是Hexo Next theme. 本文介绍如何使用和配置Next theme, 以及如何对Hexo和Next进行多主机同步.

<!--more-->

Refs:

* [NeXt Tutor](https://hexo-next.readthedocs.io/zh_CN/latest), 里面有几乎全部的主题配置教程
* [最新版(v8)NeXt Github仓库](https://github.com/next-theme/hexo-theme-next)
* [Next Official Blog](https://theme-next.js.org/)
* [Awesome NexT](https://github.com/theme-next/awesome-next) : 有很多别人的Next博客, 非常值得借鉴

# Intro

My Dependency Version:

* Next Version: 8.15.1

* Hexo Version:  6.2.0

* hexo-cli Version: 4.3.0



在本文中, 除非特殊说明, 否则编辑的都是主题配置文件( aka `NexT _config.yml` ), 由于使用了Alternate Theme Config, 因此主题配置文件位置是`<hexo>/_cofig.next.yml`.

# Config File Features

在之前关于[Hexo](https://lyk-love.cn/2023/05/05/Hexo/)的文章中, 我说过主题目录(`<hexo-dir>/themes/next`)和网站目录(`<hexo-dir>/`)是不同的. 主题的配置文件, 样式文件等, 都在主题目录下, 因此如果想要修改主题的配置, 也需要更改主题目录下的对应文件.

但是, [下文](#Installation)会讲到, 主题要么用npm下载, 要么用git下载, 无论哪种方式都会对主题进行版本管理. 我用的是git, 对主题目录下的文件做的更改会在之后`git pull`时被上游仓库的代码覆盖. 这使得对主题做自定义的配置很麻烦.

为此, Next提供了 [Alternate Theme Config](https://theme-next.js.org/docs/getting-started/configuration.html),  [Data Files](https://hexo.io/docs/data-files) 和 [Custom Files](https://theme-next.js.org/docs/advanced-settings/custom-files.html) feature, 使得我们可以把Next的配置文件, 样式文件和其他的文件copy到`<hexo-dir>/source/_data/`(这就是 [Data Files](https://hexo.io/docs/data-files)), 然后修改Data files, 并让用它们来覆盖主题目录下的对应文件(这就是 [Custom Files](https://theme-next.js.org/docs/advanced-settings/custom-files.html)  )被加载.

因此, 所有对主题的变更都会放在网站目录而不是主题目录, 主题目录下的内容不需要做变动, 可以很方便地进行版本管理.

* [Alternate Theme Config](https://theme-next.js.org/docs/getting-started/configuration.html): Next的配置文件可以放在`<hexo>/_cofig.next.yml`,这会覆盖`<hexo-dir>/themes/next/_config.yml`.
*  [Data Files](https://hexo.io/docs/data-files): 可以把Next的样式文件放在`<hexo-dir>/source/_data/`
*  [Custom Files](https://theme-next.js.org/docs/advanced-settings/custom-files.html): 可以在Next配置文件中, 指定Data files来替换掉主题目录下的对应文件. 



当然了, 不是所有主题都像Next一样提供了这些机制. 在这些主题中, 要想对主题做更改, 就得改主题目录下的文件. 此时如果要接受主题官方的更新, 就得把原来的主题目录备份, pull更新后再仔细地修改回去, 这非常麻烦. 对于这种情况, 我的建议是:

* 要么别对主题做任何修改.
* 要么就不接受官方的更新, 直接把官方主题fork下来作为自己的仓库, 之后就和这个仓库做同步, 也就是[对主题做单独的版本管理](#Apply-separate-version-control-to-themes).



## Alternate Theme Config

1. 把主题配置文件复制到Hexo项目目录下, 取名为 `_config.[name].yml`. Replace `[name]` with the value of `theme` option in Hexo config file. For NexT theme, the file name is `_config.next.yml` by default

2. 现在主题的配置文件就会读取Hexo项目目录的`_config.[name].yml`, 而不是主题目录的`_config.yml`. 由于位于Hexo项目目录下, `_config.[name].yml`会随着每次的push被push到Hexo项目的仓库. 不用担心**子项目问题**

3. 多主机同步时, 新主机只需clone整个项目:

   ```sh
   git clone https://github.com/LYK-love/LYK-love.github.io
   ```


# Next Doc

* [Next Official Doc](https://theme-next.js.org/)
* [Next Github Repo](https://github.com/next-theme/hexo-theme-next)

尽量以官方文档为准, Github repo上只有很少的信息. 此外, Next在Github上存在多个Github repo, 除了[Next Github Repo](https://github.com/next-theme/hexo-theme-next)之外的Repo都已经过时了, 请不要被混淆. 例如该repo: 

* https://github.com/theme-next/hexo-theme-next

就是一个过时的repo, 其next版本只到7.8.0. 而直到本文写作时, next版本已经达到8.15.1了, 因此要注意区分.



## Version

NeXt < 8 好像没办法查看版本

Next >=8 之后, 每次`hexo s/d`时在命令行的输出里都有Next版本信息. 此外`hexo version`也会显示next版本.

## Installation

[Next Official Doc: Installation](https://theme-next.js.org/docs/getting-started/installation.html)

无论是下载还是更新Next, 都要先更新到最新的Hexo.

为了及时收到Next官方的更新, 我就不单独开一个github仓库对主题做版本管理了.

### Using npm

```sh
npm install hexo-theme-next@latest
```

* npm会把主题文件夹下载到`/node_modules/hexo-theme-next`

### Using git

In hexo directory:

```sh
git clone https://github.com/next-theme/hexo-theme-next themes/next
```

* 注意, 如果在`themes/`下已经存在了主题文件夹, 则Hexo会忽略`node_modules/`中可能存在的主题文件夹, 使用`themes`下的. 也就是说git安装的主题会覆盖npm安装的主题.
* 我选择用git来安装, 原因是这样做可以比较方便地跳转到主题目录去看Next的源代码.

## After Installation

安装成功后就可以使用了, 命令行输入如下:

```
❯ hexo s
INFO  Validating config
INFO  ==================================
  ███╗   ██╗███████╗██╗  ██╗████████╗
  ████╗  ██║██╔════╝╚██╗██╔╝╚══██╔══╝
  ██╔██╗ ██║█████╗   ╚███╔╝    ██║
  ██║╚██╗██║██╔══╝   ██╔██╗    ██║
  ██║ ╚████║███████╗██╔╝ ██╗   ██║
  ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝   ╚═╝
========================================
NexT version 8.15.1
Documentation: https://theme-next.js.org
========================================
INFO  Start processing
INFO  Hexo is running at http://localhost:4000/ . Press Ctrl+C to stop.
```



## Upgrade

已经采用了Alternate Theme Config, 因此可以平滑地升级:

1. `cd themes/next`
2. `git pull`



保险起见, 可以备份old主题文件夹的文件, 把旧主题文件夹rename为`next-old`. 当然, 我不会更改主题目录下的任何文件, 因此不备份也没关系.

# Next Theme Config

[进阶配置](https://convivae.top/posts/hexo-bo-ke-cai-keng/)

* **Important: 关闭页面动画效果**:

  ```yaml
  # Use Animate.css to animate everything.
  # For more information: https://animate.style
  # 千万不要打开, 否则页面每次跳转都会有个渐变效果, 慢得要死. 关闭后网站速度会大幅提升.
  motion:
    enable: false
    async: false
  ```
  
  实测这样做会让网站速度大幅提升, 彻底达到可用水平.
  
* Scheme: 目前觉得Mist比较好看.

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


## Configuring Favicon

By default the Hexo site use NexT favicons in `[hexo-site]/themes/next/source/images/` directory with different size for different device. You can replace them with your own favicons.

但是, 如果使用npm安装Next, 则主题文件夹是`[hexo-site]/node_modules/hexo-theme-next`, 无法进行版本管理. 

因此, Hexo也支持将图片放在`[hexo-site]/source/images/`. 我也**强烈推荐**这么做, 这样就可以进行版本管理了:

1. 先手动创建文件夹: 

   ```sh
   cd [hexo-site]/source
   mkdir images
   ```

2. 后续在Next配置文件中使用`images`路径来找到图片:

   * 由于`themes/next/source/images/`和`source/images/`都可以放图片, 该操作实际上会扫描这两个文件夹

```
mkdir images
```



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

  

  

## Local Search

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



## Baidu Analysis

也可以添加Google统计, 都差不多

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

# Macros

https://theme-next.js.org/docs/tag-plugins/



```
{% label primary@<text> %}
```

可以把`<text>`变成紫色.



```
{% note default <text> %}
...

{% endnote %}
```



```
{% note warning %}

{% endnote %}
```



```
{% note info %}
The following examples are rendered by `mathjax` engine.
{% endnote %}
```

# Anchor

在 `<hexo>/themes/next/source/css/_common/components/post/post-body.styl`有如下代码:

```css
  h1, h2, h3, h4, h5, h6 {
    // Supported plugins: hexo-renderer-markdown-it hexo-renderer-marked
    .header-anchor, .headerlink {
      border-bottom-style: none;
      color: inherit;
      float: right;
      font-size: $font-size-small;
      margin-left: 10px;
      opacity: 0;

      &::before {
        font-family-icons('\f0c1');
      }
    }
```

它给文章的各级标题配置了anchor.

但是正如注释所说, 它只支持`hexo-renderer-markdown-it`,  `hexo-renderer-marked` 这两个renderer, 后者是next的默认renderer. 

由于我们要使用pandoc作为renderer, 所以只能放弃anchor功能.



不过, 通过模仿其他Next网站的写法, 我给`hexo-renderer-marked` 也加入了anchor支持.

`hexo-renderer-markdown-it`支持anchor的逻辑是:

1. 对每个heading, 在它内部的第一个child之前加入超链接. 

   * SCSS会将属于`.header-anchor`或`.headerlink `类的元素渲染为anchor, 所以超链接必须是`.header-anchor`或`.headerlink `类.

     ```scss
       h1, h2, h3, h4, h5, h6 {
         // Supported plugins: hexo-renderer-markdown-it hexo-renderer-marked
         .header-anchor, .headerlink {
           border-bottom-style: none;
           color: inherit;
           float: right;
           font-size: $font-size-small;
           margin-left: 10px;
           opacity: 0;
     
           &::before {
             font-family-icons('\f0c1');
           }
         }
      }
     ```

   * anchor的显示是通过font-family-icon图片完成的. 使用CSS来添加该图片. 

     ```css
     &::before {
             font-family-icons('\f0c1');
           }
     ```

   

2. 给每个heading增加id. 我个人喜欢把文本中的空格替换为`-`, 大小写不变, 因此就将这个标题内容作上述变换, 作为id.

   ```javascript
   id_text = heading.textContent;
   id_text = id_text.replace(/\s/g, "-"); //把原文的空格替换成-. 暂时没有解决重名的问题.
   ```

3. 再对超链接的`anchor`的`href`attribute设置值为`#` + (2)中heading的文本内容. 超链接的tittle, 即鼠标悬停上方后显示的提示信息, 不需要做上述转换, 直接用heading原文即可.

   ```javascript
   link.title = heading.textContent;//这是鼠标悬停到超链接时的提示信息, 不需要替换空格
   heading.id = id_text;//heading的空格替换成-.
   ```

   

   

```javascript
document.addEventListener("page:loaded", function() {
    // 获取所有标题元素
    var headings = document.querySelectorAll("h1, h2, h3, h4, h5, h6");

    // 遍历标题元素列表并为每个元素添加类名 "headerlink"
    for (var i = 0; i < headings.length; i++) {
        heading = headings[i];

        id_text = heading.textContent;
        id_text = id_text.replace(/\s/g, "-"); //把原文的空格替换成-. 暂时没有解决重名的问题.

        // 创建超链接元素
        var link = document.createElement("a");
        link.classList.add("headerlink");//在CSS中, 具有headerlink类的元素会生成anchor.
        link.href = "#" + id_text;//超链接指向的目的heading地址, 空格替换成-.
        link.title = heading.textContent;//这是鼠标悬停到超链接时的提示信息, 不需要替换空格
        link.setAttribute("aria-hidden", "true");

        // 将超链接添加到标题元素的里面
        heading.insertAdjacentElement("afterbegin", link);

        heading.id = id_text;//heading的空格替换成-.
    }
});
```

例如: 

原本heading内容为“Schedule an Interview”:

```html
<h1>Schedule-an-Interview</h1>
```



修改后, 其增加了id属性, 内部增加了超链接, 超链接的href指向其id:

````html
<h1>
<a class="headerlink" href="Schedule-an-Interview" title="Schedule an Interview"></a>
Schedule-an-Interview
</h1>
````



CSS会选中属于`headerlink`类的超链接, 为其添加anchor的动画效果.

# Math Support

[Next数学公式支持官方文档](https://github.com/theme-next/hexo-theme-next/blob/master/docs/zh-CN/MATH.md)

[Next Mathjax高级特性](https://theme-next.js.org/docs/third-party-services/math-equations.html?highlight=mathjax#mjx-eqn%3Aeq2)

目前的Latex渲染引擎有 [MathJax](https://www.mathjax.org/) 和 [Katex](https://khan.github.io/KaTeX/), `MathJax`完美支持Latex, `Katex`速度更快, 但是有些语法不支持. 综合来看还是选择Mathjax.

Hexo需要使用markdown渲染引擎将md渲染成html, 而Hexo NexT默认使用的markdown渲染引擎是[hexo-renderer-marked](https://github.com/hexojs/hexo-renderer-marked), 它不支持Mathjax，不支持插件扩展，不支持emoji表情, 因此我们需要卸载它, 并替换为别的引擎.

注意, 不同的渲染引擎是不能共存的( [hexo-filter-mathjax](https://github.com/next-theme/hexo-filter-mathjax)除外, 它是server端的渲染引擎 ), 因此在使用一个渲染引擎之前, 需要卸载掉其他全部的渲染引擎.

## Engines

Next支持的markdown数学渲染引擎:

### Mathjax

If you use MathJax to render Math Equations, you can choose one of the Markdown renderers below:

- [hexo-renderer-pandoc](https://github.com/wzpan/hexo-renderer-pandoc)
  * pandoc功能非常强大, 支持Mathjax语法, 不仅可以渲染markdown, 还支持textile, reStructedText和许多其他格式, 但仍然不支持emoji表情.
  
  * 使用pandoc不会降低网站的运行速度, 但是会极大地降低文章构建时的file load速度:
  
    ```
    > hexo g
    INFO  Files loaded in 27 s
    ...
    INFO  489 files generated in 2.93 s
    ```
  
    可以看到, generate时间为3s, 尚可接受, 但file load时间是惊人的30s.
  
  * 无论是到Github的同步还是博客内建的搜索功能都会变得很慢. 同时pandoc的渲染速度也很慢, 降低博客文章的构建速度. 可以说, 用了pandoc后, 整个网站都慢得离谱.
  
  * Hexo Next目前并不支持在pandoc下给各级heading生成anchor.
  
  * **最后选择它.**
  
- [hexo-renderer-kramed](https://github.com/sun11/hexo-renderer-kramed): 基于hexo-renderer-marked二次开发的渲染器，完善了对Mathjax的支持, 仍然不支持插件的扩展，不支持emoji表情.
  * 亲测它比`hexo-renderer-pandoc`**快一点**. 但是有bug, 需要自己配置. 由于它太老了,就不推荐了. 
  
- [hexo-renderer-markdown-it](https://github.com/hexojs/hexo-renderer-markdown-it)：支持`MathJax`, 并可以通过插件支持`KeTex`. 支持anchor.
  
  * 支持Markdown以及CommonMark语法.
  
  * 支持插件配置, 支持标题带安全的id信息
  
  * 支持脚注（上标, 下标, 下划线）.
  
  * 非常可惜的是, 它对latex支持不完善, 比如无法显示花括号, 无法显示多行公式...
  
    
  
- [hexo-renderer-markdown-it-plus](https://github.com/CHENXCHEN/hexo-renderer-markdown-it-plus): 支持Katex插件并默认启用.

- [hexo-filter-mathjax](https://github.com/next-theme/hexo-filter-mathjax): Server side [MathJax](http://www.mathjax.org/) Renderer Plugin for [Hexo](http://hexo.io/). 要使用它,需要卸载掉除了`hexo-renderer-marked` ( 用于渲染markdown )之外的LaTex引擎. 它的缺点是有些语法不支持, 而且无法渲染目录里的LaTex.

### KaTex

If you use KaTeX to render Math Equations, you can choose one of the Markdown renderers below:

- [hexo-renderer-markdown-it-plus](https://github.com/CHENXCHEN/hexo-renderer-markdown-it-plus): 没用过
- [hexo-renderer-markdown-it](https://github.com/hexojs/hexo-renderer-markdown-it): 亲测它也支持Mathjax, 并支持Hexo支持的Mathjax特性

## Support MathJax

支持Latex步骤:

1. 卸载`hexo-renderer-marked`, 安装 `hexo-renderer-markdown-it`:

   ```shell
   npm un hexo-renderer-marked
   ```

2. 选择一个renderer安装:

   ```shell
   npm i hexo-renderer-pandoc --save
   # npm i hexo-renderer-markdown-it --save #对Latex语法支持不完备
   ```

   如果选择`hexo-renderer-pandoc` , 还需要额外安装[pandoc](https://github.com/jgm/pandoc/blob/master/INSTALL.md). On Mac:

   ```shell
   brew install pandoc
   ```

3. 开启mathjax:

   ```yaml
   math:
     # Default (false) will load mathjax / katex script on demand.
     # That is it only render those page which has `mathjax: true` in front-matter.
     # If you set it to true, it will load mathjax / katex script EVERY PAGE.
     every_page: false # 按照注释说明, 设置为false后只会渲染了指定`mathjax: true`的文章
   
     mathjax:
       enable: true
       # Available values: none | ams | all
       tags: ams # ams: 开启公式自动编号
   ```

4. 在需要渲染Latex的文章的Front-matter里打开mathjax开关，如下：

   ```markdown
   ---
   title: index.html
   date: 2016-12-28 21:01:30
   tags:
   mathjax: true
   --
   ```

   

## 公式自动编号和引用

To enable this feature, you need to set `mathjax.tags` to `ams` in NexT config file.

```yaml
math:
  mathjax:
    enable: true
    # Available values: none | ams | all
    tags: ams
```

为了使用这项功能，一般来说，你必须把所使用的 LaTeX 公式放在 `equation` 环境里面，采用旧的方法（也就是说，仅仅把公式的每一边用两个 `$` 符号包含起来）是无效的。如何引用公式？你只需要在书写公式的时候给公式一个 `\label{}` 标记（tag），然后在正文中，可以使用 `\ref{}` 或者 `\eqref{}` 命令来引用对应的公式。使用 `\eqref{}` 是推荐的方式，因为如果你使用 `\ref{}`，公式在文中的引用编号将没有圆括号包围。下面介绍几种常见的公式编号例子.

对于简单的公式，使用下面的方式给公式一个标记，

```latex
$$\begin{equation}\label{eq1}
e=mc^2
\end{equation}$$
```

然后，在正文中，你可以轻松引用上述公式，一个简单的例子如下：

```
著名的质能方程 $\eqref{eq1}$ 由爱因斯坦提出 ...
```

## Multi-line Equations

对于多行公式，在 `equation` 环境中，你可以使用 `aligned` 环境把公式分成多行，

```latex
$$\begin{equation}\label{eq2}
\begin{aligned}
a &= b + c \\
  &= d + e + f + g \\
  &= h + i
\end{aligned}
\end{equation}$$
```

## Multiple Aligned Equations

要对齐多个公式，我们需要使用 `align` 环境。align 环境中的每个公式都有自己的编号：

```latex
$$\begin{align}
a &= b + c \label{eq3} \\
x &= yz \label{eq4}\\
l &= m - n \label{eq5}
\end{align}$$
```

## Exclude Equations from Numbering

在 `align` 环境中，如果你不想给某个或某几个公式编号，那么在这些公式后面使用 [`\nonumber`](https://tex.stackexchange.com/questions/17528/show-equation-number-only-once-in-align-environment) 命令即可。例如：

```
$$\begin{align}
-4 + 5x &= 2+y \nonumber  \\
 w+2 &= -1+w \\
 ab &= cb
\end{align}$$
```

## Use `\tag` to Tag Equations

有时，你可能会希望采用更加奇特的方式来标记和引用你的公式，你可以通过使用 `\tag{}` 命令来实现，例如：

```
$$x+1\over\sqrt{1-x^2} \tag{i}\label{eq_tag}$$
```

如果你想要了解更多信息，请访问 [MathJax 关于公式编号的官方文档](https://docs.mathjax.org/en/latest/input/tex/eqnumbers.html)。同时，你也可以阅读 [这篇文档](https://theme-next.org/docs/third-party-services/math-equations) 来获取更多细节信息。

# Customization

## Fonts Customization

My fonts:

* Chinese: Noto Serif SC
* English: Fira Code



[Fonts Customization](https://theme-next.js.org/docs/theme-settings/miscellaneous.html?highlight=font+settings#Fonts-Customization). 这上面的部分细节过时了, 以我这里写的为准.

> NexT gives you 5 specific font settings, they are:
>
> - Global Font: Font used in the whole site.
> - Title Font: Font used by site title.
> - Headlines Font: Font used by headings in articles (h1, h2, h3, h4, h5, h6).
> - Article Font: Font used by articles.
> - Code Font: Font used by code blocks in articles.
>
> Each font will be used as the first font of this class, NexT will **fallback** to internal font settings if they are unavailable.
>
> - Non-code Font: Fallback to `"PingFang SC", "Microsoft YaHei", sans-serif`
> - Code Font: Fallback to `consolas, Menlo, "PingFang SC", "Microsoft YaHei", monospace`
>
> Plus each section has a `external` attribute, this controls whether to use the font library CDN.
> Use this can help you to use fonts installed in system and reduce unnecessary requests.



> 

### Chinese Font

低版本Next的默认字体(`font: false`)很丑, 不知道是什么字体. 新版本的Next的默认字体是Microsoft YaHei, 也可以自己更改. 我在`NexT _config.yml`中配置了Fira Code:

```
font:
  enable: true

  # Uri of fonts host, e.g. https://fonts.googleapis.com (Default).
  # For accessibility in China mainland, I replace it with ustc source
  host: https://fonts.lug.ustc.edu.cn

  # Font options:
  # `external: true` will load this font family from `host` above.
  # `family: Times New Roman`. Without any quotes.
  # `size: x.x`. Use `em` as unit. Default: 1 (16px)

  # Global font settings used for all elements inside <body>.
  global:
    external: true
    family: Fira Code
    size:
```



> To solve the unstable of [Google Fonts API](https://fonts.google.com/) in some countries, NexT supports custom URL of fonts library by setting `font.host`. 

为了在中国大陆的访问, 我把 `font.host`换成了ustc源. 设置` external: true`来从把 `font.host`加载font.

### English Font

按[Next中文文档](https://hexo-next.readthedocs.io/zh_CN/latest/next/advanced/%E5%AD%97%E4%BD%93%E8%AE%BE%E7%BD%AE/)的说明, 通过`NexT _config.yml`仅能替换中文字体/英文字体其中一种. Fira Code是英文字体, 要想再配置中文字体, 需要改更改Next的样式文件.

由于之前讲过的[Data Files](https://hexo.io/docs/data-files) 和 [Custom Files](https://theme-next.js.org/docs/advanced-settings/custom-files.html) feature, 我不需要更改主题目录下的文件, 而是将它们copy到`<hexo>/source/_data`作为data files, 然后在`NexT _config.yml`指定它们作为custom files.



1. First, copy `<hexo>/themes/next/source/css/_variables/base.styl` to `<hexo>/source/_data/`. Rename `<hexo>/source/_data/base.styl` to `<hexo>/source/_data/variables.styl`. 

2. Edit `<hexo>/source/_data/variables.styl`, clear it original content, then add:

   ```stylus
   # use 'Noto Serif SC'
   $font-family-chinese      = 'Noto Serif SC', Monaco, Consolas, Ubuntu Mono, monospace;
   
   $font-family-base         = $font-family-chinese, sans-serif;
   $font-family-base         = get_font_family('global'), $font-family-chinese, sans-serif if get_font_family('global');
   
   $font-family-logo         = $font-family-base;
   $font-family-logo         = get_font_family('title'), $font-family-base if get_font_family('title');
   
   $font-family-headings     = $font-family-base;
   $font-family-headings     = get_font_family('headings'), $font-family-base if get_font_family('headings');
   
   $font-family-posts        = $font-family-base;
   $font-family-posts        = get_font_family('posts'), $font-family-base if get_font_family('posts');
   
   $font-family-monospace    = consolas, Menlo, monospace, $font-family-chinese;
   $font-family-monospace    = get_font_family('codes'), consolas, Menlo, monospace, $font-family-chinese if get_font_family('codes');
   ```

   This will overwrite `<hexo>/themes/next/source/css/_variables/base.styl` 's config with custom file's config.

3. Create file `<hexo>/source/_data/head.njk` , then input:

   ```njk
   <link href="https://fonts.googleapis.com/css?family=Noto+Serif+SC|Roboto&display=swap" rel="stylesheet">
   ```

   

4. Then uncomment `style` and `head` under the `custom_file_path` section in NexT config file.

   ```yaml
   custom_file_path:
     head: source/_data/head.njk # Used to config font.
     #header: source/_data/header.njk
     #sidebar: source/_data/sidebar.njk
     #postMeta: source/_data/post-meta.njk
     #postBodyEnd: source/_data/post-body-end.njk
     #footer: source/_data/footer.njk
     #bodyEnd: source/_data/body-end.njk
     variable: source/_data/variables.styl
     #mixin: source/_data/mixins.styl
     #style: source/_data/styles.styl
   ```



## Code Block

* 代码高亮(Code Highlight theme): 这个网站可以预览所有高亮效果：[传送门](https://theme-next.js.org/highlight/)

  我使用highlight作为高亮引擎, theme使用`a11y-light`

* 我没有设置代码块行号.

* 代码块超过一定高度则折叠.



`NexT _config.yml`:

```yaml
codeblock:
  # Code Highlight theme
  # All available themes: https://theme-next.js.org/highlight/
  theme:
    # light: default
    # dark: stackoverflow-dark
    light: a11y-light
    dark: a11y-dark
  prism:
    light: prism
    dark: prism-dark
  # Add copy button on codeblock
  copy_button:
    enable: false
    # Available values: default | flat | mac
    style: flat
  # Fold code block
  fold:
    enable: true
    height: 300
```



`Hexo _config.yml`:

```yaml
highlight:
  enable: true
  line_number: false
  auto_detect: true
  tab_replace: ''
  wrap: true
  hljs: false
  exclude_languages:
    - mermaid
prismjs:
  enable: false
  preprocess: true
  line_number: true
  tab_replace: ''
```

## Mermaid

NexT config file

```yaml
# Mermaid tag
mermaid:
  enable: true
  # Available themes: default | dark | forest | neutral
  theme:
    light: default
    dark: dark
```



Hexo config file

```yaml
highlight:
  exclude_languages:
   - mermaid
```



## Image

### 图像缩放

`NexT`集成了多种图像显示工具, 包括`FancyBox`和`MediumZoom`, 主要功能是图像缩放.

开启`MediumZoom`:

```
# A JavaScript library for zooming images like Medium.
# Warning: Do not enable both `fancybox` and `mediumzoom`.
# For more information: https://medium-zoom.francoischalifour.com
mediumzoom: true
```

### 图像懒加载

```
npm install hexo-lazyload --save
```

```
lazyload: true
```

## Performance

[Pjax](https://github.com/MoOx/pjax) is a standalone JavaScript module that uses AJAX (XmlHttpRequest) and `pushState()` to deliver a fast browsing experience.

```yaml
NexT config file
# Easily enable fast Ajax navigation on your website.
# For more information: https://github.com/next-theme/pjax
pjax: true
```

## Pangu Autospace

[pangu.js](https://github.com/vinta/pangu.js) will automatically **insert a blank space between all the Chinese characters and the hexagonal English numeric symbols** on the page.

实测非常好用!

You can enable it by setting value `pangu` to `true` in NexT config file.

```yaml
NexT config file
# Pangu Support
pangu: true
```

### Quickli

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

## back2top button

back2top button非常好看, Next默认是添加的:

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



如果自带的不能满足你, 那么这里有个[另外的button](https://github.com/jiangtj-lab/hexo-cake-moon-menu).

## Copyright

选择`sidebar: true`, 这会在sidebar出现不怎么碍眼的一个小徽章.

如果选择`post: false`, 版权信息会出现在文章底部, 很难看.

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

## SEO

[Source](https://suda-liu.github.io/2020/04/07/%E4%B8%80%E6%AC%A1%E6%88%90%E5%8A%9F%E7%9A%84%E4%BD%93%E9%AA%8C-Hexo%E5%8D%9A%E5%AE%A2%E6%B7%BB%E5%8A%A0%E8%B0%B7%E6%AD%8C%E6%94%B6%E5%BD%95/) 

博客搭建成功后，只能通过输入网址来访问，但是却不能被谷歌搜索到。原因是谷歌并没有收录我们的网站，所以还需向谷歌提交站点地图(sitemap)，让谷歌能够找到我们的博客。

1. 生成sitemap文件:

   1. 执行命令，安装站点地图生成插件。

   ```
   npm install hexo-generator-sitemap --save
   ```

   1. 在博客根目录下的配置文件`_config.yml`中添加下列内容。

   ```
   # 自动生成sitemap
   sitemap:
   	path: sitemap.xml
   ```

   1. 执行`hexo g`，会在`博客根目录/public`中生成`sitemap.xml`文件。

2. HTML文件验证

    这里我只记录了HTML文件的验证方式。可以根据自己网站情况自行选择验证方式。

   1. 登录谷歌账号，打开[网站管理员中心](https://www.google.com/webmasters/verification/home?hl=en)，点击`ADD A PROPERTY`。
   2. 选择验证方法。这里我使用的是DNS验证方法。也可选择替代方法。
   3. 下载HTML验证文件，存放在`博客根目录/themes/next/source`。
   4. 执行`hexo cl`,`hexo g`,`hexo d`。
   5. 返回Google网站站长进行验证，即可完成验证。

3. 提交sitemap: 点击[添加站点地图](https://www.google.com/webmasters/tools/sitemap-list)，选择要添加的网站，填入`sitemap.xml`，点击【提交】。

4. 查看被收录的文章: 在Google中搜索

   ```
   site:写你要搜索的域名 # site:xxx.github.io
   ```

   如果能搜索到就说明被收录，可以看到自己的网站啦！

   以后可以通过[Google 网站管理员](https://www.google.com/webmasters/)查看网站的一些数据。

5. Other SEO methods:

   1. Set the value of `index_with_subtitle` in NexT config file to `true` to add `subtitle` information to index page.

      ```
      NexT config file
      
      index_with_subtitle: true
      ```

      You can set `subtitle` in Hexo config file.

   2. Exturl: Just one setting must be turned on under the `SEO Settings` section in theme config file:

      ```yaml
      # NexT config file
      exturl: true
      exturl_icon: true
      ```

      Then run the following command in site root dir to ensure that `exturl` can be enabled or disabled correctly:

      ```
      hexo clean
      ```



# Synchronize between mul-hosts

如果想要在多台主机上同步Hexo项目, 只需要把自己的Hexo Github Repo clone下来. 

但是, 主题一般是用git clone来下载的, 这会让主题文件夹作为一个git submodule存在于项目目录下. 在**当push本地仓库时, submodule不会被push**.

* 证据就是, 在github上查看网站项目仓库, 点进`<repository>/themes/`, 会发现`next`文件夹有个很奇怪的名字: `[next @ XXXXX`, 点击它, 会跳转到该主题文件夹对应的github项目. 这说明**本地的主题文件夹是一个子项目, 从来没有随着父项目一起被push到github上**.

因此, 在其他主机上clone Hexo项目, 它clone下的主题文件夹是空的. 

* 比如, 我用next主题, 当我买了台新电脑, 想要在它上面同步我开发的hexo. clone下我的网站, 发现项目内`themes/next`为空. 这样就无法正确生成网站页面了. 

  > 该Bug的表面结果是: hexo生成的`index.html`也为空( 0kb )

所以**clone下来的Hexo项目是没有主题的, 需要自己重新安装主题.**

* 虽然我用git clone来下载主题, 但有些主题也可以也可以用npm install来下载(比如Next). 用npm下载的主题不会有git submodule的问题, 在其他主机上clone Hexo Repo后npm install下载依赖即可. 

## Steps

多主机同步的步骤, 就是先同步Hexo, 再同步主题.

### Synchronize Hexo

如果本机已经有hexo了:

```
# 如果本机已经有hexo了
cd <hexo>
git pull
```



如果本机没有Hexo, 只需找个地方安装Hexo即可.

```shell
git clone https://github.com/LYK-love/LYK-love.github.io
cd LYK-love.github.io
npm install
```



可能会遇到报错:

```
ERROR Cannot find module 'hexo' from '/Users/lyk/Documents/LYK-love.github.io'
<Snip>
ERROR Try running: 'rm -rf node_modules && npm install --force'
```

只需按照提示操作即可:

```sh
rm -rf node_modules && npm install --force
```

### Synchronize Theme

由于[Next提供的各种机制](#Config-File-Features), 主题配置文件, 样式文件等已经在Hexo目录中被同步了. 因此这一步只需**安装主题**即可.

* 如果你用的是官方的主题, 那就去安装官方的主题, 例如对于Next, 就可以按照[之前的教程](#Installation).
* 如果你要[对主题做单独的版本管理](#Apply-separate-version-control-to-themes) (很不推荐这种做法), 那么主题文件就是个git submodule, 需要[Update submodule](#Update-submodule).



如果还有文件没同步, 比如images等文件, 它们只能放在主题目录下, 但是如前所述, 每次从官方同步主题都会覆盖自己的更改, 那么可以把这些文件备份一下放在Hexo目录下, 之后手动copy到主题目录中.

* 我的images就放在Hexo目录下, 每次更新主题后手动copy到`source/images`中.

# Apply separate version control to themes

* [ 在 hexo 中使用 git submodules 管理主题 ](https://juejin.cn/post/6844903751908605965)

我极其不推荐这种做法, 将主题进行单独的版本管理会导致主题无法收到官方仓库的更新.



首先, 在Github上创建一个自己的主题的仓库. 由于主题是git submodule, 不会随着Hexo项目的push而被push, 所以每次push Hexo时, 还要额外push一下主题:

```shell
## ... after push Hexo
## Now push my Next theme
cd ./themes/next
git add . && git commit -m"XXX"
git push
```

## Update submodule

接下来. 如果本机已经有了主题的submodule, 则只需update submodule:

```shell
# 把项目的子项目也pull下来
git submodule update --init
```



当然也可以pull Hexo后手动再pull子项目,这样很蠢:

```shell
cd ./themes/next
git pull
```

## Add submodule

如果本机没有主题的submodule. 可以将主题作为submodule添加进来:

```shell
cd <hexo>
git submodule add <your own theme repo>
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

然后按之前的做法**update submodule**.



此外, 还可以在 clone 父项目时直接使用 `git clone --recursive` , git 会自动pull所有的子项目.



# Use multi-branches in Github

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

# 一些不想用的美化

以下美化我都不想用, 只是给出添加方式.

* 添加评论系统. 我觉得没有这个必要.

* 夜间模式: 这是永久的, 不能手动切换, 所以我也不想加. 

  ```
  darkmode: true
  ```

* Reading progress bar: 五颜六色的, 影响观看:

  ```yaml
  reading_progress: Reading progress bar
  
    enable: false
  ```
