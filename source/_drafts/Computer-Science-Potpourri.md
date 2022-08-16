---
title: Computer Science Potpourri
tags: Toolkit
categories: Computer Science
---

Outline:

- [Keyboard remapping](https://missing.csail.mit.edu/2020/potpourri/#keyboard-remapping)
- [Daemons](https://missing.csail.mit.edu/2020/potpourri/#daemons)
- [FUSE](https://missing.csail.mit.edu/2020/potpourri/#fuse)
- [Backups](https://missing.csail.mit.edu/2020/potpourri/#backups)
- [APIs](https://missing.csail.mit.edu/2020/potpourri/#apis)
- [Common command-line flags/patterns](https://missing.csail.mit.edu/2020/potpourri/#common-command-line-flagspatterns)
- [Window managers](https://missing.csail.mit.edu/2020/potpourri/#window-managers)
- [VPNs](https://missing.csail.mit.edu/2020/potpourri/#vpns)
- [Markdown](https://missing.csail.mit.edu/2020/potpourri/#markdown)
- [Hammerspoon (desktop automation on macOS)](https://missing.csail.mit.edu/2020/potpourri/#hammerspoon-desktop-automation-on-macos)
- [Booting + Live USBs](https://missing.csail.mit.edu/2020/potpourri/#booting--live-usbs)
- [Docker, Vagrant, VMs, Cloud, OpenStack](https://missing.csail.mit.edu/2020/potpourri/#docker-vagrant-vms-cloud-openstack)
- [Notebook programming](https://missing.csail.mit.edu/2020/potpourri/#notebook-programming)
- Dependency management

<!--more-->

# Dependency management

The exact meaning of each one varies between projects, but one relatively common standard is [*semantic versioning*](https://semver.org/). With semantic versioning, every version number is of the form: `major.minor.patch`. The rules are:

- If a new release does not change the API, increase the patch version.
- If you *add* to your API in a backwards-compatible way, increase the minor version.
- If you change the API in a non-backwards-compatible way, increase the major version.

example:

* if I depend on your library at version `1.3.7`, then it *should* be fine to build it with `1.3.8`, `1.6.1`, or even `1.3.0`. Version `2.2.4` would probably not be okay, because the major version was increased. We can see an example of semantic versioning in Python’s version numbers. 
* Python3.9和Pthon3.7就不通，因为3.9、 3.7都是major版本号
