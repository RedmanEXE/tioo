#include <stddef.h>

#include "programs.h"

#include "mem/mem.h"

__attribute__((section(".kernel_bss"))) Program_Item programs[PROGRAMS_MAX_COUNT];

static Program_Item *Program_FindEmptySlot()
{
    int32_t idx;
    Program_Item *empty_slot = NULL;

    for (idx = 1; idx <= PROGRAMS_MAX_COUNT; idx++)
    {
        Program_Item *program = Program_GetProgramAddress(idx);
        if (NULL == program->first_task)
        {
            empty_slot = program;
            break;
        }
    }

    return empty_slot;
}

void Program_AddTaskToQueue(Program_Item *program, Task_Item *task_to_add)
{
    if (NULL == program->first_task)
        program->first_task = task_to_add;
    if (NULL != program->last_task)
        program->last_task->next_for_program = task_to_add;

    task_to_add->prev_for_program = program->last_task;
    task_to_add->next_for_program = NULL;
    program->last_task = task_to_add;

    program->tasks_count++;
}

void Program_RemoveTaskFromQueue(Program_Item *program, Task_Item *task_to_remove)
{
    if (task_to_remove->id == program->first_task->id)
        program->first_task = task_to_remove->next_for_program;
    if (task_to_remove->id == program->last_task->id)
        program->last_task = task_to_remove->prev_for_program;

    task_to_remove->next_for_program->prev_for_program = task_to_remove->prev_for_program;
    task_to_remove->prev_for_program->next_for_program = task_to_remove->next_for_program;

    program->tasks_count--;

    if (0 == program->tasks_count)
        Program_Terminate(program->id);
}

Program_Item *Program_GetProgramAddress(uint16_t program_id)
{
    return &programs[program_id - 1];
}

int32_t Program_AddTask(uint16_t program_id, void*(*func)(void*), void* arg)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return -1;

    Program_Item *program = Program_GetProgramAddress(program_id);
    int32_t task_id = Task_Create(program->id, func, arg, PROGRAM_DEFAULT_TASK_STACK_SIZE);
    Task_Item *task = Task_GetTaskAddress(task_id);
    Program_AddTaskToQueue(program, task);

    Task_Launch(task_id);

    return task_id;
}

int32_t Program_Execute(void*(*func)(void*), void* arg)
{
    Program_Item *empty_slot = Program_FindEmptySlot();
    if (NULL == empty_slot)
        return -1;

    empty_slot->cablegrams = Memory_Allocate(PROGRAMS_ID_KERNEL, IPC_CABLEGRAMS_QUEUE_MEMORY_SIZE);
    CablegramsQueue_Initialize(empty_slot->cablegrams);

    int32_t task_id = Task_Create(empty_slot->id, func, arg, PROGRAM_DEFAULT_TASK_STACK_SIZE);
    Task_Item *task = Task_GetTaskAddress(task_id);
    Program_AddTaskToQueue(empty_slot, task);

    Task_Launch(task_id);

    return empty_slot->id;
}

void Program_Initialize(void)
{
    uint32_t idx;
    for (idx = 0; idx < PROGRAMS_MAX_COUNT; idx++)
        programs[idx].id = idx + 1;
}

// TODO: implement Program_Terminate
int32_t Program_Terminate(uint16_t id)
{
    return id;
}