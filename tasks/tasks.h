#ifndef TIOO_TASKS_H_
#define TIOO_TASKS_H_

#include <stdint.h>

#include <task_data.h>

#define TASKS_MAX_COUNT                 64

typedef struct Task_Item
{
    int32_t id;
    // uint32_t priority;

    uint32_t *stack_ptr;
    Platform_TaskData platform_data;

    struct Task_Item *next_for_program;
    struct Task_Item *next_for_switcher;
} Task_Item;

typedef struct
{
    Task_Item *curr_task;
} TasksManager;

extern Task_Item tasks[TASKS_MAX_COUNT];
extern TasksManager tasks_manager;

int32_t Task_Create(void *(*func)(void *), void *arg);
int32_t Task_Kill(int32_t id);

void *TasksManager_Switch(void *sp_to_save);

#endif //TIOO_TASKS_H_
