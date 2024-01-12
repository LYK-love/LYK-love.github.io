---
title: How to Set Up on A New Machine
date: 2024-01-09 18:58:15
tags: 
- Linux
- Terminal
categories: Software Engineering
---

How to set up configs on a brand new machine (typically a ubuntu server).

My dotfiles: `https://github.com/LYK-love/dotfiles-for-servers`

<!--more-->

# Prerequisites

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

## NvChad

[--> NvChad Installation Doc](https://nvchad.com/docs/quickstart/install)



```sh
git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1 && nvim
```



## openssh

`openssh-server` is installed by default in many distros, you can check its installation via:

```sh
sudo lsof -i :22
```

If no process is listening to port=22, then the openssh is not enabled or enven not installed.

Below is the instructions to install and enable it:

1. First, upate all softwares

   ```sh
   sudo apt update
   ```

2. Install `openssh-server`:

   ```sh
   sudo apt install openssh-server
   ```

3. Verify OpenSSH Server Installation:

   ```sh
   sudo systemctl status ssh
   ```

   This command will show the current status of the SSH service. It should be active (running).



If the SSH service is not running, you can start it with:

```sh
sudo systemctl start ssh
```

If you want the SSH server to start automatically when your system boots, use:

```sh
sudo systemctl enable ssh
```

## Cargo

[--> Installation of Rust](https://lyk-love.cn/2024/01/09/rust-tools/#install)

1. Run the command to download the `rustup` tool and install the latest stable version of Rust:

   ```bash
   curl --proto '=https' --tlsv1.3 https://sh.rustup.rs -sSf | sh
   ```

   Next, run the following command to add the Rust toolchain directory to the PATH environment variable:

   ```bash
   source $HOME/.cargo/env
   ```

2. Verify the Rust installation by requesting the version:

   ```bash
   rustc --version
   ```

3. If you don't have a `gcc`, please install one.

Now rust and corresponding tools (rustup, cargo) have been installed

## Zellij

```sh
cargo install --locked zellij
```



## Others

Zsh plugins:

* zsh-autosuggestions:

  ```sh
  git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
  ```



Unix tools:

* rigprep:

  ```sh
  sudo apt install ripgrep
  ```

  

# Set up terminal on a new machine

In this section we use my dotfiles to config:

1. zsh
2. Oh-my-zsh
3. powerlevel10k
4. NvChad
5. Zellij

For forther customization, please refer to:

1. [My zsh doc](https://lyk-love.cn/2023/12/28/zsh/?highlight=zsh)
2. [My NvChad doc](https://lyk-love.cn/2024/01/09/nvchad/)
3. [My Zellij doc](https://lyk-love.cn/2023/11/02/zellij/)



1. Clone my dotfiles

   ```sh
   git clone --recurse-submodules git@github.com:LYK-love/dotfiles-for-servers.git ~/dotfiles
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

2. Source the zsh config file in my dotfiles, in order to enable some env variables.

   ```sh
   source ~/dotfiles/zsh/.zshrc
   ```

   Now you can check some env variables I set:

   ```
   > echo $DOT_FILE_HOME
   /home/lyk/dotfiles
   
   > echo $ZSH_DOT_FILE_HOME
   /home/lyk/dotfiles/zsh
   
   > echo $NVIM_CUSTOM_HOME
   /home/lyk/dotfiles/nvchad_custom
   
   > echo $ZELLIJ_CONFIG_FILE
   /home/lyk/dotfiles/zellij/config.kdl
   ```

3. Remove original config files, if any, in your computer.

   ```sh
   rm ~/.zshrc # zsh
   rm -rf ~/.config/nvim/lua/custom # NvChad
   ```

4. Now **set the config files** as the cooresponding ones in my dotfiles:

   ```sh
   ln -s $ZSH_DOT_FILE_HOME/.zshrc ~/.zshrc # zsh
   ln -s  $NVIM_CUSTOM_HOME/ ~/.config/nvim/lua/custom # NvChad
   mkdir ~/.config/zellij # Zellij
   ln -s $ZELLIJ_CONFIG_FILE ~/.config/zellij/
   ```

   After that, zsh, nvchad and Zellij should be correctly configured. Zsh plugins are enabled as well.

5. Now we enable a **theme** for zsh. Since we've installed `powerlevel10k` before, we now start it's config:

   ```sh
   p10k configure
   ```


# Set up SSH

## Local -> Remote

Now we config the capability of connecting the server from one's local machine.

On your local machine, run:

```sh
ssh-copy-id user@host
```

where `user` is your user account name on the remote server, and `host` is the hostname or ip address of the remote server.



Or you can copy your ssh public key `id_rsa.pub` of your local machine to `~/.ssh/authorized_keys` of the remote server.

## Remote -> Github

1. Generate ssh key on the server：

   ```sh
   ssh-keygen -t rsa
   ```

2. Look at `~/.ssh`:

   ```ssh
   ❯ ls -l ~/.ssh
   total 20
   -rw-r--r-- 1 lyk lyk   27  2月 10 15:44 config
   -rw------- 1 lyk lyk 2602  2月  9 17:18 id_rsa
   -rw-r--r-- 1 lyk lyk  571  2月  9 17:18 id_rsa.pub
   -rw------- 1 lyk lyk 3926  2月 19 12:58 known_hosts
   -rw------- 1 lyk lyk 3182  2月 19 12:41 known_hosts.old
   ```

   Copy the content of `id_rsa.pub`, i.e., the public key of this user, to the Github.


# Set up conda

[--> Install Miniconda](https://docs.conda.io/projects/miniconda/en/latest/index.html#quick-command-line-install)

For Linux:

These four commands quickly and quietly install the latest 64-bit  version of the installer and then clean up after themselves. To install a different version or architecture of Miniconda for Linux, change the  name of the `.sh` installer in the `wget` command.

```sh
mkdir -p ~/miniconda3
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm -rf ~/miniconda3/miniconda.sh
```

After installing, initialize your newly-installed Miniconda. The following commands initialize for bash and zsh shells:

```sh
~/miniconda3/bin/conda init bash
~/miniconda3/bin/conda init zsh
```

# Add another user

[--> Linux Users and Groups](https://lyk-love.cn/2023/12/29/linux-users-and-groups/?highlight=shadow)



1. Add user

   ```sh
   sudo adduser <username>
   ```

2. Give the new user `sudo` permission:

   ```sh
   sudo usermod -a -G adm username
   sudo usermod -a -G sudo username
   ```

