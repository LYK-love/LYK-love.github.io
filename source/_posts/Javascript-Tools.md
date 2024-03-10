---
title: Javascript Tools
tags: Javascript
categories:
  - Software Engineering
date: 2024-01-09 20:56:20
---


Source:

1. [How To Install Node.js on Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-node-js-on-ubuntu-20-04)

<!--more-->

# Install nodejs

## Via nvm

In order to install npm, you can install [nvm](https://github.com/nvm-sh/nvm) firs and use it to install npm.

1. Visit [the project’s GitHub page](https://github.com/nvm-sh/nvm), run:

   ```sh
   curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
   ```

   The script clones the nvm repository to `~/.nvm`, and attempts to add the source lines from the snippet below to the correct profile file (`~/.bash_profile`, `~/.zshrc`, `~/.profile`, or `~/.bashrc`).

   ```shell
   export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
   [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh" # This loads nvm    
   ```

2. To enable nvm, you should update your bash config file. I use zsh, so the file is `~/.zshrc`:

   ```sh
   source ~/.zshrc
   ```

3. Now, you can ask NVM which versions of Node are available:

   ```bash
   nvm list-remote
   ```

4. You can install a version of Node by writing  in any of the release versions listed. For instance, to get version  v14.10.0, you can run:

   ```bash
   nvm install v14.10.0
   ```

5. You can use a designated version of installed nodejs:

   ```sh
   nvm use v14.10.0
   ```

   



You can view the different versions you have installed by listing them:

```sh
nvm list
```

This shows the currently active version on the first line (`-> v14.10.0`), followed by some named aliases and the versions that those aliases point to.

**Note:** if you also have a version of Node.js installed through `apt`, you may receive a `system` entry here. You can always activate the system-installed version of Node using `nvm use system`.

Additionally, there are aliases for the various [long-term support (or LTS) releases of Node](https://nodejs.org/en/about/releases/):

```
Outputlts/* -> lts/hydrogen (-> N/A)
lts/argon -> v4.9.1 (-> N/A)
lts/boron -> v6.17.1 (-> N/A)
lts/carbon -> v8.17.0 (-> N/A)
lts/dubnium -> v10.24.1 (-> N/A)
lts/erbium -> v12.22.12 (-> N/A)
lts/fermium -> v14.21.2
lts/gallium -> v16.19.0 (-> N/A)
lts/hydrogen -> v18.13.0 (-> N/A)
```

You can install a release based on these aliases as well. For instance, to install the latest long-term support version, `hydrogen`, run the following:

```bash
nvm install lts/hydrogen
OutputDownloading and installing node v18.13.0...
. . .
Now using node v18.13.0 (npm v8.19.3)
```

You can switch between installed versions with `nvm use`:

~~~bash
nvm use v14.10.0
OutputNow using node v14.10.0 (npm v6.14.8)
```

You can verify that the install was successful using the same technique from the other sections:

```command
node -v
Outputv14.10.0
~~~

The correct version of Node is installed on your machine as expected. A compatible version of `npm` is also available.

## Via apt (not recommended)

The `nodejs` installed via `apt` is very old. Therefore it's not recommended to use `apt` to install it.

1. Update the Apt package index:

   ```bash
   sudo apt update
   ```

2. Then install Node.js:

   ```bash
   sudo apt install nodejs
   ```

3. Check that the install was successful by querying `node` for its version number:

   ```bash
   node -v
   Outputv10.19.0
   ```

4. Install `npm`, the Node.js package manager. You can do this by installing the `npm` package with `apt`:

   ```bash
   sudo apt install npm
   ```

   This allows you to install modules and packages to use with Node.js.



The `npm` will be installed automatically together with `nodejs`.



## Via conda (not recommended)

Search:

```sh
conda search -c conda-forge nodejs
```

Then install one version:

```
conda install -c conda-forge nodejs=8.11.3
```



# Change npm source

国内优秀npm镜像：

淘宝npm镜像

- 搜索地址：[http://npm.taobao.org/](https://link.jianshu.com?t=http://npm.taobao.org/)
- registry地址：[http://registry.npm.taobao.org/](https://link.jianshu.com?t=http://registry.npm.taobao.org/)

cnpmjs镜像

- 搜索地址：[http://cnpmjs.org/](https://link.jianshu.com?t=http://cnpmjs.org/)
- registry地址：[http://r.cnpmjs.org/](https://link.jianshu.com?t=http://r.cnpmjs.org/)



 1.临时使用

```python
npm install express --registry https://registry.npm.taobao.org
```



2.持久使用

```python
npm config set registry https://registry.npm.taobao.org
```

配置后可通过下面方式来验证是否成功:

```shell
npm config get registry
```

# node_modules Management

一般通过包管理工具来对node_modeules进行管理。 不过手动删除这个操作无论是yarn还是npm都特别慢， 可以使用额外的工具`rimraf`， 它是node的一个包，可以快速删除`node_modules`，再也不用等半天了

- 安装： `npm install rimraf -g`
- 使用：`rimraf node_modules`

# nvm

[Github: nvm](https://github.com/nvm-sh/nvm)

`nvm` allows you to quickly install and use different versions of node via the command line.

**Example:**

```
$ nvm use 16
Now using node v16.9.1 (npm v7.21.1)
$ node -v
v16.9.1
$ nvm use 14
Now using node v14.18.0 (npm v6.14.15)
$ node -v
v14.18.0
$ nvm install 12
Now using node v12.22.6 (npm v6.14.5)
$ node -v
v12.22.6
```

​    

Simple as that!

## Commands

- 查看当前node版本:

  ```shell
  nvm current
  ```

  或者:

  ```
  node -v
  ```



* 卸载指定版本node:

  ```shell
  nvm uninstall <version>
  ```



- 列出所有可以安装的node版本号:

  ```shell
  nvm ls-remote：
  ```



- 安装指定版本号的node

  ```
  nvm v15.1.0
  ```

  或者( e.g. 对于node版本15.X ):

  ```shell
  nvm install 15
  ```



- 安装最新版本的node：

  ```
  nvm install node
  ```



- 全局地切换node的版本:

  ```
  nvm use v15.1.0
  ```

  或者( e.g. 对于node版本15.X):

  ```shell
  nvm use 15
  ```



- 列出所有已经安装的node版本:

  ```shell
  nvm ls
  ```

# npm

[npm doc](https://docs.npmjs.com/cli/v6/configuring-npm)

## npm vs yarn

| **npm**                      | **yarn**             | **说明**                                           |
| ---------------------------- | -------------------- | -------------------------------------------------- |
| npm install                  | yarn                 | 安装项目依赖                                       |
| npm install react --save     | yarn add react       | 添加一个依赖到项目中，如：添加 react 到项目。      |
| npm uninstall react --save   | yarn remove react    | 从项目删除一个依赖，如：从项目删除 react 依赖      |
| npm install react --save-dev | yarn add react --dev | 将项目依赖添加到开发依赖，只有在开发模式下才能使用 |
| npm update --save            | yarn upgrade         | 更新项目依赖                                       |



## Problems

1. This version of npm is compatible with lockfileVersion@1, but package-lock.json was generated for lockfileVersion@2. I’ll try to do my best with it!

   这是因为npm的版本和依赖文件中某些依赖所需的npm版本不同. 

   从报错可以看出npm适用于lockfileVersion@1, 但是`package-lock.json`是源于lockfileVersion@2的.

   * 这时就需要更改npm版本
   * 还有一种可能, 注意到`npm -g`和`npm`使用的是不同的npm, 所以出现这个问题很有可能是错误使用了`npm -g`

## Commands

* 查看npm版本:

  ```shell
  npm -v
  ```

  

* 安装/更新到最新版本:

  ```shell
  npm -g install  npm
  ```

  

* 安装/更新到指定版本:

  ```shell
  npm -g install npm@6.14.11
  ```


---



* 查看全局安装目录:

  ```shell
  npm root -g
  ```

  

---



* 下载依赖：

  ```
  npm i[nstall] <package> --save-dev
  ```

  * `--save`，简写为`-s`或`-S`：**将依赖信息保存至 `package.json`**, 默认保存到`dependencies`属性

    该option后可以跟选项，指定具体的依赖类型

    * `--save-dev`，简写为`-d`或`-D`: 指定依赖类型为dev dependency, 依赖信息会被保存在`devDependencies`属性。

  * **对于npm > 5.0， 默认会启用`--save`**

  * `-g`:全局安装

* 卸载依赖: 在项目根目录, 即node_modules所在目录运行: **注意, 卸载并不会把依赖从package.json中去掉**( 但是安装会 )

  ```sh
  npm un[install] <package-name>
  ```

  *  `-S` 或 `--save` 标志，则此操作还会移除 `package.json` 文件中的引用.

* 如果程序包是开发依赖项（列在 `package.json` 文件的 devDependencies 中），则必须使用 `-D` 或 `--save-dev` 标志从文件中移除

  * 如果该软件包是全局安装的，则需要添加 `-g` 或 `--global` 标志：
  * 可以在系统上的任何位置运行`npm un -g`, 因为当前所在的文件夹无关紧要

## Config

Note: If `npm install` extremely slow, there's highly possible sth wrong with your config file.



npm获取配置的方式，优先级由高到低：

* 命令行参数： 以设置代理为例：--proxy http://server:port即将proxy的值设为http://server:port。

* 环境变量：以npm_config_为前缀的环境变量将会被认为是npm的配置属性。以设置proxy为例可以加入这样的环境变量npm_config_proxy=http://server:port。

* Get the user config file:

  ```sh
  npm config get userconfig
  ```

* Get the glocal config file:

  ```sh
  npm config get globalconfig
  ```

* 内置配置文件：安装npm的目录下的npmrc文件。

* 默认配置： npm本身有默认配置参数，如果以上都没设置，则npm会使用默认配置参数。

* Reset configs of npm:

  ```sh
  npm cache clean --force
  rm -f ./.npmrc
  npm config set key default
  ```

  



```shell
npm config set <key> <value> [--global]
```



```
npm config get <key>
```



```
npm config delete <key>
```



```
npm config list
```



```
npm config edit
```



```
npm get <key>
```

```
npm set <key> <value> [--global]
```





命令行操作说明：

在设置配置属性时属性值默认是被存储于用户配置文件中，如果加上--global，则被存储在全局配置文件中。

如果要查看npm的所有配置属性（包括默认配置），可以使用`npm config ls -l`

## npm run

https://www.cnblogs.com/goloving/p/16306638.html

## Problems

### Dockerizing

使用Docker构建vue镜像:

```dockerfile
# ENV NODE_ENV production
RUN node -v && npm -v \
    && npm config set registry http://r.cnpmjs.org/ \
    && npm install


COPY . .
RUN npm run build
```

其中的`npm run build`会调用package.json中的build字段的命令:

```json
  "scripts": {
    "serve": "vue-cli-service serve",
    "build": "vue-cli-service build",
    "lint": "vue-cli-service lint"
  },
```

可以看到, `vue-cli-service`都使用了`vue-cli-service`这个命令, 他对应了一系列依赖:

```json
		<snip>  
		"@vue/cli-plugin-babel": "~5.0.0",
    "@vue/cli-plugin-eslint": "~5.0.0",
		<snip>
```

这些依赖默认全部被安装到了devDependencies. 因此, 如果在install时使用了pro模式, 即只下载pro依赖, 则不会下载上述依赖, 也就会在`npm run build`时报错:

```
Error: Cannot find module '@vue/cli-plugin-babel'
//OR:
vue-cli-service: not found
```

* 该问题发生的常见情况是, 在Dockerfile里配置了`ENV NODE_ENV production`, 

因此, **千万不要在install的时候用production**, 当然你可以在build和run的时候开启:

```json
  "scripts": {
    "serve": "vue-cli-service serve  --open  --mode development",
    "build": "vue-cli-service build --mode production",
    "lint": "vue-cli-service lint"
  },
```



## npx

npx: [a package runner tool that comes with npm 5.2+](https://medium.com/@maybekatz/introducing-npx-an-npm-package-runner-55f7d4bd282b).

 [教程]( https://www.ruanyifeng.com/blog/2019/02/npx.html)



由于node自带npm，后者( 在 npm >= 5.2 后)又自带npx，所以安装node后可以直接使用npx.

手动安装npx:

```bash
npm install -g npx
```



简单来说，npx可以指定使用某个版本的node，让该版本的node来执行命令。 避免了项目构建中需要降低node版本的尴尬情况

> ```bash
> npx node@0.12.8 [command]
> ```

上面命令会使用 0.12.8 版本的 Node 执行脚本。原理是从 npm **下载这个版本的 node，使用后再删掉**。

`-p`： 在安装指定版本的node后，不删除该node



npx可以替代很多npm版本管理工具，比如`nvm`

## n

1. 安装n模块:

   ```
   npm install -g n
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

3. 安装指定版本node:

   ```shell
    n v14.16.0
   ```

4. 切换node版本：

   ```shell
   n 7.10.0
   ```

# yarn

[Documentation](https://yarnpkg.com/getting-started/usage)

Yarn是facebook发布的一款取代npm的包管理工具， Yarn并行地安装包，速度比npm快。 **推荐使用yarn**

## Installation

[Installation of corepack and yarn](https://yarnpkg.com/getting-started/install)

`corepack`是一个对包管理器进行管理的工具，其安装包中包含了`yarn`. 也就是说，安装了`corepack`后就不需要手动安装`yarn`了

> 也可以用npm安装yarn，但是不推荐这种方法:
>
> ```
> npm install -g yarn
> ```



* **Node.js <16.10**: 

  Node默认包括了`npm`. 但在Node v16.10之前， Node没有默认包括`corepack`， 需要手动安装:

  ```
  npm i -g corepack
  ```

  

* Node.js >=16.10:

  v16.10之后，node默认包含了`corepack`， 但只是作为可选项，没有默认启用。 需要手动启用:

  ```
  corepack enable
  ```



安装完`corepack`就可以直接使用`yarn`了！



## Commands

* 把Yarn更新到最新版本

  ```
  yarn set version stable
  ```

---



* 查看全局安装目录：

  ```shell
  npm install -g yarn react-native-cli
  ```

---



* Accessing the list of commands

  ```
  yarn help
  ```

---



* Starting a new project

  ```
  yarn init
  ```

  * 同`npm init`，执行输入信息后，会生成`package.json`文件

---



* Installing all the dependencies

  ```
  yarn
  ```

  OR:

  ```
  yarn install
  ```

  * 这会安装`package.json`里所有包，并将所有依赖项信息保存进`yarn.lock`

  * options:

    * 强制重新下载所有包:

      ```shell
      yarn install --force 
      ```

---



* Adding a dependency:

  ```
  yarn add [package]
  ```

  * 依赖信息会自动更新到`package.json`和`yarn.lock`文件中
  * `yarn global add`： 全局安装

  

  * 安装指定版本, 这里指的是主要版本，如果需要精确到小版本，使用-E参数

    ```
    yarn add [package]@[version]
    ```

  * 安装某个tag（比如beta,next或者latest）:

    ```
    yarn add [package]@[tag]
    ```



* 指定添加的依赖类型：

  ```shell
  yarn add [package] --dev  # dev dependencies
  yarn add [package] --peer # peer dependencies
  ```

  

  

* Upgrading a dependency

  ```
  yarn up [package]
  yarn up [package]@[version]
  yarn up [package]@[tag]
  ```

  

* Removing a dependency

  ```
  yarn remove [package]
  ```

  

* Upgrading Yarn itself

  ```
  yarn set version latest
  yarn set version from sources
  ```


---

* 启动项目:

  ```shell
  yarn start
  ```

  

## yrm

yrm 是一个`yarn`源管理器，允许你快速地在源间切换

* 安装:

  ```
  yarn global add yrm
  ```

* 查看可用源:

  ```
  yrm ls
  ```

  

  

  

  




* 选择源:

  ```
  yrm use [source]
  ```

## Problems

* mac 运行react 项目时报错: `/bin/sh: craco: command not found` ， 很明显是`craco`这个命令没安装。 

  ```
  yarn add @craco/craco#
  ```

  OR

  ```
  npm install @craco/craco --save
  ```


# 
