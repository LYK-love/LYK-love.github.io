---
title: Computer Science Checklist
tags:
---



# General

* [Learn XX in YY minutes](https://learnxinyminutes.com/)

# Computer architecture

* [GPU Survival Toolkit for the AI age: The bare minimum every developer must know](https://journal.hexmos.com/gpu-survival-toolkit/)
* [Algorithms for Modern Hardware](https://en.algorithmica.org/hpc/)

# Programming Languages

[Justine Tunney's Web Page](https://justine.lol/)

[Learning Zig](https://www.openmymind.net/learning_zig/)

# Computation theory

* [UWisc 2010s-CS710](https://pages.cs.wisc.edu/~dieter/Courses/2010s-CS710/Scribes/PDF/)



https://plato.stanford.edu/entries/turing-machine/

https://web.mit.edu/manoli/turing/www/turing.html

https://introcs.cs.princeton.edu/java/52turing/

https://web.stanford.edu/class/archive/cs/cs103/cs103.1132/lectures/19/Small19.pdf

https://gist.github.com/NikolasTzimoulis/2846116



Ne will show that starting from a value $n=2^j 3^k$, for any $j, k \in \mathbb{N}$, the next value $n^{\prime}$ that is only livisible by 2 and 3 is $n^{\prime}=2^k 3^{j+k}$. This gives the recurrence for the Fibonacci numbers, which mplies starting from $n=2^1 3^1$, this program outputs all consecutive pairs of Fibonacci numbers.


$$
n = 2^j 3^k \\
n^\prime = 2^k 3^{j+k} \\
n^{\prime \prime} = 2^{j+k} 3^{j+2k} = (2^j 3^k)( 2^k 3^{j+k} ) = n^{\prime} n\\
$$
