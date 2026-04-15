#include <stdint.h>

extern void Platform_SCHandler(void);
extern void Platform_ResetHandler(void);

extern void Kernel_Syscalls(uint32_t *saved_args);

__attribute__ ((section(".isr_vector")))
uint32_t *isr_vectors[] = {
    0, 0,                                       // (not used)
    (uint32_t *)0,                              // Non-maskable interrupt
    (uint32_t *)0,                              // Hard fault
    (uint32_t *)0,                              // (not used)
    (uint32_t *)Platform_SCHandler,             // Ecall-M
    0, 0,                                       // (not used)
    (uint32_t *)Platform_SCHandler,             // Ecall-U
    (uint32_t *)0,                              // Breakpoint
    0, 0,                                       // (not used)
    (uint32_t *)0,                              // SysTick
    (uint32_t *)0,                              // (not used)
    (uint32_t *)0,                              // SoftWare Interrupt
    (uint32_t *)0,                              // (not used)
    // ...and IRQs
};
