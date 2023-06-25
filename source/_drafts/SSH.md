---
title: SSH
tags:
---



## SSH escape sequences

Built in to the SSH client are multiple hidden commands that can be triggered with a so called *escape sequence*. These commands can be access by a combination of the tilde prefix (`~`) followed by the command.

For example `~?` print the help message containing all of the supported escape sequences:

```bash
david@remote-host:~$ ~?
Supported escape sequences:
 ~.   - terminate session
 ~B   - send a BREAK to the remote system
 ~R   - request rekey
 ~#   - list forwarded connections
 ~?   - this message
 ~~   - send the escape character by typing it twice
(Note that escapes are only recognized immediately after newline.)
```

Pay extra attention to the last line;

> *(Note that escapes are only recognized immediately after **newline**.)*



可以看到, `~.`的组合可以关闭当前ssh session.
