---
title: React Basic
tags: Frontend
categories: Technology
date: 2022-08-22 18:50:01
---


Outline:

* Intro
* Components
* JSX
* ...

<!--more-->

# Intro

* [React Official Docs](https://reactjs.org/docs/hello-world.html)

* [Full Stack Tutorial -> Web Development](https://fullstackopen.com/en/#course-contents)

* [How do React hooks really work?](https://www.netlify.com/blog/2019/03/11/deep-dive-how-do-react-hooks-really-work/)

React is a declarative, efficient, and flexible JavaScript library for building user interfaces. It lets you compose complex UIs from small and isolated pieces of code called “components”.

# Components

Component是React中的一等公民. 有两种方式创建Component, 它们是等价的:

* Class Components
* Function Components

## Class Components

`React.Component`是一个抽象基类. 这意味着直接引用`React.Component`是毫无意义的. 你可以实现一个它的子类，并且至少定义一个`render()`方法.

```jsx
class ShoppingList extends React.Component {
  render() {
    return (
      <div className="shopping-list">
        <h1>Shopping List for {this.props.name}</h1>
        <ul>
          <li>Instagram</li>
          <li>WhatsApp</li>
          <li>Oculus</li>
        </ul>
      </div>
    );
  }
}

// Example usage: <ShoppingList name="Mark" />
```

## Function Components

 Function Components比Class Components更简洁, 它默认没有State, 可以用hook函数给Function Components添加State.

```jsx
function Square(props) {
  return (
    <button className="square" onClick={props.onClick}>
      {props.value}
    </button>
  );
}
```

## props

组件通过`props`来接收参数.

`props`是**Read-Only**的

**All React components must act like pure functions with respect to their props.**



* 对于Class Component, `props`是其自带的成员

  ```jsx
  class Welcome extends React.Component {
    render() {
      return <h1>Hello, {this.props.name}</h1>;
    }
  }
  ```

* 对于Function Component, 函数必须接受`props`为参数

  ```jsx
  function Welcome(props) {
    return <h1>Hello, {props.name}</h1>;
  }
  ```

---

外部传参数给组件时, 参数都会被绑定到`props`的属性:

```jsx
const element = <Welcome name="Sara" />;
```

* 现在`Welcome`组件实例的`props`拥有了属性`props.name`, 其值为`"Sara"`

## Fragments

the content of a React component (usually) needs to contain **one root element**:

1. 可以用*array*包裹:

   ```jsx
   const App = () => {
     return [
       <h1>Greetings</h1>,
       <Hello name="Maya" age={26 + 10} />,
       <Footer />
     ]
   }
   ```

2. 也可以用`<div><div/>`等标签包裹, 不过这样很冗余. React为此推出了 [fragments](https://reactjs.org/docs/fragments.html#short-syntax), 其语法是一个空标签:

   ```jsx
   const App = () => {
     const name = 'Peter'
     const age = 10
   
     return (
       <>
         <h1>Greetings</h1>
         <Hello name="Maya" age={26 + 10} />
         <Hello name={name} age={age} />
         <Footer />
       </>
     )
   }
   ```

# JSX

JSX形式上类似HTML, 它会被编译为JS代码. 因此JSX实际上是JS表达式.



在JSX内可以通过curly braces来使用**任何JS表达式**:

```JSX
const name = 'Josh Perez';
const element = <h1>Hello, {name}</h1>;
```





可以直接写pure JS来替代JSX:

```jsx
const element = (
  <h1 className="greeting">
    Hello, world!
  </h1>
);
const element = React.createElement(
  'h1',
  {className: 'greeting'},
  'Hello, world!'
);
```

可以看到这样写很繁琐. JSX可以简化开发

# Rendering Elements

## React Element

React element就是一段JSX( or JS表达式 ), element通过`render()`来被渲染, 并在页面展示.

```jsx
const element = <h1>Hello, world</h1>;
```

## DOM Element

React假定HTML页面有一个root element, 它是个DOM element:

```html
<div id="root"></div>
```



React把该DOM element转化成React element:

```JSX
const root = ReactDOM.createRoot(
  document.getElementById('root')
);
```

## Conditional Rendering

## render()

`render()`方法返回React element.



最简单的做法是让root element( 此时是React element )来render:

```javascript
root.render(element);
```

事实上, 大部分React APP只会调用`root.render()`一次, 用于首次加载

对于组件的重新渲染,  我们使用Stateful Components. 

* 因为需要重新渲染的组件, 都是有状态的组件( Stateful Components )
* 事实上, **当且仅当组件的状态发生变更时, 才会触发Rerender**
  * 改变`props`不会触发rerender



# Stateful Components

* 对于Class Components, 通过加入`state`成员等操作, 使其变为Stateful Components
* 对于Function Components, React引入了hook函数来使其变为Stateful Components

---

## Notes

**Do Not Modify State Directly since [it can result in unexpected side effects](https://stackoverflow.com/a/40309023).**

For example, this will not re-render a component:

```jsx
// Wrong
this.state.comment = 'Hello';
```



**Instead, use `setState()`:**

```jsx
// Correct
this.setState({comment: 'Hello'});
```

The only place where you can assign `this.state` is the constructor.

---



## For Class Component

对于Class Component, 可以使用`state`成员来保存要变化(因此要被重新rend)的成员.

此外, 将`return ...`改为`render() { ... }`

每次`state`的属性有更改,就会触发`render()`

```jsx
class Clock extends React.Component {
  constructor(props) {
    super(props);
    this.state = {date: new Date()};
  }

  render() {
    return (
      <div>
        <h1>Hello, world!</h1>
        <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }
}

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(<Clock />);
```

### State Updates May Be Asynchronous

React may batch multiple `setState()` calls into a single update for performance.

Because `this.props` and `this.state` may be updated asynchronously, you should not rely on their values for calculating the next state.

For example, this code may fail to update the counter:

```jsx
// Wrong
this.setState({
  counter: this.state.counter + this.props.increment,
});
```

To fix it, use a second form of `setState()` that accepts a function rather than an object. That function will receive the previous state as the first argument, and the props at the time the update is applied as the second argument:

```jsx
// Correct
this.setState((state, props) => ({
  counter: state.counter + props.increment
}));
```

## Lifting State Up

Often, several components need to reflect the same changing data. We recommend lifting the shared state up to their closest common ancestor. 



### Example

子组件的状态都被封装到父组件:

```jsx
const App = () => {
  const [ counter, setCounter ] = useState(0)

  const increaseByOne = () => setCounter(counter + 1)
  const decreaseByOne = () => setCounter(counter - 1)
  const setToZero = () => setCounter(0)

  return (
    <div>
      <Display counter={counter}/>
      <Button
        onClick={increaseByOne}
        text='plus'
      />
      <Button
        onClick={setToZero}
        text='zero'
      />     
      <Button
        onClick={decreaseByOne}
        text='minus'
      />           
    </div>
  )
}
```



子组件不需要保存State:

```jsx
const Display = (props) => {
  return (
    <div>{props.counter}</div>
  )
}
```

```jsx
const Button = (props) => {
  return (
    <button onClick={props.onClick}>
      {props.text}
    </button>
  )
}
```



# Hooks

*Hooks* are a new addition in React 16.8. They let you use state and other React features without writing a class.

**Hooks allow you to reuse stateful logic without changing your component hierarchy.** 

Hooks are [backwards-compatible](https://reactjs.org/docs/hooks-intro.html#no-breaking-changes). 

## useState()

React provides a few built-in Hooks like `useState`. You can also create your own Hooks to reuse stateful behavior between different components. We’ll look at the built-in Hooks first.

```jsx
import React, { useState } from 'react'; //imports the useState function

function Example() {
  // Declare a new state variable, which we'll call "count"
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>
        Click me
      </button>
    </div>
  );
}
```

* `useState` returns a pair: the *current* state value and a function that lets you update it. 

* You can call this function from an event handler or somewhere else. It’s similar to `this.setState` in a class, except it doesn’t merge the old and new state together. (We’ll show an example comparing `useState` to `this.state` in [Using the State Hook](https://reactjs.org/docs/hooks-state.html).)

* The only argument to `useState` is the initial state. In the example above, it is `0` because our counter starts from zero. Note that unlike `this.state`, the state here doesn’t have to be an object — although it can be if you want. The initial state argument is only used during the first render.

###  Complex state

The component's state or a piece of its state can be of **any type**. 

```jsx
function ExampleWithManyStates() {
  // Declare multiple state variables!
  const [age, setAge] = useState(42);
  const [fruit, setFruit] = useState('banana');
  const [todos, setTodos] = useState([{ text: 'Learn Hooks' }]);
  // ...
}
```

可以和解构赋值以及[object spread](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Spread_syntax) syntax结合来简化代码:

```javascript
const App = () => {
  const [clicks, setClicks] = useState({ //解构赋值
    left: 0, right: 0
  })

  const handleLeftClick = () => {
  const newClicks = { 
    ...clicks, //object spread syntax
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





## useEffect()

The Effect Hook, `useEffect`, adds the ability to perform side effects from a function component. It serves the same purpose as `componentDidMount`, `componentDidUpdate`, and `componentWillUnmount` in React classes, but unified into a single API. (We’ll show examples comparing `useEffect` to these methods in [Using the Effect Hook](https://reactjs.org/docs/hooks-effect.html).)

For example, this component sets the document title after React updates the DOM:

```jsx
import React, { useState, useEffect } from 'react';

function Example() {
  const [count, setCount] = useState(0);

  // Similar to componentDidMount and componentDidUpdate:
  useEffect(() => {
    // Update the document title using the browser API
    document.title = `You clicked ${count} times`;
  });

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>
        Click me
      </button>
    </div>
  );
}
```

When you call `useEffect`, you’re telling React to run your “effect” function after flushing changes to the DOM. Effects are declared inside the component so they have access to its props and state. By default, React runs the effects after every render — *including* the first render. (We’ll talk more about how this compares to class lifecycles in [Using the Effect Hook](https://reactjs.org/docs/hooks-effect.html).)



# Handling Events

## Add Event Handler

Handling events with React elements is very similar to handling events on DOM elements. There are some syntax differences:

- React events are named using **camelCase**, rather than lowercase.
- With JSX you **pass a function** as the event handler, rather than a string.

For example, the HTML:

```html
<button onclick="activateLasers()">
  Activate Lasers
</button>
```

is slightly different in React:

```jsx
<button onClick={activateLasers}>  
  Activate Lasers
</button>
```



Another difference is that 

## Event Hander

When using React, you generally don’t need to call `addEventListener` to add listeners to a DOM element after it is created. Instead, just provide a listener when the element is initially rendered.



**Event handler is either a *function* or a *function reference, not a function call***

* 将函数作为event handler:

  ```jsx
  <button onClick={() => setCounter(counter + 1)}> 
    plus
  </button>
  ```

  

* 将函数引用作为event handler :

  ```jsx
  <button onClick={increaseByOne}> 
    plus
  </button>
  ```

* **错误示范**, 将函数调用作为event handler:

  ```jsx
  <button onClick={setCounter(counter + 1)}>
  ```

  这样做的问题在于, 当React渲染该组件时, 它会直接调用`setCounter(counter + 1)`, 如果后者是一个改变该组件内部状态的函数, 就会导致该组件重新渲染, 然后继续调用该函数, 继续重渲染....



## Prevent Default Behavior

Unlike HTML, you cannot return `false` to prevent default behavior in React. You must call `preventDefault` explicitly. For example, with plain HTML, to prevent the default form behavior of submitting, you can write:

```html
<form onsubmit="console.log('You clicked submit.'); return false">
  <button type="submit">Submit</button>
</form>
```



In React, this could instead be:

```jsx
function Form() {
  function handleSubmit(e) {
    e.preventDefault();    console.log('You clicked submit.');
  }

  return (
    <form onSubmit={handleSubmit}>
      <button type="submit">Submit</button>
    </form>
  );
}
```

Here, `e` is a synthetic event. React defines these synthetic events according to the [W3C spec](https://www.w3.org/TR/DOM-Level-3-Events/), so you don’t need to worry about cross-browser compatibility. React events do not work exactly the same as native events. See the [`SyntheticEvent`](https://reactjs.org/docs/events.html) reference guide to learn more.

## Event Handler as  A Method

可以将Event Handler作为Component的成员

### bind(this)

`bind(this)`:

```jsx
class Toggle extends React.Component {
  constructor(props) {
    super(props);
    this.state = {isToggleOn: true};

    // This binding is necessary to make `this` work in the callback    
    this.handleClick = this.handleClick.bind(this);  
  }

  handleClick() {
    this.setState(prevState => ({
      isToggleOn: !prevState.isToggleOn
    }));
  }

  render() {
    return (
      <button onClick={this.handleClick}>
        {this.state.isToggleOn ? 'ON' : 'OFF'}
      </button>
    );
  }
}
```

You have to be careful about the meaning of `this` in JSX callbacks. **In JavaScript, class methods are not [bound](https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Global_objects/Function/bind) by default**. If you forget to bind `this.handleClick` and pass it to `onClick`, `this` will be `undefined` when the function is actually called.



This is not React-specific behavior; it is a part of [how functions work in JavaScript](https://www.smashingmagazine.com/2014/01/understanding-javascript-function-prototype-bind/). Generally, if you refer to a method without `()` after it, such as `onClick={this.handleClick}`, you should bind that method.

### class fields syntax

If calling `bind` annoys you, there are two ways you can get around this. You can use [public class fields syntax](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/Public_class_fields#public_instance_fields) to correctly bind callbacks:

```jsx
class LoggingButton extends React.Component {
  // This syntax ensures `this` is bound within handleClick.
  handleClick = () => {
    console.log('this is:', this);
  };
  render() {
    return (
      <button onClick={this.handleClick}>
        Click me
      </button>
    );
  }
}
```

This syntax is enabled by default in [Create React App](https://github.com/facebookincubator/create-react-app).

### arrow function

If you aren’t using class fields syntax, you can use an [arrow function](https://developer.mozilla.org/en/docs/Web/JavaScript/Reference/Functions/Arrow_functions) in the callback:

```jsx
class LoggingButton extends React.Component {
  handleClick() {
    console.log('this is:', this);
  }

  render() {
    // This syntax ensures `this` is bound within handleClick
    return (
      <button onClick={() => this.handleClick()}>
        Click me
      </button>
    );
  }
}
```

The problem with this syntax is that a different callback is created each time the `LoggingButton` renders. In most cases, this is fine. However, if this callback is passed as a prop to lower components, those components might do an extra re-rendering. We generally recommend binding in the constructor or using the class fields syntax, to avoid this sort of performance problem.

## Passing Arguments to Event Handlers

Inside a loop, it is common to want to pass an extra parameter to an event handler. For example, if `id` is the row ID, either of the following would work:

```jsx
<button onClick={(e) => this.deleteRow(id, e)}>Delete Row</button>
<button onClick={this.deleteRow.bind(this, id)}>Delete Row</button>
```

The above two lines are equivalent, and use [arrow functions](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/Arrow_functions) and [`Function.prototype.bind`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_objects/Function/bind) respectively.

In both cases, the `e` argument representing the React event will be passed as a second argument after the ID. With an arrow function, we have to pass it explicitly, but with `bind` any further arguments are automatically forwarded.



# Lists and Keys

React的列表组件( e.g. `<li></li>` )需要指定列表元素对key. 如果不指定, 则会默认使用元素的array下标作为key, 并且报一个warning.  使用元素的数组下标作为key在排序时会遇到问题. 

* 可以使用`key={i}`来规避掉warning, 但依然无法解决排序时的问题.

* 因此必须为列表组件手动指定正确的key:

  ```jsx
  <li key={user.id}>{user.name}: {user.taskCount} tasks left</li>
  ```

---

* Keys Must Only Be Unique Among Siblings
* `key` is a special and reserved property in React (along with `ref`, a more advanced feature). When an element is created, React extracts the `key` property and stores the key directly on the returned element. 
* Even though `key` may look like it belongs in `props`, **`key` cannot be referenced using `this.props.key`**

---

## Examples

使用`map()`:

```jsx
function NumberList(props) {
  const numbers = props.numbers;
  const listItems = numbers.map((number) =>
    <ListItem key={number.toString()}
              value={number} />
  );
  return (
    <ul>
      {listItems}
    </ul>
  );
}
```

OR:

```jsx
function NumberList(props) {
  const numbers = props.numbers;
  return (
    <ul>
      {numbers.map((number) =>
        <ListItem key={number.toString()}
                  value={number} />
      )}
    </ul>
  );
}
```

# Forms

HTML form elements work a bit differently from other DOM elements in React, because form elements naturally keep some internal state. For example, this form in plain HTML accepts a single name:

```
<form>
  <label>
    Name:
    <input type="text" name="name" />
  </label>
  <input type="submit" value="Submit" />
</form>
```

This form has the default HTML form behavior of browsing to a new page when the user submits the form. If you want this behavior in React, it just works. But in most cases, it’s convenient to have a JavaScript function that handles the submission of the form and has access to the data that the user entered into the form. The standard way to achieve this is with a technique called “controlled components”.

## Controlled Components

In HTML, form elements such as `<input>`, `<textarea>`, and `<select>` typically maintain their own state and update it based on user input. In React, mutable state is typically kept in the state property of components, and only updated with [`setState()`](https://reactjs.org/docs/react-component.html#setstate).

We can combine the two by making the React state be the “single source of truth”. Then the React component that renders a form also controls what happens in that form on subsequent user input. An input form element whose value is controlled by React in this way is called a “controlled component”.

For example, if we want to make the previous example log the name when it is submitted, we can write the form as a controlled component:

```jsx
class NameForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {value: ''};

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({value: event.target.value});
  }

  handleSubmit(event) {
    alert('A name was submitted: ' + this.state.value);
    event.preventDefault();
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <label>
          Name:
          <input type="text" value={this.state.value} onChange={this.handleChange} />
        </label>
        <input type="submit" value="Submit" />
      </form>
    );
  }
}
```

## Controlled Input Null Value

Specifying the `value` prop on a [controlled component](https://reactjs.org/docs/forms.html#controlled-components) prevents the user from changing the input unless you desire so. If you’ve specified a `value` but the input is still editable, you may have accidentally set `value` to `undefined` or `null`.

The following code demonstrates this. (The input is locked at first but becomes editable after a short delay.)

```jsx
ReactDOM.createRoot(mountNode).render(<input value="hi" />);

setTimeout(function() {
  ReactDOM.createRoot(mountNode).render(<input value={null} />);
}, 1000);
```







## The textarea Tag

In HTML, a `<textarea>` element defines its text by its children:

```html
<textarea>
  Hello there, this is some text in a text area
</textarea>
```

In React, a `<textarea>` uses a `value` attribute instead. This way, a form using a `<textarea>` can be written very similarly to a form that uses a single-line input:

```jsx
class EssayForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      value: 'Please write an essay about your favorite DOM element.'
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({value: event.target.value});
  }

  handleSubmit(event) {
    alert('An essay was submitted: ' + this.state.value);
    event.preventDefault();
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <label>
          Essay:
          <textarea value={this.state.value} onChange={this.handleChange} />
        </label>
        <input type="submit" value="Submit" />
      </form>
    );
  }
}
```

Notice that `this.state.value` is initialized in the constructor, so that the text area starts off with some text in it.

## The select Tag

In HTML, `<select>` creates a drop-down list. For example, this HTML creates a drop-down list of flavors:

```jsx
<select>
  <option value="grapefruit">Grapefruit</option>
  <option value="lime">Lime</option>
  <option selected value="coconut">Coconut</option>
  <option value="mango">Mango</option>
</select>
```

Note that the Coconut option is initially selected, because of the `selected` attribute. React, instead of using this `selected` attribute, uses a `value` attribute on the root `select` tag. This is more convenient in a controlled component because you only need to update it in one place. For example:

```jsx
class FlavorForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {value: 'coconut'};

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({value: event.target.value});
  }

  handleSubmit(event) {
    alert('Your favorite flavor is: ' + this.state.value);
    event.preventDefault();
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <label>
          Pick your favorite flavor:
          <select value={this.state.value} onChange={this.handleChange}>
            <option value="grapefruit">Grapefruit</option>
            <option value="lime">Lime</option>
            <option value="coconut">Coconut</option>
            <option value="mango">Mango</option>
          </select>
        </label>
        <input type="submit" value="Submit" />
      </form>
    );
  }
}
```



Overall, this makes it so that `<input type="text">`, `<textarea>`, and `<select>` all work very similarly - they all accept a `value` attribute that you can use to implement a controlled component.

> Note
>
> You can pass an array into the `value` attribute, allowing you to select multiple options in a `select` tag:
>
> ```
> <select multiple={true} value={['B', 'C']}>
> ```

## The file input Tag

In HTML, an `<input type="file">` lets the user choose one or more files from their device storage to be uploaded to a server or manipulated by JavaScript via the [File API](https://developer.mozilla.org/en-US/docs/Web/API/File/Using_files_from_web_applications).

```html
<input type="file" />
```

Because its value is read-only, it is an **uncontrolled** component in React. It is discussed together with other uncontrolled components [later in the documentation](https://reactjs.org/docs/uncontrolled-components.html#the-file-input-tag).



When you need to handle multiple controlled `input` elements, you can add a `name` attribute to each element and let the handler function choose what to do based on the value of `event.target.name`.

# Refactoring

## Components

原代码:

```jsx
const Button = (props) => {
  return (
    <button onClick={props.onClick}>
      {props.text}
    </button>
  )
}
```



重构后:

```jsx
const Button = ({ onClick, text }) => <button onClick={onClick}>{text}</button>
```

