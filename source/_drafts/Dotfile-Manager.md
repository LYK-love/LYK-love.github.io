---
title: Dotfile Manager
tags:
---



# yadm

[yadm](https://yadm.io/docs/overview)

Install:

```bash
sudo apt-get update
sudo apt-get install yadm
```

# Usage

### If you have an existing remote repository

Clone your existing repo using yadm.

```
yadm clone <url>
yadm status
```

The `clone` command will attempt to check out all files that exist in the repository. I

Now most Git commands can be used as `yadm <git command>`. Read about [common commands](https://yadm.io/docs/common_commands) for ideas.



Print  a list of files managed by yadm.  The -a option will cause all managed files to be listed.  Otherwise, the list will only include files from the current directory or below.

```
yadm list -a
```



```
```

