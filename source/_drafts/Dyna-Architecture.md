---
title: Dyna Architecture
tags:
---

Source:

1. [Reinforcement Learning: Part 7: Dyna Algorithm](https://medium.com/@j13mehul/reinforcement-learning-part-7-dyna-algorithm-d2bb7173f865)

# **But where is the model?**

Dyne provides a framework for learning, planning and acting. Let’s understand more about it.

![img](https://miro.medium.com/v2/resize:fit:914/1*8B2Yhz7Z4WMdNcKj9F2WXw.png)

> · Model Learning: The agent uses its interactions with the environment to learn a model that approximates the dynamics of the environment.
>
> · Planning: The agent performs planning using the learned model to  simulate future states and rewards. It uses algorithms, such as DP or MC simulations to update the value function. This allows the agent to  evaluate different actions and refine its policy without preforming that action in the environment.
>
> · Acting: The agent takes actions in the real environment based on its current policy.

The agent interacts with the environment, updates its model, performs  planning using the model, and adjusts its policy based on the learned  values.

Let’s understand the Dyna architecture using its pseudo code.

![img](https://miro.medium.com/v2/resize:fit:664/1*a1ReZc7DyscMyo8nQpWuwg.png)

![img](https://miro.medium.com/v2/resize:fit:1248/1*IjVjJZRr-EX1By57ODmHUQ.png)



**Step 1:** Initialize the state action values and the model (environment dynamics) randomly.

**Step 2: Model Learning (Direct RL):**

· The agent interacts with the environment by selecting actions and observing state transitions and rewards.

· For example, if the agent takes the action ‘right’ from state (1, 1),  it observes that it transitions to state (1, 2) with a reward of 0.

· The agent updates its model based on these observed state transitions and rewards.

**Step 3: Planning:**

Planning has also 3 components:



**Search control:**

· It selects a previously visited state action pair at random

· Let’s say during planning, the agent simulates taking the action ‘up’  from state (2, 2) and observes that it reaches the goal state with a  reward of 1.

![img](https://miro.medium.com/v2/resize:fit:624/1*BJCTB2_838WZnuzTUT9sKg.png)

**Model query:**

· Using the learned model, the agent performs planning to simulate or predict future states and rewards.

![img](https://miro.medium.com/v2/resize:fit:356/1*kyVIkNkL46ogn2ktUnuDQg.png)

**Value updates:**

· Based on this simulated experience, the agent knows the S, A, R, S, A.

· The agent can use an algorithm like MC, TD or DP to update its value function.

![img](https://miro.medium.com/v2/resize:fit:816/1*wmqvD0MDb_CXo7vAAHyjMQ.png)

**Step 4: Acting:**

· The agent selects actions to take in the real environment based on its current policy.

· Initially, the policy might be random or exploratory. As the agent  collects more real experiences and performs planning, it updates its  policy to improve decision-making.

# **Did you Notice?**

**The policy** is being updated during both the phases of direct RL as well as planning.

However, this will fail if the model is not static, meaning the state action rewards are changing with time.

# **Dyna Q+ is the solution**

It will update the rewards based on time. If the state was visited by the  agent long back. It will increase the reward (by the square root of the  time step) which will motivate the agent to visit the state again.

![img](https://miro.medium.com/v2/resize:fit:474/1*hUI6GUcIyF-jDts3xyZcIA.png)

Where Tau is the time steps since the transition was last visited and K is  the constant to control the amount of weight we want to give. If K is 0, then Dyna Q+ is simple Dyna Q.
