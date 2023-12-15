---
categories:
- Software Engineering
date: 2023-12-14 15:56:22
tags: Linux
title: Tips for Remote Development
---

Tutorial about using inversese proxy to connect a server in a private network which your machine don't have access to.

<!--more-->

# How to remotely evelop with pycharm

Here're two plans.

## Plan 1

1. You can put your project in local. Then using pycharm to develop it **with a remote python interpreter**, instead of a local interpreter.

   ![Figure1.1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Figure%201.1.png)

   As you can see, the interpreter is at a remote server.

2. Then you'll see a connection in In "Tools" -> "Deployment" -> "Configuration".

   ![Figure1.2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Figure1.2.png)

   ![Figure1.3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Figure1.3.png) 

3. In In "Tools" -> "Deployment" -> "Configuration" --> "Mapping", config a project mapping. So that your remote server will have a copy of your local project, and every local change will be synced to the remote server.

   ![Figure1.4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Figure1.4.png)

4. In "Tools" -> "Deployment" -> "Options", select a way to sync your file:

   ![Figure1.5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Figure1.5.png)



## Plan 2

[Connect to a remote server from PyCharm](https://www.jetbrains.com/help/pycharm/remote-development-starting-page.html)

It's also simple. You can try it.

# How to connect a remote Server in a private network

If the server is in a public network, i.e., has a public IP, then you can just use `ssh` to connect it.

But what if the server is in a private network, i.e., has a private IP, which is common because lots of servers are in campus network(like eduroam) or company's network etc

You can't use ssh to connect these private IPs, so you only have 2 ways:

1. Using "inverse proxy", which means let the server connect to a "jump server" which has a public IP. This jump server can be connected by ssh and it can forward your requests to the server.

   ```text
   <Server in private network> -Connect-> <Jump Server on public nerwork> 
   
   <Your PC on public network> -> <Jump Server on public nerwork> -> <Server in private network>
   ```

2. Ask your ISP to assign a static public IP to your server.



A common inverse proxy tool is [ngork](https://dashboard.ngrok.com/get-started/setup/macos). It offers jump servers for free.


# Ngork

1. In the server, install [ngork](https://dashboard.ngrok.com/get-started/setup/macos).

2. In the server, start ngork and listen to port `22`.

3. Now in the [Endpoints page](https://dashboard.ngrok.com/cloud-edge/endpoints) of Ngork, you can see the server is listed as an "endpoint":

   ![Ngork Endpoints page](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Software%20Engineering/Tips%20for%20Remote%20Development/Ngork%20Endpoints%20page.png)

   The endpint is identified as

   ```
   tcp://<hostname>:<port>
   ```

4. Now in the client machine, just use

   ```
   ssh -p <port> <User>@<hostname>
   ```

   

Note: Each time you start the ngork process on the server, the `hostname` and `port` will be reset.

To avoid this, you can assign a static IP, which needs to pay money to ngork.