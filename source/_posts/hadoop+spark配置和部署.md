---
title: hadoop+spark配置和部署
tags:  Cloud Computation
categories: Software Engineering
---



云计算第一次作业

Outline：

* spark + hadoop（这部分由191250071撰写，感谢这位同学）
* For Manjaro用户

<!--more-->

# spark + hadoop

## spark集群部署

华为云服务器配置如下：

| 规格名称     | vCPUs \|内存           | CPU                       | 基准/最大带宽 |
| ------------ | ---------------------- | ------------------------- | ------------- |
| c6s.large.2  | 2vCPUs \| 4 GiB        | Intel Cascade Lake 2.6GHz | 1 / 1 Gbit/s  |
| **操作系统** | **操作系统版本**       |                           |               |
| CentOS       | CentOS 8.2 64bit(40GB) |                           |               |



方便的做法是所有节点均适用`root`账户，hadoop安装在`/usr/local`，但是，严谨的做法是使用用户账户，此时为了避免权限问题，hadoop需要安装在`~`

* 如果使用root账户，环境变量一般使用`~/.bashrc`之类
* 使用普通账户，我就用了`~/.zshrc`来配置环境变量



这里我均使用普通账户lyk

## 更改主机名称，添加hosts配置

1. 使用vim更改主机名称为master、slave01、slave02、slave03

```shell
vim /etc/hostname
```

重启服务器确认名称已经改变

2. 添加hosts配置

```
# vim /etc/hosts
```

master中加入如下配置

```
127.0.0.1 localhost //如果本来就有这条就不用加了
<master的内网ip> master
<slave01的公网ip> slave01
<slave02的公网ip> slave02
<slave03的公网ip> slave03
```

* 这里增加`master`后，之后的命令会调用`ssh lyk@master`， 因此需要配置好本机到master（也是本机）的免密登陆， 是的，**本机到本机也需要配置免密登陆！！！**



slave中加入如下配置

```
172.0.0.1 localhost //如果本来就有这条就不用加了
<master的公网ip> master
<slave01的公网ip> slave01
<slave02的公网ip> slave02
<slave03的公网ip> slave03
```

## 配置无密码登录本机和访问集群机器

## 安装openssh-server，并生成ssh公钥

1. 运行如下命令安装openssh-server

```
# yum install openssh-server
```

2. 运行如下命令生成密钥

```
# ssh-keygen -t rsa -P ""
```

一路回车指导成功生成密钥即可。

3. 运行如下命令将密钥放进`authorized_keys`中

```
# cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys
```

4. 尝试如下命令

```
# ssh localhost
```

第一次登陆可能会让你确认，输入`yes`后回车即可，如果出现如下信息则说明登录成功：

```
        Welcome to Huawei Cloud Service

Last login: Fri Oct 15 14:02:37 2021 from 122.9.164.198
```

5. (仅master)通过如下命令将`id_sra.pub`发送给slave

```
scp ~/.ssh/id_rsa.pub root@slave01:/
scp ~/.ssh/id_rsa.pub root@slave02:/
scp ~/.ssh/id_rsa.pub root@slave03:/
```

## 实现无密码登录slave



1. 使用如下命令将密钥添加进slave的`authorized_keys`中

```
# cat /id_rsa.pub >> /root/.ssh/authorized_keys
```

## 安装JDK

强烈建议通过安装包的方式安装java，因为这样可以指定目录， 因为JAVA环境变量是写在`hadoop-env.sh`里的，所有节点拷贝一份。 如果指定了java目录，那么所有节点只需把jdk安装在相同目录即可。 



当然，由于我所有节点都是ubuntu20.04， 直接`sudo apt-get install openjdk-8-jdk `a安装到目录`/usr/lib/jvm/java-8-openjdk-amd64`, 所有节点都这样（安装到相同的目录）， 因此只要所有节点都通过该指令安装jdk，也可以做到环境变量的同步



下面介绍安装包的方式：

1. 将`jdk-8u301-linux-x64.tar.gz`保存在根目录
2. 运行如下命令

```shell
mkdir /usr/local/java
tar -zxvf /jdk-8u301-linux-x64.tar.gz -C /usr/local/java
```

3. 添加环境变量, 

```shell
vim ～/.zshrc
```



将下面的内容添加至末尾

```
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=$PATH:${JAVA_HOME}/bin
```

4. 退出vim，运行如下命令来使得配置生效

```
# source /etc/profile
```

5. 使用如下命令来确认是否已经安装完成

```
java -version
```

​	应该看到下面的输出

```
java version "1.8.0_301"
Java(TM) SE Runtime Environment (build 1.8.0_301-b09)
Java HotSpot(TM) 64-Bit Server VM (build 25.301-b09, mixed mode)
```

## 安装和配置Hadoop

这里用lyk用户， 而不是root用户

### 安装（ on master ）

1. 将hadoop-3.2.3.tar.gz拷贝到master服务器上
2. 使用如下命令在master上安装hadoop

```shell
tar -zxvf hadoop-3.2.3.tar.gz -C ~
cd ~
mv ./hadoop-3.2.3 ./hadoop #修改文件夹名称为hadoop
```

3. 添加Hadoop的环境变量

   ```shell
   vim /root/.bashrc # 实际我用的是～/.zshrc
   ```

   将以下内容添加到末尾

   ```shell
   export HADOOP_HOME=/usr/local/hadoop
   export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
   ```

4. 查看hadoop版本

   ```shell
   hadoop version
   ```

   

### 配置（ on master）

所有配置文件都位于目录`~/hadoop/etc/hadoop/`中

1. 修改`workers`为：

   ```
   slave01
   slave02
   slave03
   ```

   workers文件默认内容是`localhost`,这里把它删除了。 如果用单机版hadoop，则保留localhos,且不需要添加slave





2. 修改core-site.xml

   ```xml
    <configuration>
         <property>
             <name>hadoop.tmp.dir</name>
             <value>file:/usr/local/hadoop/tmp</value>
             <description>Abase for other temporary directories.</description>
         </property>
         <property>
             <name>fs.defaultFS</name>
             <value>hdfs://master:9000</value>
         </property>
    </configuration>
   ```

   请注意属性`hadoop.tmp.dir`的值,需要创建该目录（这里就需要创建`/usr/local/hadoop/tmp`）

3. 修改`hdfs-site.xml`

   ```xml
   <configuration>
       <property>
           <name>dfs.replication</name>
           <value>3</value>
   		</property>
   
   <property>
   	<name>dfs.namenode.name.dir</name>
   	<value>file:/home/lyk/hadoop/dfs/name</value>
   </property>
   
   <property>
   	<name>dfs.datanode.data.dir</name>
   	<value>file:/home/lyk/hadoop/dfs/data</value>
   </property>
     
   	<property>
       <name>dfs.blocksize</name>
       <value>134217728</value>
   	</property>
   
   	<property>
       <name>dfs.webhdfs.enabled</name>
       <value>true</value>
       <description>必须将dfs.webhdfs.enabled属性设置为true，否则就不能使用webhdfs的LISTSTATUS、LISTFILESTATUS等需要列出文件、文件夹状态的命令，因为这些信息都是由namenode来保存的</description>
   	</property>
     
   	<property>
     	<name>dfs.http.address</name>
     	<value>master:50070</value>
     	<description>hadoop的webUI访问页面</description>
   	</property>
     
   </configuration>
   ```

   * 注意， replicatoin数量即worker数量，这里有3个worker
   * 由于采用lyk用户，所以namenode和datanode目录都设在lyk用户目录下（ `/home/lyk/hadoop/dfs` ）

4. 修改`mapred-site.xml`

   ```xml
   <configuration>
       <property>
           <name>mapreduce.framework.name</name>
           <value>yarn</value>
       </property>
   </configuration>
   ```

5. 修改`yarn-site.xml`

   ```xml
   <configuration>
   
   <!-- Site specific YARN configuration properties -->
     <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
     </property>
   
     <property>
        <name>yarn.resourcemanager.hostname</name>
        <value>master</value>
     </property>
   
     <property>
       <name>yarn.resourcemanager.webapp.address</name>
       <value>master:8099</value>
     </property>
   
   </configuration>
   ```

   * `yarn.resourcemanager.webapp.address`是hadoop的master的管理页面

6. 在`hadoop-env.sh`中配置`JAVA_HOME`, 先找到本机的JAVA_HOME， 这里是`/usr/lib/jvm/java-8-openjdk-amd64`，在`hadoop-env.sh`中添加：

   ```shell
   export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
   export HDFS_NAMENODE_USER=lyk
   export HDFS_DATANODE_USER=lyk
   export HDFS_SECONDARYNAMENODE_USER=lyk
   export YARN_RESOURCEMANAGER_USER=lyk
   export YARN_NODEMANAGER_USER=lyk
   ```

   * 注意，该文件内本来有一个`export JAVA_HOME=$JAVA_HOME`， 但是该配置不知道为什么无效，所以需要换成显式的JAVA_HOME
   * 由于用户是lyk，所以这里是lyk

7. 验证`hadoop-env.sh`中 JAVA_HOME 配置是否正确：

   ```shell
   hadoop version 
   
   # 输出为：
   Hadoop 3.2.3
   Source code repository https://github.com/apache/hadoop -r abe5358143720085498613d399be3bbf01e0f131
   Compiled by ubuntu on 2022-03-20T01:18Z
   Compiled with protoc 2.5.0
   From source with checksum 39bb14faec14b3aa25388a6d7c345fe8
   This command was run using /usr/local/hadoop/share/hadoop/common/hadoop-common-3.2.3.jar
   ```

   ​			

8. 将配置好的hadoop打包

   ```shell
   cd /usr/local/
   rm -rf ./hadoop/tmp
   rm -rf ./hadoop/logs/*
   tar -zcvf /hadoop.master.tar.gz ./hadoop
   ```

9. 将打包好的hdoop发送给slave

   ```shell
   scp /hadoop.master.tar.gz lyk@slave01:~ 
   scp /hadoop.master.tar.gz lyk@slave02:~ 
   scp /hadoop.master.tar.gz lyk@slave03:~ 
   ```

   * 如果传输较慢，建议用`CMD &`， 将命令放在后台执行
     * 如果是首次ssh连接的话， 还需要对ssh公钥确认输入`yes`，所以这个命令就不能直接放入后台执行，需要先确认一次。 之后再使用该命令都不需要确认，也就可以放到后台了





### 安装（ on slave ）

1. 只要把master的hadoop文件夹发给slave就行了，这里我采用压缩包方式发送。注意需要先删除slave上原有的hadoop（如果有的话) :

   运行如下命令, 删除原有的hadoop根目录( 如果有的话 )并将新的压缩包（master发来的）解压
   
   ```shell
   rm -rf /usr/local/hadoop
   sudo tar -zxvf ~/hadoop.master.tar.gz  -C /usr/local
   ```
   
   

### 启动Hadoop

1.**格式化HDFS**
注意在首次使用时使用，若重复格式化，将无法开启datanode

```bash
cd ~/hadoop/bin
hdfs namenode -format
```

* 初始化之前需要删掉配置文件的tmp目录下的所有内容
* 如果不初始化，则启动时无法启动namenode

2. 在master上输入以下命令启动Hadoop

```shell
cd /usr/local/hadoop
```

```shell
./sbin/start-all.sh
```



1. 检验hadoop是否已经启动

   ```shell
   jps
   ```

   

   在master上应该有类似如下输出:

   ```
   1879 NameNode
   2169 SecondaryNameNode
   873 WrapperSimpleApp
   5530 Jps
   2427 ResourceManager
   ```

   主要关注`NameNode`、`ResourceManager`、`SecondaryNameNode`这三条是否存在，如果不存在则应该去`/usr/local/hadoop/logs/`目录下寻找相应地日志查看错误信息

   

   在slave上输入jps应该有类似如下输出

   ```
   4406 Jps1914 
   NodeManager1787 
   DataNode
   ```

   主要关注`NodeManager`、`DataNode`这两条是否存在，如果不存在同样去`/usr/local/hadoop/logs/`目录下寻找相应地日志查看错误信息

   * 我发现某个slave的datanode没有启动，查看其`hadoop-lyk-datanode-VM-4-7-ubuntu.log`发现，原来是xml配置文件写错了。。



2. 查看hadoop webUI：

   ```
   <master-ip>:50070
   ```

   * 在`hdfs-site.xml`中配置

### 关闭hadoop



如果关闭Hadoop(`~/hadoop/sbin/start-all.sh` ),则所有节点的jps都不会有与hadoop关联的输出

# Spark

注意到Spark3预装了Scala2.12， 而Spark 3.2+预装了Scala 2.13

由于hadoop版本是3.2.3,因此只能下载配套的Sprak3.13

由于已经安装了hadoop，就选择安装不带hadoop的Spark，即`spark-3.1.3-bin-without-hadoop.tgz`

## 安装（master）

1. 下载`spark-3.1.3-bin-hadoop3.2.tgz`， 将其拷贝到master( 这里我拷贝到了`/` )

2. 解压并改名

   ```shell
   tar -zxvf /spark-3.1.3-bin-hadoop3.2.tgz -C /usr/local/
   ```

   ```shell
   cd /usr/local
   ```

   ```shell
   mv ./spark-3.1.2-bin-without-hadoop/ ./spark
   ```

## 配置

1. 改名配置文件：

   ```shell
   cd ~/spark/
   ```

   ```shell
   cp ./conf/spark-env.sh.template ./conf/spark-env.sh
   cp ./conf/workers.template ./conf/workers
   ```

   

2. 修改workers文件的内容，将原来的内容替换成：

   ```
   master
   slave01
   slave02
   slave03
   ```

3. 在spark-env.sh的末尾添加如下内容

```shell
export SPARK_DIST_CLASSPATH=$($(HOME)/hadoop/bin/hadoop classpath)
export HADOOP_CONF_DIR=$(HOME)/hadoop/etc/hadoop#
export SCALA_HOME=/usr/lib/scala/scala-2.13.3 
export HADOOP_HOME=$(HOME)/hadoop
export SPARK_MASTER_IP=<master的公网ip> #指定 Spark 集群 Master 节点的 IP 地址 
export SPARK_MASTER_PORT=7077export SPARK_MASTER_HOST=masterexport SPARK_EXECUTOR_MEMORY=4096m #大小看虚拟机内存
export SPARK_LOCAL_IP=localhost
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
```

* 注意，由于我并没有安装scala所以不添加SCALA_HOME，而是添加JAVA_HOME。此外，由于出现了类似于如下的worker日志报错，我添加了`SPARK_LOCAL_IP`
* 这里填hadoop的目录， 我在`hadoop-env.sh`中指定了



3. 使用如下命令将配置好的spark打包发送给slave

```
cd /usr/local/
tar -zcvf /spark.master.tar.gz ./spark
scp /spark.master.tar.gz slave01:/
scp /spark.master.tar.gz slave02:/
scp /spark.master.tar.gz slave03:/
```

**安装（slave）：**

1. 使用如下命令在slave上安装spark

```
# rm -rf /usr/local/spark/# tar -zxvf /spark.master.tar.gz -C /usr/local
```

**启动spark**

==在启动之前先修改master的spark-env.sh文件，将其中的`SPARK_LOCAL`注释掉，不然就只能从服务器内网的localhost来访问spark的webui了（我也不知道为啥。。。）==

1. 先按照之前的步骤启动Hadoop
2. 启动spark

```
# cd /usr/local/spark/# sbin/start-all.sh
```

### Bugs

* jps没有输出

  `jps`是查看java进程的工具，java程序启动以后，会在`/tmp`目录下生成一个`hsperfdata_[username]`的文件夹，其中的文件以java进程的pid命名。因此使用jps查看当前进程，其实就是把`/tmp/hsperfdata_username`中的文件名遍历一遍之后输出。

  

  情况1:

  如果`/tmp/hsperfdata_[username]`的文件所有者和文件所属用户组与启动进程的用户不一致的话，在进程启动之后，就没有权限写`/tmp/hsperfdata_[username]`，所以`/tmp/hsperfdata_[username]`是一个空文件，理所当然jps也就没有任何显示。

  

  情况2:

  不知道为啥，重启服务器就好了。。。



* nodemanager running as process 6410. Stop it first.

  进程已经在运行中了，先执行`stop-all.sh`下]，再执行`start-all.sh`



* Permission denied

  文件所有权的问题， 如果以root身份安装Hadoop（比如一开始把hadoop放在`/usr/local`），然后又想用普通用户来使用hadoop（比如之后把hadoop放在`~`)，就会发生此问题，只需要更改hadoop的所有权:

  ```shell
  chown -R lyk:lyk ~/hadoop
  ```

  

# For Manjaro用户

这里演示一下Manjaro/arch用户安装hadoop的流程，只开个头。剩余的hadoop配置和spark安装及配置也大同小异。主要是对于manjaro/arch用户来说，安装这类软件会有一些小坑

* `sudo pacman -Syu`

*  安装jdk：`yay -S jdk`

* 安装openssh：`yay -S openssh`

  * manjaro默认不安装openssh

* 创建hadooop用户并且更改hadoop用户密码

  ```shell
  //创建hadoop用户
  sudo adduser hadoop
  
  //更改hadoop用户密码
  sudo passwd hadoop
  ```

  * **manjaro默认不安装`adduser`命令，要使用`useradd`**
  * 如果`yay -S adduser`,这个安装的命令默认是在/etc内创建用户，而不是（如centos中自带的`adduser`）在root目录下，因此路径会不一样，在配置环境变量时需要注意。

* 以上的配置完成之后，使用hadoop用户

  ```
  su - hadoop
  ```

  切换成hadoop之后，设置ssh免密登录

  ```
  ssh-keygen -t rsa 
  
  cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys 
  
  chmod 640 ~/.ssh/authorized_keys 
  ```

  然后试试`ssh localhost`，查看是否能够免密登录

  > 如果遇到22端口被拒绝的情况，很有可能是ssh服务并没有开启。
  > 切换成exit退出当前用户，使用主用户
  > 输入`sudo service ssh start`进行服务的开启。如果显示没有该服务，那么可以确定系统并没有安装openssh, 去安装。

* Archlinux或者manjaro开启ssh服务命令:

  `systemctl enable sshd.service`     开机启动

  `systemctl start sshd.service`      立即启动

  `systemctl restart sshd.service`    立即重启

* 用户hadoop使用`su`可能会报错：

  `hadoop is not in the sudoers file.  This incident will be reported.`，需要在/etc/sudoers文件里给该用户添加权限 （[ref](https://www.cnblogs.com/MakeView660/p/12395542.html)）

  



