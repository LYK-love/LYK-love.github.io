---
title: Network Security
tags: Computer Networking
categories: Computer Science
mathjax: true
---



# Intro

## Target

网络安全有四大目标:

* *Confidentiality*：只有信息的发送方和接收方才知道信息的内容
* *Message integrity*：信息接收方需要确认所收到的信息没有被人篡改过，且的确是报文的发送者所发送的(这就需要数字签名)
* *End-point authentication*：信息发送方和接收方都需要确保，通信对方的确是他们所声明的实体
* *Operational security*: 需要确保网络的运行时安全。 几乎所有组织的网络最终都是连到互联网的，所以网络很容易受到攻击。

## Assumptions

在本文中，我们假设Bob和Alice在偷情，他们互相在网络上通信。 而Bob的妻子Trudy，想要通过攻击网络，来发现这段恋情。（我认为这个例子更加地生动形象，也更能体现网络安全的重要作用）

# Confidentiality

* *cryptography*: 密码编码学，是密码体制的设计学
  * 加密算法也称为*cypher*

* *cryptanalysis*: 密码分析学，是在未知密钥的情况下从密文推演出明文或密钥的技术

* *cryptology*：密码学， 密码编码学+密码分析学

---



密码体制的安全性:

* 无条件安全: 不论截取者获得了多少密文，但在密文中都没有足够的信息来唯一地确定出对应的明文,  即该密码体制理论上是不可破的
  * 在无任何限制的条件下，目前几乎所有实用的密码体制均是可破的。 因此我们转而追求“计算上安全”
* 计算上安全： 密码不能在一定时间内被可以使用的计算资源破译

## 





## Cryptographic Model

![Cryptographic components](/Users/lyk/Library/Application Support/typora-user-images/image-20220727194701460.png)

Alice向Bob发送的信息是**明文**（ plaintext, or cleartext ）, 通过**encryption algorithm**加密后，就得到了**密文**( **ciphertext** )



### Encryption

Alice发送明文$m$, 并提供一个密钥$K_A$,  加密算法( encryption algorithm ) $E$接受$m$和$K_A$， 生成密文$c$：
$$
c = E_{K_A}(m)
$$

* 密钥( key )是一串秘密的字符串

### Decryption

Bob收到密文$c$后，提供一个密钥$K_B$，解密算法( decryption algorithm ) $D$接受$c$和$K_B$，得到明文$m$:
$$
m = D_{K_B}(c) = D_{K_B}( E_{K_A}(m) )
$$


* 解密算法是加密算法的逆运算，在进行解密运算时，如果不使用事先约定好的密钥就无法解出明文

### Key System

* 对称加密系统( symmetric key system ):  $K_A = K_B$ ， 且两个密钥都是保密的

* 非对称加密系统( 也称为公钥加密系统 , public key system):  $K_A \ne K_B$ ， 且密钥分为公钥( public key )和私钥( private key ),  公钥对全世界公开， 而私钥只有通信的一方知道



## Attack Types

对密码体制的攻击，分为以下三种：

- *Ciphertext-only attack*： 攻击者只知道密文
- *Known-plaintext attack*： 攻击者知道密文，以及一部分密文-明文对照( (plaintext, ciphertext) pairings  )
- *Chosen-plaintext attack*: 攻击者可以选择明文，然后获取其对应的密文。  使用Chosen-plaintext attack， 攻击者很容易破解整个密码体制
  * 当然，对于后面介绍的现代密码体制，即使是Chosen-plaintext attack也很难破解

## Symmetric Key System

### Old-Time Cipher

我们先来看看古代的对称加密系统：

* 凯撒加密（ Caesar cipher ）： 选择数字k，把英文文本的每个字母替换成其在字母表上后面第k位的字母
  * 很容易破解
* 单字母加密( monoalphabetic cipher ): 使用一张明文字母 - 密文字母的映射表，将明文按表加密
* 多字母加密( polyalphabetic encryption ): 对明文的每个字母，先后使用多个映射表加密



这些加密算法都很简陋，即使攻击者不知道任何明文( 即Ciphertext-only attack )，也可以根据一些手段进行破解：

1. 通过统计学分析。 英文中，统计意义上最常见的字母是e和f，分别占文本的13%和9%
2. 通过猜词，比如i和t常一起出现，成为it。 甚至对于Alice和Bob的情况，Trudy很可能会猜测文本中存在“love”、“Alice”、“Bob”等词，获得更多信息



### Block Cipher

与古代按字母加密不同，现代加密系统都采用分组加密。 如下所示：

1. 在加密前，先对整个的明文进行**分组**。对于64位的报文， 我们将其分成8位的组( 每个组也就是一个8位的二进制数据 )
2.  对每个组进行**加密**处理加密，形成64位的密文( 64-bit scrambler )
   * 可以按表加密，即图上的T。 更现代的做法是使用加密**函数**F 
3. **重排**这64位密文，形成输出密文( 64-bit output )
4. 将输出密文作为输入，回到步骤1。 循环n次，得到最终结果
   * 循环n次的原因在于增大输入中的每一位对输出的影响。 如果只循环一次，则输入中的1位，至多影响输出中的一位。加密过程会更容易破解

![image-20220727204239241](/Users/lyk/Library/Application Support/typora-user-images/image-20220727204239241.png)

暴力破解算法，就需要把n位长的密钥都是一遍，也就是$2^n$次的开销

### CBC

对于两个完全相同的分组，其分组加密后的密文也会是相同的。比如，对于HTTP报文， 普遍存在内容如“HTTP/1.1”的块， 它们对应的密文也是相同的，这会让攻击者很容易猜出一些信息。 为此，分组加密还引入了**密钥+ 随机数**：

1. 我们假设组为k位。 对于第$i$组( 记为$m(i)$ )，报文发送方生成一个随机的k位数$r(i)$, 然后用密钥$S$加密:
   $$
   c(i) = K_S( \ m(i) \oplus r(i) \ )
   $$

   * $r(i)$是随机的，因此对于内容相同的$m(i) = m(j)$， 有$c(i) \ne c(j)$

   

2. 发送方把每组的密文$c(i)$和随机数$r(i)$一起发送。 接收方收到密文和随机数后，使用对称密钥$S$解密:
   $$
   m(i) = K_S( \ c(i) \ )\oplus r(i)
   $$

   * 攻击者可以获得$c(i)$和$r(i)$，但不知道密钥$S$，因此无法解密得到$m$



该算法的缺点是：对于每个k位的组，都要生成一个k位的随机数r。 二者都被传输，使得报文带宽翻倍。解决方法是采用**Cipher Block Chaining (CBC)**：

1. 在加密前，发送方先生成一个随机的k位数$c(0)$, 称为**Initialization Vector (IV)**， 将其用**明文**发送

2. 对于第一个块，采用$c(0)$作为上文的$r(1)$, 用密钥$S$加密:
   $$
   c(1) = K_S( \ m(1) \oplus c(0) \ )
   $$
   

3. 对于第$i$组， 发送方计算c(i):

   ```
   c(i) = K_S( \ m(i) \oplus c(i-1) \ )
   ```

   注意到，CBC就是将$c(i-1)$作为$r(i)$. 

   

4. 对于第$i$组，发送方只需发送其密文$c(i)$.  因此接收方总共接收到$c(0), c(1), c(2), ...$， 总共只增加了$c(0)$的带宽



### Modern Ciphers

如前所述，现代的公钥加密算法采用分组加密，且都用函数F( 而非图上的表T )加密， 算法都接受一个密钥，来决定每个块的加密函数($F_1, F_2,F_3...$)以及重排时的规则等等。 

* 当然，该密钥还会用于CBC

#### DES

DES( Data Encryption Standard )：名为“数据加密标准”，由美国研发

* uses 64-bit blocks with a 56-bit key

DES对56位密钥很容易被攻破， 为此又出现了DES3。 它使用两个密钥，把一个64位明文用一个密钥加密，再用另一个密钥解密，然后再使用第一个密钥加密，即：

$$
c = DES_{K_1}( DES_{K_2}^{-1}( DES_{K_1} ) )
$$




#### AES

AES( Advanced Encryption Standard ): 名为“高级加密标准”。由美国标准与技术协会（NIST）对该标准对实现进行遴选，最终选中了Joan Daemen和Vincent Rijmen提交的Rijndael算法

* uses 128-bit blocks and can operate with keys that are 128, 192, and 256 bits long



## Public Key System

公钥密码体制 的概念是由斯坦福（Stanford）大学的研究人员Diffie与Hellman于1976年提出的［DIFF76］。公钥密码体制使用不同的加密密钥与解密密钥 。

公钥密码体制提出不久，人们就找到了三种公钥密码体制。目前最著名的是由美国三位科学家Rivest，Shamir和Adleman于1976年提出并在1978年正式发表的RSA体制 ，它是一种基于数论中的大数分解问题的体制［RIVE78］。”



在公钥密码体制中，加密密钥 PK （public key，即公钥 ）是向公众公开的，而解密密钥 SK （secret key，即私钥 或秘钥 则是需要保密的。加密算法E 和解密算法D 也都是公开的。



公钥密码体制的加密和解密过程有如下特点：

1. 密钥对产生器产生出接收者B的一对密钥：加密密钥$PK_{B}$和解密密钥$SK_{B}$。发送者A所用的加密密钥$PK_{B}$就是接收者B的公钥，它向公众公开。而B所用的解密密钥$SK_{B}$就是接收者B的私钥，对其他人都保密。

2. 发送者A用B的公钥$PK_{B}$通过E 运算对明文加密，得出密文，发送给B:
   $$
   c = E_{PK_{B}}(m)
   $$
   

   

   B用自己的私钥$SK_{B}$通过D运算进行解密，恢复出明文，即
   $$
   m = D_{SK_{B}}(c) = D_{SK_{B}}( \  E_{PK_{B}}(m) \ )
   $$
   

   

3. 虽然在计算机上可以容易地产生成对的$PK_{B}$和$SK_{B}$ ，但从已知的$PK_{B}$实际上不可能推导出$SK_{B}$，即从$PK_{B}$到$SK_{B}$是“计算上不可能的 ”。

4. 虽然公钥可用来加密，但却不能用来解密，即
   $$
   D_{ PK_{B} } (E_{PK_{B}}(m)) \ne m
   $$
   

5. 加密和解密算法本质上只是两个互逆的函数，因此可以对换计算顺序:
   $$
   D_{SK_{B}} (E_{PK_{B}}(m)) = E_{SK_{B}}(D_{PK_{B}}(m)) = m.
   $$

   * 当然，密钥不能对换



### RSA

## Cryptographic Hash Functions



# Message Integrity

## MAC

## Digital Signature

# End-point authentication

“。”



## Message Authentication

### 

## Entity Authentication



**End-point authentication** is the process of one entity proving its identity to another entity over a computer network,

# Key Distribution

## Symmentric Key Distribution

## Public Key Distribution

# Securiy in Internet

## Application Layer: Securing E-Mail

## Secure E-Mail

## PGP

## Transport Layer:  TLS

## Network-Layer: IPsec and VPN



## The AH and ESP Protocols

## Security Associations

##  The IPsec Datagram

##  IKE: Key Management in IPsec

# Securing Wireless LANs and 4G/5G Cellular Networks

## Authentication and Key Agreement in 802.11 Wireless LANs

## Authentication and Key Agreement in 4G/5G Cellular Networks



# Operational Security

## Firewalls

## IDS
