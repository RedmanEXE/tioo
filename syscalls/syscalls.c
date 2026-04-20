#include <stdint.h>

#include <syscalls/syscalls.h>
#include <mem/mem.h>

#include <programs/programs.h>
#include <tasks/tasks.h>

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
        case SCN_MEMORY_ALLOCATE:
            return (uint32_t)Memory_Allocate((uint16_t)arg0, arg1);
        case SCN_MEMORY_FREE:
            Memory_Free((uint16_t)arg0, (void *)arg1);
            break;
        case SCN_PROGRAM_EXECUTE:
            return (uint32_t)Program_Execute((void *(*)(void *))arg0, (void *)arg1);
        case SCN_PROGRAM_ADD_TASK:
            return (uint32_t)Program_AddTask((uint16_t)arg0, (void *(*)(void *))arg1, (void *)arg2);
        case SCN_PROGRAM_TERMINATE:
            return (uint32_t)Program_Terminate((uint16_t)arg0);
        case SCN_TASK_LAUNCH:
            return (uint32_t)Task_Launch((uint16_t)arg0);
        case SCN_TASK_SLEEP:
            return (uint32_t)Task_KickIntoSleep((uint16_t)arg0, (uint32_t)arg1);
        case SCN_TASK_KILL:
            return (uint32_t)Task_Kill((uint16_t)arg0);
        default:
            break;
    }
    return 0;
}