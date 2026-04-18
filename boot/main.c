#include <stddef.h>

#include <syscalls/syscalls.h>
#include <mem/mem.h>

#include "programs/programs.h"

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void *task_rountine(void *arg)
{
    (void)arg;

    while (1) {}

    return NULL;
}

// Thorfinn says:
// main file huli tut pisat'
int Kernel_EntryPoint(void)
{
    uint32_t *src, *dest;

    // Copy initialized data
    src = &_sidata;
    dest = &_sdata;
    while (dest < &_edata)
        *dest++ = *src++;

    // Fill with zeros non-initialized data
    dest = &_sbss;
    while (dest < &_ebss)
        *dest++ = 0;

    Memory_Initialize();

    // Test field
    void *point = SysMemory_Allocate(2, 1000);
    void *point2 = SysMemory_Allocate(2, 1000);
    SysMemory_Free(2, point);
    (void)point2;
    // END: Test field

    uint16_t task1_id = SysTask_Create(PROGRAMS_ID_KERNEL, task_rountine, NULL);
    SysTask_Launch(task1_id);

    while (1) {}

    return 0;
}
