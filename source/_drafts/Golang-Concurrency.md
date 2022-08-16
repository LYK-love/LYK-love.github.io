---
title: Golang Concurrency
tags:
---



## goroutine

Go语言中使用goroutine非常简单，只需要在函数或者方法前面加上go关键字就可以创建一个goroutine，从而让该函数或者方法在新的goroutine中执行

匿名函数同样也支持使用go关键字来创建goroutine去执行

一个goroutine必定对应一个函数或者方法，可以创建多个goroutine去执行相同的函数或者方法

## 启动单个goroutine

启动方式非常简单，我们先来看一个案例

```
package main

import (
	"fmt"
)

func hello() {
	fmt.Println("hello")
}

func main() {
	go hello()
	fmt.Println("欢迎来到编程狮")
}
```

尝试一下

以上代码输出结果如下

```
欢迎来到编程狮
```

上述代码执行结果只在终端控制台输出了“欢迎来到编程狮”，并没有打印“hello”，这是为什么呢 ？.

其实在Go程序中，会默认为main函数创建一个goroutine，而在上述代码中我们使用go关键字创建了一个新的goroutine去调用hello函数。而此时main的goroutine还在往下执行中，我们的程序中存在两个并发执行的goroutine。当main函数结束时，整个程序也结束了，所有由main函数创建的子goroutine也会跟着退出，也就是说我们的main函数执行过快退出导致另一个goroutine内容还未执行就退出了，导致未能打印出hello

所以我们这边要想办法让main函数等一等，让另一个goroutine的内容执行完。其中最简单的方法就是在main函数中使用time.sleep睡眠一秒钟

按如下方式修改

```
package main

import (
	"fmt"
	"time"
)

func hello(){
	fmt.Println("hello")
}

func main() {
	go hello()
	fmt.Println("欢迎来到编程狮")
	time.Sleep(time.Second)
}
```

尝试一下

此时的输出结果为

```
欢迎来到编程狮
hello
```

为什么会先打印欢迎来到编程狮呢？

这是因为在程序中创建 goroutine 执行函数需要一定的开销，而与此同时 main 函数所在的 goroutine 是继续执行的。

## sync.WaitGroup

在上述代码中使用time.sleep的方法是不准确的

Go语言中的sync包为我们提供了一些常用的并发原语

在这一小节，我们介绍一下sync包中的WaitGroup。当你并不关心并发操作的结果或者有其它方式收集并发操作的结果时，WaitGroup是实现等待一组并发操作完成的好方法

我们再修改下上述代码

```
package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func hello() {
	fmt.Println("hello")
	defer wg.Done()//把计算器-1
}

func main() {
	wg.Add(1)//把计数器+1
	go hello()
	fmt.Println("欢迎来到编程狮")
	wg.Wait()//阻塞代码的运行，直到计算器为0
}
```

尝试一下

以上代码输出结果如下

```
欢迎来到编程狮
hello
```

## 启动多个goroutine

在Go语言中启动并发就是这么简单，接下来我们看看如何启动多个goroutine

```
package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func hello(i int) {
	fmt.Printf("hello,欢迎来到编程狮%v\n", i)
	defer wg.Done()//goroutine结束计数器-1
}

func main() {
	for i := 0; i < 10; i++ {
		go hello(i)
		wg.Add(1)//启动一个goroutine计数器+1
	}
	wg.Wait()//等待所有的goroutine执行结束
}
```

尝试一下

以上代码执行结果如下

```
hello,欢迎来到编程狮6
hello,欢迎来到编程狮9
hello,欢迎来到编程狮4
hello,欢迎来到编程狮7
hello,欢迎来到编程狮8
hello,欢迎来到编程狮0
hello,欢迎来到编程狮3
hello,欢迎来到编程狮2
hello,欢迎来到编程狮1
hello,欢迎来到编程狮5
```

执行多次上述代码你会发现输出顺序并不一致，这是因为10个goroutine都是并发执行的，而goroutine的调度是随机的

## 动态栈

操作系统的线程一般都有固定的栈内存（通常为2MB），而 Go 语言中的 goroutine 非常轻量级，一个 goroutine 的初始栈空间很小（一般为2KB），所以在 Go 语言中一次创建数万个 goroutine 也是可能的。并且 goroutine 的栈不是固定的，可以根据需要动态地增大或缩小， Go 的 runtime 会自动为 goroutine 分配合适的栈空间。

## goroutine调度

在经过数个版本迭代之后，目前Go语言的调度器采用的是GPM调度模型

- G: 表示goroutine，存储了goroutine的执行stack信息、goroutine状态以及goroutine的任务函数等；另外G对象是可以重用的。
- P: 表示逻辑processor，P的数量决定了系统内最大可并行的G的数量（前提：系统的物理cpu核数>=P的数量）；P的最大作用还是其拥有的各种G对象队列、链表、一些cache和状态。
- M: M代表着真正的执行计算资源。在绑定有效的p后，进入schedule循环；而schedule循环的机制大致是从各种队列、p的本地队列中获取G，切换到G的执行栈上并执行G的函数，调用goexit做清理工作并回到m，如此反复。M并不保留G状态，这是G可以跨M调度的基础。

## GOMAXPROCS

Go运行时，调度器使用GOMAXPROCS的参数来决定需要使用多少个OS线程来同时执行Go代码。默认值是当前计算机的CPU核心数。例如在一个8核处理器的电脑上，GOMAXPROCS默认值为8。Go语言中可以使用runtime.GOMAXPROCS()函数设置当前程序并发时占用的CPU核心数

## channel

单纯地将函数并发执行是没有意义的，函数与函数间需要交换数据才能体现并发执行函数的意义

虽然可以使用共享内存进行数据交换，但是共享内存在不同的 goroutine 中容易发生竞态问题。为了保证数据交换的正确性，很多并发模型中必须使用互斥锁对内存进行加锁，这种做法势必造成性能问题

Go语言采用的并发模型是CSP（Communicating Sequential Processes），提倡通过通信共享内存，而不是通过共享内存而实现通信

Go 语言中的通道（channel）是一种特殊的类型。通道像一个传送带或者队列，总是遵循先入先出的规则，保证收发数据的顺序。每一个通道都是一个具体类型的导管，也就是声明channel的时候需要为其指定元素类型。

## channel类型

声明通道类型变量方法如下

```
var 变量名 chan 元素类型
```

其中chan是关键字，元素类型指通道中传递的元素的类型

举几个例子

```
var a chan int //声明一个传递int类型的通道
var b chan string // 声明一个传递string类型的通道
var c chan bool //声明一个传递bool类型的通道
```

## channel零值

未经初始化的通道默认值为nil

```
package main

import "fmt"

func main() {
	var a chan map[int]string
	fmt.Println(a)
}
```

以上代码执行结果如下

```
<nil>
```

## 初始化channel

声明的通道类型变量需要使用内置的make函数初始化之后才能使用，具体格式如下

```
make(chan 元素类型,[缓冲大小])
```

channel的缓冲大小是可选的

```
a:=make(chan int)
b:=make(chan int,10)//声明一个缓冲大小为10的通道
```

## channel操作

通道共有发送，接收，关闭三种操作，而发送和接收操作均用`<-`符号，举几个例子



- 声明通道并初始化



```
a := make(chan int) //声明一个通道并初始化
```



- 给一个通道发送值



```
a <- 10  //把10发送给a通道
```



- 从一个通道中取值



```
x := <-a //x从a通道中取值
<-a      //从a通道中取值，忽略结果
```



- 关闭通道



```
close(a) //关闭通道
```

一个通道值是可以被垃圾回收掉的。通道通常由发送方执行关闭操作，并且只有在接收方明确等待通道关闭的信号时才需要执行关闭操作。它和关闭文件不一样，通常在结束操作之后关闭文件是必须要做的，但关闭通道不是必须的。

关闭后的通道有以下特点

- 对一个关闭的通道再发送值就会导致 panic。
- 对一个关闭的通道进行接收会一直获取值直到通道为空。
- 对一个关闭的并且没有值的通道执行接收操作会得到对应类型的零值。
- 关闭一个已经关闭的通道会导致 panic。

## 无缓冲的通道

无缓冲的通道又称为阻塞的通道，我们来看一下如下代码片段

```
package main

import "fmt"

func main() {
	a := make(chan int)
	a <- 10
	fmt.Println("发送成功")
}
```

尝试一下

上面这段代码能够通过编译，但是执行时会报错

```
fatal error: all goroutines are asleep - deadlock!     

goroutine 1 [chan send]:
main.main()
        C:/Users/W3Cschool/Desktop/test/main.go:7 +0x31
exit status 2
```

deadlock表示我们程序中所有的goroutine都被挂起导致程序死锁了，为什么会出现这种情况呢？

这是因为我们创建的是一个无缓冲区的通道，无缓冲的通道只有在有接收方能够接收值的时候才能发送成功，否则会一直处于等待发送的阶段。同理，如果对一个无缓冲通道执行接收操作时，没有任何向通道中发送值的操作那么也会导致接收操作阻塞。

我们可以创建一个goroutine去接收值，例如

```
package main

import "fmt"

func receive(x chan int) {
	ret := <-x
	fmt.Println("接收成功", ret)
}

func main() {
	a := make(chan int)
	go receive(a)
	a <- 10
	fmt.Println("发送成功")
}
```

尝试一下

以上代码执行结果如下

```
接收成功 10
发送成功
```

## 有缓冲区的通道

另外还有一种方法解决上述死锁的问题，那就是使用有缓冲区的通道。我们可以在使用make函数初始化通道时，为其指定缓冲区大小，例如

```
package main

import "fmt"

func main() {
	a := make(chan int,1)
	a <- 10
	fmt.Println("发送成功")
}
```

尝试一下

以上代码执行结果如下

```
发送成功
```

只要通道的容量大于零，那么该通道就属于有缓冲的通道，通道的容量表示通道中最大能存放的元素数量。当通道内已有元素数达到最大容量后，再向通道执行发送操作就会阻塞，除非有从通道执行接收操作。

我们可以使用内置的len函数获取通道的长度，使用cap函数获取通道的容量

## 判断通道关闭

当向通道中发送完数据时，我们可以通过close函数来关闭通道。当一个通道被关闭后，再往该通道发送值会引发panic。从该通道取值的操作会先取完通道中的值。通道内的值被接收完后再对通道执行接收操作得到的值会一直都是对应元素类型的零值。那我们如何判断一个通道是否被关闭了呢？

```
value, ok := <-ch
```

value：表示从通道中所取得的值

ok：若通道已关闭，返回false，否则返回true

以下代码会不断从通道中取值，直到通道被关闭后退出

```
package main

import "fmt"

func receive(ch chan int) {
	for {
		v, ok := <-ch
		if !ok {
			fmt.Println("通道已关闭")
			break
		}
		fmt.Printf("v:%#v ok:%#v\n", v, ok)
	}
}

func main() {
	ch := make(chan int, 1)
	ch <- 1
	close(ch)
	receive(ch)
}
```

尝试一下

以上代码执行结果如下

```
v:1 ok:true
通道已关闭
```

## for range接收值

通常我们会使用for range循环来从通道中接收值，当通道关闭后，会在通道内所有值被取完之后退出循环，上面的例子我们使用for range会更加简洁

```
package main

import "fmt"

func receive(ch chan int) {
	for i:=range ch{
		fmt.Printf("v:%v",i)
	}
}

func main() {
	ch := make(chan int, 1)
	ch <- 1
	close(ch)
	receive(ch)
}
```

尝试一下

以上代码执行结果如下

```
v:1
```

## 单向通道

在某些场景下我们可能会将通道作为参数在多个任务函数间进行传递，通常我们会选择在不同的任务函数中对通道的使用进行限制，比如限制通道在某个函数中只能执行发送或只能执行接收操作

```
<- chan int // 只接收通道，只能接收不能发送
chan <- int // 只发送通道，只能发送不能接收
```

## select多路复用

在某些场景下我们可能需要同时从多个通道接收数据。通道在接收数据时，如果没有数据可以被接收那么当前 goroutine 将会发生阻塞。Go语言内置了select关键字，使用它可以同时响应多个通道的操作，具体格式如下

```
select {
case <-ch1:
	//...
case data := <-ch2:
	//...
case ch3 <- 10:
	//...
default:
	//默认操作
}
```

select语句具有以下特点

- 可处理一个或多个channel的发送/接收操作
- 如果多个case同时满足，select会随机选择一个执行
- 对于没有case的select会一直阻塞，可用于阻塞 main 函数，防止退出

下面这段代码在终端中打印1-10之间的奇数，借助这段代码来看下select的使用方法

```
package main

import "fmt"

func main() {
	ch := make(chan int, 1)//创建一个类型为int，缓冲区大小为1的通道
	for i := 1; i <= 10; i++ {
		select {
		case x := <-ch://第一次循环由于没有值，所以该分支不满足
			fmt.Println(x)
		case ch <- i://将i发送给通道(由于缓冲区大小为1，缓冲区已满，第二次不会走该分支)
		}
	}
}
```

尝试一下

以上代码执行结果如下

```
1
3
5
7
9
```

## 并发安全和互斥锁

有时候我们的代码中可能会存在多个 goroutine 同时操作一个资源的情况，这种情况下就会发生数据读写错乱的问题，例如下面这段代码

```
package main

import (
	"fmt"
	"sync"
)

var (
	x int64
	wg sync.WaitGroup // 等待组
)

// add 对全局变量x执行5000次加1操作
func add() {
	for i := 0; i < 5000; i++ {
		x = x + 1
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go add()
	go add()
	wg.Wait()
	fmt.Println(x)
}
```

我们将上述代码执行多次，不出意外会输出许多不同的结果，这是为什么呢？

因为在上述代码中，我们开启了2个goroutine去执行add函数，某个goroutine对全局变量x的修改可能会覆盖掉另外一个goroutine中的操作，所以导致结果与预期不符

互斥锁

互斥锁是一种常用的控制共享资源访问的方法，它能够保证同一时间只有一个 goroutine 可以访问共享资源。Go语言中使用sync包中提供的Mutex类型来实现互斥锁

我们在下面的代码中使用互斥锁限制每次只有一个goroutine能修改全局变量x，从而解决上述问题

```
package main

import (
	"fmt"
	"sync"
)

var (
	x  int64
	wg sync.WaitGroup
	m  sync.Mutex // 互斥锁
)

func add() {
	for i := 0; i < 5000; i++ {
		m.Lock() // 修改x前加锁
		x = x + 1
		m.Unlock() // 改完解锁
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go add()
	go add()
	wg.Wait()
	fmt.Println(x)
}
```

将上述代码编译后多次执行，最终结果都会是10000

使用互斥锁能够保证同一时间有且只有一个 goroutine 进入临界区，其他的 goroutine 则在等待锁；当互斥锁释放后，等待的 goroutine 才可以获取锁进入临界区，多个 goroutine 同时等待一个锁时，唤醒的策略是随机的

## 读写互斥锁

互斥锁是完全互斥的，但是实际上有很多场景是读多写少的，当我们并发的去读取一个资源而不涉及资源修改的时候是没有必要加互斥锁的，这种场景下使用读写锁是更好的一种选择。在Go语言中使用sync包中的RWMutex类型来实现读写互斥锁

读写锁分为两种：读锁和写锁。当一个 goroutine 获取到读锁之后，其他的 goroutine 如果是获取读锁会继续获得锁，如果是获取写锁就会等待；而当一个 goroutine 获取写锁之后，其他的 goroutine 无论是获取读锁还是写锁都会等待

以下为读多写少场景

```
package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	x  = 0
	wg sync.WaitGroup
	// lock sync.Mutex
	rwlock sync.RWMutex
)

func read() {
	defer wg.Done()
	// lock.Lock()
	rwlock.RLock()
	fmt.Println(x)
	time.Sleep(time.Millisecond)
	rwlock.RUnlock()
	// lock.Unlock()
}

func write() {
	defer wg.Done()
	rwlock.Lock()
	// lock.Lock()
	x += 1
	time.Sleep(time.Millisecond * 5)
	rwlock.Unlock()
	// lock.Unlock()
}

func main() {
	start := time.Now()
	for i := 0; i < 10; i++ {
		go write()
		wg.Add(1)
	}
	time.Sleep(time.Second)
	for i := 0; i < 1000; i++ {
		go read()
		wg.Add(1)
	}
	wg.Wait()
	fmt.Println(time.Since(start))
}
```
