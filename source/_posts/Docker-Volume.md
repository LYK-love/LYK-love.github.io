---
categories:
- Software Engineering
date: 2022-03-25 01:42:45
tags: Docker
title: Docker Volume
---

Outline:

* Basic Idea
* Commands
* 示例
* 第三方卷驱动
* 在集群节点间共享存储

<!--more-->

# Basic Idea

docker可以进行非持久化和持久化存储



非持久化存储: 属于容器的一部分, 与容器的生命周期一致

* 默认情况下, 容器的所有存储都使用非持久化存储



持久化存储: 用户可以创建docker卷, 将卷挂载到容器上

* 这首先需要将主机的文件挂载到docker卷,   默认会用主机的` <docker镜像存放位置>/volumes/<卷名>/_data`目录
  * 这意味着可以在主机的文件系统里查看卷的数据

* docker卷与容器是解耦的. 删除容器,卷不会被删除



本地存储默认位于`<docker镜像存放位置>/<storage-driver>`

* docker镜像存放位置: 默认情况下 在 `/var/lib/docker` 
* 存储驱动: 可以自己查看`deamon.json`, 一般都是`overlay2`



# Commands

## 创建卷

```shell
docker volume create <vol-name>
```

* `-d`: 指定驱动, 默认是`local`

## 列出卷

```shell
docker volume ls
```

## 查看卷

```shell
docker volume inpect <vol-name>
```



输出形如:

```json
[
    {
        "CreatedAt": "2022-03-25T01:02:47+08:00",
        "Driver": "local", //默认驱动是local
        "Labels": null,
        "Mountpoint": "/home/lyk/data/docker/volumes/bizvol/_data", // docker主机被挂载的文件系统位置
        "Name": "bizvol",
        "Options": null,
        "Scope": "local" // 默认是local,只能用于当前docker主机的容器
    }
]

```



## 删除卷





删除所有未被使用的卷:

```shell
docker volume prune
```





删除指定卷( 不能删除正在被使用的卷 ):

```shell
docker volume rm <vol>
```



## 将卷挂载到容器

docker命令:

```shell
docker container run \
-dit --name <contaienr> \                                                                 
--mount source=<vol>,target=<container-mount-point> \
--restart=always \
<image>

```

* `--mount`: 挂载卷, **如果没有该卷则会创建**
  * `source`: 要被挂载的docker卷
  * `target`: 卷被挂载到的容器内目录
* `--restart=always`: 容器总是自动重启，生产环境中建议使用此特性



Dockerfile: 

```
VOLUME  <container-mount-point>
```

* 这个方案没什么用,因为Dockerfile一般只能指定相对的主机目录, 这就意味着挂载点在不同主机间会不一样, 得每次部署都手动修改主机目录Docker

## 查看容器的挂载卷情况

```
docker inspect <container> | grep Mounts -A 20
```



# 示例

1. 创建一个容器,并挂载一个卷到其`/vol`目录:

   ```shell
   docker container run -dit --name voltainer \
   --mount source=bizvol,target=/vol \ # bizvol卷不存在,因此会被自动创建
   alpine
   
   ```

2. 进入该容器:

   ```
   docker container exec -it <contaienr> sh
   ```

   

3. 在容器中的`/vol`目录下存储数据:

   ```shell
   echo "This will last" > /home/lyk/data/docker/volumes/bizvol/_data/file1
   ```

4. 查看上一步操作:

   ```shell
   cat /home/lyk/data/docker/volumes/bizvol/_data/file1
   
   # 输出为: This will last
   ```

4. 删除该容器:

   ```shell
   docker container rm -f  voltainer
   ```

   * 这并不会删除docker卷

5. 查看docker主机文件系统中对应该卷的目录:

   ```shell
   sudo cat /home/lyk/data/docker/volumes/bizvol/_data/file1
   # 输出为: This will last
   # 可见卷保留了原始数据, 也证明了卷没有被删除
   ```

6. 下面将`bizvol` 卷挂载到新的服务/容器

   ```shell
   docker service create \
   --name hellcat \
   --mount source=bizvol,target=/vol \
   alpine sleep 1d
   ```

7. 由于没有指定`--replicas`, 因此服务只会部署一份副本. 找到该服务运行的节点,  在节点上找到该服务对应的容器:

   ```shell
   docker service ps hellcat
   ```

8. 进入该容器

9. 查看挂载点下的数据:

   ```shell
   sudo cat /home/lyk/data/docker/volumes/bizvol/_data/file1
   # 输出为: This will last
   # 可见可以将卷挂载给其他容器
   ```

   

# 第三方卷驱动

Docker可以通过插件方式集成第三方卷驱东, 这可以**为Docker集成外部存储系统,并使用这些系统的特性**:

* 块存储: 适用于小块数据的随机访问
* 文件存储: 包括Azure文件存储和Amazon EFS
* 对象存储: 适用于较大且长期存储的,很少变更的二进制数据, 通常是根据内容寻址

# 在集群节点间共享存储

Docker可以继承外部存储系统, 而后者中, 如LUN, NFS等能提供集群间节点共享存储



但是, 所有的共享存储都会面临缓存一致性, 数据一致性等问题,这需要在应用程序中控制. Docker自身无法控制这点