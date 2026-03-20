#include <syscalls/syscalls.h>
#include <mem/mem.h>

// Thorfinn says:
// main file huli tut pisat'
int Kernel_EntryPoint(void)
{
    Memory_Initialize();

    void *point = SysMemory_Allocate(1, 1000);
    point = SysMemory_Allocate(1, 1000);
    (void)point;

    while (1) {}

    return 0;
}
