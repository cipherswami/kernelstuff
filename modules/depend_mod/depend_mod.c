#include <linux/module.h>
#include <linux/kernel.h> // Symbols already exported (c source not required)
#include <linux/init.h>
#include <linux/kfuncs.h> // Symbols not yet exported (c source required)

// Init
static int __init depend_mod_init(void)
{
    printk(KERN_INFO "%s: Module loaded\n", THIS_MODULE->name);
    logk("kfuncs function from depend_mod.");

    return 0;
}

// Exit
static void __exit depend_mod_exit(void)
{
    printk(KERN_INFO "%s: Module exited\n", THIS_MODULE->name);
}

module_init(depend_mod_init);
module_exit(depend_mod_exit);

// Module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri <aravindswami135@gmail.com>");
MODULE_DESCRIPTION("Dependent module demonstration.");
MODULE_VERSION("1.0.0");
MODULE_SOFTDEP("pre: kfuncs");
