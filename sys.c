SYSCALL_DEFINE3(skua, uint64_t *, jaeger_trace_id, uint64_t *, jaeger_parent_id,
                size_t, count)
{
    uint64_t buf[2];
    buf[0]=0;
    buf[1]=0;

    // silently ignore if too short
    if (count < 2 * sizeof(uint64_t)) {
                return count;
        }

    /* copy src, which is in the user’s address space, into buf */
    if (copy_from_user(&buf[0],jaeger_trace_id,8))
        return -EFAULT;

    /* copy src, which is in the user’s address space, into buf */
    if (copy_from_user(&buf[1], jaeger_parent_id, 8))
        return -EFAULT;

    //putting trace context into task_struct (PCB, current) of the thread
    current->jaeger_trace_id = buf[0];
    current->jaeger_parent_id = buf[1];

    current->jaeger_span_id = 0;

      printk("skua-syscall: jaeger_trace_id %llu; jaeger_parent_id %llu\n", buf[0], buf[1]);


    /* return amount of data copied */
    return count;
}
