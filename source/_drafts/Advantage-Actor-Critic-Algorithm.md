---
title: Advantage Actor Critic Algorithm
tags:
---

Source:

1. [Sheeprl: The A2C algorithm](https://eclecticsheep.ai/2023/12/14/intro-rl.html)

<!--more-->

# A2C

The **Advantage Actor Critic** (A2C) algorithm is a [policy gradient method](https://proceedings.neurips.cc/paper_files/paper/1999/file/464d828b85b0bed98e80ade0a5c43b0f-Paper.pdf) in Reinforcement Learning. It uses the **actor-critic** architecture, composed by:

- An Actor, which takes as input the environment state $s_t$ and outputs a probability distribution over the possible actions $a_t$
- A Critic, which takes as input the environment state $s_t$ and outputs a value $V\left(s_t\right)$, which is an estimate of the expected return if the agent starts in state $s_t$ and follows the policy $\pi$ afterwards





For simplicity we have only defined the MLPEncoder and A2CAgent classes, which are the ones we will use in this article. The MLPEncoder class is used to create a multi-layer perceptron (MLP) encoder, which is used to extract features from the observations. The A2CAgent class is used to create the agent model, which is composed by:
- A feature extractor, which is an MLP encoder that takes as input the observations and outputs a vector of features
- A critic, which is an MLP that takes as input the features extracted by the feature extractor and outputs a value $V\left(s_t\right)$, which is an estimate of the expected return if the agent starts in state $s_t$ and follows the policy $\pi$ afterwards
- An actor, which is an MLP that takes as input the features extracted by the feature extractor and outputs a probability distribution over the possible actions $a_t$



# Loss

There are two loss functions we need to define:
- The policy loss, which is used to train the actor and is defined as:
$$
L_\pi=-\sum_{t=1}^T \log \pi_\theta\left(a_t \mid s_t\right)\left[G_t-V_\theta^\pi\left(s_t\right)\right]=-\sum_{t=1}^T \log \pi_\theta\left(a_t \mid s_t\right) A_t
$$
where $A_t$ is the advantage function, which is defined as:
$$
A_t=G_t-V_\theta^\pi\left(s_t\right)
$$
where $G_t$ is the return at time $t$, which is defined as:
$$
G_t=\sum_{k=t}^T \gamma^{k-t} R_{k+1}
$$

The advantage indicates how much better an action is given a particular state over a random action selected according to the policy for that state.
- The value loss, which is used to train the critic and is simply the Mean Squared Error (MSE) between the estimated value and the actual return:

$$
L_V=\sum_{t=1}^T\left(G_t-V_\theta^\pi\left(s_t\right)\right)^2
$$
