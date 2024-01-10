---
title: NvChad
tags:
  - Linux
  - Vim
categories:
  - Software Engineering
date: 2024-01-09 19:01:26
---


Source:

1. [NvChad](https://nvchad.com/docs/quickstart/install)
2. [NvChad --- Rocky Linux](https://docs.rockylinux.org/books/nvchad/nvchad_ui/using_nvchad/)
3. [Dreams of Code's NvChad playlist](https://www.youtube.com/playlist?list=PL05iK6gnYad1sb4iQyqsim_Jc_peZdNXf)
4. [BrunoKrugel's Github repo](https://github.com/BrunoKrugel/dotfiles)

Note: This article will only focus on **NvChad** itself. If you want to simply copy my computer configs (ALL OF THEM), you can refer to [*How to Set Up on A New Machine*](https://lyk-love.cn/2024/01/09/how-to-set-up-on-a-new-machine/).

<!--more-->

# How to install

[--> NvChad Installation Doc](https://nvchad.com/docs/quickstart/install)



1. Install NvChad

   ```sh
   git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1 && nvim
   ```

2. Set environment variable in `~/.zshrc` for convience:

   ```sh
   export NVIM_CUSTOM_HOME="$DOT_FILE_HOME/nvchad_custom"
   ```

3. Install NvChad. Detete its default custom file. Use a symbol link, which is to my custom file in the dotfile, to replace it.

   ```sh
   ln -s  $NVIM_CUSTOM_HOME/ ~/.config/nvim/lua/custom
   ```

# Components

## Treesitter

[Nvim-treesitter](https://github.com/nvim-treesitter/nvim-treesitter) plugin is used to suport syntax highlighting in NvChad. It can be used for various things such as auto indent etc too.

* For knowing correct parser names, do check [nvim-treesitter docs](https://github.com/nvim-treesitter/nvim-treesitter#supported-languages)

* You can also get a list of all available languages and their installation status with `:TSInstallInfo`

  ```
  TSInstallInfo
  ```

* To install parsers:

  ```
  TSInstall <parser>
  ```

- Example :

```lua
TSInstall lua html
```

But this may be tedious when you have so many parsers to install and  you'd have to repeat this step if you're re-installing nvchad with your  old custom settings.

## Telescope

FInd finds in current peoject (aka directory):

```
<leader> + ff
```



FInd finds in current buffer:

```
<leader> + fz
```



FInd finds in all buffers:

```
<leader> + fb
```

# Functionalitoes

* **Cheet sheet**:

  ```
  <Ctrl> + ch
  ```

## Window Management

window --> buffer

tab --> buffer

* Nagivate windows:

  ```
  <Ctrl> + [hjkl]
  ```

* Navigate tabs:

  ```
  <Tab>
  ```

* Close current buffer:

  ```
  <leader> + x
  ```

* Split windows:

  ```
  :vsp
  ```

  (vertical split)

### Terminal

* Open terminal horizontally:

  ```
  <leader> + h
  ```

* vertically

  ```
  <leader> + v
  ```

# LSP

## `neovim/nvim-lspconfig`

In `custom/plugins.lua`:

```lua
-- In order to modify the `lspconfig` configuration:
{
  "neovim/nvim-lspconfig",
   config = function()
      require "plugins.configs.lspconfig"
      require "custom.configs.lspconfig"
   end,
},
```

This controls the behavior of LSP.

The file `plugins/configs/lspconfi.lua`  is thr system config, we shouldn't change it. What we need to modify is `custom/configs/lspconfig.lua`. We can see its content:

```lua
local on_attach = require("plugins.configs.lspconfig").on_attach
local capabilities = require("plugins.configs.lspconfig").capabilities

local lspconfig = require("lspconfig")

-- if you just want default config for the servers then put them in a table
local servers = { "html", "cssls", "tsserver", "clangd", "pyright" }

-- Add attach and capabilities to every lspconfig[<lsp_server>]
for _, lsp in ipairs(servers) do
  lspconfig[lsp].setup {
    on_attach = on_attach,
    capabilities = capabilities,
  }
end
```

It's clear that the function  for loop `for _, lsp in ipairs(servers) do ... end` add the `on_attach` and `capabilities` attributes to every lsp server defined in the list `servers`.

So if we have a new lsp server, it has to be added to the `servers` list.

## `Mason.nvim`

The [mason.nvim](https://github.com/williamboman/mason.nvim#default-configuration) plugin is used to <u>install</u> LSP servers,  formatters, linters, and debug adapters. 

Note: Packages are installed in Neovim's data directory ([`:h standard-path`](https://neovim.io/doc/user/starting.html#standard-path)) by default. In Unix, it's under `~/.local/share/nvim`

You can mannualy install lsp packages using `:Mason`, that will open a window.

However, It's better to list all your  required packages in the config file so they automatically  install when running `MasonInstallAll` command.

As you can see in the `custom/plugins.lua`:

```lua
  -- override plugin configs
  {
    "williamboman/mason.nvim",
    opts = overrides.mason
  },
```

It reads the <u>mason</u> part of the override config file `custom/configs/overrides.lua`:

```lua
M.mason = {
  ensure_installed = {
    -- lua stuff
    "lua-language-server",
    "stylua",

    -- web dev stuff
    "css-lsp",
    "html-lsp",
    "typescript-language-server",
    "deno",
    "prettier",

    -- c/cpp stuff
    "clangd",
    "clang-format",

    -- python stuff
    "pyright",
  },
}
```

# Format & Lint

It is recommended that you install `null-ls` to manage formatting & linting. It hae s been installed as a dependency of `neovim/nvim-lspconfig`.

```lua
  -- In "custom/plugins.lua"
	{
    "neovim/nvim-lspconfig",
    dependencies = {
      -- format & linting
      {
        "jose-elias-alvarez/null-ls.nvim",
        config = function()
          require "custom.configs.null-ls" -- null-ls.nvim!!!
        end,
      },
    },
    -- .....
  },
```

As before, if we want to customize, we need to modify file `custom.configs.null-ls`.



# DAP

All custimzation should be made in the `custom` file.

There are 2 important files in **custom** dir which extend NvChad:

- **`custom/chadrc.lua`** meant to override that table in `default_config.lua` file
- **`custom/init.lua`** runs in the main `init.lua`, its meant to have vim options, globals, autocmds, commands etc.



The download of `nvim-dap-ui` may be slow. If you didn't see the UI when debugging, please install this plugin mannually.



# Customization

The config dir is  `~/.config/nvim/lua`, with total structure

```
.
├── LICENSE
├── init.lua
├── lazy-lock.json
└── lua
    ├── core
    │   ├── bootstrap.lua
    │   ├── default_config.lua
    │   ├── init.lua
    │   ├── mappings.lua
    │   └── utils.lua
    ├── custom
    │   ├── README.md
    │   ├── chadrc.lua
    │   ├── configs
    │   ├── highlights.lua
    │   ├── init.lua
    │   ├── mappings.lua
    │   └── plugins.lua
    └── plugins
        ├── configs
        └── init.lua
```

- **`init.lua` -** runs whole config
- **`core/default_config` -** returns a table of default options in NvChad.
- **`core/mappings` -** default mappings
- **`core/init` -** default globals, nvim options, commands, autocmds
- **`core/utils` -** helpful functions

## How to add LSP server

1. First, to install a lsp server, we need to add lsp config in the mason part of `custom/configs/overrides.lua`. For instance, we add a lsp server "pyright" to it.

   ```lua
   M.mason = {
     ensure_installed = {
       -- Other servers
   		-- ....
   		
       -- python stuff
       "pyright",
     },
   }
   ```

2. Next, we need to add this server to the `servers` list in  `custom/configs/lspconfig.lua`. For instance, since we already have a `pyright` server, we add it in the list:

   ```lua
   -- In "custom/configs/lspconfig.lua"
   local servers = { "html", "cssls", "tsserver", "clangd", "pyright" }
   ```

   

3. config this server so that it can apply to python files. In we h

## Other Plugins

* `olimorris/persisted.nvim`
* `Zeioth/compiler.nvim`
* `akinsho/toggleterm.nvim`
* `nvim-neotest/neotest`
* `folke/noice.nvim`: colorful floating notice message



## CPP



By default, clang-format is K&R style. You can change the format by putting a `.clang-format` file in the project.

For instance, if you want to use Google clang style:

```sh
clang-format --style Google --dump-config > .clang-format
```

Then save and format.



# Plugins

## Project Manager

The following table shows all available operations

| Key     | Operation                                       |
| ------- | ----------------------------------------------- |
| `<CR>`  | Opens the project under the cursor              |
| `<C-a>` | Adds a project through an interactive procedure |
| `<C-d>` | Delete a project                                |
| `<C-e>` | Change project settings                         |
| `<C-q>` | Close buffer                                    |

To add your first project you will need to use the combination Ctrl + a which will open an interactive menu in the *statusline*.

# Run

1. `<leader> + db`
2. `<leader> + dr`

Don't need to `<leader> +dus`

## Rust

```
RustDebuggales
```

