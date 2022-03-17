---
title: Tips for Building Vue Projects
categories: FrontEnd
---











# intro

前端包管理工具有npm和yarn,后者是npm的进化版，推荐用yarn

前端项目clone下来， nom install报错是很正常的， 其实依赖报错最主要的原因就是npm或node版本不对。

# npm

`nvm`、`node`、`npm` 区别

* `nvm`：`nodejs` 版本管理工具，也就是说：一个 `nvm` 可以管理很多 `node` 版本和 `npm` 版本。
* `nodejs`：在项目开发时的所需要的代码库。
* `npm`：`nodejs` 包管理工具，在安装的 `nodejs` 的时候，`npm` 也会跟着一起安装，它是包管理工具，`npm` 管理 `nodejs` 中的第三方插件。

`nvm`、`node`、`npm` 关系

* `nvm` 管理 `nodejs` 和 `npm` 的版本，`npm` 可以管理 `nodejs` 的第三方插件
* 另外还有`n`， n 命令是作为一个 node 的模块而存在，而 nvm 是一个独立于 node/npm 的外部 shell 脚本，因此 n 命令相比 nvm 更加局限



## commands

如果不是最新版本，运行指令

```
npm install -g npm
1
```

如果想更新到指定版本，运行指令

```
npm -g install npm@6.8.0
```



## config

npm获取配置的方式，优先级由高到底。

命令行参数。 以设置代理为例：--proxy http://server:port即将proxy的值设为http://server:port。

环境变量。 以npm_config_为前缀的环境变量将会被认为是npm的配置属性。以设置proxy为例可以加入这样的环境变量npm_config_proxy=http://server:port。

用户配置文件。可以通过npm config get userconfig查看文件路径。

全局配置文件。可以通过npm config get globalconfig查看文件路径。

内置配置文件。安装npm的目录下的npmrc文件。

默认配置。 npm本身有默认配置参数，如果以上都没设置，则npm会使用默认配置参数。

命令行操作：

npm config set <key> <value> [--global]

npm config get <key>

npm config delete <key>

npm config list

npm config edit

npm get <key>

npm set <key> <value> [--global]

命令行操作说明：

在设置配置属性时属性值默认是被存储于用户配置文件中，如果加上--global，则被存储在全局配置文件中。

如果要查看npm的所有配置属性（包括默认配置），可以使用npm config ls -l。

# npx

node版本管理工具npx, 教程： https://www.ruanyifeng.com/blog/2019/02/npx.html

node自带npx

简单来说，npx可以指定使用某个版本的node，让该版本的node来执行命令。 避免了项目构建中需要降低node版本的尴尬情况

> ```bash
> npx node@0.12.8 [command]
> ```

上面命令会使用 0.12.8 版本的 Node 执行脚本。原理是从 npm **下载这个版本的 node，使用后再删掉**。

`-p`： 在安装指定版本的node后，不删除该node



npx可以替代很多npm版本管理工具，比如`nvm`

# n

1. 安装n模块:

   ```
   `npm install -g n
   ```

   报错则改用另一条命令：

   ```
   npm install -g n --force
   ```

2. 升级node.js到最新稳定版

   ```shell
   n stable
   # 或者升级到最新版
   n latest
   ```

3、安装指定版本

```
 n v6.11.5
```

# node

* `nvm uninstall <version>` ：卸载指定版本node

- `nvm ls-remote`：列出所有可以安装的node版本号

- `nvm install v15.1.0`：安装指定版本号的node

- `nvm use v15.1.0`：切换node的版本，这个是全局的

- `nvm current`：当前node版本

  或者`npm -v`

- `nvm ls`：列出所有已经安装的node版本

# vue

### vue-cli 安装

安装之前先卸载旧版本

```
npm uninstall -g @vue/cli
```

安装3.0及其以后版本

```
npm install -g @vue/cli@x.x.x
```

安装3.0以前的旧版本

```
npm install -g vue-cli@2.x
```



查看vue-cli版本

```
vue -V
```

### vue3安装

```bash
npm install vue@next
```



查看vue版本：

```
npm list vue
```

