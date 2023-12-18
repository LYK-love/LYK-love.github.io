---
title: Python Decorators
tags: Python
categories:
  - Software Engineering
date: 2023-12-17 17:05:11
---


Decorators are a significant part of Python. In simple words: they are functions which take other functions as inputs and output their modified versions.

Source:

1. [Python Tips: Decorators](https://book.pythontips.com/en/latest/decorators.html#decorators)

<!--more-->

# First Class Functions

Recalling that in Python, functions are first class objects, which means:

- A function is an instance of the Object type.
- You can store the function in a variable. 
- You can pass the function as a parameter to another function. 
- You can return the function from a function. 
- You can store them in data structures such as hash tables, lists, …

```python
def hi(name="yasoob"):
    return "hi " + name

print(hi())
# output: 'hi yasoob'

# We can even assign a function to a variable like
greet = hi
# We are not using parentheses here because we are not calling the function hi
# instead we are just putting it into the greet variable. Let's try to run this

print(greet())
# output: 'hi yasoob'

# Let's see what happens if we delete the old hi function!
del hi
print(hi())
#outputs: NameError

print(greet())
#outputs: 'hi yasoob'
```

## Defining functions within functions

So those are the basics when it comes to functions. Let's take your
knowledge one step further. In Python we can define functions inside
other functions:

```python
def hi(name="yasoob"):
    print("now you are inside the hi() function")

    def greet():
        return "now you are in the greet() function"

    def welcome():
        return "now you are in the welcome() function"

    print(greet())
    print(welcome())
    print("now you are back in the hi() function")

hi()
#output:now you are inside the hi() function
#       now you are in the greet() function
#       now you are in the welcome() function
#       now you are back in the hi() function

# This shows that whenever you call hi(), greet() and welcome()
# are also called. However the greet() and welcome() functions
# are not available outside the hi() function e.g:

greet()
#outputs: NameError: name 'greet' is not defined
```

So now we know that we can define functions in other functions. In
other words: we can make nested functions. Now you need to learn one
more thing, that functions can return functions too.

## Returning functions from within functions

It is not necessary to execute a function within another function, we can return it as an output as well:

```python
def hi(name="yasoob"):
    def greet():
        return "now you are in the greet() function"

    def welcome():
        return "now you are in the welcome() function"

    if name == "yasoob":
        return greet
    else:
        return welcome

a = hi()
print(a)
#outputs: <function greet at 0x7f2143c01500>

#This clearly shows that `a` now points to the greet() function in hi()
#Now try this

print(a())
#outputs: now you are in the greet() function
```

Just take a look at the code again. In the ``if/else`` clause we are turning ``greet`` and ``welcome``, not ``greet()`` and ``welcome()``.

Why is that? It's because when you put a pair of parentheses after it, the function gets executed; whereas if you don't put parenthesis after it, then it can be passed around and can be assigned to other variables without executing it. Did you get it? Let me explain it in a little bit more detail. When we write ``a = hi()``, ``hi()`` gets executed and because the name is yasoob by default, the function ``greet`` is returned. If we change the statement to ``a = hi(name = "ali")`` then the ``welcome`` function will be returned. We can also do print ``hi()()`` which outputs *now you are in the greet() function*.

## Giving a function as an argument to another function

```python
def hi():
    return "hi yasoob!"

def doSomethingBeforeHi(func):
    print("I am doing some boring work before executing hi()")
    print(func())

doSomethingBeforeHi(hi)
#outputs:I am doing some boring work before executing hi()
#        hi yasoob!
```

Now you have all the required knowledge to learn what decorators really are. Decorators let you execute code before and after a function.

# Decorators

In the last example we actually made a decorator! Let's modify the previous decorator and make a little bit more usable program:

```python
# A decorator function
def a_new_decorator(func):
    def wrapTheFunction():
        print(f"wrapper: I am doing some boring work before before wrapping {func.__name__}")
        print(f"wrapper: you can do anything here, including calling {func.__name__}")
        func() # you can do any other things even not involved with `func`
        print(f"wrapper: I am doing some boring work after wrapping {func.__name__}")

    return wrapTheFunction
  
def a_function_requiring_decoration():
    print("I am the function which needs some decoration to remove my foul smell")
 
a_decorated_function = a_new_decorator(a_function_requiring_decoration)
a_decorated_function()
```

Now the original function `a_function_requiring_decoration` is wrapped by the decorator  `a_new_decorator`, it returns a new function `a_decorated_function`.

## `@wrap` syntax

The decorator feature is supported by Python directly with `@wrap` syntax.

```python
# A decorator function
def a_new_decorator(func):
    def wrapTheFunction():
        print(f"wrapper: I am doing some boring work before before wrapping {func.__name__}")
        print(f"wrapper: you can do anything here, including calling {func.__name__}")
        func() # you can do any other things even not involved with `func`
        print(f"wrapper: I am doing some boring work after wrapping {func.__name__}")

    return wrapTheFunction
  
@a_new_decorator
def a_function_requiring_decoration():
    print("I am the function which needs some decoration to remove my foul smell")
a_function_requiring_decoration()
```

It's just  the same as the previous syntax:

```python
def a_function_requiring_decoration():
    print("I am the function which needs some decoration to remove my foul smell")
 
a_decorated_function = a_new_decorator(a_function_requiring_decoration)
a_decorated_function()
```



To conclude, the `@wrap` syntax is as:

```python
def a_new_decorator(func):
    def wrapTheFunction():
        pass
    return wrapTheFunction

@a_new_decorator
def a_function_requiring_decoration():
    pass
 a_function_requiring_decoration() # equals "wrapTheFunction()"
```

## Change the decorated function name

Since the decorator just <u>substitudes the original function with a wrapper fucuntion</u>, it's easy to see that the wrapper function and the original function are not the same object.

```python
print(a_function_requiring_decoration.__name__)
# Output: wrapTheFunction
```

However, most of the time we want to make the decorator be "transparent" and let the name of the wrapper function be the same as that of original function.

Luckily, Python provides us a simple function to solve this problem and that is `functools.wraps`. Let's modify our previous example to use `functools.wraps`:

```python
from functools import wraps

def a_new_decorator(a_func):
    @wraps(a_func)
    def wrapTheFunction():
        print("I am doing some boring work before executing a_func()")
        a_func()
        print("I am doing some boring work after executing a_func()")
    return wrapTheFunction

@a_new_decorator
def a_function_requiring_decoration():
    """Hey yo! Decorate me!"""
    print("I am the function which needs some decoration to "
          "remove my foul smell")

print(a_function_requiring_decoration.__name__)
# Output: a_function_requiring_decoration
```

Now that is much better. Let's move on and learn some use-cases of decorators.

# Nesting a Decorator Within a Function

`@wrap` is a function itself. So it can be functional programmed as well. For instace, we can call it and let it return a function. In other worlds, we can nest a decorator within a function

```python
def Outer_func(param):
    def a_new_decorator(func):
        pass
    return a_new_decorator

@Outer_func('some param') # returns a decorator
def a_function_requiring_decoration():
    print("I am the function which needs some decoration to remove my foul smell")
```

Note: function `Outer_func` is not a decorator itself. Instead, it **returns a decorator** `a_new_decorator`. Thus, the wrapper in `@Outer_func('some param')` of syntax `@wrapper` is `Outer_func('some param')`, not `Outer_func`.

## Example: `add_to_class(Class)`

This decorator can register objects as methods in created class.

```python
def add_to_class(Class): 
    """Register objects as methods in created class."""
    def wrapper(obj):
        setattr(Class, obj.__name__, obj)
    return wrapper
```



Look how it works. Given class `A` and function `do`, we want to register `do` as a member function of class `A`. Note, as a member function, `do` must set it's first parameter as `self`.

```python
class A:
    def __init__(self):
        self.b = 1

a = A()

def do(self): 
    print('Class attribute "b" is', self.b)
```

There're 2 ways to do it:

First, we can use the plain syntax:

```python
def do(self): 
    print('Class attribute "b" is', self.b)

wrapper = add_to_class(A)# get the function "setattr(A, obj.__name__, obj)"
wrapper(do) # register function ` o` as a member of class `A`, i.e., execute code "setattr(Class, "do", do)".
a.do() # Now we can call `do` as a member function of `A`.
```



Or, we can either use `@` syntax:

```python
@add_to_class(A)
def do(self): 
    print('Class attribute "b" is', self.b)

a.do() # The `do` function has been registered as a member of class `A`.
```

## Example: Decorators with Arguments

Come to think of it, isn't ``@wraps`` also a decorator?  But, it takes an argument like any normal function can do.  So, why can't we do that too?

This is because when you use the ``@my_decorator`` syntax, you are applying a wrapper function with a single function as a parameter.

Remember, everything in Python is an object, and this includes functions!  With that in mind, we can write a function that returns a wrapper function.



Let's go back to our logging example, and create a wrapper which lets us specify a logfile to output to.

```python
def logit(logfile='out.log'):
    def logging_decorator(func):
        # @wraps(func)
        def wrapped_function(*args, **kwargs):
            log_string = func.__name__ + " was called"
            print(log_string)
            # Open the logfile and append
            with open(logfile, 'a') as opened_file:
                # Now we log to the specified logfile
                opened_file.write(log_string + '\n')
            return func(*args, **kwargs)

        # print(f"func in wrapped_function: {func.__name__}")
        return wrapped_function
    return logging_decorator

def myfunc1():
    pass
```



We can use this decorator `logit` in 2 ways.

First, use the plain syntax:

```python
def myfunc1():
    pass
  
logit('out.log')(myfunc1)()
```

This code is quite compact, it actually goes through 3 steps:

```python
func_logging_decorator_with_log_file = logit('out.log')
func_wrapped_function_with_myfunc1 = func_logging_decorator_with_log_file(myfunc1)
func_wrapped_function_with_myfunc1()
```



The 2nd way is to use `@` syntax:

```python
@logit('out.log') # == logging_decorator
def myfunc1():
    pass
myfunc1()
```



# Constrains of FP

However, the functional programming has it's contrains. It's hard to debug compared to OO programming. Consider following example:

```python
def outer_func(param):
    def a_new_decorator(func):
        def wrapper():
            func(param)

        return wrapper

    return a_new_decorator


def a_function_requiring_decoration(param):
    print(f"The params of outer function: {param}")


wrapperFunc = outer_func(str("some params"))(a_function_requiring_decoration)
wrapperFunc()
```

Here, we first create a decorator function object `a_new_decorator` and fix it's inner variable `param` as `"some params"`.

But the IDE can't see/visit this value when debugging.
