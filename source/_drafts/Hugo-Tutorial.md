---
title: Hugo Tutorial
tags:
---



# Intro

https://kodify.net/hugo-static-site-tutorials/







## Math

https://gohugo.io/functions/math/

## Taxnomomy

https://gohugo.io/templates/taxonomy-templates/#order-taxonomies



# Menus

https://gohugo.io/content-management/menus/

# Shortcode

https://gohugo.io/templates/shortcode-templates/

# Count

```
Number of pages: {{ len .Site.RegularPages }}
```



One way to access pages currently rendered by Hugo is `.Site.RegularPages`. That template variable returns an array of all page content in the current language (Hugo Docs, 2017a). Typical uses for this array include outputting a list with the site’s newest pages or populating a RSS feed. For our purposes, we’re simply counting the length of this array next.



If you’re building a multilingual site with Hugo, consider using the `.Site.AllPages` template variable instead of `.Site.RegularPages`. The difference between these is that `.Site.AllPages` returns an array of all pages regardless of their translation, while `.Site.RegularPages` only contains content written in the site’s current language (Hugo Docs, 2017a).



The number of pages that Hugo generates (and thus the amount of pages in `.Site.RegularPages`) can differ from the amount of files we have in our `/content/` folder. That’s because, by default, the `hugo` command line command *does not* [render draft content](https://kodify.net/hugo/pages/generate-draft-content/), [generate expired content](https://kodify.net/hugo/pages/generate-expired-content/), and [build future content](https://kodify.net/hugo/pages/generate-future-content/) (Hugo Docs, 2017c).



The `len` function originates from the Go programming language, and that is the same language that Hugo is build with. One Go feature that we can use in Hugo theme files is the `len` function (Hugo Docs, 2016), which returns the length of its argument (Go Programming Language, n.d.).

With that counting the number of pages is simply done by placing the `len` function before `.Site.RegularPages`. And since Hugo template files by default already print returned values, whichever length `len` returns appears in our rendered page.

# Variables

https://gohugo.io/variables/site/
