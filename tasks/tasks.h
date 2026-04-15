//
// Created by REXE on 21.03.26.
//

#ifndef TIOO_TASKS_H_
#define TIOO_TASKS_H_

#include <stdint.h>

#define TASKS_MAX_COUNT                 64

typedef struct Task_Item
{
    int32_t id;
    // uint32_t priority;

    uint32_t *stack_ptr;
    Platform_TaskData platform_data;

    struct Task_Item *next_for_program;
    struct Task_Item *next_for_scheduler;
} Task_Item;

__attribute__((section(".kernel_bss")))
Task_Item tasks[TASKS_MAX_COUNT];

int32_t Task_Create(void*(*func)(void*), void* arg);
int32_t Task_Kill(int32_t id);

#endif //TIOO_TASKS_H_
