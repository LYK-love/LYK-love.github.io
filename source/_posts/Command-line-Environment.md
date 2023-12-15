---
categories:
- Software Engineering
date: 2022-02-10 17:30:37
title: Command-line Environment
---

Outline:

* Job control
* Tmux
* Aliase
* Dotfiles
* Remote Machines ( ssh端口转发详见其他文章 )

ref: [MIT lesson](https://missing.csail.mit.edu/2020/command-line/), [tmux tutorial](https://www.hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/), [a good introduction of Session](https://www.cnblogs.com/sparkdev/p/12146305.html)

<!--more-->



## 控制终端(controlling terminal)

**控制终端是进程的一个属性。**通过 `fork` 系统调用创建的子进程会从父进程那里继承控制终端。这样，session 中的所有进程都从 session 领头进程那里继承控制终端。Session 的领头进程称为终端的控制进程(controlling process)。简单点说就是：**一个 session 只能与一个终端关联，这个终端被称为 session 的控制终端(controlling terminal)。**同时只能由 session 的领头进程来建立或者改变终端与 session 的联系。我们可以通过 ps 命令查看进程的控制终端：

![img](https://img2018.cnblogs.com/blog/952033/202001/952033-20200103182831279-993028624.png)

支持 job control 的 **shell** 必须能够控制在某一时刻由哪个 job 使用终端。否则，可能会有多个 job 试图同时从终端读取数据，这会导致进程在接收用户输入时的混乱。为了防止这种情况发生，shell 必须按照预定的协议与终端驱动程序协作。

shell 一次只允许一个 job(进程组)访问控制终端。来自控制终端的某些输入会导致信号被发送到与控制终端关联的 job(进程组)中的所有进程。该 job 被称为控制终端上的前台 job。由 shell 管理的其他 job 在不访问终端的情况下，被称为后台 job。

Shell 的职责是通知 job 何时停止何时启动，还要把 job 的信息通知给用户，并提供机制允许用户继续暂停的 job、在前台和后台之间切换 job。比如前台 job 可以无限制的自由使用控制终端，而后台 job 则不可以。当后台 job 中的进程试图从其控制终端读取数据时，通常会向进程组发送 SIGTTIN 信号。这通常会导致该组中的所有进程停止(变成 stopped 状态)。类似地，当后台 job 中的进程试图写入其控制终端时，默认行为是向进程组发送 SIGTTOU 信号，但是否允许写入的控制会更加的复杂。

# Job control

shell和进程采用`signal`通信，`signal`是一种软件中断



## Killing a process

* `Ctrl-z`:	`SIGSTP`,
* `Ctrl-c:	`SIGINT`
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

* `Ctrl-z`:	`SIGSTP`, 会将进程suspend

  * short for Terminal Stop (i.e. the terminal’s version of `SIGSTOP`), which pauses a process

*  [`fg`](https://www.man7.org/linux/man-pages/man1/fg.1p.html) or [`bg`](http://man7.org/linux/man-pages/man1/bg.1p.html): continue the paused job in the foreground or in the background

  * `fg/bg`: Resume the most recently suspended job and run it in the forward/background
  * `fg/bg  %job_id`

* `jobs`:  显示**当前session**的未完成的job， 每个job都会分配一个工作号， 由`%[job_id]引用`

  * `[工作号] 进程号`

  * 得到job的PID：
    * `grep`
  * To refer to the last backgrounded job you can use the `$!` special parameter.

  

  如果在终端上出现如下信息：

  `[1]+ Done find / -name install.log`

  则证明后台的这个命令已经完成了。命令如果有执行结果，则也会显示到操作终端上。其中，[1] 是这个命令的工作号，"+"代表这个命令是最近一个被放入后台的



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
   ```
   
   or:
   
   ```shell
   ssh-copy-id -i .ssh/id_ed25519.pub foobar@remote
   ```

​			

​		

  

## Copying files over SSH

There are many ways to copy files over ssh:

- `ssh+tee`, 把本地文件传到远程 

  ```shell
  cat localfile | ssh remote_server "tee serverfile"
  ```

  * `tee`: 将标准输入写入文件



- [`scp`](https://www.man7.org/linux/man-pages/man1/scp.1.html): 就是ssh + cp 

  
  把本机文件传到远程：
  ````shell
   cat <local_file> | ssh  [-p <port>] <username>@<remote_host> "tee <remote_directory>/<filename>"
  ````
  
  传远程文件到本机：
  ```shell
  scp <username>@<remote_host>:<remote_file> <local_directory>
  ```
  
  * `-r`: 传文件夹
  * scp没穿输完也会生成目标文件，因此断开scp传输后，你依然能在目标主机上看到目标文件，但是这个文件是不完整的.

​		

把远程文件传到本机：		

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