---
title: Computer System Evaluation
tags: Computer Architecture
categories: Computer Science
mathjax: true
date: 2024-02-06 20:03:07
---

Sources:

1. [UWashington: CSE378, Lecture13](https://courses.cs.washington.edu/courses/cse378/09wi/lectures/lec13.pdf)
1. John L. Hennessy & David A. Patterson. (2019). *Chapter 1. Fundamentals of Quantitative Design and Analysis. Computer Architecture: A Quantitative Approach* (6th ed.). Elsevier Inc.

<!--more-->

# Clock cycle time

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Computer%20Architecture/Computer%20System%20Evaluation/Cover.png" alt="image-20240226185036452" style="zoom:25%;" />

* One "cycle" is the minimum time it takes the CPU to do any work[^1].
  * The clock cycle time or clock period is just the length of a cycle.
  * The clock rate, or frequency, is the reciprocal of the cycle time.
* Generally, a higher frequency is better. Some examples illustrate some typical frequencies.
  * A 500MHz processor has a cycle time of 2ns.
  * A 2GHz (2000MHz) CPU has a cycle time of just 0.5ns (500ps).

# Moore’s Law

Moore’s Law: The number of transistor on a chip doubles every period of time (2, 1.5, or 2.5 years).

* It is enabled by Dennard Scaling.

* Dennard Scaling: As you reduce the size of the transistors, energy/power goes down proportionally.
  * However, Dennard Scaling started breaking down around 2003.

# Energy Consumption in CMOS Devices

The energy consumption in CMOS devices primarily occurs during the  switching of transistors from one state to another (from ON to OFF or  vice versa).

**Total Power Comsumption = Dynamic Power Consumption + Static Power Consumption**

## Dynamic Power Consumption

Dynamic power is consumed when transistors switch states. It is given by the equation:
$$
P_{\text {dynamic }}=\alpha \cdot C_L \cdot V_{D D}^2 \cdot f,
$$


where:
- $P_{\text {dynamic }}$ is the dynamic power consumption,

- $\alpha$ is the activity factor (fraction of the time the circuit is switching, usually equals to 1),

- $C_L$ is the load capacitance,

- $V_{D D}$ is the supply voltage, and

- $f$ is the switching frequency.

- The energy consumed per switching event is:
  $$
  E_{\text {switch }}=C_L \cdot V_{D D}^2
  $$
## Static Power Consumption:

Static power is consumed due to leakage currents when the transistors are in a non-switching (idle) state. It can be expressed as:
$$
P_{\text {static }}=I_{\text {leak }} \cdot V_{D D}
$$
where $I_{\text {leak }}$ is the leakage current.

## Total power consumption

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



```python
def total_power_consumption(voltage, frequency, capacitive_load, leakage_current, alpha=1.0, name=None, description=None):
    """
    Calculate the total power consumption of a system based on dynamic and static power components.

    Parameters:
    - voltage (float): Operating voltage in Volts.
    - frequency (float): Clock frequency in Hz.
    - capacitive_load (float): Capacitive load in Farads.
    - static_power (float): Static power consumption in Watts.
    - alpha (float, optional): Activity factor, defaults to 1.0 if not specified.
    - name (str, optional): Name of the system or component.
    - description (str, optional): Description of the system or component.

    Returns:
    - float: Total power consumption in Watts.
    """
    # Calculate dynamic power
    dynamic_power = alpha * capacitive_load * (voltage ** 2) * frequency
    static_power = leakage_current * voltage

    # Calculate total power
    total_power = dynamic_power + static_power

    # Optionally print the name and description if they are provided
    if name or description:
        print(f"Calculating power for: {name if name else 'Unnamed System'}")
        if description:
            print(f"Description: {description}")

    return total_power
```



# Latency and throughput

* Latency: Time a single fixed task costs to finish.
  * For example, the execution time of a benchmark is the latency.
* Throughput: Number of works/operations done in a fixed period of time.

# CPI

The average of Cycles Per Instruction in a given process (CPI) is defined by
$$
\mathrm{CPI}=\sum_{i=1}^n \mathrm{CPI}_i \times f_i \quad \text { where } f_i=\frac{\mathrm{I}_i}{\text { Instruction Count }}
$$

$f_i=$: Fraction of instructions of type $i$.



CPI is a measure related to the *latency*.



For example, for the multi-cycle MIPS:

Load: 5 cycles
Store: 4 cycles
R-type: 4 cycles 
Branch: 3 cycles
Jump: 3 cycles



If a program has

50% R-type instructions
10% load instructions
20% store instructions
8%  branch instructions
2%  jump instructions

then what is the CPI?
$$
\mathrm{CPI}=(4 \times 50+5 \times 10+4 \times 20+3 \times 8+3 \times 2) / 100=3.6
$$



# Iron Law

The performance of a processor is the time it takes to execute a program: $\frac{\text { Time }}{\text { Program }}$. This can be further broken down into three factors: ${ }^{4]}$
$$
\frac{\text { Time }}{\text { Program }} = 
\frac{\text { Instructions }}{\text { Program }} 
\times 
\frac{\text { ClockCycles }}{\text { Instruction }} 
\times 
\frac{\text { Time }}{\text { ClockCycles }}
$$
We have following dependencies:

1. the number of instructions depends on **architecture**.
2. the number of cycles per instruction (**CPI**) depends on **micro-architecture**.
3. time per cycle depends on **technology**.



Meanwhile, the *frequency* of the processor is 
$$
\text { frequency } = \frac{\text { ClockCycles }}{\text { Time }}
$$


```python
# Given data
cycles = 949429232883
time_seconds = 313.053

# Calculate the frequency in Hz
frequency_hz = cycles / time_seconds

# Convert frequency from Hz to GHz
frequency_ghz = frequency_hz / (10**9)
frequency_ghz
```

# Amdahl's Law

*"the overall performance improvement gained by optimizing a single part of a system is limited by the fraction of time that the improved part is actually used."*
$$
\text { Speedup }_{\text {overall }}=

\frac {\text { Old Time }} {\text {New Time}} =

\frac{1}{(1-P)+\frac{P}{S}}
$$
where:
- $P$ is the proportion of the execution time that the improvement affects, and
- $S$ is the speedup of the improved part (usually equals to the number of the CPU/PGPU cores).
- Here we hyphothesize $t_{\text {old }}$ and $t_{\text {new }}$ have the same frequency.

The proof of this equation is as follows:

1. By the definition of CPI, we have $t = I \times C P I \times \frac{1}{f}$, where $t$ is the total time costing.

2. We also know that, due to the effect of parallelism, we obtain $C P I_{\text {new }}=C P I_{\text {old }} \times\left(1-P+\frac{P}{S}\right)$.

3. Here we hyphothesize $t_{\text {old }}$ and $t_{\text {new }}$ have the same frequency, so that we have $t_{\text {new }}=t_{\text {old }} \times\left(1-p+\frac{p}{c}\right)$, the derivation is:
   $$
   \begin{aligned}
   & C P I_{\text {new }}=C P I_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \\
   & I \times C P I_{\text {new }} \times \frac{1}{f}=I \times C P I_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \times \frac{1}{f} \\
   & t_{\text {new }}=t_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \\
   & \text { Speedup }_{\text {overall }}= \frac {t_{\text {old }}} {t_{\text {new }}} = \frac{1}{(1-P)+\frac{P}{S}}.
   \end{aligned}
   $$
   



Note: If we have different frequency, the equation becomes $t_{\text {new }}=t_{\text {old }} \times\left(1-p+\frac{p}{c}\right) \times \frac{f_{\text {old }}}{f_{\text {new }}}$:
$$
\begin{aligned}
& \frac{1}{f_{\text {new }}}=\frac{1}{f_{\text {old }}} \times \frac{f_{\text {old }}}{f_{\text {new }}} \\
& I \times C P I_{\text {new }} \times \frac{1}{f_{\text {new }}}=I \times C P I_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \times \frac{1}{f_{\text {old }}} \\
& t_{\text {new }}=t_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \times \frac{f_{\text {old }}}{f_{\text {new }}} \\
& \text { Speedup }_{\text {overall }}= \frac {t_{\text {old }}} {t_{\text {new }}} = \frac{1}{(1-P)+\frac{P}{S}} \times \frac{f_{\text {new }}}{f_{\text {old }}}.

\end{aligned}
$$



## Example 1



Assume that you have a program which has a kernel, or the "main" part of the program, which can be accelerated by a GPU. The kernel makes up 95% of the program's execution time on a CPU system. There are two different GPU systems you could run this code on. System A has 48 GPU cores and provides a speedup of 40x for the kernel compared  to the CPU. System B has 96 GPU cores and provides a speedup of 50x for  the kernel compared to the CPU. What is the overall speedup for the entire program on System B compared  the System A?

Solution:

Given:
- The kernel makes up $95 \%$ of the program's execution time $(P=0.95)$.
- System A provides a 40x speedup for the kernel.
- System B provides a 50x speedup for the kernel.

First, let's calculate the execution time of the program on both systems in terms of the original CPU execution time ( $T_{\mathrm{CPU}}$ ).

System A Speedup
Speedup $_{\mathrm{A}}=\frac{1}{(1-0.95)+\frac{0.95}{40}}$
System B Speedup
Speedup $_B=\frac{1}{(1-0.95)+\frac{0.95}{50}}$
Let's calculate these:

System A
$$
\begin{aligned}
& \operatorname{Speedup}_A=\frac{1}{0.05+\frac{0.95}{40}} \\
& \text { Speedup }_A=\frac{1}{0.05+0.02375} \\
& \text { Speedup }_A=\frac{1}{0.07375} \approx 13.56
\end{aligned}
$$

System B
$$
\begin{aligned}
& \text { Speedup }_B=\frac{1}{0.05+\frac{0.95}{50}} \\
& \text { Speedup }_B=\frac{1}{0.05+0.019} \\
& \text { Speedup }_B=\frac{1}{0.069} \approx 14.49
\end{aligned}
$$

Now, to find the overall speedup of System B compared to System A, we divide the speedup of System B by the speedup of System A:
$$
\begin{aligned}
& \text { Overall Speedup }=\frac{\text { Speedup }_B}{\text { Speedup }_A} \\
& \text { Overall Speedup }=\frac{14.49}{13.56} \approx 1.069
\end{aligned}
$$

So, the overall speedup for the entire program on System B compared to System A is approximately 1.069.

## Example 2

There is a program in which 55% can be parallelized.

What is the *maximum possible* speedup you can achieve through parallelization?



Solution:

Consider
$$
\text { Speedup }_{\text {overall }}=

\frac{1}{(1-P)+\frac{P}{S}} ,
$$
if $S \rightarrow + \infty$ ,then $\frac{P}{S} \rightarrow0$, so the maximum speedup is $\frac{1}{(1-P)}$ = 1 / 0.45 = 2.222....

## Example 3

Assume you have an application where 75.0% is parallelizable.

You have three systems, a one core system and a two core system.

| Cores | Capacitance | Voltage | Frequency |
| ----- | ----------- | ------- | --------- |
| 1     | 1 \* c      | 1V      | 2 GHz     |
| 2     | 1.8 \* c    | 0.9V    | 1.5GHz    |

Given the Time, Power and Energy of the one core system:

* Time = 1 \* t
* Power = 2 \* c
* Energy = 2 ct

calculate the Time, Power and Energy of the two core system:



Solution:

Using
$$
t_{\text {new }}=t_{\text {old }} \times\left(1-P+\frac{P}{S}\right) \times \frac{f_{\text {old }}}{f_{\text {new }}}, 
$$
we can compute the Time to be $t_2=t_1 \times\left(0.25+\frac{0.75}{2}\right) \times \frac{2 G H z}{1.5 G H z}$ = 0.83 \* t.



Using
$$
P_{\text {dynamic }}=\alpha \cdot C_L \cdot V_{D D}^2 \cdot f ,
$$
we can compute the Power to be 1 \* 1.8^2 * 0.9 = 2.19 \* c.



So the Energy is: 0.83 \* t \* 2.19 \* c = 1.82 \* c \* t.




[^1]: In pipelined CPU design, because all stages proceed at the same time, the length of a processor cycle is determined by the time required for the slowest pipe stage.
