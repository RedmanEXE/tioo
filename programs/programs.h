#ifndef TIOO_PROGRAMS_H_
#define TIOO_PROGRAMS_H_

#include <stdint.h>

#include <tasks/tasks.h>
#include <settings.h>

#define PROGRAMS_ID_EMPTY                   0
#define PROGRAMS_ID_KERNEL                  1

#define PROGRAM_DEFAULT_TASK_STACK_SIZE     1024

typedef struct
{
    uint16_t id;
    // Platform_ProgramData platform_data;
    uint32_t tasks_count;

    Task_Item *first_task;
    Task_Item *last_task;
} Program_Item;

extern Program_Item programs[PROGRAMS_MAX_COUNT];

Program_Item *Program_GetProgramAddress(uint16_t program_id);
int32_t Program_AddTask(uint16_t program_id, void*(*func)(void*), void* arg);
int32_t Program_Execute(void*(*func)(void*), void* arg);
void Program_Initialize(void);
int32_t Program_Terminate(uint16_t id);

#endif //TIOO_PROGRAMS_H_
