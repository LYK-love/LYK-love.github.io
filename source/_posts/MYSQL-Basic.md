---
title: MYSQL Basic
tags: Database
categories: Technology
mathjax: true
date: 2022-04-09 16:45:48
---


Outline:

* CS Archetecture
* Apps
* Config
* Concurrency Control
  * Lock
  * Transaction
  * MVCC
* Sotrage Engine

ref: *Mysql是怎样运行的*, *高性能Mysql*

<!--more-->

  

# CS Archetecture

![CS Arch](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Database/Mysql%20Basic/CS%20Arch.png)

* Mysql采用CS模式，CS之间通过TCP通信，Server默认监听3306端口，也可以手动指定
  * 如果CS都运行在同一台机器上，则默认使用Unix Socket通信， Server默认监听的Socket为`/var/run/mysqld/mysqld.sock`，也可以手动指定



* 和Servlet一样，每当一个Client连接到Server， 后者都会创建一个线程与该Client交互，当Client退出后，该线程会被缓存起来，并被之后的Client复用



* Server拥有一个存储引擎API，来屏蔽底层存储引擎的差异。 Server通过API和存储引擎通信

## 连接管理



连接建立后，Mysql Server会接收到Client的请求，请求（即查询语句）是文本格式

## 解析与优化

### 查询缓存

由于维护缓存需要性能开销，Mysql 8.0开始已经没有查询缓存了

查询缓存就是对查询语句的结果做缓存，由于查询语句是文本格式，所以任何字符上的不同都会导致cache miss. 任何更新表的操作都会刷新缓存

### 语法解析

相当于编译过程

### 查询优化

优化结构生成执行计划

优化器不关心表的存储引擎，但后者又对查询有影响，因此优化器会请求存储引擎来提供信息

## 存储引擎

查看Server支持的存储引擎:

```mysql
show engines
```

* `Transactions`列表示是否支持事务处理
* `Savepoints`列表示是否支持事务的部分回滚



指定存储引擎（默认是Innodb）：

```mysql
CREATE TABLE [table_name](
...
)ENGINE = [engine_name]
```





修改表的存储引擎：

```mysql
ALTER TABLE [table_name] ENGINE = Innodb
```



查看表的存储结构：

```mysql
SHOW CREATE TABLE [table_name]]\G
```



# Apps

Mysql是一组程序，包括了可执行文件，shell脚本等

Linux下，Mysql安装目录：`/usr/bin`

```shell
❯ ls /usr/bin | grep mysql
mysql
mysql_config_editor
mysql_migrate_keyring
mysql_secure_installation
mysql_ssl_rsa_setup
mysql_tzinfo_to_sql
mysql_upgrade
mysqladmin
mysqlanalyze
mysqlbinlog
mysqlcheck
mysqld_multi
mysqld_safe
mysqldump
mysqldumpslow
mysqlimport
mysqloptimize
mysqlpump
mysqlrepair
mysqlreport
mysqlshow
mysqlslap
```

* 一般安装时会自动将这些可执行文件添加到环境变量`PATH`



## Mysql Server

* `mysqld`: Mysql Server程序, 运行该程序就启动了一个Mysql Server进程，但该文件一般不常用，我们一般用脚本启动
  * `-P`: 指定Server监听的端口，默认是3306
  * `--default-storage-engine=[engine_name]`: 指定默认存储引擎
  * `--skip_networking`:禁止使用TCP通信，即Client无法用ip来与Server通信
* `mysqld_safe`: 是一个Shell脚本，间接调用`mysqld`并持续监控Server的运行状态，并将Server的出错信息输出到错误日志
  * 对于传递给`mysqld_safe`的启动选项，如果它处理不了，会被转发到`mysqld`
* `mysqld_nulti`: Shell脚本，用于启动或停止多个Server实例





## Mysql Client

* `mysql`: Mysql Client程序，用法为：

  ```shell
  mysql -h [hostname] -u [username] -p [password]
  ```

  * `-h`: Server进程所在的主机的域名or IP地址，如果Server就运行在本机，可以省略这个参数, 长参数形式为：`--host=[hostname]`
  * `-u`: 用户名, 长参数形式为：`--user=[username]`, 缺省则为当前Linux登陆用户
  * `-p`:	密码, 长参数形式为：`--password=[password]`
  * `-P`: 指定需要连接的Server的端口，默认是3306



* 退出mysql：`exit`, `quit`

# Config

命令行指定的配置只对当次启动生效，可以在mysql配置文件里指定配置

* 命令行的配置会覆盖配置文件的配置
* 配置文件中，个人的配置会覆盖全局的配置

## 

## 配置文件

Mysql配置文件位置：

* Global: `/etc/mysql/my.cnf`

* Personal: `~/.my.cnf`

  

配置文件分多个组， `[server]`, `[client]`, `[mysqld]`这些， 对应名字的程序/脚本启动时会读取对应组的部分， 比如`mysqld`会读取`[mysqld]`的配置， `mysqld_safe`会读取`[mysqld_safe]`，当然，`mysqld_safe`会调用`mysqld`, 因此也会间接读取`[mysqld]`

* 所有Server程序都会读取`[server]`
* 所有Client程序都会读取`[client]`
* 如果一个程序间接调用了另一个程序，则后者的配置也会被读取， 如 `mysqld_safe`会读取`[mysqld_safe]`，由于`mysqld_safe`会调用`mysqld`, 因此也会间接读取`[mysqld]`

### 系统变量

通过命令行和配置文件进行的配置，会被读取为系统变量，系统变量的作用域分为GLOBAL和SESSION

* GLOBAL：对Server有效， 每次Server启动时，根据配置来初始化GLOBAL变量
* SESSION：对当次会话有效，即只对某个Client的连接有效。 SESSION变量在连接时根据相应GLOBAL变量的值来初始化
  * 更改GLOBAL变量的值只会影响到之后接入的SESSION， 之前的SESSION变量不会被改变



不是所有的系统变量都具有这两种作用范围，有些只具有GLOBAL范围，如`max_connections`;有些只具有SESSION范围，`insert_id`

有些系统变量是只读的，如`version`



查看系统变量：

```mysql
SHOW [scope] VARIABLES [LIKE [pattern]]
```

* `[scope]`: 取值为`GLOBAL`, `SESSION`， 即查看指定作用域的变量



# 并发控制



* 每种存储引擎都可以实现自己的锁策略和锁粒度

* Mysql Server不管理事务，事务由下层的存储引擎实现（当然这只是理论上，事实上server层可能会加table lock）

* **不要使用多个存储引擎**， 否则在一个事务中混合了采用多个存储引擎的表，有的支持事务，有的不支持，就会出现各种问题

* Innodb采用两阶段锁定协议，在事务执行时随时都可以锁定，锁只有在执行`COMMIT`或`ROLLBACK`后才会释放，且所有锁都在同一时刻释放

* InnoDB使用锁机制和MVCC进行并发控制, 并通过next-key locking防止幻读

  



## Lock

Innodb处理死锁的方案：将持有最少行级排他锁的事务进行回滚



下面介绍一些基本的锁策略:

### table lock

Myisam使用表锁

存储引擎管理自己的锁，但server也可能会主动加table lock

* Server会对`ALTER TABLE`之类的语句使用table lock，而忽略存储引擎的锁机制

### row lock

Innodb使用行级锁

行级锁的粒度更细，对并发的支持更好，开销也更大， row lock只在存储引擎中实现，<u>与Server无关</u>

## Transaction

### ACID

* atomicity
* consistency: 数据库总是从一个一致性的状态转换到另一个一致性的状态
* isolation: 一个事务在提交之前，对其他事务不可见
* duality: 事务提交后必须被持久化（持久性也分不同的级别，没有策略能保证100%对持久性）

### 隔离级别

* READ UNCOMMITTED: 事务中的修改，即使未提交， 对其他事物也是可见的。 事务可以读取未提交的数据，也称为脏读



* READ COMMITTED: 满足了隔离性（一个事务从开始直到提交之前，所做的任何修改对其他事务不可见）， 避免了脏读，存**在不可重复读、幻读问题**
  * 可重复读：在同一个事务中多次读取同样的记录的结果是一致的
  * MVCC对该级别的实现就是每次进行普通的select查询，都会产生一个新的快照(不同时间，当前活跃的事务不同，行记录最近一次更新的事务ID也可能不同)。相当于二级锁协议，进行读操作需要加读锁，读完就释放锁



* REPEATABLE READ: Mysql默认级别。 避免了脏读和不可重复读，但存在幻读（ Phantom Read ）问题

  * 幻读：当某个事物读取某个范围内的记录时， 另一个事务又在该范围插入了新的纪录， 当之前的事务再次读取该范围的记录时，会产生幻行

  * Innodb和Xtradb通过Next-Key Locks算法的间隙锁和记录锁解决了幻读
  * MVCC对该级别的实现就是在当前事务中只有第一次进行普通的select查询，才会产生快照，此后这个事务一直使用这一个快照进行查询，相当于三级锁协议，进行读操作需要加读锁，事务结束才释放



* SERIALIZABLE: 强制事务串行执行





Mysql能识别所有隔离级别，Innodb也支持所有隔离级别

设置当前会话隔离级别，在下一个事务开始时生效：

```mysql
 SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
```

* 可以在配置文件中设置GLOBAL的隔离级别

### Mysql的事务

Mysql默认采用自动提交模式，每个查询都是一个事务， 可以修改`AUTOCOMMIT`变量来启用/禁用该模式

* 禁用自动提交后， 所有查询都在一个事务中，直到显示地执行`COMMIT`提交或`ROLLBACK`回滚
* 该模式对不支持事务的表，如Myisam, Memory等， 没有影响



某些命令在执行前会强制执行`COMMIT`提交当前的事务

* `ALTER TABLE`, `LOCK TABLE`

### 事务日志

事务日志采用追加方式，这样日志就在磁盘中占用连续的区域，写日志非常快

预写式日志：先写入日志，再写入数据，两次写磁盘

## MVCC

ref: [MVCC]( https://blog.csdn.net/qq_41008202/article/details/105559613)

Multi Version Concurrency Control: 多版本并发控制，支持MVCC的数据库表中**每一行数据都可能存在多个版本**，对数据库的任何修改的提交都不会直接覆盖之前的数据，而是产生一个新的版本与老版本共存，通过读写数据时**读不同的版本来避免加锁阻塞**（写写还是要阻塞等待，因为事务对数据进行更新时会加上排他锁)，MVCC的具体实现依赖于存储引擎，这里只介绍Innodb的MVCC

* 实现：在每个表中添加三个隐藏字段以及事务在查询时创建快照（read view），以及建立数据版本链(Undo log)
* InnoDB支持多版本数据，**在更新或者删除数据时，并不会立马删除原有行记录，而是将旧版本存入回滚段中的Undo log内，并通过回滚指针形成一个数据链，可以通过这个指针访问链上的历代数据版本**，正是这种机制使得数据库数据产生了多个版本，为通过MVCC进行快照读提供了可能
* 并不是所有的查询都是进行快照读，使用普通的select 语句进行查询时会生成快照，进行快照读；使用select … lock in share mode，select … for update，insert，update，delete 语句等语句进行查询或者更新时还是会使用锁机制，进行锁阻塞。
* 使用MVCC的作用(意义)是非阻塞的解决了事务读写冲突，提高了并发性能
* MVCC工作在READ COMMITED和REPEATABLE READ两种隔离级别下

### 三个隐藏字段

InnoDB会为每个使用InnoDB存储引擎的表添加三个隐藏字段，用于实现数据多版本以及聚集索引：

- A 6-byte `DB_TRX_ID` field: 对该行的最后一次插入/更新的事务号， 删除也是一种更新，只是标记一下该行的deleted bit

  * 设置删除位并不会真的进行物理删除，当InnoDB丢弃为删除而编写的更新撤消日志记录时，它才会物理删除相应的行及其索引记录。此删除操作称为清除，速度非常快
  * 这意味着**每行都有一个事务号**

  

- A 7-byte `DB_ROLL_PTR` field:  called the roll pointer. The roll pointer **points to an undo log record** written to the rollback segment. If the row was updated, the undo log record contains the information necessary to rebuild the content of the row before it was updated.   回滚指针，指向当前记录行的undo log信息(存储该数据的前一个版本)



- A 6-byte `DB_ROW_ID` field:  随着新行插入而单调递增的行ID。InnoDB使用聚簇索引，数据存储是以聚簇索引字段的大小顺序进行存储的，当表没有主键或唯一非空索引时，innodb就会使用这个行ID自动产生聚簇索引。如果表有主键或唯一非空索引，聚簇索引就不会包含这个行ID了。该字段跟MVCC关系不大

### Read View

read view是读视图，其实就是一种快照，里面记录了系统中当前活跃事务的ID以及相关信息，主要用途是用来做可见性判断，判断当前事务是否有资格访问该行数据(详情下解)。read view有多个变量，这里只介绍关键部分：

* `trx_ids`: 活跃事务列表，也就是Read View开始创建时**其他未提交的活跃事务的ID列表**。例如事务A在创建read view(快照)时，数据库中事务B和事务C还没提交或者回滚结束事务，此时trx_ids就会将事务B和事务C的事务ID记录下来



* `low_limit_id`： 目前出现过的最大的事务ID+1，即下一个将被分配的事务ID



* `up_limit_id`： 活跃事务列表trx_ids中最小的事务ID，如果trx_ids为空，则up_limit_id 为 low_limit_id，虽然该字段名为up_limit,但在trx_ids中的活跃事务号是降序的，所以最后一个为最小活跃事务ID
  * 如果当前行的事务号小于`up_limit_id`, 则说明该行的最后一次更新在当前的Read View中最早的事务开始之前已经提交了



* `creator_trx_id`： 当前创建read view的事务的ID

### Undo log

Undo log中存储老版本数据，当一个事务需要读取记录行时，如果当前记录行不可见，可以通过roll pointer顺着undo log链找到满足其可见性条件的记录行版本

在InnoDB里，undo log分为如下两类：

1. `insert undo log` : 事务对insert新记录时产生的undo log, 只在事务回滚时需要, 并且在事务提交后就可以立即丢弃。
2. `update undo log` : 事务对记录进行delete和update操作时产生的undo log，不仅在事务回滚时需要，快照读也需要，只有当数据库所使用的快照中不涉及该日志记录，对应的回滚日志才会被purge线程删除



Purge线程：上文提到了InnoDB删除一个行记录时，并不是立刻物理删除，而是将该行数据的DB_TRX_ID字段更新为做删除操作的事务ID，并将删除位deleted_bit设置为true(已删除)，将其放入update undo log中。为了节省磁盘空间，<u>InnoDB有专门的purge线程来清理deleted_bit为true的记录</u>。purge线程自己也维护了一个read view，如果某个记录的deleted_bit为true，并且DB_TRX_ID相对于purge线程的read view可见，那么这条记录一定是可以被安全清除的。

### MVCC更新行的原理

MVCC机制下实现更新还是会用到排他锁，但由于我们读的时候可以通过快照读，读多个版本避免了使用共享锁，因此可以使得读事务不会因为写事务阻塞。MVCC的优越性在于事务需要读行记录的时候不会因为有事务在更新该行记录而阻塞,事务在写行记录时也不会因为有事务在读数据而阻塞。

更新原理: 假设我现在需要修改行记录A,他们的修改过程如下，

1. MVCC更新行记录A时会先用排他锁锁住该行记录A；
2. 然后将该行记录复制到update undo log中，生成旧版本行记录B；
3. 使行记录A的回滚指针指向这条旧版本B，再在行记录A中修改用户需要修改的字段，并将DB_TRX_ID字段更新为更新这条记录的事务ID；
4. 最后提交事务。(用户需要修改的字段指的是业务字段，比如我们要修改name等)

通过回滚指针，形成了一条当前行记录指向历代旧版本行记录的链表，通过这条链表，我们就可以查询该行记录的多个旧版本:

![undo log](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Database/Mysql%20Basic/undo%20log.png)

### MVCC查询行的原理

InnoDB中，事务在第一次进行普通的select查询时，会创建一个read view(快照)，用于可见性判断，事务只能查询到行记录对于事务来说可见的数据版本。可见性判断是通过行记录的DB_TRX_ID(最近一次插入/更新/删除该行记录的事务ID)以及read view中的变量比较来判断。

查询过程如下:

1. 如果 $\mathrm{DB \underline{ } TRX \underline{ }ID} < \mathrm{up\underline{ }limit \underline{ } id}$

   表明这个行记录最近一次更新在当前事务创建快照之前就已经提交了，该记录行的值对当前事务是可见的，当前事务可以访问该行记录，跳到步骤(4)。

2. 如果$\mathrm{DB \underline{ } TRX \underline{ }ID} \ge \mathrm{low \underline{ } limit \underline{ } id}$

   表明这个行记录最近一次更新是快照创建之后才创建的事务完成的，该记录行的值对当前事务是不可见的，当前事务不可以访问该行记录。因此当前事务只能访问比该行记录更旧的数据版本。通过该记录行的 DB_ROLL_PTR 指针，找到更旧一版的行记录，取出更旧一版的行记录的事务号DB_TRX_ID，然后跳到步骤(1)重新判断当前事务是否有资格访问该行记录。

3. 如果$\mathrm{up\underline{ }limit \underline{ } id} \le \mathrm{DB \underline{ } TRX \underline{ }ID} < \mathrm{low \underline{ } limit \underline{ } id} $

   则表明对这个行记录最近一次更新的事务可能是活跃列表中的事务也可能是已经成功提交的事务(事务ID号大的事务可能会比ID号小的事务先进行提交)，比如说初始时有5个事务在并发执行，事务ID分别是1001~1005，1004事务完成提交，1001事务进行普通select的时候创建的快照中活跃事务列表就是1002、1003、1005。因此up_limit_id就是1002， low_limit_id就是1006。对于这种情况，我们需要在活跃事务列表中进行遍历(因为活跃事务列表中的事务ID是有序的，因此用二分查找)，确定DB_TRX_ID是否在活跃事务列表中。

   1. 若不在，说明对这个行记录最近一次更新的事务是在创建快照之前提交的事务，此行记录对当前事务是可见的，也就是说当前事务有资格访问此行记录，跳到步骤(4)。
   2. 若在，说明对这个行记录最近一次更新的事务是当前活跃事务，在快照创建过程中或者之后完成的数据更新，此行记录对当前事务是不可见的(若可见则会造成脏读、不可重复读等问题)。因此当前事务只能访问该行记录的更旧的版本数据。通过该记录行的 `DB_ROLL_PTR` 指针，找到更旧一版的行记录，取出更旧一版的行记录的事务号`DB_TRX_ID`，然后跳到步骤(1)重新判断当前事务是否有资格访问该行记录。

4. 可以访问，将该行记录的值返回

### 当前读和快照读

快照读:使用普通的select 语句进行查询时会生成快照，进行快照读，快照读不会上锁，根据可见性判断，来决定是读取该行记录的最新版本还是旧版本。(只有使用普通的select语句进行查询才会用到快照读，才享受到了MVCC机制的读写非阻塞的优越性)

当前读:使用select … lock in share mode，select … for update，insert，update，delete 语句等语句进行查询或者更新时，会使用相应的锁进行锁定，查询到的肯定数据库中该行记录的最新版本。

### 示例

![MVCC example](https://seec2-lyk.oss-cn-shanghai.aliyuncs.com/Hexo/Database/Mysql%20Basic/MVCC%20example.png)





#  存储引擎

Mysql将每个数据库（即schema）保存为数据目录下的一个字目录，创建表时，会在数据库字目录下创建一个和表同名的`.frm`文件保存表的定义



查看表的相关信息：

```mysql
show table status like '[pattern]'\G;
```

或者查看`INFORMATION_SCHEMA`



| 功能         | MylSAM | MEMORY | InnoDB | Archive |
| ------------ | ------ | ------ | ------ | ------- |
| 存储限制     | 256TB  | RAM    | 64TB   | None    |
| 支持事务     | No     | No     | Yes    | No      |
| 支持全文索引 | Yes    | No     | No     | No      |
| 支持树索引   | Yes    | Yes    | Yes    | No      |
| 支持哈希索引 | No     | Yes    | No     | No      |
| 支持数据缓存 | No     | N/A    | Yes    | No      |
| 支持外键     | No     | No     | Yes    | No      |

## Innodb

Mysql默认的存储引擎

Innodb的数据存储在tablespace中，tablespace是由Innodb管理的黑盒

## Myisam

不支持事务和行级锁，只使用表锁

Myisam将表分别存储为数据文件(`.myd`)和索引文件(`.myi`)



Myisam可以创建压缩表，如果对表不再进行修改操作，那么可以讲该表压缩.这可以极大地减少空间占用

* 工具：`myisampack`
* 压缩表也支持索引，但索引是只读的
* 压缩表是按行压缩的，不是整表压缩。因此解压也只需要解压某些行

## CSV

可以将CSV文件和Mysql的表做转换

## Memory

所有数据都在内存，没有磁盘IO

* 即重启后数据会丢失，但表结构会保留

支持Hash索引

使用table lock，并发程度低



Mysql的临时表一般是Memoey表

* 临时表是使用`CREATE TEMPORARY TABLE`创建的表，可以采用任何存储引擎，Memory只是默认采用的存储引擎

## 转换表的引擎

1. ALTER TABLE

   ```mysql
   ALTER TABLE [table-name] ENGINE=[engine-name]
   ```

2. 先将表导出（`mysqldump`），然后修改sql文件的CREATE TABLE语句的存储引擎选项，还要修改表名（因为同一个数据库不允许重名的表）

3. 创建一个新的存储引擎的表，然后用INSERT...SELECT来导入数据



