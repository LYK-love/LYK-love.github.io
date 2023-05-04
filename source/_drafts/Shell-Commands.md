---
title: Shell Commands
tags:
---



* `type`: 

  The type command is a built-in bash shell command that can provide the type of a specified command.

  What does it mean by the “type of a command”? It means that you can get information like whether a Linux command is built-in shell command, where its executable is located and whether it is aliased to some other command.

  例如, 用`type`可以查alias:

  ```
  $ type  ls
  ls is an alias for ls -G
  ```

  加上`-a`可以查alias的位置:

  ```
  & type -a ls
  ls is an alias for ls -G
  ls is /bin/ls
  ```

  
