---
title: Rust Tools
tags: Rust
categories: Software Engineering
date: 2024-01-09 20:56:42
---


Sources:

1. [--> How To Install Rust on Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/install-rust-on-ubuntu-linux)

<!--more-->

# Install



1. Run the command to download the `rustup` tool and install the latest stable version of Rust:

   ```bash
   curl --proto '=https' --tlsv1.3 https://sh.rustup.rs -sSf | sh
   ```

   Next, run the following command to add the Rust toolchain directory to the PATH environment variable:

   ```bash
   source $HOME/.cargo/env
   ```

2. Verify the Rust installation by requesting the version:

   ```bash
   rustc --version
   ```

3. Installing a Compiler

   Rust requires a linker program to join compiled outputs into one file. The GNU Compiler Collection (`gcc`) in the `build-essential` package includes a linker. If you don’t install `gcc`, you need to use `apt` to install the `build-essential` package.

   1. First, update the Apt package index:

      ```bash
      sudo apt update
      ```

   2. Next, upgrade any out-of-date packages:

      ```bash
      sudo apt upgrade
      ```

   3. When the upgrades are complete, install the `build-essential` package:

      ```bash
      sudo apt install build-essential
      ```

Now rust and corresponding tools (rustup, cargo) have been installed
