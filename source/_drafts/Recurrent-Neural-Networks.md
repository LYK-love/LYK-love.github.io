---
title: Recurrent Neural Networks
tags:
---

Source:

1. [Stanford CS231n, Lecture 10](https://youtu.be/6niqTuYFZLQ?si=znUm_UX-goFLdJPz)
   * [Slides](http://cs231n.stanford.edu/slides/2017/cs231n_2017_lecture10.pdf)
2. [StatQuest: RNNs](https://www.youtube.com/watch?v=AsNTP8Kwu80)



## RNN

- RNNs allow a lot of flexibility in architecture design

- Vanilla RNNs are simple but don’t work very well

- Common to use LSTM or GRU: their additive interactions
  improve gradient flow

- Backward flow of gradients in RNN can explode or vanish. 

- Exploding is controlled with gradient clipping. 

- Vanishing is controlled with additive interactions (LSTM)



# LSTM

![image-20240203222012661](/Users/lyk/Library/Application Support/typora-user-images/image-20240203222012661.png)
$$
\left(\begin{array}{c}i \\ f \\ o \\ g\end{array}\right)=\left(\begin{array}{c}\sigma \\ \sigma \\ \sigma \\ \tanh \end{array}\right) W\left(\begin{array}{c}h_{t-1} \\ x_t\end{array}\right)
$$


and
$$
\begin{aligned} 
c_t & =f \odot c_{t-1}+i \odot g 
\\
h_t & =o \odot \tanh \left(c_t\right)
\end{aligned}
$$

## Gradient flow

![image-20240203222213431](/Users/lyk/Library/Application Support/typora-user-images/image-20240203222213431.png)

Backpropagation from $c_t$ to $c_{t-1}$ only elementwise multiplication by $\mathrm{f}$, no matrix multiply by $\mathrm{W}$

![image-20240203222243010](/Users/lyk/Library/Application Support/typora-user-images/image-20240203222243010.png)

# Other RNN Variants

## GRU

[Learning phrase representations using rnn encoder-decoder for statistical machine translation, Cho et al. 2014]
$$
\begin{aligned}
r_t & =\sigma\left(W_{x r} x_t+W_{h r} h_{t-1}+b_r\right) \\
z_t & =\sigma\left(W_{x z} x_t+W_{h z} h_{t-1}+b_z\right) \\
\tilde{h}_t & =\tanh \left(W_{x h} x_t+W_{h h}\left(r_t \odot h_{t-1}\right)+b_h\right) \\
h_t & =z_t \odot h_{t-1}+\left(1-z_t\right) \odot \tilde{h}_t
\end{aligned}
$$
