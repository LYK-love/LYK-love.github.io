---
title: Tmux
tags:
  - Linux
  - Terminal
categories: Toolkit
date: 2022-09-13 14:58:13
---


Outline:

* Intro
* Config
* Hierarchy
* Commands
* Session Handling

<!--more-->

# Intro

`tmux `是最常用的Terminal Multiplexer

`tmux` expects you to know its keybindings, and they all have the form `<C-b> x` where`tmux` has the following hierarchy of objects:

* All commands in tmux are triggered by a **prefix key** followed by a **command key** (quite similar to emacs).By default, tmux uses `C-b` as prefix key
  *  which means 
     1. press `Ctrl+b`
     2. release `Ctrl+b`
     3. press `command key`
* 默认的`session_name`和`window_name`都是0开头的

# Config

* 配置文件位于: `~/. tmux.conf` , 没有则自己创建

  * 我使用了符号链接+dotfile:

    ```
    
    ```

  * 参考[这个人的配置](https://github.com/pseudoyu/dotfiles/tree/master/tmux)

  * 参考

  * 也就是说,

# Hierarchy

## Sessions

 a session is an independent workspace with one or more windows

- `tmux` starts a new session.
- `tmux new -s NAME` starts it with that name.
- `tmux ls` lists the current sessions
- Within `tmux` typing `<C-b> d` detaches the current session
- `tmux a` attaches the last session. You can use `-t` flag to specify which

## Windows



Equivalent to tabs in editors or browsers, they are visually separate parts of the same session

- `<C-b> c` Creates a new window. To close it you can just terminate the shells doing `<C-d>`
- `<C-b>  [window_name]` Go to the specified window. Note they are numbered
- `<C-b> p` Goes to the previous window
- `<C-b> n` Goes to the next window
- `<C-b> ,` Rename the current window
- `<C-b> w` List current windows

## Panes

 

\- Like vim splits, panes let you have multiple shells in the same visual display.

- `<C-b> "` Split the current pane horizontally
- `<C-b> %` Split the current pane vertically
- `<C-b> <direction>` Move to the pane in the specified *direction*. Direction here means arrow keys.
- `<C-b> z` Toggle zoom for the current pane
- `<C-b> [` Start scrollback. You can then press `<space>` to start a selection and `<enter>` to copy that selection.
- `<C-b> <space>` Cycle through pane arrangements.
- `<C-b> x`: close the pane

# Commands

Some  common  commands：

- `C-b z`: make a pane go full screen. Hit `C-b z` again to shrink it back to its previous size
- `C-b C-<arrow key>`: Resize pane in direction of <arrow key>[4](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/#fn:4)
- `C-b ,`: Rename the current window

For further reading, [here](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/) is a quick tutorial on `tmux` and [this](http://linuxcommand.org/lc3_adv_termmux.php) has a more detailed explanation that covers the original `screen` command. You might also want to familiarize yourself with [`screen`](https://www.man7.org/linux/man-pages/man1/screen.1.html), since it comes installed in most UNIX systems.

# Session Handling

* `<C-b> d` : detach current session

* `<C-b> D`: choose which of your sessions you want to detach.

* `tmux ls`: List existing sessions

* `tmux attach -t [session_name]`: attach to the session you specified

  * `-t` : 指定attach的session

* renaming session:

  * 新建一个session,指定其名字

    ```shell
    tmux new -s [session_name]
    ```

  * rename your existing session:

    ```shell
    tmux rename-session -t 0 database
    ```

# 
