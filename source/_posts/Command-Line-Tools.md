---
title: Command-Line Tools
tags: shell Linux
categories: Toolkit
date: 2022-02-08 18:17:19
---



介绍了一些常用的命令行工具，和它们的现代替代

ref: [MIT  lesson](https://missing.csail.mit.edu/2020/shell-tools/), [Unix命令的现代替代](https://github.com/ibraheemdev/modern-unix)

<!--more-->

# Shell Tools

介绍一些常用的命令行工具

##  目录浏览

### exa

`exa`是`ls`命令的替代品，可以彩色输出目录内容，更容易辨识。

```shell
exa --long --git
```

* 参数`--git`表示输出文件的 Git 状态。
  - `N`：新文件
  - `M`：文件有变动
  - `I`：该文件被忽略



除了平铺显示，`exa`还支持目录的树状显示。

```shell
exa --tree --level=2
```



## Directory Navigation

### fasd & autojump

Fasd ranks files and directories by [*frecency*](https://web.archive.org/web/20210421120120/https://developer.mozilla.org/en-US/docs/Mozilla/Tech/Places/Frecency_algorithm), that is, by both *frequency* and *recency*. By default, `fasd` adds a `z` command that you can use to quickly `cd` using a substring of a *frecent* directory. For example, if you often go to  `/home/user/files/cool_project` you can simply use `z cool` to jump there. Using autojump, this same change of directory could be accomplished using `j cool`.



### broot

类似ranger的终端文件管理器， 不支持vim语法，但是能浏览媒体文件



列出当前目录的文件信息。

```shell 
br -sdph
```

* `-s`：显示文件体积
* `-d`：显示文件时间
* `-p`：显示文件权限
* `-h`：显示隐藏文件





在broot界面中，可以完成各种文件操作：

- 搜索：输入搜索词
- 复制：输入`:cp <复制后的文件名>`
- 删除：输入`:rm`
- 改名：输入`:mv <新文件名>`
- 退出：输入`:q`



还可以预览文件：

* 打开外部关联程序： 通过上下箭头选中文件，然后按下右箭头`→`
* 在当前窗口预览文件： `ctrl + →`

## 文件内容查看

### bat & fx & hexyl

[bat](https://github.com/sharkdp/bat) 是`cat`命令的替代品，输出文本文件的内容，并且带有`cat`所没有的代码高亮和行号。

> ```bash
> $ bat README.md
> ```

如果浏览的是 JSON 文件，还可以使用 [fx](https://github.com/antonmedv/fx) 或者 [jq](https://github.com/stedolan/jq)。

> ```bash
> $ fx data.json
> ```

如果浏览的是二进制文件，使用 [hexyl](https://github.com/sharkdp/hexyl)。

> ```bash
> $ hexyl example.jpg
> ```



## 文件内容比对

### diff-so-fancy

[diff-so-fancy](https://github.com/so-fancy/diff-so-fancy) 是 git diff 的替代品，使得命令行的 diff 操作具有类似 GitHub 的页面效果。

安装后，参考官方文档，将它配置为 Git 的默认 diff 工具就可以了。以后每次执行`git diff`，就会输出它的执行结果。

## Finding files

One of the most common repetitive tasks that every programmer faces is finding files or directories. All UNIX-like systems come packaged with [`find`](https://www.man7.org/linux/man-pages/man1/find.1.html), a great shell tool to find files. `find` will recursively search for files matching some criteria. Some examples:

```shell
# Find all directories named src
find . -name src -type d
# Find all python files that have a folder named test in their path
find . -path '*/test/*.py' -type f
# Find all files modified in the last day
find . -mtime -1
# Find all zip files with size in range 500k to 10M
find . -size +500k -size -10M -name '*.tar.gz'
```

Beyond listing files, find can also perform actions over files that match your query. This property can be incredibly helpful to simplify what could be fairly monotonous tasks.

```shell
# Delete all files with .tmp extension
find . -name '*.tmp' -exec rm {} \;
# Find all PNG files and convert them to JPG
find . -name '*.png' -exec convert {} {}.jpg \;
```

Despite `find`’s ubiquitousness, its syntax can sometimes be tricky to remember. For instance, to simply find files that match some pattern `PATTERN` you have to execute `find -name '*PATTERN*'` (or `-iname` if you want the pattern matching to be case insensitive). You could start building aliases for those scenarios, but part of the shell philosophy is that it is good to explore alternatives. Remember, one of the best properties of the shell is that you are just calling programs, so you can find (or even write yourself) replacements for some. For instance, [`fd`](https://github.com/sharkdp/fd) is a simple, fast, and user-friendly alternative to `find`. It offers some nice defaults like colorized output, default regex matching, and Unicode support. It also has, in my opinion, a more intuitive syntax. For example, the syntax to find a pattern `PATTERN` is `fd PATTERN`.

Most would agree that `find` and `fd` are good, but some of you might be wondering about the efficiency of looking for files every time versus compiling some sort of index or database for quickly searching. That is what [`locate`](https://www.man7.org/linux/man-pages/man1/locate.1.html) is for. `locate` uses a database that is updated using [`updatedb`](https://www.man7.org/linux/man-pages/man1/updatedb.1.html). In most systems, `updatedb` is updated daily via [`cron`](https://www.man7.org/linux/man-pages/man8/cron.8.html). Therefore one trade-off between the two is speed vs freshness. Moreover `find` and similar tools can also find files using attributes such as file size, modification time, or file permissions, while `locate` just uses the file name. A more in-depth comparison can be found [here](https://unix.stackexchange.com/questions/60205/locate-vs-find-usage-pros-and-cons-of-each-other).

### fd

## Finding code

### grep & ripgrep

For now, know that `grep` has many flags that make it a very versatile tool. Some I frequently use are `-C` for getting **C**ontext around the matching line and `-v` for in**v**erting the match, i.e. print all lines that do **not** match the pattern. For example, `grep -C 5` will print 5 lines before and after the match. When it comes to quickly searching through many files, you want to use `-R` since it will **R**ecursively go into directories and look for files for the matching string.

But `grep -R` can be improved in many ways, such as ignoring `.git` folders, using multi CPU support, &c. Many `grep` alternatives have been developed, including [ack](https://beyondgrep.com/), [ag](https://github.com/ggreer/the_silver_searcher) and [rg](https://github.com/BurntSushi/ripgrep). All of them are fantastic and pretty much provide the same functionality. For now I am sticking with ripgrep (`rg`), given how fast and intuitive it is. Some examples:

```shell
# Find all python files where I used the requests library
rg -t py 'import requests'
# Find all files (including hidden files) without a shebang line
rg -u --files-without-match "^#!"
# Find all matches of foo and print the following 5 lines
rg foo -A 5
# Print statistics of matches (# of matched lines and files )
rg --stats PATTERN
```

Note that as with `find`/`fd`, it is important that you know that these problems can be quickly solved using one of these tools, while the specific tools you use are not as important.





[ripgrep](https://github.com/BurntSushi/ripgrep) 是`grep`命令的替代品，用来搜索文件内容。

它跟`grep`的用法类似。下面例子是搜索当前目录里面，所有内容包含字符串`foo`的 Markdown 文件。

> ```bash
> # grep 的写法
> $ grep foo *.md
> 
> # ripgrep 的写法
> $ rg foo *.md
> ```

`ripgrep`的主要优势在于，默认带有行号和搜索词高亮，速度也更快。

![img](https://cdn.beekka.com/blogimg/asset/202201/bg2022012706.webp)



## Finding shell commands

### fzf



The `history` command will let you access your shell history programmatically. It will print your shell history to the standard output. If we want to search there we can pipe that output to `grep` and search for patterns. `history | grep find` will print commands that contain the substring “find”.

In most shells, you can make use of `Ctrl+R` to perform backwards search through your history. After pressing `Ctrl+R`, you can type a substring you want to match for commands in your history. As you keep pressing it, you will cycle through the matches in your history. This can also be enabled with the UP/DOWN arrows in [zsh](https://github.com/zsh-users/zsh-history-substring-search). A nice addition on top of `Ctrl+R` comes with using [fzf](https://github.com/junegunn/fzf/wiki/Configuring-shell-key-bindings#ctrl-r) bindings. `fzf` is a general-purpose fuzzy finder that can be used with many commands. Here it is used to fuzzily match through your history and present results in a convenient and visually pleasing manner.

### mcfly

[McFly](https://github.com/cantino/mcfly) 是`ctrl-r`的替代品，用来搜索 Shell 的操作历史。

安装以后，只要按下`ctrl-r`，就会出现一个更好用的搜索界面。

##  文本处理

### choose

[choose](https://github.com/theryangeary/choose) 是`cut`命令的替代品，用来选中指定的栏位。

它的优势主要是语法更简单，比如输出文件的第一列。

> ```bash
> # cut 的写法
> $ cat data.txt | cut -d " " -f 1
> # or
> $ cut -d " " -f 1 data.txt
> 
> # choose 的写法
> $ cat data.txt | choose 0
> # or
> $ choose 0 -i data.txt
> ```

## text editing

`jq`: `sed` for JSON data.

## Resource Monitoring

### **General Monitoring** 

#### htop

* [`htop`](https://htop.dev/):  `htop` has a myriad of options and keybinds, some useful ones are: `<F6>` to sort processes, `t` to show tree hierarchy and `h` to toggle threads. 
* See also [`glances`](https://nicolargo.github.io/glances/) for similar implementation with a great UI.
* For getting aggregate measures across all processes, [`dstat`](http://dag.wiee.rs/home-made/dstat/) is another nifty tool that computes real-time resource metrics for lots of different subsystems like I/O, networking, CPU utilization, context switches, &c.

#### bottom

[`bottom`](https://github.com/ClementTsang/bottom): Yet another cross-platform graphical process/system monitor.

Usage:

You can run bottom using `btm`.

- For help on flags, use `btm -h` for a quick overview or `btm --help` for more details.
- For info on key and mouse bindings, press `?` inside bottom or refer to the [documentation](https://clementtsang.github.io/bottom/nightly/).

### I/O operations

 [`iotop`](https://www.man7.org/linux/man-pages/man8/iotop.8.html) displays live I/O usage information and is handy to check if a process is doing heavy I/O disk operations



### **process  information**

* `ps`： 显示进程信息
  * `procs`:  `ps`的现代替代

### **Disk Usage** -

* `df` : 显示磁盘占用情况
  *  `duf`： `df`的现代替代
  
* [`du`](http://man7.org/linux/man-pages/man1/du.1.html) 显示当前目录下每个文件占用的磁盘空间

  *  `-h` ： print with **h**uman readable format.

  *  `ncdu`： `du`的现代替代

### **Memory Usage** -

*  [`free`](https://www.man7.org/linux/man-pages/man1/free.1.html) displays the total amount of free and used memory in the system. Memory is also displayed in tools like `htop`.

### **Open Files** -

*  [`lsof`](https://www.man7.org/linux/man-pages/man8/lsof.8.html) lists file information about files opened by processes. It can be quite useful for checking which process has opened a specific file.

### **Network Connections and Config** 

* [`ss`](https://www.man7.org/linux/man-pages/man8/ss.8.html) lets you monitor incoming and outgoing network packets statistics as well as interface statistics. A common use case of `ss` is figuring out what process is using a given port in a machine. 

* For displaying routing, network devices and interfaces you can use [`ip`](http://man7.org/linux/man-pages/man8/ip.8.html). Note that `netstat` and `ifconfig` have been deprecated in favor of the former tools respectively.

*  [`gping`](https://github.com/orf/gping): `ping`, but with a graph.

- **Network Usage** - [`nethogs`](https://github.com/raboof/nethogs) and [`iftop`](http://www.ex-parrot.com/pdw/iftop/) are good interactive CLI tools for monitoring network usage.

If you want to test these tools you can also artificially impose loads on the machine using the [`stress`](https://linux.die.net/man/1/stress) command.

#### httpie

[httpie](https://github.com/httpie/httpie) 是 curl 的替代品，用来发出 HTTP 请求。

它的特点是语法更简单，并且服务器的返回内容会格式化高亮显示。

![img](https://cdn.beekka.com/blogimg/asset/202201/bg2022012707.webp)

下面是发出 PUT 请求的例子。

> ```bash
> # curl 的写法
> $ curl -X PUT -d hello=world example.com
> 
> # httpie 的写法
> $ http PUT example.com hello=world 
> ```

同类项目还有 [curlie](https://github.com/rs/curlie)、[xh](https://github.com/ducaale/xh)。

[dog](https://dns.lookup.dog/) 是`dig`命令的替代品，用来发出 DNS 查询。它的用法比`dig`简单多了。

> ```bash
> # 默认查询 A 记录
> $ dog example.net
> 
> # 查询多个记录
> $ dog example.net A NS MX
> ```

![img](https://cdn.beekka.com/blogimg/asset/202201/bg2022012804.jpg)

## Benchmarking

### hyperfine

[`hyperfine`](https://github.com/sharkdp/hyperfine)

A command-line benchmarking tool.

# Calculating

## sc

short for: `scal`
