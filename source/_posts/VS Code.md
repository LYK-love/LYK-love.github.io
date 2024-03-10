---
title: VS Code
categories:
- Software Engineering
date: 2022-09-13 15:43:12
tags:
- Linux
- Editor

---

Outline:

* Install
* Config

<!--more-->

# Config

To open the **User** settings:

- Open the command palette (either with F1 or Cmd+Shift+P).
- Type *"open settings"*
- You are presented with two options, choose **Open Settings (JSON)**

Which, depending on platform, is one of:

- **Windows** `%APPDATA%\Code\User\settings.json`
- **macOS** `$HOME/Library/Application\ Support/Code/User/settings.json`
- **Linux** `$HOME/.config/Code/User/settings.json`

The Workspace settings will be in a `{workspaceName}.code-workspace` file where you saved it, and the Folder settings will be in a `.vscode` folder if and when it has been created.



* [Visual Studio Code on macOS](https://code.visualstudio.com/docs/setup/mac)

## Font

Change font: modify the `settings.json` file

```json
{
  "terminal.integrated.fontFamily": "FiraCode Nerd Font Mono",
   "workbench.colorTheme": "Gruvbox Dark Hard",
   "editor.fontLigatures": true,
   "editor.fontFamily": "'FiraCode Nerd Font Mono', Menlo, Monaco, 'Courier New', monospace"
}
```

## Theme

[Change color theme](https://code.visualstudio.com/docs/getstarted/themes):

1. Go to [Gruvbox Theme](https://vscodethemes.com/e/jdinhlife.gruvbox/gruvbox-dark-medium)
2. To install it, you need to:
   1. In VS Code, open the Color Theme picker with **File** > **Preferences** (**Code** > **Preferences or \**Code\** > \**Settings\** on macOS)**  > **Theme** > **Color Theme**.
   2. You can also use the keyboard shortcut ⌘K ⌘T to display the picker.
   3. Use the cursor keys to preview the colors of the theme.
   4. Select the theme you want and press Enter.

## Debug

Debug:

1. Step: F10

2. Step into: F11. 

   [disable Mac's F11 behavior](https://github.com/microsoft/vscode/issues/5102):

   1. Go to System Preferences -> Keyboard -> Shortcuts
   2. Uncheck the "Show Desktop    F11" option



## Run

Open User setting json file:

```json
"code-runner.executorMap": {
        # ...
        "python": "$pythonPath -u",
        # ...
}
```



# Dev

* [Using Clang in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-clang-mac)
* [Using C++ on Linux in VS Code](https://code.visualstudio.com/docs/cpp/config-linux)





Python formatter:

*"Formatting makes source code easier to read by human beings. By enforcing particular rules and conventions such as line spacing, indents, and  spacing around operators, the code becomes more visually organized and  comprehensible."* --> [Source](https://code.visualstudio.com/docs/python/formatting)



I use [Black formatter](https://marketplace.visualstudio.com/items?itemName=ms-python.black-formatter). Install it in VS Code's market place.

Config:

You can ensure VS Code uses Black by default for all your Python files by setting the following in your User settings (**View** > **Command Palette...** and run **Preferences: Open User Settings (JSON)**):

```json
"[python]": {
        "editor.defaultFormatter": "ms-python.black-formatter",
        "editor.formatOnSave": true,
        "editor.formatOnType": true
    },
```



# Remote development

VS Code supports [remote development](https://code.visualstudio.com/docs/remote/ssh#_remember-hosts-and-advanced-settings).





