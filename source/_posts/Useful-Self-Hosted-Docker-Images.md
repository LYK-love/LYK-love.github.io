---
title: Useful Self-Hosted Docker Images
categories:
- Software Engineering
tags: Docker
date: 2024-01-28 17:07:39
---

Useful self-hosted docker images which can be **hosted on a remote server** and **be visited on the local browser**.

<!--more-->

# List

To use them, [install docker]() and [docker compose](https://lyk-love.cn/2022/02/15/docker-compose/) first and run the corresponding commands. 



* Music: [moodist](https://github.com/geekyouth/moodist)
* Image processing: [image matting](https://github.com/ihmily/image-matting)
* Photo gallery: [photoview](https://github.com/LYK-love/photoview). This is forked from [-->here](https://github.com/photoview/photoview). I only changed the `docker-compose.yml` file.
* [webssh2](https://github.com/billchurch/WebSSH2): **Use ssh on your browser!**

# How to install

Below are my favourite docker images. To use them, [install docker]() and [docker compose](https://lyk-love.cn/2022/02/15/docker-compose/) first and run the corresponding commands. 

* [moodist](https://github.com/geekyouth/moodist)

  ```sh
  docker run -d --restart=unless-stopped -p 8000:8080 --name moodist  geekyouth/moodist:v1.2.0
  ```

* [image matting](https://github.com/ihmily/image-matting)

  ```sh
  docker run -d --restart=unless-stopped -p 8001:8000 ihmily/image-matting:0.0.3
  ```
  
* Image gallary: 

  ```sh
  git clone git@github.com:LYK-love/photoview.git
  cd photoview
  docker compose up -d
  ```
  
  According to my `docker-compose.yml`, this will listen to host's port=`8002`.
  
  Note: you need to set env variable `IMAGE_HOME` first. This will be used by Photoview to store the images.
  
* [webssh2](https://github.com/billchurch/WebSSH2):

  ```sh
  docker run -d --restart=unless-stopped --name webssh -p 8003:2222 billchurch/webssh2
  ```
  
  The docker image is [-->here](https://hub.docker.com/r/billchurch/webssh2).



# How to use

Take myself as an example, I run these containers on my remote server (Ubuntu22.04 x86_64):

1. moodist, listening to port `8000` on remote server.

2. image matting, listening to port `8001` on remote server.

3. image matting, listening to port `8002` on remote server.

4. webssh2, listening to port `8003` on remote server.

   * Note that webssh2 starts at `http://localhost:<port>/ssh/host/<hostname>`. So I use

     ```
     http://localhost:8003/ssh/host/x.x.x.x
     ```

     to visit it.



My remote server has IP `x.x.x.x`, I can directly visit `http://x.x.x.x:<port>` to visit each application.

But what if we don't have access to `x.x.x.x:<port>`? In many cases we only have access to the port=22 while other ports blocked by VPN we use or firewall on the server.

In this case you should start [ssh port forwarding](https://lyk-love.cn/2024/01/28/how-to-use-ssh/#port-forwarding) first.

```sh
ssh -f -N -q -L <localPort>:localhost:<remotePort> <username>@<remoteHost>
```

After that, we can visit these applications locally via `http://x.x.x.x:<localPort>`.



## moodist

![moodist](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Docker/Useful%20Self-Hosted%20Docker%20Images/moodist.png)

## image matting

![image matting](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Docker/Useful%20Self-Hosted%20Docker%20Images/image%20matting.png)



## photoview

The usage can be found at [Initial Setup](https://github.com/LYK-love/photoview#initial-setup).

The photos will have to be scanned before they show up, you can start a scan manually, by navigating to `Settings` and clicking on `Scan All`

![photoview](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Docker/Useful%20Self-Hosted%20Docker%20Images/photoview.png)

## webssh2

After staring the container, you can use ssh on your browser via 

```
http://localhost:<port>/ssh/host/<hostname>
```



![webssh2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Docker/Useful%20Self-Hosted%20Docker%20Images/webssh2.png)



