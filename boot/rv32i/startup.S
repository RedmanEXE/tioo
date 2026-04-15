// ON START:
// - Jumps on Platform_ResetHandler

.type       Platform_ResetHandler, %function
.global     Platform_ResetHandler
.align      2
Platform_ResetHandler:
    // Disable MIE (interruptions)
    li      t1, 0x8
    csrs    mstatus, t1

    // Set address for stack
    la      sp, _sdata

    // Set MTVEC (vectors table) address to ISR
    la      t0, _isr_base
    ori     t0, t0, 3
    csrw    mtvec, t0

    // Enable MIE again
    csrc    mstatus, t1

    // Launch kernel
    j       Kernel_EntryPoint
