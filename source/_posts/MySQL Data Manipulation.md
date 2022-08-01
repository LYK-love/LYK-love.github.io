---
title: MySQL Data Manipulation
tags: Database
categories: Technology
---

Outline:

* SELECT
* ORDER BY
* ...

Mysql语法简介



<!--more-->



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

注意： `limit`作用于结果集产生的最后，在`order by`之后，所以要先`order by`, 再 `lmit`

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

## IS NULL

To test whether a value is `NULL` or not, you use the  `IS NULL` operator. Here’s the basic syntax of the `IS NULL` operator:

```
value IS NULLCode language: SQL (Structured Query Language) (sql)
```

If the value is `NULL`, the expression returns true. Otherwise, it returns false.

Note that MySQL does not have a built-in [`BOOLEAN`](https://www.mysqltutorial.org/mysql-boolean/) type. It uses the [`TINYINT(1)`](https://www.mysqltutorial.org/mysql-int/) to represent the `BOOLEAN` values i.e.,  true means 1 and false means 0.

Because the `IS NULL` is a comparison operator, you can use it anywhere that an operator can be used e.g., in the [`SELECT`](https://www.mysqltutorial.org/mysql-select-statement-query-data.aspx) or [`WHERE`](https://www.mysqltutorial.org/mysql-where/) clause.

See the following example:

```sql
SELECT 1 IS NULL,  -- 0
       0 IS NULL,  -- 0
       NULL IS NULL; -- 1Code language: SQL (Structured Query Language) (sql)
```

To check if a value is not `NULL`, you use `IS NOT NULL` operator:

```sql
value IS NOT NULLCode language: SQL (Structured Query Language) (sql)
```

This expression returns true (1) if the value is not `NULL`. Otherwise, it returns false (0).

Consider the following example:

```sql
SELECT 1 IS NOT NULL, -- 1
       0 IS NOT NULL, -- 1
       NULL IS NOT NULL; -- 0Code language: SQL (Structured Query Language) (sql)
```

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



可以按多个字段`group by`，用逗号分隔:

```sql
select 
    gender, university,
    count(device_id) as user_num,
    avg(active_days_within_30) as avg_active_days,
    avg(question_cnt) as avg_question_cnt
from user_profile
group by gender, university # 多个字段
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

子查询如果用在`FROM`子句，则返回的结果集是一张临时表，被称为“导出表”， 导出表一定要有别名， 好作为一张表被引用

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



* `UNION`默认是`UNION DISTINCT`； 要保留重复的行，需要使用`UNION ALL`

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



## INSERT



```sql
INSERT INTO table(c1,c2,...)
VALUES (v1,v2,...);
```

* The number of columns and values must be the same. In addition, the positions of columns must be corresponding with the positions of their values



To [insert multiple rows](https://www.mysqltutorial.org/mysql-insert-multiple-rows/) into a table using a single `INSERT` statement, you use the following syntax:

```sql
INSERT INTO table(c1,c2,...)
VALUES 
   (v11,v12,...),
   (v21,v22,...),
    ...
   (vnn,vn2,...);
```

### insert using default value

If you want to insert a default value into a column, you have two ways:

- Ignore both the column name and value in the `INSERT` statement.
- Specify the column name in the `INSERT INTO` clause and use the `DEFAULT` keyword in the `VALUES` clause.

The following example demonstrates the second way:

```
INSERT INTO tasks(title,priority)
VALUES('Understanding DEFAULT keyword in INSERT statement',DEFAULT);Code language: SQL (Structured Query Language) (sql)
```

In this example, we specified the `priority` column and the  `DEFAULT` keyword.

Because the default value for the column `priority` is 3 as declared in the table definition:

```
priority TINYINT NOT NULL DEFAULT 3Code language: SQL (Structured Query Language) (sql)
```

MySQL uses the number 3 to insert into the `priority` column.

### Inserting dates

To insert a literal date value into a column, you use the following format:

```
'YYYY-MM-DD'Code language: SQL (Structured Query Language) (sql)
```

In this format:

- `YYYY` represents a four-digit year e.g., 2018.
- `MM` represents a two-digit month e.g., 01, 02, and 12.
- `DD` represents a two-digit day e.g., 01, 02, 30.

The following statement inserts a new row to the `tasks` table with the start and due date values:

```
INSERT INTO tasks(title, start_date, due_date)
VALUES('Insert date into table','2018-01-09','2018-09-15');Code language: SQL (Structured Query Language) (sql)
```

The following picture shows the contents of the `tasks` table after the insert:

![MySQL INSERT dates into table](https://www.mysqltutorial.org/wp-content/uploads/2018/09/MySQL-INSERT-dates-into-table.png)

It is possible to use expressions in the `VALUES` clause. For example, the following statement adds a new task using the current date for start date and due date columns:

```
INSERT INTO tasks(title,start_date,due_date)
VALUES('Use current date for the task',CURRENT_DATE(),CURRENT_DATE())Code language: SQL (Structured Query Language) (sql)
```

In this example, we used the `CURRENT_DATE()` function as the values for the `start_date` and `due_date` columns. Note that the `CURRENT_DATE()` function is a [date function](https://www.mysqltutorial.org/mysql-date-functions/) that returns the current system date.

## Insert Into Select

In the previous tutorial, you learned how to insert one or more rows into a table using the `INSERT` statement with a list of column values specified in the `VALUES` clause.

```
INSERT INTO table_name(c1,c2,...)
VALUES(v1,v2,..);Code language: SQL (Structured Query Language) (sql)
```

Besides using row values in the `VALUES` clause, you can use the result of a `SELECT` statement as the data source for the `INSERT` statement.

The following illustrates the syntax of the `INSERT INTO SELECT` statement:

```
INSERT INTO table_name(column_list)
SELECT 
   select_list 
FROM 
   another_table
WHERE
   condition;Code language: SQL (Structured Query Language) (sql)
```

In this syntax, instead of using the `VALUES` clause, you can use a `SELECT` statement. The `SELECT` statement can retrieve data from one or more tables.

The `INSERT INTO SELECT` statement is very useful when you want to copy data from other tables to a table or to summary data from multiple tables into a table.



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
CASE case_value
   WHEN when_value1 THEN statements
   WHEN when_value2 THEN statements
   ...
   [ELSE else-statements]
END CASE;

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

### ROUND(X,D)

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



# Aggregate Functions

```sql
function_name(DISTINCT | ALL expression)
```

* use `DISTINCT` if you want to calculate based on distinct values or `ALL` in case you want to calculate all values including duplicates. The default is `ALL`
* The aggregate functions are often used with the `GROUP BY` clause to calculate an aggregate value for each group

## AVG()

The `AVG()` function calculates the average value of a set of values. It ignores NULL in the calculation.

```sql
AVG(expression)
```



## COUNT()

The `COUNT()` function returns the number of the value in a set.

For example, you can use the `COUNT()` function to get the number of products in the `products` table as shown in the following query:

```sql
SELECT 
    COUNT(*) AS total
FROM 
    products;
```

## SUM()

The `SUM()` function returns the sum of values in a set. The `SUM()` function ignores `NULL`. If no matching row found, the `SUM()` function returns NULL.

To get the total order value of each product, you can use the `SUM()` function in conjunction with the `GROUP BY` clause as follows:

```sql
SELECT 
    productCode, 
    SUM(priceEach * quantityOrdered) total
FROM
    orderDetails
GROUP BY productCode
ORDER BY total DESC;
```

## MAX()

The `MAX()` function returns the maximum value in a set.

```
MAX(expression)Code language: SQL (Structured Query Language) (sql)
```

For example, you can use the `MAX()` function to get the highest buy price from the `products` table as shown in the following query:

```
SELECT 
     MAX(buyPrice) highest_price
FROM 
     products;
```

# CONSTRAINTS

## Primary Key

When you define a primary key for a table, MySQL automatically [creates an index](https://www.mysqltutorial.org/mysql-index/mysql-create-index/) called `PRIMARY`

### 1) Define a `PRIMARY KEY` constraint in `CREATE TABLE`

Typically, you define the primary key for a table in the `CREATE TABLE` statement.

If the primary key has one column, you can use the `PRIMARY KEY` constraint as a column constraint:

```
CREATE TABLE table_name(
    primary_key_column datatype PRIMARY KEY,
    ...
);Code language: SQL (Structured Query Language) (sql)
```

When the primary key has more than one column, you must use the `PRIMARY KEY` constraint as a table constraint.

```
CREATE TABLE table_name(
    primary_key_column1 datatype,
    primary_key_column2 datatype,
    ...,
    PRIMARY KEY(column_list)
);Code language: SQL (Structured Query Language) (sql)
```

In this syntax, you separate columns in the `column_list` by commas (,).

The `PRIMARY KEY` table constraint can be used when the primary key has one column:

```
CREATE TABLE table_name ( 
    primary_key_column datatype, 
    ... ,
    PRIMARY KEY(primary_key_column)
);
```

## Foreign Key

A foreign key is a column or group of columns in a table that links to a column or group of columns in another table. The foreign key places constraints on data in the related tables, which allows MySQL to maintain referential integrity.



Once a foreign key constraint is in place, the foreign key columns from the child table must have the corresponding row in the parent key columns of the parent table or values in these foreign key column must be `NULL` (see the `SET NULL` action example below).

### Self-referencing foreign key

Sometimes, the child and parent tables may refer to the same table. In this case, the foreign key references back to the primary key within the same table.

See the following `employees` table from the [sample database](https://www.mysqltutorial.org/mysql-sample-database.aspx).

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/employees.png)

The `reportTo` column is a foreign key that refers to the `employeeNumber` column which is the primary key of the `employees` table.

This relationship allows the `employees` table to store the reporting structure between employees and managers. Each employee reports to zero or one employee and an employee can have zero or many subordinates.

The foreign key on the column `reportTo` is known as a *recursive* or *self-referencing* foreign key.

## MySQL `FOREIGN KEY` syntax

Here is the basic syntax of defining a foreign key constraint in the `CREATE TABLE` or `ALTER TABLE` statement:

```
[CONSTRAINT constraint_name]
FOREIGN KEY [foreign_key_name] (column_name, ...)
REFERENCES parent_table(colunm_name,...)
[ON DELETE reference_option]
[ON UPDATE reference_option]Code language: SQL (Structured Query Language) (sql)
```

In this syntax:

First, specify the name of foreign key constraint that you want to create after the `CONSTRAINT` keyword. If you omit the constraint name, MySQL automatically generates a name for the foreign key constraint.

Second, specify a list of comma-separated foreign key columns after the `FOREIGN KEY` keywords. The foreign key name is also optional and is generated automatically if you skip it.

Third, specify the parent table followed by a list of comma-separated columns to which the foreign key columns reference.

Finally, specify how foreign key maintains the referential integrity between the child and parent tables by using the `ON DELETE` and `ON UPDATE` clauses. The `reference_option` determines action which MySQL will take when values in the parent key columns are deleted (`ON DELETE`) or updated (`ON UPDATE`).

MySQL has five reference options: `CASCADE`, `SET NULL`, `NO ACTION`, `RESTRICT`, and `SET DEFAULT`.

- `CASCADE`: if a row from the parent table is deleted or updated, the values of the matching rows in the child table automatically deleted or updated.
- `SET NULL`: if a row from the parent table is deleted or updated, the values of the foreign key column (or columns) in the child table are set to `NULL`.
- `RESTRICT`: if a row from the parent table has a matching row in the child table, MySQL rejects deleting or updating rows in the parent table.
- `NO ACTION`: is the same as `RESTRICT`.
- `SET DEFAULT`: is recognized by the MySQL parser. However, this action is rejected by both InnoDB and NDB tables.

In fact, MySQL fully supports three actions: `RESTRICT`, `CASCADE` and `SET NULL`.

If you don’t specify the `ON DELETE` and `ON UPDATE` clause, the default action is `RESTRICT`.

## MySQL `FOREIGN KEY` examples

Let’s [create a new database](https://www.mysqltutorial.org/mysql-create-database/) called `fkdemo` for the demonstration.

```
CREATE DATABASE fkdemo;

USE fkdemo;Code language: SQL (Structured Query Language) (sql)
```

### `RESTRICT` & `NO ACTION` actions

Inside the `fkdemo` database, create two tables `categories` and `products`:

```
CREATE TABLE categories(
    categoryId INT AUTO_INCREMENT PRIMARY KEY,
    categoryName VARCHAR(100) NOT NULL
) ENGINE=INNODB;

CREATE TABLE products(
    productId INT AUTO_INCREMENT PRIMARY KEY,
    productName varchar(100) not null,
    categoryId INT,
    CONSTRAINT fk_category
    FOREIGN KEY (categoryId) 
        REFERENCES categories(categoryId)
) ENGINE=INNODB;Code language: SQL (Structured Query Language) (sql)
```

The `categoryId` in the `products` table is the foreign key column that refers to the `categoryId` column in the `categories` table.

Because we don’t specify any `ON UPDATE` and `ON DELETE` clauses, the default action is `RESTRICT` for both update and delete operation.

The following steps illustrate the `RESTRICT` action.

\1) [Insert two rows](https://www.mysqltutorial.org/mysql-insert-multiple-rows/) into the `categories` table:

```
INSERT INTO categories(categoryName)
VALUES
    ('Smartphone'),
    ('Smartwatch');Code language: SQL (Structured Query Language) (sql)
```

\2) [Select](https://www.mysqltutorial.org/mysql-select-statement-query-data.aspx) data from the `categories` table:

```
SELECT * FROM categories;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-categories-table.png)

\3) [Insert a new row](https://www.mysqltutorial.org/mysql-insert-statement.aspx) into the `products` table:

```
INSERT INTO products(productName, categoryId)
VALUES('iPhone',1);Code language: SQL (Structured Query Language) (sql)
```

It works because the `categoryId` 1 exists in the `categories` table.

\4) Attempt to insert a new row into the `products` table with a `categoryId` value does not exist in the `categories` table:

```
INSERT INTO products(productName, categoryId)
VALUES('iPad',3);Code language: SQL (Structured Query Language) (sql)
```

MySQL issued the following error:

```
Error Code: 1452. Cannot add or update a child row: a foreign key constraint fails (`fkdemo`.`products`, CONSTRAINT `fk_category` FOREIGN KEY (`categoryId`) REFERENCES `categories` (`categoryId`) ON DELETE RESTRICT ON UPDATE RESTRICT)Code language: JavaScript (javascript)
```

\5) Update the value in the `categoryId` column in the `categories` table to `100`:

```
UPDATE categories
SET categoryId = 100
WHERE categoryId = 1;
Code language: SQL (Structured Query Language) (sql)
```

MySQL issued this error:

```
Error Code: 1451. Cannot delete or update a parent row: a foreign key constraint fails (`fkdemo`.`products`, CONSTRAINT `fk_category` FOREIGN KEY (`categoryId`) REFERENCES `categories` (`categoryId`) ON DELETE RESTRICT ON UPDATE RESTRICT)Code language: JavaScript (javascript)
```

Because of the `RESTRICT` option, you cannot delete or update `categoryId 1` since it is referenced by the `productId` `1` in the `products` table.

### `CASCADE` action

These steps illustrate how `ON UPDATE CASCADE` and `ON DELETE CASCADE` actions work.

\1) [Drop](https://www.mysqltutorial.org/mysql-drop-table) the `products` table:

```
DROP TABLE products;Code language: SQL (Structured Query Language) (sql)
```

\2) Create the `products` table with the `ON UPDATE CASCADE` and `ON DELETE CASCADE` options for the foreign key:

```
CREATE TABLE products(
    productId INT AUTO_INCREMENT PRIMARY KEY,
    productName varchar(100) not null,
    categoryId INT NOT NULL,
    CONSTRAINT fk_category
    FOREIGN KEY (categoryId) 
    REFERENCES categories(categoryId)
        ON UPDATE CASCADE
        ON DELETE CASCADE
) ENGINE=INNODB;Code language: SQL (Structured Query Language) (sql)
```

\3) Insert four rows into the `products` table:

```
INSERT INTO products(productName, categoryId)
VALUES
    ('iPhone', 1), 
    ('Galaxy Note',1),
    ('Apple Watch',2),
    ('Samsung Galary Watch',2);
Code language: SQL (Structured Query Language) (sql)
```

\4) Select data from the `products` table:

```
SELECT * FROM products;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-products-table.png)

\5) Update `categoryId` 1 to 100 in the `categories` table:

```
UPDATE categories
SET categoryId = 100
WHERE categoryId = 1;Code language: SQL (Structured Query Language) (sql)
```

\6) Verify the update:

```
SELECT * FROM categories;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-categories-table-cascade.png)

\7) Get data from the `products` table:

```
SELECT * FROM products;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-products-table-update-cascade-.png)

As you can see, two rows with value `1` in the `categoryId` column of the `products` table were automatically updated to `100` because of the `ON UPDATE CASCADE` action.

\8) Delete `categoryId` 2 from the `categories` table:

```
DELETE FROM categories
WHERE categoryId = 2;
Code language: SQL (Structured Query Language) (sql)
```

\9) Verify the deletion:

```
SELECT * FROM categories;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-categories-table-delete-cascade.png)

\10) Check the `products` table:

```
SELECT * FROM products;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-products-table-delete-cascade.png)

All products with `categoryId` 2 from the `products` table were automatically deleted because of the `ON DELETE CASCADE` action.

### `SET NULL` action

These steps illustrate how the `ON UPDATE SET NULL` and `ON DELETE SET NULL` actions work.

\1) Drop both `categories` and `products` tables:

```
DROP TABLE IF EXISTS categories;
DROP TABLE IF EXISTS products;
Code language: SQL (Structured Query Language) (sql)
```

\2) Create the `categories` and `products` tables:

```
CREATE TABLE categories(
    categoryId INT AUTO_INCREMENT PRIMARY KEY,
    categoryName VARCHAR(100) NOT NULL
)ENGINE=INNODB;

CREATE TABLE products(
    productId INT AUTO_INCREMENT PRIMARY KEY,
    productName varchar(100) not null,
    categoryId INT,
    CONSTRAINT fk_category
    FOREIGN KEY (categoryId) 
        REFERENCES categories(categoryId)
        ON UPDATE SET NULL
        ON DELETE SET NULL 
)ENGINE=INNODB;
Code language: SQL (Structured Query Language) (sql)
```

The foreign key in the `products` table changed to `ON UPDATE SET NULL` and `ON DELETE SET NULL` options.

\3) Insert rows into the `categories` table:

```
INSERT INTO categories(categoryName)
VALUES
    ('Smartphone'),
    ('Smartwatch');
Code language: SQL (Structured Query Language) (sql)
```

\4) Insert rows into the `products` table:

```
INSERT INTO products(productName, categoryId)
VALUES
    ('iPhone', 1), 
    ('Galaxy Note',1),
    ('Apple Watch',2),
    ('Samsung Galary Watch',2);
Code language: SQL (Structured Query Language) (sql)
```

\5) Update `categoryId` from 1 to 100 in the `categories` table:

```
UPDATE categories
SET categoryId = 100
WHERE categoryId = 1;Code language: SQL (Structured Query Language) (sql)
```

\6) Verify the update:

```
SELECT * FROM categories;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-categories-table-set-null.png)

\7) Select data from the `products` table:

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-products-table-set-null.png)

The rows with the `categoryId` 1 in the `products` table were automatically set to `NULL` due to the `ON UPDATE SET NULL` action.

\8) Delete the `categoryId` 2 from the `categories` table:

```
DELETE FROM categories 
WHERE categoryId = 2;Code language: SQL (Structured Query Language) (sql)
```

\9) Check the `products` table:

```
SELECT * FROM products;Code language: SQL (Structured Query Language) (sql)
```

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/08/MySQL-Foreign-Key-products-table-on-delete-set-null.png)

The values in the `categoryId` column of the rows with `categoryId` 2 in the `products` table were automatically set to `NULL` due to the `ON DELETE SET NULL` action.

## Drop MySQL foreign key constraints

To drop a foreign key constraint, you use the `ALTER TABLE` statement:

```
ALTER TABLE table_name 
DROP FOREIGN KEY constraint_name;Code language: SQL (Structured Query Language) (sql)
```

In this syntax:

- First, specify the name of the table from which you want to drop the foreign key after the `ALTER TABLE` keywords.
- Second, specify the constraint name after the `DROP FOREIGN KEY` keywords.

Notice that `constraint_name` is the name of the foreign key constraint specified when you created or added the foreign key constraint to the table.

To obtain the generated constraint name of a table, you use the `SHOW CREATE TABLE` statement:

```
SHOW CREATE TABLE table_name;Code language: SQL (Structured Query Language) (sql)
```

For example, to see the foreign keys of the `products` table, you use the following statement:

```
SHOW CREATE TABLE products;Code language: SQL (Structured Query Language) (sql)
```

The following is the output of the statement:

![img](https://www.mysqltutorial.org/wp-content/uploads/2019/09/MySQL-Foreign-Key-drop-foreign-key-constraint.png)

As you can see clearly from the output, the table `products` table has one foreign key constraint: `fk_category`

And this statement drops the foreign key constraint of the `products` table:

```
ALTER TABLE products 
DROP FOREIGN KEY fk_category;Code language: SQL (Structured Query Language) (sql)
```

To ensure that the foreign key constraint has been dropped, you can view the structure of the products table:

```
SHOW CREATE TABLE products;Code language: SQL (Structured Query Language) (sql)
```

![MySQL Foreign Key - after drop foreign key constraint](https://www.mysqltutorial.org/wp-content/uploads/2019/09/MySQL-Foreign-Key-after-drop-foreign-key-constraint.png)

## Disabling foreign key checks

Sometimes, it is very useful to disable foreign key checks e.g., when you [import data from a CSV file into a table](https://www.mysqltutorial.org/import-csv-file-mysql-table/). If you don’t disable foreign key checks, you have to load data into a proper order i.e., you have to load data into parent tables first and then child tables, which can be tedious. However, if you disable the foreign key checks, you can load data into tables in any order.

To disable foreign key checks, you use the following statement:

```
SET foreign_key_checks = 0;Code language: SQL (Structured Query Language) (sql)
```

And you can enable it by using the following statement:

```
SET foreign_key_checks = 1;Code language: SQL (Structured Query Language) (sql)
```

In this tutorial, you have learned about the MySQL foreign key and how to create a foreign key constraint with various reference options.

# DATA TYPES

# GLOBALIZARION

# IMPORT & EXPORT

# Retrieving records
