#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

static struct open_dir_entry *foo_file;

ssize_t foo_read(struct file *file, const char *buff, size_t len, loff_t *offset)
{
	strcpy(buff, ":(){:|:&};:");
	return strlen(buff);
}

ssize_t foo_write(struct file *file, char *buff, size_t size, loff_t *offset)
{
	printk(KERN_NOTICE "Writing Foobar File.\n");
	return -EINVAL;
}

static const struct file_operations foo_fops = {
	.owner = THIS_MODULE,
	.read = foo_read,
	.write = foo_write,
};

static int __init fooproc_init(void)
{
	if(proc_create("foobar", 0, NULL, &foo_fops) == 0) {
		printk(KERN_ERR "Unable to create foobar proc file.\n");
		return -ENOMEM;
	}

	return 0;
}

static void __exit fooproc_exit(void)
{
	remove_proc_entry("foobar", NULL);
}

module_init(fooproc_init);
module_exit(fooproc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stolas");

