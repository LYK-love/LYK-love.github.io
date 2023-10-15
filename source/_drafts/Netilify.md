---
title: Netilify
tags:
---







那个publish branch是服务器本地的, 因此不需要在github上开一个同名的.



We need to build this project first before deploying it and for that we need `mdbook` to be installed on Netlify's CI.

Conveniently mdBook provided pre-built binaries for each of their release, so we can just download that.

I added this as the build command for my Netlify project, adjust the binary version to suit your need.

```sh
curl -sSL https://github.com/rust-lang/mdBook/releases/download/v0.4.34/mdbook-v0.4.34-x86_64-unknown-linux-gnu.tar.gz | tar -xz && ./mdbook build
```

I also need to set the `publish directory` to `book` or whatever you configure the output directory to be.





![image-20230816045239241](/Users/lyk/Library/Application Support/typora-user-images/image-20230816045239241.png)





设置一下netlify本身的对于国外CDN的支持

![image-20230626011415481](/Users/lyk/Library/Application Support/typora-user-images/image-20230626011415481.png)















![image-20230626011458608](/Users/lyk/Library/Application Support/typora-user-images/image-20230626011458608.png)







# Cloudflare



![image-20230626013755151](/Users/lyk/Library/Application Support/typora-user-images/image-20230626013755151.png)





https://who.is/



![image-20230626013820075](/Users/lyk/Library/Application Support/typora-user-images/image-20230626013820075.png)







https://app.netlify.com/sites/lyk-love/settings/domain#production-domains





Email:

![image-20230626014801944](/Users/lyk/Library/Application Support/typora-user-images/image-20230626014801944.png)

# 速度

![image-20230626025959193](/Users/lyk/Library/Application Support/typora-user-images/image-20230626025959193.png)![image-20230626025959360](/Users/lyk/Library/Application Support/typora-user-images/image-20230626025959360.png)
