---
title: Bellman Optimality Equation
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
date: 2024-01-07 21:52:44
---


1. [Shiyu Zhao. *Chapter 3: Optimal State Values and Bellman Optimality Equation*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning).
2. [--> Youtube: Bellman Optimality Equation](https://youtu.be/_QbIzluF8YI?si=9izFpm0dn82yp2yS)

<!--more-->

# Optimal Policy

The [state value](https://lyk-love.cn/2024/01/03/bellman-equation/#state-value) could be used to evaluate if a policy is good or not: if
$$
v_{\pi_1}(s) \geq v_{\pi_2}(s) \quad \text { for all } s \in \mathcal{S}
$$
then $\pi_1$ is "better" than $\pi_2$.

Definition:

A policy $\pi^*$ is **optimal** if $v_{\pi^*}(s) \geq v_\pi(s)$ for all $s$ and for any other policy $\pi$.

The definition leads to many questions:
- Does the optimal policy exist?
- Is the optimal policy unique?
- Is the optimal policy stochastic or deterministic?
- How to obtain the optimal policy?

To answer these questions, we study the *Bellman optimality equation*.

# BOE (elementwise form)

The tool for analyzing optimal policies and optimal state values is the **Bellman optimality equation (BOE)**. By solving this equation, we can obtain optimal policies and optimal state values.

For every $s \in \mathcal{S}$, the elementwise expression of the BOE is
$$
\begin{aligned}
v(s) & =\max _{\pi(s) \in \Pi(s)} \sum_{a \in \mathcal{A}} \pi(a \mid s)\left(\sum_{r \in \mathcal{R}} p(r \mid s, a) r+\gamma \sum_{s^{\prime} \in \mathcal{S}} p\left(s^{\prime} \mid s, a\right) v\left(s^{\prime}\right)\right) \\
& =\max _{\pi(s) \in \Pi(s)} \sum_{a \in \mathcal{A}} \pi(a \mid s) q(s, a),
\end{aligned}
$$
where $v(s), v\left(s^{\prime}\right)$ are unknown variables to be solved and
$$
q(s, a) \doteq \sum_{r \in \mathcal{R}} p(r \mid s, a) r+\gamma \sum_{s^{\prime} \in \mathcal{S}} p\left(s^{\prime} \mid s, a\right) v\left(s^{\prime}\right)
$$

Here, $\pi(s)$ denotes a policy for state $s$, and $\Pi(s)$ is the set of all possible policies for $s$.



Remarks:

$p(r \mid s, a), p\left(s^{\prime} \mid s, a\right)$ are known.

$v(s), v\left(s^{\prime}\right)$ are unknown and to be calculated.

# BOE (matrix-vector form)

The BOE refers to a set of equations defined for all states. If we combine these equations, we can obtain a concise matrix-vector form, which will be extensively used in this chapter.

The matrix-vector form of the BOE is
$$
v=\max _{\pi \in \Pi}\left(r_\pi+\gamma P_\pi v\right)
$$
where $v \in \mathbb{R}^{|\mathcal{S}|}$ and $\max _\pi$ is performed in an elementwise manner. The structures of $r_\pi$ and $P_\pi$ are the same as those in the matrix-vector form of the normal Bellman equation:
$$
\left[r_\pi\right]_s \triangleq \sum_{a \in \mathcal{A}} \pi(a \mid s) \sum_{r \in \mathcal{R}} p(r \mid s, a) r, \quad\left[P_\pi\right]_{s, s^{\prime}}=p\left(s^{\prime} \mid s\right) \triangleq \sum_{a \in \mathcal{A}} \pi(a \mid s) p\left(s^{\prime} \mid s, a\right) .
$$

Since the optimal value of $\pi$ is determined by $v$, the right-hand side of (3.2) is a function of $v$, denoted as
$$
f(v) \doteq \max _{\pi \in \Pi}\left(r_\pi+\gamma P_\pi v\right)
$$

Then, the BOE can be expressed in a concise form as
$$
v=f(v)
$$

Since the matrix-vector form includes all the elementwise forms for different state $s$, **we only need to solve the matrix-vector form of BOE**.
