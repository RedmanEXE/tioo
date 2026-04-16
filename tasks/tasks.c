#include "tasks.h"

#include <stddef.h>

extern void *Platform_CreateTaskContext(void *stack_ptr, void *(*func)(void *), void *arg);

__attribute__((section(".kernel_bss"))) Task_Item tasks[TASKS_MAX_COUNT];

int32_t Task_Create(void *(*func)(void *), void *arg)
{
    // TODO: Create function for task free struct searching
    Task_Item *task = &tasks[0];

    task->stack_ptr = Platform_CreateTaskContext(task->stack_ptr, func, arg);

    // TODO: Return real task ID
    return -1;
}
