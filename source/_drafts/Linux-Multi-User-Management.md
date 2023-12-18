---
title: Linux Multi-User Management
tags:
---



```
# 创建一个共享目录
sudo mkdir /opt/shared_software

# 安装软件到共享目录
sudo tar -xzf software.tar.gz -C /opt/shared_software

```

# Shared Dir

使用以下命令更改`/Tools`目录的权限：

```
bash
sudo chmod +rx /Tools
```

这会将读取（r）和执行（x）权限添加到目录。读取权限允许用户查看目录中的文件列表，执行权限允许用户进入目录。

如果你希望所有用户都能够在`/Tools`目录中创建、编辑和删除文件，你可能还需要更改目录的所有者和组。假设你的两个用户属于同一用户组，可以使用以下命令：

```
bash
sudo chown -R :<group_name> /Tools
```

请将 `<group_name>` 替换为你希望拥有访问权限的用户组名称。

如果你的两个用户不属于相同的用户组，你可能需要创建一个新的用户组，并将这两个用户添加到该组中，然后将目录的所有者更改为该组。

```
bash
```

1. ```
   # 创建一个新的用户组
   sudo addgroup mygroup
   
   # 将用户添加到新的用户组
   sudo adduser user1 mygroup
   sudo adduser user2 mygroup
   
   # 更改目录的所有者为新的用户组
   sudo chown -R :mygroup /Tools
   ```

这样，所有用户都应该能够访问`/Tools`目录了

# User Group

在Linux系统中，你可以使用以下命令来查看用户组：

1. **查看当前用户所属的用户组：**

   ```
   bash
   ```

```
groups
```

上述命令会显示当前用户属于的所有用户组。

**查看指定用户所属的用户组：**

```
bash
groups username
```

将 `username` 替换为你要查询的实际用户名。这会显示指定用户所属的所有用户组。

**查看所有用户组：**

```
bash
cat /etc/group
```

上述命令会列出系统中所有用户组的信息。你可以查看每个用户组的名称、组ID（GID）、组内的用户等信息。

# chown

`chown` 命令用于改变文件或目录的所有者（owner）和/或所属用户组（group）。`-R` 选项是递归操作，表示对目录及其下属所有文件和子目录进行相同的所有者和组的更改。

具体而言，`chown -R` 的语法如下：

```
bash
sudo chown -R new_owner:new_group path
```

- `new_owner` 是新的所有者的用户名或用户ID。
- `new_group` 是新的用户组的组名或组ID。
- `path` 是要更改所有者和组的文件或目录路径。

使用 `-R` 选项时，`chown` 会递归地更改指定目录及其下的所有文件和子目录的所有者和组。这对于批量更改文件或目录的所有者和组非常有用。

例如，假设你有一个目录 `/mydirectory`，并且你希望将其所有者更改为 `user1`，组更改为 `group1`，可以使用以下命令：

```
bash
sudo chown -R user1:group1 /mydirectory
```

这将递归地更改 `/mydirectory` 及其下的所有文件和子目录的所有者为 `user1`，组为 `group1`

