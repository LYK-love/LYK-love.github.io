---
title: How to Use SSH
tags:
  - Linux
categories:
  - Software Engineering
date: 2024-01-28 17:07:51
---


Source:

1. [SSH Essentials: Working with SSH Servers, Clients, and Keys](https://www.digitalocean.com/community/tutorials/ssh-essentials-working-with-ssh-servers-clients-and-keys)

<!--more-->

# Port forwarding

Suppose your local machine connecting to a remote server (IP=`x.x.x.x`) via ssh (port=22). Your server starts **[moodist](https://github.com/geekyouth/moodist)** on port 8080, and you connect the server with VPN. 

Suppose you don't have access to ports other than `22` on the remote server due to some reason such as the contraint of VPN or the restriction of firewall. As a result, you can't visit the web page via `http://x.x.x.x:8080` on your local machine.



However, You can visit the web page via **ssh port forwarding**:

```sh
ssh -f -N -q -L localPort:localhost:remotePort username@remoteHost
```

* `-L`: Start port forwarding.
* `-f`: Puts the SSH session into the background just before it executes the command. This is useful for running a long-lived SSH process.
* `-N`: Indicates that no remote commands will be executed, and is useful for port forwarding.
* `-q`: Enables quiet mode to suppress command execution outputs.
* `localPort`: The port number on your local machine you want to use for forwarding.
* `localhost`: Specifies that the forwarding is to the localhost on the remote machine.
* `remotePort`: The port number on the remote machine you want to forward to.
* `username@remoteHost`: Your login credentials and the address of the remote machine.

Now you can visit `http://localhost:8080`, the ssh will route the network traffic to `x.x.x.x:8080`, then forwarding it to the 8080 port of the server locally.

# Management

Look at all ssh processes:

```sh
ps aux | grep ssh
```



Kill all ssh preocesses:

```sh
killall ssh
```

