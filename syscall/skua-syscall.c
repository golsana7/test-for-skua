



//this should be added to (sys.c file of kernel)  ~/skua-linux-lttng/kernel/sys.c


SYSCALL_DEFINE2(skua, uint64_t, jaeger_trace_id, uint64_t, jaeger_parent_id)
{

    current->jaeger_trace_id = jaeger_trace_id;
   // printk("Called 2  skua_sys with jaeger_trace_id: %llu\n",jaeger_trace_id);
   
   current->jaeger_parent_id = jaeger_parent_id;
   // printk("Called 3 skua_sys with current->jaeger_parent_id: %llu\n",current->jaeger_parent_id);
   
   current->jaeger_span_id = 0;

   
   printk("skua-syscall: jaeger_trace_id %llu; jaeger_parent_id %llu\n", current->jaeger_trace_id, current->jaeger_parent_id);

    return 0;

}
