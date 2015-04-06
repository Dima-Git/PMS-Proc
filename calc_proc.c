#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

int opA = 0;
int opB = 0;
char act = '?';

static int calc_proc_result_show(struct seq_file *m, void *v) 
{
	seq_printf(m, "%d %c %d = ", opA, act, opB);
	switch (act) {
	case '+':
		seq_printf(m, "%d\n", opA + opB);
		break;
	case '-':
		seq_printf(m, "%d\n", opA - opB);
		break;
	case '*':
		seq_printf(m, "%d\n", opA * opB);
		break;
	case '/':
		if (opB == 0)
			seq_printf(m, "Division by zero.\n");
		else
			seq_printf(m, "%d\n", opA / opB);
		break;
	default:
		seq_printf(m, "Illegal operation.\n");
	}
	return 0;
}

static int calc_proc_result_open(struct inode *inode, struct  file *file) 
{
	return single_open(file, calc_proc_result_show, NULL);
}


static const struct file_operations calc_proc_result_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_result_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int calc_proc_opA_show(struct seq_file *m, void *v) 
{
	seq_printf(m, "%d\n", opA);
	return 0;
}

static int calc_proc_opA_open(struct inode *inode, struct  file *file) 
{
	return single_open(file, calc_proc_opA_show, NULL);
}

ssize_t writeA_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	sscanf(buf, "%d", &opA);
	return count;
}

static const struct file_operations calc_proc_opA_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_opA_open,
	.write = writeA_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int calc_proc_opB_show(struct seq_file *m, void *v) 
{
	seq_printf(m, "%d\n", opB);
	return 0;
}

static int calc_proc_opB_open(struct inode *inode, struct  file *file) 
{
	return single_open(file, calc_proc_opB_show, NULL);
}

ssize_t writeB_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	sscanf(buf, "%d", &opB);
	return count;
}

static const struct file_operations calc_proc_opB_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_opB_open,
	.write = writeB_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

ssize_t writeact_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	act = buf[0];
	return count;
}

static int calc_proc_act_show(struct seq_file *m, void *v) 
{
	seq_printf(m, "%c\n", act);
	return 0;
}

static int calc_proc_act_open(struct inode *inode, struct  file *file) 
{
	return single_open(file, calc_proc_act_show, NULL);
}

static const struct file_operations calc_proc_act_fops = {
	.owner = THIS_MODULE,
	.open = calc_proc_act_open,
	.write = writeact_proc,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};


static int __init calc_proc_init(void) 
{
	proc_create("calc_proc_result", 0, NULL, &calc_proc_result_fops);
	proc_create("calc_proc_opA", 0666, NULL, &calc_proc_opA_fops);
	proc_create("calc_proc_opB", 0666, NULL, &calc_proc_opB_fops);
	proc_create("calc_proc_act", 0666, NULL, &calc_proc_act_fops);
	return 0;
}

static void __exit calc_proc_exit(void) 
{
	remove_proc_entry("calc_proc_result", NULL);
	remove_proc_entry("calc_proc_opA", NULL);
	remove_proc_entry("calc_proc_opB", NULL);
	remove_proc_entry("calc_proc_act", NULL);
}

MODULE_LICENSE("GPL");
module_init(calc_proc_init);
module_exit(calc_proc_exit);