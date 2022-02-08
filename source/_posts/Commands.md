---
title: Commands
categories: Toolkit
date: 2021-05-10 21:14:35
---


# CMD

* 命令和文件名(当然包括文件类型)是不区分大小写的。 即 cd 和 CD 一样， dir 和 DIR 一样。 Desktop 和 desktop 一样, *.pdf  和 *.PDF 一样

TAB键： 自动补完。 不区分大小写

`cd` ： change directory 改变目录

 `cd .. ` : go back to upper directory 回到上一级目录， 注意cd 和 .. 中间也可以没有空格

 `cd ../..` :  回到上两级目录

 `cd \` 直接回到根目录

 `exit`: 退出

<!--more-->

 `dir` ： list the contents of current directory 浏览当前目录（结果按字母顺序排序）.  文件有<DIR>代表它也是个目录

`dir Desktop\SE` 查看SE的内容， 不会改变当前目录

 `dir Desktop\SE\*.pdf`   遍历并列出SE中以.pdf结尾的文件

注意文件名是区分空格的，所以`dir Desktop \SE` 或 `dir Desktop\ SE`  找不到东西

` dir /a `: show hidden directories as well 注意dir 和 /a 中间也可以没有空格

 `cls`： clear your screen

 `↑`键 ：access your command history

` /?` : to access help and options menu

 `mkdir`   制作目录

 `rmdir` 删除一个空的目录

 `rmdir *** /s` 删除一个有内容的目录

`Home`键： bring u to  to the beginning of the command

`End`键：反之

`Ctrl+left` : 一次左移一个词

——————————————————————————————————

-  `echo not sweet > apple.txt`  向 apple.txt中添加not sweet（这会覆盖txt的原内容）
-  如果不想覆盖，只想append， 那就用`echo not sweet >> apple.txt` 
-  `Desktop\test> dir > apple.txt`    向apple.txt中添加test的目录

- 总之 `Desktop\test> *** > apple.txt` 星号部分是向apple.txt中添加的内容，可以是文字，可以是命令， 说到命令，当然·`ttrib`也可以，`cls`也可以。不过把cls append进去很蠢，啥都不会发生。

—————————————————————————————————

 

 `type 文件名` ： 在CMD中打印该文件的内容

 `remove 被移动的 移动到的` ： 顾名思义，当然，连空文件和空目录也会移动

 `rename 原名 新名字` ： 注意文件类型也在名字里，所以一个 XX.txt如果更名为YY(不带.txt)，那么XX会从一个文本文档变成一个文件夹

—————————————————————————————————

` copy` 要被复制的 复制到的 ： 文件复制  

 `xcopy`: 也是复制，但比copy更好（功能更多） 。 xcopy默认只会复制source中的文件，而不包括目录（copy也是如此）。 通过/S 可以让xcopy复制目录和子目录，不包括空目录。， 但copy没有/S的功能，也就是说copy无法复制目录。

 

要打开应用程序，要么转到对应的目录，然后 `start ** .exe`, 要么直接用双引号括住绝对路径

` C:\Users\color 0B`   数字是背景颜色，字母是foreground or text

 `wmic logicaldisk get name` : see all the available command drives

` tree`关键字： 以树状列出目录及其内部目录…

D: 转到D盘根路径

# Browser

* F5刷新网页，重新显示当前页面内容；
* Ctrl+F5博客的系统使用了数据缓存技术。这虽然可以加快网页的打开速度，但却经常出错。比如留言成功再重新打开网页却可能看不到刚才的的留言内容，其原因就是IE会读取本机缓存区而不是从网络服务器中更新数据。这时可以按CTRL+F5的组合键来清除IE缓存，强行刷新网页，这样就可以看到当前网页的最新内容了；
* Shift+F5全部刷新，刷新当前打开的所有网页。