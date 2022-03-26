---
title: Kubernetes Intro
tags: Kubernetes
categories: Technology
---



# Basic Idea

Kubernetes 是一个容器编排系统， 既是容器集群, 也是containerized cloud-native microservices apps的编排者( orchestrator  )

* 编排包括:
  * Deploy 
  * Scale it up and down dynamically based on demand
  * Self-heal it when things break
  * Perform zero-downtime rolling updates and rollbacks
* containerized cloud-native microservices app：容器化的云原生微服务应用, 这三个概念是互换的, 支持容器化的应用适合上云, 也适合作为微服务
  * 云原生: 满足上云的应用, 也就是适合容器化, 适合自动扩缩容等
  * 微服务: 就是独立开发，独立运营，独立部署， 独立扩缩容，有自己的生命周期的应用. 不同的微服务组合起来形成一个大型应用



## K8S Background

K8S是google用go开发的容器编排系统，并且开源,捐给了给了CNCF( Cloud Native Computing Foundation )



google自己用的容器编排系统是 Borg 和 Omega， 基于此二者开发了K8S， 但K8S不是这二者的开源版本，只是有共同之处



## K8S vs Docker

![image-20220324180510977](/home/lyk/.config/Typora/typora-user-images/image-20220324180510977.png)

K8S可以对各种容器进行编排， 也就是支持各种 container runtime, 通过：

*  The Container Runtime Interface (CRI) ： 容器运行时接口，第三方 container runtime需要实现了这个接口
* Runtime Classes： allows you to create different classes of runtimes. For example, the gVisor or Kata
  Containers runtimes might provide better workload isolation than the Docker and containerd runtimes.



Docker  是最著名的 container runtime, 但不是唯一的选择. K8S 2.0 后， K8S的runtime是` containerd` , 而不是Docker

* ` containerd` ：Docker的一个组件



K8S vs Docker Swarm:  **Kubernetes 是容器编排系统的事实标准**，Swarm、Mesos 和 Kubernetes 的大战已经基本宣告结束，Kubernetes 赢了
