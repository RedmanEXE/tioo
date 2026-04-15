//
// Created by REXE on 20.03.26.
//

#ifndef TIOO_MEM_ROUTINES_H_
#define TIOO_MEM_ROUTINES_H_

#define MEM_BASE_ADDRESS            0x20000000
#define MEM_STACK_TOP_ADDRESS       0x20000800

// Internal defines for pages logic
#define MEM_STACK_SIZE_IN_BYTES     (2 * 1024)
#define MEM_SIZE_IN_BYTES           (64 * 1024 - MEM_STACK_SIZE_IN_BYTES)

#define MEM_PAGE_SIZE_IN_BYTES      512
#define MEM_PAGES_COUNT             (uint16_t)(MEM_SIZE_IN_BYTES / MEM_PAGE_SIZE_IN_BYTES)

// Internal defines for kernel RAM
#define MEM_KERNEL_PAGES_COUNT      ((uint16_t)8 - (MEM_STACK_SIZE_IN_BYTES / MEM_PAGE_SIZE_IN_BYTES))
#define MEM_KERNEL_SIZE_IN_BYTES    (MEM_KERNEL_PAGES_COUNT * MEM_PAGE_SIZE_IN_BYTES)

#endif //TIOO_MEM_ROUTINES_H_
