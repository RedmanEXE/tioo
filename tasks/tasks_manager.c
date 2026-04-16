#include "tasks.h"

__attribute__((section(".kernel_bss"))) TasksManager tasks_manager;

void *TasksManager_Switch(void *sp_to_save)
{
    tasks_manager.curr_task->stack_ptr = sp_to_save;
    tasks_manager.curr_task = tasks_manager.curr_task->next_for_switcher;

    return tasks_manager.curr_task->stack_ptr;
}
