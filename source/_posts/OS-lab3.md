---
title: OS lab3
tags: OS lab
categories: OS
date: 2021-12-02 23:45:12
---

* Outline
  * 问答
  * 代码实现

<!--more-->

# 问答

当CPU执行了当前指令之后，在对下一条指令执行前，CPU先要判断在执行当前指令的过程中是否发生了中断或异常。如果发生了一个中断或异常，它将调用中断处理程序

## 解释中断向量

* 每个中断源对应一个向量。这些向量顺序存在主存储器的特定存储区（**中断向量表**）

* 向量的内容：

  * 相应中断服务程序的**起始地址** 
  * 处理机状态字。

* 在响应中断时，由中断系统硬件提供向量地址，处理机根据该地址取得向量，并转入相应的中断服务程序

* 作用：

  * 把中断/异常与相应的处理方法通过IDT对应起来

  

## 解释中断类型码

* 我们把每个中断服务程序进行编号，这个号就代表一个中断服务程序，就是中断类型码。这个中断类型码是计算机用来查找中断向量用的。
* 中断指令的一般格式为 “INT n”，其中，n被称为“中断类型码”

## 解释中断向量表

* 中断向量表是指中断服务程序入口地址的偏移量与段基值，一个中断向量占据**4字节**空间。中断向量表是8086系统内存中**最低端1KB**空间，它的作用就是按照中断类型号从小到大的顺序存储对应的中断向量，总共存储256个中断向量。
  * 中断向量表在内存单元的最低处，地址空间为00000H----003FFH(0-1024B)
  * 这个地址正好和中断类型码有一种对应的关系：中断类型码*4(一个中断向量所占的空间) 就等于这个中断向量的首地址。

## 实模式下中断程序地址如何得到?

* 得到中断向量地址 -> 得到中断程序地址
  * 中断类型码*4 == 中断向量的首地址。

* 在中断处理程序中，用中断返回指令IRET （interrupt return）指令使CPU返回主程序断点继续执行；
  * 中断指令 “INT n” 和调用程序指令”CALL”很相似，它们均转入内存中其它程序段执行，执行完后再返回

## INT指令

1. SP（Stack Pointer 堆栈指针）中的值减2，标志位寄存器的值入栈——保存中断前的状态 
2. 标志位TF和IF清0——关闭中断    IF=0 ，CPU不响应外部的可屏蔽中断请求；TF=0，则处于连续工作模式 
3. SP减2，把返回地址的段值（CS）推入堆栈 
4. SP减2，把返回地址的偏移量（IP）推入堆栈 
5. 根据中断类型码n，**从中断向量表中取得中断处理程序地址**，取得的段地址存入CS，偏移量 存入IP。从而使CPU转入中断处理程序运行。

## IRET指令

1.  从堆栈中取出一字（INT指令保存的返回地址偏移量），送给 IP，然后使SP加2 
2. 从堆栈中取出一字（INT指令保存的返回地址段值），送给 CS，然后使SP加2 
3. 从堆栈中取出一字（INT指令保存的标志寄存器的值），送给 标志寄存器，然后使SP加2 IRET执行后，CPU返回到INT指令后面的一条指令

* 其实同函数调用call和ret相类似，在调用时保存返回地址和标志位，但同时还会设置屏蔽请求。iret时则还原调用前状态。

## 保护模式下中断程序地址如何得到?

保护模式下的中断过程则较为复杂，它要借助**中断门描述符**来获取中断子程序这个目标段的描述符，也就是说必须经过**两次查表**才能获得中断服务子程序的入口地址 

### 得到IDT

* IDT
  * 80x86系列引入一个48位的全地址寄存器（即中断描述符表寄存器**IDTR**）**存放IDT的内存地址**，因此不再限于底部1K位置 
  * 和GDTR一样，IDTR包含32位的基地址和16位段限，基地址定义中断描述符表IDT在存储器中的起始点，段限定义中断描述符表所占的字节个数理论上IDT表同样可以有8K项，可是因为80x86只支持256个中断，因此IDT实际上最大只能有256项（2K大小）

* 因此只要查IDTR

> 寄存器CPU切换到保护模式之前，运行于实模式下的初始化程序必须使用LIDT指令装载中断描述符表IDT，将IDT基地址与段界值装入IDTR。如果不完成这一步操作，系统就会100%崩溃。在返回实模式或系统复位时，IDTR中自动装入`000000H`的基地址值与`03FFH`的段界值。可见实模式的**中断向量表**是固定在存储器的最底部，而保护模式下的**IDT**则是**可以改变**的



### 得到中断门

**第一次查表**

1. 确定中断类型码i（在0～255之间）
2. 用`i * 8`算出偏移量，读取IDT表第i项（或叫第i个门。进行有效性检查、特权级变化检查
3. 当CPU执行了当前指令之后，在对下一条指令执行前，CPU先要判断在执行当前指令的过程中是否发生了中断或异常。如果发生了一个中断或异常，那么CPU将做以下事情：
   * 确定所发生中断或异常的向量
   * 通过IDTR寄存器找到IDT表，读取IDT表第i项（或叫第i个门）。进行有效性检查、特权级变化检查
4. 查中断描述符表以IDTR指定的中断描述符表的基地址为起始地址，用调用号N×8算出偏移量，即为N号中断门描述符的首地址

### 根据中断门得到中断处理程序地址

**第二次查表**

1. 由上述方法得到中断门，取中断门的8个字节
2. 查GDT或LDT,根据中断门中的**选择子**（段选择符）和偏移量得到中断处理程序入口

## 中断向量的地址如何得到?

* 见“实模式下中断程序地址如何得到”，

## 实模式下如何根据中断向量的地址得到中断程序地址?

见“实模式下中断程序地址如何得到?”

## 解释中断描述符

* 保护模式下的中断处理与实模式下的中断处理最大区别在于寻找中断处理代码入口的方式
* 在保护模式下，为每一个中断和异常定义了一个**中断描述符**，来说明中断和异常服务程序的入口地址的属性
  由IDT<u>取代实地址模式下的中断向量表</u>
* 中断描述符除了含有中断处理程序地址信息外，还包括许多属性和类型位
  * 每个中断描述符占用连续的**8个字节**，中断描述符分为三类：**任务门、中断门和自陷门**，CPU对不同的门有不同的处理方式

### ID的结构

* 低地址的0和1两个字节是中断代码的偏移量A15～A0； 高地址的6和7两个字节是中断代码的偏移量A31～A16；
* 2和3两个字节是段选择符，段选择符和偏移量用来形成中断服务子程序的入口地址； 
* 4和5两个字节称为访问权限字节，它标识该中断描述符是否有效、服务程序的特权级和描述符的类型等信息； 
  * I. P（present）：表示中断描述符的有效性；
  * II. DPL（descriptor privilege level）；
  * III. TYPE：指示中断描述符的不同类型



## 中断的分类,举例不同类型的中断?

* 从中断源的角度分类
  * 由计算机硬件异常或故障引起的中断，也称为**内部**异常中断。
  * 由程序中执行了中断指令引起的中断，也称为**软**中断。由程序员通过INT或INT3指令触发，通常当做`trap`处理
    * 用处：实现系统调用。
  * 外部设备（如输入输出设备）请求引起的中断，也称为**外部**中断或Ｉ／Ｏ中断。
* 分类：
  * 中断： 由CPU以外的事件引起的中断
     * 如I/O中断、时钟中断、控制台中断等。 
  * 异常：来自CPU的内部事件或程序执行中的事件引起的过程。
     * 如由于CPU本身故障、程序故障和请求系统服务的指令引起的中断等。 

## 中断与异常的区别?

* 见“中断异常共同点(至少两点),不同点(至少三点)”

## 实模式和保护模式下的中断处理差别

* 见上文

## 如何识别键盘组合键(如 Shift+a)是否还有其他解决方案?

* 设置全局变量，每次按下就翻转其值

* 使用`int caps`记录是否要大写字符，若为`true`，则` column = 1`， 即取`keymap`中第二列的值（都是大写值）

* 左右`shift`和`Caps Lock`都会翻转`caps`

  ```c
  int caps = shift_l || shift_r; //如果shift被按下，开启大写
  if (caps_lock) {
  				if ((keyrow[0] >= 'a') && (keyrow[0] <= 'z')){
  					caps = !caps;
  				}
  			}
  if (caps) {
  				column = 1;
  			}
  ...
  ```

  

## IDT 是什么,有什么作用?

* 中断描述符表
* 存终端描述符

## IDT 中有几种描述符?

* 中断描述符分为三类：**任务门、中断门和自陷门**

## 异常的分类?

* Fault，是一种可被更正的异常，而且一旦被更正，程序可以不失连续性地继续执行。返回地址是**产生fault的指令**。
* Trap，一种在发生trap的指令执行之后立即被报告的异常，它也允许程序或任务不失连续性地继续执行。返回地址是产生trap的指令**之后的那条指令**。
* Abort，不总是报告精确异常发生位置的异常，不允许程序或任务继续执行，而是用来报告严重错误的

## 用户态和内核态的特权级分别是多少?

* 当中断发生在用户态（特权级为**3**），而中断处理程序运行在内核态（特权级为**0**）
  * 特权级发生变化，会引起堆栈的更换。也就是说，从用户堆栈切换到内核堆栈。
* 当中断发生在内核态时，即CPU在内核中运行时，则不会更换堆栈。

## 中断向量表中,每个中断有几个字节?里面的结构是什么?

* 起始地址：0
* 每个中断向量包含4 Bytes
* 低地址两个Byte放偏移
* 高地址两个Byte放段描述符
* 最多256个中断向量

## 中断异常共同点(至少两点),不同点(至少三点)

### 共同点

* 都是程序执行过程中的强制性转移，转移到相应的处理程序。
* 都是软件或者硬件发生了某种情形而通知处理器的行为

### 不同点

* 中断是CPU所具备的功能。通常因为“硬件”而随机发生。异常，是“软件”运行过程中的一种开发过程中没有考虑到的程序错误。  
* 中断是CPU暂停当前工作，有计划地去处理其他的事情。中断的发生一般是可以预知的，处理的过程也是事先制定好的。处理中断时程序是正常运行的。 异常是CPU遇到了无法响应的工作，而后进入一种非正常状态。异常的出现表明程序有缺陷。
* 中断是异步的，异常是同步的。
  *  中断是来自处理器外部的I/O设备的信号的结果，它不是由指令流中某条指令执行引起的，从这个意义上讲，它是异步的，是来自指令流之外的。
  * 异常是执行当前指令流中的某条指令的结果，是来自指令流内部的，从这个意义上讲它们都是同步的。
* 中断或异常的返回点
  * 良性的如中断和trap，只是在正常的工作流之外执行额外的操作，然后继续干没干完的活。因此处理程序完了后返回到原指令流的下一条指令，继续执行。
  * 恶性的如fault和abort，对于可修复fault，由于是在上一条指令执行过程中发生（是由正在执行的指令引发的）的，在修复fault之后，会重新执行该指令；至于不可修复fault或abort，则不会再返回。
* 中断是由于当前程序无关的中断信号触发的，CPU对中断的响应是被动的，且与CPU模式无关。既可以发生在用户态，又可以发生在核心态。
  * 异常是由CPU控制单元产生的，大部分异常发生在用户态

# 实验

这是我最难受的OS实验，中途遇到了很多bug,来无影去无踪，不知道怎么发生的，也不知道怎么解决的，莫名其妙地报错，过一会儿又好了QAQ 总的来说学到的东西很少

这里只给出代码逻辑，具体原因需要看`Orange's`第七章

* 实验环境：bochs 2.6.1, manjaro64
* bochsrc: 
  * 更新：`keyboard:  keymap=/usr/share/bochs/keymaps/x11-pc-us.map`
  * 如果没有`vgabios.bin`的话，得自己下载一个。 `qemu`自带了该文件，我就使用了该路径`vgaromimage: file=/usr/share/qemu/vgabios.bin`

* makefile：实现`make run`

  ```makefile
  ...
  BOCHS	= bochs
  BOCHSFLAGS  = -f bochsrc
  ...
  run:	image start_bochs
  start_bochs: 
  	$(BOCHS) $(BOCHSFLAGS)
  ...
  ```

  

## 实现逻辑

* `main.c`里定义了若干 `task`和`process`：

  ```c
  //main.c
  TASK*		p_task		= task_table;
  PROCESS*	p_proc		= proc_table;
  ```

* `task_table`中有四个`task`，其中`tty_task`最重要，负责tty显示. `Test[ABC]`定义在`main.c`中，稍后需要它们来实现清屏功能：

  ```c
  //global.c
  PUBLIC	TASK	task_table[NR_TASKS] = {{task_tty, STACK_SIZE_TTY, "tty"},
  					{TestA, STACK_SIZE_TESTA, "TestA"},
  					{TestB, STACK_SIZE_TESTB, "TestB"},
  					{TestC, STACK_SIZE_TESTC, "TestC"}};
  ```

  ```c
  /*======================================================================*
                                 TestA： 清屏功能
   *======================================================================*/
  void TestA()
  {
  	while (1) {
  		/* disp_str("A."); */
  		if( !SEARCH_MODE )
  		{
  			TTY *p_tty;
  			for( p_tty = TTY_FIRST; p_tty < TTY_END ; p_tty++ )
  			{
  				init_screen(p_tty);
  			}
  			select_console(0);
  			CLS(); //清屏
  			milli_delay(CLS_INTERVAL); //#define CLS_INTERVAL 30000
  		}
  		else{
  //			milli_delay(10);
  		}
  
  	}
  }
  
  /*======================================================================*
                                 TestB
   *======================================================================*/
  void TestB()
  {
  	int i = 0x1000;
  	while(1){
  		/* disp_str("B."); */
  		milli_delay(10);
  	}
  }
  
  /*======================================================================*
                                 TestB
   *======================================================================*/
  void TestC()
  {
  	int i = 0x2000;
  	while(1){
  		/* disp_str("C."); */
  		milli_delay(10);
  	}
  }
  
  ```

* `task_tty`会初始化各个`tty`，并循环执行`tty_do_read(p_tty)` 和`tty_do_write(p_tty)`, 这就是整个程序的输入/出入

  ```c
  //tty.c
  
  /*======================================================================*
                             task_tty
   *======================================================================*/
  PUBLIC void task_tty()
  {
  	TTY*	p_tty;
  
  	init_keyboard();
  
  	for (p_tty=TTY_FIRST;p_tty<TTY_END;p_tty++) {
  		init_tty(p_tty);
  	}
  	select_console(0);
  	while (1) {
  		for (p_tty=TTY_FIRST;p_tty<TTY_END;p_tty++) {
  			tty_do_read(p_tty);
  			tty_do_write(p_tty);
  		}
  	}
  }
  ```

* `tty_do_read(p_tty)` 调用`keyboard_read(p_tty)`，从键盘读取输入; `tty_do_write(p_tty)`从缓冲区读取字符，令`console`打印：

  ```c
  /*======================================================================*
  			      tty_do_read
   *======================================================================*/
  PRIVATE void tty_do_read(TTY* p_tty)
  {
  	if (is_current_console(p_tty->p_console)) {
  		keyboard_read(p_tty);
  	}
  }
  
  
  /*======================================================================*
  			      tty_do_write
   *======================================================================*/
  PRIVATE void tty_do_write(TTY* p_tty)
  {
  	if (p_tty->inbuf_count) {
  		char ch = *(p_tty->p_inbuf_tail);
  		p_tty->p_inbuf_tail++;
  		if (p_tty->p_inbuf_tail == p_tty->in_buf + TTY_IN_BYTES) {
  			p_tty->p_inbuf_tail = p_tty->in_buf;
  		}
  		p_tty->inbuf_count--;
  
  		out_char(p_tty->p_console, ch);
  	}
  }
  
  ```

* `keyboard_read(p_tty)`只负责读取字符，转化成`key`,并调用`in_process(p_tty, key)`处理读取的字符

  ​	* 

  ```c
  //keyboard.c
  PUBLIC void keyboard_read(TTY* p_tty)
  {
      ...
      in_process(p_tty, key);
      ...
  }
  ```

* `in_process(p_tty, key)`真正处理输入，它调用`put_key(p_tty, ** )`将输入的字符存入**缓冲区**， 稍后由`tty_do_write(p_tty)`读取。在里面添加逻辑，实现特殊字符的读取：

  * 这里只是读取，因此只存`ascii`码就行了
    * ` TAB`： `TAB`的`ascii`为`0x09`
    * `` ESC`： `TAB`的`ascii`为`0x1B`
    * 注意到这两个字符其实是**可打印**的，如`TAB（ 0x09）`会打印一个小点，不是我们期望的输出四个空格，因此输出的时候遇到这些字符需要特判，不能直接输出`ascii`

  ```c
  //tty.c
  PUBLIC void in_process(TTY* p_tty, u32 key)
  {
      ...
  	case TAB:
  		put_key(p_tty,  0x09 ); //TAB
  		break;
  	case ESC:
  		put_key(p_tty, 0x1B); //ESC
  		break;   
      ...
  }
  ```

  ```c
  //tty.c
  /*======================================================================*
  			      put_key
  *======================================================================*/
  PRIVATE void put_key(TTY* p_tty, u32 key)
  {
  	if (p_tty->inbuf_count < TTY_IN_BYTES) {
  		*(p_tty->p_inbuf_head) = key;
  		p_tty->p_inbuf_head++;
  		if (p_tty->p_inbuf_head == p_tty->in_buf + TTY_IN_BYTES) {
  			p_tty->p_inbuf_head = p_tty->in_buf;
  		}
  		p_tty->inbuf_count++;
  	}
  }
  ```

* 接下来是输出，`tty_do_write(TTY***** p_tty)`每次从缓冲区读取一个`char`，传给`out_char(p_tty->p_console, ch)`（在指定`console`）进行输出. 在后这种加逻辑，实现特殊字符的输出

  * `TAB`: 打印四个空格，前三个默认颜色`DEFAULT_CHAR_COLOR（黑底白字）`， 最后一个自定义颜色`INVISIBLE_COLOR（黑底黑字）`。 这样在显示上没有差别，而删除时遇到` INVISIBLE_COLOR `就连续删除四个空格

    ```c
    	case '	': // TAB:  三个空格，跟一个0x09
    		if (p_con->cursor + 4 <= p_con->original_addr +
    		    p_con->v_mem_limit - 1 ) {
    
    			for( int i=0; i < 3; i++ )
    			{
    				*p_vmem++ = ' ';
    				*p_vmem++ = DEFAULT_CHAR_COLOR;
    				p_con->cursor++;
    			}
    			*p_vmem++ = ' ';
    			*p_vmem++ = INVISIBLE_COLOR;
    			p_con->cursor++;
    		}
    		break;
    ```

    

  * `\b`: 默认删除当前字符（将改字符变为空格，且颜色置为` INVISIBLE_COLOR `，光标右移一位）。 需要对`TAB`加入上述的特判

    ```c
    	case '\b':
    		if (p_con->cursor > p_con->original_addr) {
    			if( *(p_vmem - 1) == INVISIBLE_COLOR ) //TAB
    			{
    				for( int i = 0 ; i < 4; i++ )
    				{
    					p_con->cursor--;
    					*(p_vmem-2) = ' ';
    					*(p_vmem-1) = DEFAULT_CHAR_COLOR;
    					p_vmem -= 2;
    				}
    			}
    			else{
    				p_con->cursor--;
    				*(p_vmem-2) = ' ';
    				*(p_vmem-1) = DEFAULT_CHAR_COLOR;
    			}
    
    		}
    		break;
    ```

    

  * `ESC`： 第一次按`ESC`进入查找模式，输入带匹配字符串; 第二次解除查找模式，其间按`\n`需要进入匹配模式，期间忽略`ESC`之外的所有输入。 

    * 解除查找模式会删除之前输入的`key_str`,所有被匹配到的文本恢复白颜色, 光标回到进入SEARCH模式时的位置
    
    ```c
    	case CHAR_ESC:// ESC
    
    		SEARCH_MODE = ~ SEARCH_MODE;
    		if( !SEARCH_MODE ) // 再按 Esc 键,之前输入的关键字被自动删除,所有文本恢复白颜色, 光标回到进入SEARCH模式时的位置
    		{
    			restore_matched_chars( p_con, ESC_CURSOR );
    			IGNORE_INPUT = 0;//恢复输入
    		}
    		else{//进入SEARCH模式，记录此时光标位置
    			ESC_CURSOR = p_con -> cursor;
    		}
    		break;
    ```
    
  * `\n`: 在查找模式下，输入回车，会进入匹配模式，匹配到的字符串变为红色，并屏蔽`ESC`之外的输入

      ```c
      	case '\n':
      		if( SEARCH_MODE )
      		{
      			IGNORE_INPUT = 1;
      			char key_str[50];
      			get_key_str( key_str,p_con, ESC_CURSOR );//得到key_str
      			int len = p_con -> cursor -  ESC_CURSOR;
      			match_chars( p_con, key_str, len );
      		}
      		else
      		{
      			if (p_con->cursor < p_con->original_addr +
      		    	p_con->v_mem_limit - SCREEN_WIDTH) {
      				p_con->cursor = p_con->original_addr + SCREEN_WIDTH * 
      					((p_con->cursor - p_con->original_addr) /
      				 	SCREEN_WIDTH + 1);
      			}
      		}
      
      		break;
    ```
    
    
    
  * 采用三个全局变量:
    * `ESC_CURSOR`标记第一次`ESC`对应的光标位置，当第二次输入`ESC`时解除查找模式，这之间的内容就是带匹配字符串`key_str`。 后续用`key_str`作为**滑动窗口**，从屏幕起始位置开始匹配
    * `SEARCH_MODE`： 表示是否处于查找模式，如果为`true`，不仅意味着输入的是`key_str`，还意味着期间不能被**清屏**
    * `IGNORE_INPUT`： 只有处于查找模式且按下回车时置为`true`，期间不响应`ESC`之外的所有输入

  * 重要参数解释:

    * `p_con->cursor`: 光标位置，在最后一个字符之后
    * `u8* p_vmem = (u8*)(V_MEM_BASE + p_con->cursor * 2)`: 当前光标所指向的显存位置，由于小端存储，且字符占2Byte（ 因此有 `cursor * 2`）。 一个字符的低1Byte存字符值，高1Byte存字符颜色
      * 操作字符颜色：`*(p_vmem-1) = DEFAULT_CHAR_COLOR;`
      * 操作字符值：`*(p_vmem- 2) =' '`

  * 一些工具函数：

    ```c
    
    /*======================================================================*
                               get_key_str
     *----------------------------------------------------------------------*
     得到key_str
     *----------------------------------------------------------------------*
     从esc_cursor后一位开始（避免把esc读进去），直到当前cursor
    *======================================================================*/
    PRIVATE void get_key_str( char* key_str, CONSOLE* p_con ,unsigned int esc_cursor  )
    {
    	u8* p_vmem;
    	for( unsigned int tmp_cursor = esc_cursor+1, i = 0  ; tmp_cursor <= p_con -> cursor ; tmp_cursor++ )//从
    	{
    		p_vmem = (u8*)(V_MEM_BASE + tmp_cursor * 2); //指向reverse_cursor指向的位置
    		key_str[i++] = *(p_vmem-2);	
    	}
    }
    
    
    /*======================================================================*
                               match_chars 
    	匹配字符串并染色
    	从光标初始位置，到最后一个ESC的光标位置，对该范围内所有字符进行匹配
    *======================================================================*/
    PRIVATE void match_chars(CONSOLE* p_con, char* key_str, int len )
    {
    
    	for( unsigned int temp_cursor = p_con -> original_addr + 1; temp_cursor < p_con -> cursor - len ; temp_cursor++ ) 
    	{
    		if( isMatch( temp_cursor, key_str, len  ) ) //匹配成功，进行染色
    		{
    			change_chars_color_sequenced( temp_cursor, len, MATCHED_CHAR_COLOR );
    		}
    		
    	}
    
    }
    
    
    
    
    /*======================================================================*
    			   isMatch
     *----------------------------------------------------------------------*
    	从指定cursor前一位开始，匹配key_str
     *----------------------------------------------------------------------*
     *======================================================================*/
    PRIVATE int isMatch( unsigned int cursor, char* key_str, int len   )
    {
    	// key_str = "q";
    	// len = 1;
    	int res = 1;
    	u8* p_vmem =  (u8*)(V_MEM_BASE + cursor * 2);
    	for( int i = 0 ; i < len; i++, p_vmem+=2 )
    	{
    		if( *(p_vmem - 2) != key_str[i] )
    		{
    			res = 0;
    			break;
    		}
    	}
    	return res;
    	
    }
    
    
    /*======================================================================*
                               delete_chars
    *======================================================================*/
    PRIVATE void delete_chars(CONSOLE* p_con, unsigned int len)
    {
    	u8* p_vmem;
    	unsigned int temp_cursor = p_con -> cursor;
    	for(  ; temp_cursor > p_con -> cursor - len ; temp_cursor-- )
    	{
    		p_vmem = (u8*)(V_MEM_BASE + temp_cursor * 2); 
    		*(p_vmem - 1) = DEFAULT_CHAR_COLOR;
    		*(p_vmem - 2) = ' ';
    	}
    	p_con -> cursor = temp_cursor; //移动指针
    }
    
    /*======================================================================*
                               change_chars_color( CONSOLE* p_con, unsigned int len, unsigned int color )
    *======================================================================*/
    PRIVATE void change_chars_color( CONSOLE* p_con, unsigned int len, u8 color )
    {
    	u8* p_vmem;
    	for( unsigned int temp_cursor = p_con -> cursor ; temp_cursor > p_con -> cursor - len ; temp_cursor-- )
    	{
    		p_vmem = (u8*)(V_MEM_BASE + temp_cursor * 2); 
    		*(p_vmem - 1) = DEFAULT_CHAR_COLOR;
    	}
    	
    }
    
    
    
    /*======================================================================*
                               change_chars_color_sequenced( unsigned int cursor, unsigned int len, unsigned int color )
    *======================================================================*/
    PRIVATE void change_chars_color_sequenced( unsigned int cursor, unsigned int len, u8 color )
    {
    	u8* p_vmem;
    	for( unsigned int temp_cursor =  cursor ; temp_cursor <  cursor + len ; temp_cursor++ )
    	{
    		p_vmem = (u8*)(V_MEM_BASE + temp_cursor * 2); 
    		*(p_vmem -1 ) = color;
    	}
    	
    }
    
    
    /*======================================================================*
                               restore_matched_chars
    *======================================================================*/
    PRIVATE void restore_matched_chars(CONSOLE* p_con, unsigned int esc_cursor)
    {
    
    	delete_chars( p_con, p_con -> cursor - esc_cursor ); // 删除待匹配字符
    	change_chars_color( p_con, p_con -> cursor - p_con -> original_addr , DEFAULT_CHAR_COLOR ); //恢复匹配到的字符的颜色
    
    }
    
    ```

    

* 输入输出已经实现了，最后是清屏功能，由于`task_table`中的四个`task`会被四个`process`执行

，只需要由一个`task`负责清屏（）

```c
//main.c
#define TTY_FIRST	(tty_table)
#define TTY_END		(tty_table + NR_CONSOLES)
#define CLS_INTERVAL 30000

...
    
void CLS()
{
			disp_pos = 0;
			for( int i = 0 ; i < 80*25; i++ )
			{
				disp_str(" ");
			}
			disp_pos = 0;
}
/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
	while (1) {
		/* disp_str("A."); */
		if( !SEARCH_MODE )
		{
			TTY *p_tty;
			for( p_tty = TTY_FIRST; p_tty < TTY_END ; p_tty++ ) //这段抄书的，我也不明白意思
			{
				init_screen(p_tty);
			}
			select_console(0);
			CLS();
			milli_delay(CLS_INTERVAL);
		}
		else{
//			milli_delay(10);
		}

	}
}
```

