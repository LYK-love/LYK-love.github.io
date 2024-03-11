---
title: ViZDoom Library in Reinforcement Learning
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Software Engineering
date: 2024-02-11 21:59:16
---


Sources:

1. [--> Documentation](https://vizdoom.farama.org/api/python/doomGame/#)
2. [--> Turorial](https://vizdoom.cs.put.edu.pl/tutorial)

ViZDoom allows developing AI **bots that play Doom using only visual information** (the screen buffer). It is primarily intended for research in machine  visual learning, and deep reinforcement learning, in particular.

<!--more-->

# Install

On Linux:

```sh
pip install vizdoom
```

Tested on Ubuntu22.04 X86_64 with python=3.9.



# Scripts

[--> A lot of example scripts](https://github.com/Farama-Foundation/ViZDoom/tree/master/examples/python), including:

1. `examples/python/basic.py`: The basic script, where the agent will perform random actions.
2. `examples/python/spectator.py`: The script of playing ViZDoom by yourself (as human), instead of by conducting random actions



Play ViZDoom by yourself:

```sh
git clone git@github.com:Farama-Foundation/ViZDoom.git
cd ViZDoom
python examples/python/basic.py
```



