---
title: Security in Internet
tags:
  - Computer Networking
  - Network Security
categories: Computer Science
mathjax: true
date: 2022-08-28 01:19:48
---


Outline:

* Intro
* Transport Layer:  TLS
* Network-Layer: IPsec and VPN
* Application Layer: Securing E-Mail

<!--more-->

# Intro

先指出一些误解:

* “只要在低层, 比如IP层, 提供安全协议, IP层及以上的层就都安全了.” 这是错误的, 因为IP报文的内容安全, 不意味着应用层数据安全. 其他层也是同理.
* "在高层实现安全后, 底层可以不用实现安全": 这显然是错的. 最简单的例子, 应用层程序只能改变报文内容, 不能改变报文头, 而很多攻击就是针对报文头的. 因此低层协议也有必要实现安全.



因此, 需要在计算机网络的每一层都采取措施, 使得该层的通信安全.

## Assumptions

本文和[Network Security](https://lyk-love.cn/2022/08/28/Network-Security/#more) 一样, 以Bob, Alice 和 Trudy 的三角恋为例

# Transport Layer:  TLS

* 运输层的安全协议是TLS( Transport Layer Security ), 它的更早期版本是SSL( Secure Socket Layer ) version3. 

  * 我们有时候也用SSL指代TLS.

* SSL( or TLS )位于网络层和运输层之间, 对**TCP**做了增强. 在开发者角度, SSL属于传输层.

  ![TLS](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/TLS.png)

  * 在发送方，SSL从SSL套接字接收应用层的数据( 如HTTP或IMAP报文 ), 对数据进行加密，然后把加密的数据送往TCP套接字; 在接收方，SSL从TCP套接字读取数据, 解密后, 通过SSL套接字把数据交给应用层.
  * 如果HTTP用了TLS, 则域名的协议名会变成`https`
  * SSL并非仅用于HTTP, 而是可用于任何应用层的协议. 例如，SSL也可用于IMAP邮件存取的鉴别和数据加密.
  * TCP的HTTPS端口号是443，而不是平时使用的端口号80

* SSL提供的安全服务可归纳为以下三种：

  1. 加密
  2. 报文完整性
  3. 鉴别, 包括报文鉴别, 实体鉴别, 以及允许SSL client查看server的CA. 
     * 当然SSL server也可以查看客户的CA, 这是可选的.



## TLS Connection Setup

TLS协议有三个阶段: *handshake*, *key derivation*, and *data transfer*.



### Handshake

![TLS Handshake](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/TLS%20Handshake.png)

1. Bob和Alice建立TCP连接.

   * TCP连接建立后, Bob和Alice就开始正式的TLS连接建立, 它们的数据传输单元就变成了TLS **Record**

2. Bob向Alice发一个message( TLS hello ). Alice将以下内容发送给Bob:

   * 可供选择的非对称加密算法( 例如, RSA with a specific key length ), 用于后续EMS的加解密
   * 可供选择的HMAC算法( 例如SHA-3或MD6 ), 用于后续的HMAC计算
* 一个nounce, 相当于TCP里的`seq`. 使用nounce可以避免message reordering等问题, 还可以避免重放攻击. 
     * 后面通信中的报文都会带有nounce, 为了叙述方便我就省略了.
   * Alice自己的证书, 其中包含了自己的公钥
     * 由于证书由CA颁发, Alice于是就证明了自己确实是Alice

   这一步完成了算法协商, 以及Alice的实体鉴别. 

3. Bob生成一个Master Secret (MS) (which will only be used for this TLS session), 用Alice的公钥加密成为Encrypted Master Secret (EMS), 然后发给Alice. Alice会用私钥解密EMS, 得到MS. 



Handshake结束后, Bob和Alice都知道MS了.



### Key Derivation

你可能会认为Bob和Alice将把MS作为对称加密的密钥. 然而TLS做得更加复杂. MS被用来生成以下四个密钥:

- $\mathrm{E_B}$ = session encryption key for data sent from Bob to Alice
- $\mathrm{M_B}$ = session HMAC key for data sent from Bob to Alice, where HMAC [RFC 2104] is a standardized hashed message authentication code (MAC) that we encountered in section 8.3.2
- $\mathrm{E_A}$= session encryption key for data sent from Alice to Bob
- $\mathrm{M_A}$ = session HMAC key for data sent from Alice to Bob



Bob和Alice各自用自己的MS生成这四个密钥, 由于两人的MS相同, 生成的密钥也是一样的. 这四个密钥中, 两个用于数据加密, 两个用于HMAC.

* 根据MS生成四个密钥的步骤比较复杂, 这里不详细介绍了.



### Data Transfer

数据传输过程依然采用TLS record作为数据传输单元

1. Bob在要传输的DATA后添加HMAC
   * HMAC根据DATA, 使用密钥 $\mathrm{M_B}$ 生成
2. Bob将DATA + HMAC一起用密钥  $\mathrm{E_B}$  加密, 发给Alice
   * 注意, 我们之前学的采用MAC的实体鉴别<u>只会对MAC加密</u>. 但这里把DATA + MAC一起加密了.
3. Alice收到后, 用 $\mathrm{E_A}$ 解密DATA + HMAC, 再用 $\mathrm{M_A}$ 检查HMAC, 进行报文鉴别和报文完整性检查. 后续Alice向Bob的通信也同理.

TLS breaks the data stream into records, appends an HMAC to each record for integrity checking, and then encrypts the record + HMAC. To create the HMAC, Bob inputs the record data along with the key MB into a hash function, as discussed in Section 8.3. To encrypt the package record + HMAC, Bob uses his session encryption key EB.

## TLS Connection Closure

* *truncation attack*: 错误的想法是, Bob和Alice只断开TCP连接就可以断开TLS连接. 问题在于**TCP是不安全的**, Trudy可以伪造一个Bob发送的TCP FIN报文给Alice, 这样Bob和Alice就无法通信了. 这种攻击称为truncation attack.
  * 因此, TLS也有自己的连接释放报文. 使用TLS时先释放TLS连接, 再释放TCP连接.

## TLS Record

![TLS Record](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/TLS%20Record.png)

* Type: 表明该Record是TLS Handshake报文, TLS Data Tranfer报文 还是 TLS连接释放报文

  



# Network-Layer: IPsec and VPN

虚拟专用网VPN时中传送的信息都经过IPsec加密.

IPsec并不是一个单一协议, 而是能够在IP层提供互联网通信安全的<u>协议族</u> （不太严格的名词“IPsec协议”也常见到）.IPsec并没有限定用户必须使用何种特定的加密和鉴别算法。实际上，IPsec是个框架，它允许通信双方选择合适的算法和参数.

为保证互操作性，IPsec还包含了一套加密算法，所有IPsec的实现都必须使用。



IPsec协议族中的协议分为以下三部分：

1. IP安全数据报格式的两个协议：鉴别首部AH （Authentication Header）协议 和 封装安全有效载荷ESP （Encapsulation Security Payload）协议.
   * 使用ESP或AH协议的IP数据报称为IPsec datagram
2. 有关加密算法的三个协议( 在此不讨论 )
3. 互联网密钥交换 IKE（Internet Key Exchange）协议

## AH and ESP

In the IPsec protocol suite, there are two principal protocols: the **Authentication Header (AH)** protocol and the **Encapsulation Security Payload (ESP)** protocol.

AH协议提供源点鉴别和数据完整性，但不能保密。而ESP比AH协议复杂得多，它提供源点鉴别、数据完整性和保密。IPsec支持IPv4和IPv6。在IPv6中，AH和ESP都是扩展首部的一部分。AH协议的功能都已包含在ESP中，因此使用ESP就可以不使用AH协议。下面我们将不再讨论AH协议，而只介绍ESP.

## Security Associations

* 安全关联SA （Security Association ): 在源实体和目的实体之间创建的网络层的逻辑连接. 因为网络层不一定是有连接的( UDP就是无连接的 ), IPsec需要SA来确保连接建立.
  * 为了节约资源, SA是**单向连接**
* 安全关联数据库 SAD（Security Association Database）: 一个 IPsec entity 把它的所有SA都存在SAD里. 当它要发送 IPsec数据报时, 就在SAD中查找相应的SA.
  * SAD在OS kernel中
* 安全策略数据库 SPD ( Security Policy Database ) : 一个主机需要判断哪些数据包要进行IPsec处理处理.  为此它需要维护一个SPD, 指明过滤规则. 这取决于源地址、源端口、目的地址、目的端口，以及协议的类型等.
  * 一个路由器可以同时转发很多分组, 它会通过查找SPD来决定哪些分组需要IPsec
* SA的内容包括:
  - A 32-bit identifier for the SA, called the **Security Parameter Index (SPI, 安全参数索引)**
  - 安全关联SA的源点和终点的IP地址（即路由器R 1 和R 2 的IP地址, 在这里就是200.168.1.100 和 193.68.2.23
  - The type of encryption to be used (for example, 3DES with CBC)
  - The encryption key
  - 报文完整性和鉴别的类型 ( for example, HMAC with SHA-3 )
  - The authentication key

## Example

假设公司总部和分公司各有路由器 R1 和 R2 (通常就是公司总部和分公司的防火墙中的路由器 ), R1和R2建立SA.

![SA Example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/SA%20Example.png)

现假定公司总部的主机H1 要和分公司的主机H2 通过互联网进行安全通信:

1. H1 发送给 H2 的IP datagram, 必须先经过R1, 然后经IPsec的加密处理后，成为IPsec datagram. 其首部目的地址是R2
2. IPIPsec datagram 经过互联网中很多路由器的转发, 最后到达R2
3. R2对IPsec datagram解密, 还原出原始的IP datagram, 原始IP datagram的首部目的地址是H2
4. R2把IP datagram发到H2

* 如果总部的主机H1 要和总部的另一台主机H3 通信, 由于都在公司内部, 不需要加密( 不使用IPsec), 因此不需要建立SA
* 从逻辑上看，IPsec datagram在SA上传送, 就好像通过一个安全的隧道. 这就是"tunnel mode".

## IPsec Datagram

* IPsec has two different packet forms:
  * **tunnel mode** : 在原始的IP数据报的前后分别添加若干控制信息，再加上新的IP首部，构成一个IP安全数据报
  * **transport mode**. 在整个<u>运输层</u>报文段的前后分别添加若干控制信息，再加上IP首部，构成IP安全数据报
    * 我们**只讨论 tunnel model**, 因为VPN中广泛使用tunnel mode

* 无论使用哪种方式，最后得到的IPsec datagram的IP header都是**不加密**的, 否则互联网上的路由器就没法识别IP首部并进行转发了.

* 通常把IP datagram的数据部分称为datagram的payload.
  * ESP IPsec datagramd的数据部分就是IP datagram. 因此ESP payload就是IP datagram.

---

我们假设公司总部的H1( 172.16.1.17 ) 向R1发送了IPv4 datagram, 目的地是公司分部的H2( 172.16.2.48 ). H1, H2不在同一个局域网, 二者通过VPN相连( 也就需要IPsec ). R1将 IPv4 datagram作为Payload, 转化成IPsec datagram:



![IPsec Datagram](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/IPsec%20Datagram.png)



- Appends to the back of the original IPv4 datagram (which includes the original header fields!) an “ESP trailer” field
  * the ESP trailer consists of three fields: 
    1. padding: 用全0填充.
    2. pad length: 指出padding的字节数. 
       * padding的目的是便于Block Cypher进行加密计算. 参见 *[Network Security](https://lyk-love.cn/2022/08/28/Network-Security/#more) -> Confidentiality -> Symmetric Key System -> Block Cipher*
    3. next header: 指ESP payload的协议类型. 
       * 这里是tunnel mode, 因此ESP payload就是original IPv4 datagram, 它是IP协议. 
       * 如果是transport mode, 那么ESP payload就是传输层报文段( TCP, UDP segment ), 它是传输层协议
  * The next header identifies the type (e.g., UDP) of data contained in the payload-data field. The payload data (typically the original IP datagram) and the ESP trailer are concatenated and then encrypted.
- **Encrypts the result( ESP payload + ESP tailer )** using the algorithm and key specified by the SA
- Appends to the front of this encrypted quantity a field called “ESP header”; the resulting package is called the “enchilada”
  * ESP header 不加密, 它包括两个field:
    * 安全参数索引SPI: 用于标识一个SA. SPI可以作为SAD和SPD中的键.
    * sequence number: 作用和TCP序号类似, 用于避免重放攻击
- <u>Creates an authentication MAC over the *whole enchilada*</u> using the algorithm and key specified in the SA
- Appends the MAC to the back of the enchilada forming the *payload*
- 生成新的IP首部, 它和普通的IP数据报的首部的格式一样( normally 20 bytes long). 首部中的协议字段值是50, 表明这其实是个IPsec datagram using the ESP protocol.
  * 最后生成的IPsec datagram在在格式上属于IP datagram, 但它的payload包括了: ESP header, 原始的IPsec datagram, ESP tailer, ESP MAC.



R2收到该datagram后, 查看其首部的协议字段号, 发现是50, 就把它作为IPsec datagram using the ESP protocol 处理:

1. 查看enchilada, 根据SPI来确定该报文属于哪条SA.
2. 重新根据enchilada计算MAC, 然后和报文中的ESP MAC比对, 验证报文完整性且进行报文鉴别.
3. 检查sequence-number field来确保这不是一个重放的报文.
4. 根据SA中的信息( 该SA使用的加解密算法, 使用的Key )将加密部分( original IP datagram + ESPtailer )解密.
5. 去掉padding, 得到original IP datagram.
6. 对该original IP datagram进行转发.



注意到, 如果IPsec datagram被人截获, 则:

1.  截获者无法对其解密, 也就无法知道original IP datagram的内容. 
2.  由于IPsec datagram使用了MAC, 截获者无法篡改IPsec datagram的内容.
3.  由于IPsec datagram使用了sequence-number, 因此截获者无法进行重放攻击.

## IKE

* 互联网密钥交换 IKE（Internet Key Exchange）协议: an automated mechanism for creating the SAs
  * IKE非常复杂

# Application Layer: Securing E-Mail

我们以E-Mail为例介绍应用层安全的实现.

E-Mail安全要实现以下几点:

1. 内容加密
2. 报文完整性检查
3. 双向鉴别

此外, 对于电子邮件, 双方要共享对称密钥比较困难, 因此一般用非对称加密.



Secure E-Mail的发送过程大概如下:

![Securing E-Mail](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Security%20in%20Internet/Securing%20E-Mail.png)

1. 首先, Alice使用HMAC计算明文m的报文摘要 $H(m)$ , 然后用自己的私钥$K_A^-$ 加密 $H(M)$ , 得到 $K_A^-(H(M))$. 把m和 $K_A^-(H(M))$ 连接在一起, 作为一个 preliminary package 
   * 这一步实现了**发送方鉴别和报文完整性**.  <u>如果Alice身份属实</u>, 那么后面Bob可以用Alice的公钥 $K_A^+$  来解密$K_A^-(H(M))$得到 $H(M)$ , 将其和自己根据m计算的 $H(M)$ 比对. 如果正确, 则既证明了 $K_A^+$  确实属于Alice( 发送方鉴别 ), 也证明了报文完整性.
2. 接着, Alice随机选择一个数作为session key $K_S$ , 用 $K_S$ 将 preliminary package 加密, 记为 $K_S(.)$ . 并且用Bob的公钥 $K_B^+$ 加密 $K_S$ . 记为 $K_B(K_s)$ . 将二者连接在一起, 发给Bob.
   * 这一步实现了**接收方鉴别和报文加密**. <u>如果Bob身份属实</u>, 那么Bob应该可以用自己的私钥 $K_B^-$  解密得到 session key  $K_S$  , 再用  $K_S$ 解密得到preliminary package . 再进行步骤一所述的验证, 如果正确, 则既证明了  $K_B^+$ 确实属于Bob( 接收方鉴别 ), 又使用 $K_S$ 实现了报文加密.

上述过程使用了非对称加密, 对于E-Mail使用者, 可以自己生成公钥, 把它放在个人主页上. 当然也可以去CA注册得到证书, 对方要获得自己的公钥可以去CA查. 





目前常用的Secure E-Mail实现是[GPG](https://lyk-love.cn/2022/02/10/GPG/)(  GPG是GNU的开源软件, 参考自功能相同的商业软件PGP ), 它的逻辑和上面所述的差不多.
