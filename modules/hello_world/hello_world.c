#include <linux/module.h> // For MODULE_LICENSE()
#include <linux/kernel.h> // For printk()
#include <linux/init.h>   // For module_init(), module_exit()

// Module init function
static int __init hello_world_init(void)
{
    printk(KERN_INFO "%s: Module loaded\n", THIS_MODULE->name);
    printk(KERN_INFO "%s: Hello there from kernel.\n", THIS_MODULE->name);
    return 0;
}

// Module exit function
static void __exit hello_wolrd_exit(void)
{
    printk(KERN_INFO "%s: Module exited\n", THIS_MODULE->name);
}

// Register module entry and exit points
module_init(hello_world_init);
module_exit(hello_wolrd_exit);

// Module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_VERSION("1.0.0");
