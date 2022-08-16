---
title: Gzip format and DEFLATE algorithm
categories: Potpourri
mathjax: true
---



# Intro

对于如下指令:

```shell
tar -czf target.tar.gz file1 file2 file3
```

tar是打包格式, `-z`指定使用Gzip压缩格式, 通过DEFLATE 算法压缩得到

DEFLATE 算法结合了 LZ77 算法和 Huffman 编码, 由 Phil Katz 设计, 并被 [RFC1951](https://tools.ietf.org/html/rfc1951) 标准化

# LZ77

