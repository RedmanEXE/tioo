.thumb
.syntax unified

.type       Platform_CreateTaskContext, %function
.global     Platform_CreateTaskContext
Platform_CreateTaskContext: // (void *stack_ptr, void *(* func)(void *), void *arg, void *data, void *heap);
    push    {r4, r5}
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

    // Load heap pointer into R5
    ldr     r5, [sp, #8]

    // Fill up full frame
    sub     r0, r0, #32
    strd    r1, r4, [r0, #24]   // R10, R11
    strd    r1, r4, [r0, #16]   // R8, R9
    strd    r5, r4, [r0, #8]    // R6 (heap), R7
    strd    r1, r3, [r0, #0]    // R4, R5 (data)

    // ...and FPU registers need to be saved

    // and return r0 as stack_ptr
    pop     {r5, r4}
    bx      lr

.type       Platform_ChangeCurrentContextPointer, %function
.global     Platform_ChangeCurrentContextPointer
Platform_ChangeCurrentContextPointer: // (void *new_ptr)
    msr     psp, r0

    bx      lr

.type       Platform_GetArgumentValueFromContext, %function
.global     Platform_GetArgumentValueFromContext
Platform_GetArgumentValueFromContext: // (void *stack_ptr, uint32_t index)
    lsl     r1, 2
    ldr     r0, [r0, r1]

    bx      lr

.type       Platform_PutReturnValueIntoContext, %function
.global     Platform_PutReturnValueIntoContext
Platform_PutReturnValueIntoContext: // (void *stack_ptr, uint32_t result)
    str     r1, [r0, #32]

    bx      lr
