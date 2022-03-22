---
title: MySQL Basic
tags: Database
categories: Technology
---

Outline:

* MYSQL Management
* Managing  Databases
* Managing Tables
* MYSQL Data Manipulation



<!--more-->

# MySQL管理

### 启动及关闭

启动MySQL:

```sql
cd D:\mysql-8.0.23-winx64\bin
net start mysql
```

<!--more-->

### 登录MySQL

当 MySQL 服务已经运行时, 我们可以通过 MySQL 自带的客户端工具登录到 MySQL 数据库中, 首先打开命令提示符, 输入以下格式的命名:

```sql
mysql -h 主机名 -u 用户名 -p
```

参数说明：

- **-h** : 指定客户端所要登录的 MySQL 主机名, 登录本机(localhost 或 127.0.0.1)该参数**可以省略**;
- **-u** : 登录的用户名;
- **-p** : 告诉服务器将会使用一个密码来登录, 如果所要登录的用户名密码为空, 可以忽略此选项。

如果我们要登录本机的 MySQL 数据库，只需要输入以下命令即可：

```sql
mysql -u root -p
```

按回车确认, 如果安装正确且 MySQL 正在运行, 会得到以下响应:

```
Enter password:
```

若密码存在, 输入密码登录, 不存在则直接按回车登录。登录成功后你将会看到 Welcome to the MySQL monitor... 的提示语。

然后命令提示符会一直以 **mysq>** 加一个闪烁的光标等待命令的输入, 输入 **exit** 或 **quit** 退出登录( 但不会关闭服务 )。

### 启动及关闭MySQL服务器

在Windows下:

```sql
cd D:\mysql-8.0.23-winx64\bin
mysqld --console
```

### 管理MySQL的命令

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







# MANAGING DATABASES

### MySQL创建数据库

我们可以在登陆 MySQL 服务后，使用 **create** 命令创建数据库，语法如下:

```sql
CREATE DATABASE 数据库名;
```

### drop 命令删除数据库

drop 命令格式：

```sql
drop database <数据库名>;
```

# MANAGING TABLES

### MySQL创建数据表

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

### MySQL 删除数据表

MySQL中删除数据表是非常容易操作的，但是你在进行删除表操作时要非常小心，因为执行删除命令后所有数据都会消失。

以下为删除MySQL数据表的通用语法：

```sql
DROP TABLE table_name ;
```

### MySQL 插入数据

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

### 读取数据表：

`select * from runoob_tbl;`

## manage MySQL

* 列出当前数据库的所有表：`SHOW TABLES;`

* 查看表的结构: `DESC [table_name]`

  * 这里`DESC`是`describe`的缩写

  * 还有个`DESC`是`descend`的缩写：

    `select ename,sal from emp order by sal desc; `

    * 手动指定按照薪水由大到小排序（降序关键字`desc`） 

  * 查看创建表的SQL语句：`SHOW CREATE TABLE [table_name];`

* 创建表使用`CREATE TABLE`语句，而删除表使用`DROP TABLE`语句：

  ```
  mysql> DROP TABLE students;
  Query OK, 0 rows affected (0.01 sec)
  ```

* 修改表就比较复杂。如果要给`students`表新增一列`birth`，使用：

  `ALTER TABLE students ADD COLUMN birth VARCHAR(10) NOT NULL;`

* 要修改birth列，例如把列名改为birthday，类型改为VARCHAR(20)：

  `ALTER TABLE students CHANGE COLUMN birth birthday VARCHAR(20) NOT NULL;`

* 要删除列，使用：

  `ALTER TABLE students DROP COLUMN birthday;`

# MYSQL DATA MANIPULATION

## SELECT

```mysql
SELECT select_list
FROM table_name;
```

* `;`是可选的，表明一条语句的结束
* SQL是大小写不敏感的，因此`SELECT0`，`FROM`这些关键字可大写可小写
* `SELECT`的结果称为一个结果集
* 如果SELECT的参数是空行（连NULL都没有)，会返回NULL。 



 ### Returning n Random Records from a Table

```mysql
select ename, job
	from emp
order by rand() limit 5
```



### Transforming Nulls into Real Values

Use the function COALESCE to substitute real values for nulls:

```mysql
select coalesce(comm, 0)
	from emp
```

COALESCE 接受至少一个参数，返回第一个非空参数。 如果comm为null,则返回0



或者：

```mysql
select case
		when comm is not null then comm
		else 0
		end
	from emp
```



## ORDER BY

默认是`ASC`

```mysql
SELECT 
   select_list
FROM 
   table_name
ORDER BY 
   column1 [ASC|DESC], 
   column2 [ASC|DESC],
   ...;
```

ORDER BY的参数一般是字段，当然也可以是列号， 但后一种方式不推荐

```mysql
SELECT 
    CONCAT(firstName,' ',lastName) fullname
FROM
    employees 
UNION SELECT 
    CONCAT(contactFirstName,' ',contactLastName)
FROM
    customers
ORDER BY 1; # 采用列号（第一列）
```



## WHERE

![ MySQL WHERE](https://www.mysqltutorial.org/wp-content/uploads/2021/07/MySQL-Where.svg)



```mysql
SELECT 
    select_list
FROM
    table_name
WHERE
    search_condition;
```

The `search_condition` is a combination of one or more expressions using the logical operator `AND`, `OR` and `NOT`.

In MySQL, a predicate is a Boolean expression that evaluates to `TRUE`, `FALSE`, or `UNKNOWN`.

The `SELECT` statement will include any row that satisfies the `search_condition` in the result set.

Besides the `SELECT` statement, you can use the `WHERE` clause in the `UPDATE` or [`DELETE`](https://www.mysqltutorial.org/mysql-delete-statement.aspx) statement to specify which rows to update or delete.

When executing a `SELECT` statement with a `WHERE` clause, MySQL evaluates the `WHERE` clause after the `FROM` clause and before the `SELECT` and `ORDER BY` clauses:





### BETWEEN

`expression BETWEEN low AND high`

### LIKE

The `LIKE` operator evaluates to `TRUE` if a value matches a specified pattern.

To form a pattern, you use the `%` and `_` wildcards. 

* **The `%` wildcard matches any string of zero or more characters**
* **the `_` wildcard matches any single character.**

The following query finds the employees whose last names end with the string `'son'`:

```mysql
SELECT 
    firstName, 
    lastName
FROM
    employees
WHERE
    lastName LIKE '%son'
ORDER BY firstName;
```



### IN

The `IN` operator returns `TRUE` if a value matches any value in a list.

```mysql
value IN (value1, value2,...)
```

The following example uses the `WHERE` clause with the `IN` operator to find employees who locate in the office with office code 1.

```mysql
SELECT 
    firstName, 
    lastName, 
    officeCode
FROM
    employees
WHERE
    officeCode IN (1 , 2, 3)
ORDER BY 
    officeCode;
```



### IS NULL

To check if a value is `NULL` or not, you use the `IS NULL` operator, not the equal operator (`=`). The `IS NULL` operator returns `TRUE` if a value is `NULL`.

```
value IS NULLCode language: SQL (Structured Query Language) (sql)
```

> In the database world, `NULL` is a marker that indicates that a value is missing or unknown. And NULL is not equivalent to the number 0 or an empty string.

对应的，还有`IS NOT NULL`

## LIMIT

The `LIMIT` clause is used in the `SELECT` statement to constrain the number of rows to return. 

```mysql
SELECT 
    select_list
FROM
    table_name
LIMIT [offset,] row_count; ( OR LIMIT row_count OFFSET offset; )
```

- The `offset` specifies the offset of the first row to return. OFFSET从0开始计数，缺省也为0

- The `row_count` specifies the maximum number of rows to return.

- `LIMIT`子句对于超过其范围的行，会返回空行而不是`NULL`：

  ```mysql
  select salary from `Employee` limit 1 offset 1
  # 如果Employee只有一行，则该查询返回空行：
  +--------+
  | salary |
  +--------+
  +--------+
  # 不会返回null
  ```

  



 可以和`ORDER BY`结合：

```mysql
SELECT 
    select_list
FROM 
    table_name
ORDER BY 
    sort_expression
LIMIT offset, row_count;
```





示例： get the highest or lowest rows

```mysql
SELECT 
    customerNumber, 
    customerName, 
    creditLimit
FROM
    customers
ORDER BY creditLimit DESC
LIMIT 5;
```

- First, the `ORDER BY` clause sorts the customers by credits in high to low.
- Then, the `LIMIT` clause returns the first 5 rows.

## SELECT DISTINCT

```mysql
SELECT DISTINCT
    select_list
FROM
    table_name
WHERE 
    search_condition
ORDER BY 
    sort_expression;
```

* `DISTINCT`:   从选出的行中选择唯一的
* 如果`DISTINCT`后面跟多个字段，就会将这些字段作为一个整体来判断唯一性
* MYSQL认为所有NULL都是相等的，因此多个NULL在DISTINCT后只剩下一个

![distinct](/home/lyk/Pictures/assets_for_hexo/DataBase/DISTINCT)



## Alias

**在一次查询中重复引用一个表名会引发ERROR**， 因此要定义别名



列别名：

```MYSQL
SELECT 
   [column_1 | expression] [AS] descriptive_name
FROM table_name;

//如果别名有空格，需要用引号括起来：‘descriptive name’
```



表达式别名：

```mysql
SELECT
   CONCAT_WS(', ', lastName, firstname) [AS] `Full name`
FROM
   employees;
```



表别名：

```mysql
table_name [AS] table_alias
```



## JOIN

A join is a method of linking data between one ([self-join](http://www.mysqltutorial.org/mysql-self-join/)) or more tables based on values of the common column between the tables.

MySQL supports the following types of joins:

1. [Inner join](https://www.mysqltutorial.org/mysql-inner-join.aspx)
2. [Left join](https://www.mysqltutorial.org/mysql-left-join.aspx)
3. [Right join](https://www.mysqltutorial.org/mysql-right-join/)
4. [Cross join](https://www.mysqltutorial.org/mysql-cross-join/)

To join tables, you use the cross join, inner join, left join, or right join clause. The join clause is used in the `SELECT` statement appeared after the `FROM` clause.

Note that MySQL hasn’t supported the `FULL OUTER JOIN` yet.

Join会创建一个包含原本两方所有字段的新行，并加入结果集

### INNER JOIN

```mysql
SELECT column_list
FROM table_1
INNER JOIN table_2 ON join_condition;
```

The inner join clause compares each row from the first table with every row from the second table.

将左边的每一行与右边的所有行匹配

只有两边的行同时满足，才会被join



如果两张表中作为条件来比较的字段相同，那么可以用` USING`来替代`ON`：

```MYSQL
using(id)
#  等价于
on a.id=b.id
```





### LEFT JOIN![mysql join - left join](https://www.mysqltutorial.org/wp-content/uploads/2019/08/mysql-join-left-join.png)

对于左边的一行，如果右边的行都不满足条件，依然会创建出新行，只不过新行中，原来的右边的行的字段的对应值为NULL



```mysql
SELECT 
    c.customerNumber, 
    c.customerName, 
    o.orderNumber, 
    o.status
FROM
    customers c
LEFT JOIN orders o 
    ON c.customerNumber = o.customerNumber
WHERE
    orderNumber IS NULL;
```



### RIGHT JOIN

从右边的行中选择，将右边的每一行与左边的所有行匹配。 如果左边的所有行都不满足条件，那么依然创建出新行，新行中左边行的字段值为NULL

```mysql
SELECT column_list 
FROM table_1 
RIGHT JOIN table_2 ON join_condition;
```

![mysql join - right join](https://www.mysqltutorial.org/wp-content/uploads/2019/08/mysql-join-right-join.png)

### CROSS JOIN

没有查询条件，产生笛卡尔积

```mysql
SELECT select_list
FROM table_1
CROSS JOIN table_2;
```

### Self Join

一个表和自己做join, 因为同一次查询中不能重复引用同一张表，因此必须定义别名



示例：

```mysql
SELECT 
    CONCAT(m.lastName, ', ', m.firstName) AS Manager,
    CONCAT(e.lastName, ', ', e.firstName) AS 'Direct report'
FROM
    employees e
INNER JOIN employees m ON 
    m.employeeNumber = e.reportsTo
ORDER BY 
    Manager;
```



## GROUP BY

![MySQL GROUP BY](https://www.mysqltutorial.org/wp-content/uploads/2021/07/MySQL-Group-By.svg)



The `GROUP BY` clause **returns one row for each group**. 

可以和聚合函数结合。 不结合聚合函数的`GROUP BY`和`SELECT DISTINCT`是类似的

MYSQL8.0后不会对`GROUP BY`的结果集进行排序



The `GROUP BY` clause is often used with an aggregate function to perform calculations and return a single value for each subgroup.

```mysql
SELECT 
    status, 
    SUM(quantityOrdered * priceEach) AS amount
FROM
    orders
INNER JOIN orderdetails 
    USING (orderNumber)
GROUP BY 
    status;
```



## HAVING

![MySQL Having](https://www.mysqltutorial.org/wp-content/uploads/2021/07/MySQL-Having.svg)



The `HAVING` clause is often used with the `GROUP BY` clause to filter groups based on a specified condition. If you omit the `GROUP BY` clause, the `HAVING` clause behaves like the `WHERE` clause.



```mysql
SELECT 
    select_list
FROM 
    table_name
WHERE 
    search_condition
GROUP BY 
    group_by_expression
HAVING 
    group_condition;
```



## ROLLUP

## Subquery

子查询必须用括号括起来， 可以作为表达式，用在任何需要表达式的地方

其中， 如果用在`FROM`子句，则返回的结果集是一张临时表，被称为“导出表”， 导出表一定要有别名， 好作为一张表被引用

### WHERE

子查询用在`WHERE`子句， 一般是和聚合函数的结合， 将聚合函数的结果返回， 然后在WHERE中进行`条件运算`：

```mysql
SELECT 
    customerNumber, 
    checkNumber, 
    amount
FROM
    payments
WHERE
    amount = (SELECT MAX(amount) FROM payments);
```

#### IN & NOT IN

如果子查询返回不止一个结果（即不止一行）， 那还可以用来作为`[NOT] IN`的参数，在`WHERE`子句中进行条件运算

```mysql
SELECT 
    customerName
FROM
    customers
WHERE
    customerNumber NOT IN (SELECT DISTINCT
            customerNumber
        FROM
            orders);
```



### FROM

子查询作为派生表，必须要有别名

```mysql
SELECT 
    MAX(items), 
    MIN(items), 
    FLOOR(AVG(items))
FROM
    (SELECT 
        orderNumber, COUNT(orderNumber) AS items
    FROM
        orderdetails
    GROUP BY orderNumber) AS lineitems;
```

### correlated subquery

子查询可以是独立的，一共只执行一次；也可以是关联的， 外层查询的每处理一行就执行一次：

```mysql
SELECT 
    productname, 
    buyprice
FROM
    products p1
WHERE
    buyprice > (SELECT 
            AVG(buyprice)
        FROM
            products
        WHERE
            productline = p1.productline)
```

### EXISTS & NOT EXISTS

子查询就是表达式，因此用在`[NOT] EXISTS` 子句中时，子查询只会返回一个BOOL值：

* 只要子查询返回至少一行，就返回TRUE,否则返回FALSE
* 一般而言，作为`EXISTS`参数的子查询都是关联查询，这样才能和外层查询联系起来， 否则如果是独立查询， 每次计算时都返回固定的BOOL值，没什么意义



The following query finds sales orders whose total values are greater than 60K.

```mysql
SELECT 
    orderNumber, 
    SUM(priceEach * quantityOrdered) total
FROM
    orderdetails
        INNER JOIN
    orders USING (orderNumber)
GROUP BY orderNumber
HAVING SUM(priceEach * quantityOrdered) > 60000;
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2013/02/MySQL-subquery-exists.png)

It returns 3 rows, meaning that there are three sales orders whose total values are greater than 60K.

You can use the query above as a correlated subquery to find customers who placed at least one sales order with the total value greater than 60K by using the `EXISTS` operator:

```mysql
SELECT 
    customerNumber, 
    customerName
FROM
    customers
WHERE
    EXISTS( SELECT 
            orderNumber, SUM(priceEach * quantityOrdered)
        FROM
            orderdetails
                INNER JOIN
            orders USING (orderNumber)
        WHERE
            customerNumber = customers.customerNumber
        GROUP BY orderNumber
        HAVING SUM(priceEach * quantityOrdered) > 60000);
```





## Derived Tables

派生表就是用在`SELECT`子句的子查询， 该子查询返回一张表（属于临时表）， 并一定具有别名以被引用



### 例子

Suppose you have to classify the customers who bought products in 2003 into 3 groups: `platinum`, `gold`, and `silver`. And you need to know the number of customers in each group with the following conditions:

- Platinum customers who have orders with the volume greater than 100K.
- Gold customers who have orders with the volume between 10K and 100K.
- Silver customers who have orders with the volume less than 10K.

To form this query, you first need to put each customer into the respective group using `CASE` expression and `GROUP BY` clause as follows:

```mysql
SELECT 
    customerNumber,
    ROUND(SUM(quantityOrdered * priceEach)) sales,
    (CASE
        WHEN SUM(quantityOrdered * priceEach) < 10000 THEN 'Silver'
        WHEN SUM(quantityOrdered * priceEach) BETWEEN 10000 AND 100000 THEN 'Gold'
        WHEN SUM(quantityOrdered * priceEach) > 100000 THEN 'Platinum'
    END) customerGroup
FROM
    orderdetails
        INNER JOIN
    orders USING (orderNumber)
WHERE
    YEAR(shippedDate) = 2003
GROUP BY customerNumber;
```

The following is the output of the query:



Then, you can use this query as the derived table and perform grouping as follows:

```mysql
SELECT 
    customerGroup, 
    COUNT(cg.customerGroup) AS groupCount
FROM
    (SELECT 
        customerNumber,
            ROUND(SUM(quantityOrdered * priceEach)) sales,
            (CASE
                WHEN SUM(quantityOrdered * priceEach) < 10000 THEN 'Silver'
                WHEN SUM(quantityOrdered * priceEach) BETWEEN 10000 AND 100000 THEN 'Gold'
                WHEN SUM(quantityOrdered * priceEach) > 100000 THEN 'Platinum'
            END) customerGroup
    FROM
        orderdetails
    INNER JOIN orders USING (orderNumber)
    WHERE
        YEAR(shippedDate) = 2003
    GROUP BY customerNumber) cg
GROUP BY cg.customerGroup;    
```

The query returns the customer groups and the number of customers in each.

## EXISTS

The `EXISTS` operator is a Boolean operator that returns either true or false. The `EXISTS` operator is often used to test for the existence of rows returned by the [subquery](https://www.mysqltutorial.org/mysql-subquery/).

The following illustrates the basic syntax of the `EXISTS` operator:

```mysql
SELECT 
    select_list
FROM
    a_table
WHERE
    [NOT] EXISTS(subquery);Code language: SQL (Structured Query Language) (sql)
```

If the subquery returns at least one row, the `EXISTS` operator returns true, otherwise, it returns false.

In addition, the `EXISTS` operator terminates further processing immediately once it finds a matching row, which can help improve the performance of the query.

The `NOT` operator negates the `EXISTS` operator. In other words, the `NOT EXISTS` returns true if the subquery returns no row, otherwise it returns false.

Note that you can use `SELECT *`, `SELECT column`, `SELECT a_constant`, or anything in the subquery. The results are the same because MySQL ignores the select list appeared in the `SELECT` clause.

## UNION

```mysql
SELECT column_list
UNION [DISTINCT | ALL]
SELECT column_list
UNION [DISTINCT | ALL]
SELECT column_list
```

`UNION`的参数也是一张表（由`SELECT`子句产生），但不是派生表，因此不需要别名

`UNION`将两张表垂直地并起来， 而`JOIN`将两张表水平地并起来：

![MySQL UNION vs JOIN](https://www.mysqltutorial.org/wp-content/uploads/2009/12/MySQL-UNION-vs-JOIN.png)







要将多张表`UNION`起来，作为`UNION`主语的SELECT和宾语的SELECT子句的对应字段的数量和顺序必须相同， 类型也必须相容

比如：

```sql
SELECT 
    firstName, # 最终结果集的字段名，使用的是UNION主语的SELECT子句的字段名
    lastName
FROM
    employees 
UNION 
SELECT 
    contactFirstName, # 字段名不同无所谓，但是类型，顺序，数量必须相同
    contactLastName
FROM
    customers;
```



* `UNION`默认就是`UNION DISTINCT`； 要保留重复的行，需要使用`UNION ALL`

* `UNION`后产生的大表的字段名用的是`UNION`主语的`SELECT`的字段名

* 使用`ORDER BY`对产生的大表的行进行排序

  * 注意， UNION宾语的那张子表里不需要排序

  ```mysql
  SELECT 
      concat(firstName,' ',lastName) fullname
  FROM
      employees 
  UNION SELECT 
      concat(contactFirstName,' ',contactLastName)
  FROM
      customers
  ORDER BY fullname;
  ```



## MINUS

```mysql
SELECT select_list1 
FROM table_name1
MINUS 
SELECT select_list2 
FROM table_name2;
```





Unfortunately, MySQL does not support `MINUS` operator. However, you can use [join](https://www.mysqltutorial.org/mysql-join/) to emulate it.

To emulate the `MINUS` of two queries, you use the following syntax:

```mysql
SELECT 
    select_list
FROM 
    table1
LEFT JOIN table2 
    ON join_predicate
WHERE 
    table2.column_name IS NULL; 
```



## UPDATE

```mysql
UPDATE salary
SET
    sex = CASE sex
        WHEN 'm' THEN 'f'
        ELSE 'm'
    END;
```



## CASE

`CASE`返回一个字段值

case和when的参数字段都不要加别名， 别名要加在整个case子句后面，也就是`END`后面



### Simple CASE expression

```mysql
CASE expression
WHEN when_expression_1 THEN
	result_1
WHEN when_expression_2 THEN
	result_2
WHEN when_expression_3 THEN
	result_3
...
ELSE
	else_result
END
```

* 如果没有任何一个`WHEN`子句被匹配，则进入`ELSE`子句。 `ELSE`子句是可选的， 如果省略了`ELSE`子句，则不匹配任何when时，直接返回`NULL`



例子：

```mysql
SELECT 
    first_name,
    last_name,
    CASE
        WHEN salary < 3000 THEN 'Low'
        WHEN salary >= 3000 AND salary <= 5000 THEN 'Average'
        WHEN salary > 5000 THEN 'High'
    END evaluation
FROM
    employees;
```



### Searched CASE expression

```mysql
CASE
WHEN boolean_expression_1 THEN
	result_1
WHEN boolean_expression_2 THEN
	result_2
WHEN boolean_expression_3 THEN
	result_3
ELSE
	else_result
END;
```



例子：

```mysql
SELECT 
    first_name,
    last_name,
    CASE
        WHEN salary < 3000 THEN 'Low'
        WHEN salary >= 3000 AND salary <= 5000 THEN 'Average'
        WHEN salary > 5000 THEN 'High'
    END evaluation
FROM
    employees;
```

## DERIVED TABLE

派生表是从[SELECT语句](http://www.yiibai.com/mysql/select-statement-query-data.html)返回的虚拟表。派生表类似于临时表，但是在`SELECT`语句中使用派生表比[临时表](http://www.yiibai.com/mysql/temporary-table.html)简单得多，因为它不需要创建临时表的步骤。

**术语:\***派生表*和[子查询](http://www.yiibai.com/mysql/subquery.html)通常可互换使用。当`SELECT`语句的`FROM`子句中使用独立子查询时，我们将其称为派生表。

以下说明了使用派生表的查询：

![img](http://www.yiibai.com/uploads/images/201707/1907/437150722_21821.png)

> 请注意，独立子查询是一个子查询，可独立于包含该语句的执行语句。

与子查询不同，派生表必须具有[别名](http://www.yiibai.com/mysql/alias.html)，以便稍后在查询中引用其名称。 如果派生表没有别名，MySQL将发出以下错误：

```shell
Every derived table must have its own alias.
Shell
```

以下说明了使用派生表的SQL语句：

```sql
SELECT 
    column_list
FROM
    (SELECT 
        column_list
    FROM
        table_1) derived_table_name;
WHERE derived_table_name.c1 > 0;
```

aA12345678

## FUNCTION

### ROUND

## ROUND(X,D)

​	此函数返回x舍入到最接近的整数。如果第二个参数，D有提供，则函数返回x四舍五入至第D位小数点。D必须是正数

### IFNULL

MySQL `IFNULL`函数是MySQL控制流函数之一，它接受两个参数，如果不是`NULL`，则返回第一个参数。 否则，`IFNULL`函数返回第二个参数。

两个参数可以是文字值或表达式。

以下说明了`IFNULL`函数的语法：

```sql
IFNULL(expression_1,expression_2);
SQL
```

如果`expression_1`不为`NULL`，则`IFNULL`函数返回`expression_1`; 否则返回`expression_2`的结果。

`IFNULL`函数根据使用的上下文返回字符串或数字。

如果要返回基于`TRUE`或`FALSE`条件的值，而不是`NULL`，则应使用[IF函数](http://www.yiibai.com/mysql/if-function.html)。



# 

# 

# CONSTRAINTS

# DATA TYPES

# GLOBALIZARION

# IMPORT & EXPORT

# Retrieving records
