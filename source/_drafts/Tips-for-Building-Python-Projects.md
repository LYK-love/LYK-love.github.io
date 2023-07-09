---
title: Tips for Building Python Projects
tags:
---



# Python项目容器化

Py项目和别的项目的不同之处在于需要安装各种依赖，所以需要写个`requirements.txt`来指定依赖，然后dockerfile中用pip3来下载



## Dockerfile

```dockerfile
FROM python:3.9.7
WORKDIR /project
COPY requirements.txt ./




RUN pip3 install -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/
RUN pip3 uninstall opencv-python -y
RUN pip3 install opencv-python-headless -i https://mirrors.aliyun.com/pypi/simple/

COPY . .
CMD ["python", "server.
```

## requirements.txt

```
text2vec==1.1.5
numpy==1.21.2
pandas==1.4.1
flask==2.0.3

baidu-aip
jieba
gensim
opencv-python==4.5.5.64

urllib3
matplotlib
chardet
```

# 常见环境问题

## opencv

If you are using **`cv2`** or **`opencv-python`** and then building the application through docker you will get an **importerror: libgl.so.1: cannot open shared object file: no such file or directory.**

The **importerror: libgl.so.1: cannot open shared object file: no such file or directory** mainly occurs because of the missing dependencies of cv2 when you build the application with Docker. These dependencies will be present in the local instance and thus you will not get this error.

解决方案：Install `opencv-python-headless`, which includes a a precompiled binary *wheel* with no external dependencies (other than **numpy**), and is intended for headless environments like Docker.

in Dockerfile:

```dockerfile
RUN pip3 uninstall opencv-python -y
RUN pip3 install opencv-python-headless -i https://mirrors.aliyun.com/pypi/simple/
```

# M1 Mac环境配置

众所周知，各大机器学习Python库对Mac M1的支持并不好，因此这里介绍一下M1的Python机器学习环境配置

* tensorflow 几乎不支持 M1

* pytorch(.包括torchvison )已经支持M1

* torchboard等库仍未支持M1

* **Python < 3.8  [are not available on M1](https://bugs.python.org/msg382939).**

  > There are no plans to backport support to 3.7 and 3.6 which are in the security-fix-only phase of their release cycles.



## opencv

```python
conda install -c conda-forge opencv  # 安装M1 M2 open cv，已经默认可用
```

## pytorch

[官网](https://pytorch.org/)

之前Torchvison不支持M1时，`import torchvision`会得到 segment falut报错:

```
libc++: terminating with uncaught exception of type std::length_error: vector
```



现在Torchvision已经支持M1了！ pytorch && torchvision安装:

```python
conda install pytorch torchvision torchaudio -c pytorch # 安装M1 M2 pytorch，已经默认可用
```







## pip

Pip的安装详见*Linux Toolkit*



安装最新版模块 / 升级模块

```python
# --upgrade or -U: Upgrade all packages to the newest available version
pip install -U [lib]
```



## 
