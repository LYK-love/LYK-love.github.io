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

所有服务器都使用root账户

## 更改主机名称，添加hosts配置

1. 使用vim更改主机名称为master、slave01、slave02、slave03

```
# vim /etc/hostname
```

重启服务器确认名称已经改变

2. 添加hosts配置

```
# vim /etc/hosts
```

master中加入如下配置

```
172.0.0.1 localhost //如果本来就有这条就不用加了
<master的内网ip> master
<slave01的公网ip> slave01
<slave02的公网ip> slave02
<slave03的公网ip> slave03
```

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
# scp ~/.ssh/id_rsa.pub root@slave01:/
# scp ~/.ssh/id_rsa.pub root@slave02:/
# scp ~/.ssh/id_rsa.pub root@slave03:/
```

## 实现无密码登录slave



1. 使用如下命令将密钥添加进slave的`authorized_keys`中

```
# cat /id_rsa.pub >> /root/.ssh/authorized_keys
```

## 安装JDK

1. 将`jdk-8u301-linux-x64.tar.gz`保存在==根目录==
2. 运行如下命令

```
# mkdir /usr/local/java
# tar -zxvf /jdk-8u301-linux-x64.tar.gz -C /usr/local/java
```

3. 使用如下命令添加环境变量

```
# vim /etc/profile
```

​		将下面的内容添加至末尾

```
export JAVA_HOME=/usr/local/java/jdk1.8.0_301
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
# java -version
```

​	应该看到下面的输出

```
java version "1.8.0_301"
Java(TM) SE Runtime Environment (build 1.8.0_301-b09)
Java HotSpot(TM) 64-Bit Server VM (build 25.301-b09, mixed mode)
```

## 安装和配置Hadoop

**安装：**

1. 将hadoop-3.2.2.tar.gz拷贝到==master的根目录==下
2. 使用如下命令在==master==上安装hadoop

```
# tar -zxvf /hadoop-3.2.2.tar.gz -C /usr/local
# mv ./hadoop-3.2.2 ./hadoop #修改文件夹名称为hadoop
```

3. 使用如下命令添加环境变量

```
# vim /root/.bashrc
```

将以下内容添加到末尾

```
export HADOOP_HOME=/usr/local/hadoop
export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
```

----

**配置（master）：**

所有配置文件都位于目录`/usr/local/hadoop/etc/hadoop/`中

1. 修改workers

```
slave01
slave02
slave03
```



2. 修改core-site.xml

```
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

请注意属性`hadoop.tmp.dir`的值。

3. 修改`hdfs-site.xml`

```xml
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>3</value>
</property>

<!--添加下面这个属性是因为我在部署过程中遇到了一个问题导致namenode无法部署-->
<property>
  <name>dfs.namenode.name.dir</name>
  <value>file:/usr/local/hadoop/tmp/dfs/name</value>
  <description>Determines where on the local filesystem the DFS name node
      should store the name table(fsimage).  If this is a comma-delimited list
      of directories then the name table is replicated in all of the
      directories, for redundancy. </description>
</property>
</configuration>
```

4. 修改`mapred-site.xml`

```
<configuration>
<property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
</configuration>
```

5. 修改`yarn-site.xml`

```
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
</configuration>

```

添加下面这一步是因为我在部署的过程中遇到了无法找到`JAVA_HOME`环境变量的问题

6. 在`hadoop-env.sh`中配置`JAVA_HOME`

添加如下内容：

```
 export JAVA_HOME=/usr/local/java/jdk1.8.0_301
```

7. 使用如下命令将配置好的hadoop打包

```
# cd usr/local/# rm -rf ./hadoop/tmp# rm -rf ./hadoop/logs/*# tar -zcvf /hadoop.master.tar.gz ./hadoop
```

8. 使用如下命令将打包好的hdoop发送给slave

```
# scp /hadoop.master.tar.gz slave01:/# scp /hadoop.master.tar.gz slave02:/# scp /hadoop.master.tar.gz slave03:/
```



9. 其它master上的环境变量

在`/etc/profile`的末尾添加：

```
export HDFS_NAMENODE_USER=rootexport HDFS_DATANODE_USER=rootexport HDFS_SECONDARYNAMENODE_USER=rootexport YARN_RESOURCEMANAGER_USER=rootexport YARN_NODEMANAGER_USER=root
```

这是因为我在部署中遇到了和用户名相关的报错

**安装（slave）：**

1. 运行如下命令删除原有的hadoop根目录并将新的压缩包解压

```
# rm -rf /usr/local/hadoop# tar -zxvf /hadoop.master.tar.gz  -C /usr/local
```

**启动Hadoop：**

1. 在master上输入以下命令启动Hadoop

```
# cd /usr/local/hadoop# sbin/start-all.sh
```

2. 检验hadoop是否已经启动

```
# jps
```

在master上输入jps应该有类似于如下输出

```
1879 NameNode2169 SecondaryNameNode873 WrapperSimpleApp5530 Jps2427 ResourceManager
```

主要关注`NameNode`、`ResourceManager`、`SecondaryNameNode`这三条是否存在，如果不存在则应该去`/usr/local/hadoop/logs/`目录下寻找相应地日志查看错误信息。

在slave上输入jps应该有类似于如下输出

```
4406 Jps1914 NodeManager1787 DataNode
```

主要关注`NodeManager`、`DataNode`这两条是否存在，如果不存在同样去`/usr/local/hadoop/logs/`目录下寻找相应地日志查看错误信息。

## 安装配置和启动Spark

**安装（master）：**

1. 将`spark-3.1.2-bin-without-hadoop.tgz`拷贝到master的根目录
2. 输入如下命令安装

```
# tar -zxvf /spark-3.1.2-bin-without-hadoop.tgz -C /usr/local/# cd /usr/local# mv ./spark-3.1.2-bin-without-hadoop/ ./spark
```

3. 使用如下命令配置环境变量

```
# vim /root/.bashrc 
```

将下面的内容加入到`.bashrc`之中

```
export SPARK_HOME=/usr/local/sparkexport PATH=$PATH:$SPARK_HOME/bin:$SPARK_HOME/sbin
```

**配置（master）**

1. 使用如下命令将workers.template拷贝到同目录的workers文件中

```
# cd /usr/local/spark/# cp ./conf/workers.template ./conf/workers
```

2. 修改刚刚拷贝的workers文件的内容：

将原来的内容替换成：

```
masterslave01slave02slave03
```

3. 使用如下命令将spark-env.sh.template拷贝到spar-env.sh中

```
# cp ./conf/spark-env.sh.template ./conf/spark-env.sh
```

4. 在spark-env.sh的末尾添加如下内容

```
export SPARK_DIST_CLASSPATH=$(/usr/local/hadoop/bin/hadoop classpath)export HADOOP_CONF_DIR=/usr/local/hadoop/etc/hadoop# export SCALA_HOME=/usr/lib/scala/scala-2.13.3 export HADOOP_HOME=/usr/local/hadoopexport SPARK_MASTER_IP=<master的公网ip> #指定 Spark 集群 Master 节点的 IP 地址； export SPARK_MASTER_PORT=7077export SPARK_MASTER_HOST=masterexport SPARK_EXECUTOR_MEMORY=4096m #大小看虚拟机内存export SPARK_LOCAL_IP=localhostexport JAVA_HOME=/usr/local/java/jdk1.8.0_301
```

注意，由于我并没有安装scala所以不添加SCALA_HOME，而是添加JAVA_HOME。此外，由于出现了类似于如下的worker日志报错，我添加了`SPARK_LOCAL_IP`

5. 使用如下命令将配置好的spark打包发送给slave

```
# cd /usr/local/# tar -zcvf /spark.master.tar.gz ./spark# scp /spark.master.tar.gz slave01:/# scp /spark.master.tar.gz slave02:/# scp /spark.master.tar.gz slave03:/
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

  