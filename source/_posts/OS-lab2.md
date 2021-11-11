---
title: OS lab2
tags: OS lab
categories: Language
date: 2021-11-11 19:42:50
---


* Outline:
  * PPT内容
  * 实验内容（ 附我的部分代码 ）

<!--more-->

# PPT内容

## 什么是实模式,什么是保护模式?

* 实模式就是用基地址加偏移量就可以直接拿到物理地址的模式
  * 缺点:实模式非常不安全
* 保护模式就是不能直接拿到物理地址的模式
  * 需要进行地址转换
  * 从80386开始,是现代操作系统的主要模式

## 什么是选择子?

* 选择子共16位,放在段选择寄存器里
* 低2位表示请求特权级
* 第3位表示选择GDT方式还是LDT方式
* 高13位表示在描述符表中的偏移(故描述符表的项数最多是2^13)

## 什么是描述符?

* 描述符表中存储的一个元素,是一个指针

## 什么是GDT,什么是LDT?

* GDT:全局描述符表,是全局唯一的。存放一些公用的描述符和包含各进程LDT首地址的描述符。
* LDT:局部描述符表,每个进程都可以有一个。存放本进程内使用的描述符。

## 请分别说明GDTR和LDTR的结构

* GDTR:48位寄存器,高32位放置GDT首地址,低16位放置GDT
  限长(限长决定了可寻址的大小,注意低16位放的不是选择子)
* LDTR:16位寄存器,放置一个特殊的选择子,用于查找当前进
  程的LDT首地址。

## 请说明GDT直接查找物理地址的具体步骤

1. 给出段选择子(放在段选择寄存器里)+偏移量
2. 若选择了GDT方式,则从GDTR获取GDT首地址,用段选择
   子中的13位做偏移,拿到GDT中的描述符
3. 如果合法且有权限,用描述符中的段首地址加上(1)中的偏移量找到物理地址。寻址结束。

## 请说明通过LDT查找物理地址的具体步骤。

1. 给出段选择子(放在段选择寄存器中)+偏移量
2. 若选择了LDT方式,则从GDTR获取GDT首地址,用LDTR中的偏移量（ LDTR内部的选择子 ）做偏移,拿到GDT中的描述符1， 它的内容是LDT的首地址
3. 从描述符1中获取LDT首地址,用段选择子中的13位做偏移,拿到LDT中的描述符2
4. 如果合法且有权限,用描述符2中的段首地址加上(1)中的偏移量找到物理地址。寻址结束。

## 根目录区大小一定么?扇区号是多少?为什么?

* 不一定， 目录区大小为`(RootEntCnt * 32 + BytsPerSec - 1) / BytsPerSec`， 即 取决于BPB中的`RootEntCnt`

* 扇区号为`RsvdSecCnt + NumFATs * FATSz`， 即 引导区的扇区数 + fat表数*每个fat表所占扇区数

## 数据区第一个簇号是多少?为什么?

* 在1.44M软盘上，FAT前三个字节的值是固定的0xF0、0xFF、0xFF，用于表示这是一个应用在1.44M软盘上的FAT12文件系统。本来序号为0和1的FAT表项应该对应于簇0和簇1，但是由于这两个表项被设置成了固定值，簇0和簇1就没有存在的意义了，所以数据区就起始于簇2

## FAT表的作用?

* FAT项的值代表文件的下一个簇号

## 解释静态链接的过程

* 静态链接是指在编译阶段直接把静态库加入到可执行文件中去
* 空间和地址分配 ; 符号解析和重定位

## 解释动态链接的过程

1. 动态链接器自举
   动态链接器本身也是一个不依赖其他共享对象的共享对象，需要完成自举。
2. 装载共享对象
   将可执行文件和链接器自身的符号合并成为全局符号表，开始寻找依赖对象。加载对象的过程可以看做图的遍历过程；新的共享对象加载进来后，其符号将合并入全局符号表；加载完毕后，全局符号表将包含进程动态链接所需全部符号。
3. 重定位和初始化
   链接器遍历可执行文件和共享对象的重定位表，将它们GOT/PLT中每个需要重定位的位置进行修正。完成重定位后，链接器执行.init段的代码，进行共享对象特有的初始化过程（例如C++里全局对象的构造函数）。
4. 转交控制权
   完成所有工作，将控制权转交给程序的入口开始执行。

## 静态链接相关PPT中为什么使用ld链接而不是gcc

* gcc默认动态链接， 当然也可以指定`-static`使用静态链接

* ld也相同（ 所以这二者都可以 ）

## linux下可执行文件的虚拟地址空间默认从哪里开始分配

* 事实上，入口地址的选择取决于链接器

* The script define the following variables used by the loader **ld**:

  ```shell
  #       TEXT_START_ADDR - the first byte of the text segment, after any
  #               headers.
  #       TEXT_BASE_ADDRESS - the first byte of the text segment.
  #       TEXT_START_SYMBOLS - symbols that appear at the start of the
  #               .text section.
  ```

  For example, on GNU/Linux, 

   `/usr/lib/ldscripts/elf_x86_64.x` 或者`ld --verbose |grep SEGMENT_START`

  we see:

  ```shell
  ...
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x400000)); \
      . = SEGMENT_START("text-segment", 0x400000) + SIZEOF_HEADERS;
  ```

  The text-segment mapping values are:

  - **0x08048000** on 32 Bits
  - **0x400000** on 64 Bits

  You can find out more about linker scripts by browsing the linker manual:

  ```shell
  info ld Scripts
  ```

  

* 你也可以手动指定入口地址，比如：

  `gcc -Wl,-Ttext-segment=0x800000 hello_world.c `

  which sets the entry point to 0x800000 (+ the ELF header size, which gets loaded at 0x800000 in memory) instead of the default 0x400000.

* 证据：写一个汇编文件`a.asm`

  ```asm
  main:
      ret
  ```

  `nasm -f elf64 a.asm`

  `ld a.o`

  `readelf -l a.out`

  可以看到：

  ```
  Elf file type is EXEC (Executable file)
  Entry point 0x401000
  There are 2 program headers, starting at offset 64
  
  Program Headers:
    Type           Offset             VirtAddr           PhysAddr
                   FileSiz            MemSiz              Flags  Align
    LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                   0x00000000000000b0 0x00000000000000b0  R      0x1000
    LOAD           0x0000000000001000 0x0000000000401000 0x0000000000401000
                   0x0000000000000001 0x0000000000000001  R E    0x1000
  
   Section to Segment mapping:
    Segment Sections...
     00     
     01     .text 
  ```

  The first (lowest) `LOAD` segment's virtual address is the default load base of the file. You can see it's `0x0000000000400000` for this file.


# 实验相关内容

## 思路

* 用OO方式，构建文件系统树， 对文件系统的所有操作转换为对文件系统树的操作
* 对指令的解析采用工厂模式
* 缺点是没有充分重构， 比如加入异常机制和lamda表达式，太懒了QAQ
  * 并且，这个思路会在程序开始时加载完整个文件系统树，内存占用很高，不符合实际情况。

```C++

class Fat12FileSystemTree
{
public:
    ~Fat12FileSystemTree()
    {
        delete root;
        root = nullptr;
    };

    static Fat12FileSystemTree *init( FILE *fat12, BPB *bpb, DirEntry *rootEntry);
    void initSystemParameters();
    void mountFiles( );//将目录区的数据挂载到文件系统,构造文件树

    Node *searchByPath( const string &path );
    Node *searchByPath( DirNode* parent, const string &path );


public:
    int  BytsPerSec;	//每扇区字节数
    int  SecPerClus;	//每簇扇区数
    int  RsvdSecCnt;	//Boot记录占用的扇区数
    int  NumFATs;	//FAT表个数（默认为2）
    int  RootEntCnt;	//根目录最大文件数
    int  FATSz;	//每个FAT表占用扇区数



private:
    static Fat12FileSystemTree *instance;
    DirEntry *dirEntry;//目录项的指针，每次fread都会被刷新
    DirNode *root;
    BPB *bpb;
    FILE *fat12;



private:
    Fat12FileSystemTree(FILE *fat12, BPB *bpb, DirEntry *rootEntry);
    DirNode *initRoot(); //初始化root节点，name和path均为"/"
    bool isMatch( Node* node, const string & AbsolutePath );

    //    void mountChildren(int startCluster, DirNode *parent);

    void mountFiles( int startClusterNum, DirNode* parent );//递归地将数据区的数据挂载到文件系统树，对文件节点获取其内容，对目录节点进一步递归
    void mountNode( DirEntry*dirEntry, int baseAddr, DirNode *parent );//将给定地址的数据加载进当前目录项（ currentEntry ），再通过当前目录项创建节点
    void loadContent( int startClus, FileNode *fileNode );//加载文件节点的内容

    int getNextClusterNum( int num );//读取FAT表，获取下一个簇号

    bool isValidNodeName(string name);
    string getDirNodeName(string name);
    string getFileNodeName(string name);

};
```

## 主程序

```c++
int main() {

    FILE* fat12 = fopen("../a.img", "rb");	//打开FAT12镜像文件
    BPB *bpb = BPB::init( fat12);
    DirEntry *rootEntry = new DirEntry();

    Fat12FileSystemTree *fileSystem = Fat12FileSystemTree::init(fat12, bpb, rootEntry );

    while( true )
    {
        myPrint("@lyk>");

        vector<string> input_list = handleInput();
        string instructionName = getInstructionName( input_list );
        vector<string> options = getOptions( input_list );
        vector<string> parameters = getParameters( input_list  );


        Instruction *instruction = InstructionFactory:: create( fileSystem, instructionName );
        instruction -> exec( options, parameters );

    }
    return 0;

}
```



## BPB指定字段的含义

```c++
//从软盘的第11Byte开始，到第35Byte, 共25Byte
class BPB {
public:
    u16  BPB_BytsPerSec;	//每扇区字节数
    u8   BPB_SecPerClus;	//每簇扇区数
    u16  BPB_RsvdSecCnt;	//Boot占用的扇区数
    u8   BPB_NumFATs;	//FAT表个数
    u16  BPB_RootEntCnt;	//根目录最大文件数
    u16  BPB_TotSec16;		//逻辑扇区总数
    u8   BPB_Media;		//介质描述符
    u16  BPB_FATSz16;	//每个FAT占用扇区数
    u16  BPB_SecPerTrk;  //	每磁道扇区数（Sector/track）
    u16  BPB_NumHeads;	//磁头数（面数）
    u32  BPB_HiddSec;	//隐藏扇区数
    u32  BPB_TotSec32;	//如果BPB_TotSec16为0，该值为逻辑扇区总数
public:
    static BPB *init(FILE * fat12)
    {
        if( instance == NULL  )
            instance = new BPB( fat12);
        return instance;
    }

private:
    static BPB *instance;
private:
    BPB(FILE* fat12); //读取boot信息
};

BPB* BPB:: instance = nullptr;

BPB:: BPB(FILE* fat12 )
{
    int check;

    //BPB第11个字节处开始
    check = fseek(fat12, 11, SEEK_SET);
    if (check == -1)
        myPrint("fseek in fillBPB failed!\n");

    //BPB长度为25字节
    check = fread( this , 1, 25, fat12);
    if (check != 25)
        myPrint("fread in fillBPB failed!\n");

}
```



## 如何进入子目录并输出(说明方法调用)

* 目录项结构;

  ```C++
  //32Byte per entry, 数据区的目录项也采用此结构
  class DirEntry {
  public:
      char DIR_Name[Dir_Name_Length];
      u8   DIR_Attr;		//文件属性
      char Reserve[10]; //保留位，用于Win NT
      u16  DIR_WrtTime;
      u16  DIR_WrtDate;
      u16  DIR_FstClus;	//开始簇号
      u32  DIR_FileSize;
  };
  ```

* 获得baseAddr。对根目录区而言，只需得到Directory Area 起始地址`baseAddressOfDirArea`，加上 项数 * 32Byte 就是`baseAddressForDirEntry`

  ```C++
  void Fat12FileSystemTree:: mountFiles()
  {
      int baseAddressOfDirArea = ( RsvdSecCnt + NumFATs * FATSz ) * BytsPerSec;// Directory Area 起始地址
  
      int baseAddressForDirEntry = baseAddressOfDirArea;//目录项的起始地址
      for(int i=0 ; i < RootEntCnt; i++ , baseAddressForDirEntry+=32 )
      {
          mountNode( dirEntry, baseAddressForDirEntry, root );
      }
  
  }
  ```

  

* 获得baseAddr,对数据区而言

  * 首先得到数据区起始地址`baseAddressOfDataArea`和当前簇号`currentClusterNum`

  * 得到当前簇的起始地址`baseAddressForCurrentCluster`， 就是该簇第一个的baseAddr`baseAddressForDirEntry`，每次迭代读取一个目录项（32Byte）， 因此`baseAddr += 32`, 

  * 直到到达簇的末尾`baseAddressForCurrentCluster + bytesOfThisCluster`， 通过`fatValue = getNextClusterNum( currentClusterNum )`从fat表中得到下一个簇的簇号。

  * 令`currentClusterNum = fatValue`  ， 不断迭代读取簇，直到文件结束或坏簇

    

  ```C++
  void Fat12FileSystemTree::mountFiles(int startClusterNum, DirNode *parent) {//    parent->createDefaultNodes();    //数据区起始地址，即第一个簇（2号簇）的偏移字节    int baseAddressOfDataArea = BytsPerSec * (RsvdSecCnt + FATSz * NumFATs + (RootEntCnt * 32 + BytsPerSec - 1) / BytsPerSec);    int fatValue = 0; //fat表项的值，代表文件的下一个簇号    int currentClusterNum = startClusterNum;    while( fatValue < 0xFF8 )    {        fatValue = getNextClusterNum( currentClusterNum );//查FAT表获取下一个簇号        if( fatValue == 0xFF7 )        {            myPrint("ERR 读取了坏簇\n");            break;        }        int baseAddressForCurrentCluster = baseAddressOfDataArea + (currentClusterNum - 2)*SecPerClus*BytsPerSec;//当前簇的起始地址        int bytesOfThisCluster = SecPerClus * BytsPerSec; //当前簇的长度        for( int  baseAddressForDirEntry = baseAddressForCurrentCluster ;  baseAddressForDirEntry < baseAddressForCurrentCluster + bytesOfThisCluster ; baseAddressForDirEntry+=32 ) //baseAddressForDirEntry = 当前目录项的起始地址，不能超过该簇        {            mountNode( dirEntry, baseAddressForDirEntry,parent );        }        currentClusterNum = fatValue;//根据fat项更新簇号    }    return; //该目录节点递归完毕}
  ```

  

* 从软盘中读取目录项，并创建节点

  ```C++
  //将baseAddr起始的数据加载进当前目录项（ currentEntry ），再通过当前目录项创建节点void  Fat12FileSystemTree:: mountNode( DirEntry* currentEntry, int baseAddr, DirNode *parent) {    if (fseek(fat12, baseAddr, SEEK_SET) == -1)        myPrint("fseek in mountFiles failed!\n");    if (fread(currentEntry, 1, 32, fat12) != 32)        myPrint("fread in mountFiles failed!\n");    string dirEntryName(&(currentEntry->DIR_Name[0]), &(currentEntry->DIR_Name[Dir_Name_Length]));///起始位置 结束长度位置 +1    if (!isValidNodeName(dirEntryName)) {        return;//目录项名字不合法，不挂载    }    else    {        string realName;        if (dirEntry->DIR_Attr == 0x10) // directory node        {            realName = getDirNodeName(dirEntryName);            DirNode *child = new DirNode(realName, parent->AbsolutePath + realName + "/",                                         currentEntry->DIR_FileSize);   //新建该目录的节点            parent->children.push_back(child);            if(child->isDefaultNode())// . 和 ..不递归            {                ;            }            else            {                parent->dir_count++;                mountFiles(currentEntry->DIR_FstClus, child);            }        } else// file node        {            realName = getFileNodeName(dirEntryName);            FileNode *child = new FileNode(realName, parent->AbsolutePath + realName + "/",                                           currentEntry->DIR_FileSize);   //新建该文件的节点            parent->children.push_back(child);            parent->file_count++;            loadContent(currentEntry->DIR_FstClus, child);//读取文件的内容        }    }}
  ```

  

## 如何获得指定文件的内容,即如何获得数据区的内容(比如使用指针等)

* 对目录节点而言， 就是上文的` mountNode用`，  用 `fseek`和`fread`不断从baseAddr开始读取目录项，用目录项的数据初始化节点

* 对文件节点而言：（ 与 ` mountNode`的逻辑相同，只是懒得重构了）

  ```C++
  //获取文件内容void Fat12FileSystemTree :: loadContent( int startClus, FileNode  *fileNode){    int dataBase = BytsPerSec * (RsvdSecCnt + FATSz * NumFATs + (RootEntCnt * 32 + BytsPerSec - 1) / BytsPerSec);    int currentClus = startClus;    int value = 0;		//这里用value来进行不同簇的读取（超过512字节）    char *p = fileNode -> content;    if (startClus == 0) {        return;    }    while (value < 0xFF8) {        value = getNextClusterNum( currentClus);//获取下一个簇        if (value == 0xFF7                ) {            myPrint("坏簇，读取失败!\n");            break;        }        char* str = (char*)malloc(SecPerClus*BytsPerSec);	//暂存从簇中读出的数据        char *content = str;        int startByte = dataBase + (currentClus - 2)*SecPerClus*BytsPerSec;        int check;        check = fseek(fat12, startByte, SEEK_SET);        if (check == -1)            myPrint("fseek in loadContent failed!");        check = fread(content, 1, SecPerClus*BytsPerSec, fat12);//提取数据        if (check != SecPerClus * BytsPerSec)            myPrint("fread in loadContent failed!");        int count = SecPerClus * BytsPerSec; //簇的字节数        int loop = 0;        for (int i = 0; i < count; i++) {//读取赋值            *p = content[i];            p++;        }        free(str);        currentClus = value;    }}
  ```

  

## 如何进行C代码和汇编之间的参数传递和返回值传递

* 64位linux, 参数传递使用`rdi`, `rsi`

  ```C++
  extern "C" {void asm_print(const char *, const int);}void myPrint(const char *p){    asm_print(p, strlen(p));}
  ```

  

## 汇编代码中对I/O的处理方式,说明指定寄存器所存值的含义

```asm
global	asm_print	section .textasm_print:        mov    rdx,rsi    ;message length        mov    rcx,rdi    ;message to write        mov    rbx,1   ;file descriptor (stdout)        mov    rax,4   ;system call number (sys_write)        int    0x80;call kernel        ret
```

