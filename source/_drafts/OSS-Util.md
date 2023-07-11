---
title: OSS Util
tags:
---



https://help.aliyun.com/document_detail/50452.html



## 安装ossutil

有关ossutil的下载及安装的具体操作，请参见[安装ossutil](https://help.aliyun.com/document_detail/120075.html#concept-303829)。

## 配置ossutil

有关ossutil的配置的具体操作，请参见[配置ossutil](https://help.aliyun.com/document_detail/474474.html#task-2284742)。



列举所有Bucket

```bash
./ossutil64 ls
```

或

```bash
./ossutil64 ls oss://
```



## 列举Object

- 命令格式

  ```bash
  ./ossutil64 ls oss://bucketname[/prefix] [-s] [-d] [--limited-num] [--marker] [--include] [--exclude]  [--version-id-marker] [--all-versions]
  ```

  





# cp



批量上传符合条件的文件

批量上传时，如果指定**--include**和**--exclude**选项，ossutil会批量上传符合指定条件的文件。



示例如下：

- 上传所有文件格式为TXT的文件

  ```bash
  ./ossutil64 cp localfolder/ oss://examplebucket/desfolder/ --include "*.txt" -r
  ```

- 上传所有文件名包含abc且不是JPG和TXT格式的文件:

  ```bash
  ./ossutil64 cp localfolder/ oss://examplebucket/desfolder/ --include "*abc*" --exclude "*.jpg" --exclude "*.txt" -r
  ```



# [如何获取单个或多个文件（Object）的URL](https://help.aliyun.com/document_detail/39607.html#section-mfq-69s-o76)

公共读Object:

如果文件的读写权限ACL为公共读，即该文件允许匿名访问，则文件URL的格式为`https://BucketName.Endpoint/ObjectName`。其中，ObjectName需填写包含文件夹以及文件后缀在内的该文件的完整路径。各地域的Endpoint信息介绍，请参见[访问域名和数据中心](https://help.aliyun.com/document_detail/31837.html#concept-zt4-cvy-5db)。

例如华东1（杭州）地域下名为examplebucket的Bucket下有名为example的文件夹，文件夹内有个名为example.jpg的文件。则该文件URL为：

- 外网访问URL：`https://examplebucket.oss-cn-hangzhou.aliyuncs.com/example/example.jpg`
- 内网访问URL（供同地域ECS实例访问）：`https://examplebucket.oss-cn-hangzhou-internal.aliyuncs.com/example/example.jpg`

**重要**

- 如果文件所在的Bucket绑定了自定义域名，则文件URL的格式为

  ```
  https://YourDomainName/ObjectName
  ```

  例如您在华东1（杭州）地域下的examplebucket绑定了自定义域名`example.com`，且该Bucket下包含example.jpg的文件，则该文件URL为`https://example.com/example.jpg`。

- 如需确保通过文件URL访问文件时是预览行为，您需要绑定自定义域名并添加CNAME记录。详情请参见[控制台使用自有域名访问OSS资源](https://help.aliyun.com/document_detail/195675.html#task-2010682)。





## 获取多个文件的URL

无法在CLI完成.

