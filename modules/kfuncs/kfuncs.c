#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kfuncs.h>

/**
 * logk - Logs a message to the kernel log
 * @msg: Pointer to the message to be logged
 *
 * This function logs the given message to the kernel log
 * with the name of the calling module as a prefix. If the
 * message pointer is NULL, it logs a warning instead.
 */
void logk(const char *msg)
{
    if (!msg)
    {
        printk(KERN_WARNING "%s: Received a NULL message\n", THIS_MODULE->name);
        return;
    }

    printk(KERN_INFO "%s: %s\n", THIS_MODULE->name, msg);
}
EXPORT_SYMBOL(logk);

// No init and exit funcs as, module can be loaded without them. And,
// when this code is sourced by other modules we will run into problem
// for have multiple inits and exits funcs.
// TL;DR - Avoid init and exit funcs for helper modules.

// Module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri <aravindswami135@gmail.com>");
MODULE_DESCRIPTION("Module to provide basic kernel functions.");
MODULE_VERSION("1.0.0");