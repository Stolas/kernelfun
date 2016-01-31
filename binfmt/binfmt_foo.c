#include <linux/module.h>
#include <linux/string.h>
#include <linux/stat.h>
#include <linux/binfmts.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/err.h>
#include <linux/fs.h>

static int load_foobin(struct linux_binprm *bprm)
{
	if ((bprm->buf[0] != 'f') ||  (bprm->buf[1] != 'o') || (bprm->buf[2] != 'o'))
		return -ENOEXEC;

	printk(KERN_DEBUG "Foobar in the kernel!");

	return -EFAULT;
}

static struct linux_binfmt foo_format = {
	.module		= THIS_MODULE,
	.load_binary	= load_foobin,
};

static int __init init_foo_binfmt(void)
{
	register_binfmt(&foo_format);
	return 0;
}

static void __exit exit_foo_binfmt(void)
{
	unregister_binfmt(&foo_format);
}

core_initcall(init_foo_binfmt);
module_exit(exit_foo_binfmt);
MODULE_LICENSE("GPL");
