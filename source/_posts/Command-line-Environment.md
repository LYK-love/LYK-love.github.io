---
title: Command-line Environment
tags: Toolkit
date: 2022-02-10 17:30:37
---




Outline:

* Intro: Shell Session
* Job control
* Tmux
* Aliase
* Dotfiles
* Remote Machines ( ssh端口转发详见其他文章 )

ref: [MIT lesson](https://missing.csail.mit.edu/2020/command-line/), [tmux tutorial](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/), [a good introduction of Session](https://www.cnblogs.com/sparkdev/p/12146305.html)

<!--more-->

# Intro of Shell Session



Shell session 是终端中当前的状态，在终端中只能有一个 session。当我们打开一个新的终端时，总会创建一个新的 shell session。

就进程间的关系来说，session 由一个或多个进程组组成。一般情况下，来自单个登录的所有进程都属于同一个 session。我们可以通过下图来理解进程、进程组和 session 之间的关系：

![Shell Session Archetecture](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Toolkit/Shel%20lSession%20Archetecture)

会话是由会话中的第一个进程创建的，**一般情况下是打开终端时创建的 shell 进程**。该进程也叫 session 的领头进程。Session 中领头进程的 PID 也就是 session 的 SID。我们可以通过下面的命令查看 SID：

```
ps -o pid,ppid,pgid,sid,tty,comm
```

```
    PID    PPID    PGID     SID TT       COMMAND
   5745    5729    5745    5745 pts/4    zsh
   5785       1    5784    5745 pts/4    zsh
   5787       1    5784    5745 pts/4    zsh
   5789       1    5788    5745 pts/4    zsh
   5794    5789    5788    5745 pts/4    gitstatusd
   5844    5745    5844    5745 pts/4    ps

```

Session 中的每个进程组被称为一个 **job**，有一个 job 会成为 session 的前台 job(foreground)，其它的 job 则是后台 job(background)。每个 session 连接一个控制终端(control terminal)，控制终端中的输入被发送给前台 job，从前台 job 产生的输出也被发送到控制终端上。同时由控制终端产生的信号，比如 ctrl + z 等都会传递给前台 job。

一般情况下 session 和终端是一对一的关系，当我们打开多个终端窗口时，实际上就创建了多个 session。

Session 的意义在于多个工作(job)在一个终端中运行，其中的一个为前台 job，它直接接收该终端的输入并把结果输出到该终端。其它的 job 则在后台运行。

## Session 的创建和销毁

session的创建：

* 通常，新的 session 由系统登录程序创建，session 中的领头进程是运行用户登录 shell 的进程。新创建的每个进程都会属于一个进程组，当创建一个进程时，它和父进程在同一个进程组、session 中。



将进程放入不同 session 的惟一方法是使用 `setsid` 函数使其成为新 session 的领头进程。这还会将 session 领头进程放入一个新的进程组



session的销毁：

* 当 session 中的所有进程都结束时 session 也就消亡了。实际使用中比如网络断开了，session 肯定是要消亡的。
* 让 session 的领头进程退出。一般情况下 session 的领头进程是 shell 进程，如果它处于前台，我们可以使用 exit 命令或者是 ctrl + d 让它退出。或者我们可以直接通过 kill 命令杀死 session 的领头进程。
  * 原理是：当系统检测到挂断(hangup)条件时，内核中的驱动会将 SIGHUP 信号发送到整个 session。通常情况下，这会杀死 session 中的所有进程



session 与终端的关系：

* 如果 session 关联的是**伪终端**，这个伪终端本身就是随着 session 的建立而创建的，session 结束，那么这个伪终端也会被销毁。

  * 打开终端，会话开始；关闭终端，会话结束，会话内部的进程也会随之终止，不管有没有运行完。

    一个典型的例子就是，[SSH 登录](https://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html)远程计算机，打开一个远程终端执行命令。这时，网络突然断线，再次登录的时候，是找不回上一次执行的命令的。因为上一次 SSH 会话已经终止了，里面的进程也随之消失了

    为了解决这个问题，会话与窗口可以"解绑"：窗口关闭时，会话并不终止，而是继续运行，等到以后需要的时候，再让会话"绑定"其他窗口（见“ Terminal  Multiplexer”）

* 如果 session 关联的是 **tty**1-6，tty 则不会被销毁。因为该终端设备是在系统初始化的时候创建的，并不是依赖该会话建立的，所以当 session 退出，tty 仍然存在。只是 init 系统在 session 结束后，会重启 getty 来监听这个 tty

## 控制终端(controlling terminal)

**控制终端是进程的一个属性。**通过 `fork` 系统调用创建的子进程会从父进程那里继承控制终端。这样，session 中的所有进程都从 session 领头进程那里继承控制终端。Session 的领头进程称为终端的控制进程(controlling process)。简单点说就是：**一个 session 只能与一个终端关联，这个终端被称为 session 的控制终端(controlling terminal)。**同时只能由 session 的领头进程来建立或者改变终端与 session 的联系。我们可以通过 ps 命令查看进程的控制终端：

![img](https://img2018.cnblogs.com/blog/952033/202001/952033-20200103182831279-993028624.png)

支持 job control 的 **shell** 必须能够控制在某一时刻由哪个 job 使用终端。否则，可能会有多个 job 试图同时从终端读取数据，这会导致进程在接收用户输入时的混乱。为了防止这种情况发生，shell 必须按照预定的协议与终端驱动程序协作。

shell 一次只允许一个 job(进程组)访问控制终端。来自控制终端的某些输入会导致信号被发送到与控制终端关联的 job(进程组)中的所有进程。该 job 被称为控制终端上的前台 job。由 shell 管理的其他 job 在不访问终端的情况下，被称为后台 job。

Shell 的职责是通知 job 何时停止何时启动，还要把 job 的信息通知给用户，并提供机制允许用户继续暂停的 job、在前台和后台之间切换 job。比如前台 job 可以无限制的自由使用控制终端，而后台 job 则不可以。当后台 job 中的进程试图从其控制终端读取数据时，通常会向进程组发送 SIGTTIN 信号。这通常会导致该组中的所有进程停止(变成 stopped 状态)。类似地，当后台 job 中的进程试图写入其控制终端时，默认行为是向进程组发送 SIGTTOU 信号，但是否允许写入的控制会更加的复杂。

# Job control

shell和进程采用`signal`通信，`signal`是一种软件中断

## Killing a process

* `Ctrl-C`:	`SIGINT`
* `Ctrl-\`:	`SIGQUIT`
* `kill -TERM<PID>`: `SIGTERM`(  比前二者更general )



An example of a Python program that captures `SIGINT` and ignores it,

```python
#!/usr/bin/env python
import signal, time

def handler(signum, time):
    print("\nI got a SIGINT, but I am not stopping")

signal.signal(signal.SIGINT, handler)
i = 0
while True:
    time.sleep(.1)
    print("\r{}".format(i), end="")
    i += 1

```



Terminal :

```
202^C
I got a SIGINT, but I am not stopping
212^C
I got a SIGINT, but I am not stopping
219^C
I got a SIGINT, but I am not stopping
367^\zsh: quit (core dumped)  /bin/python ~/Projects/Python/ignoreSIGINT.py
```

`^` is how `Ctrl` is displayed when typed in the terminal



## Pausing and backgrounding processes

* `Ctrl-C`:	`SIGSTP`

  * short for Terminal Stop (i.e. the terminal’s version of `SIGSTOP`), which pauses a process

*  [`fg`](https://www.man7.org/linux/man-pages/man1/fg.1p.html) or [`bg`](http://man7.org/linux/man-pages/man1/bg.1p.html): continue the paused job in the foreground or in the background

  * `fg/bg`: Resume the most recently suspended job and run it in the forward/background
  * `fg/bg  %job_id`

* `jobs`:  显示**当前session**的未完成的job

  * 得到job的PID：
    * `grep`
    * `%job_id`: `job_id`由`job`显示
  * To refer to the last backgrounded job you can use the `$!` special parameter.

* `pgrep`: Find or signal processes by name.

  * `-l`：同时显示进程名和PID

  * `-o`： 当匹配多个进程时，显示进程号最小的那个

  * `-n`： 当匹配多个进程时，显示进程号最大的那个
    * 注：进程号越大，并不一定意味着进程的启动时间越晚

  ```shell
  #Return PIDs of any running processes with a matching command string:
  pgrep process_name
  ```

  

* `&` suffix in a command will run the command in the background, giving you the prompt back, although **it will still use the shell’s `STDOUT` which can be annoying**

  *  (use shell redirections in that case): `command >out.file 2>&1 &`

* 被放到后台的进程是当前terminal的子进程，当杀死父进程terminal时，会发送`SIGHUP`杀死子进程，为了避免这种情况：

  * run the program with [`nohup`](https://www.man7.org/linux/man-pages/man1/nohup.1.html) (a wrapper to ignore `SIGHUP`)

    `nohup command command_arguments`

  * use `disown` if the process has already been started

    ```shell
    #disown the current job:                                                     
    disown
    
    #Disown a specific job:
    disown %job_number                                                           
    
    #Disown all jobs:
    disown -a                                                                   
    
    #Keep job (do not disown it), but mark it so that no future SIGHUP is #received on shellexit:                                                     
    disown -h %job_number
    ```

## example

```shell
$ sleep 1000
^Z
[1]  + 18653 suspended  sleep 1000

$ nohup sleep 2000 &
[2] 18745
appending output to nohup.out

$ jobs
[1]  + suspended  sleep 1000
[2]  - running    nohup sleep 2000

$ bg %1
[1]  - 18653 continued  sleep 1000

$ jobs
[1]  - running    sleep 1000
[2]  + running    nohup sleep 2000

$ kill -STOP %1
[1]  + 18653 suspended (signal)  sleep 1000

$ jobs
[1]  + suspended (signal)  sleep 1000
[2]  - running    nohup sleep 2000

$ kill -SIGHUP %1
[1]  + 18653 hangup     sleep 1000

$ jobs
[2]  + running    nohup sleep 2000

$ kill -SIGHUP %2

$ jobs
[2]  + running    nohup sleep 2000

$ kill %2
[2]  + 18745 terminated  nohup sleep 2000

$ jobs
```



# Terminal Multiplexers





我们只介绍`tmux `，`tmux` expects you to know its keybindings, and they all have the form `<C-b> x` where`tmux` has the following hierarchy of objects:

* All commands in tmux are triggered by a **prefix key** followed by a **command key** (quite similar to emacs).By default, tmux uses `C-b` as prefix key
  *  which means (1) press `Ctrl+b`, (2) release `Ctrl+b`, and then (3) press `command key`. 
*   默认的`session_name`和`window_name`都是0开头的数字

## hierarchy

### Sessions

 a session is an independent workspace with one or more windows

- `tmux` starts a new session.
- `tmux new -s NAME` starts it with that name.
- `tmux ls` lists the current sessions
- Within `tmux` typing `<C-b> d` detaches the current session
- `tmux a` attaches the last session. You can use `-t` flag to specify which

### Windows



Equivalent to tabs in editors or browsers, they are visually separate parts of the same session

- `<C-b> c` Creates a new window. To close it you can just terminate the shells doing `<C-d>`
- `<C-b>  [window_name]` Go to the specified window. Note they are numbered
- `<C-b> p` Goes to the previous window
- `<C-b> n` Goes to the next window
- `<C-b> ,` Rename the current window
- `<C-b> w` List current windows

### Panes

 

\- Like vim splits, panes let you have multiple shells in the same visual display.

- `<C-b> "` Split the current pane horizontally
- `<C-b> %` Split the current pane vertically
- `<C-b> <direction>` Move to the pane in the specified *direction*. Direction here means arrow keys.
- `<C-b> z` Toggle zoom for the current pane
- `<C-b> [` Start scrollback. You can then press `<space>` to start a selection and `<enter>` to copy that selection.
- `<C-b> <space>` Cycle through pane arrangements.
- `<C-b> x`: close the pane

## moving on

Some  common  commands：

- `C-b z`: make a pane go full screen. Hit `C-b z` again to shrink it back to its previous size
- `C-b C-<arrow key>`: Resize pane in direction of <arrow key>[4](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/#fn:4)
- `C-b ,`: Rename the current window

For further reading, [here](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/) is a quick tutorial on `tmux` and [this](http://linuxcommand.org/lc3_adv_termmux.php) has a more detailed explanation that covers the original `screen` command. You might also want to familiarize yourself with [`screen`](https://www.man7.org/linux/man-pages/man1/screen.1.html), since it comes installed in most UNIX systems.

## session handling

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

# Aliases

```
alias alias_name="command_to_alias arg1 arg2"
```

`alias`是一个`command`，接受**一个**参数， 因此`=`左右不能有空格

## example

```shell
# Make shorthands for common flags
alias ll="ls -lh"

# Save a lot of typing for common commands
alias gs="git status"
alias gc="git commit"
alias v="vim"

# Save you from mistyping
alias sl=ls

# Overwrite existing commands for better defaults
alias mv="mv -i"           # -i prompts before overwrite
alias mkdir="mkdir -p"     # -p make parent dirs as needed
alias df="df -h"           # -h prints human readable format

# Alias can be composed
alias la="ls -A"
alias lla="la -l"

# To ignore an alias run it prepended with \
\ls
# Or disable an alias altogether with unalias
unalias la

# To get an alias definition just call it with alias
alias ll
# Will print ll='ls -lh'
```

`alias`是面向session的，session关闭也使得`alias`失效， 要想使`alias`持久化，可以将其写在shell的启动文件，如 `.bashrc` or `.zshrc`

# Dotfiles

* 使用dotbot

* dotfile无法跨平台，换个os就会失效. 为此，可以根据不同的平台加载不同的配置：

  ```shell
  if [[ "$(uname)" == "Linux" ]]; then {do_something}; fi
  
  # Check before using shell-specific features
  if [[ "$SHELL" == "zsh" ]]; then {do_something}; fi
  
  # You can also make it machine-specific
  if [[ "$(hostname)" == "myServer" ]]; then {do_something}; fi
  
  ```



* 不同程序共享相同配置：

  ```shell
  # Test if ~/.aliases exists and source it
  if [ -f ~/.aliases ]; then
      source ~/.aliases
  fi
  ```

*  注意，某些配置最好不要公开，比如`~/.ssh/config`, 因此dotfile的版本管理最好用私人仓库

# SSH

`ssh`

* `ssh username@remote_host`

## execute commands on remote machine

* ``ssh username@remote_host -t “command command_arguments“` `: 在目标主机的home目录下执行command

  * 要执行的命令必须括起来，否则在有的系统中除了第一个命令，其它都是在本地执行的（比如manjaro）

  * 支持pipe： 
    * `ssh foobar@server ls | grep PATTERN`： 在本地grep远程的输出
    * `ls | ssh foobar@server grep PATTERN`： 在远程grep本地的输出

  * `-t`：Run a command on a remote server with a [t]ty allocation allowing interaction with the remote command

    * explain： 命令如果要与用户交互，就需要分配tty,默认情况下，单纯的ssh连接，shell会分配一个tty,此时你运行了一个shell session； 但当执行`ssh foobar@server "command"`时，shell不会为这个远程会话分配 TTY。此时 ssh 会立即退出远程主机，所以需要交互的命令也随之结束， 添加 -t 参数会告诉shell分配一个tty与远程 shell 进行交互，ssh 会保持登录状态，直到你退出需要交互的命令

    

## Key  generation

```bash
ssh-keygen -t rsa -b 1024 -f yourkeyname -C "备注"
```

| 参数   | 解释                                                         |
| ------ | ------------------------------------------------------------ |
| -b     | 采用长度1024bit的密钥对,b=bits,最长4096                      |
| -t rsa | 采用rsa加密方式,t=type                                       |
| -f     | 生成文件名,f=output_keyfiles                                 |
| -C     | 备注，C=comment                                              |
| -a     | rounds <br/>       指定密钥生成函数，参数数值越高，密码越安全也越慢，默认为16  Higher numbers result in <br/> |
|        |                                                              |
|        |                                                              |

* 公钥和私钥默认位于`~/.ssh`
*  使用[`ssh-agent`](https://www.man7.org/linux/man-pages/man1/ssh-agent.1.html) or [`gpg-agent`](https://linux.die.net/man/1/gpg-agent)  避免每次都输密码
* `ssh-keygen -y -f ~/.ssh/id_rsa`： 根据私钥，检查公钥
  * `-y`：  This option will read a private OpenSSH format file and print an OpenSSH public key to stdout

## Key based authentication


* `ssh` will look into `.ssh/authorized_keys` to determine which clients it should let in

   ```shell
   cat .ssh/id_ed25519.pub | ssh foobar@remote 'cat >> ~/.ssh/authorized_keys'
   
   #or 
   ssh-copy-id -i .ssh/id_ed25519.pub foobar@remote
   ```



​		

  

## Copying files over SSH

There are many ways to copy files over ssh:

- `ssh+tee`, the simplest is to use `ssh` command execution and STDIN input by doing `cat localfile | ssh remote_server tee serverfile`. Recall that [`tee`](https://www.man7.org/linux/man-pages/man1/tee.1.html) writes the output from STDIN into a file.



- [`scp`](https://www.man7.org/linux/man-pages/man1/scp.1.html) when copying large amounts of files/directories, the secure copy `scp` command is more convenient since it can easily recurse over paths. 

  ````shell
  scp path/to/local_file remote_host:path/to/remote_file
  ````



- [`rsync`](https://www.man7.org/linux/man-pages/man1/rsync.1.html) improves upon `scp` by detecting identical files in local and remote, and preventing copying them again. It also provides more fine grained control over symlinks, permissions and has extra features like the `--partial` flag that can resume from a previously interrupted copy. `rsync` has a similar syntax to `scp`.



## Port Forwarding

* 见《SSH Port Forwarding》

## SSH Configuration

* alias:

  ```shell
  alias my_server="ssh -i ~/.id_ed25519 --port 2222 -L 9999:localhost:8888 foobar@remote_server
  ```

  好处是可以继续调用别的命令

  

* using `~/.ssh/config`.

  ```
  Host vm
      User foobar
      HostName 172.16.174.141
      Port 2222
      IdentityFile ~/.ssh/id_ed25519
      LocalForward 9999 localhost:8888
  
  # Configs can also take wildcards
  Host *.mit.edu
      User foobaz
  ```

