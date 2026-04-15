#ifndef TIOO_PROGRAMS_H_
#define TIOO_PROGRAMS_H_

#include <stdint.h>

#include <tasks/tasks.h>

#define PROGRAMS_ID_EMPTY               0
#define PROGRAMS_ID_KERNEL              1

#define PROGRAMS_MAX_COUNT              32

typedef struct
{
    int32_t id;
    Platform_ProgramData platform_data;

    Task_Item *first_task;
} Program_Item;

__attribute__((section(".kernel_bss")))
Program_Item programs[PROGRAMS_MAX_COUNT];

int32_t Program_Create(void*(*func)(void*), void* arg);
int32_t Program_Terminate(int32_t id);

#endif //TIOO_PROGRAMS_H_
