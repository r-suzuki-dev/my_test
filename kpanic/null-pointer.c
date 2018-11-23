#include <linux/module.h>
#include <linux/kernel.h>

char *p=NULL;

int init_module(void)
{
    printk(KERN_INFO "call the init_module\n");

    *p = 1;
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "call the cleannup_module\n");
}
