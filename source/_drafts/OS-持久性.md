---
title: OS 持久性
tags: Operating Systems Three Easy pieces 
categories: OS
---

# I/O Devicecs

![image-20220107045837925](/home/lyk/snap/typora/46/.config/Typora/typora-user-images/image-20220107045837925.png)

## RAID

# File and Directory

* 进程是虚拟化的CPU, 地址空间是虚拟化的内存， 而文件和目录就是虚拟化的外部存储设备
* 文件：线性字节数组，每个文件都有一个低级名称：`inode number`
* 目录：其内容为`（用户可读名字， 低级名称）`对的列表。 目录本身也有低级名称`inode number`. 
  * 目录的每个对，即每个条目`entry`，都指向文件或其他目录
  * 目录层次结构从根目录`/`开始

## 创建文件

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

## 读写文件

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

## 不按顺序读取和写入

使用`lseek（）`

```c
off_t lseek(int fildes, off_t offset, int whence);
```

可以看到，对每个进程打开的文件，OS都会跟踪一个当前偏移量`offset`。 要么每次读写后隐式更新，要么通过`lssek（）`指定

## 强制写入

```c
#include <unistd.h>

int fsync(int fildes);
```

一般来说， 程序执行`write（）`系统调用时，文件系统会将写入在内存中缓冲一段时间。 要立即写入，需要`fsync（）`

* 强制写回脏数据

## 文件改名

```c
 int rename(char * oldname, char * newname);
```

* `rename（）`是原子操作

## 获取文件信息

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

## 删除文件

shell命令`rm`使用`unlink（）`系统调用删除文件：

```c
int unlink(const char * pathname);
```

## 目录操作

```c
mkdir() //仅仅列举函数名
opendir()
readdir()
closedir()
rmdir()
```

## 硬链接

通过`link（ old_path_name, new_path_name ）`系统调用创建硬链接。 对应的shell工具是`ln`

```shell
ln far far2  
```

* 硬链接只是对**同一个**inode号创建了新的引用
* 事实上，文件名都只是对`inode`的链接
* 创建文件时，实际上是先创建`inode`，然后将人类可读的名称链接到该文件，并将这个键值对存入目录
* 不能创建目录的硬链接，因为会在目录树中成环
* `inode  number`在不同文件系统中不唯一，因此不能硬链接到其他磁盘分区中的文件

```c
> ls -i                                                                       
    
2536724 far  2536724 far2  //inode number一样

```



## 软链接

也称为符号链接，用`ln -s`

```shell
ln -s  far far3  
```

* 符号链接是一个**不同类型的文件**,
  * `ls`显示，类型为`l`
* 链接指向的内容是指向文件的路径名
  * OS将截获对符号链接文件的访问，,依据符号链接中的路径名去读真正的目标文件
  * 优点： 可链接目录， 可跨文件系统链接
  * 缺点:**搜索文件路径**开销大,需要额外的空间查找存储路径

```shell
> ls -al
drwxr-xr-x 3 lyk lyk  4096 11月 26 22:14 .
drwxr-xr-x 4 lyk lyk  4096 11月 26 22:00 ..
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far
-rwxrwxrwx 2 lyk lyk     6 11月 26 21:41 far2
lrwxrwxrwx 1 lyk lyk     3 11月 26 22:14 far3 -> far  //软链接，内容为目标文件名“far”，是三字节

```



## 创建并挂载文件系统

```
mkfs()
mount()
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


## Locality and FFS

## Crush-Consistency Problem: FSCK and Journalist

## File System Based on Journalist

## Data Integrity and Protection

## Conclusion

