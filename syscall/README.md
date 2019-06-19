## H2 steps of adding new syscall

Step 1: system call was added in ~/skua-linux-lttng/kernel/sys.c

Step 2: add new system call number at the end of this file (system call table): ~/skua-linux-lttng/arch/x86/entry/syscalls/syscall_64.tbl

Step 3: add this line to /home/ubuntu/skua-linux-lttng/include/linux/syscalls.h : asmlinkage long sys_skua(uint64_t  jaeger_trace_id, uint64_t jaeger_parent_id);

Step 4: building kernel

After those steps, system call's related things should be already in following files:

~/skua-linux-lttng/arch/x86/include/generated/asm/syscalls_64.h:__SYSCALL_64(333, sys_skua, )

~/skua-linux-lttng/arch/x86/include/generated/uapi/asm/unistd_x32.h:#define __NR_skua (__X32_SYSCALL_BIT + 333)


~/skua-linux-lttng/rch/x86/include/generated/uapi/asm/unistd_64.h:#define __NR_skua 333



## H2 for user level part (using this skua syscall):

in skua-jaeger-client-cpp/src/jaegertracing/Tracer.cpp, insert_trace function has changed to call this new system call: syscall(333, jaeger_trace_id, jaeger_parent_id);
(necessary headers should be added). modified file is uploaded as Tracer.cpp
