---
title: Key Concepts in Reinforcement Learning
tags:
- Machine Learning
- Reinforcement Learning
categories: Computer Science
mathjax: true
---

# Markov decision processes

This section presents the basic RL concepts in a more formal way under the framework of Markov decision processes (MDPs).

An MDP is a general framework for describing stochastic dynamical systems. The key ingredients of an MDP are listed below.

## Sets

Sets:

- State space: the set of all states, denoted as $\mathcal{S}$.
- Action space: a set of actions, denoted as $\mathcal{A}(s)$, associated with each state $s \in \mathcal{S}$.
- **Reward set**: a set of rewards, denoted as $\mathcal{R}(s, a)$, associated with each state-action pair $(s, a)$.



The state, action, reward at time index $t$ are denoted as $s_t, a_t, r_t$ separately.

The reward depends on the sate and action, but <u>not the next state</u>.

## Model

Model:

- **State transition probability**: At state $s$, when taking action $a$, the probability of transitioning to state $s^{\prime}$ is $p\left(s^{\prime} \mid s, a\right)$. It holds that $\sum_{s^{\prime} \in \mathcal{S}} p\left(s^{\prime} \mid s, a\right)=1$ for any $(s, a)$.
- **Reward probability**: At state $s$, when taking action $a$, the probability of obtaining reward $r$ is $p(r \mid s, a)$. It holds that $\sum_{r \in \mathcal{R}(s, a)} p(r \mid s, a)=1$ for any $(s, a)$.

## Policy

Policy: At state $s$, the probability of choosing action $a$ is $\pi(a \mid s)$. It holds that $\sum_{a \in \mathcal{A}(s)} \pi(a \mid s)=1$ for any $s \in \mathcal{S}$.

A policy can be deterministic or stochastic.

* A **deterministic** policy is usually denoted by $\mu$ :
  $$
  a_t=\mu\left(s_t\right) .
  $$

* A **stochastic** policy is usually denoted by $\pi$ :
  $$
  a_t \sim \pi\left(\cdot \mid s_t\right) .
  $$
  In this case, at state $s$, the probability of choosing action $a$ is $\pi(a \mid s)$. It holds that $\sum_{a \in \mathcal{A}(s)} \pi(a \mid s)=1$ for any $s \in \mathcal{S}$.

In RL, the policies are often **parameterized**, the parameters are commonly denoted as $\theta$ or ![\phi](https://spinningup.openai.com/en/latest/_images/math/3b22abcadf8773922f8db80011611bad8123a783.svg) and are written as a subscript on the policy symbol:

![a_t &= \mu_{\theta}(s_t) \\ a_t &\sim \pi_{\theta}(\cdot | s_t).](https://spinningup.openai.com/en/latest/_images/math/831f731859658682b2af7e217a76648697c9de46.svg)



## Markov property

Markov property:

The name Markov Decision Process refers to the fact that the system obeys the [Markov property](), the memoryless property of a stochastic process. 

Mathematically, it means that

1. The state is markovian:
   $$
   p(s_{t+1} \mid s_t, s_{t-1}, \cdots, s_0)=p(s_{t+1} \mid s_t)
   $$
   
2. The state transition is markovian:
   $$
   p\left(s_{t+1} \mid s_t, a_t, s_{t-1}, a_{t-1}, \ldots, s_0, a_0\right)=p\left(s_{t+1} \mid s_t, a_t\right)
   $$
   
3. The action itself doesn't have markov property, but it's defined to only rely on current state and policy $a_t \sim \pi\left(\cdot \mid s_t\right)$,
   $$
   p(a_{t+1}|s_{t+1}) = p(a_{t+1}|s_{t+1}, s_t, \cdots, s_0) .
   $$
   $a_t$ doesn't depends on $s_{t-1}, s_{t-2}, \cdots$.

4. The reward $r_{t+1}$ itself doesn't have markov property, but it's defined to only rely on $s_t, a_t$:
   $$
   p\left(r_{t+1} \mid s_t, a_t, s_{t-1}, a_{t-1}, \ldots, s_0, a_0\right)=p\left(r_{t+1} \mid s_t, a_t\right).
   $$
   

$t$ represents the current time step and $t+1$ represents the next time step. 

Here, $p\left(s^{\prime} \mid s, a\right)$ and $p(r \mid s, a)$ for all $(s, a)$ are called the **model or dynamics**. The model can be either stationary or nonstationary (or in other words, time-invariant or time-variant). A stationary model does not change over time; a nonstationary model may vary over time. For instance, in the grid world example, if a forbidden area may pop up or disappear sometimes, the model is nonstationary. Unless specifically stated, <u>we only consider consider stationary models</u>.

# States and Observations

* A **state** $s$ is a complete description of the state of the world. There is no  information about the world which is hidden from the state. 
* An **observation** $o$ is a partial description of a state, which may omit information.

* The environment is **fully observed** when the agent is able to observe the complete state of the environment.
* The environment is **partially observed** when the agent can only see a partial observation.



Reinforcement learning notation sometimes puts the symbol for state, ![s](https://spinningup.openai.com/en/latest/_images/math/96ac51b9afe79581e48f2f3f0ad3faa0f4402cc7.svg), in places where it would be technically more appropriate to write the symbol for observation, ![o](https://spinningup.openai.com/en/latest/_images/math/ca2d5053d03bd8fd9f399e5afbb834202e2d2f2d.svg). 

Specifically, this happens when talking about how the agent decides an  action: we often signal in notation that the action is conditioned on the state, when in practice, <u>the action is conditioned on the observation because the agent does not have access to the state</u>.

In our guide, we’ll follow standard conventions for  notation, but it should be clear from context which is meant. If  something is unclear, though, please raise an issue! Our goal is to  teach, not to confuse.

# Actions

Different environments allow different kinds of actions. The set of  all valid actions in a given environment is often called the **action space**. Some environments, like Atari and Go, have **discrete action spaces**, where only a finite number of moves are available to the agent. Other  environments, like where the agent controls a robot in a physical world, have **continuous action spaces**. In continuous spaces, actions are real-valued vectors.

This distinction has some quite-profound consequences for methods in  deep RL. Some families of algorithms can only be directly applied in one case, and would have to be substantially reworked for the other.

# Policies

A policy is a rule used by an agent to decide what actions to take. 



# Trajectories

![Figure 1.6: Trajectories obtained by following two policies. The trajectories are indicated by red dashed lines.](/Users/lyk/Library/Application Support/typora-user-images/image-20240103140901269.png)



A **trajectory** $\tau$ is a state-action chain $\tau = (s_1, a_1, s_2, a_2, ...)$.

## Return

For example, given the policy shown in Figure 1.6(a), if the agent can move along a trajectory as follows:
$$
s_1 \underset{r=0}{\stackrel{a_2}{\longrightarrow}} s_2 \underset{r=0}{\stackrel{a_3}{\longrightarrow}} s_5 \underset{r=0}{\stackrel{a_3}{\longrightarrow}} s_8 \underset{r=1}{\stackrel{a_2}{\longrightarrow}} s_9 .
$$

The **return** <u>of this trajectory</u> is defined as the sum of all the rewards collected along the trajectory:
$$
\text { return }=0+0+0+1=1 .
$$
Returns are also called total *rewards* or *cumulative rewards*.

**Note**: Sometimes we define the return function (or rewards function) with symbol $R$. Thus, the return of trajectory $\tau$ is
$$
R({\tau}).
$$
This is different from the return function $G_t$ defined in t

## Epsisodes

When interacting with the environment by following a policy, the agent may <u>stop at some terminal states</u>. In this case, the resulting trajectory is <u>finite</u>, and is called an **episode** (or a **trial**, **rollout**).

However, some tasks may have no terminal states. In this case, the resulting trajectory is <u>infinite</u>.

Tasks with episodes are called <u>episodic tasks</u>. Tasks are called <u>continuing tasks</u>.



In fact, we can treat episodic and continuing tasks in a unified mathematical manner by converting episodic tasks to continuing ones. We have two options:

1. First, if we treat the terminal state as a special state, we can specifically design its action space or state transition so that the agent stays in this state forever. Such states are called absorbing states, meaning that the agent never leaves a state once reached.
2. Second, if we treat the terminal state as a normal state, we can simply set its action space to the same as the other states, and the agent may leave the state and come back again. Since a positive reward of $r=1$ can be obtained every time $s_9$ is reached, the agent will eventually learn to stay at $s_9$ forever to collect more rewards.

In this document, we consider the second scenario where the target state is treated as a normal state whose action space is $\mathcal{A}\left(s_9\right)=\left\{a_1, \ldots, a_5\right\}$.



# The RL Problem

The goal in RL is to select a policy which maximizes **expected return** when the agent acts according to it.

To talk about expected return, we first have to talk about probability distributions over trajectories.

Let’s suppose that both the environment transitions and the policy are stochastic. In this case, the probability of a $T$-step trajectory is:
$$
P(\tau|\pi) = \rho_0 (s_0) \prod_{t=0}^{T-1} P(s_{t+1} | s_t, a_t) \pi(a_t | s_t).
$$


The expected return (for whichever measure), denoted by ![J(\pi)](https://spinningup.openai.com/en/latest/_images/math/89397c4cc47a40c3466507e1330dc380458f762e.svg), is then:
$$
J(\pi) = \int_{\tau} P(\tau|\pi) R(\tau) = {\mathrm E}_{\tau\sim \pi}{R(\tau)}.
$$


The central optimization problem in RL can then be expressed by
$$
\pi^* = \arg \max_{\pi} J(\pi),
$$
with ![\pi^*](https://spinningup.openai.com/en/latest/_images/math/1fbf259ac070c92161e32b93c0f64705a8f18f0a.svg) being the **optimal policy**.

# Value Functions

It's often useful to know the value of a state, or state-action pair. By value, we mean the expected return if you start in that state or state-action pair, and then act according to a particular policy forever after. Value functions are used, one way or another, in almost every RL algorithm.

There are four main functions of note here.
1. The On-Policy Value Function, $V^\pi(s)$, which gives the expected return if you start in state $s$ and always act according to policy $\pi$ :
$$
V^\pi(s)=\underset{\tau \sim \pi}{\mathrm{E}}\left[R(\tau) \mid s_0=s\right]
$$
2. The On-Policy Action-Value Function, $Q^\pi(s, a)$, which gives the expected return if you start in state $s$, take an arbitrary action $a$ (which may not have come from the policy), and then forever after act according to policy $\pi$ :
$$
Q^\pi(s, a)=\underset{\tau \sim \pi}{\mathrm{E}}\left[R(\tau) \mid s_0=s, a_0=a\right]
$$
3. The Optimal Value Function, $V^*(s)$, which gives the expected return if you start in state $s$ and always act according to the optimal policy in the environment:
$$
V^*(s)=\max _\pi \underset{\tau \sim \pi}{\mathrm{E}}\left[R(\tau) \mid s_0=s\right]
$$
4. The Optimal Action-Value Function, $Q^*(s, a)$, which gives the expected return if you start in state $s$, take an arbitrary action $a$, and then forever after act according to the optimal policy in the environment:

$$
Q^*(s, a)=\max _\pi \underset{\tau \sim \pi}{\mathrm{E}}\left[R(\tau) \mid s_0=s, a_0=a\right]
$$



There are two key connections between the value function and the action-value function that come up pretty often:

![V^{\pi}(s) = \underE{a\sim \pi}{Q^{\pi}(s,a)},](https://spinningup.openai.com/en/latest/_images/math/5151391b2cd2bfa909a3b5a057b6c93d4191790b.svg)

and

![V^*(s) = \max_a Q^* (s,a).](https://spinningup.openai.com/en/latest/_images/math/4cbd255e1ecc9f7083034be12148e8b98cefc2ee.svg)

These relations follow pretty directly from the definitions just given: can you prove them?



Note:

1. When we talk about value functions, if we do not make reference to time-dependence, we only mean expected **infinite-horizon discounted return**. Value functions for finite-horizon undiscounted return would need to  accept time as an argument. Can you think about why? Hint: what happens  when time’s up?

# The Optimal Q-Function and the Optimal Action

There is an important connection between the optimal action-value function ![Q^*(s,a)](https://spinningup.openai.com/en/latest/_images/math/cbed396f671d6fb54f6df5c044b82ab3f052d63e.svg) and the action selected by the optimal policy. By definition, ![Q^*(s,a)](https://spinningup.openai.com/en/latest/_images/math/cbed396f671d6fb54f6df5c044b82ab3f052d63e.svg) gives the expected return for starting in state ![s](https://spinningup.openai.com/en/latest/_images/math/96ac51b9afe79581e48f2f3f0ad3faa0f4402cc7.svg), taking (arbitrary) action ![a](https://spinningup.openai.com/en/latest/_images/math/76a319586cd215c8f2075b938fc6f6e07c81714b.svg), and then acting according to the optimal policy forever after.

The optimal policy in ![s](https://spinningup.openai.com/en/latest/_images/math/96ac51b9afe79581e48f2f3f0ad3faa0f4402cc7.svg) will select whichever action maximizes the expected return from starting in ![s](https://spinningup.openai.com/en/latest/_images/math/96ac51b9afe79581e48f2f3f0ad3faa0f4402cc7.svg). As a result, if we have ![Q^*](https://spinningup.openai.com/en/latest/_images/math/c2e969d09ae88d847429eac9a8494cc89cabe4bd.svg), we can directly obtain the optimal action, ![a^*(s)](https://spinningup.openai.com/en/latest/_images/math/baf715aa6a295b7b7d85e1e1123552c5ae705756.svg), via

![a^*(s) = \arg \max_a Q^* (s,a).](https://spinningup.openai.com/en/latest/_images/math/42490c4d812c9ca1fc226684577900bc8bdd609b.svg)

Note: there may be multiple actions which maximize ![Q^*(s,a)](https://spinningup.openai.com/en/latest/_images/math/cbed396f671d6fb54f6df5c044b82ab3f052d63e.svg), in which case, all of them are optimal, and the optimal policy may  randomly select any of them. But there is always an optimal policy which deterministically selects an action.

# Bellman Equations

All four of the value functions obey special self-consistency equations called **Bellman equations**. The basic idea behind the Bellman equations is this:

> The value of your starting point is the reward you expect to get from being there, plus the value of wherever you land next.

The Bellman equations for the on-policy value functions are

![\begin{align*} V^{\pi}(s) &= \underE{a \sim \pi \\ s'\sim P}{r(s,a) + \gamma V^{\pi}(s')}, \\ Q^{\pi}(s,a) &= \underE{s'\sim P}{r(s,a) + \gamma \underE{a'\sim \pi}{Q^{\pi}(s',a')}}, \end{align*}](https://spinningup.openai.com/en/latest/_images/math/7e4a2964e190104a669406ca5e1e320a5da8bae0.svg)

where ![s' \sim P](https://spinningup.openai.com/en/latest/_images/math/411171ab57c4bec0d86c9f4b495106ba5d73decc.svg) is shorthand for ![s' \sim P(\cdot |s,a)](https://spinningup.openai.com/en/latest/_images/math/ed45f9d37dbb092727104773ca3a464d46f892b8.svg), indicating that the next state ![s'](https://spinningup.openai.com/en/latest/_images/math/6e85fa05d4954e7c1e8037ee1bd163d15bc2e2d6.svg) is sampled from the environment’s transition rules; ![a \sim \pi](https://spinningup.openai.com/en/latest/_images/math/e87025074e03131c69c6c5758e873a6224ea5d3a.svg) is shorthand for ![a \sim \pi(\cdot|s)](https://spinningup.openai.com/en/latest/_images/math/35c684d9cc672fd0bbacd896f49abdd986f40b02.svg); and ![a' \sim \pi](https://spinningup.openai.com/en/latest/_images/math/b3f46cc6cd6c2fa9068013fafbe1b4b029bb8a58.svg) is shorthand for ![a' \sim \pi(\cdot|s')](https://spinningup.openai.com/en/latest/_images/math/6eb25f9175aa0471d7a7728ab237a92fef5009e9.svg).

The Bellman equations for the optimal value functions are

![\begin{align*} V^*(s) &= \max_a \underE{s'\sim P}{r(s,a) + \gamma V^*(s')}, \\ Q^*(s,a) &= \underE{s'\sim P}{r(s,a) + \gamma \max_{a'} Q^*(s',a')}. \end{align*}](https://spinningup.openai.com/en/latest/_images/math/f8ab9b211bc9bb91cde189360051e3bd1f896afa.svg)

The crucial difference between the Bellman equations for the  on-policy value functions and the optimal value functions, is the  absence or presence of the ![\max](https://spinningup.openai.com/en/latest/_images/math/a52117d0fa54eb8449482447cad9c0ab54c757cc.svg) over actions. 

Its inclusion reflects the fact that whenever the agent  gets to choose its action, in order to act optimally, it has to <u>pick whichever action leads to the highest value</u>.



You Should Know

The term “Bellman backup” comes up quite frequently in  the RL literature. The Bellman backup for a state, or state-action pair, is the right-hand side of the Bellman equation: the  reward-plus-next-value.

# Advantage Functions

Sometimes in RL, we don’t need to describe how good an action is in  an absolute sense, but only how much better it is than others on  average. That is to say, we want to know the relative **advantage** of that action. We make this concept precise with the **advantage function.**

The advantage function ![A^{\pi}(s,a)](https://spinningup.openai.com/en/latest/_images/math/09f82f133e9f89a59ba22266639c4968b5641c28.svg) corresponding to a policy ![\pi](https://spinningup.openai.com/en/latest/_images/math/1ae2bd722da01b3a89ffc139af2437c28364a966.svg) describes how much better it is to take a specific action ![a](https://spinningup.openai.com/en/latest/_images/math/76a319586cd215c8f2075b938fc6f6e07c81714b.svg) in state ![s](https://spinningup.openai.com/en/latest/_images/math/96ac51b9afe79581e48f2f3f0ad3faa0f4402cc7.svg), over randomly selecting an action according to ![\pi(\cdot|s)](https://spinningup.openai.com/en/latest/_images/math/8d2c2c23f74e7a0cf98b0ee1de016825eb50e2d4.svg), assuming you act according to ![\pi](https://spinningup.openai.com/en/latest/_images/math/1ae2bd722da01b3a89ffc139af2437c28364a966.svg) forever after. Mathematically, the advantage function is defined by

![A^{\pi}(s,a) = Q^{\pi}(s,a) - V^{\pi}(s).](https://spinningup.openai.com/en/latest/_images/math/3748974cc061fb4065fa46dd6271395d59f22040.svg)

You Should Know

We’ll discuss this more later, but the advantage function is crucially important to policy gradient methods.

