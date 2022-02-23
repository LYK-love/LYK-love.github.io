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



commandS：

- `nvm uninstall <version>` ：卸载指定版本node
- `nvm use <version>` ：使用指定版本node
- `nvm ls`: ：显示已安装的node版本列表

## npx

node版本管理工具npx, 教程： https://www.ruanyifeng.com/blog/2019/02/npx.html

node自带npx

简单来说，npx可以指定使用某个版本的node，让该版本的node来执行命令。 避免了项目构建中需要降低node版本的尴尬情况

> ```bash
> npx node@0.12.8 [command]
> 
> ```

上面命令会使用 0.12.8 版本的 Node 执行脚本。原理是从 npm **下载这个版本的 node，使用后再删掉**。

`-p`： 在安装指定版本的node后，不删除该node



npx可以替代很多npm版本管理工具，比如`nvm`



