---
title: Zellij
categories:
- Software Engineering
tags:
- Linux
- Terminal
date: 2023-11-02 21:20:52
---

[Zellij](https://zellij.dev/) is a new Rust-based terminal multiplexer. It's aimed to replace [tmux](https://lyk-love.cn/2022/09/13/tmux/).

<!--more-->

# Quick Start

1. [-->Install](https://zellij.dev/documentation/installation)

   ```sh
   cargo install --locked zellij
   ```

2. By default, zellij will use `~/.config/zellij/config.kdl` as its config file. You need to create it first:

   ```sh
   mkdir ~/.config/zellij
   zellij setup --dump-config > ~/.config/zellij/config.kdl
   ```

   [--> Set config file](https://zellij.dev/documentation/configuration)

   However, since I use "dotfiles", I replace it with my dotfile. 

3. First, create environment variables for convience:

   ```sh
   # In `~/.zshrc`
   # Zellij. Default config dir is $HOME/.config/zellij
   export ZELLIJ_CONFIG_DIR="$DOT_FILE_HOME/zellij"
   export ZELLIJ_CONFIG_FILE="$ZELLIJ_CONFIG_DIR/config.kdl"
   ```

4. Next, replace `~/.config/zellij/config.kdl` with my dotfile. 

   ```shell
   rm ~/.config/zellij/config.kdl
   ln -s $ZELLIJ_CONFIG_FILE ~/.config/zellij/
   ```

# Config

[Zellij Config Options](https://zellij.dev/documentation/options#options)

`pane_frames false`

# Theme

1. Choose one theme from [-> Zellij Theme Gallery](https://zellij.dev/documentation/theme-gallery#theme-gallery).

2. Go to [zellij-utils/assets/themes](https://github.com/zellij-org/zellij/blob/main/zellij-utils/assets/themes). Choose the theme file.

3. In the configuration file of zellij:
   1. Under the "themes" section, secify your theme.
   
   2. Paste the code of the theme you like.
   
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
   
   

# Commands

* Start a new named session:

  ```shell
  zellij --session name
  ```

*  List existing sessions:

  ```shell
  zellij list-sessions
  ```

* Attach to the most recently used session:

  ```shell
  zellij attach
  ```

* Attach to the session with the given name:

  ```shell
  zellij attach <session-name>
  ```

* Attach to given seesion:

  ```sh
  zellij attach <session-name>
  ```

* Detach from the current session (inside a zellij session):

      Ctrl + O, D  

# Usage

Normally, we login to a server, start Zellij on it. Then create a Zellij session, run commands  it. Then we can close the ssh session to do other things. The command will not be stopped, it'll run in the Zellij session. 

We can attach the Zellij session to see it.



1.  Start a new named session, say `exp`:

   ```sh
   zellij --session exp
   ```

2. Run some commands in it. Such as

   ```python
   xvfb-run -s "-screen 0 1400x900x24" python data/generation_script.py --rollouts 1000 --rootdir datasets/carracing --threads 8
   ```

3. This command may take 10 hours. We can detatch current Zellij session, close our ssh session and do other things.

   ```
   Ctrl + O, D
   ```

4. We can view all active Zellij sessions

   ```
   zellij list-sessions
   ```

5. We can re-attach this session

   ```shell
   zellij attach exp
   ```

   

   