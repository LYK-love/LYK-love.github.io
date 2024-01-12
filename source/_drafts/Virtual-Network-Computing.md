---
title: Virtual Network Computing
tags:
---

VNC is an acronym for Virtual Network Computing. It is nothing but a  Linux desktop sharing system or set of protocols for sharing desktop.  One can use VNC to control or access Linux based desktop remotely. VNC  works on client-server principal. There are many implementations of the  VNC protocol for Linux or Unix like systems. 

Some typical examples are  

TigerVNC: 

TightVNC: not support GLX ([-->Source](https://forums.raspberrypi.com/viewtopic.php?t=8200#p98101))

Vino (default for Gnome desktop), x11vnc, krfb  (default for KDE desktop), vnc4server and more.



# Run on Jupyter server

```shell
# Tested on Python 3.7-3.10. You can't install gym on Python>=3.11 since it's not supported.
pip install -q gym==0.26.2
pip install -q matplotlib
pip install -q jupyter
```

In jupyter, run:

```python
import matplotlib.pyplot as plt
%matplotlib inline
from IPython import display

import gym
```



```python

def show_state(env, step=0, info=""):
    plt.figure(3)
    plt.clf()
    plt.imshow(env.render())
    plt.title("Step: %d %s" % (step, info))
    plt.axis('off')

    display.clear_output(wait=True)
    display.display(plt.gcf())
env = gym.make("LunarLander-v2", render_mode="rgb_array")
env.action_space.seed(42)

observation, info = env.reset(seed=42)

for step in range(1000):
    observation, reward, terminated, truncated, info = env.step(env.action_space.sample())
    show_state(env=env, step=step, info=info)
    if terminated or truncated:
        observation, info = env.reset()
```

This outputs screenshots of the video and it's vary laggy. As a result, the VNC is the only choice.

# VNC vs. X11 Forwarding

X11 Forwarding just forwards the requests to the X server. Thus it'll not show the full desktop.



# TigerVNC (support GLX)

[-->Install tigetvnc on Ubuntu](https://www.cyberciti.biz/faq/install-and-configure-tigervnc-server-on-ubuntu-18-04/)



```shell
vncserver -kill :1
```



Make sure you the port is available (not blocked by the firewall).



* Listen to port 5901.



https://bytexd.com/how-to-install-configure-vnc-server-on-ubuntu/

不知道为什么, 有的机器上不支持gnome

# TightVNC (not support GLX)

[-->How to Install and Configure VNC on Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-and-configure-vnc-on-ubuntu-20-04)

* Listen to port 5901.

# X11VNC (support GLX)

[-->How to Setup X11VNC Server on Ubuntu & LinuxMint](https://tecadmin.net/setup-x11vnc-server-on-ubuntu-linuxmint/)

[Install x11vnc Server on Ubuntu 20.04 for Remote Access](https://omar2cloud.github.io/rasp/x11vnc/)

`x11vnc` connects to an **existing X server session**. This means it allows you to remotely view and interact with the same session that  someone would see if they were physically sitting in front of the  computer. It's like remotely controlling the actual physical display.

But if the server is headless, it doesn't have a monitor, and thus not have a X server session, which means  `x11vnc` can't work on headless servers! (I know some people have solutions, but I tried and all failed.)

( Listen to port 5900.

# Connect to a VNC

This is quite simple, you can use [VNC Viewer](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwj7gubo3bmDAxXmEkQIHWJNB6kQFnoECAYQAQ&url=https%3A%2F%2Fwww.realvnc.com%2Fen%2Fconnect%2Fdownload%2Fviewer%2F&usg=AOvVaw0UTdY8kQhw7EWigV5-iC08&opi=89978449).

For Mac users, VNC connection has already been supported in the Finder. 

1. Open Finder. "Go" > "Connect to Server..."
2. Input `vnc://<hostname>:<port>`. The `hostname` is that of the server, and the `port` is the port number VNC listens on the server.
3. Press "Connect".

