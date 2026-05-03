#include "ipc.h"

#include <stddef.h>
#include <programs/programs.h>
#include <errors/cablegrams.h>

extern uint32_t Platform_GetArgumentValueFromContext(void *stack_ptr, uint32_t index);
extern void Platform_PutReturnValueIntoContext(void *stack_ptr, uint32_t result);

static uint32_t CablegramsQueue_AddMessage(Cablegrams_Queue *cablegrams_queue, Cablegram_Item *cablegram)
{
    Cablegram_Item *preview_value = cablegrams_queue->header.next_write + 1;
    if (preview_value > &cablegrams_queue->cablegrams[31])
        preview_value = &cablegrams_queue->cablegrams[0];
    if (cablegrams_queue->header.last_read == preview_value)
        return 0;

    cablegrams_queue->header.next_write->sender_id = cablegram->sender_id;
    cablegrams_queue->header.next_write->type = cablegram->type;
    cablegrams_queue->header.next_write->data = cablegram->data;

    cablegrams_queue->header.next_write = preview_value;

    return 1;
}

static Cablegram_Item *CablegramsQueue_ReadMessage(Cablegrams_Queue *cablegrams_queue)
{
    Cablegram_Item *preview_value = cablegrams_queue->header.last_read + 1;
    if (preview_value > &cablegrams_queue->cablegrams[31])
        preview_value = &cablegrams_queue->cablegrams[0];
    if (cablegrams_queue->header.next_write == preview_value)
        return NULL;

    cablegrams_queue->header.last_read = preview_value;
    Cablegram_Item *cablegram = cablegrams_queue->header.last_read;

    return cablegram;
}

static void CablegramsQueue_UnlockCallback(Lock_KeyObject *key, Task_Item *task)
{
    (void)key;
    uint16_t program_id = (uint16_t)Platform_GetArgumentValueFromContext(task->stack_ptr, 0);
    Cablegram_Item *out = (Cablegram_Item *)Platform_GetArgumentValueFromContext(task->stack_ptr, 2);

    int32_t result = Cablegram_Receive(program_id, out);
    Platform_PutReturnValueIntoContext(task->stack_ptr, result);
}

void CablegramsQueue_Initialize(Cablegrams_Queue *cablegrams_queue)
{
    cablegrams_queue->header.last_read = &cablegrams_queue->cablegrams[31];
    cablegrams_queue->header.next_write = &cablegrams_queue->cablegrams[0];

    Lock_InitializeKey(&cablegrams_queue->header.key, cablegrams_queue, CablegramsQueue_UnlockCallback);
}

int32_t Cablegram_Send(uint16_t program_id, Cablegram_Item *cablegram)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS;

    Program_Item *program = Program_GetProgramAddress(program_id);
    cablegram->sender_id = program_id;
    if (!CablegramsQueue_AddMessage(program->cablegrams, cablegram))
        return CABLEGRAM_ERROR_QUEUE_IS_FULL;

    Lock_OpenByKey(&program->cablegrams->header.key, 1);

    return 0;
}

int32_t Cablegram_Receive(uint16_t program_id, Cablegram_Item *out)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS;

    Program_Item *program = Program_GetProgramAddress(program_id);
    Cablegram_Item *cablegram = CablegramsQueue_ReadMessage(program->cablegrams);
    if (NULL == cablegram)
        return 0;

    out->sender_id = cablegram->sender_id;
    out->type = cablegram->type;
    out->data = cablegram->data;

    return 1;
}

int32_t Cablegram_WaitAndReceive(uint16_t program_id, uint16_t task_id, Cablegram_Item *out, int32_t timeout)
{
    if (PROGRAMS_MAX_COUNT <= program_id)
        return CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS;

    if (0 > timeout)
        timeout = 0;

    Program_Item *program = Program_GetProgramAddress(program_id);
    Cablegram_Item *cablegram = CablegramsQueue_ReadMessage(program->cablegrams);
    if (NULL == cablegram)
    {
        Lock_CloseByKey(&program->cablegrams->header.key, task_id, timeout);
        return 0;
    }

    out->data = cablegram->data;
    out->type = cablegram->type;
    return 1;
}
