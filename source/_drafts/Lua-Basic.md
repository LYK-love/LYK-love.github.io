---
title: Lua Basic
tags:

---



# Isntall

[Installing Lua](http://www.lua.org/manual/5.4/readme.html)

Lua is distributed in [source](http://www.lua.org/ftp/) form. You need to build it before using it. Building Lua should be straightforward because Lua is implemented in pure ANSI C and compiles unmodified in all known platforms that have an ANSI C compiler. Lua also compiles unmodified as C++. The instructions given below for building Lua are for Unix-like platforms, such as Linux and Mac OS X. See also [instructions for other systems](http://www.lua.org/manual/5.4/readme.html#other) and [customization options](http://www.lua.org/manual/5.4/readme.html#customization).



1. Build Lua:

   ```
   curl -R -O http://www.lua.org/ftp/lua-5.4.6.tar.gz
   tar zxf lua-5.4.6.tar.gz
   cd lua-5.4.6
   make all test
   ```

   

2. Install Lua:

   ```
   sudo make install
   ```

   

我在build过程中出现报错, 排查发现是因为我之前由于其它原因设置了如下的环境变量:

```
# in `~/.zshrc`
export LDFLAGS="-L($LLVM_HOME)/lib -Wl,-rpath,($LLVM_HOME)/lib"
```

gcc会用到该环境变量(如果有的话), 因此会报错. 只需要删除这些环境变量即可:

1. 删除`~/.zshrc`中对该变量的定义.
2. 重启shell, 或者在当前shell中: `unset LDFLAGS`.

