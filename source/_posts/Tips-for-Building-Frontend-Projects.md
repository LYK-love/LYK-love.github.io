---
title: Tips for Building Frontend Projects
categories:
- Software Engineering
tags: Javascript
date: 2022-07-30 17:23:43
---

Outline:

* nodejs
* npm
* nvm
* yarn
* ...

<!--more-->

# nodejs

For the installation of nodejs, npm and nvm, please refer to [my Javascript tools doc](https://lyk-love.cn/2024/01/09/javascript-tools/).

Two popular package managers for nodejs are [npm](https://docs.npmjs.com/about-npm) and [yarn](https://yarnpkg.com/getting-started/install). Basically, yarn is faster than npm, so it's recommended to use yarn.

Some basic concepts:

* `nodejs`: 是JS的一个运行时库, 用于在native环境下运行JS.
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
* 对于`npm > 5.0`，`npm install [package]`已经可以自动将依赖信息写入`package.json`了

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

* `package.json`中记录的依赖有三种

* `npm install`默认会下载pro和dev的依赖.
  * 参见[dev](https://docs.npmjs.com/cli/v8/configuring-npm/package-json#devdependencies): *These things will be installed when doing `npm link` or `npm install` from the root of a package*

  

#### pro

* production dependencies: **是依赖的默认种类**.在项目开发和运行阶段都需要的依赖。

  * 在添加依赖时( 使用`npm install [包名]`/ `yarn add [包名]` )，如果不手动指定，则都添加为producrtion dependencies
  * 被记录在`package.json`的`dependencies`属性

#### dev

* dev dependencies: 只在开发过程中需要，而运行时不需要的依赖

  * 比如 Babel, Flow 和`"@vue/cli-service": "xx"`）
  * 被记录在`package.json`的`devDependencies`属性

  * 除非是想要把包发布在npm上, 否则pro和dev没什么区别, 都会被`npm install`下载.

#### peer

* peer dependencies: 在发布包的时候需要的依赖。有这种依赖意味着安装包的用户也需要和包同样的依赖。 这对于像 react 这样也被人安装的、需要单一 react-dom 副本的包很有用

  * 用于安装可能与使用者冲突的包

    > 我们组件的包需要react，使用者的项目也需要react，两个react的版本可能不一致，这个时候可以使用`peer-dependencies`来安装我们的react，避免与使用者冲突。

  * 被记录在`peerDependencies` 属性

* 可以用`export NODE_ENV=production`来制定默认依赖环境

## Env

可以通过环境变量来指定下载的依赖类型:

```
export NODE_ENV = production
```

https://juejin.cn/post/6844903681192804359

https://cli.vuejs.org/zh/guide/mode-and-env.html#%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F





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

* vue是构建用户界面的渐进式JavaScript 框架

* vue-cli是vue的一个官方脚手架工具（快速工程化命令工具）, 用来帮助程序员们快速搭建基于vue框架的开发环境。
  * vue有很多脚手架工具，vue-cli只是其中一种，侧重于单页面应用 (SPA) 的快速搭建，网址：cli.vuejs.org/zh/guide/
  * Vue-cli = Vue + 一堆的js插件
  * vue-cli 4.5以下, 对应的是Vue2
  * vue-cli 4.5及以上, 对应的是Vue3

* @vue/cli是新版vue-cli，提供了GUI维护界面，@vue/cli 安装的是vue3及以上版本, vue-cli 安装的是vue2
* 命令行的`vue`命令其实是对应`vue-cli`这个程序, 而不是`vue`






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



查看vue-cli 版本

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