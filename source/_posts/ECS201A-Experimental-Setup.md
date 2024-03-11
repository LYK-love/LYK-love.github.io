---
title: ECS201A Experimental Setup
tags: Computer Architecture
categories: Computer Science
date: 2024-01-11 21:59:13
---


Sources:

1. [ECS201A Homepage](https://jlpteaching.github.io/comparch/)
2. [ECS201A Projects(gem5)](https://jlpteaching.github.io/comparch/modules/gem5/assignment0/)

All the experiments rely on the same python env and a software called `gem5`.  

The professor has offered us github codespaces, such as **[classroom assignment-0](https://classroom.github.com/a/Ru771Yj_)**,  to develop,upon which you don't need to worry about the setup. So it's strongly recommended to develop with github codespaces.

However, if you prefer to develop on your local machine, to set up for the experiments you must:

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
   scons build/{ISA}/gem5.{variant} -j {cpus}
   ```

   For instance, if your target ISA is `X86` and you want to leverage your 4-core CPU to compile, the command is:

   ```sh
   scons build/X86/gem5.opt -j 4
   ```

   If the target ISA is `RISCV`, then the command is `scons build/RISCV/gem5.opt -j 4`.

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

4. Now you can call gem5 with: `<path of gym5 repo>/build/{ISA}/gem5.{variant}`. For convience, you can add gem5 to your systems `PATH`:

   ```sh
   # In your `~/.zshrc` or `~/.bashrc`
   # Path to built gem5:
   # Syntax: "<path to gym>/build/{ISA}/gem5.{variant}". Note: Change the path according your need. E.g., for RISCV ISA as your target, the command is 
   # "$GEM5_HOME/build/RISCV/gem5.opt"
   
   export GEM5_HOME="$HOME/gem5"
   alias gem5="$GEM5_HOME/build/X86/gem5.opt"
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

3. One problem is that, in the code, many scripts rely on `gem5` python package, e.g., in `components/boards.py`:

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

# Commands

By default `gem5` outputs to standard out `stdout` and standard error `stderr` . To dump these info to a file, you can:

```sh
gem5 -r run.py
```

This is what you will see in your terminal after running the command above.

```
Redirecting stdout and stderr to m5out/simout
```

Now, if you look at `m5out`, you will see that there is a new file name `simout`. Let’s print the content of that file and compare to our previous output in [Invoking gem5](https://jlpteaching.github.io/comparch/modules/gem5/assignment0/#invoking-gem5). To do that, run the following command in your terminal.

You separate `stdout` and `stderr` into two files. 

```sh
gem5 -re run.py
```

After running the command above, this is what you will see in your terminal.

```
Redirecting stdout to m5out/simout
Redirecting stderr to m5out/simerr
```



Redirecting output: `--outdir=<outpout_folder>`

# Appendix

* [Syllabus](https://jlpteaching.github.io/comparch/syllabus/#tests)
* [Past lecture videos](https://video.ucdavis.edu/playlist/details/1_r742jxna)
