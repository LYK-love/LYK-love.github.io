---
title: Lossless and Lossy Comprehension
categories: Potpourri
date: 2022-08-14 21:21:32
tags:
---


Outline: 

* Lossless and Lossy Compression
* Comparison Between the two
* PNG
* AVIF
* WebP
* JPEG XL

<!--more-->

# Lossless and Lossy Compression

* Lossless Comporession: 就是可逆的压缩, 压缩文件可以被解压为原文件

  * 流行的无损压缩方法:

    * 普通文件: ZIP, RAR
    * Web中的JS和CSS文件: GZIP
    * 图像: **PNG**

  * 无损压缩适合:logos, screenshots, charts, and graphics.

    因为这些图片都有着**连续的色块**, 可以用类似[Run-Length Encoding (RLE)](https://en.wikipedia.org/wiki/Run-length_encoding)的算法来压缩. 

* Lossy Comporession: 在压缩时会损失一些信息, 但是压缩效果比无损压缩好很多

  * 流行的有损压缩方法: 
    * JPEG,  lossy WebP
  * 有损压缩适合处理照片. 因为损失一些细节并不能被用户看出. 但是它不适合图表( graphics )之类的有连续色块的图像, 在这些图像上损失一点细节都会被用户察觉

# Comparison Between the two

![img](https://siipo.la/app/uploads/comparing-lossy-and-lossless-compression.png?ver=ce9b57b5)

如上“可回收图案”有大量连续色块. 用无损压缩PNG压缩到3KB, 其效果远好于无损压缩的JPEG的3KB, 甚至略好于JPEG的24KB.



这证明了对于Graphics等图片, 无损压缩的优势

# PNG

* PNG ( [Portable Network Graphics](https://en.wikipedia.org/wiki/Portable_Network_Graphics) ): 最古老的图像格式之一. 基于[DEFLATE compression algorithm](https://en.wikipedia.org/wiki/Deflate), 并且有一个颜色筛选器. 
  * 可以把PNG的DEFLATE算法替换成Google的 [Zopfli](https://en.wikipedia.org/wiki/Zopfli)算法, 后者压缩效果更好, 但消耗时间更长
  * PNG format is supported by all browsers.
* 背景: 1996年发布, 旨在取代GIF. PNG拥有24-bit color (8 bits per channel) and an alpha channel. 而 GIF 只有24种颜色和一个透明度值

## 优化步骤

有许多[PNG优化工具](https://www.cyberciti.biz/faq/linux-unix-optimize-lossless-png-images-with-optipng-command/): [PNGOUT](http://advsys.net/ken/utils.htm), [OptiPNG](http://optipng.sourceforge.net/), and Rust-based [OxiPNG](https://github.com/shssoichiro/oxipng)





1. I compressed PNG files using OxiPNG v5.0.0, using the maximum possible optimization level with the following command:

   ```
   oxipng /path/to/input/image.png --out /path/to/output/image.png --opt max --strip safe
   ```

2. I also optimized the same set of images using the Zopfli compression which takes a really long time but results in even smaller files.

   ```
   oxipng /path/to/input/image.png --out /path/to/output/image.png --opt max --strip safe --zopfli
   ```



PNG优化效果很一般, OXIPNG能优化12%左右. 开启`--zopfli`后优化时间大幅提升, 但最终效果也只有18%. 总的来说, PNG除了支持度比较高之外没什么优势. 要降低图片大小, 与其使用PMG + 优化, 不如直接使用其他图片格式( 无损的WebP和无损的JPEG XL )

# AVIF

* AVIF( [AV1 Image File Format](https://en.wikipedia.org/wiki/AV1#AV1_Image_File_Format_(AVIF)) ): 基于AV1 video codec( codec = encoder + decoder, 编解码器 )的新图像格式. **同时支持无损和有损压缩**
* AVIF is supported in recent versions of Google Chrome and can be enabled in Firefox by using a configuration flag.
* AVIF有许多advanced features: high bit depth, HDR ...

## 压缩步骤

压缩工具是avifenc from [libavif](https://github.com/AOMediaCodec/libavif)



With avifencv0.9.1I, used the lowest possible speed to get the best compression.

```
avifenc --lossless --speed 0 /path/to/input/image.png /path/to/output/image.avif
```



无损和有损的AVIF压缩效果都很一般,不推荐

# WebP

* [WebP](https://en.wikipedia.org/wiki/WebP):  Google在2008年发布了基于VP8 video codec的有损WebP; 又在2012年发布了不基于VP8 video codec的无损WebP0.3
* While lossy WebP is limited to 4:2:0 Chroma subsampling which discards some color information, lossless WebP will retain all original image data.
* WebP is now supported by all major browsers <u>except Safari</u>

## 压缩步骤

For WebP, I used the official cwebp tool, version 1.2.0. For best compression, I defined quality of 100 and method 6.

```shell
cwebp /path/to/input/image.png -o /path/to/output/image.webp -q 100 -m 6 -lossless
```



Lossless WebP压缩效果暴打PMG, 其大小能降低大约41%, 压缩速度也很快. WebP的支持度也很高. **强烈推荐使用WebP**

# JPEG XL

* [JPEG XL](https://en.wikipedia.org/wiki/JPEG_XL):  JPEG XL是JPEG( aka JPG )格式的后继, 它相当于两种图像格式的结合: [Pik](https://github.com/google/pik) developed by Google  +  [FUIF](https://github.com/cloudinary/fuif) (Free Universal Image Format) developed by Cloudinary. **同时支持无损和有损压缩**
* JPEG XL is supported in Chrome and Firefox, but it’s not enabled by default. Support for the format must be enabled by using a feature flag.

## 压缩步骤

Pik使用的CLI tool是`cjxl`, 再开启`--modular`选项就可以添加FUIF格式



To compress JPEG XL files, I used the official cjxl tool, version 0.3.7_1.

```
cjxl /path/to/input/image.png /path/to/output/image.jxl --modular --quality 100 --speed 9 -E 3 
```

* `-E` flag: means "extra arguments", I used the value 3, which is recommended for best compression. Using this option shaved off a few kilobytes from the file size while the image took a bit longer to compress.



JEPG XL的压缩效果略好于WebP, 二者详细对比见[这篇文章](https://nginx-v5qibj75pa-ew.a.run.app/blog/is-webp-really-better-than-jpeg)

