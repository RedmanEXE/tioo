#ifndef TIOO_SYSCALL_MECHANICS_H_
#define TIOO_SYSCALL_MECHANICS_H_

#include <stdint.h>
#include <syscalls/syscalls.h>

// ======== DEFAULT SUBROUTINES ========
inline uint32_t Platform_SyscallInvoke(Kernel_SyscallNumber num, uint32_t arg0, uint32_t arg1,
                                            uint32_t arg2, uint32_t arg3);

// Platform-depended function for syscalls
inline uint32_t Platform_SyscallInvoke(Kernel_SyscallNumber num, uint32_t arg0, uint32_t arg1,
                                            uint32_t arg2, uint32_t arg3)
{
    register uint32_t r0  __asm__("r0")  = arg0;
    register uint32_t r1  __asm__("r1")  = arg1;
    register uint32_t r2  __asm__("r2")  = arg2;
    register uint32_t r3  __asm__("r3")  = arg3;
    register uint32_t r12 __asm__("r12") = (uint32_t)num;

    __asm__ volatile (
        "svc    #0"                                 // SuperVisor Call
        : "+r" (r0)
        : "r" (r1), "r" (r2), "r" (r3), "r" (r12)
        : "memory"
    );
    return r0;
}

#endif //TIOO_SYSCALL_MECHANICS_H_
