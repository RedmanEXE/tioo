#include "ipc.h"

#include <stddef.h>
#include <errors/synchronizers.h>

__attribute__((section(".kernel_bss"))) Synchronizer_Object synchronizers[IPC_SYNCHRONIZERS_MAX_COUNT];

Synchronizer_Object *Synchronizer_GetSynchronizerAddress(uint16_t sync_id)
{
    return &synchronizers[sync_id - 1];
}

Synchronizer_Object *Synchronizers_FindFreeObject()
{
    uint16_t idx;
    Synchronizer_Object *free_item = NULL;
    for (idx = 1; IPC_SYNCHRONIZERS_MAX_COUNT >= idx; idx++)
    {
        Synchronizer_Object *item = Synchronizer_GetSynchronizerAddress(idx);
        if (SYNCHRONIZER_TYPE_NONE == item->type)
        {
            free_item = item;
            break;
        }
    }

    return free_item;
}

void Synchronizers_Initialize(void)
{
    uint16_t idx;
    for (idx = 1; IPC_SYNCHRONIZERS_MAX_COUNT >= idx; idx++)
    {
        Synchronizer_Object *item = Synchronizer_GetSynchronizerAddress(idx);
        item->id = idx;
    }
}

int32_t Synchronizer_GetResource(uint16_t syncer_id, uint16_t task_id, int32_t timeout)
{
    if (IPC_SYNCHRONIZERS_MAX_COUNT <= syncer_id)
        return SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS;

    int32_t result;
    Synchronizer_Object *synchronizer = Synchronizer_GetSynchronizerAddress(syncer_id);
    switch (synchronizer->type)
    {
        case SYNCHRONIZER_TYPE_MUTEX:
            result = Mutex_GetResource(synchronizer, task_id);
            break;
        case SYNCHRONIZER_TYPE_SEMAPHORE:
            result = Semaphore_GetResource(synchronizer);
            break;
        default:
            result = SYNCHRONIZER_ERROR_WRONG_TYPE;
    }

    if (0 > timeout)
        timeout = 0;

    if (0 == result)
        Lock_CloseByKey(&synchronizer->key, task_id, timeout);

    return result;
}

int32_t Synchronizer_ReturnResource(uint16_t syncer_id, uint16_t task_id)
{
    if (IPC_SYNCHRONIZERS_MAX_COUNT <= syncer_id)
        return SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS;

    int32_t result;
    Synchronizer_Object *synchronizer = Synchronizer_GetSynchronizerAddress(syncer_id);
    switch (synchronizer->type)
    {
        case SYNCHRONIZER_TYPE_MUTEX:
            result = Mutex_ReturnResource(synchronizer, task_id);
            break;
        case SYNCHRONIZER_TYPE_SEMAPHORE:
            result = Semaphore_ReturnResource(synchronizer);
            break;
        default:
            result = SYNCHRONIZER_ERROR_WRONG_TYPE;
    }

    if (0 < result)
        Lock_OpenByKey(&synchronizer->key, 1);

    return result;
}

int32_t Synchronizer_FreeObject(uint16_t syncer_id)
{
    if (IPC_SYNCHRONIZERS_MAX_COUNT <= syncer_id)
        return SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS;

    Synchronizer_Object *synchronizer = Synchronizer_GetSynchronizerAddress(syncer_id);
    if (SYNCHRONIZER_TYPE_NONE == synchronizer->type)
        return SYNCHRONIZER_ERROR_OBJECT_IS_ALREADY_FREE;

    Lock_OpenAllByKey(&synchronizer->key);
    synchronizer->type = SYNCHRONIZER_TYPE_NONE;

    return 0;
}
