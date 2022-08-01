---
title: Jenkins Tutorial
tags: CICD
categories: Toolkit
date: 2022-05-26 22:48:57
---




Outline:

* Jenkins
* SCM
* Access Token
* Credentials
* Webhook
* slave
* Jenkinsfile
* 日志

<!--more-->





# Jenkins

Jenkins是一个开源的CICD工具

## 安装

建议以容器形式安装并运行jenkins

容器形式运行jenkins，需要注意jenkins的数据持久化， jenkins的数据目录为`/var/jenkins_home` ， 需要将其挂载到宿主机的某个目录

注意，以容器形式运行的jenkins，其**主体是容器**，因此后续配置SSH 公钥，SSH私钥等等操作，都是对于Jenkins容器（而非宿主机）的。 甚至Jenkins容器对宿主机的ssh登陆也需要手动配置

1. pull镜像：

   ```
    docker pull jenkins/jenkins
   ```

2. 启动容器：

   ```shell
   docker run -d -uroot -p 8081:8080 -p 50000:50000 --name jenkins -v /home/jenkins_home:/var/jenkins_home -v /etc/localtime:/etc/localtime jenkins/jenkins
   
   参数说明：
   -d                 	 # -d:后台启动
   -u root              # 指定容器的用户
   --name jenkins       # 容器实例名
   --restart=always     # 容器随docker自启动，因为重启docker时，默认容器都会被关闭
   -p                   # -p host_port:container_port: 指定将主机的端口映射到容器的端口
   -v                   # 映射目录（给容器挂载存储卷）
   -e                   # 指定环境变量
   
   注意：
   1. 将宿主机端口映射到容器端口，映射端口不要和宿主机冲突
   2. 将容器对应的数据目录映射到宿主机上（实现数据持久化）
   3. 将宿主机node、maven等前后台构建工具（环境变量）映射到容器中
   4. Jenkins镜像创建的容器自带Git工具（/usr/bin/git）
   5. Jenkins镜像创建的容器自带java环境（/usr/local/openjdk-8/bin/java）
   
   ```

   接下来就可以通过浏览器访问jenkins



## 登陆

密码保存在容器的`/var/jenkins_home/secrets/initialAdminPassword`中，如果忘记了登录密码，可以查看该文件

## 进入jenkins容器

```shell
docker container exec jenkins bash
```





# SCM

SCM就是Source Code Management， 即github， gitlab这样的代码托管平台， jenkins可以用git从SCM上clone代码，并进行构建

* jenkins要从SCM上clone代码，需要先在SCM上配置jenkins的ssh公钥
  * 注意，如果是以容器形式运行的jenkins，这个“公钥”也必须是jenkins容器而非宿主机的公钥

在job configuration页面，可以配置job的SCM， 由于Jenkins构建需要jenkinsfile， 因此还需要指定jenkinsfile在代码仓库中的位置（所在分支、脚本名等）

* Branches to build：即要clone的代码分支
* Script Path： jenkinsfile所在目录，包括其名字
  * jenkinsfile不一定名为`jenkinsfile`, 它可以自由命名， jenkins根据Script Path来找到jenkinsfile



Jenkins从SCM得到代码以及jenkins脚本后，就要根据脚本进行项目构建， 而项目构建不一定由jenkins主机来做。 jenkins采用master - slave模式， jenkins主机作为master，可以将代码和脚本交给slave，让脚本执行构建过程



注意： 

使用github作为SCM时， 如果`Branches to build` 设为空，则必须取消lightweight checkout，详见https://issues.jenkins.io/browse/JENKINS-46588

# Access Token

jenkins与SCM交互，需要配置对这些SCM的Access Token



1. 先在SCM生成Access Token

   * github: [在github生成Access Token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
   * gitlab: 登录GitLab -> 在用户头像下拉框，选择“Setting” -> 点击“Access Tokens”，输入“Name”和“Expires at”，勾选“api” -> 点击“Create personal access token”，生成access token，记录下此token

2. 在jenkins， 系统管理 -> Manage Credentials -> Stores scoped to Jenkins -> 添加该Token作为凭据

   * 类型选择Username and password
   * 在用户名中输入一个不存在的用户名
   * 密码填写Personal Access Token

3. 用该凭据来连接SCM:

   * github: “Manage Jenkins” -> "Configure System" -> GitHub， 使用刚才配置的Credential

     * github网址：https://api.github.com

   * gitlab: “Manage Jenkins” -> "Configure System" -> "GitLab"，使用刚才配置的Credential

     * Gitlab host URL：https://git.nju.edu.cn/

       我用的学校的gitlab， 所以用的是学校的gitlab的网址





# Credentials

Jenkins采用CS模式与其他服务通信（比如gitlab的webhook、 jenkins slave节点）， 通信的建立需要有**凭据（Credential）**

## 添加Credential

1. 进入`Manage Jenkins` --> `Manage Credentials` --> `Stores scoped to Jenkins` --> `Global Credentials(unrestricted)`, 点击`Add Credentials`

2. 根据不同的通信类型选择不同的凭据形式，并填写即可

3. 以ssh私钥连接（ 这意味着jenkins主机已经将ssh 公钥发送给了目标主机， 以后只需要私钥就可以登录目标主机 ）为例，需要填写:

   * Username: ssh连接采用的的用户名
   * Private Key：ssh连接所需的私钥

   

   

   

# webhook

> Webhooks are **event**s sent by a webhook provider to your app

jenkins + github配置 webhook教程：https://www.decodingdevops.com/configure-github-web-hook-for-jenkins/

jenkins + gitlab配置webhook很简单



jenkins可以暴露给github和gitlab等代码托管平台一个webhook url, 每当用户在代码托管平台触发某些事件时（比如进行了push，merge等），后者就可以给jenkins发送一个hook，让jenkins进行构建

* jenkins在收到SCM的hook后，会检查在jenkins上注册的SCM 仓库，如果发现某个仓库的信息和hook信息一致，jenkins的SCM插件（gitlab插件/github插件）就会去检查SCM上的仓库内容，如果该仓库内容有改动，就会发起一次build

  * 这意味着如果本次push没有对内容做更改，jenjins插件就不会检查出变动，也就不会发起构建。 对于用户来说，这意味着jenkins正常收到了hook消息，却一直无法触发构建，jenkins log中也查不到信息（GitHub Hook Log到了“Changes not found”就结束了，没有下文）， **需要在job的`Github Hook Log`页面查看信息**（该页面只有github插件有）

    

下面演示github的webhook配置过程：

1. 得到webhook url
   * 对于gitlab，jenkins在安装gitlab插件后，可以在job configuration页面的**Build Triggers ** 勾选： `Build when a change is pushed to GitLab. GitLab webhook URL ***`, 并复制webhook url
   * 对于github: 默认是`http://[jenkins-host-ip]:[port]/github-webhook/`， 也可以在配置页面override该url
2. 在gitlab/github 仓库的设置里面添加webhook
   * github： 填写**Payload URL**字段
3. 在Jenkins的 job configuration页面的 **Build Triggers** 勾选 **GitHub hook trigger for GITScm polling.**

Note: Jenkins默认暴露8080端口，与github通信，因此要确保8080端口开放，否则github发送的消息无法到达jenkins







# slave

jenkins是master-slave模式， jenkins自身只是指挥者， 它**根据jenkinsfile的内容选择slave**，指挥slave运行脚本

* 如果某台主机被设置为slave主机，jenkins会在其中安装一个agent程序。 如果jenkins选择该slave进行构建，则会ssh连接到该slave， 运行agent进程，并将代码和jenkinsfile发给它, 实现**通过slave构建**

  * agent程序用java编写，所以slave节点上**必须有jdk**, 否则无法安装agent程序，也就无法将其作为slave节点

    ```shell
    # 在slave节点上
    
    sudo apt-get install openjdk-8-jdk
    ```

  * BTW，由于jenkins一般配合docker，所以slave节点上还要安装docker

* 默认情况下，jenkins的slave只有一个，即jenkins自身（ 如果是容器形式的jenkins， 那就是jenkins容器作为slave ）。 可以在`Manage Jenkins` --> `Manage Nodes and Clouds`中查看和配置slave节点

  * 可以看到，容器和宿主机是两个独立的实体，jenkins容器的默认slave是自身容器。在Jenkins容器眼中，宿主机和其他机器一样，jenkins把宿主机和其他机器添加为slave的步骤都相同



## 添加slave

0. 由于我采用ssh方式连接到slave，jenkins主机需要先配置对slave节点的ssh免密登陆， 即把ssh **public key**发给slave节点：

   ```shell
   ssh-copy-id lyk@[slave-host]
   ```

​		然后在`Credentials`页面，设置一个Credential， 内容是 jenkins主机到该slave节点的ssh **private key**

1. 进入`Manage Jenkins` --> `Manage Nodes and Clouds` ， 进入添加节点页面，输入相应信息，最终进入节点的配置页面

2. 在节点配置页面填写信息：

   * **Labels**： **指定该slave的label, 在jenkinsfile中通过label来引用对应的slave**

   * **Remote root directory**: jenkins agent的根目录，agent会在**此目录下创建`workspace`目录，作为jenkins的工作目录**，也就是构建上下文

     这里将Remote root directory设为用户目录：

     ```
     /home/lyk
     ```

     * 这会**创建`/home/lyk/workspace`目录，后续的构建都在该目录下进行**

   * Launch method: jenkins master登录到slave节点的方法，只有先登录到主机，才能启动slave agent进程

     一般通过ssh：

     ```
     Launch agents via SSH
     ```

     接下来输入ssh登录到slave节点所需的信息：

     * Host： slave节点的ip
     * Credentials：之前设置好的Credential， 即jenkins主机到该slave的ssh公钥
     * Host Key Verification Strategy： Mannually trusted Key Verification Strategy

     

   注意： 

   主机要使用docker，需要把用户添加进docker群组，而这一步需要用户重新登陆才能生效。 但是，jenkins client是通过用户身份登陆的，而且应该是**永久**登陆，即使令节点"Disconnect"(在节点控制界面)， 依然不会断开登陆。

   也就是说，如果在配置好slave主机的docker之前（即将用户添加至docker群组并重新登录），就令主机成为slave节点，这就会导致jenkins agent使用不了docker，报错:

   ````
   Got permission denied while trying to connect to the Docker daemon socket
   ````

   解决方法是删除该节点，重新配置节点

   ## 

   

   





# Jenkinsfile

官网教程：https://www.jenkins.io/doc/book/pipeline/

jenkins根据jenkinsfile来进行构建，该文件有两种写法： `Declarative`和`pipeline script`，后者使用groovy语言，表达能力比较强，推荐使用

pipeline script由一个个stage组成，在每个stage内执行一些指令

## 选择slave

后面会看到，jenkins由slave来负责实际的构建过程，而slave就是根据jenkinsfile选择的:

```groovy
# 选择label为volatile-ai-slave的节点来构建此脚本
node("volatile-ai-slave") 
{
...
}
```





## workspace

jenkins会在配置slave时指定的`Remote root directory`下创建`workspace`目录,作为工作目录

* 可以在jenkinsfile中使用：

  ````
  def workspace = pwd()
  
  ...
  echo ${workspace}
  ````

  输出为`[Remote root directory]/workspace`

## example



```groovy
node("volatile-ai-slave") {
    def workspace = pwd()

    def git_branch = '**'
    def git_repository = '**'
    def vm_ip = '**'
    def vm_port = '**'
    def vm_user = '**'



    def IMAGE_NAME = 'volatile_ai'
    def IMAGE_NAME_WITH_TAG = 'volatile_ai:latest'
    def IMAGE_TO_RUN = 'lyklove/volatile_ai:latest'
    def CONTAINER_NAME = 'volatile_ai'

    stage('clone from gitlab into slave\'s workspace') {
        echo "workspace: ${workspace}"
        git branch: "${git_branch}", url: "${git_repository}"
    }


    stage('cd to build context') {
        echo "the context now is:"
        sh "ls -al"
        sh "cd ${workspace}"
        echo "cd to build context, now the context is:"
        sh "ls -al"

    }



    stage("build docker image"){
        sh "docker build -t ${IMAGE_NAME} ."
    }

//     stage("login to dockerhub"){
//         withCredentials([usernamePassword(credentialsId: 'DOCKERHUB_KEY', passwordVariable: 'password', usernameVariable: 'username')]) {
//             sh 'docker login -u $username -p $password'
//         }
//     }
//
    stage("push to dockerhub"){
//         echo "begin push to dockerhub"
        sh "docker image tag ${IMAGE_NAME_WITH_TAG} lyklove/${IMAGE_NAME_WITH_TAG}"
//         sh "docker image push lyklove/${IMAGE_NAME_WITH_TAG}"
    }
    stage("clean previous image and container"){
        sh "docker container rm -f ${CONTAINER_NAME}"
//         sh "docker image rm ${IMAGE_NAME_WITH_TAG}"
//         sh "docker image rm ${IMAGE_TO_RUN}"
    }
//     stage( "pull image" ){
//         sh "docker pull  lyklove/${IMAGE_NAME_WITH_TAG}"
//     }
    stage("run container") {
        sh "docker image ls"
        sh "docker container run --name ${CONTAINER_NAME} --net=host  -d ${IMAGE_TO_RUN}"
    }
    stage("signal gitlab: deployed"){
        updateGitlabCommitStatus name: 'deployed', state: 'success'
    }


}

```



# 日志

日志是最好的debug工具， jenkins日志位于：Dashboard -> System Log 
