---
categories:
- Software Engineering
date: 2022-04-09 16:44:41
tags: Database
title: MYSQL Management
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

 `CREATE USER`:

```sql
CREATE USER user_account IDENTIFIED BY password;
```

* `user_account`: 格式为`username@hostname`

  * `localhost`: 只允许从本机连接

  * `%`: 相当于通配, **但是不能匹配到 `locahost`**

    * 例如,要允许`mysqladmin`用户帐户从`yiibai.com`主机的任何子域连接到数据库服务:

      ```sql
      CREATE USER mysqladmin@'%.yiibai.com'
      IDENTIFIED by 'mypassword';
      ```

    * 如果只写`username@%`, 则相当于允许 `locahost`外的所有ip

    * 也就是说, `username@%`和`username@localhost`是两个用户!

  * 可以不写hostname, 此时相当于`%`

* `password`: 在`IDENTIFIED BY`子句中指定.
  * `password`必须是明文, 它会被MySQL加密
  * 空密码就是`IDENTIFIED BY ''`
* 新创建的用户只能登录到mysql, 没有其他权限
* 要注意引号`''`, 特别当用户帐户包含特殊字符(如`_`或`%`)时, 比如, 如果你写了`"username@hostname"`, 这其实是一整个username, 而没有包含hostname, 而hostname会被默认设置为`%`
* 这样的用户帐户，MySQL将创建一个`username@hostname`的用户，并允许用户从任何主机进行连接，这可能不是您预期的。

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
GRANT ALL ON *.* TO 'super'@'localhost' WITH GRANT OPTION;
```

* `ON *.*`: 表示MySQL中的所有数据库和所有对象
  * `.`之前的部分表示数据库, `.`后面的部分表示表, 例如`database.table`, `testdb.offices`等等

* `WITH GRANT OPTION`: 允许`super@localhost`向其他用户授予权限



授权后需要刷新权限:

```mysql
flush privileges
```



## 查看用户权限

```mysql
show grants for [user]
```



##  修改用户名和密码

### 在登陆MySQL的情况下

### Plan A: 通过sql命令修改密码

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



### Plan B: 用UPDATE直接修改user表

1. 使用mysql数据库

   ```mysql
   use mysql; 
   ```

2. 更改user表中指定用户的密码

   ```mysql
   update user set password=password('123') where user='root' and host='localhost'; 
   ```

3. 权限刷新

   ```mysql
   flush privileges;
   ```

   

### 在没有登陆的情况下

`mysqladmin` 命令:

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



RENAME用于表的重命名：RENAME <NAME> 或 RENAME TO <NAME>

MODIFY用于字段类型的修改：MODIFY COLUMN  <列名> <类型>

ALTER用于对字段类型、默认值的修改：ALTER COLUMN <列名> <类型>  SET DE***T <默认值>

CHANGE用于对列名及类型的修改：CHANGE COLUMN <旧列名> <新列名> <类型>