---
title: ECS201A Experimental Setup
tags: Computer Architecture
categories: Computer Science
date: 2024-01-11 21:59:13
---


Source:

1. [ECS201A Homepage](https://jlpteaching.github.io/comparch/)
2. [ECS201A Projects(gem5)](https://jlpteaching.github.io/comparch/modules/gem5/assignment0/)

All the experiments rely on the same python env and a software called `gem5`. To set up for the experiments, you must:

1. Install and config gem5 on your system.
2. Clone the assignment repo and config it.

<!--more-->

# Steps

## Install gem5

[--> Building gem5 on Ubuntu](https://www.gem5.org/documentation/general_docs/building)

It's highly recommended to use Ubuntu20.04 or 22.04.

1. Install all dependencies (For Ubuntu 20.04):

   ```sh
   sudo apt install build-essential git m4 scons zlib1g zlib1g-dev \
       libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev \
       python3-dev python-is-python3 libboost-all-dev pkg-config
   ```

2. Getting the code:

   ```sh
   git clone https://github.com/gem5/gem5
   cd gem
   ```

3. Make sure your **system python version** is larger than 3.6. In the  root of the gem5 directory, run:

   ```sh
   scons build/X86/gem5.opt -j 4
   ```

   Wait for a long time until the compilation ends.

   Note: you must **use your system's python interpreter instead of conda**. (-->[Source](https://github.com/gem5/gem5#building-gem5)). If not, you'll have a linking error looks like:

   ```
   $ scons build/X86/gem5.opt -j 4
   scons: Reading SConscript files ...
   Mkdir("/home/lykuni_ucdavis_edu/gem5/build/X86/gem5.build")
   Checking for linker -Wl,--as-needed support... yes
   Checking for compiler -gz support... yes
   Checking for linker -gz support... yes
   Info: Using Python config: python3-config
   Checking for C header file Python.h... yes
   build/X86/gem5.build/scons_config/conftest_5: error while loading shared libraries: libpython3.9.so.1.0: cannot open shared object file: No such file or directory
   Checking Python version... no
   Error: Can't find a working Python installation
   ```

4. Add gem5 to your systems `PATH`:

   ```
   # In your `~/.zshrc` or `~/.bashrc`
   
   ```

## Config your project

1. Clone your project together with the submodule `gem5`. Take my assignment0 project as example:

   ```sh
   git clone --recurse-submodules git@github.com:ECS201A-WQ24/ecs201a-assignment0-LYK-love.git
   cd ecs201a-assignment0-LYK-love
   ```

   * The `--recurse-submodules` is to clone the gem5 repo as a submodule. Otherwise you'll get a blank  `gem5` dir under the project root.

   One problem is that in the code, many scripts rely on `gem5` python package, whereas this package 

2. Install all dependencies:

   ```sh
   pip install -r requirements.txt
   ```

3. One problem is that in the code, many scripts rely on `gem5` python package, e.g., in `components/boards.py`:

   ```python
   from gem5.simulate.simulator import Simulator
   ```

   whereas this package lies in `<project>/gem5/src/python`. In order to let PyCharm be able to search (and import) this package, we must mark  `<project>/gem5/src/python` as "Source Root":

   ![ECS201A Figure_1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/ECS201A%20Experimental%20Setup/ECS201A%20Figure_1.png)

4. After that, all the imports of gem package is successful:

   ![ECS201A Figure_2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/ECS201A%20Experimental%20Setup/ECS201A%20Figure_2.png)

### In detail

The building command of gem5 is 

```
scons build/{ISA}/gem5.{variant} -j {cpus}
```

where `{ISA}` is the target (guest) Instruction Set Architecture, and `{variant}` specifies the compilation settings. For most intents and purposes `opt` is a good target for compilation. The `-j` flag is optional and allows for parallelization of compilation with `{cpus}` specifying the number of threads. A single-threaded compilation from scratch can take up to 2 hours on some systems. We therefore strongly advise allocating more threads if possible.
