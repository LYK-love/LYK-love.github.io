---
title: L5 HeapSort
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2021-07-21 15:33:29
---


Outline:

* **Heap**
* **HeapSort**

* **FixHeap**
* **ConstructHeap**

* **Accelerated HeapSort**

<!--more-->

# `Heap`

* 定义：一棵二叉树满足
  * 堆结构特性： 即 是一课完全二叉树
  * 堆偏序特性： 堆节点中存储的元素满足父结点的值大于所有子节点的值（左右子节点的值之间的大小关系无要求）
* 堆的最大元素必然位于堆顶。



# `FixHeap`

* 堆顶元素被取走后，整个堆的结构特性和偏序特性均被破坏，但堆的这两个特性是正交的，我们可以先修复结构特性，再修复偏序特性。在修复时，我们面临的不是一个被任意破坏的堆，而只是一个被“**局部**”破坏的堆，即： 堆顶元素被取走，但堆的左右子树仍然是一个合法的堆。
* 对于堆结构特性的修复，只需<u>取最底层最右边的元素，放在堆顶位置</u>
* 修复完结构特性后，我们面对的是一个满足<u>堆结构</u>的二叉树，其左右子树均是一个合法的堆, 只是其根节点的值与其两个（边界情况下可能只有一个）子节点的值不满足偏序特性的要求，为此，需要：
  1. 将父结点的值与子节点的值比较，假设左子节点最大，则将父结点与左子点交换位置。 此时，父节点和右子树均满足了<u>堆偏序</u>
  2. 左子树由于引入了新的根节点,可能不满足偏序特性. 为此,需要对左子树递归地进行上述修复过程
* 由于堆的修复只会在高度严格递减的一系列子树上进行, 所以修复过程一定会终止,且次数不会超过树的高度. 由于堆的高度为$O(logn)$, 每次修复的比较次数为`O(1)`(最多为2次),所以堆修复的代价为$O(logn)$

# `ConstructHeap`

* 假设有一颗满足<u>堆结构特性</u>的二叉树,但树中每个节点所存储的值的大小关系完全是杂乱的,我们需要使书中所有父子节点间均满足堆的偏序特性,基于堆修复操作,递归实现:
  1. 从根部开始堆的构建,因为堆的左右子树必然还是堆. 此时如果堆的左右子树均是一个合法的堆,那么最多只是根节点有局部破坏,用`FixHeap`处理
  2. 对堆结构的左右子树,只需递归地将它们构建成合法的堆



* 建堆的代价即堆修复代价的总和： $ W(n) = O(n)$



# 堆的实现

* 堆中的父子节点下标满足如下关系:
  *  $PARENT(i) = \lfloor \frac i  2 \rfloor$
  * $LEFT(i) = 2i$
  * $RIGHT(i) = 2i + 1$
* Proof: 略

# `HeapSort`

* 复杂度 $W(n) = O(nlogn)$​​ ; $A(n) = O(nlogn)$​

* 可以用堆实现`PRIORITY QUEUE`



# `Accelerated HeapSort`

* 采用折半查找, 子元素不和父元素比较,只和兄弟元素比较,比较完后与父元素交换,即父元素直接下沉. 元素每次下沉到剩余高度一半的时候,和PQRENT比较一次(由于只有一个父元素,比较次数为1),若大于父元素,则上浮, 否则递归执行上述操作( 继续下沉,比较... )
* 这样做基于的假设是: 对于一个很深的堆,`FixHeap`时,替换而来的根元素极有可能比两个子元素都要小,因此不用将根元素带入比较,以减少一次比较次数.



## Extension

* 堆可以扩展为 n-way ,这样的堆会变胖变矮
* 一般来说, 如果堆的上浮操作比较多,那么堆越胖越好.
  * 上浮只需一次操作,由于堆变矮了,还能减少上浮次数
* 若堆的下沉操作比较多,那么堆越瘦越好
  * 堆越瘦,每次比较的操作数越少,极限情况是二叉树,三个元素只需比较两次