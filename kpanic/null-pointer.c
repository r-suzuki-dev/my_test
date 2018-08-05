/*
 *  null-pointer.c - A not so simple kernel module to crash kernel.
 */

#include <linux/module.h>    /* Needed by all modules */
#include <linux/kernel.h>    /* Needed for KERN_INFO */

char *p=NULL;

int init_module(void)
{
    printk(KERN_INFO "We is gonna KABOOM now!\n");

    *p = 1;
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye world.\n");
}
