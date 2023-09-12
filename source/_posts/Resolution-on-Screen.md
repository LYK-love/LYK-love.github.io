---
title: Resolution on Screen
categories: Computer Science
mathjax: true
date: 2022-08-13 20:35:23
tags:
---



Outline:

* Pixel
* Resolution
* Pixel in Other Domains

<!--more-->

# Pixel

* Pixel( "px" for short  ): 像素，简称px. pixel是构成digtial picture的基本单位

* Mega Pixel( "MP" for short ): 百万像素. 比如IPhone13的单相机像素就是[12MP](https://www.technadu.com/iphone-13-camera/301276/#:~:text=Photography-Related%20iPhone%2013%20Camera%20Specs%20%20%20,Aperture%20size%3A%20F1.5%20%202%20more%20rows%20). 

  * 在计算机科学中, Mega一般表示$2^{20}$; 不过这里的Mega是$10^{6}$

* 一般用 [width] x [height] px来衡量图片和屏幕的清晰度, 比如下面的50 x 50 px图片一小格代表一个pixel; 比如常见的1920 x 1080 px屏幕.

  * 也可用**总像素数**表示, 50 x 50px也就是2500 px. 
  * “总像素数”的表示方式一般用在相机/屏幕上,图片描述都用[width] x [height] 形式

  ![A with 50 * 50px](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/Resolution%20on%20Screen/A%20with%2050%20%2A%2050px.png)

# Resolution

图像的Resolution( 解析度 or 清晰度 )是比较模糊的概念, 对于**图像**本身而言, 就是像素的密度, 单位为PPI; 而对于**打印**出的图像而言, 是打印时的墨点密度, 单位为DPI. 

DPI和PPI很容易被混淆, 其实二者是不同的

对于设备而言,有时候直接把总像素数称为清晰度, 所以说到”清晰度“时,一定要注意指的是px, PPI还是DPI

## PPI

* Pixels Per Inch( "PPI" for short ): 一英寸内的像素数量, PPI用来表示像素密度

  * 相同尺寸下, 不同像素数的图片, 清晰度差距是很大的:

    ![PPI](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/Resolution%20on%20Screen/PPI.png)

    上面两张图的图片尺寸一样, 左图PPI=16, 右图PPI=32

    

* 只要屏幕大于300 PPI, 人眼就不能分辨. 问题在于不仅是屏幕大于300PPI, 屏幕内显示的图片也要跟上这个解析度

## DPI

* Dots Per Inch( "DPI" for short ): 每英寸的墨点数, DPI用来表示打印机的墨点密度. 

  * 对于喷墨式打印机, DPI取决于其X, Y轴的马达步进速度. 所以打印机的DPI参数一般是[ X ], [Y] dpi. 
    * 你可以见到600dpi的打印机, 这意味着X和Y轴的DPI都是600
  * 对于非喷墨的打印机,当然就不存在“墨点”,但它们的成像密度也都用DPI表示

* 不同媒体对DPI的“Dot”的定义不一样, 

  * Dot本来是成像设备的墨点, 和图片没有关系. 但是图片的参数也一般会有DPI, 图片的"Dot"就是Pixel, 因此DPI就是PPI. 而当图片被传到打印机, "Dot"又被解读为墨点. 

    ![DPI](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Potpourri/Resolution%20on%20Screen/DPI.png)

    可以看到,DPI在这里就是PPI( pixels/inch )

  * 手机屏幕作为成像设备, 其“Dot”就是屏幕的物理像素点, 所以手机屏幕的PPI和DPI也是一回事

* 在打印时,DPI一般首先取决于纸张和打印机,. 假设有400 * 400 dpi的打印机, 要求输出图像宽度为A4纸宽度(  = 8.268 inch = 21 cm ), 则图像在X方向的像素数为:
  $$
  X \ \mathrm{px} / (400 \ \mathrm{px/inch}) = 8.268 \ \mathrm{inch} \\
  X = 3307 \ \mathrm{px}
  $$
  假设图片是正方形的, 也就是Y方向像素数也是3307 px, 这张图片的像素数就是3,307 * 3,307 ≈ 10.9 MP, 需要千万像素的相机才能拍出( 比如iPhone13的12MP摄像头). 以此类推, 一张正方形图片,以400DPI按宽度满版打印, 需要的总像素数如下:

  

  | Size    | Millimeters   | Inches          | Pixels |
  | :------ | :------------ | :-------------- | ------ |
  | A0 size | 841 x 1189 mm | 33.1 x 46.8 in  | 175MP  |
  | A1 size | 594 x 841 mm  | 23.4 x 33.1 in  | 87.6MP |
  | A2 size | 420 x 594 mm  | 16.5 x 23.4 in  | 43.6MP |
  | A3 size | 297 x 420 mm  | 11.7 x 16.5 in  | 21.9MP |
  | A4 size | 210 x 297 mm  | 8.268 x 11.7 in | 10.9MP |

  

现在最新的专业相机,其像素数也就是60MP, 入门级的一般就20MP, 在400DPI下连A3纸大小的图片都打印不了. 

事实上,大部分图片的人眼观看距离都在30cm以上, 对于贴在墙上的海报, 那距离就更远了. 在这么远的距离下, 没有必要维持很高的DPI, 所以一般DPI都小于400

## DPI && PPI

# Pixel in Other Domains

| device            | 屏幕像素       | 屏幕对角线尺寸 | PPI  |  CSS Pixel    | DPR |
| ----------------- | -------------- | -------------- | ---- | ---- | --------- |
| iPhone SE2        | 750 * 1134 px  | 4.7 inch       | 326  | 375 * 667 px | @2x |
| iPhone 12 Pro Max | 1284 * 2778 px | 6.68 inch      | 458  | 428 * 926 px | @3x |
| iPhone 13 Pro Max | 2778 * 1284 px | 6.7 inch       | 458  | 926 * 428 px | @3x |

移动设备的屏幕分辨率普遍比桌面屏幕好, iPhone13的分辨率1170 x 2532已经大于桌面屏幕的1920 x 1080了. 而iPhone13的宽度只有8cm!  

移动设备的屏幕较小, 但分辨率很高, CSS media query很容易把1170 x 2532 px认为是桌面屏幕. 为此, 对于移动设备, 我们使用的是**CSS Pixel**,

## CSS pixel in Web

### CSS Pixel

* CSS Pixel: Web领域的Pixel, 可以认为是虚拟像素 or 标准像素. 它与真正的屏幕Pixel成比例关系( DPR )

  * 经过DPR的转化, iPhone13的CSS Pixel只有926 x 428 px, CSS media query会将其判定为移动设备

  * 事实上DPR和CSS Pixel的转换都是隐式发生的. CSS media query和JS都只能查询到CSS Pixel. 因此我们开发时不需要考虑二者的转化, **只需要面对CSS Pixel**

    ```html
    <meta name="viewport" content="width=device-width, initial-scale=1">
    ```

### DPR

* Device Pixel Ratio( DPR ): 就是CSS Pixel和屏幕Pixel的比值. 别名有:
  * Dots Per PiXel( DPPX ) : 这里的“Dot”就是屏幕像素, 而"Pixel"是CSS Pixel
  * or pixel density
* 不同设备的屏幕大小不同, 因此DPR也不同,
  * 比如iPhone SE2的DPR是2, 那么每2个屏幕Pixel对应一个CSS Pixel; iPhone13的DPR是3,每三个屏幕Pixel对应一个CSS Pixel;
  * 因此, 对于100 x 100 px( 这里是CSS Pixel ) 的图片, 在iPhone SE2被放大为200 x  200 屏幕px, 在iPhone13被放大为300 x 300 屏幕px, 清晰度会受影响. 因此有必要**为不同DPR的设备提供不同清晰度的图像**





## pt && dp in APP

对于APP( 或者说客户端 ), 不同平台使用的Pixel分别是:

*  ios: point( “iOS pt” for short) 
* Android: device-independent pixel( “dp” for short )

二者其实都是 屏幕Pixel / DPR

## DPR and PPI/DPI

我们知道手机的PPI( or DPI, 二者对于手机是一个东西 )是屏幕的像素密度, 而DPR是屏幕像素与 虚拟/标准像素( CSS Pixel or iOS pt or dp ) 的比. 

对于**手机**, Web( 使用CSS Pixel )的**标准**PPI是160; APP的标准依平台而定. Android( 使用dp )的标准PPI是160, iOS( 使用iOS pt )的标准PPI是163( 这是iPhone13的PPI ). 那么:

* 1 CSS pixel ≈ 1/160 inch
* 1 dp ≈ 1/160 inch
* 1 iOS pt ≈ 1/163 inch

以CSS pixel为例, 其标准PPI是160, 那么对于PPI = 320的屏幕, 其DPR就是 320 / 160 = 2. 即每两个屏幕像素被转化成一个虚拟/标准像素

以此类推,对于iOS, 以iPhone13为例, 其PPI = 458, 则其DPR就是 458 / 163 = 3
