---
title: Shebang
tags:
---

https://linuskarlsson.se/blog/shebang-shenanigans/





## Helpers

To easily see how arguments are passed to a binary, a wrote a small helper application in C. It prints one line for every argument passed.

```c
#include <stdio.h>

int main(int argc, char **argv)
{
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	return 0;
}
```

Copy

Running it like `./args hi there reader` provides the following output:

```shell
$ ./args hi there reader
argv[0]: ./args
argv[1]: hi
argv[2]: there
argv[3]: reader
```

Copy

I copy this binary to `/usr/local/bin/args`, and then proceed to create the following test file, and make it executable with `chmod +x file.txt`.

```
#!/usr/local/bin/args -a -b --something

hello i'm a line that doesn't matter
```

Now, let’s try it out on different systems!

## Linux

As explained before this produced the following output:

```shell
$ ./file.txt
argv[0]: /usr/local/bin/args
argv[1]: -a -b --something
argv[2]: ./file.txt
```

Copy

As we can see, `argv[1]` has all flags stored as a single argument. :(

## FreeBSD / OpenBSD

Nothing exciting here, it turns out both these systems work the same way as Linux regarding shebangs.

```shell
$ ./file.txt
argv[0]: /usr/local/bin/args
argv[1]: -a -b --something
argv[2]: ./file.txt
```

Copy

## macOS

This worked exactly as I expected initially! Here each argument is passed independently to the interpreter.

```shell
$ ./file.txt
argv[0]: /Users/linus/args
argv[1]: -a
argv[2]: -b
argv[3]: --something
argv[4]: ./file.txt
```

Copy

## OpenIndiana

I also wanted to try out a Solaris-fork, in this case OpenIndiana, to try out different Unixes. Turns out this provided different results as well:

```shell
$ ./file.txt
argv[0]: /usr/local/bin/args
argv[1]: -a
argv[2]: ./file.txt
```

Copy

As we can see, OpenIndiana completely throws away anything except the first argument. (What? ಠ_ಠ )

## Summary

The results can be summarized in the following table:

|                 | argv[0]               | argv[1]             | argv[2]      | argv[3]       | argv[4]      |
| --------------- | --------------------- | ------------------- | ------------ | ------------- | ------------ |
| Linux           | `/usr/local/bin/args` | `-a -b --something` | `./file.txt` |               |              |
| FreeBSD OpenBSD | `/usr/local/bin/args` | `-a -b --something` | `./file.txt` |               |              |
| macOS           | `/usr/local/bin/args` | `-a`                | `-b`         | `--something` | `./file.txt` |
| OpenIndiana     | `/usr/local/bin/args` | `-a`                | `./file.txt` |               |              |
