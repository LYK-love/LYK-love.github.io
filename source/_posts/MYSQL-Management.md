---
title: MYSQL Management
tags: Database
categories: Technology
date: 2022-04-09 16:44:41
---


Outline:

* Mysql Management
* Mysql Database Management
* Mysql Table Management

<!--more-->

# Mysql Management

* **USE \*数据库名\*** :
  选择要操作的Mysql数据库，使用该命令后所有Mysql命令都只针对该数据库。

```sql
mysql> use RUNOOB;
Database changed
```

* **SHOW DATABASES:**
  列出 MySQL 数据库管理系统的数据库列表。

```sql
mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| information_schema |fuke
| RUNOOB             |
| cdcol              |
| mysql              |
| onethink           |
| performance_schema |
| phpmyadmin         |
| test               |
| wecenter           |
| wordpress          |
+--------------------+
10 rows in set (0.02 sec)
```

* **SHOW TABLES:**
  显示指定数据库的所有表，使用该命令前需要使用 use 命令来选择要操作的数据库。

  ```sql
  mysql> use RUNOOB;
  Database changed
  mysql> SHOW TABLES;
  +------------------+
  | Tables_in_runoob |
  +------------------+
  | employee_tbl     |
  | runoob_tbl       |
  | tcount_tbl       |
  +------------------+
  3 rows in set (0.00 sec)
  ```

* **SHOW COLUMNS FROM \*数据表\*:**
  显示数据表的属性，属性类型，主键信息 ，是否为 NULL，默认值等其他信息。

  ```sql
  mysql> SHOW COLUMNS FROM runoob_tbl;
  +-----------------+--------------+------+-----+---------+-------+
  | Field           | Type         | Null | Key | Default | Extra |
  +-----------------+--------------+------+-----+---------+-------+
  | runoob_id       | int(11)      | NO   | PRI | NULL    |       |
  | runoob_title    | varchar(255) | YES  |     | NULL    |       |
  | runoob_author   | varchar(255) | YES  |     | NULL    |       |
  | submission_date | date         | YES  |     | NULL    |       |
  +-----------------+--------------+------+-----+---------+-------+
  4 rows in set (0.01 sec)
  ```

* **SHOW INDEX FROM \*数据表\*:**
  显示数据表的详细索引信息，包括PRIMARY KEY（主键）。

  ```sql
  mysql> SHOW INDEX FROM runoob_tbl;
  +------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
  | Table      | Non_unique | Key_name | Seq_in_index | Column_name | Collation | Cardinality | Sub_part | Packed | Null | Index_type | Comment | Index_comment |
  +------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
  | runoob_tbl |          0 | PRIMARY  |            1 | runoob_id   | A         |           2 |     NULL | NULL   |      | BTREE      |         |               |
  +------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
  1 row in set (0.00 sec)
  ```

* **SHOW TABLE STATUS [FROM db_name] [LIKE 'pattern'] \G:**
  该命令将输出Mysql数据库管理系统的性能及统计信息。

  ```sql
  mysql> SHOW TABLE STATUS  FROM RUNOOB;   # 显示数据库 RUNOOB 中所有表的信息
  
  mysql> SHOW TABLE STATUS from RUNOOB LIKE 'runoob%';     # 表名以runoob开头的表的信息
  mysql> SHOW TABLE STATUS from RUNOOB LIKE 'runoob%'\G;   # 加上 \G，查询结果按列打印
  ```

## 创建用户帐户

MySQL提供了`CREATE USER`语句，允许您创建一个新的用户帐户。 `CREATE USER`语句的语法如下：

```sql
CREATE USER user_account IDENTIFIED BY password;
SQL
```

用户帐号(`user_account`)是以`username@hostname`格式跟在`CREATE USER`子句之后。

密码(`password`)在`IDENTIFIED BY`子句中指定。`password`必须是明文。 在将用户帐户保存到用户表之前，MySQL将加密明文密码。

例如，要创建一个新的用户`dbadmin`，这个用户只允许从`localhost`主机并使用密码为`pwd123`连接到MySQL数据库服务器，使用`CREATE USER`语句，如下所示：

```sql
CREATE USER dbadmin@localhost 
IDENTIFIED BY 'pwd123';
SQL
```

如果用户`dbadmin`还可以从IP为`192.168.1.100`的主机连接到MySQL数据库服务器，使用`CREATE USER`语句，如下所示：

```sql
CREATE USER dbadmin@192.168.1.100 
IDENTIFIED BY 'pwd123';
SQL
```

要查看用户帐户的权限，请使用`SHOW GRANTS`语句，如下所示：

```sql
SHOW GRANTS FOR dbadmin@localhost;
SQL
```

执行上面查询语句，得到以下结果 - 

```shell
mysql> SHOW GRANTS FOR dbadmin@localhost;
+---------------------------------------------+
| Grants for dbadmin@localhost                |
+---------------------------------------------+
| GRANT USAGE ON *.* TO 'dbadmin'@'localhost' |
+---------------------------------------------+
1 row in set
Shell
```

上面结果中的`*.*`显示`dbadmin`用户帐户只能登录到数据库服务器，没有其他权限。 要授予用户权限，您可以使用[GRANT语句](http://www.yiibai.com/mysql/grant.html)，有关`Grant`语句，我们将在[下一个教程](http://www.yiibai.com/mysql/grant.html)中介绍。

请注意，点(`.`)之前的部分表示数据库，点(`.`)后面的部分表示表，例如`database.table`，`testdb.offices`等等。

要允许用户帐户从任何主机连接，请使用百分比(`%`)通配符，如以下示例所示：

```
CREATE USER superadmin@'%' IDENTIFIED BY 'mypassword';
```

百分比通配符`%`与[LIKE](http://www.yiibai.com/mysql/like.html)运算符中使用的效果相同，例如，要允许`mysqladmin`用户帐户从`yiibai.com`主机的任何子域连接到数据库服务器，请使用百分比通配符`%`，如下所示：

```sql
CREATE USER mysqladmin@'%.yiibai.com'
IDENTIFIED by 'mypassword';
SQL
```

> 请注意，也可以在`CREATE USER`语句中使用下划线通配符`_`。

如果您省略了用户帐户的主机名部分，MySQL也会接受它，并允许用户从任何主机进行连接。 例如，以下语句创建一个名为`remote_user`的新用户帐户，可以从任何主机连接到数据库服务器：

```sql
CREATE USER remote_user;
SQL
```

可以看到授予远程用户帐户(`remote_user`)的权限如下：

```sql
SHOW GRANTS FOR remote_user;
SQL
```

执行上面查询语句，得到以下结果 - 

```sql
mysql> SHOW GRANTS FOR remote_user;
+-----------------------------------------+
| Grants for remote_user@%                |
+-----------------------------------------+
| GRANT USAGE ON *.* TO 'remote_user'@'%' |
+-----------------------------------------+
1 row in set
SQL
```

要注意，引用是非常重要的，特别是当用户帐户包含特殊字符(如`_`或`%`)时。

如果您不小心引用`"username@hostname"`这样的用户帐户，MySQL将创建一个`username@hostname`的用户，并允许用户从任何主机进行连接，这可能不是您预期的。

例如，以下语句创建可以从任何主机连接到MySQL数据库服务器的新用户`api@localhost`(这是用户名，并非用户账号)。

```sql
-- 常用创建用户为：CREATE USER api@'localhost' 与下面语句不同 -
CREATE USER 'api@localhost';
SQL
```

查看上面创建的用户的权限 - 

```sql
mysql> SHOW GRANTS FOR 'api@localhost';
+-------------------------------------------+
| Grants for api@localhost@%                |
+-------------------------------------------+
| GRANT USAGE ON *.* TO 'api@localhost'@'%' |
+-------------------------------------------+
1 row in set
SQL
```

如果创建一个已经存在的用户，MySQL会发出一个错误。 例如，以下语句创建一个名为`remote_user`的用户帐户已经存在：

```sql
CREATE USER remote_user;
SQL
```

上面语句执行后，MySQL发出以下错误信息：

```sql
1396 - Operation CREATE USER failed for 'remote_user'@'%'
SQL
```

请注意，`CREATE USER`语句只是创建一个没有任何权限的新用户帐户。如果要[向用户授予使用权限](http://www.yiibai.com/mysql/grant.html)，则使用`GRANT`语句

## 导出/入数据库

导出：

```shell
mysqldump -u [user] [database_name] > [filename].sql
```





导入:

```mysqlm y
mysql> source c:\temp\mysqlsampledatabase.sql
```

## 给用户授权

```mysql
GRANT ALL ON *.* TO 'super'@'localhost' identified by 'abc123' WITH GRANT OPTION;
```

`ON *.*`子句表示MySQL中的所有数据库和所有对象。`WITH GRANT OPTION`允许`super@localhost`向其他用户授予权限。

##  修改用户名和密码

### 在登陆MySQL的情况下

方法一：通过sql命令修改密码
命令格式：set password for 用户名@localhost = password('新密码'); 

新版本mysql 命令：

```mysql
alter user 用户名@localhos identified by '新密码';
```

* 如果密码为空，则不要加`identified by ''`子句

例子：

```mysql
set password for root@localhost = password('123'); 
# or
alter user 'root'@'localhost' identified by '123';
```



方法二：用UPDATE直接修改user表
--使用mysql数据库

```mysql
use mysql; 
```


--更改user表中指定用户的密码

```mysql
update user set password=password('123') where user='root' and host='localhost'; 
```

--权限刷新

```mysql
flush privileges;
```



### 在没有登陆的情况下

`mysqladmin` 命令
命令格式:   

```mysql
mysqladmin -u用户名 -p旧密码 password 新密码 
```



例子：将root用户的密码由123456改为123

```
mysqladmin   -u root -p 123456 password 123
```





# MYSQL Database Management

### MySQL创建数据库

我们可以在登陆 MySQL 服务后，使用 **create** 命令创建数据库，语法如下:

```mysql
CREATE DATABASE 数据库名;
```

### drop 命令删除数据库

drop 命令格式：

```mysql
drop database <数据库名>;
```


# MYSQL Table Management

### 创建表

```sql
CREATE TABLE table_name (column_name column_type);
```

以下例子中我们将在 RUNOOB 数据库中创建数据表runoob_tbl：

```sql
CREATE TABLE IF NOT EXISTS `runoob_tbl`(
   `runoob_id` INT UNSIGNED AUTO_INCREMENT,
   `runoob_title` VARCHAR(100) NOT NULL,
   `runoob_author` VARCHAR(40) NOT NULL,
   `submission_date` DATE,
   PRIMARY KEY ( `runoob_id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
```

实例解析：

- 如果你不想字段为 **NULL** 可以设置字段的属性为 **NOT NULL**， 在操作数据库时如果输入该字段的数据为**NULL** ，就会报错。
- AUTO_INCREMENT定义列为自增的属性，一般用于主键，数值会自动加1。
- PRIMARY KEY关键字用于定义列为主键。 您可以使用多列来定义主键，列间以逗号分隔。
- ENGINE 设置存储引擎，CHARSET 设置编码。

### 删除表

```sql
DROP TABLE table_name ;
```

### 查看表

* 列出当前数据库的所有表：`SHOW TABLES;`

* 查看表的结构: `DESC [table_name]`

  * 这里`DESC`是`describe`的缩写

  * 还有个`DESC`是`descend`的缩写：

    `select ename,sal from emp order by sal desc; `

    * 手动指定按照薪水由大到小排序（降序关键字`desc`） 

  * 查看创建表的SQL语句：`SHOW CREATE TABLE [table_name];`



### 插入记录

MySQL 表中使用 **INSERT INTO** SQL语句来插入数据。

你可以通过 mysql> 命令提示窗口中向数据表中插入数据，或者通过PHP脚本来插入数据。

以下为向MySQL数据表插入数据通用的 **INSERT INTO** SQL语法：

```
INSERT INTO table_name ( field1, field2,...fieldN )
                       VALUES
                       ( value1, value2,...valueN );
```

如果数据是字符型，必须使用单引号或者双引号，如："value"。

如果数据是DATE类型， 则不需要输入连字符， 如`2019-08-01`， 则插入`20190721`





### 修改字段

* 如果要给`students`表新增一列`birth`，使用：

  `ALTER TABLE students ADD COLUMN birth VARCHAR(10) NOT NULL;`

* 要修改birth列，例如把列名改为birthday，类型改为VARCHAR(20)：

  `ALTER TABLE students CHANGE COLUMN birth birthday VARCHAR(20) NOT NULL;`

* 要删除列，使用：

  `ALTER TABLE students DROP COLUMN birthday;`
