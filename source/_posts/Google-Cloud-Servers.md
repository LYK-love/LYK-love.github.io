---
title: Google Cloud Servers
tags: Linux
categories: Software Engineering
date: 2023-12-25 00:24:54
---


Source:

1. [GCloud](https://console.cloud.google.com/compute)
2. [GCloud: Install GPU drivers](https://cloud.google.com/compute/docs/gpus/install-drivers-gpu#ubuntu-pro-and-lts)

<!--more-->

# Intro

[GCloud](https://console.cloud.google.com/compute) offers 300 USD credits for first year.

![Google Cloud Credits](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/Google%20Cloud%20Server/Google%20Cloud%20Credits.png)

[->Source](https://cloud.google.com/products/ai?hl=en)

If you're an education account, i.e., your email account ends with `.edu`, then you'll get additional 100 USD credis.

So, I got 400 USD credits. 

Now I'll show you how to rent a GPU server on GCloud and config it.



[-->Control Panel for Google Cloud Instances](https://console.cloud.google.com/compute).

# Rent A Server

Go to [Marketplace](https://console.cloud.google.com/compute/instancesAdd(cameo:browse)), choose your desired config.

![Creat an instance](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/Google%20Cloud%20Server/Creat%20an%20instance.png)

Remember to select "GPU".

Now you can create your instance (your server based on this configuration).

![Created Instance](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Linux/Google%20Cloud%20Server/Created%20Instance.png)

# Config SSH Connection

Now you can use []() to connect to your server. But many people prefer to use ssh (or "OpenSSH"). 

Normally, following thses instructions will suffice. However, in GCloud, you need to do two things in advance:

## 1. Authentication

1. [Install](https://cloud.google.com/sdk/docs/install) the Google Cloud CLI, then

2. [initialize](https://cloud.google.com/sdk/docs/initializing) it by running the following command:    

   ```sh
   gcloud init
   ```

   * If you installed the gcloud CLI previously, make sure you have the latest version by running `gcloud components      update`. 

   * During initialization, you must choose your `Zone` the same as the one of your VM. E.g., if your VM's zone is `us-central-1`, then your config in your authentication should be it as well

     ```
     > gcloud init                                                                              Welcome! This command will take you through the configuration of gcloud.
     
     Settings from your current configuration [default] are:
     compute:
       region: us-central1
       zone: us-central1-a # The same!
     <...>
     ```

## 2. Choose an access method

[Choose an access method](https://cloud.google.com/compute/docs/instances/access-overview#oslogin)

It's recommended to choose [OS Login](https://cloud.google.com/compute/docs/oslogin). We need to set OS Login at the instance level (You can also set it at the project level but it's more complicated).

1. Know how to set custom data at the instance level ([->Source](https://cloud.google.com/compute/docs/metadata/setting-custom-metadata#gcloud)): Use the [`project-info add-metadata` command](https://cloud.google.com/sdk/gcloud/reference/compute/project-info/add-metadata).

   ```sh
   gcloud compute project-info add-metadata --metadata=KEY=VALUE
   ```

   Replace the following:

   - `KEY`: the name of your metadata key
   - `VALUE`: the value stored for this key

   **Example**

   For example to set two new entries `foo=bar` and `baz=bat` on a project, run the following command:

   ```sh
   gcloud compute project-info add-metadata \
       --metadata=foo=bar,baz=bat
   ```

   You can optionally specify one or more files from which to read metadata by using the `--metadata-from-file` flag.

2. Now plugin the parameters to enable OS Login ([->Source](https://cloud.google.com/compute/docs/oslogin/set-up-oslogin)):

   - Key: `enable-oslogin`
   - Value: `TRUE`

   Briefly

   ```
   gcloud compute project-info add-metadata --metadata=enable-oslogin=TRUE
   ```



## 3. Establish SSH Connection

[Connect to Linux VMs](https://cloud.google.com/compute/docs/connect/standard-ssh#openssh-client)

Connect to the VM by running the following command:

```sh
ssh -i PATH_TO_PRIVATE_KEY USERNAME@EXTERNAL_IP
```

Replace the following:

- `PATH_TO_PRIVATE_KEY`: the path to the private SSH key file that corresponds to the public key you added to the VM.
- `USERNAME`: your username. If you manage your SSH keys in  metadata (We don't use this method), the username is what you specified when you [created the SSH key](https://cloud.google.com/compute/docs/connect/create-ssh-keys).  For OS Login accounts, the username is [defined in your Google profile](https://cloud.google.com/compute/docs/connect/add-ssh-keys#os-login). For example, `cloudysanfrancisco_example_com` or `cloudysanfrancisco`. You can view your username after finishing the [authentication]().
- `EXTERNAL_IP`: the external IP address of the VM. 

   

To login witouout need to enter passeord, you can upload your ssh public key to the server:

```sh
ssh-copy-id PATH_TO_PRIVATE_KEY USERNAME@EXTERNAL_IP
```

# Install Nvidia Driver and CUDA

[Install GPU drivers](https://cloud.google.com/compute/docs/gpus/install-drivers-gpu#ubuntu-pro-and-lts)

You can also refer to [Pytorch GPU Setup Guide](https://lyk-love.cn/2023/12/22/pytorch-gpu-setup-guide/) tough the instructions here are easier.

1. First, select and install a [CUDA toolkit](https://docs.nvidia.com/deploy/cuda-compatibility/index.html#binary-compatibility__table-toolkit-driver)  that supports the [minimum driver](https://cloud.google.com/compute/docs/gpus/install-drivers-gpu#minimum-driver) that you need. 

2. Then install the Nvidia driver:

   **Ensure that Python 3 is installed** on your operating system.

   Download the installation script.

   ```sh
   curl https://raw.githubusercontent.com/GoogleCloudPlatform/compute-gpu-installation/main/linux/install_gpu_driver.py --output install_gpu_driver.py
   ```

   Run the installation script.

   ```sh
   sudo python3 install_gpu_driver.py
   ```

   The script takes some time to run. It might restart your VM. If the VM restarts, run the script again to continue the installation.

   Verify the installation. See [Verifying the GPU driver install](https://cloud.google.com/compute/docs/gpus/install-drivers-gpu#verify-driver-install).

3. This should be OK. There's no need to reboot your system.

# Assign a Static IP

By default, the instance will have a new enternal IP each time it starts. For convinence, you can reserve (aka, buy) a static external IP and attach to the instance.

1. [Reserve a new static external IP address](https://cloud.google.com/compute/docs/ip-addresses/reserve-static-external-ip-address#reserve_new_static)
2. [Change or assign an external IP address to an existing VM](https://cloud.google.com/compute/docs/ip-addresses/reserve-static-external-ip-address#IP_assign)

# Others

* [Add disk storage of VM](https://cloud.google.com/compute/docs/disks/resize-persistent-disk).

# What is OSLogin

https://cloud.google.com/compute/docs/oslogin

So, with OSLogin, a weird thing happens. My username after ssh is `lykuni_ucdavis_edu`:

```
$ whoami
lykuni_ucdavis_edu
```

However, I can't search this account name in the `/etc/passwd`!
