#include "ipc.h"

#include <tasks/tasks.h>
#include <stddef.h>

static void Lock_AddTask(Lock_KeyObject *key, Task_Item *task)
{
    task->next_for_lock = NULL;

    if (NULL == key->first_locked)
        key->first_locked = task;
    if (NULL != key->last_locked)
        key->last_locked->next_for_lock = task;

    key->last_locked = task;
}

static void Lock_TrimUntilTask(Lock_KeyObject *key, Task_Item *task)
{
    key->first_locked = task;
    if (NULL == task)
        key->last_locked = task;
}

void Lock_CloseByKey(Lock_KeyObject *key, uint16_t task_id, int32_t timeout)
{
    Task_Item *task = Task_GetTaskAddress(task_id);
    Lock_AddTask(key, task);
    Task_LockByKey(task_id, key, timeout);
}

void Lock_InitializeKey(Lock_KeyObject *key, void *object, void (*callback)(Lock_KeyObject *key, Task_Item *task))
{
    key->object = object;
    key->on_unlock_callback = callback;

    key->first_locked = NULL;
    key->last_locked = NULL;
}

void Lock_OpenByKey(Lock_KeyObject *key, uint32_t count)
{
    uint32_t idx = 0;
    Task_Item *task = key->first_locked;

    while (NULL != task && idx < count)
    {
        if (task->lock_key == key)
        {
            key->on_unlock_callback(key, task);
            Task_UnlockByKey(task->id, key);
            idx++;
        }

        Task_Item *next_task = task->next_for_lock;
        task->next_for_lock = NULL;
        task = next_task;
    }

    Lock_TrimUntilTask(key, task);
}

void Lock_OpenAllByKey(Lock_KeyObject *key)
{
    Task_Item *task = key->first_locked;

    while (NULL != task)
    {
        if (task->lock_key == key)
        {
            key->on_unlock_callback(key, task);
            Task_UnlockByKey(task->id, key);
        }

        Task_Item *next_task = task->next_for_lock;
        task->next_for_lock = NULL;
        task = next_task;
    }
}
