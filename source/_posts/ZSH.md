---
title: ZSH
tags:
  - Linux
  - Terminal
categories:
  - Software Engineering
date: 2023-12-28 23:59:30
---


Zsh, On-my-zsh and their configs.

<!--more-->

# Zsh

Offical docs:

1. https://zsh.sourceforge.io/
2. https://zsh.sourceforge.io/Guide/zshguide.html



Install zsh: []

# Oh-my-zsh



## Details

The Oh-my-zsh itself will be installed at dir `$HOME/.oh-my-zsh`, everytime you start `zsh`,  `zsh` will start Oh-my-zsh. You can view this logic in the `~/.zshrc` file:

```shell
 # Path to your oh-my-zsh installation. This includes your downloaded plugins.
export ZSH="$HOME/.oh-my-zsh"
export OH_MY_ZSH=$ZSH
# ...

plugins=(git zsh-syntax-highlighting  zsh-autosuggestions fasd)

# Execute the `oh-my-zsh` file
source $ZSH/oh-my-zsh.sh 
# ...
```



`$ZSH/oh-my-zsh.sh`定义了一些环境变量:

* `ZSH_CUSTOM`: 默认为`$ZSH/custom`, 即`~/.oh-my-zsh/custom`

  ```
  # Set ZSH_CUSTOM to the path where your custom config files  Haltarys, 2023-06-21 - fix(docker): use `command docker` (#11766)                                      1 # and plugins exists, or else we will use the default custom/
  if [[ -z "$ZSH_CUSTOM" ]]; then                                                                                                                                     	ZSH_CUSTOM="$ZSH/custom"
  fi
  ```

  

## Install: For China users

对于国内用户:

可能遇到报错: Failed to connect to raw.githubusercontent.com port 443 after 7 ms: Couldn't connect to server.

这是因为域名被墙了导致的. 可以设置代理再重新下载:

```
export https_proxy=http://127.0.0.1:7890
```

(`7890`换成你用的VPN对https代理所用的实际端口)



1. 从gitee下载oh-my-zsh的安装脚本:

   ```shell
   wget https://gitee.com/mirrors/oh-my-zsh/raw/master/tools/install.sh
   ```

2. 执行`install.sh`

3. `install.sh`会clone github的Oh-my-zsh仓库. 如果访问不了github, 可以修改脚本, 把仓库地址换成gitee的:

   1. `vim install.sh`

   2. 找到以下部分：

      ```shell
      # Default settings
      ZSH=${ZSH:-~/.oh-my-zsh}
      REPO=${REPO:-ohmyzsh/ohmyzsh}
      REMOTE=${REMOTE:-https://github.com/${REPO}.git}
      BRANCH=${BRANCH:-master}
      ```

   3. 将中间两行改为：

      ```shell
      REPO=${REPO:-mirrors/oh-my-zsh}
      REMOTE=${REMOTE:-https://gitee.com/${REPO}.git}
      ```

## Plugins Installation

Use Oh-My-Zsh to manage plugins.

* 如果使用brew, yay等包管理工具安装插件, 会把插件安装在`$ZSH/plugins`,这些插件被称为""standard plugins"

* 如果使用git clone安装插件, 则文件需要被clone到到`$ZSH_CUSTOM/plugins`, 这些插件被称为"custom plugins", .

* 所有插件在安装完毕后,都需要在`~/.zshrc`的`plugins`中配置:

  ```undefined
  plugins=( [custom plugins...] zsh-syntax-highlighting autosuggestion)
  ```

* 修改完配置文件后记得`source ~/.zshrc`, 然后重新启动shell

### zsh-autosuggestions

[How to install](https://github.com/zsh-users/zsh-autosuggestions/blob/master/INSTALL.md#oh-my-zsh)

这里直接用环境变量+重定向，不需要在指定目录下clone了

1. Clone this repository into `$ZSH_CUSTOM/plugins` (by default `~/.oh-my-zsh/custom/plugins`)

   ```
   git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
   ```

   

2. Add the plugin to the list of plugins for Oh My Zsh to load (inside `~/.zshrc`):

   ```
   plugins=( 
       # other plugins...
       zsh-autosuggestions
   )
   ```

   

3. Start a new terminal session.

### zsh-syntax-highlighting

[How to install](https://github.com/zsh-users/zsh-syntax-highlighting/blob/master/INSTALL.md#oh-my-zsh)


* 1. Clone this repository in oh-my-zsh's plugins directory:

     ```
     git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
     ```

     

  2. Activate the plugin in `~/.zshrc`:

     ```
     plugins=( [plugins...] zsh-syntax-highlighting)
     ```

     

  3. Restart zsh (such as by opening a new instance of your terminal emulator).

Note: There're [conflicts](https://gitlab.com/gnachman/iterm2/-/issues/8727) between zsh-syntax-highlighting and ligature. So if you want to use one of them, you must give up the other.

### fasd & autojump

* 安装`fasd`: 它将文件和目录**按最近最常用**算法排序, 并提供各种操作

  ```shell
  yay -S fasd
  ```

  安装后需要配置`~/.zshrc`:

  ```shell
  alias a='fasd -a'        # any
  alias s='fasd -si'       # show / search / select
  alias d='fasd -d'        # directory
  alias f='fasd -f'        # file
  alias sd='fasd -sid'     # interactive directory selection
  alias sf='fasd -sif'     # interactive file selection
  alias z='fasd_cd -d'     # cd, same functionality as j in autojump
  alias zz='fasd_cd -d -i' # cd with interactive selection
  ```

  alias使用:

  ```
  a foo 列出最近操作的路径匹配 'foo' 的文件与目录
  f foo 列出最近操作的路径匹配 'foo' 的文件
  d foo 列出最近操作的路径匹配 'foo' 的目录
  s foo 列出最近操作的路径匹配 'foo' 的文件与目录，并可以通过序号选择
  sf foo 列出最近操作的路径匹配'foo'的文件，并可以通过序号选择
  sd foo 列出最近操作的路径匹配'foo'的目录，并可以通过序号选择
  z foo cd到最近操作的匹配'foo'并且得分最高的目录
  zz foo 列出最近操作的路径匹配'foo'的目录，通过序号选择，然后cd进目录
  ```

  e.g. If you often go to  `~/files/cool_project` you can simply use `z cool` to jump there. 



* `autojump`提供了`j`命令, 效果和`fasd`的`z`命令一样, 可以作为`fasd`的替代品:

  ```shell
  yay -S autojump
  ```



# Zsh Themes

Currently I have 2 themes. You can choose either.

## Dracula

 [Dracula](https://draculatheme.com/): 该网站收集了Dracula主题配色方案, 可以应用于各种终端模拟器和Shell.

* [Dracula for Zsh](https://draculatheme.com/zsh)

Install using Git: 

1. Clone.

   ```
   git clone https://github.com/dracula/zsh.git
   ```

2. Move an rename it to some place. For me, I move it under my dotfiles folder(`$DOT_FILE_HOME`) as `zsh-dracula_theme`

   ```
   mv zsh $DOT_FILE_HOME/zsh-dracula_theme
   ```

3. Create env vatiable for it in `~/.zshrc`:

   ```sh
   export DRACULA_THEME="$DOT_FILE_HOME/zsh-dracula_theme"
   ```

4. And creating a symbolic link to [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh/)'s theme folder:

   ```
   ln -s $DRACULA_THEME/dracula.zsh-theme $OH_MY_ZSH/themes/dracula.zsh-theme
   ```

   Note, you must set `$OH_MY_ZSH`  as [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh/)'s theme folder first.

   By default, the theme folder is already defined in `~/.zshrc`:

   ```
   export ZSH="$HOME/.oh-my-zsh"
   ```

    `$OH_MY_ZSH`   is just the same as it. So append in `~/.zshrc`:

   ```
   export OH_MY_ZSH=$ZSH
   ```

5. Go to your `~/.zshrc` file and set `ZSH_THEME="dracula"`.



### Customization

https://github.com/dracula/zsh



官网上给了一些自定义的配置方式, 我只选择增加username显示.



In `~/.zshrc`:

```
export DRACULA_DISPLAY_CONTEXT=1
```

## powlevel10k

[Github Repo](https://github.com/romkatv/powerlevel10k/blob/master/README.md). 上面也给了中国大陆的下载方式. 



1. Clone the repository:

   ```shell
   git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
   ```

2. Set `ZSH_THEME="powerlevel10k/powerlevel10k"` in `~/.zshrc`

3. Enable the update:

   ```sh
   source ~/.zshrc
   ```

   Since you've installed `p10k`, an interative program (`p10k configure`) will be created after this step. Make your custimization in that program. You can also manually start config:

   ```sh
   p10k configure
   ```

   The config file of powlevel10k generatied by `p10k configure` is `~/.p10k.zsh`.

4. Create a environment variable `P10K_CONFIG_FILE` to denote the real path of your p10k config file.

   ```shell
   # in ~/.zshrc
   export P10K_CONFIG_FILE="$ZSH_DOT_FILE_HOME/.p10k.zsh"
   ```

5. remove original `~/.p10k.zsh`, replace it with one in your dotfile:

   ```shell
   rm ~/.p10k.zsh
   ln -s $P10K_CONFIG_FILE ~/.p10k.zsh
   ```

后续可以继续用`p10k configure`重新开始配置, 这个命令的效果就是修改`~/.p10k.zsh`. 你也可以直接手动更改`~/.p10k.zsh`.

* 当`~/.p10k.zsh`是一个指向`$DOT_FILE_HOME/.p10k.zsh`的symlink时, `p10k configure`依然会正确地作出修改(即修改symlink指向的文件).

