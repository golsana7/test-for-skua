#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/slab.h>

ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
        uint64_t jaeger_trace_id;
        uint64_t jaeger_parent_id;

        // silently ignore if too short
        if (count < 2 * sizeof(uint64_t)) {
                return count;
        }



       if(copy_from_user(&jaeger_trace_id,&buf[0],8))
                    return -EFAULT;

       if(copy_from_user(&jaeger_parent_id,&buf[1],8))
                    return -EFAULT;



        current->jaeger_trace_id = jaeger_trace_id;
        current->jaeger_parent_id = jaeger_parent_id;

        current->jaeger_span_id = 0;
        
        printk("copy-from-user");
        printk("jaeger_ctx: jaeger_trace_id %llu; jaeger_parent_id %llu\n", jaeger_trace_id, jaeger_parent_id);
        //printk("%.*s\n", (int)count, buf);

        // silently ignore extra characters
        return count;
}

struct file_operations proc_fops = {
    write: write_proc
};

int proc_init (void) {
  // TODO: should check the output of this too
  proc_create("lttng_jaeger", S_IRUGO|S_IWUGO, NULL, &proc_fops);

  return 0;
}

void proc_cleanup(void) {
    remove_proc_entry("lttng_jaeger",NULL);
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);
