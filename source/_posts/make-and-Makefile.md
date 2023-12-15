---
categories:
- Software Engineering
date: 2022-05-05 03:43:04
tags: Linux
title: make and Makefile
---

Outline:

* make
* Makefile

<!--more-->

# make

GNU make是一个命令工具，是一个用来控制软件**构建**过程的自动化管理工具。make通过称为Makefile的文件来完成并自动维护编译工作, makefile定义了系统各模块间的依赖关系，make解释makefile中的指令

make所在路径: `$(MAKE)`



```shell
make [-f filename] [targetname]
```

* make会在当前目录下找名字叫"Makefile"或"makefile"的文件, 根据Makefile中定义的规则来执行命令
* Makefile中第一条规则定义的target是默认target。 直接执行`make`，执行的就是默认target
* `make install`需要 root 权限
* 如果 config 的时候使用 root 权限，则编译后产生的所有文件都需要root权限

```shell
# automake方式
./configure #生成新的makefile
make
make install
make uninstall
make clean
make distclean# 退回到configure之前(删除makefile)
```



example：

```makefile
TOPDIR = ../
include $(TOPDIR)Rules.mak
EXTRA LIBS += :
EXEC = $(INSTALL_DIR)/hello
OBJS = hello.o # make uninstall之后系统中源代码仍然存在
# 变量定义，makefile可以include别的makefile

all: $(EXEC) # 默认执行make all
  $(EXEC): $(OBJS)
  $(CC) $(LDFLAGS) -0 $@ $(OBJS) $(EXTRA_ LIBS) # gcc的别名CC，$@明确了目标文件放置位置
install:
  $(EXP_ INSTALL) $(EXEC) $(INSTALL_ DIR) # make install执行的指定目标
clean:
  -rm -f $(EXEC) *.elf*.gdb *.o
```



# Makefile

## 概述

Makefile文件由一系列规则（rules）构成。每条规则的形式如下：

```bash
<target> : <prerequisites> 
[tab]  <commands>
```

* target是一个目标文件，可以是Object File，也可以是执行文件

* prerequisites是要生成target所需要的文件或是目标

* command是make需要执行的命令。(可以是任意的Shell命令)

* "目标"是必需的，不可省略；"前置条件"和"命令"都是可选的，但是两者之中必须至少存在一个
* 每条规则就明确两件事：构建目标的前置条件是什么，以及如何构建

## Makefile文件的规则



```makefile
hello : main.o kbd.o
  gcc -o hello main.o kbd.o
main.o : main.c defs.h
  cc -c main.c
kbd.o : kbd.c defs.h command.h
  cc -c kbd.c
clean :
  rm edit main.o kbd.o # 伪目标
```

### target

一个目标（target）就构成一条规则。目标通常是文件名，指明Make命令所要构建的对象，比如上文的 a.txt 。目标可以是一个文件名，也可以是多个文件名，之间用空格分隔



如果Make命令运行时没有指定目标，会执行Makefile文件的**第一个目标**作为默认目标

```
make
```

* 该命令执行Makefile的第一个目标



#### 伪目标

除了文件名，目标还可以是某个操作的名字，这称为"伪目标"（phony target），伪目标不是文件名，而是一个操作的名字

```makefile
clean:
   rm *.o
```

上面代码的目标是clean，属于"伪目标 "，作用是删除对象文件:

```shell
make clean
```



* "伪目标"的取名不能和文件名重名
  * 例如，如果当前目录中，正好有一个文件叫做clean，那么这个`make clean`不会执行。因为Make发现clean文件已经存在，就认为没有必要重新构建了，就不会执行指定的rm命令



* 为了避免和文件重名的这种情况，可以使用`.PHONY`来显示地指明一个目标是"伪目标"，向make说明，不管是否有这个文件，这个目标就是"伪目标"

  ```makefile
  .PHONY: clean
  clean:
       rm *.o temp
  ```

  声明clean是"伪目标"之后，make就不会去检查是否存在一个叫做clean的文件，而是每次运行都执行对应的命令。像.PHONY这样的内置目标名还有不少，可以查看[手册](https://www.gnu.org/software/make/manual/html_node/Special-Targets.html#Special-Targets)



* 伪目标一般没有依赖的文件，但也可以为伪目标指定所依赖的文件

* 伪目标同样可以作为"默认目标"，只要将其放在第一个

#### 多目标

当多个目标同时依赖于一个文件，并且其生成的命令大体类似，可以使用`$@`表示目前规则中所有的目标的集合

举例:

```makefile
bigoutput littleoutput : text.g
generate text.g -$(subst output,,$@) > $@ # 将$@中的output替换成空

#上述规则等价于
bigoutput : text.g
  generate text.g -big > bigoutput
littleoutput : text.g
  generate text.g -little > littleoutput 
```





### prerequisites

prerequisite通常是一组文件名，之间用空格分隔。它指定了target是否重新构建的判断标准：make会检查prerequisite, **只要有一个prerequisite不存在，或者有过更新**（前置文件的last-modification**时间戳**比目标的时间戳新），target就需要重新构建

如果prerequisite也不存在，make就会查找生成该prerequisite（此时是作为目标）的规则，这是个递归的过程



```makefile
result.txt: source.txt
 cp source.txt result.txt
```

上面代码中，构建 result.txt 的前置条件是 source.txt 。如果当前目录中，source.txt 已经存在，那么`make result.txt`可以正常运行，否则必须再写一条规则，来生成 source.txt 



```makefile
source.txt:
 echo "this is the source" > source.txt
```

上面代码中，source.txt后面没有前置条件，就意味着它跟其他文件都无关，只要这个文件还不存在，每次调用`make source.txt`，它都会生成



```shell
make result.txt
make result.txt
```

上面命令连续执行两次`make result.txt`。第一次执行会先新建 source.txt，然后再新建 result.txt。第二次执行，Make发现 source.txt 没有变动（时间戳晚于 result.txt），就不会执行任何操作，result.txt 也不会重新生成



如果需要生成多个文件，往往采用下面的写法:

```makefile
source: file1 file2 file3
```

上面代码中，source 是一个伪目标，只有三个前置文件，没有任何对应的命令



```shell
make source
```

执行`make source`命令后，就会一次性生成 file1，file2，file3 三个文件。这比下面的写法要方便很多:

```
make file1
make file2
make file3
```





### commands

命令（commands）表示如何更新目标文件，由一行或多行的Shell命令组成。它是构建"目标"的具体指令，它的运行结果通常就是生成目标文件

每行命令之前必须有一个tab键。如果想用其他键，可以用内置变量`.RECIPEPREFIX`声明:

```makefile
.RECIPEPREFIX = >
all:
> echo Hello, world
```

上面代码用`.RECIPEPREFIX`指定，大于号（>）替代tab键。所以，每一行命令的起首变成了大于号，而不是tab键



需要注意的是，**每行命令在一个单独的shell中执行** , 这些Shell之间没有继承关系（因而普通变量不可见）

```makefile
var-lost:
 export foo=bar
 echo "foo=[$$foo]"
```

上面代码执行后（`make var-lost`），取不到foo的值。因为两行命令在两个不同的进程执行。一个解决办法是将两行命令写在一行，中间用分号分隔:

```makefile
var-kept:
 export foo=bar; echo "foo=[$$foo]"
```



另一个解决办法是在换行符前加反斜杠转义:

```shell
var-kept:
 export foo=bar; \
 echo "foo=[$$foo]"
```



最后一个方法是加上`.ONESHELL:`命令:

```makefile
.ONESHELL:
var-kept:
 export foo=bar; 
 echo "foo=[$$foo]"
```





## Makefile文件的语法

makefile描述模块间的依赖关系

### 注释

井号（#）在Makefile中表示注释。

> ```bash
> # 这是注释
> result.txt: source.txt
>  # 这是注释
>  cp source.txt result.txt # 这也是注释
> ```

### 回显（echoing）



默认情况下，每执行一条 makefile 中的命令之前，**Shell 终端都会显示出这条命令的具体内容**，除非该命令用分号分隔而紧跟在依赖关系后面，我们称之为"回显"。如果不想显示命令的具体内容，我们可以在命令的开头加上`@`，这种情况通常用于 echo 命令



> ```bash
> test:
>  # 这是测试
> ```

执行上面的规则，会得到下面的结果

> ```bash
> $ make test
> # 这是测试
> ```

在命令的前面加上@，就可以关闭回声

> ```bash
> test:
>  @# 这是测试
> ```

现在再执行`make test`，就不会有任何输出

由于在构建过程中，需要了解当前在执行哪条命令，所以通常只在注释和纯显示的echo命令前面加上@

> ```bash
> test:
>  @# 这是测试
>  @echo TODO
> ```

### 通配符

通配符（wildcard）用来指定一组符合条件的文件名。Makefile 的通配符与 Bash 一致，主要有星号（*）、问号（？）和 [...] 。比如， *.o 表示所有后缀名为o的文件。

> ```bash
> clean:
>      rm -f *.o
> ```

### 模式匹配

Make命令允许对文件名，进行类似正则运算的匹配，主要用到的匹配符是%。比如，假定当前目录下有 f1.c 和 f2.c 两个源码文件，需要将它们编译为对应的对象文件。

> ```bash
> %.o: %.c
> ```

等同于下面的写法。

> ```bash
> f1.o: f1.c
> f2.o: f2.c
> ```

使用匹配符%，可以将大量同类型的文件，只用一条规则就完成构建。

### 变量和赋值符

Makefile 允许使用等号自定义变量。

> ```bash
> txt = Hello World
> test:
>  @echo $(txt)
> ```

上面代码中，变量 txt 等于 Hello World。调用时，变量需要放在 $( ) 之中。

调用Shell变量，需要在美元符号前，再加一个美元符号，这是因为Make命令会对美元符号转义。

> ```bash
> test:
>  @echo $$HOME
> ```

有时，变量的值可能指向另一个变量。

> ```bash
> v1 = $(v2)
> ```

上面代码中，变量 v1 的值是另一个变量 v2。这时会产生一个问题，v1 的值到底在定义时扩展（静态扩展），还是在运行时扩展（动态扩展）？如果 v2 的值是动态的，这两种扩展方式的结果可能会差异很大。

为了解决类似问题，Makefile一共提供了四个赋值运算符 （=、:=、？=、+=），它们的区别请看[StackOverflow](https://stackoverflow.com/questions/448910/makefile-variable-assignment)。

> ```bash
> VARIABLE = value
> # 在执行时扩展，允许递归扩展。
> 
> VARIABLE := value
> # 在定义时扩展。
> 
> VARIABLE ?= value
> # 只有在该变量为空时才设置值。
> 
> VARIABLE += value
> # 将值追加到变量的尾端。
> ```

### 内置变量（Implicit Variables）

Make命令提供一系列内置变量，比如，$(CC) 指向当前使用的编译器，$(MAKE) 指向当前使用的Make工具。这主要是为了跨平台的兼容性，详细的内置变量清单见[手册](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html)。

> ```bash
> output:
>  $(CC) -o output input.c
> ```

### 自动变量（Automatic Variables）

Make命令还提供一些自动变量，它们的值与当前规则有关。主要有以下几个。

**（1）$@**

$@指代当前目标，就是Make命令当前构建的那个目标。比如，`make foo`的 $@ 就指代foo。

> ```bash
> a.txt b.txt: 
>  touch $@
> ```

等同于下面的写法。

> ```bash
> a.txt:
>  touch a.txt
> b.txt:
>  touch b.txt
> ```

**（2）$<**

$< 指代第一个前置条件。比如，规则为 t: p1 p2，那么$< 就指代p1。

> ```bash
> a.txt: b.txt c.txt
>  cp $< $@ 
> ```

等同于下面的写法。

> ```bash
> a.txt: b.txt c.txt
>  cp b.txt a.txt 
> ```

**（3）$?**

$? 指代比目标更新的所有前置条件，之间以空格分隔。比如，规则为 t: p1 p2，其中 p2 的时间戳比 t 新，$?就指代p2。

**（4）$^**

$^ 指代所有前置条件，之间以空格分隔。比如，规则为 t: p1 p2，那么 $^ 就指代 p1 p2 。

**（5）$\***

$* 指代匹配符 % 匹配的部分， 比如% 匹配 f1.txt 中的f1 ，$* 就表示 f1。

**（6）$(@D) 和 $(@F)**

$(@D) 和 $(@F) 分别指向 $@ 的目录名和文件名。比如，$@是 src/input.c，那么$(@D) 的值为 src ，$(@F) 的值为 input.c。

**（7）$(<D) 和 $(<F)**

$(<D) 和 $(<F) 分别指向 $< 的目录名和文件名。

所有的自动变量清单，请看[手册](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html)。下面是自动变量的一个例子。

> ```bash
> dest/%.txt: src/%.txt
>  @[ -d dest ] || mkdir dest
>  cp $< $@
> ```

上面代码将 src 目录下的 txt 文件，拷贝到 dest 目录下。首先判断 dest 目录是否存在，如果不存在就新建，然后，$< 指代前置文件（src/%.txt）， $@ 指代目标文件（dest/%.txt）。

### 判断和循环

Makefile使用 Bash 语法，完成判断和循环。

> ```bash
> ifeq ($(CC),gcc)
> libs=$(libs_for_gcc)
> else
> libs=$(normal_libs)
> endif
> ```

上面代码判断当前编译器是否 gcc ，然后指定不同的库文件。

> ```bash
> LIST = one two three
> all:
>  for i in $(LIST); do \
>      echo $$i; \
>  done
> 
> # 等同于
> 
> all:
>  for i in one two three; do \
>      echo $i; \
>  done
> ```

上面代码的运行结果。

> ```bash
> one
> two
> three
> ```

### 函数

Makefile 还可以使用函数，格式如下。

> ```bash
> $(function arguments)
> # 或者
> ${function arguments}
> ```

Makefile提供了许多[内置函数](https://www.gnu.org/software/make/manual/html_node/Functions.html)，可供调用。下面是几个常用的内置函数。

**（1）shell 函数**

shell 函数用来执行 shell 命令

> ```bash
> srcfiles := $(shell echo src/{00..99}.txt)
> ```

**（2）wildcard 函数**

wildcard 函数用来在 Makefile 中，替换 Bash 的通配符。

> ```bash
> srcfiles := $(wildcard src/*.txt)
> ```

**（3）subst 函数**

subst 函数用来文本替换，格式如下。

> ```bash
> $(subst from,to,text)
> ```

下面的例子将字符串"feet on the street"替换成"fEEt on the strEEt"。

> ```bash
> $(subst ee,EE,feet on the street)
> ```

下面是一个稍微复杂的例子。

> ```bash
> comma:= ,
> empty:=
> # space变量用两个空变量作为标识符，当中是一个空格
> space:= $(empty) $(empty)
> foo:= a b c
> bar:= $(subst $(space),$(comma),$(foo))
> # bar is now `a,b,c'.
> ```

**（4）patsubst函数**

patsubst 函数用于模式匹配的替换，格式如下。

> ```bash
> $(patsubst pattern,replacement,text)
> ```

下面的例子将文件名"x.c.c bar.c"，替换成"x.c.o bar.o"。

> ```bash
> $(patsubst %.c,%.o,x.c.c bar.c)
> ```

**（5）替换后缀名**

替换后缀名函数的写法是：变量名 + 冒号 + 后缀名替换规则。它实际上patsubst函数的一种简写形式。

> ```bash
> min: $(OUTPUT:.js=.min.js)
> ```

上面代码的意思是，将变量OUTPUT中的后缀名 .js 全部替换成 .min.js 。





## 预定义变量

1. `$<` 第一个依赖文件的名称
2. `$?` 所有的依赖文件，以空格分开，这些依赖文件的修改日期比目标的创建日期晚
3. `$+` 所有的依赖文件，以空格分开，并以出现的先后为序，可能包含重复的依赖文件
4. `$^` 所有的依赖文件，以空格分开，不包含重复的依赖文件
5. `$*` 不包括扩展名的目标文件名称
6. `$@` 目标的完整名称
7. `$%` 如果目标是归档成员，则该变量表示目标的归档成员名称

```makefile
edit : main.o kbd.o command.o display.o \
  insert.o search.o files.o utils.o
  gcc -o edit main.o kbd.o command.o display.o \
  insert.o search.o files.o utils.o
main.o : main.c defs.h
  gcc -c main.c
kbd.o : kbd.c defs.h command.h
  gcc -c kbd.c
command.o : command.c defs.h command.h
  gcc -c command.c
display.o : display.c defs.h buffer.h
  gcc -c display.c
insert.o : insert.c defs.h buffer.h
  gcc -c insert.c
search.o : search.c defs.h buffer.h
  gcc -c search.c
files.o : files.c defs.h buffer.h command.h
  gcc -c files.c
utils.o : utils.c defs.h
  gcc -c utils.c
clean :
  rm edit main.o kbd.o command.o display.o \
  insert.o search.o files.o utils.o
OBJECTS = main.o kbd.o command.o display.o \
insert.o search.o files.o utils.o
edit : $(OBJECTS)
  gcc -o edit $(OBJECTS)
main.o : main.c defs.h
  gcc -c main.c
kbd.o : kbd.c defs.h command.h
  gcc -c kbd.c
command.o : command.c defs.h command.h
  gcc -c command.c
display.o : display.c defs.h buffer.h
  gcc -c display.c
insert.o : insert.c defs.h buffer.h
  gcc -c insert.c
search.o : search.c defs.h buffer.h
  gcc -c search.c
files.o : files.c defs.h buffer.h command.h
  gcc -c files.c
utils.o : utils.c defs.h
  gcc -c utils.c
clean :
  rm edit $(OBJECTS) 
```

## 多目标扩展

1. 语法`<targets ...>: <target-pattern>: <prereq-patterns ...> <commands>`
2. 例子
   1. 目标从$object中获取
   2. "%.o"表明要所有以".o"结尾的目标，即"foo.o bar.o"，就是变量$object集合的模式
   3. 依赖模式"%.c"则取模式"%.o"的"%"，也就是"foo bar"，并为其加下".c"的后缀，于是依赖的目标就是"foo.c bar.c"

```makefile
objects = foo.o bar.o
all: $(objects)
$(objects): %.o: %.c
  $(CC) -c $(CFLAGS) $< -o $@

# 等价于如下
foo.o : foo.c
  $(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
  $(CC) -c $(CFLAGS) bar.c -o bar.o
```

3. 编写方法：
   1. 遍历.c文件中的头文件依赖树，把每一个依赖的头文件都放到后面！gcc里面有参数。
   2. 不写.h的话：第一次编译连接不会有问题，但是若头文件发生更新，并不会重新编译
4. 多目标扩展
   1. 语法：`<targets ...>: <target-pattern>: <prereq-patterns ...><commands>... `
   2. 举例

```makefile
objects = foo.o bar.o
all: $(objects)
$(objects): %.o: %.
   c$(CC) -c $(CFLAGS) $< -o $@
```

5. 目标从$object中获取
6. "%.o"表明要所有以".o"结尾的目标，即"foo.o bar.o"，就是变量$object集合的模式

* 依赖模式"%.c"则取模式"%.o"的"%"，也就是"foo bar"，并为其加下".c"的后缀，于是依赖的目标就是"foo.c bar.c"

上述规则等价于

```makefile
foo.o : foo.c$(CC) -c $(CFLAGS) foo.c -o foo.o

bar.o : bar.c$(CC) -c $(CFLAGS) bar.c -o bar.o 
```

## Makefile执行顺序

1. make在当前目录下查找Makefile/makefile
2. make查找Makefile中第一个target
3. 如果该target不存在或者该target的依赖文件中至少有一个比target新，则继续执行指令
4. 如果target的依赖文件不存在，则找到生存该依赖的规则，执行该规则
5. make根据依赖文件生成target