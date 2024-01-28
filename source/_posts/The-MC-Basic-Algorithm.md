---
title: The MC Basic Slgorithm
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
date: 2024-01-27 17:23:26
---


1. [Shiyu Zhao. *Chapter 5: Monte Carlo Methods. Mathematical Foundations of Reinforcement Learning*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning).
2. [--> Youtube: MC Basic](https://youtu.be/q1rTQXd1p-c?si=wuQpNK0b1GACa9eE)

<!--more-->

# Motivation

Recalling that the [policy iteration algorithm](https://lyk-love.cn/2024/01/08/value-iteration-and-policy-iteration/) has two steps in each iteration:

1. Policy evaluation(PE): $v_{\pi_k}=r_{\pi_k}+\gamma P_{\pi_k} v_{\pi_k}$.
2. Policy improvement(PI): $\pi_{k+1}=\arg \max _\pi\left(r_\pi+\gamma P_\pi v_{\pi_k}\right)$.

The PE step is calculated through solving the [Bellman equation]().

The elementwise form of the (PI) step is:
$$
\begin{aligned}
\pi_{k+1}(s) & =\arg \max _\pi \sum_a \pi(a \mid s)\left[\sum_r p(r \mid s, a) r+\gamma \sum_{s^{\prime}} p\left(s^{\prime} \mid s, a\right) v_{\pi_k}\left(s^{\prime}\right)\right] \\
& =\arg \max _\pi \sum_a \pi(a \mid s) q_{\pi_k}(s, a), \quad s \in \mathcal{S}
\end{aligned}
$$

The key is $q_{\pi_k}(s, a)$! So how can we compute $q_{\pi_k}(s, a)$?

## Model based case

Since the policy iteration algorithm is a **model based** algorithm, i.e., the model is given. [Recalling that](https://lyk-love.cn/2024/01/03/basic-concepts-in-reinforcement-learning/#markov-decision-processes) the model (or dynamic) of a MDP is composed of two parts:

1. State transition probability: $p\left(s^{\prime} \mid s, a\right)$. 
2. Reward probability: $p(r \mid s, a)$.

Thus, we can calculate $q_{\pi_k}(s, a)$ via following equation
$$
q_{\pi_k}(s, a)=\sum_r p(r \mid s, a) r+\gamma \sum_{s^{\prime}} p\left(s^{\prime} \mid s, a\right) v_{\pi_k}\left(s^{\prime}\right)
$$
where  $p\left(s^{\prime} \mid s, a\right)$ and  $p(r \mid s, a)$ are given, and every $v_{\pi_k}\left(s^{\prime}\right)$ is calculated in the PE step.

## Model free case

But what if we don't know the model, i.e., we want to convert policy iteration to a **model based** algorhtm?

Recalling [the definition of action value](https://lyk-love.cn/2024/01/06/action-value/#definition):
$$
\begin{equation} \label{eq_def_of_action_value}
q_\pi(s, a) \triangleq \mathbb{E}\left[G_t \mid S_t=s, A_t=a\right]
\end{equation}
$$


We can use expression $\eqref{eq_def_of_action_value}$ to calculate $q_{\pi_k}(s, a)$ **based on data** (samples or experiences).

This is the key idea of MBRL: **If we don't have a model, we estimate one based on data** (or experience).

## The procedure of Monte Carlo estimation of action values

- Starting from $(s, a)$, following policy $\pi_k$, generate an episode.
- The return of this episode is $g(s, a)$
- $g(s, a)$ is a sample of $G_t$ in
$$
q_{\pi_k}(s, a)=\mathbb{E}\left[G_t \mid S_t=s, A_t=a\right]
$$
Suppose we have a set of episodes and hence $\left\{g^{(j)}(s, a)\right\}$. Then,
$$
q_{\pi_k}(s, a)=\mathbb{E}\left[G_t \mid S_t=s, A_t=a\right] \approx \frac{1}{N} \sum_{i=1}^N g^{(i)}(s, a)
$$

The idea of estimate the mean based on data is called [Monte Carlo estimation](). This is why our method is called "MC (Monte Carlo)" Basic.

# The MC Basic algorithm

The MC Basic algorithm is **exactly the same as the policy iteration algorithm except**: In policy evaluation (PI), **we don't solve $v_{\pi_k}(s)$, instead we estimate $q_{\pi_k}(s, a)$ directly**.

> Question: why we don't compute $v_{\pi_k}(s)$?
>
> Answer: If we calculate the state value in PE, in PI step we still need to calculate activion value. So we can directly calculate activion value in PE.

![Algorithm 5.1: MC Basic (a model-free variant of policy iteration)](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/The%20MC%20Basic%20Algorithm/Algorithm%205.1-%20MC%20Basic%20%28a%20model-free%20variant%20of%20policy%20iteration%29.png)

The MC Basic algorithm is convergent since the policy iteration algorithm (MC Basic is just a variant of it) is convergent.

However, the MC Basic algorithm is not practical due its low data efficiency (we need to calculate $N$ episodes for every $q_{\pi_k}(s, a)$).
