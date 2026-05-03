#include <syscalls/syscalls.h>
#include <syscall_routines.h>

// Kernel:
// - Read
// - Write

// Executable:
// - Load
// - Exit

// Service:
// - Register
// - Find
// - List
// - port python (in future)

// RPC:
// - CallService

// ======== DEFAULT SUBROUTINES ========
inline void *SysMemory_Allocate(uint32_t bytes_len);
inline void SysMemory_Free(void *block);

inline int32_t SysProgram_AddTask(void*(*func)(void*), void* arg);
inline int32_t SysProgram_Execute(void*(*func)(void*), void *arg);
inline int32_t SysProgram_GetID();
inline int32_t SysProgram_Terminate(uint16_t program_id);

inline int32_t SysTask_Free(uint16_t task_id);
inline int32_t SysTask_GetID();
inline int32_t SysTask_KickIntoSleep(int32_t sleep_time);
inline int32_t SysTask_Kick(uint16_t task_id);
inline int32_t SysTask_Launch(uint16_t task_id);

inline int32_t SysCablegram_Send(uint16_t receiver_id, Cablegram_Item *in);
inline int32_t SysCablegram_Receive(Cablegram_Item *out);
inline int32_t SysCablegram_WaitAndReceive(Cablegram_Item *out, int32_t timeout);

inline int32_t SysMutex_CreateObject();
inline int32_t SysSemaphore_CreateObject(uint8_t max_count);
inline int32_t SysSynchronizer_FreeObject(uint16_t syncer_id);
inline int32_t SysSynchronizer_GetResource(uint16_t syncer_id, int32_t timeout);
inline int32_t SysSynchronizer_ReturnResource(uint16_t syncer_id);

// later
inline void *SysMemory_Allocate(uint32_t bytes_len)
{
    return (void *)Platform_SyscallInvoke(SCN_MEMORY_ALLOCATE, bytes_len, 0, 0, 0);
}

// later
inline void SysMemory_Free(void *block)
{
    Platform_SyscallInvoke(SCN_MEMORY_FREE, (uint32_t)block, 0, 0, 0);
}

// later
inline int32_t SysProgram_AddTask(void*(*func)(void*), void* arg)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_ADD_TASK, (uint32_t)func, (uint32_t)arg, 0, 0);
}

// later
inline int32_t SysProgram_Execute(void*(*func)(void*), void *arg)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_EXECUTE, (uint32_t)func, (uint32_t)arg, 0, 0);
}

// later
inline int32_t SysProgram_GetID()
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_GET_ID, 0, 0, 0, 0);
}

// later
inline int32_t SysProgram_Terminate(uint16_t program_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_TERMINATE, (uint32_t)program_id, 0, 0, 0);
}

// later
inline int32_t SysTask_Free(uint16_t task_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_FREE, (uint32_t)task_id, 0, 0, 0);
}

// later
inline int32_t SysTask_GetID()
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_GET_ID, 0, 0, 0, 0);
}

// later
inline int32_t SysTask_KickIntoSleep(int32_t sleep_time)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_KICK_INTO_SLEEP, (uint32_t)sleep_time, 0, 0, 0);
}

// later
inline int32_t SysTask_Kill(uint16_t task_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_KILL, (uint32_t)task_id, 0, 0, 0);
}

// later
inline int32_t SysTask_Launch(uint16_t task_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_LAUNCH, (uint32_t)task_id, 0, 0, 0);
}

// later
inline int32_t SysCablegram_Send(uint16_t receiver_id, Cablegram_Item *in)
{
    return (int32_t)Platform_SyscallInvoke(SCN_IPC_CABLEGRAM_SEND, (uint32_t)receiver_id, (uint32_t)in, 0, 0);
}

// later
inline int32_t SysCablegram_Receive(Cablegram_Item *out)
{
    return (int32_t)Platform_SyscallInvoke(SCN_IPC_CABLEGRAM_RECEIVE, (uint32_t)out, 0, 0, 0);
}

// later
inline int32_t SysCablegram_WaitAndReceive(Cablegram_Item *out, int32_t timeout)
{
    return (int32_t) Platform_SyscallInvoke(SCN_IPC_CABLEGRAM_WAIT_AND_RECEIVE, (uint32_t)out, (uint32_t)timeout, 0, 0);
}

// later
inline int32_t SysMutex_CreateObject()
{
    return (int32_t)Platform_SyscallInvoke(SCN_SYNCER_MUTEX_CREATE, 0, 0, 0, 0);
}

// later
inline int32_t SysSemaphore_CreateObject(uint8_t max_count)
{
    return (int32_t)Platform_SyscallInvoke(SCN_SYNCER_SEMAPHORE_CREATE, max_count, 0, 0, 0);
}

// later
inline int32_t SysSynchronizer_FreeObject(uint16_t syncer_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_SYNCER_FREE_OBJECT, (uint32_t)syncer_id, 0, 0, 0);
}

// later
inline int32_t SysSynchronizer_GetResource(uint16_t syncer_id, int32_t timeout)
{
    return (int32_t)Platform_SyscallInvoke(SCN_SYNCER_GET_RESOURCE, (uint32_t)syncer_id, (uint32_t)timeout, 0, 0);
}

// later
inline int32_t SysSynchronizer_ReturnResource(uint16_t syncer_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_SYNCER_RETURN_RESOURCE, (uint32_t)syncer_id, 0, 0, 0);
}
