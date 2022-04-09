---
title: OS Persistence
tags: OS Basic
categories: Computer Science
mathjax: true
date: 2022-04-04 01:36:01
---



Outline:

* I/O Devices
* File
* File System
* Locality and FFS
* Crush-Consistency Problem
* VFS



Ref: *OSTEP*

<!--more-->



# I/O Devicecs

![IO Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/IO%20Arch.png)

* CPU通过内存总线连接到内存
* 图像和其他高性能IO设备连接到常规的IO总线（如PCI）
* 最慢的设备，如键盘、鼠标等，连接到外围总线

## I/O系统各层软件及其功能

![IO Layers](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/IO%20Layers.png)

# RAID

略

# File

* 进程是虚拟化的CPU, 地址空间是虚拟化的内存， 而文件和目录就是虚拟化的外部存储设备
* 文件：线性字节数组，每个文件都有一个低级名称：`inode number`
* 目录：目录是特殊的文件，本身也有低级名称`inode number`，其内容为`（用户可读名字， 低级名称）`对的列表。 
  * 目录的每个对，即每个条目`dentry`，都指向文件或其他目录
  * 目录层次结构从根目录`/`开始

![File Structure](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/IO%20Layers.png)

## File types

从细节来说，文件类型分为:

* regular file 
* character special file 
* block special file 
* fifo 
* socket 
* symbolic link 
* directory (  目录也是一种文件，我们只是把目录和文件分开讨论 )

## File  Structure

File  Structure:

* Byte stream; 
* no particular internal structure

## Unbuffered I/O & Buffered I/O

* Unbuffered I/O:
  * read/write ->System calls 
  * File descriptor 
  * Not in ANSI C, but in POSIX.1 and XPG3 
* Buffered I/O 
  * Implemented in standard I/O library (属于库函数，而不是系统调用)
  * 处理很多细节, 如缓存分配, 以优化长度执行I/O等. 
  * Stream -> a pointer to FILE

## Basic I/O System Calls 

* File descriptor 
* Basic I/O:
  * open/creat, close, read, write, lseek 
  * dup/dup2 
  * fcntl
  *  ioctl

## File descriptor

File descriptor:

* A small non-negative integer 
  * `int fd;` 
* **是thread local的**
* 在UNIX中用于访问文件,  也可以将它作为指向文件对象的指针
*  in `<unistd.h>`
  * **STDIN_FILENO: 0**
  * **STDOUT_FILENO : 1**
  * **STDERR_FILENO: 2** 



General steps of file operation: 

1. open
2. read/write
3. [lseek]
4. close

## 文件操作

### open/creat Function

Open and possibly create a file or device

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode); // equivalent to open with flags: O_CREAT|O_WRONLY|O_TRUNC
```

* Return: a new file descriptor if success; -1 if failure

#### Parameter‏”flags” 

“flags”:‏file‏ access‏ mode 

* 定义在 `<fcntl.h>`
*   分为主标志和副标志， 主标志必须，且是互斥的，即只能选择一种。 副标志是可选的，可以选择多个
* 标志之间用`|`隔开



| 主标志       | 含义                     |
| ------------ | ------------------------ |
| **O_RDONLY** | **以只读方式打开文件**   |
| **O_WRONLY** | **以只写方式打开文件**   |
| **O_RDWR**   | **以可读写方式打开文件** |

| 副标志       | 含义                                                         |
| ------------ | ------------------------------------------------------------ |
| **O_TRUNC**  | **若文件存在并且以可写的方式打开时，**此标志会将文件长度清为0，而原来存于该文件的资料也会消失 |
| **O_CREAT**  | **若路径中的文件不存在则自动建立该文件**                     |
| **O_EXCL**   | 如果与O_CREAT同时设置，此指令会去检查文件是否存在，文件若不存在则建立该文件，否则将导致打开文件错误。此外，若O_CREAT与O_EXCL同时设置，并且将要打开的文件为符号链接，则将导致打开文件失败 |
| **O_APPEND** | 读写文件从文件尾部开始移动，所写入的数据追加到文件尾         |

#### Parameter‏: mode

mode:  设定新建的文件的权限,    详见下文《File Permission》

### close Funtion

```c
// Close a file descriptor
#include <unistd.h>
int close(int fd);
(Return: 0 if success; -1 if failure)
```



`open`系统调用：

```c++
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>

int main()
{
    int fd = open("foo", O_CREAT, O_WRONLY | O_TRUNC);
}
```

* `open`返回`file discriptor`,这是一个thread local的整数，在UNIX中用于访问文件。 也可以将它作为指向文件对象的指针

* 打开文件过程：
  1. 检索目录,把它的外存索引节点复制到活动索引节点表。
  2. 根据参数`mode`核对权限,如果非法,则这次打开失败。
  3. 当“打开”合法时,为文件分配用户打开文件表项和系统打开文件表项,并为表项设置初值。通过指针建立这些表项与活动索引节点间的联系。把`fd`,即用户打开文件表中相应文件表项的序号返回给调用者。

* 关闭文件过程：
  1. 根据`fd`找到用户打开文件表项,再找到系统打开文件表项。释放用户打开文件表项。
  2. 把对应系统打开文件表项中的`f_count--`如果非“0”,说明还有进程共享这一表项,不用释放直接返回;否则释放表项
  3. 把活动索引节点中的`i_count --`,若不为“0”,表明还有用户进程正在使用该文件,不用释放而直接返回,否则在把该活动索引节点中的内容复制回文件卷上的相应索引节点中后,释放该活动索引节点。

* f_count和i_count分别反映进程动态地共享一个文件的两种方式,
  * `f_count`反映不同进程通过同一个系统打开文件表项共享
    一个文件的情况;
  * `i_count`反映不同进程通过不同系统打开文件表项共享一
    个文件的情况。
  * 通过两种方式,进程之间既可用相同的位移指针f_offset,
    也可用不同位移指针f_offset共享同一个文件。

### read/write Function

`<unistd.h>`



```c
// Read from a file descriptor
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
(返回值: )

//Write to a file descriptor
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

* 第一个参数为文件描述符
* 第二个参数指向放置结果的缓冲区
* 第三个参数是缓冲区大小
* 返回值：
  * `read()`: 读到的字节数，若已到文件尾为0. 若出错为-1
  * `write()`: 若成功为已写的字节数. 若出错为-1



```c
// myCat.c
while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
{
    if (write(STDOUT_FILENO, buf, n) != n)
		err_sys(“write error”);	
}
if (n<0)
		err_sys(“read error”);

```



#### 例子



使用`strace`跟踪system call

```shell
> echo hello>foo
> strace cat foo 
...
> open("foo", O_RDonly|O_LARGEFILE) //使用64位偏移量（ O_LARGEFILE ）
> read(3, "hello\n", 6  )
> read(3,"",4096)
> close(3)
...
>prompt
```

这是书上的输出，我自己manjaro64的打印结果如下：

```shell
...

openat(AT_FDCWD, "foo", O_RDONLY)       = 3
...
read(3, "hello\n", 131072)              = 6
write(1, "hello\n", 6hello)             = 6
read(3, "", 131072)                     = 0
munmap(0x7f90b3935000, 139264)          = 0
close(3)                                = 0
...
```

省略了一些输出

* `cat`先打开文件准备读取
  * 每个进程已经打开了三个文件： `std input`, `std output`, `std err`,其文件描述符分别为`0`，`1`，`2`。 因此`open`返回`3`

* 打开后，`cat`使用`read()` system call, 

  ```c
  ssize_t read(int fd, void * buf, size_t count);
  ```

  * 第一个参数为文件描述符
  *  第二个参数指向放置结果的缓冲区, `strace`显示了此时的读取结果`hello\n`
  * 第三个参数是缓冲区大小, 在我的电脑上是`139264B`
  * 返回值为其读取的字节数，这里是`6`

* 同样能看到，`write（）`针对文件描述符`1`，这是标准输出。

  * 这是`cat`要做的事，它可能直接调用`write（）`，也可能调用库例程`printf（）`，当然最终还是会调用`write（）`

* 然后，`cat`试图从文件中读取更多内容，但是文件中没有剩余字节，`read（）`返回0

* 程序知道它已经读取完了文件，因此调用`close（）`，传入相应的文件描述符（`3`），该文件因此会关闭

### lseek Function

不按顺序读取和写入



Reposition read/write file offset:

```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fildes, off_t offset, int whence);

```

* Return: the resulting offset location if success; -1 if failure

The ‏directive‏  `whence`:

* SEEK_SET: ‏the‏ offset ‏is ‏set ‏to ‏”offset” ‏bytes
* SEEK_CUR: the offset is set to its current location plus “offset” ‏bytes
* SEEK_END:‏the ‏offset‏ if‏ set ‏to ‏the ‏size‏ of‏ the ‏file ‏plus ‏”offset”‏ bytes



使用`lseek（）`

```c
off_t lseek(int fildes, off_t offset, int whence);
```

可以看到，对每个进程打开的文件，OS都会跟踪一个当前偏移量`offset`。 要么每次读写后隐式更新，要么通过`lssek（）`指定

### dup/dup2 Function

* Duplicate a file descriptor 

  ```c
  #include <unistd.h>
  int dup(int oldfd);
  int dup2(int oldfd, int newfd);
  ```

  * Return: the new file descriptor if success; -1 if failure

* File sharing

  * **Example: redirection**

### fcntl Function

* Manipulate a file descriptor 

  ```c
  #include <unistd.h>
  #include <fcntl.h>
  int fcntl(int fd, int cmd);
  int fcntl(int fd, int cmd, long arg);
  int fcntl(int fd, int cmd, struct flock *lock);
  ```

  * 返回值: 若成功则依赖于`cmd`，若出错为-1

* The ‏operation‏ is ‏determined‏ by ‏`cmd`

#### cmd

* The ‏value ‏of‏ `cmd`:
  * `F_DUPFD`: Duplicate a file descriptor 
  * `F_GETFD`/`F_SETFD`:‏Get/set‏the‏file‏descriptor‟s‏close-onexec flag. 
  * `F_GETFL`/`F_SETFL`:‏Get/set‏the‏file‏descriptor‟s‏flags 
  * `F_GETOWN`/`F_SETOWN`: Manage I/O availability signals 
  * `F_GETLK`/`F_SETLK`/`F_SETLKW`: Get/set the file lock

* Example: 
  * dup/dup2 and fcntl

### ioctl Function

Control devices 

```c
#include  
int ioctl(int d, int request, ...);
```



### fsync Function

```c
#include <unistd.h>

int fsync(int fildes);
```

一般来说， 程序执行`write（）`系统调用时，文件系统会将写入在内存中缓冲一段时间。 要立即写入，需要`fsync（）`

* 强制写回脏数据

### 文件改名

```c
 int rename(char * oldname, char * newname);
```

* `rename（）`是原子操作

### 获取文件信息

```从
int stat(const char * file_name, struct stat *buf);
```

`stat()`用来将参数`file_name` 所指的文件状态, 复制到参数`buf `所指的结构中。

```C++
struct stat
{
  dev_t st_dev; //device 文件的设备编号
  ino_t st_ino; //inode 文件的i-node
  mode_t st_mode; //protection 文件的类型和存取的权限
  nlink_t st_nlink; //number of hard links 连到该文件的硬连接数目, 刚建立的文件值为1.
  uid_t st_uid; //user ID of owner 文件所有者的用户识别码
  gid_t st_gid; //group ID of owner 文件所有者的组识别码
  dev_t st_rdev; //device type 若此文件为装置设备文件, 则为其设备编号
  off_t st_size; //total size, in bytes 文件大小, 以字节计算
  unsigned long st_blksize; //blocksize for filesystem I/O 文件系统的I/O 缓冲区大小.
  unsigned long st_blocks; //number of blocks allocated 占用文件区块的个数, 每一区块大小为512 个字节.
  time_t st_atime; //time of lastaccess 文件最近一次被存取或被执行的时间, 一般只有在用mknod、utime、read、write 与tructate 时改变.
  time_t st_mtime; //time of last modification 文件最后一次被修改的时间, 一般只有在用mknod、utime 和write 时才会改变
  time_t st_ctime; //time of last change i-node 最近一次被更改的时间, 此参数会在文件所有者、组、权限被更改时更新
};
```



* shell中可以用`stat`工具

```shell
stat far
  File: far
  Size: 6               Blocks: 8          IO Block: 4096   regular file
Device: 259,8   Inode: 2536724     Links: 1
Access: (0777/-rwxrwxrwx)  Uid: ( 1000/     lyk)   Gid: ( 1001/     lyk)
Access: 2021-11-26 21:31:56.163748288 +0800
Modify: 2021-11-26 21:41:07.306528022 +0800
Change: 2021-11-26 21:59:32.375301046 +0800
 Birth: 2021-11-26 21:31:56.163748288 +0800

```

### 删除文件

shell命令`rm`使用`unlink（）`系统调用删除文件：

```c
int unlink(const char * pathname);
```

####  change ownership

Change ownership of a file

```C
#include <sys/types.h>
#include <unistd.h>
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
```

* Return: 0 if success; -1 if failure

### 目录操作

仅仅列举函数名:

* `mkdir / rmdir`
* `chdir/fchdir, getcwd`
* Read a directory：
  * `opendir/closedir`
  * `readdir `
  * `telldir `
  * `seekdir`

#### Data structures

* `DIR`: The data type of directory stream objects

  * `<dirent.h>`:

    ```c
    typedef struct __dirstream DIR;
    ```

* struct dirent:

  * Directory item
  * Defined in `<dirent.h>`

  ```c
  ino_t d_ino; /* inode number */
  char d_name[NAME_MAX + 1]; /* file name */
  ```

#### 目录的打开、关闭、读、定位

```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
off_t telldir(DIR *dir);
void seekdir(DIR *dir, off_t offset);
```

#### example

A directory scanning program

```c
DIR *dp;
struct dirent *entry;
if ( (dp = opendir(dir)) == NULL )
err_sys(…);
while ( (entry = readdir(dp)) != NULL ) {
lstat(entry->d_name, &statbuf);
if ( S_ISDIR(statbuf.st_mode) )
…
else
…
}
closedir(dp);
```



### 硬链接( link )

Create a new link to (make a new name for) a file:

```c
#include <unistd.h>
int link(const char *oldpath, const char *newpath);
```

* Return: 0 if success; -1 if failure
* 对应系统调用`link`



Delete a name and possibly the file it refers to:

```
#include <unistd.h>
int unlink(const char *pathname);
```

* Return: 0 if success; -1 if failure



* 对应的shell工具是`ln`

* 硬链接只是对**同一个**inode创建了新的引用

  ```shell
  > ln far far2 
  > ls -i                                                                       
  
  2536724 far  2536724 far2  //inode number一样
  ```

  

* 事实上，文件名都只是对`inode`的链接

* 创建文件时，实际上是先创建`inode`，然后将人类可读的名称链接到该文件，并将这个键值对存入目录

* 不能创建目录的硬链接，因为会在目录树中成环

* `inode  number`在不同文件系统中不唯一，因此硬链接不能跨文件系统





### 软链接( symlink )

也称为符号链接

Create a symbolic link (named newpath which contains‏the‏sting‏”oldpath”):

```c
#include <unistd.h>
int symlink(const char *oldpath, const char *newpath);
```

* Return: 0 if success; -1 if failure



Read value of a symbolic link: 

```c
#include <unistd.h>
int readlink(const char *path, char *buf, size_t bufsiz);
```

* Return: the count of characters placed in the buffer if success; -1 if failure



 对应命令行工具`ln -s`

```shell
ln -s  far far3  
```

* 符号链接是一个**不同类型的文件**, 它的内容是被链接文件的文件名
  * `ls`显示，类型为`l`
* **OS将截获对符号链接文件的访问，,依据符号链接中的文件名去读真正的目标文件**
* 优点： 可链接目录， 可跨文件系统链接
* 缺点:**搜索文件路径**开销大,需要额外的空间查找存储路径
* 对应系统调用`symlink`

```shell
> ls -al
drwxr-xr-x 3 lyk lyk  4096 11月 26 22:14 .
drwxr-xr-x 4 lyk lyk  4096 11月 26 22:00 ..
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far2
lrwxrwxrwx 1 lyk lyk     3 11月 26 22:14 far3 -> far  //软链接，内容为目标文件名“far”，是三字节

```



### 创建并挂载文件系统

```
mkfs()
mount()
```

# Standard I/O Library

* File stream 

* Standard I/O functions

## File Stream

* Stream ‏and ‏”FILE” ‏structure:
  * `FILE* fp; `
  * Predefined pointer: stdin, stdout, stderr  
* Buffered I/O

### Stream Buffering Operations

`<stdio.h>`

Three types of buffering: 

* block buffered (fully buffered) 
* line buffered 
* unbuffered



setbuf, setvbuf functions: 

```c
void setbuf(FILE *stream, char *buf);
```

```c
int setvbuf(FILE *stream, char *buf, int mode, size_t
size);
```

*  type：
  * `_IOFBF`: 满缓冲
  * `_IOLBF`: 行缓冲
  * `_IONBF`: 无缓冲

## Standard I/O Functions

* Stream open/close 
* Stream read/write 
  * 每次一个字符的I/O 
  * 每次一行的I/O 
  * 直接I/O(二进制I/O) 
  * 格式化I/O 
* Stream reposition 
* Stream flush

### Stream open/close

#### Open a stream:

```c
#include <stdio.h>
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
```



Parameter‏ `mode`:

* `r`: Open text file for reading. 
* `w`: Truncate file to zero length or create text file for writing. 
* `a`: Open for appending. 
* `r+`: Open for reading and writing. 
* `w+`: Open for reading and writing. The file is created if it does not exist, otherwise it is truncated. 
* `a+`: Open for reading and appending. The file is created if does not exist.

#### Close a stream

```c
#include <stdio.h>
int fclose(FILE *fp);
```

* Return: 0 if success; -1 if failure

### character operations

#### input of a character

```c
#include <stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
```

* Result: Reads the next character from a stream and returns it as an unsigned char cast to an int, or EOF on end of file or error.



Three functions: 

* `ferror`
* `feof`
* `clearerr`  

`ungetc` function: push a character back to a stream.

#### output of a character

```c
#include <stdio.h>
int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);
```

* Return: the character if success; -1 if failure

### Line of String operations

#### Input of a Line of String

```c
#include <stdio.h>
char *fgets(char *s, int size, FILE *stream);
char *gets(char *s); //not recommended.
```

`fgets`: reads in at most **size-1** characters from **stream** and stores them into the buffer pointed by `s`. **Reading stops after an EOF or a new line.**  A `\0` character is stored at the end of the buffer.

#### Output of a Line of String

```c
#include <stdio.h>
int fputs(const char *s, FILE *stream);
int puts(const char *s);
```



### Binary Stream Input/Output

```c
#include <stdio.h>
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

* Return: the number of a items successfully read or written



Application:

* Read/write a binary array:

  ```c
  float data[10];
  if ( fwrite(&data[2], sizeof(float), 4, fp) != 4 )
  err_sys(“fwrite‏error”);
  ```

* Read/write a structure:

  ```c
  struct {
  short count; long total; char name[NAMESIZE];
  }item;
  if ( fwrite(&item, sizeof(item), 1, fp) != 1)
  err_sys(“fwrite‏error”);
  ```

  

### Formatted I/O

scanf, fscanf, sscanf functions

```c
#include <stdio.h>
int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);
```

* Use fgets, then parse the string



printf, fprintf, sprintf functions:

```c
#include <stdio.h>
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
```



### Reposition a stream

fseek, ftell, rewind functions:

```c
#include <stdio.h>
int fseek(FILE *stream, long int offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
```



fgetpos, fsetpos functions ( Introduced in ANSI C):

```c
#include <stdio.h>
int fgetpos(FILE *fp, fpos_t *pos);
int fsetpos(FILE *fp, const fpos_t *pos);
```

### Flush a stream

把流里的数据立刻写入文件

```c
#include <stdio.h>
int fflush(FILE *stream);
```

### Stream and File Descriptor

确定流使用的底层文件描述符:

```c
#include <stdio.h>
int fileno(FILE *fp);
```



根据已打开的文件描述符创建一个流:

```c
#include <stdio.h>
FILE *fdopen(int fildes, const char *mode);
```

### Temporary File

Create a name for a temporary file:

```c
#include <stdio.h>
char *tmpnam(char *s);
```

* 返回值: 指向唯一路径名的指针



Create a temporary file:

```c
#include <stdio.h>
FILE *tmpfile(void);
```

* 返回值: 若成功为文件指针，若出错为NULL

### Advanced System Calls

Handling file attributes 

* stat/fstat/lstat, ... 

Handling directory

#### stat/fstat/lstat functions

Get file status

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int stat(const char *filename, struct stat *buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *file_name, struct stat *buf);
```

* Return: 0 if success; -1 if failure

#### struct stat

```c
struct stat {
mode_t st_mode; /*file type & mode*/
ino_t st_ino; /*inode number (serial number)*/
dev_t st_rdev; /*device number (file system)*/
nlink_t st_nlink; /*link count*/
uid_t st_uid; /*user ID of owner*/
gid_t st_gid; /*group ID of owner*/
off_t st_size; /*size of file, in bytes*/
time_t st_atime; /*time of last access*/
time_t st_mtime; /*time of last modification*/
time_t st_ctime; /*time of last file status change*/
long st_blksize; /*Optimal block size for I/O*/
long st_blocks; /*number 512-byte blocks allocated*/
};
```

#### Test macros for file types

Defined in `<sys/stat.h>`

| Macro     | File type              |
| --------- | ---------------------- |
| S_ISREG   | regular file           |
| S_ISDIR   | directory              |
| S_ISCHR   | character special file |
| S_ISBLK   | block special file     |
| S_ISFIFO  | fifo                   |
| S_ISLNK() | symbolic link          |
| S_ISSOCK  | socket                 |

## File Permission

| Perm       | File                                          | Directory                                                    |
| ---------- | --------------------------------------------- | ------------------------------------------------------------ |
| r          | User can read contents of file                | User can list the contents of the directory                  |
| w          | User can change contents of file              | User can change the contents of the directory                |
| x          | User can execute file as a command            | User can cd to directory and can use it in PATH              |
| SUID       | Program runs with effective user ID of owner  |                                                              |
| SGID       | Program runs with effective group ID of owner | Files created in directory inherit the same group ID as the directory |
| Sticky bit |                                               | Only the owner of the file and the owner of the directory may delete files in this directory |



| **mode**        | **含义**                          |
| --------------- | --------------------------------- |
| S_IRUSR (00400) | Read by owner                     |
| S_IWUSR (00200) | Write by owner                    |
| S_IXUSR (00100) | Execute by owner                  |
| S_IRWXU(00700)  | Read, write and execute by owner  |
| S_IRGRP (00040) | Read by group                     |
| S_IWGRP (00020) | Write by group                    |
| S_IXGRP (00010) | Execute by group                  |
| S_IRWXG (00070) | Read, write and execute by group  |
| S_IROTH (00004) | Read by others                    |
| S_IWOTH (00002) | Write by others                   |
| S_IXOTH (00001) | Execute by others                 |
| S_IRWXO (00007) | Read, write and execute by others |
| S_ISUID(04000)  | Set user ID on execution          |
| S_ISGID(02000)  | Set group ID on execution         |
| S_ISVTX(01000)  | Saved-text bit (sticky bit)       |

Example: testing file permission:

```c
if (buf.st_mode & S_IRUSR)
	printf(“readable by owner”);
else
	printf(“unreadable by owner”);
```

### umask

` umask`：  文件权限屏蔽字,  是用户在建立文件或目录时需要减掉的权限

* **file persission = mode & ~umask**

* 命令行工具：` umask`

  * `umask -S`:  以符号形式显示

  ```shell
  ❯ umask //表明group和others没有2（写）权限
  022
  
  //或者
  ❯ umask -S 
  u=rwx,g=rx,o=rx
  ```

  

```C
#include <sys/types.h>
#include <sys/stat.h>
mode_t umask(mode_t mask); //为进程设置文件存取权限屏蔽字，并返回以前的值
```





Regular files:

| permissions           | symbol      | number |
| --------------------- | ----------- | ------ |
| default permissions   | `rw-rw-rw-` | 666    |
| umask                 | `----w--w-` | 022    |
| resulting permissions | `rw-r--r--` | 644    |



Directories:

| permissions           | symbol      | number |
| --------------------- | ----------- | ------ |
| default permissions   | `rwxrwxrwx` | 777    |
| umask                 | `----w--w-` | 022    |
| resulting permissions | `rwxr-xr-x` | 755    |



### access function

按实际用户ID和实际组ID测试文件存取权限

```C
#include <unistd.h>
int access(const char *pathname, int mode);
```

* Return: 0 if success; -1 if failure
* Parameter‏ `mode`:
  * `R_OK`
  * `W_OK`
  * `X_OK`
  * `F_OK`

### chmod/fchmod functions

Change permissions of a file:

```C
#include <sys/types.h>
#include <sys/stat.h>
int chmod(const char *path, mode_t mode);
int fchmod(int fildes, mode_t mode);
```

* Return: 0 if success; -1 if failure





## File lock

File lock 可以保证文件的并发安全访问



分类：

* 记录锁 
* 劝告锁
  * 检查，加锁有应用程序自己控制 
* 强制锁
  * 检查，加锁由内核控制 
  * 影响[ `open()`，  `read()`，  `write()` ]等 
* 共享锁
* 排他锁



特殊类型：

* 共享模式强制锁 
* 租借锁

### 标志位

* `mount -o mand /dev/sdb7 /mnt `

* super_block 
  * s_flags 

* `MS_MANDLOCK`

### fcntl记录锁

用于记录锁的fcntl函数:

```c
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *lock);
```

* 返回值: 若成功则依赖于`cmd`，若出错为-1

### struct flock

```c
struct flock{
...
short l_type; /* Type of lock: F_RDLCK, F_WRLCK, F_UNLCK */
short l_whence; /* How to interpret l_start: SEEK_SET, SEEK_CUR,
SEEK_END */
off_t l_start; /* Starting offset for lock */
off_t l_len; /* Number of bytes to lock */
pid_t l_pid; /* PID of process blocking our lock (F_GETLK only) */
...
}
```

### cmd参数

cmd参数的取值：

* `F_GETLK`：获得文件的封锁信息 
* `F_SETLK`：对文件的某个区域封锁或解除封锁
* `F_SETLKW`：功能同`F_SETLK`, wait方式

### 其它封锁命令

`lockf`函数：

```c
#include <sys/file.h>
int lockf(int fd, int cmd, off_t len)
```



# File System

## 整体组织

我们实现极简版的VSFS（ `Very Simple File System` ）， 本文最后会看到，VVFS事实上与Linux的VFS（虚拟文件系统，提供了统一的文件系统模型）相同：

* 磁盘分块（block），文件系统由一系列块组成
* 假定有64块，每块4KB. 数据块为最后56个，inode表占5个，两种位图各占一个，超级块占一个

![VSFS Disk Image](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VSFS%20Disk%20Image.png)





* `superblock`：位于第一块， 记录关于该文件系统的信息, 包括`inode`和数据块数量，inode表的起始地址等。 和一些标识文件系统类型的`magic number`
* 位图（bitmap）：记录inode或数据块是否已分配的数据结构，有`inode bitmap`和`data bitmap`
* `inode`表：就是 `inode`数组
* 数据块



| 超级块 | inode bit map | data bitmap | inode table | datablock |
| ------ | ------------- | ----------- | ----------- | --------- |
| 1      | 1             | 1           | 5           | 56        |

* **挂载文件系统时，OS首先读取`superblock`，初始化各种参数，然后将该卷添加到文件系统树中**
  * 也就是说挂载文件系统时，超级块必定被加载到内存里

### 文件组织： inode

index node， named by Ken Thompson

* `inode`：保存给定文件的元数据的结构

* **由`inumber`隐式引用,** 给定`inumber`，可以计算磁盘上相应节点的位置

* 假设：

  * inode表大小为20KB（5个4KB块）
  * 每个`inode`256字节，因此有80个`inode`；
  * 超级块0KB开始，`inode map`从4KB开始， `data map`从8KB开始，`inode table`从12字节开始
  * 要读取`inode number=32`

* 过程：

  1. 先得到inode表的起始地址：`12KB`
  
  2. 再加上此`inode`在表内的偏移量：`32 * 256B = 8192B`， `12KB + 8192B= 20KB`
  
  3.  由于磁盘不是字节可寻址的，而是由可寻址扇区组成（512B），因此为了获取`inumber=32`的`inode`块，文件系统将请求物理节点号`40`（ `20KB / 512B= 40` ）,获得期望的`inode`块
  
     ```python
     #通用算法： inumber -> sector number
     blk = ( inumber * sizeof(inode_t) )/ blockSize; # 得到该inode所在的块号
     sector = ((blk*blockSize)+ inodeStartAddr)/ sectorSize;
     ```

#### 多级索引

为了支持大文件，inode中除了直接指针外，还允许间接指针。 间接指针指向一个间接块（磁盘的数据块区域）。 假设一个块是4KB，磁盘地址空间是4Byte， 那就增加了1024个指针。 假设inode有12个直接指针和一个间接指针，则一个inode可以支持$(12+ 1 \times 1024) \times 4 \mathrm{KB}$

按这个逻辑，还可以分配一个二重间接块，存放指向间接块的指针， inode存放一个二重间接指针， 这个指针就可以表示$1024 \times 1024 \mathrm{KB}$



* 注意到，使用了多级索引的文件系统的文件分配模型是一个不平衡树，这个设计的初衷是： 大部分文件都是小文件， 因此只需要对大文件进行特殊的设计， 小文件让直接指针指向就好了



* 还有一种基于链表的方法，即inode只需存储一个指向第一个块的指针， 而数据区每个数据块的末尾都会有一个指向该文件下一个数据块的指针。但是这种方式对于某些workload效果不好，比如随机访问。
  * windows采用FAT（File Allocation Table）, 指向下一块的指针不存在当前数据块中， 而是存在FAT（位于内存）中

### 目录组织

目录是特殊的文件，它也有inode， 但是目录的内容（即数据块的内容）是目录条目（称为`dentry` )与该条目对应inode的映射

打开目录，首先是打开目录的文件描述符

目录基本上是一个`<dentry， inode number>`的列表。 其中条目名称还包括条目的记录长度（名称的总字节数 + 所有的剩余空间）和字符串长度（即条目名称的实际长度）。 每个目录还有两个额外的条目： `.`和`..` 用于表示当前目录和父目录

* 目录就是特殊的文件， 它也有inode， 目录的数据块的内容就是以上说的`<条目名称， inode number>`的列表

假设某目录（i number = 5）中有三个文件（foo, bar, foo bar）， i number分别为12，13和24，则dir在磁盘上的数据是：

| inum | reclen | strlen | name   |
| ---- | ------ | ------ | ------ |
| 5    | 4      | 2      | .      |
| 2    | 4      | 3      | ..     |
| 12   | 4      | 4      | foo    |
| 13   | 4      | 4      | bar    |
| 24   | 8      | 7      | foobar |

删除一个文件会在目录中留下一段空白空间， 一般是将该文件对应条目的inum设为一个保留的inum（例如0）



目录的内容虽然位于数据块，但它一般被认为是**元数据**， 因此在写入日志时，会被当作元数据（而不是物理数据）处理

## 空闲空间管理

文件系统必须记录哪些inode和数据块是空闲的，这样在分配新文件/新目录时，就可以使用空闲的inode和数据块， 这就是空闲空间管理

VFSFS中使用位图进行空闲空间管理， 然而也有别的方法， 比如空闲列表和B树等

* 空闲列表：（超级块中的有一个空闲指针，指向第一个空闲块，此后每个空闲块内部都有指向下一个空闲块的指针

## 文件访问

假设文件系统已经挂载，要读取文件`/foo/bar`, 要读取该文件（也就是该文件的数据块），需要先找到该文件的inode， **文件系统必须遍历路径名，才能找到inode， 所有遍历都从文件系统的根目录开始**。 即文件系统会先读入inode为2的块， 然后找到`/foo`的inumber和块，最后找到`/foo/bar`的inumber和块

* 一般而言，根目录的inode number为2
* 这种遍历方式会导致， 访问文件导致的IO与路径长度成正比，路径上的每个目录都会被读取
* `read()`系统调用不会查询位图，因为**只有要分配空间时（比如write()）才需要查询分配结构**

## 缓存

如前所述，每次文件访问都会读取路径上的所有目录，为此可以用缓存，将数据保留在内存中， 分为读缓存和写缓存

* 写缓存： 显然，写入数据最终必须要写入磁盘，这看上去和缓存没什么关系。然而，写缓存可以将一组写入操作编成一批（batch）, 再延迟写入， 一次延迟写入就处理一批写操作

为了避免缓存，可以用`fsync()`来强制写入磁盘， 甚至可以不使用文件系统，直接使用原始磁盘接口（`raw disk interface`）来写入数据（数据库就经常这么干， 因为数据库坚持自己控制一切）

# Locality and FFS

**内存是随机访问的，但目前为止的磁盘都是顺序访问的，OS通过抽象，把磁盘抽象成了内存，让程序以为所有空间都是随机访问的，这就导致了某些workload会导致磁盘性能不佳，因为毕竟底层是顺序访问**



解决这个问题，需要文件系统面向磁盘设计。为此，Berkley的一个小组设计了FFS（Fast File System），它将磁盘分为一些组，称为柱面组（或称为块组），将两个**有关联**的块放到同一分组，这样访问的时候可以提高效率

* 举例来说，FFS将文件的inode所在块和数据块放在一起（因为这二者必定有关联），避免长时间寻道
* “有关联”还可以建立在局部性原理上，例如，FFS将同一目录下的所有文件尽量放在一组，因为按照局部性原理，这些文件被经常一起访问



由于大文件无法全部放入一个分组，因此FFS会将某些块（比如inode块）分配到一个组， 而大块房贷单独的分组。这会导致磁盘碎片化。 当然，允许的块越大，这种碎片也就越少



FFS的贡献：

* 引入了面向磁盘的文件系统
* 引入了软链接
* 引入了`rename()`系统调用



# Crush-Consistency Problem

崩溃一致性问题 ： 更新持久数据结构时发生崩溃，解决方案有fsck和日志



向文件写数据时，要更新至少三个块：更新的inode（比如，要增加新的指针）， 更新的数据块和更新的数据位图

这三个块的写入操作，无论哪个出问题，都会导致崩溃后不一致



在元数据日志中，我们会看到， 解决崩溃一致性的核心，就是**先写入被指对象，再写入指针对象**，这样能保证数据的正确性

## 示例

示例：对于如下文件系统结构，有一个inode位图，一个数据位图，一个inode表（包含8个inode）和一个数据块表（包含8个数据块）

![Crush Consistency example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/Crush%20Consistency%20example.png)

（ 这里inode bmap和data bmap实际指向了下标3和5，应该是图画错了 ）



可以看到，已经分配了一个inode（inumber=2），它在inode位图中标记， 单个分配的数据块Da（数据块4）也在数据位图（记为`B[v1]`， 表示第一个版本)）中标记， inode表示为`I[v1]`，即该inode的第一个版本，`I[v1]`的内容有：

```
owner						:lyk
permissions			:read-write
size						:1
pointer				  :4
pointer:				:null
pointer:				:null
pointer:				:null
...
```

* 文件大小为1 （ 有一个数据块 ）， 第一个直接指针指向块4， 且所有其他直接指针都是null



假如要向文件追加内容，比如要增加一个数据块， 此时要更新至少三个块：更新的inode（比如，要增加新的指针）， 更新的数据块和更新的数据位图：



我们希望更新后的inode（用`I[v2]`表示）内容如下：

```
owner						:lyk
permissions			:read-write
size						:2
pointer				  :4
pointer:				:5
pointer:				:null
pointer:				:null
...
```

* 更新后的数据位图(记为`B[v2]`)要变成： 00001100
* 新增的数据块记为Db



我们希望最终的文件系统如下所示：

![Crush Consistency example expected result](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/Crush%20Consistency%20example%20expected%20result.png)



然而，对`I[v2]`, `B[v2]`, Db 这三个块的写入操作，无论哪个出问题，都会导致崩溃后不一致



## FSCK

File System Checker

一个UNIX工具，在文件系统挂载之前执行， 可以保证，fsck检查结束后，文件系统时一致的

fsc会检查超级块，空闲块，inode状态，inode链接等信息， 事实上，fsck会**扫描整个磁盘**（另一方面，出现不一致的可能只是几个数据块）， 因此fsck的代价非常大

## Journalist

Linux的ext2文件系统没有日志 ，日志是由ext3引入的

带有日志的ext3文件系统如下所示：

![ext3 with journalist](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/ext3%20with%20journalist.png)

* 可以看到，这里对块/柱面进行了分组

### Data Journaling

数据日志就是将要更新的物理内容也写进日志里



对于之前的示例，加入数据日志后，文件系统的日志区域如下所示：

![data journaling](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/data%20journaling.png)

这里写了五个块：

* 事务开始TxB： 此更新的相关信息，以及事务标识符（TID）
* 物理日志： 这里占三个块，就是更新的确切物理内容
* 事务结束TxE： 也会包含TID



更新文件系统分为三个步骤：

1. 日志写入： 将食物的内容（包括TxB， 元数据和数据）写入日志，等待这些写入完成

2. 日志提交： 将事务提交块（包括TxE）写入日志，事务被认为已提交（committed）

3. 加检查点： 将更新内容（元数据和数据）写入磁盘

4. 释放： 一段时间后，通过更新日志超级块（不是主文件系统的超级块）， 在超级块中标识该事物为空闲

   * 这一步和事务的原子性没有关系，只是为了重用日志空间。日志空间如果满了，就无法提交事务了，因此日志被实现为循环数据结构，一旦事务被加检查点，文件系统就应该释放它在日志中占用的空间，允许重用日志空间
     * 要达到这个目的有很多方法，比如在日志超级块中标记最新和最旧的事务

   ![journaling circyling journalist](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/journaling%20circyling%20journalist.png)



注意，如果将TxE在日志写入阶段一并提交（即没有日志提交步骤），那么在日志写入阶段发生崩溃时（即将以上五个块发生崩溃时），会出现问题。 因此， **日志总是要分为日志写入和提交两阶段，来确日志的原子性**





崩溃恢复：

1. 如果在步骤2之前崩溃，那可以跳过这个更新（事务），因为没有该事物的日志，崩溃后的系统根本不知道这个事务的存在
2. 如果在步骤3之前崩溃，系统只需要replay日志中的食物，这称为redo logging
3. 如果在加检查点时发生崩溃，处理方式如步骤2



缺点： 数据日志需要将待更新数据写入磁盘两次，一次写入日志空间，一次写入真正的待更新区域，这是巨大的开销，为此，我们一般使用**元数据日志**

### Metadata Journaling

元数据日志与数据日志几乎相同，但是物理数据没有写入日志，而是直接写入文件系统

但是，物理数据不能在事务提交后再写入文件系统，否则即使replay日志，也无法恢复数据（因为此时的日志中没有物理数据），所以，应该**首先进行数据写入，这可以保证指针永远不会指向垃圾**， 其核心理念是**先写入被指对象，再写入指针对象**：

1. 物理数据写入
2. 日志元数据写入： 将开始块TxB和元数据写入日志
3. 日志提交
4. 加检查点元数据： 将元数据更新的内容写入文件系统
5. 释放



元数据日志的缺点是**块复用问题**， 因为目录的内容被当作元数据而不是物理数据，这意味着（在元数据日志中）**目录的内容会放在日志空间**。 假设某目录的内容在日志空间中占用块1000， 随后用户删除该目录，并释放块1000， 最后用户创建了新文件，并复用了块1000（此时该块位于物理数据空间）， 此时，在日志提交后，加检查点完成之前发生了崩溃，在replay阶段， 会重放日志中所有内容， 那么新文件的内容（也就是块1000）就会被恢复为目录的内容！ 这都是因为目录的内容被视作元数据，而不是物理数据，保留在日志空间

Linux ext3点解决方案是加入撤销（revoke）指令，在上例中，删除目录将导致revoke指令被添加到日志，在replay时，被revoke的数据（这里是目录的内容）将不会被重放



# Data Integrity and Protection

# VFS

VFS（Virtual Filesystem Switch）：虚拟文件系统或虚拟文件系统转换，是文件系统的虚拟化，位于内核态，将底层异构的文件系统转换为统一的文件系统，并通过统一的Posix接口访问

* 作为文件系统的抽象，VFS只存在于内存
* VFS起源于Unix， 所以VFS适用于所有Unix like OS
* VFS的整体组织与前文提到的VVFS相同，分为超级块、inode等



![VFS Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Arch.png)

## 分层

VFS在整个Linux系统中的分层视图如下：

![VFS Layer](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Layer.png)

Linux系统的User**使用GLIBC（POSIX标准、GUN C运行时库）作为应用程序的运行时库**，然后通过OS转换为系统调用SCI（system-call interface），SCI是操作系统内核定义的系统调用接口，这层抽象允许**用户程序的I/O操作转换为内核的接口调用**。VFS提供了一个抽象层，将POSIX API接口与不同存储设备的具体接口实现进行了分离，使得底层的文件系统类型、设备类型对上层应用程序透明。

## 接口适配示例

用户写入文件时，使用POSIX标准的write接口，然后陷入kernel mode，调用`sys_write()`系统调用（属于SCI层）。然后VFS层接受到该调用，转换为对给定文件系统、给定设备的操作



![VFS Function Call workflow](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20Function%20Call%20workflow.png)

## 跨设备/文件系统示例

下面中，用户通过cp命令进行文件拷贝，用户不需要关心底层文件系统的实现，只需要通过VFS抽象层实现对不同文件系统的读写操作：

![VFS example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/VFS%20example.png)

## VFS支持的系统调用

上述示例中提到VFS也有自己的文件模型，用来支持操作系统的系统调用。下面是VFS抽象模型支持的所有Linux系统调用：

- 文件系统相关：mount, umount, umount2, sysfs,  statfs,  fstatfs,  fstatfs64, ustat
- 目录相关：chroot，pivot_root，chdir，fchdir，getcwd，mkdir，rmdir，getdents，getdents64，readdir，link，unlink，rename，lookup_dcookie
- 链接相关：readlink，symlink
- 文件相关：chown， fchown，lchown，chown16，fchown16，lchown16，hmod，fchmod，utime，stat，fstat，lstat，acess，oldstat，oldfstat，oldlstat，stat64，lstat64，lstat64，open，close，creat，umask，dup，dup2，fcntl， fcntl64，select，poll，truncate，ftruncate，truncate64，ftruncate64，lseek，llseek，read，write，readv，writev，sendfile，sendfile64，readahead

## VFS支持的文件系统

- Disk-based 文件系统：Ext2, ext3, ReiserFS，Sysv, UFS, MINIX, VxFS，VFAT, NTFS，ISO9660 CD-ROM, UDF DVD，HPFS, HFS, AFFS, ADFS,
- Network 文件系统：NFS, Coda, AFS, CIFS, NCP
- 特殊文件系统：/proc，/tmpfs等

