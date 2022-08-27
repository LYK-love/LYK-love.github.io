---
title: GPG
categories: Toolkit
date: 2022-02-10 14:57:00
---


useful encryption tool

<!--more-->

# Intro

 **Pretty Good Privacy (PGP)** is a nice example of an e-mail encryption scheme written by Phil Zimmermann in 1991 [PGP 2020]. Depending on the version, the PGP soft- ware uses MD5 or SHA for calculating the message digest; CAST, triple-DES, or IDEA for symmetric key encryption; and RSA for the public key encryption.

不过PGP是商用软件, 因此自由软件基金会( FSF )开发了PGP的替代品GnuPG, 也就是GPG. 这两个软件事实上差不多, 我们接下来介绍GPG.



GPG( or PGP )的实现原理参见拙著[Security in Internet](https://lyk-love.cn/2022/08/28/Security-in-Internet/) --> Application Layer: Securing E-Mail

# install

* 输入`gpg --help`可以查看你是否已经安装

# generate GPG key

* `gpg --full-generate-key`
* 按照提示输入信息，密钥类型使用默认的`RSA and RSA`即可。密钥长度推荐使用4096,
* 然后输入你的个人信息，这样密钥就会绑定到你的邮箱，要使用和 Git 提交相同的邮箱地址。
* 最后输入**私钥的密码**，用来提取这个密钥。这样一个 GPG 密钥就生成好了



# generate revocation certificate

* `gpg --gen-revoke [用户ID]`:生成一张"撤销证书"，以备以后密钥作废时，可以请求外部的公钥服务器撤销你的公钥

# key management

## list  keys

### public key

* `--list-keys`: 列出系统中已有的公钥

  显示如下：

  ```
  /home/lyk/.gnupg/pubring.kbx
  ----------------------------
  pub   rsa4096 2022-02-10 [SC]
        DFD9A8D9CF0BD747BE1BDBD839AD95E8DF842459
  uid           [ultimate] LYK-love (gpg for lyk) <your_email>
  sub   rsa4096 2022-02-10 [E]
  ```

  第一行： **公钥**文件名（`pubring.kbx`）

  第二行： 公钥特征（4096位，Hash字符串和生成时间）

  第三行： 密钥保质期，用户id， comment, email

  第四行： 私钥特征

### private key

* `--list-secret-keys --keyid-format LONG <your_email>`： 列出私钥

  ```shell
  # 这里以别人的为例
  sec   rsa4096/39AD95E8DF842459 2022-02-10 [SC]
        DFD9A8D9CF0BD747BE1BDBD839AD95E8DF842459
  uid                 [ultimate] LYK-love (gpg for lyk) <your_email>
  ssb   rsa4096/051FBEBE8BDED88B 2022-02-10 [E]
  ```

  `39AD95E8DF842459`就是用户ID的hash, 等价于用户ID（`LYK-love`  or `<your_email>`）

## export keys

* `gpg --armor --output public-key.txt  --export pub [用户ID]`： 导出该用户ID的公钥

  * 公钥文件（`pubring.kbx`）以二进制形式储存，`-armor`可以将其转换为ASCII码显示

  * `--output outputfile_name`:  指定输出位置

  * `export-secret-keys`：导出私钥：

    `gpg --armor --output private-key.txt --export-secret-keys`



## upload public key

公钥服务器是网络上专门储存用户公钥的服务器



* `gpg --send-keys [用户ID] --keyserver hkp://subkeys.pgp.net`：将公钥传到服务器`subkeys.pgp.net`，通过交换机制，所有的公钥服务器最终都会包含该公钥



* `gpg --fingerprint [用户ID]`：生成公钥指纹
  * 由于公钥服务器没有检查机制，任何人都可以用你的名义上传公钥，所以没有办法保证服务器上的公钥的可靠性。通常，因此需要公布一个公钥指纹，让其他人核对下载到的公钥是否为真



## import public key

* 除了生成自己的密钥，还需要将他人的公钥或者你的其他密钥输入系统

  ```shell
  gpg --import [密钥文件]
  ```

  

* 为了获得他人的公钥，可以让对方直接发给你，或者到公钥服务器上寻找

  ```shell
  gpg --keyserver hkp://subkeys.pgp.net --search-keys [用户ID]
  ```

  

正如前面提到的，我们无法保证服务器上的公钥是否可靠，下载后还需要用其他机制验证



# encrypt && decrypt

## encrypt

假定有一个文本文件demo.txt，对它加密:

*  `gpg --recipient [用户ID] --output demo.en.txt --encrypt demo.txt`
  * `--encrypt`: 指定加密源文件
  * `--recipient`：指定**接收者**的公钥
  * `--output`： 指定加密后的文件名

## decrypt

对方收到加密文件以后，就用自己的私钥解密。

* `gpg --decrypt demo.en.txt --output demo.de.txt`
  * `--decrypt`： 指定需要解密的文件
  * `--output`“： 指定解密后生成的文件



* GPG允许省略decrypt的参数:

  ```shell
  gpg demo.en.txt
  ```

  运行上面的命令以后，解密后的文件内容直接显示在STDOUT

# signiture

## file signiture

有时，我们不需要加密文件，只需要对文件签名，表示这个文件确实是我本人发出的

* `gpg --sign demo.txt`:  在当前目录下生成`demo.txt.gpg`文件，这就是签名后的文件,默认采用二进制储存

  * `--clearsign`: 生成ASCII码的签名文件（ `demo.txt.asc`， 后缀名asc表示该文件是ASCII码形式 ）

* `gpg --detach-sign demo.txt`： 生成单独的签名文件，与文件内容分开存放

   运行上面的命令后，当前目录下生成一个单独的签名文件demo.txt.sig。该文件是二进制形式的，如果想采用ASCII码形式，要加上armor参数。

  `gpg --armor --detach-sign demo.txt`



## verify signiture

我们收到别人签名后的文件，需要用对方的公钥验证签名是否为真,`--verify`用来验证

`gpg --verify demo.txt.asc demo.txt`

举例来说，[openvpn](https://openvpn.net/index.php/open-source/downloads.html)网站就提供每一个下载包的gpg签名文件。你可以根据它的[说明](https://openvpn.net/index.php/open-source/documentation/sig.html)，验证这些下载包是否为真



# signiture + encryption

如果想同时签名和加密，可以使用下面的命令：

`gpg --local-user [发信者ID] --recipient [接收者ID] --armor --sign --encrypt demo.txt`

* --`local-user`： 用发信者的名字作为私钥签名，该option必须放在前面。 该option是可选的，默认采用`default- key`
* `--recipient`： 指定用接收者的公钥加密
* --`armor`： 采用ASCII码形式显示
* `--sign`： 表示需要签名
* `--encrypt`： 指定源文件

# **将 GPG 密钥与 Git 关联**

```shell
git config --global user.signingkey 66DD4800155F7A2B
# 或者
git config user.signingkey 66DD4800155F7A2B
```



## Git 提交启用签名

* 在提交时启用签名很简单，只要在`git commimt`命令中加上`-S`选项即可。

* 1Git 提交时，使用 -S 标记进行 GPG 签名：

  ```shell
  git commit -S -m “commit message"
  ```



* Git 可以设置默认使用 GPG 签名提交：

  ```shell
  git config --global commit.gpgsign true
  # 或者
  git config commit.gpgsign true
  ```

  

## 解决“error: gpg 数据签名失败”

* commit报错：

  ```
  error: gpg 数据签名失败
  fatal: 写提交对象失败
  ```

* solution：

  1. 在`.zshrc`里面加入一行代码 `export GPG_TTY=$(tty)`

  2. 重启 gpg-agent: 第一次配置，必须重启，否则签名会失败:

     `gpgconf –kill gpg-agent`

  3. 重启终端（或者新开一个终端标签）
