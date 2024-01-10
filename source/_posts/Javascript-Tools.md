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

First, you should install and enable nvm:

1. Install nvm. You can visit [the project’s GitHub page](https://github.com/nvm-sh/nvm) and copy the `curl` command from the README file that displays on the main page. This will  get you the most recent version of the installation script.

   ```sh
   curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
   ```

   Running either of the above commands downloads a script and runs it. The script clones the nvm repository to `~/.nvm`, and attempts to add the source lines from the snippet below to the correct profile file (`~/.bash_profile`, `~/.zshrc`, `~/.profile`, or `~/.bashrc`).

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

4. Now Now, you can ask NVM which versions of Node are available:

   ```sh
   nvm list-remote
   ```

5. You can install a version of Node by writing  in any of the release versions listed. For instance, to get version  v14.10.0, you can run:

   ```bash
   nvm install v14.10.0
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

