---
title: Linux Signals
tags:
  - Shell
  - Linux
categories:
  - Software Engineering
date: 2023-12-29 05:35:12
---


Sources:

1. [Kill Command in Linux](https://linuxize.com/post/kill-command-in-linux/).
2. Machtelt Garrels. *[Chapter 12. Catching signals. Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_12_01.html)*.

<!--more-->

# Linux Signals

Find available signals:

```sh
man signal
```



A signal is a kind of (usually software) interrupt, used to announce    asynchronous events to a process.

There is a limited list of possible signals; we do not invent our own.  (There  might be 64 signals, for instance.)  

The name of a LINUX signal begins with  "SIG".  Although signals are numbered, we normally refer to them by their   names.  For example:

| Signal name | Signal value | Effect                  |
| ----------- | ------------ | ----------------------- |
| SIGHUP      | 1            | Hangup                  |
| SIGINT      | 2            | Interrupt from keyboard |
| SIGKILL     | 9            | Kill signal             |
| SIGTERM     | 15           | Termination signal      |
| SIGSTOP     | 17,19,23     | Stop the process        |

- `SIGINT` can be generated when a user presses `Control-C`.  

- `SIGSTOP` can be generated when a user presses `Control-Z`. 

  

# Usage of signals with kill

The `kill` command sends a signal to specified processes or process groups, causing them to act  according to the signal. 

To get a list of all available signals, invoke the command with the `-l` option:

```shell
kill -l
```



Usage:

```sh
kill [OPTIONS] [PID]...
```

The most commonly used signals are:

- `1` (`HUP`) - Reload a process.
- `9` (`KILL`) - Kill a process.
- `15` (`TERM`) - Gracefully stop a process.

When the signal is not specified, it defaults  to `-15` (-TERM).

## Terminating Processes Using the `kill` Command

To terminate or [kill a process](https://linuxize.com/post/how-to-kill-a-process-in-linux/) with the `kill` command, first you need to find the process ID number (PID). You can do this using different commands such as `top`, [`ps`](https://linuxize.com/post/ps-command-in-linux/) , `pidof` and [`pgrep`](https://linuxize.com/post/pgrep-command-in-linux/) .

Let’s say the Firefox browser has become unresponsive, and you  need to kill the Firefox process. To find the browser PIDs use the [`pidof`](https://linuxize.com/post/pidof-command-in-linux/) command:

```
pidof firefox
```

The command will print the IDs of all Firefox processes:

```output
6263 6199 6142 6076
```

Once you know the processes numbers, you can kill all of them by sending the `TERM` signal:

```
kill -9 6263 6199 6142 6076
```

Instead of searching for PIDs and then killing the processes, you can combine the above commands into one:

```
kill -9 $(pidof firefox)
```

## Reloading Processes Using the `kill` Command

Another common use case for `kill` is to send the `HUP` signal, which tells the processes to reload its settings.

For example, to [reload Nginx](https://linuxize.com/post/nginx-commands-you-should-know/) , you need to send a signal to the master process. The process ID of the Nginx master process can be found in the `nginx.pid` file, which is typically is located in the `/var/run` directory.

Use the [`cat`](https://linuxize.com/post/linux-cat-command/) command to find the master PID:

```
cat /var/run/nginx.pid
30251
```

Once you found the master PID reload the Nginx settings by typing:

```
sudo kill -1 30251
```

The command above must be run as root or user with [sudo](https://linuxize.com/post/sudo-command-in-linux/) privileges.
