#include <stddef.h>

#include <peripherals/systimer/systimer.h>
#include <syscalls/syscalls.h>
#include <mem/mem.h>
#include <programs/programs.h>

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern void Platform_ScheduleTaskSwitch();

void *task1_routine(void *arg)
{
    (void)arg;
    Cablegram_Item cablegram;
    cablegram.type = 1;
    cablegram.data = 1;

    while (1)
    {
        SysCablegram_Send(2, &cablegram);
        SysTask_KickIntoSleep(1, 1000);
    }

    return NULL;
}

void *task2_routine(void *arg)
{
    (void)arg;
    Cablegram_Item cablegram;

    while (1)
    {
        int32_t answer = SysCablegram_WaitAndReceive(2, 3, &cablegram, 3000);
        if (answer == 1)
            SysTask_KickIntoSleep(3, 500);
    }

    return NULL;
}

void *task3_routine(void *arg)
{
    (void)arg;
    while (1) {}
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
    TasksManager_Initialize();
    Program_Initialize();
    Synchronizers_Initialize();

    // Test field
    void *point = SysMemory_Allocate(2, 1000);
    void *point2 = SysMemory_Allocate(2, 1000);
    SysMemory_Free(2, point);
    (void)point2;

    // uint32_t *ahb1 = (uint32_t *)0x40021018;
    // *ahb1 |= 4;
    // uint32_t *cmoder = (uint32_t *)0x40010800;
    // *cmoder &= ~(0xFU << 20);
    // *cmoder |= 0x3U << 20;

    SysProgram_Execute(task1_routine, (void *)1);
    uint16_t program_id = SysProgram_Execute(task3_routine, (void *)2);
    SysProgram_AddTask(program_id, task2_routine, (void *)3);
    SysProgram_Execute(task3_routine, (void *)4);
    // END: Test field

    SystemTimer_InitializeForTaskSwitching();

    while (1) {}

    return 0;
}
