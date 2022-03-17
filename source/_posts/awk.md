---
title: awk
tags: awk
categories: Language
date: 2022-02-08 18:13:53
---




`awk` is a an **interpreted** programming language that is good at **processing text streams**

ref: [awk tutorial](https://www.tutorialspoint.com/awk/index.htm)

<!--more-->

# AWK

## workflow

![](https://www.tutorialspoint.com/awk/images/awk_workflow.jpg)

* Read

  AWK reads a line from the input stream (file, pipe, or stdin) and stores it in memory.

* Execute

  All AWK commands are applied sequentially on the input. By default AWK execute commands on every line. We can restrict this by providing patterns.

* Repeat

  This process repeats until the file reaches its end.

## Program Structure

Let us now understand the program structure of AWK.

### Body Block

The syntax of the body block is as follows −

**Syntax**

```
/pattern/ {awk-commands}
```

`awk` programs take the form of an optional **pattern** plus a **block** saying what to do if the pattern matches a given line. 

* The default pattern (which we used above) matches all lines

* pattern不仅可以是REGEX，还可以是条件表达式：

  ```shell
  # 输出奇数行
  $ awk -F ':' 'NR % 2 == 1 {print $1}' demo.txt
  ```

  

* In the absence of a body block − default action is taken which is **print** the line.

* Inside the block, 

  * `$0` :  entire line’s contents, and
  * `$1` through `$n` :  the `n`th *field* of that line,
    * fields are separated by the `awk` field separator, (whitespace by default, change with `-F`)

### BEGIN && END block

this block is optional.

**Syntax**

```awk
BEGIN {awk-commands}
END {awk-commands}
```

* The BEGIN block gets executed at program start-up.  

* The END block executes at the end of the program

* 属于 AWK keyword， 必须大写



===================================>

* examole:

  ```shell
  | awk '$1 == 1 && $2 ~ /^c[^ ]*e$/ { print $2 }' | wc -l
  ```

  * The pattern says that the first field of the line should be equal to 1 (that’s the count from `uniq -c`), and that the second field should match the given regular expression. And the block just says to print the username.
  * We then count the number of lines in the output with `wc -l`.

## command line

* ark command 必须用单引号括起来

```awk
awk [options] 'command' target_file
```

## program File

We can provide AWK commands in a script file 

```awk
awk [options]-f source_code_file  target_file
```

## standard options

* `-v`:  assigns a value to a variable. It allows assignment before the program execution.

  ```awk
  $ awk -v name=Jerry 'BEGIN{printf "Name = %s\n", name}'
  ```

* `--dump-variables[=file]`:  prints a sorted list of global variables and their final values to file. The default file is `awkvars.out`

  ```awk
  $ awk --dump-variables ''
  $ cat awkvars.out 
  ```

* `--help`

* `--lint[=fatal]` :  enables checking of non-portable or dubious constructs. When an argument **fatal** is provided, it treats warning messages as errors

* `-posix option`:   turns on strict POSIX compatibility, in which all common and gawk-specific extensions are disabled

* `--profile[=file]`: generates a pretty-printed version of the program in file. Default file is `awkprof.out`

  example:

  ```shell
  [jerry]$ awk --profile 'BEGIN{printf"---|Header|--\n"} {print} 
  END{printf"---|Footer|---\n"}' marks.txt > /dev/null 
  [jerry]$ cat awkprof.out
  ```

  output:

  ```
  # gawk profile, created Sun Oct 26 19:50:48 2014
  
     # BEGIN block(s)
  
     BEGIN {
        printf "---|Header|--\n"
     }
  
     # Rule(s) {
        print $0
     }
  
     # END block(s)
  
     END {
        printf "---|Footer|---\n"
     }
  ```

* `--traditional` :  disables all gawk-specific extensions.

## variable

* awk变量不需要定义和声明，可以直接使用，初始值为`0`

```awk
[jerry]$ awk '/a/{++cnt} END {print "Count = ", cnt}' marks.txt
```

* built-in variables:

  * `ARGC`

  * `ARGV`

  * `CONVFMT`: It represents the conversion format for numbers. Its default value is `%.6g`

  * `ENVIRON`: It is an associative array of environment variables.

    `awk 'BEGIN { print ENVIRON["USER"] }'`

  * `FILENAME`: 当前处理的文件名

  * `FS`: 字段分隔符，默认是空格和制表符, 可以用`-F`更改

    `awk 'BEGIN {print "FS = " FS}' | cat -vte`

  * `NF`: 表示当前行的字段数，因此`$NF`就代表最后一个字段。

    `echo -e "One Two\nOne Two Three\nOne Two Three Four" | awk 'NF > 2'`

    ```bash
    $ echo 'this is a test' | awk '{print $NF}'
    test
    ```

  * `NR`：表示当前处理的行号

  * `OFMT`: It represents the output format number and its default value is `%.6g`.

  * `OFS`:  输出字段的分隔符，用于打印时分隔字段，默认为空格。

    `awk 'BEGIN {print "OFS = " OFS}' | cat -vte`

  * `ORS`:  输出记录的分隔符，用于打印时分隔记录，默认为换行符。

    

## REGEX

与其他语言的regex相同

```shell
echo -e "Apple Juice\nApple Pie\nApple Tart\nApple Cake" | awk 
   '/Apple (Juice|Cake)/'
   
#output：
Apple Juice
Apple Cake
```

## Array

* assign : `array_name[index] = value`

  * 不需要定义或声明
  * `index`可以是`string`或`number`

* Creating Array

  ```awk
  [jerry]$ awk 'BEGIN {
     fruits["mango"] = "yellow";
     fruits["orange"] = "orange"
     print fruits["orange"] "\n" fruits["mango"]
  }'
  
  #output
  orange
  yellow
  ```

* Deleting Array Elements

  ```
  delete array_name[index]
  ```

* Multi-Dimensional arrays

  `array_name[index, index] = value`

## control flow

与其他语言同

* `if`

  ```
  if (condition)
     action
  ```

  ```shell
  [jerry]$ awk 'BEGIN {num = 10; if (num % 2 == 0) printf "%d is even number.\n", num }'
  ```



* `if-else`

  ```
  if (condition)
     action-1
  else
     action-2
  ```

  ```shell
  [jerry]$ awk 'BEGIN {
     num = 11; if (num % 2 == 0) printf "%d is even number.\n", num; 
        else printf "%d is odd number.\n", num 
  }'
  ```



* `if -else if`

  ```shell
  [jerry]$ awk 'BEGIN {
     a = 30;
     
     if (a==10)
     print "a = 10";
     else if (a == 20)
     print "a = 20";
     else if (a == 30)
     print "a = 30";
  }'
  
  ```

  

## loop

* `for`

  ```shell
  [jerry]$ awk 'BEGIN { for (i = 1; i <= 5; ++i) print i }'
  ```

* `while`

  ```shell
  [jerry]$ awk 'BEGIN {i = 1; while (i < 6) { print i; ++i } }'
  ```

## built-in function

### arithmetic function

- `sin()`：正弦。
- `cos()`：余弦。
- `sqrt()`：平方根。
- `rand()`：随机数。

### string function

* `length(arg)`

  ```awk
  [jerry]$ awk 'length($0) > 18' marks.txt
  ```



* ` print item1，item,...`

  各项目间使用逗号分隔开，而输出时以`OFS`为分隔

* `printf "format", expr,expr,... `

  ```awk
  [jerry]$ awk 'BEGIN {
     param = 1024.0
     result = sqrt(param)
     
     printf "sqrt(%f) = %f\n", param, result
  }'
  ```



* `asort(arr [, d [, how] ])`

  This function sorts the contents of **arr** using GAWK's normal rules for comparing values, and replaces the indexes of the sorted values **arr** with sequential integers starting with 1.

  

  ```
  [jerry]$ awk 'BEGIN {
     arr[0] = "Three"
     arr[1] = "One"
     arr[2] = "Two"
     print "Array elements before sorting:"
     
     for (i in arr) {
        print arr[i]
     }
     asort(arr)
     print "Array elements after sorting:"
     
     for (i in arr) {
        print arr[i]
     }
  }'
  
  #Output
  Array elements before sorting:
  Three
  One
  Two
  Array elements after sorting:
  One
  Three
  Two
  ```



* `asorti(arr [, d [, how] ])`

  The behavior of this function is the same as that of **asort()**, except that the array indexes are used for sorting.

  ```
  [jerry]$ awk 'BEGIN {
     arr["Two"] = 1
     arr["One"] = 2
     arr["Three"] = 3
     asorti(arr)
     print "Array indices after sorting:"
     
     for (i in arr) {
        print arr[i]
     }
  }'
  
  #Output
  Array indices after sorting:
  One
  Three
  Two
  ```





* `gsub(regex, sub, string)`

  global substitution. It replaces every occurrence of regex with the given string (sub). The third parameter is optional. If it is omitted, then $0 is used.

  

  ```
  [jerry]$ awk 'BEGIN {
     str = "Hello, World"
     print "String before replacement = " str
     
     gsub("World", "Jerry", str)
     print "String after replacement = " str
  }'
  
  #output
  String before replacement = Hello, World
  String after replacement = Hello, Jerry
  ```

  

  

* `match(str, regex)`
  It returns the index of the first longest match of regex in string str. It returns 0 if no match found.

  ```awk
  [jerry]$ awk 'BEGIN {
       str = "One Two Three"
       subs = "Two"
       ret = match(str, subs)
  
     printf "Substring \"%s\" found at %d location.\n", subs, ret
  }'
  On executing this code, you get the following result −
  
  #Output
  Substring "Two" found at 5 location
  
  
  ```

  


* `split(str, arr, regex)`

  splits the string **str** into fields by regular expression **regex** and the fields are loaded into the array **arr**. If **regex** is omitted, then FS is used.

  ```awk
  [jerry]$ awk 'BEGIN {
     str = "One,Two,Three,Four"
     split(str, arr, ",")
     print "Array contains following values"
     
     for (i in arr) {
        print arr[i]
     }
  }'
  
  #output
  Array contains following values
  One
  Two
  Three
  Four
  ```

* `strtonum(str)`

  This function examines **str** and return its numeric value. If str begins with a leading 0, it is treated as an octal number. If str begins with a leading 0x or 0X, it is taken as a hexadecimal number. Otherwise, assume it is a decimal number.

  

  ```
  [jerry]$ awk 'BEGIN {
     print "Decimal num = " strtonum("123")
     print "Octal num = " strtonum("0123")
     print "Hexadecimal num = " strtonum("0x123")
  }'
  
  #output
  Decimal num = 123
  Octal num = 83
  Hexadecimal num = 291
  ```



* `sub(regex, sub, string)`

  This function performs a single **substitution**. It replaces the first occurrence of the regex pattern with the given string (sub). The third parameter is optional. If it is omitted, $0 is used.

* `substr(str, start, l)`

  This function returns the substring of string **str**, starting at index **start** of length **l**. If length is omitted, the suffix of **str** starting at index **start** is returned.

* `tolower()`：字符转为小写

## user-defined functions

```awk
function function_name(argument1, argument2, ...) { 
   function body
}
```



example

```awk
# Returns minimum number
function find_min(num1, num2){
   if (num1 < num2)
   		return num1
   return num2
}
```

## redirection

Redirections in AWK are written just like redirection in shell commands, except that they are written inside the AWK program

## pretty printing

* Horizontal Tab

  ```shell
  [jerry]$ awk 'BEGIN { printf "Sr No\tName\tSub\tMarks\n" }'
  
  #output
  #Sr No   Name    Sub Marks
  ```

* Backspace

  `\b`删除前一个字符

  ```shell
  [jerry]$ awk 'BEGIN { printf "Field 1\bField 2\bField 3\bField 4\n" }'
  
  #Output
  #Field Field Field Field 4
  ```

  On executing this code, you get the following result −

* Format Specifier

  同其他语言
