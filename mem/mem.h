#ifndef TIOO_MEM_H_
#define TIOO_MEM_H_

// ======== DEFAULT SUBROUTINES ========
void Memory_Initialize(void);
void *Memory_Allocate(uint16_t requester_id, uint32_t bytes_len);
void Memory_Free(uint16_t requester_id, void *block);

#endif //TIOO_MEM_H_
