#ifndef TIOO_IPC_H_
#define TIOO_IPC_H_

#include <stdint.h>
#include <settings.h>
#include <tasks/tasks.h>

#define IPC_CABLEGRAMS_QUEUE_MEMORY_SIZE            1024

typedef struct Lock_KeyObject
{
    void *object;
    void (*on_unlock_callback)(struct Lock_KeyObject *key, Task_Item *task);

    Task_Item *first_locked;
    Task_Item *last_locked;
} Lock_KeyObject;

typedef struct
{
    uint32_t type;
    uint32_t data;
} Cablegram_Item;

typedef struct
{
    Cablegram_Item *last_read;
    Cablegram_Item *next_write;

    Lock_KeyObject key;

    Cablegram_Item cablegrams[32];
} Cablegrams_Queue;

void CablegramsQueue_Initialize(Cablegrams_Queue *cablegrams_queue);

int32_t Cablegram_Send(uint16_t program_id, Cablegram_Item *cablegram);
int32_t Cablegram_Receive(uint16_t program_id, Cablegram_Item *out);
int32_t Cablegram_WaitAndReceive(uint16_t program_id, uint16_t task_id, Cablegram_Item *out, int32_t timeout);

void Lock_CloseByKey(Lock_KeyObject *key, uint16_t task_id, int32_t timeout);
void Lock_InitializeKey(Lock_KeyObject *key, void *object, void (*callback)(Lock_KeyObject *key, Task_Item *task));
void Lock_OpenByKey(Lock_KeyObject *key, uint32_t count);
void Lock_OpenAllByKey(Lock_KeyObject *key);

#endif //TIOO_IPC_H_
