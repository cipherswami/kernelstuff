#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kfuncs.h>

// Init
static int __init inherit_mod_init(void)
{
    printk(KERN_INFO "%s: Module loaded\n", THIS_MODULE->name);
    logk("kfuncs function from inherit_mod.");

    return 0;
}

// Exit
static void __exit inherit_mod_exit(void)
{
    printk(KERN_INFO "%s: Module exited\n", THIS_MODULE->name);
}

module_init(inherit_mod_init);
module_exit(inherit_mod_exit);

// Module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri <aravindswami135@gmail.com>");
MODULE_DESCRIPTION("Module to demonstrate module_param().");
MODULE_VERSION("1.0.0");
