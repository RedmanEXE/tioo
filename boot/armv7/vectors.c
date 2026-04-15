#include <stdint.h>

extern void Platform_SCHandler(void);
extern void Platform_ResetHandler(void);

extern void Kernel_Syscalls(uint32_t *saved_args);

__attribute__ ((section(".isr_vector")))
uint32_t *isr_vectors[] = {
    (uint32_t *)0x20001000,                     // Stack top
    (uint32_t *)Platform_ResetHandler,          // Entry point
    (uint32_t *)0,                              // Non-maskable interrupt
    (uint32_t *)0,                              // Hard fault
    (uint32_t *)0,                              // Memory management fault
    (uint32_t *)0,                              // Bus fault
    (uint32_t *)0,                              // Usage fault
    0, 0, 0, 0,                                 // (not used)
    (uint32_t *)Platform_SCHandler,             // SVC interrupt
    (uint32_t *)0,                              // Debug monitor
    (uint32_t *)0,                              // (not used)
    (uint32_t *)0,                              // PendSV interrupt
    (uint32_t *)0,                              // SysTick interrupt
    // ...and IRQs
};
