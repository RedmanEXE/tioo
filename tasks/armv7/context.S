.thumb
.syntax unified

.equ        ICSR_ADDR, 0xE000ED04

.type       Platform_CreateTaskContext, %function
.global     Platform_CreateTaskContext
Platform_CreateTaskContext: // (void *stack_ptr, void *(*func)(void *), void *arg);
    // Align stack by 8
    bic     r0, r0, #7

    sub     r0, r0, #64
    // In xPSR Thumb need to be enabled
    ldr     r3, =0x01000000
    str     r3, [r0, #60]
    // Save func as entry for task
    str     r1, [r0, #56]

    // Save all Rs
    mov     r3, #0
    mov     r1, #0
    strd    r3, r1, [r0, #52]   // LR, R12
    strd    r3, r1, [r0, #44]   // R3, R2
    strd    r3, r2, [r0, #36]   // R1, R0 (arg)
    strd    r1, r3, [r0, #24]   // R10, R11
    strd    r1, r3, [r0, #16]   // R8, R9
    strd    r1, r3, [r0, #8]    // R6, R7
    strd    r1, r3, [r0, #0]    // R4, R5
    // ...and FPU registers need to be saved

    // and return r0 as stack_ptr
    bx      lr

.type       Platform_CreateMemoryProtectionContext, %function
.global     Platform_CreateMemoryProtectionContext
Platform_CreateMemoryProtectionContext: // ()
    

    bx      lr