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
inline uint32_t Kernel_Read(uint32_t descriptor, char *buffer);
inline uint32_t Kernel_Write(uint32_t descriptor, const char *buffer);
inline uint32_t Service_Register();
inline void *SysMemory_Allocate(uint16_t owner_id, uint32_t size);
inline int32_t SysTask_Create(uint16_t program_id, void *(*func)(void *), void *arg);
inline int32_t SysTask_Launch(uint16_t task_id);

// later
inline uint32_t Kernel_Read(uint32_t descriptor, char *buffer)
{
    return Platform_SyscallInvoke(SCN_KERNEL_READ, descriptor, (uint32_t)buffer, 0, 0);
}

// later
inline uint32_t Kernel_Write(uint32_t descriptor, const char *buffer)
{
    return Platform_SyscallInvoke(SCN_KERNEL_WRITE, descriptor, (uint32_t)buffer, 0, 0);
}

// later
inline void *SysMemory_Allocate(uint16_t owner_id, uint32_t size)
{
    return (void *)Platform_SyscallInvoke(SCN_MEMORY_ALLOCATE, owner_id, size, 0, 0);
}

// later
inline void SysMemory_Free(uint16_t owner_id, void *ptr)
{
    Platform_SyscallInvoke(SCN_MEMORY_FREE, owner_id, (uint32_t)ptr, 0, 0);
}

// later
inline int32_t SysProgram_AddTask(uint16_t program_id, void*(*func)(void*), void* arg)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_ADD_TASK, (uint32_t)program_id, (uint32_t)func, (uint32_t)arg, 0);
}

// later
inline int32_t SysProgram_Execute(void*(*func)(void*), void *arg)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_EXECUTE, (uint32_t)func, (uint32_t)arg, 0, 0);
}

// later
inline int32_t SysProgram_Terminate(uint16_t program_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_PROGRAM_TERMINATE, (uint32_t)program_id, 0, 0, 0);
}

// later
inline int32_t SysTask_Launch(uint16_t task_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_LAUNCH, (uint32_t)task_id, 0, 0, 0);
}

// later
inline int32_t SysTask_KickIntoSleep(uint16_t task_id, int32_t sleep_time)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_SLEEP, (uint32_t)task_id, (uint32_t)sleep_time, 0, 0);
}

// later
inline int32_t SysTask_Kill(uint16_t task_id)
{
    return (int32_t)Platform_SyscallInvoke(SCN_TASK_KILL, (uint32_t)task_id, 0, 0, 0);
}

inline void SysGPIO_LEDXOR(void)
{
    Platform_SyscallInvoke(SCN_KERNEL_READ, 0, 0, 0, 0);
}

int32_t SysCablegram_Send(uint16_t program_id, Cablegram_Item *cablegram)
{
    return (int32_t)Platform_SyscallInvoke(SCN_IPC_CABLEGRAM_SEND, (uint32_t)program_id, (uint32_t)cablegram, 0, 0);
}

int32_t SysCablegram_Receive(uint16_t program_id, Cablegram_Item *out)
{
    return (int32_t)Platform_SyscallInvoke(SCN_IPC_CABLEGRAM_RECEIVE, (uint32_t)program_id, (uint32_t)out, 0, 0);
}
