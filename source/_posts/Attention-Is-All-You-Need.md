---
title: Attention Is All You Need
tags: Machine Learning
categories: Research
mathjax: true
date: 2023-07-12 02:28:06
---




Transformer论文阅读笔记.

Paper name: *[Attention Is All You Need](https://arxiv.org/abs/1706.03762)*

[Code](https://github.com/tensorflow/tensor2tensor)

<!--more-->

# Intro

根据Mu Li的[讲解视频](Transformer论文)做了笔记. 这篇文章写得非常紧凑,用语也十分抽象,看完视频后还是有很多没弄懂.

Transformer采用了注意力机制,因此泛化能力更强,模型更简单,需要设置的参数也更少. 但也意味着Transformer模型需要更大的数据量来训练. 

后续的BERT和GPT基于Transformer都取得了成功. 虽然提出时只被用于文本处理,后面也可以被迁移到image, voice, video, etc...

Transformer的最大贡献就是给ML的诸多领域提供了一个统一的基础架构, 从此从业人员不再需要对每个领域使用其专有的方法. 这也使得ML中一个领域的新技术可以很快地被用于其他领域.

虽然标题为"Attention Is All You Need", 但Transformer的成功不仅仅是因为其注意力机制, 具体因为什么我也不知道.

# Abstract





Transformer论文发布于2017年, 当时只将其用于文本翻译.  当时主流的sequence transduction model是结合了encoder and decoder的CNN/RNN, 并将attention mechanism和encoder & decoder 结合起来.

> The dominant sequence transduction models are based on complex recurrent or convolutional neural networks that include an encoder and a decoder. The best performing models also connect the encoder and decoder through an attention mechanism.



Transformer的创新之处在于其只使用attention mechanism( 加上encoder&decoder), 完全摈弃了CNN/RNN. 

> We propose a new simple network architecture, the Transformer, based solely on attention mechanisms, dispensing with recurrence and convolutions entirely. 

并且其注意力机制用的是"**multi-headed** self-attention"

* RNN的局限: RNN对输入的序列进行计算, 在位置t的状态值$h_t = f(h_{t-1}, \mathrm{sequence[t]})$ .  $\mathrm{sequence[t]}$ 是在位置t输入. 也就是说RNN的当前状态是根据前一个状态和当前位置的输入得到的, 这有两个问题:

  1. 难以并行处理.
  2. 对于较长的序列, 由于内存大小的限制, 无法整个存入内存.

  > Recurrent models typically factor computation along the symbol positions of the input and output sequences. Aligning the positions to steps in computation time, they generate a sequence of hidden states ht, as a function of the previous hidden state ht−1 and the input for position t. This inherently sequential nature precludes parallelization within training examples, which becomes critical at longer sequence lengths, as memory constraints limit batching across examples. 



# Model

![Transformer](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Transformer.png)



Most competitive neural sequence transduction models have an encoder-decoder structure [5, 2, 29]. Here, the encoder maps an input sequence of symbol representations (x1,...,xn) to a sequence of continuous representations z = (z1,...,zn). Given z, the decoder then generates an output sequence (y1, ..., ym) of symbols one element at a time. At each step the model is auto-regressive [9], consuming the previously generated symbols as additional input when generating the next.

## Attention

> An attention function can be described as mapping a query and a set of key-value pairs to an output, where the query, keys, values, and output are all vectors. The output is computed as a weighted sum of the values, where the weight assigned to each value is computed by a compatibility function of the query with the corresponding key.

Attention function的原理很简单: 给定query和key-value pairs. 通过衡量query和key的相似程度来得到每个value的权重, 函数output是所有value的加权和.



Transformer使用了Scaled Dot-Product Attention, 

> We call our particular attention "Scaled Dot-Product Attention" (Figure 2). The input consists of queries and keys of dimension dk, and values of dimension dv. We compute the dot products of theuery with all keys, divide each by values.
>
> dk, and apply a softmax function to obtain the weights on the
>
> In practice, we compute the attention function on a set of queries simultaneously, packed together into a matrix Q. The keys and values are also packed together into matrices K and V . We compute the matrix of outputs as:

$$
\operatorname{Attention}(Q, K, V)=\operatorname{softmax}\left(\frac{Q K^{T}}{\sqrt{d_{k}}}\right) V
$$

Scaled Dot-Product Attention和普通dot product的区别在于用了一个$\sqrt d_k$. 

> We suspect that for large values of $\sqrt d_k$. , the dot products grow large in magnitude, pushing the softmax function into regions where it has extremely small gradients 4. To counteract this effect, we scale the dot products by $\frac 1 {\sqrt d_k}$. 

### Multi-Head Attention

![Multi-Head Attention](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Multi-Head%20Attention.png)

> Instead of performing a single attention function with dmodel-dimensional keys, values and queries, **we found it beneficial to linearly project the queries, keys and values h times with different, learned linear projections to $d_k$, $d_k$ and $d_v$ dimensions, respectively. On each of these projected versions of queries, keys and values we then perform the attention function in parallel, yielding dv -dimensional output values. These are concatenated and once again projected, resulting in the final values, as depicted in Figure 2.**

简单来说多头的注意力就是把数据集拆分成不同的batch并进行注意力计算, 再将不同batch的结果concat起来. 在计算前和concat后分别还要进行一次projection. 每个样本都会:

1. 先linearly project
2. 再进行attention function计算
3. 把结果合并(之前讲的多头注意力机制), 然后project回去.



这样做的作用我没有看懂...

>  Multi-head attention **allows the model to jointly attend to information from different representation subspaces at different positions. With a single attention head, averaging inhibits this.**



Formular:
$$
\mathrm{MultiHead}(Q, K, V)=\mathrm{Concat} (\mathrm{ head }_1, \ldots, \mathrm { head }_h)  W^O
$$

where:
$$
\mathrm{ head }_i=\mathrm{Attention}(Q W_i^Q, K W_i^K, V W_i^V)
$$




Where the projections are parameter matrices $W_i^Q ∈ R^{d_\mathrm{model} \times d_k}$ , $W_i^K ∈ R^{d_\mathrm{model} \times d_k}$ , $W_i^V ∈ R^{d_\mathrm{model} \times d_v}$ and $W_i^O ∈ R^{hd_v \times d_\mathrm{model}}$

> In this work we employ h = 8 parallel attention layers, or heads. For each of these we use $d_k = d_v = d_{model}/h = 64$. Due to the reduced dimension of each head, the total computational cost is similar to that of single-head attention with full dimensionality.





### Applications of Attention in our Model

![Applications of Attention in our Model1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Applications%20of%20Attention%20in%20our%20Model1.png)

在"encoder-decoder attention" layers中, k, v (key, value)都来自encoder的输出, q(query)来自前一层decoder的输出.

> In "encoder-decoder attention" layers, the queries come from the previous decoder layer, and the memory keys and values come from the output of the encoder. 

***





![Applications of Attention in our Model2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Applications%20of%20Attention%20in%20our%20Model2.png)

在 self-attention layer( encoder和decoder都有self-attention layer), 同一个样本被复制为三份, 分别作为key, value和query:

> The encoder contains self-attention layers. In a self-attention layer all of the keys, values and queries come from the same place, in this case, the output of the previous layer in the encoder. Each position in the encoder can attend to all positions in the previous layer of the encoder.

(图上的三个箭头代表同一个样本被复制为三倍)

***



![Applications of Attention in our Model3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Applications%20of%20Attention%20in%20our%20Model3.png)

在decoder的self-attention layer中, 为了保持整个模型的self regressive property(因为之前的attention function会对所有样本进行计算, 得到所有样本的信息), 会对attention function的结果进行一次mask. (这部分我也不明白)

> Similarly, self-attention layers in the decoder allow each position in the decoder to attend to all positions in the decoder up to and including that position. **We need to prevent leftward information flow in the decoder to preserve the auto-regressive property. We implement this inside of scaled dot-product attention by masking out (setting to −∞) all values in the input of the softmax which correspond to illegal connections.** See Figure 2.





## Position-wise Feed-Forward Networks

> In addition to attention sub-layers, each of the layers in our encoder and decoder contains a **fully connected feed-forward network**, which is applied to each position separately and identically. This consists of two linear transformations with a ReLU activation in between.

除了attention function, 每一层还包括了一个Feed-Forward Network, 其实就是个最简单的MLP.
$$
\mathrm{FFN}(x) = \max(0, xW_1 + b_1)W_2 + b_2
$$

> While the linear transformations are **the same across different positions,** they use different parameters from layer to layer. Another way of describing this is as two convolutions with kernel size 1. The dimensionality of input and output is dmodel = 512, and the inner-layer has dimensionality dff =2048.

所有层都用相同的MLP.



至于为什么要用Position-wise Feed-Forward Networkk, 我不知道...

## Embeddings and Softmax

> Similarly to other sequence transduction models, we use learned embeddings to convert the input
>
> tokens and output tokens to vectors of dimension dmodel. We also use the usual learned linear transfor-
>
> mation and softmax function to convert the decoder output to predicted next-token probabilities. In
>
> our model, we share the same weight matrix between the two embedding layers and the pre-softmax
>
> linear transformation, similar to [24]. In the embedding layers, we multiply those weights by $\sqrt d_\mathrm{model}$

很常规.

## Positional Encoding

Transformer没有用RNN, 只使用注意力机制, 因此在处理数据时不会收到任何的位置信息. 将样本的顺序打乱后得到的输出依然是相同的值, 只是顺序可能也会被打乱.

我们需要把输入的序列(Transformer在本文中被用于翻译, 因此输入是文本序列)的位置信息也加入到模型中.

> Since our model contains no recurrence and no convolution, in order for the model to **make use of the order of the sequence**, we must **inject some information about the relative or absolute position of the tokens in the sequence.** To this end, we add "positional encodings" to the input embeddings at the

$$
PE_{(pos, 2i)} = \sin (pos / 10000^{2i / d_{\mathrm{model}}}) \\
PE_{(pos, 2i+1)} = \cos (pos / 10000^{2i / d_{\mathrm{model}}})
$$

完全看不懂.

> where pos is the position and i is the dimension. That is, each dimension of the positional encoding corresponds to a sinusoid. The wavelengths form a geometric progression from 2π to 10000 · 2π. We chose this function because we hypothesized it would allow the model to easily learn to attend by relative positions, since for any fixed offset k, P Epos+k can be represented as a linear function of PEpos.
>
> We also experimented with using learned positional embeddings [8] instead, and found that the two versions produced nearly identical results (see Table 3 row (E)). We chose the sinusoidal version because it may allow the model to extrapolate to sequence lengths longer than the ones encountered during training.





Table1: Maximumpathlengths,per-layercomplexityandminimumnumberofsequentialoperations for different layer types. $n$ is the sequence length, $d$ is the representation dimension, $k$ is the kernel size of convolutions and $r$ the size of the neighborhood in restricted self-attention.

![Table1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Table1.png)





# Evaluation



We employ three types of regularization during training:

* **Residual Dropout**: We apply dropout [27] to the output of each sub-layer, before it is added to the sub-layer input and normalized. In addition, we apply dropout to the sums of the embeddings and the positional encodings in both the encoder and decoder stacks. For the base model, we use a rate of Pdrop = 0.1.

* **Label Smoothing During training**: we employed label smoothing of value εls = 0.1 [30]. This hurts perplexity, as the model learns to be more unsure, but improves accuracy and BLEU score.



Table 2: The Transformer achieves better BLEU scores than previous state-of-the-art models on the English-to-German and English-to-French newstest2014 tests at a fraction of the training cost.

![Table2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Machine%20Learning/Attention-Is-All-You-Need/Table2.png)

