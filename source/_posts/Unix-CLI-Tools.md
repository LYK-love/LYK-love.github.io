---
title: Unix CLI Tools
tags:
  - Linux
  - Shell
categories: Toolkit
date: 2022-09-13 14:57:44
---


一些常用的命令行工具，和它们的现代替代

ref: [MIT  lesson](https://missing.csail.mit.edu/2020/shell-tools/), [Unix命令的现代替代](https://github.com/ibraheemdev/modern-unix)

<!--more-->

# Easy Installation

对于传统UnixCLi工具,都已经被加入到Unix标准工具集中,不需要手动下载了. 而很多新工具需要手动下载. 以下列出的所有新工具均可以用包管理器( `yay` for Arch, `brew` for OSX )下载. 为了方便, 我还提供了[依赖列表](https://github.com/LYK-love/PackageLists)来批量下载.

## 依赖列表说明

文件名格式为`[XX_Packages]_[Platform[_Advanced]]].txt`:

* `[xx_packages]`: 就是包的类型, 比如R`esource_Monitoring_Packages`等等
* `[Platform]`:包兼容的平台
  * `Linux`: 故名思义,就是Linux下可以安装的包
  * `Mac`: Mac OSX下可以安装的包. 总体来说和linux下没有大的区别
  * `General`:Linux和Mac同时兼容的包

* `[XX]_[Platform[_Advanced]`: 如果一个列表出现了有和无`Advanced`的两个版本, 说明该列表的类型内有些包用处不大, 不需要安装, 也就没有包括在无`Advanced`的列表里面. 而`Advanced`列表中包含了全部包. 
  * 比如同为终端文件浏览器的`ranger`和`broot`,一般情况下使用前者就够了, 因此 `File&Oir_Operations_Packages_General.txt`只包含了`ranger`, 而`File&Oir_Operations_Packages_Anvanced.txt`包含了后者

## 依赖列表使用

Mac:

```
brew install $(cat [packages].txt)
```

for other platform just replace brew with your correspondding package manager

# File and Dir

For mac:

```
brew install coreutils
```



`File&Dir_Operations_Packages_General.txt`: 没安装broot

```
exa	ranger	bat	diff-so-fancy	fd	ripgrep
```



`File&Dir_Operations_Packages_Advanced.txt`: 把broot加上了

```
exa	ranger	bat	diff-so-fancy	fd	ripgrep broot
```

## 列出目录: exa

`exa`是`ls`命令的替代品，可以彩色输出目录内容，更容易辨识:

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

## 终端文件浏览器: ranger / broot

* ranger: 终端文件浏览器, 支持vim语法

* broot: 类似ranger的终端文件浏览器， 不支持vim语法，但是能浏览媒体文件

  Usage:

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

  

## bat & fx & hexyl

* [bat](https://github.com/sharkdp/bat) : `cat`命令的替代品，输出文本文件的内容，并且带有`cat`所没有的代码高亮和行号

  ```
  yay -S bat
  ```

  usage:

  ```shell
  bat README.md
  ```

* [fx](https://github.com/antonmedv/fx) 或者 [jq](https://github.com/stedolan/jq): 浏览JSON 文件

  ```
  yay -S fx
  ```

  usage:

  ```
  fx data.json
  ```

* [hexyl](https://github.com/sharkdp/hexyl): 浏览二进制文件

  ```shell
  yay -S hexyl
  ```

  usage:

  ```
  hexyl example.jpg
  ```

  



### diff-so-fancy

* [diff-so-fancy](https://github.com/so-fancy/diff-so-fancy) : 对diff进行了改进, 使得命令行的 diff 操作具有类似 GitHub 的页面效果. 可以用来替代git diff和diff

  ```shell
  yay -S diff-so-fancy
  ```

安装后, 参考官方文档进行配置:



## With diff

Use `-u` with `diff` for unified output, and pipe the output to `diff-so-fancy`:

```shell
diff -u file_a file_b | diff-so-fancy
```

## find/fd

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

## grep & ripgrep

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



* [ripgrep](https://github.com/BurntSushi/ripgrep) 是`grep`命令的替代品，用来搜索文件内容, 默认带有行号和搜索词高亮，速度也更快:

  它跟`grep`的用法类似。下面例子是搜索当前目录里面，所有内容包含字符串`foo`的 Markdown 文件。

> ```bash
> # grep 的写法
> $ grep foo *.md
> 
> # ripgrep 的写法
> $ rg foo *.md
> ```





## Finding Shell History

`Finding_Shell_History_Packages_General.txt`:

```
fzf mcfly
```



* `history` : 在STDOUT上打印shell命令记录, 可以用 `history | grep find` 进行检索
* `Ctrl+R` + type a substring you want to match for commands in your history来检索历史命令. This can also be enabled with the UP/DOWN arrows in [zsh](https://github.com/zsh-users/zsh-history-substring-search)

### fzf && mcfly

* `fzf` : GO 语言编写的交互式的 Unix 命令行工具。可以用来查找任何 **列表**内容，文件、Git 分支、进程等。所有的命令行工具可以生成列表输出的都可以再通过管道 pipe 到 fzf 上进行搜索和查找.

  ```shell
  yay -S fzf
  ```

  这个命令比较复杂, 见[教程](https://zhuanlan.zhihu.com/p/41859976#:~:text=Fuzzy%20finder%20%28fzf%2Bvim%29%20%E4%BD%BF%E7%94%A8%E5%85%A8%E6%8C%87%E5%8D%97%201%20%E5%AE%89%E8%A3%85%20%E4%BB%A5%20macOS,fzf%20%E9%BB%98%E8%AE%A4%E9%85%8D%E7%BD%AE%E5%8F%82%E6%95%B0%208%20%E6%A0%B8%E5%BF%83%E5%91%BD%E4%BB%A4%20FZF_DEFAULT_COMMAND%20...%20More%20items)

* [McFly](https://github.com/cantino/mcfly) 是`ctrl-r`的替代品，安装以后，只要按下`ctrl-r`，就会出现一个更好用的搜索界面

  ```
  yay -S mcfly
  ```

  

# Version Control

## Configure git: diff-so-fancy

Configure git to use `diff-so-fancy` for all diff output:

```shell
git config --global core.pager "diff-so-fancy | less --tabs=4 -RFX"
git config --global interactive.diffFilter "diff-so-fancy --patch"
```

Improved colors for the highlighted bits

The default Git colors are not optimal. The colors used for the screenshot above were:

```shell
git config --global color.ui true

git config --global color.diff-highlight.oldNormal    "red bold"
git config --global color.diff-highlight.oldHighlight "red bold 52"
git config --global color.diff-highlight.newNormal    "green bold"
git config --global color.diff-highlight.newHighlight "green bold 22"

git config --global color.diff.meta       "11"
git config --global color.diff.frag       "magenta bold"
git config --global color.diff.func       "146 bold"
git config --global color.diff.commit     "yellow bold"
git config --global color.diff.old        "red bold"
git config --global color.diff.new        "green bold"
git config --global color.diff.whitespace "red reverse"
```

以后每次执行`git diff`，就会输出它的执行结果

## gitupdate

[gitupdate](https://github.com/nikitavoloboev/gitupdate)是一个工具, 用于Commit and push updated files with file names as commit message:

Install: 

```
go install github.com/nikitavoloboev/gitupdate@latest
```



Usage:

You can either use it by passing it a file path (with git repo) that you want to commit. i.e.

```
gitupdate /Users/nikivi/src/cli/gitupdate
```

Or if you are already in the git directory you want to commit, run:

```
gitupdate .
```

This will add all files that have changed since last commit and will include all the file names (without extension) as the commit message. [Example use](https://github.com/nikitavoloboev/knowledge/commits/main).

If you want to only consider top level folders for the commit message, use the `--top` (or `-t` for short) flag.

# Text Operation

`Text_Operations_Packages_General.txt`

```
choose	jq	
```

## choose 

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

## jq

* `jq`: `sed` for JSON data.

# Resource Monitoring

`Resource_Monitoring_Packages_General.txt`:

```
htop	bottom	iotop	procs	duf	ncdu	free	lsof
```

可以酌情添加`glances`和`dstat`

## General Monitor: htop && bottom && iotop

* `top`: 传统的资源监控工具

* [`htop`](https://htop.dev/):  `htop` has a myriad of options and keybinds, some useful ones are: `<F6>` to sort processes, `t` to show tree hierarchy and `h` to toggle threads. 
* [`glances`](https://nicolargo.github.io/glances/): alternative for htop. with a great UI.
* For , [`dstat`](http://dag.wiee.rs/home-made/dstat/) : alternative for htop. with aggregate measures across all processes. It can computes real-time resource metrics for lots of different subsystems like I/O, networking, CPU utilization, context switches, &c.



* [`bottom`](https://github.com/ClementTsang/bottom): Yet another cross-platform graphical process/system monitor. You can run bottom using `btm`.
  - For help on flags, use `btm -h` for a quick overview or `btm --help` for more details.
  - For info on key and mouse bindings, press `?` inside bottom or refer to the [documentation](https://clementtsang.github.io/bottom/nightly/).

* [`iotop`](https://www.man7.org/linux/man-pages/man8/iotop.8.html) displays live **I/O usage information** and is handy to check if a process is doing heavy I/O disk operations

## Process Info:procs

* `ps`： 显示进程信息
* `procs`:  `ps`的现代替代

## Disk Usage: duf, ncdu

* `df` : 显示磁盘占用情况

* [`du`](http://man7.org/linux/man-pages/man1/du.1.html) 显示当前目录下每个文件占用的磁盘空间
  *  `-h` ： print with **h**uman readable format.



* `duf`： `df`的现代替代
* `ncdu`： `du`的现代替代

## Memory Usage: free

*  [`free`](https://www.man7.org/linux/man-pages/man1/free.1.html) displays the total amount of free and used memory in the system. Memory is also displayed in tools like `htop`.

## Open Files: lsof

*  [`lsof`](https://www.man7.org/linux/man-pages/man8/lsof.8.html) lists file information about files opened by processes. It can be quite useful for checking which process has opened a specific file.

# Networking

`networking_packages_Linux.txt`:

```
ss	iproute2	nethlogs	iftop	gping	dog
```



`Networking_Packages_Mac.txt`: 没有`ss`, `iproute2`改成了`iproute2mac`

```
iproute2mac	nethlogs	iftop	gping	dog
```

## Network Package Monitor: ss

* [`ss`](https://www.cnblogs.com/duanxz/p/4669798.html): short for "**socket statistics**".  `ss` lets you monitor incoming and outgoing network packets statistics as well as interface statistics. A common use case of `ss` is figuring out what process is using a given port in a machine. 

  * 当服务器的socket连接数量变得非常大时，无论是使用netstat命令还是直接cat /proc/net/tcp，执行速度都会很慢, 用ss才是节省时间。

  * [教程](https://www.igoroseledko.com/socket-statistics-ss-command/)
  * 该工具似乎没有mac版

## Network Config: ip

* `ip`: 用于操作路由,网络设备和网络接口. 是`netstat` and `ifconfig` 的现代替代, 后二者已经停止维护了，可能不会被包含在新的Linux发行版中. `ip`命令位于iproute2工具包中. 

  Linux:

  ```shell
  apt install iproute2
  ```

  [Mac版本](https://github.com/brona/iproute2mac):

  ```shell
  brew install iproute2mac
  ```

### Usage

也可以手动在`/etc/network/interfaces`内永久地添加路由信息

* 查看路由表

  ```
  ip route
  ```

  注意，物理上的路由表和转发表，在Linux内核中被抽象成了一个东西，不作区分，所以统称为路由表

  如果用netstat: `netstat -nr`

* Add a new default gateway route:

  ```
  add default via <gateway_IP>
  ```



* Add/Delete an IP address to an interface:

  ```
  sudo ip route add <network_ip>/<cidr> via <gateway_ip> [ dev <network_card_name> ]
  ```

  * 如果不指定网络设备，则会默认使用第一块网卡( 不会使用环回地址)

  * 也可以添加默认路由: 把`<network_ip>/<cidr>`换成`default`

    



* Modify an existing route using ip route command

  ```
  sudo ip route change 
  ```



* Clear routes with flush using ip route command

  ```
  sudo ip route flush [ip]
  ```



* Clear all the routes from the routing table using ip route command

  ```
  sudo ip route flush table main
  ```

## Network Usage: nethogs, iftop

- [`nethogs`](https://github.com/raboof/nethogs) and [`iftop`](http://www.ex-parrot.com/pdw/iftop/) are good interactive CLI tools for monitoring network usage.

If you want to test these tools you can also artificially impose loads on the machine using the [`stress`](https://linux.die.net/man/1/stress) command.

## Network Connections: gping

* [`gping`](https://github.com/orf/gping): `ping`, but with a graph.

## NetworkRequests: httpie



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

## DNS: dog

* [dog](https://dns.lookup.dog/) : 是`dig`命令的替代品，用来发出 DNS 查询。它的用法比`dig`简单多了。

  ```shell
  # 默认查询 A 记录
  dog example.net
  
  # 查询多个记录
  dog example.net A NS MX
  ```

  

# Benchmarking

`Benchmarking_Packages_General.txt`:

```
hyperfine
```

## hyperfine

* [`hyperfine`](https://github.com/sharkdp/hyperfine): A command-line benchmarking tool.

# Calculating

`Calculating_Packages_General.txt`

```
scal
```

## sc

* `sc`: short for: `scal`

# Efficiency

## tldr

```
yay -S tldr
```

或者用man/info，后者的信息存放在`/usr/info`

