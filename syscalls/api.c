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

inline uint32_t Kernel_Read(uint32_t descriptor, char *buffer)
{
    return Platform_SyscallInvoke(SCN_KERNEL_READ, descriptor, (uint32_t)buffer, 0, 0);
}

inline uint32_t Kernel_Write(uint32_t descriptor, const char *buffer)
{
    return Platform_SyscallInvoke(SCN_KERNEL_WRITE, descriptor, (uint32_t)buffer, 0, 0);
}

inline uint32_t Service_Register()
{
    return Platform_SyscallInvoke(SCN_SERVICE_REGISTER, 0, 0, 0, 0);
}

inline void *SysMemory_Allocate(uint16_t owner_id, uint32_t size)
{
    return (void *)Platform_SyscallInvoke(SCN_MEMORY_ALLOCATE, owner_id, size, 0, 0);
}
