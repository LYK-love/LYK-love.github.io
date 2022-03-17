---
title: Shell Script
tags: shell
categories: Language
date: 2022-03-17 17:06:52
---

Outline:

* Variable
* String
* Array
* Quoting Mechanism
* Control Flow
* I/O redirection
* Function
* .....



ref:  [shell tutorial](https://www.tutorialspoint.com/unix/unix-shell-functions.htm)

 <!--more-->



# Shell Script

## Variable

* assign variables in bash:  `foo=bar` 
  * Note that `foo = bar` will not work since it is interpreted as calling the `foo` program with arguments `=` and `bar`. In general, in shell scripts the space character will perform argument splitting
* access the value of the variable:  `$foo`
  * 等价于 `${foo}`， 花括号可以精确地界定变量名称的范围。

## String

* Strings in bash can be defined with `'` and `"` delimiters, but they are not equivalent. 

* Strings delimited with `'` are **literal string**s and will not substitute variable values whereas `"` delimited strings will.

  ```shell
  foo=bar
  echo "$foo"
  # prints bar
  echo '$foo'
  # prints $foo
  ```

## Array

* array initialization −

  ```shell
  array_name=(value1 ... valuen)
  ```

* assign

  ```shell
  array_name[index]=value
  ```

  

* access Array Values

  ```shell
  ${array_name[index]}
  ```

## Quoting Mechanism

### metacharacters

Unix Shell provides various metacharacters which have special meaning while using them in any Shell Script and causes termination of a word unless quoted.

```shell
* ? [ ] ' " \ $ ; & ( ) | ^ < > new-line space tab
```

### quoting

The following table lists the four forms of quoting −

| Sr.No. |                    Quoting & Description                     |
| :----: | :----------------------------------------------------------: |
|   1    | **Single quote**<br/>All special characters between these quotes lose their special meaning. |
|   2    | **Double quote**<br/>Most special characters between these quotes lose their special meaning with these exceptions −$`\$\'\"\\ |
|   3    | **Backslash**<br/>Any character immediately following the backslash loses its special meaning. |
|   4    | **Back quote** (aka **backtick**)<br>Everything you type between backticks is evaluated (executed) by the shell before the main command, and the *output* of that execution is used by that command, |

* The Single Quotes: 其内容不转义, 相当于在每个字符前加 backslash

* The Double Quotes： 其内容转义 

* The Backslash: 取消其后面的一个字符的转义

* The Backquotes：将其内容视作 command 并执行， 与后文的CMD substitution类似

  ```shell
  var=`command`
  ```

  ```shell
  DATE=`date`
  
  echo $DATE
  
  #等价于后文的CMD substitution
  echo $(DATE)
  ```





## Control Flow

* As with most programming languages, bash supports control flow techniques including `if`, `case`, `while` and `for`. 


### if else

syntax:

```shell
if [ expression ] 
then 
   Statement(s) to be executed if expression is true 
fi
```



```shell
if [ expression 1 ]
then
   Statement(s) to be executed if expression 1 is true
elif [ expression 2 ]
then
   Statement(s) to be executed if expression 2 is true
elif [ expression 3 ]
then
   Statement(s) to be executed if expression 3 is true
else
   Statement(s) to be executed if no expression is true
fi
```

### for

syntax：

```shell
for var in word1 word2 ... wordN
do
   Statement(s) to be executed for every word.
done
```



example:

```shell
for FILE in $HOME/.bash*
do
   echo $FILE
done
```





### switch case

syntax:

```shell
case word in
   pattern1)
      Statement(s) to be executed if pattern1 matches
      ;;
   pattern2)
      Statement(s) to be executed if pattern2 matches
      ;;
   pattern3)
      Statement(s) to be executed if pattern3 matches
      ;;
   *)
     Default condition to be executed
     ;;
esac
```

​	

example:

```shell
#!/bin/sh

option="${1}" 
case ${option} in 
   -f) FILE="${2}" 
      echo "File name is $FILE"
      ;; 
   -d) DIR="${2}" 
      echo "Dir name is $DIR"
      ;; 
   *)  
      echo "`basename ${0}`:usage: [-f file] | [-d directory]" 
      exit 1 # Command to come out of the program with status 1
      ;; 
esac 
```

### select in && case in

```
select variable in value_list
do
  statements
done
```

* variable: 表示变量
* value_list:  取值列表
* in:  Shell关键字

select in 通常和 [case in](http://c.biancheng.net/view/2767.html) 一起使用，在用户输入不同的编号时可以做出不同的反应。

修改上面的代码，加入 case in 语句：

```shell
#!/bin/sh
clear
select item in Continue Finish
do
case “$item” in
	Continue) ;;
	Finish) break ;;
	*) echo “Wrong choice! Please select again!” ;;
esac
done
```

用户只有输入正确的编号才会结束循环，如果输入错误，会要求重新输入。

## I/O redirection

* Discard the output

  ```shell
  $ command > /dev/null
  ```

  The file **/dev/null** is a special file that automatically discards all its input.

* Discard both output of a command and its error output,

  ```shell
  $ command > /dev/null 2>&1
  ```

  * a command normally writes its output to **STDOUT**
  * use standard redirection to redirect **STDERR** to **STDOUT** 

* file descriptor:

  * **0** : STDIN
  * **1**: STDOUT
  * **2**: STDERR



| Sr.No. |                    Command & Description                     |
| :----: | :----------------------------------------------------------: |
|   1    | **pgm > file**<br>Output of pgm is redirected to file<br>会覆盖目标文件中原有的数据 |
|   2    |   **pgm < file**<br>Program pgm reads its input from file    |
|   3    |     **pgm >> file**<br>Output of pgm is appended to file     |
|   4    | **n > file**<br>Output from stream with descriptor **n** redirected to file |
|   5    | **n >> file**<br/>Output from stream with descriptor **n** appended to file |
|   6    | **n >& m**<br/>Merges output from stream **n** with stream **m** |
|   7    | **n <& m**<br/>Merges input from stream **n** with stream **m** |
|   8    | **<< tag**<br/>Standard input comes from here through next tag at the start of line |
|   9    | **\|**<br/>Takes output from one program, or process, and sends it to another |

## Function

syntax

```shell
function_name(){
	list of commands
	[ return value ]
}
```



example:

```shell
mcd () {
    mkdir -p "$1"
    cd "$1"
}
```

### parameter

- `$0` - Name of the script
- `$1` to `$9` - Arguments to the script. `$1` is the first argument and so on.
  * 当`n>=10`时，需要使用$`{n}`来获取参数
- `$@` - All the arguments
- `$#` - Number of arguments
- `$?` - Return code of the previous command
- `$$` - Process identification number (PID) for the current script
- `!!` - **Entire last command**, including arguments. A common pattern is to execute a command only for it to fail due to missing permissions; you can quickly re-execute the command with sudo by doing `sudo !!`
- `$_` - Last argument from the last command. If you are in an interactive shell, you can also quickly get this value by typing `Esc` followed by `.` or `Alt+.`

### return code

* `exit`: 不仅会退出函数，还会退出执行该函数的shell
* `return code`:仅仅退出函数。和command的return code同



### Function Call from Prompt

* 令shell加载函数定义：

  * 可以将函数定义在主目录下的`.profile`，这样每次登陆后，在命令提示符后面输入函数名字就可以立即调用
  * 将函数定义写在一个文件( say `test.sh` ), 然后执行它

* 令shell删除函数定义：

  ```
  unset -f function_name
  ```

  * 该命令也可用来令shell删除变量定义

## output 

* Commands will often return output using `STDOUT`, errors through `STDERR`

## return code

*  Commands have **Return Code** to report errors in a more script-friendly manner. 
   *  **0 usually means everything went OK**; anything different from 0 means an error occurred.
   *  `return code`， 你可以指定返回任何值

## return code as bool value

* Return codes can be used to conditionally execute commands using `&&` (and operator) and `||` (or operator) . 

* Commands can also be separated within the same line using a semicolon `;`. 

* The `true` program will always have a **0** return code and the `false` command will always have a 1 return code. 

  ```shell
  false || echo "Oops, fail"
  # Oops, fail
  
  true || echo "Will not be printed"
  #
  
  true && echo "Things went well"
  # Things went well
  
  false && echo "Will not be printed"
  #
  
  true ; echo "This will always run"
  # This will always run
  
  false ; echo "This will always run"
  # This will always run
  ```

  

## CMD substitution

* 命令替换: `$(CMD)`执行命令，并将其输出作为一个变量 

  * For example, if you do `for file in $(ls)`, the shell will first call `ls` and then iterate over those values. 

  

## variable substitution

变量替换可以根据变量的状态（是否为空、是否定义等）来改变它的值

可以使用的变量替换形式：

| 形式            | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| ${var}          | 变量本来的值                                                 |
| ${var:-word}    | 如果变量 var 为空或已被删除(unset)，那么返回 word，但不改变 var 的值。 |
| ${var:=word}    | 如果变量 var 为空或已被删除(unset)，那么返回 word，并将 var 的值设置为 word。 |
| ${var:?message} | 如果变量 var 为空或已被删除(unset)，那么将消息 message 送到标准错误输出，可以用来检测变量 var 是否可以被正常赋值。 若此替换出现在Shell脚本中，那么脚本将停止运行。 |
| ${var:+word}    | 如果变量 var 被定义，那么返回 word，但不改变 var 的值。      |

```shell
#!/bin/sh

echo ${var:-"Variable is not set"}
echo "1 - Value of var is ${var}"

echo ${var:="Variable is not set"}
echo "2 - Value of var is ${var}"

unset var
echo ${var:+"This is default value"}
echo "3 - Value of var is $var"

var="Prefix"
echo ${var:+"This is default value"}
echo "4 - Value of var is $var"

echo ${var:?"Print this message"}
echo "5 - Value of var is ${var}"
```



result:

```shell
Variable is not set
1 - Value of var is
Variable is not set
2 - Value of var is Variable is not set

3 - Value of var is
This is default value
4 - Value of var is Prefix
Prefix
5 - Value of var is Prefix
```

## process substitution

* `<( CMD )` ： 执行 `CMD` 并将其输出重定向到一个临时文件， 用这个临时文件的名字替换 `<()`
  
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

### Arithmetic Operators

Assume variable **a** holds 10 and variable **b** holds 20 then −

|      Operator      |                         Description                          |                Example                |
| :----------------: | :----------------------------------------------------------: | :-----------------------------------: |
|    + (Addition)    |          Adds values on either side of the operator          |      `expr $a + $b` will give 30      |
|  - (Subtraction)   |     Subtracts right hand operand from left hand operand      |     `expr $a - $b` will give -10      |
| * (Multiplication) |       Multiplies values on either side of the operator       |     `expr $a \* $b` will give 200     |
|    / (Division)    |       Divides left hand operand by right hand operand        |      `expr $b / $a` will give 2       |
|    % (Modulus)     | Divides left hand operand by right hand operand and returns remainder |      `expr $b % $a` will give 0       |
|   = (Assignment)   |            Assigns right operand in left operand             | a = $b would assign value of b into a |
|   == (Equality)    |  Compares two numbers, if both are same then returns true.   |   [ $a == $b ] would return false.    |
| != (Not Equality)  | Compares two numbers, if both are different then returns true. |    [ $a != $b ] would return true.    |

* All the arithmetical calculations are done using long **integers**.

### Relational Operators

These operators do not work for **string** values **unless their value is numeric**.

* For example, following operators will work to check a relation between 10 and 20 as well as in between "10" and "20" but not in between "ten" and "twenty".

Assume variable **a** holds 10 and variable **b** holds 20 then −

| Operator |                         Description                          |          Example           |
| :------: | :----------------------------------------------------------: | :------------------------: |
| **-eq**  | Checks if the value of two operands are equal or not; if yes, then the condition becomes true. | [ $a -eq $b ] is not true. |
| **-ne**  | Checks if the value of two operands are equal or not; if values are not equal, then the condition becomes true. |   [ $a -ne $b ] is true.   |
| **-gt**  | Checks if the value of left operand is greater than the value of right operand; if yes, then the condition becomes true. | [ $a -gt $b ] is not true. |
| **-lt**  | Checks if the value of left operand is less than the value of right operand; if yes, then the condition becomes true. |   [ $a -lt $b ] is true.   |
| **-ge**  | Checks if the value of left operand is greater than or equal to the value of right operand; if yes, then the condition becomes true. | [ $a -ge $b ] is not true. |
| **-le**  | Checks if the value of left operand is less than or equal to the value of right operand; if yes, then the condition becomes true. |   [ $a -le $b ] is true.   |

### Boolean Operators

The following Boolean operators are supported by the Bourne Shell.

Assume variable **a** holds 10 and variable **b** holds 20 then −

| Operator |                         Description                          |                Example                |
| :------: | :----------------------------------------------------------: | :-----------------------------------: |
|  **!**   | This is logical negation. This inverts a true condition into false and vice versa. |         [ ! false ] is true.          |
|  **-o**  | This is logical **OR**. If one of the operands is true, then the condition becomes true. | [ $a -lt 20 -o $b -gt 100 ] is true.  |
|  **-a**  | This is logical **AND**. If both the operands are true, then the condition becomes true otherwise false. | [ $a -lt 20 -a $b -gt 100 ] is false. |

### String Operators

The following string operators are supported by Bourne Shell.

Assume variable **a** holds "abc" and variable **b** holds "efg" then −

| Operator |                         Description                          |         Example          |
| :------: | :----------------------------------------------------------: | :----------------------: |
|  **=**   | Checks if the value of two operands are equal or not; if yes, then the condition becomes true. | [ $a = $b ] is not true. |
|  **!=**  | Checks if the value of two operands are equal or not; if values are not equal then the condition becomes true. |  [ $a != $b ] is true.   |
|  **-z**  | Checks if the given string operand size is zero; if it is zero length, then it returns true. |  [ -z $a ] is not true.  |
|  **-n**  | Checks if the given string operand size is non-zero; if it is nonzero length, then it returns true. | [ -n $a ] is not false.  |
| **str**  | Checks if **str** is not the empty string; if it is empty, then it returns false. |   [ $a ] is not false.   |

### File Test Operators

We have a few operators that can be used to test various properties associated with a Unix file.

Assume a variable **file** holds an existing file name "test" the size of which is 100 bytes and has **read**, **write** and **execute** permission on −

|  Operator   |                         Description                          |          Example          |
| :---------: | :----------------------------------------------------------: | :-----------------------: |
| **-b file** | Checks if file is a block special file; if yes, then the condition becomes true. |  [ -b $file ] is false.   |
| **-c file** | Checks if file is a character special file; if yes, then the condition becomes true. |  [ -c $file ] is false.   |
| **-d file** | Checks if file is a directory; if yes, then the condition becomes true. | [ -d $file ] is not true. |
| **-f file** | Checks if file is an ordinary file as opposed to a directory or special file; if yes, then the condition becomes true. |   [ -f $file ] is true.   |
| **-g file** | Checks if file has its set group ID (SGID) bit set; if yes, then the condition becomes true. |  [ -g $file ] is false.   |
| **-k file** | Checks if file has its sticky bit set; if yes, then the condition becomes true. |  [ -k $file ] is false.   |
| **-p file** | Checks if file is a named pipe; if yes, then the condition becomes true. |  [ -p $file ] is false.   |
| **-t file** | Checks if file descriptor is open and associated with a terminal; if yes, then the condition becomes true. |  [ -t $file ] is false.   |
| **-u file** | Checks if file has its Set User ID (SUID) bit set; if yes, then the condition becomes true. |  [ -u $file ] is false.   |
| **-r file** | Checks if file is readable; if yes, then the condition becomes true. |   [ -r $file ] is true.   |
| **-w file** | Checks if file is writable; if yes, then the condition becomes true. |   [ -w $file ] is true.   |
| **-x file** | Checks if file is executable; if yes, then the condition becomes true. |   [ -x $file ] is true.   |
| **-s file** | Checks if file has size greater than 0; if yes, then condition becomes true. |   [ -s $file ] is true.   |
| **-e file** | Checks if file exists; is true even if file is a directory but exists. |   [ -e $file ] is true.   |

## test

* `[` (aka `test`) command the and `[[ ... ]]` test construct are used to evaluate expressions
* `[`是一条命令， 与`test`等价，大多数shell都支持。在现代的大多数sh实现中，`[`与`test`是builtin命令

  * `[]`将其operand直接当作argument
* `[[`，是关键字，许多shell(如ash bsh)并不支持这种方式

  * `[[]]`将其operand进行参数引用，算术扩展和CMD substitution， 不需要手动转义等

```shell
echo "Starting program at $(date)" # Date will be substituted

echo "Running program $0 with $# arguments with pid $$"

for file in "$@"; do
    grep foobar "$file" > /dev/null 2> /dev/null
    # When pattern is not found, grep has exit status 1
    # We redirect STDOUT and STDERR to a null register since we do not care about them
    if [[ $? -ne 0 ]]; then
        echo "File $file does not have any foobar, adding one"
        echo "# foobar" >> "$file"
    fi
done
```

## shell globbing

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

## env virable

`$PATH` 是由多个路径所组成的，并且用冒号进行了分隔

使用 export 设置的变量就成为了环境变量，而没有使用 export 设置的则是自定义变量

环境变量可以在其进程的子进程中继续有效，而自定义变量则无效

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



```shell
export PATH=$PATH:/home/to/operation_tools
```

* 声明环境变量PATH, 值为之前的`PATH`的值（采用`$`进行赋值）， 再append `:/home/to/operation_tools`， 这里要append冒号，因为环境变量之间通过冒号隔开

## scripts

### shebang

Note that scripts need not necessarily be written in bash to be called from the terminal. For instance, here’s a simple Python script that outputs its arguments in reversed order:

```shell
#!/usr/local/bin/python
import sys
for arg in reversed(sys.argv[1:]):
    print(arg)
```

* shebang: the character sequence consisting of `#!` at the beginning of a script in   a [Unix-like](https://en.wikipedia.org/wiki/Unix-like) operating system

  * shell会将shebang中`#!`之后的内容作为一个程序的路径，打开该程序， 将本script的路径当作参数传入（ 即，将整个script当作input传入shebang所指定的程序 ）

  

  * For example, if a script is named with the path *path/to/script*, and it starts with the following line, `#!/bin/sh`, then the program loader is instructed to run the program */bin/sh*, passing *path/to/script* as the first argument. In [Linux](https://en.wikipedia.org/wiki/Linux), this behavior is the result of both kernel and user-space code.[[9\]](https://en.wikipedia.org/wiki/Shebang_(Unix)#cite_note-9)

  * The shebang line is usually ignored by the interpreter, because the "#" character is a [comment](https://en.wikipedia.org/wiki/Comment_(computer_programming)) marker in many scripting languages; some language interpreters that do not use the hash mark to begin comments still may ignore the shebang line in recognition of its purpose.

### shebang with env

The shebang expects a full path to the interpreter to use so the following syntax would be incorrect:

```py
#!python
```

Setting a full path like this might work:

```py
#!/usr/local/bin/python
```

but would be non portable as python might be installed in `/bin`, `/opt/python/bin`, or wherever other location.

Using `env`

```py
#!/usr/bin/env python
```

is a method allowing a portable way to specify to the OS a full path equivalent to the one where `python` is first located in the `PATH`.

### scripts vs shell functions

Some differences between shell functions and scripts that you should keep in mind are:

- Functions have to be in the same language as the shell, while scripts can be written in any language. This is why including a shebang for scripts is important.
- Functions are loaded once when their definition is read. Scripts are loaded every time they are executed. This makes functions slightly faster to load, but whenever you change them you will have to reload their definition.
- Functions are executed **in the current shell environment**( 可以简单理解为， function的所在路径是当前路径 ) whereas scripts execute in their own process. Thus, functions can modify environment variables, e.g. change your current directory, whereas scripts can’t. Scripts will be passed by value environment variables that have been exported using [`export`](https://www.man7.org/linux/man-pages/man1/export.1p.html)
- As with any programming language, functions are a powerful construct to achieve modularity, code reuse, and clarity of shell code. Often shell scripts will include their own function definitions.
