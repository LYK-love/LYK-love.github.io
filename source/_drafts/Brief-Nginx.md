---
title: Brief Nginx
---







查看nginx配置文件位置：

```shell
nginx -t
```





# Problems

```
could not build the types_hash, you should increase either types_hash_max_size: 1024 or....
```

解决方法：在nginx配置文件http模块添加:types_hash_max_size 2048
