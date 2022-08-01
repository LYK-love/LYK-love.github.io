---
title: String Algorithms
categories: Algorithm
date: 2022-04-10 17:49:04
tags:
---




Outline:

* String Sort
* Tries
* Substring Search
* Regex
* Data Compress

目前只更新到String Sort

<!--more-->

# String Sort

因为字符串天然就有序（ascii， unicode序），因此可以用桶排序的方法，进行key indexed counting, 这样排序不需要比较，也就能达到线性时间
* 这里我用的序都是ascii序，当然你也可以自定义一个符号表，然后用符号表里的序



```c++
class StringSortStrategy
{
public:
    void LSD(  vector<string> &strs);
    void MSD( vector<string> &strs);
    void Quick3string( vector<string> &strs);

private:
    void LSD(  vector<string> &strs , int W);
    void MSD( vector<string> &strs, vector<string> &aux, vector<int> &count, const int lo, const int hi, const int d );
    void Quick3string( vector<string> & strs, const int lo, const int hi, const int d );


};
```

```c++
void StringSortStrategy::LSD(  vector<string> &strs)
{
    const int W = strs[0].length();
    LSD( strs, W );
}

void StringSortStrategy::MSD( vector<string> &strs)
{
    const int R = 256;
    vector<int> count(R+2);
    int N = strs.size();
    vector<string> aux(N);

    MSD(strs, aux, count, 0, N - 1, 0);
}


void StringSortStrategy::Quick3string(vector<string> &strs)
{
    int N = strs.size();
    Quick3string( strs, 0, N-1, 0 );
}
```

## 工具函数

```c++
char CharAt(const string s, int i) {
	if (i < s.length())
		return s[i];
	else
		return -1;
}


void exch(string &s1, string &s2) {
	string tmp = s1;
	s1 = s2;
	s2 = tmp;
}

bool Less(string s1, string s2, int d) {
	return s1.substr(d).compare(s2.substr(d)) < 0;
}
 


void InsertionSort(vector<string> &a, int lo, int hi, int d) {
	for (int i = lo; i <= hi; i++)
		for (int j = i; j > lo && Less(a[j], a[j - 1], d); j--)
			exch(a[j], a[j - 1]);
}
```



## LSD

LSD算法对等长的字符串数组从右往左按key进行排序，确保稳定性。 由于是key indexed counting, 不需要元素之间两两比较，因此可以达到线性复杂度

思路是把所有元素按key放在对应的桶里面，桶与桶之间按桶内的元素数拉开距离，然后对于每个桶，对其每个元素进行位置的分配。最后将结果写回到原来的strs数组

例如， 当前要将所有字符串的第0个字符（这里都是从右往左的，也就是倒数第0个字符）作为key进行排序，假设key为A的字符串有3个， key为B的字符串有5个，key为C的字符串有8个

1. 可以装三个桶，key为A的桶有三个元素，key为B的桶有5个元素，key为C的桶有8个元素；
2. 然后桶之间拉开距离，A桶和B桶之间距离为5， B桶和C桶间的距离为8；
3. 然后给每个桶内的元素分配坐标，对于B桶中五个元素，就把它们按在原strs中的顺序（**这一步确保了算法的稳定性**）分配到A，B桶之间的空间中，其他桶亦如此，这样所有字符串就排好了序；
4. 接着把上述结果写回到原strs中；
5. 再对下一个key位置进行迭代（这里就是第1个字符）

* 注意`count[0]`必须存0值，表示下标分配时，最小桶的起始下标从0开始分配。比如0桶存放在`count[1]`,0桶元素的下标分配就在`count[0]`和`count[1]`之间的空间中





```c++
/**
* @param strs: 要排序的字符串列表，LSD要求所有字符串都是等长的（当然不等长的话修改算法也可以排序，但是一般我们     		直接用MSD）
* @param W : 要排序的key的范围，比如W=3，就代表对从右往左的三位进行排序
*/
void StringSortStrategy::LSD(vector<string> &strs , int W)
{
    const int R = ALPHABET_SIZE;
    const int N = strs.size();

    int len = strs[0].length();

    vector<string> aux(N);

    for( int w = len - 1; w >= len - W; w--  )
    {
        int count[ R+1 ] = {};


        for( int i = 0 ; i < N; i++ ) // count frequencies, 装满桶
        {
            count[CharAt(strs[i], w) + 1]++;
        }

        for( int i = 1; i < R+1; i++ )//桶之间拉开距离
        {
            count[i] += count[i-1];
        }

        for( int i = 0; i < N; i++ )//桶内元素在空间中进行分配
        {
            int r = CharAt(strs[i],w);
            aux[  count[ r ]++ ] = strs[i];
        }

        for( int i = 0; i < N; i++ )//写回
        {
            strs[ i ] = aux[i];
        }

    }
}
```





## MSD

MSD同样是key indexed count的桶排序，但是是从左向右扫，并且能允许不同长度的字符串

MSD可以看作是从左往右的LSD，并且将空key（因为字符串长度可能不够了，那一位的key可能为空）放在一个特别的空桶上，其余性质不变。 因此MSD也是稳定, 线性时间的

由于要处理空key，我们将空key的key定义为-1 (见`CharAt()`函数 )， 本来按LSD算法，桶的大小要存放在下一个count中，比如key为A的元素的个数（即A桶的大小）存放在`count[B]`。 由于count[0]必须是0值，所以只能把-1桶放在`count[1]`, 0桶放在`count[2]`... 相当于所有count后延一位.这样, -1取代0成为符号表最初的元素，-1桶元素的下标也就从`count[0]`和`count[1]`的空间中分配。


总体思路和LSD一模一样，只不过是从左到右的，并且count要后延一位

* 注意到MSD对短字符串的处理性能不佳，因此对于短字符串( `hi - lo <= M `)就直接用插入排序了。 这一步还顺便处理了递归的终止条件，即`hi - lo <= 0 `的情况



```c++
void StringSortStrategy::MSD( vector<string> &strs, vector<string> &aux, vector<int> &count, const int lo, const int hi, const int d )
{
	const int M = 3, R = 256;

	if (hi <= lo + M) {
		InsertionSort(strs, lo, hi, d);
		return;
	}


    for( int i = 0; i <  R + 2; i++ )
    {
        count[i] = 0;
    }



    for( int i = lo; i <= hi; i++ )
    {
        count[ CharAt(strs[i],d) + 2 ]++; 

    }

    for( int i = 1; i < R+2; i++ )
    {
        count[i] += count[i-1];
    }

    for( int i = lo; i <= hi; i++ )
    {
        aux[ count[ CharAt( strs[i],d ) + 1 ]++ ] = strs[i];
    }

    for( int i = lo; i <= hi; i++ )
    {
        strs[i] = aux[i - lo];
    }

    for( int i = 0; i < R; i++ )
    {
        MSD( strs, aux, count, lo + count[i], lo + count[i+1] - 1, d+1 );
    }

}

```



## 三向排序

三向排序混合了桶排序（MSD）和快排， 由于引入了快排，所以是不稳定排序，但依然是线性时间

和MSD的区别是，MSD将每个key作为一个桶，而三向排序通过快排只引入三个桶 ----

*  key小于指定key的桶( 放到lt左边)
* key等于指定key的桶（lt ～ ht ）
* 和key大于指定key的桶（ht右边）

对于key种类很少的情况，可以用三向排序，这样产生的桶更少，子数组就更少

和传统快排的区别在于，快排要左右分别开始扫，扫到符合要求的元素就分别停下，这样做是为了方便两边对换；但是对于三向排序，不需要两边对换（只需要把元素换到左/右界之外），所以也没必要从两边开始扫。一遍就够了

```c++
void StringSortStrategy::Quick3string(vector<string> &strs, const int lo, const int hi, const int d)
{
    if( hi <= lo )
        return;

    int v = CharAt(strs[lo],d); //pivot

    int lt = lo, gt = hi; //桶的界限，小桶会放到lt左边，大桶放到gt右边，与指定key相等的桶就放到lt，gt之间
    int i = lo+1;
    while( i <= gt ) //循环可保证，lt之前的值永远小于v， gt之后的值永远大于v
    {
        int t = CharAt(strs[i],d);
        if( t < v )
            exch(strs[i++], strs[lt++]);
        else if( t > v )
                exch( strs[i], strs[gt--] ); //不能保证换过来的gt之后的值就是v了，因此不能i++，需要再次进循环
        else
            i++;
    }




    Quick3string(strs, lo, lt-1, d);
    if( v > 0 )
        Quick3string(strs, lt, gt , d + 1 );
    Quick3string( strs, gt + 1, hi, d );
}
```
