---
title: OS Persistence
tags: Operating Systems Three Easy pieces
categories: OS
date: 2022-03-21 17:31:25
---


# I/O Devicecs

![image-20220107045837925](/home/lyk/snap/typora/46/.config/Typora/typora-user-images/image-20220107045837925.png)

# RAID

# File

* 进程是虚拟化的CPU, 地址空间是虚拟化的内存， 而文件和目录就是虚拟化的外部存储设备
* 文件：线性字节数组，每个文件都有一个低级名称：`inode number`
* 目录：其内容为`（用户可读名字， 低级名称）`对的列表。 目录本身也有低级名称`inode number`. 
  * 目录的每个对，即每个条目`entry`，都指向文件或其他目录
  * 目录层次结构从根目录`/`开始

![image-20220321150141539](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/OS/OS%20Basic/OS%20Persistence/ls%20output.png)

## File types

File types:

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
| **O_TRUNC**  | **若文件存在并且以可写的方式打开时，****此标志会将文件长度清为0，而原来存于****该文件的资料也会消失** |
| **O_CREAT**  | **若路径中的文件不存在则自动建立该文件**                     |
| **O_EXCL**   | **如果与O_CREAT同时设置，此指令会去检****查文件是否存在，文件若不存在则建立该文****件，否则将导致打开文件错误。此外，若****O_CREAT与O_EXCL同时设置，并且将要****打开的文件为符号连接，则将导致打开文件失败** |
| **O_APPEND** | **读写文件从文件尾部开始移动，所写入****的数据追加到文件尾** |

#### Parameter‏: mode

mode:  设定新建的文件的权限,    详见下文《File Permission》

|      |      |
| ---- | ---- |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |

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

* 硬链接只是对**同一个**inode号创建了新的引用

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

#### functions

* 



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

我们实现极简版的VSFS（ `Very Simple File System` ）

* 磁盘分块（block），文件系统由一系列块组成

  * 假定有64块，每块4KB. 数据块为最后56个，inode表占5个，两种位图各占一个，超级块占一个

  *  `superblock`：位于第一块， 记录关于该文件系统的信息。 包括`inode`和数据块数量，inode表的起始地址。 和一些标识文件系统类型的`magic number`
  * 位图（bitmap：记录inode或数据块是否已分配的数据结构，有`inode bitmap`和`data bitmap`
  * `inode`表： `inode`数组

  | 超级块 | inode bit map | data bitmap | inode table | datablock |
  | ------ | ------------- | ----------- | ----------- | --------- |
  | 1      | 1             | 1           | 5           | 56        |

* 挂载文件系统时，OS首先读取`superblock`，初始化各种参数，然后将该卷添加到文件系统树中

## 文件组织： inode

* `inode`：保存给定文件的元数据的结构

* 由`inumber`隐式引用, 给定`inumber`，可以计算磁盘上相应节点的位置

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
     blk = ( inumber + sizeof(inode_t) )/ blockSize;
     sector = ((blk*blockSize)+ inodeStartAddr)/ sectorSize;
     ```

### 多级索引

# Locality and FFS

# Crush-Consistency Problem: FSCK and Journalist

# File System Based on Journalist

# Data Integrity and Protection

# VFS

VFS（Virtual Filesystem Switch）称为虚拟文件系统或虚拟文件系统转换，是一个内核软件层，在具体的文件系统之上抽象的一层，用来处理与Posix文件系统相关的所有调用，表现为能够给各种文件系统提供一个通用的接口，使上层的应用程序能够使用通用的接口访问不同文件系统，同时也为不同文件系统的通信提供了媒介。



![image-20220321143850941](/home/lyk/.config/Typora/typora-user-images/image-20220321143850941.png)



## [架构](https://so.csdn.net/so/search?q=架构&spm=1001.2101.3001.7020)

VFS在整个Linux系统中的架构视图如下：

![img](https://img-blog.csdn.net/20180318233241252?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3UwMTA0ODc1Njg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

Linux系统的User使用GLIBC（POSIX标准、GUN C运行时库）作为应用程序的运行时库，然后通过操作系统，将其转换为系统调用SCI（system-call interface），SCI是操作系统内核定义的系统调用接口，这层抽象允许用户程序的I/O操作转换为内核的接口调用。VFS提供了一个抽象层，将POSIX API接口与不同存储设备的具体接口实现进行了分离，使得底层的文件系统类型、设备类型对上层应用程序透明。

## 接口适配示例

用户写入一个文件，使用POSIX标准的write接口，会被操作系统接管，转调sys_write这个系统调用（属于SCI层）。然后VFS层接受到这个调用，通过自身抽象的模型，转换为对给定文件系统、给定设备的操作，这一关键性的步骤是VFS的核心，需要有统一的模型，使得对任意支持的文件系统都能实现系统的功能。这就是VFS提供的统一的文件模型（common file model），底层具体的文件系统负责具体实现这种文件模型，负责完成POSIX API的功能，并最终实现对物理存储设备的操作。

![img](https://img-blog.csdn.net/20180318233301175?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3UwMTA0ODc1Njg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
VFS这一层建模和抽象是有必要的，如果放在SCI层会导致操作系统的系统调用的功能过于复杂，易出bug。那么就只能让底层文件系统都遵循统一实现，这对于已经出现的各种存储设备来说天然就有不同的特性，也是无法实现的。因此VFS这样一层抽象是有其必要性的。

## 跨设备/文件系统示例

VFS为不同设备或文件系统间的访问提供了媒介，下面的示意图和代码中，用户通过cp命令进行文件的拷贝，对用户来说是不用关心底层是否跨越文件系统和设备的，具体都通过VFS抽象层实现对不同文件系统的读写操作。

![img](https://img-blog.csdn.net/201803182333190?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L3UwMTA0ODc1Njg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## VFS的抽象接口

上述示例中提到VFS也有自己的文件模型，用来支持操作系统的系统调用。下面是VFS抽象模型支持的所有Linux系统调用：

- 文件系统相关：mount, umount, umount2, sysfs,  statfs,  fstatfs,  fstatfs64, ustat
- 目录相关：chroot，pivot_root，chdir，fchdir，getcwd，mkdir，rmdir，getdents，getdents64，readdir，link，unlink，rename，lookup_dcookie
- 链接相关：readlink，symlink
- 文件相关：chown， fchown，lchown，chown16，fchown16，lchown16，hmod，fchmod，utime，stat，fstat，lstat，acess，oldstat，oldfstat，oldlstat，stat64，lstat64，lstat64，open，close，creat，umask，dup，dup2，fcntl， fcntl64，select，poll，truncate，ftruncate，truncate64，ftruncate64，lseek，llseek，read，write，readv，writev，sendfile，sendfile64，readahead

## Linux系统VFS支持的文件系统

- Disk-based 文件系统：Ext2, ext3, ReiserFS，Sysv, UFS, MINIX, VxFS，VFAT, NTFS，ISO9660 CD-ROM, UDF DVD，HPFS, HFS, AFFS, ADFS,
- Network 文件系统：NFS, Coda, AFS, CIFS, NCP
- 特殊文件系统：/proc，/tmpfs等

## 统一文件模型（common file model）

VFS采用统一文件模型 VFS model， 它是一个对底层不同文件系统的抽象，只存在于内存。

* 统一文件模型是一个标准，各种具体文件系统必须按照该标准来实现

VFS起源于Unix， 所以VFS对所有Unix like OS都适用 



Components:

- superblock：存储文件系统基本的元数据。如文件系统类型、大小、状态，以及其他元数据相关的信息（元元数据）
- index node（inode）：保存一个文件相关的元数据。包括文件的所有者（用户、组）、访问时间、文件类型等，但不包括这个文件的名称。文件和目录均有具体的inode对应
- directory entry（dentry）：保存了文件（目录）名称和具体的inode的对应关系，用来粘合二者，同时可以实现目录与其包含的文件之间的映射关系。另外也作为缓存的对象，缓存最近最常访问的文件或目录，提示系统性能
- file：一组逻辑上相关联的数据，被一个进程打开并关联使用

![image-20220321145155528](/home/lyk/.config/Typora/typora-user-images/image-20220321145155528.png)



 进程打开file descriptor, 后者映射了dentry, denbtry又映射到inode, inode映射到super block具体的磁盘文件

## Conclusion



[##File Permission]: 
