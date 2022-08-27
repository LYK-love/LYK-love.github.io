---
title: Network Security
tags:
  - Computer Networking
  - Network Security
categories: Computer Science
mathjax: true
date: 2022-08-28 01:20:12
---

Outline:

* Intro
* Confidentiality
* Digital Signature
* Message Digest
* End-point Authentication
* Key Distribution
* Securing Wireless LANs and 4G/5G Cellular Networks
* Operational security

<!--more-->


# Intro

## Target

网络安全有四大目标:

* *Confidentiality*：只有信息的发送方和接收方才知道信息的内容
* *Message integrity*：报文完整性. 信息接收方需要确认所收到的信息**没有被人篡改**过.
  * Message integrity一方面要确保报文完整性报文鉴别, 即对每一个收到的报文都要鉴别报文的发送者
* *Authentication*: 鉴别. 信息接收方要确保所通信的对象确实是他声明的实体. 鉴别分为两种:
  * *Message Authentication*: 报文鉴别. 对每一个收到的报文都要鉴别报文的发送者
    * 很多书( 谢希仁, 自顶而下... 都把报文鉴别也放到 *Message integrity* 的范畴, 我觉得这样会引起混淆. 因此我用自己的分类方式 )
    * 事实上, **实现报文鉴别的方法, 也都实现了报文完整性, 因此我不会单独介绍*Message integrity*和*Message Authentication*, 而是直接介绍实现了这两个特性的方法**: 
      1. **数字签名**
      2. **报文摘要**
  * *End-point authentication* or *Entity authenticatio*：端点鉴别/实体鉴别. 在整个通信过程内, 对对方只鉴别一次. 
    * 由于通信是双向的, 所以实体鉴别也是双向的. 报文鉴别只需要单向.
    * 这里的“实体”鉴别指的是对通信实体, 报文鉴别不包括在内.
* *Operational security*: 需要确保网络的运行时安全。 几乎所有组织的网络最终都是连到互联网的，所以网络很容易受到攻击。

## Problems

计算机网络的攻击可以分为四种:

1. 截获——从网络上窃听他人的通信内容
2. 中断——有意中断他人在网络上的通信
3. 篡改——故意篡改网络上传送的报文
4. 伪造——伪造信息在网络上传送



此外, 攻击还可以分为被动攻击和主动攻击:

* 被动攻击: Attacker只是观察和分析PDU( 协议数据单元 )而不干扰信息流
* 主动攻击: Attacker对PDU进行各种处理

## Assumptions

在本文中，我们假设Bob和Alice在偷情, 他们互相在网络上通信. 而Bob的妻子Trudy, 想要通过攻击网络来发现这段恋情.（我认为这个例子更加生动形象，也更能体现网络安全的重要作用）

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





## Cryptographic Model

![Cryptographic components](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Cryptographic%20components.png)

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

* 对称加密系统( symmetric key system ):  $K_A = K_B$ ， 且两个密钥都是保密的.
* 非对称加密系统( 也称为公钥加密系统 , public key system):  $K_A \ne K_B$ ， 且密钥分为公钥( public key )和私钥( private key ),  公钥对全世界公开， 而私钥只有通信的一方知道.
  * 非对称加密一般更慢.



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
   * **正由于Block Cypher接受固定位数的Block, 因此许多协议中都要加入一个padding字段, 用于填充报文以便于加密**.
2. 对每个组进行**加密**处理加密，形成64位的密文( 64-bit scrambler )
   * 可以按表加密，即图上的T。 更现代的做法是使用加密**函数**F 
3. **重排**这64位密文，形成输出密文( 64-bit output )
4. 将输出密文作为输入，回到步骤1。 循环n次，得到最终结果
   * 循环n次的原因在于增大输入中的每一位对输出的影响。 如果只循环一次，则输入中的1位，至多影响输出中的一位。加密过程会更容易破解

![Block Cipher](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Block%20Cipher.png)

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
   $$
   c(i) = K_S( \ m(i) \oplus c(i-1) \ )
   $$
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
c = \mathrm{DES}_{K_1}( \mathrm{DES}_{K_2}^{-1}( \mathrm{DES}_{K_1} ) )
$$




#### AES

AES( Advanced Encryption Standard ): 名为“高级加密标准”。由美国标准与技术协会（NIST）对该标准对实现进行遴选，最终选中了Joan Daemen和Vincent Rijmen提交的Rijndael算法

* uses 128-bit blocks and can operate with keys that are 128, 192, and 256 bits long



## Public Key System

公钥密码体制: 使用不同的加密密钥与解密密钥 

* 由斯坦福（Stanford）大学的研究人员Diffie与Hellman于1976年提出［DIFF76]. 
* 最著名的是RSA, 详见拙著[RSA](https://lyk-love.cn/2022/08/24/RSA/#more)



在公钥密码体制中，加密密钥 PK （public key ）是向公众公开的，而解密密钥 SK （secret key )则是需要保密的. 加密算法E 和解密算法D也都是公开的. 



公钥密码体制的加密和解密过程：

1. 接收者B先生成一堆密钥：公钥$PK_{B}$ ( public key, 向公众公开. 用于加密 )和私钥$SK_{B}$ ( secret key, 保密. 用于解密  ). 

2. 发送者A用B的公钥$PK_{B}$通过E运算对明文加密，得出密文，发送给B:
   $$
   c = E_{PK_{B}}(m)
   $$

   

3. B用自己的私钥$SK_{B}$通过D运算进行解密，恢复出明文，即:
   $$
   m = D_{SK_{B}}(c) = D_{SK_{B}}( \  E_{PK_{B}}(m) \ )
   $$
   
4. 虽然在计算机上可以容易地产生成对的$PK_{B}$和$SK_{B}$ ，但从已知的$PK_{B}$实际上不可能推导出$SK_{B}$，即从$PK_{B}$到$SK_{B}$是“计算上不可能的 ”.  

   * 参见我的[RSA](https://lyk-love.cn/2022/08/24/RSA/#more), RSA算法生成公钥$(n,e)$ 和私钥$(n, d)$ , 要根据$(n,e)$ 推导出$d$, 需要对$n$ 进行质数分解. 目前质数分解是计算上不可能的

5. 虽然公钥可用来加密，但却不能用来解密，即
   $$
   D_{ PK_{B} } (E_{PK_{B}}(m)) \ne m
   $$

6. 对[RSA](https://lyk-love.cn/2022/08/24/RSA/#more)来说,它的加密函数和解密函数都是一个函数, 只是加密和解密时接受的参数不同. 因此可以把加密函数用于解密, 只要给它输入私钥和密文即可; 对于解密函数也同理
   $$
   D_{SK_{B}} (E_{PK_{B}}(m)) = E_{SK_{B}}(D_{PK_{B}}(m)) = m.
   $$

   



## Cryptographic Hash Functions

a hash function takes an input, $m$, and computes a fixed-size string $H(m)$ known as a hash.



* **cryptographic hash function**: 哈希函数, 且满足 It is **computationally infeasible** to find any two different messages *x* and *y* such that $H(x) = H(y)$ , which means it's a one-way function.
  * cryptographic hash function 就是比较难发生碰撞的Hash函数, 常见的Checksum和CRC校验都属于Hash函数, 但都很容易碰撞, 因此不适合作为“加密哈希函数”. 具体例子见[我的checksum实现](https://github.com/LYK-love/Lazy-Scripts/blob/master/checksum.py)
  * 对于$(m, H(m))$ , 入侵者不可能使用$m'$替换$m$并使得$H(m') == H(m)$

* 最初的著名的加密哈希函数是MD5 ( Message Digest version 5 ), 由Rivest发明. 不过MD5在2004年被王小云给破解了.
* 后来, 美国标准与技术协会NIST又提出了SHA( Secure Hash Algorithm ), SHA-1也被破解了. 现在一般用SHA-2, 3 ...

### MD5

MD5代码为128位

Steps:

1. append: 先把报文按模 $2^{64}$ 计算其余数（64位），追加在报文后面
2. padding: 在报文和余数之间填充1～512位，使得填充后的总长度是512的整数倍. 填充的首位是1，后面都是0
   * 填充到固定位数, 用于Block Cypher
3. 把追加和填充后的报文分割为一个个512位的数据块，每个512位的报文数据再分成4个128位的数据块依次送到不同的散列函数进行4轮计算。每一轮又都按32位的小数据块进行复杂的运算。一直到最后计算出MD5报文摘要代码（128位）

### SHA

# Digital Signature

数字签名实现了以下三点:

1. 接收者能够核实发送者对报文的签名。也就是说，接收者能够确信该报文的确是发送者发送的。其他人无法伪造对报文的签名. 即**报文鉴别**
2. 接收者确信所收到的数据和发送者发送的完全一样而没有被篡改过. 即**报文完整性** 



数字签名的步骤:

1. 发送方A用自己的撕咬对报文进行加密, 发给接收方B.
2. B用A的公钥对数据解密, 得到报文



* 因为除A外没有别人持有A的私钥. 别人如果伪造A向B发报文, B将无法用A对公钥进行解密, 这就实现了**报文鉴别**. 
* 同理, 别人篡改过这篇报文, 但因为不知道A的私钥, B将将无法用A对公钥进行解密, 这就实现了**报文完整性**.
* 注意, 任何人用A的公钥都可以得出A发送的明文. 因此数据签名并不能用于保密.  如果要加密的话, 可以再使用加密算法.

# Message Digest

Message Digest实现了报文完整性和报文鉴别, Message Digest通过报文鉴别码MAC实现.

* NB: 局域网中使用的媒体接入控制MAC也是使用这三个字母, 因此在看到MAC时应注意上下文.
* 报文鉴别码MAC和数字签名的最大区别就是, 数字签名需要对整个报文进行加密, 而MAC只需要对报文的Hash $H$ 进行加密. 而 $H$ 一般远小于整个报文, 因此MAC消耗的资源更少. 当然MAC存在哈希碰撞的问题, 所以可以理解为 MAC 比数字签名“轻”一点, 但是安全性弱一点.



先来看一个反例. 下面给出的简单步骤, 看起来似乎可以实现报文的完整性和报文鉴别:

1. 用户A首先根据自己的明文 $X$计算出散列$H ( X )$（例如，使用MD5）。为方便起见，我们把得出的散列$H ( X )$记为$H$ 。
2. 用户A把散列$H$拼接在明文 $X$ 的后面，生成了扩展的报文$(X,H)$, 然后发送给B.
3. 用户B收到了这个扩展的报文$(X,H)$. 因为散列的长度$H$是早已知道的固定值, 因此可以把收到的散列$H$和明文$X$分离开. B通过散列函数的运算, 计算出收到的明文$X$ 的散列$H ( X )$. 若$H ( X ) = H$, 则B似乎可以相信所收到的明文是A发送过来的.

像上面列举的做法，实际上是**不可行**的 . 设想某个入侵者创建了一个伪造的报文$M$ ，然后也同样地计算出其散列$H ( M )$ , 并且冒充A把拼接有散列的扩展报文发送给B. B收到扩展的报文$(M,H(M))$后，按照上面步骤 (3) 的方法进行验证, 发现一切都是正常的, 就会误认为所收到的伪造报文就是A发送的. 

解决上面问题的办法并不复杂，就是对散列进行一次加密( 对称和非对称都可以 ):

![Message Digest](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Message%20Digest.png)



在A从报文$X$导出散列$H$后，就对散列$H$用密钥 $K$ 加密。这样得出的结果叫做**报文鉴别码 MAC**（Message Authentication Code )

* 现在已经有了好几个不同的MAC标准，而使用最广泛的就是HMAC，它可以和MD5或SHA一起使用［RFC 2104, 6151].



A把已加密的报文鉴别码MAC拼接在报文 $X$ 的后面，得到扩展的报文，发送给B.

B收到后把MAC与报文 $X$ 分离出来, 然后用密钥对MAC解密, 得到加密前的散列$H$, 再计算出$X$的散列$H ( X )$, 将$H ( X )$  与 $H$比较. 由于入侵者无法对MAC解密. 

* NB: 该方法不会加密整个报文, 只加密$H$, 由于$H$的位数一般远小于整个报文, 这样做节约了计算资源.
* 例如, 在链路层, 大量交换机需要交换报文, 为了保证报文完整性, 一般都要用这种方法. 既然该方法用到了加密, 就需要密钥分配, 对于链路层这样庞大的系统, 当然不可能手动分配, 一般我们用KAE来自动化密钥分配.

# End-point Authentication 

or Entity Authentication



你可能认为只要通信时每一个报文都采用HMAC之类的方式保证报文鉴别和报文完整性, 就能实现整个通信过程的安全, 这是错误的.

注意, 实体鉴别只需要在通信建立时实施一次. 此外在通信过程中的每一个报文, 依然需要进行报文鉴别和报文完整性检查, 以保证报文的安全性.

## IP Spoofing

* IP Spoofing: C可以截获A的IP地址( HMAC对报文头不加密, 因此可以获取IP地址 )，然后把A的IP地址冒充为自己的IP地址(这叫做IP欺骗). 不过IP Sproofing只能单向, 没啥用.

## Message Reordering

* C可以把两个报文重新排序, 更改其TCP `seq`号( 因为报文头没有被HMAC加密 ), 再发给B. 或者C可以干脆删除该报文. B就无法收到正确的信息了.



## Playback Attack

 **我们假设报文采用了HMAC, , 但还是会遇到实体鉴别问题**

* Playback Attack( 重放攻击 ): 
  1. 入侵者C可以从网络上截获A发给B的报文, C并不需要破译这个报文 ( 因为这可能得花很长时间 ）, 而是直接把这个由A加密的报文发送给B, 使B误认为C就是A. 
  2. 完成“实体鉴别后”, C就和B开始通信, B会向伪装成A的C发送许多本来应当发给A的报文.

* 重放攻击的关键在于, B无不知道他所受到的报文是来自A的, 还是来自攻击者C的playback. 导致B将这些报文视作属于同一个会话的.

* 这个问题和TCP连接时的三报文握手是一样的: 当server遇到一个 SYN segment 时, 它如何判断这个segment是否属于这次连接? 毕竟它也可能属于上一次连接. 

* TCP的解决方案是server向client发送的SYNACK报文中添加一个`seq`, 并等待client发来的ACK, 查看其中是否有`ack = seq + 1`. 

  也就是说, TCP server使用一个`seq`来维护一条连接. 对于不同的连接, 其`seq`不一样, 因此server能把重放攻击者和正常client区分.
  
  * 使用序列号之后, 对报文排了序. 也可以**顺便避免Message Reordering攻击**
  
    



在实体鉴别时采用**nonce**( 不重数 )来维护一个“鉴别会话”. 不重数就是一种`seq`, 在每次“鉴别会话”都不相同.. 因此, B和A的鉴别会话, 与B和重放者C的鉴别会话, 拥有不同的nounce, 也就**被视作两个会话**, B不会把A和C混淆.

当然, 为了保证鉴别会话的报文不被篡改, 还需要报文加密. 下图给出了采用对称加密的鉴别会话过程:



![End-point Authentication against Playback Attack](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/End-point%20Authentication%20against%20Playback%20Attack.png)







1. A首先用明文发送其身份A和一个不重数 $R_A$ 给B.
2. B响应A的查问，用共享的密钥$K_{AB}$ 对 $R_A$ 加密后发回给A，同时也给出了自己的不重数$R_B$
3. 最后, A再响应B的查问, 用共享的密钥$K_{AB}$ 对 $R_B$ 加密后发回给B. 
   * 这里很重要的一点是A和B对不同的会话必须使用不同的不重数集。由于不重数不能重复使用, 所以C在进行重放攻击时无法重复使用所截获的不重数.
4. B用$K_{AB}$对 $R_B$ 解密, 发现确实是自己发送的 $R_B$ , 就相信通信的对方是A.



对称加密,需要通信双方共享密钥. 为了省去这个麻烦, 似乎可以用非对称加密:

* 在前面的例子中, B可以用其私钥对不重数 $R_A$ 进行签名后发回给A. A用B的公钥核实签名, 如能得出自己原来发送的不重数 $R_A$ , 就核实了和自己通信的对方的确是B. 同样, A也用自己的私钥对不重数R B 进行签名后发送给B. B用A的公钥核实签名, 鉴别了A的身份.

  

上面的做法是有漏洞的, 让我们看下面的例子: 

1. C冒充是A，发送报文给B，说: ”我是A“
2. B选择一个不重数 $R_B$  , 发送给A，但被C截获了。
3. C用自己的私钥$SK_C$冒充是A的私钥，对 $R_B$ 加密，并发送给B。
4. B向A发送报文，要求对方把解密用的公钥发送过来，但这报文也被C截获了.
5. C把自己的公钥 $PK_C$ 冒充是A的公钥发送给B。
6. B用收到的公钥PK C 对收到的加密的 $R_B$ 进行解密，其结果当然正确. 于是B相信通信的对方是A，接着就向A发送许多敏感数据，但都被C截获了.

然而上述这种欺骗手段不够高明，因为B只要打电话询问一下A就能戳穿骗局，因为A根本没有和B进行通信。但下面的“中间人攻击 ”（man-in-the-middle attack）就更加具有欺骗性.

## man-in-the-middle attack

![man-in-the-middle attack](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/man-in-the-middle%20attack.png)

1. A想和B通信，向B发送“我是A”的报文, 并给出了自己的身份。这个报文被“中间人”C截获, C把这个报文原封不动地转发给B. B选择一个不重数 $R_B$ 发送给A，但同样被C截获后也照样转发给A.
2. 中间人C用自己的私钥 $SK_C$ 对 $R_B$ 加密后发回给B, 使B误以为是A发来的。A收到 $R_B$ 后也用自己的私钥 $SK_C$ 对 $R_B$ 加密后发回给B，但中途被C截获并丢弃. B向A索取其公钥，这个报文被C截获后转发给A.
3. C把自己的公钥 $PK_C$ 冒充是A的公钥发送给B，而C也截获到A发送给B的公钥$PK_A$ .
4. B用收到的公钥  $PK_C$ （以为是A的）对数据 DATA 加密，并发送给A.
5. C截获后用自己的私钥 $SK_C$  解密，复制一份留下, 然后再用A的公钥 $PK_A$ 对数据DATA 加密后发送给A.
6. A收到数据后，用自己的私钥 $SK_A$ 解密, 以为和B进行了保密通信. 其实, B发送给A的加密数据已被中间人C截获并解密了一份, 但A和B却都不知道.



# Key Distribution

密钥分配也是网络安全的重要问题. 

* 对于对称加密, 常见问题是对称密钥的分配很麻烦. 需要一个设施来进行自动化的密钥分配.
* 对于非对称加密, 常见问题是:**声称拥有某人密钥的人, 在现实中并不是某人** , 这也是**中间人攻击成功的原因**. 其实这是一个网络-现实中的实体鉴别问题. 
  * 实体鉴别只能对通信方在网络上的身份进行鉴别. , 但是,网络上的身份不一定就是现实中的身份, 比如, Trudy声称自己是Bob, 然后使用自己的私钥和Alice通信. 在Alice看来, 一切都是正常的, 实体鉴别也通过了. 问题在她鉴别的“Bob”身份只是网络上的, 在现实中, 这个人是Trudy.  Alice使用了所谓的Bob的密钥, 其实她使用的一直都是Trudy的. 
  * 因此需要有一个机构来在现实中进行鉴别, 建立网络 - 现实身份的映射

## Symmentric Key Distribution

* KDC( Key Distribution Center ): KDC是大家都信任的机构，其任务就是给需要进行秘密通信的用户临时分配一个会话密钥（仅使用一次）.

## Public Key Distribution

**认证中心CA ( Certification Authority )**: 一个权威机构, 用于接受用户认证, 向用户发放证书（certificate）, 证书内容是用户的公钥和个人信息( 比如IP, 人名... ). 

* CA对证书进行数字签名, 这样用户就保证了该证书真的属于改CA.
* 当然, CA的安全性取决于其权威性. 我自己也可以作为CA生成一个证书, 但是这样的证书肯定没人信.



使用CA的步骤:

1. 每个实体需要持有CA发的证书
2. 任何人想要获取该实体的公钥, 只需从CA处获取该实体的证书( 或者让该实体自己提供证书也行 ). 这样就能确保对方真的是现实中的那个人.
   * 比如说, 如果我用了数字签名, 你就可以拿我证书上的公钥和我的公钥比对一下, 这样就能确保我的身份,



# Securing Wireless LANs and 4G/5G Cellular Networks

在无线网络( 包括802.11 wireless LANs 和4G/5G cellular network )中, 攻击者可以嗅探到任何报文, 因此无线网络的安全很重要.  

## Authentication and Key Agreement in 802.11 Wireless LANs

* WIFI的网络安全有两个目标:
  * *Mutual authentication*: 如果移动设备要接入网络, 移动设备和网络需要互相鉴别
  * *Encryption*: 移动设备和access point (AP)通信的报文 ( 属于链路层frame ) 需要加密. 因为移动网络中的加密一般要求高速,所以采用对称加密.

* **Authentication Server** (AS) : WIFI还需要一个AS来负责鉴别. AP在鉴别时仅仅作为Mobile device和AS通信的桥接.



以下是一个Mobile device接入WIFI的过程:

![Authentication and Key Agreement in 802.11 Wireless LANs](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Authentication%20and%20Key%20Agreement%20in%20802.11%20Wireless%20LANs.png)





We can identify four distinct phases to the process of mutual authentication and encryption-key derivation and use in Figure 8.30:

1. *Discovery.* AP广播其存在, 然后mobile device与其通信. 此时还没有经过鉴别, 也没有生成链路层frame加密的密钥.
2. *Mutual authentication and shared symmetric key derivation.* : 详细过程在下面的*Mutual Authentication and Shared Symmetric Session Key Derivation*介绍
   1. 为了方便, mobile device都会和AS共享一个密钥( e.g. WIFI密码 )用于鉴别时加密, 双方通过这个密钥, nounce( 避免playback attack )和cryptographic hashing( 报文鉴别, 报文完整性 )来进行双向的实体鉴别. 
   2. 并且会生成一个对称( 如前所述, 我们一般用对称加密 )的session key, 用于**加密mobile device和AP间传输的链路层frame**.
      * 一般而言,对称加密算法是AES
3. *Shared symmetric session key distribution.* 步骤二中, mobile device和AS都拥有了session key, 此时还需要把session key也传输给AP. ( 不然mobile device和AP通信怎么加密呢.... )
4. *Encrypted communication between mobile device and a remote host **via the AP**.*



### **Mutual Authentication and Shared Symmetric Session Key Derivation**

* Wired Equivalent Privacy( WEP ): 就是WIFI网络的安全通信协议. WEP很快被WPA取代.
* WiFi Protected Access( WPA ): 就是WEP的改进版.目前都用的WPA3( 2018年发布 )
  * WEP a **four-way handshake** protocol
  * 作用:
    * mutual authentication
    * shared symmetric session-key derivation





![Mutual Authentication and Shared Symmetric Session Key Derivation](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Mutual%20Authentication%20and%20Shared%20Symmetric%20Session%20Key%20Derivation.png)

如图, WPA工作流程为:

0. Mobile device( M )和AS事先会共享一个密钥( 比如WIFI密码 ), 记为$K_{AS-M}$
1. AS生成一个NonceAS发给M, 这用于避免重放攻击
2. M收到NonceAS, 并生成它自己的NonceM. 然后M使用NonceAS, NonceM, $K_{AS-M}$, 其MAC地址和AS的MAC地址生成symmentric session key $K_{M-AP}$. 然后将NonceM 和 一个HMAC加密的值( 包括了 $K_{AS-M}$ 和 NounceAS )发给AS
3. AS通过decode HMAC, 得到NonceAS, 确认了M不是重放攻击. 同时得到了$K_{AS-M}$, 完成了实体鉴别( 即对方确实是拥有这个 $K_{AS-M}$ 的设备). AS然后执行和M一样的操作, 用它收到的NonceAS, NonceM, $K_{AS-M}$, 其MAC地址和M的MAC地址生成$K_{M-AP}$. 因为和M的参数一样, 它们推导出的 $K_{M-AP}$ 也一样.  接下来 $K_{M-AP}$ 会被通知给AP

### 802.11 Security Messaging Protocols

* Extensible Authentication Protocol (EAP): M和AS通信时采用的协议. 
  * 注意到M和AS其实是端到端的request/response通信. 因此EAP是一个端到端协议.
  * EAP是链路层协议. 数据封装成EAPoL (EAP over LAN) 在WIFI链路上传输. AP收到后, 使用RADIUS protoco( or DIAMETER protocol )来解包为通用的链路层协议( TCP/UDP ) ,然后发给AS.

![EAP](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/EAP.png)

## Authentication and Key Agreement in 4G/5G Cellular Networks

* 4G/5G蜂窝网络的安全性要求和WIFI差不多, 都需要:
  * 双向鉴别: 基站当然有必要鉴别手机. 但因为基站也有可能被黑, 所以手机也有必要鉴别基站....
  * 加密: 手机和基站依然需要生成一个对称加密密钥, 用来加密M和BS之间通信的链路层frame

### AKA Protocol in 4G

* 4G/5G蜂窝网络的鉴别和加密协议为AKA( Authentication and Key Agreement (AKA) protocol ), 它规定了如下步骤:

  



![AKA](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/AKA.png)

0. 和WIFI一样, 手机和HSS之间需要共享一个密钥$K_{HSS-M}$用于鉴别时的加密. 和WIFI的密钥一般就是WIFI密码不同, $K_{HSS-M}$一般存在手机的SIM卡和HSS database里.

1. *Authentication request to HSS.* 当mobile device第一次通过基站请求加入网络时, 它将发送一个包含其 international mobile subscriber identity (IMSI) 的sttach message, 基站会把该信息转发给被访网络( visited network, 图中称为VN )的MME. 然后MME把**IMSI和VN的信息**发送给家庭网络的HSS.

   * IMSI在4G中被明文传输.

2. *Authentication response from HSS.* HSS使用预先共享的$K_{HSS-M}$进行加密, 以获得一个认证令牌auth_token = $K_{HSS-M}(IMSI)$和 一个expected authentication response token $xres_{HSS}$.  前者最终被转发给mobile device, 后者发给MME.

3. *Authentication response from mobile device.* mobile device收到auth_token后解密得到IMSI:
   $$
   K_{HSS-M}(K_{HSS-M}(IMSI)) = IMSI
   $$
   mobile device于是知道了该HSS拥有$K_{HSS-M}$, mobile device因此就**鉴别了蜂窝网络** ( HSS和MME就是蜂窝网络的AS ).

   并且, mobile device会使用和HSS相同的算法计算出$xres_{M}$, 只是使用了自己的key ( $K_{HSS-M}$) , 并将其$K_{HSS-M}$发送给MME

4. *Mobile device authentication.* MME比对$xres_{M}$ 和  $xres_{HSS}$ , 由于HSS和mobile device拥有相同的$K_{HSS-M}$, 因此:
   $$
   xres_{M} == xres_{HSS}
   $$
   MME于是知道了mobile device拥有和HSS相同的key ,因此蜂窝网络**鉴别了mobile device** . 

   * 这里MME的作用类似WIFI中的AP, 仅仅是一个中介, 不需要知道$K_{HSS-M}$. 和WIFI中不同的是, MME在这里做了认证决定.

5. *Data plane and control plane key derivation.* 步骤1~4完成了双向鉴别, 接下来mobile device就和基站共同生成了symmentric session key, 过程和WIFI中的一样. sesssion key用于加密蜂窝网络的链路层frame, 当然, data plane 和 control plane通信是不同的, 因此需要生成两个key.

   * 加密算法是AES, 和WIFI一样



### Changes in 5G

1. 5G的鉴别和加密协议是AKA' , 它继承了4G的AKA 此外, 5G还采用了WIFI中的EAP, 因此报文格式和4G的不同. 并且5G还新增了一个协议用于IoT场景, 该协议不需要$K_{HSS-M}$
2. 4G的鉴别中, 是被访网络的MME做了mobile device的鉴别决定, 在5G中, 一般都由家庭网络来进行这个鉴别.
3. 5G中的IMSI是被非对称加密的.

关于4G/5G安全的更多细节: [3GPP SAE 2019; Cable Labs 2019; Cichonski 2017]



# Operational Security

三大组件:

1. Firewall
2. Intrusion Detection System ( IDS )
3. Intrusion Prevention Systems (IPS)



使用防火墙, IDS等技术肯定会让网络变慢. 因此一般会把网络划分为不同区域. 需要与外网连接的那些服务器被分到防御较宽松的**demilita- rized zone (DMZ)**, 其他服务器被分到防御更严格的区域:

![Operational Security](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Operational%20Security.png)

* 注意, IDS等设施同一时间要计算无数个报文, 工作量很大. 因此一般在网络中部署多个IDS, 达到分治的效果, 如上图所示.

## Firewalls

* A **firewall** is a combination of hardware and software that isolates an organization’s internal network from the Internet at large, allowing some packets to pass and blocking others

* Firewalls can be classified in 2 categories: 

  1. packet filters: 工作在传输层, 是一种具有分组过滤功能的<u>路由器</u>，它根据过滤规则对进出内部网络的分组执行转发或者丢弃. 
  2. application gateways: 也称为Proxy Server( 代理服务器 )工作在应用层, 就是一个应用层APP, 用来在应用层监控某个应用发出在报文.
     * An **application gateway** is an <u>application-specific</u> server through which all application data (inbound and out- bound) must pass. 

* 分组过滤器和应用网关可以结合使用, 如图:

  ![packet filters plus application gateways](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/packet%20filters%20plus%20application%20gateways.png)

### Packet Filters

* 分组过滤器分为两种:
  * 无状态: 独立地处理每一个分组.
  * 有状态: 会跟踪每个连接或会话的通信状态，并根据这些状态信息来决定是否转发分组.

* 以无状态过滤器为例, 假设要保护的网络是130.207/16, 它要和一个Web server at 130.207.244.203 通信:

  | Policy                                                       | Policy Firewall Setting                                      |
  | ------------------------------------------------------------ | ------------------------------------------------------------ |
  | No outside Web access.                                       | Drop all outgoing packets to any IP address, port 80.        |
  | No incoming TCP connections, except those for organization’s public Web server only. | Drop all incoming TCP SYN packets to any IP except 130.207.244.203, port 80. |
  | Prevent Web-radios from eating up the available bandwidth.   | Drop all incoming UDP packets—except DNS packets.            |
  | Prevent your network from being used for a  smurf DoS attack. | Drop all ICMP ping packets going to a “broadcast” address (eg 130.207.255.25) |
  | Prevent your network from being tracerouted.                 | Drop all outgoing ICMP TTL expired traffic.                  |

  上表中只是抽象的规则, 具体的规则存储在ACL. 



#### ACL

* ACL( access control list ): 就是 packet filters 里的过滤规则.  
  * 比如, 如果想要禁止所有的TCP连接的建立, 只要过滤掉所有ACK = 0的报文 ( 因为TCP中, 只有连接建立时第一个报文的ACK = 0, 此后所有的报文都有ACK =1 )
  * 如果想要禁止员工看视频, 可以把不必要的UDP报文都过滤掉. 当然DNS之类的服务也使用UDP, 这些不能过滤
* ACL自顶而下<u>顺序匹配</u>.
  * When a statement “matches,” no more statements are evaluated. 
  * The packet is either permitted or denied.
* There is an implicit “<u>deny any</u>” statement at the end of the ACL. If a packet does not match any of the statements in the ACL, it is dropped. 下面例子的表中显式地给出了这条规则, 



* 下面是一个例子, 该防火墙要保护的网络是222.22/16

  | action | source address       | dest address         | prototol | source port | dest port |
  | ------ | -------------------- | -------------------- | -------- | ----------- | --------- |
  | allow  | 222.22/16            | outside of 222.22/16 | TCP      | \> 1023     | any       |
  | allow  | outside of 222.22/16 | 222.22/16            | TCP      | 80          | \> 1023   |
  | allow  | 222.22/16            | outside of 222.22/16 | UDP      | \> 1023     | 53        |
  | allow  | outside of 222.22/16 | 222.22/16            | UDP      | 53          | \> 1023   |
  | deny   | all                  | all                  | all      | all         | all       |

  1. 前两条规则允许网络内部的主机**单向**地访问Web:

     1. 第一条规则允许TCP packet with destination port 80 离开网络, 即允许主机单方面发出TCP请求

     2. 第二条规则允许TCP packet with source port 80 and the ACK bit set进入网络, 即允许主机接受对方的TCP请求. 

        注意, 由于不允许外部主机的ACK = 0进入网络( 因此无法建立TCP连接 ), 所以外部主机是无法用TCP访问内部主机的. 因此是“单向”

  2. 接下来两条规则允许所有DNS packets进出网络.

  3. 最后一条规则就是deny any, 它是默认的, 禁止了除上述规则匹配的分组之外的所有其他分组.



* ACL其实和路由表长得差不多

### Application Gateways

* 相比工作在传输层的报文过滤器, 应用网关的控制能力更强更灵活. 
  * 比如, 组织可能希望某些内部人员必须先在内网进行登录认证后, 才能访问外网. 而“登录认证”的数据属于应用层, 不属于IP/TCP/UDP. 这一级别的访问控制只能由应用网关来处理.

## IDS

* IDS: 防火墙只能对分组进行简单的检查, 像上面所介绍的, 只能检查地址,协议类型等, 因此很容易被攻破. IDS能对分组进行深度检查, 并对可疑分组发出alert

* IDS分两种:

  * Signature-based IDS( 基于特征的IDS ): 维护一个所有已知攻击标志性特征的数据库, 每个特征是一个与某种入侵活动相关联的规则集. 这些规则一般是手动输入的.
    * 基于特征的IDS只能检测已知攻击，对于未知攻击则束手无策. 而且即使某个报文匹配了某条规则, 它也不一定就是个有害报文.

  * Anomaly-based IDS( 基于异常的IDS ):通过观察正常运行的网络流量来动态判断. 不过区分正常和异常流量很困难, 所以基于异常的IDS能力有限

* 目前最常用的开源IDS是Snort, 它是Signature-based IDS.

## IPS

* IPS: 和IDS配套使用, 在IDS发出alert后, IPS负责把可疑分组清除

## EXP: ANONYMITY AND PRIVACY

假如我要访问一个奇怪的网站( 比如, 某个含有不当言论的网站 ), 我想要:

1. 不让网站知道我的IP
2. 不让我的local ISP知道我在访问这个网站, 也就是不让ISP知道我的目的IP
3. 不让local ISP知道我和网站通信交换的报文.

只使用SSL是不行的, SSL只能加密报文payload, 但是不能加密源和目的IP地址, 所以无法满足要求1, 2.



正确做法是使用Proxy Server( 代理服务器, 也就是应用网关 ) + SSL:

![Example: ANONYMITY AND PRIVACY](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Network%20Security/Example-%20ANONYMITY%20AND%20PRIVACY.png)

1. 我使用SSL和代理服务器通信, 我向代理服务器发送的HTTP报文都是SSL加密的. 
2. 报文被代理服务器解密发给网站.
3. 代理服务器和网站通信, 它们之间的报文不需要加密.
4. 网站发给代理服务器的报文被SSL加密后传给我.

这种方式下, 代理服务器的IP作为ISP看到的的目的IP和网站看到的源IP. 数据也被SSL保护. 问题在于, 代理服务器会知道一切( 我的源IP, 目的IP, 我的数据 ), 因此这种方法的安全性取决于代理服务器的安全性.



更好的方法是采用[TOR](https://zh.wikipedia.org/zh-my/Tor), 它使用一个 Proxy Server Pool, 其中每个Proxy Server都是不互通的( non-colluding ). 每次通信随机从中选一个Proxy Server. [[TOR 2020]



