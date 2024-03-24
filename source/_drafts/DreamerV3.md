---
title: DreamerV3
tags:
  - Machine Learning
categories:
  - Research
---



Source:

1. Papers:

   1. [RSSM](https://arxiv.org/pdf/1811.04551.pdf)

   1. [DreamerV1](https://arxiv.org/abs/1912.01603)
   2. [DreamerV2](https://arxiv.org/abs/2010.02193)
   3. [DreamerV3](https://arxiv.org/abs/2301.04104)

2. Blogs:

   1. [EclecticSheep: Dreamer V1](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html)
   2. [EclecticSheep: Dreamer V2](https://eclecticsheep.ai/2023/07/06/dreamer_v2.html)
   3. [EclecticSheep: Dreamer V3](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html)
   4. [EclecticSheep: a2c algorithm](https://eclecticsheep.ai/2023/12/14/intro-rl.html)

<!--more-->





# Notations

In this article, we follow these notations:

1. The stochastic state of Dreamer(V1,V2,V3) is denoted as $s_t$ or $z_t$ interchangeably.
2. $\hat s_t$ or $\hat z_t$ represents the stochastic state predicted by the transition model.
3. By default, $s_t$ or $z_t$ represents the stochastic state predicted by the representation model.
4. The latent state of Dreamer(V1,V2,V3) is the <u>concatenation</u> of $h_t$ and $z_t$.
5. The representation model and the transition model both compute the (**normal**) distribution of the stochastic state.
   * representation model: $p$, posterior
   * transition model: $q$, prior
   * the stochastic states are sampled through the corresponding distributions.

# DreamerV3

It's highly recommended to follow this reading sequence to fully understand DreamerV3:

1. [RSSM](https://arxiv.org/pdf/1811.04551.pdf)

2. [DreamerV1](https://arxiv.org/abs/1912.01603)
3. [DreamerV2](https://arxiv.org/abs/2010.02193)
4. [DreamerV3](https://arxiv.org/abs/2301.04104)

The reason is that, the later paper assumes you are already familiar with the knowledge from the previous papers, and therefore, it **omits those descriptions**. This leads to a situation where those who have not read the previous works cannot understand the subsequent ones. If you have not read RSSM, DreamerV1,  and DreamerV2, then reading DreamerV3 would be very confusing.

# RSSM

![image-20240225121511259](/Users/lyk/Library/Application Support/typora-user-images/image-20240225121511259.png)

In this example, the model observes the first two time steps and predicts the third. 

<u>Circles</u> represent **stochastic** variables and <u>squares</u> **deterministic** variables. 

Solid lines denote the generative process and dashed lines the inference model. 

* (a) Transitions in a recurrent neural network are <u>purely deterministic</u>. This prevents the model from capturing multiple futures and makes it easy for the planner to exploit inaccuracies. 
* (b) Transitions in a state-space model are purely stochastic. This makes it <u>difficult to remember information</u> over multiple time steps. 
* (c) The author uses RSSM to **split the state into stochastic and deterministic parts**, allowing the model to robustly learn to predict multiple futures.

# Algorithm

The training alrotithm of DreamerV1 proposed in the [paper](https://arxiv.org/abs/1912.01603) is:

![image-20240225122007862](/Users/lyk/Library/Application Support/typora-user-images/image-20240225122007862.png)

Baically, all three papers (DreamerV1, V2, V3) follows this algorithm. The only modification is in DreamerV3, where it changes a little bit "Behavior learning" process by removing the vlue model $v_\psi\left(s_t\right)$.

There're 4 stages in this algorithm:

1. Experience collection
2. Dynamic learning. This is the process of traing the world model.
3. Behavior learning. This is the process of training the agent's policy with the help of world model.
   * The world model is **fixed** while learning behaviors.
4. Environment iteraction: Basically, this process is used to use the learned policy to **collect more data** to add to the dataset.

As you may think, the most important stages are "Dynamic learning" and "Behavior learning".

## Experience collection

Experience collection: The world model is trained from the agent's **growing**  dataset of past experience that contains sequences of **images $x_{1: T}$, actions $a_{1: T}$, rewards $r_{1: T}$, and discount factors $\gamma_{1: T}$ (or continuation flags $c_{1: T}$)**.

* What does a growing dataset mean? 

  Since the agent may not initially visit all parts of the environment, we need to **iteratively collect new experience and refine the dynamics model**. We do so by planning with the partially trained model, as shown in Algorithm 1. Starting from a small amount of $S$ seed episodes collected under random actions, we train the model and **add one additional episode to the data set every $C$ update steps.** 

  When collecting episodes for the data set, we **add small Gaussian exploration noise to the action**. To reduce the planning horizon and provide a clearer learning signal to the model, we repeat each action $R$ times, as common in reinforcement learning (Mnih et al., 2015; 2016).

## Dynamic learning

![image-20240225123812315](/Users/lyk/Library/Application Support/typora-user-images/image-20240225123812315.png)

Figure 2: World Model Learning. The training sequence of images $x_t$ is encoded using the CNN. The RSSM uses a sequence of deterministic recurrent states $h_t$. At each step, it computes a posterior stochastic state $z_t$ that incorporates information about the current image $x_t$, as well as a prior stochastic state $\hat{z}_t$ that tries to predict the posterior without access to the current image. 



The <u>concatenation</u> of $h_t$ and $z_t$ forms the model state (or **latent state**),

```python
latent_states = torch.cat((posteriors.view(*posteriors.shape[:-2], -1), recurrent_states), -1)
```





from which we:

1. predict rewards $r_t$
2. predict episode continuation flags $c_t \in\{0,1\}$
3. use decoder to get the reconstructed image $\hat x$


$$
\operatorname{RSSM} 
\begin{cases}
\text { Sequence model: } & h_t=f_\phi\left(h_{t-1}, z_{t-1}, a_{t-1}\right) \\ \text { Encoder: } & z_t \sim q_\phi\left(z_t \mid h_t, x_t\right) 
\\ 
\text { Dynamics predictor: } & \hat{z}_t \sim p_\phi\left(\hat{z}_t \mid h_t\right) 
\end{cases}
\\ 
\text { Reward predictor: } & \hat{r}_t \sim p_\phi\left(\hat{r}_t \mid h_t, z_t\right) 
\\ 
\text { Continue predictor: } & \hat{c}_t \sim p_\phi\left(\hat{c}_t \mid h_t, z_t\right) 
\\ 
\text { Decoder: } & \hat{x}_t \sim p_\phi\left(\hat{x}_t \mid h_t, z_t\right)
$$

We use $p$ for distributions that generate samples in the real environment and $q$ for their approximations that enable latent imagination.

* Note that starting from DreamerV2, the stochastic state is a vector of multiple **categorical**, instead of continuous, variables.
* The learned prior is used for imagination, as shown in Figure 3. 
* The KL loss both trains the prior and regularizes how much information the posterior incorporates from the image. The regularization increases robustness to novel inputs. It also encourages reusing existing information from past steps to predict rewards and reconstruct images, thus learning long-term dependencies.








## Behavior learning

![image-20240225124214149](/Users/lyk/Library/Application Support/typora-user-images/image-20240225124214149.png)

As you can see from the figure, during the behavior learning process we don't use the decoder, only encoder is used.

Figure 3: Actor Critic Learning. The world model learned in Figure 2 is used for learning a policy from trajectories imagined in the compact latent space. 

**The <u>trajectories start from prior states computed during model training (representation model)</u> and predict forward by sampling actions from the actor network.** The critic network predicts the expected sum of future rewards for each state. The critic uses temporal difference learning on the imagined rewards. The actor is trained to maximize the critic prediction, via reinforce gradients, straight-through gradients of the world model, or a combination of them.





# Loss

## KL balancing

During the dynamic learning phase, i.e. the one in which the world model is learned, the prior distribution over the latent states, estimated by the transition model, and the posterior one, estimated by the representation model, are learned so to minimize their KL divergence:
$$
\begin{aligned}
\mathrm{KL}(P \| Q) & =\int_{\mathcal{X}} p(x) \log \left(\frac{p(x)}{q(x)}\right) d x \\
& =\int_{\mathcal{X}} p(x) \log (p(x)) d x-\int_{\mathcal{X}} p(x) \log (q(x)) d x \\
& =\mathrm{H}(P, Q)-\mathrm{H}(P)
\end{aligned}
$$
where $P, Q, \mathrm{H}(P, Q)$ and $\mathrm{H}(P)$ are the posterior and prior distributions, the cross-entropy between the posterior and the prior and the entropy of the posterior distribution respectively. The KL loss serves two purposes: it trains the prior toward the representations, and it regularizes the representations toward the prior. However, since learning the prior is difficult, we want to avoid regularizing the representations toward a poorly trained prior. To overcome this issue, the divergence between the posterior and the prior is replaced with the following:
$$
\alpha \mathrm{KL}(\operatorname{sg}(P) \| Q)+(1-\alpha) \mathrm{KL}(P \| \operatorname{sg}(Q))
$$
with $\alpha=0.8$ and sg stands for "stop-gradient" (. $\operatorname{detach}($ ) on a PyTorch tensor). By scaling up the prior cross entropy relative to the posterior entropy, the world model is encouraged to minimize the KL by improving its prior dynamics toward the more informed posteriors, as opposed to reducing the KL by increasing the posterior entropy.



## DreamerV1 dynamic loss

```python
				# posterior_dist is "ground truth"
        kl_divergence_loss = torch.mean(
            torch.distributions.kl.kl_divergence(posterior_dist, prior_dist)
        )
        
        # Here we also used a "free nats" trick to truncate the very low loss.
        # This trick is not in DreamerV1, but in V3.
        kl_divergence_loss = torch.max(
            torch.tensor(self.config.free_nats).to(self.device), kl_divergence_loss
        )
        model_loss = (
            self.config.kl_divergence_scale * kl_divergence_loss
            - reconstruction_observation_loss.mean()
            - reward_loss.mean()
        )
        if self.config.use_continue_flag:
            model_loss += continue_loss.mean()
```

The dynamic loss / reconstruction loss / world model loss:


$$
\text { rec loss }=\mathrm{KL}(p \| q)-\ln q_o(o)-\ln q_r(r)+\operatorname{BCE}(\hat{d},(1-d) * \gamma)
$$

Where:

* $p$ and $q$ are the posterior and prior, respectively.
* $q_o$: the normal distribution predicted by the observation model (We takes their mean)
* $q_r$: the normal distribution predicted by the reward model (We takes their mean)
* $q_c$: the logits of the Bernoulli distribution predicted by the continue model (We takes their mean)
* $\hat{d} \sim q_c$, and $d$ are the dones received by the environment.
* The [KL balancing]() (in Modified KL divergence. Bascally it's about clipping and weighting) is applied to the `KL()`.
* SInce the items on the right are all distris, we have to compute their mean to get the final scalar loss.



KL(p || q):

```
kl_loss = dyn_loss + repr_loss
```



After that we multiply it with "kl_regularizer", which is 1.

```
kl_loss = kl_regularizer * kl_loss
```



The final loss is:

```
reconstruction_loss = (kl_regularizer * kl_loss + observation_loss + reward_loss + continue_loss).mean()
```



return:

```python
return (
        reconstruction_loss,
        kl.mean(),
        kl_loss.mean(),
        reward_loss.mean(),
        observation_loss.mean(),
        continue_loss.mean(),
    )
```



## DreamerV3 loss



![image-20240225124413062](/Users/lyk/Library/Application Support/typora-user-images/image-20240225124413062.png)

Figure 3: Training process of DreamerV3. The world model encodes sensory inputs into a discrete representation $z_t$ that is predicted by a sequence model with recurrent state $h_t$ given actions $a_t$. The inputs are reconstructed as learning signal to shape the representations. The actor and critic learn from trajectories of abstract representations predicted by the world model.



The DreamerV3 algorithm consists of 3 neural networks—the world model, the critic, and the actor—that are trained concurrently from replayed experience without sharing gradients, as shown in Figure 3.



The world model parameters $\phi$ are optimized end-to-end to minimize the prediction loss $\mathcal{L}_{\text {pred }}$, the dynamics loss $\mathcal{L}_{\text {dyn }}$, and the representation loss $\mathcal{L}_{\text {rep }}$ with corresponding loss weights $\beta_{\text {pred }}=1, \beta_{\text {dyn }}=0.5, \beta_{\text {rep }}=0.1$ :
$$
\mathcal{L}(\phi) \doteq \mathrm{E}_{q_\phi}\left[\sum_{t=1}^T\left(\beta_{\text {pred }} \mathcal{L}_{\text {pred }}(\phi)+\beta_{\text {dyn }} \mathcal{L}_{\text {dyn }}(\phi)+\beta_{\text {rep }} \mathcal{L}_{\text {rep }}(\phi)\right)\right]
$$

* The **prediction loss** trains <u>the decoder and reward predictor</u> via the symlog loss and the continue predictor via binary classification loss. 

* The **dynamics loss** trains the <u>sequence model</u> to predict the next representation by minimizing the KL divergence between the prior $p_\phi\left(z_t \mid h_t\right)$ and the posterior n $q_\phi\left(z_t \mid h_t, x_t\right)$. 

* The **representation loss** trains the <u>representations</u> to become more predictable if the dynamics cannot predict their distribution, allowing us to use a factorized dynamics predictor for fast sampling when training the actor critic. The two losses differ in the stop-gradient operator $\operatorname{sg}(\cdot)$ and their loss scale. 

  To avoid a degenerate solution where the dynamics are trivial to predict but contain not enough information about the inputs, we employ free bits by clipping the dynamics and representation losses below the value of 1 nat $\approx 1.44$ bits. This disables them while they are already minimized well to focus the world model on its prediction loss:

$$
\begin{aligned}
\mathcal{L}_{\text {pred }}(\phi) & \doteq-\ln p_\phi\left(x_t \mid z_t, h_t\right)-\ln p_\phi\left(r_t \mid z_t, h_t\right)-\ln p_\phi\left(c_t \mid z_t, h_t\right) \\
\mathcal{L}_{\text {dyn }}(\phi) & \doteq \max \left(1, \operatorname{KL}\left[\operatorname{sg}\left(q_\phi\left(z_t \mid h_t, x_t\right)\right) \| p_\phi\left(z_t \mid h_t\right)\right]\right) \\
\mathcal{L}_{\text {rep }}(\phi) & \doteq \max \left(1, \operatorname{KL}\left[\quad q_\phi\left(z_t \mid h_t, x_t\right) \| \operatorname{sg}\left(p_\phi\left(z_t \mid h_t\right)\right)\right]\right)
\end{aligned}
$$

# World model

The world model of DreamerV3 is composed by five parts. 

1. An image **encoder**, that is a fully convolutional neural network, encodes the pixel-based observations provided by the environment.
2. An **RSSM** (Recurrent State-Space Model) which generates the latent states, and it is composed by three models:
   1. The **recurrent model**: a linear layer followed by an ELU activation function and a GRU, that encodes the history of the  episode and computes the recurrent state.
   2. The **representation model**: an MLP, that computes the stochastic state from the recurrent state and the actual observations.
   3. The **transition model**: an MLP, that predicts the stochastic state given only the recurrent state, it is used to imagine  trajectories in the latent dynamic.
3. An **observation model (image decoder)** consisting of a linear layer followed by a convolutional neural network with transposed convolutions; this <u>reconstructs</u> the original  observation from the latent state. 
4. A **reward model** (MLP) predicts the reward for a given latent state. Finally, 
5. An optional **continue model** (MLP) predicts the *continues* (whether or not the episode continues)

## Encoder

```python
cnn_stages = int(np.log2(cfg.env.screen_size) - np.log2(4))
    cnn_encoder = (
        CNNEncoder(
            keys=cfg.algo.cnn_keys.encoder,
            input_channels=[int(np.prod(obs_space[k].shape[:-2])) for k in cfg.algo.cnn_keys.encoder],
            image_size=obs_space[cfg.algo.cnn_keys.encoder[0]].shape[-2:],
            channels_multiplier=world_model_cfg.encoder.cnn_channels_multiplier,
            layer_norm=world_model_cfg.encoder.layer_norm,
            activation=eval(world_model_cfg.encoder.cnn_act),
            stages=cnn_stages,
        )
        if cfg.algo.cnn_keys.encoder is not None and len(cfg.algo.cnn_keys.encoder) > 0
        else None
    )
    mlp_encoder = (
        MLPEncoder(
            keys=cfg.algo.mlp_keys.encoder,
            input_dims=[obs_space[k].shape[0] for k in cfg.algo.mlp_keys.encoder],
            mlp_layers=world_model_cfg.encoder.mlp_layers,
            dense_units=world_model_cfg.encoder.dense_units,
            activation=eval(world_model_cfg.encoder.dense_act),
            layer_norm=world_model_cfg.encoder.layer_norm,
        )
        if cfg.algo.mlp_keys.encoder is not None and len(cfg.algo.mlp_keys.encoder) > 0
        else None
    )


    encoder = MultiEncoder(cnn_encoder, mlp_encoder)
```

## RSSM

<p align="center">
  <img src="https://eclecticsheep.ai/assets/images/dreamer_v1/recurrent_model.png" alt="The recurrent model" width="30%" />
  <img src="https://eclecticsheep.ai/assets/images/dreamer_v1/representation_model.png" alt="The representation model" width="30%" />
  <img src="https://eclecticsheep.ai/assets/images/dreamer_v1/transition_model.png" alt="The transition model" width="20%" />
</p>
The recurrent model tries to encode the consequences of the performed action
$$
a_{t-1}, s_{t-1}, h_{t-1} \rightarrow h_{t}
$$
In the implementation, $s_{t-1}, a_{t-1}$ are concatenated together.



The representation model and the transition model both compute the distribution of the stochastic state ( $p$ and , respectively)



The representation model uses recurrent state and the observation (encoded by the  encoder) to compute the <u>distribution</u> of the stochastic state, called the **posterior**.
$$
h_{t}, o_{t} \rightarrow s_{t}
$$
Note: In the implementation, $h_t, o_t$ are concatenated together:

```yaml
transition_model : 
                hidden_size : 200
                num_layers : 2
                activation : ELU
                min_std : 0.1

            representation_model:
                hidden_size : 200
                num_layers : 2
                activation : ELU
                min_std : 0.1
```

```python
def forward(self, embedded_observation, deterministic):

        x = self.network(torch.cat((embedded_observation, deterministic), 1)) # contatenation
        posterior_dist = create_normal_dist(x, min_std=self.config.min_std)
        posterior = posterior_dist.rsample()
        return posterior_dist, posterior
```






1. The transition model only uses the recurrent state to compute the distribution of the stochastic state, called the **prior**
   $$
   h_{t} \rightarrow \hat s_{t}
   $$

   ```python
       def _transition(self, recurrent_out: Tensor) -> Tuple[Tuple[Tensor, Tensor], Tensor]:
           """Predict the prior state (Transition Model).
   
           Args:
               recurrent_out (Tensor): the output of the recurrent model, i.e., the deterministic part of the latent space.
   
           Returns:
               The predicted mean and the standard deviation of the distribution of the prior state (Tensor, Tensor).
               The prior state (Tensor): the sampled prior state predicted by the transition model.
           """
           prior_mean_std = self.transition_model(recurrent_out)
           return compute_stochastic_state(
               prior_mean_std, event_shape=1, min_std=self.min_std, validate_args=self.distribution_cfg.validate_args
           )
   ```

   

<img src="https://eclecticsheep.ai/assets/images/dreamer_v1/rssm.png" alt="img" style="zoom: 33%;" />

```python
    def dynamic(
        self,
        posterior: Tensor,
        recurrent_state: Tensor,
        action: Tensor,
        embedded_obs: Tensor,
    ) -> Tuple[Tensor, Tensor, Tensor, Tuple[Tensor, Tensor], Tuple[Tensor, Tensor]]:
        """
        Perform one step of the dynamic learning:
            Recurrent model: compute the recurrent state from the previous latent space, the action taken by the agent,
                i.e., it computes the deterministic state (or ht).
            Transition model: predict the prior state from the recurrent output.
            Representation model: compute the posterior state from the recurrent state and from
                the embedded observations provided by the environment.
        For more information see [https://arxiv.org/abs/1811.04551](https://arxiv.org/abs/1811.04551)
        and [https://arxiv.org/abs/1912.01603](https://arxiv.org/abs/1912.01603).

        Args:
            posterior (Tensor): the posterior state.
            recurrent_state (Tensor): a tuple representing the recurrent state of the recurrent model.
            action (Tensor): the action taken by the agent.
            embedded_obs (Tensor): the embedded observations provided by the environment.

        Returns:
            The recurrent state (Tensor): the recurrent state of the recurrent model.
            The posterior state (Tensor): computed by the representation model
            from the recurrent state and the embedded observation.
            The prior state (Tensor): computed by the transition model from the recurrent state
            and the embedded observation.
            The posterior mean and std (Tuple[Tensor, Tensor]): the posterior mean and std of
            the distribution of the posterior state.
            The prior mean and std (Tuple[Tensor, Tensor]): the predicted mean and std of
            the distribution of the prior state.
        """
        recurrent_out, recurrent_state = self.recurrent_model(torch.cat((posterior, action), -1), recurrent_state)
        prior_state_mean_std, prior = self._transition(recurrent_out)
        posterior_mean_std, posterior = self._representation(recurrent_state, embedded_obs)
        return recurrent_state, posterior, prior, posterior_mean_std, prior_state_mean_std
```





One-step imagination:

```python
    def imagination(self, prior: Tensor, recurrent_state: Tensor, actions: Tensor) -> Tuple[Tensor, Tensor]:
        """
        One-step imagination of the next latent state, using the recurrent model and the transition model.
        The results are the prior state ($\hat s_t$) and the recurrent state ($h_t$).
        It can be used several times to imagine trajectories in the latent space (Transition Model).

        Args:
            prior (Tensor): the prior state.
            recurrent_state (Tensor): the recurrent state of the recurrent model.
            actions (Tensor): the actions taken by the agent.

        Returns:
            The imagined prior state (Tuple[Tensor, Tensor]): the imagined prior state.
            The recurrent state (Tensor).
        """
        recurrent_state = self.recurrent_model(torch.cat((prior, actions), -1), recurrent_state)
        _, imagined_prior = self._transition(recurrent_state)
        return imagined_prior, recurrent_state
```



## Decoder



# Dynamic learning

After computing all the latent states in the batch, the next steps involve learning to <u>reconstruct the original observations and predict rewards, as well as computing the probability of episode continuation from the computed latent states</u>. 

The world model loss, also known as the **reconstruction loss**, is computed as follows:

$$
\text{rec loss} = \mathcal{L}_{\mathrm{KL}}(p \Vert q) - \ln q_o(o) - \ln q_r(r) + \text{BCE}(\hat{d}, d) .
$$

* $p$: the posterior distribution of the stochastic state, predicted by the representation model

* $q$: the prior distribution of the stochastic state, predicted by the transition model

* $q_r$: the mean predictions for the reward normal distribution, predicted by the reward model

* $q_o$: the mean predictions for the observation normal distribution, predicted by the observation model

* $q_c$: logits of a Bernoulli distribution, predicted by the continue model. This is <u>compared with the real information provided by the environment</u>. 



```python
# kl_regularizer == 1
reconstruction_loss = (kl_regularizer * kl_loss + observation_loss + reward_loss + continue_loss).mean()
```



## Modified KL divergence

Note that the KL divergence here is modified to
$$
\mathcal{L}_{\mathrm{KL}}(\phi) \doteq 0.5 \cdot \mathcal{L}_{\mathrm{dyn}}(\phi)+0.1 \cdot \mathcal{L}_{\mathrm{rep}}(\phi)
$$
with two parts:

1. The transition loss is the follwing: $\mathcal{L}_{\text {dyn }}(\phi) \doteq \max (1, \mathrm{KL}(\operatorname{sg}(p) \| q))$
2. The representation loss is the following: $\mathcal{L}_{\text {rep }}(\phi) \doteq \max (1, \mathrm{KL}(p \| \operatorname{sg}(q)))$





Reason:

Why two parts?

Since, 3D domains may contain unnecessary details whereas in 2D domains the background is often static and each pixel could be important for solving the task, the KL loss was slightly modified.



Why scaling ? 

To have a good balance between complex and very detailed environments (e.g, 3D envs) and simpler and less detailed environments (e.g., static 2D envs), the two losses are scaled differently and summed together.



What is this 1 here?

**1 is the free bits** used to clip the dynamic and representation losses below of the free bits, necessary to avoid degenerate solutions where the dynamics are trivial to predict, but do not contain enough information about the inputs.



## Modified categorical distributions

![img](https://eclecticsheep.ai/assets/images/dreamer_v2/dreamer-v2-arch.png)

Every latent variable of the environment is a **discrete** state as a mixture of 32 categoricals with 32 classes each.



Meanwhile, to prevent spikes in the KL loss, the **categorical distributions** (the one for discrete actions and the one for the posteriors/priors) are parametrized as mixtures of $1 \%$ uniform and $99 \%$ neural network output. This avoid the distributions to become near deterministic. To implement the uniform mix, we applied the uniform mix function to the logits returned by the neural networks.

```python
import torch
from torch import Tensor
from torch.distributions.utils import probs_to_logits

def uniform_mix(self, logits: Tensor, unimix: float = 0.01) -> Tensor:
    if unimix > 0.0:
        # compute probs from the logits
        probs = logits.softmax(dim=-1)
        # compute uniform probs
        uniform = torch.ones_like(probs) / probs.shape[-1]
        # mix the NN probs with the uniform probs
        probs = (1 - unimix) * probs + unimix * uniform
        # compute the new logits
        logits = probs_to_logits(probs)
    return logits
```

// In sheeprl, I can see only the actor uses this.

#### Symlog predictions

![img](https://eclecticsheep.ai/assets/images/dreamer_v3/symlog.png)

To solve this issue caused by the varying scales of inputs, rewards and values, Hafner et al. propose to use **symlog predictions**, 
$$
\operatorname{sym} \log (x) \doteq \operatorname{sign}(x) \ln (|x|+1) .
$$
After convert $x$ into a symlog, we can recover it via the inverse function
$$
\operatorname{symexp}(x) \doteq \operatorname{sign}(x)(\exp (|x|)-1) .
$$
However, in practice, Hafner used a neural network $f(x, \theta)$, with inputs $x$ and parameters $\theta$ to learn the symblog fucntion. The loss fcuntion of this NN is
$$
\mathcal{L}(\theta) \doteq \frac{1}{2}(f(x, \theta)-\operatorname{symlog}(y))^2
$$

$$

$$

The last detail to report is that the symlog prediction is used in the decoder, the reward model and the critic. Moreover, the inputs of the MLP encoder (the one that encodes observations in vector form) are squashed with the symlog function (Figure 2).

# Behavior learning

After completing the dynamic learning phase, the next step is to learn  the actor and critic using the learned world model. The objective is to  use the world model to imagine the consequences of actions. 

1. The first step: The first latent state $s_t$ is computed **from the representation model, and continues for a certain number of imagination  steps (horizon).** 
2. After that, during the following steps, the imagined trajectory is denoted as $\hat s_t$ and is computed by the **transition model** because the environment observations are not available during imagination. Additionally, imagining in the  latent space is faster and more cost-effective than doing so in the  image space, making the transition model more convenient.

During each step, the agent takes an action selected by the actor in [Figure 3](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-actor), which is based on **the current latent state** ($z_0$ or $z_t$ where $t > 0$, predicted by the transition model) and the recurrent state. Then the agent computes the next latent state using the world model.

<img src="https://eclecticsheep.ai/assets/images/dreamer_v1/actor.png" alt="Figure 3: How the actor works. It selects the action from the lantent state (recurrent and stochastic state)." style="zoom: 50%;" />







To sum up, the process of imagining trajectories, as shown in the [Figure 4](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-imagine), involves the recurrent and transition models of the RSSM, and the actor.

<img src="https://eclecticsheep.ai/assets/images/dreamer_v1/imagination.png" alt="Figure 4: Imagination phase. The actor, the recurrent and the transition models iteratively perform the imagination steps. The actor comptes the next actions, then the recurrent model encodes this information in the  recurrent state. Finally the transition model predicts the stochastic  state." style="zoom:50%;" />



All the latent states computed in the previous phase (dynamic learning) serve as **starting points for fully imagined trajectories.** Consequently, the latent states are reshaped to consider each computed latent state  independently. A *for loop* is necessary for behavior learning, as trajectories are imagined one step at a time. 



From the imagined trajectories, the **critic** ([Figure 5](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-critic)), reward model, and continue model predict values, rewards, and continue  probabilities, respectively. These predicted quantities are used to  compute the lambda values (TD()), which serve as target values for actor and critic losses.

<img src="https://eclecticsheep.ai/assets/images/dreamer_v1/critic.png" alt="Figure 5: How the critic works. It estimates the state value from the lantent state (recurrent and stochastic state)." style="zoom:50%;" />

An important consideration is the composition of the imagined trajectories. The starting latent state computed by the representation model (from the recurrent state and embedded observations) must be excluded from the trajectory because it is not consistent with the rest of the trajectory. This was one of the initial challenges faced during the implementation of Dreamer, and without this adjustment, the agent would not converge.



When computing the lambda values, the last element in the trajectory is "lost" because the next value is needed to calculate the $\operatorname{TD}(\lambda)$, but the last imagined state does not have a next value. Moreover, according to the DreamerV1 paper, the lambda targets are weighted by the cumulative product of predicted discount factors $(\gamma)$, estimated by the continue model. This weighting downweights terms based on the likelihood of the imagined trajectory ending. This crucial detail, necessary for convergence. These weighted lambda targets are used in the actor loss as part of the update process. Instead, the critic predicts the distribution of the values $\left(q_v\right)$ without the last element of the imagined trajectory and then it is compared with the lambda values. The actor and critic losses are computed as follows:
$$
\begin{gathered}
\text { policy loss }=-\boldsymbol{\gamma} \cdot \mathbf{T D}(\boldsymbol{\lambda}) \\
\text { value loss }=-\boldsymbol{\gamma} \cdot \ln q_v(\mathbf{T D}(\boldsymbol{\lambda}))
\end{gathered}
$$

## Actor

The actor () of Dreamer supports both continuous and discrete control. 

For  continuous actions, it:

1. First, the actor outputs the mean and standard deviation of the actions. 

2. The mean is scaled by a factor of 5, and the standard deviation is processed using a [SoftPlus](https://pytorch.org/docs/stable/generated/torch.nn.Softplus.html) function to ensure non-negative values. 

3. The formulas for calculating  the mean and standard deviation are
   $$
   \begin{gathered}
   \mu_a=5 \cdot \tanh \left(\mu_\phi / 5\right) \\ 
   \sigma_a=\operatorname{softplus}\left(\sigma_\phi+\chi\right)+5
   \end{gathered}
   $$
   Where $\chi=\ln e^{5-1}$ is the <u>raw init std value</u> and $\mu_\phi$ and $\sigma_\phi$ are the mean and standard deviation computed by the actor.

   ```python
   mean = mean / mean_scale
   if activation:
   	man = activation(mean)
   mean = mean_scale * mean # 5 * tanh (\mu / 5)
   std = F.softplus(std + init_std) + min_std
   ```
   
   
   
4. At last, it outputs the distribution of rhe actions as $\mathcal N(\mu_\phi, \sigma ^ 2 _\phi)$.



For discrete actions, no transformations are applied to the  model output, which serves as the logits of a one-hot categorical  distribution.



```python
out: Tensor = self.model(state)
        pre_dist: List[Tensor] = [head(out) for head in self.mlp_heads]
        if self.is_continuous:
            # # For continuous actions, it outputs the mean and standard deviation of the actions.
            mean, std = torch.chunk(pre_dist[0], 2, -1)
            if self.distribution == "tanh_normal":

                
                # The mean is scaled by a factor of 5, and the standard deviation is processed using a SoftPlus function to ensure non-negative values.
                mean = 5 * torch.tanh(mean / 5)
                std = F.softplus(std + self.init_std) + self.min_std

                actions_dist = Normal(mean, std)
                actions_dist = Independent(
                    TransformedDistribution(
                        actions_dist, TanhTransform(), validate_args=self.distribution_cfg.validate_args
                    ),
                    1,
                    validate_args=self.distribution_cfg.validate_args,
                )
            elif self.distribution == "normal":
                actions_dist = Normal(mean, std, validate_args=self.distribution_cfg.validate_args)
                actions_dist = Independent(actions_dist, 1, validate_args=self.distribution_cfg.validate_args)
            elif self.distribution == "trunc_normal":
                std = 2 * torch.sigmoid((std + self.init_std) / 2) + self.min_std
                dist = TruncatedNormal(torch.tanh(mean), std, -1, 1, validate_args=self.distribution_cfg.validate_args)
                actions_dist = Independent(dist, 1, validate_args=self.distribution_cfg.validate_args)
            if is_training:
                actions = actions_dist.rsample()
            else:
                sample = actions_dist.sample((100,))
                log_prob = actions_dist.log_prob(sample)
                actions = sample[log_prob.argmax(0)].view(1, 1, -1)
            actions = [actions]
            actions_dist = [actions_dist]
        else:
            actions_dist: List[Distribution] = []
            actions: List[Tensor] = []
            for logits in pre_dist:
                actions_dist.append(
                    OneHotCategoricalStraightThroughValidateArgs(
                        logits=self._uniform_mix(logits), validate_args=self.distribution_cfg.validate_args
                    )
                )
                if is_training:
                    actions.append(actions_dist[-1].rsample())
                else:
                    actions.append(actions_dist[-1].mode)
        return tuple(actions), tuple(actions_dist)
```



# Others





## Hyperparameters



The used activation function is the [SiLU](https://pytorch.org/docs/stable/generated/torch.nn.SiLU.html).

 Moreover, all the models use the [LayerNorm](https://pytorch.org/docs/stable/generated/torch.nn.LayerNorm.html?highlight=layernorm#torch.nn.LayerNorm) on the last dimension, except for the convolutional layers that apply the *layer norm* only on the channels dimension. 

The last detail is the presence of the bias in the models, in particular, all the layers followed by a *LayerNorm* are instantiated without the bias.

We used the same weight initialization of the models: all the models are initialized with a [xavier normal](https://pytorch.org/docs/stable/nn.init.html?highlight=xavier+normal+init#torch.nn.init.xavier_normal_) initialization [[4\]](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html#ref-4), except for the heads of the actor, the last layer of the transition,  representation, continue and encoder models that are initialized with a [xavier uniform](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html) initialization [[4\]](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html#ref-4) and the last layer of the critic and the reward model that are initialized with all zeros (to speed up the convergence).

### Batch size

"We draw batches of 50 sequences of length 50 to train the world model, value model, and action model models using Adam" --- [DreamerV1](https://arxiv.org/abs/1912.01603)

In this phase the agent learns a latent representation of the  environment from **a batch of sequences**, The key component of the world  model is the RSSM.

In Dreamer V1, we have

```yaml
  per_rank_batch_size: 50
  per_rank_sequence_length: 50
```



In DreamerV3, we have:

```yaml
  per_rank_batch_size: 16
  per_rank_sequence_length: 64
```

16 batches, each batch has 64 sequences (a video of len=64)



## Critic learning

Another difference is that the critc learn the twohot-encoded symlog-transformed returns, to be able to predict the expected value of a widespread return distribution. So, the symlog-transformed returns are discretized into a sequence of $K=255$ equally spaced buckets, whereas the critc outputs a softmax distribution over the buckets.

The twohot encoding is defined as follows:
$$
\operatorname{twohot}(x)_i \doteq \begin{cases}\left|b_{k+1}-x\right| /\left|b_{k+1}-b_k\right| & \text { if } i=k \\ \left|b_k-x\right| /\left|b_{k+1}-b_k\right| & \text { if } i=k+1 \\ 0 & \text { otherwise }\end{cases}
$$

Where $x$ is the input to encode, $i$ is the index of the twohot, $b_k$ is the value of the $k$-th bucket and $k=\sum_{j=1}^B \delta\left(b_j<x\right)$.

In this way a nuber $x$ is represented by a vector of $K$ numbers, all set to zero except for the two positions corresponding to the two buckets among which is situated $x$. For instance, if you have 5 buckets which equally divide the range $[0,10]$ (i.e., the 5 buckets are: $[0,2.5,5,7.5,10]$ ) and you have to represent the number $x=5.5$, then its two hot encoding is the following:
$$
\text { twohot }(5.5)=[0,0,0.8,0.2,0]
$$

Because 5.5 is closer to bucket 5 than bucket 7.5.

## Train ratio

The training ratio is the **ratio of replayed steps to environment steps**. The model sizes are detailed in Table B.1. Higher training ratios result in substantially improved data-efficiency. 



