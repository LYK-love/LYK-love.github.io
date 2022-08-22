---
title: HTML Basic
tags: HTML
categories: Frontend
date: 2022-08-22 19:02:39
---


Outline:

* Basic
* HTML Attributes
* Head Elements
* Block and Inline Elements
* Other Elements
* CSS

<!--more-->

# Basic

## <!DOCTYPE> 

The `<!DOCTYPE>` declaration represents the document type, and helps browsers to display web pages correctly.

It must only appear once, at the top of the page (before any HTML tags).

The `<!DOCTYPE>` declaration is not case sensitive.

The `<!DOCTYPE>` declaration for HTML5 is:

<!DOCTYPE html>
  # HTML Elements

An HTML element is defined by a start tag, some content, and an end tag:

```
<tagname> Content goes here... </tagname>
```

tag及其包括的content构成了HTML元素

* HTML tag不是大小写敏感的
  * `<P>` means the same as `<p>`
* HTML元素可以嵌套
* 某些HTML元素没有内容部分(比如 `<br>` 元素)，称为空元素。  空元素不能有end tag

## 基本标签

- The `<!DOCTYPE html>` declaration defines that this document is an HTML5 document
- The `<html>` element is the root element of an HTML page
- The `<head>` element contains meta information about the HTML page
- The `<title>` element specifies a title for the HTML page (which is shown in the browser's title bar or in the page's tab)
- The `<body>` element defines the document's body, and is a container for all the visible contents, such as headings, paragraphs, images, hyperlinks, tables, lists, etc.
- The `<h1>` element defines a large heading
- The `<p>` element defines a paragraph

## Usage

* All HTML documents must start with a document type declaration: `<!DOCTYPE html>`.
* The HTML document itself begins with `<html>` and ends with `</html>`.
* The visible part of the HTML document is between `<body>` and `</body>`.



## \<nav>

```
<nav>
  <a href="/html/">HTML</a> |
  <a href="/css/">CSS</a> |
  <a href="/js/">JavaScript</a> |
  <a href="/jquery/">jQuery</a>
</nav>
```



## \<aside>

The `<aside>` element defines some content aside from the content it is placed in (like a sidebar).

The `<aside>` content should be indirectly related to the surrounding content.

# HTML Attributes

HTML attributes provide additional information about HTML elements.

- All HTML elements can have **attributes**
- Attributes are always specified in **the start tag**
- Attributes usually come in name/value pairs like: **name="value"**

## 基本属性

The `<a>` tag defines a hyperlink. The `href` <u>attribute</u> specifies the URL of the page the link goes to:

```html
<a href="https://www.w3schools.com">Visit W3Schools</a>
```

## Class

 The `class` attribute can be used on **any** HTML element.

**Note:** The class name is case sensitive!



HTML elements can belong to more than one class.

# HTML Head Elements

The `<head>` element is a container for metadata (data about data) and is placed between the `<html>` tag and the `<body>` tag.

HTML metadata is data about the HTML document. Metadata is not displayed.

Metadata typically define the document title, character set, styles, scripts, and other meta information.

You can have several `<header>` elements in one HTML document. However, `<header>` cannot be placed within a `<footer>`, `<address>` or another `<header>` element.

## \<title>

* The title must be text-only

- defines a title in the browser toolbar
- displays a title for the page in search engine-results

## \<style>

```html
<style>
  body {background-color: powderblue;}
  h1 {color: red;}
  p {color: blue;}
</style>
```

## \<meta>

**Define the character set used:**

```
<meta charset="UTF-8">
```



**Define keywords for search engines:**

```
<meta name="keywords" content="HTML, CSS, JavaScript">
```



**Define a description of your web page:**

```
<meta name="description" content="Free Web tutorials">
```



**Define the author of a page:**

```
<meta name="author" content="John Doe">
```



**Refresh document every 30 seconds:**

```
<meta http-equiv="refresh" content="30">
```



**Setting the viewport to make your website look good on all devices:**

```
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```



## \<link>

The `<link>` tag is most often used to link to external style sheets:

```
<link rel="stylesheet" href="mystyle.css">
```



## \<script>

```
<script>
function myFunction() {
  document.getElementById("demo").innerHTML = "Hello JavaScript!";
}
</script>
```

## \<base>

The `<base>` element specifies the base URL and/or target for all relative URLs in a page.

The `<base>` tag must have either an href or a target attribute present, or both.

There can only be one single `<base>` element in a document!

```
<head>
<base href="https://www.w3schools.com/" target="_blank">
</head>

<body>
<img src="images/stickman.gif" width="24" height="39" alt="Stickman">
<a href="tags/tag_base.asp">HTML base Tag</a>
</body>
```





# Block and Inline Elements

- The `<div>` element is a block-level and is often used as a container for other HTML elements
- The `<span>` element is an inline container used to mark up a part of a text, or a part of a document

## Block

A block-level element always **starts on a new line**, and the browsers automatically add some space (**a margin**) **before and after the element**.

A block-level element always takes up the full width available (stretches out to the left and right as far as it can).

Two commonly used block elements are: `<p>` and `<div>`.

The `<p>` element defines a paragraph in an HTML document.

The `<div>` element defines a division or a section in an HTML document.

## Inline

An inline element does not start on a new line.

An inline element only takes up as much width as necessary.

**Note:** An inline element cannot contain a block-level element!





```
<span>Hello World</span>
```

# Other Elements

# \<label>

The `for` attribute of `<label>` must be equal to the id attribute of the related element to bind them together. A label can also be bound to an element by placing the element inside the `<label>` element. 

```
<form action="/action_page.php">
  <input type="radio" id="html" name="fav_language" value="HTML"> # 对应for = "html"
  <label for="html">HTML</label><br>
  
  <input type="radio" id="css" name="fav_language" value="CSS"># 对应for = "css"
  <label for="css">CSS</label><br>
  
  <input type="radio" id="javascript" name="fav_language" value="JavaScript">
  <label for="javascript">JavaScript</label><br><br>
  
  <input type="submit" value="Submit">
</form>
```



# CSS

## Using CSS

CSS can be added to HTML documents in 3 ways:

- **Inline** - by using the `style` attribute inside HTML elements
- **Internal** - by using a `<style>` element in the `<head>` section
- **External** - by using a `<link>` element to link to an external CSS file

## Inline



```
<h1 style="color:blue;">A Blue Heading</h1>
```



## Internal

```
<!DOCTYPE html>
<html>
<head>
<style>
body {background-color: powderblue;}
h1   {color: blue;}
p    {color: red;}
</style>
</head>
<body>

<h1>This is a heading</h1>
<p>This is a paragraph.</p>

</body>
</html>
```

## External

```
<!DOCTYPE html>
<html>
<head>
  <link rel="stylesheet" href="styles.css">
</head>
<body>

<h1>This is a heading</h1>
<p>This is a paragraph.</p>

</body>
</html>
```

## Class

To create a class; write a period (.) character, followed by a class name. Then, define the CSS properties within curly braces {}:

```
<!DOCTYPE html>
<html>
<head>
<style>
.city {
  background-color: tomato;
  color: white;
  padding: 10px;
}
</style>
</head>
<body>

<h2 class="city">London</h2>
<p>London is the capital of England.</p>

<h2 class="city">Paris</h2>
<p>Paris is the capital of France.</p>

<h2 class="city">Tokyo</h2>
<p>Tokyo is the capital of Japan.</p>

</body>
</html>
```


