---
title: Pytorch GPU Setup Guide
tags:
  - Machine Learning
  - Python
categories: Software Engineering
mathjax: true
date: 2023-12-22 22:48:51
---


Sources:

1. [Pytorch GPU Setup Guide](https://mct-master.github.io/machine-learning/2023/04/25/olivegr-pytorch-gpu.html)

<!--more-->

# Install CUDA

> CUDA is a programming model and computing toolkit developed by NVIDIA.  It enables you to perform compute-intensive operations faster by  parallelizing tasks across GPUs. CUDA is the dominant API used for deep  learning although other options are available, such as OpenCL. PyTorch  provides support for CUDA in the `torch.cuda` library. 



**Note: While this section introduces two ways to install CUDA. If you simply want to run CUDA code, you don't need to install CUDA**. In fact, PyTorch has a built-in CUDA runtime (See the next section.) so that you can just install PyTorch(CUDA version) and you can run CUDA code! 

* Note: Only CUDA runtime is included by PyTorch. The toolchain, such as `nvcc`, is not included.

## Install locally (recommended)

1. Using [this website](https://developer.nvidia.com/cuda-downloads) to get the installation command.

2. Check if CUDA driver is running:

   ```sh
   nvidia-smi
   ```

For instance, the installation instructions for x86_64 Ubuntu22.04 is:

1. Base Installer:

   ```
   wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.deb
   sudo dpkg -i cuda-keyring_1.1-1_all.deb
   sudo apt-get update
   sudo apt-get -y install cuda-toolkit-12-3
   ```

2. Driver Installer (the legacy kernel module flavor):

   ```
   sudo apt-get install -y cuda-drivers
   ```

   You can install To install the open kernel module flavor rather than the legacy one using:

   ```sh
   sudo apt-get install -y nvidia-kernel-open-545sudo apt-get install -y cuda-drivers-545
   ```

3. [Environment Setup](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#post-installation-actions):

   Add this path to the `PATH` variable:

   ```sh
   export PATH=/usr/local/cuda-12.3/bin${PATH:+:${PATH}}
   export LD_LIBRARY_PATH=/usr/local/cuda-12.3/lib64\
                            ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
   ```

   After that, you can use

   ```sh
   nvcc -v
   ```



### Old cuda

[CUDA Toolkit 12.1 Downloads](https://developer.nvidia.com/cuda-12-1-0-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=22.04&target_type=deb_network)



1. Base Installer:

   ```
   wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.0-1_all.debsudo 
   dpkg -i cuda-keyring_1.0-1_all.deb
   sudo apt-get update
   sudo apt-get -y install cuda-12-1 # select the version you want
   ```

2. Driver Installer (the legacy kernel module flavor):

   ```sh
   sudo apt-get install -y cuda-drivers
   ```

3. [Environment Setup](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#post-installation-actions):

   Add this path to the `PATH` variable:

   ```sh
   export PATH=/usr/local/cuda-12.1/bin${PATH:+:${PATH}}
   export LD_LIBRARY_PATH=/usr/local/cuda-12.1/lib64\
                            ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
   ```

   

## Install via conda

You can install CUDA and its toolchain(like `nvcc`) [via conda](https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/index.html?highlight=conda#conda-overview):

```sh
conda install cuda -c nvidia
```

CUDA installed by conda is **local to the conda environment**.



# Pytorch(CUDA version)

This command will only install a **CPU** compiled version of pytorch:

```sh
conda install torch
```



To install a **GPU** compiled version, you need to:

1. Go to the [Pytorch website](https://pytorch.org/get-started/locally/)

2. Choose a CUDA version of pytorch:

   ![image-20231218223607563](/Users/lyk/Library/Application Support/typora-user-images/image-20231218223607563.png)



But how do we know which version **CUDA_VERSION** we need?

# CUDA Versions

CUDA has both a <u>driver API</u> and a <u>runtime API</u>, and their API versions can be entirely different. 



* Get the driver API version

  ```shell
  nvidia-smi
  ```

  * This command points to the GPU  driver, and **it’s this CUDA version you need when installing Pytorch**.

* Get the runtime API version

  ```sh
  nvcc --version
  ```

The original commands from the Pytorch website, i.e., CUDA11.8, CUDA12.1, works just fine for most cases. Just double check with the command above if you’re  running into issues.

# Monitor CUDA

```sh
watch -n 1 nvidia-smi
```

or

[nvitop](https://github.com/XuehaiPan/nvitop?tab=readme-ov-file)



# Check if CUDA is avaiable

To check if Pytorch can find your GPU, use the following:

```python
import torch

# Check if CUDA (GPU) is available
if torch.cuda.is_available():
    # Print the number of available GPUs
    print(torch.cuda.device_count(), "GPU(s) available.")

    # Print the name of the current GPU
    print("Current GPU:", torch.cuda.get_device_name(0))
else:
    print("No GPU available. Switching to CPU.")
    device = torch.device("cpu")
```

## If GPU cannot be found

If your GPU cannot be found, it would be helpful to get some more feedback. Try  sending something to the GPU. It will fail, and give you the reason:

```python
torch.zeros(1).cuda()
```

Should you want to start over because Pytorch is still not  communicating with your GPU, you can remove your current environment and packages through your command line interface like so:

# Additional notes

If any GPU is recognized, you can now get more info about them or  even decide which tensors and operations should go on which GPU.

```python
    torch.cuda.current_device()     # The ID of the current GPU.
    torch.cuda.get_device_name(id)  # The name of the specified GPU, where id is an integer.
    torch.cuda.device(id)           # The memory address of the specified GPU, where id is an integer.
    torch.cuda.device_count()       # The amount of GPUs that are accessible.
```

Hopefully, that will resolve some issues for you. Happy hacking!

# Jax



[JAX: pip installation: GPU (CUDA, installed locally, harder)](https://jax.readthedocs.io/en/latest/installation.html)

# Common Problems

Error:

```
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver. Make sure that the latest NVIDIA driver is installed and running.
```

This happens often after the update of the kernel.



Solution:

1. Remove current cuda driver:

   ```
   # First of all, we need to remove all of the previous dependencies
   sudo apt-get remove --purge '^nvidia-.*'
   sudo apt-get purge nvidia-*
   sudo apt-get update
   sudo apt-get autoremove
   ```

2. Reinstall CUDA.

