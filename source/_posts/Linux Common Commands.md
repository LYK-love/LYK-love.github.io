---
title: Linux Common Commands
tags: Linux
categories: Toolkit
date: 2022-02-19 14:04:37
---


Linux主机的常用命令，可以用来快速进行linux服务器的配置

OS可以是各种LINUX发行版，因此你可以看到各种包管理工具（yay,apt,yum...）, 选自己用的就好

<!--more-->

# 配置ssh免密登陆

主机上生成 ssh key：

```
ssh-keygen -t rsa
```

* 腾讯云的服务器不会默认生成ssh key， 所以也不会有`~/.ssh`文件夹， 其他主机也无法通过ssh连接（`ssh-copy-id`）也不行。 因此腾讯云服务器需要先生成ssh key，才能使用

查看`~/.ssh`:

```ssh
❯ ls -l ~/.ssh
total 20
-rw-r--r-- 1 lyk lyk   27  2月 10 15:44 config
-rw------- 1 lyk lyk 2602  2月  9 17:18 id_rsa
-rw-r--r-- 1 lyk lyk  571  2月  9 17:18 id_rsa.pub
-rw------- 1 lyk lyk 3926  2月 19 12:58 known_hosts
-rw------- 1 lyk lyk 3182  2月 19 12:41 known_hosts.old

```

* authorized_keys: 存放远程免密登录的公钥,主要通过这个文件记录多台机器的公钥。(没有则手动创建该文件)

* id_rsa: 生成的私钥文件

* id_rsa.pub: 生成的公钥文件

* known_hosts: 已知的主机公钥清单





服务器上配置ssh免密登陆：

* 将本地 id_rsa.pub 文件的内容拷贝至远程服务器的 ~/.ssh/authorized_keys
  * 如果服务器没有`~/.ssh`，则需要自己创建
* 也可以`ssh-copy-id user@host `

## 本机到本机的免密登陆

本机到本机也是需要配置免密登陆的，但是`root@localhost`需要额外配置，`/etc/ssh/sshd_config`中有一个属性为`PermitRootLogin` ,默认值no不允许进行密码登录，我们需要将其改为yes.：

```shell
vim /etc/ssh/sshd_config
```



然后重启ssh服务:

```shell
sudo service ssh restart
```



ssh会因为各种各样的原因失败，排查ssh问题的命令:

```shell
sshd -T
```



# 用户

## 查看用户名



## 创建新用户
`sudo adduser username`

## 赋予新用户sudo权限

用adduser创建后的新用户是不能使用sudo的，因为还没有赋予相关root权限，执行以下代码赋予权限

```shell
sudo usermod -a -G adm username
sudo usermod -a -G sudo username
```


或者将用户加到sudoers文件中:



```shell
#添加sudo文件的写权限,命令是:
chmod u+w /etc/sudoers
#编辑sudoers文件
vim /etc/sudoers
#在 root ALL=(ALL) ALL,下面添加lyk ALL=(ALL) ALL 
lyk ALL=(ALL) ALL

#最后删除sudo文件的写权限
chmod u-w /etc/sudoers
```



## 修改用户密码

```shell
sudo passwd user
```



## 删除用户

`sudo userdel username`: 仅仅删除用户，不删除用户的home目录文件

* `-r`: 删除用户的home目录文件

当需要删除用户时可以使用以下指令

## 切换用户

```
su [user]
```

输入要切换的用户的密码

## 查看用户组

`cat /etc/group`



#   磁盘挂载

`fdisk`：查看磁盘信息

```shell
sudo fdisk -l
```



卸载分区

```shell
#sudo umount  [磁盘路径]
sudo umount /dev/nvme0n1p11
```



将分区格式化为ext4类型

``` shell
#（这里分区为/dev/nvme0n1p11）
sudo mkfs.ext4  /dev/sdb1
```



##  挂载分区（临时）

挂载分区（ 这里挂载到到`/data`目录下 ）

```
#sudo mount  /dev/sdb1  /[目录名] （目录当然是已存在的）
sudo mount /dev/sdb1 /data
```

* 这个挂载是临时的，重新开机就会丢失。 如果要开机自动启动挂载， 需要编辑`/etc/fstab`



查看硬盘和挂载分区等信息

```
df  -h
```

这样就成功添加了一块硬盘并挂载到`/data`目录下了，



## 设置开机自动挂载

1. 查询UUID

```shell 
ls -al /dev/disk/by-uuid

#输出为：
...
... 88e7c2eb-82e6-48c2-a3d8-829c32468f1f -> ../../nvme0n1p11
...
```

可以查到对应分区`nvme0n1p11`的uuid为`88e7c2eb-82e6-48c2-a3d8-829c32468f1f`



2. 编辑`/etc/fstab`(用来存放文件系统的静态信息的文件)

```
sudo vim /etc/fstab
```

末尾加上UUID=刚刚复制的UUID /data ext defaults 0 0

```
UUID=刚刚复制的UUID /data ext4 defaults 0 0
```





# Shell

检查当前可用的shell:

```shell
cat /etc/shells
```






查看当前使用的shell:

```shell
echo $SHELL
```

## zsh

安装zsh shell

```shell
sudo apt install zsh
```



切换shell

```
chsh -s /bin/zsh
```



## ohmyzsh

1. clone mirror:

   github安装oh-my-zsh（很慢）

   ```shell
   sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
   ```

   

   gitee安装oh-my-zsh: (国内用这个 )

   ```shell
   wget https://gitee.com/mirrors/oh-my-zsh/raw/master/tools/install.sh
   ```

   

2. 执行`install.sh`

3. 如果发现install很慢，可以修改为gitee：
   `vim install.sh`
   找到以下部分：

   ```shell
   # Default settings
   ZSH=${ZSH:-~/.oh-my-zsh}
   REPO=${REPO:-ohmyzsh/ohmyzsh}
   REMOTE=${REMOTE:-https://github.com/${REPO}.git}
   BRANCH=${BRANCH:-master}
   ```



   将中间两行改为：

   ```shell
   REPO=${REPO:-mirrors/oh-my-zsh}
   REMOTE=${REMOTE:-https://gitee.com/${REPO}.git}
   ```

   

   



## plugins

把插件仓库克隆到`$ZSH_CUSTOM/plugins` (默认位置是 `~/.oh-my-zsh/custom/plugins`)

clone完毕后，编辑`~/.zshrc`

```undefined
plugins=( [plugins...] zsh-syntax-highlighting)
```



* 安装` autosuggestion`s：( github非常慢，改用gitee ) (这里直接用环境变量+重定向，不需要在指定目录下clone了)

  ```shell
  git clone https://gitee.com/phpxxo/zsh-autosuggestions.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
  ```

  



* 安装`syntax-highlighting`：

  ```shell
  git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
  ```

  

* 安装`autojump`:

  ```shell
  yay -S autojump
  ```

  

最后`vim ~/.zshrc`：

```shell
plugins=(git zsh-syntax-highlighting zsh-autosuggestions autojump)
```








## theme

目前用[powlevel10k](https://github.com/romkatv/powerlevel10k/blob/master/README.md)， 主页上给了中国大陆的下载方式, oh-my-zsh下：

1. Clone the repository:

   ```shell
   git clone --depth=1 https://gitee.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
   ```

   

2. Set `ZSH_THEME="powerlevel10k/powerlevel10k"` in `~/.zshrc`
3. source一下配置文件
4. 开启主题配置：`p10k configure`
5. 后续可以继续用`p10k configure`重新开始配置， 或者手动更改配置文件：`~/.p10k.zsh`



* 默认配置不开启username@hostname 的显示，可以将这行注释掉：

  ```shell
  # Don't show context unless running with privileges or in SSH.
  typeset -g POWERLEVEL9K_CONTEXT_{DEFAULT,SUDO}_{CONTENT,VISUAL_IDENTIFIER}_EXPANSION=
  ```




## Changing your default shell

After installing one of the above shells, you can execute that shell inside of your current shell, by just running its executable. If you want to be served that shell when you login however, you will need to change your default shell.

To list all installed shells, run:

```shell
chsh -l
```

And to set one as default for your user do:

```shell
chsh -s full-path-to-shell
```

where *full-path-to-shell* is the full path as given by `chsh -l`.



# Editor

其实大多数OS预装的vim都够用了，nvim就图一乐

## nvim

* Neovim设置全局配置文件,需要在`/etc/profile`添加：

  ```shell
  export VIM=/usr/share/nvim
  export PATH="$PATH:$VIM/sysinit.vim"
  ```

* 有可能会出现这种情况：

  > 直接使用 nvim ... 打开文件时一切正常，配置也生效;
  > 但当你使用 sudo nvim ... 打开文件时，配置文件并没有生效

  出现这种情况的原因是：当你使用 sudo命令的时候，用户的身份切换了（默认是root）,此时你的环境变量也被重置了，系统当然就找不到你的配置文件。

  解决的方案大致有2种：

  1. 使用 sudo -E nvim ... 打开文件 （最快速的方法，不过每次都需要加上 -E, 有点麻烦）
  2. 修改 sudo 的配置文件: /etc/sudoers(如果用nvim打开是空文件的话，可以试一下用vim 或者 visudo打开，后面就不细说了，超纲了)

# 包管理工具

## apt

更新软件源

```
apt-get update
apt-get upgrade
```





## brew

安装：

```shekk
/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"
```



## pacman

同步存储库数据库，并且更新系统的所有软件包，但不包括不在软件库中的“本地安装的”包：

```
pacman -Syu
```

- `S` 代表同步
- `y` 代表更新本地存储库
- `u` 代表系统更新

## conda

 推荐`miniconda`， 直接去NJU MIRROR下载：

```shell
wget https://mirror.nju.edu.cn/anaconda/miniconda/Miniconda3-py39_4.9.2-Linux-x86_64.sh
```

* 清华源

然后安装：

```shell
bash /path/to/miniconda
```



重启终端，检查安装是否成功：

```shell
conda -V
```

### 换源

conda换源建议用nju源  （清华源早就不行了，建议别用）， [具体指导](https://mirrors.nju.edu.cn/help/anaconda)

1. 先执行 `conda config --set show_channel_urls yes` 生成用户目录下的 `.condarc` 文件

2. 编辑该文件：

   ```yaml
   channels:
     - defaults
   show_channel_urls: true
   default_channels:
     - https://mirror.nju.edu.cn/anaconda/pkgs/main
     - https://mirror.nju.edu.cn/anaconda/pkgs/r
     - https://mirror.nju.edu.cn/anaconda/pkgs/msys2
   custom_channels:
     conda-forge: https://mirror.nju.edu.cn/anaconda/cloud
     msys2: https://mirror.nju.edu.cn/anaconda/cloud
     bioconda: https://mirror.nju.edu.cn/anaconda/cloud
     menpo: https://mirror.nju.edu.cn/anaconda/cloud
     pytorch: https://mirror.nju.edu.cn/anaconda/cloud
     simpleitk: https://mirror.nju.edu.cn/anaconda/cloud
   ```

   即可添加 Anaconda Python 免费仓库。

3. 运行 `conda clean -i` 清除索引缓存，保证用的是镜像站提供的索引。

4. 运行 `conda create -n myenv numpy` 测试一下吧

## pip3

python2: pip

python3: pip3

### 安装

```shell
yay -S pip3
```



mac用户：`brew intall pip3`相当卡， 因此要用：

```
curl bootstrap.pypa.io/get-pip.py | python3
```



检查安装是否成功：

```shell
pip3 --version
```



### 换源



在 pip 命令中使用 **-i** 参数来指定镜像地址

```
pip3 install numpy -i https://mirrors.aliyun.com/pypi/simple/
```



如果需要全局修改，则需要修改配置文件:

Linux/Mac os 环境中，配置文件在 ~/.pip/pip.conf（如不存在创建该目录和文件）：

```text
mkdir ~/.pip
```

打开配置文件 **~/.pip/pip.conf**，修改如下：

```text
[global]
index-url = https://mirrors.aliyun.com/pypi/simple/
[install]
trusted-host = https://mirrors.aliyun.com
```



查看镜像地址：

```text
$ pip3 config list  
```

### npm

#### 换源

## 国内优秀npm镜像

------

#### 淘宝npm镜像

- 搜索地址：[http://npm.taobao.org/](https://link.jianshu.com?t=http://npm.taobao.org/)
- registry地址：[http://registry.npm.taobao.org/](https://link.jianshu.com?t=http://registry.npm.taobao.org/)

#### cnpmjs镜像

- 搜索地址：[http://cnpmjs.org/](https://link.jianshu.com?t=http://cnpmjs.org/)
- registry地址：[http://r.cnpmjs.org/](https://link.jianshu.com?t=http://r.cnpmjs.org/)

## 如何使用


 1.临时使用
 `npm install express --registry https://registry.npm.taobao.org `

2.持久使用

```shell
npm config set registry https://registry.npm.taobao.org
```

 配置后可通过下面方式来验证是否成功:

```shell
npm config get registry
```



# 开发环境配置

## JDK

### 安装jdk

mac:

mac建议到[oracle官网](https://www.oracle.com/java/technologies/downloads/#java11-mac)下载jdk



linux一般用命令行安装，因此推荐openjdk



Ubuntu:

查找合适的openjdk版本:

```shell
# ubuntu
apt-cache search openjdk
```

安装

```shell
sudo apt-get install openjdk-8-jdk
```

* 如果search和install都没反应，应该先更新软件源

Manjaro:

查找合适的openjdk版本:

```shell
yay search jdk
```



```shell
yay install openjdk-8-jdk
```





(3) 配置环境变量, 编辑如下文件:

```
vim ~/.bashrc
```

在最后一行加:

```
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
```

## 查找JDK

查看jdk版本：

```shell
java -version
```



查找jdk:

```shell
whereis java
```

输出为

```
java: /usr/bin/java /usr/share/java /usr/share/man/man1/java.1.gz
```



查看jdk真实位置（上面的都是软链接）：

```shell
ls -l /usr/bin/java
```

输出为：

```
lrwxrwxrwx 1 root root 22 Mar 30 16:07 /usr/bin/java -> /etc/alternatives/java
```



```
ls -l /etc/alternatives/java
```

输出为：

```shell
lrwxrwxrwx 1 root root 46 Mar 30 16:07 /etc/alternatives/java -> /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java
# 以上就是jdk位置
```



### 配置jdk环境变量

#### linux

对于linux:  编辑`/etc/profile`, 或 `~/.bashrc`, ` .zshrc`等：

```
vim /etc/profile # 这里可以选择任意的shell配置文件，
```

```shell
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64 # 这里填jdk位置
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=./:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=$PATH:${JAVA_HOME}/bin
```



使配置文件生效：

```
source /etc/profile
```



#### mac

mac的jdk安装位置和linux不同



查询当前的java的安装版本

```shell
cd /Library/Java/JavaVirtualMachines
ls
```

### 

配置`.zshrc`

```bash
# jdk 版本切换， on mac
# jdk-17.0.2.jdk   jdk1.8.0_321.jdk jdk-11.0.14.jdk 
export JAVA_8_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_321.jdk/Contents/Home
export JAVA_11_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.14.jdk/Contents/Home
export JAVA_17_HOME=/Library/Java/JavaVirtualMachines/jdk-17.0.2.jdk/Contents/Home



alias jdk8='export JAVA_HOME=$JAVA_8_HOME'
alias jdk11='export JAVA_HOME=$JAVA_11_HOME'
alias jdk17='export JAVA_HOME=$JAVA_17_HOME'
```

```shell
source ~/.bash_profi
```



切换jdk版本

```shell
jdk11
java -version
```





# 用户软件安装

这部分不仅是给主机，也是给容器的，尤其是容器，可能连ping这样的基本命令都没有，需要手动安装



如果OS是Ubuntu（ 云服务器或容器 ）， 需要先：

```shell
apt-get update
```

## docker

参见《Docker Intro》



1. ````shell
   sudo apt install docker
   # Ubuntu则为 sudo apt install docker.io
   ````

   

2. 最好使用非root用户来使用Docker,此时需要添加非root用户到本地Docker Unix组：`sudo usermod -aG docker [user_name]`
   * 如果当前登陆用户就是要添加进组的用户的话，需要重新登陆才能生效



3. 换源阿里云：

   ```shell
   sudo mkdir -p /etc/docker
   sudo tee /etc/docker/daemon.json <<-'EOF'
   {
     "registry-mirrors": ["https://zz1b9pta.mirror.aliyuncs.com"] # 这个url需要去阿里云“容器镜像服务” --> “镜像加速器” 生成
   }
   EOF
   sudo systemctl daemon-reload
   sudo systemctl restart docker
   ```


## mycli

好用的命令行mysql界面,[项目地址](https://github.com/dbcli/mycli)



```shell
# 通用
pip install -U mycli
```

or

```shell
# on Arch
yay -S mycli
```

or

```shell
# Only on macOS
brew update && brew install mycli  
```

or

```shell
# Only on debian or ubuntu
sudo apt-get install mycli 
```

## ping  & traceroute

ping:

```shell
apt-get install iputils-ping
```



traceroute:

```shell
apt-get install traceroute
```



# Dababase

## mysql

manjaro:

```shell
yay -S mysql
```



mac:

```
brew install mysql
```





ubuntu:

这里只针对ubuntu 20.04， Ubuntu 源仓库中最新的 MySQL 版本号是 MySQL 8.0

```shell
sudo apt update
sudo apt install mysql-server
```



安装完成后，MySQL 服务将会自动启动。想要验证 MySQL 服务器正在运行，输入：

```shell
sudo systemctl status mysql
```

输出应该显示服务已经被启用，并且正在运行：

```
● mysql.service - MySQL Community Server
     Loaded: loaded (/lib/systemd/system/mysql.service; enabled; vendor preset: enabled)
     Active: active (running) since Tue 2020-04-28 20:59:52 UTC; 10min ago
   Main PID: 8617 (mysqld)
     Status: "Server is operational"
     ...
```

## mongodb

由于 MongoDB 修改了软件授权协议，  官方仓库已经删除了此软件包。请注意从代码编译 mongodb 需要 ~160GB 磁盘空间，需要花费几个小时时间。因此我们最好安装`-bin`版本

```
yay -S mongodb
```



注意： 只有先启动`mongod`， 才能正确启动`mongo`

### 报错

可能有报错：

```
> mongo
connecting to: mongodb://127.0.0.1:27017
2018-09-27T21:11:14.779+0800 W NETWORK  [main] Failed to connect to 127.0.0.1:27017, reason: Connection refused
2018-09-27T21:11:14.780+0800 E QUERY    [main] Error: couldn't connect to server 127.0.0.1:27017, connection attempt failed :
connect@src/mongo/shell/mongo.js:234:13
@(connect):1:6
exception: connect failed
```

出现以上原因，可能是data目录下的mongod.lock文件的问题。可以使用命令修复：

```csharp
[root@localhost mongodb]# ./bin/mongod --repair
```

 然后重新打开一个窗口，启动mongodb

### 配置

配置文件路径： `\etc\mongodb.conf`. 

* 其中`dbpath`为数据库的路径

### 启动服务

启动

```ruby
$ systemctl start mongodb.service
```

查看状态:

```lua
sudo systemctl status mongodb
```

重启:

```text
sudo systemctl restart mongodb
```

停止:

```text
sudo systemctl stop mongodb
```

重载服务:

```text
sudo systemctl daemon-reload
```

开机启动:

```
sudo systemctl enable mongodb
```



# DEV

## maven

maven配置文件位置： `～/.m2/settings.xml`

加入阿里云仓库：

```xml
        <!-- 阿里云仓库 -->
        <mirror>
            <id>alimaven</id>
            <mirrorOf>central</mirrorOf>
            <name>aliyun maven</name>
            <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
        </mirror>
```



### 设置开机自启

```sql
system enable mongodb
```

# 基本命令

## clear

清屏：

```
clear
```



## 切换tty

1. CTRL + ALT + Fn

2. ```shell
   sudo chvt N # N: tty number, 1 represents the main tty
   ```





## 下载

```shell
# Download the contents of a URL to a file (named "foo" in this case):
wget https://example.com/foo

# Download the contents of a URL to a file (named "bar" in this case):
wget -O bar https://example.com/foo
```

## 主机操作

查看主机名：

```shell
hostname 
```



更改主机名：

```shell
vim /etc/hostname # 编辑该文件
```



添加域名映射：

```
vim /etc/hosts
```



## 时间

查看时间：

```shell
date
```

## 查看发行版

```shell
lsb_release -a
```

