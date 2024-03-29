---
title: Computer Information Representation
tags: Computer Architecture
categories: Computer Science
---

# Information Storage

## Hexadecimal Notation

## Data Sizes

## Addressing and Byte Ordering

## Representing Strings

## Representing Code

## Introduction to Boolean Algebra

## Bit-Level Operations in C

## Logical Operations in C

## Shift Operations in C 93

# Integer Representation

//TODO int - binary

## Integral Data Types

## Unsigned Encodings

PRINCIPLE: Definition of unsigned encoding:
For vector  $\vec{x}=\left[x_{w-1}, x_{w-2}, \ldots, x_{0}\right]$  :
$$
B 2 U_{w}(\vec{x}) \doteq \sum_{i=0}^{w-1} x_{i} 2^{i}
$$
The range of $w$-bit unsigned integer:

* 最小值为$0$
* 最大值为: $ UMax_w \doteq \sum_{i=1}^{w-1} 2^i = 2^w - 1$





由二进制数转换成十进制数的基本做法是: 把二进制数首先写成加权系数展开式，然后按十进制加法规则求和。这种做法称为"**按权相加**"法。

例如把二进制数 110.11 转换成十进制数。

![img](https://www.runoob.com/wp-content/uploads/2018/11/210-1.png)





十进制小数转换成二进制小数采用"**乘2取整，顺序排列"**法。具体做法是：用2乘十进制小数，可以得到积，将积的整数部分取出，再用2乘余下的小数 部分，又得到一个积，再将积的整数部分取出，如此进行，直到积中的小数部分为零，或者达到所要求的精度为止。

然后把取出的整数部分按顺序排列起来，先取的整数作为二进制小数的高位有效位，后取的整数作为低位有效位。

例如把（0.8125）转换为二进制小数:

![img](https://www.runoob.com/wp-content/uploads/2018/11/210-3.png)



## Two’s-Complement Encodings

PRINCIPLE: Definition of two's-complement encoding
For vector $ \vec{x}=\left[x_{w-1}, x_{w-2}, \ldots, x_{0}\right]$  :
$$
B 2 T_{w}(\vec{x}) \doteq-x_{w-1} 2^{w-1}+\sum_{i=0}^{w-2} x_{i} 2^{i}
$$

### Range

Let us consider the range of values that can be represented as a w-bit two’s-complement number. 

* The least representable value is given by bit vector $[10\dots0]$ (set the bit with negative weight but clear all others), having integer value $TMin_w \doteq −2^{w−1}$. 
* The greatest value is given by bit vector $[01 . . . 1]$ (clear the bit with negative weight but set all others), having integer value $TMax_w \doteq \sum_{i=1}^{w-2} 2^i = 2^{w−1} − 1$. 

* Examples:

  * Using the 4-bit case as an example, we have:
    *  $TMin_4 = B2T_4([1000]) = −2^3 = −8$
    * $TMax_4 = B2T_4([0111]) = 2^2 + 2^1 + 2^0 = 4 + 2 + 1 = 7$
  * 再例如, 对于32-bit二进制串`0x80000000`, 它代表的是32-bit 二进制补码的下界`-2147483648`

* 可以看到, 二进制补码的值域是asymmetric的:
  $$
  |TMin| = |TMax| + 1
  $$
  这是由于一半的比特串被分配给了负数, 而另一半比特串被分配给了非负数(包括0), 因此正数的比特串就比负数的少一个.

* The maximum unsigned value is just over twice the maximum two’s-complement value: 
  $$
  UMax = 2TMax + 1
  $$
  

  

***

可以看到,   $B2T_w$建立了$w$-bit 二进制数与$\{TMin_w, \dots, TMax_w\}$的一一对应.



principle: Uniqueness of two’s-complement encoding:

Function $B2T(w)$ is a bijection.



We define function $T2B_w$ (for “two’s complement to binary”) to be the inverse of $B2T_w.$ That is, for a number $x$, such that

$TMin_w < x < TMax_w$ ,  $T2B_w(x)$is the (unique) $w$-bit pattern that encodes $x$.

***









## Conversions between Signed and Unsigned

![image-20230302195301581](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195301581.png)







![image-20230302195331453](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195331453.png)





![image-20230302195359694](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195359694.png)



![image-20230302195409538](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195409538.png)



To summarize, we considered the effects of converting in both directions between unsigned and two’s-complement representations. 

* For values x in the range $0 ≤ x ≤ TMax_w$, we have$T2U_w(x) = x$ and $U2T_w(x) = x$. That is, **numbers in this range have identical unsigned and two’s-complement representations.** 

* For values outside of this range, the conversions either add or subtract $2_w$. 

  ![image-20230302195547362](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195547362.png)

  



## Signed versus Unsigned in C

## Expanding the Bit Representation of a Number



For converting a two’s-complement number to a larger data type, the rule is to perform a *sign extension*, adding copies of the most significant bit to the representation,  expressed by the following principle. We show the sign bit $x_{w−1}$ in blue to highlight its role in sign extension.

![image-20221208193507872](/Users/lyk/Library/Application Support/typora-user-images/image-20221208193507872.png)







## Truncating Numbers

When truncating a w-bit number $\vec x = [x_{w−1}, x_{w−2}, . . . , x_0]$ to a k-bit number, we drop the high-order w − k bits, giving a bit vector $\vec x = [x_{k−1}, x_{k−2}, . . . , x_0]$. Truncating a number can alter its value—a form of **overflow**. 



![image-20230302195803053](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195803053.png)

The intuition behind this principle is simply that all of the bits that were truncated have weights of the form 2i, where i ≥ k, and therefore each of these weights reduces to zero under the modulus operation. This is formalized by the following derivation:

相当于mod掉$2^k$



![image-20230302195835969](/Users/lyk/Library/Application Support/typora-user-images/image-20230302195835969.png)



In this derivation, we make use of the property that:
$$
\forall i \geq k, \ 2^i \mathrm{mod} 2^k = 0
$$


A similar property holds for truncating a two’s-complement number, except that it then converts the most significant bit into a sign bit:



![image-20230302200014678](/Users/lyk/Library/Application Support/typora-user-images/image-20230302200014678.png)



![image-20230302200034867](/Users/lyk/Library/Application Support/typora-user-images/image-20230302200034867.png)



# Floating-Point Representation

We can represent a number in the form:
$$
\pm \mathrm{S} \times \mathrm{B} ^ {\pm \mathrm{E} }
$$

 This number can be stored in a binary word with three fields:

- Sign:  1st bit (0 = positive, 1 = negative)
- Significand $\mathrm{S}$
- Exponent $\mathrm{E}$: unsigned int, 采用**biased representation**, 即存储的Exponent = 真实的Exponent - bias
  *  **bias**  =  $(2^{k- 1} - 1)$, where *k* is the number of bits in the binary exponent.
  *  对unsigned int采用biased representation有一个好处, 那就是数字的relative magnitude不会改变, 也就是说最小值依然是$0000...$, 最大值依然是$1111...$, 这样可以使
- The **base**  $\mathrm{B}$ is **implicit** and **need not be stored** because it is the same for all numbers.



The following are equivalent, where the significand is expressed in binary form:
$$
0.110 \times 2^5 \\
110 \times 2^2 \\
0.0110 \times 2^6
$$

### Normalization

浮点数可以分为规格化( normalized )和非规格化( subnormalized ):

* **Normal number** : 最大数位为非零数. 对于2进制来说, 只有一个非零数就是1, 所以二进制的规格化数的最大数位的数是1. 因此, 一个规格化的非零数可以表示为:
  $$
  \pm \mathrm{1.bbb\dots b} \times \mathrm{B} ^ {\pm \mathrm{E} }
  $$
  where $\mathrm{b}$ is either binary digit (0 or 1). 

  **S的最大数位总是1, 因此它不需要存储在Significand field ( 默认省略 )**

  * 规格化数的Biased Exponent实际取值为$[1, 2^{k} - 1 - 1]$. 因为全零阶码$0000...$和全一阶码$1111....$都有特殊用途. 对于32-bit float, 其8-bit Exponent的Biased Exponent范围是$[1, 254]$, True Exponent范围是$[-126, 127]$

* **Subnormal number**: 用于处理规格化数中的underflow情况, 当数的阶值太小时, 可以不断右移Significand并增加阶值, 直到阶值落在可表示范围内( 这就是**非规格化** )
  
  * 阶值太小: 小于biasd representation可表示的阶值范围. 比如, 8-bit exponent只能表示最小阶值-127( $00000000_2$), 如果某浮点数的阶值为-128, 则无法被规格化表示. 可以通过右移Significand并阶值加一, 来使得该数字作为非规格化数表示



下图展示了32-bit float使用非规格化数的影响:

![image-20221118123141959](/Users/lyk/Library/Application Support/typora-user-images/image-20221118123141959.png)

* 规格化数的阶值最小为$ 1 - 127 = 126$, 导致无法表示$\mathrm{1.bbb} \times 2^{-127}$. 因此$[0,2^{-126}]$ 出现了空隙. 
* 使用非规格化数后,  $[0,2^{-126}]$ 和 $[ 2^{-126}, 2^{-125}]$之间出现了**均匀**且对称的空隙
  * “均匀”是因为非规格化数的阶值都是-126. 
  * “对称”是因为最小的规格化数的阶值也都是-126

### IEEE 

### 32-bit Representation

![Typical 32-Bit Floating-Point Format](/Users/lyk/Library/Application Support/typora-user-images/image-20221118114740517.png)



* 1-bit sign. <u>The sign is stored in the first bit</u> of the word.

* 8-bit Biased exponent: 该比特串代表无符号整数, 等于真实的阶值 + 偏置值( **127** ($2^7 - 1$)  )

  * 8-bit无符号整数的值域为$[0, 255]$
  * 真实阶值的值域因此为$[-127, 128]$. 但是后面我们会看到, 全0的阶码有特殊用途. 它表示该数是个非规格化数, 阶值为$-126$. (即偏置值变成了126, 真实值0 - 偏置值126 = -126 ). 因此真实阶值最小为$-126$, 值域因此为$[-126, 128]$. 
    * 真实阶值 =-126 有两种情况:
      1. 该浮点数为非规格化数, 阶码为全0
      2. 该浮点数为规格化数, 阶值为1, 因此真实阶值为-126 = 1 - 127

  * <u>true</u> exponent values are in the range <u>\- 127 to +128</u>. 

* 23-bit Significand: 如果是规格化数, 那么这23-bit实际上表达的是一个24-bit的Significand, 它的第一位永远是1, 因此被省略.

* The base is 2.



Following Figure indicates the range of numbers that can be represented in a 32-bit word:

* Negative numbers between $- (2 - 2^{-23}) \times 2^{128}$  and $- 2^{-127}$

* Positive numbers between $2^{-127}$ and $(2 - 2^{-23}) \times 2^{128}$

* 然而, 

  

![Expressible Numbers in Typical 32-Bit Formats](/Users/lyk/Library/Application Support/typora-user-images/image-20221118121525695.png)

Five regions on the number line are not included in these ranges:

- Negative numbers less than $- (2 - 2^{-23}) \times 2^{128}$, called **negative overflow**
- Negative numbers greater than $- 2^{-127}$, called **negative underflow**
- **Zero**
- Positive numbers less than  $2^{-127}$, called **positive underflow**
- Positive numbers greater than $(2 - 2^{-23}) \times 2^{128}$, called **positive overflow**



1. If we increase the number of bits in the exponent, we expand the range of expressible numbers. But because only a fixed number of different values can be expressed, we have reduced the density of those numbers and therefore the precision. 
2. So there is a trade-off between the number of bits in the exponent and the number of bits in the significand. But it is even more complicated than that. The implied base of the exponent need not be 2. The IBM S/390 architecture, for example, uses a base of 16 



> In the IBM base-16 format,
> $$
> 0.11010001 \times 2^{10100} = 0.11010001 \times 16^{101}
> $$
> and the exponent is stored to represent 5 rather than 20.

## Fractional Binary Numbers

## IEEE Floating-Point Representation

The most important floating-point representation is defined in IEEE Standard 754, adopted in 1985 and revised in 2008. 

IEEE 754-2008 defines the following different types of floating-point formats:

- **Arithmetic format:** All the mandatory operations defined by the standard are supported by the format. The format may be used to represent floating-point operands or results for the operations described in the standard.
- **Basic format:** This format covers five floating-point representations, three binary and two decimal, whose encodings are specified by the standard, and which can be used for arithmetic. At least one of the basic formats is imple- mented in any conforming implementation.
- **Interchange format:** A fully specified, fixed-length binary encoding that allows data interchange between different platforms and that can be used for storage.

![IEEE 754 Formats](/Users/lyk/Library/Application Support/typora-user-images/image-20221118124914058.png)



1. All of the basic formats are also arithmetic format types (can be used for arithmetic operations) and interchange format types (platform independent).



![image-20221118125023938](/Users/lyk/Library/Application Support/typora-user-images/image-20221118125023938.png)



Not all bit patterns in the IEEE formats are interpreted in the usual way; instead, some bit patterns are used to represent special values. Table 10.5 indicates the values assigned to various bit patterns. The exponent values of all zeros (0 bits) and all ones (1 bits) define special values. The following classes of numbers are represented:

- For exponent values in the range of 1 through 254 for 32-bit format, 1 through 2046 for 64-bit format, and 1 through 16382, normal nonzero floating-point numbers are represented. The exponent is biased, so that the range of expo- nents is - 126 through + 127 for 32-bit format, and so on. A normal number requires a 1 bit to the left of the binary point; this bit is implied, giving an effec- tive 24-bit, 53-bit, or 113-bit significand. Because one of the bits is implied, the corresponding field in the binary format is referred to as the **trailing signifi- cand field**.
- An exponent of zero together with a fraction of zero represents positive or negative zero, depending on the sign bit. As was mentioned, it is useful to have an exact value of 0 represented.



![binary32 format](/Users/lyk/Library/Application Support/typora-user-images/image-20221118125133354.png)

- An exponent of all ones together with a fraction of zero represents positive or negative infinity, depending on the sign bit. It is also useful to have a represen- tation of infinity. This leaves it up to the user to decide whether to treat over- flow as an error condition or to carry the value ∞ and proceed with whatever program is being executed.
- An exponent of zero together with a nonzero fraction represents a subnormal number. In this case, the bit to the left of the binary point is zero and the true exponent is - 126 or - 1022. The number is positive or negative depending on the sign bit.
- An exponent of all ones together with a nonzero fraction is given the value NaN, which means *Not a Number*, and is used to signal various exception conditions.

## Example Numbers

## Rounding

## Floating-Point Operations

## Floating Point in C

## Code



```
```



```java
/**
 * 如果float是NaN或者+-Inf， 则返回"NaN"和"+-Inf"
 * 得到unbiased_expoenent和sig
 * @param floatStr
 * @return
 */
public static String my_floatToBinary(String floatStr) {
    float d = Float.parseFloat(floatStr);

    boolean isNeg = d < 0;
    //corner check

    if(Float.isNaN(d))
        return "NaN";//不管符号
    if(Float.isInfinite(d))
        return isNeg ? "-Inf" : "+Inf";
    //corner check over

    StringBuilder ans = new StringBuilder(1 + e_length + trailing_sig_length);//需要capacity吗？



    if(d == 0.0)
    {
        for(int i = 0; i < e_length + trailing_sig_length; i++ )
            ans.append('0');
        return ans.toString();
    }


    d = Math.abs(d);
    int bias = get_bias(e_length);
    boolean isSubnormal = ( d < minNormal(e_length, trailing_sig_length));

    // d = true_sig * 2^(true_exponent) ==> true_sig = d / 2^(true_exponent)
    int unbiased_exponent;//阶码真实值
    int biased_exponent;//阶码字面值

    float true_sig_value;
    float trailing_sig_value;

    String biased_exp_bits = "";
    String trailing_sig_bits = "";


    //计算出阶码真值和sig去隐藏位的真值

    if( isSubnormal )
    {
        bias -= 1;//126
        unbiased_exponent = -bias;//-126
        true_sig_value = (float)(d / Math.pow(2,unbiased_exponent));
        trailing_sig_value = true_sig_value;
    }
    else
    {
        unbiased_exponent = getExponent(d);
        true_sig_value = (float) (d / Math.pow(2,unbiased_exponent));
        trailing_sig_value = true_sig_value - 1;
    }

    //计算出biased_exponent,转换成biased_exp_bits
    //计算出trailing_sig_value，转换成trailing_sig_bits

    biased_exponent = unbiased_exponent + bias;
    biased_exp_bits = get_exponent_bits(biased_exponent,e_length);
    trailing_sig_bits = my_fixPoint(trailing_sig_value,trailing_sig_length);

    //append sign bit
    if(isNeg) ans.append('1');
    else ans.append('0');

    //append exp and sig
    ans.append(biased_exp_bits).append(trailing_sig_bits);

    return ans.toString();

}
```
