---
title: Linux Users and Groups
tags:
  - Linux
categories:
  - Software Engineering
date: 2023-12-29 05:12:30
---


Source:

* [A complete guide to Manage Users and Groups on Linux!](https://blog.learncodeonline.in/a-complete-guide-to-manage-users-and-groups-on-linux)
* 蔡德明. *[第十四章 Linux账号管理与权限配置. 鸟哥的Linux私房菜](http://cn.linux.vbird.org/linux_basic/0410accountmanager_1.php)*.

<!--more-->

# Linux Users

* Linux user is an account or an entity which provides interactive access  to the system and allows to create or modify files and to perform  several other operations. 

# Types of Linux 

There are two types of users which exists on a typical Linux operating system.

* Administrater: Any user with `UID=0` becomes an administrater. By default, only the `root` account is an administrater. You can set other admiistraters by just setting `UID=0`, but it's highly unrecommended.

* A system user account aka privileged account is created by the  operating system during its installation and that is used for operating  system defined purposes. UID: `100-999`.

  * We can see some sys accounts in `/etc/passwd`:

    ```text
    daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
    bin:x:2:2:bin:/bin:/usr/sbin/nologin
    sys:x:3:3:sys:/dev:/usr/sbin/nologin
    ```

    Their UID is in `1-99`, which is unusual. In fact, this is due to the backward compability. In normal, sys accounts are in `100-999`.

* A regular user account: UID: `1000-6000`

```text
# /etc/login.defs
# ...
# Min/max values for automatic uid selection in useradd
#
UID_MIN                  1000
UID_MAX                 60000
# System accounts
#SYS_UID_MIN              100
#SYS_UID_MAX              999

#
# Min/max values for automatic gid selection in groupadd
#
GID_MIN                  1000
GID_MAX                 60000
# ...
```

* To make the IDs assigned to new users by default start at any range of  your choice for e.g. 5,000, change the `UID_MIN` and `GID_MIN` directives in the /etc/login.defs file:

## System user

The regular user accounts has ids from 100 to 999.

```bash
cat /etc/login.defs  | grep -i SYS_UID_MIN
cat /etc/login.defs  | grep -i SYS_UID_MAX
cat /etc/login.defs  | grep -i SYS_GID_MIN
cat /etc/login.defs  | grep -i SYS_GID_MAX
```



## Regular user

The regular user accounts has ids begin from 1000 onwards.

```bash
cat /etc/login.defs  | grep -i UID_MIN | grep -v -E '^\#'
cat /etc/login.defs  | grep -i UID_MAX | grep -v -E '^\#'
cat /etc/login.defs  | grep -i GID_MIN | grep -v -E '^\#'
cat /etc/login.defs  | grep -i GID_MAX | grep -v -E '^\#'
```

# How users and groups database is maintained

On Linux Operating system there are primarily four files placed under `/etc` directory which manages records about `users` and `groups`.

* `/etc/passwd` -> The file containing basic information about users.
* `/etc/shadow` -> The file containing encrypted passwords.
* `/etc/group` -> The file containing basic information about groups and which users belong to them.
* `/etc/gshadow` -> The containing encrypted group passwords.

The password (`/etc/passwd`) and group (`/etc/group`) files doesn't contain password information for security reasons and they are plain text, but the other two files are encrypted text.

The format of files for groups (`/etc/group` and `/etc/gshadow`) are quite similar to that of the files for users (`/etc/passwd` and `/etc/shadow`).

## `/etc/passwd` 

[Source: Understanding the `/etc/passwd` File](https://linuxize.com/post/etc-passwd-file/)

View this file:

```shell
cat /etc/passwd
```



```
mark:x:1001:1001:mark,,,:/home/mark:/bin/bash
[--] - [--] [--] [-----] [--------] [--------]
|    |   |    |     |         |        |
|    |   |    |     |         |        +-> 7. Login shell
|    |   |    |     |         +----------> 6. Home directory
|    |   |    |     +--------------------> 5. GECOS
|    |   |    +--------------------------> 4. GID
|    |   +-------------------------------> 3. UID
|    +-----------------------------------> 2. Password
+----------------------------------------> 1. Username

```

The **syntax** is:

```text
username:password:UID:GID:name:home directory:shell
```



Explanation:

1. Username. the username given a the time of creation

2. Password. Usually, we’ll see an `x` character there. It means the password is encrypted.

3. UID. The user identifier is a number assigned to each user. It is used by the operating system to refer to a user.

4. GID. The user’s group identifier number, referring to the user’s primary group. When a user [creates a file](https://linuxize.com/post/create-a-file-in-linux/) , the file’s group is set to this group. Typically, the name of the group is the same as the name of the user. User’s [secondary groups](https://linuxize.com/post/how-to-add-user-to-group-in-linux/) are listed in the `/etc/groups` file.

5. GECOS or the full name of the user. It's optional and not important. You can write anything to it.

6. Home directory. User’s home directory.

7. Login shell. User’s default shell. Note:  `/sbin/nologin` or `/bin/false` indicates [logging in is disabled](https://www.baeldung.com/linux/disable-user-logins) for the user.

   * To view valid login shell please run the following command

     ```shell
     cat /etc/shells
     ```

     

## `/etc/shadow`

[Source: Understanding the `/etc/shadow` File](https://linuxize.com/post/etc-shadow-file/)



View this file:

```shell
sudo cat /etc/shadow
```



Output:

```txt
mark:$6$.n.:17736:0:99999:7:::
[--] [----] [---] - [---] ----
|      |      |   |   |   |||+-----------> 9. Unused
|      |      |   |   |   ||+------------> 8. Expiration date
|      |      |   |   |   |+-------------> 7. Inactivity period
|      |      |   |   |   +--------------> 6. Warning period
|      |      |   |   +------------------> 5. Maximum password age
|      |      |   +----------------------> 4. Minimum password age
|      |      +--------------------------> 3. Last password change
|      +---------------------------------> 2. Encrypted Password
+----------------------------------------> 1. Username
```

Explanation:

1. Username. The string you type when you log into the system. The user account that exist on the system.

2. Encrypted Password. The password is using the `$type$salt$hashed` format. `$type` is the method cryptographic hash algorithm and can have the following values:

   - `$1$` – MD5
   - `$2a$` – Blowfish
   - `$2y$` – Eksblowfish
   - `$5$` – SHA-256
   - `$6$` – SHA-512

   If the password field contains an asterisk (`*`) or exclamation point (`!`), the user will not be able to login to the system using password authentication. Other login methods like [key-based authentication](https://linuxize.com/post/how-to-setup-passwordless-ssh-login/) or [switching to the user](https://linuxize.com/post/su-command-in-linux/) are still allowed.

   In older Linux systems, the user’s encrypted password was stored in the `/etc/passwd` file.

3. Last password change. This is the date when the password was last changed.  The number of days is counted since January 1, 1970 (epoch date).

4. Minimum password age. The number of days that must pass before the user  password can be changed. Typically it is set to zero, which means that  there is no minimum password age.

5. Maximum password age. The number of days after the user password must be changed. By default, this number is set to `99999`.

6. Warning period. The number of days before the password expires during which the user is warned that the password must be changed.

7. Inactivity period. The number of days after the user password expires before the  user account is disabled. Typically this field is empty.

8. Expiration date. The date when the account was disabled. It is represented as an epoch date.

9. Unused. This field is ignored. It is reserved for future use.

### Example Entry

Let’s take a look at the following example:

```txt
linuxize:$6$zHvrJMa5Y690smbQ$z5zdL...:18009:0:120:7:14::
```

The entry above contains information about the user “linuxize” password:

- The password is encrypted with SHA-512 (the password is truncated for better readability).
- The password was last changed on April 23, 2019 - `18009`.
- There is no minimum password age.
- The password must be changed at least every 120 days.
- The user will receive a warning message seven days before the password expiration date.
- If the user doesn’t attempt to login to the system 14 days after the password is expired, the account will be disabled.
- There is no account expiration date.

# `id` and `groups` command

Another way to check groups information of a Linux user using `id` and `groups` command.

```bash
id sample

id user1

groups sample

groups user1
```



# User Management

## Create a Linux User

**Method 1: Using `useradd` command** ->

```bash
useradd <user1>
```

**Method 2: Using `adduser` command** ->

`adduser` is a Perl script which uses `useradd` (which is native to Linux) binary in back-end. It's more interactive and user friendly than it's back-end `useradd`. 

```bash
adduser <user2>
```

**Method 3: By directly modifying `/etc/passwd` file** ->

Not a recommended way but one can create a Linux user by directly modifying `/etc/passwd` file and making an entry for new user. In such cases you need to create the `group`, `home directory` etc. individually for that user.

```bash
cat /etc/passwd | tail -1
```

## Assign Password to a Linux user

Using `passwd` command we can assign passwords to Linux user.

## Assign Password to a Linux user

Using `passwd` command we can assign passwords to Linux user.

```bash
passwd <user3>
```

## Delete a Linux user

Using `userdel` command you can delete a user from Linux operating system.

```bash
userdel -r user2
```

### Modifying an Existing user's properties

`usermod` command is used to modify an existing user's properties.



**Update the `comment` part ->**

```bash
usermod -c "This is Sample user" sample
```



**Change User Home Directory ->**

```bash
usermod -d /var/www/ sample
```



**Lock and unlock the user account ->**

Use ‘-L‘ (lock) option with `usermod` command to lock the user account and to `unlock` use `-U` option.

Once locked user can’t login by using the password and you will see a `!` added before the encrypted password in `/etc/shadow` file, means password is disabled.

```bash
usermod -L sample

usermod -U sample
```

# Group Management

There are two types of groups in Linux.

* primary group: when you create a user the primary group that  the user belongs to also gets created with the same name as the user.  User must be a member of a primary group and there can be only one  primary group for each member.
* secondary group: It's always optional. If  you have a requirement create it and add the users to it. A user can be  mart of one or more secondary groups.

### Create a Linux group

Use `groupadd` command to create a Linux group.

```bash
groupadd secondgroup
```

### Add users to a Linux group

We can add users to become part of any other groups.

```bash
usermod -G secondgroup sample

usermod -G secondgroup user1
```

### Change Name of a Linux group

Run following command to change name of a Linux group.

```bash
groupmod -n secondarygroup secondgroup
```

### Change GID of a Linux group

Run following command to change name of a Linux group.

```bash
groupmod -g 1007 secondarygroup
```

The syntax is -> `groupmod -g newgid groupname`

### Remove a User from a Linux group

Run the following commands to remove a user from a Linux group.

```bash
gpasswd -d user1 lcousersecondary1

gpasswd -d user4 lcousersecondary1
```

### Delete or Remove a Linux group

Run following command to delete a Linux group.

```bash
groupdel secondarygroup
```

# Example: Create a user

Here we will use multiple `useradd` command options to create the user.

Our requirement is as follows:

1. Full name is `LearnCodeOnline` 
2. username is` lcouser` 
3. Primary group is `lcouserprimary` 
4. Secondary groups are `lcousersecondary1` and `lcousersecondary2` 
5. Default shell is `/bin/tcsh`

Run the following commands to achieve this.

```shell
groupadd lcouserprimary

groupadd lcousersecondary1

groupadd lcousersecondary2

useradd -c "LearnCodeOnline" -g lcouserprimary -G lcousersecondary1,lcousersecondary2 -s /bin/tcsh lcouser
```

