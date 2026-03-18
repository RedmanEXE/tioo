//
// Created by REXE on 18.03.26.
//

#include <stdint.h>

extern int Kernel_EntryPoint(void);

void Kernel_ResetHandler(void)
{
    Kernel_EntryPoint();
}

__attribute__ ((section(".isr_vector")))
uint32_t *isr_vectors[] = {
    (uint32_t *)0x20000010,
    (uint32_t *)Kernel_ResetHandler,
};
