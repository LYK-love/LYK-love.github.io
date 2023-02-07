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

建议[以容器形式安装并运行jenkins](https://www.jenkins.io/doc/book/installing/docker/)

容器形式运行jenkins，需要注意jenkins的数据持久化， jenkins的数据目录为`/var/jenkins_home` ， 需要将其挂载到宿主机的某个目录

注意，以容器形式运行的jenkins，其**主体是容器**，因此后续配置SSH 公钥，SSH私钥等等操作，都是对于Jenkins容器（而非宿主机）的。 甚至Jenkins容器对宿主机的ssh登陆也需要手动配置

1. pull镜像：

   ```sh
    docker pull jenkins/jenkins
   ```

2. 启动容器：

   ```shell
   docker run -d -uroot -p 8081:8080 -p 50000:50000 --name jenkins -v /home/jenkins_home:/var/jenkins_home -v /etc/localtime:/etc/localtime jenkins/jenkins
   
   参数说明：
   -d                 	 # -d:后台启动
   -u root              # 指定容器的用户
   --privileged				 # 	Running Docker in Docker currently requires privileged access to function properly. 
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



# Steps

## Create a Jenkins Item

1. 点击"New Item", 选择"Pipeline"形式
   * 因为我喜欢用pipeline script. 而Freestyle我还不会..
2. 进入Jenkins的 job configuration页面

## Configure the Hook Trigger

在**Build Triggers** 勾选:

* Github: **GitHub hook trigger for GITScm polling**
  * by selecting this trigger, this job will run whenever Jenkins receive git hub webhook request from git hub. Git hub webhook will send request according to your choices which you selected in “which events would you like to trigger this webhook” option in git hub webhooks.
    That’s all we have successfully configured git hub webhook for Jenkins.
* Gitlab:  **Build when a change is pushed to GitLab. GitLab webhook URL**
  * 这需要Jenkins安装gitlab插件





## Configure Webhook on Registry

> Webhooks are **event**s sent by a webhook provider to your app

jenkins + github配置 webhook教程：https://www.decodingdevops.com/configure-github-web-hook-for-jenkins/



jenkins可以暴露给github和gitlab等代码托管平台一个webhook url, 每当用户在代码托管平台触发某些事件时（比如进行了push，merge等），后者就可以给jenkins发送一个hook，让jenkins进行构建

* jenkins在收到SCM的hook后，会检查在jenkins上注册的SCM 仓库，如果发现某个仓库的信息和hook信息一致，jenkins的SCM插件（gitlab插件/github插件）就会去检查SCM上的仓库内容，如果该仓库内容有改动，就会发起一次build

  * 这意味着如果本次push没有对内容做更改，jenjins插件就不会检查出变动，也就不会发起构建。 对于用户来说，这意味着jenkins正常收到了hook消息，却一直无法触发构建，jenkins log中也查不到信息（GitHub Hook Log到了“Changes not found”就结束了，没有下文）， **需要在job的`Github Hook Log`页面查看信息**（该页面只有github插件有）
* Note: Jenkins默认暴露8080端口，与github通信，因此要确保8080端口开放，否则github发送的消息无法到达jenkins. 
  * 由于我设置了容器的端口映射, Jenkins容器的8080端口实际被映射到了宿主机的8081端口, 因此下文的Payload URL中的端口是8081

### Github

默认是`http://[jenkins-host-ip]:[port]/github-webhook/`, 也可以在配置页面override该url

先进入对应的仓库.

1. click on the **Settings** tab

2. then click **Webhooks** from the left panel. 

3. Now, click on the **Add webhook**  button at the right.  

4. 接下来你可以看到一个表单:

   1. **Payload URL** : `http://[jenkins-host-ip]:[port]/github-webhook/`, 最终的Payload URL形如:

      ```
      http://124.222.135.47:8081/github-webhook/
      ```

      * Jenkins域名必须是可被Github可访问到的, 所以一般都是公网IP
      * 也可以在配置页面override该url

   2. **Content type**:  pick **application/json** 

   3. Leave the rest of the options as they are, with the **Just the push event** option selected. For simplicity, I said before that GitHub would call Jenkins only when there’s a push in the repo. If you want to configure other actions, you’ll have to select **Let me select individual events**, but for now, let’s keep it simple. 

   4. Finally, click on the green **Add webhook** button.

5. 现在已经Webhook配置完毕了. 每当仓库被push, Github就会向设置好的Payload URL发送webhook

### Gitlab

jenkins + gitlab配置webhook很简单



1. 得到**Payload URL**: 之前在**Build Triggers ** 勾选**Build when a change is pushed to GitLab. GitLab webhook URL: [xxx] **时就可以得到Payload URL
   * 形如`https://JENKINS_URL/project/YOUR_JOB`
2. 复制Payload URL
3. 进入Gitlab对应仓库, 进入**Settings** -> **Webhooks**, 
   * **URL**: 填写 Payload URL
   * **Secret Token**: 可以不填. 配置步骤:
     1. In the configuration of your Jenkins job, in the GitLab configuration section, select **Advanced**.
     2. Under **Secret Token**, select **Generate**.
     3. 将生成的**Secret Token**粘贴到Gitlab的**Secret Token**
   * **Trigger**: 选择**Push events**
   * **SSL verification**: 可以勾上**Enable SSL verification**
4. Finally, click on the green **Add webhook** button.
5. To test the webhook, select **Test**.

## Use SCM

SCM就是Source Code Management， 即github/gitlab上的repository. jenkins可以用git从SCM上clone代码，并进行构建.

* jenkins需要SCM上clone Jenkinsfile,甚至有可能调用其他的API. 这就需要在Jenkins上[配置Credential](# Credentials)
  * 对于SSH Key而言, 需要先在对应的Registry上配置Jenkins endpoint的公钥
    * 注意, 由于容器和宿主机的公私钥不一样. 所以如果是以容器形式运行的jenkins, 这个“公钥”也必须是jenkins容器而非宿主机的公钥



我选择的Jenkinsfile形式是Pipeline, 且Jenkinsfile放在SCM中. 因此我在**Pipleline**区域设置:

1. **Definition**: **Pipeline script from SCM**

   * 这样Jenkins就会拉取SCM中的Jenkinsfile. 
   * 如果选择**Pipeline script**, 则会在Jenkins中设置Jenkinsfile, 这样太僵硬了

2. **Repositories**: 指定要clone的jenkinsfile的位置（ SCM地址, 所在分支, 脚本名 ）

   1. **Repository URL**: 使用HTTPS url和ssh url都可以
   2. **Credentials**: 指定Jenkins使用的私钥, 由于是容器形式的Jenkins ,就选择容器的私钥

3. **Branches to build**: 选择使用的分支, 我只用master分支

   * 注意： 

     使用github作为SCM时， 如果`Branches to build` 设为空，则必须取消lightweight checkout，详见https://issues.jenkins.io/browse/JENKINS-46588

4. **Script Path**: 指定SCM中的Jenkinsfile的名字

   * 注意要写全名. 比如我的脚本为: `Jenkinsfile-fast.groovy`, 则在该栏填这个名字

   









## Build Manually

Webhook会自动触发构建, 当然也可以手动构建:

1. click on the **Build Now** link 

# Access Token

jenkins与SCM交互，需要配置对这些SCM的Access Token



1. 先在SCM生成Access Token

   * github: [在github生成Access Token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
   * gitlab: 登录GitLab -> 在用户头像下拉框，选择“Setting” -> 点击“Access Tokens”，输入“Name”和“Expires at”，勾选“api” -> 点击“Create personal access token”，生成access token，记录下此token

2. 在jenkins， 系统管理 -> Manage Credentials -> Stores scoped to Jenkins -> 全局凭据 添加该Token作为凭据

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

https://www.jenkins.io/zh/doc/book/using/using-credentials/

https://blog.csdn.net/elva1087penny/article/details/115387664

Jenkins要调用其他服务的API, 这需要Credential( 凭据, 事实上就是一种密钥 ).

根据目标平台的不同, Jenkins可以使用SSH Key, Username and password, API Token 等形式的凭据

* Credential不仅可以用于免密登陆平台, 免密clone, 还可以调用平台的各种API



## Credential Type

Jenkins可以存储以下类型的credentials:

- **Secret text** - API token之类的token (如GitHub个人访问token)
- **Username and password** - 可以为独立的字段，也可以为冒号分隔的字符串：`username:password`(更多信息请参照 [处理 credentials](https://www.jenkins.io/zh/doc/book/pipeline/jenkinsfile#handling-credentials)),
- **Secret file** - 保存在文件中的加密内容
- **SSH Username with private key**: 需要jenkins终端已经将ssh 公钥发送给了目标主机,  以后只需要私钥就可以登录目标主机 )
  * Github和Gitlab都可以使用SSH Username with private key
- **Certificate** - a [PKCS#12 证书文件](https://tools.ietf.org/html/rfc7292) 和可选密码
- 此外, 通过安装第三方插件, 还可以使用别的类型的凭据:
  * **Docker Host Certificate Authentication** credentials: 需要安装Docker插件
  * **Gitlab API Token**: 同理, 使用API Token
    * 注意, Gitlab认证不仅需要配置Credential, 还需要额外的步骤, [参见下文](#Configure Access Token)
  * **Github App**: 同理, 但我不知道有什么用, 也不知道怎么用. Github认证我使用的是SSH Key

## Add Credential

需要**Credentials**插件

1. 进入`Manage Jenkins` --> `Manage Credentials` --> `Stores scoped to Jenkins` --> `Global Credentials(unrestricted)`, 点击`Add Credentials`
2. 填写表单:
   * **Type**: 根据不同的通信类型选择不同的凭据形式
   * **Scope**: 选择Global
   * **Description**: 可用于标记别名方便区别或记录凭据作用, 写上为妙
   * **ID**: Credential的唯一标识, 会显示在项目构建时的Credentials插件选项中.
     * 可自定义, 若为空则自动生成.

* 对于SSH Key, 需要填写( 前提是已经在Github上配置了Jenkins的公钥 ):
  * Username: ssh连接采用的的用户名
  * Private Key：ssh连接所需的私钥

## Use Credential



# API Token

API Token是一种用于认证的密钥, 其 作用SSH Key, Username and password 一样. 可以用API Token来访问平台提供的各种服务.

## Github

Github中的API Token称作“PAT”( Personal Access Token ).

Github的Credential支持SSH Key, 也支持PAT. 虽然我使用前者, 但用后者也是可行的

* Github API Token: 首先要[得到PAT](Get Get API Token), 然后将其[添加进Crendential](#Add Credential), 可以以两种Type添加
  *  **Username and password** : `Username` is the GitHub user ID and `Password` is the Password or a [personal API Token](https://github.com/blog/1509-personal-api-tokens) (recommended). 
    * However, [use of a password with the GitHub API is now **deprecated**](https://developer.github.com/changes/2020-02-14-deprecating-password-auth/).
  * **Secret Text**: 
    * Scope: Global
    * Secret: 填写之前生成的PAT
    * ID: 写一个名字
    * Description：可以填入一些描述，如 GitHub with token

### Get PAT

[Creating a personal access token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)

1. On Github, click **Settings**
2. In the left sidebar, click **Developer settings**.
3. In the left sidebar, click **Personal access tokens**.
4. Click **Generate new token**.
5. Give your token a descriptive name.
6. To give your token an expiration, select the **Expiration** drop-down menu, then click a default or use the calendar picker.
7. Select the scopes, or permissions, you'd like to grant this token. To use your token to access repositories from the command line, select **repo**.
8. Click **Generate token**.
   * **Warning:** Treat your tokens like passwords and keep them secret. When working with the API, use tokens as environment variables instead of hardcoding them into your programs.

### Use PAT

*For more information, see [Jenkins-to-GitLab authentication](https://github.com/jenkinsci/gitlab-plugin#jenkins-to-gitlab-authentication).*

根据[Add Credential](# Add Credential)将之前配置的API Token配置为Credential

* **Type**: **Gitlab API Token**
* **API Token**: 填写之前生成的API Token

## Gitlab

Gitlab和Github一样, 可以用SSH Username with private key (这里就不演示了) 和 Gitlab API Token.

### Plugins

Gitlab API Token

需要安装插件:

* GitLab Plugin ;
* Gitlab Hook
* Build Authorization Token Root

### Get Access Token

Create a personal access token to authorize Jenkins to access GitLab.

1. Sign in to GitLab as the user to be used with Jenkins.
2. On the top bar, in the top right corner, select your avatar.
3. Select **Edit profile**.
4. On the left sidebar, select **Access Tokens**.
5. Select the cope.
   * **api**: 选上
   * **read_user**: 选上
   * **read_repository**: 选上
   * **write_repository**: 选上
6. 点击 **Create a [personal access token](https://docs.gitlab.com/ee/user/profile/personal_access_tokens.html)** 
7. Copy the personal access token. You need it to [configure the Jenkins server](https://docs.gitlab.com/ee/integration/jenkins.html#configure-the-jenkins-server).

### Configure Access Token

*For more information, see [Jenkins-to-GitLab authentication](https://github.com/jenkinsci/gitlab-plugin#jenkins-to-gitlab-authentication).*

根据[Add Credential](# Add Credential)将之前配置的API Token配置为Credential

* **Type**: **Gitlab API Token**
* **API Token**: 填写之前生成的API Token

---

理论上讲, 这样做之后Credential配置就结束了, 但是Gitlab插件还提供了一些深层次的Jenkins集成功能, 所以需要在Jenkins中继续配置, 来开启这些功能:

1. Select **Manage Jenkins > Configure System**.
2. In the **GitLab** section, select **Enable authentication for ‘/project’ end-point**.
3. 然后填写表单:
   1. **Connection name**: 自定义
   2. **GitLab host URL**: Enter the GitLab server’s URL, 比如校园网公网的gitlab: `https://git.nju.edu.cn/`
   3. **Credentials**: 选择之前配置的Credential
4. 点击 **Test Connection**, 出现 Success, 表示成功

### Use API Token

1. 进入Jenkins Item的GitLab Connection, 填写GitLab Connection
2. 选择Use alternative credential
3. **Credential** : 选择之前生成的API Token



## DockerHub

我们需要Credential来**log in** Dockerhub, 以从Dockerhub pull或者向其push镜像

Dockerhub支持username-password和API Token作为Credential

## Get API Token

1. Get the token using the following link.

   ```url
   https://hub.docker.com/settings/security
   ```

2. Create an access token using the New Access Token button on the security page.

---

## Use API Token

假设我们把username-password 或者 API Token 配置为了Credential, 就可以在jenkinsfile中使用:

```groovy
stage("login to dockerhub"){
        withCredentials([usernamePassword(credentialsId: 'DOCKERHUB_KEY', passwordVariable: 'password', usernameVariable: 'username')]) {
            sh 'docker login -u $username -p $password'
        }
    }
```

* Credential:`DOCKERHUB_KEY`







# Build

Jenkins从SCM得到代码以及jenkins脚本后，就要根据脚本进行项目构建， 而项目构建不一定由jenkins主机来做。 jenkins采用master - slave模式， jenkins主机作为master，可以将代码和脚本交给slave，让脚本执行构建过程

## slave

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

   

   


# Environment Variable

* Jenkins**内置**了一系列环境变量, 它们都是**global**的, 即可以在所有Jenkinsfile使用, 且作用域是整个Jenkinsfile

* 用户也可以在Jenkinsfike中自定义环境变量, 它们都是local per stage的(即只在指定的stage生效).
* 用法: (前提是环境变量在作用域内)
  * 可以在Jenkinsfile中通过 `env` 关键字使用: `${env.BUILD_ID}$`

## Global Env

### 内置Env

* 可以通过`${YOUR_JENKINS_HOST}/env-vars.html` 查看所有内置环境变量

* 通过执行 `printenv` shell 命令获取：

  ```groovy
  sh "printenv"
  ```

* 使用Jenkins的**内置**环境变量时:

  * 可以不写`env`, 如:`${BUILD_ID}`

  * 如果使用shell 命令, 甚至可以不用写 `{}`, 如: `$BUILD_ID`

    ```groovy
    stage("Read Env Variables") {
                    echo "带 env 的读取方式：${env.BUILD_NUMBER}"
                    echo "不带 env 的读取方式：${BUILD_NUMBER}"
                    sh 'echo "shell 中读取方式 $BUILD_NUMBER"'
                }
    ```

  * 以上用法会让人困惑, 保险起见还是全部用`${env.BUILD_ID}$`吧



### 自定义Env

在Jenkins→Manage Jenkins→Confiure System找到Global properties→勾选”Environment variables”选框，单击“Add”按钮，在输入框中输入变量名和变量值即可。

自定义全局环境变量也会被加入`env`的属性列表中

### 常用Env

* BUILD_NUMBER 构建号，累加的数字。在打包时，它可作为制品名称的一部分，比如server-${BUILD_NUMBER}.jar

* BRANCH_NAME 多分支pipeline项目支持。当需要根据不同的分支做不同的事情时就会用到，比如通过代码将release分支发布到生产环境中、master分支发布到测试环境中。

* BUILD_URL 当前构建的页面URL。如果构建失败，则需要将失败的构建链接放到邮件通知中，这个链接就可以是BUILD_URL

* GIT_BRANCH 通过git拉取的源码构建的项目才会有此变量。在使用env变量时，需要注意不同类型的项目，env变量所包含的属性及其值是不一样的。比如普通pipeline任务中的GIT_BRANCH变量值为roigin/master，在多分支pipeline中GIT BRANCH变量的值为master

  所以，在pipeline中根据分支进行不同行为的逻辑处理时，需要留意。

* BUILD_ID 当前版本ID，与BUILD_NUMBER相同，用于在1.597+中创建的构建，但较旧版本的YYYY-MM-DD_hh-mm-ss时间戳记

* BUILD_DISPLAY_NAME 当前版本的显示名称，默认为“＃153”

* JOB_NAME 此构建项目的名称，如“foo”或“foo / bar”

* JOB_BASE_NAME 此建立项目的名称将剥离文件夹路径，例如“bar / foo”的“foo”

* BUILD_TAG: `jenkins- $ {JOB_NAME} - $ {BUILD_NUMBER} `的字符串。JOB_NAME中的所有正斜杠（/）都会用破折号（ - ）替换。方便放入资源文件，jar文件等，以方便识别

* EXECUTOR_NUMBER 识别执行此构建的当前执行程序（在同一台计算机的执行程序中）的唯一编号。这是您在“构建执行者状态”中看到的数字，但数字从0开始，而不是1。

* NODE_NAME 代理的名称

* NODE_LABELS 空格分隔的节点分配的标签列表

* WORKSPACE 分配给构建作为工作区的目录的绝对路径

* JENKINS_HOME Jenkins主节点上分配的目录绝对路径存储数据

* JENKINS_URL 完整的Jenkins网址，例如[http://server：port/jenkins/](http://server:port/jenkins/) （注意：只有在系统配置中设置了Jenkins URL）

* JOB_URL 此作业的完整URL，如[http://server：port/jenkins/job/foo/](http://server:port/jenkins/job/foo/) （必须设置Jenkins URL）

## Local Env

在Jenkinsfile中可以通过内置函数`withEnc(['key=value'])`来自定义环境变量, 注意它们都是local per stage的:

```groovy
node('!windows') {
    withEnv(['DISABLE_AUTH=true',
             'DB_ENGINE=sqlite']) {
        stage('Build') {
            echo "Database engine is ${DB_ENGINE}"
            echo "DISABLE_AUTH is ${DISABLE_AUTH}"
            sh 'printenv'
        }
    }
}
```

* **这里的 = 号两侧不能有空格**, 必须是 `key=value` 的形式

* 如果使用Declarerative Script, 也可以用: 

  ```groovy
          stage('Build') {
            environment {
                  NAME = "RGYB"
              }
           }
  ```



## 环境变量生效顺序

安装插件：

[https://](https://wiki.jenkins.io/display/JENKINS/Build+Environment+Plugin)[wiki.jenkins.io/display/JENKINS/Build+Environment+Plugin](https://wiki.jenkins.io/display/JENKINS/Build+Environment+Plugin)

[https://](https://wiki.jenkins-ci.org/display/JENKINS/EnvInject+Plugin)[wiki.jenkins-ci.org/display/JENKINS/EnvInject+Plugin](https://wiki.jenkins-ci.org/display/JENKINS/EnvInject+Plugin)

全局环境变量 < Slave 配置环境变量 < Job 参数 < Job injected 环境变量   

一般不Override 全局环境变量, 否则可能出现不可预知的问题




# Jenkinsfile

官网教程：https://www.jenkins.io/doc/book/pipeline/

jenkins根据jenkinsfile来进行构建，该文件有两种写法： `Declarative`和`pipeline script`, 后者使用groovy语言，表达能力比较强，推荐使用

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

# Jenkinsfile Example

# Integration with Shell

Many Pipeline steps also use the named-parameter syntax as a shorthand for creating a Map in Groovy, which uses the syntax `[key1: value1, key2: value2]`.



For convenience, when calling steps taking only one parameter (or only one mandatory parameter), the parameter name may be omitted, for example:

```groovy
sh 'echo hello' /* short form  */
sh([script: 'echo hello'])  /* long form */
```

* Jenkins没有Terminal, 所以shell里面没法用`sh 'sudo [...]'`



可以利用Shell的返回值:

```groovy
sh(script: 'cmd', returnStdout:true)
```

例如:

```groovy
LS_RESULT = "${sh(script:'ls -lah', returnStdout: true).trim()}"
```



# Integration with Git

Many Pipeline steps also use the named-parameter syntax as a shorthand for creating a Map in Groovy, which uses the syntax `[key1: value1, key2: value2]`. Making statements like the following functionally equivalent:

```groovy
git url: 'git://example.com/amazing-project.git', branch: 'master'
git([url: 'git://example.com/amazing-project.git', branch: 'master'])
```



e.g.

```groovy
   def git_branch = 'master'
   def git_repository = 'git@github.com:VolatileReborn/Frontend-VolatileReborn.git' //Github
   
<Snip>
  
   stage('clone from github into slave\'s workspace. Using branch: ' + "master") {
        echo "workspace: ${workspace}"
        git branch: "${git_branch}", url: "${git_repository}"
     
    }
```



# Integration with Docker

[Using Docker with Pipeline ](https://www.jenkins.io/doc/book/pipeline/docker/)

Starting with Pipeline versions 2.5 and higher, Pipeline has built-in support for interacting with Docker from within a `Jenkinsfile`.

* 注意, Jenkins所在主机(宿主机或者容器)必须要安装Docker

### Customizing the execution environment

Pipeline is designed to easily use [Docker](https://docs.docker.com/) images as the execution environment for a single [Stage](https://www.jenkins.io/doc/book/glossary/#stage) or the entire Pipeline. Meaning that a user can define the tools required for their Pipeline, without having to manually configure agents. 



```groovy
node {
    /* Requires the Docker Pipeline plugin to be installed */
    docker.image('node:16.13.1-alpine').inside {
        stage('Test') {
            sh 'node --version'
        }
    }
}
```

### Volumes

```groovy
node {
    /* Requires the Docker Pipeline plugin to be installed */
    docker.image('maven:3.8.1-adoptopenjdk-11').inside('-v $HOME/.m2:/root/.m2') {
        stage('Build') {
            sh 'mvn -B'
        }
    }
}
```

### Multiple Containers

```groovy
node {
    /* Requires the Docker Pipeline plugin to be installed */

    stage('Back-end') {
        docker.image('maven:3.8.1-adoptopenjdk-11').inside {
            sh 'mvn --version'
        }
    }

    stage('Front-end') {
        docker.image('node:16.13.1-alpine').inside {
            sh 'node --version'
        }
    }
```

### Build Image

```groovy
node {
    checkout scm
    def customImage = docker.build("my-image:${env.BUILD_ID}")
    customImage.push()
}
```

#### Build with Tag

One common usage of image "tags" is to specify a `latest` tag for the most recently, validated, version of a Docker image. The `push()` method accepts an optional `tag` parameter, allowing the Pipeline to push the `customImage` with different tags, for example:

```
node {
    checkout scm
    def customImage = docker.build("my-image:${env.BUILD_ID}")
    customImage.push()

    customImage.push('latest')
}
```

#### Using Dockerfile

The `build()` method builds the `Dockerfile` in the current directory by default. This can be overridden by providing a directory path containing a `Dockerfile` as the second argument of the `build()` method, for example:

```groovy
node {
    checkout scm
    def testImage = docker.build("test-image", "./dockerfiles/test") 

    testImage.inside {
        sh 'make test'
    }
}
```

* Builds `test-image` from the Dockerfile found at `./dockerfiles/test/Dockerfile`.



It is possible to pass other arguments to [docker build](https://docs.docker.com/engine/reference/commandline/build/) by adding them to the second argument of the `build()` method. When passing arguments this way, the last value in the that string must be the path to the docker file and should end with the folder to use as the build context)

This example overrides the default `Dockerfile` by passing the `-f` flag:

```
node {
    checkout scm
    def dockerfile = 'Dockerfile.test'
    def customImage = docker.build("my-image:${env.BUILD_ID}",
                                   "-f ${dockerfile} ./dockerfiles") 
}
```

* Builds `my-image:${env.BUILD_ID}` from the Dockerfile found at `./dockerfiles/Dockerfile.test`.

### Push to Registry

In order to use a custom Docker Registry, users of Scripted Pipeline can wrap steps with the `withRegistry()` method, passing in the custom Registry URL, for example:

```groovy
node {
    checkout scm

    docker.withRegistry('https://registry.example.com') {

        docker.image('my-custom-image').inside {
            sh 'make test'
        }
    }
}
```



For a Docker Registry which requires authentication, add a "Username/Password" Credentials item from the Jenkins home page and use the Credentials ID as a second argument to `withRegistry()`:

```groovy
node {
    checkout scm

    docker.withRegistry('https://registry.example.com', 'credentials-id') {

        def customImage = docker.build("my-image:${env.BUILD_ID}")

        /* Push the container to the custom Registry */
        customImage.push()
    }
}
```

### Bugs

* `docker run -it ...`报错: the input device is not a TTY
  * Jenkins没有TTY, 所以不要使用`-it`

## Frontend

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

# Integration with Gitlab

[Jenkins integration ](https://docs.gitlab.com/ee/integration/jenkins.html), 我的过程和文档上的略有不同



```groovy
    //Gitlab
    stage("signal github: deployed"){
        echo 'Notify GitLab'
        updateGitlabCommitStatus name: 'build', state: 'pending'
        updateGitlabCommitStatus name: 'build', state: 'success'
    }
```



# Plugins

* 可以在 [Jenkins plugins](https://plugins.jenkins.io/) 搜索

* 也可以在 Manage Jenkins --> Manage Plugins -->可选插件 中选择
* 在jenkins安装时, 勾选推荐安装的插件(包括了Git插件)
* 需要手动安装:
  * Install the [Jenkins GitLab Plugin](https://wiki.jenkins.io/display/JENKINS/GitLab+Plugin).

1. ### 安装GitHub Plugin

   > 系统管理-->插件管理-->可选插件

   直接安装Github Plugin, jenkins会自动帮你解决其他插件的依赖，直接安装该插件Jenkins会自动帮你安装plain-credentials 、[Git](http://lib.csdn.net/base/git) 、 credentials 、 github-api

# 日志

日志是最好的debug工具， jenkins日志位于：Dashboard -> System Log 

# Ref

* [Gitlab Jenkins integration](https://docs.gitlab.com/ee/integration/jenkins.html )
