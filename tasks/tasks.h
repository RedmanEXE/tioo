#ifndef TIOO_TASKS_H_
#define TIOO_TASKS_H_

#include <stdint.h>

#include <task_data.h>

#define TASKS_MAX_COUNT                     64

typedef enum
{
    TASK_LAUNCH_STATE_SUSPENDED             = 0,
    TASK_LAUNCH_STATE_LAUNCHED              = 1,
    TASK_LAUNCH_STATE_WAITS_FOR_ANSWERS     = 2,
} Task_LaunchState;

typedef struct __attribute__((packed, aligned(4))) Task_Item
{
    uint16_t id;
    // uint32_t priority;
    Task_LaunchState launch_state;

    uint32_t *stack_ptr;
    Platform_TaskData platform_data;

    struct Task_Item *next_for_program;

    struct Task_Item *prev_for_switcher;
    struct Task_Item *next_for_switcher;
} Task_Item;

typedef struct
{
    Task_Item *curr_task;

    uint32_t tasks_count;
    Task_Item *first_task;
    Task_Item *last_task;
} TasksManager;

extern Task_Item tasks[TASKS_MAX_COUNT];
extern TasksManager tasks_manager;

int32_t Task_Create(void *(*func)(void *), void *arg, uint32_t stack_size);
int32_t Task_Kill(uint16_t id);

void TasksManager_AddToQueue(TasksManager *manager, Task_Item *task_to_add);
void TasksManager_RemoveFromQueue(TasksManager *manager, Task_Item *task_to_remove);
void *TasksManager_Switch(void *sp_to_save);

#endif //TIOO_TASKS_H_
