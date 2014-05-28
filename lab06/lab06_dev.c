#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timer;

static long timeout = 2000;

void time_handler(unsigned long data)
{
	int ret;
	
	printk(KERN_INFO "Lab06 time handler, timeout=%ld \n", timeout);
	ret = mod_timer(&timer, jiffies + msecs_to_jiffies(timeout));
	if (ret) {
		printk(KERN_ERR "Fail to mod timer\n");
	}
}

static ssize_t write_handler(struct file *filp, const char *buff,
		size_t count, loff_t *offp)
{
	long t = -1l;
	kstrtol(buff, 10, &t);
	if (t == -1l) {
		printk(KERN_INFO "Wrong argument.\n");
		return count;
	}
	timeout = t;
	return count;
}


