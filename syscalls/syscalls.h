#ifndef TIOO_SYSCALLS_H_
#define TIOO_SYSCALLS_H_

#include <stdint.h>

#include <ipc/ipc.h>

typedef enum
{
    SCN_MEMORY_ALLOCATE                 = 0x00,
    SCN_MEMORY_FREE                     = 0x01,

    SCN_PROGRAM_ADD_TASK                = 0x02,
    SCN_PROGRAM_EXECUTE                 = 0x03,
    SCN_PROGRAM_GET_ID                  = 0x04,
    SCN_PROGRAM_TERMINATE               = 0x05,

    SCN_TASK_FREE                       = 0x06,
    SCN_TASK_GET_ID                     = 0x07,
    SCN_TASK_KICK_INTO_SLEEP            = 0x08,
    SCN_TASK_KILL                       = 0x09,
    SCN_TASK_LAUNCH                     = 0x0A,

    SCN_IPC_CABLEGRAM_SEND              = 0x0B,
    SCN_IPC_CABLEGRAM_RECEIVE           = 0x0C,
    SCN_IPC_CABLEGRAM_WAIT_AND_RECEIVE  = 0x0D,

    SCN_SYNCER_MUTEX_CREATE             = 0x0E,
    SCN_SYNCER_SEMAPHORE_CREATE         = 0x0F,
    SCN_SYNCER_FREE_OBJECT              = 0x10,
    SCN_SYNCER_GET_RESOURCE             = 0x11,
    SCN_SYNCER_RETURN_RESOURCE          = 0x12,

    SCN_CALLS_LENGTH,
} Kernel_SyscallNumber;

void *SysMemory_Allocate(uint32_t bytes_len);
void SysMemory_Free(void *block);

int32_t SysProgram_AddTask(void*(*func)(void*), void* arg);
int32_t SysProgram_Execute(void*(*func)(void*), void *arg);
int32_t SysProgram_GetID();
int32_t SysProgram_Terminate(uint16_t program_id);

int32_t SysTask_Free(uint16_t task_id);
int32_t SysTask_GetID();
int32_t SysTask_KickIntoSleep(int32_t sleep_time);
int32_t SysTask_Kick(uint16_t task_id);
int32_t SysTask_Launch(uint16_t task_id);

int32_t SysCablegram_Send(uint16_t receiver_id, Cablegram_Item *in);
int32_t SysCablegram_Receive(Cablegram_Item *out);
int32_t SysCablegram_WaitAndReceive(Cablegram_Item *out, int32_t timeout);

int32_t SysMutex_CreateObject();
int32_t SysSemaphore_CreateObject(uint8_t max_count);
int32_t SysSynchronizer_FreeObject(uint16_t syncer_id);
int32_t SysSynchronizer_GetResource(uint16_t syncer_id, int32_t timeout);
int32_t SysSynchronizer_ReturnResource(uint16_t syncer_id);

#endif //TIOO_SYSCALLS_H_
