---
ftitle: Go Basic
tags:
---



# Package



# Go Module

要启用go module支持首先要设置环境变量GO111MODULE，通过它可以开启或关闭模块支持，它有三个可选值：off、on、auto，默认值是auto。



1. GO111MODULE=off禁用模块支持，编译时会从GOPATH和vendor文件夹中查找包。
2. GO111MODULE=on启用模块支持，编译时会忽略GOPATH和vendor文件夹，只根据 go.mod下载依赖。
3. GO111MODULE=auto，当项目在$GOPATH/src外且项目根目录有go.mod文件时，开启模块支持。

通过以下命令修改:

```
go env -w GO111MODULE=on
```







使用go module模式新建项目时，我们需要通过go mod init 项目名命令对项目进行初始化，该命令会在项目根目录下生成go.mod文件。例如，我们使用hello作为我们第一个Go项目的名称，执行如下命令。

```
go mod init hello
```



go.mod 文件内提供了module, require、replace和exclude四个关键字

- `module`语句指定包的名字（路径）
- `require`语句指定的依赖项模块
- `replace`语句可以替换依赖项模块
- `exclude`语句可以忽略依赖项模块



2.在当前目录下，命令行运行 **go mod init + 模块名称** 来初始化模块

初始化之后，会在当前目录下生成一个go.mod文件，这是一个go用来管理包的关键文件

**注1:**为了确保一致性构建，Go引入了`go.mod`文件来标记每个依赖包的版本，在构建过程中`go`命令会下载`go.mod`中的依赖包，下载的依赖包会缓存在本地，以便下次构建。 考虑到下载的依赖包有可能是被黑客恶意篡改的，以及缓存在本地的依赖包也有被篡改的可能，单单一个`go.mod`文件并不能保证一致性构建。

为了解决Go module的这一安全隐患，Go开发团队在引入`go.mod`的同时也引入了`go.sum`文件，用于记录每个依赖包的哈希值，在构建时，如果本地的依赖包hash值与`go.sum`文件中记录得不一致，则会拒绝构建。

**注2:**go.sum 不需要手工维护，所以可以不用太关注。

**注3:**子目录里是不需要init的，所有的子目录里的依赖都会组织在根目录的go.mod文件里

**注4:**使用Go的包管理方式，依赖的第三方包被下载到了$GOPATH/pkg/mod路径下。

**注5:**版本是在go.mod中指定的。如果，在go.mod中没有指定，go命令会自动下载代码中的依赖的最新版本。如果，在go.mod用require语句指定包和版本 ，go命令会根据指定的路径和版本下载包，指定版本时可以用latest，这样它会自动下载指定包的最新版本；

**注6:** go mod init 模块名 生成的go.mod文件里的第一行会申明 module 模块名

3.4 go.mod 命令

- go mod download 下载模块到本地缓存，缓存路径是 $GOPATH/pkg/mod/cache
- go mod edit 是提供了命令版编辑 go.mod 的功能，例如 go mod edit -fmt go.mod 会格式化go.mod
- go mod graph 把模块之间的依赖图显示出来
- go mod init 初始化模块（例如把原本dep管理的依赖关系转换过来）
- go mod tidy 增加缺失的包，移除没用的包
- go mod vendor 把依赖拷贝到 vendor/ 目录下
- go mod verify 确认依赖关系
- go mod why 解释为什么需要包和模块

**附 : go 相关命令**

1. 指定module的根目录并生成go.mod文件

   ```bash
   go mod init example.com/hello
   复制代码
   ```

2. 下载并添加依赖到go.mod文件中

   ```go
   go build, go test
   复制代码
   ```

3. 查看module下的所有依赖

   ```css
   go list -m all
   复制代码
   ```

4. 更新稳定版依赖

   ```arduino
   go get rsc.io/sampler
   复制代码
   ```

5. 清理无用的依赖

   ```go
   go mod tidy
   复制代码
   ```

6. 将依赖复制到项目路径的vendor文件夹中

   ```go
   go mod vendor
   复制代码
   ```

7. 忽略cache里的包，只使用vendor目录里的依赖进行编译

   ```ini
   go build -mod=vendor
   复制代码
   ```

8. 校验依赖并查看是否有修改

   ```go
   go mod verify
   复制代码
   ```

**注1:**go mod 命令在 GOPATH里默认是执行不了的，因为GO111MODULE的默认值是auto。默认在GOPATH 里默认是执行不了的，因为 GO111MODULE 的默认值是 auto。默认在GOPATH里默认是执行不了的，因为GO111MODULE的默认值是auto。默认在GOPATH 里是不会执行， 如果一定要强制执行，就设置环境变量为 on。

**注2:**go mod init 在没有接module名字的时候是执行不了的，会报错 go: cannot determine module path for source directory。

# 







运行之前可以使用`go mod tidy`命令将所需依赖添加到go.mod文件中，并且能去掉项目中不需要的依赖





# Grammar

# Dependency Management

Go code is grouped into packages, and packages are grouped into modules. Your module specifies dependencies needed to run your code, including the Go version and the set of other modules it requires.



go.mod file : to track your code's dependencies:

Go模块都从https://pkg.go.dev/下载

* Enable dependency tracking, whcich means creating a go.mod file

  ```
   go mod init
  ```

  

* 下载依赖:

  ````
  go mod tidy
  ````



