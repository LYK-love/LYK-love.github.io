---
title: Terminal
tags:
  - Linux
  - Terminal
categories: Toolkit
date: 2022-09-13 14:58:22
---


Outline:

* Terminal Emulators
* Zsh
* Ohmyzsh
* Zsh Theme
* General Terminal Emulater Config

<!--more-->



# Intro

为了做到100%的跨平台和可移植性, 我争取使用跨平台的工具, 并且使用dotfile来管理这些工具的配置文件.

# Terminal Emulators

MacOS常用的终端模拟器是iTerm2, 而Linux KDE使用Konsole. 这两个**都不能跨平台**.

Alacritty是一个跨平台的终端, 但是有一些小小的问题.

为了能正常使用, 目前我还是用iTerm2.



## Konsole

Linux上无敌, 可惜MacOS不能用

## iTerms2

和MacOS无缝集成, 开箱即用. 但是它也不能跨平台, 所以**没必要对它进行过度的配置**. 



到 Settings -> Appearance -> General 中，将 **Theme** 设置为 Minimal， 将 **Status bar location** 设置为 Bottom。





https://icloudnative.io/posts/customize-iterm2-1/



在安装完 iTerm2 的 `shell integration` 后会在终端界面中最左侧多出一个**蓝色三角形**的标记。如图：

![img](https://hugo-picture.oss-cn-beijing.aliyuncs.com/images/20200310155736.png)

有蓝色三角形的标记说明当前 shell 支持 shell integration。如需关闭标记，可以在 `iTerm2 > Preferences > Profiles > (your profile) > Terminal 最下面 > Shell Integration` 关闭 `Show mark indicators` 。





Open iTerm2, go to Preferences > Profiles > Text > Select the "Fira code" font, mark "Use ligatures". Do the same to "Non-ASCII Font".



In iTerm2 Preferences > Advanced > Drawing (or just search for 'ligature'), change the *Improves drawing performance at the expense of disallowing alphanumeric characters to belong to ligatures* setting to *No*. This allows the "www" and "0xFF" ligatures to display correctly with Fira Code.

https://stackoverflow.com/questions/59128426/firacode-ligatures-not-working-in-iterm-2



## Alacritty

* [Official Website](https://alacritty.org/index.html)
* [Github Repo](https://github.com/alacritty/alacritty)
  * [Installation](https://github.com/alacritty/alacritty#installation)
  * [Configuration](https://github.com/alacritty/alacritty#configuration)
* [作者的Blog](https://jwilm.io/blog/announcing-alacritty/)

### Features

* **跨平台**
* 可定制性强, 并且由于是跨平台的, 不用担心换平台之后, Alacritty用不了, 定制打水漂的问题
  * 使用配置文件来配置, 意味着可以使用版本管理, 换台电脑clone一下就能用原来的配置了
* **可以在MacOS的OpenInTerminal里配置, 太爽了!** 一键打开! 我就是因为Warp不能这么做才放弃了Warp
* uses GPU acceleration (OpenGL in Rust), **Performance天下第一**
* [specifically written to correctly render applications like Vim](https://jwilm.io/blog/announcing-alacritty/), Alacritty + Nvim是天然搭档

### Config

[Github Configuration Official Doc](https://github.com/alacritty/alacritty#configuration)

https://clubmate.fi/alacritty



| Cmd+0      | ResetFontSize    |
| ---------- | ---------------- |
| Cmd+Equals | IncreaseFontSize |
| Cmd+Plus   | IncreaseFontSize |
| Cmd+Minus  | DecreaseFontSize |



| Cmd+Q | Quit             |
| ----- | ---------------- |
| Cmd+W | Quit             |
| Cmd+N | SpawnNewInstance |

* 配置文件位置: 

  Alacritty <u>doesn't create the config file for you</u>, but it looks for one in the following locations:

  1. `$XDG_CONFIG_HOME/alacritty/alacritty.yml`
  2. `$XDG_CONFIG_HOME/alacritty.yml`
  3. `$HOME/.config/alacritty/alacritty.yml`: 我用这个
  4. `$HOME/.alacritty.yml`

* 字体: 由于我的Zsh主题是p10k, 使用的默认字体是Meslo Nerd Font, 而Alacritty默认使用的不是Meslo Nerd Font, 这会导致p10k的很多图标在Alacritty中无法正常显示. 所以需要[安装Meslo Nerd Font字体](#p10k Fonts)

* 配色: 使用下文所述的[Dracula](# Color: Dracula), 配色文件是一个符号链接, 指向dotfile, 纳入了版本管理

  ```sh
  ln -s /Users/lyk/Projects/MyOfficialProjects/dotfiles/dracula.yml ~/.config/alacritty/dracula.yml
  ```

  当然还可以用别的[方案](https://github.com/eendroroy/alacritty-theme)

* Alacritty 本身不提供窗口拆分、Session 管理等功能, 所以需要安装[Tmux](# Terminal Multiplexer). 并且对于MacOS来说, 每次使用` <Ctrl+b> `实在是太繁琐了. 可以使用改键, 改成`Cmd`, 具体参考 [Josh Medeski](https://www.joshmedeski.com/) 的这篇『[macOS Keyboard Shortcuts for tmux](https://www.joshmedeski.com/posts/macos-keyboard-shortcuts-for-tmux)』:

  ```yaml
  # alacritty.yml
  key_bindings:
    - { key: T, mods: Command, chars: "\x02\x63" }
  ```

  `\x02\x63`就是`<Ctrl+b> + c`的十六进制表示, 可以用[`xxd -ps`](# xxd )验证

* I have also been playing with [Zellij](https://zellij.dev/), a full terminal workspace manager that combines the best of tmux with native tabs and scrollback. 

## WezTerm

https://wezfurlong.org/wezterm/install/macos.html

比Alacritty大, 比Alacritty慢, 并且对OSX支持很差. 在换屏幕时有bug.



https://github.com/Ji4n1ng/OpenInTerminal



Check Finder Extension permission

Open the OpenInTerminal app. Go to `System Preferences` -> `Extensions` -> `Finder Extensions`, check the permission button as below.





## Config

https://draculatheme.com/wezterm

```
ln -s /Users/lyk/Projects/MyOfficialProjects/dotfiles/wezterm-dracula_theme/dracula.toml $HOME/.config/wezterm/colors/dracula.toml
```





使用键盘快捷键：按下 `Alt` 键和 `Enter` 键，这将切换 WezTerm 窗口到全屏模式。按下相同的快捷键可以切换回普通模式。





```lua
-- Pull in the wezterm API
local wezterm = require("wezterm")

-- This table will hold the configuration.
local config = {}

-- In newer versions of wezterm, use the config_builder which will
-- help provide clearer error messages
if wezterm.config_builder then
	config = wezterm.config_builder()
end

-- This is where you actually apply your config choices

-- For example, changing the color scheme:
config.color_scheme = "Dracula (Official)"

config.tab_bar_at_bottom = true

config.use_fancy_tab_bar = false
config.window_decorations = "RESIZE"

-- Font
config.font = wezterm.font("Fira Code")
config.font_size = 14.0

-- and finally, return the configuration to wezterm
return config
```







使用键盘快捷键：按下 `Alt` 键和 `Enter` 键，这将切换 WezTerm 窗口到全屏模式。按下相同的快捷键可以切换回普通模式。

# Zsh

## Install

安装zsh shell

```shell
sudo apt install zsh
```



切换shell

```
chsh -s /bin/zsh
```

## Shell Switch

检查当前可用的shell:

```shell
cat /etc/shells
```




查看当前使用的shell:

```shell
echo $SHELL
```



set one shell  as default for your user:

```shell
chsh -s full-path-to-shell
```



在Parallels的Ubuntu虚拟机中, `chsh -s /bin/zsh`无法切换shell到zsh, 原因未知. 只能手动设置:

edit `~/.bashrc`, 在最后一行加上:

```shell
bash -c zsh
```

重启shell即可.



# Oh-my-zsh

## Install

https://github.com/ohmyzsh/ohmyzsh#basic-installation



```sh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```



可能遇到报错: Failed to connect to raw.githubusercontent.com port 443 after 7 ms: Couldn't connect to server.

这是因为域名被墙了导致的. 可以设置代理再重新下载:

```
export https_proxy=http://127.0.0.1:7890
```

(`7890`换成你用的VPN对https代理所用的实际端口)



对于国内用户, 可以:

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


## Details

Oh-my-zsh会创建`~/.zshrc`这个shell文件, 并将其作为配置文件. 

默认的`/.zshrc`文件中有如下内容:

```shell
# ...
export ZSH="$HOME/.oh-my-zsh"

# ...

plugins=(git zsh-syntax-highlighting  zsh-autosuggestions fasd)

source $ZSH/oh-my-zsh.sh
# ...
```

zsh会执行`~/.zshrc`这个shell文件.  

可以看到, 默认会设置Oh-my-zsh的目录为`~/.oh-my-zsh`, 记为环境变量`$ZSH`

```
ZSH="$HOME/.oh-my-zsh
```



在`~/.zshrc`中还会执行`$ZSH/oh-my-zsh.sh`文件.

`$ZSH/oh-my-zsh.sh`定义了一些环境变量:

* `ZSH_CUSTOM`: 默认为`$ZSH/custom`, 即`~/.oh-my-zsh/custom`

  ```
  # Set ZSH_CUSTOM to the path where your custom config files  Haltarys, 2023-06-21 - fix(docker): use `command docker` (#11766)                                      1 # and plugins exists, or else we will use the default custom/
  if [[ -z "$ZSH_CUSTOM" ]]; then                                                                                                                                     	ZSH_CUSTOM="$ZSH/custom"
  fi
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

## Uninstall

https://github.com/ohmyzsh/ohmyzsh#uninstalling-oh-my-zsh

If you want to uninstall `oh-my-zsh`, just run `uninstall_oh_my_zsh` from the command-line. It will remove itself and revert your previous `bash` or `zsh` configuration.



# Zsh Themes

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

   ```
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

[Github Repo](https://github.com/romkatv/powerlevel10k/blob/master/README.md)

主页上给了中国大陆的下载方式. 如果使用oh-my-zsh, 下载方式为：

1. Clone the repository:

   ```shell
   git clone --depth=1 https://gitee.com/romkatv/powerlevel10k.git ${ZSHz
   ```

   

2. Set `ZSH_THEME="powerlevel10k/powerlevel10k"` in `~/.zshrc`

3. source一下配置文件

4. 开启主题配置：`p10k configure`

   * 这会开启一个交互式程序, 根据用户的设定在`~/.p10k.zsh`生成主题的配置文件

5. 后续可以继续用`p10k configure`重新开始配置， 或者手动更改配置文件：`~/.p10k.zsh`

   * 为了对配置文件进行版本管理, 我对`~/.p10k.zsh`使用了符号链接.  `~/.p10k.zsh`实际是指向`~/Projects/MyOfficialProjects/dotfiles/.p10k.zsh`的符号链接. 
   * 新版的p10k是可以正确识别符号链接的, 当`~/.p10k.zsh`是一个指向`$DOT_FILE_HOME/.p10k.zsh`的符号连接时, `p10k configure`会在`$DOT_FILE_HOME`处生成(or 重新生成)配置文件. 
   * 而老版本p10k没有无法正确识别, 每次`p10k configure`后, 生成的配置文件都位于`~/.p10k.zsh`, 覆盖了原来的符号链接, ,**需要手动修**改.



### Notes

* p10k虽然效果很华丽, 配置也方便, 但是它支持的字体中不包括Fira Code, 因此我选择了Dracula作为主题.

* p10k在Linux的默认配置不开启username@hostname 的显示，参加官方文档的“How do I add username and/or hostname to prompt?”. 也可以将这行注释掉：

  ```shell
  # Don't show context unless running with privileges or in SSH.
  typeset -g POWERLEVEL9K_CONTEXT_{DEFAULT,SUDO}_{CONTENT,VISUAL_IDENTIFIER}_EXPANSION=
  ```



# Font

## Fira Code

https://github.com/tonsky/FiraCode



## p10k Fonts

[For Details Go To Github](https://github.com/romkatv/powerlevel10k#meslo-nerd-font-patched-for-powerlevel10k)

> Powerlevel10k doesn't require custom fonts but can take advantage of them if they are available. It works well with [Nerd Fonts](https://github.com/ryanoasis/nerd-fonts), [Source Code Pro](https://github.com/adobe-fonts/source-code-pro), [Font Awesome](https://fontawesome.com/), [Powerline](https://github.com/powerline/fonts), and even the default system fonts. The full choice of style options is available only when using [Nerd Fonts](https://github.com/ryanoasis/nerd-fonts).
>
> 👇 **Recommended font**: **Meslo Nerd Font** patched for Powerlevel10k. 👇

If you are using iTerm2 or Termux, `p10k configure` can **install the recommended font for you.** Simply answer `Yes` when asked whether to install *Meslo Nerd Font*.

### Manual font installation

1. Download these four ttf files:

   - [MesloLGS NF Regular.ttf](https://github.com/romkatv/powerlevel10k-media/raw/master/MesloLGS NF Regular.ttf)
   - [MesloLGS NF Bold.ttf](https://github.com/romkatv/powerlevel10k-media/raw/master/MesloLGS NF Bold.ttf)
   - [MesloLGS NF Italic.ttf](https://github.com/romkatv/powerlevel10k-media/raw/master/MesloLGS NF Italic.ttf)
   - [MesloLGS NF Bold Italic.ttf](https://github.com/romkatv/powerlevel10k-media/raw/master/MesloLGS NF Bold Italic.ttf)

2. Double-click on each file and click "Install". This will make `MesloLGS NF` font available to all applications on your system.

3. Configure your terminal to use this font:

   - **iTerm2**: Type `p10k configure` and answer `Yes` when asked whether to install *Meslo Nerd Font*. Alternatively, open *iTerm2 → Preferences → Profiles → Text* and set *Font* to `MesloLGS NF`.

   - **Visual Studio Code**: Open *File → Preferences → Settings* (PC) or *Code → Preferences → Settings* (Mac), enter `terminal.integrated.fontFamily` in the search box at the top of *Settings* tab and set the value below to `MesloLGS NF`. Consult [this screenshot](https://raw.githubusercontent.com/romkatv/powerlevel10k-media/389133fb8c9a2347929a23702ce3039aacc46c3d/visual-studio-code-font-settings.jpg) to see how it should look like or see [this issue](https://github.com/romkatv/powerlevel10k/issues/671) for extra information.

   - **Alacritty**: Create or open

     ```sh
     ~/.config/alacritty/alacritty.yml
     ```

     and add the following section to it:

     ```yaml
     font:
       normal:
         family: "MesloLGS NF"
     ```

## IDE Font Support Problem

* 采用前面的步骤, 我们的Terminal的字体就变成了Meslo Nerd Font, 具体而言是**MesloLGS NF**, 而很多IDE的默认Terminal字体不是Meslo Nerd Font, 因此p10k的图标在这些IDE的Terminal里还是不能正常显示, 因为没有对应字体支持. 

* Jetbrains IDE: 例如IDEA, 默认使用的Terminal字体是Jetbrains Mono, 需要在`Setting` ->` Editor` -> `Font` 里将字体改成MesloLGS NF

* VSCode: `Settings -> ``terminal`, 在`Font Family`中可以看到

  > Controls the font family of the terminal. Defaults to [Editor: Font Family](vscode-file://vscode-app/Applications/Visual Studio Code.app/Contents/Resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)'s value.

  这里的字体默认和 [Editor: Font Family](vscode-file://vscode-app/Applications/Visual Studio Code.app/Contents/Resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)的相同,但后者一般不用终端的字体. 我们将Terminal的字体单独设置为`MesloLGS NF`

# General Terminal Emulater Config

## Color: Dracula

 [Dracula](https://draculatheme.com/): 该网站收集了很多终端模拟器的Dracula主题配色方案

* iTerms2:

  1. Install:

     ```url
     git clone https://github.com/dracula/iterm.git
     ```

  2. 启用该配色：

     1. *iTerm2 > Preferences > Profiles > Colors Tab*
     2. Open the *Color Presets...* drop-down in the bottom right corner
     3. Select *Import...* from the list
     4. Select the `Dracula.itermcolors` file
     5. Select the *Dracula* from *Color Presets...*

* Alacritty:

  1. Install: Download using the [GitHub .zip download](https://github.com/dracula/alacritty/archive/master.zip) option.

  2. You just have to import `dracula.yml` in `~/.config/alacritty/alacritty.yml`.

     ```yaml
     ## Dracula Color Theme
     ## It's a symlink to my dotfile
     import:
       - ~/.config/alacritty/dracula.yml
     ```



