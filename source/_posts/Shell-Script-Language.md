---
categories:
- Software Engineering
date: 2022-03-17 17:06:52
tags: Shell
title: Shell Script Language
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

