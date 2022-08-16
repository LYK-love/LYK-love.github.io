---
title: VSCode
tags:
---

To open the **User** settings:

- Open the command palette (either with F1 or Ctrl+Shift+P)
- Type *"open settings"*
- You are presented with two options, choose **Open Settings (JSON)**

Which, depending on platform, is one of:

- **Windows** `%APPDATA%\Code\User\settings.json`
- **macOS** `$HOME/Library/Application\ Support/Code/User/settings.json`
- **Linux** `$HOME/.config/Code/User/settings.json`

The Workspace settings will be in a `{workspaceName}.code-workspace` file where you saved it, and the Folder settings will be in a `.vscode` folder if and when it has been created.

