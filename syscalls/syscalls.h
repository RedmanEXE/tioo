#ifndef TIOO_SYSCALLS_H_
#define TIOO_SYSCALLS_H_

#include <stdint.h>

typedef enum
{
    SCN_KERNEL_READ             = 0,
    SCN_KERNEL_WRITE            = 1,

    SCN_MEMORY_ALLOCATE         = 2,
    SCN_MEMORY_FREE             = 3,

    SCN_PROGRAM_EXECUTE         = 4,
    SCN_PROGRAM_ADD_TASK        = 5,
    SCN_PROGRAM_TERMINATE       = 6,

    SCN_TASK_LAUNCH             = 7,
    SCN_TASK_SLEEP              = 8,
    SCN_TASK_KILL               = 9,

    SCN_CALLS_LENGTH,
} Kernel_SyscallNumber;

uint32_t Kernel_Read();
uint32_t Kernel_Write();

void *SysMemory_Allocate(uint16_t owner_id, uint32_t size);
void SysMemory_Free(uint16_t owner_id, void *ptr);

int32_t SysProgram_AddTask(uint16_t program_id, void*(*func)(void*), void* arg);
int32_t SysProgram_Execute(void*(*func)(void*), void* arg);
int32_t SysProgram_Terminate(uint16_t id);

int32_t SysTask_Create(uint16_t program_id, void *(*func)(void *), void *arg);
int32_t SysTask_Launch(uint16_t task_id);
int32_t SysTask_KickIntoSleep(uint16_t task_id, int32_t sleep_time);

uint32_t Service_Register();

#endif //TIOO_SYSCALLS_H_
