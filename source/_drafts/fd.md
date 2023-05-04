---
title: fd
tags:
---



https://github.com/sharkdp/fd

<!--more-->

`fd` is a program to find entries in your filesystem. It is a simple, fast and user-friendly alternative to [`find`](https://www.gnu.org/software/findutils/). While it does not aim to support all of `find`'s powerful functionality, it provides sensible (opinionated) defaults for a majority of use cases.



## How to use

First, to get an overview of all available command line options, you can either run [`fd -h`](https://github.com/sharkdp/fd#command-line-options) for a concise help message or `fd --help` for a more detailed version.

### Simple search

*fd* is designed to find entries in your filesystem. The most basic search you can perform is to run *fd* with a single argument: the search pattern. For example, assume that you want to find an old script of yours (the name included `netflix`):

```
> fd netfl
Software/python/imdb-ratings/netflix-details.py
```

If called with just a single argument like this, *fd* searches the current directory recursively for any entries that *contain* the pattern `netfl`.

### Regular expression search

The search pattern is treated as a regular expression. Here, we search for entries that start with `x` and end with `rc`:

```
> cd /etc
> fd '^x.*rc$'
X11/xinit/xinitrc
X11/xinit/xserverrc
```

The regular expression syntax used by `fd` is [documented here](https://docs.rs/regex/1.0.0/regex/#syntax).

### Specifying the root directory

If we want to search a specific directory, it can be given as a second argument to *fd*:

```
> fd passwd /etc
/etc/default/passwd
/etc/pam.d/passwd
/etc/passwd
```

### List all files, recursively

*fd* can be called with no arguments. This is very useful to get a quick overview of all entries in the current directory, recursively (similar to `ls -R`):

```
> cd fd/tests
> fd
testenv
testenv/mod.rs
tests.rs
```

If you want to use this functionality to list all files in a given directory, you have to use a catch-all pattern such as `.` or `^`:

```
> fd . fd/tests/
testenv
testenv/mod.rs
tests.rs
```

### Searching for a particular file extension

Often, we are interested in all files of a particular type. This can be done with the `-e` (or `--extension`) option. Here, we search for all Markdown files in the fd repository:

```
> cd fd
> fd -e md
CONTRIBUTING.md
README.md
```

The `-e` option can be used in combination with a search pattern:

```
> fd -e rs mod
src/fshelper/mod.rs
src/lscolors/mod.rs
tests/testenv/mod.rs
```

### Searching for a particular file name

To find files with exactly the provided search pattern, use the `-g` (or `--glob`) option:

```
> fd -g libc.so /usr
/usr/lib32/libc.so
/usr/lib/libc.so
```

### Hidden and ignored files

By default, *fd* does not search hidden directories and does not show hidden files in the search results. To disable this behavior, we can use the `-H` (or `--hidden`) option:

```
> fd pre-commit
> fd -H pre-commit
.git/hooks/pre-commit.sample
```

If we work in a directory that is a Git repository (or includes Git repositories), *fd* does not search folders (and does not show files) that match one of the `.gitignore` patterns. To disable this behavior, we can use the `-I` (or `--no-ignore`) option:

```
> fd num_cpu
> fd -I num_cpu
target/debug/deps/libnum_cpus-f5ce7ef99006aa05.rlib
```

To really search *all* files and directories, simply combine the hidden and ignore features to show everything (`-HI`).

### Matching the full path

By default, *fd* only matches the filename of each file. However, using the `--full-path` or `-p` option, you can match against the full path.

```
> fd -p -g '**/.git/config'
> fd -p '.*/lesson-\d+/[a-z]+.(jpg|png)'
```
