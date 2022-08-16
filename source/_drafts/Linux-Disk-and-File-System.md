---
title: Linux Disk and File System
tags: Linux
categories: Computer Science
---

# Linux File System

# File System Operations

## Finding files

* `find`:  Find files or directories under the given directory tree, recursively.

  ```shell
  # Find files by extension:
  find root_path -name '*.ext'
  # Find files matching multiple path/name patterns:
  find root_path -path '**/path/**/*.ext' -or -name '*pattern*'
  
  ===========================================
  # Find all directories named src
  find . -name src -type d
  # Find all python files that have a folder named test in their path
  find . -path '*/test/*.py' -type f
  # Find all files modified in the last day
  find . -mtime -1
  # Find all zip files with size in range 500k to 10M
  find . -size +500k -size -10M -name '*.tar.gz'
  ```

* `fd`: An alternative to `find`. 

  ```shell
  #Recursively find files matching the given pattern in the current directory: 
  fd pattern
  
  #ind files that begin with "foo": 
  fd '^foo' 
  
  #Find files with a specific extension: 
  fd --extension txt 
  
  #Find files in a specific directory: 
  fd pattern path/to/directory 
  
  #Include ignored and hidden files in the search: 
  fd --hidden --no-ignore pattern 
  
  #Execute a command on each search result returned: 
  fd pattern --exec command
  ```

  * pattern 遵循metacharacter模式， 即与常规的REGEX不同，`?` 和`* `分别匹配1和任意个数的字符

* `locate`: Find filenames quickly， 使用一个本地数据库` /var/lib/mlocate/`

  ```shell
  #Look for pattern in the database. Note: the database is recomputed periodically (usually weekly or daily):
  locate pattern
  
  #Look for a file by its exact filename (a pattern containing no globbing characters is interpreted as `*pattern*`):
  locate */filename
  
  #Recompute the database. You need to do it if you want to find recently added files:
  sudo updatedb
  
  ```

  * `locate` uses a database that is updated using [`updatedb`](https://www.man7.org/linux/man-pages/man1/updatedb.1.html). In most systems, `updatedb` is updated daily via [`cron`](https://www.man7.org/linux/man-pages/man8/cron.8.html)

* `whick` : 从环境变量中搜索

* `whereis`: 从一些目录中搜索，主要是`/usr/bin`, `/etc`等

  * `whereis -l` : 查看到底在哪些目录下进行了搜索



## Finding code

* `grep`:

  * **-C** NUM, **-**NUM, **--context=**NUM 
        Print **NUM** lines of output context.  Places a line containing a group separator (**--**) between contiguous groups of matches.  With the **-o** or **--only-matching**  option, this has no effect and a warning is given.

  * **-v**, **--invert-match** 
        Invert the sense of matching, to select non-matching lines.

  * **-R**

    **R**ecursively go into directories and look for files for the matching string.

* `rg`

  ```shell
  # Find all python files where I used the requests library
  rg -t py 'import requests'
  # Find all files (including hidden files) without a shebang line
  rg -u --files-without-match "^#!"
  # Find all matches of foo and print the following 5 lines
  rg foo -A 5
  # Print statistics of matches (# of matched lines and files )
  rg --stats PATTERN
  ```

## Finding shell commands

* `history`
* `CTRL + R`:  In most shells, you can make use of `Ctrl+R` to perform backwards search through your history. After pressing `Ctrl+R`, you can type a **substring** you want to match for commands in your history. As you keep pressing it, you will cycle through the matches in your history
* edit `/etc/[.bash_history or .zhistory].`

## Directory Navigation

* `fasd`
* `auto dump`: AUR package corrupted, 不知道啥时候修好
* File manager:`broot`,`nnn`,`ranger`

# 

# Disk Operations

# mount

# swap

