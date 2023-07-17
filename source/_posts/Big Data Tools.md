---
title: Big Data Tools
tags: Cloud Computation
categories: Technology
date: 2022-04-10 12:00:00
---

Outline：

* 集群简介
* Hadoop
* Spark
* Hadoop + Spark For Manjaro
* Hadoop + Spark For Mac
* Clickhouse
* Flink
* Kafka( //TODO )

<!--more-->

# Hadoop + Spark 集群报告

> 这是hadoop+spark集群搭建的报告，当然集群太卡了用不了， 所以实际做作业我采用了单机( on Mac M1 )形式[hadoop  2.7.4](https://archive.apache.org/dist/hadoop/common/hadoop-2.7.4/hadoop-2.7.4-src.tar.gz ) + [spark 2.3.3](.https://archive.apache.org/dist/spark/spark-2.3.3/spark-2.3.3-bin-without-hadoop.tgz    ) + [scala  2.11.12](https://scala-lang.org/download/2.11.12.html ) + `jdk8 `
>
> 这只是hadoop+spark集群搭建的报告， 不包括Clickhouse、Flink的内容； 可以作为hadoop+spark单机搭建的参考

hadoop+spark集群搭建完毕

hadoop, spark低版本和高版本没有任何区别，只是高版本的spark，hadoop的worker(s)文件， 在低版本中名为slaves

单机和集群也没有什么区别，只是不需要配置worker的DNS了，由于maser和worker都是本机，就直接让localhost做唯一的worker。

* 这意味着hadoop、spark的worker文件不需要做任何更改（里面默认值就是localhost）
* 主机只需配置master的DNS
* `hdfs-site.xml`中的dfs.replication数量应该设为1，因为只有本机自己一个worker





## 集群部署

云服务器配置如下：

| 拥有者 | ip             | role    |
| ------ | -------------- | ------- |
| lyk    | 124.222.135.47 | master  |
| sgf    | 81.69.174.80   | slave01 |
| lss    | 47.93.158.241  | slave02 |
| xmt    | 175.27.136.106 | slave03 |
|        |                |         |

方便的做法是所有节点均适用`root`账户，hadoop安装在`/usr/local`，但是，严谨的做法是使用用户账户，此时为了避免权限问题，hadoop需要安装在`~`

* 所有节点均使用用户lyk
* 使用`/home/lyk/.bashrc`（或者`.zshrc`）来配置环境变量



由于所有服务器都不在同一局域网，因此都采用公网通信。 实际上十分不推荐公网通信，太慢了







## 集群网络

1. 对于master和slave节点，配置其DNS表(.`/etc/hosts` )， 其中增加:

   ```
   127.0.0.1 localhost //如果本来就有这条就不用加了
   <master的内网ip> master //对于master而言，这里直接填127.0.0.1
   <slave01的公网ip> slave01
   <slave02的公网ip> slave02
   <slave03的公网ip> slave03
   ```

2. 配置master自己到自己的ssh免密登陆

   * 这里增加`master`后，之后的命令会调用`ssh lyk@master`， 因此需要配置好本机到master（也是本机）的免密登陆， 是的，**本机到本机也需要配置免密登陆！！！**

3. 配置master对所有slave的ssh免密登陆

   * 不需要配置shave对其他节点的免密登陆



master需要开放相应端口：

* hadoop:
  * 8099
  * 50070
  * 9000
* spark:
  * 7077
  * 18080



## 集群用户

所有节点采用lyk用户

## 集群环境

这里的环境是集群的环境，与我做作业时单机配置的版本不同

注意，hadoop+spark+scala的版本管理非常混乱，因此要**严格按照文档里的版本来安装**（要么用下面集群这套( hadoop3.2.3... )， 要么用上面单机那套（hadoop2.7.4...））



除了jdk和scala， 其他用户软件都安装在lyk用户目录下

* JDK：`usr/lib/jvm/java-8-openjdk-amd64`
  * `sudo apt-get install openjdk-8-jdk`
* scala: `/usr/local/scala`
  * `scala-2.12.15`
* hadoop: `/home/lyk/hadoop`
  * `hadoop-3.2.3`
* spark: `/home/lyk/spark`
  * `spark-3.1.3`



**spark和hadoop均是先在master上安装，并进行一些配置，最后打包发给slave**

spark是scala实现，hadoop是java实现，二者都运行在JVM上， 因此都可以使用JVM进程查看工具`jps`进行查看

### 环境变量

`/home/lyk/.bashrc`中一共需要配置如下环境变量：

```shell
# JAVA_HOME
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib

# SCALA_HOME
export SCALA_HOME=/usr/local/scala
export PATH=$PATH:${JAVA_HOME}/bin:$SCALA_HOME/bin

#HADOOP_HOME
export HADOOP_HOME=/home/lyk/hadoop
export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
```

### hadoop安装

下载hadoop安装包，传到服务器上，改名，配置环境变量

1. [下载hadoop安装包](https://hadoop.apache.org/release/3.2.3.html)

1. 将hadoop-3.2.3.tar.gz拷贝到master服务器上

2. 在master上将hadoop压缩包解压并改名

   ```
   tar -zxvf hadoop-3.2.3.tar.gz -C ~
   cd ~
   mv ./hadoop-3.2.3 ./hadoop #修改文件夹名称为hadoop
   ```

3. 添加Hadoop的环境变量

   ```shell
   vim ~/.bashrc # 实际我用的是～/.zshrc
   ```

   将以下内容添加到末尾：

   ```shell
   export HADOOP_HOME=/home/lyk/hadoop
   export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
   ```

4. 查看hadoop版本

   ```shell
   hadoop version
   ```

   * 这一命令对所有节点都有效(包括slave)，可以查看hadoop是否被正确安装

### spark安装

spark会预装scala，位于其jar文件夹内，但我没有使用内置的scala，而是自己下载了一个

注意到Spark3预装了Scala2.12， 而Spark 3.2+预装了Scala 2.13

* 我的集群hadoop版本是3.2.3, 与Sprak3.1.3配套， 因此就选择Sprak3.1.3, 而后者对应Scala版本是`2.12`



由于已经安装了hadoop，就选择安装不带hadoop的Spark，即`spark-3.1.3-bin-without-hadoop.tgz`

1. [下载`spark-3.1.3-bin-without-hadoop.tgz`](https://dlcdn.apache.org/spark/spark-3.1.3/spark-3.1.3-bin-without-hadoop.tgz)

1. 将压缩包拷贝到master( 这里我拷贝到了`/` )

2. 解压并改名

   ```shell
   tar -zxvf spark-3.1.3-bin-without-hadoop.tgz -C /usr/local/
   ```

   ```shell
   cd /home/lyk
   ```

   ```shell
   mv ./spark-3.1.2-bin-without-hadoop/ ./spark
   ```

### scala

1. [下载安装包](https://scala-lang.org/download/2.12.15.html)
2. 解压到对应目录（我放在`/usr/local`）并改名为scala
3. 配置环境变量`$SCALA_HOME`, 这一步在上文“环境变量”已经做好了

### JDK

强烈建议通过安装包的方式安装java，因为这样可以指定目录， 因为JAVA环境变量是写在`hadoop-env.sh`里的，所有节点拷贝一份。 如果指定了java目录，那么所有节点只需把jdk安装在相同目录即可。 



（我采用了直接`apt-get install`对方式）

由于我所有节点都是ubuntu20.04， 直接`sudo apt-get install openjdk-8-jdk `安装到目录`/usr/lib/jvm/java-8-openjdk-amd64`, 所有节点都这样（安装到相同的目录）， 因此只要所有节点都通过该指令安装jdk，也可以做到环境变量的同步



下面介绍安装包的方式：

1. 将`jdk-8u301-linux-x64.tar.gz`保存在根目录
2. 运行如下命令

```shell
mkdir /usr/local/java
tar -zxvf /jdk-8u301-linux-x64.tar.gz -C /usr/local/java
```

3. 添加环境变量, 

```shell
vim ～/.bashrc
```



将下面的内容添加至末尾

```shell
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=$PATH:${JAVA_HOME}/bin
```

4. 退出vim，运行如下命令来使得配置生效

```shell
source ~/.bashrc
```

5. 使用如下命令来确认是否已经安装完成

```shell
java -version
```

​	应该看到如下输出：

```
java version "1.8.0_301"
Java(TM) SE Runtime Environment (build 1.8.0_301-b09)
Java HotSpot(TM) 64-Bit Server VM (build 25.301-b09, mixed mode)
```

## 集群页面

正确启动hadoop和spark后，应该能看到二者的webUI页面：

* hadoop：`<master-ip>:50070`
* spark: `<master-ip>:18080`

# Hadoop

## 配置（ on master）

所有配置文件都位于目录`~/hadoop/etc/hadoop/`中

1. 修改`workers`为：

   ```
   slave01
   slave02
   slave03
   ```

   workers文件默认内容是`localhost`,这里把它删除了。 如果用单机版hadoop，则保留localhost,且不需要添加slave





2. 修改core-site.xml

   ```xml
    <configuration>
         <property>
             <name>hadoop.tmp.dir</name>
             <value>file:/home/lyk/hadoop/tmp</value>
             <description>Abase for other temporary directories.</description>
         </property>
         <property>
             <name>fs.defaultFS</name>
             <value>hdfs://master:9000</value>
         </property>
    </configuration>
   ```

   请注意属性`hadoop.tmp.dir`的值,需要创建该目录（这里就需要创建`/home/lyk/hadoop/tmp`）

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
       <description>必须将dfs.webhdfs.enabled属性设置为true，否则就不能使用webhdfs的LISTSTATUS、LISTFILESTATUS等需要列出文件、文件夹状态的命令，因为这些信息都是由namenode来保存的</description>
       <value>true</value>
   	</property>
     
   	<property>
     	<name>dfs.http.address</name>
     	<value>master:50070</value>
     	<description>hadoop的webUI访问页面</description>
   	</property>
     
   </configuration>
   ```

   * 注意， replicatoin数量即worker数量，这里有3个worker； 如果是单机，那么只有1个worker（就是本机）
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

   * 在hadoop2.X中，该文件内容名为`mapred-site.xml.template`，需要先改名为`mapred-site.xml`，再编辑

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
   
   * 注意，该文件内本来有一个`export JAVA_HOME=${JAVA_HOME}`， 但是该配置不知道为什么无效，所以需要换成显式的JAVA_HOME
   * 由于用户是lyk，所以这里是lyk			
   
8. 将配置好的hadoop打包

   ```shell
   cd ~
   rm -rf ./hadoop/tmp
   rm -rf ./hadoop/logs/*
   tar -zcvf hadoop.master.tar.gz ./hadoop
   ```

9. 将打包好的hdoop发送给slave

   ```shell
   scp hadoop.master.tar.gz lyk@slave01:~ 
   scp hadoop.master.tar.gz lyk@slave02:~ 
   scp hadoop.master.tar.gz lyk@slave03:~ 
   ```

   * 如果传输较慢，建议用`CMD &`， 将命令放在后台执行
     * 如果是首次ssh连接的话， 还需要对ssh公钥确认输入`yes`，所以这个命令就不能直接放入后台执行，需要先确认一次。 之后再使用该命令都不需要确认，也就可以放到后台了

## 安装（ on slave ）

1. 只要把master的hadoop文件夹发给slave就行了，这里我采用压缩包方式发送。注意需要先删除slave上原有的hadoop（如果有的话) :

   运行如下命令, 删除原有的hadoop根目录( 如果有的话 )并将新的压缩包（master发来的）解压
   
   ```shell
   rm -rf /usr/local/hadoop
   tar -zxvf ~/hadoop.master.tar.gz  -C ~
   ```
   
   然后改名为`hadoop`

## 启动Hadoop

1. **格式化HDFS**:注意在首次使用时使用，若重复格式化，将无法开启datanode

   ```bash
   cd ~/hadoop/bin
   hdfs namenode -format
   ```

   * 初始化之前需要删掉配置文件的tmp目录下的所有内容
   * 如果不初始化，则启动时无法启动namenode
   * 最终会输出SHUTTING DOWN....

2. 在master上输入以下命令启动Hadoop

   ```shell
   cd ~/hadoop
   ```

   ```shell
   ./sbin/start-all.sh
   ```


## 查看Hadoop是否启动

1. 检验hadoop是否已经启动

   ```shell
   jps
   ```

   在master上应该有类似如下输出:

   ```
   28848 NameNode
   29122 ResourceManager
   29234 Jps
   29016 SecondaryNameNode
   28921 DataNode
   29199 NodeManager
   ```

   主要关注`NameNode`、`ResourceManager`、`SecondaryNameNode`这三条是否存在，如果不存在则应该去`~/hadoop/logs/`目录下寻找相应地日志查看错误信息

   

   在slave上输入jps应该有类似如下输出

   ```
   4406 Jps1914 
   NodeManager1787 
   DataNode
   ```

   主要关注`NodeManager`、`DataNode`这两条是否存在，如果不存在同样去`~/hadoop/logs/`目录下寻找相应地日志查看错误信息

   * 我发现某个slave的datanode没有启动，查看其`hadoop-lyk-datanode-VM-4-7-ubuntu.log`发现，原来是xml配置文件写错了。。

2. 查看hadoop webUI：

   ```
   <master-ip>:50070
   ```

   * 在`hdfs-site.xml`中配置

## 关闭hadoop



如果关闭Hadoop(`~/hadoop/sbin/stop-all.sh` ),则所有节点的jps都不会有与hadoop关联的输出

## Bugs

* ERROR: Invalid HADOOP_HDFS_HOME

  网上有说需要配置`HADOOP_HDFS_HOME`这个环境变量，其实根本不需要。 发生这个问题，大概率是你的hadoop安装出错了， 启动hadoop实际上会执行类似`/home/lyk/hadoop/share/hadoop/common/hadoop-common-3.2.3.jar`的jar包， 进到该目录看看有没有这个jar包就行了

# Spark

Spark是一个分布式的大数据计算引擎，可以执行你的任务（jar包）



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
   export SPARK_DIST_CLASSPATH=$(/home/lyk/hadoop/bin/hadoop classpath)
   
   export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
   export SCALA_HOME=/usr/local/scala
   export HADOOP_HOME=/home/lyk/hadoop
   export HADOOP_COMMON_HOME=$HADOOP_HOME
   
   # Spark
   # SPARK_MASTER_PORT是7077
   # SPARK_MASTER_WEBUI_PORT用于在网页上访问spark管理页面，默认的端口是8080, 这是个常用端口， 因此替换成了18080
   export SPARK_MASTER_HOST=master
   export SPARK_MASTER_PORT=7077
   export SPARK_MASTER_WEBUI_PORT=18080
   ```

   

```shell
export SPARK_DIST_CLASSPATH=$($(HOME)/hadoop/bin/hadoop classpath)
export HADOOP_CONF_DIR=$(HOME)/hadoop/etc/hadoop#
export SCALA_HOME=/usr/lib/scala/scala-2.13.3 
export HADOOP_HOME=$(HOME)/hadoop
export SPARK_MASTER_IP=<master的公网ip> #指定 Spark 集群 Master 节点的 IP 地址 
export SPARK_MASTER_PORT=7077export SPARK_MASTER_HOST=master
export SPARK_EXECUTOR_MEMORY=4096m #大小看虚拟机内存
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
# rm -rf /usr/local/spark/# 
tar -zxvf /spark.master.tar.gz -C /usr/local
```

## 启动spark

==在启动之前先修改master的spark-env.sh文件，将其中的`SPARK_LOCAL`注释掉，不然就只能从服务器内网的localhost来访问spark的webui了（我也不知道为啥。。。）==

1. **先按照之前的步骤启动Hadoop**

2. 启动spark

   ```shell
   cd ~/spark
   ```

   ```shell
   ./sbin/start-all.sh
   ```

## 查看spark是否启动

   执行jps，此时除了hadoop的进程输出外，还能看到spark的进程：

* master： 多了`Master`和`Worker`(加入指定该master也作为worker的话)

* worker： 多了`Worker`

   

  

  
  
## 提交任务

```shell
 spark-submit [path-to-jar]
```



  

   

## Bugs

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

  

# Hadoop + Spark For Manjaro

这里演示一下Manjaro/arch用户安装hadoop的流程，只开个头。剩余的hadoop配置和spark安装及配置也大同小异。主要是对于manjaro/arch用户来说，安装这类软件会有一些小坑

* `sudo pacman -Syu`
* 安装jdk：`yay -S jdk`
* 安装openssh：`yay -S openssh`

  * manjaro默认不安装openssh



**如果你要用hadoop用户，而非lyk用户的话，还得做以下步骤**

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

  



# Hadoop + Spark For Mac

实际做作业时，我用的就是mac m1单机hadoop+spark，亲测没问题

mac和linux的区别主要还是文件路径不同，需要修改一些环境变量，其余步骤完全相同

* 由于mac的用户目录位于`/Users/lyk`, 各种配置中的环境变量也需要更改（而不是linux的`/home/lyk`）
* 同理， mac的jdk位置也可能不一样，需要做更改
* 因为spark和hadoop都是由高级语言java/scala编写的，因此没有跨平台问题。我的m1能正常安装、运行集群

# Clickhouse

Clickhouse是一个单机数据库，对机器学习的支持比较好

## 环境

mac（m1）没法装clickhouse，只能用服务器，即在服务器上裸机安装（后来为了服务高可用性，改为在服务器上docker安装 ）

## 搭建clickhouse

[官网文档](https://clickhouse.com/docs/zh/getting-started/install/)



### 系统要求

ClickHouse可以在任何具有x86_64，AArch64或PowerPC64LE CPU架构的Linux，FreeBSD或Mac OS X上运行。

官方预构建的二进制文件通常针对x86_64进行编译，并利用`SSE 4.2`指令集，因此，除非另有说明，支持它的CPU使用将成为额外的系统需求。下面是检查当前CPU是否支持SSE 4.2的命令:

```bash
$ grep -q sse4_2 /proc/cpuinfo && echo "SSE 4.2 supported" || echo "SSE 4.2 not supported"
```



要在不支持`SSE 4.2`或`AArch64`，`PowerPC64LE`架构的处理器上运行ClickHouse，您应该通过适当的配置调整从[源代码构建ClickHouse](https://clickhouse.com/docs/zh/getting-started/install/#from-sources)

* 注意，m1无法安装用软件包clickhouse，只能手动编译，clickhouse官网有[教程](https://clickhouse.com/docs/zh/development/build-osx)。 然而m1默认的编译器是apple clang，而clickhouse只推荐clang编译(教程也是用的clang)，因此m1用户还得把默认编译器换成clang， 由于特别麻烦，因此我在服务器上搭建了clickhouse，没有用mac本机

  * [Apple clang无法编译clickhouse，只能用clang]([Clickhouse installation for mac fails: "AppleClang is not supported, you should install clang from brew."](https://stackoverflow.com/questions/64497835/clickhouse-installation-for-mac-fails-appleclang-is-not-supported-you-should))

  * [Installing LLVM/Clang on OS X](https://embeddedartistry.com/blog/2017/02/24/installing-llvm-clang-on-osx/)

### DEB软件包安装

建议使用Debian或Ubuntu的官方预编译`deb`软件包。运行以下命令来安装包:

```bash
sudo apt-get install -y apt-transport-https ca-certificates dirmngr
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 8919F6BD2B48D754

echo "deb https://packages.clickhouse.com/deb stable main" | sudo tee \
    /etc/apt/sources.list.d/clickhouse.list
sudo apt-get update

sudo apt-get install -y clickhouse-server clickhouse-client

sudo service clickhouse-server start
clickhouse-client # or "clickhouse-client --password" if you've set up a password.
```

### docker安装

强烈建议安装docker版本的clickhouse，[文档]( https://hub.docker.com/r/clickhouse/clickhouse-server/)



pull镜像：

```shell
docker pull clickhouse/clickhouse-server
```



运行server容器，并进行端口映射：

```shell
docker run -d -p 8123:8123 -p9000:9000 --name some-clickhouse-server --ulimit nofile=262144:262144 clickhouse/clickhouse-server
```

* 这里将主机端口9000， 8123 映射到容器的9000， 8123， 和裸机版的clickhouse一样

* 这样就可以进行公网通信了



运行client容器，连接到server容器：

```shell
docker run -it --rm --link lyk-clickhouse-server:clickhouse-server clickhouse/clickhouse-client --host clickhouse-server
```



其余功能，如挂载卷，指定容器使用某个配置文件启动等，都参见文档

## 配置clickhosue

clickhouse系统配置文件:`/etc/clickhouse-server/config.xml `

clickhouse用户配置文件:`/etc/clickhouse-server/users.xml `



clickhouse日志文件所在目录: `/var/log/clickhouse-server`

* 如果`clickhouse-server` 没有找到任何有用的信息或根本没有任何日志，您可以使用命令查看 system.d :

  ```shell
  sudo journalctl -u clickhouse-server
  ```

### 允许远程连接

ClickHouse server默认只监听环回地址, 无法用公网通信：

```
root@ubuntu:/var/lib/clickhouse/# lsof -i :8123
COMMAND   PID       USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
clickhous 653 clickhouse   41u  IPv6  32544      0t0  TCP ip6-localhost:8123 (LISTEN)
clickhous 653 clickhouse   44u  IPv4  32547      0t0  TCP localhost:8123 (LISTEN)
```




需要修改系统配置文件，使其监听公网地址：

```shell
vim /etc/clickhouse-server/config.xml
```



把注释掉的`<listen_host>::</listen_host>`取消注释，然后重启服务：

```shell
service clickhouse-server restart 
```



现在的端口监听情况：

```
root@ubuntu:/var/lib/clickhouse/data/# lsof -i :8123
COMMAND    PID       USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
clickhous 9188 clickhouse   32u  IPv6  61573      0t0  TCP *:8123 (LISTEN)
```

### 配置用户名和密码

clickhouse默认的登录账号是default， 没有密码

[教程](https://blog.csdn.net/qq_38830964/article/details/114012700)

可以修改用户配置文件，添加密码：

```shell
vim /etc/clickhouse-server/users.xml
```



在对应用户的<password>标签中添加密码：

```
<password>123</password>
```

* 这里是明文密码，还可以配置加密密码，这里不介绍了
* 当password标签为空时，代表免密码登录

## 登陆

```shell
clickhouse-client -u default --passord 123
```

* -u 为指定使用哪个账号进行登录，如不指定, 默认使用default

## Bugs

clickhouse有时会自动崩溃，客户端启动时报错：

```
clickhouse-client
ClickHouse client version 21.2.4.6 (official build).
Connecting to localhost:9000 as user default.
Code: 210. DB::NetException: Connection refused (localhost:9000)
```

* 并且，一旦出现一次崩溃，之后的clickhouse都无法通过systemctl启动(`sudo service clickhouse-server start`)，只能手动启动(`sudo clickhouse start` )
* 在网上找了各种教程，都没能解决。 我的服务器是ubuntu20.04，换了新服务器（相同OS），重装，依然有这个问题。  最后无奈使用docker的clickohouse，崩溃就崩溃，重启容器就好了



clickhouse的文件的用户/组都为clickhouse，如果发现权限问题，需要chown

例如，新建了日志文件，需要手动更改其权限:

```shell
sudo chown clickhouse:clickhouse /var/log/clickhouse-server/clickhouse-server.log
```

## 删除clickhouse

查看系统已安装的包：

```shell
apt list --installed 
```



```shell
sudo apt remove -y clickhouse-common-static
```

```shell
sudo apt remove -y clickhouse-server-common
```

```shell
sudo rm -rf /var/lib/clickhouse
sudo rm -rf /etc/clickhouse-*
sudo rm -rf /var/log/clickhouse-server
```



# Flink

Flink也是一个计算引擎，可以执行你提交的jar包

## 搭建FLink

环境：Mac单机搭建， Flink Version: 1.13.5-bin-scala-2.11

[参考教程](https://www.jianshu.com/p/bbaa8d72cfcf)



下载jar包：https://archive.apache.org/dist/flink/flink-1.13.5/



解压：

```shell
sudo tar -zxf flink-1.13.5-bin-scala_2.11.tgz  -C /usr/local
```



修改文件名字，并设置权限

```shell
cd /usr/local
sudo mv ./flink-*/ ./flink
sudo chown -R hadoop:hadoop ./flink
```



添加环境变量:

```
vim ~/.zshrc

export FLINK_HOME=/usr/local/flink
export PATH=$FLINK_HOME/bin:$PATH
```



更改配置文件( `[flink位置]/conf/flink-conf.yaml` ):

```
# The number of task slots that each TaskManager offers. Each slot runs one parallel pipeline.

taskmanager.numberOfTaskSlots: 4

# The parallelism used for programs that did not specify and other parallelism.

parallelism.default: 1
```



## 启动Flink

```shell
# 启动Flink,因为FLINK_HOME已经写入了环境变量，因此可以直接执行脚本：
start-cluster.sh
```

- 可以通过观察logs目录下的日志来检测系统是否正在运行了

  ```shell
  tail log/flink--jobmanager-.log
  ```



- JobManager同时会在8081端口上启动一个web前端，通过[http://localhost:8081](https://links.jianshu.com/go?to=http%3A%2F%2Flocalhost%3A8081)来访问

## 关闭Flink

```
stop-cluster.sh
```



## 提交任务

[教程](https://www.cnblogs.com/fonxian/p/12334222.html)



Flink可以直接在Flink的webUI上提交jar包

也可以命令行提交：

```shell
run  -c Flink -p 2 [path-to-jar]
```





# Kafka

没学，不会，不想学
