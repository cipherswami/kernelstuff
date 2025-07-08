---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults
layout: default
title: Home
---

## Learn Kernel Programming <!-- omit in toc -->

Linux kernel programming is a specialized area that involves writing code that interacts directly with the operating system's kernel. This guide provides an overview of key concepts, practices, and resources for getting started in Linux kernel development.

#### Table of Contents <!-- omit in toc -->

- [Kernel Basics](#kernel-basics)
	- [What is Kernel Module](#what-is-kernel-module)
	- [What is a Device Driver](#what-is-a-device-driver)
- [Kernel Modules vs Device Driver](#kernel-modules-vs-device-driver)
- [Module Types](#module-types)
- [Basic Commands](#basic-commands)
- [insmod vs modprobe](#insmod-vs-modprobe)
	- [insmod](#insmod)
	- [modprobe](#modprobe)
- [How modprobe Calculates Dependencies](#how-modprobe-calculates-dependencies)


## Kernel Basics

###  What is Kernel Module

A **kernel module** is a piece of code that can be dynamically loaded into or unloaded from the kernel. It allows for kernel extension and modification without needing to recompile or reboot the system.

- Other names:
  - **Loadable Kernel Module (LKM)**
  - **Module**

- File extension: `.ko` (Kernel Object)

### What is a Device Driver

A **device driver** is software that enables the operating system (OS) to interact with hardware devices. The device driver acts as a mediator between three key components:

- **User Space:** The part of the operating system where user applications run.
- **Kernel Space:** The core of the operating system that manages hardware and system resources.
- **Hardware:** Physical devices that the OS needs to interact with.

```
	==================
	=     User       = ---------
	==================        |
	      |                   |
	      |                   |
	      |                   |
	==================        |
	=     Kernel     = Via Device File
	==================        |
	      |                   |
	      |  Device Driver    |
	      |                   |
	==================        |
	=    Hardware     = -------
	==================
```

## Kernel Modules vs Device Driver

Although kernel modules can include device drivers, they serve a broader purpose. A kernel module is a more general concept that refers to any piece of code that can be loaded into the kernel. Device drivers are one specific use case of kernel modules.

Kernel modules are used for:

1. **Device drivers** - Managing hardware devices
2. **File systems** - Managing data storage
3. **System calls** - Enabling kernel-user communication
4. **Network drivers** - Implementing networking protocols like TCP/IP
5. **TTY line disciplines** - Managing terminal devices

## Module Types

1. **In-Tree Modules**: Modules included in the official Linux kernel source code.
2. **Out-of-Tree Modules**: Modules developed independently of the kernel source and compiled separately.

Modules generally start as "out-of-tree" and become "in-tree" when accepted into the official kernel.

Kernel modules are typically installed in:

```
/lib/modules/<kernel_version>
```

## Basic Commands

- `lsmod`: Lists currently loaded modules.
- `insmod`: Inserts a specified module into the kernel.
- `rmmod`: Removes a module from the kernel.
- `modinfo`: Displays detailed information about a module.
- `modprobe`: Adds or removes modules, handling dependencies automatically.

## insmod vs modprobe

### insmod

- **Usage**: `insmod /path/to/module.ko`
- **Dependency Handling**: Does not handle dependencies automatically. Dependencies need to be manually resolved before loading the module.
- **Scope**: Can load modules from any location, as the full path is specified.

### modprobe

- **Usage**: `modprobe module_name`
- **Dependency Handling**: Automatically resolves and loads dependencies for the module.
- **Scope**: Searches for modules in the default system path (`/lib/modules/$(uname -r)`), making it easier to load modules.

## How modprobe Calculates Dependencies

`modprobe` relies on `depmod` to calculate module dependencies. These dependencies are stored in the `/lib/modules/$(uname -r)/modules.dep` file.

Example of dependencies listed in `modules.dep`:

```
kernel/drivers/adm8211.ko: kernel/net/cfg80211.ko kernel/drivers/eeprom_93cx6.ko
```

When running `modprobe adm8211`, `cfg80211` and `eeprom_93cx6` are loaded first, followed by `adm8211`. To remove the modules, they are unloaded in reverse order.

To update the dependencies, run:

```
depmod -a
```