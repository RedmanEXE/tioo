.thumb
.syntax unified

// Before PendSV handling core does:
// - Pushes xPSR
// - Pushes PC, LR
// - Pushes R12, R3, R2, R1, R0
// - Pushes S0-S15 and FPSCR, if FPU in use

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

.type       Platform_ScheduleTaskSwitch, %function
.global     Platform_ScheduleTaskSwitch
Platform_ScheduleTaskSwitch: // ()
    // Enable PendSV flag in ICSR
    ldr     r0, =ICSR_ADDR
    ldr     r1, [r0]
    orr     r1, r1, (1 << 28)
    str     r1, [r0]

    // Data Synchronization Barrier
    dsb
    // Instruction Synchronization Barrier
    isb
    bx      lr