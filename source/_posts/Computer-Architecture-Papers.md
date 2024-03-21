---
title: Computer Architecture Papers
date: 2024-03-19 22:49:45
tags:
---

Used for ECS 201A final.

<!--more-->

<!--more-->

# An Empirical Guide to the Behavior and Use of Scalable Persistent Memory

DIMM (**Dual In-Line Memory Module**)

Over the past ten years, researchers have been anticipating the arrival of commercially available, scalable **non-volatile main memory (NVMM)** technologies that provide “byte-addressable” storage that survives power outages. With the arrival of Intel’s Optane DC Persistent Memory Module (which we refer to as **Optane DIMMs**),

The widely expressed expectation was that NVDIMMs would have behavior that was broadly similar to DRAM-based DIMMs but with lower performance (i.e., **higher latency and lower bandwidth**).

This paper <u>presents a detailed evaluation of the behavior and performance of Optane DIMMs on microbenchmarks</u> and applications and <u>provides concrete, actionable guidelines</u> for how programmers should tune their programs to make the best use of these new memories. 

# Fundamental Latency Trade-offs in Architecting DRAM Caches

* This paper analyzes the design trade-offs in architecting large-scale **DRAM caches**.
* Some of the basic design decisions typically made for conventional caches are **detrimental** to the performance of **DRAM caches**, as they **exacerbate the already high hit latency**. 
* We show that higher performance can be obtained by optimizing the DRAM cache architecture **first for latency, and then for hit rate.**

# Efficient Virtual Memory for Big Memory Servers

*“Virtual memory was invented in a time of scarcity. Is it still a good idea?”*

*– Charles Thacker, 2010 ACM Turing Award Lecture.*



* virtual memory usage has changed dramatically in recent years
* While address translation can be accel- erated by TLB hits, **misses** are **costly**.
* Our analysis shows that **many “big-memory” server workloads**, such as databases, in-memory caches, and graph analytics, pay a high cost for page-based virtual memory. They **consume as much as 10% of execution cycles on TLB misses**, even using large pages. 
* To remove the TLB miss overhead for big-memory workloads, we propose <u>mapping part of a process’s linear virtual address space with a *direct segment*</u>, while page <u>mapping the rest of the virtual address space.</u>

#         Pioneering Chiplet Technology and Design for the AMD EPYC™ and Ryzen™ Processor Families          

* disintegrating the traditional monolithic silicon chip into multiple smaller “chiplets.
* The overall idea with chiplets is to take what would normally be a monolithic, single-die SoC, and then partition it into multiple smaller die or “chiplets” and then “reintegrate” them with some form of in-package interconnect to enable the collective to operate as a single, logical SoC.
* After chip construction, each SoC die undergoes a test procedure to deter-
  mine functionality, also commonly called “known good die” (KGD) testing.
* The chiplets can be **individually tested** and then reassembled and packaged into the complete final SoCs. Now, for the same fault distribution as in the monolithic case, each potential defect results in discarding only approximately one-fourth of the amount of silicon. 

# In-Datacenter Performance Analysis of a Tensor Processing Unit

* Doubling the total amount of Google's datacenters if everyone used voice 3 minutes per day. 
* Batches 
  - Try to do as much as you can within the maximum latency 
* response time matter? 
* **domain-specific hardware**
* **using the GPU’s GDDR5 memory**
* **throughput**
