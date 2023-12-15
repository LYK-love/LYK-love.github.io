---
categories:
- Software Engineering
date: 2022-09-13 15:43:12
tags:
- Linux
- Editor
title: VSCode
---

Outline:

* Install
* Config

<!--more-->

# Config



To open the **User** settings:

- Open the command palette (either with F1 or Ctrl+Shift+P)
- Type *"open settings"*
- You are presented with two options, choose **Open Settings (JSON)**

Which, depending on platform, is one of:

- **Windows** `%APPDATA%\Code\User\settings.json`
- **macOS** `$HOME/Library/Application\ Support/Code/User/settings.json`
- **Linux** `$HOME/.config/Code/User/settings.json`

The Workspace settings will be in a `{workspaceName}.code-workspace` file where you saved it, and the Folder settings will be in a `.vscode` folder if and when it has been created.

## Using Clang in Visual Studio Code

https://code.visualstudio.com/docs/cpp/config-clang-mac

# Visual Studio Code on macOS

https://code.visualstudio.com/docs/setup/mac

# Using C++ on Linux in VS Code

https://code.visualstudio.com/docs/cpp/config-linux