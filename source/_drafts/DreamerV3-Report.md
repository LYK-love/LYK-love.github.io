---
title: DreamerV3 Report
tags:
  - Machine Learning
categories:
  - Research
---

# Commands

See gym's [atari game list](https://gymnasium.farama.org/environments/atari/complete_list/)

See logs:

```
tensorboard --logdir logs
```







Box2D:

CarRacing

```sh
python sheeprl.py exp=dreamer_v3 env=gym env.id=CarRacing-v2 algo.cnn_keys.encoder=\[rgb\]
```



Atari:



Alien:

```
python sheeprl.py exp=dreamer_v3 env=atari env.id=AlienNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\]
```



Videopinball:

```
python sheeprl.py exp=dreamer_v3 env=atari env.id=VideoPinballNoFrameskip-v4 algo.cnn_keys.encoder=\[rgb\]
```



Vebture:

```
python sheeprl.py exp=dreamer_v3 env=atari env.id=Venture-v4 algo.cnn_keys.encoder=\[rgb\]
```





To move videos to my photoview:

```
cp -r /home/lyk/Projects/sheeprl/logs/runs/dreamer_v3/VideoPinballNoFrameskip-v4/2024-02-10_21-27-36_dreamer_v3_VideoPinballNoFrameskip-v4_42/version_0/train_videos/* ~/Images
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



# Envs

## Gravital

[Youtube: Gravital](https://youtu.be/mrWy2-mbmDg?si=EhnUoISIT9rKB6xv)

![image-20240210134900637](/Users/lyk/Library/Application Support/typora-user-images/image-20240210134900637.png)

# DreamerV2 drawbacks

> DreamerV2 achieves comparable or higher performance on most games except for Video Pinball. We hypothesize that the reconstruction loss of the world model does not encourage learning a meaningful latent representation because the most important object in the game, the ball, occupies only a single pixel. 



Figure F.1: Comparison of DreamerV2 to the top model-free RL methods IQN and Rainbow. The curves show mean and standard deviation over 5 seeds. IQN and Rainbow additionally average each point over 10 evaluation episodes, explaining the smoother curves. DreamerV2 outperforms IQN and Rainbow in all four aggregated scores. While IQN and Rainbow tend to succeed on the same tasks, DreamerV2 shows a different performance profile.

![DreamerV1 Figure F.1](/Users/lyk/Library/Application Support/typora-user-images/image-20240210133647475.png)

Figure E.1: Atari agent comparison. The bars show the difference in gamer normalized scores at 200M steps. DreamerV2 outperforms the four model-free algorithms IQN, Rainbow, C51, and DQN while learning behaviors purely by planning within a separately learned world model. DreamerV2 achieves higher or similar performance on all tasks besides Video Pinball, where we hypothesize that the reconstruction loss does not focus on the ball that makes up only one pixel on the screen.

![Figure E.1: Atari agent comparison.](/Users/lyk/Library/Application Support/typora-user-images/image-20240210125854769.png)

| Env            | DreamerV2 performs bad |
| -------------- | ---------------------- |
| Chopper Cum    | True                   |
| Private Eye    | True                   |
| Riverraid      | True                   |
| Seaquest       | True                   |
| Solaris        | True                   |
| Space Invaders | True                   |
| Star Gunner    | True                   |
| Venture        | True                   |
| Video Pinball  | True                   |

# DreamerV3 drawbacks

![DreamerV3 Figure U_1](/Users/lyk/Library/Application Support/typora-user-images/image-20240210131515070.png)



![DreamerV3 Table V_1](/Users/lyk/Library/Application Support/typora-user-images/image-20240210132000139.png)

[Rainbow DQN](https://arxiv.org/pdf/1710.02298v1.pdf): a model-free algorithm

| Env             | DreamerV2 performs better | Both Dreamers perform bad | Only DreamerV2 performs bad | Description |
| --------------- | ------------------------- | ------------------------- | --------------------------- | ----------- |
| Gravital        | True                      |                           |                             |             |
| James Bond      | True                      |                           |                             |             |
| Krull           | True                      |                           |                             |             |
| Road Runner     | True                      |                           |                             |             |
| Up N Down       | True                      |                           |                             |             |
| Zaxxon          | True                      |                           |                             |             |
| Chopper Command |                           | True                      |                             |             |
| Private Eye     |                           | True                      |                             |             |
| Riverraid       |                           | True                      |                             |             |
| Star Gunner     |                           | True                      |                             |             |
| Venture         |                           | True                      |                             |             |
| Video Pinball   |                           | True                      |                             |             |
| Gamer Mean (?)  |                           | True                      |                             |             |
| Seaquest        |                           |                           | True                        |             |
| Solaris         |                           |                           | True                        |             |
| Space Invaders  |                           |                           | True                        |             |

## James Bond 007

[Youtube: James Bond 007](https://youtu.be/O9NeL3hvbas?si=0u0EGlTb-RwTwYlu)

![image-20240210135121124](/Users/lyk/Library/Application Support/typora-user-images/image-20240210135121124.png)

## Krull

[Youtube: Krull](https://youtu.be/Yg_YK1owACE?si=S5VMoaXPr5droGII)

![image-20240210135440787](/Users/lyk/Library/Application Support/typora-user-images/image-20240210135440787.png)

## Road Runner

[Youtube: Road Runner](https://youtu.be/Y1ipBZGrxiY?si=xD8_4jbuGPqv_-O9)

![image-20240210135637263](/Users/lyk/Library/Application Support/typora-user-images/image-20240210135637263.png)

## Up and Down

[Youtube: Up and Down](https://youtu.be/pK61QuN2d8A?si=ZODqx90EeUt8Wl6G)

![image-20240210135934260](/Users/lyk/Library/Application Support/typora-user-images/image-20240210135934260.png)

To complete a round, the player must collect 10 colored flags by running over them with the buggy. If the player passes by a flag without  picking it up, it will appear again later in the round. The roads  feature inclines and descents that affect the buggy's speed, and bridges that must be jumped. A player loses a turn whenever the buggy either  collides with another vehicle without jumping on it, or jumps off the  road and into the grass or water.

## Zaxxon

[Youtube: Zaxxon](https://youtu.be/hj6LCdCwMYs?si=7DSoBOS6uQpeRcqS)

![image-20240210140411844](/Users/lyk/Library/Application Support/typora-user-images/image-20240210140411844.png)

## Chopper Command

[Youtube: Chopper Command](https://youtu.be/axswPLhb3PU?si=1hBcBwmN5cGrCqDH)

![image-20240210140834071](/Users/lyk/Library/Application Support/typora-user-images/image-20240210140834071.png)

## Private Eye

[Youtube: Private Eye](https://youtu.be/OfyS-Wj1M78?si=RUmNRlqxzomWrgC2)

![image-20240210141536522](/Users/lyk/Library/Application Support/typora-user-images/image-20240210141536522.png)

## River Raid

[Youtube: River Raid](https://youtu.be/pmPjsBDN9Xw?si=0HVIPKLsadblHzcz)

![image-20240210141727194](/Users/lyk/Library/Application Support/typora-user-images/image-20240210141727194.png)

## Star Gunner

[Youtube: Star Gunner]()

![image-20240210142027955](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142027955.png)

## Venture

[Atari: Venture](https://youtu.be/Two45w911PM?si=tXWTJ9wON9JgsVno)

![image-20240210142147018](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142147018.png)

![image-20240210142234691](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142234691.png)

## Video Pinball

[Youtube: Video Pinball]()

![image-20240210142309531](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142309531.png)

## Seaquest

[Youtube: Seaquest](https://youtu.be/Ir1t57ItCpw?si=wnnBCg-qqZaz9rnV)

![image-20240210142559348](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142559348.png)

## Solaris

[Youtube: Solaris](https://youtu.be/f68IjW7_w98?si=nGoBOvXASnvMKpTR)

![image-20240210142749807](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142749807.png)

## Space Invaders

[Youtube: Space Invaders](https://youtu.be/_ftVrgJTl4w?si=Eh-tOrTVnuAwoS8F)

![image-20240210142938820](/Users/lyk/Library/Application Support/typora-user-images/image-20240210142938820.png)



## Alien

[Youtube: Alien](https://www.youtube.com/watch?v=bOZ7TIx5Zv8&t=26s)

![image-20240210143242836](/Users/lyk/Library/Application Support/typora-user-images/image-20240210143242836.png)

## Tennis

[Youtube: Tennis](https://youtu.be/U-zMdAVr_oI?si=43FSrLu-ZFEIZPQ4)

![image-20240210143204036](/Users/lyk/Library/Application Support/typora-user-images/image-20240210143204036.png)
