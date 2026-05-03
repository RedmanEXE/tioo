#include "ipc.h"

#include <stddef.h>
#include <errors/synchronizers.h>

extern void Platform_PutReturnValueIntoContext(void *stack_ptr, uint32_t result);

static void Mutexes_UnlockCallback(Lock_KeyObject *key, Task_Item *task)
{
    Synchronizer_Object *synchronizer = key->object;
    if (SYNCHRONIZER_TYPE_MUTEX != synchronizer->type)
        Platform_PutReturnValueIntoContext(task->stack_ptr, -1);
    else
    {
        int32_t result = Mutex_GetResource(synchronizer, task->id);
        Platform_PutReturnValueIntoContext(task->stack_ptr, result);
    }
}

int32_t Mutex_CreateObject(void)
{
    Synchronizer_Object *synchronizer = Synchronizers_FindFreeObject();
    if (NULL == synchronizer)
        return SYNCHRONIZER_ERROR_THERE_IS_NO_FREE_SLOTS;

    synchronizer->type = SYNCHRONIZER_TYPE_MUTEX;
    synchronizer->data.mutex.owner_task_id = 0;

    Lock_InitializeKey(&synchronizer->key, synchronizer, Mutexes_UnlockCallback);

    return synchronizer->id;
}

int32_t Mutex_IsResourceBusy(Synchronizer_Object *synchronizer)
{
    if (SYNCHRONIZER_TYPE_MUTEX != synchronizer->type)
        return SYNCHRONIZER_ERROR_WRONG_TYPE;

    return 0 != synchronizer->data.mutex.owner_task_id;
}

int32_t Mutex_GetResource(Synchronizer_Object *synchronizer, uint16_t task_id)
{
    if (0 != Mutex_IsResourceBusy(synchronizer))
        return 0;

    synchronizer->data.mutex.owner_task_id = task_id;
    return 1;
}

int32_t Mutex_ReturnResource(Synchronizer_Object *synchronizer, uint16_t task_id)
{
    if (0 <= Mutex_IsResourceBusy(synchronizer))
        return SYNCHRONIZER_ERROR_RESOURCE_NOT_USED;

    if (task_id != synchronizer->data.mutex.owner_task_id)
        return SYNCHRONIZER_ERROR_RESOURCE_YOU_ARE_NOT_OWNER;

    synchronizer->data.mutex.owner_task_id = 0;
    return 0;
}
