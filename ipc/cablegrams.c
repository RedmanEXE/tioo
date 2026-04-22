#include "ipc.h"

#include <stddef.h>
#include <settings.h>
#include <programs/programs.h>

static uint32_t CablegramsQueue_AddMessage(Cablegrams_Queue *cablegrams_queue, Cablegram_Item *cablegram)
{
    Cablegram_Item *preview_value = cablegrams_queue->next_write + 1;
    if (preview_value > &cablegrams_queue->cablegrams[31])
        preview_value = &cablegrams_queue->cablegrams[0];
    if (cablegrams_queue->last_read == preview_value)
        return 0;

    cablegrams_queue->next_write->type = cablegram->type;
    cablegrams_queue->next_write->data = cablegram->data;

    cablegrams_queue->next_write = preview_value;

    return 1;
}

void CablegramsQueue_Initialize(Cablegrams_Queue *cablegrams_queue)
{
    cablegrams_queue->last_read = &cablegrams_queue->cablegrams[31];
    cablegrams_queue->next_write = &cablegrams_queue->cablegrams[0];
    cablegrams_queue->swapped_since_last_read = 0;
}

static Cablegram_Item *CablegramsQueue_ReadMessage(Cablegrams_Queue *cablegrams_queue)
{
    Cablegram_Item *preview_value = cablegrams_queue->last_read + 1;
    if (preview_value > &cablegrams_queue->cablegrams[31])
        preview_value = &cablegrams_queue->cablegrams[0];
    if (cablegrams_queue->next_write == preview_value)
        return NULL;

    cablegrams_queue->last_read = preview_value;
    Cablegram_Item *cablegram = cablegrams_queue->last_read;

    return cablegram;
}

int32_t Cablegram_Send(uint16_t program_id, Cablegram_Item *cablegram)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return -1;

    Program_Item *program = Program_GetProgramAddress(program_id);
    if (!CablegramsQueue_AddMessage(program->cablegrams, cablegram))
        return -2;

    TasksManager_UnlockTasksByObject(program->cablegrams);

    return 0;
}

int32_t Cablegram_Receive(uint16_t program_id, Cablegram_Item *out)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return -1;

    Program_Item *program = Program_GetProgramAddress(program_id);
    Cablegram_Item *cablegram = CablegramsQueue_ReadMessage(program->cablegrams);
    if (NULL == cablegram)
        return 0;

    out->data = cablegram->data;
    out->type = cablegram->type;
    return 1;
}

int32_t Cablegram_WaitAndReceive(uint16_t program_id, uint16_t task_id, Cablegram_Item *out, int32_t timeout)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return -1;

    Program_Item *program = Program_GetProgramAddress(program_id);
    Cablegram_Item *cablegram = CablegramsQueue_ReadMessage(program->cablegrams);
    if (NULL == cablegram)
    {
        Task_LockByObject(task_id, program->cablegrams, timeout);
        return 0;
    }

    out->data = cablegram->data;
    out->type = cablegram->type;
    return 1;
}
