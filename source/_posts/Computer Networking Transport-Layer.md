---
title: Transport Layer
tags: Computer Networking
categories: Computer Science
mathjax: true
date: 2022-07-05 16:47:03
---


Outline:

* Intro
* UDP
* TCP
* 可靠传输
* TCP Flow Conteol
* TCP Congestion Conteol

<!--more-->

# Intro

网络层(IP)为**主机**之间提供了逻辑通信， 而运输层为**进程**之间提供了端到端的逻辑通信

* 逻辑通信就是好像两个对等实体(无论是网络层的实体(主机)还是运输层的实体(进程))之间有一条水平方向的信道
* 运输层的端到端通信， 是**进程**间的通信



## 运输层的作用

![Transport Layer](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/Transport%20Layer.png)

* 复用( multiplexing )：client的不同进程都可以使用同一个运输层协议发送数据到网络层
* 分用( demultiplexing ): server的运输层在从网络层收到发送给各进程的数据后，可以分别交付给目的进程， 即server的不同进程可以用同一个运输层协议接收数据
* 对报文进行差错检测

## 运输层的协议

运输层协议主要有面向连接的TCP和无连接的UDP。 两种协议在协议栈中的位置：

![Transport Layer in Network Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/Transport%20Layer%20in%20Network%20Arch.png)



* TCP的数据传输单元称为TCP报文段( TCP Segment )

* UDP的数据传输单元称为UDP用户数据报( UDP Diagram )



以下给出应用层协议主要使用的运输层协议:

| 应用             | 应用层协议                        | 运输层协议 |
| ---------------- | --------------------------------- | ---------- |
| 域名 --- IP 映射 | DNS                               | UDP        |
| 文件传送         | TFTP                              | UDP        |
| 路由选择         | RIP（Router Informatio Protocal） | UDP        |
| IP分配           | DHCP                              | UDP        |
| 远程文件服务器   | NFS( Network File System )        | UDP        |
| 多播             | IGMP                              | UDP        |
| Email            | SMTP                              | TCP        |
| 远程终端接入     | TELNET                            | TCP        |
| 万维网           | HTTP                              | TCP        |
| 文件传送         | FTP                               | TCP        |
|                  |                                   |            |

## Socket && port

* 套接字( Socket ): 网络通信中的进程的唯一标识， 格式为`( IP : port )`

* 协议端口号( protocal port number ): 简称端口( port )，用来唯一标识一个本机的（应用层）进程
  * 数据通过IP发送到对应的主机， 主机上的运输层协议再通过端口来找到对应的应用层进程, 即: **端口是本机的应用层进程和运输层协议交互的一种地址**
  * 在本机中，进程也可以通过PID标识，不同的OS拥有不同格式的PID，格式无法统一，因此无法用于运输层与应用层的交互
  * 这里的“端口”是软件端口， 与用于硬件设备交互的硬件端口不同
* 端口有16位, 即 0 ~ 65535， 可分为:
  * server port: 0 ~ 49151
    * well-known port: 0 ~ 1023, 被保留用于一些常见的程序，如HTTP(80), FTP(21)
    * register port: 1024 ~ 49151，被用于没有well-known port的程序
  * client port: 49152 ~ 65535xs



| 端口号 | 服务进程 | 说明                     |
| ------ | -------- | ------------------------ |
| 7      | echo     | 将收到的数据报送到服务器 |
| 9      | Discard  | 丢弃任何收到的数据报     |
| 21     | FTP      | 活跃的用户               |
| 25     | SMTP     | 简单邮件传输协议         |
| 53     | DNS      |                          |
| 69     | HTTP     |                          |
| 161    | SNMP     |                          |
| 443    | HTTPS    |                          |
| 23     | Telnet   | 虚拟终端网络             |
|        |          |                          |



# UDP

Features:

1. 无连接
2. 不可靠传输
3. 面向报文：即将报文剥去/添加UDP头后转交给上/下层， 不进行任何的合并/拆分。这意味着进程必须选择合适大小的报文，若报文过长，IP层会进行分片；若报文太短，则会使得IP数据报的首部的相对长度较大，两种情况都会降低IP层效率
4. 没有拥塞控制
5. 首部开销小，只有 8 Byte

## UDP通信过程



![UDP communication prodedure](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/UDP%20communication%20prodedure.png)

## UDP Diagram

UDP Diagram分为Header和Dara两部分

* Header是固定的8 Byte



![UDP Diagram](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/UDP%20Diagram.png)



 Header各字段如下:

1. 源端口：源端口号；在需要对方回信时选用；不需要时用全0 

2. 目的端口：目的端口号；在终点交付报文时必须使用

3. 长度：UDP用户数据报的长度，最小值是8(仅有首部)

4. checksum：检测UDP用户数据报在传输过程中是否有错。有就丢弃

   * 在计算checksum时，需要在UDP报文之前增加12 Byte的"伪首部"( 其结构和内容见上图 ), 伪首部不是报文的一部分，只是在计算checksum时临时添加的

   ​     



如果Receiver的UDP发现收到的报文中的目的端口号非法( 比如，没有进程监听该端口 ), 就会丢弃该报文并由ICMP发送一个"port unreachable"差错报文（ type=3, code=3）给Sender

## 常用的UDP程序



## Example

流程图见上文"UDP通信过程"

### UDP Client

```python
from socket import *
serverName = 'localhost' # 服务器地址，可以是IP或者域名，如果是域名，则会进行DNS lookup
serverPort = 12000 # 服务器指定的端口

# 创建Client Socker
# AF_INET：表明IP采用IPv4
# SOCK_DGRAM:表明这是个UDP Socket
clientSocket = socket(AF_INET, SOCK_DGRAM) # 创建UDP套接字，使用IPv4协议

message = input('Input lowercase sentence:').encode() # 用户输入信息，并编码为bytes以便发送
clientSocket.sendto(message, (serverName, serverPort)) # 将信息发送到服务器

# 从服务器接收信息，同时也能得到服务器地址(当然，其实Client已经知道了Server IP，因此这个信息是多余的)
# 缓存长度2048
modifiedMessage, serverAddress = clientSocket.recvfrom(2048) 
print(modifiedMessage.decode()) # 显示信息
clientSocket.close() # 关闭套接字
```



### UDP Server

```python
from socket import *
serverPort = 12000 # 服务器指定的端口
serverSocket = socket(AF_INET, SOCK_DGRAM) # 创建UDP套接字，使用IPv4协议
serverSocket.bind(('',serverPort)) # 将套接字绑定到之前指定的端口
print("The server is ready to receive")
while True: # 服务器将一直接收UDP报文
	message, clientAddress = serverSocket.recvfrom(2048) # 接收客户端信息，同时获得客户端地址
	modifiedMessage = message.upper() # 将客户端发来的字符串变为大写
	serverSocket.sendto(modifiedMessage, clientAddress) # 通过已经获得的client地址，将修改后的字符串发回client户端
```





# TCP



Featues:

1. 面向连接，且连接是**点对点** 即以Socket为进程的地址，一对一通信)的

   * TCP无法提供多播

2. 可靠传输

3. 全双工通信

4. 面向字节流：虽然进程与TCP的交互以数据块（大小不等）为单位， 但TCP将应用层的数据仅仅看成无结构的字节流。 发送方的进程把数据写入TCP的**发送缓存**，接收方的进程从TCP的**接收缓存**中读取字节流

   * 发送缓存实际上是发送窗口的超集，二者的关系详见下文*滑动窗口与缓存*

   ![TCP Procedure](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20Procedure.png)

## TCP连接

* TCO连接的端点就是Socket，每条TCP连接唯一地被两个端点确定：

   TCP连接::={socket1,socket2} = {(IP1:port1),(IP2:port2)}



## TCP数据传输

当TCP连接建立后，两个进程就可以发送数据了

* 发送缓存：应用程序将要发送的数据通过Socket传递给TCP，TCP将数据引导到该连接的发送缓存，**发送缓存**大小是在三阶段握手的过程中确定的；之后TCP将时不时地从该缓存中拿出数据，封装成报文段进行发送
  * TCP规范中**没有规定TCP应该在何时发送缓存里的数据**，描述为“TCP应该在它方便的时候以报文段的形式发送数据”。 关于TCP如何控制发送报文段的时机，见下文*TCP的传输效率*
  
* 接收缓存：当TCP Segment到达接收端时，便进入了接收端的缓存，等待被应用程序读取
  * TCP连接的每一端都有发送和接收缓存

* MSS(Maximum Segment Size)： TCP每次可以从缓存中发送的最大数据长度
  
  *  一般来说，MSS+TCP/IP首部的长度要小于等于链路的MTU（即链路层最大帧长度Maximum Transport Unit）
  
  * MSS的名字很让人误解， 事实上MSS指的只是Segment的Data部分的最大长度，而不是整个Segment的长度

## TCP Segment

TCP Segment分为Header和Data两部分

* Header前20Byte固定，后面跟$4n$个可选的Byte，因此Header占$20 + 4n$ Byte



![TCP Segment](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20Segment.png)

Header各字段如下： 

1. 源端口和目的端口：各占2字节，分别是源端口号和目的端口号 
2. **序号**：占4字节, 序号范围$[0,2^{32}-1]$。TCP中传输的数据流中的每一字节都按顺序编号。序号字段的值是**本报文段所发送的数据的第一个字节的序号**
3. **确认号**：占4字节，是**期望收到对方下一个报文段的第一个数据字节的序号**。 例如B正确收到了A发送过来的一个Segment。序号为501，而数据长度是200Byte，这表明B正确收到了A发送的到序号700为止的数据。 因此B期望收到A的下一个数据序号是701， 于是B在发送给A的Segment中把确认号置为701
   * 若确认号=$N$，则表明到序号$N-1$为止所有数据都正确收到
4. **数据偏移**：占4位，指出TCP报文段的数据起始处与TCP报文段的起始处的距离，也就是**Header的长度**
5. 保留：占6位，保留为今后使用，目前应置为0
6. 紧急URG：当URG=1时，表明紧急指针字段有效，告诉系统此报文中有紧急数据，应尽快传送，而不采用原来的按排队顺序来传送
7. 确认**ACK**：仅当ACK=1时确认号字段有效，TCP规定，在**连接建立后**所有数据报文段都把ACK置为1
8. 推送PSH：当收到PSH=1的报文时，就尽快交付接收应用进程，而不再等到整个缓存都填满后再向上交付
9. 复位RST：当RST=1时，表明TCP连接中出现严重差错，必须释放连接，然后重新建立连接。 RST=1还用来咀嚼一个非法的Segment或拒绝打开一个连接。 RST也称为重置位
10. 同步**SYN**：**在连接建立时用来同步序号；当SYN=1而ACK=0时，表明这是一个连接请求报文，对方若同意建立连接，则应在响应报文中使SYN=1，ACK=1**（称为SYNACK）。 因此，SYN=1就表明这是一个连接请求( SYN Segment )或连接接受报文( SYNACK Segment )
11. 终止**FIN**：用来释放一个连接，当FIN=1时，表示此报文段的发送方已经发送完毕，并要求释放连接
12. **窗口**：占2字节，指的是**发送本报文段的一方的接收窗口**（而不是自己的发送窗口 ）。 例如，A是Sender， B是Receiver， A的窗口值作为A让对方设置其发送窗口（ B虽然是Receiver， 但也会向A发送数据 ）的依据；窗口字段明确指出了**从本Sement Header的确认号算起，A目前允许B发送的数据量（以字节为单位）**，窗口值经常动态变化
    * 例如，A发送给B一个Segment，确认号是701，窗口字段是1000， 这就是告诉B：“从701算起，我的接收缓存空间还可接收1000Byte数据，你在给我发送数据时，必须考虑到这点”
13. 校验和：占2字节，检验和字段检验的范围包括首部和数据两部分。 在计算校验和是，需要在Header前面加上12Byte的伪首部
14. 紧急指针：占2字节，在URG=1时才有意义，指出本报文段中的紧急数据的字节数
15. 选项：长度可变，最长40Byte。 当没有使用任何选项时， Header长度是20Byte。 最后的填充字段仅仅是为了使整个TCP首部长度是4Byte的整数倍
    * MSS就是选项之一

## TCP连接管理

## TCP连接建立

我们将主动发起连接建立的进程称为client， 被动等待连接建立的进程称为server。 记A为client， B为Server， 连接建立过程为三报文握手：

* 一般将其称作“三次握手”，但严谨地说，TCP连接建立只是“在一次握手中报文交换三次”，因此称为“三报文握手”
* 注意，**只有SYN和SYNACK报文段会被超时重传， ACK报文段是不会被重传的**

![TCP 3-way handshake](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%203-way%20handshake.png)

起初，A和B都为CLOSED状态。在通信开始前，双方都得创建各自的传输控制块（TCB）。B创建完TCB后便进入LISTEN状态，此时准备接收A发来的连接请求。

### 第一个报文

client向server发送连接请求报文段。该报文段没有Data部分, Header中:

```
SYN=1，ACK=0，seq = client_isn
```

该Segment称为**SYN Segment**

请求发送后，client便进入SYN-SENT状态

* SYN=1，ACK=0表示该报文段为连接请求报文。
* `client_isn`为本次TCP通信的字节流的初始序号， TCP规定：SYN=1的报文段不能有数据部分，但要**消耗掉一个序号**
* `client_isn`和后文的`server_isn`可以随机选择，也可以（为了避免网络攻击）使用算法生成





### 第二个报文

服务端收到连接请求报文段后，如果同意连接，则会发送一个应答：

```
SYN=1，ACK=1，seq=server_isn，ack=client_isn + 1
```

该Segment称为**SYNACK Segment**

该应答发送完成后，server便进入SYN-RCVD（同步收到）状态

* SYN=1，ACK=1表示该segment为连接同意的应答报文
* seq=`server_isn`表示server作为sender时，发送字节流的初始序号. 这个序号也可以是随机选取的
* ack=`client_isn`+1表示服务端希望下一个数据报发送序号从`client_isn`+1开始的字节
* TCP规定: **SYNACK Segment要消耗一个序号，也就是B向A发送的下一个Segment的起始序号是`server_isn`+1**



### 第三个报文

当客户端收到连接同意的应答后，还要向服务端发送一个确认报文段，表示：server发来的SYNACK已经成功收到。
该报文段的头部为：

```
ACK=1，seq=client_isn + 1，ack=server_isn+1
```

该Sement称为**ACK Segment**

client发完这个segment后便进入ESTABLISHED状态，server收到这个应答后也进入ESTABLISHED状态，此时连接建立完成

* SYN = 0， ACK = 1 标识该segment为连接建立确认报文。 由于client发送完这个报文后就处于连接建立状态，因此SYN=0
* TCP规定：ACK Segment可以携带数据，**但如果不携带数据则不消耗序号**，此时，**A向B发送的下一个Segment的起始序号仍然是`client_isn` + 1**

---



**为什么连接建立需要发送第三个报文？**

防止失效的连接请求报文段被服务端接收，从而产生错误

考虑如下情况：我们采用两报文握手， A给B发送SYN Segment， 但因该报文丢失而没有收到确认（ SYNACK ），于是A再重传一次SYN Segment。 后来A收到了确认，建立了连接。通信结束后释放连接。 A总共发送了两个报文段，第一个丢失了，第二个正确到达了B，没有“失效的”报文段。这是正常情况。

现在假设一种异常情况， 即A发出的第一个SYN Segment没有丢失，而是迟到了，以致在**连接释放后**才到达B， 这是个**已经失效的Segment**，B收到该SYN Segment后，误以为A又发出了一次新的连接请求，于是就向A发送SYNACK Segment，同意建立连接， **由于这是“两报文握手”， B发送SYNACK后就进入了ESTABLISHED状态**。 但此时A早已进入CLOSED状态， A会直接丢弃这个SYNACK，也不会给B发数据，更不会通知B，B会一直等待下去，持续地浪费其资源。

---



**如果第三个报文握手丢失怎么办？**

problem：如果第三个报文握手丢失，A处于ESTABLISHED状态，向B发送数据，而B仍然处于SYN_RECV状态，无法响应连接。 

solution：B在发送SYNACK后，会根据 TCP的超时重传机制，等待3秒、6秒、12秒后重新发送SYN+ACK包，以便Client重新发送ACK包。



## TCP连接释放

![TCP 4-way wavehand](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%204-way%20wavehand.png)

起初，A和B都为ESTABLISHED状态



### 第一个报文

若A认为数据发送完成，则它需要向B发送连接释放请求。该Segment只有Header，其中：

```
FIN=1，seq=u
```

此时，A将进入FIN-WAIT-1状态

* FIN=1表示该报文段是一个连接释放请求
* seq=u，u-1是A向B发送的最后一个字节的序号
* TCP规定： FIN 报文段总是会消耗一个序号

### 第二个报文

B收到连接释放请求后，会通知高层进程：**A向B这个方向的连接已经释放**。此时B进入CLOSE-WAIT状态，并向A发送连接释放的应答，Header包含：

```
ACK=1，seq=v，ack=u+1
```

A收到该应答，进入FIN-WAIT-2状态，等待B发送连接释放请求。

* ACK=1：除TCP连接请求和链接释放请求报文段以外，**TCP通信过程中所有数据报的ACK都为**1，表示应答。
* seq=v，v-1是B向A发送的最后一个字节的序号。
* ack=u+1表示希望收到从第u+1个字节开始的报文段，并且已经成功接收了前u个字节。（因为第一个报文序号为u，且会消耗一个序号，因此ack = u+1）A收到该应答，进入FIN-WAIT-2状态，等待B发送连接释放请求
  

第二次挥手完成后，A到B方向的连接已经释放，B不会再接收数据，A也不会再发送数据。但**B到A方向的连接仍然存在，B可以继续向A发送数据**， 此时连接处于**“半关闭”状态**
### 第三个报文

当B向A发完所有数据后，向A发送连接释放请求，Header包含：

```
FIN=1，ACK=1，seq=w，ack=u+1
```

B然后进入LAST-ACK状态。

* seq=w： B在半关闭状态可能又发送了一些数据，现在起始序号为w

### 第四个报文

A收到释放请求后，向B发送确认应答，Header包含：

```
FIN=1，ACK=1，seq=w，ack=u+1
```

此时A进入TIME-WAIT状态，此时连接还没有释放掉，必须经过时间等待计时器( TIME-WAIT timer )设置的时间 2MSL 后，且该时间段内没有B的重发请求的话，A才会进入CLOSED状态，撤销TCB。当B收到确认应答后，也会进入CLOSED状态，撤销TCB。

* 最长报文段寿命MSL( Maximum Segment Lifetime ): 这个值是从工程上考虑的，一般是2min。 因此从A进入TIME-WAIT状态后，最少需要4min才能进入CLOSED



**为什么A要先进入TIME-WAIT状态，等待时间后才进入CLOSED状态？**

为了保证B能收到A的确认应答。
若A发完确认应答后直接进入CLOSED状态，那么如果该应答丢失，B等待超时后就会重新发送连接释放请求，但此时A已经关闭了，不会作出任何响应，因此B永远无法正常关闭。

## Example

### TCP Client

```python
from socket import *
serverName = 'localhost' # 指定服务器地址
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM) # 建立TCP套接字，使用IPv4协议
clientSocket.connect((serverName,serverPort)) # 向服务器发起连接

sentence = input('Input lowercase sentence:').encode() # 用户输入信息，并编码为bytes以便发送
clientSocket.send(sentence) # 将信息发送到服务器
modifiedSentence = clientSocket.recvfrom(1024) # 从服务器接收信息
print(modifiedSentence[0].decode()) # 显示信息
clientSocket.close() # 关闭套接字
```



### TCP Server

和Servlet类似，TCP Server实际上会先打开一个"欢迎套接字"来等待client连接，当client请求请求到来后， server通过“欢迎套接字”创建一个新的连接套接字(`serverSocket.accept()`)，由后者进行与该client的连接

* Client Socket与Server的Connection Socket(而不是欢迎套接字)建立了TCP连接

```python
from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM) # 创建TCP欢迎套接字，使用IPv4协议
serverSocket.bind(('',serverPort)) # 将TCP欢迎套接字绑定到指定端口
serverSocket.listen(1) # 最大连接数为1
print("The server in ready to receive")

while True:
	connectionSocket, addr = serverSocket.accept() # 接收到客户连接请求后，建立新的TCP连接套接字
	print('Accept new connection from %s:%s...' % addr)
	sentence = connectionSocket.recv(1024) # 获取客户发送的字符串
	capitalizedSentence = sentence.upper() # 将字符串改为大写
	connectionSocket.send(capitalizedSentence) # 向用户发送修改后的字符串
	connectionSocket.close() # 关闭TCP连接套接字
```

## SYN Flood Attack

在TCP三报文握手中，server为了响应一个SYN，会分配一些资源（初始化一些变量和缓存），然后发送一个SYNACK， 并等待client的ACK Segment。 如果client不发送ACK， 最终server将终止该半开连接并回收资源

SYN洪泛攻击( SYN flood attack ): 是一种经典DoS攻击, 在这种攻击中，攻击者发送大量的TCP SYN，而不对返回的SYNACK进行ACK。 随着大量SYN的到来，server会不停地新建半开连接并分配资源，导致server的资源耗尽



流行的解决方法称为SYN cookie， 过程为：

1. 当服务器接收到一个SYN报文段时，其并不知道该报文段来自一个合法用户还是要进行SYN洪泛攻击的攻击者，因此服务器不会为该报文段生成一个半开的连接（即**不会分配资**源） 。 服务器返回的SYNACK中的`server_isn`由hash生成：

   ```
   server_isn = hash(srcIP,srcPort,dstIP,dstPort, magic)
   ```

   * `magic`是只有server知道的一个秘密数字
   * server不会记住该`server_isn`及其相关的任何信息



2. 如果client是合法的，则它将返回一个ACK Segment， 其中`ack = server_isn+1`， server收到该报文后只要根据IP、端口和自己的`magic`重新计算`new_server_isn`，并比较:

   ```
   if new_server_isn == ack - 1
   ```

   判定该client是否合法。  如果合法，server会生成一个全开连接

   

3. 如果客户没有返回一个ACK报文段，则说明之前的SYN报文段属于要进行SYN洪泛攻击的攻击者，但其并没有对服务器造成任何危害，因为服务器没有为它分配任何资源



# 可靠传输



理想的传输条件：

1. 传输信道不产生差错
2. 不管发送方以多快的速度发送数据，接收方总是来得及处理收到的数据

在以上网络条件( 也可以说是**网络层条件** )下，不需要任何措施就可以实现可靠传输。 然而实际的网络都不具备以上理想条件（IP层就是不可靠的），因此要采用一些可靠传输协议来确保可靠传输。



基本上，可靠传输要用到以下机制：

* 计时器（超时重传）
* 序号

## 可靠传输协议

我们这里讨论抽象的可靠传输协议，其实现不一定局限于应用层。 我们把传输的数据都称为分组，而不考虑数据实际上是在哪一层发送的。



### 停止等待协议

对于全双工通信，双方既是Sender又是Receiver。 为了简化问题，我们仅考虑A为Sender， B为Receiver的情况。

* 停止等待： 每发送完一个分组就停止发送，等待对方的确认，在收到确认后再发送下一个分组





#### 无差错情况

![stop-wait protocal without error](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/stop-wait%20protocal%20without%20error.png)

#### 出现差错

以下是传输过程中出现差错的情况：

1. B在接收M1时检测出差错，就丢弃M1，什么也不做（不通知A收到有差错的分组）
   * B当然可以在检测出差错后给A发送错误报文，但这种方法很复杂，实践中一般不采用
2. M1在传输过程中就丢失了，B什么也不知道

在这两种情况下，B都不会发送任何信息。 而可靠传输协议规定，如果A超过一段时间依然没有收到确认，就会重传前面发送过的分组，这就是**超时重传**。 

* 超时重传需要在每发送一个分组后设置超时计时器，如果在计时器在到期之前收到了确认，就重置计时器



注意:

1. A发送完一个分组后，必须暂时保留已发送分组的副本，只有在收到相应确认后才删除
2. 分组和确认都需要编号，才能明确哪个分组收到确认，哪个没收到
3. 超时计时器的重传时间应比数据在分组传输的平均往返时间更长一些

![stop-wait protocal RTO](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/stop-wait%20protocal%20RTO.png)

#### 确认丢失和确认迟到

假设M1的传输正常，但B对M1的确认丢失了，A在没有收到确认后会超时重传M1，B会：

1. 丢弃这么重复的分组
2. 向A发送确认

​        ![stop-wait protocal with SYNACK loss](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/stop-wait%20protocal%20with%20SYNACK%20loss.png)

​      



还有一种情况，B对M1对确认没有丢失，而是迟到了。 A超时重传后，B会收到重复的M1，并将其丢弃，并重传确认分组， A会受=收到该重复的确认分组。，并丢弃该确认:

​        ![stop-wait protocal with SYNACK late](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/stop-wait%20protocal%20with%20SYNACK%20late.png)



#### 信道利用率

上述的停止等待协议使用了超时重传，因此也被称为ARQ( Automatic Repeat reQuest )， ARQ的缺点是大部分的时间都浪费在等待确认上面，信道利用率低

为了提高信道利用率，可以用*流水线传输*来取代*停止等待传输*，流水线传输协议包括了连续ARQ协议和滑动窗口协议， 其中滑动窗口协议比较复杂，被TCP所采用，放到*TCP可靠传输的实现*一节

* “滑动窗口协议”一般指TCP所采用的滑动窗口协议， 尽管连续ARQ协议也采用了滑动窗口 

### 连续ARQ协议

发送方维持**发送窗口**，位于发送窗口内的分组都可以连续发送出去，而不需要等待对方确认，这样信道利用率就提高了

 工作原理：

![ARQ sliding window](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/ARQ%20sliding%20window.png)

ARQ规定，发送方每收到一个确认，就把发送窗口滑动一个分组位置，接收方采用**累积确认**方式，在收到几个分组后，对**按序到达的最后一个分组发送确认**

* 优点：容易实现，确认丢失也不必重传
* 缺点：不能向发送方反映出接收方已经正确收到的所有分组信息
  * 例如，若Sennder发送了前五个分组，而中间的第三个分组丢失了，这时接收方只能对前两个分组发出确认。 Sender无法知道后面三个分组的下落，只能把后面三个分组再重传一次，这就叫做 **Go-back-N**. 表示需要再退回来重传已发送过的N个分组。 可见当网络质量不好时，连续ARQ协议的效率很低。



## TCP可靠传输的实现



我们假定数据传输只在一个方向进行，即A为Sender， B为Receiver





### 滑动窗口

TCP滑动窗口**以字节为单位**。 假设A收到了B发来的ACK Segment，其中窗口是20Byte，确认号是31（表明B期望收到的下一个序号是31），A根据B的报文构造自己的发送窗口：

* 之前提到了，除了连接请求和连接释放请求, TCP通信过程中的所有Segment均含有`ACK=1`,这里是传输数据的Segment，也不例外

![TCP sliding window](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20sliding%20window.png)

* 发送窗口表示：**在没有收到B的确认时，A可以连续把窗口内的数据都发送出去**。 凡是已发送的数据，在未收到确认之前必须暂时保留，以便在超时重传时使用

* 发送窗口中的序号表示允许发送的序号，窗口越大，发送方就可以在收到对方确认前连续发送更多的数据，因此可能获得更高的传输效率。

  * 发送方的发送窗口大小一定不能超过接收方的接受窗口(这里是20)

* 发送窗口的后沿的后面部分表示：已发送且已经收到了确认的序号（显然这部分不需要保留）。 前沿的前面部分部分表示：不允许发送的序号。 发送窗口的位置由前沿和后沿决定

* 后沿变化的情况有两种：

  1. 不动（没有收到新的确认）
  2. 前移（收到了新的确认）
     * 注： 由于不能撤销已收到的确认，因此后沿不能向后移动

* 前沿变化的情况有两种：

  1. 前移， 这是一般情况

  2. 不变，这包含两种情况：

     1. 没有收到新的确认，且对方通知的窗口大小也不变
     2. 收到了新的确认，但对方通知的窗口缩小了，使得前沿正好不懂

     * 注意，发送窗口前沿不能向后移动，虽然实践上可以，但TCP标准强烈不建议这样做

  

* 注意，A的发送窗口是根据B的接受窗口设置的，此外还要考虑到网络情况和拥塞控制等等，因此A的发送窗口不一定和B的接受窗口一样大



### 滑动窗口与缓存

TCP的缓存和窗口的关系：

![TCP cache and sliding window](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20cache%20and%20sliding%20window.png)

发送缓存存放：

* 发送应用程序发送给发送方TCP准备发送的数据

* TCP已发送出但尚未收到确认的数据

发送窗口只是发送缓存的一部分，已被确认的数据应当从发送缓存中删除，因此发送缓存和发送窗口的后沿是重合的。 发送方进程最后写入发送缓存的字节减去最后被确认的字节，就是还保留在**发送缓存**中的被写入的字节数。 <u>这些（发送缓存中的）字节在发送窗口内的部分，可以被一次性发送</u>



接收缓存存放：

* 按序到达的、但尚未被接受应用程序读取的数据

* 未按序到达的数据





### 超时重传时间的选择

TCP连接建立时， 发送方如果在规定时间内没有收到确认， 就会超时重传已发送的报文，。为了得到标准的超时重传时间， 我们定义:

* RTT: 报文段的往返时间， 注意，每个报文的RTT都不一样

* RTTs：报文段的加权平均往返时间， 's'表示Smoothed， 因为使用了加权平均，所以得到的结果更平滑, 算法为:
  $$
  \mathrm{新的RTT_S} = (1 - \alpha) \times (\mathrm{旧的RTT_S}) + \alpha \times(\mathrm{RTT_S} - \mathrm{新的RTT样本})
  $$

  * $\alpha$一般为0.125

* $\mathrm{RTT_D}$: RTT的偏差的加权平均值， 它与RTTs和新的RTT样本之差有关。 RFC规定，在第一次测量时，$\mathrm{RTT_D}$为测量到的RTT样本值的一半，在以后的测量中，则是用下式计算$\mathrm{RTT_D}$:
  $$
  \mathrm{新的RTT_D} = (1 - \beta) \times (\mathrm{旧的RTT_D}) + \beta \times|\mathrm{RTT_S} - \mathrm{新的RTT样本}|
  $$

  * $\beta$一般为0.25

* RTO( Retransmission Time-Out ): **超时重传时间**，算法为
  $$
  \mathrm{RTO}=\mathrm{RTT_S}+4*\mathrm{RTT_D}
  $$



RTT的定义是“报文往返时间”， 那么如何判定收到的确认报文是对第一次发送的Segment的曲确认，还是对之后超时重传的Segment的确认？

解决方案之一是Karn算法：

*在计算加权平均RTTs时，只要报文段重传了，就不采用其往返时间样本，这样得出的加权平均RTTs和RTO就较准确*

然而Karn算法也不太合理（自行百度），实践中一般采用改进的Karn算法。 总之，RTO的选择是很复杂的。            

### 选择确认SACK

如果收到的报文段无差错，只是中间缺少了一些序号。 选择确认( Selective ACK, aka SACK ) 可以让发送方只传送缺少的数据，而不是重传所有数据



示例：   

假设TCP的接收方收到了序号1 ~ 1000, 1501 ~ 3000, 3501 ~ 4500, 其余序号都没有收到，如果所有序号的范围都在接收窗口内，则接收方会收下这些数据，并把已收到序号的“边界”告诉对方，让对方不要再重传这些数据。 对于本例，“边界”就是$[1,1001)$,$[1501,3001)$, $[3501, 4501)$， 注意边界的右界是序号的最右端 + 1

![TCP SACK](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20SACK.png)

显然，TCP 首部中没有哪个字段是用来存放边界的， 因此边界信息都存放在首部“选项”字段。 由于首部选项最多只有40Byte， 而每个字节块有两个边界， 每个边界4Byte（因为序号用4byte表示）， 所以一个字节块就要用8Byte。 选项中还需要指明“启用SACK”（1Byte）和“SACK选项占用的字节数”（1Byte）， 对于n个字节块，一共会在选项字段占用：
$$
8n + 2
$$
字节， 很容易就超过了选项字段40Byte的上限， 再加上SACK文档没有对发送方怎样响应SACK做规定， 因此SACK没有被广泛采用。 一般的实现还是重传所有数据块。

​         





# TCP Flow Control

* 流量控制( Flow Control ):  让发送方发送速率不要太快，使接收方来得及接收。 这是**端到端**通信量的控制( 接收端控制发送端 )， 

## 利用滑动窗口实现流量控制

TCP利用滑动窗口实现流量控制，示例：

我们假设A向B发送数据，且：

* 开始时B告诉A： “我的接受窗口rwnd=400”( rwnd = received window ) 
* 每个报文段长100字节
* 数据报文段的序号初始值为1

![TCP flow control with sliding window](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/Transport%20Layer/TCP%20flow%20control%20with%20sliding%20window.png)

我们看到，上图中B一共进行了三次流量控制。 第一次把窗口减小到rwnd = 300； 第二次把窗口减小到rwnd =100；第三次把窗口减小到rwnd = 0， 即不允许发送方再发送数据了，该状态持续到B重新发出新的窗口值为止。

* 这三个报文段的ACK均为1， 仅当ACK = 1时， 确认号字段才有意义
* 显然，发送方的发送窗口不能大于接收方给出的接收窗口( rwnd )

假设B在发送rwnd = 0， 其接收窗口又有了一些空间， 然后B向A发送了rwnd = 400的报文段，但是这个报文段丢失了， 则A会一直等待B发送的非零窗口的报文段， B也在等待A传来的数据，形成死锁。

* 注意，B如果不继续收到A的报文段，自己是不会再次主动通知A的 （ 因为“通知”是ACK ， 而ACK报文段不会被重传）

为此，需要对TCP连接设置**持续计时器**：只要TCP连接的一方收到对方的零窗口通知，就启动持续计时器，若计时器到期，就发送一个零窗口**探测报文段**，而对方就在确认这个报文段时给出了现在的窗口值，若窗口值仍是零，那么收到报文的一方就重新设置持续计时器，若不是零，那么死锁就被打破

## TCP的传输效率

进程把数据传送到TCP发送缓存后，就由TCP来控制数据的发送。 TCP需要控制报文的发送时机，来得到最大的数据传输效率。 目前的TCP实现中广泛采用Nagle算法

* Nagle算法：若进程要把数据逐个字节地送到TCP发送缓存，则发送方就把第一个数据字节先发送出去，把后面到达的数据字节都缓存起来。当发送方收到对第一个数据字符的确认后，再把发送缓存中的所有数据组装成一个报文发送出去，同时继续对后到达的数据进行缓存。只有在收到对前一个报文段的确认后才继续发送下一个报文段
  

# TCP Congestion Control

* 拥塞( congestion ): 网络中对资源的需求 > 可用资源
* 拥塞控制( congestion control ): 防止过多的数据注入到网络中，使网络中的路由器或链路不致过载。 拥塞控制是一个**全局的**过程，面向整个网络 

## 拥塞控制的原理

拥塞控制可分为开环控制和闭环控制

* 开环控制：在设计网络时事先将有关发生拥塞的因素考虑周到，力求网络在工作时不发生拥塞
* 闭环控制：基于反馈回路概念；检测网络系统以便检测到拥塞在何时、何处发生；把拥塞发生的信息传送到可采取行动的地方；调整网络系统的运行以解决出现的问题
* 检测网络拥塞的指标：
  * 由于缺少缓存空间而被丢弃的分组的百分数
  * 平均队列长度
  * 超时重传分组数
  * 平均分组时延

## TCP拥塞控制的方法

TCP的拥塞控制方法有四种：

1. 慢开始
2. 拥塞避免
3. 快重传
4. 快恢复

