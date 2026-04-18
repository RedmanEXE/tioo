#ifndef TIOO_PROGRAMS_H_
#define TIOO_PROGRAMS_H_

#include <stdint.h>

#include <tasks/tasks.h>
#include <settings.h>

#define PROGRAMS_ID_EMPTY               0
#define PROGRAMS_ID_KERNEL              1

typedef struct
{
    uint16_t id;
    // Platform_ProgramData platform_data;

    Task_Item *first_task;
} Program_Item;

extern Program_Item programs[PROGRAMS_MAX_COUNT];

int32_t Program_Create(void*(*func)(void*), void* arg);
int32_t Program_Terminate(uint16_t id);

#endif //TIOO_PROGRAMS_H_
