#ifndef TIOO_IPC_H_
#define TIOO_IPC_H_

#include <stdint.h>
#include <settings.h>
#include <tasks/tasks.h>

#define IPC_CABLEGRAMS_QUEUE_MEMORY_SIZE            1024
#define IPC_SYNCHRONIZERS_MAX_COUNT                 TASKS_MAX_COUNT

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

typedef enum
{
    SYNCHRONIZER_TYPE_NONE                  = 0,
    SYNCHRONIZER_TYPE_MUTEX                 = 1,
    SYNCHRONIZER_TYPE_SEMAPHORE             = 2
} Synchronizer_ObjectType;

typedef struct
{
    uint16_t id;
    Synchronizer_ObjectType type;
    Lock_KeyObject key;

    union
    {
        struct
        {
            uint8_t current_count;
            uint8_t max_count;
        } semaphore;

        struct
        {
            uint16_t owner_task_id;
        } mutex;
    } data;
} Synchronizer_Object;

extern Synchronizer_Object synchronizers[IPC_SYNCHRONIZERS_MAX_COUNT];

void CablegramsQueue_Initialize(Cablegrams_Queue *cablegrams_queue);

int32_t Cablegram_Send(uint16_t program_id, Cablegram_Item *cablegram);
int32_t Cablegram_Receive(uint16_t program_id, Cablegram_Item *out);
int32_t Cablegram_WaitAndReceive(uint16_t program_id, uint16_t task_id, Cablegram_Item *out, int32_t timeout);

void Lock_CloseByKey(Lock_KeyObject *key, uint16_t task_id, int32_t timeout);
void Lock_InitializeKey(Lock_KeyObject *key, void *object, void (*callback)(Lock_KeyObject *key, Task_Item *task));
void Lock_OpenByKey(Lock_KeyObject *key, uint32_t count);
void Lock_OpenAllByKey(Lock_KeyObject *key);

int32_t Mutex_CreateObject(void);
int32_t Mutex_GetResource(Synchronizer_Object *synchronizer, uint16_t task_id);
int32_t Mutex_ReturnResource(Synchronizer_Object *synchronizer, uint16_t task_id);

int32_t Semaphore_CreateObject(uint8_t max_count);
int32_t Semaphore_GetResource(Synchronizer_Object *synchronizer);
int32_t Semaphore_ReturnResource(Synchronizer_Object *synchronizer);

void Synchronizers_Initialize(void);
Synchronizer_Object *Synchronizers_FindFreeObject();

int32_t Synchronizer_GetResource(uint16_t syncer_id, uint16_t task_id, int32_t timeout);
int32_t Synchronizer_ReturnResource(uint16_t syncer_id, uint16_t task_id);
int32_t Synchronizer_FreeObject(uint16_t syncer_id);

#endif //TIOO_IPC_H_
