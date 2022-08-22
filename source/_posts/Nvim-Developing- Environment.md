---
title: Nvim Developing Environment
categories: Toolkit
date: 2022-08-17 22:52:46
tags:
---


Outline:

* Nvim
* LspInstall
* Dap
* Keybinds

<!--more-->

# Nvim

使用[ayamir的Nvim配置](https://github.com/ayamir/nvimdots/),  它集成了大量插件, 包括Nvim + LSP + Dap.

其配置文件位于`~/.config/nvim/lua`



## Install

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
   # ~/.config/nvim/lua/modules/editor
   	dap.adapters.lldb = {
   		type = "executable",
   		
   		command = "/usr/local/bin/lldb-vscode", # 改到自己的路径
   		name = "lldb",
   	}
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
