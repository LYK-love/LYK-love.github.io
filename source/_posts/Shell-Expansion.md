---
title: Shell Expansion
date: 2023-12-29 03:33:35
tags:
  - Shell
  - Linux
categories:
  - Software Engineering
---

Sources:

1. Machtelt Garrels. *[Chapter 3. The Bash environment. Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_03_04.html)*.

<!--more-->

# Brace expansion

Brace expansion is a mechanism  by which arbitrary strings may be generated.  Patterns to be  brace-expanded take the form of an optional *PREAMBLE*, followed by a series of comma-separated strings between a pair of braces, followed by an optional *POSTSCRIPT*.  The preamble is prefixed to each string contained within the braces,  and the postscript is then appended to each resulting string, expanding  left to right.

Brace expansions may be nested.  The results of each expanded string are not sorted; left to right order is preserved:

```
franky ~> **echo `\*sp{el,il,al}l\*`** spell spill spall 
```

Brace expansion is performed  before any other expansions, and any characters special to other  expansions are preserved in the result.  It is strictly textual.  Bash  does not apply any syntactic interpretation to the context of the  expansion or the text between the braces.  To avoid conflicts with  parameter expansion, the string "${" is not considered eligible for brace expansion.

A correctly-formed brace expansion must contain unquoted opening and  closing braces, and at least one unquoted comma.  Any incorrectly formed brace expansion is left unchanged.

# Tilde expansion

If a word begins with an unquoted tilde character ("~"), all of the characters up to the first unquoted slash (or all characters, if there is no unquoted slash) are considered a *tilde-prefix*.  If none of the characters in the tilde-prefix are quoted, the  characters in the tilde-prefix following the tilde are treated as a  possible login name.  If this login name is the null string, the tilde  is replaced with the value of the `HOME` shell variable.  If `HOME` is unset, the home directory of the user executing the shell is  substituted instead.  Otherwise, the tilde-prefix is replaced with the  home directory associated with the specified login name.

If the tilde-prefix is "~+", the value of the shell variable `PWD` replaces the tilde-prefix.  If the tilde-prefix is "~-", the value of the shell variable `OLDPWD`, if it is set, is substituted.

If the characters following the tilde in the tilde-prefix consist of a number N, optionally prefixed by a "+" or a "-", the tilde-prefix is replaced with the corresponding element from the directory stack, as it would be displayed by the **dirs** built-in invoked with the characters following tilde in the  tilde-prefix as an argument.  If the tilde-prefix, without the tilde,  consists of a number without a leading "+" or "-", "+" is assumed.

If the login name is invalid, or the tilde expansion fails, the word is left unchanged.

Each variable assignment is checked for unquoted tilde-prefixes immediately following a ":" or "=".  In these cases, tilde expansion is also performed.  Consequently, one may use file names with tildes in assignments to `PATH`, `MAILPATH`, and `CDPATH`, and the shell assigns the expanded value.

Example:

```
franky ~> **export `PATH`=`\*"$PATH:~/testdir"\*`** 
```

`~/testdir` will be expanded to `$HOME``/testdir`, so if `$HOME` is `/var/home/franky`, the directory `/var/home/franky/testdir` will be added to the content of the `PATH` variable.

# Parameter and variable expansion

The `$` character introduces parameter expansion, command substitution, or  arithmetic expansion.  The parameter name or symbol to be expanded may  be enclosed in braces, which are optional but serve to protect the  variable to be expanded from characters immediately following it which  could be interpreted as part of the name.

The basic form of parameter expansion is 

```shell
${PARAMETER}
```

The value of `PARAMETER` is substituted.  The braces are required when `PARAMETER` is a positional parameter with more than one digit, or when `PARAMETER` is followed by a character that is not to be interpreted as part of its name.

If the first character of `PARAMETER` is an exclamation point,  Bash uses the value of the variable formed from the rest of "PARAMETER" as the name of the variable; this variable is then expanded and that  value is used in the rest of the substitution, rather than the value of "PARAMETER" itself.  This is known as *indirect expansion*.

You are certainly familiar with straight parameter expansion, since it  happens all the time, even in the simplest of cases, such as the one  above or the following:

```
$ echo $SHELL
/bin/bash 
```

The following is an example of indirect expansion:

```text
$ echo ${!N*}
NNTPPORT NNTPSERVER NPX_PLUGIN_PATH 
```

Note that this is not the same as **echo `$N\*`**.

The following construct allows for creation of the named variable if it does not yet exist:

```shell
${VAR:=value}
```



Example:

```
$ echo $FRANKY

$ echo ${FRANKY:=Franky}
Franky 
```

Special parameters, among others the positional parameters, may not be assigned this way, however.

We will further discuss the use of the curly braces for treatment of variables in [Chapter 10](https://tldp.org/LDP/Bash-Beginners-Guide/html/chap_10.html).  More information can also be found in the Bash info pages.

# Command substitution

Command substitution allows the output of a command to replace the command itself.  Command substitution occurs when a command is enclosed like this:

```
$(command)
```

or like this using backticks:

```
`command`
```



Bash performs the expansion by executing COMMAND and replacing the command  substitution with the standard output of the command, with any trailing  newlines deleted.  Embedded newlines are not deleted, but they may be  removed during word splitting.

example:

```shell
for file in $(ls)
...
```

```shell
#!/bin/sh
echo "The current directory is $PWD"
echo "The current directory is $(pwd)"
exit 0
```

# Arithmetic expansion

Arithmetic expansion allows the evaluation of an arithmetic  expression and the substitution of the result.  The format for  arithmetic expansion is:

```shell
$(( EXPRESSION ))
```

The expression is treated as if it were within double quotes, but a double quote inside the parentheses is not treated specially.  

All tokens in  the expression undergo parameter expansion, command substitution, and  quote removal.  Arithmetic substitutions may be nested.

Evaluation of arithmetic expressions is done in fixed-width integers with no check for overflow - although division by zero is trapped and recognized as  an error.  The operators are roughly the same as in the C programming  language.  In order of decreasing precedence, the list looks like this:

```shell
#!/bin/sh
x=0
while [[ $x != 10 ]]; do
echo $x
x=$(($x+1)) 
done
exit 0
```

# Process Substitution

`<( CMD )` ： 执行 `CMD` 并将其输出重定向到一个临时文件， 用这个临时文件的名字替换 `<()`

* This is useful when commands expect values to be passed by file instead of by STDIN. 

* For example, `diff <(ls foo) <(ls bar)` will show differences between files in dirs `foo` and `bar`.

## operator

Bourne shell didn't originally have any mechanism to perform simple arithmetic operations but it uses external programs, either **awk** or **expr**.



```shell
#!/bin/sh

val=`expr 2 + 2`
echo "Total value : $val"
```

- There must be spaces between operators and expressions. 
  * `2+2` ： wrong
  * `2 + 2` ： right
- all the conditional expressions should be inside square braces with spaces around them
  *  `[$a==$b]` or `[$a <= $b]`: wrong
  *  `[ $a == $b ]` or `[ $a <= $b ]`: right
- When performing **comparison**s in bash, try to use double brackets `[[ ]]` in favor of simple brackets `[ ]`
- 因为表达式要先执行，因此它必须被包裹在backquote内

# Shell Globbing

*  一些正则操作，用于文件名扩展

  * Wildcards: 

    *  `?`: match **one** character
    *  `*`:  match **any** amount of characters  

    *  For instance, given files `foo`, `foo1`, `foo2`, `foo10` and `bar`, the command `rm foo?` will delete `foo1` and `foo2` whereas `rm foo*` will delete all but `bar`.
* Curly braces `{}` -  相当于笛卡尔积：  `a.{py,cpp,java}`等价于 `a.py a.cpp a.java`

```shell
convert image.{png,jpg}
# Will expand to
convert image.png image.jpg

cp /path/to/project/{foo,bar,baz}.sh /newpath
# Will expand to
cp /path/to/project/foo.sh /path/to/project/bar.sh /path/to/project/baz.sh /newpath

# Globbing techniques can also be combined
mv *{.py,.sh} folder
# Will move all *.py and *.sh files


mkdir foo bar
# This creates files foo/a, foo/b, ... foo/h, bar/a, bar/b, ... bar/h
touch {foo,bar}/{a..h}
touch foo/x bar/y
# Show differences between files in foo and bar
diff <(ls foo) <(ls bar)
# Outputs
# < x
# ---
# > y

```



# Environment virable

shell变量可分为环境变量和自定义变量. **环境变量可以在其进程的子进程中继续有效，而自定义变量则无效.**

使用 `export` 设置的变量就成为了环境变量, 而没有使用 `export` 设置的则是自定义变量.

`$PATH`详见[Shell Script Searching Path]()

****

常见的环境变量:

| 环境变量 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| $HOME    | 当前用户的登陆目录                                           |
| $PATH    | 以冒号分隔的, 由多个路径所组成的, 用来搜索命令的列表         |
| $PS1     | 命令行提示符，通常是”\$”字符 (很多主题都会改掉\$PS1)         |
| $PS2     | 辅助提示符，用来提示后续输入，通常是”>”字符                  |
| $IFS     | 输入区分隔符。当shell读取输入数据时会把一组字符看成是单词之间的分隔符，通常是空格、制表符、换行符等 |





```shell
#我们在当前Shell进程中指定了var1变量
[roc@roclinux ~]$ var1="hello"
[roc@roclinux ~]$ echo $var1
hello

#我们在当前Shell进程中又指定了var2变量
[roc@roclinux ~]$ var2="world"
[roc@roclinux ~]$ echo $var2
world

#我们通过export发布var1
[roc@roclinux ~]$ export var1
 
#我们进入到一个bash子进程中
[roc@roclinux ~]$ bash
 
#var1变量仍然有效, 而var2变量已经无效了
[roc@roclinux ~]$ echo $var1 # 输出变量的值
hello
[roc@roclinux ~]$ echo $var2  # 什么也没有输出
```



# Parameter variable

- `$0` - Name of the script
- `$1` to `$9` - Arguments to the script. `$1` is the first argument and so on.
  * 当`n>=10`时，需要使用$`{n}`来获取参数
- `$@` - 全部参数组成的列表
- `$#` - Number of arguments
- `$?` - Return code of the previous command
- `$*`： 全部参数连接成的字符串，按`$IFS`的第一个字符分割
- `$$` - Process identification number (PID) for the current script
- `!!` - **Entire last command**, including arguments. A common pattern is to execute a command only for it to fail due to missing permissions; you can quickly re-execute the command with sudo by doing `sudo !!`
- `$_` - Last argument from the last command. If you are in an interactive shell, you can also quickly get this value by typing `Esc` followed by `.` or `Alt+.`





