---
title: Security in Computer Architecture
tags: Computer Architecture
categories: Computer Science
mathjax: true

---

Sources:

<!--more-->

# CIA

CIA stands for Confidentiality, Integrity, and Availability. 

## Confidentiality

- **Definition**: Ensuring that information is not disclosed to unauthorized individuals, entities, or processes. **Other's can't read data**
- **In Computer Architecture**: Confidentiality involves designing systems and hardware that protect data from being accessed or intercepted by unauthorized users. This can include implementing hardware-level encryption mechanisms to secure data stored in memory or transmitted over a network. Secure execution environments, like Trusted Execution Environments (TEEs), ensure that sensitive operations are performed in isolated and secure portions of the processor, safeguarding sensitive data from the rest of the system.

## Integrity

- **Definition**: Maintaining and assuring the accuracy and completeness of data over its entire lifecycle. This means that the data <u>cannot be tampered</u> with or altered by unauthorized parties. **Other's can't modify data**
- **In Computer Architecture**: Integrity mechanisms ensure that data is not improperly modified, either intentionally or accidentally, and remains in its original state unless changed by authorized actions. Error detection and correction codes (e.g., ECC memory) are used to prevent data corruption. Techniques such as secure boot processes verify that system firmware and software have not been tampered with, ensuring that only verified code is executed.

## Availability

- **Definition**: Ensuring that information and resources are accessible to authorized users when needed. **Always available to do compute**
- **In Computer Architecture**: This involves designing systems that are resilient and can continue to operate even in the face of hardware failures, software errors, or cyber attacks. Redundancy, fault tolerance, and graceful degradation techniques are employed to maintain service availability. For example, redundant power supplies, RAID storage configurations, and error-correcting memory can help keep a system running smoothly despite component failures.

# Secure Hardware Design Principles 

- **Security by Design**: Why security should be considered from the outset. 
- **Least Privilege**: Restricting access to critical resources. 

# Hardware security mechanisms

Hardware security mechanisms are integral components of a computer  system designed to protect against various types of attacks, ensuring the confidentiality, integrity, and availability of data and operations. These mechanisms are implemented at the hardware level, which means they are <u>not part of the architecture</u> (they are microarchitecture).

## Virtual memory

**Process shouldn't see other processes' data** 



## Virtual machine (Virtualization-based confidential computing )

This has another level of protection for software 

![img](https://miro.medium.com/v2/0*Jae4bJGtSEV-dn1i.png)

> Unlike a VM, Docker containers *do not* boot up their own guest OS. Rather, they run on top of the host operating system. This is facilitated by a container engine.



Our focus here will be on VMs where the ISA presented by the VM and the underlying hardware match. Such VMs are called (operating) system virtual machines.

On a conventional platform, a single OS “owns” all the hardware resources, but with a VM, multiple OSes all share the hardware resources.

The software that supports VMs is called a virtual machine monitor (VMM) or hypervisor; the VMM is the heart of virtual machine technology. The underlying hardware platform is called the **host**, and its resources are shared among the **guest** VMs.

## Confidential Computing

"Confidential computing" (with trusted execution environments) 

- Guarantee that **no one, including OS/hypervisor can possibly see the data/code.** 
- We can do "at rest" 
- We can do "in flight" 
- But not while we're computing 

- Main examples: **Intel's SGX**, then AMD's SEV and Intel's TDX, Arm Trustzone and Realms 

- Data confidentiality: Usually through **encrypting memory** 

  - Do we store encrypted data in the cache? Why or why not? 

- Data integrity: How to ensure someone doesn't change the data? 

  - Can do a Merkle tree (SGX) 

- Code integrity: use same things as data 

- Attestation: How do we know that the code/data that we are running haven't already been modified 

  - Remote attestation 
  - Need hardware support to check crypto signatures 
  - Need to have a "root of trust" that is based in hardware 
  - Measurement is key 
  - Also need to trust *someone*… 

  

Confidential computing is a security mechanism that protects data in use by **performing computation in a hardware-based Trusted Execution  Environment (TEE)**. Unlike traditional approaches that focus on data at  rest and in transit, confidential computing specifically addresses the  security of data while it's being processed.

**How it Works**: Confidential computing utilizes secure enclaves or <u>secure partitions within the CPU</u> or another processing unit. 

**Benefits**:

- **Enhanced Security**: By isolating the execution environment, it protects sensitive data from unauthorized access, even if the system is compromised.
- **Privacy Assurance**: Enables companies to process sensitive data in shared environments (e.g., cloud computing) with the assurance that the data is protected.
- **Compliance**: Helps organizations meet strict data protection regulations by providing a higher level of security for sensitive information.

**Challenges**:

- **Performance Overheads**: The encryption/decryption processes and the secure context switching can introduce performance overheads.
- **Limited Accessibility**: Data and operations within an enclave are not accessible to external processes, which, while a security feature, can also limit functionality and interoperability.

# Side-Channel Attacks

A side-channel attack is a security exploit that <u>targets the implementation</u> of a computer system rather than exploiting weaknesses in the actual software or algorithms. This type of attack relies on  information gained from the <u>physical implementation</u> of a system,  including, but not limited to, timing information, power consumption,  electromagnetic leaks, or even sound to extract secret data.





- Covert channel: Communicate information **not using shared memory** 

- Side channel: A covert channel where **the sender doesn't intend to send data** 

  

## Common Types of Side-Channel Attacks:

1. **Timing Attacks**: Exploiting variations in execution time. 
2. **Power Analysis Attacks**: Leveraging power consumption patterns. 
3. **Differential Power Analysis (DPA)**: Detecting cryptographic key leakage. 



Countermeasures: **Masking, blinding, and noise injection.** 

```
torchrun --standalone --nproc_per_node 1 scripts/inference.py configs/opensora/inference/16x512x512.py --ckpt-path $CKPT --prompt-path ./assets/texts/t2v_samples.txt

```

