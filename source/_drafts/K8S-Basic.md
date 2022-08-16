---
title: K8S Basic
tags: Kubernetes
categories: Technology
---

# K8S概览



Docker是一种更加偏向底层的技术，它负责诸如启停容器的操作；而Kubernetes是一种更加偏向上层的技术，它注重集群范畴的管理，比如决定在哪个节点上运行容器、决定什么适合进行扩缩容或升级”



一个Kubernetes集群由主节点（master）与工作节点（node）组成。这些节点都是Linux主机

主节点负责管理整个集群，有时主节点也被称为控制平面（control plane）
应用服务运行在工作节点上，有时也将工作节点称作数据平面（data plane）

* 建议部署3～5个主节点



K8S的对象的部署分为命令式和声明式， 命令式就是命令行的command，缺点是容易和manifest文件发生冲突； 声明式就是定义对象的manifest文件，并将其POST到API Server， 建议使用声明式

## commands

K8S的`object-type`有：

* `Pods`:
* `deploy`
* `svc`: 或`service`
* `ep`: 或endpoint`
* `pv`
* `pvc`
* `cm`: 或`configmap`
* `sts`

### 部署对象

将manifest文件POST到API Server:

```shell
kubectl apply -f XX.yml
```

### 列出节点

```shell
kubectl get nodes 
```



### 列出Pod

```shell
kubectl get Pods
```

* `--watch`: Pods，以便在状态发生变化时能够及时看到
* `-o wide`: 多输出几列信息，不过依然是单行输出。
* `-o yaml`: 返回集群存储中的一份完整的关于Pod的清单。输出的内容大体分为两块:
  * 期望状态(spec)
  * 当前(观测)状态(status)
* `--record`: 记录下该命令，使其可以在之后的`kubectl rollout history`中查看

### 列出所有对象

```
kubectl get <object-type>
```

* `-o yaml`: 显示对象的完整配置



### 查看对象信息



```shell
kubectl describe <object-type> <object>
```

* `<object-type> <object>`: 可以选择：
  * `Pods <Pod>`: 查看指定的Pod信息，该命令还可以看到Pod内的容器顺序
  * `deploy <deployment>`
  * `svc <service>`
    * `svc`也可写成`service`
  * `ep <service>`: 查看该service的endpoint对象，该对象维护着所有与该Service匹配的动态的Pod列表
    * `ep`也可以写成`endpoint`
  * `pv`
  * `pvc`

### 进入容器执行命令

```
kubectl exec -it <Pod> --container <container>-- <command>
```

* `--container <container>`: 指定想要创建exec会话的容器。如果不指定，则会进入Pod的第一个容器中执行

### 查看容器log

```
kubectl logs <Pod> -c --container <container>
```

* `--container <container>`： 同样，默认为Pod内第一个容器

### 删除对象

通过删除对象的配置文件来删除对象：

```shell
kubectl delete -f <manifest>
```

### 对象扩缩容

```shell
“kubectl scale <object-type> <object> --replicas=<num>
```



“容器中的root用户通常也会拥有所在节点上不受限制的root访问权限。”

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

## 主节点和工作节点



### 主节点

![image-20220531133842442](/Users/lyk/Library/Application Support/typora-user-images/image-20220531133842442.png)

主节点运行了调度决策、监控集群、响应事件与集群变化等服务

* 因此主节点也称作头结点（head node）、控制平面（control plane）

#### API Server

API Server位于控制平面的最前端，所有的指令与通信均需要通过API Server来完成。默认情况下，API Server通过443端口对外提供Https RESTful风格的接口

* kubectl会将manifest文件通该接口（HTTP POST）发送到控制平面
* 这些YAML文件有时也被称作manifest文件，它们描述了用户希望应用在运行时达到的期望状态（desired state）
* 访问API Server的全部请求都必须经过授权与认证，一旦通过之后，YAML文件配置就会被认为是有效的，并被持久化到集群的存储中，最后部署到整个集群



  

#### 集群存储

集群存储是控制层中唯一有状态（stateful）的部分，它持久化地存储了整个集群的配置与状态

* 通常集群存储底层会选用一种常见的分布式数据库etcd。因为这是整个集群的唯一存储源，用户需要运行3～5个etcd副本来保证存储的高可用性，并且需要有充分的手段来应对可能出现的异常情况。
* etcd认为一致性比可用性更加重要。这意味着etcd在出现brain break时，会停止为集群提供更新能力，来保证存储数据的一致性。但是，就算etcd不可用，应用仍然可以在集群性持续运行，只不过无法更新任何内容而已
* 对于所有分布式数据库来说，写操作的一致性都至关重要。例如，分布式数据库需要能够处理并发写操作来尝试通过不同的工作节点对相同的数据进行更新， etcd使用RAFT算法



#### controller管理器

controller管理器实现了全部的后台**控制循环**，完成对集群的监控并对事件作出响应
controller管理器是controller的管理者（**controller of controller**），负责创建controller，并监控它们的执行

* 控制循环包括：工作节点controller、终端controller，以及副本controller
  * 对应的每个controller都在后台启动了独立的循环监听功能，负责监控API Server的变更。这样做的目的是保证集群的current state可以与desired state相匹配



控制循环的逻辑如下：

1. 获取期望状态

   * 期望状态: 用户通过manifest文件来告知Kubernetes集群自己希望应用运行的样子

     Excerpt From
     Kubernetes修炼手册
     （英）奈吉尔·波尔顿（Nigel Poulton）
     This material may be protected by copyright.

2. 通过reconciliation loop来持续监控集群状态，如果current state 和 desired state 有差异，则变更当前状态来消除差异点。
   

#### 调度器

调度器的**通过监听API Server来启动新的工作任务，并将其分配到适合的且处于正常运行状态的节点中**

* 调度器会过滤掉不能运行指定任务的工作节点，并对过滤后的节点进行排序。排序系统非常复杂，在排序之后会选择分数最高的节点来运行指定的任务
  * 过滤规则包括：节点是否仍然存在、是否有affinity或者anti-affinity规则、任务所依赖的端口在当前工作节点是否可以访问、工作节点是否有足够的资源等。不满足任务执行条件的工作节点会被直接忽略，剩下的工作节点会依据下面的判定规则计算得分并排序，
  * 排序的判定规则包括：工作节点上是否已经包含任务所需的镜像、剩余资源是否满足任务执行条件，以及正在执行多少任务
* 如果调度器无法找到一个合适的工作节点，那么当前任务就无法被调度，并且会被标记为暂停状态
* 调度器并不负责执行任务，只是为当前任务选择一个合适的节点运行

### 工作节点

![image-20220531135322554](/Users/lyk/Library/Application Support/typora-user-images/image-20220531135322554.png)

工作节点的任务：

1. 监听API Server分派的新任务
2. 执行新分派的任务
3. 向控制平面回复任务执行的结果（通过API Server）

#### Kubelet

Kubelet是Kubernetes中重要的代理端，并且在集群中的每个工作节点上都有部署。

* 通常工作节点与Kubelet这两个术语基本上是等价的。

在一个新的工作节点加入集群之后，Kubelet就会被部署到新节点上。然后Kubelet负责将当前工作节点注册到集群当中，集群的资源池就会获取到当前工作节点的CPU、内存以及存储信息，并将工作节点加入当前资源池。

Kubelet的一个重要职责就是负责监听API Server新分配的任务。每当其监听到一个任务时，Kubelet就会负责执行该任务，并维护与控制平面之间的一个通信频道，准备将执行结果反馈回去。

如果Kuberlet无法运行指定任务，就会将这个信息反馈给控制平面，并由控制平面决定接下来要采取什么措施。例如，如果Kubelet无法执行一个任务，则其并不会负责寻找另外一个可执行任务的工作节点。Kubelet仅仅是将这个消息上报给控制平面，由控制平面决定接下来该如何做。


#### 容器运行时

Kubelet需要容器运行时（container runtime）来执行依赖容器才能执行的任务，例如拉取镜像并启动或停止容器。

* Kubelet通过容器运行时接口（CRI）来屏蔽不同CR的实现细节
* 老版本k8s默认的CR是docker；现在是containerd，它是docker的一个组件

#### kube-proxy

kube-proxy运行在每个工作节点，负责本地集群网络。

* kube-proxy保证了每个工作节点都可以获取到唯一的IP地址，并且实现了本地IPTABLE以及IPVS来保障Pod间的网络路由与负载均衡

### K8S DNS

每个Kubernetes集群都有自己内部的DNS服务

* 集群DNS服务有一个静态IP地址，并且这个IP地址集群总每个Pod上都是硬编码的，这意味着每个容器以及Pod都能找到DNS服务



每个新服务都会自动注册到集群DNS服务上，这样所有集群中的组件都能根据**名称**找到相应的服务。

* 一些其他的组件也会注册到集群DNS服务，例如Statefulset以及由Statefulset管理的独立Pod。

集群DNS是基于CoreDNS来实现的。



### K8S 应用打包

![image-20220531140519651](/Users/lyk/Library/Application Support/typora-user-images/image-20220531140519651.png)

应用部署到K8S步骤:

1. 将应用按容器方式进行打包。
2. 将应用封装到Pod中。
3. 通过声明式manifest文件部署。



# kubectl

kubectl是在进行Kubernetes管理的过程中使用的主要命令行工具,  它将对用户友好的命令转换成API Server所能理解的JSON格式。并基于一个配置文件来决定将其POST到哪个集群的API Server

## commands

### 查看kubectl配置

```
kubectl config view
```

* 敏感数据会在输出中被抹掉

### 查看kubectl当前使用的context

```
kubectl config current-context
```



### 改变当前使用的context

```shell
kubectl config use-context <new-context>
```

* 需要确保`<new-context>`在配置文件中有定义

## config



kubectl的配置文件默认位于`$HOME/.kube/config`,包含如下信息: 

* clusters: 是kubectl可以连接的多个集群的列表，当用户需要管理多个集群时会非常有用。每个集群的定义都包含名字、证书信息和API Server端口
* contexts: 是**集群和相关用户的组合**，并用易于记忆的名字来代指。例如，配置中有名为deploy-prod的context，它将名为deploy的用户凭证和名为prod的集群定义组合起来。此时如果基于这个context使用kubectl，那么该命令将会以deploy用户的身份发送至集群prod的API Server
* users（凭证）: 定义不同的用户以及对不同集群的不同级别的权限。例如，配置中可能有dev用户和ops用户，它们分别具有不同的权限。每一个用户的定义都有一个易于记忆的名字（name）、一个账号（username）和一系列凭证信息



如下是一个kubectl的配置文件，其中定义了一个名为minikube的集群、一个名为minikube的context，以及一个名为minikube的用户。该context是用户minikube和集群minikube的组合，并被设置为默认的context:

```yaml
apiVersion: v1  
clusters:  

- cluster: 
  certificate-authority: C:\Users\nigel\.minikube\ca.crt 
  server: https://192.168.1.77:8443 
  name: minikube  
  contexts:  
- context:  
  cluster: minikube  
  user: minikube 
  name: minikube  
  current-context: minikube  
  kind: Config  
  preferences: {} 
  users:  
- name: minikube  
  user: 
    client-certificate: C:\Users\nigel\.minikube\client.crt
    client-key: C:\Users\nigel\.minikube\client.key
```

## context

context是集群和用户的组合



如下示例表示kubectl命令会发送给`$HOME/.kube/config`中定义的名为eks-K8sbook的集群:

```
$ kubectl config current-context
eks_k8sbook
```



## 

## 

# Pod

> 在英语中，会将a group of whales（一群鲸鱼）称作a Pod of whales，Pod就是来源于此。因为Docker的Logo是鲸鱼，所以在Kubernetes中会将包含了一组容器的事物称作Pod



![image-20220531144221373](/Users/lyk/Library/Application Support/typora-user-images/image-20220531144221373.png)

Pod是由一个或多个容器共享的运行环境，是K8S中调度的原子单位

* 在使用Docker作为CR时， **Pod实际上是一个名为`pause container`的特殊容器**
  * 没错，Pod就是一种特殊容器的花哨称谓。这意味着，**运行在Pod中的容器实际上是运行在容器中的**

* Pod只是一个运行环境，相当于沙盒，本身不会运行任何东西
* **容器必须在Pod中运行**

## commands

## Pod与命名空间

和容器一样，Pod本质上也是一系列**kernel namespace的集**合，包括:

* 网络命名空间：**IP地址**、端口范围、路由表
* UTS命名空间：**主机名**
* IPC命名空间：UNIX域套接字（domain socket）……
  因此，Pod中的所有容器都共享主机名、IP地址、内存地址空间以及卷



![image-20220531142019036](/Users/lyk/Library/Application Support/typora-user-images/image-20220531142019036.png)







Pod中可能包含多个容器。单容器Pod是最简单的，但是多容器Pod对于紧耦合的容器使用场景来说更加适用，比如日志和Service Mesh

* 在Service Mesh中，每个Pod会塞入一个代理容器（proxy container）。由代理容器来处理所有进出Pod的网络流量

* 同一个Pod中运行的容器可以通过localhost进行通信



在Kubernetes集群中可以运行一个Pod单例，但是通常情况下不建议这么做。推荐的方式是通过更上层的controller来完成。最常见的controller就是Deployment，它提供了可扩容、自愈与滚动升级等特性。读者只需要通过一个YAML文件就可以指定Deployment的配置信息，包括需要使用哪个镜像以及需要部署多少副本



## Pod网络

每个Pod会创建其自己的网络命名空间。其中包括一个IP地址、一组TCP和UDP端口范围，以及一个路由表

* 即使是多容器Pod也是如此——其中的每个容器共享Pod的IP、端口范围和路由表。



如果要从Pod的外部访问内部的容器，需要使用IP地址和容器所关联的端口号。 同一Pod内搭容器间通过Pod的localhost适配器进行通信

* 如果需要从外部访问Pod内的容器，则需要分别将其暴露在不同的端口上。每个容器都有其自己的端口，同一个Pod中的容器不能使用同一个端口


## Pod与CGroup

控制组（Control Group, CGroup）用于避免某个容器消耗掉节点上所有可用的CPU、RAM和IOPS。可以说是CGroup限制了资源的使用

每个**容器**有其自己的CGroup限额。

* 也就是说，同一个Pod中的两个容器可以有不同的CGroup限额

## Pod生命周期

![image-20220531150039097](/Users/lyk/Library/Application Support/typora-user-images/image-20220531150039097.png)



Pod的生命周期是**有限**的

Deployment等高级对象提供了Pod的自愈功能，但自愈并不是使Pod复活。 而是删除原Pod并启动一个新的



Pod生命周期：

1. 用户定义一个manifest文件中进行定义，并将其POST到API Server
2. control plane会检查这个YAML格式的配置文件，并将其作为一条部署意图的记录（a record of intent）写入集群存储中
   * 意图记录即“期望状态”（desired state）
3. 然后Pod被调度到一个健康的、有充足资源的节点上
4. 一旦完成调度，就会进入等待状态（pending state），此时节点会下载镜像并启动容器。
5. 在所有资源就绪前，Pod的状态都保持在等待状态
6. 一切就绪后，Pod进入运行状态（running state）
7. 在完成所有任务后，会停止并进入成功状态（succeeded state）。

* 当Pod无法启动时，保持在等待状态（pending state）或进入失败状态（failed state）





## Pod部署

建议**用Deployment等更高级的对象来部署Pod**

* 通过Pod manifest部署的Pod是单例的，没有副本、自愈等等高阶特性
* Pod有生命周期，一旦Pod挂了（停止状态、失败状态）， 就用另外一个来代替，新的Pod具有**不同的ID和IP**
  * 因此，Pod manifest部署的Pod是不可靠的



Pod的部署是原子的。这意味着，只有当Pod中的所有容器都启动成功且处于运行状态时，Pod提供的服务才会被认为是可用的。对于部分启动的Pod，绝对不会响应服务请求。整个Pod要么全部启动成功，并加入服务；要么被认为启动失败。
一个Pod只会被唯一的工作节点调度



## Pod 实战

Pod manifest文件如下：

```yaml
apiVersion: v1 
kind: Pod 
metadata: 
  name: hello-Pod  
  labels: 
    zone: prod 
    version: v1 
spec: 
  containers: 
  - name: hello-ctr 
    image: nigelpoulton/k8sbook:latest  
    ports: 
    - containerPort: 8080
```

首先可以看到4个顶级资源(top-level resource): 

* `apiVersion`: 定义了两个属性：用来创建部署对象的API组和API版本
  * 通常来说，其格式是`<api-group>/<version>`。不过，Pod对象定义在一个名为Core的特殊的API组（API Group），**可以忽略api-group部分**
    * 例如，StorageClass对象是在v1版本的`storage.k8s.io`API组中定义的，那么在YAML文件中就写作`storage.k8s.io/v1`
    * 定义Pod所在的Core API组是特殊的，可以忽略组名，故而在YAML文件中只写v1即可
* `kind`: 要部署的对象类型
* `metadata`: 定义name和label ( label就是kay-value pair ), 用于标识对象. 
  * 还可以对对象指定namespace. namespace是对Kubernetes集群进行切分的唯一方式. **Kubernetes中的命名空间与Linux内核命名空间是不同的，它仅是Kubernetes集群的逻辑分区, 用于对以下资源分组**:
    * 限制（Limit）
    * 配额（Quota）
    * RBAC规则
      重点在于，**Kubernetes的命名空间，并不能保证某一个命名空间中的Pod不会影响到另一个命名空间中的Pod。因此，我们不应将生产负载和有潜在风险的负载运行在同一个物理集群上。唯一能够确保真正的隔离的方式是将其置于一个独立的集群中运行**
    * metadata中并未指定namespace，因此会使用`default` namespace。在生产环境中，建议自己指定namespace, 不建议使用`default`
* `spec`: 定义Pod所运行的容器。本例所部署的Pod中只有一个基于镜像nigelpoulton/k8sbook:latest的容器。这个容器被命名为hello-ctr并且通过端口8080暴露出来








#  Deployment

## commands

### 显示历史版本

```
kubectl rollout history deployment <deployment>
```

### 回滚

注意， 该回滚操作是一个命令式的指令， 会使得集群的当前状态和manifest文件不符。 因此执行该命令后，还需要手动更新manifest文件

```
kubectl rollout undo deployment <deployment> --to-revision=<version>
```



![image-20220531153641676](/Users/lyk/Library/Application Support/typora-user-images/image-20220531153641676.png)

大多数时间，用户通过更上层的控制器来完成Pod部署。上层的控制器包括Deployment、DaemonSet以及StatefulSet。
举例说明一下：**Deployment是对Pod的更高一层的封装**，除Pod之外，还提供了如扩缩容管理、不停机更新以及版本控制等其他特性



Deployment在Pod基础上增加了自愈、水平扩缩容与更新能力

* 自愈和扩缩容通过ReplicaSet实现，后者是一种更底层的对象，一般不建议直接操作ReplicaSet
* “自愈”指的是删除该Pod并重启一个新的。 而不会复活该Pod

## 滚动更新&&回滚

“假设某人遇到了一个Bug，并且需要部署一个新的镜像来完成修复。因此，他修改了同一个Deployment的YAML文件，将镜像版本更新并重新POST到API Server。这会在集群中注册新的期望状态，需要同样数量的Pod，但全部都要运行新版的镜像。为了达到这一点，Kubernetes基于新镜像的Pod创建了一个新的ReplicaSet。此时就有两个ReplicaSet了：一个是包含基于旧版镜像的Pod，一个是新版本的Pod。每次Kubernetes增加新ReplicaSet（新版镜像）中的Pod数量的时候，都会相应地减少旧ReplicaSet（旧版镜像）中的Pod数量。从而，在零宕机的情况下实现了一种平滑的滚动升级。当然，以后的更新也都可以重复这一过程——只需要更新清单文件（应该保存在版本管理系统中）即可。”

* 旧版的ReplicaSet已经暂停并且不再管理任何Pod。然而，仍然保留了所有的配置信息，包括旧版的镜像



回滚与滚动升级的过程正好相反：启用旧的ReplicaSet，停用当前的ReplicaSet



“图6.9中是一个部署在Kubernetes中的简单应用，它由一系列通过Deployment管理的Pod构成。其中，有一个Service筛选的是能够同时匹配app=biz1和zone=prod的Pod（请注意图中的Pod是如何匹配Label筛选器的）。应用目前是运行状态。”

![image-20220531173152897](/Users/lyk/Library/Application Support/typora-user-images/image-20220531173152897.png)





现在假设我们需要上线新的版本，并且不能导致服务停用。
为了达到目的，我们可以增加一批运行着新版应用的Pod，如图6.10所示。

![image-20220531173221546](/Users/lyk/Library/Application Support/typora-user-images/image-20220531173221546.png)

新版的Pod也拥有与Label筛选器所匹配的Label。此时，Service是能够对两个版本（version=4.1和version=4.2）的应用进行负载均衡的。这是由于Service的Label筛选器是会持续检查的，其Endpoint对象会跟进更新所匹配的Pod列表。
当确认新版本没有问题之后，可以通过对Service的Label筛选器追加version=4.2来强制所有的流量转向新版本。这样，旧版本的Pod就不再匹配了，Service只会对新版本转发流量（见图6.11）

![image-20220531173256173](/Users/lyk/Library/Application Support/typora-user-images/image-20220531173256173.png)

“不过此时旧版本的Pod依然在运行，只是不再接受任何流量。也就是说，此时如果发现新版有任何问题，仍然可以仅仅通过将Label筛选器的version=4.1修改为version=4.2来切换回原来的版本。如图6.12所示。”



![image-20220531173336076](/Users/lyk/Library/Application Support/typora-user-images/image-20220531173336076.png)

现在已经切回旧版本了



## Deployment manifest

```yaml
apiVersion: apps/v1  #旧版K8s使用apps/v1beta1
kind: Deployment # 定义的对象类型是Deployment
metadata: 
 name: hello-deploy 
spec: 
  replicas: 10 
  selector: 
    matchLabels: 
      app: hello-world 
  minReadySeconds: 10 
  strategy: 
    type: RollingUpdate 
    rollingUpdate: 
      maxUnavailable: 1 
      maxSurge: 1 
  template: 
    metadata: 
      labels: 
        app: hello-world 
    spec: 
      containers: 
      - name: hello-Pod 
        image: nigelpoulton/k8sbook:latest 
        ports: 
        - containerPort: 8080
```

* `apiVersion`: 所使用的API版本。若使用最新版的Kubernetes，则Deployment对象是位于apps/v1的API组中的
* `spec`:
  * `spec.replicas`: Pod副本数量。spec.selector表明Deployment要管理的Pod所必须具备的标签。
  * `spec.strategy`:告诉Kubernetes如何执行更新操作。
  * `spec.template`: 定义了Deployment管理的Pod模板。这个例子中，Pod模板只有一个容器



Deployment会自动创建相对应的ReplicaSet。可使用如下的kubectl命令予以验证:

```shell
kubectl get rs 
```

* ReplicaSet的名称其实是Deployment的名称与一个hash值的拼接。这里的hash值是对YAML清单文件中Pod模板部分（spec.template下的所有内容）的hash

### manifest

以下就是更新之后的deploy.yml清单文件，唯一有改动的地方就是追加注释的spec.template.spec.containers.image一行

```yaml
apiVersion: apps/v1 
kind: Deployment 
metadata: 
  name: hello-deploy
spec: 
  replicas: 10 
  selector: 
   matchLabels: 
      app: hello-world 
  minReadySeconds: 10 
  strategy: 
    type: RollingUpdate 
    rollingUpdate: 
      maxUnavailable: 1 
      maxSurge: 1 
  template: 
    metadata: 
      labels: 
        app: hello-world 
    spec: 
      containers: 
      - name: hello-Pod 
        image: nigelpoulton/k8sbook:edge # 这一行修改了 
        ports: 
        - containerPort: 8080
```

“关于更新操作如何执行的设置位于spec部分。首先需要注意的是spec.minReady Seconds，它的值被设置为10，也就是告诉Kubernetes每个Pod的更新动作之间间隔10s。这有助于调节更新操作的节奏：如果预留更长的时间，就能让运维人员从容地进行跟踪检查，以避免若一次性全部更新所有Pod时由于出现失误而导致问题产生的风险。
spec.strategy部分的内容告诉Kubernetes。

* 使用RollingUpdate策略来进行更新。
* 不允许出现比期望状态指定的Pod数量少超过一个的情况（maxUnavailable:1）。
* 不允许出现比期望状态指定的Pod数量多超过一个的情况（maxSure:1）。”

在本例中，期望状态是Pod数量为10个副本，那么maxSure:1的意思是在更新过程中，Pod数量不能超过11个，而maxUnavailable:1的意思是不能少于9个。导致的结果就是，在滚动更新的过程中，最多只能同时更新两个Pod（11减9）

# Service

Service提供了稳定的网络与负载均能能力



Pod的IP地址是不可靠的。在某个Pod失效之后，它会被一个拥有新的IP的Pod代替。Deployment扩容也会引入拥有新IP的Pod；而缩容则会删除Pod。这会导致大量的IP流失，因而Pod的IP地址是不可靠的

每一个Service都拥有固定的IP地址、固定的DNS名称，以及固定的端口。
最后，Service利用Label来动态选择将流量转发至哪些Pod



Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

![image-20220531142620885](/Users/lyk/Library/Application Support/typora-user-images/image-20220531142620885.png)

Service为一组Pod提供了可靠且稳定的网络。
图2.12展示了上传这个微服务并通过Kubernetes中的Service机制来与渲染微服务进行交互的过程。Kubernetes Service提供了一个稳定的服务名称与IP地址，并且对于其下的两个Pod提供了请求级别的负载均衡机制

Pod可能会出现故障并销毁。如果通过Deployment或者DaemonSet对Pod进行管理，出现故障的Pod会自动被替换。但是替换后的新Pod会拥有完全不同的IP地址。这种情况也会在水平扩/缩容时发生，扩容时会创建拥有新IP地址变化（IP churn）”

因为**Service作用于TCP以及UDP层**，所以Service层并不具备应用层的智能，即无法提供应用层的主机与路径路由能力。因此，用户需要一个入口来解析HTTP请求并提供基于主机与路径的路由能力



## 将Pod连接到Service

Service只会将流量路由到健康的Pod，如果Pod的健康检查失败，那么Pod就不会接收到任何流量

Service与Pod之间是通过Label和Label筛选器（selector）松耦合在一起的

* Service通过Label和Label Selector来决定应当将流量负载均衡到哪一个Pod集合
* Label Selector包含了要被选择的Pod所需要处理的全部请求对应的标签



标签选择器只会选择包含自己的所有label的Pod:

```python
selected_pods = ()

for pod in all_pod:
	isSelected = True
	
	for selector_label in selector.labels:
    # 如果pod没有选择器中的任何一个label，则该pod不会被选择
    # 即，被匹配的Pod要拥有Service所查找的所有Label
Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.
		if selector_label not in pod.labels:
			isSelected = False
			break
			
	if not isSelected:
		continue
	
	selected_pods.add(pod)
```

## Endpoint

每一个Service在被创建的时候，都会得到一个关联的Endpoint对象。整个Endpoint对象其实就是**一个动态的列表，其中包含集群中所有的匹配Service Label筛选器的健康Pod**

* Kubernetes会不断地检查Service的Label筛选器和当前集群中健康Pod的列表。如果有新的能够匹配Label筛选器的Pod出现，它就会被加入Endpoint对象，而消失的Pod则会被剔除。
  * 也就是说，Endpoint对象始终是保持更新的。
* 这时，当Service需要将流量转发到Pod的时候，就会到Endpoint对象中最新的Pod的列表中进行查找。



当要通过Service转发流量到Pod时，通常会：

1. 先在集群的内部DNS中查询Service的IP地址。
2. 流量被发送到该IP地址后，Service会查找Endpoint对象，并将流量转发到列表中一个Pod



不过，Kubernetes原生应用（知悉Kubernetes集群并且能够访问Kubernetes API的应用）是可以直接查询Endpoint API，而无须查找DNS和使用Service IP的。

## Service 类型

### Cluster IP

Service分为Cluster IP Service和 Nodeport Service，默认是Cluster IP Service

Cluster IP是集群内部分配的IP， 集群DNS存储了Cluster IP到Service名的映射



ClusterIP Service拥有固定的 Cluster IP和端口号，集群内节点可以通过集群DNS，使用Service名来访问对应的节点

### NodePort

Cluster IP Service拥有固定的Cluster IP， 端口号，并在集群DNS中存储了相应的映射。而Nodeport Service是Cluster IP Service的超集，在ClusterIP的基础之上增加了一个集群范围的TCP或UDP的端口，从而使Service可以从集群外部访问



每个节点上的Kubelet进程都会监视API Server上出现的新的Endpoint对象。一旦发现，Kubelet就会创建相应的网络规则，将ClusterIP的流量转发至Pod的IP

* 如今基于Linux的Kubernetes集群中要创建这些规则的技术使用的是Linux IP Virtual Server（IP虚拟服务器，IPVS）。较旧版本的Kubernetes使用的是iptables
  



以下的例子表示一个NodePort Service：

* Name:magic-sandbox。
* ClusterIP:172.12.5.17。
* port:8080。
* NodePort:30050。
  从集群内部，可以通过前3个值（Name、ClusterIP、port）来直接访问这个名为magic sandbox的服务。此外，也可以从集群外部，通过发送请求到集群中的**任何一个节点**的IP上的端口30050来访问它
  * 很显然，这和Docker Swarm几乎完全相同 ---- 通过集群任意节点的Nodeport的流量，最终都会被路由到运行了该Service副本的节点上。 这就是**服务发现**

### LoadBalancer
LoadBalancer Service能够云服务商提供的**负载均衡**服务集成。

* 基于NodePort Service实现，并在此基础上允许互联网上的客户端能够通过云平台的负载均衡服务到达Pod

* 只能在受支持的云平台上的Kubernetes集群中才能生效。比如，我们不能让运行在Microsoft Azure云上的Kubernetes集群利用AWS上才有的ELB负载均衡服务。
  

### ExternalName

ExternalName Service能够将流量路由至Kubernetes集群之外的系统中去（所有其他类型的Service都是在集群内部进行流量的路由）



# 服务发现

## 服务注册

“关于服务注册的几点重要说明如下。
1.Kubernetes使用一个内部DNS服务作为服务注册中心。
2.服务是基于DNS注册的（而非具体的Pod）。
3.每个服务的名称、IP地址和网络端口都会被注册。
为此，Kubernetes提供了一个“众所周知”的内部DNS服务，通常被称为“集群DNS”（cluster DNS）。之所以说是“众所周知”，是因为集群里的所有Pod和容器都知道它的地址。实际上它是运行在kube-system命名空间中，并被一个名为coredns的Deployment管理着的一组Pod。这一组Pod前面也有一个Service，称为kube-dns。具体实现上，它是基于CoreDNS的作为Kubernetes原生应用（Kubernetes-native application）运行的一种DNS技术。”

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

集群DNS是一个Kubernetes原生应用。这意味着它知道自身是运行在Kubernetes上的，而且实现了一个控制器（controller）来监视API Server，以了解新创建的Service对象。一旦发现有新创建的Service对象，就会创建一个能够将该Service的名称解析到其集群IP的DNS记录。因此，应用和Service无须主动执行服务注册——集群DNS会持续监视新Service并自动完成注册”

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

## 集群DNS

“Kubernetes自动配置所有的容器，以便它们能够找到集群DNS，并用来将Service名字解析为IP地址。具体来说，Kubernetes会为每一个容器注入/etc/resolv.conf文件，其中有集群DNS服务的IP地址和搜索域（search domain）——被用来追加至简单名称（unqualified name）作为后缀。
注：所谓“简单名称”（unqualified name）就是类似ent这样的短名称。加上搜索域之后就会变成全限定域名（Fully Qualified Domain Name, FQDN），比如ent.default. svc.cluster.local。”

## qkube-proxy

![image-20220531174553746](/Users/lyk/Library/Application Support/typora-user-images/image-20220531174553746.png)

“在Pod知道对方Service的ClusterIP之后，就可以向该IP地址发送请求了。不过，这个地址在一个特殊的名为服务网络（Service network）的网络上，是没有路由可达的！也就是说，应用的容器并不知道应该将流量发往何处，因此只得发送至默认网关（default gateway）。”

“容器的默认网关会将流量发送至其所在的主机节点。
节点同样没有到达服务网络的路由，因此它会将流量发往自身的默认网关。这一过程中，流量会被节点的内核处理，此时就是网络“黑科技”产生的时机！
每一个Kubernetes节点都运行着一个名为kube-proxy的系统服务。总体来说，kube proxy负责捕获发送至ClusterIP的流量，并转发至匹配Service的Label筛选器的Pod的IP地址。具体如何实现呢？
qkube-proxy是一个基于Pod的Kubernetes原生应用，它实现了一个能够监视API Server上新创建的Service和Endpoint的控制器。当它有新发现时，就回创建一条本地的IPVS规则，该规则告诉主机节点拦截发往Service的ClusterIP的流量，并发送至具体的Pod。
这意味着，每次节点的内核在处理发往服务网络上某个地址的流量时，就会发生一次捕获（trap）“，并将流量转发至匹配目标Service的Label筛选器的某个健康Pod的IP地址。
Kubernetes原本使用iptables来进行捕获和负载均衡。然而在Kubernetes 1.11之后替换为IPVS。这是因为IPVS在进行基于内核的4层负载均衡时有更高的性能，”



“并不存在到达服务网络上的ClusterIP的路由。这意味着，请求会被发送至容器的默认网关，也就是容器所在的节点。节点也没有到达服务网络的路由，因此请求被发送至节点的默认网关。然后该请求会被节点的内核处理，此时会触发一次捕获（trap），从而将请求转发至匹配目标Service的Label筛选器的某个Pod的IP地址。”

## 命名空间

“若想要理解服务发现是如何在命名空间（namespace）内部和之间工作的，有两点很重要。
1.每一个集群都有一个地址空间。
2.命名空间为集群的地址空间的分区。
每一个集群都有一个基于DNS域（domain）的地址空间，我们通常称之为集群域（cluster domain）。默认名称是cluster.local，Service对象都被放在这个地址空间中。例如，Service ent的全限定域名（FQDN）是ent.default.svc.cluster.local。
FQDN的格式是<object-name>.<namespace>.svc.cluster.local。
命名空间可以用来对集群域下的地址空间进行分区。比如，创建prod和dev两个命名空间之后，就会拥有可以安排Service和其他对象的两个地址空间了。
●dev: <object-name>.dev.svc.cluster.local。
●prod:<object-name>.prod.svc.cluster.local。
同一命名空间内部的对象名称必须是唯一的，不过不同命名空间之间的对象可以重名。也就是说，不能在同一个命名空间内有两个名为“ent”的Service对象，但在不同的命名空间是可以的。这一点可用于有开发和生产两套并行的配置环境的情况。如图7.7所示，一个集群域被分成了dev和prod两个地址空间，其中各自部署有ent和voy两个Service。

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

# K8S存储

![image-20220531174907631](/Users/lyk/Library/Application Support/typora-user-images/image-20220531174907631.png)

“无论什么类型的存储，或来自哪里，在其对接到Kubernetes集群中后，都会被统称为卷（volume）”

“图8.1的右侧是Kubernetes持久化卷子系统。其中是一组能够被各个应用来使用的API对象。简单来说，持久化卷（Persistent Volume, PV）允许用户将外部存储映射到集群，而持久化卷申请（Persistent Volume Claim, PVC）则类似于许可证，使有授权的应用（Pod）可以使用PV”

* 一个外部存储卷只能被一个PV使用。例如，一个50GB的外部卷不能分成两个25GB的Kubernetes PV来使用”

  

## 持久化卷子系统

“持久化卷子系统中的3个主要资源如下。
●持久化卷（Persistent Volume，PV）。
●持久化卷申请（Persistent Volume Claim，PVC）。
●存储类（Storage Class，SC）。
概括地说，PV代表的是Kubernetes中的存储；PVC就像许可证，赋予Pod访问PV的权限；CS则使分配过程是动态的。”



“假设有一个Kubernetes集群和一套外部存储系统。存储提供商的CSI插件能够用来在Kubernetes集群中使用其存储。我们在存储系统上置备3个10GB的卷，并创建3个Kubernetes PV对象以便集群可以使用这3个卷。每一个PV代表存储上的一个卷。这时，在Kubernetes集群中就可以看到这3个卷并使用它们了。”

## PV && PVC

“现在假设要部署一个需要10GB存储空间的应用。这没问题，因为已经有3个10GB的PV了。为了让应用能够使用其中一个PV，需要PVC。前面提到，PVC就像许可证，能够准许一个Pod（应用）使用一个PV。应用有了PVC之后，就可以将相应的PV作为卷挂载到Pod中。可以回看图8.2以帮助理解。
大体的过程就是这样的，下面上手操作一下。
本示例适用于运行在Google云上的Kubernetes集群。本书之所以基于一个云平台来举例，是因为这能够简化示例的理解，读者可以使用云平台上的免费方案或初始的免费券。当然，在其他平台上也是类似的，稍作改动即可。
本例假设，在Google云上，集群所在的Region或Zone已经预先创建了一个名为uber-disk的10GB的SSD卷。那么，在Kubernetes中的操作将分为如下几步。
（1）创建PV。
（2）创建PVC。
（3）在PodSpec中定义卷。
（4）挂载到一个容器上。
下面的YAML文件将创建一个PV对象，该对象与Google云上已创建的“uber-disk”磁盘是关联的。”

```yaml
apiVersion: v1 
kind: PersistentVolume 
metadata: 
  name: pv1 
spec: 
  accessModes: 
  - ReadWriteOnce 
  storageClassName: test 
  capacity:  
    storage: 10Gi 
  persistentVolumeReclaimPolicy: Retain
  gcePersistentDisk: 
    pdName: uber-disk
```





“PV资源是定义在coreAPI组的v1中的。PV的名称是pv1，其访问模式是ReadWriteOnce，并且将其存储类设置为test。另外，它还被定义为一个10GB的卷，设置了Reclaim策略，并且被映射到已创建的GCE磁盘uber-disk上。”



spec.accessModes定义了PV是如何被挂载的。可选项包括以下几种。

* ReadWriteOnce（RWO）。
* ReadWriteMany（RWM）。
* ReadOnlyMany（ROM）。”

ReadWriteOnce限制一个PV只能以读写方式被挂载或绑定到一个PVC。尝试将其绑定到多个PVC的话会失败。
ReadWriteMany则允许一个PV能够以读写方式被绑定到多个PVC上。这种模式通常只支持诸如NFS这样的文件或对象存储。块存储通常只支持RWO。
ReadOnlyMany允许PV以只读方式绑定到多个PVC。
需要强调几点。首先，一个PV只能设置一种模式：不能在与一个PVC以ROM模式绑定的同时再与另一个PVC以RWM模式绑定。其次，Pod不能直接与PV对接，而是必须通过PVC与某个PV绑定。
spec.storageClassName让Kubernetes将该PV归入名为test的存储类。本章后续还会就存储类展开介绍，此处为了确保PV与PVC顺利完成绑定暂且如此设置。
还有一个属性spec.persistentVolumeReclaimPolicy，用于定义在PVC被释放之后，如何处理对应的PV。具体来说有两种策略。

* Delete。
* Retain。

Delete是更危险的方式，也是在使用存储类动态创建PV时的默认策略。这一策略会删除对应的PV对象以及外部存储系统中关联的存储资源，从而可能导致数据丢失！因此必须谨慎使用该策略。
Retain则会保留对应的PV对象，以及外部存储系统中的资源。不过，也会导致其他PVC无法继续使用该PV。
如果想要继续使用保留的PV，则需要执行如下3个步骤。
1.手动删除该PV。
2.格式化外部存储系统中相对应的存储资源。
3.重新创建PV。
注意，在实验环境中，非常容易忘记还需要执行以上3个步骤来尝试重新使用一个旧的已删除的设置为retain策略的PV。
spec.capacity用于告诉Kubernetes这个PV的容量是多少。它的值可以比实际的物理存储资源更少，但是不能更多。比如读者不能在外部存储系统的50GB的设备上创建一个100GB的PV[…]”



此外，还可以在YAML文件的parameters部分定义与存储提供商相关的属性。这在后续介绍存储类的时候会看到。如果存储系统支持NVMe设备，那么就可以在这里进行定义。
现在已经有PV了，下面再创建一个PVC，这样Pod就可以声明（claim）对PV的使用了。
下面的YAML文件定义了一个PVC，可以被Pod用来声明对名为pv1的PV的使用权。以下文件gke-pvc.yml可以在本书GitHub库的storage目录下找到

```yaml
apiVersion: v1 
kind: PersistentVolumeClaim 
metadata: 
  name: pvc1 
spec: 
  accessModes: 
  - ReadWriteOnce 
  storageClassName: test 
  resources:  
    requests: 
      storage: 10Gi

```

同PV一样，PVC也是core API组中稳定的v1资源。
最重要的是要注意到，PVC的spec部分的值与要绑定的PV要一致。本例中，access mode、storage class和capacity必须与PV的一致，如图8.5所示。
注：PV可以拥有比PVC更大的容量。比如，一个10GB的PVC可以绑定到一个15GB的PV上（显然会浪费5GB的PV空间）。不过，一个15GB的PVC无法绑定到一个10GB的PV上。

## Stotage Class

“用于在集群中创建不同的存储层（tier）/类（class）。比如，有一个名为“fast”的SC能够创建基于NVMe的存储，而另一个名为“medium-three-site”的SC能够在横跨三地的分布式存储资源上创建稍慢的存储。”

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

“存储类被作为资源定义在storage.k8s.io/v1的API组中。资源类型是StorageClass，用户可以在YAML文件中进行配置，然后POST到API Server中进行部署。在使用kubectl时，用户也可以使用sc作为简称来指代StorageClass对象。
注：使用kubectl api-resources命令可以查看API资源列表及其简称。输出的信息中还包括：每个资源属于哪个API组（空的话表示属于core API组）、资源是否在命名空间中（namespaced），以及在编写YAML文件时的kind值。”

“以下是一个存储类YAML文件的简单例子。它定义了一个名为fast的存储类，存储后端是AWS“爱尔兰”域eu-west-1a上的固态硬盘（io1）。它还定义性能级别为10 IOPs/GB。

```
kind: StorageClass 
apiVersion: storage.k8s.io/v1 
metadata: 
  name: fast 
provisioner: kubernetes.io/aws-ebs
parameters: 
  type: io1 
  zones: eu-west-1a 
  iopsPerGB: "10”
```

与其他Kubernetes的YAML文件类似，kind告诉API Server现在定义的对象是什么类型，apiVersion给出要部署资源的版本。metadata.name用于指定要部署的对象的名字——例子中是fast。provisioner告诉Kubernetes使用哪个插件，parameters的内容用于指定后端存储的具体信息。
以下是几点补充说明。
1.StorageClass对象是不可变的——也就是说它在部署之后是不能修改的。
2.metadata.name应当是有意义的，因为其他对象可能会用到它来代指某个类。
3.provisioner和plugin两个术语可互相替换。
4.parameters定义了与插件相关的值，每个插件可以支持其特有的一组参数。关于这部分的配置需要建立在对相关的存储插件及其关联的后端存储有一定了解的基础之上

### 创建存储类

“部署和使用StorageClass对象的基本流程如下。
1.创建Kubernetes集群及其存储后端。
2.确保与存储后端对应的插件是就绪的。
3.创建一个StorageClass对象。
4.创建一个PVC对象，并通过名称与StorageClass对象关联。
5.部署一个Pod，使用基于该PVC的卷。
请注意以上流程不包括创建PV。这是因为**存储类能够自动创建PV**。
以下的YAML代码片段包含对一个StorageClass、一个PVC和一个Pod的定义。这3个对象可以被定义在同一个YAML文件中，只需要用3个中划线（---）隔开。
请留意PodSpec是如何通过名称引用PVC的，以及PVC是如何通过名称引用SC（StorageClass）的

```yaml
kind: StorageClass 
apiVersion: storage.k8s.io/v1 
metadata:  
  name: fast # 由PVC引用 
provisioner: kubernetes.io.gce-pd 
parameters:  
  type: pd-ssd 
---  
apiVersion: v1 
kind: PersistentVolumeClaim 
metadata: 
  name: mypvc  # 由PodSpec引用 
  namespace: mynamespace 
spec: 
  accessModes: 
  - ReadWriteOnce  
  resources:  
    requests: 
      storage: 50Gi 
  storageClassName: fast  

---  
apiVersion: v1 
kind: Pod 
metadata: 
  name: myPod 
spec: 
  volumes: 
    - name: data  
      persistentVolumeClaim:
        claimName: mypvc  # 匹配PVC名称 
  containers: ...  
  <SNIP>
```



StorageClass使我们无须手动创建PV，只需要创建一个StorageClass对象，然后使用一个插件将其与某个具体的存储后端联系起来。比如在AWS“孟买”域上的高性能AWS SSD存储。SC需要有名称（name），并且需要在YAML文件中定义，然后用kubectl来部署。部署成功之后，StorageClass会观察API Server上是否有新的被关联的PVC对象。当匹配的PVC出现时，StorageClass会自动在后端存储系统上创建所需的卷，并在Kubernetes上创建PV

# ConfigMap

> 云原生应用应当将应用和配置解耦



ConfigMap（CM）可以**动态地在Pod运行时注入数据**, 将配置从Pod中剥离

* 这里实际上是指Pod及其所有的容器。毕竟最终是Pod内的容器获取了配置数据。

ConfigMap位于core API组，并且版本是v1

ConfigMap没有对其内容做加密，因此不能存储敏感数据

* 应使用Secret对象来存储敏感数据





ConfigMap是一个保存有一组键值对（key/value pair）的map，每一个键值对称为一个entry

* key是一个可以包含字母、数字、中划线、点和下划线的名称。
* value可以包含任何内容，包括换行符
* key和value之间用冒号隔开——key:value。
  举两个简单的例子
* db-port:13306
* hostname:msb-prd-db1

```yaml
key:conf value: 
 
directive in; 
main block; 
http { 
  server { 
    listen        80 default_server;
    server_name   *.msb.com; 
    root          /var/www/msb.com; 
    index         index.html  
 
    location / { 
      root   /usr/share/nginx/html; 
      index  index.html;  
    } 
  }  
}
```



“在数据被保存到ConfigMap之后，可以通过以下任一种途径注入运行的容器中。
●环境变量。
●容器启动命令的参数。
●某个卷（volume）上的文件。”



K8S原生应用，是指知道自己运行在Kubernetes上的、能够查询Kubernetes API的应用。因此，Kubernetes原生应用能够通过API直接访问ConfigMap数据，而无须使用类似环境变量或卷的方式。这一点能够简化应用的配置，但是应用只能运行在Kubernetes上

## manifest

COnfigMap可以通过声明式( manifest文件 )和命令式( command )创建



该YAML定义了只有一个entry的map：

```yaml
kind: ConfigMap 
apiVersion: v1 
metadata: 
  name: test-conf
data:  
  test.conf: | 
    env = plex-test 
    endpoint = 0.0.0.0:31001 
    char = utf8 
    vault = PLEX/test 
    log-size = 512M
```

* 管道符号（`|`）: 该符号之后的所有内容被作为一个字面值. 因此，该名为`test-conf`的ConfigMap对象只有一个entry：
  * key: `test.conf`
  * value: `env=plex-test endpoint=0.0.0.0:31001 char=utf8 vault= PLEX/test log-size=512M`
* ConfigMap对象没有状态（期望状态和当前状态）的概念。因此它没有spec和status部分，取而代之的是data



## 将ConfigMap数据注入Pod和容器

### ConfigMap与环境变量

把ConfigMap数据注入容器的常见方式是通过环境变量。首先，创建ConfigMap；然后，将其entity映射到位于Pod template的container部分的环境变量中。当容器启动的时候，环境变量会以标准Linux或Windows环境变量的形式出现在容器中

将ConfigMap作为环境变量来使用是有缺点的，即环境变量是静态的。也就是说，所有对ConfigMap的更新操作并不会影响到运行中的容器



查看Pod（或者说容器）环境变量：

```
kubectl exec envPod -- env | grep NAME
```



### ConfigMap与容器启动命令

容器是允许定义启动命令的，而我们又可以借助变量来自定义启动命令。
下面的Pod模板（template，YAML文件中定义Pod及其容器的部分）定义了一个名为args1的容器。容器基于busybox镜像，并且执行/bin/sh命令（第5行）



仔细看启动命令会发现，其中有两个变量：FIRSTNAME和LASTNAME。它们是在env部分进行的具体定义。

* FIRSTNAME基于ConfigMap multimap的given entry。
* LASTNAME基于同一个ConfigMap的family entry。



在容器的启动命令中使用ConfigMap，也会遇到和作为环境变量使用的时候同样的限制——对ConfigMap的更新不会同步到已运行的容器中





### ConfigMap与卷

1. 创建一个ConfigMap。
2. 在Pod模板中创建一个ConfigMap卷。
3. 将ConfigMap卷挂载到容器中。
4. ConfigMap中的entry会分别作为单独的文件出现在容器中



下面的YAML创建了一个名为cmoul的Pod，其中配置项如下

* spec.volumes创建了一个基于ConfigMap multimap的名为volmap的卷
* spec.containers.volumeMounts将volmap卷挂载到/etc/name

```yaml
apiVersion: v1 
kind: Pod 
metadata: 
  name: cmvol 
spec: 
  volumes: 
    - name: volmap 
      configMap: 
        name:multimap
  containers: 
    - name: ctr 
      image: nginx
      volumeMounts: 
        - name: volmap 
          mountPath: /etc/name
```

spec.volumes创建了一个特殊类型的卷，称为ConfigMap卷。卷的名称是volmap，它基于ConfigMap multimap。这意味着卷中的内容将来自ConfigMap的data部分定义的各个entry。这个例子的卷中有两个文件：given和family。given文件的内容是Nigel，family文件的内容是Poulton。
在spec.containers中将volmap卷挂载到了容器的/etc/name。也就是说在容器中，两个文件的路径如下

* /etc/name/given
* /etc/name/family



执行下面的命令来部署这个容器（来自cmvol.yml部署文件），然后执行kubectl exec命令来列出/etc/name目录下的文件。
```
$ kubectl apply -f cmPod.yml 
Pod/cmvol created 
 
$ kubectl exec volPod -- ls /etc/name
family 
given 
```



# StatefulSet

StatefulSet和Deployment相似，但用于部署和管理有状态的Pod



Pod状态包括：

* Pod的名字是可预知和保持不变的
* DNS主机名是可预知和保持不变的。
* 卷的绑定是可预知和保持不变的。
  以上3个属性构成了Pod的状态，有时也被成为Pod的状态ID（stick ID）。状态ID在即使发生故障、扩缩容，以及其他调度操作之后，依然保持不变，从而使StatefulSet适用于那些要求Pod保持不变的应用中
  This material may be protected by copyright.



“举个简单的例子，由StatefulSet管理的Pod，在发生故障后会被新的Pod代替，不过依然保持相同的名字、相同的DNS主机名和相同的卷。即使新的Pod在另一个节点上启动



由StatefulSet管理的所有Pod都会获得一个可预知的、保持不变的名字。这些Pod名字对于其启动、自愈、扩缩容、删除、附加卷等操作都非常重要。

StatefulSet的Pod名字遵循<StatefulSetName>-<Integer>的规则。其中Integer是一个从零开始的索引号，也就是“一个从0开始的整数”。被StatefulSet创建的第一个Pod的索引号为“0”，之后的Pod的索引号依次递增



“关于StatefulSet的另一个基本特性就是，对Pod的启动和停止是受控和有序的。
StatefulSet每次仅创建一个Pod，并且总是等前一个Pod达到运行且就绪状态之后才开始创建下一个Pod。而Deployment在使用ReplicaSet控制器创建Pod时则是并行开始的，这可能会引发潜在的竞态条件（race condition）。
对于前面的YAML文件的例子，tkb-sts-0 会最先启动，并且在达到运行且就绪状态之后，StatefulSet控制器才会创建tkb-sts-1。对于tkb-sts-2也是同样的待遇



“扩缩容操作也遵循同样的规则。例如，当从3个副本扩容到5个副本时，会启动一个名为tkb-sts-3的新Pod，并且等待其处于运行且就绪状态之后，再创建tkb-sts-4。当缩容时，则遵循相反的规则：控制器会首先终止拥有最高索引号的Pod，等待其被完全删除之后，再继续删除下一个拥有最高索引号的Pod



“在缩容的时候Pod是被依序而非并行删除的，这对于许多的有状态应用来说意义重大。例如，对于数据存储类的集群化应用来说，如果多个副本是被同时删除的话，会面临数据丢失的风险。StatefulSet将确保这种情况不会发生”

“StatefulSet控制器能够自行完成自愈和扩缩容。而Deployment是通过一个独立的ReplicaSet控制器来完成这些操作的，二者从架构上是不同的。”

“在删除StatefulSet时，需要重点考虑两个问题。
删除一个StatefulSet并不是按序依次终止所有Pod的，因此，也许在删除StatefulSet之前首先将其缩容至0是个不错的主意。
我们可以使用terminationGracePeriodSeconds来调整间隔时间。通常应至少将该参数设置为10，以便让Pod中的应用能够有机会将本地缓存中的数据落盘，以及安全地提交进行中的写入操作。”

## headless Service

部署为StatefulSet的应用，认为Pod是可预知的、长期存在的。因此，应用中的其他组件或其他的应用，可能需要直接连接到某个Pod上。为了实现这一点，StatefulSet使用了一个headless Service来为每一个Pod副本创建一个可预知的DNS主机名。从而，其他应用可以通过向DNS查询所有Pod的信息来实现对这些Pod的直接连接。
下面的YAML代码定义的StatefulSet将一个名为mongo-prod的headless Service作为governing Service

```yaml
apiVersion: v1 
kind: Service 
metadata: 
  name: mongo-prod 
spec:  
  clusterIP: None 
  selector: 
    app: mongo 
    env: prod 
---  
apiVersion: apps/v1 
kind: StatefulSet 
metadata:
  name: sts-mongo 
spec:  
  ServiceName: mongo-prod
```

“headless Service，就是一个将spec.clusterIP设置为None的常规Kubernetes Service对象。当这个headless Service被设置为StatefulSet的spec.ServiceName时，它就成为了StatefulSet的governing Service。

* “一个headless Service（无头Service）就是没有ClusterIP的Service对象。”

  Excerpt From
  Kubernetes修炼手册
  （英）奈吉尔·波尔顿（Nigel Poulton）
  This material may be protected by copyright.

在二者如此关联之后，Service会为所匹配的每个Pod副本创建DNS SRV记录。其他Pod可以通过对headless Service发起DNS查询来获取StatefulSet的信息

## manifest

```
“apiVersion: apps/v1 
kind: StatefulSet 
metadata: 
  name: tkb-sts 
spec:  
  replicas: 3 
  selector: 
    matchLabels: 
      app: web 
  ServiceName: "dullahan" 
  template:
    metadata: 
      labels: 
        app: web 
    spec: 
      terminationGracePeriodSeconds: 10  
      containers: 
      - name: ctr-web  
        image: nginx:latest  
        ports: 
        - containerPort: 80 
          name: web 
        volumeMounts: 
        - name: webroot  
          mountPath: /usr/share/nginx/html
  volumeClaimTemplates: 
  - metadata:  
      name: webroot  
    spec: 
      accessModes: [ "ReadWriteOnce" ] 
      storageClassName: "flash" 
      resources: 
        requests: 
          storage: 1Gi
```



“该StatefulSet的名字是tk-sts。名字是很重要的，因为它的所有Pod副本都基于这个名字——都以tkb-sts为前缀。
spec.replicas属性定义了3个Pod副本，它们将分别被命名为tsk-sts-0、tsk-sts-1、tsk-sts-2。它们会被依序创建，并且StatefulSet控制器会在等待当前所创建的Pod达到运行且就绪状态后才会创建下一个。
spec.ServiceName属性指定了governing Service。其名字是前面创建的headless Service，它会为每一个StatefulSet的Pod创建一个对应的DNS SRV。而“之所以被称为governing Service，是由于它负责管理该StatefulSet所有的DNS子域名。
之后的spec.template部分定义了Pod的模板，包括容器的镜像、暴露的端口等。
最后一段非常重要的内容是spec.volumeClaimTemplates部分。
本章前面提到，StatefulSet对存储的需求是希望能够动态创建所使用的卷。因此用到了StorageClass和PersistentVolumeClaim（PVC）。
现在StorageClass已经就位备用。不过，关于PVC却存在一个有趣的挑战。
StatefulSet的每一个Pod都需要拥有独立的存储。这意味着每个Pod需要自己的PVC。然而这是不可能的，因为每个Pod都是基于同一个template创建的。这样就得提前为每个Pod创建好PVC，这也不好办，因为还要考虑到StatefulSet可能会扩容或缩容。
显然，这里需要一个更加聪明的基于StatefulSet的方案。这也是volumeClaimTemplate（卷申请模板）出现的原因。
总体来说，volumeClaimTemplate用于在每次创建一个新的Pod副本的时候，自动创建一个PVC。它还能够自动为PVC命名，以便实现与Pod的准确关联。如此，在StatefulSet的配置中，template部分用来定义Pod的模板，而volumeClaimTemplate部分则用来定义PVC。
下面的YAML代码是例子中StatefulSet应用的volumeClaimTemplate部分。它定义了一个名为webroot的申请模板，从前面创建的flash StorageClass中申请一个10GB的卷

```yaml
volumeClaimTemplates: 
- metadata:  
    name: webroot 
  spec: 
    accessModes: [ "ReadWriteOnce" ]
    storageClassName: "flash" 
    resources: 
      requests: 
        storage: 10Gi
```

“在StatefulSet对象部署之后，会创建3个Pod副本以及3个PVC”

## 扩缩容

“当StatefulSet进行扩容的时候，都会创建一个Pod和一个PVC。不过，当StatefulSet进行缩容的时候，Pod会被删除而PVC仍然保留。也就是说，将来再次进行扩容操作的时候只需要创建一个新的Pod即可，新Pod会连接保留的PVC。这其中的Pod和PVC的映射关系由StatefulSet控制器负责跟踪和管理”

Excerpt From
Kubernetes修炼手册
（英）奈吉尔·波尔顿（Nigel Poulton）
This material may be protected by copyright.

# K8S Security

Kubernetes不支持安全的多租户（nulti-tenancy）集群，Kubernetes中唯一的集群级别的安全边界就是集群本身。
**对Kubernetes集群进行切分的唯一方式是创建命名空间（namespace）**。**Kubernetes中的命名空间与Linux内核命名空间是不同的，它仅是Kubernetes集群的逻辑分区。事实上，它更是一种对以下资源进行分组的方式**:

* 限制（Limit）
* 配额（Quota）
* RBAC规则
  重点在于，**Kubernetes的命名空间，并不能保证某一个命名空间中的Pod不会影响到另一个命名空间中的Pod。因此，我们不应将生产负载和有潜在风险的负载运行在同一个物理集群上。唯一能够确保真正的隔离的方式是将其置于一个独立的集群中运行**

