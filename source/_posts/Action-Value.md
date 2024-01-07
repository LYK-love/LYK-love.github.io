---
title: Action Value
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
date: 2024-01-06 20:05:35
---


Source:

1. [Shiyu Zhao. *Chapter 2: State Values and Bellman Equation. Mathematical Foundations of Reinforcement Learning*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning).
2. [--> Youtube: Bellman Equation: Action Value](https://youtu.be/vfCd-_Yt_Gk?si=7q5Kh1HJ9Hy1kntn)

<!--more-->

# Action Value

From state value to action value:

* State value: the average return the agent can <u>get starting from a state</u>.
* Action value: the average return the agent can <u>get starting from a state and taking an action</u>.

## Definition

Definition of action value (or action value function):
$$
\begin{equation} \label{eq_def_of_action_value}
q_\pi(s, a) \triangleq \mathbb{E}\left[G_t \mid S_t=s, A_t=a\right]
\end{equation}
$$
Note:

1. The $q_\pi(s, a)$ is a function of the state-action pair $(s, a)$.
2. The $q_\pi(s, a)$ depends on $\pi$.

## Relation to the state value function

It follows from the properties of *conditional expectation* that
$$
\underbrace{\mathbb{E}\left[G_t \mid S_t=s\right]}_{v_\pi(s)}=\sum_a \underbrace{\mathbb{E}\left[G_t \mid S_t=s, A_t=a\right]}_{q_\pi(s, a)} \pi(a \mid s)
$$

Hence,
$$
\begin{equation} \label{eq_state_value_and_action_value}
v_\pi(s)=\sum_a \pi(a \mid s) q_\pi(s, a)
\end{equation}
$$


Recall the [Bellman equation](https://lyk-love.cn/2024/01/03/bellman-equation/), that the state value is given by
$$
\begin{equation} \label{eq_Bellman_equation}
v_\pi(s)=\sum_a \pi(a \mid s)[\underbrace{\sum_r p(r \mid s, a) r+\gamma \sum_{s^{\prime}} p\left(s^{\prime} \mid s, a\right) v_\pi\left(s^{\prime}\right)}_{q_\pi(s, a)}]
\end{equation}
$$

By comparing $\eqref{eq_state_value_and_action_value}$ and $\eqref{eq_Bellman_equation}$, we have the action-value function as
$$
\begin{equation} \label{eq_verbose_def_of_action_value}
q_\pi(s, a)=\sum_r p(r \mid s, a) r+\gamma \sum_{s^{\prime}} p\left(s^{\prime} \mid s, a\right) 
v_\pi\left(s^{\prime}\right)
\end{equation}
$$
$\eqref{eq_state_value_and_action_value}$ and $\eqref{eq_verbose_def_of_action_value}$ are the two sides of the same coin:

* $\eqref{eq_state_value_and_action_value}$ shows how to obtain state values from action values.
* $\eqref{eq_verbose_def_of_action_value}$ shows how to obtain action values from state values.

# Example

![Figure 2.8: An example for demonstrating the process of calculating action values.](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Action%20Value/Figure%202.8-%20An%20example%20for%20demonstrating%20the%20process%20of%20calculating%20action%20values.png)

Consider the stochastic policy shown in Figure 2.8. 
$$
q_\pi\left(s_1, a_2\right)=-1+\gamma v_\pi\left(s_2\right)
$$
Note that even if an action would not be selected by a policy, it still has an action value. Therefor, for the other actions:
$$
\begin{aligned}
& q_\pi\left(s_1, a_1\right)=-1+\gamma v_\pi\left(s_1\right), \\
& q_\pi\left(s_1, a_3\right)=0+\gamma v_\pi\left(s_3\right), \\
& q_\pi\left(s_1, a_4\right)=-1+\gamma v_\pi\left(s_1\right), \\
& q_\pi\left(s_1, a_5\right)=0+\gamma v_\pi\left(s_1\right) .
\end{aligned}
$$

# How to calculate action value

* We can first calculate all the state values and then calculate the action values with $\eqref{eq_verbose_def_of_action_value}$.

* We can also directly calculate the action values with or without models (discussed later).
