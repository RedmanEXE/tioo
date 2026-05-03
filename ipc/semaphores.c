#include "ipc.h"

#include <stddef.h>

extern void Platform_PutReturnValueIntoContext(void *stack_ptr, uint32_t result);

static void Semaphores_UnlockCallback(Lock_KeyObject *key, Task_Item *task)
{
    Synchronizer_Object *synchronizer = key->object;
    if (SYNCHRONIZER_TYPE_SEMAPHORE != synchronizer->type)
        Platform_PutReturnValueIntoContext(task->stack_ptr, -1);
    else
    {
        int32_t result = Semaphore_GetResource(synchronizer);
        Platform_PutReturnValueIntoContext(task->stack_ptr, result);
    }
}

int32_t Semaphore_CreateObject(uint8_t max_count)
{
    Synchronizer_Object *synchronizer = Synchronizers_FindFreeObject();
    if (NULL == synchronizer)
        return -1;

    synchronizer->type = SYNCHRONIZER_TYPE_SEMAPHORE;
    synchronizer->data.semaphore.current_count = 0;
    synchronizer->data.semaphore.max_count = max_count;

    Lock_InitializeKey(&synchronizer->key, synchronizer, Semaphores_UnlockCallback);

    return synchronizer->id;
}

int32_t Semaphore_IsResourceBusy(Synchronizer_Object *synchronizer)
{
    if (NULL == synchronizer)
        return -1;

    if (SYNCHRONIZER_TYPE_MUTEX != synchronizer->type)
        return -2;

    return synchronizer->data.semaphore.max_count <= synchronizer->data.semaphore.current_count;
}

int32_t Semaphore_GetResource(Synchronizer_Object *synchronizer)
{
    if (0 != Semaphore_IsResourceBusy(synchronizer))
        return 0;

    synchronizer->data.semaphore.current_count++;
    return 1;
}

int32_t Semaphore_ReturnResource(Synchronizer_Object *synchronizer)
{
    if (0 <= Semaphore_IsResourceBusy(synchronizer))
        return -1;

    if (0 == synchronizer->data.semaphore.current_count)
        return -2;

    synchronizer->data.semaphore.current_count--;
    return 0;
}
