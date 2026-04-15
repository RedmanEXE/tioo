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
    register uint32_t a0  __asm__("a0")  = arg0;
    register uint32_t a1  __asm__("a1")  = arg1;
    register uint32_t a2  __asm__("a2")  = arg2;
    register uint32_t a3  __asm__("a3")  = arg3;
    register uint32_t a7  __asm__("a7")  = (uint32_t)num;

    __asm__ volatile (
        "ecall"                                   // Environment Call
        : "+r" (a0)
        : "r" (a1), "r" (a2), "r" (a3), "r" (a7)
        : "memory"
    );
    return a0;
}

#endif //TIOO_SYSCALL_MECHANICS_H_
