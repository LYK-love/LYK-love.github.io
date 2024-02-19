---
title: DreamerV3
tags:
  - Machine Learning
categories:
  - Research
---



Source:

1. [EclecticSheep: Dreamer V1](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html)
2. [EclecticSheep: Dreamer V2](https://eclecticsheep.ai/2023/07/06/dreamer_v2.html)
3. [EclecticSheep: Dreamer V3](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html)
4. [EclecticSheep: a2c algorithm](https://eclecticsheep.ai/2023/12/14/intro-rl.html)
5. RSSM
6. [DreamerV2](https://arxiv.org/abs/2010.02193)
7. [DreamerV3](https://arxiv.org/abs/2301.04104)

<!--more-->

# World model

The world model of DreamerV3 is composed by five parts. 

1. An image **encoder**, that is a fully convolutional neural network, encodes the pixel-based observations provided by the environment.
2. An **RSSM** (Recurrent State-Space Model) which generates the latent states, and it is composed by three models:
   1. The **recurrent model**: a linear layer followed by  an ELU activation function and a GRU, that encodes the history of the  episode and computes the recurrent state.
   2. The **representation model**: an MLP, that computes the stochastic state from the recurrent state and the actual observations.
   3. The **transition model**: an MLP, that predicts the  stochastic state given only the recurrent state, it is used to imagine  trajectories in the latent dynamic.
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

1. The recurrent model tries to encode the consequences of the performed action, so what is happening. 
   $$
   a_{t-1}, s_{t-1}, h_{t-1} \rightarrow h_{t}
   $$
   Note: In the implementation, $s_{t-1}, a_{t-1}$ are concatenated together.

   
   
2. The representation model uses recurrent state and the observation (encoded by the  encoder) to compute the distribution of the stochastic state, called the **posterior**.
   $$
   h_{t}, o_{t} \rightarrow s_{t}
   $$
   Note: In the implementation, $h_t, o_t$ are concatenated together:

   ```python
       def _representation(self, recurrent_state: Tensor, embedded_obs: Tensor) -> Tuple[Tuple[Tensor, Tensor], Tensor]:
           """Compute the distribution of the posterior state.
   
           Args:
               recurrent_state (Tensor): the recurrent state of the recurrent model, i.e.,
                   what is called h or deterministic state in
                   [https://arxiv.org/abs/1811.04551](https://arxiv.org/abs/1811.04551).
               embedded_obs (Tensor): the embedded real observations provided by the environment.
   
           Returns:
               posterior_mean_std (Tensor, Tensor): the mean and the standard deviation
               of the distribution of the posterior state.
               posterior (Tensor): the sampled posterior.
           """
           posterior_mean_std, posterior = compute_stochastic_state(
               self.representation_model(torch.cat((recurrent_state, embedded_obs), -1)), # Concatenating all the features for every datapoint
               event_shape=1,
               min_std=self.min_std,
               validate_args=self.distribution_cfg.validate_args,
           )
           return posterior_mean_std, posterior
   ```

   

3. The transition model only uses the recurrent state to compute the distribution of the stochastic state, called the **prior**
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

1 is the free bits used to clip the dynamic and representation losses below of the free bits, necessary to avoid degenerate solutions where the dynamics are trivial to predict, but do not contain enough information about the inputs.



## Modified categorical distributions

![img](https://eclecticsheep.ai/assets/images/dreamer_v2/dreamer-v2-arch.png)

Every latent variable of the environment is a **discrete** state as a mixture of 32 categoricals with 32 classes each.



Meanwhile, to prevent spikes in the KL loss, the categorical distributions (the one for discrete actions and the one for the posteriors/priors) are parametrized as mixtures of $1 \%$ uniform and $99 \%$ neural network output. This avoid the distributions to become near deterministic. To implement the uniform mix, we applied the uniform mix function to the logits returned by the neural networks.

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

1. The first step: The first latent state $s_t$ is computed **from the  representation model, and continues for a certain number of imagination  steps (horizon).** 
2. After that, during the following steps, the imagined trajectory is denoted as $\hat s_t$ and is computed by the **transition model** because the environment observations are not available during imagination. Additionally, imagining in the  latent space is faster and more cost-effective than doing so in the  image space, making the transition model more convenient.

During each step, the agent takes an action selected by the actor in [Figure 3](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-actor), which is based on  the current latent state ($z_0$ or $z_t$ where $t > 0$). Then the agent computes the next latent state using the world model.

![Figure 3: How the actor works. It selects the action from the lantent state (recurrent and stochastic state).](https://eclecticsheep.ai/assets/images/dreamer_v1/actor.png)



To sum up, the process of imagining trajectories, as shown in the [Figure 4](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-imagine), involves the recurrent and transition models of the RSSM, and the actor.

![Figure 4: Imagination phase. The actor, the recurrent and the transition models iteratively perform the imagination steps. The actor comptes the next actions, then the recurrent model encodes this information in the  recurrent state. Finally the transition model predicts the stochastic  state.](https://eclecticsheep.ai/assets/images/dreamer_v1/imagination.png)



All the latent states computed in the previous phase (dynamic learning)  serve as starting points for fully imagined trajectories. Consequently,  the latent states are reshaped to consider each computed latent state  independently. A *for loop* is necessary for behavior learning,  as trajectories are imagined one step at a time. The actor selects an  action based on the last imagined state, and the new imagined latent  state is computed.
 From the imagined trajectories, the critic ([Figure 5](https://eclecticsheep.ai/2023/06/16/dreamer_v1.html#fig-critic)), reward model, and continue model predict values, rewards, and continue  probabilities, respectively. These predicted quantities are used to  compute the lambda values (TD()), which serve as target values for actor and critic losses.

![Figure 5: How the critic works. It estimates the state value from the lantent state (recurrent and stochastic state).](https://eclecticsheep.ai/assets/images/dreamer_v1/critic.png)

An important consideration is the composition of the imagined trajectories. The starting latent state computed by the representation model (from the recurrent state and embedded observations) must be excluded from the trajectory because it is not consistent with the rest of the trajectory. This was one of the initial challenges faced during the implementation of Dreamer, and without this adjustment, the agent would not converge.

When computing the lambda values, the last element in the trajectory is "lost" because the next value is needed to calculate the $\operatorname{TD}(\lambda)$, but the last imagined state does not have a next value. Moreover, according to the DreamerV1 paper, the lambda targets are weighted by the cumulative product of predicted discount factors $(\gamma)$, estimated by the continue model. This weighting downweights terms based on the likelihood of the imagined trajectory ending. This crucial detail, necessary for convergence. These weighted lambda targets are used in the actor loss as part of the update process. Instead, the critic predicts the distribution of the values $\left(q_v\right)$ without the last element of the imagined trajectory and then it is compared with the lambda values. The actor and critic losses are computed as follows:
$$
\begin{gathered}
\text { policy loss }=-\boldsymbol{\gamma} \cdot \mathbf{T D}(\boldsymbol{\lambda}) \\
\text { value loss }=-\boldsymbol{\gamma} \cdot \ln q_v(\mathbf{T D}(\boldsymbol{\lambda}))
\end{gathered}
$$

# Others

The used activation function is the [SiLU](https://pytorch.org/docs/stable/generated/torch.nn.SiLU.html).

 Moreover, all the models use the [LayerNorm](https://pytorch.org/docs/stable/generated/torch.nn.LayerNorm.html?highlight=layernorm#torch.nn.LayerNorm) on the last dimension, except for the convolutional layers that apply the *layer norm* only on the channels dimension. 

The last detail is the presence of the bias in the models, in particular, all the layers followed by a *LayerNorm* are instantiated without the bias.

We used the same weight initialization of the models: all the models are initialized with a [xavier normal](https://pytorch.org/docs/stable/nn.init.html?highlight=xavier+normal+init#torch.nn.init.xavier_normal_) initialization [[4\]](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html#ref-4), except for the heads of the actor, the last layer of the transition,  representation, continue and encoder models that are initialized with a [xavier uniform](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html) initialization [[4\]](https://eclecticsheep.ai/2023/08/10/dreamer_v3.html#ref-4) and the last layer of the critic and the reward model that are initialized with all zeros (to speed up the convergence).







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





