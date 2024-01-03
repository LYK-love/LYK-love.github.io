---
title: Bellman Equation
tags:
  - Machine Learning
  - Reinforcement Learning
categories: Computer Science
mathjax: true
date: 2024-01-03 13:35:01
---


Source:

1. [*Shiyu Zhao. *[Chapter 2: State Values and Bellman Equation. Mathematical Foundations of Reinforcement Learning](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning)*.*](https://github.com/MathFoundationRL/Book-Mathmatical-Foundation-of-Reinforcement-Learning)
2. [--> Youtube: Bellman Equation: Derivation](https://youtu.be/Su9PPdoxvtQ?si=JdeBKeeZ9PEBKDVH)

<!--more-->

# Bellman Equation

Given a policy, finding out the corresponding state values is called **policy evaluation**. This is through solving an equation called <u>the Bellman equation</u>.

Consider a random trajectory:
$$
S_t \xrightarrow{A_t} R_{t+1}, S_{t+1} \stackrel{A_{t+1}}{\longrightarrow} R_{t+2}, S_{t+2} \stackrel{A_{t+2}}{\longrightarrow} R_{t+3}, \ldots
$$

The (discounted)[^1] return $G_t$ can be written as
$$
\begin{aligned}
G_t & =R_{t+1}+\gamma R_{t+2}+\gamma^2 R_{t+3}+\ldots \\
& =R_{t+1}+\gamma\left(R_{t+2}+\gamma R_{t+3}+\ldots\right) \\
& =R_{t+1}+\gamma G_{t+1}
\end{aligned}
$$

Recalling that the definition of the state value is
$$
\begin{equation} \label{eq_state_value_function}
v_\pi(s)  =\mathbb{E}\left[G_t \mid S_t=s\right]
\end{equation}
$$
Substitute $G(t) = R_{t+1}+\gamma G_{t+1}$ into $\eqref{eq_state_value_function}$:
$$
\begin{aligned} \label{eq_derivation_of_state_value_function}
v_\pi(s) & =\mathbb{E}\left[G_t \mid S_t=s\right] \\
& =\mathbb{E}\left[R_{t+1}+\gamma G_{t+1} \mid S_t=s\right] \\
& =\mathbb{E}\left[R_{t+1} \mid S_t=s\right]+\gamma \mathbb{E}\left[G_{t+1} \mid S_t=s\right]
\end{aligned}
$$

Next calculate the two terms of the last line, respectively.

## First term: the mean of immediate rewards

First, calculate the first term $\mathbb{E}\left[R_{t+1} \mid S_t=s\right]$ :
$$
\begin{aligned}
\mathbb{E}\left[R_{t+1} \mid S_t=s\right] & =\sum_a \pi(a \mid s) \mathbb{E}\left[R_{t+1} \mid S_t=s, A_t=a\right] \\
& =\sum_a \pi(a \mid s) \sum_r p(r \mid s, a) r
\end{aligned}
$$

Note that
- This is the mean of immediate rewards

## Second term: the mean of future rewards

Second, calculate the second term $\mathbb{E}\left[G_{t+1} \mid S_t=s\right]$ :
$$
\begin{aligned}
\mathbb{E}\left[G_{t+1} \mid S_t=s\right] & =\sum_{s^{\prime}} \mathbb{E}\left[G_{t+1} \mid S_t=s, S_{t+1}=s^{\prime}\right] p\left(s^{\prime} \mid s\right) \\
& =\sum_{s^{\prime}} \mathbb{E}\left[G_{t+1} \mid S_{t+1}=s^{\prime}\right] p\left(s^{\prime} \mid s\right) \\
& =\sum_{s^{\prime}} v_\pi\left(s^{\prime}\right) p\left(s^{\prime} \mid s\right) \\
& =\sum_{s^{\prime}} v_\pi\left(s^{\prime}\right) \sum_a p\left(s^{\prime} \mid s, a\right) \pi(a \mid s)
\end{aligned}
$$

Note that
- This is the mean of future rewards
- $\mathbb{E}\left[G_{t+1} \mid S_t=s, S_{t+1}=s^{\prime}\right]=\mathbb{E}\left[G_{t+1} \mid S_{t+1}=s^{\prime}\right]$ due to the memoryless Markov property.

## Result formula

Therefore, we have
$$
\begin{align}
\underbrace{v_\pi(s)} & =\mathbb{E}\left[R_{t+1} \mid S_t=s\right]+\gamma \mathbb{E}\left[G_{t+1} \mid S_t=s\right], \nonumber \\

& =\underbrace{\sum_a \pi(a \mid s) \sum_r p(r \mid s, a) r}_{\text {mean of immediate rewards }}+\underbrace{\gamma \sum_{s^{\prime}} \pi(a \mid s) \sum_a p\left(s^{\prime} \mid s, a\right) v_\pi\left(s^{\prime}\right),}_{\text {mean of future rewards }} \nonumber \\

& =\sum_a \pi(a \mid s)\left[\sum_r p(r \mid s, a) r+\gamma \sum_{s^{\prime}} p\left(s^{\prime} \mid s, a\right) v_\pi\left(s^{\prime}\right)\right], \quad \forall s \in \mathcal{S} \label{eq_Bellman_equation} .
\end{align}
$$

Highlights:

- The above equation is called the **Bellman equation**, which characterizes the relationship among the state-value functions of different states.
- It consists of two terms: 
  1. First term: the mean of immediate rewards
  2. Second term: the mean of future rewards
- The above elementwise form is valid for every state $s \in \mathcal{S}$. That means there are $|\mathcal{S}|$ equations like this!

# Examples

## For deterministic policy

![Figure 2.4: An example for demonstrating the Bellman equation. The policy in this example is deter- ministic.](/Users/lyk/Library/Application Support/typora-user-images/image-20240103131942992.png)

Consider the first example shown in Figure 2.4, where the policy is deterministic. We next write out the Bellman equation and then solve the state values from it.

First, consider state $s_1$. Under the policy, the probabilities of taking the actions are $\pi\left(a=a_3 \mid s_1\right)=1$ and $\pi\left(a \neq a_3 \mid s_1\right)=0$. The state transition probabilities are $p\left(s^{\prime}=s_3 \mid s_1, a_3\right)=1$ and $p\left(s^{\prime} \neq s_3 \mid s_1, a_3\right)=0$. The reward probabilities are $p\left(r=0 \mid s_1, a_3\right)=1$ and $p\left(r \neq 0 \mid s_1, a_3\right)=0$. Substituting these values into (2.7) gives
$$
v_\pi\left(s_1\right)=0+\gamma v_\pi\left(s_3\right)
$$

Interestingly, although the expression of the Bellman equation in (2.7) seems complex, the expression for this specific state is very simple.

Similarly, it can be obtained that
$$
\begin{aligned}
& v_\pi\left(s_2\right)=1+\gamma v_\pi\left(s_4\right), \\
& v_\pi\left(s_3\right)=1+\gamma v_\pi\left(s_4\right), \\
& v_\pi\left(s_4\right)=1+\gamma v_\pi\left(s_4\right) .
\end{aligned}
$$

We can solve the state values from these equations. Since the equations are simple, we can manually solve them. More complicated equations can be solved by the algorithms presented in Section 2.7. Here, the state values can be solved as
$$
\begin{aligned}
& v_\pi\left(s_4\right)=\frac{1}{1-\gamma}, \\
& v_\pi\left(s_3\right)=\frac{1}{1-\gamma}, \\
& v_\pi\left(s_2\right)=\frac{1}{1-\gamma}, \\
& v_\pi\left(s_1\right)=\frac{\gamma}{1-\gamma} .
\end{aligned}
$$
Furthermore, if we set $\gamma=0.9$, then
$$
\begin{aligned}
& v_\pi\left(s_4\right)=\frac{1}{1-0.9}=10, \\
& v_\pi\left(s_3\right)=\frac{1}{1-0.9}=10, \\
& v_\pi\left(s_2\right)=\frac{1}{1-0.9}=10, \\
& v_\pi\left(s_1\right)=\frac{0.9}{1-0.9}=9 .
\end{aligned}
$$

## For stochastic policy

![Figure 2.5: An example for demonstrating the Bellman equation. The policy in this example is stochastic.](/Users/lyk/Library/Application Support/typora-user-images/image-20240103134129310.png)

Consider the second example shown in Figure 2.5, where the policy is stochastic. We next write out the Bellman equation and then solve the state values from it.

At state $s_1$, the probabilities of going right and down equal 0.5 . Mathematically, we have $\pi\left(a=a_2 \mid s_1\right)=0.5$ and $\pi\left(a=a_3 \mid s_1\right)=0.5$. The state transition probability is deterministic since $p\left(s^{\prime}=s_3 \mid s_1, a_3\right)=1$ and $p\left(s^{\prime}=s_2 \mid s_1, a_2\right)=1$. The reward probability is also deterministic since $p\left(r=0 \mid s_1, a_3\right)=1$ and $p\left(r=-1 \mid s_1, a_2\right)=1$. Substituting these values into (2.7) gives
$$
v_\pi\left(s_1\right)=0.5\left[0+\gamma v_\pi\left(s_3\right)\right]+0.5\left[-1+\gamma v_\pi\left(s_2\right)\right]
$$

Similarly, it can be obtained that
$$
\begin{aligned}
& v_\pi\left(s_2\right)=1+\gamma v_\pi\left(s_4\right), \\
& v_\pi\left(s_3\right)=1+\gamma v_\pi\left(s_4\right), \\
& v_\pi\left(s_4\right)=1+\gamma v_\pi\left(s_4\right) .
\end{aligned}
$$

The state values can be solved from the above equations. Since the equations are

simple, we can solve the state values manually and obtain
$$
\begin{aligned}
v_\pi\left(s_4\right) & =\frac{1}{1-\gamma}, \\
v_\pi\left(s_3\right) & =\frac{1}{1-\gamma}, \\
v_\pi\left(s_2\right) & =\frac{1}{1-\gamma}, \\
v_\pi\left(s_1\right) & =0.5\left[0+\gamma v_\pi\left(s_3\right)\right]+0.5\left[-1+\gamma v_\pi\left(s_2\right)\right], \\
& =-0.5+\frac{\gamma}{1-\gamma} .
\end{aligned}
$$

Furthermore, if we set $\gamma=0.9$, then
$$
\begin{aligned}
& v_\pi\left(s_4\right)=10, \\
& v_\pi\left(s_3\right)=10, \\
& v_\pi\left(s_2\right)=10, \\
& v_\pi\left(s_1\right)=-0.5+9=8.5 .
\end{aligned}
$$


[^1]: In this article we only deal with discounted return witout the loss of generality since we can simply trate undiscounted return as discounted-return's special case when $\gamma = 1$.
