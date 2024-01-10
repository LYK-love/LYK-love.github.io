---
title: How to Set Up on A New Machine
date: 2024-01-09 18:58:15
tags:
categories: Software Engineering
---



My dotfiles: `https://github.com/LYK-love/dotfiles/`

* It's a private repo so other people can't clone it.

# Prerequists

Install following softwares:

## zsh


1. Install zsh:

   ```shell
   sudo apt install zsh
   ```

   By default, zsh will use  `~/.zshrc` as config file. 

2. Switch your shell to zsh:

   ```
   chsh -s /bin/zsh
   ```

3. Install and config [Oh-my-zsh]()

## Oh-my-zsh

Install it via [-->repo](https://github.com/ohmyzsh/ohmyzsh#basic-installation):

```sh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```



Uninstall: If you want to uninstall `oh-my-zsh`, just run `uninstall_oh_my_zsh` from the command-line. It will remove itself and revert your previous `bash` or `zsh` configuration. ([-->Source](https://github.com/ohmyzsh/ohmyzsh#uninstalling-oh-my-zsh))



## p10k

## neovim

You may install neovim via `sudo apt install neovim`. However, the neovim installed through this method is **very old** due to the slow updates of the official package source.

Therefore, in order to install the latest neovim, **which is a must to use NvChad ([need neovim>0.9.4](https://nvchad.com/docs/quickstart/install))**, you can install neovim via:

1. [Neovim official github repo](https://github.com/neovim/neovim/releases).
2. Or use some PPA repository since it gets updated more often ([-->](https://darryldias.me/2023/install-neovim-on-ubuntu/)).



For method 2, you should

1. Add unstable ppa repository:

   ```sh
   sudo add-apt-repository ppa:neovim-ppa/unstable
   ```

   If you wish to install the stable version of the PPA. Enter the  command below in the terminal, the rest of the procedure is the same.

   ```sh
   sudo add-apt-repository ppa:neovim-ppa/stable
   ```

2. The command above will ask you to confirm you want to add the  unstable/stable PPA to the local package database. Press enter. This  should update the local package database, but if it does not, then you  will need to do it manually. We can do this by entering the command  below.

   ```sh
   sudo apt update
   ```

3. Time to do the thing. The command below will install Neovim.

   ```sh
   sudo apt install neovim
   ```

4. If you want to uninstall Neovim simply run.

   ```sh
   sudo apt remove neovim
   ```



## openssh

## NvChad

[--> NvChad Installation Doc](https://nvchad.com/docs/quickstart/install)



```sh
git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1 && nvim
```



1. Set environment variable in `~/.zshrc` for convience:

   ```sh
   export NVIM_CUSTOM_HOME="$DOT_FILE_HOME/nvchad_custom"
   ```

2. Install NvChad. Detete its default custom file. Use a symbol link, which is to my custom file in the dotfile, to replace it.

   ```sh
   ln -s  $NVIM_CUSTOM_HOME/ ~/.config/nvim/lua/custom
   ```




## Others

Zsh plugins:

* zsh-autosuggestions:

  ```sh
  git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
  ```



# Set up terminal stuff on a new machine

1. Clone my dotfiles

   ```sh
   git clone --recurse-submodules git@github.com:LYK-love/dotfiles.git
   ```

   parameter `--recurse-submodules` is because my NvChad dotfile, which is a distinct public repo, is added as a git submodule:

   ```ini
   # In `.gitmodules`
   [submodule "NvChad-custom-file"]
   	path = NvChad-custom-file
   	url = git@github.com:LYK-love/NvChad-custom-file.git
   ```

   A submodule won't be automatically cloned when the parent repo is cloned. You must use `--recurse-submodules` to mannually do it.

   If you already cloned without the parameter, you can alsouse

   ```sh
   git submodule update --init --recursive
   ```

   

2. There're 2 branches on it. `mac` is for my macbook, `ubuntu` os for my ubuntu servers. For servers, I'll use the `ubuntu` branch.

   ```sh
   git switch ubuntu
   ```

3. Source the zsh config file in my dotfiles, in order to enable some env variables.

   ```sh
   source <my dotfile folder>/zsh/.zshrc
   ```

   Now you can check some env variables I set:

   ```
   > echo $DOT_FILE_HOME
   /home/lyk/dotfiles
   
   > echo $ZSH_DOT_FILE_HOME
   /home/lyk/dotfiles/zsh
   
   > echo $NVIM_CUSTOM_HOME
   /home/lyk/dotfiles/nvchad_custom
   ```

4. Remove original config files, if any, in your computer.

   ```sh
   rm ~/.zshrc # zsh
   rm -rf ~/.config/nvim/lua/custom # NvChad
   ```

5. Now **set the config files** as the cooresponding ones in my dotfiles:

   ```sh
   ln -s $ZSH_DOT_FILE_HOME/.zshrc ~/.zshrc # zsh
   ln -s  $NVIM_CUSTOM_HOME/ ~/.config/nvim/lua/custom # NvChad
   ```

   After that, zsh and nvchad should be correctly configured. Zsh plugins are enabled as well.

6. Now we enable a **theme** for zsh. Since we've installed `powerlevel10k` before, we now start it's config:

   ```sh
   p10k configure
   ```

   

# Set up other things

