---
title: Tips for Building Front-end Projects
categories: Toolkit
date: 2022-07-30 17:23:43
---


Outline:

* Intro
* node
* npm
* yarn
* ...

<!--more-->

# Intro

前端包管理工具有npm和yarn,后者是npm的进化版，推荐用yarn

前端项目clone下来， `[npm/yarn] install`报错是很正常的， 其实依赖报错最主要的原因就是npm/yarn或node版本不对。



# node



## node生态的基本工具

* `nodejs`是JS的一个运行时库，用于在native环境下运行JS
* `nvm`：`nodejs` 的一个**版本管理工具**，用于管理 `nodejs` 和 `npm` 的版本。 `nvm`是一个独立于`node`/`npm`的Shell脚本，需要手动安装
* `npm` or `yarn: `: `nodejs`的包管理工具（就是安装第三方模块的工具）主要是`npm`和`yarn`
  * `npm`已经被包含在Nodejs包中，不需要手动安装
  * `yarn`被包含在`corepack`中，后者是一个对包管理工具进行管理的工具，其二进制包中默认包含了`yarn`。 也就是说安装了`corepack`就同时安装了`yarn`。 当然也可以独立地安装`yarn`，但是不推荐
* `n`: `n`命令是`nodejs`的一个模块，用法类似于`nvm`. 不过作为一个集成进`nodejs`的模块，它的功能比`nvm`局限很多

## 包所在文件`node_modules`

`node_modules`：node安装的第三方模块的所在文件夹。 通过包管理工具( `npm` or `yarn` )安装的第三方模块都会被下载到该文件夹。

* 包默认会被安装在项目根目录下的`node_modules`。 如果指定了全局安装：

  * `npm install -g`: node目录下的`node_modules`， 比如`~/.nvm/versions/node/v18.4.0/lib/node_modules`

    * 用`npm root -g`查看

  *  `yarn global add`: `yarn`的全局安装目录不是node目录，而是形如`~/.config/yarn/global`

    * 用`yarn global dir`查看

    

## 项目描述文件`package.json`

`package.json`： 使用`npm`/ `yarn`生成node项目后，会生成项目的描述文件`package.json`，记录了当前项目信息，例如项目名称、版本、作者、github地址、**当前项目依赖了哪些第三方模块**等

* 一个文件夹，如果其目录下有`package.json`, 它就是一个node项目

* `package.json`只是**初步指定**了项目的依赖( 依赖名和依赖的版本 )， 但没有指定依赖的详细信息。

  * 例如， `package.json`只指定了大版本，也就是版本号的第一位，并不能锁定后面的小版本，每次 `npm install` 都是拉取的该大版本下的最新的版本。 版本管理粒度太粗了，为了稳定性考虑我们几乎不敢随意升级依赖。
  * 所以在npm > 5.0之后，增加了`package-lock.json`文件来指定**具体的依赖信息**(比如依赖具体来源和具体版本号）)。 yarn的`yarn.lock`文件也类似
  * 简言之，**`package.json` 由于历史遗留原因，没能做到细粒度的依赖管理。 具体依赖信息都记录在`package-lock.json`或`yarn.lock`中**

  

* 对于**`npm < 5.0`**,  `npm install [package]`只会下载依赖，不会把依赖信息添加到`package.json`， 需要手动配置进去。使用`--save`选项，把依赖信息自动添加到到`package.json`:

  ```
  npm install [package] --save
  ```

* 对于`yarn`，`yarn add [package]`会将依赖信息写入`package.json`
* 对于**`npm > 5.0`**，`npm install [package]`已经可以自动将依赖信息写入`package.json`了

### example

```json
{ 
  //项目名称
  "name": "description",
  //项目的版本
  "version": "1.0.0",
  //项目的描述
  "description": "在这里可以快速了解当前项目的功能及作用",
  //项目的主入口文件,在模块化项目中都会有一个主模块,main 里面填写的就是主模块的入口文件
  "main": "index.js",
  //定义命令别名,当命令很长时可以使用别名替换
  //使用方法:npm run 别名
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "nodemon app.js"
  },
  //关键字,它允许我们使用关键字去描述当前的项目
  "keywords": [],
  //项目的作者
  "author": "",
  //项目遵循的协议,默认是ISC也就是开放源代码的协议
  "license": "ISC",
  //项目依赖所需要的第三方模块（包）
  "dependencies": {
    "formidable": "^1.2.1",
    "mime": "^2.3.1"
  },
  //开发依赖所需要的第三方模块（包）
  "devDependencies": {
    "gulp": "^3.9.1"
  }
}
```

### dependency categories

`package.json`中记录的依赖有三种:

* production dependencies: **是依赖的默认种类**.在项目开发和运行阶段都需要的依赖。

  * 在添加依赖时( 使用`npm install [包名]`/ `yarn add [包名]` )，如果不手动指定，则都添加为producrtion dependencies
  * 被记录在`package.json`的`dependencies`属性

* dev dependencies: 只在开发过程中需要，而运行时不需要的依赖（比如 Babel 和 Flow）

  * 被记录在`devDependencies`属性

* peer dependencies: 在发布包的时候需要的依赖。有这种依赖意味着安装包的用户也需要和包同样的依赖。 这对于像 react 这样也被人安装的、需要单一 react-dom 副本的包很有用

  * 用于安装可能与使用者冲突的包

    > 我们组件的包需要react，使用者的项目也需要react，两个react的版本可能不一致，这个时候可以使用`peer-dependencies`来安装我们的react，避免与使用者冲突。

  * 被记录在`peerDependencies` 属性


## 具体依赖管理文件

### package-lock.json

`package-lock.json`: 在npm > 5.0 使用`npm install` 下载依赖会生成`package-lock.json`文件。**它记录了实际依赖版本信息，下次可以通过该文件去下载依赖，保证项目每次下载的依赖版本完全一致**。

作用如下：

* 锁定包的版本，确保再次下载时不会因为包版本不同而产生问题
* 加快下载速度，因为该文件中已经记录了项目所依赖第三方包的树状结构和包的下载地址，重新安装时只需下载即可，不需要做额外的工作



注意：

* npm < 5.0 没有`package-lock.json`，也不能自动把依赖信息写入`package.json`



### yarn.lock

`yarn.lock`:  使用`yarn add`下载依赖会生成`yarn.lock`文件。其作用基本上等于`npm`的`package-lock.json`。

* `yarn.lock` 文件会锁定你安装的每个依赖项的确切版本，这可以确保你不会意外获得不良依赖。如：以前是1.2.1，执行 yarn 后，变为 1.2.2
* 注意，**如果一个项目既用了`npm install`又用了`yarn add`， 那么会同时存在`package-lock.json`和`yarn.lock`文件**，会发生什么我也不知道，所以一个项目最好只用一个依赖管理工具

## node模块

在node.[js](http://www.fly63.com/tag/js)中模块与文件是一一对应的，也就是说一个node.[js](http://www.fly63.com/tag/js)文件就是一个模块。

* 核心模块：nodejs已经内置的一些模块，不需要用包管理工具下载
* 外部模块：需要用包管理工具下载，下载后均存放在`node_modules`文件夹中

### node模块查找规则

#### 通过路径查找

当指定模块路径时

```javascript
require('./find.js');
require('./find'); //模块文件后缀可以省略
```



1. require方法根据该路径查找模块，如果是完整路径，直接引入模块。
2. 如果模块后缀省略，先找同名JS文件再找同名JS文件夹
3. 如果找到了同名文件夹，找文件夹中的`index.js`
4. 如果文件夹中没有`index.js`就会去当前文件夹中的`package.json`文件中查找main选项中的入口文件
5. 如果找指定的入口文件不存在或者没有指定入口文件就会报错，模块没有被找到

#### 通过模块名查找

可以不指定路径，直接写模块名:

```javascript
require('find');
```

1. Node.js会假设它是系统模块
2. Node.js会去`node_modules`文件夹中
3. 首先看是否有该名字的JS文件
4. 再看是否有该名字的文件夹
5. 如果是文件夹看里面是否有`index.js`
6. 如果没有index.js查看该文件夹中的`package.json`中的main选项确定模块入口文件
   否则找不到报错



简言之，先查同名的系统模块，找不到再去`node_modules`中查外部模块

## 查看node项目版本

1. 如果项目使用 yarn 和 typescript，可以查看yarn.lock 里的@types/node@ 的 version:

   ```
   "@types/node@*":
     version "14.0.20"
     resolved "https://registry.npmjs.org/@types/node/-/node-14.0.20.tgz#0da05cddbc761e1fa98af88a17244c8c1ff37231"
     integrity sha512-MRn/NP3dee8yL5QhbSA6riuwkS+UOcsPUMOIOG3KMUQpuor/2TopdRBu8QaaB4fGU+gz/bzyDWt0FtUbeJ8H1A==
   ```

2. packageJson.engines，第三方模块都会有，自己的项目中有可能有

3. FROM，如果采用 docker 部署，查看基础镜像 Dockerfile 中 node 的版本号

4. 如果以上方式都不可以，那就只能问人或者自己蒙了. 可以查找[nodejs的版本发布表](https://nodejs.org/zh-cn/download/releases/), 根据项目的日期大概能猜出来版本

那只有问人了. **因此强烈建议项目使用yarn + Ts**

## nvm 

### Commands



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

  

  

### Installation

以下只演示[macOS上的NVM安装过程](https://tecadmin.net/install-nvm-macos-with-homebrew/#:~:text=%20How%20To%20Install%20NVM%20on%20macOS%20with,ready%20for%20the%20installation.%20Update%20the...%20More%20)， 对于Linux，nvm只要一行命令就可以安装了

1.  Remove existing Node Versions

   ```shell
   brew uninstall --ignore-dependencies node 
   brew uninstall --force node 
   ```

2. Install NVM on macOS

   ```shell
   brew update 
   brew install nvm 
   ```

3. Next, create a directory for NVM at home.

   ```shell
   mkdir ~/.nvm 
   ```

4. 编辑配置文件(这里我用的是`~/.zshrc`)

   ```shell
   nvim ~/.zshrc
   ```

5. 使编辑生效:

   ```shell
   source ~/.zshrc
   ```

   

## node Installation

在安装了nvm的情况下:

Install any version listed in above output. You can also use aliases names like **node** for latest version, **lts** for latest LTS version, etc.

```shell
nvm install node     ## Installing Latest version 
nvm install 14       ## Installing Node.js 14.X version 
```

After installing you can verify what is installed with:

```
nvm ls
```



## node_modules Management

一般通过包管理工具来对node_modeules进行管理。 不过手动删除这个操作无论是yarn还是npm都特别慢， 可以使用额外的工具`rimraf`， 它是node的一个包，可以快速删除`node_modules`，再也不用等半天了

- 安装： `npm install rimraf -g`
- 使用：`rimraf node_modules`

# npm

## npm vs yarn

| **npm**                      | **yarn**             | **说明**                                           |
| ---------------------------- | -------------------- | -------------------------------------------------- |
| npm install                  | yarn                 | 安装项目依赖                                       |
| npm install react --save     | yarn add react       | 添加一个依赖到项目中，如：添加 react 到项目。      |
| npm uninstall react --save   | yarn remove react    | 从项目删除一个依赖，如：从项目删除 react 依赖      |
| npm install react --save-dev | yarn add react --dev | 将项目依赖添加到开发依赖，只有在开发模式下才能使用 |
| npm update --save            | yarn upgrade         | 更新项目依赖                                       |



## npm Installation

node自带了npm，所以安装node后就默认安装了对应版本的npm







## Commands

* 查看npm版本:

  ```shell
  npm -v
  ```

  

* 安装/更新到最新版本:

  ```shell
  npm install -g npm
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
  npm install [package] --save-dev
  ```

  * `--save`，简写为`-s`或`-S`：将依赖信息保存至 `package.json`, 默认保存到`dependencies`属性。 这个option后可以跟选项，指定具体的依赖类型

    * `--save-dev`，简写为`-d`或`-D`: 指定依赖类型为dev dependency, 依赖信息会被保存在`devDependencies`属性。

  * 对于npm > 5.0， 默认会启用`--save`

  * `-g`:全局安装

    

## Config

npm获取配置的方式，优先级由高到低：

* 命令行参数： 以设置代理为例：--proxy http://server:port即将proxy的值设为http://server:port。

* 环境变量：以npm_config_为前缀的环境变量将会被认为是npm的配置属性。以设置proxy为例可以加入这样的环境变量npm_config_proxy=http://server:port。

* 用户配置文件：可以通过npm config get userconfig查看文件路径。

* 全局配置文件：可以通过npm config get globalconfig查看文件路径。

* 内置配置文件：安装npm的目录下的npmrc文件。

* 默认配置： npm本身有默认配置参数，如果以上都没设置，则npm会使用默认配置参数。



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

[文档](https://yarnpkg.com/getting-started/usage)

Yarn是facebook发布的一款取代npm的包管理工具， Yarn并行地安装包，速度比npm快。 **推荐使用yarn**

## corepack Installation

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



*  指定添加的依赖类型：

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


# React

生成一个全新的 ts + react 的模版:

```
npx create-react-app my__app__name --template typescript

OR

yarn create react-app my__app__name --template typescript
```







Before we get started, "Tailwind CSS requires Node.js 12.13.0 or higher" (tailwindcss). Make sure you have Node.js installed and the correct version by running `node --version` in your command line.



使用tailwind CSS: 进入项目目录，

```shell
yarn add tailwindcss -D
```





After installation process is done, we need to create Tailwind CSS configuration file. To do so, we need to run the following command:

```
npx tailwind init
```

This will initialise Tailwind with a new configuration file in the root of your project.

# Vue

## vue-cli 安装

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

## vue3安装

```bash
npm install vue@next
```



查看vue版本：

```
npm list vue
```

# Tailwind

```
yarn add tailwindcss -D
```

