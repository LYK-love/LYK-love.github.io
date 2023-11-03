---
title: Helix editor
tags:
---







使用体验: Nice but so far I haven’t been super impressed. 和Nvim+Nvchad相比并没有任何优势, 反而因为内置功能不如Nvchad等framework多而具备了一些劣势. 

况且Helix的操作逻辑和vim不同, 这就很要命了. 程序员可以不会helix, 但不能不会vim, 因此总会发生冲突.

# Install

[Install](https://docs.helix-editor.com/install.html)

# Usage

In shell: `hx`

是的, 它的名字叫helix, 但command line名字是hx.

# Configuration

To override global configuration parameters, create a `config.toml` file located in your config directory:

- Linux and Mac: `~/.config/helix/config.toml`
- Windows: `%AppData%\helix\config.toml`

# Theme

already installed by default. Just add `theme = "<name>"` to the top of your [`config.toml`](https://docs.helix-editor.com/configuration.html) file, or select it during runtime using `:theme <name>`.
