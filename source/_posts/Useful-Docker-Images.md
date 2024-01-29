---
title: Useful Docker Images
date: 2024-01-28 17:07:39
tags:
---




# How to install

Below are my favourite docker images. To use them, [install docker]() first and run the corresponding commands. 

* Music: [Moodist](https://github.com/geekyouth/moodist)

  ```sh
  docker run -d --restart=unless-stopped -p 8080:8080 --name moodist  geekyouth/moodist:v1.2.0
  ```

* Image processing: [Image matting](https://github.com/ihmily/image-matting)

  ```sh
  docker run -d --restart=unless-stopped -p 8000:8000 ihmily/image-matting:0.0.3
  ```

# How to use

* If you run this containers on you local machine, you can visit them at `http://localhost:<port>`.

* If you run this containers on you server, you can visit them at `http://<hostname>:<port>`, where `<hostname>` is the IP of your server.

* If you run this containers on you server and you don't have access to these ports (8080, 8000, etc), as long as you have access to the port=22, you can use [ssh port forwarding]() to visit them.

  ```sh
  ssh -f -N -q -L <localPort>:localhost:<remotePort> <username>@<remoteHost>
  ```





