.thumb
.syntax unified

.type       Platform_CreateTaskContext, %function
.global     Platform_CreateTaskContext
Platform_CreateTaskContext: // (void *stack_ptr, void *(*func)(void *), void *arg, uint32_t create_with_extras);
    push    {r4}
    // Align stack by 8
    bic     r0, r0, #7

    sub     r0, r0, #32
    // In xPSR Thumb need to be enabled
    ldr     r4, =0x01000000
    str     r4, [r0, #28]
    // Save func as entry for task
    str     r1, [r0, #24]

    // Save all Rs
    mov     r4, #0
    mov     r1, #0
    strd    r4, r1, [r0, #16]   // LR, R12
    strd    r4, r1, [r0, #8]   // R3, R2
    strd    r2, r4, [r0, #0]   // R1, R0 (arg)

    tst     r3, r3
        beq     .SkipExtrasAdd

    sub     r0, r0, #32
    strd    r1, r4, [r0, #24]   // R10, R11
    strd    r1, r4, [r0, #16]   // R8, R9
    strd    r1, r4, [r0, #8]    // R6, R7
    strd    r1, r4, [r0, #0]    // R4, R5
.SkipExtrasAdd:
    // ...and FPU registers need to be saved

    // and return r0 as stack_ptr
    pop     {r4}
    bx      lr

.type       Platform_ChangeCurrentContextPointer, %function
.global     Platform_ChangeCurrentContextPointer
Platform_ChangeCurrentContextPointer: // (void *new_ptr)
    msr     psp, r0

    bx      lr