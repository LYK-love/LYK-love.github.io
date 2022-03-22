---
title: Sort
categories: Algorithm
date: 2021-06-27 11:33:08
---

Outline

* `MergeSort`
* `QuickSort`
* `HeapSort( and Heap )`

<!--more-->

## 快速排序

```c++

template<typename T, int N>
int partition(T(&a)[N], int lo, int hi)
{
	int i = lo, j = hi + 1;
	T v = a[lo];
	while (true)
	{
		while (a[++i] < v)	if (i == hi)	break;
		while (a[--j] > v)	if (j == lo)	break;
		if (i >= j) break;
		exch(a, i, j);
	}
	exch(a, lo, j);
	return j;




}


template<typename T,int N>
void exch(T (&a)[N], int i , int j)
{
	T tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

template<typename T, int N>
void sort(T(&a)[N])
{
	sort(a, 0, N - 1);
}

template<typename T, int N>
void sort(T ( &a )[N], int lo, int hi)
{
	if (hi <= lo) return;
	int j = partition(a, lo, hi);
	sort(a, lo, j - 1);
	sort(a, j + 1, hi);
}


```

