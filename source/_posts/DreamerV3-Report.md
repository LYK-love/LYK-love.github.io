---
title: DreamerV3 Report
tags:
  - Tech Reports
categories:
  - Research
mathjax: true
date: 2024-02-25 09:28:46
---


Papers:

1. [RSSM](https://arxiv.org/pdf/1811.04551.pdf)

1. [DreamerV1](https://arxiv.org/abs/1912.01603)
2. [DreamerV2](https://arxiv.org/abs/2010.02193)
3. [DreamerV3](https://arxiv.org/abs/2301.04104)

<!--more-->

# Projects

THere're currently 3 codebases about DreamerV3. The most readable one is sheeprl's codebase.

1. The author's implementation, written in Jax: https://github.com/danijar/dreamerv3
2. A PyTorch implementation by NM512: https://github.com/NM512/dreamerv3-torch
3. A PyTorch implementation by sheeprl: https://github.com/Eclectic-Sheep/sheeprl



Besides, there're some impementations for DreamerV2 and DreamerV1. 

* [adityabingi's Dreamerv1 & v2 codebase](https://github.com/adityabingi/Dreamer)
* [EasyDreamer: A Simplified Version of the DreamerV1 Algorithm with Pytorch](https://github.com/kc-ml2/SimpleDreamer?tab=readme-ov-file)



There're also some explanations of the code:

1. [some code notes](https://docs.google.com/document/d/179Nqo1dc9ZExB1-71Tj4iFt2Dq-uWH-6k6w1e2rkwBM/edit) from a [Reddit user](https://www.reddit.com/r/reinforcementlearning/comments/1azgrc4/comment/ks1hipp/?utm_source=share&utm_medium=web2x&context=3)
2. [implementations of the tricks in cleanRL, applied to PPO.](https://github.com/RyanNavillus/PPO-v3/blob/main/ppo_v3/ppo_envpool_tricks.py): This obviously doesn't include any of the world model architecture or loss functions,  just the new tricks introduced by DreamerV3

## sheeprl

Installation:

```sh
conda create -n sheeprl python=3.9
conda activate sheeprl

git clone git@github.com:Eclectic-Sheep/sheeprl.git
cd sheeprl
pip install .
pip install .\[atari,mujoco,dev,test\]
pip install gymnasium\[box2d\]
```

## Hafner's version

Hafner's codebase

Installation:

```sh
git clone git@github.com:danijar/dreamerv3.git
cd dreamerv3
conda create -n DreamerV3JAX python=3.9
conda activate DreamerV3JAX
pip install --upgrade "jax[cuda12_pip]" -f https://storage.googleapis.com/jax-releases/jax_cuda_releases.html
pip install -r requirements.txt
pip install wandb
```


To save and see the reports, you need to config wandb.

## NM512's version

Github: NM512's PyTorch implementation

```sh
conda create -n DreamerTorch python=3.9
conda activate DreamerTorch

git clone git@github.com:NM512/dreamerv3-torch.git
cd dreamerv3-torch
pip install setuptools==65.5.0 "wheel<0.40.0"
pip install -r requirements.txt
```



In addition, you need to install Atari ROMs to run Atari envs, follow here to download and install ROM:

```sh
wget http://www.atarimania.com/roms/Atari-2600-VCS-ROM-Collection.zip ./
unzip ./Atari-2600-VCS-ROM-Collection.zip
python -m atari_py.import_roms ./ROMS
```

This should print out the names of ROMs as it imports them.  The ROMs will be copied to your atari_py installation directory.

# Commands

Here I introduce my commands for running the codebase of **sheeprl**.

## Tricks

### Multi-GPU

Use [multi -GPU supported by Ligntening Fabric](https://lightning.ai/docs/fabric/stable/api/fabric_args.html)

```sh
fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 
```

### Mixed-precision

Use [mixed precision supported by Ligntening Fabric](https://lightning.ai/docs/fabric/stable/fundamentals/precision.html):

```
fabric.precision=16-mixed
```

### Model size

DreamerV3 has multiple sizes of models, see the table from the [the Appendices: B in the paper](https://arxiv.org/pdf/2301.04104.pdf):

| Dimension           | XS   | S    | M    | L    | XL   |
| ------------------- | ---- | ---- | ---- | ---- | ---- |
| GRU recurrent units | 256  | 512  | 1024 | 2048 | 4096 |
| CNN multiplier      | 24   | 32   | 48   | 64   | 96   |
| Dense hidden units  | 256  | 512  | 640  | 768  | 1024 |
| MLP layers          | 1    | 2    | 3    | 4    | 5    |
| Parameters          | 8M   | 18M  | 37M  | 77M  | 200M |

Table B.1: Model sizes. The encoder consists of stride 2 convolutions of doubling depth until resolution $4 \times 4$ followed by flattening. The decoder starts with a dense layer, followed by reshaping to $4 \times 4 \times C$ and then inverts the encoder architecture. The dynamics are implemented as RSSM with vectors of categorical representations, consisting of a GRU and dense layers.

I use the XS size.

```sh
algo=dreamer_v3_XS  algo.learning_starts=1024
```

## Log

See logs:

```sh
tensorboard --logdir logs
```



Map generated videos to my photoview:

```sh
ln -s /home/lyk/Projects/sheeprl/logs $IMAGE_HOME/sheeprl_log
```

# Scripts

## DMC

## Box2D

### CarRacing

CarRacing

```sh
python sheeprl.py exp=dreamer_v3 env=gym env.id=CarRacing-v2 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```



For dev:

```
python sheeprl.py exp=dreamer_v3 env=gym env.id=CarRacing-v2 algo.cnn_keys.encoder=[rgb] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=200 env.num_envs=1
```



For testing videos:

```sh
python sheeprl.py exp=dreamer_v3 env=gym env.id=CarRacing-v2 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed env.num_envs=2  algo.learning_starts=1024 algo.total_steps=2000000
```

`total_steps` should be small.

I didn't set `env.num_envs `, by default it should be 4.



Eval from checkpoint:

```
export CKPT="/home/lyk/Projects/sheeprl/logs/runs/dreamer_v3/VideoPinballNoFrameskip-v4/2024-02-18_02-56-29_dreamer_v3_VideoPinballNoFrameskip-v4_42/version_0/checkpoint/ckpt_4800000_0.ckpt"

python sheeprl_eval.py checkpoint_path=$CKPT fabric.accelerator=gpu env.capture_video=True
```



## Atari

See gym's [atari game list](https://gymnasium.farama.org/environments/atari/complete_list/) for all atari envs.



Alien:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=AlienNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```

For testing videos:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=AlienNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed env.num_envs=1  algo.learning_starts=1024 algo.total_steps=200000
```





Video pinball:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=VideoPinballNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```



For testing videos:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=VideoPinballNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed env.num_envs=1  algo.learning_starts=1024 algo.total_steps=2000000
```

`total_steps` should be small.



Alien:

Venture:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=VentureNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_M fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```



Star Gunner

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=StarGunnerNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_M fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```



Private Eye:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=PrivateEyeNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_M fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```



Riverraid:

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=RiverraidNoFrameskip algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_M fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```

# Errors

If you interrupt the running command, you might get 

```
Inconsistency detected by ld.so: ../sysdeps/x86_64/dl-machine.h: 534: elf_machine_rela_relative: Assertion `ELFW(R_TYPE) (reloc->r_info) == R_X86_64_RELATIVE' failed!
```

at next execution.

Solution: reboot the system.



***



Error:

```
Error in call to target 'gymnasium.envs.registration.make':
DependencyNotInstalled('Box2D is not installed, run `pip install gymnasium[box2d]`')
```



Solution:

```
pip install gymnasium[box2d]
```

***



```
ValueError: bad marshal data (unknown type code)
```



If you get that error, the compiled version of the Python module (the .pyc file) is corrupt probably. Gentoo Linux provides `python-updater`, but in Debian the easier way to fix: just delete the .pyc file. If you don't know the pyc, just delete all of them (as root):

```sh
find <the error dir> -name '*.pyc' -delete
```

# Training process

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Tech%20Reports/DreamerV3%20Report/Decoder%27s%20out%20after%201.2M%20steps.png" alt="image-20240225085626417" style="zoom:33%;" />



I use sheeprl code base to trian the `dreamer_v3_XS` model (max_steps = 5,000,000), it'll take about 50 hours. 

```sh
python sheeprl.py exp=dreamer_v3 env=atari env.id=VideoPinballNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\] algo=dreamer_v3_XS fabric.accelerator=gpu fabric.strategy=ddp fabric.devices=2 fabric.precision=16-mixed algo.learning_starts=1024
```

So in average, every 1,000,000 steps cost 10 hours. Meanwile, the output of the decoder is blurry and has a lot of colorful noise at step=1,200,000. I'll wait until step=5,000,000 to see if these noise still exists.

