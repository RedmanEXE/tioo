#include <stddef.h>

#include "programs.h"

__attribute__((section(".kernel_bss"))) Program_Item programs[PROGRAMS_MAX_COUNT];

Program_Item *Program_FindEmptySlot()
{
    int32_t i;
    Program_Item *empty_slot = NULL;

    for (i = 0; i < PROGRAMS_MAX_COUNT; i++)
        if (PROGRAMS_ID_EMPTY == programs[i].id)
        {
            empty_slot = &programs[i];
            break;
        }

    return empty_slot;
}

int32_t Program_Create(void*(*func)(void*), void* arg)
{
    Program_Item *empty_slot = Program_FindEmptySlot();
    if (NULL == empty_slot)
        return -1;

    int32_t task_id = Task_Create(func, arg);
    empty_slot->first_task = Task_GetTaskAddress(task_id);

    empty_slot->id = 2;

    return 2;
}