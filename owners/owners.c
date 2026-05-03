#include "owners.h"

#include "tasks/tasks.h"

uint16_t Owner_GetActiveTaskID()
{
    return tasks_manager.curr_task->id;
}

uint16_t Owner_GetActiveTaskProgramID()
{
    return tasks_manager.curr_task->program_owner_id;
}
