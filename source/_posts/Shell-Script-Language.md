---
title: Shell Script Language
tags: shell
categories: Language
date: 2022-03-17 17:06:52
---

The  basic grammer of shell script.

ref:  [shell tutorial](https://www.tutorialspoint.com/unix/unix-shell-functions.htm)

 <!--more-->

# Intro

不同的Shell实现会有不同的方言，不过这很少见。 这里只介绍最标准的Shell Script语法，, 能够被最常用的Shell(如Bash)接受

# Variable

* assign variables in bash:  `foo=bar` 
  * Note that `foo = bar` will not work since it is interpreted as calling the `foo` program with arguments `=` and `bar`. In general, in shell scripts <u>the space character will perform argument splitting.</u>
    * 因此不要加空格
  
* access the value of the variable:  `$foo`
  * 等价于 `${foo}`， 花括号可以精确地界定变量名称的范围。
  
* 可以用`read`命令从标准输入接受数据并赋值:`read val`
  
  example:
  
  ```shell
  #! /usr/bin/env bash
  echo -n "Enter your name:"
  read name
  echo "hello $name"
  exit 0
  ```
  
  

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

# 常见语法

## 条件语句

* As with most programming languages, bash supports control flow techniques including `if`, `case`, `while` and `for`. 

### if

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



紧凑形式： `; ` (同一行上多个命令的分隔符)



example:

```bash
if [ -f ~/.bashrc ]; then 
. ~/.bashrc fi
```

```shell
#!/bin/sh
read -p "Is this morning? Please answer yes or no: " answer
if [ "$answer" = "yes" ]; then
 echo “Good morning”
elif [ "$answer" = "no" ]; then
 echo “Good afternoon” 
else
 echo “Sorry, $answer not recognized. Enter yes or no”
 exit 1 
fi
exit 0
```





### case

syntax:

```shell
case word in
   pattern1 | pattern2)
      Statement(s) to be executed if pattern1 matches
      ;;
   pattern3)
      Statement(s) to be executed if pattern2 matches
      ;;
   pattern4)
      Statement(s) to be executed if pattern3 matches
      ;;
   *)
     Default condition to be executed
     ;;
esac
```





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

```shell
#!/bin/sh

read -p "Is this morning? Please answer yes or no." answer
case "$answer" in
    yes | y | Yes | YES) 
        echo “Good morning!” 
        ;; 
    no | n | No | NO) 
        echo “Good afternoon!” 
        ;; 
    *)
        echo “Sorry, $answer not recognized.” 
        ;;
esac 
exit 0
```







### select in && case in

select in语句自带循环

```
select variable in value_list
do
  statements
done
```

* variable: 表示变量
* value_list:  取值列表
* in:  Shell关键字

**select in 通常和 case in 一起使用，在用户输入不同的编号时可以做出不同的反应**



example:

```shell
#!/bin/sh
clear
select item in Continue Finish
do
    case "$item" in
    Continue) 
        ;;
    Finish) 
        break 
        ;;
    *) 
        echo "Wrong choice! Please select again!" 
        ;;
    esac 
done
```

该命令的while版本：

```shell
while [ "$item" != "Finish" ]; 
do 
    read item
    case "$item" in
        "Continue") 
            ;;
        "Finish")
            ;;
        *) echo "Wrong choice! Please select again!"
            ;;
    esac 
done
```

## 循环语句

`break`: 从for/while/until循环退出



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

```shell
for f in *.png             
do
	mv -n $f $f.kk
done
```



### while

syntax:

```shell
while condition 
do
	statements 
done
```



example:

```shell
quit=n
while [ "$quit" != "y" ]; do read menu_choice
case "$menu_choice" in
a) echo "a, continue...";;
b) echo "b, continue...";;
q|Q) quit=y;;
*) echo "Sorry, choice not recognized.";;
esac done
```

```shell
a=0
LIMIT=10
while [ $a -le $LIMIT ] 
do
    a=$(($a+1))
        if [ $a -gt 2 ] 
        then
            break # Skip entire rest of loop. 
        fi
    echo -n "$a"
done
```

## 命令组合

分号串联：

```sh
command1 ; command2 ; ...
```

 

条件组合:
```sh
statement1 && statement2 && statement3 && ...
```

```sh
statement1 || statement2 || statement3 ||
```

## 语句块

```
{
	statement1 
	statement2 
	...
}
```

 或

```
{ 
	statement1; statement2 ; ... ; 
}
```



test expression 或 `[ expression ]`

* `[` (aka `test`) command the and `[[ ... ]]` test construct are used to evaluate expressions
* `[`是一条命令， 与`test`等价，大多数shell都支持。在现代的大多数sh实现中，`[`与`test`是builtin命令

  * `[]`将其operand直接当作argument
* `[[`，是关键字，许多shell(如ash bsh)并不支持这种方式

  * `[[]]`将其operand进行参数引用，算术扩展和CMD substitution， 不需要手动转义等



## test

test expression:

```
test 1 -lt 2
echo $?
0
test 1 -gt 2
echo $?
1
```



`[ expression ]`:

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



### 与文件有关的条件测试

文件测试运算符的形式及功能

| option | parameter  | function                                                     |
| ------ | ---------- | ------------------------------------------------------------ |
| -r     | 文件名     | 如文件存在并且是用户可读的，则测试条件为真                   |
| -w     | 文件名     | 如文件存在并且是用户可写的，则测试条件为真                   |
| -x     | 文件名     | 如文件存在并且是用户可执行的，则测试条件为真                 |
| -f     | 文件名     | 如文件存在并且是普通文件，则测试条件为真                     |
| -d     | 文件名     | 如文件存在并且是目录文件，则测试条件为真                     |
| -p     | 文件名     | 如文件存在并且是命名的FIFO文件，则测试条件为真               |
| -b     | 文件名     | 如文件存在并且是块特殊文件，则测试条件为真                   |
| -c     | 文件名     | 如文件存在并且是字符特殊文件，则测试条件为真                 |
| -s     | 文件名     | 如文件存在并且文件长度大于0，则测试条件为真                  |
| -t     | 文件描述符 | 如文件被打开且文件描述符是与终端设备相关的，则测试条件为真，默认文件描述符是1 |
|        |            |                                                              |

### 字符串测试	

| option | parameter | function                                     |
| ------ | --------- | -------------------------------------------- |
| -z     | s1        | 如果字符串s1的长度为0，则测试条件为真        |
| -n     | s1        | 如果字符串s1的长度大于0，则测试条件为真      |
|        | s1        | 如果字符串s1不是空字符串，则测试条件为真     |
| =或==  | s1=s2     | 如果s1等于s2，则测试条件为真,“=”前后应有空格 |
| !=     | s1!=s2    | 如果s1不等于s2，则测试条件为真               |
| <      | s1<s2     | 如果按字典顺序s1在s2之前，则测试条件为真     |
| >      | s1>s2     | 如果按自定顺序s1在s2之后，则测试条件为真     |
|        |           |                                              |

### 数值测试

| parameter | function                              |
| --------- | ------------------------------------- |
| n1 -eq n2 | 如果整数n1等于n2，则测试条件为真      |
| n1 -ne n2 | 如果整数n1不等于n2，则测试条件为真    |
| n1 -lt n2 | 如果如果n1小于n2,则测试条件为真       |
| n1 -le n2 | 如果如果n1小于或等于n2,则测试条件为真 |
| n1 -gt n2 | 如果n1大于n2,则测试条件为真           |
| n1 -ge n2 | 如果n1大于或等于n2,则测试条件为真     |
|           |                                       |

### 逻辑操作

| parameter      | function            |
| -------------- | ------------------- |
| ! expr         | 逻辑表达式求反      |
| expr1 –a expr2 | 两个逻辑表达式“And“ |
| expr1 –o expr2 | 两个逻辑表达式“Or“  |

# Function

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

## return

* `exit`: 不仅会退出函数, 还会退出执行该函数的shell
* `return code`:仅仅退出函数. 和command的return code同

## Function Call from Prompt

* 令shell加载函数定义：

  * 可以将函数定义在主目录下的`.profile`，这样每次登陆后，在命令提示符后面输入函数名字就可以立即调用:

    ```shell
    func para1 para2
    ```

    

  * 将函数定义写在一个文件( say  `test.sh` ), 然后执行它

* 令shell删除函数定义：

  ```
  unset -f function_name
  ```

  * 该命令也可用来令shell删除变量定义
  * 反之，`set`可以用来定义变量
  
  output 

* Commands will often return output using `STDOUT`, errors through `STDERR`

## return code

*  Commands have **Return Code** to report errors in a more script-friendly manner. 
   *  **0 usually means everything went OK**; anything different from 0 means an error occurred.
   *  `return code`， 你可以指定返回任何值

### return code as bool value

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


# Substitutions

## CMD substitution

* 命令替换: `$(CMD)`执行命令，并将其输出作为一个变量 

  

  * For example, if you do ``, the shell will first call `ls` and then iterate over those values. 
  

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

## Arithmetic Substitution

`$((...))`

```shell
#!/bin/sh
x=0
while [[ $x != 10 ]]; do
echo $x
x=$(($x+1)) 
done
exit 0
```

## Variable Substitution

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

## Process Substitution

* `<( CMD )` ： 执行 `CMD` 并将其输出重定向到一个临时文件， 用这个临时文件的名字替换 `<()`
  
  * This is useful when commands expect values to be passed by file instead of by STDIN. 
  
  * For example, `diff <(ls foo) <(ls bar)` will show differences between files in dirs `foo` and `bar`.

### operator

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

# Env virable

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
|          |                                                              |





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



# Built-in Commands

Your shell has some *built-in* commands that are executed directly by the shell itself and not looked up in `PATH`, e.g. `echo`, `cd`, `umask`, `pwd`, `history`

```
$ type echo
echo is a shell builtin
```

