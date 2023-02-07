---
title: Github
categories: Toolkit
date: 2022-09-28 18:17:23
tags:
---


* Import Repository
* Transfer

<!--more-->

# Import Repository

Side of profile picture you will find `+` button click on that then there will be option to `import repository`. 

our old repository’s clone URL is required which is gitlab repo url in your case. then select Owner and then type name for this repo and click to begin import button.

# Transfer

可以把个人仓库转给别人或者组织.

在仓库的Settings主页的最末尾的Transfer ownership.

# Organization

Within in a **Organization**, each **Repository** defines its restrictions by **Permission** associated to **Team/s** and Collaborator/s.

- There are 2 [Roles](https://help.github.com/articles/managing-people-s-access-to-your-organization-with-roles/) within a GitHub Organization: `Owner` or `Member`.
- A GitHub user becomes a Member by "joining" an Organization (by default). **Note**: An invitation from an Owner is needed before hand.
- Members within an GitHub Organization can be distributed in [Teams](https://help.github.com/articles/organizing-members-into-teams/). A member can join one or more teams.
- Collaborators (members or external user from the organization) and teams can be defined for each repository. For each of them should be assigned a [Permission Level](https://help.github.com/articles/permission-levels-for-an-organization/)

As a summary: [Repository permission levels for an organization](https://help.github.com/articles/repository-permission-levels-for-an-organization/).

## 成员权限

member默认只有read权限, 可以更改配置, 使其拥有push权限:

1. settings --> Member privileges --> Base permissions --> 选择Write
