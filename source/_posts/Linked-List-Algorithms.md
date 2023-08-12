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

2. 递归思考, 将以`2`为head的`2->3->4`子链表进行反转. 根据函数定义, 我们得到的是反转后子链表`4->3->2`的头节点`4`, 记为`last`. 而此时`head.next`依然为`2`, 即`1->2`. 

   ```java
   ListNode last = reverse_linked_list(head.next);
   ```

   而由于`2`已经是翻转后子链表的最后一个节点, 因此`2->null`. 如图(2).

3. 接着把(1)变成最后一个节点, 即有`4->3->2->1`, 如图(3).

   ```java
   head.next.next = head;
   ```

   然而, 虽然`2`的next为`1`, 但`1`的next依然为`2`. 而`1`作为翻转后链表的最后一个节点, 它的next应当为`null`.

4. 令`1`的next为`null`, 如图(4).

   ```java
   head.next = null;
   ```

5. 返回翻转后的整个链表的头节点, 它就是翻转后的子链表的头节点`last`.

   ```java
   return last;
   ```

   







