---
title: Linux File
---

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





## File Permission

### chmod

`chmod`: There are two ways to use chmod — the symbolic mode and the absolute mode.

* Using `chmod` in Symbolic Mode

  | Sr.No. |                 Chmod operator & Description                 |
  | :----: | :----------------------------------------------------------: |
  |   1    | **+**Adds the designated permission(s) to a file or directory. |
  |   2    | **-**Removes the designated permission(s) from a file or directory. |
  |   3    |           **=**Sets the designated permission(s).            |

  ```
  $chmod o+wx,u-x,g = rx testfile
  $ls -l testfile
  -rw-r-xrwx  1 amrood   users 1024  Nov 2 00:10  testfile
  ```

  

* Using `chmod` with Absolute Permissions

| Number |              Octal Permission Representation              | Ref  |
| :----: | :-------------------------------------------------------: | :--: |
| **0**  |                       No permission                       | ---  |
| **1**  |                    Execute permission                     | --x  |
| **2**  |                     Write permission                      | -w-  |
| **3**  | Execute and write permission: 1 (execute) + 2 (write) = 3 | -wx  |
| **4**  |                      Read permission                      | r--  |
| **5**  |  Read and execute permission: 4 (read) + 1 (execute) = 5  | r-x  |
| **6**  |    Read and write permission: 4 (read) + 2 (write) = 6    | rw-  |
| **7**  |  All permissions: 4 (read) + 2 (write) + 1 (execute) = 7  | rwx  |

### chown && chgrp

While creating an account on Unix, it assigns a **owner ID** and a **group ID** to each user. 

- **chown** − The **chown** command stands for **"change owner"** and is used to change the owner of a file.
- **chgrp** − The **chgrp** command stands for **"change group"** and is used to change the group of a file.

#### Changing Ownership

The **chown** command changes the ownership of a file. The basic syntax is as follows −

```
$ chown user filelist
```

The value of the user can be either the **name of a user** on the system or the **user id (uid)** of a user on the system.

The following example will help you understand the concept −

```
$ chown amrood testfile
```

Changes the owner of the given file to the user **amrood**.

**NOTE** − The super user, root, has the unrestricted capability to change the ownership of any file but normal users can change the ownership of only those files that they own.

#### Changing Group Ownership

The **chgrp** command changes the group ownership of a file. The basic syntax is as follows −

```
$ chgrp group filelist
```

The value of group can be the **name of a group** on the system or **the group ID (GID)** of a group on the system.

Following example helps you understand the concept −

```
$ chgrp special testfile
$
```

Changes the group of the given file to **special** group.

#### SUID and SGID File Permission

>  Linux系统中,所有账号的密码都记录在 `/etc/shadow` ，它的权限为:『---------- 1 root root』,即仅有 root 可读可写。 然而我们使用`passwd`命令可以查询看和修改自己的密码，这是因为`passwd`设定了SUID使用户可以以root权限执行该程序



Additional permissions are given to programs via a mechanism known as the **Set User ID (SUID)** and **Set Group ID (SGID)** bits.

* 仅对二进制程序(binary program)有效;
  * 这意味着对`shell script`无效
* 执行者对于该程序需要具有 x 的可执行权限;
* 本权限仅在执行该程序的过程中有效 (run-time);
* 执行者将继承该程序拥有者 (owner) 的权限
  * 执行者如果执行没有SUID/SGID bit的程序， 他只拥有自己的权限
  * 对SGID也如此，普通程序只能以用户的group权限执行， SGIG程序会以group owner权限执行



* The SUID and SGID bits will appear as the letter **"s"** if the permission is available. 

  A capital letter **S** in the <u>execute</u> position instead of a lowercase **s** indicates that the execute bit is not set.

  * The SUID **"s"** bit will be located in the permission bits where the owners’ **execute** permission normally resides.

* example:

  ```
  $ ls -l /usr/bin/passwd
  -r-sr-xr-x  1   root   bin  19031 Feb 7 13:47  /usr/bin/passwd*
  $
  ```

  Shows that the SUID bit is set and that the command is owned by the root. 

  

* If the sticky bit is enabled on the directory, files can only be removed if you are one of the following users −

  - The owner of the sticky directory
  - The owner of the file being removed
  - The super user, root

  To set the SUID and SGID bits for any directory try the following command −

  ```
  $ chmod ug+s dirname
  $ ls -l
  drwsr-sr-x 2 root root  4096 Jun 19 06:45 dirname
  $
  ```

#### SBIT

 Sticky Bit, SBIT ： 目录具有 SBIT 时,代表在该目录下用户建立的文件只有自己与 root 能够删除

（ 目前只针对目录有效,对于文件已经没有效果了。SBIT 对于目录的作用是:

* 当用户对于此目录具有 w, x 权限,亦即具有写入的权限时;

* 当用户在该目录下建立文件或目录时,仅有自己与 root 才有权力删除该文件



换句话说:当甲这个用户于 A 目录是具有群组或其他人的身份,并且拥有该目录 w 的权限, 这表
示『甲用户对该目录内任何人建立的目录或文件均可进行 "删除/更名/搬移" 等动作。』 不过,如果
将 A 目录加上了 SBIT 的权限项目时, 则甲只能够针对自己建立的文件或目录进行删除/更名/移动
等动作,而无法删除他人的文件。
举例来说,我们的 /tmp 本身的权限是『drwxrwxrwt』, 在这样的权限内容下,任何人都可以在 /tmp
内新增、修改文件,但仅有该文件/目录建立者与 root 能够删除自己的目录或文件

## umask

`umask` 是目前用户在建立文件或目录时候需要减掉的权限

* `-S`： 以符号形式显示



```shell
❯ umask //表明group和others没有2（写）权限
022

//或者
❯ umask -S 
u=rwx,g=rx,o=rx

```

## chattr

Linux文件/目录有隐藏属性， 用`lsattr`可以看到。 `chattr`可以编辑隐藏属性



```shell
//Make a file or directory immutable to changes and deletion, even by superuser:
    chattr +i path/to/file_or_directory

//Make a file or directory mutable:
    chattr -i path/to/file_or_directory

//Recursively make an entire directory and contents immutable:
    chattr -R +i path/to/directory
```





# File time

每个文件都有三个时间参数：

* modification time (`mtime`):
  当该文件的『内容数据』变更时,就会更新这个时间!内容数据指的是文件的内容,而不是文件的属性或权限
* status time (`ctime`):
  当该文件的『状态 (status)』改变时,就会更新这个时间,比如权限与属性被更改
* access time (`atime`):
  当『该文件的内容被取用』时,就会更新这个读取时间 (access)

使用`ls -l --time=[ctime]`查看文件时间， 使用`touch`修改文件时间
