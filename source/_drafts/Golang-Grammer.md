---
title: Golang Grammer
tags: Golang
categories: Language
---



# Program Structure

1. “Go源文件一般以.go作为后缀，文件名全部小写，多个单词之间用下划线分隔。Go语言规范要求Go源文件必须使用UTF-8编码，详见https://golang.org/ref/spec。”
2. “Go语言有函数（Function）和方法（Method）之分，方法调用需要receiver，函数调用则不需要”

3. 必须在源文件中非注释的第一行指明这个文件属于哪个包，如：package main
4. 入口程序或者说可独立执行的程序必须位于package main
5. 入口程序必须包含main函数.  程序执行时,先进行全局变量初始化; 然后执行`init()`函数(如果有的话); 然后执行`main()`
6. 下一行 *func main()* 是程序开始执行的函数。main 函数是每一个可执行程序所必须包含的，一般来说都是在启动后第一个执行的函数（如果有 init() 函数则会先执行该函数）
7. 大写字母开头的identifier是对外部包可见的( 相当于OO语言的public ), 而小写开头的identifier是对外部包不可见多( 相当于OO语言的private )
8. 必须使用所有被声明的变量. 
9. 如果不想要函数的返回值, 可以用`_`, `_` 实际上是一个只写变量，你不能得到它的值

# Data Type

不同类型的局部和全局变量默认值为：

| 数据类型 | 初始化默认值 |
| :------- | :----------- |
| int      | 0            |
| float32  | 0            |
| pointer  | nil          |

## Variable

声明后若不赋值，使用默认值:

```go
var identifier type
v_name = value
```



也可以在声明时直接赋值,此时可以不声明变量类型, 类型会自动推导:

```
var v_name = value
```



使用`:=`来在一行内声明变量, 并且省略`var`. 这种初始化方式只能被用在函数体内，而不可以用于全局变量的声明与赋值. 出现在:=左侧的变量不应该是已经被声明过的，否则会导致编译错误

```
var a int = 10
var b = 10
c := 10
```



多变量声明:

```go
var vname1, vname2, vname3 = v1, v2, v3 //和python很像,不需要显示声明类型，自动推断

var (  
    a int
    b bool
)
```





空白标识符 _ 也被用于抛弃值，如值 5 在：_, b = 5, 7 中被抛弃。

。这样做是因为 Go 语言中你，但有时你并不需要使用从一个函数得到的所有返回值。

## 常量

常量的定义格式：

```
const identifier [type] = value
```

你可以省略类型说明符 [type]，因为编译器可以根据变量的值来推断其类型。

- 显式类型定义： `const b string = "abc"`
- 隐式类型定义： `const b = "abc"`

多个相同类型的声明可以简写为：

```
const c_name1, c_name2 = value1, value2
```



常量的值也可以是常量表达式：

```go
import "unsafe"
const (
    a = "abc"
    b = len(a)
    c = unsafe.Sizeof(a)
)
```



## iota

iota，特殊常量，可以认为是一个可以被编译器修改的常量。

在每一个const关键字出现时，被重置为0，然后再下一个const出现之前，每出现一次iota，其所代表的数字会自动增加1。

iota 可以被用作枚举值：

```
const (
    a = iota
    b = iota
    c = iota
)
```

第一个 iota 等于 0，每当 iota 在新的一行被使用时，它的值都会自动加 1；所以 a=0, b=1, c=2 可以简写为如下形式：

```
const (
    a = iota
    b
    c
)
```

## Control Flow

Go语言的条件语句不需要小括号, 当然你可以加, 只是不符合代码规范:

```go
if  a && b  {      
  fmt.Printf("第一行 - 条件为 true\n" )   
}
```



## Functions

Go 语言函数定义格式如下：

```
func function_name( [parameter list] ) [return_types]{
   函数体
}
```

函数定义解析：

- func：函数由 func 开始声明
- function_name：函数名称，函数名和参数列表一起构成了函数签名。
- parameter list]：参数列表，参数就像一个占位符，当函数被调用时，你可以将值传递给参数，这个值被称为实际参数。参数列表指定的是参数类型、顺序及参数个数。参数是可选的，也就是说函数也可以不包含参数。
- return_types：返回类型，函数返回一列值。return_types 是该列值的数据类型。有些功能不需要返回值，这种情况下 return_types 不是必须的。
- 函数体：函数定义的代码集合。



默认情况下，Go 语言使用的是**值传递**，即在调用过程中不会影响到实参

### defer语句

Go语言中的defer语句会将其后面跟随的语句进行延迟处理

在defer所属的函数即将返回时，将延迟处理的语句按照defer定义的顺序逆序执行，即先进后出

```go
package main

import "fmt"

func main() {
	fmt.Println("开始")
	defer fmt.Println(1)
	defer fmt.Println(2)
	defer fmt.Println(3)
	fmt.Println("结束")
}
```

以上代码执行结果如下

```
开始
结束
3
2
1
```

# Pointer

https://www.cnblogs.com/cheyunhua/p/15302200.html

```go
var var_name *var-type
```

Go的空指针值为`nil`



# Array

### 声明数组

Go 语言数组声明需要指定元素类型及元素个数，语法格式如下：

```
var variable_name [SIZE] variable_type
```

以上为一维数组的定义方式。数组长度必须是整数且大于 0。例如以下定义了数组 balance 长度为 10，类型为 float32：

```
var balance [10] float32
```

### 初始化数组

以下演示了数组初始化：

```
var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
```

初始化数组中 {} 中的元素个数不能大于 [] 中的数字。

如果忽略 [] 中的数字不设置数组大小，Go 语言会根据元素的个数来设置数组的大小：

```
 var balance = []float32{1000.0, 2.0, 3.4, 7.0, 50.0}
```

该实例与上面的实例是一样的，虽然没有设置数组的大小。

```
 balance[4] = 50.0
```



**Go数组长度不可变**

## Structure

### 定义结构体

结构体定义需要使用 type 和 struct 语句。struct 语句定义一个新的数据类型，结构体中有一个或多个成员。type 语句设定了结构体的名称。结构体的格式如下：

```
type struct_variable_type struct {
   member definition
   member definition
   ...
   member definition
}
```

一旦定义了结构体类型，它就能用于变量的声明，语法格式如下：

```
variable_name := structure_variable_type {value1, value2...valuen}
```

### 使用结构体

访问结构体实例的成员使用`.`操作符:



和CPP不同, Go中通过结构体实例的指针,访问结构体示例的成员, 也使用`.`操作符:

```go
package main

import "fmt"

type Books struct {
   title string
   author string
   subject string
   book_id int
}

func main() {
   var Book1 Books        /* Declare Book1 of type Book */
   var Book2 Books        /* Declare Book2 of type Book */

   /* book 1 描述 */
   Book1.title = "Go 语言"
   Book1.author = "www.w3cschool.cn"
   Book1.subject = "Go 语言教程"
   Book1.book_id = 6495407

   /* book 2 描述 */
   Book2.title = "Python 教程"
   Book2.author = "www.w3cschool.cn"
   Book2.subject = "Python 语言教程"
   Book2.book_id = 6495700

   /* 打印 Book1 信息 */
   printBook(&Book1)

   /* 打印 Book2 信息 */
   printBook(&Book2)
}
func printBook( book *Books ) {
   fmt.Printf( "Book title : %s\n", book.title) //book是个指针
   fmt.Printf( "Book author : %s\n", book.author)
   fmt.Printf( "Book subject : %s\n", book.subject)
   fmt.Printf( "Book book_id : %d\n", book.book_id)
}
```



## Slice

### 定义切片

你可以声明一个未指定大小的数组来定义切片：

```
var identifier []type
```

切片不需要说明长度。

或使用make()函数来创建切片:

```
var slice1 []type = make([]type, len)
```

也可以简写为

```
slice1 := make([]type, len)
```

也可以指定容量，其中capacity为可选参数。

```
make([]T, length, capacity)
```

这里 len 是数组的长度并且也是切片的初始长度。

### 切片初始化

```
s :=[] int {1,2,3 } 
```

直接初始化切片，[]表示是切片类型，{1,2,3}初始化值依次是1,2,3.其cap=len=3

```
s := arr[:] 
```

初始化切片s,是数组arr的引用

```
s := arr[startIndex:endIndex] 
```

将arr中从下标startIndex到endIndex-1 下的元素创建为一个新的切片

```
s := arr[startIndex:] 
```

缺省endIndex时将表示一直到arr的最后一个元素

```
s := arr[:endIndex] 
```

缺省startIndex时将表示从arr的第一个元素开始

```
s1 := s[startIndex:endIndex] 
```

通过切片s初始化切片s1

```
s :=make([]int,len,cap) 
```

通过内置函数make()初始化切片s,[]int 标识为其元素类型为int的切片

### len() 和 cap() 函数

切片是可索引的，并且可以由 len() 方法获取长度。

切片提供了计算容量的方法 cap() 可以测量切片最长可以达到多少。

以下为具体实例：

```
package main

import "fmt"

func main() {
   var numbers = make([]int,3,5)

   printSlice(numbers)
}

func printSlice(x []int){
   fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
```

尝试一下

以上实例运行输出结果为:

```
len=3 cap=5 slice=[0 0 0]
```

### 空(nil)切片

一个**切片在未初始化之前默认为 nil**，长度为 0，实例如下：

```go
package main

import "fmt"

func main() {
   var numbers []int

   printSlice(numbers)

   if(numbers == nil){
      fmt.Printf("切片是空的")
   }
}

func printSlice(x []int){
   fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
```

尝试一下

以上实例运行输出结果为:

```
len=0 cap=0 slice=[]
切片是空的
```

### 切片截取

可以通过设置下限及上限来设置截取切片 *[lower-bound:upper-bound]*，实例如下：

```
package main

import "fmt"

func main() {
   /* 创建切片 */
   numbers := []int{0,1,2,3,4,5,6,7,8}   
   printSlice(numbers)

   /* 打印原始切片 */
   fmt.Println("numbers ==", numbers)

   /* 打印子切片从索引1(包含) 到索引4(不包含)*/
   fmt.Println("numbers[1:4] ==", numbers[1:4])

   /* 默认下限为 0*/
   fmt.Println("numbers[:3] ==", numbers[:3])

   /* 默认上限为 len(s)*/
   fmt.Println("numbers[4:] ==", numbers[4:])

   numbers1 := make([]int,0,5)
   printSlice(numbers1)

   /* 打印子切片从索引  0(包含) 到索引 2(不包含) */
   number2 := numbers[:2]
   printSlice(number2)

   /* 打印子切片从索引 2(包含) 到索引 5(不包含) */
   number3 := numbers[2:5]
   printSlice(number3)

}

func printSlice(x []int){
   fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
```

尝试一下

执行以上代码输出结果为：

```
len=9 cap=9 slice=[0 1 2 3 4 5 6 7 8]
numbers == [0 1 2 3 4 5 6 7 8]
numbers[1:4] == [1 2 3]
numbers[:3] == [0 1 2]
numbers[4:] == [4 5 6 7 8]
len=0 cap=5 slice=[]
len=2 cap=9 slice=[0 1]
len=3 cap=7 slice=[2 3 4]
```

### append() 和 copy() 函数

如果想增加切片的容量，我们必须创建一个新的更大的切片并把原分片的内容都拷贝过来。

下面的代码描述了从拷贝切片的 copy 方法和向切片追加新元素的 append 方法。

```go
package main

import "fmt"

func main() {
   var numbers []int
   printSlice(numbers)

   /* 允许追加空切片 */
   numbers = append(numbers, 0)
   printSlice(numbers)

   /* 向切片添加一个元素 */
   numbers = append(numbers, 1)
   printSlice(numbers)

   /* 同时添加多个元素 */
   numbers = append(numbers, 2,3,4)
   printSlice(numbers)

   /* 创建切片 numbers1 是之前切片的两倍容量*/
   numbers1 := make([]int, len(numbers), (cap(numbers))*2)

   /* 拷贝 numbers 的内容到 numbers1 */
   copy(numbers1,numbers)
   printSlice(numbers1)   
}

func printSlice(x []int){
   fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
}
```

## range

Go 语言中 range 关键字用于for循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素。在数组和切片中它返回元素的索引值，在集合中返回 key-value 对的 key 值。

对于映射，它返回下一个键值对的键。Range返回一个值或两个值。如果在Range表达式的左侧只使用了一个值，则该值是下表中的第一个值。

| Range表达式             | 第一个值   | 第二个值[可选的] |
| ----------------------- | ---------- | ---------------- |
| Array 或者 slice a [n]E | 索引 i int | a[i] E           |
| String s string type    | 索引 i int | rune int         |
| map m map[K]V           | 键 k K     | 值 m[k] V        |
| channel c chan E        | 元素 e E   | none             |

### 实例

```go
package main
import "fmt"
func main() {
    //这是我们使用range去求一个slice的和。使用数组跟这个很类似
    nums := []int{2, 3, 4}
    sum := 0
    for _, num := range nums {
        sum += num
    }
    fmt.Println("sum:", sum)
    //在数组上使用range将传入index和值两个变量。上面那个例子我们不需要使用该元素的序号，所以我们使用空白符"_"省略了。有时侯我们确实需要知道它的索引。
    for i, num := range nums {
        if num == 3 {
            fmt.Println("index:", i)
        }
    }
    //range也可以用在map的键值对上。
    kvs := map[string]string{"a": "apple", "b": "banana"}
    for k, v := range kvs {
        fmt.Printf("%s -> %s\n", k, v)
    }
    //range也可以用来枚举Unicode字符串。第一个参数是字符的索引，第二个是字符（Unicode的值）本身。
    for i, c := range "go" {
        fmt.Println(i, c)
    }
}
```

## map

可以使用内建函数 make 也可以使用 map 关键字来定义 Map:

```
/* 声明变量，默认 map 是 nil */
var map_variable map[key_data_type]value_data_type

/* 使用 make 函数 */
map_variable = make(map[key_data_type]value_data_type)
```

如果不初始化 map，那么就会创建一个 nil map。nil map 不能用来存放键值对

## Type Convert

类型转换用于将一种数据类型的变量转换为另外一种类型的变量。Go 语言类型转换基本格式如下：

```
type_name(expression)
```



go 不支持隐式转换类型

```go
package main
import "fmt"

func main() {  
    var a int64 = 3
    var b int32
    b = a
    fmt.Printf("b 为 : %d", b)
}
```

会报错



## interface

Go 语言提供了另外一种数据类型即接口，它把所有的具有共性的方法定义在一起，任何其他类型只要实现了这些方法就是实现了这个接口。

实例

```go
/* 定义接口 */
type interface_name interface {
   method_name1 [return_type]
   method_name2 [return_type]
   method_name3 [return_type]
   ...
   method_namen [return_type]
}

/* 定义结构体 */
type struct_name struct {
   /* variables */
}

/* 实现接口方法 */
func (struct_name_variable struct_name) method_name1() [return_type] {
   /* 方法实现 */
}
...
func (struct_name_variable struct_name) method_namen() [return_type] {
   /* 方法实现*/
}
```



实例

```go
package main

import (
    "fmt"
)

type Phone interface {
    call()
}

type NokiaPhone struct {
}

func (nokiaPhone NokiaPhone) call() {
    fmt.Println("I am Nokia, I can call you!")
}

type IPhone struct {
}

func (iPhone IPhone) call() {
    fmt.Println("I am iPhone, I can call you!")
}

func main() {
    var phone Phone

    phone = new(NokiaPhone)
    phone.call()

    phone = new(IPhone)
    phone.call()

}
```



## error

Go 语言通过内置的错误接口提供了非常简单的错误处理机制。

error类型是一个接口类型，这是它的定义：

```
type error interface {
    Error() string
}
```

我们可以在编码中通过实现 error 接口类型来生成错误信息。

函数通常在最后的返回值中返回错误信息。使用errors.New 可返回一个错误信息：

```go
func Sqrt(f float64) (float64, error) {
    if f < 0 {
        return 0, errors.New("math: square root of negative number")
    }
    // 实现
}
```

如果不出现错误, `errors.New()`返回空字符串



在下面的例子中，我们在调用Sqrt的时候传递的一个负数，然后就得到了non-nil的error对象，将此对象与nil比较，结果为true，所以fmt.Println(fmt包在处理error时会调用Error方法)被调用，以输出错误，请看下面调用的示例代码：

```
result, err:= Sqrt(-1)

if err != nil {
   fmt.Println(err)
}
```

 

# reflect

## Typeof

Typeof返回接口中保存的值得类型，Typeof(nil)会返回nil

实例

```
package main

import (
	"fmt"
	"reflect"
)

func main() {
	var booknum float32 = 6
	var isbook bool = true
	bookauthor := "www.w3cschool.cn"
	bookdetail := make(map[string]string)
	bookdetail["Go语言教程"]="www.w3cschool.cn"
	fmt.Println(reflect.TypeOf(booknum))
	fmt.Println(reflect.TypeOf(isbook))
	fmt.Println(reflect.TypeOf(bookauthor))
	fmt.Println(reflect.TypeOf(bookdetail))
}
```

以上代码执行结果如下

```
float32
bool
string
map[string]string
```

## ValueOf



ValueOf返回一个初始化为interface接口保管的具体值得Value，ValueOf(nil)返回Value零值

## 通过反射设置值

```
package main

import (
	"fmt"
	"reflect"
)

func reflectsetvalue1(x interface{}){
	value:=reflect.ValueOf(x)
	if value.Kind() == reflect.String{
		value.SetString("欢迎来到W3Cschool")
	}
} 
func reflectsetvalue2(x interface{}){
	value:=reflect.ValueOf(x)
    // 反射中使用Elem()方法获取指针所指向的值
	if value.Elem().Kind() == reflect.String{
		value.Elem().SetString("欢迎来到W3Cschool")
	}
} 

func main() {
	address := "www.w3cschool.cn"
	// reflectsetvalue1(address) 
    // 反射修改值必须通过传递变量地址来修改。若函数传递的参数是值拷贝，则会发生下述错误。
    // panic: reflect: reflect.Value.SetString using unaddressable value
	reflectsetvalue2(&address)
	fmt.Println(address)
}
```

# 
