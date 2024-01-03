---
title: The Bash Environment
tags:
  - Shell
  - Linux
categories:
  - Software Engineering
date: 2023-12-29 03:23:41
---


* Machtelt Garrels. *[Chapter 3. The Bash environment. Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_03_01.html)*.
* 蔡德明. *[第十一章 认识与学习Bash. 鸟哥的Linux私房菜](http://cn.linux.vbird.org/linux_basic/0320bash_4.php)*.

<!--more-->

# Intro

Commands and implementations may be specific for Ubuntu22.04, but the concepts should be universal for all Unix like systems.

# Login shell and Interactive shell

[-->Source](https://superuser.com/a/183956)

> `man bash`:
>
> A login shell is one whose first character of argument zero is a -, or one started with the --login option.
>
>        An interactive shell is one started without non-option arguments (unless -s is specified) and without the -c option  whose  standard  input
>        and error are both connected to terminals (as determined by isatty(3)), or one started with the -i option.  PS1 is set and $- includes i if
>        bash is interactive, allowing a shell script or a startup file to test this state.

* interactive shell: An interactive shell generally reads from, and writes to, a user's terminal: input and output are connected to a terminal.
* **login shell**: The shell executed with a login process is a login shell. For example, when you **log into** your machine through `tty1 ~ tty6`, or through, you need to input the username and  password, that's a **login process**. So the started shell is a login shell.
  * **interactive login shell**: When you log into your machine from the command line, via `ssh`, or run a command such as `su - username`, you are running an *interactive login* shell.
* **non-login shell**: The shell that doesn't executed with a login process is a non-login shell. For example, if you use a graphic interface, say X windows, then you've logged into the system using the the graphic interface, not the shell. You can start a non-login shell via a terminal emulator like `KDE Konsole`.
  * **interactive, non-login shell**: When you open a terminal emulator (`iTerm` for example), the executed shell is interactive, but not a login shell, meaning you didn't use it to login the system.
* Finally, when you run a shell script, it is run in a *non-interactive, non-login shell*.



## Is this shell interactive?

[-->Source](https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_02.html)

Test by looking at the content of the special parameter `-`, it contains an 'i' when the shell is interactive:

```text
> echo $-
569JNRXZghiklms
```

In non-interactive shells, the prompt, `PS1`, is unset.

## Is this shell a login shell?

[-->Source](https://floatingoctothorpe.uk/2018/bash-config-and-where-it-lives.html)

If bash is started by a login process (e.g. by /bin/login) the first argument by convention is prefixed with a - character:

```text
$ echo $0
-bash
```

Bash uses this to determine if the shell should be treated as a login shell. Bash then checks to see if the shell is interactive, this is done by calling `isatty` to check stdin and stderr are connected to a tty. There are a few exceptions to this, for example using the `-c` option will normally prevent bash running as an interactive shell. For more info on the other exceptions, refer to the bash docs.

* On OS X, a terminal (including iTerm) by default runs a login shell (Zsh) every time, so this argument not satisfies all systems.

# Shell initialization files

> `man bash`:
>
> When  bash is invoked as an **interactive login shell**, or as a non-interactive shell with the --login option, it first reads and executes  commands  from  the file **/etc/profile**, if that file exists.  After reading    that file, it looks for **~/.bash_profile, ~/.bash_login, and ~/.profile,   in  that order**, and reads and executes commands from the first one that  exists and is readable.  The --noprofile option may be  used  when  the   shell is started to inhibit this behavior.
>
> When an **interactive shell** that is **not a login shell**  is  started,  bash  reads  and  executes  commands  from **/etc/bash.bashrc** and **~/.bashrc**, if  these files exist.  This may be inhibited by using the  --norc  option.  The  --rcfile  file option will force bash to read and execute commands  from file instead of /etc/bash.bashrc and ~/.bashrc.

The shell initialization files can be split as two categories:

1. System-wide configuration files
2. Individual user configuration files

A configuration file in the root dir `/` is system-wide, file in the home dir `~/` is user-wide.



According to the output of `man bash`, 

When an interactiv <u>login shell</u> is started, it'll:

1. Read `/etc/profile`, which is system-wide.
2. Then it'll read (if any) `~/.bash_profile, ~/.bash_login, and ~/.profile`, which are user-wide.



When an interactive <u>non-login shell</u> is started, it'll:

1. Read `/etc/bash.bashrc`, which is system-wide.
2. Then it'll read (if any) `~/.bashrc`, which is user-wide.

****

NOTE: 

1. `/etc/profile`  is only read by login shells, and `~/.bashrc` is only read by non-login shells.
2. The specific files depends on the platform. In Ubuntu22.04, there's no  `~/.bash_profile, ~/.bash_login, and ~/.profile`, only a `~/.bashrc`. In MacOS, there's only a `~/.bash_profile`. In this chapter, all commands and files are contraint to **Ubuntu22.04**.
3. The system will skip config files if they're missing. You can create them manually as well.

## System-wide configuration files

### `/etc/profile`

Let's see it's content:

```shell
# In Ubuntu 22.04
# /etc/profile: system-wide .profile file for the Bourne shell (sh(1))
# and Bourne compatible shells (bash(1), ksh(1), ash(1), ...).

if [ "${PS1-}" ]; then
  if [ "${BASH-}" ] && [ "$BASH" != "/bin/sh" ]; then
    # The file bash.bashrc already sets the default PS1.
    # PS1='\h:\w\$ '
    if [ -f /etc/bash.bashrc ]; then
      . /etc/bash.bashrc
    fi
  else
    if [ "$(id -u)" -eq 0 ]; then
      PS1='# '
    else
      PS1='$ '
    fi
  fi
fi

if [ -d /etc/profile.d ]; then
  for i in /etc/profile.d/*.sh; do
    if [ -r $i ]; then
      . $i
    fi
  done
  unset i
fi
```

Basically, `/etc/profile` will do two things:

1. Search if file `/etc/bash.bashrc` exists, if it does, execute it.

   ```shell
   if [ -f /etc/bash.bashrc ]; then
         . /etc/bash.bashrc
   fi
   ```

2.  Search if dir `/etc/profile.d` exists, if it does, execute all the files (if readable) in it.

   ```shell
   if [ -d /etc/profile.d ]; then
     for i in /etc/profile.d/*.sh; do
       if [ -r $i ]; then
         . $i
       fi
     done
     unset i
   fi
   ```

### `/etc/bash.bashrc`

We can see the content of  `/etc/bash.bashrc` :

```shell
# System-wide .bashrc file for interactive bash(1) shells.

# To enable the settings / commands in this file for login shells as well,
# this file has to be sourced in /etc/profile.

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, overwrite the one in /etc/profile)
# but only if not SUDOing and have SUDO_PS1 set; then assume smart user.
if ! [ -n "${SUDO_USER}" -a -n "${SUDO_PS1}" ]; then
  PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
```

### `/etc/profile.d` 

We can see the content of  files in `/etc/profile.d` :

```text
$ ls /etc/profile.d
01-locale-fix.sh  bash_completion.sh     debuginfod.csh  gnome-session_gnomerc.sh  vte-2.91.sh  xdg_dirs_desktop_session.sh
apps-bin-path.sh  cedilla-portuguese.sh  debuginfod.sh   im-config_wayland.sh      vte.csh
```

Every `.sh` file is just a simple shell script.

## User-wide configuration files

In Ubuntu22.04, there's no  `~/.bash_profile, ~/.bash_login, and ~/.profile`, only a `~/.bashrc`.

### `~/.bashrc`

The content of `~/.bashrc`:

```shell
# In Ubuntu 22.04
# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

<...>
```

# Zsh initialization files

[--> Zsh manual](https://zsh.sourceforge.io/Doc/Release/zsh_toc.html)

Zsh uses different config files from bash.

When an interactiv <u>Zshl</u> (Not clear if whether login affects) is started, it'll:

1. Read system-wide config files in the order `zshenv, zprofile, zshrc, zlogin`. See `/etc/zsh.zshenv`:

   ```sh
   # /etc/zsh/zshenv: system-wide .zshenv file for zsh(1).
   #
   # This file is sourced on all invocations of the shell.
   # If the -f flag is present or if the NO_RCS option is
   # set within this file, all other initialization files
   # are skipped.
   #
   # This file should contain commands to set the command
   # search path, plus other important environment variables.
   # This file should not contain commands that produce
   # output or assume the shell is attached to a tty.
   #
   # Global Order: zshenv, zprofile, zshrc, zlogin
   # ....
   ```

2. Read user-wide config file: `~/.zshrc`

