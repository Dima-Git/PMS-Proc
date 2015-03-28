#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

int opA = 0;
int opB = 0;
char act = '?';

static int calc_proc_show(struct seq_file *m, void *v) {
	seq_printf(m, "%d %c %d\n", opA, act, opB);
	return 0;
}

static int calc_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, calc_proc_show, NULL);
}


static const struct file_operations calc_proc_result_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int writeA_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	int i = 0;
	for (i = 0; i < count - 1; ++ i)
		opA = opA * 10 + (buf[i]-'0');
	return count;
}

static const struct file_operations calc_proc_opA_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_open,
	.write = writeA_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int writeB_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	int i = 0;
	for (i = 0; i < count - 1; ++ i)
		opB = opB * 10 + (buf[i]-'0');
	return count;
}

static const struct file_operations calc_proc_opB_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_open,
	.write = writeB_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

int writeact_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	act = buf[0];
	return count;
}

static const struct file_operations calc_proc_act_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_open,
	.write = writeact_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};


static int __init calc_proc_init(void) {
	proc_create("calc_proc_result", 0, NULL, &calc_proc_result_fops);
	proc_create("calc_proc_opA", 0666, NULL, &calc_proc_opA_fops);
	proc_create("calc_proc_opB", 0666, NULL, &calc_proc_opB_fops);
	proc_create("calc_proc_act", 0666, NULL, &calc_proc_act_fops);
	return 0;
}

static void __exit calc_proc_exit(void) {
	remove_proc_entry("calc_proc_result", NULL);
	remove_proc_entry("calc_proc_opA", NULL);
	remove_proc_entry("calc_proc_opB", NULL);
	remove_proc_entry("calc_proc_act", NULL);
}

MODULE_LICENSE("GPL");
module_init(calc_proc_init);
module_exit(calc_proc_exit);