#include "tasks.h"

#include <stddef.h>

#include <mem/mem.h>
#include <programs/programs.h>

extern void *Platform_CreateTaskContext(void *stack_ptr, void *(*func)(void *), void *arg);
extern void Platform_ScheduleTaskSwitch();

__attribute__((section(".kernel_bss"))) Task_Item tasks[TASKS_MAX_COUNT];

static Task_Item *Task_FindFirstFreeStruct()
{
    int32_t idx;
    Task_Item *item = NULL;
    for (idx = 0; idx < TASKS_MAX_COUNT; idx++)
        if (NULL == tasks[idx].stack_ptr)
        {
            item = &tasks[idx];
            break;
        }

    return item;
}

Task_Item *Task_GetTaskAddress(uint16_t task_id)
{
    return &tasks[task_id];
}

int32_t Task_Create(uint16_t program_id, void *(*func)(void *), void *arg, uint32_t stack_size)
{
    Task_Item *task = Task_FindFirstFreeStruct();
    if (NULL == task)
        return -1;

    task->program_owner_id = program_id;

    // TODO: Create memory allocation as a program and as a task
    // - All tasks can access program's memory (data)
    // - Every task can access only their memory (stack)
    void *stack_ptr = Memory_Allocate(task->id, stack_size) + stack_size;

    // TODO: Create MPU/PMP setup
    // Platform_SetupMemoryProtectionContext()

    task->stack_ptr = Platform_CreateTaskContext(stack_ptr, func, arg);
    task->launch_state = TASK_LAUNCH_STATE_SUSPENDED;

    TasksManager_AddToQueue(&tasks_manager, task);

    return task->id;
}

int32_t Task_Launch(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = &tasks[task_id];
    if (TASK_LAUNCH_STATE_SUSPENDED != task->launch_state)
        return -2;

    task->launch_state = TASK_LAUNCH_STATE_LAUNCHED;
    return 0;
}

int32_t Task_Kill(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = &tasks[task_id];
    task->launch_state = TASK_LAUNCH_STATE_SUSPENDED;

    if (tasks_manager.curr_task->id == task->id)
        Platform_ScheduleTaskSwitch();

    return 0;
}

int32_t Task_Free(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = &tasks[task_id];
    if (TASK_LAUNCH_STATE_SUSPENDED != task->launch_state)
        return -2;

    if (tasks_manager.curr_task->id == task->id)
        return -3;

    // FIXME: Check Memory_Free in mem/mem.c
    Memory_Free(task_id, task->stack_ptr);
    task->stack_ptr = NULL;
    task->program_owner_id = PROGRAMS_ID_EMPTY;

    TasksManager_RemoveFromQueue(&tasks_manager, task);

    return 0;
}
