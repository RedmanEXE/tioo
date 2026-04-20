//
// Created by REXE on 18.04.2026.
//

#ifndef TIOO_SETTINGS_H_
#define TIOO_SETTINGS_H_

// Interruptions settings

// END: Interruptions settings

// Programs settings
#define PROGRAMS_MAX_COUNT                      32
// END: Programs settings

// Platform registers and internals
#include "platform_constants.h"
// END: Platform registers and internals

// Memory settings
#define MEM_BASE_ADDRESS                        0x20000000
#define MEM_STACK_TOP_ADDRESS                   0x20000400

// Internal defines for pages logic
#define MEM_STACK_SIZE_IN_BYTES                 (1 * 1024)
#define MEM_SIZE_IN_BYTES                       (128 * 1024 - MEM_STACK_SIZE_IN_BYTES)

#define MEM_PAGE_SIZE_IN_BYTES                  1024
#define MEM_PAGES_COUNT                         (uint16_t)(MEM_SIZE_IN_BYTES / MEM_PAGE_SIZE_IN_BYTES)

// Internal defines for kernel RAM
#define MEM_KERNEL_PAGES_COUNT                  ((uint16_t)8 - (MEM_STACK_SIZE_IN_BYTES / MEM_PAGE_SIZE_IN_BYTES))
#define MEM_KERNEL_SIZE_IN_BYTES                (MEM_KERNEL_PAGES_COUNT * MEM_PAGE_SIZE_IN_BYTES)
// END: Memory settings

// Memory protection settings
#define MEMORY_PROTECTION_REGIONS_COUNT         8
// END: Memory protection settings

// Tasks settings
#define TASK_DEFAULT_STACK_SIZE                 1024
#define TASKS_MAX_COUNT                         64
// END: Tasks settings

// SysTimer settings

// END: SysTimer settings

#endif //TIOO_SETTINGS_H_
