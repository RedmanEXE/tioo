#include <syscalls/syscalls.h>
#include <mem/mem.h>

// Thorfinn says:
// main file huli tut pisat'
int Kernel_EntryPoint(void)
{
    Memory_Initialize();

    void *point = SysMemory_Allocate(2, 1000);
    void *point2 = SysMemory_Allocate(2, 1000);
    SysMemory_Free(2, point);
    (void)point2;

    while (1) {}

    return 0;
}
