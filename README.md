first round of adding system call to kernel:

-system call was added in ~/skua-linux-lttng/kernel/sys.c 

-add new system call number at the end of this file (I think this is system call table):
 ~/skua-linux-lttng/arch/x86/entry/syscalls/syscall_64.tbl

-add this line to /home/ubuntu/skua-linux-lttng/include/linux/syscalls.h : asmlinkage long sys_skua(uint64_t *jaeger_trace_id, uint64_t *jaeger_parent_id, size_t count);

-[I removed this before building kernel](I don't know based on previous step this step is correct or not, bc in some sites I read it is said to do this step and in some it is not), add "define part in this file:
~/skua-linux-lttng/arch/x86/include/generated/uapi/asm/unistd_64.h" I added this:  #define __NR_skua 333


