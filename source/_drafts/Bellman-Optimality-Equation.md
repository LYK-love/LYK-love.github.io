---
title: Bellman Optimality Equation
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
---

1. [Shiyu Zhao. *Chapter 3: Optimal State Values and Bellman Optimality Equation*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning).
2. [--> Youtube: Bellman Optimality Equation](https://youtu.be/_QbIzluF8YI?si=9izFpm0dn82yp2yS)

<!--more-->

# Optimal Policy

The [state value]() could be used to evaluate if a policy is good or not: if
$$
v_{\pi_1}(s) \geq v_{\pi_2}(s) \quad \text { for all } s \in \mathcal{S}
$$
then $\pi_1$ is "better" than $\pi_2$.
Definition
A policy $\pi^*$ is optimal if $v_{\pi^*}(s) \geq v_\pi(s)$ for all $s$ and for any other policy
$\pi$.

The definition leads to many questions:
- Does the optimal policy exist?
- Is the optimal policy unique?
- Is the optimal policy stochastic or deterministic?
- How to obtain the optimal policy?

To answer these questions, we study the Bellman optimality equation.
