---
title: gitignore
tags: git
categories: Software Engineering
date: 2023-12-25 01:19:39
---


Sources: 

* [Github: Ignoring files](https://docs.github.com/en/get-started/getting-started-with-git/ignoring-files)

<!--more-->

# Examples

### Exclude Specific Files:

```
gitignore
# Ignore a single file
secrets.txt

# Ignore all .log files
*.log
```

### Exclude Specific Directories:

```
gitignore
# Ignore an entire directory
node_modules/

# Ignore all directories named 'temp'
temp/
```

### Exclude All Files In a Directory:

```
gitignore
# Ignore all files in the bin directory
bin/*

# Ignore all files in all directories named build
build/*
```

### Include Specific Files or Directories:

The `!` operator can be used to negate the ignore pattern and include specific files or directories.

```
gitignore
# Ignore everything in the logs directory
logs/*

# But include the .keep file
!logs/.keep
```

### Using Wildcards and Patterns:

```
gitignore
# Ignore all .txt files in the doc/ directory
doc/*.txt

# Ignore all .pdf files in the root directory (but not in subdirectories)
/*.pdf

# Ignore all .tar.gz files in any directory
*.tar.gz

# Ignore files with a number as the filename
*[0-9]*
```

### Comments:

```
gitignore
# This is a comment - it will be ignored by Git
```

### Exclude Folders with Specific Names Anywhere in the Repository:

```
gitignore
# Ignore any folder named build wherever it is in the project
**/build/
```

### Exclude Files with Specific Names Anywhere in the Repository:

```
gitignore
# Ignore any file named TODO wherever it is in the project
**/TODO
```

### Practical Examples:

```
gitignore
# Ignore Mac system files
.DS_Store

# Ignore node_modules in any JavaScript project
node_modules/

# Ignore the build output directory
/dist

# Ignore log files
*.log

# Ignore all .env files
.env*

# Include .env.example file
!.env.example

# Ignore compiled Python files
*.pyc

# Ignore the database file in a Django project
*.sqlite3
```

Remember, the patterns in a `.gitignore` file are relative to the location of the `.gitignore` file itself. Typically, you'd place this file in the root directory of your repository so it applies to the entire repo. After editing the `.gitignore` file, you need to commit it to your repository for the changes to take effect.

# `/dir`

when you put a slash `/` at the beginning of a pattern, it anchors the pattern to the root of the repository. This means that it will only match files or directories in the specified location relative to the repository root, not anywhere else in the project.

Here's what happens with different usages:

### `/bin/`

- **Pattern:** `/bin/`
- **Meaning:** This pattern will ignore the `bin` directory at the root of the repository. It will not ignore `bin` directories located in any subdirectories deeper in the project structure.
- 
