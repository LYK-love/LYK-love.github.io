---
title: Tensor Processing Units
tags:
  - Hardware
  - Machine Learning
categories: Computer Science
date: 2024-03-10 18:57:07
---


Sources:

* TPU v1: [In-Datacenter Performance Analysis of a Tensor Processing Unit](https://arxiv.org/pdf/1704.04760.pdf). 2017.
* TPU v2, v3: [A Domain Specific Supercomputer for Training Deep Neural Networks](https://dl.acm.org/doi/pdf/10.1145/3360307).
* [AI Chips: Google TPU](https://jonathan-hui.medium.com/ai-chips-tpu-3fa0b2451a2d)
* [HotChips 2019 Tutorial Cloud TPU: Codesigning Architecture and Infrastructure](https://old.hotchips.org/hc31/HC31_T3_Cloud_TPU_Codesign.pdf)



*Many architects believe that major improvements in cost-energy-performance must now come from domain-specific hardware.*

<!--more-->

# TPU block diagram

Below is the Block Diagram of TPU v1 in 2017:

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/TPU%20v1%20Block%20Diagram.png" alt="TPU v1 Block Diagram" style="zoom:67%;" />



The main computation part is the yellow **Matrix Multiply Unit (MXU)** in the upper right hand corner. Its inputs are the blue Weight FIFO and the blue **Unified Buffer (UB)** and its output is the blue Accumulators (Acc). The yellow **Activation Unit (AU)** performs the nonlinear functions on the Acc, which go to the UB.



The main componnets are:

- **Matrix Multiplier Unit (MXU)**: 65,536 8-bit multiply-and-add units for matrix operations
- **Unified Buffer (UB)**: 24MB of SRAM that work as registers
- **Activation Unit (AU)**: Hardwired activation functions

# Key components

## Matrix Multiplier Unit (MXU)

At least in TPU v1, each MXU performs 16K multiply-accumulate operations in each cycle using [BF16 precision](https://cloud.google.com/blog/products/ai-machine-learning/bfloat16-the-secret-to-high-performance-on-cloud-tpus) (16 bits with value cover the range of FP32 but in lower precision) for the internal multiplication and FP32 for accumulation.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/bfloat16.png" alt="bfloat16" style="zoom:50%;" />

# Floor plan of TPU die

Because general-purpose processors such as CPUs and GPUs must provide good performance across a wide range of applications, they have evolved myriad sophisticated, performance-oriented mechanisms. As a side effect, the behavior of those processors can be difficult to predict, which  makes it hard to guarantee a certain latency limit on neural network  inference. 

In contrast, TPU design is strictly **minimal**. You can see its simplicity in the floor plan of the TPU die.

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Floor%20Plan%20of%20TPU%20v1%20die%28yellow%20%3D%20compute%2C%20blue%20%3D%20data%2C%20green%20%3D%20I%3AO%2C%20red%20%3D%20control%29.png" alt="Floor Plan of TPU v1 die(yellow = compute, blue = data, green = I/O, red = control)" style="zoom: 50%;" />

(yellow = compute, blue = data, green = I/O, red = control)

# Systolic array

<img src="https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20data%20flow%20of%20the%20Matrix%20Multiply%20Unit.png" alt="Systolic data flow of the Matrix Multiply Unit" style="zoom:33%;" />

TPU implements the Matrix Unit (MXU) with the [systolic array](https://en.wikipedia.org/wiki/Systolic_array) in a pipeline fashion.

In TPU v1, the MXU is a 128 x 128 systolic array. Below is the processing logic of a systolic array. Images are from [->source](Modified from [source](https://www.hotchips.org/hc31/HC31_T3_Cloud_TPU_Codesign.pdf)).

## Load the values of a matrix

![Systolic Array: Load the values of a matrix](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20Load%20the%20values%20of%20a%20matrix.png)

## t=1

![Systolic Array: t=1](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D1.png)



## t=2

![Systolic Array: t=2](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D2.png)

## t=3

![Systolic Array: t=3](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D3.png)

## t=4

![Systolic Array: t=4](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D4.png)

## t=5

![Systolic Array: t=5](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D5.png)

## t=6

![Systolic Array: t=6](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D6.png)

## t=7

![Systolic Array: t=7](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D7.png)

## t=8

![Systolic Array: t=8](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Systolic%20Array-%20t%3D8.png)



# Technogies

## Quantization in neural networks

*"If it’s raining outside, you probably don’t need to know exactly how many droplets of water are falling per*
*second — you just wonder whether it’s raining lightly or heavily. Similarly, neural network predictions*
*often don't require the precision of floating point calculations." ([Source](https://cloud.google.com/blog/products/ai-machine-learning/an-in-depth-look-at-googles-first-tensor-processing-unit-tpu))*

![Quantization in TensorFlow](https://lyk-love.oss-cn-shanghai.aliyuncs.com/Hardware/Tensor%20Processing%20Units/Quantization%20in%20TensorFlow.png)

Quantization: Before inference phase, Google will apply an extra step called *quantization* transforms floating-point numbers into narrow integers—often just **8-bit integer**s—which are usually good enough for inference.

The idea is that 8-bit integers are usually good enough for inference.

## The TPU instruction set

Since TPU is highly specilized, it has a lot of instructions dedicated for neural networks. As a result, it uses a Complex Instruction Set Computer (CISC) design, instead of the popular Reduced Instruction Set Computer (RISC) design.



TPU v1 defined  a dozen high-level instructions. Five of these operations are highlighted below.

| TPU Instruction         | Function                                                     |
| ----------------------- | ------------------------------------------------------------ |
| Read_Host_Memory        | Read data from memory                                        |
| Read_Weights            | Read weights from memory                                     |
| MatrixMultiply/Convolve | Multiply or convolve with the data and weights,accumulate the results |
| Activate                | Apply activation functions                                   |
| Write_Host_Memory       | Write result to memory                                       |



# Pitfalls

**Ideas that didn't fly for general-purpose computing may be ideal for domain-specific architectures.** 

For the TPU, three important architectural features date back to the early 1980s: systolic arrays, decoupled-access/execute, and CISC instructions. The first reduced the area and power of the large matrix multiply unit, the second fetches weights concurrently during operation of the matrix multiply unit, and the third better utilizes the limited bandwidth of the PCIe bus for delivering instructions. Historyaware architects could have a competitive edge.
