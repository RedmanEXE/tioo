.thumb
.syntax unified

// Before PendSV handling core does:
// - Pushes xPSR
// - Pushes PC, LR
// - Pushes R12, R3, R2, R1, R0
// - Pushes S0-S15 and FPSCR, if FPU in use

.equ        ICSR_ADDR, 0xE000ED04

.type       Platform_PendSVHandler, %function
.global     Platform_PendSVHandler
Platform_PendSVHandler: // aka Platform_ContextSwitch
    // We need to save:
    // - R4-R11
    // - S16-S31, if FPU in use
    mrs     r0, psp
    stmdb   r0!, {r4-r11}
    // vstmdb  r0!, {s16-s31}

    // Then call switcher and give them stack pointer
    // to save into Task structure
    push    {lr}
    bl      TasksManager_Switch
    pop     {lr}

    // Restoring another-task(R) context
    // vldmia  r0!, {s16-s31}
    ldmia   r0!, {r4-r11}
    msr     psp, r0

    bx      lr

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

.type       Platform_ScheduleTaskSwitch, %function
.global     Platform_ScheduleTaskSwitch
Platform_ScheduleTaskSwitch: // ()
    // Enable PendSV flag in ICSR
    ldr     r0, =ICSR_ADDR
    ldr     r1, [r0]
    orr     r1, r1, (1 << 28)
    str     r1, [r0]

    // Instruction Synchronization Barrier
    isb
    bx      lr
