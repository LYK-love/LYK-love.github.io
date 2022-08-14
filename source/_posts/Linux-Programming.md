---
title: Linux Programming
tags: Linux
categories: Technology
date: 2022-05-05 03:43:30
---


Outline：

* Linux文件操作api

<!--more-->



# Linux File

## File types

从细节来说，文件类型分为:

* regular file 
* character special file： 与设备进行交互的文件，按字符IO，如终端文件tty
* block special file: 同上，但是按块IO
* 管道文件/fifo ： 用于进程间通信
* socket：表示一个socket连接
* symbolic link：符号链接
* directory (  目录也是一种文件，我们只是把目录和文件分开讨论 )

## File  Structure

File  Structure:

* Byte stream; 
* no particular internal structure

## FIle Descripter

Linux中的文件描述符和文件指针FILE *的区别什么？

1. 文件描述符：在Linux系统中打开文件就会获得文件描述符，它是很小的正整数。每个进程在PCB(Process Control Block)中保存着一份文件描述表，文件描述符就是这个文件描述符的索引，每个表项都有一个指向已打开文件的指针。
2. 文件指针：C语言中使用文件指针作为I/O的句柄，文件指针指向进程用户区中的一个被称为FILE结构的数据结构。FILE结果包括一个缓冲区和一个文件描述符。而文件描述符是文件描述符表的一个索引，因此从某种意义上文件指针就是句柄的句柄

## Basic I/O System Calls 

* File descriptor 
* Basic I/O:
  * open/creat, close, read, write, lseek 
  * dup/dup2 
  * fcntl
  * ioctl

## File descriptor

File descriptor:

* A small non-negative integer 
  * `int fd;` 
* **是thread local的**
* 在UNIX中用于访问文件,  也可以将它作为指向文件对象的指针
* in `<unistd.h>`
  * **STDIN_FILENO: 0**
  * **STDOUT_FILENO : 1**
  * **STDERR_FILENO: 2** 
* 进程总是会打开0,1,2这三个文件描述符



General steps of file operation: 

1. open
2. read/write
3. [lseek]
4. close

## File Name Suffix

| suffix                      | 解释                                                        |
| --------------------------- | ----------------------------------------------------------- |
| .c                          | C source code which must be preprocessed                    |
| .i                          | C source code which should not be preprocessed              |
| .cc.cp.cpp.CPP. c++ .C .cxx | C++sourcecodewhichmustbepreprocessed                        |
| .ii                         | C++ source code which should not be preprocessed            |
| .h                          | C or C++ header file to be turned into a precompiled header |
| .H .hh                      | C++ header file to be turned into a precompiled header      |
| .s                          | Assembler code                                              |
| .S                          | Assembler code which must be preprocessed                   |
| .o                          | Object file                                                 |
| .a                          | Static library file (archive file)                          |
| .so                         | Dynamic library file (shared object)                        |
|                             |                                                             |

## File Permission

| Perm       | File                                             | Directory                                                    |
| ---------- | ------------------------------------------------ | ------------------------------------------------------------ |
| r          | User can read contents of file                   | User can list the contents of the directory                  |
| w          | User can change contents of file                 | User can change the contents of the directory                |
| x          | User can execute file as a command               | User can cd to directory and can use it in PATH              |
| SUID       | **Program runs with effective user ID of owner** |                                                              |
| SGID       | Program runs with effective group ID of owner    | Files created in directory inherit the same group ID as the directory |
| Sticky bit |                                                  | Only the owner of the file and the owner of the directory may delete files in this directory |



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





## File Attribute



```C++
struct stat
{
  dev_t st_dev; //device 文件的设备编号
  ino_t st_ino; //inode 文件的i-node
  mode_t st_mode; //protection 文件的类型和存取的权限
  nlink_t st_nlink; //number of hard links 连到该文件的硬链接数目, 刚建立的文件值为1.
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

# Linux Signal

      1. SIGHUP连接挂断
      2. SIGINT终端中断
      3. SIGKILL终止进程（此信号不能被捕获或忽略）
      4. SIGQUIT终端退出
      5. SIGTERM终止
      6. SIGCHLD子进程已经停止或退出
      7. SIGCONT继续执行暂停进程
      8. SIGSTOP停止执行（此信号不能被捕获或忽略）
      9. SIGTSTP终端挂起

# io系统调用

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
* 分为主标志和副标志， 主标志必须，且是互斥的，即只能选择一种。 副标志是可选的，可以选择多个
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
  * 第二个参数指向放置结果的缓冲区, `strace`显示了此时的读取结果`hello\n`
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

* 参数 offset 的含义取决于参数 whence：
  * 如果 whence 是 SEEK_SET，文件偏移量将被设置为 offset。
  * 如果 whence 是 SEEK_CUR，文件偏移量将被设置为 当前偏移量加上 offset，offset 可以为正也可以为负。
  * 如果 whence 是 SEEK_END，文件偏移量将被设置为文件长度加上 offset，   offset 可以为正也可以为负。



使用`lseek（）`

```c
off_t lseek(int fildes, off_t offset, int whence);
```

可以看到，对每个进程打开的文件，OS都会跟踪一个当前偏移量`offset`。 要么每次读写后隐式更新，要么通过`lssek（）`指定

### dup/dup2 Function

dup用来复制oldfd所指的文件描述符。但复制成功时返回最小的尚未被使用的文件描述符。若有错误则返回－1，错误代码存入errno中。返回的新文件描述符和参数oldfd指向同一个文件，共享所有的锁定，读写指针，和各项权限或标志位

dup2可以用参数newfd指定新文件描述符的数值。若newfd已经被程序使用，系统就会将其关闭以释放该文件描述符；若newfd与oldfd相等，dup2将返回newfd，而不关闭他。dup2调用成功返回新的文件描述符，出错则返回－1



* Duplicate a file descriptor 

  ```c
  #include <unistd.h>
  int dup(int oldfd);
  int dup2(int oldfd, int newfd);
  ```

  * Return: the new file descriptor if success; -1 if failure

* File sharing

  * **Example: redirection**, 步骤详见*Using Shell*， dup/dup2所做的就是给原有的文件描述符再分配一个复制，由于此时标准输出/输入一半已经关闭，新分配的fd一般就是标准输出/输入，这就实现了重定向

### fcntl Function

Manipulate a file descriptor，该函数对fd的操作比较全面

```c++
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock);//可以对文件加锁
//(返回值: 若成功则依赖于cmd，若出错为-1)
```

2. The‏ operation‏ is‏ determined ‏by‏"cmd".
3. The‏ value‏ of‏"cmd"
   1. **F_DUPFD**: Duplicate a file descriptor
   2. **F_GETFD/F_SETFD**:‏Get/set ‏the‏ file‏d escriptor's
   3. **‏close-on exec** flag：执行时是否关闭，文件描述符能否从父进程传递到子进程。
   4. F_GETFL/F_SETFL:‏Get/set ‏the‏ file ‏descriptor's **‏flags**(并不是所有情况都可以setfl的)
   5. F_GETOWN/F_SETOWN: Manage I/O availability signals(告诉当前进程是否I/O传来的信号)(不要求理解深刻)
   6. F_GETLK/F_SETLK/F_SETLKW: Get/set the file lock(暂时不讲)
4. Example：dup/dup2 and fcntl

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

### 获取文件属性

```从
int stat(const char * file_name, struct stat *buf);
```

`stat()`用来将参数`file_name` 所指的文件状态, 复制到参数`buf `所指的结构中

`stat`结构体见上文*File Attribute*

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

```c
#include <stdio.h> // 如果引入的是标准库，就不是系统调用，系统调用的输入参数一般是文件描述符而不是流指针
```

三种缓冲

1. 块缓冲（完全缓冲）
2. 行缓冲
3. 无缓冲



setbuf用于打开或关闭流缓冲机制，参数buf指向一个长度为BUFSIZ（该常量在`<stdio.h>`中定义）的缓冲区；如果要关闭缓冲，则将buf设置为NULL即可:

```c
void setbuf(FILE *stream, char *buf);
```



setvbuf用于精确地设置所需的缓冲类型

```c
int setvbuf(FILE *stream, char *buf, int mode, size_t
size);
```

*  `mode`取值如下：
   
   * `_IOFBF`: 满缓冲
   * `_IOLBF`: 行缓冲
   * `_IONBF`: 无缓冲
   
* 如果指定了mode为带缓冲类型，而buf却为NULL，则系统会自动分配BUFSIZ个字节的缓冲区:

   

   

   



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

## File lock

File lock 可以保证文件的并发安全访问



分类：

* 记录锁： 可以锁定文件的部分区域甚至字节
* 劝告锁
  * 检查，加锁由应用程序自己控制 
* 强制锁
  * 检查，加锁由内核控制 
  * 影响[`open()`，  `read()`，  `write()` 等 
* 共享锁： 读锁，不能加排他锁
* 排他锁：写锁，不能加读锁或其他写锁



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



