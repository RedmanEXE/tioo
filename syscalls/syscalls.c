#include <stdint.h>

#include <syscalls/syscalls.h>
#include <mem/mem.h>

// ======== DEFAULT SUBROUTINES ========
uint32_t Kernel_Syscalls(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3,
                         uint32_t func_idx);

uint32_t Kernel_Syscalls(
    uint32_t arg0,
    uint32_t arg1,
    uint32_t arg2,
    uint32_t arg3,
    uint32_t func_idx)
{
    ((void)func_idx), ((void)arg0), ((void)arg1), ((void)arg2), ((void)arg3);
    if (SCN_CALLS_LENGTH <= func_idx)
        return 0;

    switch (func_idx)
    {
        case SCN_SERVICE_REGISTER:
            return 20;
        case SCN_MEMORY_ALLOCATE:
            return (uint32_t)Memory_Allocate((uint16_t)arg0, arg1);
        case SCN_MEMORY_FREE:
            Memory_Free((uint16_t)arg0, (void *)arg1);
            break;
        default:
            break;
    }
    return 0;
}