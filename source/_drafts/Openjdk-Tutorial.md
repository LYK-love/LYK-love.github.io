---
title: Openjdk Tutorial
tags:
---



[OpenJDK](https://openjdk.org/groups/build/doc/building.html)

[JDK20](https://openjdk.org/projects/jdk/20/)

## TL;DR (Instructions for the Impatient)

If you are eager to try out building the JDK, these simple steps works most of the time. They assume that you have installed Git (and Cygwin if running on Windows) and cloned the top-level JDK repository that you want to build.

1. [Get the complete source code](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#getting-the-source-code):
   `git clone https://git.openjdk.org/jdk/`

2. [Run configure](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#running-configure):
   `bash configure`

   If `configure` fails due to missing dependencies (to either the [toolchain](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#native-compiler-toolchain-requirements), [build tools](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#build-tools-requirements), [external libraries](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#external-library-requirements) or the [boot JDK](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#boot-jdk-requirements)), most of the time it prints a suggestion on how to resolve the situation on your platform. Follow the instructions, and try running `bash configure` again.

3. [Run make](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html#running-make):
   `make images`

4. Verify your newly built JDK:
   `./build/*/images/jdk/bin/java -version`

5. [Run basic tests](https://htmlpreview.github.io/?https://raw.githubusercontent.com/openjdk/jdk/master/doc/building.html##running-tests):
   `make run-test-tier1`

If any of these steps failed, or if you want to know more about build requirements or build functionality, please continue reading this document.
