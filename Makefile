###################### Linux Kernel Module Makefile #######################
# Author			: 	Aravind Potluri <aravindswami135@gmail.com>
# Arguments		:
# 		all					- Builds all module.
# 		module			- Builds the defined module.
# 		clean				- Cleans the module build artifacts.
# 		sign				- Signs the module. [Requires *signmod]
# 		lsmod				- List the last few installed modules.
# 		insert			- Inserts the module for testing.
# 		remove			- Removes the inserted module.
# 		install			- Module will be placed in source tree.
# 		uninstall		- Module will be removed from source tree.
# 		load				- Load the source tree module. [insert]
# 		unload			- Unload the module from kernel. [remove]
# 		info				- Show the information of loaded module.
# 		dmesg				- Prints the live kernel ring buffer.
#
# *signmod More info : https://github.com/cipherswami/signmod
##########################################################################

######## Select Module ########
MODULE ?= hello_world
###############################

# Makefile Variables
include .config
ARCH			?= x86_64
CROSS_COMPILE	?= x86_64-linux-gnu-
export

# Directories
SDIR := $(PWD)/modules
MDIR := $(SDIR)/$(MODULE)
HDIR := /lib/modules/$(shell uname -r)
KDIR := $(HDIR)/build
IDIR := $(HDIR)/updates

# Flags
FLAGS += EXTRA_CFLAGS:=-I$(PWD)/include

# Default target: build the kernel modules
all:
	$(MAKE) -C $(KDIR) M=$(SDIR) $(FLAGS) modules

# Build the module defined by "MODULE" variable
module:
	$(MAKE) -C $(KDIR) M=$(MDIR) $(FLAGS) modules

# Cleans the build artifacts
clean:
	$(MAKE) -C $(KDIR) M=$(SDIR) clean

# Sign the kernel module (requires signmod external tool)
sign:
	sudo signmod $(MDIR)/$(MODULE).ko

# List the top 5 loaded modules
lsmod:
	lsmod | head -n 6

# Insert the kernel module
insert: sign
	sudo insmod $(MDIR)/$(MODULE).ko

# Remove the kernel module
remove:
	sudo rmmod $(MODULE)

# Install the module to the kernel directory
install: sign
	sudo cp $(MDIR)/$(MODULE).ko $(IDIR) && sudo depmod -a

# Uninstall the module
uninstall:
	sudo rm -f $(IDIR)/$(MODULE).ko && sudo depmod -a

# Load the module using modprobe
load:
	sudo modprobe $(MODULE)

# Unload the module using modprobe
unload:
	sudo modprobe -r $(MODULE)

# Show module information
info:
	modinfo $(MDIR)/$(MODULE).ko

# Clear ans show the Ring buffer
dmesg:
	clear && sudo dmesg -C && sudo dmesg -wHT || true

.PHONY: all clean sign lsmod insert remove install uninstall load unload info dmesg
