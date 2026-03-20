#include <stdint.h>

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int Kernel_EntryPoint(void);
extern void Kernel_Syscalls(uint32_t *saved_args);

void Platform_ResetHandler(void)
{
    uint32_t *src, *dest;

    // Copy initialized data
    src = &_sidata;
    dest = &_sdata;
    while (dest < &_edata)
    {
        *dest++ = *src++;
    }

    // Fill with zeros non-initialized data
    dest = &_sbss;
    while (dest < &_ebss)
    {
        *dest++ = 0;
    }

    Kernel_EntryPoint();
}

__attribute__((naked))
void Platform_SVCHandler(void)
{
    __asm__ volatile (
        "tst    lr, #4\n"
        "ite    eq\n"
        "mrseq  r0, msp\n"
        "mrsne  r0, psp\n"
        "b      Kernel_Syscalls\n"
    );
}

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
    (uint32_t *)Platform_SVCHandler,            // SVC interrupt
    (uint32_t *)0,                              // Debug monitor
    (uint32_t *)0,                              // (not used)
    (uint32_t *)0,                              // PendSV interrupt
    (uint32_t *)0,                              // SysTick interrupt
    // ...and IRQs
};
