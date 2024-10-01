/**
 * @file helloWorld.c
 * @author Aravind Potluri
 * @date 5 Sept 2024
 * @brief An introductory "Hello World!" loadable kernel module.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

// Function Declarations
static void print_hello_dev(const char *dev_name);

// Module Initialization Function
static int __init hello_init(void)
{
    printk(KERN_INFO "%s: Module loaded\n", THIS_MODULE->name);
    print_hello_dev("Kernel logger");
    return 0;
}

// Module Exit Function
static void __exit hello_exit(void)
{
    printk(KERN_INFO "%s: Module exited\n", THIS_MODULE->name);
}

// Function to Print Device Information
static void print_hello_dev(const char *dev_name)
{
    printk(KERN_INFO "%s: Hello kernel from the device %s\n", THIS_MODULE->name, dev_name);
}

// Register Module Entry and Exit Points
module_init(hello_init);
module_exit(hello_exit);

// Module Information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_VERSION("1.0.0");
