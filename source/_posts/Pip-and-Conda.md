---
title: Pip and Conda
tags: Python
categories:
  - Software Engineering
date: 2023-12-24 22:16:11
---


Source:

* [miniconda](https://docs.conda.io/projects/miniconda/en/latest/index.html#miniconda)

<!--more-->

# Conda

推荐`miniconda`.

## Install

[->Install](https://docs.conda.io/projects/miniconda/en/latest/index.html#quick-command-line-install).

For Linux:

These four commands quickly and quietly install the latest 64-bit  version of the installer and then clean up after themselves. To install a different version or architecture of Miniconda for Linux, change the  name of the `.sh` installer in the `wget` command.

```
mkdir -p ~/miniconda3
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm -rf ~/miniconda3/miniconda.sh
```

After installing, initialize your newly-installed Miniconda. The following commands initialize for bash and zsh shells:

```
~/miniconda3/bin/conda init bash
~/miniconda3/bin/conda init zsh
```

​        

## Install in China

If you're in China, you need to download conda from a mirror. Take the example from NJU Mirror:

```shell
wget https://mirror.nju.edu.cn/anaconda/miniconda/Miniconda3-py39_23.1.0-1-Linux-aarch64.sh
```



然后安装：

```shell
bash /path/to/miniconda
```



After installing, initialize your newly-installed Miniconda. The following commands initialize for bash and zsh shells:

```
~/miniconda3/bin/conda init bash
~/miniconda3/bin/conda init zsh        
```

## Switch source

If you're in China, you need to switch your conda source to a mirror.  Take the example from NJU Mirror, [具体指导](https://mirrors.nju.edu.cn/help/anaconda).(其实nju源就是从[tuna](https://mirrors.tuna.tsinghua.edu.cn/help/anaconda/)搬运的, 直接用tuna也可以)

1. 先执行 `conda config --set show_channel_urls yes` 生成用户目录下的 `.condarc` 文件( 即`~/.condarc`)

2. 编辑该文件：

   ```yaml
   channels:
     - defaults
   show_channel_urls: true
   default_channels:
     - https://mirror.nju.edu.cn/anaconda/pkgs/main
     - https://mirror.nju.edu.cn/anaconda/pkgs/r
     - https://mirror.nju.edu.cn/anaconda/pkgs/msys2
     - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
     - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
     - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2
   
   
   custom_channels:
     conda-forge: https://mirror.nju.edu.cn/anaconda/cloud
     msys2: https://mirror.nju.edu.cn/anaconda/cloud
     bioconda: https://mirror.nju.edu.cn/anaconda/cloud
     menpo: https://mirror.nju.edu.cn/anaconda/cloud
     pytorch: https://mirror.nju.edu.cn/anaconda/cloud
     simpleitk: https://mirror.nju.edu.cn/anaconda/cloud
   ```

   即可添加 Anaconda Python 免费仓库。

3. 运行 `conda clean -i` 清除索引缓存，保证用的是镜像站提供的索引。

4. 运行 `conda create -n myenv numpy` 测试一下吧

## Commands

Display Conda environment information:

```
conda info
```



list all existing  environments.

```
conda env list
```



指定channel:

```sh
conda install -c <channel> <library>
```



Create a new environment

```
conda create --name [project-env] python=3.7
```

<u>The environments created by Anaconda is always located in `~/anaconda3/envs/`( 对于Miniconda: `~/miniconda3/envs/`)

* 注意， 不要写成`python==3.7`. conda和pip不同. conda安装依赖只需要一个等号.

<u> You may change the default location by using the following command but it is not encouraged.</u> Conda can no longer find your environment by your environment name, you will have to specify the environment’s full path to activate it every time.

```
conda create --prefix /path/project-env
```



Activate your new environment:

```
conda activate project-env
```



 display all packages in this environment:

```
conda list
```



`conda list` also supports revision history.:

```
conda list --revision
```



remove the environment:

```
conda env remove --name [project-env]
```

# pip

pip是python的一个包管理工具，python2:使用`pip`, python3使用`pip3`

* ( Python3下使用`pip` 默认用的是`pip3` )

## Install

```shell
yay -S pip3
```



mac用户：`brew intall pip3`相当卡， 因此要用：

```
curl bootstrap.pypa.io/get-pip.py | python3
```



检查安装是否成功：

```shell
pip3 --version
```



## Switch source

在 pip 命令中使用 **-i** 参数来指定镜像地址

```
pip3 install numpy -i https://mirrors.aliyun.com/pypi/simple/
```



如果需要配置全局的镜像地址，需要修改配置文件:

Linux/Mac os 环境中，配置文件在 ~/.pip/pip.conf（如不存在创建该目录和文件）：

```text
mkdir ~/.pip
```

打开配置文件 **~/.pip/pip.conf**，修改如下：

```text
[global]
index-url = https://mirrors.aliyun.com/pypi/simple/
[install]
trusted-host = https://mirrors.aliyun.com
```



查看镜像地址：

```python
pip3 config list  
```

## Commands

### from a git repository

pip install a [package](https://lyk-love.cn/2022/08/24/python-module/) from a git repository

```
pip install "Package" @ git+"URL of the repository"
```

e.g., If github repo `https://github.com/AndrejOrsula/dreamerv3` has following arch:

```
.
├── dreamerv3
│   ├── <.....>
│   ├── __init__.py
├── example.py
├── LICENSE
├── MANIFEST.in
├── README.md
├── requirements.txt
├── scores
├── setup.py
└── test.py

```

Then this repo has a module `dreamerv3`. It can be downloaded by:

```
pip install --no-cache-dir "dreamerv3 @ git+https://github.com/AndrejOrsula/dreamerv3.git"
```

### Don't use cache

```
pip install --no-cache-dir <package-name]>
```

It ensures that the package is always downloaded directly from the repository.
