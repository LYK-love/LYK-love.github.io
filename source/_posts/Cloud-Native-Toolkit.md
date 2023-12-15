---
categories:
- Software Engineering
date: 2022-09-13 15:10:42
tags:
- Linux
- Docker
- K8s
title: Cloud Native Toolkit
---

Outline:

* Docker
* Kubernetes

<!--more-->

# Docker

参见《Docker Intro》

1. install:

   ```shell
   sudo apt install docker.io
   ```

   

2. 最好使用非root用户来使用Docker,此时需要添加非root用户到本地Docker Unix组：

   ````
   sudo usermod -aG docker [user_name]
   ````

   * 如果当前登陆用户就是要添加进组的用户的话，需要重新登陆才能生效

3. 换源阿里云,需要去阿里云“容器镜像服务” --> “镜像加速器” 生成镜像url：

   ```shell
   sudo mkdir -p /etc/docker
   sudo tee /etc/docker/daemon.json <<-'EOF'
   {
     "registry-mirrors": ["https://zz1b9pta.mirror.aliyuncs.com"]
   }
   EOF
   sudo systemctl daemon-reload
   sudo systemctl restart docker
   ```

   *mac用户可在setting -- docker engine中修改`daemon.json`文件

4. 终端输入docker info查看是否配置成功

   ```
   > docker info
   ...
   Registry Mirrors:
   https://zz1b9pta.mirror.aliyuncs.com/
   ```

5. 将docker设置为开机自启：

   ```shell
   systemctl enable docker
   ```

   

# kubernetes

## Install

ubuntu20.04下安装k8s

注意，k8s的安装和集群初始化都需要root用户

1. 安装docker

2. 安装依赖

   ```
   sudo apt-get update
   sudo apt-get -y install apt-transport-https ca-certificates curl software-properties-common
   ```

   * 直接在`/etc/apt/sources.list`里添加`https://mirrors.aliyun.com/kubernetes/apt/`是不行的，因为这个阿里镜像站使用的`ssl`进行传输的，所以要先安装`apt-transport-https`并下载镜像站的密钥才可以进行下载

3. 安装GPG证书:

   ```
   curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add - 
   ```

4. 写入软件源信息:

   ```javascript
   cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
   deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main
   EOF
   ```

5. 然后更新源列表：

   ```
   apt-get update
   ```

6. 查看可安装版本：

   ```shell
   apt-cache madison kubelet
   ```

7. 安装指定版本:

   ```
   apt-get install -y kubelet=1.18.4-00 kubeadm=1.18.4-00 kubectl=1.18.4-00
   ```

   * 如果想要安装最新版本，就直接：

     ```
     apt-get install -y kubelet kubeadm kubectl
     ```

     但是很不推荐，因为最新的k8s 1.24.* 的集群初始化有bug，不如用老版本

8. 设置开机启动:

   ```shell
   sudo systemctl enable kubelet && sudo systemctl start kubelet
   ```

9. 查看所需镜像,以刚才安装的1.18.4版本为例:

   ```
   kubeadm config images list --kubernetes-version=v1.18.4
   
   k8s.gcr.io/kube-apiserver:v1.18.4
   k8s.gcr.io/kube-controller-manager:v1.18.4
   k8s.gcr.io/kube-scheduler:v1.18.4
   k8s.gcr.io/kube-proxy:v1.18.4
   k8s.gcr.io/pause:3.2
   k8s.gcr.io/etcd:3.4.3-0
   k8s.gcr.io/coredns:1.6.7
   ```

10. 上面的镜像是Google的，国内无法访问，需要用阿里云的镜像来替换:

    ```shell
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-apiserver:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-controller-manager:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-scheduler:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/kube-proxy:v1.18.4
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.2
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/etcd:3.4.3-0
    docker pull registry.cn-hangzhou.aliyuncs.com/google_containers/coredns:1.6.7
    ```

11. 为镜像重新打tag：

    ```
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-apiserver:v1.18.4 k8s.gcr.io/kube-apiserver:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-controller-manager:v1.18.4 k8s.gcr.io/kube-controller-manager:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-scheduler:v1.18.4 k8s.gcr.io/kube-scheduler:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/kube-proxy:v1.18.4 k8s.gcr.io/kube-proxy:v1.18.4
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/pause:3.2 k8s.gcr.io/pause:3.2
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/etcd:3.4.3-0 k8s.gcr.io/etcd:3.4.3-0
    docker tag registry.cn-hangzhou.aliyuncs.com/google_containers/coredns:1.6.7 k8s.gcr.io/coredns:1.6.7
    ```







5. 执行下面命令，测试安装是否正常

   ```
   kubeadm init
   ```

   * k8s集群在初始化时建议使用root用户，如果以普通用户执行`kubeadm init`， 会得到报错:

     ```
     [ERROR IsPrivilegedUser]: user is not running as root [preflight] If you know what you are doing, you can make a check non-fatal with `--ignore-preflight-errors=...`
     ```

6. 查看k8s版本:

   ```
   kubeadm version
   ```

   ````
   kubeadm version: &version.Info{Major:"1", Minor:"24", GitVersion:"v1.24.1", GitCommit:"3ddd0f45aa91e2f30c70734b175631bec5b5825a", GitTreeState:"clean", BuildDate:"2022-05-24T12:24:38Z", GoVersion:"go1.18.2", Compiler:"gc", Platform:"linux/amd64"}
   ````

   * ``GitVersion:"v1.24.1""` 即为版本号

## Uninstall



```shell
sudo apt remove -y kubelet kubeadm kubectl
rm -rf ~/.kube/
rm -rf /etc/kubernetes/
rm -rf /etc/systemd/system/kubelet.service.d
rm -rf /etc/systemd/system/kubelet.service
rm -rf /usr/bin/kube*
rm -rf /etc/cni
rm -rf /opt/cni
rm -rf /var/lib/etcd
rm -rf /var/etcd
```





## 配置管理节点

## 配置主机

增加主机名:

单独为每个服务器增加主机名，格式为hostnamectl set-hostname hostname。一般主节点取名master，从节点取名node.

```text
hostnamectl set-hostname [k8s-master]
```





在主节点配置所有k8s服务器的host，并且host名字跟各服务器的主机名对应。这里配置的是公网IP

```
cat >> /etc/hosts << EOF 
<主节点公网IP> k8s-master
<工作节点公网IP> k8s-node1
EOF
```

```
echo "使host配置生效" > /dev/null
/etc/init.d/network restart
```

## 修改cgroup

Kubernetes cgroup driver was set to systems but docker was set to systemd. So I created `/etc/docker/daemon.json` and added below:

```yaml
{
    "exec-opts": ["native.cgroupdriver=systemd"]
}
```

Then

```yaml
 sudo systemctl daemon-reload
 sudo systemctl restart docker
 sudo systemctl restart kubelet
```



Then：

```
docker info | grep Cgroup
```

如果输出为：

```
Cgroup Driver: systemed
Cgroup Version: 1
```

即成功

## Cluster Config

### 初始化master节点

如果初始化过程中出现错误，要使用`kubeadm reset -f`清除之前的配置



```
kubeadm init \
--apiserver-advertise-address=121.36.247.134 \
--kubernetes-version=v1.18.4 \
--pod-network-cidr=10.244.0.0/16 \
--service-cidr=10.96.0.0/12 \
--ignore-preflight-errors=Swap
```

```
kubeadm init \
--apiserver-advertise-address=121.36.247.134 \
--image-repository registry.aliyuncs.com/google_containers \
--pod-network-cidr=10.244.0.0/16
```

这里介绍一下一些常用参数的含义：

- `--apiserver-advertise-address`: k8s 的`apiserver`的部署地址，填自己的管理节点 ip( 如果公网通信，那就是公网ip )
- `--image-repository`: 拉取的 docker 镜像源，因为初始化的时候`kubeadm`会去拉 k8s 的很多组件来进行部署，所以需要指定国内镜像源，下不然会拉取不到镜像。
- `--pod-network-cidr`: 这个是 k8s 采用的节点网络，因为我们将要使用`flannel`作为 k8s 的网络，所以这里填`10.244.0.0/16`就好
- `--kubernetes-version`: 这个是用来指定你要部署的 k8s 版本的，一般不用填，不过如果初始化过程中出现了因为版本不对导致的安装错误的话，可以用这个参数手动指定。
- `--ignore-preflight-errors`: 忽略初始化时遇到的错误，比如说我想忽略 cpu 数量不够 2 核引起的错误，就可以用`--ignore-preflight-errors=CpuNum`。错误名称在初始化错误时会给出来。

### 配置 kubectl 工具

```
mkdir -p /root/.kube && \
cp /etc/kubernetes/admin.conf /root/.kube/config
```

### 执行完成后并不会刷新出什么信息，可以通过下面两条命令测试 `kubectl`是否可用：

```csharp
# 查看已加入的节点
kubectl get nodes
# 查看集群状态
kubectl get cs
```

### 部署 flannel 网络

`flannel`是一个专门为 k8s 设置的网络规划服务，可以让集群中的不同节点主机创建的 docker 容器都具有全集群唯一的虚拟IP地址

```ruby
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```

### 检查节点是否部署完成

```
kubectl get nodes
```