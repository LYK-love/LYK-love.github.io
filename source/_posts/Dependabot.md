---
categories:
- Software Engineering
date: 2022-06-26 16:56:12
tags: null
title: Dependabot
---

Outline：

* Intro
* Dependabot alerts
* Dependabot security updates
* Dependabot version updates

<!--more-->

# Intro



Dependabot是Github的依赖管理工具, 它具有如下功能:

* Dependabot alerts: dependabot会检测vulnerable dependencies，在以下情况下，会触发`dependabot alert`:
  * 当GitHub Advisory Database中收录了一个新的vulnerable dependency
  * repo的依赖图发生了改变，比如新添加了某个依赖，或者用户改变了某个依赖的版本
    * 这里的版本指：“语义版本”([semver](https://semver.org/))



* Dependabot updates: 

  * Dependabot security updates: 在一个`dependabot alert`产生时，自动触发一次update

  * Dependabot version updates:  当用户依赖的上游有更新时update

    * 通过depenency graph来得到用户依赖和上游依赖
    * 用户需要编写依赖配置文件`dependabot.yml`， 来**说明如何更新依赖**

    * 这确保了用户依赖始终是updated的



# Dependabot alerts

在repo页面 -> `Settings` -> `Security`栏的`Code security and analysis` ， 开启 `Dependency graph`和`Dependabot alerts`

*  `Dependency graph`和`Dependabot alerts`对于public repo是默认开启的，只有private repo需要手动开启这两项
*  `Dependency graph`： 根据依赖配置文件，生成依赖图
* `Dependabot alerts`: 自动检测依赖，如果依赖有更新，就会向用户的邮箱发alert，alert中会包含被影响的文件link，以及漏洞修复的版本和信息

# Dependabot security updates

在开启了`Dependency graph`和`Dependabot alerts`的基础上，再开启`Dependabot security updates`

* `security updates`: Dependabot会自动将漏洞修复，并且给repo提PR



# Dependabot version updates

在开启了`Dependency graph`和`Dependabot alerts`的基础上，再开启`Dependabot version updates`, 然后配置**依赖文件**，以指定依赖的更新过程

* `version updates`: 在发现依赖有更新后，会自动创建一个 PR 来更新依赖文件，并说明依赖更新内容，用户自己选择是否 merge该PR



依赖配置文件`dependabot.yml`可以在Github上创建，也可以手动创建：

* 手动创建： 在repo根目录下创建`.github` folder，并且在folder下添加`dependabot.yml`（dependabot的config）

* 用Github创建：在repo页面通过 `Insights` -> `Dependency graph` -> `Dependabot` -> `Enable Dependabot` 路径即可开启，之后就可以点击 `Create config file` 来创建配置文件了

## dependabot.yml

具体见[官方文档](https://docs.github.com/cn/code-security/dependabot/dependabot-version-updates/configuring-dependabot-version-updates)

`version`、`updates`、`package-ecosystem` 、`schedule` 是必填的，还可以配置 `registries` 来指定私有仓库地址及认证信息



example:

```yaml
# Basic dependabot.yml file with
# minimum configuration for two package managers

version: 2
updates:
  # Enable version updates for npm
  - package-ecosystem: "npm"
    # Look for `package.json` and `lock` files in the `root` directory
    directory: "/"
    # Check the npm registry for updates every day (weekdays)
    schedule:
      interval: "daily"

  # Enable version updates for Docker
  - package-ecosystem: "docker"
    # Look for a `Dockerfile` in the `root` directory
    directory: "/"
    # Check for updates once a week
    schedule:
      interval: "weekly"
```