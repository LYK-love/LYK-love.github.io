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

Ref: [阮一峰的GPG教程](https://www.ruanyifeng.com/blog/2013/07/gpg.html)



````sh
gpg --full-generate-key
````

1. 按照提示输入信息，密钥类型使用默认的`RSA and RSA`即可。密钥长度推荐使用4096.

2. 然后输入你的个人信息，GPG会根据你输入的信息来生成一个User ID. 个人信息包括: 用户名, 邮箱.

   > GnuPG needs to construct a user ID to identify your key.

以"阮一峰"为例, 他填写的Real Name是Ruan YiFeng, Email address是yifeng.ruan@gmail.com，所以他的USER ID就是"Ruan YiFeng <yifeng.ruan@gmail.com>".

3. 接着, 系统会让你设定一个私钥的密码. 这是为了防止误操作, 或者系统被侵入时有人擅自动用私钥.

   > Please enter the passphrase to protect your new key: ...

4. 然后, 系统就开始生成密钥了, 这时会要求你做一些随机的举动, 以生成一个随机数.

   > We need to generate a lot of random bytes. It is a good idea to perform
   > some other action (type on the keyboard, move the mouse, utilize the
   > disks) during the prime generation; this gives the random number
   > generator a better chance to gain enough entropy.



密钥生成完毕后, 会有如下输出:

```
public and secret key created and signed.

pub   rsa3072 2023-07-09 [SC]
      B1C0305758DA8FFA44969E22F06D2DE2F071A57E
uid                      Ruan YiFeng <yifeng.ruan@gmail.com>
sub   rsa3072 2023-07-09 [E]
```

注意上面的字符串`B1C030...`, 它是USER ID `Ruan YiFeng <yifeng.ruan@gmail.com>`的hash. **在之后需要填写USER ID的场合, 可以填写其hash作为替代. **并且USER ID中单独的Real Name和Email部分也都能够替代USER ID.



也就是说, 下面四段文本都表示同一个User:

```
Ruan YiFeng
yifeng.ruan@gmail.com
Ruan YiFeng <yifeng.ruan@gmail.com>
B1C0305758DA8FFA44969E22F06D2DE2F071A57E
```



# generate revocation certificate

在生存密钥后, 最好再生成一张revocation certificate(撤销证书), 以备以后密钥作废时, 可以请求外部的公钥服务器撤销你的公钥.

```sh
gpg --gen-revoke [USER ID]
```

如之前所说, 这里的USER ID可以填写USER ID的hash.

# key management

## list  keys

### public key

列出系统中已有的公钥:

```sh
gpg --list-keys
```



显示如下：

```
/home/lyk/.gnupg/pubring.kbx
----------------------------
pub   rsa4096 2022-02-10 [SC]
      DFD9A8D9CF0BD747BE1BDBD839AD95E8DF842459
uid           [ultimate] LYK-love (gpg for lyk) <your_email>
sub   rsa4096 2022-02-10 [E]
```

* 第一行： 公钥文件地址()`/home/lyk/.gnupg/pubring.kbx`)

* 第二行: 公钥特征.

  * `rsa4096`: 使用rsa算法, 密钥长度为4096.
  * `2022-02-10 [SC]`: 密钥生成时间.
  * `DFD9A8D9CF0BD747BE1BDBD839AD95E8DF842459`: USER ID的hash.

* 第三行:

  * 密钥保质期. ` [ultimate]`即永不过期.

  * USER ID: `LYK-love (gpg for lyk) <your_email>`. 说明:

    * Real name: `LYK-love`
    * Email: `your_email`
    * comment: `(gpg for lyk)`

    这个USER ID也可以用其hash来替代.

* 第四行: 私钥特征

### private key

`--list-secret-keys --keyid-format LONG <your_email>`： 列出私钥

```shell
sec   rsa4096/39AD95E8DF842459 2022-02-10 [SC]
      DFD9A8D9CF0BD747BE1BDBD839AD95E8DF842459
uid                 [ultimate] LYK-love (gpg for lyk) <your_email>
ssb   rsa4096/051FBEBE8BDED88B 2022-02-10 [E]
```

各个字段的解释和公钥的相同.

## export keys

导出指定USER ID的公钥:

````sh
gpg --armor --output public-key.txt  --export [USER ID]
````

* `--output outputfile_name`:  指定输出位置
* 由于公钥文件（`pubring.kbx`）以二进制形式储存, 使用 `-armor`可以将其转换为ASCII码显示.





类似地, `export-secret-keys`参数可以导出私钥.



导出指定User的私钥:

```sh
gpg --export-secret-keys  --output private-key.txt --armor <USER ID>
```



导出全部User的私钥:

```sh
gpg --armor --output private-key.txt --export-secret-keys
```

在导出私钥时, 需要为每一个私钥都输入passphrase.



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



# Encrypt && Decrypt

[Encrypting and decrypting documents](https://www.gnupg.org/gph/en/manual/x110.html)

## Encrypt

假定有一个文本文件demo.txt，对它加密:

```
gpg --recipient [USER ID] --output demo.en.txt --encrypt demo.txt
```

* `--encrypt`: 要加密的源文件

* `-r`/`--recipient`：

  指定接受者的USER ID. 可以写完整的USER ID, 也可以写它的hash表示, 也可以只写Email. (--> [ref](https://www.gnupg.org/gph/en/manual/r1208.html))

  文件将会使用这个公钥进行加密, 也就是**只有拥有这个私钥的人才能解密信息**. 可以指定多个, 则多个接受者都能解密信息.

  > The [--recipient](https://www.gnupg.org/gph/en/manual/r1208.html) option is used once for each recipient and takes an extra argument specifying the public key to which the document should be encrypted. **The encrypted document can only be decrypted by someone with a private key that complements one of the recipients' public keys**. **In particular, you cannot decrypt a document encrypted by you** unless you included your own public key in the recipient list.

* `-o`/`--output`：指定加密后的信息输出到哪个文件。可选，如果不指定将会输出到标准输出。

* `-a`/`--armor`：将加密后的信息转为可打印的 ASCII 字符。可选，如果不指定将会输出二进制信息。



## Decrypt

对方收到加密文件以后，就用自己的私钥解密。

```sh
gpg --decrypt demo.en.txt --output demo.de.txt
```

* `--decrypt`： 指定需要解密的文件
* `--output`： 指定解密后生成的文件



GPG允许省略decrypt的参数:

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
