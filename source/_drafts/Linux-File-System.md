---
title: Linux File System
tags:
---







文本文件：

DOS, UNIX/LINUX， Mac中的文本文件的差别：

DOS文本文件中的换行符使用`CRLF`,而Unix系统使用`LF`， MAC使用`CR`， 现在的MAC OS使用`LF`

In DOS/Windows text files a *line break*, also known as newline, is a combination of two characters: a Carriage Return (CR) followed by a Line Feed (LF). In Unix text files a line break is a single character: the Line Feed (LF). In Mac text files, prior to Mac OS X, a line break was single Carriage Return (CR) character. Nowadays Mac OS uses Unix style (LF) line breaks.





# 挂载



/etc/fstab文件的作用：

​     磁盘被手动挂载之后都必须把挂载信息写入/etc/fstab这个文件中，否则下次开机启动时仍然需要重新挂载。

​    系统开机时会主动读取/etc/fstab这个文件中的内容，根据文件里面的配置挂载磁盘。这样我们只需要将磁盘的挂载信息写入这个文件中我们就不需要每次开机启动之后手动进行挂载了。



挂载的限制：

  在说明这个文件的作用之前我想先强调一下挂载的限制。

1、根目录是必须挂载的，而且一定要先于其他mount point被挂载。因为mount是所有目录的跟目录，其他木有都是由根目录 /衍生出来的。

2、挂载点必须是已经存在的目录。

3、挂载点的指定可以任意，但必须遵守必要的系统目录架构原则

4、所有挂载点在同一时间只能被挂载一次

5、所有分区在同一时间只能挂在一次

6、若进行卸载，必须将工作目录退出挂载点（及其子目录）之外。

/etc/fstab文件记录了挂载信息，系统开机时会主动读取/etc/fstab这个文件中的内容，根据文件里面的配置挂载磁盘。磁盘被手动挂载之后都必须把挂载信息写入/etc/fstab这个文件中，否则下次开机启动时仍然需要重新挂载

/etc/fstab文件的每一行都遵循以下格式：

```xml
<device>        <dir>         <type>    <options>             <dump> <pass>
```

- **device**：指定加载的磁盘分区或移动文件系统，除了指定设备文件外，也可以使用UUID、LABEL来指定分区；
- **dir**：指定挂载点的路径；
- **type**：指定文件系统的类型，如ext3，ext4等；
- **options**：指定挂载的选项，默认为defaults，其他可用选项包括acl，noauto，ro等等；
- **dump**：表示该挂载后的文件系统能否被dump备份命令作用；0表示不能，1表示每天都进行dump备份，2表示不定期进行dump操作。
- **pass**：表示开机过程中是否校验扇区；0表示不要校验，1表示优先校验（一般为根目录），2表示为在1级别校验完后再进行校验；



# 制作ISO

1、把光盘复制成ISO文件方法一。把光盘放入光驱，系统会自动挂载光盘，桌面上出现光盘图标，用鼠标右键点击光盘图标选择“复制光盘”，在出现的对话框里选择制作镜像文件即可。
2、把光盘复制成ISO文件方法二。假设光盘设备文件是/dev/cdrom，使用如下命令即可
\#cp /dev/cdrom filename.iso
上述命令把光盘复制生成一个ISO文件filename.iso。

文件和目录制作成ISO：
使用 mkisofs 命令
\#mkisofs -o filename.iso dir1 dir2 file1 file2
上述命令会把目录dir1、dir2和文件file1、file2一起制作成一个ISO文件filename.iso
ISO文件的使用：
要使用ISO文件，只需要把该ISO文件挂载到系统的某个空目录即可，比如：
\#mkdir /mnt/iso
\#mount -o loop filename.iso /mnt/iso
上述命令会把ISO文件filename.iso挂载到/mnt/iso目录里，访问 /mnt/iso目录即是访问ISO文件里的内容。
