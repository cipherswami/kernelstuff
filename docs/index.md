# Kernel Proagramming <!-- omit in toc -->

This document provides an overview of kernel programming and various concepts related to device drivers, kernel modules, and commands for managing them.

### Table of Contents <!-- omit in toc -->

- [What is a device driver](#what-is-a-device-driver)
- [What is a Kernel Module](#what-is-a-kernel-module)
	- [Other Names](#other-names)
	- [Standard Location for Kernel Modules](#standard-location-for-kernel-modules)
- [Device Driver vs Kernel Modules](#device-driver-vs-kernel-modules)
- [Advantages of Kernel Modules](#advantages-of-kernel-modules)
- [Disadvantages of Kernel Modules](#disadvantages-of-kernel-modules)
- [Types of Modules](#types-of-modules)
- [Basic Commands](#basic-commands)
- [insmod vs modprobe](#insmod-vs-modprobe)
	- [How modprobe calculates dependencies?](#how-modprobe-calculates-dependencies)

## What is a device driver

A device driver is a piece of software that controls a particular type of device which is connected to the computer system. Device driver has three sides:  

- one talks with Kernel Space  
- one talks with hardware  
- one talks wirh User Space  

Diagram:

```
	==================
	=		 =
	=   User	 =  ---------
	= 		 =	    |
	==================          |
		|                   |
		|                   |
		|                   |
	==================          |
	=		 =          |
	=   Kernel	 =          |
	= 		 =          |  Via Device File
	==================          |
		|                   |
		|Device Driver 
		|                   |
	==================          |
	=		 =          |
	=   Hardware	 = ---------
	= 		 =
	==================
```

## What is a Kernel Module

Kernel Modules are piece of code that can be loaded/inserted and unloaded/removed from the kernel as per the demand/need. Traditional way of adding code to the kernel was to recompile the kernel and reboot the system. 

### Other Names

1. Loadable Kernel Modules (LKM)
2. Modules

Extension: .ko (Kernel Object)

### Standard Location for Kernel Modules

Modules are installed in the  below directory of the rootfs by default:   

```
/lib/modules/<kernel version>
```

## Device Driver vs Kernel Modules

A kernel module may not be a device driver at all. A driver is like a sub-class of module.

Modules are used for the below:

1. Device Drivers.
2. File System.
3. System Calls.
4. Network drivers: Drivers implementing a network protocol (TCP/IP).
5. TTY line disciplines: For terminal devices.

## Advantages of Kernel Modules

1. All parts of the base kernel stay loaded all the time. Modules can save you memory, because you have to have them loaded only when you're actually using them

2. Users would need to rebuild and reboot the kernel every time they would require a new functionality.

3. A bug in driver which is compiled as a part of kernel will stop system from loading, whereas module allows systems to load. 

4. Faster to maintain and debug

5. Makes it easier to maintain multiple machines on a single kernel base.

## Disadvantages of Kernel Modules

1. Size:  Module management consumes unpageable kernel memory.  
	- A basic kernel with a number of modules loaded will consume more memory than an equivalent kernel with the drivers compiled into the kernel image itself. 
	- This can be a very significant issue on machines with limited physical memory.

2. As the kernel modules are loaded very late in the boot process, hence core functionality has to go in the base kernel (E.g. Memory Management)

3. Security: If you build your kernel statically and disable Linux's dynamic module loading feature, you prevent run-time modification of the kernel code. In order to support modules, the kernel must have been built with the following option enabled:
	```
	CONFIG_MODULES=y
	```
## Types of Modules

1. In-Source Tree: Modules present in the Linux Kernel Source Code

2. Out-of-Tree: Modules not present in the Linux Kernel Source Code.

All modules start out as "out-of-tree" developments, that can be compiled using the context of a source-tree. 

Once a module gets accepted to be included, it becomes an in-tree module.

## Basic Commands

1. lsmod – List Modules that Loaded Already
2. insmod – Insert Module into Kernel
3. rmmod – Remove Module from Kernel
4. modinfo – Display Module Info
5. modprobe – Add or Remove modules from the kernel

## insmod vs modprobe

insmod:		Loads the module given 'insmod /path/to/module.ko'
modprobe:	Loads the module only in /lib/modules/$(uname -r) 'modprobe /home/test/hello.ko' will not work

insmod:		Dependencies if present are not loaded
modprobe:	modprobe calculates dependencies, loads the dependencies and then the main module

### How modprobe calculates dependencies?

Modprobe depends on depmod tool to calculate dependencies.
depmod calculates dependencies of all the  modules present in `/lib/modules/$(uname -r)` folder, and places the dependency information in `/lib/modules/$(uname -r)/modules.dep` file

Exapmle:
```bash
kernel/drivers/net/wireless/admtek/adm8211.ko: kernel/net/mac80211/mac80211.ko kernel/net/wireless/cfg80211.ko      kernel/drivers/misc/eeprom/eeprom_93cx6.ko

When you say modprobe adm8211.ko, eeprom_93cx6.ko, cfg80211.ko is loaded first and then adm8211.ko

Modules are loaded right  to left and removed left to right

So while removing adm8211.ko is removed, then cfg80211.ko and finally eeprom_93cx6.ko

We can re-load the modules.dep file by running "depmod -a" command
```
