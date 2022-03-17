---
title: Linux Common Commands
tags: Linux
categories: OS
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

* authorized_keys: 存放远程免密登录的公钥,主要通过这个文件记录多台机器的公钥。

* id_rsa: 生成的私钥文件

* id_rsa.pub: 生成的公钥文件

* known_hosts: 已知的主机公钥清单





服务器上配置ssh免密登陆：

将本地 id_rsa.pub 文件的内容拷贝至远程服务器的 ~/.ssh/authorized_keys

* 如果服务器没有`~/.ssh`，则需要自己创建



# 用户

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

# pacman

同步存储库数据库，并且更新系统的所有软件包，但不包括不在软件库中的“本地安装的”包：

```
pacman -Syu
```

- `S` 代表同步
- `y` 代表更新本地存储库
- `u` 代表系统更新

# conda

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

## 换源

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

# docker

参加《Docker Intro》

1. ``sudo apt install docker`



2. 最好使用非root用户来使用Docker,此时需要添加非root用户到本地Docker Unix组：`sudo usermod -aG docker [user_name]`
   * 如果当前登陆用户就是要添加进组的用户的话，需要重新登陆才能生效

# dababase

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





### 设置开机自启

```sql
system enable mongodb
```

