#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#define BUF_SIZE 1024
static char dataBuffer[BUF_SIZE];
static int dataBuffer_len = 0;

struct proc_dir_entry *module_proc_node;

static ssize_t procMod_read(struct file *filePtr, char __user *userBuffer, size_t count, loff_t *offset)
{
    if (*offset > 0 || count < dataBuffer_len)
    {
        return 0;
    }

    if (copy_to_user(userBuffer, dataBuffer, dataBuffer_len))
    {
        return -EFAULT;
    }

    *offset = dataBuffer_len;

    printk(KERN_INFO "%s: Data read from proc\n", THIS_MODULE->name);
    return dataBuffer_len;
}

static ssize_t procMod_write(struct file *filePtr, const char __user *userBuffer, size_t count, loff_t *offset)
{
    if (count > BUF_SIZE - 1)
    {
        return -EINVAL;
    }

    memset(dataBuffer, 0, BUF_SIZE);

    if (copy_from_user(dataBuffer, userBuffer, count))
    {
        return -EFAULT;
    }

    dataBuffer_len = count;
    dataBuffer[dataBuffer_len] = '\0';

    printk(KERN_INFO "%s: Data wrrittrn to proc\n", THIS_MODULE->name);
    return count;
}

struct proc_ops module_proc_ops = {
    .proc_read = procMod_read,
    .proc_write = procMod_write,
};

static int __init mod_init(void)
{
    module_proc_node = proc_create("procMod_driver", 0755, NULL, &module_proc_ops);
    printk(KERN_INFO "%s: %s\n", THIS_MODULE->name, __func__);
    return 0;
}

static void __exit mod_exit(void)
{
    proc_remove(module_proc_node);
    printk(KERN_INFO "%s: %s\n", THIS_MODULE->name, __func__);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aravind Potluri <aravindswami135@gmail.com>");
MODULE_DESCRIPTION("Module to demonstrate userspace access via proc.");
MODULE_VERSION("1.0.0");
