---
title: Unix CLI Tools
categories:
- Software Engineering
tags:
- Linux
- Shell
date: 2022-09-13 14:57:44
---

Sources:

1. [MIT: Shell Tools and Scripting](https://missing.csail.mit.edu/2020/shell-tools/)
2. [Modern Unix](https://github.com/ibraheemdev/modern-unix)

<!--more-->

# Basic operations

## grep --> rg

[ripgrep](https://github.com/BurntSushi/ripgrep) 

```sh
cargo install ripgrep
```

## ls --> eza

[eza](https://github.com/eza-community/eza): A modern replacement for `ls`.

Install:

```sh
cargo install eza
```



Usage:

```shell
eza --long --git
```

* 参数`--git`表示输出文件的 Git 状态。
  - `N`：新文件
  - `M`：文件有变动
  - `I`：该文件被忽略



除了平铺显示，`exa`还支持目录的树状显示。

```shell
eza --tree --level=2
```

## cd --> zoxide

[zoxide](https://github.com/ajeetdsouza/zoxide?tab=readme-ov-file): is a **smarter cd command**, inspired by z and autojump.

1. Install it.

   ```sh
   cargo install zoxide --locked
   ```

2. Remove the completions cache of my zsh:

   ```sh
   rm ~/.zcompdump*; compinit
   ```

3. Then, add this line to `~/.zshrc` file:

   ```sh
   eval "$(zoxide init zsh)"
   ```

   This should be **skiped** since I have already added it.

4. Install [fzf](https://github.com/junegunn/fzf):

   ```sh
   sudo apt install fzf
   ```

## cat --> bat, fx, hexyl

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

  

# Resource monitoring

## Network monitoring

* [gping](https://github.com/orf/gping): `ping`, but with a graph.

  ```
  cargo install gping
  ```

### bandwidth

[bandwidth](https://github.com/imsnif/bandwhich): displaying current network utilization by process, connection and remote IP/hostname

```sh
cargo install bandwhich
```



Since `bandwhich` sniffs network packets, it requires elevated privileges. On Linux, there are two main ways to accomplish this:

1. (Not recommended) Permanently allow the `bandwhich` binary its required privileges.

2. Use `sudo` everytime

   ```sh
   sudo bandwhich
   ```

## Process monitoring

* `ps`： 显示进程信息

### procs

[procs](https://github.com/dalance/procs):  `ps`的现代替代

```sh
cargo install procs
```

## Disk monitoring

* `df` : 显示磁盘占用情况

* [`du`](http://man7.org/linux/man-pages/man1/du.1.html) 显示当前目录下每个文件占用的磁盘空间
  *  `-h` ： print with **h**uman readable format.



We have two modern alternatives: dust and dua. We can choose one of them.

### dust

[dust](https://github.com/bootandy/dust): `du` + Rust.

```sh
cargo install du-dust
```

### dua

[dua](https://github.com/Byron/dua-cli): Disk Usage Analyzer

```sh
cargo install dua-cli

# And if you don't need a terminal user interface (most compatible)
cargo install dua-cli --no-default-features

# Compiles on most platforms, with terminal user interface
cargo install dua-cli --no-default-features --features tui-crossplatform
```

Usage:

```
# count the space used in the current working directory
dua
# count the space used in all directories that are not hidden
dua *
# learn about additional functionality
dua aggregate --help
```

​    

# File navigator: ranger / broot

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




# Benchmarking

[hyperfine](https://github.com/sharkdp/hyperfine): A command-line benchmarking tool.

```sh
cargo install hyperfine
```



To run a benchmark, you can simply call `hyperfine <command>...`. The argument(s) can be any shell command. For example:

```sh
hyperfine 'sleep 0.3'    
```

If you want to compare the runtimes of different programs, you can pass multiple commands:

```sh
hyperfine 'hexdump file' 'xxd file'
```

 

# Development

* [Convco](https://convco.github.io/): A Conventional commit cli build with [Rust](https://www.rust-lang.org/).

## TLDR

[tealdeer](https://github.com/dbrgn/tealdeer)

A very fast implementation of [tldr](https://github.com/tldr-pages/tldr) in Rust: Simplified, example based and community-driven man pages.

```sh
cargo install tealdeer
```



## Tokei

[Tokei](https://github.com/XAMPPRocky/tokei?ref=itsfoss.com):

```
cargo install tokei
```



Basic usage

This is the basic way to use tokei. Which will report on the code in `./foo` and all subfolders

```
tokei ./foo
```

​    

Multiple folders:

To have tokei report on multiple folders in the same call simply add a comma, or a space followed by another path.

```
tokei ./foo ./bar ./baz
```

​    

```
$ tokei ./foo, ./bar, ./baz
```

​    

## Finding Shell History: atuin

* `history` : 在STDOUT上打印shell命令记录, 可以用 `history | grep find` 进行检索
* `Ctrl+R` + type a substring you want to match for commands in your history来检索历史命令. This can also be enabled with the UP/DOWN arrows in [zsh](https://github.com/zsh-users/zsh-history-substring-search)



[atuin](https://github.com/atuinsh/atuin): Atuin replaces your existing shell history with a SQLite database, and records additional context for your commands. 

1. Install: 

   ```sh
   cargo install atuin
   ```

2. Then, config it in your shell concig file:

   In ``~/.zshrc`:

   ```sh
   # Here I disabled the keybinding for the `up` arraw. See: https://docs.atuin.sh/configuration/key-binding/
   # Bind ctrl-r but not up arrow
   eval "$(atuin init zsh --disable-up-arrow)"
   ```

   In `~/.bashrc`:

   ```sh
   eval "$(atuin init bash --disable-up-arrow)"
   ```

   Then execute the code:

   ```sh
   source ~/.zshrc
   source ~/.bashrc
   ```

3. After that, start the sync server **Offline (no sync)**

   ```sh
   bash <(curl https://raw.githubusercontent.com/atuinsh/atuin/main/install.sh)
               
   atuin import auto
   ```



# Potpourri

[Neofetch](https://github.com/dylanaraps/neofetch)

It's better than screenfetch, which has bug on OSX.