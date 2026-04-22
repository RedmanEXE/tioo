#include "tasks.h"

#include <stddef.h>

#include <mem/mem.h>
#include <programs/programs.h>

extern void *Platform_CreateTaskContext(void *stack_ptr, void *(*func)(void *), void *arg, uint32_t create_with_extras);
extern void Platform_CreateMemoryProtectionContext(Platform_TaskData *zone);
extern void Platform_ScheduleTaskSwitch();

__attribute__((section(".kernel_bss"))) Task_Item tasks[TASKS_MAX_COUNT];

static Task_Item *Task_FindFirstFreeStruct()
{
    uint32_t idx;
    Task_Item *item = NULL;
    for (idx = 1; idx <= TASKS_MAX_COUNT; idx++)
    {
        Task_Item *task = Task_GetTaskAddress(idx);
        if (NULL == task->stack_ptr)
        {
            item = task;
            break;
        }
    }

    return item;
}

static uint32_t Task_IsLaunched(Task_Item *task)
{
    return task->launch_state == TASK_LAUNCH_STATE_RUNNING || task->launch_state == TASK_LAUNCH_STATE_LAUNCHED;
}

Task_Item *Task_GetTaskAddress(uint16_t task_id)
{
    return &tasks[task_id - 1];
}

void Task_SetState(Task_Item *task, Task_LaunchState new_state)
{
    if (tasks_manager.curr_task->id == task->id)
        task->post_state = new_state;
    else
        task->launch_state = new_state;
}

void Task_SwapStates(Task_Item *task)
{
    Task_LaunchState state = task->launch_state;
    task->launch_state = task->post_state;
    task->post_state = state;
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
    // Platform_CreateMemoryProtectionContext(&task->platform_data);

    task->stack_ptr = Platform_CreateTaskContext(stack_ptr, func, arg, tasks_manager.curr_task != NULL);
    task->launch_state = TASK_LAUNCH_STATE_SUSPENDED;

    TasksManager_AddToQueue(&tasks_manager, task);

    return task->id;
}

int32_t Task_Launch(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    if (Task_IsLaunched(task))
        return -2;

    Task_SetState(task, TASK_LAUNCH_STATE_LAUNCHED);
    return 0;
}

int32_t Task_Kill(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    Task_SetState(task, TASK_LAUNCH_STATE_SUSPENDED);

    if (tasks_manager.curr_task->id == task->id)
        Platform_ScheduleTaskSwitch();

    return 0;
}

int32_t Task_Free(uint16_t task_id)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    if (Task_IsLaunched(task))
        return -2;

    if (tasks_manager.curr_task->id == task->id)
        return -3;

    // FIXME: Check Memory_Free in mem/mem.c
    Memory_Free(task_id, task->stack_ptr);
    task->stack_ptr = NULL;
    task->program_owner_id = PROGRAMS_ID_EMPTY;

    TasksManager_RemoveFromQueue(&tasks_manager, task);
    task->prev_for_switcher = NULL;
    task->next_for_switcher = NULL;
    task->prev_for_program = NULL;
    task->next_for_program = NULL;

    return 0;
}

int32_t Task_KickIntoSleep(uint16_t task_id, int32_t sleep_time)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    if (!Task_IsLaunched(task))
        return -2;

    task->remains_to_sleep = sleep_time;
    Task_SetState(task, TASK_LAUNCH_STATE_BLOCKED);

    if (tasks_manager.curr_task->id == task->id)
        Platform_ScheduleTaskSwitch();

    return 0;
}

int32_t Task_LockByObject(uint16_t task_id, void *object, int32_t timeout)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    if (NULL != task->lock_object)
        return -2;

    task->lock_object = object;
    task->remains_to_sleep = timeout;
    Task_SetState(task, TASK_LAUNCH_STATE_BLOCKED);

    if (tasks_manager.curr_task->id == task->id)
        Platform_ScheduleTaskSwitch();

    return 0;
}

int32_t Task_UnlockByObject(uint16_t task_id, void *object)
{
    if (TASKS_MAX_COUNT <= task_id)
        return -1;

    Task_Item *task = Task_GetTaskAddress(task_id);
    if (object != task->lock_object)
        return -2;

    task->lock_object = NULL;
    task->remains_to_sleep = 0;
    Task_SetState(task, TASK_LAUNCH_STATE_LAUNCHED);

    return 0;
}
