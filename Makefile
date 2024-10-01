###################### Linux Kernel Module Makefile #######################
## Author		: 	Aravind Potluri <aravindswami135@gmail.com>
## Arguments	: 	
#					all 		- Builds the kernel module. 
#					clean 		- Clean up the build artifacts.
#					sign* 		- Signs the module. [Secure Boot Devices]
#					insert 		- Inserts the module for testing.
#					remove 		- Removes the inserted module. 
#					install 	- Module will be placed in source tree.
#					uninstall	- Module will be remvoed from source tree.
#					load 		- Load the source tree module. [insert]
#					unload 		- Unload the modle from kernel. [remove] 
#
# * Signing the modlue is required for Secure boot enabled devices and
#	signing key to be installed in the MOK. Please refer the regMOK for 
#	more info: https://github.com/cipherswami/regMOK	
##i#########################################################################

### Define your Module Name ###
MODULE_NAME := myModule
###############################

# Define the module objects
obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-objs := main.o # Add other object files if needed

# Set the target architecture (default is x86_64)
ARCH ?= x86_64

# Define the cross-compiler toolchain 
CROSS_COMPILE ?=

# Define the path to the current kernel build directory (kernel headers)
KDIR := /lib/modules/$(shell uname -r)/build

# Define the installation path for the module
INSTALL_PATH := /lib/modules/$(shell uname -r)/kernel/drivers/devmods/

# Build the kernel module
all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

# Clean up build artifacts
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

# Sign the module (External Script NEEDED: https://github.com/cipherswami/regMOK)
sign:
	sudo signmod $(MODULE_NAME).ko

# Testing: Insert
insert:
	sudo insmod $(MODULE_NAME).ko

# Testing: Remove
remove:
	sudo rmmod $(MODULE_NAME)

# Install the module
install:
	sudo mkdir -p $(INSTALL_PATH)
	sudo cp $(MODULE_NAME).ko $(INSTALL_PATH)
	sudo depmod -a

# Uninstall the module
uninstall:
	sudo rm -f $(INSTALL_PATH)$(MODULE_NAME).ko
	sudo depmod -a

# Load the module
load:
	sudo modprobe $(MODULE_NAME)

# Unload the module
unload:
	sudo modprobe -r $(MODULE_NAME)

.PHONY: all clean sign install uninstall load unload
