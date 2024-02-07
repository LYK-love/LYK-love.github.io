---
title: Computer System Evaluation
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 20:03:07
---

Source:

1. John L. Hennessy & David A. Patterson. (2019). *Chapter 1. Fundamentals of Quantitative Design and Analysis. Computer Architecture: A Quantitative Approach* (6th ed.). Elsevier Inc.

<!--more-->

# Current Computing

Moore’s Law:The number of transistor on a chip doubles every period of time (2, 1.5, or 2.5 years).

* It is enabled by Dennard Scaling.

* Dennard Scaling: As you reduce the size of the transistors, energy/power goes down proportionally.
  * However, Dennard Scaling started breaking down around 2003.

## Energy Consumption in CMOS Devices

The energy consumption in CMOS devices primarily occurs during the  switching of transistors from one state to another (from ON to OFF or  vice versa).

Total Power Comsumption = Dynamic Power Consumption + Static Power Consumption

### Dynamic Power Consumption

Dynamic power is consumed when transistors switch states. It is given by the equation:
$$
P_{\text {dynamic }}=\alpha \cdot C_L \cdot V_{D D}^2 \cdot f
$$


where:
- $P_{\text {dynamic }}$ is the dynamic power consumption,

- $\alpha$ is the activity factor (fraction of the time the circuit is switching),

- $C_L$ is the load capacitance,

- $V_{D D}$ is the supply voltage, and

- $f$ is the switching frequency.

- The energy consumed per switching event is:
  $$
  E_{\text {switch }}=C_L \cdot V_{D D}^2
  $$
### Static Power Consumption:

Static power is consumed due to leakage currents when the transistors are in a non-switching (idle) state. It can be expressed as:
$$
P_{\text {static }}=I_{\text {leak }} \cdot V_{D D}
$$
where $I_{\text {leak }}$ is the leakage current.

### Total power consumption?

$$
\begin{aligned}
P_\text{total} 
&= P_{\text {dynamic }} + P_{\text {static }} \\
&= \alpha \cdot C_L \cdot V_{D D}^2 \cdot f + I_{\text {leak }} \cdot V_{D D}
\end{aligned}
$$



How to reduce power consumption?

1. Lower the voltage
2. Lower the frequency



# Performance

Performance: latency and throughput

* Latency: Time a single fixed task costs to finish.
  * For example, the execution time of a benchmark is the latency.
* Throughput: Number of works/operations done in a fixed period of time.
  * For example, the CPI is the throughput.



## Iron Law
$$
\text{CPU iime} = \text{the number of instructions} \times \text{cycle per instruction} \times \text{time per cycle}
$$

= architecture * micro-architecture * technology







## Amdahl's Law
*"the overall performance improvement gained by optimizing a single part of a system is limited by the fraction of time that the improved part is actually used."*



Speedup = old time $/$ new time


$$
S_{\text {latency }}(s)=\frac{1}{(1-p)+\frac{p}{s}}
$$
where
- $S_{\text {latency }}$ is the theoretical speedup of the execution of the whole task;
- $s$ is the speedup of the part of the task that benefits from improved system resources;
- $p$ is the proportion of execution time that the part benefiting from improved resources originally occupied.
