#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
MODULE_LICENSE("Dual BSD/GPL");

#define HELLO_NO_OF_DEVICES          1
#define HELLO_FIRST_MINOR_DEVICE_NO  0



struct file_operations scull_fops = {
.owner =
 THIS_MODULE,
.llseek =
 scull_llseek,
.read =
 scull_read,
.write =
 scull_write,
.ioctl =
 scull_ioctl,
.open =
 scull_open,
.release = scull_release,
};


static void __exit hello_exit(void);
dev_t dev_name;

static int __init hello_init(void)
{
	int status = -1;
	printk(KERN_ALERT "HELLO : Hello, world\n");
	
		
	status = alloc_chrdev_region(&dev_name,HELLO_FIRST_MINOR_DEVICE_NO,HELLO_NO_OF_DEVICES,"heloModule");
	if(status != 0)
	{
		printk(KERN_ALERT "HELLO : Unable to register driver\n");
		goto driver_no_not_allocated;
	}	
	
	return 0;

driver_no_not_allocated:
	hello_exit();
	return status;
}

static void __exit hello_exit(void)
{
	unregister_chrdev_region(dev_name,HELLO_NO_OF_DEVICES);
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
