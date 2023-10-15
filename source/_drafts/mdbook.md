---
title: mdbook
tags:
---

# Mathjax Support

https://rust-lang.github.io/mdBook/format/mathjax.html



To enable MathJax, you need to add the `mathjax-support` key to your `book.toml` under the `output.html` section.

```toml
[output.html]
mathjax-support = true
```



### [Inline equations](https://rust-lang.github.io/mdBook/format/mathjax.html#inline-equations)

Inline equations are delimited by `\\(` and `\\)`. So for example, to render the following inline equation ∫xdx=x22+C∫���=�22+� you would write the following:

```
\\( \int x dx = \frac{x^2}{2} + C \\)
```

### [Block equations](https://rust-lang.github.io/mdBook/format/mathjax.html#block-equations)

Block equations are delimited by `\\[` and `\\]`. To render the following equation



μ=1N∑i=0xi�=1�∑�=0��



you would write:

```bash
\\[ \mu = \frac{1}{N} \sum_{i=0} x_i \\]
```
