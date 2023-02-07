---
title: Computer Information Manipulation
tags: Computer Architecture
categories: Computer Science
---



# Integer Arithmetic 

## Unsigned Addition

Let us define the operation $+_w^u$ for arguments $x$ and $y$, where $ 0 ≤ x$,  $y < 2^w$, as the result of **truncating  the integer sum x + y to be** $w$ **bits long and then viewing the result as an unsigned number. **

This can be characterized as a form of <u>modular  arithmetic</u>, computing the sum modulo $2^w$ by simply discarding any bits with weight greater than$ 2^w−1$ in the bit-level representation of $x + y$. For example, consider a 4-bit number representation with x = 9 and y = 12, having bit representations [1001] and [1100], respectively. Their sum is 21, having a 5-bit representation [10101]. But if we discard the high-order bit, we get $[0101]$, that is, decimal value 5. This matches the value 21 mod 16 = 5.

![image-20221208181841021](/Users/lyk/Library/Application Support/typora-user-images/image-20221208181841021.png)

In general, we can see that

* if $x + y < 2^w$, the leading bit in the (w + 1)-bit represen- tation of the sum will equal 0, and hence discarding it will not change the numeric value. 
* On the other hand, if $2^w ≤ x + y < 2^w+1$, the leading bit in the (w + 1)-bit representation of the sum will equal 1, and hence **discarding it is equivalent to subtracting**  $2^w$ **from the sum.**



![Unsigned addition. With a 4-bit word size, addition is performed modulo 16.](/Users/lyk/Library/Application Support/typora-user-images/image-20221208193012204.png)

An arithmetic operation is said to *overflow* when the full integer result <u>cannot fit within the word size limits of the data type.</u> 

As Equation 2.11 indicates, overflow occurs when the two operands sum to $2^w$ or more. 

Figure 2.23 shows a plot of the unsigned addition function for word size $w = 4$. The sum is computed modulo $2^4 = 16$. 

When $x + y < 16$, there is no overflow, and x +u4 y is simply x + y. This is shown as the region forming a sloping plane labeled “Normal.” 

When $x + y ≥ 16$, the addition overflows, having the effect of decrementing the sum by 16.  This is shown as the region forming a sloping plane labeled “Overflow.”





![image-20221208182327174](/Users/lyk/Library/Application Support/typora-user-images/image-20221208182327174.png)





![image-20221208182400607](/Users/lyk/Library/Application Support/typora-user-images/image-20221208182400607.png)

### Machine Implementation

对于n-bit整数加法$S= X + Y$:

* $S_i, X_i$, $Y_i$: $X$, $Y$ 在第n位的值
* $C_i$: $X_i + Y_i$ 产生的向更高一位的进位, 用于第$i-1$位的运算



#### Full Adder

![Full Adder](/Users/lyk/Library/Application Support/typora-user-images/image-20221210180004108.png)

第i位加法:

* $S_i = X_i \oplus Y_i \oplus C_{i-1}$
* $C_i = = X_i C_{i-1} + Y_i C_{i-1} + X_i Y_i $  





```java
    /**
     * the 2 bits' full adder
     * @param x X_{i}
     * @param y Y_{i}
     * @param c C_{i-1}, carry from the former bit
     * @return result after adding, the first position means the carry to the next and second means the result in this position
     */
    private String fullAdder(char x, char y, char c) {
        int x_bit = char_to_int(x);
        int y_bit = char_to_int(y);
        int c_bit = char_to_int(c);

        assert c_bit < 2;

        int bit = x_bit ^ y_bit ^ c_bit;
        int carry = (x_bit & c_bit) | (y_bit & c_bit) | (x_bit & y_bit);
        return "" + carry + bit;
    }
```



### Carry Adder



```java
    /**
     * add two nums with the length of given length
     * the result's first bit represents the carry bit derived from the lestmost bit( the result's first bit	   presents whether it generates the carry +
     * @param operand1
     * @param operand2
     * @param c
     * @param length
     * @return
     */
    public String carry_adder(String operand1, String operand2, char c, int length) {
        String A = impleDigits(operand1, length);
        String B = impleDigits(operand2, length);
        String S = "";
        char carry = c;

        for (int i = length - 1; i >= 0; i--) {  //这里length不一定是4的倍数，采用更加通用的加法算法
            String temp = fullAdder(A.charAt(i), B.charAt(i), carry );
            carry = temp.charAt(0);
            char bit = temp.charAt(1);

            S = bit + S;
        }

        return carry + S;
    }
```



## Unsigned Sub

Modular addition forms a mathematical structure known as an *abelian group*, named after the Norwegian mathematician Niels Henrik Abel (1802–1829). That is, it is **commutative** (that’s where the “abelian” part comes in) and **associative**; it has an identity element **0**, and every element has an additive inverse. Let us consider the set of w-bit unsigned numbers with addition operation  $+_w^u$. For every value x, there must be some value  $-_w^u$ x such that  $+_w^u x \  + \ -_w^u x = 0$ . This additive inverse operation can be characterized as follows:

即, 对于每个w-bit unsigned int x, 都存在它的w-bit的逆元(negation).

这个negation也是个无符号数, 可以看做x的相反元.



![image-20221208182436046](/Users/lyk/Library/Application Support/typora-user-images/image-20221208182436046.png)



* When $x = 0$, the additive inverse is clearly 0. 
* For $ x > 0$, consider the value $2^w − x$. Observe that this number is in the range $0 < 2^w − x < 2^w$, 即可以用w-bit正常表示
* We can also see that$ (x + 2^w − x) \mod 2^w = 2^w \mod 2^w = 0$. Hence it is the inverse of $x$ under $+_w^u$.



原码的减法运算就是:
$$
x \ -_w^u \ y = x +_w^u (-_w^u y)
$$


## Two’s-Complement Addition

Given integer values $x$ and $y$ in the range $−2^{(w−1)} ≤ x$,  $y ≤ 2^{(w−1)} − 1$,

their sum is in the range $−2^w ≤ x + y ≤ 2^w − 2$, potentially requiring $w + $1 bits to represent exactly.

As before, we avoid ever-expanding data sizes by truncating the representation to w bits. The result is not as familiar mathematically as modular addition, however. 

Let us define $x +_t^w y$  to be the result of truncating the integer sum $x +y$ to be $w$ bits long and then viewing the result as a two’s-complement number.

![image-20221208183253439](/Users/lyk/Library/Application Support/typora-user-images/image-20221208183253439.png)

The $w$-bit two’s-complement sum of two numbers  **has the exact same bit-level representation as the unsigned sum.** 

即, 补码的加减法其实在比特层面和unsigned integers的相同, 但是乘和除却不是如此.





![image-20221208174135118](/Users/lyk/Library/Application Support/typora-user-images/image-20221208174135118.png)



![image-20221010183923683](/Users/lyk/Library/Application Support/typora-user-images/image-20221010183923683.png)



* Overflow: 对于n-bit表示, 只有两个同号的数相加才会导致溢出

```java

    /**
     * the 2 bits' full adder
     *
     * @param x first char
     * @param y second char
     * @param c carry from the former bit
     * @return result after adding, the first position means the carry to the next and second means the result in this position
     */
    private String fullAdder(char x, char y, char c) {
        int bit = (x - '0') ^ (y - '0') ^ (c - '0');  //三位异或
        int carry = ((x - '0') & (y - '0')) | ((y - '0') & (c - '0')) | ((x - '0') & (c - '0'));  //有两位为1则产生进位
        return "" + carry + bit;  //第一个空串让后面的加法都变为字符串加法
    }
```





```java
/**
     * add two nums with the length of given length
     *
     * @param operand1 first
     * @param operand2 second
     * @param c        original carray
     * @param length   given length
     * @return result
     */
    private String carry_adder(String operand1, String operand2, char c, int length) {
        operand1 = impleDigits(operand1, length);
        operand2 = impleDigits(operand2, length);
        String res = "";
        char carry = c;
        for (int i = length - 1; i >= 0; i--) {  //这里length不一定是4的倍数，采用更加通用的加法算法
            String temp = fullAdder(operand1.charAt(i), operand2.charAt(i), carry);
            carry = temp.charAt(0);
            res = temp.charAt(1) + res;
        }
        CF = String.valueOf(carry);
        return res;  //注意这个方法里面溢出即有进位
    }
```



```java
private String adder(String operand1, String operand2, char c, int length) {
        operand1 = impleDigits(operand1, length);
        operand2 = impleDigits(operand2, length);
        String res = carry_adder(operand1, operand2, c, length);
        OF = addOverFlow(operand1, operand2, res);
        return res;  //注意有进位不等于溢出，溢出要另外判断
    }
```



## Two’s-Complement Negation



![image-20221208193613933](/Users/lyk/Library/Application Support/typora-user-images/image-20221208193613933.png)



That is, for w-bit two’s-complement addition, $TMin_w$ is its own additive inverse, while any other value $x$ has $−x$ as its additive inverse.

Observe that $TMin_w + TMin_w = −2^{w−1} + −2^{w−1} = −2^w$ . <u>This would cause negative overflow</u>, and hence. $TMin_w +_x^t TMin_w = −2^{w} + −2^{w} = 0$ 

For values of $x$ such that $x > TMin_w$, the value $−x$ can also be represented as a $w$-bit two’s-complement number, and their sum will be $−x + x = 0$.

# Integer Multiplication

两个n-bit操作数, 进行整数乘法运算会产生2n-bit结果, 

## Unsigned Multiplication

Integers $x$ and $y$ in the range $0 ≤ x$, $y ≤ 2^w − 1$ can be represented as w-bit unsigned numbers, but their product $x . y$ can range between 0 and $(2^w − 1)^2 = 2^{2w} − 2^{(w+1)} + 1$. 

**This could require as many as $2w$ bits to represent.** 

Instead, unsigned multiplication in C is defined to yield the $w$-bit value given by the low-order w bits of the $2w$-bit integer product. Let us denote this value as $x *_u^w y$.

![image-20221208183655070](/Users/lyk/Library/Application Support/typora-user-images/image-20221208183655070.png)



### Simple

基本的无符号乘法:

假设两个操作数为 $n$-bit, 它们的乘积是$2n$-bit (e.g., 11 * 11 = 1001).

![Multiplication of Unsigned Binary Integers Easy Exp](/Users/lyk/Library/Application Support/typora-user-images/image-20221120202719802.png)



1. 首先, 按位扫描multiplier, 得到partial product(部分积 ). 

   ```python
   partial_product_list = []
   
   # partial product:  one for each digit in the multiplier. 
   for i in range (0,n):
     # When the multiplier bit is 0, the partial product is 0. 
     # When the multiplier is 1, the partial product is the multiplicand.
     partial_product =  multiplier[ n - 1 - i] == '1' ? multiplicand : 0
     partial_product_list.append[partial_product]
   ```

   

2. 扫描整个的multiplier, 得到所有的部分积

3. 然后, 将所有部分积相加得到最后的积. 这需要$n$次迭代:

   ```python
   for i in range(0,n):
     # 规定, new_product, previous_product, successive_partial_product都是n位寄存器
     
     # 只需要让上一轮结果的前n-1位和新的部分积和相加. 
     # previous_product取前n-1位后只有n-1位了, 为了和n位的successive_partial_product相加, 其前面还需要无符号扩展一个‘0’
   	new_product = add( ('0' + previous_product[0,n-1]),successive_partial_product ) 
     previous_product = new_product # 下一轮迭代
     successive_partial_product = get_successive_partial_product() #部分积在之前都全部生成了,这里只需要直接拿
   ```

   * 可以看到, 每次迭代中 `previous_product`只有前$n-1$ bit 参与运算, 最后一位相当于已经计算完成了, 这符合我们对手算乘法的认知

4. The multiplication of two *n*-bit binary integers results in a product of up to 2*n* bits in length

* 在手算乘法时, "让上一轮结果的前n-1位和新的部分积相加"是通过“**leftshift新部分积** + 上一轮迭代结果” 实现的. 这就是手算乘法时的“每次左移一位部分积”. 

* 后面我们会使用新的方法: “**rightshift上一轮结果** + 新部分积”. ( 由于寄存器都只有$n$-bit, 每次rightshift后, 上一轮结果的最后一位都会被移到新的寄存器, 不参与后面的运算, 相当于计算完成了 )

* 可以看到两种方法没什么区别, 本质上都是让新部分积和上一轮结果的前$n-1$-bit相加, 而上一轮结果的最后一个bit不参与运算, 作为结果存起来就好了. 迭代n次也就产生了n个存起来的bit, 这也就是最终的乘法结果






### Advanced

上面的算法可以再优化:

* 可以在<u>每产生一个部分积之后立即和之前的相加结果相加</u>, 不需要等到所有部分积产生
  * 这样就不需要存储所有的部分积了. 因为部分积是存在register中的, 这样做减少了使用的register.
* 既然当multiplier的某一位是0时,产生的部分积也是0, 做不做加法都一样, 因此在扫描到0时, 在leftshift后不需要做add.
  * 如上图, 在扫描到<u>1101</u>的第二位‘’0‘时, 可以只leftshift( 使得部分积变成5bit )然后进入下一轮迭代, 下一轮迭代的新部分积继续leftshift, 变成6bit, 与之前的相加结果(1101)相加.
* 采用“**rightshift上一轮结果** + 新部分积”的方式, 这是为了代码实现的方便

示意图如下:

![Multiplication of Unsigned Binary Integers](/Users/lyk/Library/Application Support/typora-user-images/image-20221120205459461.png)



机器层面实现如下: 

* Q,M,A寄存器都是$n$-bit.
  * Q: multiplier
  * M: multiplicand
  * A: 用于存放每次迭代计算出的结果
    * A is initially set to 0
  * C: 1-bit, which holds a potential carry bit resulting from addition.
* 计算过程如下:
  1. 每次扫描multiplier 的一位, 如前所述, 如果是1, 则部分积为multiplicand, 如果是0, 则部分积为0. 将这个部分积与A相加并存储到A, 将进位( 1 or 0 )存储到C.  由于之前说的优化, 当遇到0时, 实际上不需要做相加操作.
  2. **将C, A, Q作为一个整体右移一位**, so that the C bit goes into $A_{n-1}$, $A_0$ goes into $Q_{n-1}$, and $Q_0$ is lost. 
     * 如之前所讨论的, $A_0$相当于计算完了, n次迭代后累积下来的n个$A_0$就是最终结果
     * $Q_0$丢了就丢, 无所谓. 注意的是, 既然Q在这里充当垃圾桶的作用. 每次扫描的“multiplier”需要另外存, 不能放在Q中. (当然也可以放在Q中, 然后多用一个寄存器作为垃圾桶...)
  3. The resulting 2*n*-bit product is contained in the A and Q registers



![image-20221120213102782](/Users/lyk/Library/Application Support/typora-user-images/image-20221120213102782.png)







![image-20221210023701912](/Users/lyk/Library/Application Support/typora-user-images/image-20221210023701912.png)

* C: 1-bit C register, 初始化为0, 存放部分积加法运算的可能的进位
* A: 初始化为全0
* Q: 初始化为multiplier
* M: 初始化为multiplicand



The multiplier and multiplicand are loaded into two registers (Q and M). 

A third register, the A register, is also needed and is initially set to 0. There is also a 1-bit C register, initialized to 0, **which holds a potential carry bit resulting from addition.** 

The operation of the multiplier is as follows. 



Control logic reads the bits of the multiplier one at a time. 

* **If Q0 is 1, then the multiplicand is added to the A register and the result is stored in the A register, with the C bit used for overflow.** 

  Then all of the bits of the C, A, and Q registers are **shifted to the right one bit, so that the C bit goes into A*n*-1, A0 goes into Q*n*-1, and Q0 is lost.**

  * 使用逻辑右移

* **If Q0 is 0, then no addition is performed, just the shift.**

This process is repeated for each bit of the original multiplier. 



**The resulting 2*n*-bit product is contained in the A and Q registers.** 

A flowchart of the operation is shown in Figure 10.9, and an example is given in Figure 10.8b. Note that on the second cycle, when the multiplier bit is 0, there is no add operation.

![image-20221210024133756](/Users/lyk/Library/Application Support/typora-user-images/image-20221210024133756.png)



```java
    /**
     * unsigned integer multiplication
     * @param multiplicand: n-bit
     * @param multiplier: n-bit
     * @param operand_len: n-bit
     * @return 2-n bit
     */
    public String unsigned_mul(String multiplicand, String multiplier, int operand_len)
    {
        assert multiplicand.length() == operand_len;

        //* C: 1-bit C register, 初始化为0, 存放部分积加法运算的可能的进位
        //* A: 初始化为全0
        //* Q: 初始化为multiplier
        //* M: 初始化为multiplicand
        char C = '0';
        String A = String.join( "", Collections.nCopies(operand_len,"0"));
        String Q = multiplier;
        String M = multiplicand;

        for( int i = 0; i < operand_len; i++ )
        {
            char Q_0 = Q.charAt(operand_len-1);

            //If Q0 is 1, then the multiplicand is added to the A register and the result is stored in the A register,
            // with the C bit used for overflow( unsigned addition overflow ).

            //Then all of the bits of the C, A, and Q registers are **shifted to the right one bit,
            // so that the C bit goes into A*n*-1, A0 goes into Q*n*-1, and Q0 is lost.

            //If Q0 is 0, then no addition is performed, just the shift.
            if(Q_0 == '1')
            {
                String temp = carry_adder_with_leftmost_carry_bit(A,M,'0',operand_len);

                C = temp.charAt(0);
                A = temp.substring(1);

            }
            String right_shift_res = logic_shift_right(C + A + Q);//这里只是逻辑右移

            //reassign registers
            C = right_shift_res.charAt(0);
            A = right_shift_res.substring(1,1+operand_len);
            Q = right_shift_res.substring(1+operand_len);
        }

        String res = A + Q; //The resulting 2*n*-bit product is contained in the A and Q registers.
        return res;
    }
```



## Two’s-Complement Multiplication

前面提到了, 对unsigned interger的加减法运算和对补码的加减法运算在比特层面相同. 但是, 对unsigned interger和对补码的**乘/除法**运算,在比特层面是不同的:

例如, 考虑 1011 * 1101 , 将其 进行[Unsigned Multiplication](#Unsigned Multiplication)如下图, 得到结果是10001111:

![Multiplication of Two Unsigned 4-Bit Integers Yielding an 8-Bit Result](/Users/lyk/Library/Application Support/typora-user-images/image-20221210004158725.png)

如果将两个操作数解释为unsigned interger, 即11 * 13, 结果$10001111$被解释为原码143, 符合11 * 13 = 143.

但是, 如果将两个操作数解释为补码, 则上图的运算被解释为$- 5(1011)_2 \times 3 (1101)_2 = - 113 (10001111)$. 

因此, **unsigned interger multiplication对于负数的补码是错误的**.



而错误的原因在于, 根据原码乘法, 原码乘法实际是将**2n-bit** 的 partial products相加, **2n-bit的partial products是n-bit multiplicand的无符号扩展**:

![Unsigned integers](/Users/lyk/Library/Application Support/typora-user-images/image-20221210005056719.png)

, 而对于补码乘法, 

如果multiplier是正的, 那么正确算法是将multiplicand**符号扩展**生成partial products:

![Twos complement integers](/Users/lyk/Library/Application Support/typora-user-images/image-20221210005149372.png)

但是, 如果multiplier是负的, 那么上面的运算依然错误, 因为对于一个补码负数而言, 它的每一位不再能直接对应partial products了



下面介绍Booth’s algorithm:

### Booth’s algorithm

![image-20221210010028362](/Users/lyk/Library/Application Support/typora-user-images/image-20221210010028362.png)

* Q: 初始化为multiplier
* M: 初始化为multiplicand
* A: 初始化为全0
* Q_0: There is also a 1-bit register placed logically to the right of the least significant bit (Q0) of the Q register and designated Q-1, 初始化为0
* The results of the multiplication will appear in the A and Q registers

As before, **the multiplier and multiplicand are placed in the Q and M registers**, respectively. **There is also a 1-bit register placed logically to the right of the least significant bit (Q0) of the Q register and designated Q-1**; its use is explained shortly. 

**The results of the multiplication will appear in the A and Q registers. A and Q-1 are initialized to 0.** 

As before, control logic scans the bits of the multiplier one at a time. Now, as each bit is examined, the bit to its right is also examined. 

* **If the two bits are the same (1–1 or 0–0), then all of the bits of the A, Q, and Q-1 registers are shifted to the right 1 bit.** 

* **If the two bits differ, then the multiplicand is added to or subtracted from the A register, depending on whether the two bits are 0–1 or 1–0.** 

* Following the addition or subtraction, the right shift occurs. In either case, the **right shift** is such that the leftmost bit of A, namely A*n*-1, not only is shifted into A*n*-2, but also remains in A*n*-1. 

  **This is required to preserve the sign of the number in A and Q**. It is known as an **arithmetic shift**, because it preserves the sign bit.



![Example of Booth’s Algorithm (7 * 3)](/Users/lyk/Library/Application Support/typora-user-images/image-20221210010643412.png)



More compactly, the same operation is depicted in Figure 10.14a. The rest of Figure 10.14 gives other examples of the algorithm. As can be seen, it works with any combination of positive and negative numbers. 

<u>Note also the effi- ciency of the algorithm. Blocks of 1s or 0s are skipped over, with an average of only one addition or subtraction per block.</u>

![Examples Using Booth’s Algorithm](/Users/lyk/Library/Application Support/typora-user-images/image-20221210010732244.png)

### Code

```java
    /**
     * signed integer multiplication
     * @param multiplicand: n-bit
     * @param multiplier: n-bit
     * @param operand_len: n-bit
     * @return 2-n bit
     */
    public String signed_mul(String multiplicand, String multiplier, int operand_len) {


        assert operand_len == multiplicand.length();

        //Q: 初始化为multiplier
        //M: 初始化为multiplicand
        //A: 初始化为全0
        //Q_neg_1 = 初始化为0
        String Q = multiplier;
        String M = multiplicand;
        String A = String.join( "", Collections.nCopies(operand_len,"0"));
        String Q_neg_1 = "0";

        for( int i = 0; i < operand_len; i++ )
        {
            String Q_0 = String.valueOf(Q.charAt(operand_len-1));

            String tmp = Q_0 + Q_neg_1;

            if( tmp.equals("10"))
            {
                A = generalSub(M,A); // A <= A - M
            }
            else if(tmp.equals("01"))
            {
                A = generalAdd(M,A); //A <= A + M
            }
            else
                ;
            String right_shift_res = arithmetic_shift_right(A + Q + Q_neg_1);

            //reassign registers
            A = right_shift_res.substring(0, operand_len);
            Q = right_shift_res.substring(operand_len, operand_len*2);
            Q_neg_1 = right_shift_res.substring(operand_len*2);
        }

        //The results of the multiplication will appear in the A and Q registers
        String res = A + Q;
        return res;
    }

```



## Multiplying by Constants



# Integer Division

我们先介绍无符号数的除法, 而有符号数的除法可以调用无符号除法, 然后给结果加上符号



我们规定:

* $D$: dividend
* $V$: divisor
* $Q$: quotient
* $R$: remainder

则除法被表示为:
$$
D=Q \times V + R
$$
因为$D$和$V$的符号不影响$Q$和$R$的绝对值, 因此Two’s-Complement Division可以:

1. 将$D$和$V$转换成正数$|D|$和$|V|$, 使用unsigned division计算$|D| \div |V|$, 得到$|Q|$和$|R|$
2. 根据$D$和$V$的实际符号再确定$Q$和$R$的符号



我们规定:
$$
\mathrm{sign}(R) = \mathrm{sign}(D)  \\ 
\mathrm{sign}(Q) = \mathrm{sign}(D) \times \mathrm{sign}(V)
$$
因此有: 

![image-20221210165210170](/Users/lyk/Library/Application Support/typora-user-images/image-20221210165210170.png)







## Unsigned Division

As before, the basis for the algorithm is the paper-and-pencil approach, and the operation involves repetitive shifting and addition or subtraction.

### Handwrite

![Example of Division of Unsigned Binary Integers](/Users/lyk/Library/Application Support/typora-user-images/image-20221210020524502.png)

手算乘法步骤:

1. First, the bits of the dividend are examined from left to right, until the set of bits examined represents a number greater than or equal to the divisor; this is referred to as **the divisor being able to divide the number.** 

   **When the event occurs, a 1 is placed in the quotient and the divisor is subtracted from the partial dividend.** The result is referred to as a *partial remainder.*

2. From this point on, the division follows a cyclic pattern:

   **At each cycle, additional bits from the dividend are appended to the partial remainder until the result is greater than or equal to the divisor.** 

   **As before, the divisor is subtracted from this number to produce a new partial remainder.** 

3. The process continues until all the bits of the dividend are exhausted.





例子: 
$$
7(0111)_2 \ \div \ 3(0011)_2 = 2(0010)_2
$$


![Example of Division of Unsigned Binary Integers from PPT](/Users/lyk/Library/Application Support/typora-user-images/image-20221208170308003.png)

### Macheine Implementation

This figure shows a machine algorithm that corresponds to the long division process:

![Flowchart for Unsigned Binary Division](/Users/lyk/Library/Application Support/typora-user-images/image-20221210020456583.png)



* A: 初始化为全0. 算法结束后, 存放remainder
* Q: 初始化为dividend. 算法结束后, 存放quotient
* M: 初始化为divisor



Steps:

1. 初始化
2. Cycle:
   1. **At each step, the A and Q registers together are shifted to the left 1 bit.** 
   2. **M is subtracted from A to determine whether A divides the partial remainder.**
      * This is subtraction of unsigned integers. A result that requires a borrow out of the most significant bit is a negative result.
   3. **If it does, then Q0 gets a 1 bit. Otherwise, Q0 gets a 0 bit and M must be added back to A to restore the previous value.** The count is then decremented, and the process continues for *n* steps. 
3. At the end, the quotient is in the Q register and the remainder is in the A register.



### Code

```java
   /**
     * Unsigned int Division, only return quotient + remainder
     *
     * @param dividend
     * @param divisor 如果为0， 则抛出异常
     * @param operand_len
     * @return n-bit quotient + n-bit remainder
     */
    public String unsigned_division(String dividend, String divisor, int operand_len) throws ArithmeticException{

        //* A: 初始化为全0. 算法结束后, 存放remainder
        //* Q: 初始化为dividend. 算法结束后, 存放quotient
        //* M: 初始化为divisor

        if( isZero(divisor))
            throw new ArithmeticException();

        String A = String.join( "", Collections.nCopies(operand_len,"0"));;
        String Q = dividend;
        String M = divisor;

        assert operand_len == dividend.length();


        for(int i=0; i < operand_len; i++)
        {
            String left_shift_res = leftshift_shorten(A.toString() + Q.toString());

            //reassign registers
            A = left_shift_res.substring(0, operand_len);//length(A) = len
            Q = left_shift_res.substring(operand_len);// length(Q) = len - 1
            char Q_0;

            if(largeOrEqual(A,M))//够减
            {
                A = unsignedSub(A,M);
                Q_0 = '1';
            }
            else
                Q_0 = '0';

            Q += Q_0; // now length(Q) = len
        }

        String Quotient = Q;
        String Remainder = A;
        return Quotient + Remainder;
    }
```



## Two’s-Complement Division

例子: 
$$
7(0111)_2 \ \div \ 3(0011)_2 = 2(0010)_2
$$


note that [-3]的补码表示为1101

![Example of Restoring Twos Complement Division (7/3)](/Users/lyk/Library/Application Support/typora-user-images/image-20221210020719922.png)

* A: 初始化为全0. 算法结束后, 存放 $|R|$.
* Q: 初始化为$|D|$. 算法结束后, 存放$|D|$.
* M: 初始化为$|V|$.



步骤如下:

1. 将$D$和$V$转换成正数$|D|$和$|V|$. 这里可以特判一下$|D|$和$|V|$的大小:
   * If  $|V| = |D|$. then the quotient $Q = 1$ and the remainder $R = 0$
   * If $|V| > |D|$, then $Q = 0$ and $R = D$. 
2. 对$|D|$和$|V|$使用之前的[无符号除法](#Unsigned Division), 得到结果 $|R|$ 和$|D|$. 
3. 根据$D$和$V$的实际符号再确定$Q$和$R$的符号, 得到补码形式的$Q$和$R$

****



The algorithm assumes that the divisor $V$ and the dividend $D$ are positive and that $|V| < |D|$. (即够除)

* The algorithm can be summarized as follows:

1. **Load the twos complement of the divisor into the M register; that is, the M register contains the negative of the divisor.** 

   **Load the dividend into the A, Q registers.** The dividend must be expressed as a 2*n*-bit positive number. Thus, for example, the 4-bit 0111 becomes 00000111.

2. **Shift A, Q left 1 bit position.**

3. Perform $A \larr A - M$. **This operation subtracts the divisor from the contents of A.**

4. Two Cases:

   * If the result is nonnegative (most significant bit of A = 0), then set $Q_0 \larr 1$.
   * If the result is negative (most significant bit of A = 1), then set $Q_0 \larr 0$. and restore the previous value of A.

5. Repeat steps 2 through 4 as many times as there are bit positions in Q.

6. The remainder is in A and the quotient is in Q.

### Code

```java
   /**
     * Two’s-Complement Division
     * 方法是将两个操作数当作unsigned interger做除法， 然后根据操作数的符号确定结果的符号，转换成相应补码
     * 该方法对于溢出情况( 4-bit下， -8 / 2 = -4 余 0)也能正确处理: 操作数会被转化为8和2（ -8取反加一后在unsigned int下是8），做除法， 结果是4和0， 然后加上符号
     * @param dividend
     * @param divisor
     * @param operand_len
     * @return quotient + remainder
     */
    public String div(String dividend, String divisor, int operand_len) throws ArithmeticException{
        String D = dividend;
        String V = divisor;
        String R;
        String Q;

        boolean D_is_neg = isNeg(D);
        boolean V_is_neg = isNeg(V);

        String abs_D = convert_to_unsigned_int(D);
        String abs_V = convert_to_unsigned_int(V);

        String unsigned_div_res = unsigned_division(abs_D,abs_V,operand_len);//可能抛出除以0的异常

        String abs_Q = unsigned_div_res.substring(0,operand_len);
        String abs_R = unsigned_div_res.substring(operand_len);

        //sign(R) = sign(D)
        //sign(Q) = sign(D) * sign(V)
        R = isNeg(D) ? InvertPlusOne(abs_R) : abs_R;
        Q = ( (isNeg(D) && !isNeg(V)) || (!isNeg(D) && isNeg(V))) ? InvertPlusOne(abs_Q) : abs_Q;

        return Q + R;
    }
```



## Dividing by Powers of 2

# Final Thoughts on Integer Arithmetic





# Floating Point Arithmetic 

## Addition and Subtraction

![Floating-Point Addition and Subtraction](/Users/lyk/Library/Application Support/typora-user-images/image-20221210033116951.png)

1. Check for zeros and Inf
2. Align the significands.
3. Add or subtract the significands.
4. Normalize the result.



X_sig = 011000110011001100110011000

Y_sig = 110001100110011001100110000

001010011001100110011001000



X_sig = 010100000000000000000000000

Y_sig = 110001100110011001100110000

000101100110011001100110000



## Float Div



![image-20221208231036154](/Users/lyk/Library/Application Support/typora-user-images/image-20221208231036154.png)



27bit尾数做除法:

//TODO

```java
/**
         * 专门为了float的sig的除法准备的
         * 111 / 100 = 111
         * @param operand1
         * @param operand2
         * @return
         */
        public String my_unsignedDivision(String operand1, String operand2) {
            String quotient = "";
            String product = operand1;
            int len = operand1.length();

            for (int i = 0; i < len; i++) product += "0";  //直接在后面加0, 0111 0000
            for (int i = 0; i < len; i++) {

                char end;
                String R1 = product.substring(0,len);
                String temp = carry_adder(product.substring(0, operand1.length()), negation(operand2), '1', operand2.length()).substring(1);//减法结果

              //为什么要用temp[0] == '0'来判断够减?????
                if( temp.charAt(0) == '0' )//确保unsigned减法可以正常进行
                {
                    end = '1';

                    product = temp + product.substring(len);
                }
                else
                {
                    end = '0';
                }
                product = ALU.leftshift_shorten(product) + end;
            }
            quotient = product.substring(len);

            return quotient;

        }

```



- 通过在前面加n位符号扩展被除数，并存储在余数寄存器和商寄存器中

- 将余数和商左移，判断是否“够减”

  • 如果“够”，则做减法(同号)或者加法(异号)，并上 商为1

  • 如果“不够，则上商为0

- 重复以上步骤

- 如果除数和被除数不同号，则将商替换为其相反数

- 余数存在余数寄存器中

- 



![image-20221208231019225](/Users/lyk/Library/Application Support/typora-user-images/image-20221208231019225.png)

完全不理解...
