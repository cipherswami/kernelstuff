#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kfuncs.h>

// Module params
static int num = 10;
module_param(num, int, S_IRUGO);

// External module funcs
extern void logk(const char *msg);

// Init
static int __init mod_init(void)
{
    printk(KERN_INFO "%s: Module loaded\n", THIS_MODULE->name);
    if (num % 2 == 0)
    {
        logk("num is even.");
    }
    else
    {
        logk("num is odd.");
    }
    return 0;
}

// Exit
static void __exit mod_exit(void)
{
    printk(KERN_INFO "%s: Module exited\n", THIS_MODULE->name);
}

module_init(mod_init);
module_exit(mod_exit);

// Module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri <aravindswami135@gmail.com>");
MODULE_DESCRIPTION("Module to demonstrate module_param().");
MODULE_VERSION("1.0.0");
