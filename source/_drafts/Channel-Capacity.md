---
title: Channel Capacity
tags:
  - Information Theory
categories: Mathematics
mathjax: true
---

Ref:

1. *Elements of Information Theory*
2. [EE 376A: Information Theory](https://web.stanford.edu/class/ee376a/) - Stanford University
3. [10-704: Information Processing and Learning. Spring 2012. Lecture 15.](https://www.cs.cmu.edu/~aarti/Class/10704/lec15-channelintro.pdf) - CMU
4. [EE 376A: Information Theory. Winter 2018. Lecture 4.](https://web.stanford.edu/class/ee376a/files/2017-18/lecture_4.pdf) - Stanford University
5. [EE 376A: Information Theory. Winter 2017. Lecture 4.](https://tselab.stanford.edu/mirror/ee376a_winter1617/Lecture_4.pdf) - Stanford University

# Channel Encoding

Until now we have studied the data compression (source coding) problem, schematically described by the following diagram:

![image-20231130132411081](/Users/lyk/Library/Application Support/typora-user-images/image-20231130132411081.png)



We now turn to the channel coding problem, where we introduce an intermediate step between the output of the compressor and the input to the decompressor:

![image-20231130132524543](/Users/lyk/Library/Application Support/typora-user-images/image-20231130132524543.png)

A “**channel**” is any source of noise, for example a wireless link, an error prone storage device, an IP network with the potential for packet loss, etc.

# Discrete Memoryless Channels (DMC)

Essentially, a channel is a conditional distribution like $p(Y |X)$. We will focus on **discrete memoryless channels (DMC)**.

* **Discrete**: Input and output alphabets $\mathcal X$ , $\mathcal Y$ are finite; and

* **Memoryless**: $P_{Y^{n} \mid X^{n}}\left(y^{n} \mid x^{n}\right)$ is **independent** of outputs in previous timesteps (later we will discuss more general feedback channels). Thus
  $$
  p(y_k|x_k, y_{k−1}) = p(y_k|x_k) .
  $$

* If the channel is used *without feedback* [i.e., if the input symbols do not depend on the past output symbols, namely, $p(x_k|x^{k−1},y^{k−1}) = p(x^k|x^{k−1})]$, the channel transition function for the nth extension of the discrete memoryless channel reduces to
  $$
  P_{Y^{n} \mid X^{n}}\left(y^{n} \mid x^{n}\right) \triangleq \prod_{i=1}^{n} P_{Y \mid X}\left(y_{i} \mid x_{i}\right) .
  $$
  
* When we refer to the DMC, we mean the **discrete memoryless channel without feedback** unless we state explicitly otherwise.

![DMC](/Users/lyk/Library/Application Support/typora-user-images/image-20231130132543151.png)

1. The recovered message(bits):  $\hat{B}^{m}=\left(\hat{B}_{1}, \hat{B}_{2}, \ldots, \hat{B}_{m}\right)$.
2. The channel, which is identified as a conditional distribution $p(y^{n} \mid x^{n})$.

# Definitions

- $M$: The number of possible messages.

  * We denote every message as $m$ bits: $B^{m}=\left(B_{1}, B_{2}, \ldots, B_{m}\right)$.
  * $M = 2^m$.

  * Le$B_{1}, B_{2}, \ldots, B_{m}$  be i.i.d. bits $\sim \operatorname{Ber}\left(\frac{1}{2}\right)$ . 
  * Notice that $m$ is not necessarily equal to $n$.
  * We often interchangably use the index set $\{1,\cdots,M\}$ to represent $B^m$ and $\hat B^m$, since the encoder and decoder agree about what are the possible messages and on an index on these messages.  In other words, there's a bijection between them.

- $\mathcal X$ denotes the alphabet in which the message is encoded. $X^n$ denotes the encoding function, that is, 
  $$
  \hat X^n: \{1,\cdots,M\} \rightarrow \mathcal X^n .
  $$
  Note: here we use the index set $\{1,\cdots,M\}$ to represent $B^m$, since there's  we can freely interchange them.

- $\mathcal Y$ denotes the alphabet in which the output of the channel is written. Wc denotes the decoding function, that is, 
  $$
  \hat W: \mathcal Y ^n \rightarrow \{1,2,\cdots, M\} .
  $$
  Note: here we use $\{1,\cdots,M\}$ to represent $\hat B^m$, since there's a bijection between, we can freely interchange them.

  

## Channel

A **channel** is defined as
$$
(\mathcal X^n, \mathcal Y^n, p(y^n|x^n)) .
$$


$p(y_n|x_n)$ represents the probability of the channel out- putting yn when xn is received as an input.

## Code

A **code** is defined as
$$
\begin{equation} \label{eq_Scheme}
(M, n, X^n, \hat W)
\end{equation}
$$


## Rate

A scheme with rate $R$ can **transmit $R$  bits per channel use.**
$$
\text { rate } \triangleq \frac{\log M}{n} = \frac{m}{n} \frac{\text { bits }}{\text { channel use }}
$$
In other words, a $m = nR$ bits message can represent   $2^{nR} = 2^m$ distinguishable info??

The higher the rate, the better we are at communicating our information.



## Probability of Error

Probability of Error:
$$
P_{e}^{(n)} \triangleq P\left(\hat{B}^{m} \neq B^{m}\right)
$$

- (Conditional Probability of Error) $\lambda_i^{(n)}=P(\widehat{W} \neq i \mid W=i)$ .
- (Maximal Probability of Error) $\lambda^{(n)}=\max _{i \in\{1, \ldots, M\}} \lambda_i^{(n)}$.
- (Arithmetic Probability of Error) $p_e^{(n)}=\frac{\sum_{i=1}^M \lambda_i^{(n)}}{M}$ .

## Achievable Rate

Achievable Rate:  $R$  is an <u>achievable rate</u> if, for all $n$, there exists a code with $M = 2^{nR}$ s.t. 
$$
\lambda ^{(n)} \stackrel{n \rightarrow \infty}{\longrightarrow} 0 .
$$


Note that $m$ has to be scaling and growing with $n$ as it goes to infinity.

With the notion of achievable rate, we can talk about channel capacity.

## Channel Capacity

The channel capacity, aka operational capacity, of a channel is **the supremum of all achievable rates** on that channel:
$$
C \triangleq \sup \{R \mid R \text { is achievable }\}
$$


All these definitions are valid for any kind of channel. However, to get started, we choose to work with simpler channels. This brings us to the notion of a <u>memoryless channel</u>, which is a surprisingly common assumption to make in communication.

## Information Capacity

The information capacity of a (DMC) channel is


$$
C^{(I)} \triangleq \max _{X \sim P_{X}} I(X ; Y)
$$
where the maximum is over all distributions on $X$.



Intuitively we would expect that the most information that can be sent with a single use of this channel is exactly 1 bit.

# Examples of Information Capacity

For the convience of issustration. in the following we just consider the “single-letter” channel with $n=1$. (You can think it's a memoryless channel as well.)

![image-20231130140035481](/Users/lyk/Library/Application Support/typora-user-images/image-20231130140035481.png)



In this case, the information capacity is $C^{(I)} \triangleq \max _{X \sim P_{X}} I(X ; Y)$.

We now calculate the information capacity for some simple channel models.

## Noiseless binary channel

Identity (noiseless) channels: An identity channel has equal size input and output alphabets $(|\mathcal{X}|=|\mathcal{Y}|)$ and channel transition probability satisfying
$$
P_{Y \mid X}(y \mid x)= \begin{cases}1 & \text { if } y=x \\ 0 & \text { if } y \neq x\end{cases}
$$

This is a noiseless or perfect channel as the channel input is received error-free at the channel output.



To calculate the information capacity, note that for any distribution over the inputs p(x) we have
$$
\begin{align} 
I(X,Y) 
&= H(Y)−H(Y|X) \nonumber \\
& = H(Y ) \label{eq_NBC_1} \\
& = H(X) \\ \label{eq_NBC_2}
\end{align}
$$

* $\eqref{eq_NBC_1}$: Because $Y$ is deterministic given $X$, so $H(Y \mid X) = 0$.

* $\eqref{eq_NBC_2}$: Because $Y$ has the same distribution as $X$, so $H(Y) = H(X)$.

  

Since $X \sim \text{Bern}$, we know that its entropy is maximized when $p(0) = p(1) = 1/2$, and
$$
\max _{X \sim P_{X}} I(X ; Y) = 1
$$


## Noisy channel with non-overlapping output distributions

![image-20231130144244549](/Users/lyk/Library/Application Support/typora-user-images/image-20231130144244549.png)
$$
\begin{align} 
I(X,Y) 
&= H(X)−H(X|Y) \nonumber \\
& = H(X ) \label{eq_NBC_3}
\end{align}
$$

* $\eqref{eq_NBC_3}$: Because $X$ is deterministic given $Y$, so $H(X \mid Y) = 0$.
  1. Y = 1 --> X = 0
  2. Y = 2 --> X = 0
  3. Y = 3 --> X = 1
  4. Y = 4 --> X = 2



So 
$$
\max _{X \sim P_{X}} I(X ; Y) = \max _{X \sim P_{X}} H(X) = 1
$$
where the maximum is achieved when $X \sim \text{Bern}(\frac 1 2)$.

## Noisy typewriter

Consider a 26-key typewriter. If pushing a key results in printing the associated letter, what is the capacity C in bits?

Solution: If the typewriter prints out whatever key is struck, then the output, $Y$, is the same as the input, $X$, and
$$
C=\max I(X ; Y)=\max H(X)=\log 26,
$$
attained by a uniform distribution over the input.

***

(b) Now suppose that pushing a key results in printing that letter or the next (with equal probability). Thus A → A or B, . . ., Z → Z or A. what is the capacity?

![image-20231130145257885](/Users/lyk/Library/Application Support/typora-user-images/image-20231130145257885.png)

In this case, the output is either equal to the input (with probability $1 / 2$ ) or equal to the next letter (with probability 1/2). Hence $H(Y \mid X)=\log 2$ independent of the distribution of $X$, and hence
$$
C=\max I(X ; Y)=\max H(Y)-\log 2=\log 26-\log 2=\log 13,
$$
attained for a uniform distribution over the output, which in turn is attained by a uniform distribution on the input. //WHY??

## Binary symmetric channel (BSC)

![image-20231206231609331](/Users/lyk/Library/Application Support/typora-user-images/image-20231206231609331.png)

Binary symmetric channels: A binary symmetric channel (BSC) is a channel with binary input and output alphabets such that each input has a (conditional) probability given by $\varepsilon$ for being received inverted at the output, where $\varepsilon \in[0,1]$ is called the channel's crossover probability or bit error rate. The channel's transition distribution matrix is given by
$$
\begin{aligned}
\mathbb{Q} & =\left[p_{x, y}\right]=\left[\begin{array}{ll}
p_{0,0} & p_{0,1} \\
p_{1,0} & p_{1,1}
\end{array}\right] \\
& =\left[\begin{array}{ll}
P_{Y \mid X}(0 \mid 0) & P_{Y \mid X}(1 \mid 0) \\
P_{Y \mid X}(0 \mid 1) & P_{Y \mid X}(1 \mid 1)
\end{array}\right]=\left[\begin{array}{cc}
1-\varepsilon & \varepsilon \\
\varepsilon & 1-\varepsilon
\end{array}\right]
\end{aligned}
$$
and can be graphically represented via a transition diagram as shown in Fig. 4.2.

* If we set $\varepsilon=0$, then the BSC reduces to the binary identity (noiseless) channel. The channel is called "symmetric" since $P_{Y \mid X}(1 \mid 0)=P_{Y \mid X}(0 \mid 1)$; i.e., it has the same probability for flipping an input bit into a 0 or a 1 . A detailed discussion of DMCs with various symmetry properties will be discussed later in this chapter.

Despite its simplicity, the $\mathrm{BSC}$ is rich enough to capture most of the complexity of coding problems over more general channels. For example, it can exactly model the behavior of practical channels with additive memoryless Gaussian noise used in conjunction of binary symmetric modulation and hard-decision demodulation (e.g., see [407, p. 240]). 



It is also worth pointing out that the **BSC can be explicitly represented via a binary modulo- 2 additive noise channel** whose output at time $i$ is the modulo-2 sum of its input and noise variables:
$$
\begin{equation} \label{eq_BSC}
Y_i=X_i \oplus Z_i \text { for } i=1,2, \ldots,
\end{equation}
$$
where $\oplus$ denotes addition modulo-$2$, $Y_i$, $X_i$, and $Z_i$ are the channel output, input, and noise, respectively, at time $i$, the alphabets $\mathcal{X}=\mathcal{Y}=\mathcal{Z}=\{0,1\}$ are all binary. 

It is assumed in $\eqref{eq_BSC}$ that $X_i$ and $Z_j$ are **independent** of each other for any $i, j=1,2, \ldots$, and that the noise process is a Bernoulli $(\varepsilon)$ process-i.e., a binary i.i.d. process with $\operatorname{Pr}[Z=1]=\varepsilon$.



We have
$$
\begin{aligned}
H(Y \mid X) & =\sum_x p(x) H(Y \mid X=x) \\
& =\sum_x p(x) H(\text { Bernoulli }(p)) \\
& = H(\text { Bernoulli }(p))
\end{aligned} .
$$
where $p$ is in the figure.



Then
$$
\begin{aligned}
\max _{p(x)} I(X, Y) & =\max _{p(x)} H(Y)-H(Y \mid X) \\
& =\max _{p(x)} H(Y)- H(\text { Bernoulli }(p)) \\
& \le 1 - H(\text { Bernoulli }(p))
\end{aligned}
$$
where the last inequality follows because $Y$ is a <u>binary random variable</u>. (For a binary rv, it's largest entropy is 1).

Equality ($H(Y) = 1$) is achieved when $Y \sim \text{Bern}(\frac 1 2)$. But how to set $p(x)$ to achieve this?

### How to achieve equality

If we want to achieve $Y \sim \text{Bern}(\frac 1 2)$, then $p(x)$ must be uniform.

Proof:

Let $k = p(X=1)$, then:

1. $p(Y=1) = p(X=1)(1-p) + p(X=0)p = k-kp + p - kp = p + k - 2kp$.
2. $p(Y=0) = p(X=1)(p) + p(X=0)(1-p) = 1 - p - k + 2kp$.

If we want $Y \sim \text{Bern}(\frac 1 2)$, then $p(Y=1) = p(Y=0) = 1/2$. So we want to get $k$ satisfies
$$
\forall p , \quad p + k - 2kp = 1/2 .
$$
Note that $p + k - 2kp = p(1-2k) + k$, so $k=1/2$.

So $X \sim \text{Bern}(\frac 1 2)$. Note that Bernoulli distribution is also a kind of uniform distribution.

## Binary erasure channel (BEC)

Define alphabets $\mathcal X = \{0,1\}$ and $\mathcal Y = \{0,1, e \}$ where $e$ stands for erasure. 

Any input symbol $X_i$ has a probability $1−α$ of being retained in the output sequence and a probability $α$ of being erased.

![image-20231130141618906](/Users/lyk/Library/Application Support/typora-user-images/image-20231130141618906.png)

We again begin by writing
$$
I(X, Y)=H(X)-H(X \mid Y) .
$$

Note that if we observe $Y=0$ or $Y=1$, then $X$ is known exactly, so $H(X \mid Y \neq e)=0$. Furthermore $H(X \mid Y=e)=H(X)$, so
$$
\begin{aligned}
H(X \mid Y) 
&= H(X \mid Y \neq e) \cdot P(Y \neq e)+H(X | Y=e) \cdot P(Y=e) \\
& =0 \cdot P(Y \neq e)+H(X) \cdot P(Y=e) \\
& =\alpha H(X)
\end{aligned}
$$
and
$$
\begin{aligned}
I(X, Y) 
&= H(X) - H(X|Y) \\
& =(1-\alpha) H(X) \\
& \leq 1-\alpha
\end{aligned}
$$
The equality is achieved when $H(X) = 1$, i.e., $p(x)$ is uniform.  

So
$$
\max _{p(x)} I(X, Y)=1-\alpha
$$

Again, **the interpretation is obvious. We lose $\alpha$ fraction of bits per transmission.**

# Symmetric Channels

Notice that in many of the above examples the maximizing distribution on $X$ in the information capacity is uniform. Here we describe a class of channels that have this property.

Note that a DMC channel with input alphabet $\mathcal{X}$ and output alphabet $\mathcal{Y}$ can be described in terms of a transition probability matrix $P \in \mathbb{R}^{\mathcal{X} \times \mathcal{Y}}$ where $P_{i j}=p\left(y_j \mid x_i\right)$. 

If both the rows and the columns of $P$ are permutations of each other, then the channel is called **symmetric**.

Another example of a symmetric channel is one of the form
$$
Y=X+Z \quad (\mod r),
$$


where $Z$ has some distribution on the integers $\{0, 1, 2, . . . , r − 1\}$, $X$ has the same alphabet as $Z$, and $Z$ is independent of $X$.



For such a channel, we have that $H(Y \mid X=x)=c$ is **constant** for all $x \in \mathcal{X}$ and so $H(Y \mid X)=c$ as well(See [Appendix: Proof1]()), and so for any $x \in \mathcal{X}$
$$
\begin{aligned}
I(X, Y) & =H(Y)-H(Y \mid X) \\
& =H(Y)-c \\
& \leq \log _2|\mathcal{Y}|-c
\end{aligned}
$$

**The inequality is achieved exactly when the distribution of $Y$ is uniform**(See [Theorem: $H(X) \leq \log |\mathcal{X}|$](https://lyk-love.cn/2023/10/15/jensen%E2%80%99s-inequality/?highlight=jens#theorem-hx-leq-log-mathcalx),

we observe that **uniform input distribution can achieves the uniform output distribution**. (See [Appendix: Proof2]())

但是X的别的分布也可能可以满足这点吧?

## Weakly Symmetric Channels

Note that the above argument holds if we relax the assumption on <u>the columns of $P$ to summing to the same quantity</u> (we only used the permutation property of the columns in the last step to argue precisely that their sum is constant).

That is, a channel is said to be **weakly symmetric** if every **row** of the transition matrix $p(·|x)$ is a **permutation** of every other row and all the **column sums**  $p(y|x)$ are **equal**.

For example, the channel with transition matrix
$$
\begin{bmatrix}
  \frac 1 3 & \frac 1 6 & \frac 1 2 \\
  \frac 1 3 & \frac 1 2 & \frac 1 6 \\
\end{bmatrix}
$$
is weakly symmetric but not symmetric.

# Jointly Typical Sets

When studying compression, we defined that a sequence is typical if its information content is close to the entropy. For i.i.d. sequences, we proved that typical sequences occur with high probability. In the problem of sending codes through a channel we are concerned with two sequences, the input and output of the channel. In this context, we develop the notion of jointly typical sets.



Definition 16.4: $A_\epsilon^{(n)}$ is the set of typical sets of length $n$ and tolerance $\epsilon$ and is composed of sequences $\left(x^n, y^n\right)$ such that:

1. $\left|\frac{-\log \left(p\left(x^n\right)\right)}{n}-H(X)\right|<\epsilon$
2. $\left|\frac{-\log \left(p\left(y^n\right)\right)}{n}-H(Y)\right|<\epsilon$
3. $\left|\frac{-\log \left(p\left(x^n, y^n\right)\right)}{n}-H(X, Y)\right|<\epsilon$

## Lemma 16.5

Lemma 16.5: If $\left(X_i, Y_i\right)$ are i.i.d., the jointly typical sets $A_\epsilon^{(n)}$ satisfy the following properties:

1. $P\left( (X^n, Y^n\right) \in A_\epsilon^{(n)}) \rightarrow 1$ as $n \rightarrow \infty$
2. $\left|A_\epsilon^{(n)}\right| \leq 2^{n(H(X, Y)+\epsilon)}$.
3. $\left|A_\epsilon^{(n)}\right| \geq(1-\epsilon) 2^{n(H(X, Y)-\epsilon)}$, for large $n$

4. Let $\left(\tilde{X}^n, \tilde{Y}^n\right) \sim p\left(x^n\right) p\left(y^n\right)$, i.e. $\tilde{X}^n$ and $\tilde{Y}^n$ are independent with distributions same as the marginal distributions $p\left(x^n\right)$ and $p\left(y^n\right)$ of $p\left(x^n, y^n\right)$, then
$$
P\left(\left(\tilde{X}^n, \tilde{Y}^n\right) \in A_\epsilon^{(n)}\right) \leq 2^{-n(I(X, Y)-3 \epsilon)}
$$

Also, for sufficiently large $n$,
$$
P\left(\left(\tilde{X}^n, \tilde{Y}^n\right) \in A_\epsilon^{(n)}\right) \geq(1-\epsilon) 2^{-n(I(X, Y)+3 \epsilon)}
$$

### Proof

Proof: Items 1, 2 and 3 follow analogously to the results regarding typicality in the source coding theorem. 

For item 4, observe that:
$$
P\left(\left(\tilde{X}^n, \tilde{Y}^n\right) \in A_\epsilon^{(n)}\right)=\sum_{\left(x^n, y^n\right) \in A_\epsilon^{(n)}} p\left(x^n\right) p\left(y^n\right) \leq \left|A_\epsilon^{(n)}\right| \max _{\left(x^n, y^n\right) \in A_\epsilon^{(n)}} p\left(x^n\right) p\left(y^n\right)
$$

第一个等号可以这样理解: 设$X \sim p(x)$, then $p(X \in \mathcal B ) = \sum_{x \in \mathcal B} p(X=x)$.

第二个等号就很好理解了.、



From item 2, $\left|A_\epsilon^{(n)}\right| \leq 2^{n(H(X, Y)+\epsilon)}$. Also observe that for any $\left(x^n, y^n\right) \in A_\epsilon^{(n)}$, $x^n$ is typical.(Why?) 

Hence, $p\left(x^n\right) \leq 2^{-n(H(X)-\epsilon)}$. Similarly, $p\left(y^n\right) \leq 2^{-n(H(Y)-\epsilon)}$.  (这一步就是typical set的定义)

Using these inequalities:

得到$P\left(\left(\hat{X}^n, \hat{Y}^n\right) \in A_\epsilon^{(n)}\right)$的上界:
$$
P\left(\left(\hat{X}^n, \hat{Y}^n\right) \in A_\epsilon^{(n)}\right) \leq 2^{n(H(X, Y)+\epsilon)} 2^{-n(H(X)-\epsilon)} 2^{-n(H(Y)-\epsilon)}=2^{-n(I(X ; Y)-3 \epsilon)}
$$



Similarly, using item 3 , we get for large enough $n$ :
$$
P\left(\left(\tilde{X}^n, \tilde{Y}^n\right) \in A_\epsilon^{(n)}\right)=\sum_{\left(x^n, y^n\right) \in A_\epsilon^{(n)}} p\left(x^n\right) p\left(y^n\right) = |A_\epsilon^{(n)}| p\left(x^n\right) p\left(y^n\right)
$$
第二个等号是因为item1.

接下来就能得到$P\left(\left(\hat{X}^n, \hat{Y}^n\right) \in A_\epsilon^{(n)}\right)$的下界:
$$
P\left(\left(\hat{X}^n, \hat{Y}^n\right) \in A_\epsilon^{(n)}\right) \geq(1-\epsilon) 2^{n(H(X, Y)-\epsilon)} 2^{-n(H(X)+\epsilon)} 2^{-n(H(Y)+\epsilon)}=(1-\epsilon) 2^{-n(I(X ; Y)+3 \epsilon)}
$$
A consequence of property 4 is that, for a fixed $y^n$, we can consider $\sim 2^{n I(X, Y)}$ $x^n$ sequences before we are likely to find another that is jointly typical with $y^n$. 

This implies that there are $2^{n I(X, Y)}$ distinguishable input signals $x^n$. This observation is the key insight that leads to Shannon's noisy channel coding theorem, as discussed next.

//WHY?

# Channel Coding Theorem: Direct Part

Direct Part: if $R < \max_{p(x)} I(X; Y )$, then $R$ is achievable, i.e., ∃ schemes with rate ≥ R and $P^e \stackrel{n \rightarrow \infty}{\longrightarrow}0$.

# Channel Coding Theorem: Converse Part

Converse part: if $R > \max_{p(x)} I (X ; Y )$, then R is not achievable.

# Appendix

## Proof1

Proof: "For such a channel, we have that $H(Y \mid X=x)=c$ is constant for all $x \in \mathcal{X}$ and so $H(Y \mid X)=c$ as well, and so for any $x \in \mathcal{X}$".



Now consider a channel with a $3 \times 3$ transition matrix:
$$
\begin{bmatrix}
  a & b & 1-ab \\
  b & 1-ab & a \\
  1-ab & a & b \\
\end{bmatrix}
$$


We find out that $H(Y|X=x_1) = H(Y|X=x_2) = H(Y|X=x_3)$. Denote it as $c$. Thus $c$ is constant.

Then
$$
H(Y|X) = \sum_{x \in \mathcal X} p(x) H(Y|X=x) = \sum_{x \in \mathcal X} p(x) \cdot c = c .
$$


Q.E.D.

## Proof2

**Proof:** "uniform input distribution can achieves the uniform output distribution"

If $X$ follow an uniform distribution, then $p(x) = \frac{1}{|\mathcal X|}$. We obtain
$$
\begin{aligned}
p(y) & =\sum_x p(y \mid x) p(x) \\
& =\frac{1}{|\mathcal{X}|} \sum_x p(y \mid x)
\end{aligned}
$$
Because the columns of $P$ are permutations of each other, and $\sum_x p(y \mid x)$ is just the sum of the colum when $Y=y$, then $\sum_x p(y \mid x)$ is constant for all $y$.  Since $p(y)$ is constant, $Y$ follows an uniform distribution.

Q.E.D.

## Proof3

