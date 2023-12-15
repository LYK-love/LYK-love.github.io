---
categories:
- Software Engineering
date: 2022-08-22 18:51:59
tags: JS
title: Javascript Basic
---

Outline:

* Intro
* Basic
* Function
* ...

<!--more-->

# Intro

* [MDN -> JS](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
* [廖雪峰 ->JS](https://www.liaoxuefeng.com/wiki/1022910821149312)

# Basic

## Object

JavaScript的对象是一种无序的集合数据类型，它由若干键值对组成.

JavaScript用一个`{...}`表示一个对象，键值对以`xxx: xxx`形式申明，用`,`隔开。注意，最后一个键值对不需要在末尾加`,`，如果加了，有的浏览器（如低版本的IE）将报错.

JS对象的属性的key是一个**字符串**, value可以是任意类型.

JS中访问不存在的属性会返回`undefined`：

## 成员访问

如果属性名包含特殊字符，就必须用`''`括起来：

```javascript
let xiaohong = {
    name: '小红',
    'middle-school': 'No.1 Middle School'
};
```

`xiaohong`的属性名`middle-school`不是一个有效的变量，就需要用`''`括起来。访问这个属性也无法使用`.`操作符，必须用`['xxx']`来访问：

```
xiaohong['middle-school']; // 'No.1 Middle School'
xiaohong['name']; // '小红'
xiaohong.name; // '小红'
```

也可以用`xiaohong['name']`来访问`xiaohong`的`name`属性，不过`xiaohong.name`的写法更简洁。我们在编写JavaScript代码的时候，属性名尽量使用标准的变量名，这样就可以直接通过`object.prop`的形式访问一个属性了。



# Function

## Destructuring

ES6支持解构赋值. 这是对容器、对象等对象赋值的语法糖. 

解构赋值可以支持**嵌套结构**, 只需保持赋值时的嵌套的层次一致

### 数组的解构赋值

对数组:

```
let [x, y, z] = ['hello', 'JavaScript', 'ES6'];
```

对嵌套的数组元素的解构赋值:

```javascript
let [x, [y, z]] = ['hello', ['JavaScript', 'ES6']];
```

解构赋值还可以忽略某些元素：

```javascript
let [, , z] = ['hello', 'JavaScript', 'ES6']; // 忽略前两个元素，只对z赋值第三个元素
z; // 'ES6'
```

### 对象的解构赋值

对象的解构赋值是按成员名字匹配的:

```javascript
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678',
    school: 'No.4 middle school'
};
var {name, age, passport} = person;
```

```javascript
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678',
    school: 'No.4 middle school',
    address: {
        city: 'Beijing',
        street: 'No.1 Road',
        zipcode: '100001'
    }
};
var {name, address: {city, zip}} = person;
name; // '小明'
city; // 'Beijing'
zip; // undefined, 因为属性名是zipcode而不是zip
// 注意: address不是变量，而是为了让city和zip获得嵌套的address对象的属性:
address; // Uncaught ReferenceError: address is not defined
```

* 变量名`zip`不匹配对象的`address`属性的`zipcode`, 所以是`undefined`
* `address`没有被赋值为变量



如果要使用的变量名和属性名不一致，可以用下面的语法获取：

```
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678',
    school: 'No.4 middle school'
};

// 把passport属性赋值给变量id:
let {name, passport:id} = person;
name; // '小明'
id; // 'G-12345678'
// 注意: passport不是变量，而是为了让变量id获得passport属性:
passport; // Uncaught ReferenceError: passport is not defined
```

解构赋值还可以使用默认值，这样就避免了不存在的属性返回`undefined`的问题：

```javascript
var person = {
    name: '小明',
    age: 20,
    gender: 'male',
    passport: 'G-12345678'
};

// 如果person对象没有single属性，默认赋值为true:
var {name, single=true} = person;
name; // '小明'
single; // true
```

有些时候，如果变量已经被声明了，再次赋值的时候，正确的写法也会报语法错误：

```javascript
// 声明变量:
let x, y;
// 解构赋值:
{x, y} = { name: '小明', x: 100, y: 200};
// 语法错误: Uncaught SyntaxError: Unexpected token =
```

这是因为JavaScript引擎把`{`开头的语句当作了块处理，于是`=`不再合法。解决方法是用小括号括起来：

```javascript
({x, y} = { name: '小明', x: 100, y: 200});
```

### 应用

假设`props`为:

```javascript
props = {
  name: 'Arto Hellas',
  age: 35,
}
```



React中:

```jsx
const Hello = (props) => {
  const { name, age } = props
  const bornYear = () => new Date().getFullYear() - age

  return (
    <div>
      <p>Hello {name}, you are {age} years old</p>
      <p>So you were probably born in {bornYear()}</p>
    </div>
  )
}
```



可以更加简化, 在形参中写解构赋值:

```jsx
const Hello = ({ name, age }) => {
  //...
}
```





## object spread syntax

[ref](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Spread_syntax)

**Spread syntax** (`...`) allows an iterable, such as an array or string, to be expanded in places where zero or more arguments (for function calls) or elements (for array literals) are expected. In an object literal, the spread syntax enumerates the properties of an object and adds the key-value pairs to the object being created.



```javascript
function sum(x, y, z) {
  return x + y + z;
}

const numbers = [1, 2, 3];

console.log(sum(...numbers));
// expected output: 6

console.log(sum.apply(null, numbers));
// expected output: 6
```

### 应用

在React中, `useState()`可以和解构赋值结合:

```jsx
const App = () => {
  const [clicks, setClicks] = useState({
    left: 0, right: 0
  })

  const handleLeftClick = () => {
    const newClicks = { 
      left: clicks.left + 1, 
      right: clicks.right 
    }
    setClicks(newClicks)
  }

  const handleRightClick = () => {
    const newClicks = { 
      left: clicks.left, 
      right: clicks.right + 1 
    }
    setClicks(newClicks)
  }

  return (
    <div>
      {clicks.left}
      <button onClick={handleLeftClick}>left</button>
      <button onClick={handleRightClick}>right</button>
      {clicks.right}
    </div>
  )
}
```



注意到, 状态`clicks`有两部分: `clicks.left`, `clicks.right`. 每次更新其中一部分时, 还要写另一部分:

```jsx
const handleLeftClick = () => {
  const newClicks = { 
    left: clicks.left + 1, 
    right: clicks.right // clicks.right没有改变, 但setter里还是要写
  }
  setClicks(newClicks)
}
//handleRightClick同理
```



这样很冗余,可以用object spread syntax来简化:

```jsx
const handleLeftClick = () => {
  const newClicks = { 
    ...clicks, 
    left: clicks.left + 1 
  }
  setClicks(newClicks)
}

const handleRightClick = () => {
  const newClicks = { 
    ...clicks, 
    right: clicks.right + 1 
  }
  setClicks(newClicks)
}
```



这里的`...clicks`实际上被展开为:

```javascript
//以handleLeftClick内为例
const newClicks = { 
    //...clicks 被展开为:
    left: xx
    right: xx
    
    // 这里重新声明了right属性,也就覆盖了前面的right
    left: clicks.left + 1 
  }
```

由于JS对象支持重复声明属性, 并且后面的属性会覆盖前面同名的属性, 这样做实际上就保留了`left`属性, 只更改`right`属性