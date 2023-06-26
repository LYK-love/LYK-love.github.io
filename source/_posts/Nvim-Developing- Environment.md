---
title: Nvim Developing Environment
tags: 
- Linux
- Editor
categories: Toolkit
date: 2022-08-17 22:52:46

---


Outline:

* Nvim
* Nvim Config
* LspInstall
* Dap
* Keybinds

<!--more-->

# Nvim

## Nvim vs VSCode

Nvim和VSCode是两个主流的编辑器/IDE. 

* VS Code’s use of [Electron](https://www.electronjs.org/) makes it available on all major platforms. This is how [GitHub Codespaces](https://github.com/features/codespaces) or [Gitpod](https://www.gitpod.io/) can access to the entire VS Code ecosystem. See [our interview with GitPod’s Chief Architect / Head of Engineering](https://console.dev/interviews/gitpod-christian-weichel/) about how important this has been.
  * 虽然微软团队对VSCode的Electron做了很多魔改, 极大地提升了性能, 但依然使得我个人感觉很不舒服
* Nvim更快

## Features

- **Performance:** 🚀 Very fast.
- **Syntax highlighting:** Neovim 0.5 now includes [Treesitter](https://github.com/nvim-treesitter/nvim-treesitter) and supports  [LSP](https://github.com/neovim/nvim-lspconfig), but still requires some config.
- **Customizable:** ✅ Large ecosystem of plugins and themes.
- **Cross-platform:** Linux ✅ Windows ✅ macOS ✅

## Config

* Neovim设置全局配置文件,需要在`/etc/profile`添加：

  ```shell
  export VIM=/usr/share/nvim
  export PATH="$PATH:$VIM/sysinit.vim"
  ```

* 有可能会出现这种情况：

  > 直接使用 nvim ... 打开文件时一切正常，配置也生效;
  > 但当你使用 sudo nvim ... 打开文件时，配置文件并没有生效

  出现这种情况的原因是：当你使用 sudo命令的时候，用户的身份切换了（默认是root）,此时你的环境变量也被重置了，系统当然就找不到你的配置文件。

  解决的方案大致有2种：

  1. 使用 sudo -E nvim ... 打开文件 （最快速的方法，不过每次都需要加上 -E, 有点麻烦）
  2. 修改 sudo 的配置文件: /etc/sudoers(如果用nvim打开是空文件的话，可以试一下用vim 或者 visudo打开，后面就不细说了，超纲了)

 

# Nvim Config

使用[ayamir的Nvim配置](https://github.com/ayamir/nvimdots/),  它集成了大量插件, 包括Nvim + LSP + Dap.

其配置文件位于`~/.config/nvim/lua`



插件实际的安装路径在

```text
~/.local/share/nvim/site/lazy
```



所有你可以简单修改的设置都放在`lua/core/settings.lua`里



https://github.com/TheZoraiz/ascii-image-converter#cli-usage



## Config Install

https://github.com/ayamir/nvimdots/wiki/Prerequisites

```
# for neovim python module
pip install neovim --user

# clone
git clone git@github.com:ayamir/nvimdots.git ~/.config/nvim

# sync plugins(maybe need multiple times)
nvim +PackerSync
```



## Structure

`init.lua` is the kernel config file. It requires configuration in `lua` directory.

- `lua` directory contains 3 parts.
  - `core` directory contains base configuration of neovim.
  - `keymap` directory contains keybindings of plugins.
  - `modules` directory contains 5 parts.
    - `completion` directory contains code completion's configuration.
    - `editor` directory contains plugins' configuration about editing.
    - `lang` directory contains plugins' configuration about specific language.
    - `tools` directory contains telescope and its extensions' configuration.
    - `ui` directory contains plugins' configuration about ui.

## Usage

* 已经集成了[nvim-lsp-installer](https://github.com/williamboman/nvim-lsp-installer), 只需手动安装对应语言的language server.

  * lsp-installer默认安装的html LSP有问题, 需要手动安装新的:

    ```sh
    npm i -g vscode-html-languageserver-bin
    ```

* For [nvim-treesitter](https://github.com/nvim-treesitter/nvim-treesitter#supported-languages), ensure installed parsers are configured [here](https://github.com/ayamir/nvimdots/blob/f593682b349f69a468bfeb6cd1eb87f810b8a37f/lua/modules/editor/config.lua#L19-L37), you can add or remove parsers on your own demand.

* For [efm-langserver](https://github.com/mattn/efm-langserver), you need to install itself and format/lint tools manually.

  ```
  brew install clang
  brew install eslint
  go install golang.org/x/tools/...@latest
  ```

---



* You can use `FormatToggle` command to enable/disable format-on-save which is enabled by default.

* Also, you can disable format-on-save for specific workspace by add its absolute path in `format_disabled_dirs.txt` in new line.

* You can use `:checkhealth` command to check whether all modules works or not.

* **Please ensure all of tools installed above can be found in `PATH`**.

* You can configure these tools in your own habit like `.eslintrc.js` and `.prettierrc.json`.

  Recommanded way to set **PATH** variable is export it in your `~/.profile` like this:

  ```sh
  export LOCAL_BIN="$HOME/.local/bin"
  
  export GOROOT="/usr/lib/go"
  export GOPATH="$HOME/go"
  export GOBIN="$HOME/go/bin"
  
  export HS_BIN="$HOME/.cabal/bin"
  
  export NPM_BIN="$HOME/.npm-global/bin"
  
  export KT_BIN="$HOME/.kotlin/bin"
  
  export RS_BIN="$HOME/.cargo/bin"
  
  export JAVA_HOME="/usr/lib/jvm/default"
  
  export BENTO_BIN="$HOME/.local/share/bento4/bin"
  
  export ROFI_BIN="$HOME/.config/rofi/bin"
  
  export PATH=$LOCAL_BIN:$GOBIN:$HS_BIN:$NPM_BIN:$RS_BIN:$JAVA_HOME:$BENTO_BIN:$ROFI_BIN:$PATH
  ```

  

## Customize

https://github.com/ayamir/nvimdots/wiki/Usage



nvim添加插件, 需要用[packaer.nvim](https://github.com/wbthomason/packer.nvim)

# LspInstall

https://github.com/williamboman/nvim-lsp-installer#available-lsps

## Commands

- `:LspInstallInfo` - opens a graphical overview of your language servers
- `:LspInstall [--sync] [server] ...` - installs/reinstalls language servers. Runs in a blocking fashion if the `--sync` argument is passed (only recommended for scripting purposes).
- `:LspUninstall [--sync] <server> ...` - uninstalls language servers. Runs in a blocking fashion if the `--sync` argument is passed (only recommended for scripting purposes).
- `:LspUninstallAll [--no-confirm]` - uninstalls all language servers
- `:LspInstallLog` - opens the log file in a new tab window
- `:LspPrintInstalled` - prints all installed language servers

# Dap

[Official Repositoty](https://github.com/mfussenegger/nvim-dap)



 *dap*.adapters 用来配置如何启动调试器， *dap*.configurations 用来配置如何将当前项目*加载*到调试器上

https://zignar.net/2023/02/17/debugging-neovim-with-neovim-and-nvim-dap/

```
if command -v curl >/dev/null 2>&1; then
    bash -c "$(curl -fsSL https://github.com/ayamir/nvimdots/blob/main/scripts/install.sh)"
else
    bash -c "$(wget -O- https://github.com/ayamir/nvimdots/blob/main/scripts/install.sh)"
fi
```



```
To use the bundled libc++ please add the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/c++ -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++"

llvm is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have llvm first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

For compilers to find llvm you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
```



nvim-dap is a Debug Adapter Protocol client, or "debugger", or "debug-frontend".

With the help of a debug adapter it can:

1. Launch an application to debug
2. Attach to running applications to debug them
3. Set breakpoints and step through code
4. Inspect the state of the application



Dap插件的配置代码位于: `~/.config/nvim/lua/modules/editor/plugins.lua`, 我们不需要改动. 

```lua
...

editor["rcarriga/nvim-dap-ui"] = {
	opt = false,
	config = conf.dapui,
	requires = {
		{ "mfussenegger/nvim-dap", config = conf.dap },
		{
			"Pocco81/dap-buddy.nvim",
			opt = true,
			cmd = { "DIInstall", "DIUninstall", "DIList" },
			commit = "24923c3819a450a772bb8f675926d530e829665f",
			config = conf.dapinstall,
		},
	},
}

...
```

## Structure

You'll need to install and configure a debug adapter per language. See

- [:help dap.txt](https://github.com/mfussenegger/nvim-dap/blob/master/doc/dap.txt)
- the [Debug-Adapter Installation](https://github.com/mfussenegger/nvim-dap/wiki/Debug-Adapter-installation) wiki
- `:help dap-adapter`
- `:help dap-configuration`



A debug adapter is a facilitator between nvim-dap (the client), and a language-specific debugger:

```txt
    DAP-Client ----- Debug Adapter ------- Debugger ------ Debugee
    (nvim-dap)  |   (per language)  |   (per language)    (your app)
                |                   |
                |        Implementation specific communication
                |        Debug adapter and debugger could be the same process
                |
         Communication via the Debug Adapter Protocol
```



adapter 示例:

```lua
	dap.adapters.python = {
		type = "executable",
		command = os.getenv("HOME") .. "/.local/share/nvim/dapinstall/python/bin/python",
		args = { "-m", "debugpy.adapter" },
	}
```



configurations 示例:

```lua
	dap.configurations.python = {
		{
			-- The first three options are required by nvim-dap
			type = "python", -- the type here established the link to the adapter definition: `dap.adapters.python`
			request = "launch",
			name = "Launch file",
			-- Options below are for debugpy, see https://github.com/microsoft/debugpy/wiki/Debug-configuration-settings for supported options

			program = "${file}", -- This configuration will launch the current file if used.
			pythonPath = function()
				-- debugpy supports launching an application with a different interpreter then the one used to launch debugpy itself.
				-- The code below looks for a `venv` or `.venv` folder in the current directly and uses the python within.
				-- You could adapt this - to for example use the `VIRTUAL_ENV` environment variable.
				local cwd = vim.fn.getcwd()
				if vim.fn.executable(cwd .. "/venv/bin/python") == 1 then
					return cwd .. "/venv/bin/python"
				elseif vim.fn.executable(cwd .. "/.venv/bin/python") == 1 then
					return cwd .. "/.venv/bin/python"
				else
					return "/usr/bin/python"
				end
			end,
		},
	}
```



## Usage

A typical debug flow consists of:

- Setting breakpoints via `:lua require'dap'.toggle_breakpoint()`.
- Launching debug sessions and resuming execution via `:lua require'dap'.continue()`.
- Stepping through code via `:lua require'dap'.step_over()` and `:lua require'dap'.step_into()`.
- Inspecting the state via the built-in REPL: `:lua require'dap'.repl.open()` or using the widget UI (`:help dap-widgets`)

See [:help dap.txt](https://github.com/mfussenegger/nvim-dap/blob/master/doc/dap.txt), `:help dap-mapping` and `:help dap-api`.

## Specific Daps

* 具体语言的Dap配置代码位于: `~/.config/nvim/lua/modules/editor/config.lua`. 

* 具体语言的Dap的安装文档: [Doc](https://github.com/mfussenegger/nvim-dap/wiki/Debug-Adapter-installation)



ayamir默认配置好了许多Dap, 大部分情况下我们只需安装对应的依赖, 让ayamir的代码生效即可. 





[github release](https://github.com/vadimcn/codelldb/releases/download/v1.9.0/codelldb-aarch64-darwin.vsix) just extract the file as zip and find the executable binary in there: /extension/adapter/*

### C/C++/Rust (via lldb-vscode)

ayamir用的就是`lldb-vscode`, 只需要自己自己下载`lldb-vscode`, 确保其能够在命令行调用, 再在ayamir的配置代码里把`lldb-vscode`的路径改为自己的路径即可:

1. install:

   `lldb-vscode`是LLVM的一个包, 只需安装LLVM, 并配置到环境变量即可

2. 找到LLVM的路径,将其`bin`目录配置到`PATH`, 这样该目录下的子命令( 包括`lldb-vscode` )就可以在命令行调用了. 这一步也是在安装LLVM的时候做的

3. `lldb-vscode` 在LLVM目录下, 太曲折了. 我们弄一个符号链接. 注意,  注意一般OS的软件都放在`/usr/bin`,但Mac不允许在`/usr/bin`随意操作( ln会报错"Operation not permitted" ), 因此我的软件链接放在`/usr/local/bin`

   ```sh
    ln -s /opt/homebrew/opt/llvm/bin/lldb-vscode /usr/bin/lldb-vscode
   ```

4. 修改代码中的路径:

   ```lua
   # ~/.config/nvim/lua/modules/editor/config.lua
   	dap.adapters.lldb = {
   		type = "executable",
   		
   		command = "/usr/local/bin/lldb-vscode", # 改到自己的路径
   		name = "lldb",
   	}
   
   
    »···dap.adapters.lldb = {
       1 »···»···type = "executable",
   │   2 »···»···-- 我使用OSX, brew自己安装的LLVM路径在/opt/homebrew/opt/llvm,·
   │   3 »···»···-- 做了个/usr/local/bin/lldb-vscode的软链接指向它
   │   4 »···»···-- 注意一般OS的软件都放在/usr/bin,但Mac不允许在/usr/bin随意操作
   │   5 »···»···-- 所以我放在/usr/local/bin
   │   6 »···»···command = "/usr/local/bin/lldb-vscode",
       7 »···»···name = "lldb",
       8 »···}
   ```

### Go

默认配置代码不需要改动, 只需安装依赖:

1. Install delve:

   ```sh
   go install github.com/go-delve/delve/cmd/dlv@latest
   ```

2. Install vscode-go:

   ```sh
   git clone https://github.com/golang/vscode-go
   cd vscode-go
   npm install
   npm run compile
   ```

# Keybinds

https://github.com/ayamir/nvimdots/wiki/Keybindings

## Modify keymap

https://github.com/ayamir/nvimdots/wiki/Usage#modify-keymap

- For vanilla nvim's keymap

  modify `lua/core/mapping.lua`

- For specific plugin's keymap

  modify `lua/keymap/init.lua`

- Command breakdown

  ```
      ┌─ sep     ┌── map_type
   ["n|gb"] = map_cr("BufferLinePick"):with_noremap():with_silent(),
     │  └── map_key          │              └── special     │
     └──── map_mode          └── map_content                └── special (can be chained)
  ```

### 






# Lazy.nvim

https://github.com/folke/lazy.nvim





 let b = 3;
    let sum = a + b;
    let product = a * b;
    let difference = a - b;
    let quotient = a / b;
    let remainder = a % b;



ln -s /Users/lyk/Projects/MyOfficialProjects/dotfiles/wezterm-dracula_theme/dracula.toml $HOME/.config/wezterm/colors/dracula.toml





```

```

# Font



[Nerd Fonts](https://www.nerdfonts.com/font-downloads)





**[JetBrainsMono](https://github.com/JetBrains/JetBrainsMono)**



![image-20230625212217416](/Users/lyk/Library/Application Support/typora-user-images/image-20230625212217416.png)







![image-20230625222854356](/Users/lyk/Library/Application Support/typora-user-images/image-20230625222854356.png)



[Fira Code](https://github.com/tonsky/FiraCode/releases/tag/6.2)





Fira COde Nerd Font Mono

![image-20230625223428192](/Users/lyk/Library/Application Support/typora-user-images/image-20230625223428192.png)

# NvChad

NVcheatsheet

1. `<leader>ch` to access that
2. 
