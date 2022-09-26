---
title: Git
tag: Git
categories: Toolkit
---





全面介绍了Git的原理和使用



<!-- more-->

ref: 

*  [廖雪峰的教程](https://www.liaoxuefeng.com/wiki/896043488029600)

* [git使用技巧和笔记](https://wangchujiang.com/git-tips/)
* [Learn Git Branching](https://learngitbranching.js.org/?locale=zh_CN)

Tools:

* [Git Command Explorer](https://gitexplorer.com/)

# Intro 

* Git是Linus用**C**写的分布式版本管理系统

> 集中式:
>
> * CVS[^1]:最早的开源且免费的集中式版本控制系统<由于自身设计问题,会造成提交文件不完整,版本库莫名损坏的情况
> * SVN[^2]:同样开源且免费,修正了CVS的一些稳定性问题,是目前用得最多的集中式版本控制系统 
> * ClearCase:IBM的,收费,又大又笨

> 分布式:
>
> * Git

[^1]: Concurrent Versions System
[^2]:Apache Subversion

## 创建版本库

版本库:*repository*

第一步,选一个地方,创建一个空目录

```
$ mkdir Doc
$ cd Doc
$ pwd
/c/Users/陆昱宽/Desktop/DOC
```

`pwd`命令用于显示当前目录,在我的电脑上,这个仓库位于`/c/Users/陆昱宽/Desktop/DOC`.

第二步,通过`git init`命令把这个目录变成git可以管理的仓库

```
$ git init
Initialized empty Git repository in /c/Users/陆昱宽/Desktop/DOC/.git/
```

仓库建好了,而且是空的. 当前目录下多了个`.git`的目录,这个目录是Git来跟踪管理版本库的,不要乱碰.

`.git`目录默认是隐藏的,用`ls -ah`命令就能看见

## 把文件添加到版本库

所有版本控制系统,只能跟踪文本文件的改动,比如txt,网页,代码等. 而图片,视频这些二进制文件,虽然也能由版本控制系统管理,但没法跟踪文件的变化,就是说知道改了,但不知道改了啥. 

微软的Word格式是二进制格式,所以版本控制文件没法跟踪Word文件的改动. Windows自带的记事本在保存UTF-8的文件时,会自动在其开头添加0xefbbbf（十六进制）的字符,因此会有许多问题,建议使用Notepad++ ,编码设为UTF-8 without BOM



编写一个`Git.md`文件,放到`Doc`目录下(子目录也行)

1. 先add

`$ git add Git.md`

执行上面的命令,没有任何反馈,OK了,说明添加成功

2. 再commit

```
$ git  commit -m'1
[master 45a4a38] 3
 1 file changed, 46 insertions(+)
 create mode 100644 readme.txt
```

`46 insertions`：插入了46行内容

* Q:如果输入`git add Git.md`，得到错误`fatal: pathspec 'Git.md' did not match any files`。

  A：添加某个文件时，该文件必须在当前目录下存在，用`ls`或者`dir`命令查看当前目录的文件，看看文件是否存在，或者是否写错了文件名。

# 基本操作

## git add

我们修改Git.md文件,运行`git.status`看看结果:

```

$ git statusOn branch master
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    "\346\227\245\350\256\260.md"

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Diary.md
        "\344\271\220\350\260\261.md"

no changes added to commit (use "git add" and/or "git commit -a")
```

`git.status`命令可以展示仓库当前的状态,上面的输出告诉我们,`Git.md`被修改过了,但还没有准备提交的修改.

用`git  diff Git.md`能看到具体修改了什么内容:

```
$ git diff
diff --git "a/\346\227\245\350\256\260.md" "b/\346\227\245\350\256\260.md"
deleted file mode 100644
index 4db3376..0000000
--- "a/\346\227\245\350\256\260.md"
+++ /dev/null
@@ -1,179 +0,0 @@
-　# Diary
-
-## 12 / 25
-
-　　圣诞夜中了两棵树,一棵二叉搜索树,一棵AVL树,另一棵B树没有开工,忙碌的一天。
-
-
-
-　## 12/26
-
-　　昨天凡人修仙传看到四点, 今天本打算写完微积分和计基的,但是没忍住看了一天小说
```

`git diff`顾名思义就是查看difference，显示的格式正是Unix通用的diff格式

知道了对`Git.md`作了什么修改后,再把它提交到仓库就放心多了. 提交修改和提交新文件一样是两步,

1. `git add`

   

```
$ git add Git.md
```

没有任何反应,在执行`git commit`之前,我们再运行`git status` 看看当前仓库的状态:

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   Git.md
```

`git status`告诉我们,将要被提交的修改包括`Git.md` ,下一步就能放心提交了:

```
$ git commit -m"4"
[master 4553e0a] 4
 1 file changed, 77 insertions(+), 1 deletion(-)
```

提交后,再用`git status`看看仓库的当前状态:

```
$ git status
On branch master
nothing to commit, working tree clean
```

Git告诉我们当前没有需要提交的修改,且工作目录是干净(working tree clean)的.

**小结**

*  要随时掌握工作区的状态,使用`git status`命令
* 如果`git status`告诉你文件有被修改过,用`git diff 文件名` 可以查看修改内容
* `commit`的message千万不能有中文,否则会乱码

## 版本回退

先提交文件,message为"origin";再输入"初次修改"并提交,message为"chucixiugai";再输入"再次修改"
并提交,message为"再次修改".

现在,`Git.md`一共有三个版本(origin之前的不算)被提交到repository里了,

版本1:origin

```

```

(啥都没写)

版本2:chucixiugai

```
初次修改
```

版本3:zaicixiugai

```
再次修改
```

我们不可能记住一个文件每次都改了什么内容,版本控制系统肯定有某个命令可以告诉我们历史记录,Git中用`git log`命令查看:

```
$ git log
commit 028637e47a974357debe623e8bb4d0ca5053db87 (HEAD -> master)
Author: 陆昱宽 <191820133@ smail.nju.edu.cn>
Date:   Sun Feb 28 23:41:08 2021 +0800

    zaicixiugai

commit cdd92a630141982791273c123d60b3ce0ed09932
Author: 陆昱宽 <191820133@ smail.nju.edu.cn>
Date:   Sun Feb 28 23:40:30 2021 +0800

    chucixiugai

commit 914f04abce43f4517121ba10957d89bd9658432e
Author: 陆昱宽 <191820133@ smail.nju.edu.cn>
Date:   Sun Feb 28 23:39:31 2021 +0800

    origin
```

`git log`命令显示最近到最远的全部提交日志,我们看最近三次,最近一次是`zaicixiugai`,上一次是`chuxixiugai`,再上一次是`origin`. 如果嫌输出信息太多不太好看,可以加上`--pretty=oneline`参数:

```
$ git log --pretty=oneline
028637e47a974357debe623e8bb4d0ca5053db87 (HEAD -> master) zaicixiugai
cdd92a630141982791273c123d60b3ce0ed09932 初次修改
914f04abce43f4517121ba10957d89bd9658432e origin
```

 我们看到许多类似`028637e`的`commit id`(版本号),这是一个SHA1计算出的非常大的数字,用十六进制表示. SVN的版本号是1,2,3,4递增,因为SVN是集中式. Git是分布式,号码容易不够,所以用这种方式

每提交一个新版本，实际上Git就会把它们自动串成一条时间线。如果使用可视化工具查看Git历史，就可以更清楚地看到提交历史的时间线

现在我们把`Git.md`回退到上个版本`chucitijiao`. 首先,Git必须知道当前版本是哪个版本,在Git中,用`HEAD`(小写也可以)表示**当前版本**,即最近的提交`02863`,上个版本就是**`HEAD^`**,上上个版本就是`HEAD^^`,以此类推. 往前100个版本数不过来,可以写成**`HEAD~100`**.

用 `git reset`命令:

```
$ git reset --hard HEAD^
HEAD is now at cdd92a6 chucitijiao
```

,`--hard`参数的意义之后再讲.  

OK,已经被还原了

现在用`git log`看看当前版本库的提交日志:

```
$ git log
commit cdd92a630141982791273c123d60b3ce0ed09932 (HEAD -> master)
Author: 陆昱宽 <191820133@ smail.nju.edu.cn>
Date:   Sun Feb 28 23:40:30 2021 +0800

    chucixiugai
    
commit 914f04abce43f4517121ba10957d89bd9658432e 
Author: 陆昱宽 <191820133@ smail.nju.edu.cn>
Date:   Sun Feb 28 23:39:31 2021 +0800

    origin
```

我们看不到最近的那个版本`zaicixiugai`了! 好比时间从21世纪穿越回了10世纪,当然看不到后面的历史了! 如果想回去,就要用`commit id`. 

1. 如果还没关掉GIt窗口,可以把窗口往上翻,找到那个`zaicixiugai`的`commit id`是`028637e...`,于是可以指定回到未来的某个版本:

```
$ git reset --hard 0286
HEAD is now at 028637e zaicixiugai
```

版本号没必要写全,写前几位. Git会自动去找. 

OK,已经回到未来了.

2. 如果已经关掉窗口了,Git中有`git reflog`记录你的每一次命令:

```
$ git reflog --pretty=oneline
028637e (HEAD -> master) HEAD@{0}: reset: moving to 0286
914f04a HEAD@{1}: reset: moving to head^
cdd92a6 HEAD@{2}: reset: moving to HEAD^
028637e (HEAD -> master) HEAD@{3}: commit: zaicixiugai
cdd92a6 HEAD@{4}: commit: 初次修改
914f04a HEAD@{5}: commit: origin
```

**小结**

* `HEAD`指向的版本就是当前版本,这是个指针. 版本穿梭使用`git reset --hard commit_id`
* 穿梭前,用`git log`可以查看提交历史,以便确定要回退到哪个版本.
* 要回到未来,可以用`git reflog`来确定要回到未来的哪个版本.
* 如果commit（提交）比较多，git log 的内容就会比较多；当满屏放不下，就会显示冒号，回车（往下滚一行）、空格（往下滚一页）可以继续查看剩余内容；**退出**：英文状态下 按 **q** 可以退出git log 状态。

## 工作区和暂存区

Git和其他版本控制系统如SVN的一个不同之处就是有暂存区的概念.

*工作区(Working directory)*
就是在电脑里能看到的目录,如`Doc`文件夹就是一个工作区.

*版本库(Eepository)*
工作区有一个隐藏目录`.git`,它不算作工作区,而是Git的版本库.

Git的版本库里存了许多东西,其中最重要的就是称为*stage*(或*index*)的**暂存区**,还有Git为我们自动创建的第一个**分支**`master`,以及指向`master`的一个**指针**叫`HEAD` 

(所以版本库(包括暂存区和分支们)都在工作区里面,只是不算作工作区)

![git-repo](https://www.liaoxuefeng.com/files/attachments/919020037470528/0)

分支和`HEAD`的概念暂且不表.

前面讲了我们把文件添加剂Git版本库时,是分两步的:

第一步用`git add`把文件修改添加到**暂存区**(stage)

第二步用`git commit`把**暂存区**的**所有内容**提交到**当前分支**

因为我们创建Git版本库时,Git为我们自动创建了一个`master`分支,所以,现在`git commit`就是往`master`分支上提交更改.

需要提交的文件统统放到暂存区,然后,一次性提交暂存区(stage)的所有修改到当前分支

举例,先建个`readme.txt`提交到版本库,再在工作区(即Doc这个文件夹)里新增一个`LICENSE`文本文件,再对`readme.txt`做些修改(内容都随意). 先用`git status`看看状态:

```
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   readme.txt

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        LICENSE.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

Git告诉我们,`readme.txt`被修改了,这个修改没有被添加到暂存区,遑论分支了( changes not staged for commit). 而`LICENSE`这个文件还从来没被添加(add)过,所以其状态是`Untracked`. 由于没有修改被提交到暂存区,暂存区就是空的( no changes added to be commit).

现在用两次`git add`把把`readme.txt`和`LICENSE`都添加后，用`git status`再查看一下：

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   LICENSE.txt
        modified:   readme.txt
```

现在,暂存区状态变成这样了:

![git-stage](https://www.liaoxuefeng.com/files/attachments/919020074026336/0)



所以,`git add`命令就是把要提交的所有修改放到暂存区(stage),然后,执行`git commit`可以一次性把暂存区所有修改提交到分支. (注意暂存区不是被**"清空"**,而是"安静"了.暂存区中永远保留着上次add的版本)因此

![git-stage-after-commit](https://www.liaoxuefeng.com/files/attachments/919020100829536/0)



一旦**提交**(注意是`commit`) 后,如果你对工作区又没有做任何修改,那么**工作区**就是clean的:

```
$ git status
On branch master
nothing to commit, working tree clean
```

* 关于`git diff`:

  如果是输入`git diff`，查看到的是**工作区和暂存区**(上次git add 的内容)的不同，如果是`git diff --cached`，查看到的是**暂存区和HEAD**的不同。 

## 撤销修改

在`readme .txt`中添加了一行,但还没有`git add`:

```
$ cat readme.txt
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
Git tracks changes of files.
My stupid boss still prefers SVN.
```

现在想撤销最后一行,可以用 `git restore readme.txt`, 有两种情况:

* `read.me.txt`自修改后还没有被放到暂存区,现在,撤销修改就回到和版本库一模一样的状态 .
* `readme.txt`已经添加到暂存区后,又做了修改. 现在,撤销修改就回到和添加到暂存区后的状态.

总之,就是让该文件回到最近一次`add`时的状态(即 **暂存区**里的状态)

现在,看看`readme.txt`的内容:

```
$ cat readme.txt
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
Git tracks changes of files.
```

果然复原了.



如果我把那句话` git add`到暂存区了呢? ( 但还没有`commit`) ,先用`git status`查看一下,

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   readme.txt
```

git告诉我们,修改只是被添加到了暂存区,还没有被提交,可以用 `git restore --staged readme.txt`  把暂存区的修改撤销掉( unstage ),**重新放回工作区**:

```
$ cat readme.txt
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
Git tracks changes of files.
My stupid boss still prefers SVN.
```

再用`git status`查看一下,现在暂存区是干净的,工作区有修改:

```
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   readme.txt
```

我们要丢弃工作区的修改,就回到了上上步: `git restore readme.txt`

```
$ git restore readme.txt

$ git status
On branch master
nothing to commit, working tree clean
```

Over!

如果我不仅把那句话`git add`了,我还`git commit`到了版本库, 我们可以用*版本回退*. 但如果你还把它`git push`到了 远程版本库,那就完蛋了.

## 删除文件

情况一: 工作区文件删除,无其它操作

1.  `rm readme.txt`

可用命令`git restore readme.txt`恢复文件

情况二: 工作区文件删除,版本库文件删除

1. ` rm readme.txt`
2. `git rm readme.txt`
3. `git commit -m" remove readme.txt "`

  可用命令`git reset --hard HAED^`恢复文件( 回到哪个头要看情况,如果当前分支内有这个文件,那就可以回到当前版本,不用去上个版本)



`rm`是DOS命令,在各个shell都可以用. 用在git仓库中,是删除工作区的文件,用 `git restore readme.txt`可以还原. 而`git rm readme.txt`是删除工作区和暂存区的文件, **由于`git restore`的原理是将工作复原为暂存区中的版本**,而暂存区中该文件也被删除了,所以恢复不了, 分支里还有这个文件,所以用版本回退`git reset --hard HEAD^`

## git pull

1、将远程指定分支 拉取到 本地指定分支上：

```
git pull origin <远程分支名>:<本地分支名>
```

2、将远程指定分支 拉取到 本地当前分支上：

```
git pull origin <远程分支名>
```

3、将与本地当前分支同名的远程分支 拉取到 本地当前分支上(需先关联远程分支，方法见文章末尾)

```
git pull
```

在克隆远程项目的时候，本地分支会自动与远程仓库建立追踪关系，可以使用默认的origin来替代远程仓库名

### pull强制覆盖本地文件

ref： https://www.jianshu.com/p/1ac2e1f99166

> **重要提示：如果您有任何本地更改，将会丢失。无论是否有--hard选项，任何未被推送的本地提交都将丢失。**
>  如果您有任何未被Git跟踪的文件(例如上传的用户内容)，这些文件将不会受到影响。
>  下面是正确的方法：



```undefined
git fetch --all
```



然后，你有两个选择：

```undefined
git reset --hard origin/master
```

或者如果你在其他分支上：

```jsx
git reset --hard origin/<branch_name>
```



说明：

`git fetch`从远程下载最新的，而不尝试合并或rebase任何东西。

然后`git reset`将主分支重置为您刚刚获取的内容。 `--hard`选项更改工作树中的所有文件以匹配`origin/master`中的文件

在重置之前可以通过从master创建一个分支来维护当前的本地提交：



```cpp
git checkout master
git branch new-branch-to-save-current-commits
git fetch --all
git reset --hard origin/master
```

在此之后，所有旧的提交都将保存在new-branch-to-save-current-commits中。然而，没有提交的更改(即使staged)将会丢失。确保存储和提交任何你需要的东西。

## git push

1、将本地当前分支 推送到 **远程指定分支上**：

```
git push origin <本地分支名>:<远程分支名>
```

2、将本地当前分支 推送到 **与本地当前分支同名的远程分支**：

```
git push origin <本地分支名>
```

3、将本地当前分支 推送到 与本地当前分支同名的远程分支上(需先关联远程分支])

```
git push
```

### 修改commit信息

https://blog.csdn.net/Muscleape/article/details/105637401

## 远程仓库

### 添加远程库

把已有的本地仓库与一个git仓库相关联( 建立绑定关系 ):

`$ git remote add origin https://github.com/LYK-love/Learning`, 添加后,远程库的名字就是`origin`,这是Git默认的叫法,也可以改名,但没必要.

下一步,就可以把本地库的内容push到远程库上:

```
$ git push -u origin master
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (7/7), done.
Writing objects: 100% (7/7), 6.46 KiB | 6.46 MiB/s, done.
Total 7 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), done.
To https://github.com/LYK-love/Learning.git
 * [new branch]      master -> master
Branch 'master' set up to track remote branch 'master' from 'origin'.
```

把本地库内容推送到远程,用`git push`命令,实际上是把当前分支`master`(本地的那个)推送到远程库(名叫`origin`).

由于远程库是空的,我们第一次推送`master`分支时,加上了`-u`参数. Git不但会把本地的`master`分支内容推送到远程新的`master`分支( 现在远程也有一个叫`master`的分支了),还会把本地的`master`分支和远程的`master`分支关联起来,这样在以后的oush或oull时就可以简化命令.

从现在起,只要在本地作了`git commit`,就可以通过命令`git push origin`把本地的`master`分支的最新修改推送到Github,大功告成!

### 删除远程库

如果添加远程库的时候地址写错了,或者就是想删除远程库,可以用`git remote rm <name>`命令. 使用前建议先用`git remote -v`查看远程库信息:

```
$ git remote -v
origin  https://github.com/LYK-love/Learning.git (fetch)
origin  https://github.com/LYK-love/Learning.git (push)
```

然后,根据名字删除.

**注意**:

* 此处的*"删除"*其实是解除了本地和远程库的绑定关系,并没有物理上删除远程库,远程库本身没有任何改动( 也就是说远程库里的内容都还在 )要恢复绑定关系,可以再次用`$ git remote add origin https://github.com/LYK-love/Learning` , 然后用`$ git push -u origin master`来推送( `-u`参数能关联分支 )
* `origin`就是你指向的远程库的名字,可以等价于`https://github.com/LYK-love/Learning`,它指向的是repository, 而master只是这个repository中默认创建的第一个branch. 当我们`push`的时候,因为`origin`和`master`是默认创建的,所以这二者可以省略,但这是个bad practice,因为如果我换一个branch再push的时候,这样就很纠结了. 
* 当然`origin`这个名字来源于`$ git remote add origin https://github.com/LYK-love/Learning`,我们也可以把`origin`改成别的名字,比如阿猫阿狗,如 `$ git remote add aMao https://github.com/LYK-love/Learning`,那么推送的时候就可以用`git push -u aMao master`了, 如果你的本地版本库是从远程仓库git clone而来，git会默认把这个远程仓库的地址叫做origin. 这时候依旧可以通过 git remote add 把远程仓库的名称改成'aGou'

### 从远程库clone

随便哪个本地仓库,都可以用`$ git clone git@github.com:LYK-love/Learning.git`来clone. Github给出的地址不止一个,还可以用`https://github.com/LYK-love/Learning`. 实际上Git支持多种协议,默认的`git://`使用`ssh`( Secure Shell,安全外壳协议),但也可以使用`http`等其他协议. 使用`https`除了**速度慢**以外，还有个最大的麻烦是每次推送都必须输入口令，但是在某些只开放http端口的公司内部就无法使用`ssh`协议而只能用`https`。

**补充**: SSH

* Intro:

  SSH 为 [Secure Shell](https://baike.baidu.com/item/Secure Shell) 的缩写，由 IETF 的网络小组（Network Working Group）所制定；SSH 为建立在应用层基础上的安全协议。SSH 是较可靠，专为[远程登录](https://baike.baidu.com/item/远程登录/1071998)会话和其他网络服务提供安全性的协议。利用 SSH 协议可以有效防止远程管理过程中的信息泄露问题。

* 功能:

  传统的网络服务程序，如：ftp、pop和telnet在本质上都是不安全的，因为它们在网络上用明文传送口令和数据，别有用心的人非常容易就可以截获这些口令和数据。而且，这些服务程序的安全验证方式也是有其弱点的， 就是很容易受到“**中间人**”（man-in-the-middle）这种方式的攻击。所谓“中间人”的攻击方式， 就是“中间人”冒充真正的服务器接收你传给服务器的数据，然后再冒充你把数据传给真正的服务器。服务器和你之间的数据传送被“中间人”一转手做了手脚之后，就会出现很严重的问题。通过使用SSH，你可以把所有传输的数据进行加密，这样"中间人"这种攻击方式就不可能实现了，而且也能够防止DNS欺骗和IP欺骗。使用SSH，还有一个额外的好处就是传输的数据是经过压缩的，所以可以加快传输的速度。SSH有很多功能，它既可以代替Telnet，又可以为FTP、PoP、甚至为PPP提供一个安全的"通道" 。

* 验证:

  从客户端来看，SSH提供两种级别的安全验证。

  **第一种级别（基于口令的安全验证）**

  只要你知道自己帐号和口令，就可以登录到远程主机。所有传输的数据都会被加密，但是不能保证你正在连接的服务器就是你想连接的[服务器](https://baike.baidu.com/item/服务器)。可能会有别的服务器在冒充真正的服务器，也就是受到“中间人”这种方式的攻击。

  **第二种级别（基于密匙的安全验证）**

  需要依靠[密匙](https://baike.baidu.com/item/密匙)，也就是你必须为自己创建一对密匙，并把公用密匙放在需要访问的服务器上。如果你要连接到SSH服务器上，客户端软件就会向服务器发出请求，请求用你的密匙进行安全验证。服务器收到请求之后，先在该服务器上你的主目录下寻找你的公用密匙，然后把它和你发送过来的公用密匙进行比较。如果两个密匙一致，服务器就用公用密匙加密“**质询**”（challenge）并把它发送给客户端软件。客户端软件收到“质询”之后就可以用你的 **私人密匙** *解密再把它发送给服务器*。

  用这种方式，你必须知道自己密匙的[口令](https://baike.baidu.com/item/口令)。但是，与第一种级别相比，第二种级别不需要在网络上传送口令。

  第二种级别不仅加密所有传送的数据，而且“中间人”这种攻击方式也是不可能的（因为他没有你的私人密匙）。但是整个登录的过程可能需要10秒  。

# Branch

## 创建分支

创建`dev`分支, 然后切换到`dev`分支：

```Git
$ git switch -c dev 
Switched to a new branch 'dev'
```

## 切换分支

```
git switch dev 
```



## 查看分支

查看当前分支：

```
$ git branch
* dev
  master
```



## 关联分支

将本地分支与远程同名分支相关联

```
git branch --set-upstream-to=origin/develop develop
```



也可以在push时设置:

```she l
git push --set-upstream origin <本地分支名>

# 简写方式： 
# git push -u origin <本地分支名>
```

pull和push同.

## 创建与合并分支

`HEAD`严格来说不是指向提交，而是指向`master`，`master`才是指向提交的，所以，`HEAD`指向的就是当前分支。

* 首先，我们创建`dev`分支，然后切换到`dev`分支：

  
  
* 然后，用`git branch`命令查看当前分支：




* 然后提交:

  ```
  $ git add readme.txt 
  $ git commit -m "branch test"
  [dev b17d20e] branch test
   1 file changed, 1 insertion(+)
  ```

* 现在，`dev`分支的工作完成，我们就可以切换回`master`分支：

  ```
  $ git switch master
  Switched to branch 'master'
  ```

切换回`master`分支后，再查看一个`readme.txt`文件，刚才添加的内容不见了！( 工作区的不见了!!!  )因为那个提交是在`dev`分支上，而`master`分支此刻的提交点并没有变：

  ![git-br-on-master](https://www.liaoxuefeng.com/files/attachments/919022533080576/0)

* 现在，我们把`dev`分支的工作成果合并到`master`分支上：

  ```
  $ git merge dev
  Updating d46f35e..b17d20e
  Fast-forward
   readme.txt | 1 +
   1 file changed, 1 insertion(+)
  ```

  

* `git merge`命令用于合并指定分支到当前分支。合并后，再查看`readme.txt`的内容(工作区)，就可以看到，和`dev`分支的最新提交是完全一样的。

注意到上面的`Fast-forward`信息，Git告诉我们，这次合并是“快进模式”，也就是直接把`master`指向`dev`的当前提交，所以合并速度非常快。

当然，也不是每次合并都能`Fast-forward`，我们后面会讲其他方式的合并。

合并完成后，就可以放心地删除`dev`分支了：

```
$ git branch -d dev
Deleted branch dev (was b17d20e).
```

删除后，查看`branch`，就只剩下`master`分支了：

```
$ git branch
* master
```

因为创建、合并和删除分支非常快，所以Git鼓励你使用分支完成某个任务，合并后再删掉分支，这和直接在`master`分支上工作效果是一样的，但过程更安全。

* 查看分支：`git branch`

* 创建分支：`git branch <name>`

* 切换分支：`git checkout <name>`或者`git switch <name>`

* 创建+切换分支：`git checkout -b <name>`或者`git switch -c <name>`

* 合并某分支到当前分支：`git merge <name>`

* 删除分支：`git branch -d <name>`

## 查看远程分支

查看远程与本地当前分支对应的分支：

```shell
git branch -vv
```



查看本地和远程所有分支

```shell
git branch -a
```

### 解决冲突



如果`master`分支和`feature1`分支各自都分别有新的提交，变成了这样：

![git-br-feature1](https://www.liaoxuefeng.com/files/attachments/919023000423040/0)

这种情况下，Git无法执行“快速合并”，只能试图把各自的修改合并起来，但这种合并就可能会有冲突，我们试试看：

```
$ git merge feature1
Auto-merging readme.txt
CONFLICT (content): Merge conflict in readme.txt
Automatic merge failed; fix conflicts and then commit the result.
```

果然冲突了！Git告诉我们，`readme.txt`文件存在冲突，必须手动解决冲突后再提交。`git status`也可以告诉我们冲突的文件：

```
$ git status
On branch master
Your branch is ahead of 'origin/master' by 2 commits.
  (use "git push" to publish your local commits)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)

	both modified:   readme.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

打开工作区的`readme.txt`,我们可以直接查看readme.txt的内容：

```
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
Git tracks changes of files.
<<<<<<< HEAD
Creating a new branch is quick & simple.
=======
Creating a new branch is quick AND simple.
>>>>>>> feature1
```

Git用`<<<<<<<`，`=======`，`>>>>>>>`标记出不同分支的内容，我们修改如下后保存：

```
Creating a new branch is quick and simple.
```

再提交：

```
$ git add readme.txt 
$ git commit -m "conflict fixed"
[master cf810e4] conflict fixed
```

现在，`master`分支和`feature1`分支变成了下图所示：

![git-br-conflict-merged](https://www.liaoxuefeng.com/files/attachments/919023031831104/0)

用带参数的`git log`也可以看到分支的合并情况：

```
$ git log --graph --pretty=oneline --abbrev-commit
*   cf810e4 (HEAD -> master) conflict fixed
|\  
| * 14096d0 (feature1) AND simple
* | 5dc6824 & simple
|/  
* b17d20e branch test
* d46f35e (origin/master) remove test.txt
* b84166e add test.txt
* 519219b git tracks changes
* e43a48b understand how stage works
* 1094adb append GPL
* e475afc add distributed
* eaadf4e wrote a readme file
```

最后，删除`feature1`分支：

```
$ git branch -d feature1
Deleted branch feature1 (was 14096d0).
```

工作完成。

* 当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。

  解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。

  用`git log --graph`命令可以看到分支合并图。

### 分支管理策略

通常，合并分支时，如果可能，Git会用`Fast forward`模式，但这种模式下，删除分支后，会丢掉分支信息。

如果要强制禁用`Fast forward`模式，Git就会在merge时生成一个新的commit，这样，从分支历史上就可以看出分支信息。

下面我们实战一下`--no-ff`方式的`git merge`：

首先，仍然创建并切换`dev`分支：

```
$ git switch -c dev
Switched to a new branch 'dev'
```

修改readme.txt文件，并提交一个新的commit：

```
$ git add readme.txt 
$ git commit -m "add merge"
[dev f52c633] add merge
 1 file changed, 1 insertion(+)
```

现在，我们切换回`master`：

```
$ git switch master
Switched to branch 'master'
```

准备合并`dev`分支，请注意`--no-ff`参数，表示禁用`Fast forward`：

```
$ git merge --no-ff -m "merge with no-ff" dev
Merge made by the 'recursive' strategy.
 readme.txt | 1 +
 1 file changed, 1 insertion(+)
```

因为本次合并要创建一个新的commit，所以加上`-m`参数，把commit描述写进去。

合并后，我们用`git log`看看分支历史：

```
$ git log --graph --pretty=oneline --abbrev-commit
*   e1e9c68 (HEAD -> master) merge with no-ff
|\  
| * f52c633 (dev) add merge
|/  
*   cf810e4 conflict fixed
...
```

可以看到，不使用`Fast forward`模式，merge后就像这样：

![git-no-ff-mode](https://www.liaoxuefeng.com/files/attachments/919023225142304/0)

* 不用`Fast forwa`模式,提交图就像是 `dev`分支上做提交, `master`分支上做提交, 然后在`master`分支上手动解决冲突再提交 的图一样!.
* 合并分支时，加上`--no-ff`参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并。
* 如果之前`master`和`dev`只想相同提交. 现在你在`master`分支, 对 `readme.txt`做了修改, 然后`switch`到了`dev`分支, `add`, `commit`, 现在`dev`指向新的提交了! 我们`switch`回到`master`分支, 打开`readme.txt`,发现里面的内容是没有修改过的, 这是因为**分支是指向提交的**, 尽管你在`master`分支做了修改,但没有提交, 提交是在`dev`分支上完成的. 因此`master`分支指向的是上一次提交, 也就是没有修改过的版本.

### Bug分支

软件开发中，bug就像家常便饭一样。有了bug就需要修复，在Git中，由于分支是如此的强大，所以，每个bug都可以通过一个新的临时分支来修复，修复后，合并分支，然后将临时分支删除。

当你接到一个修复一个代号101的bug的任务时，很自然地，你想创建一个分支`issue-101`来修复它，但是，等等，当前正在`dev`上进行的工作还没有提交：

```
$ git status
On branch dev
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   hello.py

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   readme.txt
```

并不是你不想提交，而是工作只进行到一半，还没法提交，预计完成还需1天时间。但是，必须在两个小时内修复该bug，怎么办？

幸好，Git还提供了一个`stash`功能，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作：

```
$ git stash
Saved working directory and index state WIP on dev: f52c633 add merge
```

现在，用`git status`查看工作区，就是干净的（除非有没有被Git管理的文件），因此可以放心地创建分支来修复bug。

首先确定要在哪个分支上修复bug，假定需要在`master`分支上修复，就从`master`创建临时分支：

```
$ git checkout master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 6 commits.
  (use "git push" to publish your local commits)

$ git checkout -b issue-101
Switched to a new branch 'issue-101'
```

现在修复bug，需要把“Git is free software ...”改为“Git is a free software ...”，然后提交：

```
$ git add readme.txt 
$ git commit -m "fix bug 101"
[issue-101 4c805e2] fix bug 101
 1 file changed, 1 insertion(+), 1 deletion(-)
```

修复完成后，切换到`master`分支，并完成合并，最后删除`issue-101`分支：

```
$ git switch master
Switched to branch 'master'
Your branch is ahead of 'origin/master' by 6 commits.
  (use "git push" to publish your local commits)

$ git merge --no-ff -m "merged bug fix 101" issue-101
Merge made by the 'recursive' strategy.
 readme.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

太棒了，原计划两个小时的bug修复只花了5分钟！现在，是时候接着回到`dev`分支干活了！

```
$ git switch dev
Switched to branch 'dev'

$ git status
On branch dev
nothing to commit, working tree clean
```

工作区是干净的，刚才的工作现场存到哪去了？用`git stash list`命令看看：

```
$ git stash list
stash@{0}: WIP on dev: f52c633 add merge
```

工作现场还在，Git把stash内容存在某个地方了，但是需要恢复一下，有两个办法：

一是用`git stash apply`恢复，但是恢复后，stash内容并不删除，你需要用`git stash drop`来删除；

另一种方式是用`git stash pop`，恢复的同时把stash内容也删了：

```
$ git stash pop
On branch dev
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   hello.py

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   readme.txt

Dropped refs/stash@{0} (5d677e2ee266f39ea296182fb2354265b91b3b2a)
```

再用`git stash list`查看，就看不到任何stash内容了：

```
$ git stash list
```

你可以多次stash，恢复的时候，先用`git stash list`查看，然后恢复指定的stash，用命令：

```
$ git stash apply stash@{0}
```



在master分支上修复了bug后，我们要想一想，dev分支是早期从master分支分出来的，所以，这个bug其实在当前dev分支上也存在。

那怎么在dev分支上修复同样的bug？重复操作一次，提交不就行了？

有木有更简单的方法？

有！

同样的bug，要在dev上修复，我们只需要把`4c805e2 fix bug 101`这个提交所做的修改“复制”到dev分支。注意：我们只想复制`4c805e2 fix bug 101`这个提交所做的修改，并不是把整个master分支merge过来。

为了方便操作，Git专门提供了一个`cherry-pick`命令，让我们能复制一个特定的提交到当前分支：

```
$ git branch
* dev
  master
$ git cherry-pick 4c805e2
[master 1d4b803] fix bug 101
 1 file changed, 1 insertion(+), 1 deletion(-)
```

Git自动给dev分支做了一次提交，注意这次提交的commit是`1d4b803`，它并不同于master的`4c805e2`，因为这两个commit只是改动相同，但确实是两个不同的commit。用`git cherry-pick`，我们就不需要在dev分支上手动再把修bug的过程重复一遍。

* 修复bug时，我们会通过创建新的bug分支进行修复，然后合并，最后删除；

* 当手头工作没有完成时，先把工作现场`git stash`一下，然后去修复bug，修复后，再`git stash pop`，回到工作现场；

* 在master分支上修复的bug，想要合并到当前dev分支，可以用`git cherry-pick <commit>`命令，把bug提交的修改“复制”到当前分支，避免重复劳动。

### Feature分支

软件开发中，总有无穷无尽的新的功能要不断添加进来。

添加一个新功能时，你肯定不希望因为一些实验性质的代码，把主分支搞乱了，所以，每添加一个新功能，最好新建一个feature分支，在上面开发，完成后，合并，最后，删除该feature分支。

现在，你终于接到了一个新任务：开发代号为Vulcan的新功能，该功能计划用于下一代星际飞船。

于是准备开发：

```
$ git switch -c feature-vulcan
Switched to a new branch 'feature-vulcan'
```

5分钟后，开发完毕：

```
$ git add vulcan.py

$ git status
On branch feature-vulcan
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   vulcan.py

$ git commit -m "add feature vulcan"
[feature-vulcan 287773e] add feature vulcan
 1 file changed, 2 insertions(+)
 create mode 100644 vulcan.py
```

切回`dev`，准备合并：

```
$ git switch dev
```

一切顺利的话，feature分支和bug分支是类似的，合并，然后删除。

但是！

就在此时，接到上级命令，因经费不足，新功能必须取消！

虽然白干了，但是这个包含机密资料的分支还是必须就地销毁：

```
$ git branch -d feature-vulcan
error: The branch 'feature-vulcan' is not fully merged.
If you are sure you want to delete it, run 'git branch -D feature-vulcan'.
```

销毁失败。Git友情提醒，`feature-vulcan`分支还没有被合并，如果删除，将丢失掉修改，如果要强行删除，需要使用大写的`-D`参数。。

现在我们强行删除：

```
$ git branch -D feature-vulcan
Deleted branch feature-vulcan (was 287773e).
```

终于删除成功！

* 开发一个新feature，最好新建一个分支；
* 如果要丢弃一个没有被合并过的分支，可以通过`git branch -D <name>`强行删除。

### 多人协作

- `master`分支是主分支，因此要时刻与远程同步；
- `dev`分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步；
- bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug；
- feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发。



1. 首先，可以试图用`git push origin <branch-name>`推送自己的修改；
2. 如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并；
3. 如果合并有冲突，则解决冲突，并在本地提交；
4. 没有冲突或者解决掉冲突后，再用`git push origin <branch-name>`推送就能成功



- 查看远程库信息，使用`git remote -v`；
  *  比` git  remote`更详细
  * 上面显示了可以抓取和推送的`origin`的地址。如果没有推送权限，就看不到push的地址。
- 本地新建的分支如果不推送到远程，对其他人就是不可见的；
- 从本地推送分支，使用`git push origin branch-name`，如果推送失败，先用`git pull`抓取远程的新提交；
- 在本地创建和远程分支对应的分支并关联起来（ 就是说不用 `set-upstream` ），使用`git switch -c  branch-name origin/branch-name`，本地和远程分支的名称最好一致.
- 建立本地分支和远程分支的关联，使用`git branch --set-upstream branch-name origin/branch-name`；
- 从远程抓取分支，使用`git pull`，如果有冲突，要先处理冲突。

### Rebase

在上一节我们看到了，多人在同一个分支上协作时，很容易出现冲突。即使没有冲突，后push的童鞋不得不先pull，在本地合并，然后才能push成功。

每次合并再push后，分支变成了这样：

```
$ git log --graph --pretty=oneline --abbrev-commit
* d1be385 (HEAD -> master, origin/master) init hello
*   e5e69f1 Merge branch 'dev'
|\  
| *   57c53ab (origin/dev, dev) fix env conflict
| |\  
| | * 7a5e5dd add env
| * | 7bd91f1 add new env
| |/  
* |   12a631b merged bug fix 101
|\ \  
| * | 4c805e2 fix bug 101
|/ /  
* |   e1e9c68 merge with no-ff
|\ \  
| |/  
| * f52c633 add merge
|/  
*   cf810e4 conflict fixed
```

总之看上去很乱，有强迫症的童鞋会问：为什么Git的提交历史不能是一条干净的直线？

其实是可以做到的！

Git有一种称为rebase的操作.

同步后，我们对`hello.py`这个文件做了两次提交。用`git log`命令看看：

```
$ git log --graph --pretty=oneline --abbrev-commit
* 582d922 (HEAD -> master) add author
* 8875536 add comment
* d1be385 (origin/master) init hello
*   e5e69f1 Merge branch 'dev'
|\  
| *   57c53ab (origin/dev, dev) fix env conflict
| |\  
| | * 7a5e5dd add env
| * | 7bd91f1 add new env
...
```

注意到Git用`(HEAD -> master)`和`(origin/master)`标识出当前分支的HEAD和远程origin的位置分别是`582d922 add author`和`d1be385 init hello`，本地分支比远程分支快两个提交。

现在我们尝试推送本地分支：

```
$ git push origin master
To github.com:michaelliao/learngit.git
 ! [rejected]        master -> master (fetch first)
error: failed to push some refs to 'git@github.com:michaelliao/learngit.git'
hint: Updates were rejected because the remote contains work that you do
hint: not have locally. This is usually caused by another repository pushing
hint: to the same ref. You may want to first integrate the remote changes
hint: (e.g., 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

很不幸，失败了，这说明有人先于我们推送了远程分支。按照经验，先pull一下：

```
$ git pull
remote: Counting objects: 3, done.
remote: Compressing objects: 100% (1/1), done.
remote: Total 3 (delta 1), reused 3 (delta 1), pack-reused 0
Unpacking objects: 100% (3/3), done.
From github.com:michaelliao/learngit
   d1be385..f005ed4  master     -> origin/master
 * [new tag]         v1.0       -> v1.0
Auto-merging hello.py
Merge made by the 'recursive' strategy.
 hello.py | 1 +
 1 file changed, 1 insertion(+)
```

再用`git status`看看状态：

```
$ git status
On branch master
Your branch is ahead of 'origin/master' by 3 commits.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
```

加上刚才合并的提交，现在我们本地分支比远程分支超前3个提交。

用`git log`看看：

```
$ git log --graph --pretty=oneline --abbrev-commit
*   e0ea545 (HEAD -> master) Merge branch 'master' of github.com:michaelliao/learngit
|\  
| * f005ed4 (origin/master) set exit=1
* | 582d922 add author
* | 8875536 add comment
|/  
* d1be385 init hello
...
```

对强迫症童鞋来说，现在事情有点不对头，提交历史分叉了。如果现在把本地分支push到远程，有没有问题？

有！

什么问题？

不好看！

有没有解决方法？

有！

这个时候，rebase就派上了用场。我们输入命令`git rebase`试试：

```
$ git rebase
First, rewinding head to replay your work on top of it...
Applying: add comment
Using index info to reconstruct a base tree...
M	hello.py
Falling back to patching base and 3-way merge...
Auto-merging hello.py
Applying: add author
Using index info to reconstruct a base tree...
M	hello.py
Falling back to patching base and 3-way merge...
Auto-merging hello.py
```

输出了一大堆操作，到底是啥效果？再用`git log`看看：

```
$ git log --graph --pretty=oneline --abbrev-commit
* 7e61ed4 (HEAD -> master) add author
* 3611cfe add comment
* f005ed4 (origin/master) set exit=1
* d1be385 init hello
...
```

原本分叉的提交现在变成一条直线了！这种神奇的操作是怎么实现的？其实原理非常简单。我们注意观察，发现Git把我们本地的提交“挪动”了位置，放到了`f005ed4 (origin/master) set exit=1`之后，这样，整个提交历史就成了一条直线。rebase操作前后，最终的提交内容是一致的，但是，我们本地的commit修改内容已经变化了，它们的修改不再基于`d1be385 init hello`，而是基于`f005ed4 (origin/master) set exit=1`，但最后的提交`7e61ed4`内容是一致的。

这就是rebase操作的特点：把分叉的提交历史“整理”成一条直线，看上去更直观。缺点是本地的分叉提交已经被修改过了。

最后，通过push操作把本地分支推送到远程：

```
Mac:~/learngit michael$ git push origin master
Counting objects: 6, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (5/5), done.
Writing objects: 100% (6/6), 576 bytes | 576.00 KiB/s, done.
Total 6 (delta 2), reused 0 (delta 0)
remote: Resolving deltas: 100% (2/2), completed with 1 local object.
To github.com:michaelliao/learngit.git
   f005ed4..7e61ed4  master -> master
```

再用`git log`看看效果：

```
$ git log --graph --pretty=oneline --abbrev-commit
* 7e61ed4 (HEAD -> master, origin/master) add author
* 3611cfe add comment
* f005ed4 set exit=1
* d1be385 init hello
...
```

远程分支的提交历史也是一条直线。

- rebase操作可以把本地未push的分叉提交历史整理成直线；
- rebase的目的是使得我们在查看历史提交的变化时更容易，因为分叉的提交需要三方对比。

# 标签管理

***

发布一个版本时，我们通常先在版本库中打一个标签（tag），这样，就唯一确定了打标签时刻的版本。将来无论什么时候，取某个标签的版本，就是把那个打标签的时刻的历史版本取出来。所以，标签也是版本库的一个快照。

Git的标签虽然是版本库的快照，但其实它就是指向某个commit的指针（跟分支很像对不对？但是分支可以移动，标签不能移动），所以，创建和删除标签都是瞬间完成的。

Git有commit，为什么还要引入tag？

“请把上周一的那个版本打包发布，commit号是6a5819e...”

“一串乱七八糟的数字不好找！”

如果换一个办法：

“请把上周一的那个版本打包发布，版本号是v1.2”

“好的，按照tag v1.2查找commit就行！”

所以，tag就是一个让人容易记住的有意义的名字，它跟某个commit绑在一起。

## 创建标签

在Git中打标签非常简单，首先，切换到需要打标签的分支上：

```
$ git branch
* dev
  master
$ git checkout master
Switched to branch 'master'
```

然后，敲命令`git tag <name>`就可以打一个新标签：

```
$ git tag v1.0
```

可以用命令`git tag`查看所有标签：

```
$ git tag
v1.0
```

默认标签是打在最新提交的commit上的。有时候，如果忘了打标签，比如，现在已经是周五了，但应该在周一打的标签没有打，怎么办？

方法是找到历史提交的commit id，然后打上就可以了：

```
$ git log --pretty=oneline --abbrev-commit
12a631b (HEAD -> master, tag: v1.0, origin/master) merged bug fix 101
4c805e2 fix bug 101
e1e9c68 merge with no-ff
f52c633 add merge
cf810e4 conflict fixed
5dc6824 & simple
14096d0 AND simple
b17d20e branch test
d46f35e remove test.txt
b84166e add test.txt
519219b git tracks changes
e43a48b understand how stage works
1094adb append GPL
e475afc add distributed
eaadf4e wrote a readme file
```

比方说要对`add merge`这次提交打标签，它对应的commit id是`f52c633`，敲入命令：

```
$ git tag v0.9 f52c633
```

再用命令`git tag`查看标签：

```
$ git tag
v0.9
v1.0
```

注意，标签不是按时间顺序列出，而是按字母排序的。可以用`git show <tagname>`查看标签信息：

```
$ git show v0.9
commit f52c63349bc3c1593499807e5c8e972b82c8f286 (tag: v0.9)
Author: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 21:56:54 2018 +0800

    add merge

diff --git a/readme.txt b/readme.txt
...
```

可以看到，`v0.9`确实打在`add merge`这次提交上。

还可以创建带有说明的标签，用`-a`指定标签名，`-m`指定说明文字：

```
$ git tag -a v0.1 -m "version 0.1 released" 1094adb
```

用命令`git show <tagname>`可以看到说明文字：

```
$ git show v0.1
tag v0.1
Tagger: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 22:48:43 2018 +0800

version 0.1 released

commit 1094adb7b9b3807259d8cb349e7df1d4d6477073 (tag: v0.1)
Author: Michael Liao <askxuefeng@gmail.com>
Date:   Fri May 18 21:06:15 2018 +0800

    append GPL

diff --git a/readme.txt b/readme.txt
...
```

## 操作标签

如果标签打错了，也可以删除：

```
$ git tag -d v0.1
Deleted tag 'v0.1' (was f15b0dd)
```

因为创建的标签都只存储在本地，不会自动推送到远程。所以，打错的标签可以在本地安全删除。

如果要推送某个标签到远程，使用命令`git push origin <tagname>`：

```
$ git push origin v1.0
Total 0 (delta 0), reused 0 (delta 0)
To github.com:michaelliao/learngit.git
 * [new tag]         v1.0 -> v1.0
```

或者，一次性推送全部尚未推送到远程的本地标签：

```
$ git push origin --tags
Total 0 (delta 0), reused 0 (delta 0)
To github.com:michaelliao/learngit.git
 * [new tag]         v0.9 -> v0.9
```

如果标签已经推送到远程，要删除远程标签就麻烦一点，先从本地删除：

```
$ git tag -d v0.9
Deleted tag 'v0.9' (was f52c633)
```

然后，从远程删除。删除命令也是push，但是格式如下：

```
$ git push origin :refs/tags/v0.9
To github.com:michaelliao/learngit.git
 - [deleted]         v0.9
```

要看看是否真的从远程库删除了标签，可以登陆GitHub查看。

- 命令`git push origin <tagname>`可以推送一个本地标签；
- 命令`git push origin --tags`可以推送全部未推送过的本地标签；
- 命令`git tag -d <tagname>`可以删除一个本地标签；
- 命令`git push origin :refs/tags/<tagname>`可以删除一个远程标签

# 自定义Git

## 忽略特殊文件

有些时候，你必须把某些文件放到Git工作目录中，但又不能提交它们，比如保存了数据库密码的配置文件啦，等等，每次`git status`都会显示`Untracked files ...`，有强迫症的童鞋心里肯定不爽。

好在Git考虑到了大家的感受，这个问题解决起来也很简单，在Git工作区的根目录下创建一个特殊的`.gitignore`文件，然后把要忽略的文件名填进去，Git就会自动忽略这些文件。

不需要从头写`.gitignore`文件，GitHub已经为我们准备了各种配置文件，只需要组合一下就可以使用了。所有配置文件可以直接在线浏览：https://github.com/github/gitignore

忽略文件的原则是：

1. 忽略操作系统自动生成的文件，比如缩略图等；
2. 忽略编译生成的中间文件、可执行文件等，也就是如果一个文件是通过另一个文件自动生成的，那自动生成的文件就没必要放进版本库，比如Java编译产生的`.class`文件；
3. 忽略你自己的带有敏感信息的配置文件，比如存放口令的配置文件。

举个例子：

假设你在Windows下进行Python开发，Windows会自动在有图片的目录下生成隐藏的缩略图文件，如果有自定义目录，目录下就会有`Desktop.ini`文件，因此你需要忽略Windows自动生成的垃圾文件：

```
# Windows:
Thumbs.db
ehthumbs.db
Desktop.ini
```

然后，继续忽略Python编译产生的`.pyc`、`.pyo`、`dist`等文件或目录：

```
# Python:
*.py[cod]
*.so
*.egg
*.egg-info
dist
build
```

加上你自己定义的文件，最终得到一个完整的`.gitignore`文件，内容如下：

```
# Windows:
Thumbs.db
ehthumbs.db
Desktop.ini

# Python:
*.py[cod]
*.so
*.egg
*.egg-info
dist
build

# My configurations:
db.ini
deploy_key_rsa
```

最后一步就是把`.gitignore`也提交到Git，就完成了！当然检验`.gitignore`的标准是`git status`命令是不是说`working directory clean`。

使用Windows的童鞋注意了，如果你在资源管理器里新建一个`.gitignore`文件，它会非常弱智地提示你必须输入文件名，但是在文本编辑器里“保存”或者“另存为”就可以把文件保存为`.gitignore`了。

有些时候，你想添加一个文件到Git，但发现添加不了，原因是这个文件被`.gitignore`忽略了：

```
$ git add App.class
The following paths are ignored by one of your .gitignore files:
App.class
Use -f if you really want to add them.
```

如果你确实想添加该文件，可以用`-f`强制添加到Git：

```
$ git add -f App.class
```

或者你发现，可能是`.gitignore`写得有问题，需要找出来到底哪个规则写错了，可以用`git check-ignore`命令检查：

```
$ git check-ignore -v App.class
.gitignore:3:*.class	App.class
```

Git会告诉我们，`.gitignore`的第3行规则忽略了该文件，于是我们就可以知道应该修订哪个规则。

还有些时候，当我们编写了规则排除了部分文件时：

```
# 排除所有.开头的隐藏文件:
.*
# 排除所有.class文件:
*.class
```

但是我们发现`.*`这个规则把`.gitignore`也排除了，并且`App.class`需要被添加到版本库，但是被`*.class`规则排除了。

虽然可以用`git add -f`强制添加进去，但有强迫症的童鞋还是希望不要破坏`.gitignore`规则，这个时候，可以添加两条例外规则：

```
# 排除所有.开头的隐藏文件:
.*
# 排除所有.class文件:
*.class

# 不排除.gitignore和App.class:
!.gitignore
!App.class
```

把指定文件排除在`.gitignore`规则外的写法就是`!`+文件名，所以，只需把例外文件添加进去即可。