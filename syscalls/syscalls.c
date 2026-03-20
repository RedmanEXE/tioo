#include <stdint.h>

#include <syscalls/syscalls.h>
#include <mem/mem.h>

void Kernel_Syscalls(uint32_t *saved_args)
{
    Kernel_SyscallNumber syscall_number = saved_args[4];
    if (SCN_CALLS_LENGTH <= syscall_number)
        return;

    switch (syscall_number)
    {
        case SCN_SERVICE_REGISTER:
            saved_args[0] = 20;
            break;
        case SCN_MEMORY_ALLOCATE:
            saved_args[0] = (uint32_t)Memory_Allocate((uint16_t)saved_args[0], saved_args[1]);
            break;
        default:
            break;
    }
}