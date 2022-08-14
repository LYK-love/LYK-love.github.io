---
title: Unix Toolkit
tags: Linux
categories: Toolkit
date: 2022-02-19 14:04:37
---


介绍了Unix, Unix Like主机的常用操作

OS可以是各种LINUX发行版和Mac OSX，因此你可以看到各种包管理工具（yay,apt,yum, brew...）, 选自己用的就好

<!--more-->

# 配置ssh免密登陆



主机上生成 ssh key：

```
ssh-keygen -t rsa
```

* 腾讯云的服务器不会默认生成ssh key， 所以也不会有`~/.ssh`文件夹， 其他主机也无法通过ssh连接（`ssh-copy-id`）也不行。 因此腾讯云服务器需要先生成ssh key，才能使用

* (这种情况很罕见)如果主机没有安装ssh，需要先安装`openssh-server`:

  ```shell
  apt install openssh-server
  ```

  

查看`~/.ssh`:

```ssh
❯ ls -l ~/.ssh
total 20
-rw-r--r-- 1 lyk lyk   27  2月 10 15:44 config
-rw------- 1 lyk lyk 2602  2月  9 17:18 id_rsa
-rw-r--r-- 1 lyk lyk  571  2月  9 17:18 id_rsa.pub
-rw------- 1 lyk lyk 3926  2月 19 12:58 known_hosts
-rw------- 1 lyk lyk 3182  2月 19 12:41 known_hosts.old

```

* authorized_keys: 存放远程免密登录的公钥,主要通过这个文件记录多台机器的公钥。(没有则手动创建该文件)

* id_rsa: 生成的私钥文件

* id_rsa.pub: 生成的公钥文件

* known_hosts: 已知的主机公钥清单





服务器上配置ssh免密登陆：

* 将本地 id_rsa.pub 文件的内容拷贝至远程服务器的 ~/.ssh/authorized_keys
  * 如果服务器没有`~/.ssh`，则需要自己创建
* 也可以`ssh-copy-id user@host `

## 本机到本机的免密登陆

本机到本机也是需要配置免密登陆的，但是`root@localhost`需要额外配置，`/etc/ssh/sshd_config`中有一个属性为`PermitRootLogin` ,默认值no不允许进行密码登录，我们需要将其改为yes.：

```shell
vim /etc/ssh/sshd_config
```



然后重启ssh服务:

ubuntu：

```shell
sudo service ssh restart
```

manjaro:

```shell
systemctl restart sshd.service
```

mac:

```shell
sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist
```





ssh会因为各种各样的原因失败，排查ssh问题的命令:

```shell
sshd -T
```



如果远程主机的公钥发生了变化, 那么需要重新纪录远程主机的公钥，这需要先把原来的记录清空：

```bash
ssh-keygen -R [remote-host-ip]
```



# 配置用户

详见后文 *用户操作*



添加用户：

```
sudo adduser [username]
```







## 赋予新用户sudo权限

用adduser创建后的新用户是不能使用sudo的，因为还没有赋予相关root权限，执行以下代码赋予权限

```shell
sudo usermod -a -G adm username
sudo usermod -a -G sudo username
```


或者将用户加到sudoers文件中:



```shell
#添加sudo文件的写权限,命令是:
chmod u+w /etc/sudoers
#编辑sudoers文件
vim /etc/sudoers
#在 root ALL=(ALL) ALL,下面添加lyk ALL=(ALL) ALL 
lyk ALL=(ALL) ALL

#最后删除sudo文件的写权限
chmod u-w /etc/sudoers
```







#   磁盘挂载

`fdisk`：查看磁盘信息

```shell
sudo fdisk -l
```



卸载分区

```shell
#sudo umount  [磁盘路径]
sudo umount /dev/nvme0n1p11
```



将分区格式化为ext4类型

``` shell
#（这里分区为/dev/nvme0n1p11）
sudo mkfs.ext4  /dev/sdb1
```



##  挂载分区（临时）

挂载分区（ 这里挂载到到`/data`目录下 ）

```
#sudo mount  /dev/sdb1  /[目录名] （目录当然是已存在的）
sudo mount /dev/sdb1 /data
```

* 这个挂载是临时的，重新开机就会丢失。 如果要开机自动启动挂载， 需要编辑`/etc/fstab`



查看硬盘和挂载分区等信息

```
df  -h
```

这样就成功添加了一块硬盘并挂载到`/data`目录下了，



## 设置开机自动挂载

1. 查询UUID

```shell 
ls -al /dev/disk/by-uuid

#输出为：
...
... 88e7c2eb-82e6-48c2-a3d8-829c32468f1f -> ../../nvme0n1p11
...
```

可以查到对应分区`nvme0n1p11`的uuid为`88e7c2eb-82e6-48c2-a3d8-829c32468f1f`



2. 编辑`/etc/fstab`(用来存放文件系统的静态信息的文件)

```
sudo vim /etc/fstab
```

末尾加上UUID=刚刚复制的UUID /data ext defaults 0 0

```
UUID=刚刚复制的UUID /data ext4 defaults 0 0
```





# Terminal

## commands

检查当前可用的shell:

```shell
cat /etc/shells
```

or:

```shell
chsh -l
```




查看当前使用的shell:

```shell
echo $SHELL
```



set one shell  as default for your user:

```shell
chsh -s full-path-to-shell
```

## zsh

安装zsh shell

```shell
sudo apt install zsh
```



切换shell

```
chsh -s /bin/zsh
```



## ohmyzsh

1. clone mirror:

   github安装oh-my-zsh（很慢）

   ```shell
   sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
   ```

   

   gitee安装oh-my-zsh: (国内用这个 )

   ```shell
   wget https://gitee.com/mirrors/oh-my-zsh/raw/master/tools/install.sh
   ```

   

2. 执行`install.sh`

3. 如果发现install很慢，可以修改为gitee：
   `vim install.sh`
   找到以下部分：

   ```shell
   # Default settings
   ZSH=${ZSH:-~/.oh-my-zsh}
   REPO=${REPO:-ohmyzsh/ohmyzsh}
   REMOTE=${REMOTE:-https://github.com/${REPO}.git}
   BRANCH=${BRANCH:-master}
   ```



   将中间两行改为：

   ```shell
   REPO=${REPO:-mirrors/oh-my-zsh}
   REMOTE=${REMOTE:-https://gitee.com/${REPO}.git}
   ```

   

   



## plugins

* 如果使用brew, yay等包管理工具安装插件, 会把插件安装在`$ZSH/plugins`,这些插件被称为""standard plugins", 不需要

* 如果使用git clone安装插件, 则这些插件被称为"custom plugins", 需要被clone到`$ZSH_CUSTOM/plugins` (默认位置是 `~/.oh-my-zsh/custom/plugins`)

* 所有插件在安装完毕后,都需要在`~/.zshrc`的`plugins`中配置:

  ```undefined
  plugins=( [custom plugins...] zsh-syntax-highlighting autosuggestion)
  ```

* 修改完配置文件后记得`source ~/.zshrc`, 然后重新启动shell

### autosuggestion && highlighting

* 安装` autosuggestion`：( github非常慢，改用gitee ) (这里直接用环境变量+重定向，不需要在指定目录下clone了)

  ```shell
  git clone https://gitee.com/phpxxo/zsh-autosuggestions.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
  ```




* 安装`syntax-highlighting`：

  ```shell
  git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syn tax-highlighting
  ```

  

### fasd & autojump

* 安装`fasd`: 它将文件和目录**按最近最常用**算法排序, 并提供各种操作

  ```shell
  yay -S fasd
  ```

  安装后需要配置`~/.zshrc`:

  ```shell
  alias a='fasd -a'        # any
  alias s='fasd -si'       # show / search / select
  alias d='fasd -d'        # directory
  alias f='fasd -f'        # file
  alias sd='fasd -sid'     # interactive directory selection
  alias sf='fasd -sif'     # interactive file selection
  alias z='fasd_cd -d'     # cd, same functionality as j in autojump
  alias zz='fasd_cd -d -i' # cd with interactive selection
  ```

  alias使用:

  ```
  a foo 列出最近操作的路径匹配 'foo' 的文件与目录
  f foo 列出最近操作的路径匹配 'foo' 的文件
  d foo 列出最近操作的路径匹配 'foo' 的目录
  s foo 列出最近操作的路径匹配 'foo' 的文件与目录，并可以通过序号选择
  sf foo 列出最近操作的路径匹配'foo'的文件，并可以通过序号选择
  sd foo 列出最近操作的路径匹配'foo'的目录，并可以通过序号选择
  z foo cd到最近操作的匹配'foo'并且得分最高的目录
  zz foo 列出最近操作的路径匹配'foo'的目录，通过序号选择，然后cd进目录
  ```

  e.g. If you often go to  `~/files/cool_project` you can simply use `z cool` to jump there. 



* `autojump`提供了`j`命令, 效果和`fasd`的`z`命令一样, 可以作为`fasd`的替代品:

  ```shell
  yay -S autojump
  ```









## theme

目前用[powlevel10k](https://github.com/romkatv/powerlevel10k/blob/master/README.md)， 主页上给了中国大陆的下载方式, oh-my-zsh下：

1. Clone the repository:

   ```shell
   git clone --depth=1 https://gitee.com/romkatv/powerlevel10k.git ${ZSHz
   ```

   

2. Set `ZSH_THEME="powerlevel10k/powerlevel10k"` in `~/.zshrc`

3. source一下配置文件

4. 开启主题配置：`p10k configure`

5. 后续可以继续用`p10k configure`重新开始配置， 或者手动更改配置文件：`~/.p10k.zsh`

   * 注意, 我使用了符号链接. `~/.p10k.zsh`实际是指向`/Users/lyk/Projects/MyOfficialProjects/dotfiles/.p10k.zsh`的符号链接. 因此每次`p10k configure`后, 都不能正确地在`~/.p10k.zsh`生成配置文件,需要手动修改



* Linux上默认配置不开启username@hostname 的显示，参加官方文档的“How do I add username and/or hostname to prompt?”. 也可以将这行注释掉：

  ```shell
  # Don't show context unless running with privileges or in SSH.
  typeset -g POWERLEVEL9K_CONTEXT_{DEFAULT,SUDO}_{CONTENT,VISUAL_IDENTIFIER}_EXPANSION=
  ```



## color

这个[网站](https://draculatheme.com/)收集了很多终端模拟器的Dracula主题配色方案

以Mac常用的iTerms2为例，只需：



安装：

```url
git clone https://github.com/dracula/iterm.git
```



启用该配色：

1. *iTerm2 > Preferences > Profiles > Colors Tab*
2. Open the *Color Presets...* drop-down in the bottom right corner
3. Select *Import...* from the list
4. Select the `Dracula.itermcolors` file
5. Select the *Dracula* from *Color Presets...*

# Unix CLI Tools

一些常用的命令行工具，和它们的现代替代

ref: [MIT  lesson](https://missing.csail.mit.edu/2020/shell-tools/), [Unix命令的现代替代](https://github.com/ibraheemdev/modern-unix)

## Easy Installation

对于传统UnixCLi工具,都已经被加入到Unix标准工具集中,不需要手动下载了. 而很多新工具需要手动下载. 以下列出的所有新工具均可以用包管理器( `yay` for Arch, `brew` for OSX )下载. 为了方便, 我还提供了[依赖列表](https://github.com/LYK-love/PackageLists)来批量下载.

### 依赖列表说明

文件名格式为`[XX_Packages]_[Platform[_Advanced]]].txt`:

* `[xx_packages]`: 就是包的类型, 比如R`esource_Monitoring_Packages`等等
* `[Platform]`:包兼容的平台
  * `Linux`: 故名思义,就是Linux下可以安装的包
  * `Mac`: Mac OSX下可以安装的包. 总体来说和linux下没有大的区别
  * `General`:Linux和Mac同时兼容的包

* `[XX]_[Platform[_Advanced]`: 如果一个列表出现了有和无`Advanced`的两个版本, 说明该列表的类型内有些包用处不大, 不需要安装, 也就没有包括在无`Advanced`的列表里面. 而`Advanced`列表中包含了全部包. 
  * 比如同为终端文件浏览器的`ranger`和`broot`,一般情况下使用前者就够了, 因此 `File&Oir_Operations_Packages_General.txt`只包含了`ranger`, 而`File&Oir_Operations_Packages_Anvanced.txt`包含了后者

### 依赖列表使用

Mac:

```
brew install $(cat [packages].txt)
```

for other platform just replace brew with your correspondding package manager

##  文件/目录操作

`File&Dir_Operations_Packages_General.txt`: 没安装broot

```
exa	ranger	bat	diff-so-fancy	fd	ripgrep
```



`File&Dir_Operations_Packages_Advanced.txt`: 把broot加上了

```
exa	ranger	bat	diff-so-fancy	fd	ripgrep broot
```





### 列出目录: exa

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



### 终端文件浏览器: ranger / broot

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

  





### bat & fx & hexyl

* [bat](https://github.com/sharkdp/bat) : `cat`命令的替代品，输出文本文件的内容，并且带有`cat`所没有的代码高亮和行号

  ```
  yay -S bat
  ```

  usage:

  ```shell
  bat README.md
  ```

*  [fx](https://github.com/antonmedv/fx) 或者 [jq](https://github.com/stedolan/jq): 浏览JSON 文件

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

#### With git

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

#### With diff

Use `-u` with `diff` for unified output, and pipe the output to `diff-so-fancy`:

```shell
diff -u file_a file_b | diff-so-fancy
```



### find/fd

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
*  `Ctrl+R` + type a substring you want to match for commands in your history来检索历史命令. This can also be enabled with the UP/DOWN arrows in [zsh](https://github.com/zsh-users/zsh-history-substring-search)

### fzf && mcfly

*  `fzf` : GO 语言编写的交互式的 Unix 命令行工具。可以用来查找任何 **列表**内容，文件、Git 分支、进程等。所有的命令行工具可以生成列表输出的都可以再通过管道 pipe 到 fzf 上进行搜索和查找.

  ```shell
  yay -S fzf
  ```

  这个命令比较复杂, 见[教程](https://zhuanlan.zhihu.com/p/41859976#:~:text=Fuzzy%20finder%20%28fzf%2Bvim%29%20%E4%BD%BF%E7%94%A8%E5%85%A8%E6%8C%87%E5%8D%97%201%20%E5%AE%89%E8%A3%85%20%E4%BB%A5%20macOS,fzf%20%E9%BB%98%E8%AE%A4%E9%85%8D%E7%BD%AE%E5%8F%82%E6%95%B0%208%20%E6%A0%B8%E5%BF%83%E5%91%BD%E4%BB%A4%20FZF_DEFAULT_COMMAND%20...%20More%20items)

* [McFly](https://github.com/cantino/mcfly) 是`ctrl-r`的替代品，安装以后，只要按下`ctrl-r`，就会出现一个更好用的搜索界面

  ```
  yay -S mcfly
  ```

  

##  文本处理

`Text_Operations_Packages_General.txt`

```
choose	jq	
```



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

### jq

* `jq`: `sed` for JSON data.

## Resource Monitoring

`Resource_Monitoring_Packages_General.txt`:

```
htop	bottom	iotop	procs	duf	ncdu	free	lsof
```

可以酌情添加`glances`和`dstat`





### General Monitor: htop && bottom && iotop

* `top`: 传统的资源监控工具

* [`htop`](https://htop.dev/):  `htop` has a myriad of options and keybinds, some useful ones are: `<F6>` to sort processes, `t` to show tree hierarchy and `h` to toggle threads. 
* [`glances`](https://nicolargo.github.io/glances/): alternative for htop. with a great UI.
* For , [`dstat`](http://dag.wiee.rs/home-made/dstat/) : alternative for htop. with aggregate measures across all processes. It can computes real-time resource metrics for lots of different subsystems like I/O, networking, CPU utilization, context switches, &c.



* [`bottom`](https://github.com/ClementTsang/bottom): Yet another cross-platform graphical process/system monitor. You can run bottom using `btm`.
  - For help on flags, use `btm -h` for a quick overview or `btm --help` for more details.
  - For info on key and mouse bindings, press `?` inside bottom or refer to the [documentation](https://clementtsang.github.io/bottom/nightly/).

*  [`iotop`](https://www.man7.org/linux/man-pages/man8/iotop.8.html) displays live **I/O usage information** and is handy to check if a process is doing heavy I/O disk operations

### Process Info:procs

* `ps`： 显示进程信息
* `procs`:  `ps`的现代替代

### Disk Usage: duf, ncdu

* `df` : 显示磁盘占用情况

* [`du`](http://man7.org/linux/man-pages/man1/du.1.html) 显示当前目录下每个文件占用的磁盘空间
  *  `-h` ： print with **h**uman readable format.



* `duf`： `df`的现代替代
* `ncdu`： `du`的现代替代

### Memory Usage: free

*  [`free`](https://www.man7.org/linux/man-pages/man1/free.1.html) displays the total amount of free and used memory in the system. Memory is also displayed in tools like `htop`.

### Open Files: lsof

*  [`lsof`](https://www.man7.org/linux/man-pages/man8/lsof.8.html) lists file information about files opened by processes. It can be quite useful for checking which process has opened a specific file.

## Networking

`networking_packages_Linux.txt`:

```
ss	iproute2	nethlogs	iftop	gping	dog
```



`Networking_Packages_Mac.txt`: 没有`ss`, `iproute2`改成了`iproute2mac`

```
iproute2mac	nethlogs	iftop	gping	dog
```



### Network Package Monitor: ss

* [`ss`](https://www.cnblogs.com/duanxz/p/4669798.html): short for "**socket statistics**".  `ss` lets you monitor incoming and outgoing network packets statistics as well as interface statistics. A common use case of `ss` is figuring out what process is using a given port in a machine. 

  * 当服务器的socket连接数量变得非常大时，无论是使用netstat命令还是直接cat /proc/net/tcp，执行速度都会很慢, 用ss才是节省时间。

  * [教程](https://www.igoroseledko.com/socket-statistics-ss-command/)
  * 该工具似乎没有mac版

### Network Config: ip

* `ip`: 用于操作路由,网络设备和网络接口. 是`netstat` and `ifconfig` 的现代替代, 后二者已经停止维护了，可能不会被包含在新的Linux发行版中. `ip`命令位于iproute2工具包中. 

  Linux:

  ```shell
  apt install iproute2
  ```

  [Mac版本](https://github.com/brona/iproute2mac):

  ```shell
  brew install iproute2mac
  ```


#### Usage

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





### Network Usage: nethogs, iftop

- [`nethogs`](https://github.com/raboof/nethogs) and [`iftop`](http://www.ex-parrot.com/pdw/iftop/) are good interactive CLI tools for monitoring network usage.

If you want to test these tools you can also artificially impose loads on the machine using the [`stress`](https://linux.die.net/man/1/stress) command.

### Network Connections: gping

* [`gping`](https://github.com/orf/gping): `ping`, but with a graph.

### NetworkRequests: httpie



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

### DNS: dog

* [dog](https://dns.lookup.dog/) : 是`dig`命令的替代品，用来发出 DNS 查询。它的用法比`dig`简单多了。

  ```shell
  # 默认查询 A 记录
  dog example.net
  
  # 查询多个记录
  dog example.net A NS MX
  ```

  





## Benchmarking

`Benchmarking_Packages_General.txt`:

```
hyperfine
```



### hyperfine

* [`hyperfine`](https://github.com/sharkdp/hyperfine): A command-line benchmarking tool.

## Calculating: sc

`Calculating_Packages_General.txt`

```
scal
```



* `sc`: short for: `scal`

# Editor

对于服务器而言, 大多数OS预装的vim都够用了. 自用的话还得是nvim

## nvim

* Neovim设置全局配置文件,需要在`/etc/profile`添加：

  ```shell
  export VIM=/usr/share/nvim
  export PATH="$PATH:$VIM/sysinit.vim"
  ```

* 有可能会出现这种情况：

  > 直接使用 nvim ... 打开文件时一切正常，配置也生效;
  > 但当你使用 sudo nvim ... 打开文件时，配置文件并没有生效

  出现这种情况的原因是：当你使用 sudo命令的时候，用户的身份切换了（默认是root）,此时你的环境变量也被重置了，系统当然就找不到你的配置文件。

  解决的方案大致有2种：

  1. 使用 sudo -E nvim ... 打开文件 （最快速的方法，不过每次都需要加上 -E, 有点麻烦）
  2. 修改 sudo 的配置文件: /etc/sudoers(如果用nvim打开是空文件的话，可以试一下用vim 或者 visudo打开，后面就不细说了，超纲了)

# 包管理工具

## apt

更新软件源

```
apt-get update
apt-get upgrade
```



查看系统已安装的包：

```shell
apt list --installed 
```



## brew

安装：

```shell
/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"
```



## pacman

同步存储库数据库，并且更新系统的所有软件包，但不包括不在软件库中的“本地安装的”包：

```
pacman -Syu
```

- `S` 代表同步
- `y` 代表更新本地存储库
- `u` 代表系统更新

## conda

 推荐`miniconda`， 直接去NJU MIRROR下载：

```shell
wget https://mirror.nju.edu.cn/anaconda/miniconda/Miniconda3-py39_4.9.2-Linux-x86_64.sh
```

* 清华源

然后安装：

```shell
bash /path/to/miniconda
```



重启终端，检查安装是否成功：

```shell
conda -V
```

### 换源

conda换源建议用nju源  （清华源早就不行了，建议别用）， [具体指导](https://mirrors.nju.edu.cn/help/anaconda)

1. 先执行 `conda config --set show_channel_urls yes` 生成用户目录下的 `.condarc` 文件

2. 编辑该文件：

   ```yaml
   channels:
     - defaults
   show_channel_urls: true
   default_channels:
     - https://mirror.nju.edu.cn/anaconda/pkgs/main
     - https://mirror.nju.edu.cn/anaconda/pkgs/r
     - https://mirror.nju.edu.cn/anaconda/pkgs/msys2
   custom_channels:
     conda-forge: https://mirror.nju.edu.cn/anaconda/cloud
     msys2: https://mirror.nju.edu.cn/anaconda/cloud
     bioconda: https://mirror.nju.edu.cn/anaconda/cloud
     menpo: https://mirror.nju.edu.cn/anaconda/cloud
     pytorch: https://mirror.nju.edu.cn/anaconda/cloud
     simpleitk: https://mirror.nju.edu.cn/anaconda/cloud
   ```

   即可添加 Anaconda Python 免费仓库。

3. 运行 `conda clean -i` 清除索引缓存，保证用的是镜像站提供的索引。

4. 运行 `conda create -n myenv numpy` 测试一下吧

## pip3

pip是python的一个包管理工具，python2:使用`pip`, python3使用`pip3`

* ( Python3下使用`pip` 默认用的是`pip3` )

### 安装

```shell
yay -S pip3
```



mac用户：`brew intall pip3`相当卡， 因此要用：

```
curl bootstrap.pypa.io/get-pip.py | python3
```



检查安装是否成功：

```shell
pip3 --version
```



### 换源

在 pip 命令中使用 **-i** 参数来指定镜像地址

```
pip3 install numpy -i https://mirrors.aliyun.com/pypi/simple/
```



如果需要配置全局的镜像地址，需要修改配置文件:

Linux/Mac os 环境中，配置文件在 ~/.pip/pip.conf（如不存在创建该目录和文件）：

```text
mkdir ~/.pip
```

打开配置文件 **~/.pip/pip.conf**，修改如下：

```text
[global]
index-url = https://mirrors.aliyun.com/pypi/simple/
[install]
trusted-host = https://mirrors.aliyun.com
```



查看镜像地址：

```python
pip3 config list  
```

### npm

#### 换源

国内优秀npm镜像：

淘宝npm镜像

- 搜索地址：[http://npm.taobao.org/](https://link.jianshu.com?t=http://npm.taobao.org/)
- registry地址：[http://registry.npm.taobao.org/](https://link.jianshu.com?t=http://registry.npm.taobao.org/)

cnpmjs镜像

- 搜索地址：[http://cnpmjs.org/](https://link.jianshu.com?t=http://cnpmjs.org/)
- registry地址：[http://r.cnpmjs.org/](https://link.jianshu.com?t=http://r.cnpmjs.org/)



 1.临时使用

```python
npm install express --registry https://registry.npm.taobao.org
```



2.持久使用

```python
npm config set registry https://registry.npm.taobao.org
```

配置后可通过下面方式来验证是否成功:

```shell
npm config get registry
```



# 开发环境配置

## JDK

### 安装jdk

mac:

mac建议到[oracle官网](https://www.oracle.com/java/technologies/downloads/#java11-mac)下载jdk



linux一般用命令行安装，因此推荐openjdk



Ubuntu:

查找合适的openjdk版本:

```shell
# ubuntu
apt-cache search openjdk
```

安装

```shell
sudo apt-get install openjdk-8-jdk
```

* 如果search和install都没反应，应该先更新软件源

Manjaro:

查找合适的openjdk版本:

```shell
yay search jdk
```



```shell
yay install openjdk-8-jdk
```





(3) 配置环境变量, 编辑如下文件:

```
vim ~/.bashrc
```

在最后一行加:

```
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
```

## 查找JDK

查看jdk版本：

```shell
java -version
```



查找jdk:

```shell
whereis java
```

输出为

```
java: /usr/bin/java /usr/share/java /usr/share/man/man1/java.1.gz
```



查看jdk真实位置（上面的都是软链接）：

```shell
ls -l /usr/bin/java
```

输出为：

```
lrwxrwxrwx 1 root root 22 Mar 30 16:07 /usr/bin/java -> /etc/alternatives/java
```



```
ls -l /etc/alternatives/java
```

输出为：

```shell
lrwxrwxrwx 1 root root 46 Mar 30 16:07 /etc/alternatives/java -> /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java
# 以上就是jdk位置
```



### 配置jdk环境变量

#### linux

对于linux:  编辑`/etc/profile`, 或 `~/.bashrc`, ` .zshrc`等：

```
vim /etc/profile # 这里可以选择任意的shell配置文件，
```

```shell
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64 # 这里填jdk位置
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=$PATH:${JAVA_HOME}/bin
```



使配置文件生效：

```
source /etc/profile
```



#### mac

mac的jdk安装位置和linux不同



查询当前的java的安装版本

```shell
cd /Library/Java/JavaVirtualMachines
ls
```



配置`.zshrc`

```bash
# jdk 版本切换， on mac
# jdk-17.0.2.jdk   jdk1.8.0_321.jdk jdk-11.0.14.jdk 
export JAVA_8_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_321.jdk/Contents/Home
export JAVA_11_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.14.jdk/Contents/Home
export JAVA_17_HOME=/Library/Java/JavaVirtualMachines/jdk-17.0.2.jdk/Contents/Home



alias jdk8='export JAVA_HOME=$JAVA_8_HOME'
alias jdk11='export JAVA_HOME=$JAVA_11_HOME'
alias jdk17='export JAVA_HOME=$JAVA_17_HOME'
```

```shell
source ~/.bash_profi
```



切换jdk版本

```shell
jdk11
java -version
```





# 用户软件安装

这部分不仅是给主机，也是给容器的，尤其是容器，可能连ping这样的基本命令都没有，需要手动安装



如果OS是Ubuntu（ 云服务器或容器 ）， 需要先：

```shell
apt-get update
```

## Docker

参见《Docker Intro》

1. install:

   ```shell
   sudo apt install docker.io
   ```

   

2. 最好使用非root用户来使用Docker,此时需要添加非root用户到本地Docker Unix组：

   ````
   sudo usermod -aG docker [user_name]
   ````

   * 如果当前登陆用户就是要添加进组的用户的话，需要重新登陆才能生效

3. 换源阿里云,需要去阿里云“容器镜像服务” --> “镜像加速器” 生成镜像url：

   ```shell
   sudo mkdir -p /etc/docker
   sudo tee /etc/docker/daemon.json <<-'EOF'
   {
     "registry-mirrors": ["https://zz1b9pta.mirror.aliyuncs.com"]
   }
   EOF
   sudo systemctl daemon-reload
   sudo systemctl restart docker
   ```

   *mac用户可在setting -- docker engine中修改`daemon.json`文件

4. 终端输入docker info查看是否配置成功

   ```
   > docker info
   ...
   Registry Mirrors:
   https://zz1b9pta.mirror.aliyuncs.com/
   ```

5. 将docker设置为开机自启：

   ```shell
   systemctl enable docker
   ```

   

## kubernetes

### 安装

ubuntu20.04下安装k8s

注意，k8s的安装和集群初始化都需要root用户

1. 安装docker

2. 安装依赖

   ```
   sudo apt-get update
   sudo apt-get -y install apt-transport-https ca-certificates curl software-properties-common
   ```

   * 直接在`/etc/apt/sources.list`里添加`https://mirrors.aliyun.com/kubernetes/apt/`是不行的，因为这个阿里镜像站使用的`ssl`进行传输的，所以要先安装`apt-transport-https`并下载镜像站的密钥才可以进行下载

3. 安装GPG证书:

   ```
   curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add - 
   ```

4. 写入软件源信息:

   ```javascript
   cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
   deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main
   EOF
   ```

5. 然后更新源列表：

   ```
   apt-get update
   ```

6. 查看可安装版本：

   ```shell
   apt-cache madison kubelet
   ```

7. 安装指定版本:

   ```
   apt-get install -y kubelet=1.18.4-00 kubeadm=1.18.4-00 kubectl=1.18.4-00
   ```

   * 如果想要安装最新版本，就直接：

     ```
     apt-get install -y kubelet kubeadm kubectl
     ```

     但是很不推荐，因为最新的k8s 1.24.* 的集群初始化有bug，不如用老版本

8. 设置开机启动:

   ```shell
   sudo systemctl enable kubelet && sudo systemctl start kubelet
   ```

9. 查看所需镜像,以刚才安装的1.18.4版本为例:

   ```
   kubeadm config images list --kubernetes-version=v1.18.4
   
   k8s.gcr.io/kube-apiserver:v1.18.4
   k8s.gcr.io/kube-controller-manager:v1.18.4
   k8s.gcr.io/kube-scheduler:v1.18.4
   k8s.gcr.io/kube-proxy:v1.18.4
   k8s.gcr.io/pause:3.2
   k8s.gcr.io/etcd:3.4.3-0
   k8s.gcr.io/coredns:1.6.7
   ```

10. 上面的镜像是Google的，国内无法访问，需要用阿里云的镜像来替换:

    ```shell
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-apiserver:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-controller-manager:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-scheduler:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-proxy:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.2
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/etcd:3.4.3-0
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/coredns:1.6.7
    ```

11. 为镜像重新打tag：

    ```
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-apiserver:v1.18.4 k8s.gcr.io/kube-apiserver:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-controller-manager:v1.18.4 k8s.gcr.io/kube-controller-manager:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-scheduler:v1.18.4 k8s.gcr.io/kube-scheduler:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-proxy:v1.18.4 k8s.gcr.io/kube-proxy:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.2 k8s.gcr.io/pause:3.2
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/etcd:3.4.3-0 k8s.gcr.io/etcd:3.4.3-0
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/coredns:1.6.7 k8s.gcr.io/coredns:1.6.7
    ```







5. 执行下面命令，测试安装是否正常

   ```
   kubeadm init
   ```

   * k8s集群在初始化时建议使用root用户，如果以普通用户执行`kubeadm init`， 会得到报错:

     ```
     [ERROR IsPrivilegedUser]: user is not running as root [preflight] If you know what you are doing, you can make a check non-fatal with `--ignore-preflight-errors=...`
     ```

6. 查看k8s版本:

   ```
   kubeadm version
   ```

   ````
   kubeadm version: &version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.1", GitCommit:"3ddd0f45aa91e2f30c70734b175631bec5b5825a", GitTreeState:"clean", BuildDate:"2022-05-24T12:24:38Z", GoVersion:"go1.18.2", Compiler:"gc", Platform:"linux/amd64"}
   ````

   * ``GitVersion:"v1.24.1""` 即为版本号



### 配置管理节点



#### 配置主机

增加主机名:

单独为每个服务器增加主机名，格式为hostnamectl set-hostname hostname。一般主节点取名master，从节点取名node.

```text
hostnamectl set-hostname [k8s-master]
```





在主节点配置所有k8s服务器的host，并且host名字跟各服务器的主机名对应。这里配置的是公网IP

```
cat >> /etc/hosts << EOF 
<主节点公网IP> k8s-master
<工作节点公网IP> k8s-node1
EOF
```

```
echo "使host配置生效" > /dev/null
/etc/init.d/network restart
```

#### 修改cgroup

Kubernetes cgroup driver was set to systems but docker was set to systemd. So I created `/etc/docker/daemon.json` and added below:

```yaml
{
    "exec-opts": ["native.cgroupdriver=systemd"]
}
```

Then

```yaml
 sudo systemctl daemon-reload
 sudo systemctl restart docker
 sudo systemctl restart kubelet
```



Then：

```
docker info | grep Cgroup
```

如果输出为：

```
Cgroup Driver: systemed
Cgroup Version: 1
```

即成功









#### 初始化master节点

如果初始化过程中出现错误，要使用`kubeadm reset -f`清除之前的配置



```
kubeadm init \
--apiserver-advertise-address=121.36.247.134 \
--kubernetes-version=v1.18.4 \
--pod-network-cidr=10.244.0.0/16 \
--service-cidr=10.96.0.0/12 \
--ignore-preflight-errors=Swap
```

```
kubeadm init \
--apiserver-advertise-address=121.36.247.134 \
--image-repository registry.aliyuncs.com/google_containers \
--pod-network-cidr=10.244.0.0/16
```

这里介绍一下一些常用参数的含义：

- `--apiserver-advertise-address`: k8s 的`apiserver`的部署地址，填自己的管理节点 ip( 如果公网通信，那就是公网ip )
- `--image-repository`: 拉取的 docker 镜像源，因为初始化的时候`kubeadm`会去拉 k8s 的很多组件来进行部署，所以需要指定国内镜像源，下不然会拉取不到镜像。
- `--pod-network-cidr`: 这个是 k8s 采用的节点网络，因为我们将要使用`flannel`作为 k8s 的网络，所以这里填`10.244.0.0/16`就好
- `--kubernetes-version`: 这个是用来指定你要部署的 k8s 版本的，一般不用填，不过如果初始化过程中出现了因为版本不对导致的安装错误的话，可以用这个参数手动指定。
- `--ignore-preflight-errors`: 忽略初始化时遇到的错误，比如说我想忽略 cpu 数量不够 2 核引起的错误，就可以用`--ignore-preflight-errors=CpuNum`。错误名称在初始化错误时会给出来。





#### 配置 kubectl 工具

```
mkdir -p /root/.kube && \
cp /etc/kubernetes/admin.conf /root/.kube/config
```



执行完成后并不会刷新出什么信息，可以通过下面两条命令测试 `kubectl`是否可用：

```csharp
# 查看已加入的节点
kubectl get nodes
# 查看集群状态
kubectl get cs
```



#### 部署 flannel 网络

`flannel`是一个专门为 k8s 设置的网络规划服务，可以让集群中的不同节点主机创建的 docker 容器都具有全集群唯一的虚拟IP地址

```ruby
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```



#### 检查节点是否部署完成

```
kubectl get nodes
```





### 卸载

```shell
sudo apt remove -y kubelet kubeadm kubectl
rm -rf ~/.kube/
rm -rf /etc/kubernetes/
rm -rf /etc/systemd/system/kubelet.service.d
rm -rf /etc/systemd/system/kubelet.service
rm -rf /usr/bin/kube*
rm -rf /etc/cni
rm -rf /opt/cni
rm -rf /var/lib/etcd
rm -rf /var/etcd
```





## mycli

好用的命令行mysql界面,[项目地址](https://github.com/dbcli/mycli)



```shell
# 通用
pip install -U mycli
```

or

```shell
# on Arch
yay -S mycli
```

or

```shell
# Only on macOS
brew update && brew install mycli  
```

or

```shell
# Only on debian or ubuntu
sudo apt-get install mycli 
```

## 网络工具

ping:

```shell
apt-get install iputils-ping
```



traceroute:

```shell
apt-get install traceroute
```



iproute2:

```
apt install iproute2
```

Mac:

```
brew install iproute2mac
```



# Dababase

## mysql

manjaro:

```shell
yay -S mysql
```



mac:

```
brew install mysql
```





ubuntu:

这里只针对ubuntu 20.04， Ubuntu 源仓库中最新的 MySQL 版本号是 MySQL 8.0

```shell
sudo apt update
sudo apt install mysql-server
```



安装完成后，MySQL 服务将会自动启动。想要验证 MySQL 服务器正在运行，输入：

```shell
sudo systemctl status mysql
```

输出应该显示服务已经被启用，并且正在运行：

```
● mysql.service - MySQL Community Server
     Loaded: loaded (/lib/systemd/system/mysql.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2020-04-28 20:59:52 UTC; 10min ago
   Main PID: 8617 (mysqld)
     Status: "Server is operational"
     ...
```

### mysql允许远程访问

mysql默认绑定本地环回地址（127.0.0.1），无法公网通信(即使你的用户是允许远程登录的用户(如`%`)):

```
tcp 0 0 127.0.0.1:3306 0.0.0.0:* LISTEN 3783/mysqld
```

需要修改mysql的配置文件`/etc/mysql/my.conf`，在bind-address后面增加远程访问IP地址， 或者禁掉该字段

* mysql配置文件，在ubuntu20.04的Ver 8.0.29-0ubuntu0.20.04.3上，位于`/etc/mysql/mysql.conf.d/mysqld.cnf`

```
bind-address=127.0.0.1  139.196.197.138
```

* 可以直接把改字段注释掉
* 也可以添加可访问mysql服务器的ip，用空格隔开



重启mysql服务

```
service mysql restart
```



## mongodb

由于 MongoDB 修改了软件授权协议，  官方仓库已经删除了此软件包。请注意从代码编译 mongodb 需要 ~160GB 磁盘空间，需要花费几个小时时间。因此我们最好安装`-bin`版本

```
yay -S mongodb
```



注意： 只有先启动`mongod`， 才能正确启动`mongo`

### 报错

可能有报错：

```
> mongo
connecting to: mongodb://127.0.0.1:27017
2018-09-27T21:11:14.779+0800 W NETWORK  [main] Failed to connect to 127.0.0.1:27017, reason: Connection refused
2018-09-27T21:11:14.780+0800 E QUERY    [main] Error: couldn't connect to server 127.0.0.1:27017, connection attempt failed :
connect@src/mongo/shell/mongo.js:234:13
@(connect):1:6
exception: connect failed
```

出现以上原因，可能是data目录下的mongod.lock文件的问题。可以使用命令修复：

```csharp
[root@localhost mongodb]# ./bin/mongod --repair
```

 然后重新打开一个窗口，启动mongodb

### 配置

配置文件路径： `\etc\mongodb.conf`. 

* 其中`dbpath`为数据库的路径

### 启动服务

启动

```ruby
$ systemctl start mongodb.service
```

查看状态:

```lua
sudo systemctl status mongodb
```

重启:

```text
sudo systemctl restart mongodb
```

停止:

```text
sudo systemctl stop mongodb
```

重载服务:

```text
sudo systemctl daemon-reload
```

开机启动:

```
sudo systemctl enable mongodb
```



# DEV

## maven

maven配置文件位置： `～/.m2/settings.xml`

加入阿里云仓库：

```xml
        <!-- 阿里云仓库 -->
        <mirror>
            <id>alimaven</id>
            <mirrorOf>central</mirrorOf>
            <name>aliyun maven</name>
            <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
        </mirror>
```



### 设置开机自启

```sql
system enable mongodb
```

# 基本命令

## 查看命令

```
yay -S tldr
```



或者用man/info，后者的信息存放在`/usr/info`

## clear

清屏：

```
clear
```



## 切换tty

1. CTRL + ALT + Fn

2. ```shell
   sudo chvt N # N: tty number, 1 represents the main tty
   ```





## 下载

```shell
# Download the contents of a URL to a file (named "foo" in this case):
wget https://example.com/foo

# Download the contents of a URL to a file (named "bar" in this case):
wget -O bar https://example.com/foo
```

## 主机操作

查看主机名：

```shell
hostname 
```



更改主机名：

```shell
vim /etc/hostname # 编辑该文件
```



添加域名映射：

```
vim /etc/hosts
```



## 时间

查看时间：

```shell
date
```

## 查看发行版

```shell
lsb_release -a
```

## 用户操作

### 创建新用户

```shell
sudo adduser [username]
```



### 切换用户

```shell
sudo su [username]
```

### 修改用户密码

```shell
sudo passwd user
```

### 删除用户

`sudo userdel username`: 仅仅删除用户，不删除用户的home目录文件

* `-r`: 删除用户的home目录文件

当需要删除用户时可以使用以下指令

### 查看用户组

```shell
cat /etc/group
```



