//
// Created by REXE on 20.03.26.
//

#ifndef TIOO_MEM_H_
#define TIOO_MEM_H_

#define NULL                        (void *)0

// Internal defines for pages logic
#define MEM_PAGE_SIZE_IN_BYTES      1024
#define MEM_SIZE_IN_BYTES           (128 * 1024)
#define MEM_PAGES_COUNT             (uint16_t)(MEM_SIZE_IN_BYTES / MEM_PAGE_SIZE_IN_BYTES)

// Internal defines for kernel RAM
#define MEM_KERNEL_PAGES_COUNT      (uint16_t)8
#define MEM_KERNEL_SIZE_IN_BYTES    (MEM_KERNEL_PAGES_COUNT * MEM_PAGE_SIZE_IN_BYTES)

void Memory_Initialize(void);
void *Memory_Allocate(uint16_t owner_id, uint32_t bytes_len);
void Memory_Free(uint16_t owner_id, void *block);

#endif //TIOO_MEM_H_
