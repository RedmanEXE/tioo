#ifndef TIOO_IPC_H_
#define TIOO_IPC_H_

#include <stdint.h>

#define IPC_CABLEGRAMS_QUEUE_MEMORY_SIZE            1024

typedef struct
{
    uint32_t type;
    uint32_t data;
} Cablegram_Item;

typedef struct
{
    Cablegram_Item *last_read;
    Cablegram_Item *next_write;
    uint8_t swapped_since_last_read;

    Cablegram_Item cablegrams[32];
} Cablegrams_Queue;

void CablegramsQueue_Initialize(Cablegrams_Queue *cablegrams_queue);

int32_t Cablegram_Send(uint16_t program_id, Cablegram_Item *cablegram);
int32_t Cablegram_Receive(uint16_t program_id, Cablegram_Item *out);
int32_t Cablegram_WaitAndReceive(uint16_t program_id, uint16_t task_id, Cablegram_Item *out, int32_t timeout);

#endif //TIOO_IPC_H_
