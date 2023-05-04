---
title: Hugo Config
tags:
---



# Why Hugo

之前我一直使用Hexo Next Theme来写博客. 之后遇到了Hugo的Terminal Theme, 觉得这个主题很好看, 因此想要把博客迁移到Hugo.

但是, 实际操作后发现Hugo的配置非常复杂, 需要仔细阅读Hugo的内部机制, 完全不能做到像Hexo那样的专注写作.

Hexo的优点是配置和使用简单, 缺点是使用npm, 运行速度很慢.

Hugo的优点是运行速度很快, 缺点是配置和使用极其复杂. 这里我指的是深入使用, 因为Hugo的默认配置和Hexo一样方便, 主题可以开箱即用. 但如果主题不能满足你的需求, 那就惨了. 

Hexo的几个主题对各种插件的集成非常好, 想要加什么功能, 直接在主题的配置文件里加就行了. 但是Hugo的功能支持差的离谱, 许多主题(包括我用的Terminal Theme)默认连Archive Page和Local Search都没有, 如果文章数量比较大, 连文档管理都做不到. 

事实上, 直到本文写作时, 我还没有配置好所有想要的功能. 其中的Local Search功能似乎非常难实现, 因为大多数方案使用的Fuse.js对中文支持很差.

网络上有些讨论说Hugo相比Hexo的优势还有一个使用和配置简单, 这是无稽之谈. 对于我用的Next Theme来说, Hexo Next的版本管理和配置都非常方便,用[Alternate Theme Config机制](https://theme-next.js.org/docs/getting-started/configuration)就可以实现版本管理和及时更新. 而使用Hugo的情况下, 几乎所有想要的功能都没办法一键集成, 需要手动实现, 这是非常麻烦的. Hexo一直由于使用npm而为人诟病, 但npm是一个package manager, 在Hugo里我需要手写JS代码, 连package manager都没有, 依赖的更新无法保证, 还不如用npm呢.

我用Hugo的原因仅仅是它有好看的Terminal主题, 至于运行速度, 其实我不在乎.  就为了“好看”这个原因, 我选择了Hugo, 在Hugo上投入了无数努力.

# Local Search

Hugo的Terminal主题没有集成Local Search, 需要自己实现. 在Hugo官方的Local Search集成方案: [Search for your Hugo Website](https://gohugo.io/tools/search/) 中提供了两个方法:

1. 使用Hugo官方推荐的一些开源和商业站内搜索方案.
2. 自己实现.

由于不想有过多的外部依赖, 并且商业站点, 如Algolia, 提供的搜索服务需要引入npm, 过于臃肿, 因此我决定自己实现Local Search, 也就是自己写一个搜索组件. HTML和CSS部分没什么好说的, 对于搜索功能, 目前主流的方法都是使用[Fuse.js](https://fusejs.io/demo.html)库来实现.

## My config file

```
baseurl = "https://lyk-love.cn/Hugo-Blog/"
languageCode = "en-us"
# title = 'LYK-love'
# Add it only if you keep the theme in the `themes` directory.
# Remove it if you use the theme as a remote Hugo Module.
# theme = "Hugo-blog-awesome"
# theme = "LoveIt"
theme = "terminal"

paginate = 5

#What's this??
enableEmoji = true
[markup]
  [goldmark]
    [renderer]
      unsafe = true

[params]
  # dir name of your main content (default is `content/posts`).
  # the list of set content will show up on your index page (baseurl).
  contentTypeName = "posts" #    如果找不到, 会显示不了read other posts

  # ["orange", "blue", "red", "green", "pink"]
  themeColor = "green"

  # if you set this to 0, only submenu trigger will be visible
  showMenuItems = 4

  # show selector to switch language
  showLanguageSelector = false

  # set theme to full screen width
  fullWidthTheme = false

  # center theme with default width
  centerTheme = true

  # if your resource directory contains an image called `cover.(jpg|png|webp)`,
  # then the file will be used as a cover automatically.
  # With this option you don't have to put the `cover` param in a front-matter.
  autoCover = true

  # set post to show the last updated
  # If you use git, you can set `enableGitInfo` to `true` and then post will automatically get the last updated
  showLastUpdated = false

  # set a custom favicon (default is a `themeColor` square)
  favicon = "/images/favicon.ico"

  # Provide a string as a prefix for the last update date. By default, it looks like this: 2020-xx-xx [Updated: 2020-xx-xx] :: Author
  # updatedDatePrefix = "Updated"

  # set all headings to their default size (depending on browser settings)
  # oneHeadingSize = true # default

  # whether to show a page's estimated reading time
  # readingTime = false # default

  # whether to show a table of contents
  # can be overridden in a page's front-matter
  Toc = true # default

  # set title for the table of contents
  # can be overridden in a page's front-matter
  TocTitle = "Contents" # default

[taxonomies]
  # key-value pairs. the value is the url. So if we set  category = 'categories1', then the taxonomy page of category is: https://mywebsite.com/categories1
  category = 'categories'
  tag = 'tags'

[outputs]
  home = ["HTML", "RSS", "JSON"]

#[frontmatter]
#  date = [":filename", ":default", ":fileModTime"]
#
#[permalinks]
#  post = "/blog/:year/:month/:day/:slug/"

disablePathToLower = true

# [params.twitter]
#   # set Twitter handles for Twitter cards
#   # see https://developer.twitter.com/en/docs/tweets/optimize-with-cards/guides/getting-started#card-and-content-attribution
#   # do not include @
#   creator = ""
#   site = ""

[languages]
  [languages.en]
    languageName = "English"
    title = "LYK-love"
    subtitle = "A site by lyk"
    owner = "LYK-love"
    keywords = ""
    # copyright = "LYK-love" # 页面最底下的名字
    menuMore = "Show more"
    # readMore = "Read more"
    readMore = ""
    readOtherPosts = "Read other posts"
    newerPosts = "Newer posts"
    olderPosts = "Older posts"
    missingContentMessage = "Page not found..."
    missingBackButtonLabel = "Back to home page"
    minuteReadingTime = "min read"
    words = "words"

    [languages.en.params.logo]
      logoText = "LYK-love"
      logoHomeLink = "/"

    [languages.en.menu]
      [[languages.en.menu.main]]
        # (string) Required when two or more menu entries have the same name,
        # or when localizing the name using translation tables.
        # Must start with a letter, followed by letters, digits, or underscores.
        identifier = "about"

        # (string) The text to display when rendering the menu entry.
        name = "About"
        url = "/about"

        # (int) A non-zero integer indicating the entry’s position relative the root of the menu, or to its parent for a child entry.
        # Lighter entries float to the top, while heavier entries sink to the bottom.
        weight = 1
      [[languages.en.menu.main]]
        identifier = "archive"
        name = "Archive"
        url = "/archive"
        weight = 2
      [[languages.en.menu.main]]
        identifier = "tags"
        name = "Tags"
        url = "/tags"
        weight = 3
    [[languages.en.menu.main]]
      identifier = "categories22"
      name = "Categories"
      url = "/categories"
      weight = 5

## 我决定把search button放在网页右上角, 而不是作为menu item
#      [[languages.en.menu.main]]
#        identifier = "search"
#        name = "Search"
#        url = "/search"
#        weight = 9
      [[languages.en.menu.main]]
        identifier = "research"
        name = "Research"
        url = "/research"
        weight = 6
      [[languages.en.menu.main]]
        identifier = "Code"
        name = "Code"
        url = "/code"
        weight = 7
# [module]
#   # In case you would like to make changes to the theme and keep it locally in you repository,
#   # uncomment the line below (and correct the local path if necessary).
#   # --
#   # replacements = "github.com/panr/hugo-theme-terminal -> themes/terminal"
# [[module.imports]]
#   path = 'github.com/panr/hugo-theme-terminal'
```



## Refs

我结合了下面两个方法:

1. https://ttys3.dev/post/hugo-fast-search/ 创建一个搜索组件(由搜索按钮和搜索框组成)放在页面右上角, 点击搜索按钮(`#search-btn`)后, 会显示搜索框(`searchInput`). 

   `layouts/partials/extended_footer.html`:

   ```html
   <!--Fast Search Component from: https://ttys3.dev/post/hugo-fast-search/-->
   <!--这个方案和fuse.js差不多, 但是自己在extended_heead中定义了组件css, 和Terminal主题不够契合.-->
   <a id="search-btn" style="display: inline-block;" href="javascript:void(0);">
     <span class="icon-search">Search</span>
   </a>
   
   <!--这个搜索框目前已经没用了, 因为点击搜索按钮后会直接跳转到search page, 而不是显示搜索框.-->
   <div id="fastSearch">
     <input id="searchInput" tabindex="0">
     <ul id="searchResults">
     </ul>
   </div>
   <script src="/js/fuse.min.js"></script> <!-- download and copy over fuse.min.js file from fusejs.io -->
   <script src="/js/fastsearch.js"></script>
   ```

   问题在于这个搜索框用了单独的CSS, 和Terminal theme不搭, 我也不知道怎么改样式; 此外, 这个搜索框只能显示搜索结果页面的标题, 但无法显示页面的内容以及高亮, 关键代码:

   ```javascript
       document.getElementById("searchResults").innerHTML = searchitems;
       if (results.length > 0) {
           first = list.firstChild.firstElementChild; // first result container — used for checking against keyboard up/down location
           last = list.lastChild.firstElementChild; // last result container — used for checking against keyboard up/down location
       }
   ```

   这个组件优化起来很麻烦, 我放弃了这个方案.

2. https://juejin.cn/post/7149051443234734111 我实际借鉴的方案, 它又借鉴了:  [Github Gist for Fuse.js integration](https://link.juejin.cn/?target=https%3A%2F%2Fgist.github.com%2Feddiewebb%2F735feb48f50f0ddd65ae5606a1cb41ae). 这个方案没有自定义搜索组件, 而是借用了一个page在进行搜索. 

   我需要创建一个search page(`content/search.md`), 然后创建一个按钮组件, 点击该按钮后就会路由到search page( `https://mywebsite.com/site`)来进行搜索. 

   * 使用`    window.location.href = "/search"`可以在任何url下跳转到`https://mywebsite.com/search`.

## Problems

方案2的缺陷在于: 相比用一个单独的网页来进行search, 使用单独的组件无疑是更好的方案. 但我目前写不出来这样的组件, 等以后前端熟练了再说吧. (现有的方案只能是用menu item来跳转)

由于不会编写组件, 按钮组件我用的是现成的menu item. 也就是在配置文件中创建一个menu item, 指向创建的search page. search page的内容我不会写. 只能抄网上的方案, 使用`layouts/_default/search.html`作为`content/search.md`的内容.

但是, 我发现search page如果使用layout, 就**会使得在seach page中点击menu按钮无反应**. debug发现, 在其他页面下, menu item被绑定了click事件, 但是在search page, menu按钮没有事件绑定. **我不知道事件绑定是在哪一步被移除的.**

有两个办法: 要么找到移除事件绑定的代码然后修改; 要么不用layout, 而是用shortcodes, 但是我都不会.



## Steps

目前的实现是:

1. 按照方案1, 实现一个单独的搜索按钮, 放在页面右上角. 但是, 该搜索按钮并不具有搜索逻辑, 点击它之后只会进行页面跳转.
2. 点击该按钮后, 会跳转到按照方案2编写的search page.



首先, 在hugo项目根目录添加4个文件：`content/search.md`,`layouts/_default/search.html`, `static/js/search.js`,`layouts/_default/index.json`. 在其中加入内容, 实现search page.

接着, 编辑`layouts/partials/extended_footer.html`, 在其中加入search按钮, 点击后会跳转到search page.

最后, 在`Config.toml`中编辑, 设置search的输出.

### Files

#### [content/search.md](https://gist.github.com/eddiewebb/735feb48f50f0ddd65ae5606a1cb41ae#content-searchmd)

添加`content/search.md`, 其内容不重要, 因为不会被渲染. 

Hugo在发现`layouts/_default/`下有同名("search")html文件后, 会渲染该html文件, 而不是md文件.

````markdown
---
title: "Search Results"
sitemap:
priority : 0.1
layout: "search"
---


This file exists solely to respond to /search URL with the related `search` layout template.

No content shown here is rendered, all content is based in the template layouts/page/search.html

Setting a very low sitemap priority will tell search engines this is not important content.

This implementation uses Fusejs, jquery and mark.js


## Initial setup

Search  depends on additional output content type of JSON in config.toml
```
[outputs]
home = ["HTML", "JSON"]
```

## Searching additional fileds

To search additional fields defined in front matter, you must add it in 2 places.



### Edit layouts/_default/index.JSON
This exposes the values in /index.json
i.e. add `category`
```
...
"contents":{{ .Content | plainify | jsonify }}
{{ if .Params.tags }},
"tags":{{ .Params.tags | jsonify }}{{end}},
"categories" : {{ .Params.categories | jsonify }},
...
```

### Edit fuse.js options to Search
`static/js/search.js`
```
keys: [
  "title",
  "contents",
  "tags",
  "categories"
]
```
```

##### layouts/_default/search.html

```

{{ define "footer" }}
<script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/fuse.js/3.2.0/fuse.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/mark.js/8.11.1/jquery.mark.min.js"></script>
<script src="{{ "js/search.js" | absURL }}"></script>
{{ end }}
{{ define "main" }}
<section class="resume-section p-3 p-lg-5 d-flex flex-column">
  <div class="my-auto" >
    <form action="{{ "search" | absURL }}">
      <input id="search-query" name="s"/>
    </form>
    <div id="search-results">
     <h3>Matching pages</h3>
    </div>
  </div>
</section>
<!-- this template is sucked in by search.js and appended to the search-results div above. So editing here will adjust style -->
<script id="search-result-template" type="text/x-js-template">
    <div id="summary-${key}">
      <h4><a href="${link}">${title}</a></h4>
      <p>${snippet}</p>
      ${ isset tags }<p>Tags: ${tags}</p>${ end }
      ${ isset categories }<p>Categories: ${categories}</p>${ end }
    </div>
</script>
{{ end }}
````

#### layouts/_default/search.html

该文件会代替`content/search.md`被渲染, 作为search page.

相对原方案的[layouts/_default/search.html](https://gist.github.com/eddiewebb/735feb48f50f0ddd65ae5606a1cb41ae#layouts---default-searchhtml), 我做了一个修改. 原文中define了`footerfiles`, 此处的 `define` 其实更像是 implement, 或者说 define 这个 block 内的内容, 而前提是你已经定义过这个 block. 一般是在 [Base Template](https://gohugo.io/templates/base/) 里，以 `{{ block "main" . }} … {{ end }}` 的格式定义. 



但我用的Terminal theme的`baseof.html`中没有定义`footerfiles`这个block, 结果就是直接使用[layouts/_default/search.html](https://gist.github.com/eddiewebb/735feb48f50f0ddd65ae5606a1cb41ae#layouts---default-searchhtml)代码后, 搜索结果是空的.

但我的`baseof.html`中定义了block `footer`, 因此把`footerfiles`换成`footer`就好了.

```html
{{ define "footer" }}
<script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/fuse.js/3.2.0/fuse.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/mark.js/8.11.1/jquery.mark.min.js"></script>
<script src="{{ "js/search.js" | absURL }}"></script>
{{ end }}
{{ define "main" }}
<section class="resume-section p-3 p-lg-5 d-flex flex-column">
    <div class="my-auto" >
        <form action="{{ "search" | absURL }}">
        <input id="search-query" name="s"/>
        </form>
        <div id="search-results">
            <h3>Matching pages</h3>
        </div>
    </div>
</section>
<!-- this template is sucked in by search.js and appended to the search-results div above. So editing here will adjust style -->
<script id="search-result-template" type="text/x-js-template">
    <div id="summary-${key}">
        <h4><a href="${link}">${title}</a></h4>
        <p>${snippet}</p>
        ${ isset tags }<p>Tags: ${tags}</p>${ end }
        ${ isset categories }<p>Categories: ${categories}</p>${ end }
    </div>
</script>
{{ end }}
```

#### [static/js/search.js](https://gist.github.com/eddiewebb/735feb48f50f0ddd65ae5606a1cb41ae#static-js-searchjs)

`static/js/search.js`:

```javascript
summaryInclude=60;
var fuseOptions = {
  shouldSort: true,
  includeMatches: true,
  threshold: 0.0,
  tokenize:true,
  location: 0,
  distance: 100,
  maxPatternLength: 32,
  minMatchCharLength: 1,
  keys: [
    {name:"title",weight:0.8},
    {name:"contents",weight:0.5},
    {name:"tags",weight:0.3},
    {name:"categories",weight:0.3}
  ]
};


var searchQuery = param("s");
if(searchQuery){
  $("#search-query").val(searchQuery);
  executeSearch(searchQuery);
}else {
  $('#search-results').append("<p>Please enter a word or phrase above</p>");
}

function executeSearch(searchQuery){
  $.getJSON( "/index.json", function( data ) {
    var pages = data;
    var fuse = new Fuse(pages, fuseOptions);
    var result = fuse.search(searchQuery);
    console.log({"matches":result});
    if(result.length > 0){
      populateResults(result);
    }else{
      $('#search-results').append("<p>No matches found</p>");
    }
  });
}

function populateResults(result){
  $.each(result,function(key,value){
    var contents= value.item.contents;
    var snippet = "";
    var snippetHighlights=[];
    var tags =[];
    if( fuseOptions.tokenize ){
      snippetHighlights.push(searchQuery);
    }else{
      $.each(value.matches,function(matchKey,mvalue){
        if(mvalue.key == "tags" || mvalue.key == "categories" ){
          snippetHighlights.push(mvalue.value);
        }else if(mvalue.key == "contents"){
          start = mvalue.indices[0][0]-summaryInclude>0?mvalue.indices[0][0]-summaryInclude:0;
          end = mvalue.indices[0][1]+summaryInclude<contents.length?mvalue.indices[0][1]+summaryInclude:contents.length;
          snippet += contents.substring(start,end);
          snippetHighlights.push(mvalue.value.substring(mvalue.indices[0][0],mvalue.indices[0][1]-mvalue.indices[0][0]+1));
        }
      });
    }

    if(snippet.length<1){
      snippet += contents.substring(0,summaryInclude*2);
    }
    //pull template from hugo templarte definition
    var templateDefinition = $('#search-result-template').html();
    //replace values
    var output = render(templateDefinition,{key:key,title:value.item.title,link:value.item.permalink,tags:value.item.tags,categories:value.item.categories,snippet:snippet});
    $('#search-results').append(output);

    $.each(snippetHighlights,function(snipkey,snipvalue){
      $("#summary-"+key).mark(snipvalue);
    });

  });
}

function param(name) {
  return decodeURIComponent((location.search.split(name + '=')[1] || '').split('&')[0]).replace(/\+/g, ' ');
}

function render(templateString, data) {
  var conditionalMatches,conditionalPattern,copy;
  conditionalPattern = /\$\{\s*isset ([a-zA-Z]*) \s*\}(.*)\$\{\s*end\s*}/g;
  //since loop below depends on re.lastInxdex, we use a copy to capture any manipulations whilst inside the loop
  copy = templateString;
  while ((conditionalMatches = conditionalPattern.exec(templateString)) !== null) {
    if(data[conditionalMatches[1]]){
      //valid key, remove conditionals, leave contents.
      copy = copy.replace(conditionalMatches[0],conditionalMatches[2]);
    }else{
      //not valid, remove entire section
      copy = copy.replace(conditionalMatches[0],'');
    }
  }
  templateString = copy;
  //now any conditionals removed we can do simple substitution
  var key, find, re;
  for (key in data) {
    find = '\\$\\{\\s*' + key + '\\s*\\}';
    re = new RegExp(find, 'g');
    templateString = templateString.replace(re, data[key]);
  }
  return templateString;
}
```

#### layouts/_default/index.json

`layouts/_default/index.json`:

```json
{{- $.Scratch.Set "index" slice -}}
{{ $posts_num := (len (where .Site.RegularPages "Type" "posts")) }}
{{ range where .Site.RegularPages "Type" "posts" }}
{{- $.Scratch.Add "index" (dict "posts_num" $posts_num "title" .Title "tags" .Params.tags "categories" .Params.categories "contents" .Plain "permalink" .Permalink) -}}
{{- end -}}
{{- $.Scratch.Get "index" | jsonify -}}
```

在用户进行搜索时, 会从网站中爬数据, 然后将爬到的数据用`fuse.js`进行查找. 关键逻辑:

`static/js/search.js`

```javascript
function executeSearch(searchQuery){
  $.getJSON( "/index.json", function( data ) { //执行layouts/_default/index.json文件, 其结果是一个数组
    var pages = data;
    var fuse = new Fuse(pages, fuseOptions);
    var result = fuse.search(searchQuery);
    console.log({"matches":result});
    if(result.length > 0){
      populateResults(result);
    }else{
      $('#search-results').append("<p>No matches found</p>");
    }
  });
}
```





注意, [参考方案]([layouts/_default/index.json](https://gist.github.com/eddiewebb/735feb48f50f0ddd65ae5606a1cb41ae#layouts---default-indexjson))里的index.json是:

```javascript
{{- $.Scratch.Add "index" slice -}}
{{- range .Site.RegularPages -}}
{{- $.Scratch.Add "index" (dict "title" .Title "tags" .Params.tags "categories" .Params.categories "contents" .Plain "permalink" .Permalink) -}}
{{- end -}}
{{- $.Scratch.Get "index" | jsonify -}}
```

我的改动如下:

1. 原方案会对`.Site.RegularPages`进行迭代, 并将每一个item(regular page)转化成index数组的一个元素.

   `.Site.RegularPages`:

   > ref: https://gohugo.io/variables/site/
   >
   > a shortcut to the *regular* page collection. `.Site.RegularPages` is equivalent to `where .Site.Pages "Kind" "page"`. See [`.Site.Pages`](https://gohugo.io/variables/site/#site-pages).

   但是, 我只想对posts(在`content/posts`下的文件)进行迭代, 其余的比如`Archive`, `About`, `Tags`等页面则不需要迭代, 因为我只想搜索posts. 因此做了如下改动:

   ```
   //删掉这行: {{- range .Site.RegularPages -}}
   //换成这个:
   {{- range where .Site.RegularPages "Type" "posts" -}}
   ```

   这会只对`.Site.RegularPages`中的posts进行迭代.

2. 实践证明, 在某些时候,执行 `{{- $.Scratch.Add "index" slice -}}`不会清除之前的`"index"`数组. 也就是说我会在index.json以及拥有所有posts的情况下继续重新往里面添加posts, 导致index.json返回的posts其实是posts的整数倍. **原因未知**. 我把`$.Scratch.Add`改成了`$.Scratch.Set`, 每次都重新初始化index.

3. 为了debug, 返回的数组元素中还会带有`"posts_num" $posts_num`属性.

#### layouts/partials/extended_footer.html

这里是根据https://ttys3.dev/post/hugo-fast-search/的魔改版本, 原方案会引用`static/js/fastsearch.js`, 但因为我的js代码很少, 就干脆放在了html文件里.

```html
<!--Fast Search Component from: https://ttys3.dev/post/hugo-fast-search/-->
<a id="search-btn" style="display: inline-block;" href="javascript:void(0);">
  <span class="icon-search">Search</span>
</a>
<!--<script src="/js/my_fastsearch.js"></script>-->

<!--&lt;!&ndash;这个搜索框目前已经没用了, 因为点击搜索按钮后会直接跳转到search page, 而不是显示搜索框.&ndash;&gt;-->
<!--<div id="fastSearch">-->
<!--  <input id="searchInput" tabindex="0">-->
<!--  <ul id="searchResults">-->
<!--  </ul>-->
<!--</div>-->
<!--<script src="/js/fuse.min.js"></script> &lt;!&ndash; download and copy over fuse.min.js file from fusejs.io &ndash;&gt;-->
<!--<script src="/js/fastsearch.js"></script>-->

<script>
  // 相比https://ttys3.dev/post/hugo-fast-search/, 我修改了很多部分, 目前的逻辑很简单:
  // 监听页面事件:
  //如果点击了search-btn或者键盘输入了`Alt` + `\n`, 则会跳转到search page.
  //如果键盘输入了`Esc`, 则会跳转到homepage
  var search_page_relative_url = "/search"
  // ==========================================
  // The main keyboard event listener running the show
  //
  document.addEventListener('keydown', function(event) {

    // `Alt` + `/` to show search.
    if (event.altKey && event.which === 191) {
      // Load json search index if first time invoking search
      // Means we don't load json unless searches are going to happen; keep user payload small unless needed
      navToSearchPage(event)
    }

    // Allow ESC (27) to re-navigate to home page
    if (event.keyCode == 27) {
      navToHomePage()
    }
  });


  document.querySelector("#search-btn").onclick = function(e) {
    e.stopPropagation();
    navToSearchPage()
  }


  function navToHomePage() {
    window.location.href = "/"
  }

  function navToSearchPage() {
    window.location.href = search_page_relative_url
    // document.getElementById("fastSearch").style.visibility = "visible" // show search box
    // document.getElementById("searchInput").focus() // put focus in input box so you can just start typing
    // searchVisible = true
  }
</script>
```

### Config.toml

在配置文件`Config.toml`中，添加以下内容

```ini
[outputs]
home = ["HTML", "RSS", "JSON"]
复制代码
```

如果已经存在 `[outputs]`这项，就在`home`中增加`"JSON"`格式.



访问`localhost:1313/search`就可以看到search api. 也



## Result

按上述步骤完成之后, 可以点击页面右上角的搜索图标, 或者键盘输入`Alt` + `/`来进入search page.

Search button:

![image-20230504052040712](/Users/lyk/Library/Application Support/typora-user-images/image-20230504052040712.png)



Search page:

![image-20230503104252751](/Users/lyk/Library/Application Support/typora-user-images/image-20230503104252751.png)

注意到, 在search page点击`Show more`按钮会没有反应, 之前说过了这个问题.

## TODO

Local Search暂时是实现了, 但是还有很多遗留问题. 

1. 首先是`fuse.js`对中文搜索的支持不好, 经过测试, `fuse.js`库本身就有很大概率搜索不出来中文内容. 

2. 使用search page有如上所说的bug, 而且也不符合用户直觉. 之后应该使用方案1, 优化search组件, 做到像Hexo local-search那样的搜索功能.

   * Hexo local search: https://github.com/theme-next/hexo-generator-searchdb

     可以参考一下他的实现.

   * 这个theme支持search, 可以学一下: https://github.com/adityatelange/hugo-PaperMod/

     不过它也用了`fuse.js`, 亲测对中文支持不行.

# Toc

[ref](https://shishuochen.gitee.io/2020/uffick8u1/#16-%E4%B8%BA%E6%96%87%E7%AB%A0%E6%B7%BB%E5%8A%A0%E7%9B%AE%E5%BD%95)

这个我没有添加, 因为Terminal theme默认实现了一个Toc, 和新添加的冲突了.

在`themes/terminal/layouts/_default/single.html`中可以看到默认Toc的配置:

```html
  {{ if (.Params.Toc | default .Site.Params.Toc) }}
    <div class="table-of-contents">
      <h2>
        {{ (.Params.TocTitle | default .Site.Params.TocTitle) | default "Table of Contents" }}
      </h2>
      {{ .TableOfContents }}
    </div>
  {{ end }}
```

## TODO

默认的Toc是极简主义的, 不够完美, 我希望它能换个样式出现在Sidebar. 

# Archive Page

教程如下:

* https://cpbotha.net/2021/01/10/super-simple-yearly-post-archives-hugo/
  * 我用这个
* https://note.qidong.name/2018/03/hugo-mathjax/
* https://www.thedroneely.com/posts/generating-archive-pages-with-hugo/

## Step1 Install shortcode

Save the following snippet as `layouts/shortcodes/archive.html`.

```html
{{/*

simple shortcode to display all posts in yearly sections on your archive page
by Charl P. Botha

this is a much simplified version of the yearly post archiving template at:
https://rohanverma.net/blog/2019/11/15/archive-pages-group-by-year-hugo/

*/}}

{{ $posts_num := (len (where .Site.RegularPages "Section" "posts")) }}
{{ $posts_num }}
posts in total

{{ $prev := 3000}}
{{range where .Site.RegularPages "Section" "posts"}}
{{if .Date}}
{{if gt $prev (.Date.Format "2006")}}
# {{ .Date.Format "2006" }}
{{end}}
{{.Date.Format "02 Jan"}} -- [{{.Title}}]({{.Permalink}})
{{ $prev = .Date.Format "2006"}}
{{end}}
{{end}}
```



相比原方案, 我多添加了:

```
{{ $posts_num := (len (where .Site.RegularPages "Section" "posts")) }}
{{ $posts_num }}
posts in total
```

这会额外显示post的总数.

## Step 2: Use shortcode

Use the shortcode on any page as `{{% archive %}}`, as shown in the example below.

For me, I use it in `content/archive.md`

Note here that we’re using [the shortcode syntax for markdown shortcodes](https://gohugo.io/content-management/shortcodes/#shortcodes-with-markdown), i.e. `%` instead of the `<` you might be more used to for HTML shortcodes.

```markdown
---
title: "Posts Archive"
slug: "archive"
date: 2021-01-09T16:17:00+02:00
type: "page"
---

Some text that will appear before the archive.



{{% archive %}}
```

## Step3: Add it as menu item

`Config.toml`:

```toml
      [[languages.en.menu.main]]
        identifier = "archive"
        name = "Archive"
        url = "/archive"
        weight = 2
```

## Result

![image-20230504052857468](/Users/lyk/Library/Application Support/typora-user-images/image-20230504052857468.png)



# Tags Page && Categories Page

这两个的实现和[Archive Page](#Archive-Page)一样, 都是编写一个shordcode, 然后创建md文件, 引用该shortcode. 最后创建一个menu item, 指向该md文件. 

我不想实现Tag cloud, 和我主题的风格不符. 如果想要实现的话, 可以参考:

* https://www.jakewiesler.com/blog/hugo-taxonomies
* https://mertbakir.gitlab.io/hugo/tag-cloud-in-hugo/

注意, Hugo实际上会为Taxonomy中的每个key[生成](https://gohugo.io/content-management/taxonomies/#default-destinations)一个索引页面, 而Taxonomy中默认含有的两个key就是`tags`和`categories`.  因此, 即使不做任何配置, 也可以访问`https://mywebsite.com/tag/`, `https://mywebsite.com/categories`来查看tags/categories page.

但是, Hugo默认生成的page不够美观, 因此要自定义它们. 自定义的tags/categories page 会覆盖默认的, 但如果自定义的page编译失败, 则访问`https://mywebsite.com/XX`得到的是默认生成的page.

## content/{tags, categories}.md

`content/tags.md`:

```
+++
title = "Tags"
toc = false
+++


{{% tags %}}
```

## Shortcode file:

`layouts/shortcodes/tags.html`:

```html
{{ $tag_num := (len .Site.Taxonomies.tags) }}
{{ $tag_num }}
tags in total

{{ range .Site.Taxonomies.tags.ByCount }}
* [{{ .Page.Title }} ({{ .Count }})]({{.Page.Permalink}})
{{ end }}
```



`layouts/shortcodes/categories.html`:

```html
{{ $category_num := (len .Site.Taxonomies.categories) }}
{{ $category_num }}
categories in total

{{ range .Site.Taxonomies.categories }}
* [{{ .Page.Title }} ({{ .Count }})]({{.Page.Permalink}})
{{ end }}
```

# Latex Render

[Ref: 在Hugo中使用MathJax](https://note.qidong.name/2018/03/hugo-mathjax/)

Hugo对Pandoc等后端渲染工具等支持好像很差, 对Latex的支持也很差. 因此我用了[Mathjax](https://www.mathjax.org/#gettingstarted)做前端渲染.



在`layouts/partials/extended_head.html`添加:

```
{{ partial "mathjax.html" . }}
```





然后在`layouts/partials/mathjax.html`里写partial:

```html
{{ if .Params.mathjax }}
<script>
    MathJax = {
        tex: {
            inlineMath: [["$", "$"]],
        },
        displayMath: [
            ["$$", "$$"],
            ["\[\[", "\]\]"],
        ],
        svg: {
            fontCache: "global",
        },
    };
</script>
<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
<script
        id="MathJax-script"
        async
        src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"
></script>
{{ end }}
```



# Back2Top

Hexo Next有Back2Top插件, 也就是网页角落有一个显示当前阅读进度以及点击后跳转到网页最顶端的小箭头. 这里模仿它实现.

[ref: 右下角添加到顶部按钮和进度比例](https://shishuochen.gitee.io/2020/uffick8u1/#10-%E5%8F%B3%E4%B8%8B%E8%A7%92%E6%B7%BB%E5%8A%A0%E5%88%B0%E9%A1%B6%E9%83%A8%E6%8C%89%E9%92%AE%E5%92%8C%E8%BF%9B%E5%BA%A6%E6%AF%94%E4%BE%8B)



先定义组件样式, 在`layouts/partials/extended_head.html`中添加:

```html
<style>
    /*back2top*/
    /** 进度比例和到顶部**/
    .back-to-top {
        box-sizing: border-box;
        border-radius: 8px;       /** 圆角**/
        position: fixed;
        right: 30px;
        z-index: 1050;
        padding: 0 6px;
        width: initial;
        background: #222;
        font-size: 12px;
        opacity: 0.6;
        color: #fff;
        cursor: pointer;
        text-align: center;
        transition-property: bottom;
        transition-duration: 0.2s;
        transition-timing-function: ease-in-out;
        transition-delay: 0s;
        bottom: -40px;
    }

    .back-top-active {
        bottom: 30px;
    }

    @media (max-width: 767px) {

        .back-to-top {
            right: 10px;
        }


        .back-top-active {
            bottom: 10px;
        }
    }
</style>
```



然后写html, js, 在 `layouts/partials/extended_footer.html中`添加:

```html
<!-- For back2top -->
<div class="footer-box">
  <footer class="footer">
    <div class="copyright">
      &copy;
      {{ with .Site.Params.since }}
      <span itemprop="copyrightYear">{{.}} - {{ now.Year }}</span>
      {{ end }}
      <span class="with-love">
         <i class="iconfont icon-love"></i>
      </span>
      {{ if .Site.Params.author }}
      <span class="author" itemprop="copyrightHolder"><a href="{{ .Site.BaseURL }}">{{ .Site.Params.author  }}</a> |
      </span>
      {{ end }}
      {{ with .Site.Params.beian }}
      <a href="http://www.miibeian.gov.cn/" target="_blank" rel="external nofollow">{{ . }} </a> |
      {{ end }}
      <span>Powered by <a href="https://gohugo.io/" target="_blank" rel="external nofollow">Hugo</a> & <a
              href="https://github.com/Mogeko/Mogege" target="_blank" rel="external nofollow">Mogege</a></span>
  </footer>
  <!-- 设置滚动条和进度比例 -->
  <div class="back-to-top" id="back_to_top">
    <!-- 箭头-->
    <!-- https://www.toptal.com/designers/htmlarrows/-->
    <!-- 箭头 <span>&#8593;</span> -->
    <span><i class="fas fa-arrow-up"></i></span> <!-- 需要FontAwesome支持，参见文末-->
    <!-- 进度比例 -->
    <span class="scrollpercent">
            <span id="back_to_top_text">0</span>%
         </span>
  </div>
</div>
<script>
  let sideBarOpen = 'sidebar-open';
  let body = document.body;
  let back2Top = document.querySelector('#back_to_top'),
          back2TopText = document.querySelector('#back_to_top_text'),
          drawerBox = document.querySelector('#drawer_box'),
          rightSideBar = document.querySelector('.sidebar'),
          viewport = document.querySelector('body');

  function scrollAnimation(currentY, targetY) {

    let needScrollTop = targetY - currentY
    let _currentY = currentY
    setTimeout(() => {
      const dist = Math.ceil(needScrollTop / 10)
      _currentY += dist
      window.scrollTo(_currentY, currentY)
      if (needScrollTop > 10 || needScrollTop < -10) {
        scrollAnimation(_currentY, targetY)
      } else {
        window.scrollTo(_currentY, targetY)
      }
    }, 1)
  }

  back2Top.addEventListener("click", function (e) {
    scrollAnimation(document.scrollingElement.scrollTop, 0);
    e.stopPropagation();
    return false;
  });

  window.addEventListener('scroll', function (e) {
    let percent = document.scrollingElement.scrollTop / (document.scrollingElement.scrollHeight - document.scrollingElement.clientHeight) * 100;
    if (percent > 1 && !back2Top.classList.contains('back-top-active')) {
      back2Top.classList.add('back-top-active');
    }
    if (percent == 0) {
      back2Top.classList.remove('back-top-active');
    }
    if (back2TopText) {
      back2TopText.textContent = Math.floor(percent);
    }
  });
  let hasCacu = false;
  window.onresize = function () {
    calcuHeight();
  }
</script>

```

注意, 跳转到最顶端的小箭头图片得自己找, 这里用的是Font Awesome的图片, 需要[添加Font Awesome支持](#Support-Font-Awesome-Image).

# Support Font Awesome Image

- 进入 [Font Awesome 官网](https://fontawesome.com/start)

- 注册账号登录获取html代码. 形如: 

  ```html
  <script src="https://kit.fontawesome.com/XXXXXX.js" crossorigin="anonymous"></script>
  ```

  

- 在`layouts/partials/extended_head.html` 添加代码

- 如果要在文章中使用Font Awesome Image, 可以在文章中使用 `<i class="fab fa-iconname"></i>` 或者 `<i class="fas fa-iconname"></i>`

# Deployment

[Host on GitHub](https://gohugo.io/hosting-and-deployment/hosting-on-github/) 



根据: https://waynerv.com/posts/setup-blog-with-hugo-and-github-pages/

很多Hugo theme在网站baseURL具有子页面时无法正确构建文件, 结果就是CSS文件构建不出来. 我也遇到了这个问题:

![image-20230504073915589](/Users/lyk/Library/Application Support/typora-user-images/image-20230504073915589.png)

这意味着无法用项目主页发布网页.

# Todo

* 图像放大Image zoom
* 图像懒加载
* Local search
* 把博客迁移到hugo, 主要就是formar matter和permalink.
