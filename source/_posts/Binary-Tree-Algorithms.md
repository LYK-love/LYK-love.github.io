---
title: Binary Tree Algorithms
tags: 
- Algorithm
- LeetCode
categories: 
- Computer Science
mathjax: true
date: 2023-08-13 22:57:24
---


Common binary tree algorithms from leetcode.

<!--more-->

# Operations

API for Binary Tree Node.

```java
public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int val){this.val = val;}
    public TreeNode(int val, TreeNode left, TreeNode right){
        this.val = val;
        this.left = left;
        this.right = right;
    }
}
```



## Tree Traversal

Traversing(遍历) a tree means visiting and outputting the value of each node in a particular order.

There're typically 3 ways of tree traversal:

- Inorder(中序遍历) => Left, Root, Right.

- Preorder(前序遍历)  => Root, Left, Right.

- Post order(后序遍历)  => Left, Right, Root.

  

E.g.:

```markdown
    1
   / \
  2   3
 / \
4   5
```

- Preorder: 1, 2, 4, 5, 3
- Inorder: 4, 2, 5, 1, 3
- Postorder: 4, 5, 2, 3, 1

# Construct Binary Tree from Traversal

[105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

[106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)



可以通过 (中序,前序) 或 (中序,后序) 遍历来构造二叉树.  

```java
int[] preorder;//前序遍历结果, 由三部分组成: (root, root.left, root.right)
int[] inorder;//中序遍历结果, 由三部分组成: (root.left, root, root.right)
int[] postorder;//后序遍历结果, 由三部分组成: (root.left, root.right, root)
```



以 (中序,前序) 为例: 

```java
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        HashMap<Integer,Integer> map = new HashMap<>();
        for(int i=0; i < inorder.length; i++)
            map.put(inorder[i], i);//根据root节点的值找到在inorder[]中找到root节点的下标

        return buildBinaryTree(preorder,0,preorder.length,inorder,0,inorder.length, map);
    }

    /**
     * 前序遍历数组: preorder[preStart, ..., preEnd-1]
     * 中序遍历数组: inorder[inStart, ..., inEnd-1]
     * 根据给定的preorder和inorder, 构造二叉树, 返回其root.
     */
    private TreeNode buildBinaryTree(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd, HashMap<Integer,Integer> map)
    {
        if( preStart >= preEnd )
            return null;

        // root 节点对应的值就是前序遍历数组的第一个元素
        int rootValue = preorder[preStart];

        // rootVal 在中序遍历数组中的索引
        int rootIdxForInorder = map.get(rootValue);

        int leftSize = rootIdxForInorder - inStart;
        int rightSize = inEnd - rootIdxForInorder - 1;

        // 先构造出当前根节点
        TreeNode root = new TreeNode(rootValue);

        // 递归构造左右子树
        root.left = buildBinaryTree(preorder,preStart+1, preStart+leftSize+1, inorder, inStart, inStart+leftSize, map );
        root.right = buildBinaryTree(preorder,preStart+leftSize+1, preEnd, inorder, inStart+leftSize+1, inEnd, map );
        return root;
    }
```



1. 由于`preorder[]`第一个就是根节点的值.通过在`inorder[]`中寻找该值, 就可以找到root节点, 并且找到root的左右子树. 

   ```java
   // root 节点对应的值就是前序遍历数组的第一个元素
   int rootValue = preorder[preStart];
   
   // rootValue 在中序遍历数组中的索引
   int rootIdxForInorder = map.get(rootValue);
   
   int leftSize = rootIdxForInorder - inStart;
   int rightSize = inEnd - rootIdxForInorder - 1;
   ```

   

2. 对左右子树再递归地进行构造, 即可得到完整的二叉树.  (中序,后序) 也同理.

   ```java
   // 先构造出当前根节点
   TreeNode root = new TreeNode(rootValue);
   
   // 递归构造左右子树
   root.left = buildBinaryTree(preorder,preStart+1, preStart+leftSize+1, inorder, inStart, inStart+leftSize, map );
   root.right = buildBinaryTree(preorder,preStart+leftSize+1, preEnd, inorder, inStart+leftSize+1, inEnd, map );
   return root;
   ```

* **无法通过 (前序,后序) 遍历来构造二叉树,** 因为在知道root节点后无法得到其左右子树.

## Example

E.g.:

![Construct Binary Tree from Traversal](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Algorithm/Binary%20Tree%20Algorithms/Construct%20Binary%20Tree%20from%20Traversal.png)

如图所示, 从`preorder[0]`得到`root`节点的值为`1`, 使用此信息从`indorder[]`中查找到`root`节点. 

接下去得到root左右子树的`preorder`和`inorder[]`:

* root.left:
  * `preorder[]={2,5,4,6,7}`
  * `inorder[]={5,2,6,4,7}`
* root.right:
  * `preorder[]={3,8,9}`
  * `inorder[]={8,3,9}`

对左右子树再按照上述步骤递归即可.

# Get Depth

[111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)









