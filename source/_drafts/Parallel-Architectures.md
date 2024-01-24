---
title: Parallel Architectures
tags:
---

# Amdahl's Law

Amdahl's Law is a principle used in computer architecture and parallel computing to predict the theoretical maximum speedup for a program when only part of the program can be parallelized. It is named after computer scientist Gene Amdahl, who presented the concept in 1967.

Amdahl's Law can be stated as follows:
$$
\text{Speedup}=\frac {1} {(1−P)+\frac{P}{N}}
$$




Where:

- **Speedup**: The theoretical maximum speedup of the execution of the whole task.
- **P**: **The proportion of the execution time that the task can be parallelized** (i.e., the part of the task that can benefit from parallel execution). This is a value between 0 and 1, where 0 means no part of the task can be parallelized and 1 means the entire task can be parallelized.
- **N**: The number of processors.

This law highlights a key limitation in parallel computing: if a part of a task cannot be parallelized and must be executed serially, this part limits the overall speedup that can be achieved by adding more processors. Even with an infinite number of processors, the speedup will be limited by the serial fraction of the task.

# Region of Interest

Region of Interest (ROI): code snippet that we are interested in.



# Latencies

* **issue latency**: the number of cycles between injection two consecutive instructions into the pipeline. An **issue latency** of `4 cycles` means that an instruction is injected to the pipeline, every *4 cycles*. On the other hand,
* Issue latency in a computer processor refers to the time delay between  when an instruction is decoded and when it actually starts its execution phase. 
* **floating point operation latency**: the number of cycles it takes to complete the execution of a **floating point instruction**.
* **integer point operation latency**: the number of cycles it takes to complete the execution of a **integer instruction**.
  * the latency for floating point and integer operations typically occurs  during the execution stage of the pipeline in a processor. I

# Arithmetic intensity

Arithmetic intensity is usually expressed in terms of "flops per byte."

1. **Flops (Floating Point Operations per Second):** This measures the number of arithmetic operations performed by the algorithm. For instance, adding two numbers or multiplying two numbers each count as one flop.
2. **Data Movement:** This refers to the amount of data that needs to be read from or written to memory or moved across the network for the algorithm to complete its execution.

The formula for arithmetic intensity is:
$$
\text { Arithmetic Intensity }=\frac{\text { Number of Flops }}{\text { Amount of Data Movement (in bytes) }}
$$


High arithmetic intensity implies that an algorithm performs many operations relative to the amount of data it moves. This is typically seen as desirable because it means the algorithm spends more time doing useful computational work and less time waiting for data to be moved in and out of memory (which is a relatively slow operation). 
