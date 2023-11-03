---
title: Zellij
tags:
  - Linux
  - Terminal
categories: Toolkit
date: 2023-11-02 21:20:52
---



[Zellij](https://zellij.dev/) is a new Rust-based terminal multiplexer. It's aimed to replace [tmux](https://lyk-love.cn/2022/09/13/tmux/).

<!--more-->

# Quick Start

1. [->Install](https://zellij.dev/documentation/installation)

2. [Set config file](https://zellij.dev/documentation/configuration):

   ```sh
   mkdir ~/.config/zellij
   zellij setup --dump-config > ~/.config/zellij/config.kdl
   ```

3. Set config file as symlink:

   ```sh
   cp $ZELLIJ_CONFIG_FILE /Users/lyk/Projects/MyOfficialProjects/dotfiles/zellij/config.kdl
   rm $ZELLIJ_CONFIG_FILE 
   ln -s /Users/lyk/Projects/MyOfficialProjects/dotfiles/zellij/config.kdl $ZELLIJ_CONFIG_FILE
   ```

   By default, `$ZELLIJ_CONFIG_FILE ` is: "~/.config/zellij/config.kdl".

# Config

[Zellij Config Options](https://zellij.dev/documentation/options#options)

`pane_frames false`



# Theme

1. Choose one theme from [-> Zellij Theme Gallery](https://zellij.dev/documentation/theme-gallery#theme-gallery).
2. Go to [zellij-utils/assets/themes](https://github.com/zellij-org/zellij/blob/main/zellij-utils/assets/themes). Choose the theme file.
3. In the configuration file of zellij:
   1. Paste the code of the theme code.
   2. Under the "themes" section, secify your theme.



```kdl
themes {
    gruvbox-light {
        fg 124 111 100
        bg 251 82 75
        black 40 40 40
        red 205 75 69
        green 152 151 26
        yellow 215 153 33
        blue 69 133 136
        magenta 177 98 134
        cyan 104 157 106
        white 213 196 161
        orange 214 93 14
    }
    //other themes
}

//...

// Choose the theme that is specified in the themes section.
// Default: default
//
theme "gruvbox-light"
```



