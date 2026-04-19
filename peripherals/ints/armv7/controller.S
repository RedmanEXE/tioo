.thumb
.syntax unified

#include    <settings.h>

.type       Platform_InterruptionSetPriority, %function
.global     Platform_InterruptionSetPriority
Platform_InterruptionSetPriority: // (uint8_t int_idx, uint8_t priority)
    ldr     r2, =PLATFORM_INTS_PRIORITY_REGISTER
    add     r2, r0

    ldr     r0, [r2]
    orr     r0, r0, 0xFF
    and     r0, r0, r1
    str     r0, [r2]

    bx      lr