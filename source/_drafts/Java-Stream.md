---
title: Java Stream
tags:
---



# Operation

从Array中删除重复项:

从数组元素构造一个流，并使用 `distinct()` 方法。然后调用 `toArray()` 方法将流元素累积到一个新数组中。

该方案保留了元素的相对顺序

```java
public static int[] removeDuplicates(int[] arr) {
  return Arrays.stream(arr).distinct().toArray();
}
```





We can use Java 8 Stream to convert an array to collections. Meanwhile we can change the type of  all elements. This is often used in boxing primitive type value.



primitive type array to  array:

We can use Java 8 Stream to convert a primitive integer array to Integer array:

1. [Convert the specified primitive array to a sequential Stream](https://www.techiedelight.com/convert-array-stream-java-8/) using `Arrays.stream()`.
2. Box each element of the stream to an `Integer` using `IntStream.boxed()`.
3. Return an Integer array containing elements of this stream using `Stream.toArray()`.

```java
int[] primitiveArray = { 1, 2, 3, 4, 5 };
Integer[] boxedArray = Arrays.stream(primitiveArray) // IntStream
                                .boxed()                // Stream<Integer>
                                .toArray(Integer[]::new);
```



Convert a primitive integer array to Integer set:

```
Set<Integer> nums_set = Arrays.stream(nums).boxed().collect(Collectors.toSet());
```
