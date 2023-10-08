---
title: Tries
tags:
  - Algorithm
  - LeetCode
categories:
  - Computer Science
date: 2023-10-01 21:16:45
---


A [**trie**](https://en.wikipedia.org/wiki/Trie) (pronounced as "try") or **prefix tree** is a tree data structure used *for storing and searching a specific key from a set, usually a string set.*

*Using Trie, search complexities can be brought to O(n)(n = key length).* 

[208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

<!--more-->

# Properties

Below are some important properties of the Trie data structure[^1]:

- There is one root node in each Trie.
- Each node of a Trie represents a string and **each edge represents a character**.
- Every node consists of hashmaps or **an array of pointers**, with each index representing a character and a flag to indicate if any string ends at the current node.
- Trie data structure can contain any number of characters including **alphabets**, **numbers**, and **special characters**. But for this article, we will discuss strings with characters a-z. Therefore, only 26 pointers need for every node, where the **0th** index represents **‘a’** and the **25th** index represents **‘z’** characters. 我们仅讨论key为`[a-z]`的Trie.
- **Each path from the root to any node represents a word or string.**

![Trie Data Structure](https://media.geeksforgeeks.org/wp-content/uploads/20220828232752/Triedatastructure1.png)

[^1]: https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/

# Data Structure

Every node of Trie consists of multiple branches. Each branch represents a possible character of keys:

![An array of pointers inside every Trie node](https://media.geeksforgeeks.org/wp-content/uploads/20220829160839/nodeintrie.png)



Mark the last node of every key as the end of the word node. A Trie node field **isEndOfWord** is used to distinguish the node as the end of the word node.

```java
public static class TrieNode{
        public TrieNode[] children;
        boolean isEndOfWord; // isEndOfWord is true if the node represents end of a word

        public TrieNode()
        {
            isEndOfWord = false;
            children = new TrieNode[ALPHABET_SIZE];
            for(TrieNode child: children)
                child = null;
        }
    }
```

 



# Operations

```txt
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
```



```java
public class Trie {

    // Alphabet size (# of symbols)
    static final int ALPHABET_SIZE = 26;

    public static class TrieNode{
			//...
    }

    private TrieNode root = new TrieNode();
    
    public void insert(String word) {
        __insert(word, root);
    }
    
    public boolean search(String word) {
        return __search(word, root);
    }
    
    public boolean startsWith(String prefix) {
        return __startsWith(prefix, root);
    }
}
```

## Insert

每一个输入的word都对应一条path.

![Insertion operation](https://media.geeksforgeeks.org/wp-content/uploads/20220902035030/ex1.png)

使用递归的思路进行插入:

```java
    // If not present, inserts key into trie.
    // If the key is prefix of trie node, just marks leaf node.
    public void insert(String word) {
        __insert(word, root);
    }

    private void __insert(String word, TrieNode currentRoot) {
        if(word.length() == 0)
            return;

        int idx = word.charAt(0) - 'a';

        if(currentRoot.children[idx] == null) currentRoot.children[idx] = new TrieNode();
        if(word.length() == 1)
            currentRoot.children[idx].isEndOfWord = true;// mark last node as leaf

        __insert(word.substring(1), currentRoot.children[idx]);
    }
```

## Search

![Searching in Trie](https://media.geeksforgeeks.org/wp-content/uploads/20220831073313/search1.png)

使用递归的思路进行查找. 如果当前字符匹配且该word只剩下这1个字符(` currentRoot.children[idx] != null && word.length() == 1 `), 那么如果当前node的`isEndOfWord==false`, 则返回false; 如果`isEndOfWord==true`, 则返回true.

```java
    public boolean search(String word) {
        return __search(word, root);
    }

    // Returns true if key presents in trie, else false
    private boolean __search(String word, TrieNode currentRoot) {
        if(word.length() == 0)//If input is a null string, we just return false.
            return false;

        int idx = word.charAt(0) - 'a';
        if(currentRoot.children[idx] == null) return false;
        else
        {
            if(word.length() == 1)
                return currentRoot.children[idx].isEndOfWord;
            else
                return __search(word.substring(1), currentRoot.children[idx]);
        }
    }
```

## StartsWith

和查找差不多, 但只要输入和某个路径的前面一部分匹配即可:

```txt
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
```



```java
    public boolean startsWith(String prefix) {
        return __startsWith(prefix, root);
    }

    private boolean __startsWith(String word, TrieNode currentRoot) {
        if(word.length() == 0)//If input is a null string, we just return false.
            return false;

        int idx = word.charAt(0) - 'a';
        if(currentRoot.children[idx] == null) return false;
        else
        {
            if(word.length() == 1)
                return true;
            else
                return __startsWith(word.substring(1), currentRoot.children[idx]);
        }
    }
```

