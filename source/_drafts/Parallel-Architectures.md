---
title: Parallel Architectures
tags:
---

Source: *Computer Organization and Design* 

<!--more-->

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
