---
title: Fuse.js
tags:
---



[Fuse.js](https://fusejs.io/demo.html#live-demo)对中文的支持很差. 

# Bad Chinese Support

这里是Fuse.js对中文支持差的一个例子.

1. 首先, 创建文件夹, 安装Fuse.js.

   ```
   mkdir test_fuse
   cd test_fuse
   yarn add fuse.js
   ```

2. 接着创建测试文件:

   ```
   touch test.js
   ```

3. 编辑该文件, 添加如下代码:

   ```javascript
   const Fuse = require('fuse.js')
   
   const options = {
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
   
   
   var list = [
       {
           "categories": [
               "Essay"
           ],
           "contents": "“我始终坚信，舞蹈是二十世纪的仪式”",
           "permalink": "//localhost:1313/posts/%E7%81%AB%E9%B8%9F/",
           "posts_num": 12,
           "tags": [
               "Reading"
           ],
           "title": "火鸟"
       }
   ]
   
   const fuse = new Fuse(list, options);
   
   // Change the pattern
   const pattern = "舞蹈"
   
   console.log(fuse.search(pattern))
   ```

执行该文件, 会发现结果为空列表. 这是很离谱的, 要知道我搜索的列表就这一个元素, 而且contet还这么短. 因此在中文网站上就不要用`fuse.js`了. 考虑到Hugo的search方案大部分都用的fuse.js, 这是个很麻烦的事.
