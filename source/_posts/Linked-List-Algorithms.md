---
title: Linked List Algorithms
tags: Algorithm design and analysis
categories: Algorithm
mathjax: true
date: 2023-08-13 03:25:15
---

Commen Linked List Algorithms on Leetcode.

<!--more-->

# Reverse the Linkedlist

[206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)

[92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)

![Reverse the Linkedlist](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Algorithm/Linkedlist%20Algorithms/Reverse%20the%20Linkedlist.png)



输入一个单链表头结点, 将该链表反转, 返回新的头结点:

```java
    private static ListNode reverse_linked_list(ListNode head)
    {
        if( head == null || head.next == null )
            return head;

        ListNode last = reverse_linked_list(head.next);
        head.next.next = head;
        head.next = null;
        return last;
    }
```

以上图为例:

1. 如图(1), head为`1`, 链表为`1->2->3->4`.

2. 如图(2), 递归思考, 将以`2`为head的子链表`2->3->4`进行反转. 根据函数定义, 我们会得到反转后子链表`4->3->2`的头节点`4`, 记为`last`. 此时`head.next`依然为`2`, 即`1->2`. 

   ```java
   ListNode last = reverse_linked_list(head.next);
   ```

   而由于`2`已经是翻转后子链表的最后一个节点, 因此`2->null`.

   ```txt
   4(last)->3->2->null
   1(head)-2->null
   ```

3. 接着把(1)变成最后一个节点, 即`4->3->2->1`.

   ```java
   head.next.next = head;
   ```

   虽然`2`的next变为`1`, 但`1`的next依然为`2`, 造成死循环:

   ```txt
   4(last)->3->2->1(->2->1->2->1->2->1....无限循环)
   ```

4. 由于`1`是翻转后链表的最后一个节点, 所以令`1`的next为`null`, 即`4(last)->3->2->1(head)->null`如图(4).

   ```java
   head.next = null;
   ```

5. 返回翻转后的整个链表的头节点, 它就是翻转后的子链表的头节点`last`.

   ```java
   return last;
   ```

   









