---
title: Exceptional Control Flow
tags:
---

# Intro

## Control Flow

CPU从接上电源开始就不停地处理指令, 指令形成了如下序列:
$$
a_0, a_1, \dots, a_{n−1}
$$
where each $a_k$ is the address of some corresponding instruction $I_k$. Each transition from $a_k$ to $a_{k+1}$ is called a *control transfer*. A sequence of such control transfers is called the *flow of control*, or *control flow*, of the processor.

* The simplest kind of control flow is a “smooth” sequence where each $I_k$ and $I_{k+1}$ are adjacent in memory. 
* Typically, <u>abrupt changes</u> to this smooth flow, where $I_{k+1}$ is not adjacent to  $I_k$, are caused by familiar program instructions such as jumps, calls, and returns.
  * Such instructions are necessary mechanisms that allow programs to react to changes in <u>internal program state</u> represented by program variables.
* 但是, 系统必须对外部状态所引起的改变也有所反应. 外部状态指的是各种I\O设备. 
* ECF: Modern systems react to these situations by making abrupt changes in the control flow. In general, we refer to these abrupt changes as *exceptional control flow (ECF)*. ECF occurs at all levels of a computer system. For example, at the hardware level, events detected by the hardware trigger abrupt control transfers to exception handlers. At the operating systems level, the kernel transfers control from one user process to another via context switches. At the application level, a process can send a *signal* to another process that abruptly transfers control to a signal handler in the recipient.



# Exceptions

## Classes of Exceptions

可以把异常分为同步和异步的:

* **Asynchronous exceptions** occur as a result of events in **I/O devices** that are external to the processor. 
* **Synchronous exceptions** occur as a **direct result of executing an instruction**.

| Class     | Cause                         | Async/sync | Return behavior                     |
| --------- | ----------------------------- | ---------- | ----------------------------------- |
| Interrupt | Signal from I/O device        | Async      | Always returns to next instruction  |
| Trap      | Intentional exception         | Sync       | Always returns to next instruction  |
| Fault     | Potentially recoverable error | Sync       | Might return to current instruction |
| Abort     | Nonrecoverable error          | Sync       | Never returns                       |
|           |                               |            |                                     |



### Interrupts

* 







# Processes

# System Call Error Handling 773

# Process Control 774

# Signals 792

# Nonlocal Jumps 817

# Tools for Manipulating Processes 822

