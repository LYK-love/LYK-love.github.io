---
categories:
- Software Engineering
date: 2022-02-08 18:14:27
title: Data Wrangling
---

Some tools for data wrangling

ref: [MIT lesson](https://missing.csail.mit.edu/2020/data-wrangling/)

<!--more-->

# sed

* `sed` is a “stream editor” that builds on top of the old `ed` editor. In it, you basically give short **commands** for how to modify the file, rather than manipulate its contents directly (although you can do that too). 

  *  one of the most common ones is `s`: substitution
    * ` sed 's/REGEX/SUBSTITUTION/'`： Replace **the first occurrence** of a regular expression in **each line** of a file, and print the result
      * `REGEX`:  the regular expression you want to search for
      * SUBSTITUTION`: the text you want to substitute matching text with
      * `'s/REGEX/SUBSTITUTION/g'`:  Replace **all occurrences** of an extended regular expression in a **file**
  
  ```shell
  ssh myserver journalctl
   | grep sshd
   | grep "Disconnected from"
   | sed 's/.*Disconnected from //'
  ```
  

## REGEX

* REGEX special characters:
  - `.` means “any single character” except newline
  - `*` zero or more of the preceding match
  - `+` one or more of the preceding match
  - `[abc]` any one character of `a`, `b`, and `c`
  - `(RX1|RX2)` either something that matches `RX1` or `RX2`
  - `^` the start of the line
  - `$` the end of the line
* `sed`默认**不转义特殊字符**， 这与其他工具都相反。
  * 使用`-E`开启转义
* `sed`的REGEX是贪婪匹配

## capture groups

* 使用捕获组来进行非贪婪匹配

* Any text matched by a regex surrounded by parentheses is stored in a numbered capture group. These are available in the substitution (and in some engines, even in the pattern itself!) as `\1`, `\2`, `\3`, etc. So:

  ```shell
   | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
  ```

  将输出username

# sort

* `sort` will sort its input
  * default: in lexicographic order
  * `-n`: in numeric order
  * `k, --key=KEYDEF` :sort via a key; KEYDEF gives location and type
    * `KEYDEF` is `F[.C][OPTS][,F[.C][OPTS]]` for **start and stop position**, where F is a **field number** and C a character position in the field; both are origin 1, and the stop posi‐ tion defaults to the line's end.  
    * If neither **-t** nor **-b** is in effect, characters in a field are counted from the beginning of the preceding whitespace.  
    * OPTS  is  one  or more single-letter ordering options `[bdfgiMhnRrV]`, which override global ordering options for that key.  If no key is given, use the entire line as the key.  Use **--debug** to diagnose incorrect key usage.
    * example: `-k1,1`即以第一个field为key排序， 而`-k`1即以第一个field直到行的末尾为key进行排序
      * `,n`:  sort until the `n`th field, where the default is the end of the line
  *  `-r`: sort in reverse order.

# uniq

*  `uniq -c` will collapse consecutive lines that are the same into a single line, prefixed with a count of the number of occurrences

  ```shell
  ssh myserver journalctl
   | grep sshd
   | grep "Disconnected from"
   | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
   | sort | uniq -c
   | sort -nk1,1 | tail -n10
  ```

  对username（sort默认按字典序）排序



# tail

* Display the last part of a file.

# awk

```shell
echo "sfsdfs\n asdfdas" | awk '{print $2}' | paste -sd,
```

*  explain:  for every line, print the contents of the second field,



```awk
BEGIN { rows = 0 }
$1 == 1 && $2 ~ /^c[^ ]*e$/ { rows += $1 }
END { print rows }
```



# paste

* `paste`: Merge lines of files

  * `-s`: join all the lines into a single line, using TAB as delimiter
  * `-d`: using the specified delimiter
  
    * `paste -s -d delimiter file`
  



```shell
ssh myserver journalctl
 | grep sshd
 | grep "Disconnected from"
 | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
 | sort | uniq -c
 | sort -nk1,1 | tail -n10
 | awk '{print $2}' | paste -sd,
```

extract the usernames as a comma-separated list instead of one per line

  

# bc

You can do math directly in your shell using `bc`, a calculator that can read from STDIN! For example, add the numbers on each line together by concatenating them together, delimited by `+`:

```
 | paste -sd+ | bc -l
```

Or produce more elaborate expressions:

```
echo "2*($(data | paste -sd+))" | bc -l
```

You can get stats in a variety of ways

# st

* 优雅简洁的数据处理工具https://github.com/nferraz/st
* 与linux的`st`命令重名，需要改名(如`scal`)

# R

* R is another (weird) programming language that’s great at data analysis and [plotting](https://ggplot2.tidyverse.org/). 

  * 相比之前的工具更重量级

  ````shell
  ssh myserver journalctl
   | grep sshd
   | grep "Disconnected from"
   | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
   | sort | uniq -c
   | awk '{print $1}' | R --no-echo -e 'x <- scan(file="stdin", quiet=TRUE); summary(x)'
  R is another (weird) programming language that’s great at data analysis and
  ````

  `summary` prints summary statistics for a vector, and we created a vector containing the input stream of numbers, so R gives us the statistics we wanted!

# gnuplot

* simple plotting http://www.gnuplot.info/

```shell
ssh myserver journalctl
 | grep sshd
 | grep "Disconnected from"
 | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/'
 | sort | uniq -c
 | sort -nk1,1 | tail -n10
 | gnuplot -p -e 'set boxwidth 0.5; plot "-" using 1:xtic(2) with boxes'
```



# xargs

*  `xargs `： Execute a command with piped arguments coming from another command, a file, etc. 
    The input is treated as a single block of text and split into separate pieces on spaces, tabs, newlines and end-of-file. 

  ```shell
  # Run a command using the input data as arguments: 
  arguments_source | xargs command
  ```

  

* Sometimes you want to do data wrangling to find things to install or remove based on some longer list. The data wrangling we’ve talked about so far + `xargs` can be a powerful combo.

  For example, as seen in lecture, I can use the following command to uninstall old nightly builds of Rust from my system by extracting the old build names using data wrangling tools and then passing them via `xargs` to the uninstaller:

  ```shell
  rustup toolchain list | grep nightly | grep -vE "nightly-x86" | sed 's/-x86.*//' | xargs rustup toolchain uninstall
  ```