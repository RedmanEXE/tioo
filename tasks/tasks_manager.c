#include "tasks.h"

#include <stddef.h>

#include <programs/programs.h>

extern void Platform_ChangeCurrentContextPointer(void *new_ptr);

__attribute__((section(".kernel_bss"))) TasksManager tasks_manager;

static Task_Item *TasksManager_FindNextTask(Task_Item *curr_task)
{
    int32_t idx;
    Task_Item *task = curr_task;
    for (idx = 0; idx < TASKS_MAX_COUNT + 1; idx++)
    {
        task = task->next_for_switcher;
        if (TASK_LAUNCH_STATE_LAUNCHED == task->launch_state)
            break;
    }

    if (TASKS_MAX_COUNT < idx)
        return curr_task;
    return task;
}

void TasksManager_AddToQueue(TasksManager *manager, Task_Item *task_to_add)
{
    if (NULL == manager->first_task)
        manager->first_task = task_to_add;
    if (NULL != manager->last_task)
        manager->last_task->next_for_switcher = task_to_add;

    if (NULL == manager->curr_task)
    {
        manager->curr_task = task_to_add;
        Platform_ChangeCurrentContextPointer(task_to_add->stack_ptr);
    }

    task_to_add->prev_for_switcher = manager->last_task;
    task_to_add->next_for_switcher = manager->first_task;
    manager->last_task = task_to_add;

    manager->tasks_count++;
}

void TasksManager_RemoveFromQueue(TasksManager *manager, Task_Item *task_to_remove)
{
    if (task_to_remove->id == manager->first_task->id)
        manager->first_task = task_to_remove->next_for_switcher;
    if (task_to_remove->id == manager->last_task->id)
        manager->last_task = task_to_remove->prev_for_switcher;

    task_to_remove->next_for_switcher->prev_for_switcher = task_to_remove->prev_for_switcher;
    task_to_remove->prev_for_switcher->next_for_program = task_to_remove->next_for_switcher;

    manager->tasks_count--;

    if (0 == manager->tasks_count)
    {
        manager->first_task = NULL;
        manager->last_task = NULL;
    }
}

void TasksManager_UpdateSleepTimersForTasks()
{
    Task_Item *item = tasks_manager.first_task;

    if (NULL == item)
        return;

    do
    {
        if (0 < item->remains_to_sleep)
        {
            item->remains_to_sleep--;
            if (0 == item->remains_to_sleep && TASK_LAUNCH_STATE_BLOCKED == item->launch_state)
                item->launch_state = TASK_LAUNCH_STATE_LAUNCHED;
        }

        item = item->next_for_switcher;
    } while (item != tasks_manager.first_task);
}

void TasksManager_Initialize(void)
{
    uint16_t idx;
    for (idx = 0; idx < TASKS_MAX_COUNT; idx++)
        tasks[idx].id = idx + 1;
}

void *TasksManager_Switch(void *sp_to_save)
{
    Task_Item *task = TasksManager_FindNextTask(tasks_manager.curr_task);

    tasks_manager.curr_task->stack_ptr = sp_to_save;
    Task_SwapStates(tasks_manager.curr_task);

    tasks_manager.curr_task = task;
    Task_SwapStates(task);
    task->launch_state = TASK_LAUNCH_STATE_RUNNING;
    return tasks_manager.curr_task->stack_ptr;
}
