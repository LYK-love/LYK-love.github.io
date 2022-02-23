---
title: Java Container
tags: java
---



# 基本概念

![查看源图像](https://th.bing.com/th/id/OIP.667m4vNLjqp5LGdpEC2oGQHaHP?pid=ImgDet&rs=1)

java容器类类库的用途是保存对象，并将其划分为两个不同的概念：

1. Collection:  List,  Set, Queue
2. Map： 一组键值对对象
   * HashMap： 无序
   * TreeMap: 按照比较结果的升序来保存key
   * LinkedHashMap： 按照插入的顺序来保存key



## 添加元素

```java
class Snow{}
class Powder extends Snow{}
class Light extends Powder{}
class Heavy extends Powder{}
class Crusty  extends Snow{}
class Slush extends Snow{}
```



* `Arrays.asList()`: 接收一个数组或是用逗号分隔的元素列表（使用可变参数），并将其转换成一个`List`对象 

  ```java
  public static <T> java.util.List<T> asList(T... arg0);
  ```

  ```java
  Integer[] ia = { 1,2,3,4,5,6,7,8 };
  List<Integer> list1 = new ArrayList<>(Arrays.asList(ia));
  List<Integer> list2 = Arrays.asList(ia);
  ```

  产生的List用底层数组作为物理实现，任意对List的改变会反映到底层数组(因此用add, delete来增删元素会导致`Unsupported Operation`， 因为数组不能改变大小)

  * `list1`创建了一个引用`ia`元素的ArrayList, 对`list1`的改变不会改变`ia`
  * `list2`直接引用了`Arrays.asList(ia)`，这意味着`list2`将`ia`作为底层实现，对`list2`的任何改变都会改变`ia`

  

* `Collecions.addAll()`:接收一个`Collection`对象，以及一个数组或是一个用逗号分隔的列表，将元素添加到` Collection`中

  ```java
  public static <T> boolean addAll(java.util.Collection<? super T> arg0, T... arg1) {
      return false;}
  ```

  

* `Collection.addAll()`成员方法: 接收另一个`Collection`对象作为参数



---

*  无法将子类型元素的容器转型为父亲类型元素的容器：

  ```java
   List<Snow> snow2 = Arrays.asList( new Light(), new Heavy());
  ```

  会报错， 因为无法将`List<Powder>` 转型为`List<Snow>`, 尽管`Powder`是`Snow`的子类

* 可以用`Collecions.addAll()`，它从第一个参数知道了容器类型是什么：

  ```java
  List<Snow> snow3 = new ArrayList<Snow>();
  
  Collections.addAll( snow3, new Light(), new Heavy() );
  ```

* 也可以用`Arrays.<Class>asList`， 显式类型参数说明：

  ```java
  List<Snow> snow4 = Arrays.<Snow>asList( new Light(), new Heavy() );
  ```

  

## 对象打印

Object的默认toString（）：打印类名，后面跟对象的散列码的十六进制表示（由`hashCode（）`产生）

```
Light@42a57993,
```



## 容器打印

容器都重载了`toString()`方法：

* Collection: 方括号括住， 对每个元素采用toString（），逗号分隔。
* Map： 花括号括住，键与值用等号连接，逗号分隔

```shell
[Light@42a57993, Heavy@75b84c92] //Collection
{rat=Fuzzy, cat=Rags}
```

## 转换为Array

* `Collection.toArray()`成员方法：

  * 无参版本返回`Object[]`:

    ```java
    public abstract java.lang.Object[] toArray();
    ```

  * 接受一个参数，返回参数类型的数组（假设能通过类型检查）：

    ```java
    public abstract <T> T[] toArray(T[] arg0);
    ```

    

# Collection

## List

确定一个元素是否属于某个List, 发现某个元素的索引，从List中移除元素，都会用`equals()`， 这意味着List的行为随`equals()`的行为而变化



我们考察`List<E>`接口，可以看到几个主要的接口方法：

- 在末尾添加一个元素：`boolean add(E e)`
- 在指定索引添加一个元素：`boolean add(int index, E e)`
- 删除指定索引的元素：`E remove(int index)`
- 删除某个元素：`boolean remove(Object e)`
- 删除参数List中的所有元素：`boolean removeAll(java.util.Collection<?> arg0);`
- 获取指定索引的元素：`E get(int index)`
- 获取链表大小（包含元素的个数）：`int size()`
- 两个集合的交集：`boolean retainAll(java.util.Collection<?> arg0);`
- 截取列表（对子列表的所有修改都会反映到父列表）：`java.util.List<E> subList(int arg0, int arg1);`

### 创建List

除了使用`ArrayList`和`LinkedList`，我们还可以通过`List`接口提供的`of()`方法，根据给定元素快速创建`List`：

```java
List<Integer> list = List.of(1, 2, 5);
```

但是`List.of()`方法不接受`null`值，如果传入`null`，会抛出`NullPointerException`异常。

### LinkedList

一般用来实现Queue

## Queue

在Java的标准库中，队列接口`Queue`定义了以下几个方法：

- `int size()`：获取队列长度；
- `boolean add(E)`/`boolean offer(E)`：添加元素到队尾；
- `E remove()`/`E poll()`：获取队首元素并从队列中删除；
- `E element()`/`E peek()`：获取队首元素但并不从队列中删除。

对于具体的实现类，有的Queue有最大队列长度限制，有的Queue没有。注意到添加、删除和获取队列元素总是有两个方法，这是因为在添加或获取元素失败时，这两个方法的行为是不同的。我们用一个表格总结如下：

|                    | throw Exception | 返回false或null    |
| :----------------- | :-------------- | :----------------- |
| 添加元素到队尾     | add(E e)        | boolean offer(E e) |
| 取队首元素并删除   | E remove()      | E poll()           |
| 取队首元素但不删除 | E element()     | E peek()           |



`LinkedList`既实现了`List`接口，又实现了`Queue`接口，但是，在使用的时候，如果我们把它当作List，就获取List的引用，如果我们把它当作Queue，就获取Queue的引用：

```
// 这是一个List:
List<String> list = new LinkedList<>();
// 这是一个Queue:
Queue<String> queue = new LinkedList<>();
```

## Set

`Set`用于存储不重复的元素集合，它主要提供以下几个方法：

- 将元素添加进`Set<E>`：`boolean add(E e)`
- 将元素从`Set<E>`删除：`boolean remove(Object e)`
- 判断是否包含元素：`boolean contains(Object e)`



放入`Set`的元素和`Map`的key类似，都要正确实现`equals()`和`hashCode()`方法，否则该元素无法正确地放入`Set`。

最常用的`Set`实现类是`HashSet`，实际上，`HashSet`仅仅是对`HashMap`的一个简单封装，它的核心代码如下：

```java
public class HashSet<E> implements Set<E> {
    // 持有一个HashMap:
    private HashMap<E, Object> map = new HashMap<>();

    // 放入HashMap的value:
    private static final Object PRESENT = new Object();

    public boolean add(E e) {
        return map.put(e, PRESENT) == null;
    }

    public boolean contains(Object o) {
        return map.containsKey(o);
    }

    public boolean remove(Object o) {
        return map.remove(o) == PRESENT;
    }
}
```

`Set`接口并不保证有序，而`SortedSet`接口则保证元素是有序的：

- `HashSet`是无序的，因为它实现了`Set`接口，并没有实现`SortedSet`接口；
- `TreeSet`是有序的，因为它实现了`SortedSet`接口。
  * `TreeSet`（和`TreeMap`）添加的元素必须正确实现`Comparable`接口，如果没有实现`Comparable`接口，那么创建`TreeSet`时必须传入一个`Comparator`对象。

用一张图表示：

```ascii
       ┌───┐
       │Set│
       └───┘
         ▲
    ┌────┴─────┐
    │          │
┌───────┐ ┌─────────┐
│HashSet│ │SortedSet│
└───────┘ └─────────┘
               ▲
               │
          ┌─────────┐
          │ TreeSet │
          └─────────┘
```





# Map

`Map<K, V>`是一种键-值映射表，当我们调用`put(K key, V value)`方法时，就把`key`和`value`做了映射并放入`Map`。当我们调用`V get(K key)`时，就可以通过`key`获取到对应的`value`。如果`key`不存在，则返回`null`。和`List`类似，`Map`也是一个接口，最常用的实现类是`HashMap`。



Map中放入相同的key，会把原有的key-value对应的value给替换掉。

```java
public interface Map<K,V>
```



```java
clear(): void
compute(K, BiFunction<? super K, ? super V, ? extends V>): V
computeIfAbsent(K, Function<? super K, ? extends V>): V
computeIfPresent(K, BiFunction<? super K, ? super V, ? extends V>): V
containsKey(Object): boolean
containsValue(Object): boolean
entrySet(): Set<Entry<K, V>>
equals(Object): boolean
forEach(BiConsumer<? super K, ? super V>): void
get(Object): V
getOrDefault(Object, V): V
hashCode(): int
isEmpty(): boolean
keySet(): Set<K>
merge(K, V, BiFunction<? super V, ? super V, ? extends V>): V
put(K, V): V
putAll(Map<? extends K, ? extends V>): void
putIfAbsent(K, V): V
remove(Object): V
remove(Object, Object): boolean
replace(K, V): V
replace(K, V, V): boolean
replaceAll(BiFunction<? super K, ? super V, ? extends V>): void
size(): int
values(): Collection<V>
```



## Equals && hashcode

容器内部通过`equals`（ 基本类型使用`==` ）来比较元素

* Map比较`key`





我们经常使用`String`作为`key`，因为`String`已经正确覆写了`equals()`方法。但如果我们放入的`key`是一个自己写的类，就必须保证正确覆写了`equals()`方法。

我们再思考一下`HashMap`为什么能通过`key`直接计算出`value`存储的索引。相同的`key`对象（使用`equals()`判断时返回`true`）必须要计算出相同的索引，否则，相同的`key`每次取出的`value`就不一定对。

通过`key`计算索引的方式就是调用`key`对象的`hashCode()`方法，它返回一个`int`整数。`HashMap`正是通过这个方法直接定位`key`对应的`value`的索引，继而直接返回`value`。

因此，正确使用`Map`必须保证：

1. 作为`key`的对象必须正确覆写`equals()`方法，相等的两个`key`实例调用`equals()`必须返回`true`；
2. 作为`key`的对象还必须正确覆写`hashCode()`方法，且`hashCode()`方法要严格遵循以下规范：

- 如果两个对象相等，则两个对象的`hashCode()`必须相等；
- 如果两个对象不相等，则两个对象的`hashCode()`尽量不要相等。

即对应两个实例`a`和`b`：

- 如果`a`和`b`相等，那么`a.equals(b)`一定为`true`，则`a.hashCode()`必须等于`b.hashCode()`；
- 如果`a`和`b`不相等，那么`a.equals(b)`一定为`false`，则`a.hashCode()`和`b.hashCode()`尽量不要相等。

上述第一条规范是正确性，必须保证实现，否则`HashMap`不能正常工作。

而第二条如果尽量满足，则可以保证查询效率，因为不同的对象，如果返回相同的`hashCode()`，会造成`Map`内部存储冲突，使存取的效率下降。



编写`equals()`和`hashCode()`遵循的原则是：

`equals()`用到的用于比较的每一个字段，都必须在`hashCode()`中用于计算；`equals()`中没有使用到的字段，绝不可放在`hashCode()`中计算。

实现`hashCode()`方法可以通过`Objects.hashCode()`辅助方法实现。



## 遍历Map

对`Map`来说，要遍历`key`可以使用`for each`循环遍历`Map`实例的`keySet()`方法返回的`Set`集合，它包含不重复的`key`的集合：

```java
public class Main {
    public static void main(String[] args) {
        Map<String, Integer> map = new HashMap<>();
        map.put("apple", 123);
        map.put("pear", 456);
        map.put("banana", 789);
        for (String key : map.keySet()) {
            Integer value = map.get(key);
            System.out.println(key + " = " + value);
        }
    }
}

```



可以通过`for each`遍历`keySet()`，也可以通过`for each`遍历`entrySet()`，直接获取`key-value`

```
public class Main {
    public static void main(String[] args) {
        Map<String, Integer> map = new HashMap<>();
        map.put("apple", 123);
        map.put("pear", 456);
        map.put("banana", 789);
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            System.out.println(key + " = " + value);
        }
    }
}

```

## TreeMap

`TreeSet`（和`TreeMap`）添加的元素必须正确实现`Comparable`接口，如果没有实现`Comparable`接口，那么创建`TreeSet`(`TreeMap`)时必须传入一个`Comparator`对象。



`TreeMap`在比较两个Key是否相等时，依赖Key的`compareTo()`方法或者`Comparator.compare()`方法

```java
Map<Student, Integer> map = new TreeMap<>(new Comparator<Student>() {
    public int compare(Student p1, Student p2) {
        return p1.score > p2.score ? -1 : 1;
            }
}

```



# 迭代器

## Iterator

```java
public abstract interface Iterator<E> {
  
  public abstract boolean hasNext();
  
  public abstract  E next();
  
  public void remove() {
  }
  
  public  void forEachRemaining(java.util.function.Consumer<? super E> arg0) {
  }
}
```

`Iterator`接口用于遍历容器中的元素。 注意`iterator()`是由`Iterable`接口实现的。 `Iterator`只是提供了迭代器的各种操作

如果我们自己编写了一个集合类，想要使用`for each`循环，只需满足以下条件：

- 集合类实现`Iterable`接口，该接口要求返回一个`Iterator`对象；
- 用`Iterator`对象迭代集合内部数据。

这里的关键在于，集合类通过调用`iterator()`方法，返回一个`Iterator`对象，这个对象必须自己知道如何遍历该集合。



Iterator 只能单向移动，只能用来：

1. `iterator()`: 返回一个Iterator, Iterator指向容器的第一个元素
2. `next()`：容器的下一个元素
3. `hasNext()`: 容器中是否还有元素
4. `remove()`: 可选方法，删除迭代器新进返回的元素

### ListIterator

```java
public abstract interface ListIterator<E> extends java.util.Iterator
```

只能用于List, 可以双向移动

* `listIterator()`: 返回一个指向List第一个元素的ListIterator
  * ``listIterator(int n)`: 返回一个指向List第n个元素的ListIterator`
* `set( E element )`:  将其所指的元素替换

## Iterable

java引入了`Iterable`接口，包含了`iterator()`   方法

```java
public abstract interface Iterable<T> 
```

  

`Iterable`接口， 具有` `Collection`接口继承了`Iteratable`接口（）`方法，  `Collection`接口继承了`Iteratable`接口：

```java
public abstract interface Collection<E> extends java.lang.Iterable
```

因此如果要实现`Collection`, 就必须实现`iterator()`



java提供了Collection的默认抽象实现类`AbstractCollection`， 通过继承它，我们自定义一个Collection只许亚萍override少部分代码

```java
public abstract class AbstractCollection<E> implements java.util.Collection
```



 当然，如果我们自定义的类继承了其他类，就不能再继承`AbstractCollection`了，这时候可以考虑实现`Iterable`

### forEach

forEach使用`Iterable` 接口在序列中移动，

因此下面的代码：

```
for( E element: Arr )
```

实际上被翻译为：

```java
for( E element: Arr.iterator() ) 
```



这也意味着我们可以override`iterator()`    来提供多种迭代器策略：

```java
public class ReversibleArrayList<T> extends ArrayList<T> {

    public ReversibleArrayList(Collection<T> c)
    {
        super(c);
    }
   
    public Iterable<T> reversed()
    {
        return new Iterable<T>() {
            public Iterator<T> iterator(){

                return new Iterator<T>() {                
                    int current = size() -1;

                    public boolean hasNext() { return current > -1; }

                    public T next() { return get(current --) ;}

                    public void remove()
                    {
                    throw new UnsupportedOperationException();
                    }
                    
                };

            }
            
        };
    }

    public static void main(String[] args)
    {
        ReversibleArrayList<String> ral = new ReversibleArrayList<String>( Arrays.asList("To be or not to be".split(" ")) );
        for(String s: ral)
        {
            System.out.print(s + " ");
        }

        for( String s: ral.reversed() )
        {
            System.out.print( s + " " );
        }
    }
}
```



# Collections

`Collections`是JDK提供的工具类，同样位于`java.util`包中。它提供了一系列静态方法，能更方便地操作各种集合。

```java
List list = new ArrayList(); …
Collections.sort(list);//顺序排序
Collections.shuffle(list);//乱序
Collections.reverse(list);//逆序
Collections.binarySearch(list, obj);//二分查找返回obj在list中的位置

Collections.addAll(Collection<? super T> c, T... elements) { ... } //给一个Collection添加若干元素
```



## 创建空集合

`Collections`提供了一系列方法来创建空集合：

- 创建空List：`List<T> emptyList()`
- 创建空Map：`Map<K, V> emptyMap()`
- 创建空Set：`Set<T> emptySet()`

要注意到返回的空集合是**不可变**集合，无法向其中添加或删除元素。

此外，也可以用各个集合接口提供的`of(T...)`方法创建空集合。例如，以下创建空`List`的两个方法是等价的：

```java
List<String> list1 = List.of();
List<String> list2 = Collections.emptyList();
```

## 创建单元素集合

`Collections`提供了一系列方法来创建一个单元素集合：

- 创建一个元素的List：`List<T> singletonList(T o)`
- 创建一个元素的Map：`Map<K, V> singletonMap(K key, V value)`
- 创建一个元素的Set：`Set<T> singleton(T o)`

要注意到返回的单元素集合也是不可变集合，无法向其中添加或删除元素。

此外，也可以用各个集合接口提供的`of(T...)`方法创建单元素集合。例如，以下创建单元素`List`的两个方法是等价的：

```java
List<String> list1 = List.of("apple");
List<String> list2 = Collections.singletonList("apple");
```

实际上，使用`List.of(T...)`更方便，因为它既可以创建空集合，也可以创建单元素集合，还可以创建任意个元素的集合：

```java
List<String> list1 = List.of(); // empty list
List<String> list2 = List.of("apple"); // 1 element
List<String> list3 = List.of("apple", "pear"); // 2 elements
List<String> list4 = List.of("apple", "pear", "orange"); // 3 elements
```



# Tips

由于Java的集合设计非常久远，中间经历过大规模改进，我们要注意到有一小部分集合类是遗留类，不应该继续使用：

- `Hashtable`：一种线程安全的`Map`实现；
- `Vector`：一种线程安全的`List`实现；
- `Stack`：基于`Vector`实现的`LIFO`的栈。

还有一小部分接口是遗留接口，也不应该继续使用：

- `Enumeration<E>`：已被`Iterator<E>`取代。
