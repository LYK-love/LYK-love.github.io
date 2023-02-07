---
title: Computer Memory Error Correction
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2022-10-10 20:41:28
---


Outline:

* Intro
* Error Correction
* Odd-Even Check
* Hamming Code
* Cyclic Redundancy Check

<!--more-->

# Intro

A semiconductor memory system is subject to errors. These can be categorized as hard failures and soft errors. 

* A **hard failure** is <u>a permanent physical defect</u>. 受影响的存储单元不能可靠地存储数据.
  * can be caused by harsh environmental abuse, manufacturing defects, and wear. 
* A **soft error** is <u>a random, nondestructive event</u>. 它改变了某个或某些存储单元的内容, 但没有损坏机器
  * can be caused by power supply problems or alpha particles. 
    * These particles result from radioactive decay and are distressingly common because radioactive nuclei are found in small quantities in nearly all materials. 

Both hard and soft errors are clearly undesirable, and most modern main memory systems include logic for both **detecting and correcting errors**.



# Error Correction

![Error Correction](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/Error%20Correction.png)

Error Correction的基本思想就是使用额外的checkbit. 

Steps:

1. 记输入的数据为 $D$ ,  有 $M$ 位. 我们使用函数 $f$ 将其编码为 $K$ 位 checkcode, 记为 $C$. The actual size of the stored word is $ M + K $ bits

2. 接收方收到 $M + K$ bits 数据, 其中的 $M$ 位数据记为 $D'$ , $K$ 位checkcode记为 $C'$ . 

3. 对  $D'$ 再次使用 $f$ 得到 $K$ 位的 $C''$. 

4. 将 $C'$ 和 $C''$ 做比较( 事实上就是异或 ), 得到故障字(syndrome word) $S$ :
   $$
   S = C' \oplus C''
   $$
   

   * No errors are detected. 使用数据 $D'$
   * An error is detected, and it is possible to correct the error. 使用  $D'$ 来生成正确的数据 $D''$ , 并使用 $D''$
   * An error is detected, but it is not possible to correct it. This condition is reported.

# Odd-Even Check

最简单的方法是奇偶校验. 

* 增加1位checkbit $C$ , 表示$D$中1的数量是奇数还是偶数. 

  

* 假设数据为$𝐷=𝐷_M \cdots 𝐷_2𝐷_1$:

  * 奇校验:
    $$
    C=D_{M} \oplus \cdots \oplus D_{2} \oplus D_{1} \oplus
    $$
    
  * 偶校验:
    $$
    C=D_{M} \oplus \cdots \oplus D_{2} \oplus D_{1}
    $$


* Error Detection:
  $$
  S = C' \oplus C''
  $$

  * $𝑆 = 0$ : $C + D$ 正确 or 其中出错的位数为偶数
  * $𝑆 = 1$ : $C+D$ 中出错, 且出错的位数为奇数

## Steps

以偶校验为例:

1. 发送方计算$C$. 将 $C$ 与 $D$ 一同发送

2. 接收方收到$C'$ 和 $D'$, 计算 $C''$ :
   $$
   C''=D'_{M} \oplus \cdots \oplus D'_{2} \oplus D'_{1}
   $$

3. 计算$S$
   $$
   S = C' \oplus C''
   $$
   


## Drawbacks

* 不能检测到偶数个bit出错
* 发现错误后不能校正, 因为不能定位到出错的bit

# Hamming Code

The simplest of the error-correcting codes is the **Hamming code** devised by *Richard Hamming* at Bell Laboratories. 

Hamming Code is a **single-error-correcting (SEC) code**

* **只能检测和纠正1-bit errors**

## Idea

见如下Venn diagram:

![Hamming Code](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/Hamming%20Code.png)

假设$ M = 4 $ :

* 我们画三个圆, 中间相交的四个部分分别填4 data bits ( 如图a ).
* 剩下的最外面三个部分填 **parity bits** ( 也就是checkcode ). Each parity bit is chosen so that the total number of 1s in its circle is **even**( 如图b )
* Now, if an error changes one of the data bits ( 如图c ), it is eas- ily found. 
* By checking the parity bits, discrepancies are found in circle A and circle C but not in circle B. Only one of the seven compartments is in A and C but not B ( 如图d ). The error can therefore be corrected by changing that bit.



## Steps

* 将数据分成几组, 对每一组都使用奇偶校验进行检错. 我们默认使用偶校验
* 数据输入:为数据 $D$ 中每组生成checkbit, 合并得到 $K$ 位check code $C$
* 数据输出:为数据 $D'$ 中每组生成checkbit, 合并得到 $K$ 位check code $C''$
* 检错:将 $C''$ 和取出的 $C’$ 按位进行异或, 生成 $K $位 syndrome word $S$
  * 全部是0:没有检测到错误
  * 有且仅有1位是1:错误发生在校验码中的某一位，不需要纠正
  * 有多位为1:错误发生在数据中的某一位，将𝐷′中对应数据位 取反即可纠正(得到𝐷")

## Check Code Length

![Increase in Word Length with Error Correction](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/Increase%20in%20Word%20Length%20with%20Error%20Correction.png)

* 从上表可以看到, 使用checkcode会使得实际可用的主存( 用户可见的主存 ) 比 事实上的主存 大小更小. 对于64-bit的内存, 如果使用7bit的hamming code, 它的实际word-size是 64 + 7 = 71bit, 而用户只能看见其中的64bit.

假设最多1位发生错误, 可能的情况有:

* $D$ 中有1位出现错误: $M$
* $C$ 中有1位出现错误: $K$
* 没有错误: $1$



因此, $K$ 位的$S$ 需要能表示 $M + K + 1$ 种情况, 即满足:
$$
2^{K}-1 \geq M+K
$$
E.g. for a word of 8 data bits ( $M = 8$ ), we have

* $K=3: 2^{3}-1<8+3$
* $K=4: 2^{4}-1>8+4$

因此, $M=8$ 时 $K=4$







## Checkbit

假设$M=8, K=4$

![Layout of Data Bits and Check Bits](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/Layout%20of%20Data%20Bits%20and%20Check%20Bits.png)






* **checkbit的position number是2的幂**:

  * $\mathrm{C}1$: 0001
  * $\mathrm{C}3$: 0010
  * $\mathrm{C}4$: 0100
  * $\mathrm{C}8$: 1000
  * ...

* **Each check bit operates on every data bit whose position number contains a 1 in the same bit position as the position number of that check bit.**  

  * 比如说, $\mathrm{C}1$ 是 $0001$ , 因此$\mathrm{C}1$ 就和所有的 position number 的第一位为 $1$ 的 databit 有关, 即data bit positions 3, 5, 7, 9, and 11 (D1, D2, D4, D5, D7) 

    * bit positions 3, 6, 7, 10, and 11 all contain a 1 in the second bit position, as does C2; 

    ![checkbit cal](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/checkbit%20cal.png)
  
  * Looked at another way, bit position *n* is checked by those bits $C_i$ such that 
    $$
    n=\sum_{i=1}^{K} (C_{i})
    $$
    For example, position 7 is checked by bits in position 4, 2, and 1; and 7 = 4 + 2 + 1.

## Example

Let us verify that this scheme works with an example. Assume that the 8-bit input word is $00111001$, with data bit $\mathrm{D}1$ in the rightmost position. The calculations are as follows:

1. Sender: Compute $C$ :

   ![checkbit exp step1](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/checkbit%20exp%20step1.png)

   

2. 假设 $\mathrm{D}3$ 出错, 从0变成了1. 接收方收到 $D'$ and $C'$, then Compute $C''$ :

   ![checkbit exp step2](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/checkbit%20exp%20step2.png)

3. 最后计算故障字$S$:
   $$
   S = C' \oplus C''
   $$
   ![checkbit exp step3](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/checkbit%20exp%20step3.png)

   得到$0110 = 3$, 发现是$\mathrm{D}3$ 出错



## Why Only One-Bit Errors?

In computer operation 2-bit errors are **very, very unlikely**. 

假设:  the probability of a 1-bit error  =   $10^{-9}$ , if a computer makes 10,000,000 moves a second

On average you get an error **every 100 seconds = less than 2 minutes.**



相对应的, 2-bit error的概率大概是 $10^{-18}$, 使用同样的电脑, you get a 2-bit error once **every 1011 seconds = once every 3,171 years.**



There may be other considerations, specifically to do with data communications. It is quite common to establish communications over noisy lines, for example, and then the probability of errors increase dramatically. It often happens that there is a short period when may be multiple-bit errors, and it would be impracticable to use a Hamming code in this situation. Other schemes more appropriate to this problem are used instead.

## SEC-DED

Hamming Code只能检查和纠正1-bit error. More commonly, semiconductor memory is equipped with a **single-error-correcting, double-error-detecting (SEC-DED) code**. 这通过添加一个额外的checkbit完成

* 单纠错, 双检错. ( 可以找到两个位产生的错误, 并纠正一个位的错误 )

### Idea

![SEC-DED](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/SEC-DED.png)

This figure illustrates how such a code works, again with a 4-bit data word. 

1. If **two errors occur** ( 如图c )
2. The checking procedure goes astray ( 如图d )
3. The situation worsens the problem by creating a third error ( 如图e )
4. To overcome the problem, **an eighth bit is added** that is set so that the total number of 1s in the diagram is even. The extra parity bit catches the error (f).

### Steps

* 添加:
  $$
  C_{5}=D_{1} \oplus D_{2} \oplus D_{3} \oplus D_{5} \oplus D_{6} \oplus D_{8}
  $$

* SED-DED的故障字 $S$ 的分析:

  * 都是0: 没有检测到错误
  * 1位为1: 在5个校验位中有一个发生了错误, 不需要修正
  * 2位为1: 有2位数据和校验位出现错误，但找不到错误的位置
  * 3位为1: 8位数据位中有1位发生了错误，该错误可以被纠正
  * 3位以上均为1: 严重情况，检查硬件



## Drawbacks

* Hamming Code需要额外的存储空间
* Hamming Code需要先对数据进行分组, 这无法处理流式数据

# Cyclic Redundancy Check

循环冗余校验(Cyclic Redundancy Check, CRC)

* 适用于以流格式存储和传输大量数据
* 用数学函数生成数据和校验码之间的关系

## Steps

- Get Check Code:
  * 假设数据有 $M$ 位，左移数据 $K$ 位(右侧补0), 并用 $K+1$ 位**生成多项式**除它(**模2运算**)
  * 采用 $K$ 位余数作为checkcode
  * 把checkcode放在数据(不含补的0 )后面, 一同存储或传输
- 校错: 如果M+K位内容可以被生成多项式除尽，则没有检测到错误 • 否则，发生错误

## Example

假设数据是 $100011$, 生成多项式为$x^3 + 1$ ( 二进制表示为$1001$ ):

![CRC](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Computer%20Architecture/CRC.png)

最后生成的checkcode是$111$
