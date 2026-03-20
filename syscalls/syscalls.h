#ifndef TIOO_SYSCALLS_H_
#define TIOO_SYSCALLS_H_

#include <stdint.h>

typedef enum
{
    SCN_KERNEL_READ             = 0,
    SCN_KERNEL_WRITE            = 1,

    SCN_EXECUTABLE_EXEC         = 2,
    SCN_EXECUTABLE_EXIT         = 3,

    SCN_SERVICE_REGISTER        = 4,
    SCN_SERVICE_UNREGISTER      = 5,
    SCN_SERVICE_GET_SID         = 6,
    SCN_SERVICE_LIST            = 7,

    SCN_SERVICE_CALL_SERVICE    = 8,

    SCN_MEMORY_ALLOCATE         = 9,
    SCN_MEMORY_FREE             = 10,

    SCN_CALLS_LENGTH,
} Kernel_SyscallNumber;

uint32_t Kernel_Read();
uint32_t Kernel_Write();

uint32_t Service_Register();

#endif //TIOO_SYSCALLS_H_
