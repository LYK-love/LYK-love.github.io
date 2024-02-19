---
title: Gymnasium Library in Reinforcement Learning
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Software Engineering
date: 2024-02-11 22:08:47
---


Source:

1. [--> Gymnasium github repo](https://github.com/Farama-Foundation/Gymnasium)
2. [--> Documentation](https://gymnasium.farama.org/)

Gymnasium is the successsor of the famous [OpenAI Gym](https://github.com/openai/gym) library. It's highly recommended to move to gymnasium since gym is not being maintained.

Gymnasium is maintained by the Farama Foundation, an open-source nonprofit foundation.

<!--more-->

# Install

On Linux:

```
pip install gymnasium
```

Tested on Ubuntu22.04 X86_64 with `python=3.9`.



This does not include dependencies for all families of environments. According to your requirement, you may need to install dependencies for one family like `pip install "gymnasium[atari]"` or use `pip install "gymnasium[all]"`.

# Scripts

## Box2D

For [`box2d` environments](https://gymnasium.farama.org/environments/box2d/), we must also install:

```sh
pip install gymnasium[box2d]
```

### CarRacing

To play:

```sh
git clone git@github.com:Farama-Foundation/Gymnasium.git
cd Gymnasium
python gymnasium/envs/box2d/car_racing.py
```

## Atari

For [Atari environments](https://gymnasium.farama.org/environments/atari/), we must also install:

```sh
pip install "gymnasium[atari, accept-rom-license]"
```



# Errors

1. OpenGL error: when running

   ```sh
   python gymnasium/envs/box2d/car_racing.py
   ```

   The output is

   ```
   libGL error: MESA-LOADER: failed to open swrast: /usr/lib/dri/swrast_dri.so: cannot open shared object file: No such file or directory (search paths /usr/lib/x86_64-linux-gnu/dri:\$${ORIGIN}/dri:/usr/lib/dri, suffix _dri)
   libGL error: failed to load driver: swrast
   X Error of failed request:  BadValue (integer parameter out of range for operation)
     Major opcode of failed request:  149 (GLX)
     Minor opcode of failed request:  3 (X_GLXCreateContext)
     Value in failed request:  0x0
     Serial number of failed request:  153
   ```

   This problem occurs randomly. I can successfully run the experiment for one day and meet this error the next day with not any conguguration changed.

   The [solution](https://stackoverflow.com/a/76557173) is simple:

   ```sh
   conda install -c conda-forge libffi
   ```

   Works on my Ubuntu22.04 x86_64 Python=3.10 environment.

2. Can't create Atari environment:

   ```
   gymnasium.error.NamespaceNotFound: Namespace ALE not found. Have you installed the proper package for ALE?
   ```

   [Solution](https://stackoverflow.com/questions/76150278/getting-an-error-trying-to-import-environment-openai-gym): There seems sth wrong with gymnasium. We have to use gym instead of gymnasium, and 

   ```sh
   pip install "gym[atari, accept-rom-license]"
   ```

   Run:

   ```py
   import gym # or "import gymnasium as gym"
   
   if __name__ == '__main__':
       env = gym.make("ALE/Breakout-v5")
   ```

   The output is

   ```
   A.L.E: Arcade Learning Environment (version 0.8.1+53f58b7)
   [Powered by Stella]
   ```

   

