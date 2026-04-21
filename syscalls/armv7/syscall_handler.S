.thumb
.syntax     unified

.type       Platform_SCHandler, %function
.global     Platform_SCHandler
Platform_SCHandler:
    tst     lr, #4
    ite     eq
        mrseq   r0, msp
        mrsne   r0, psp

    push    {lr, r4, r5}
    mov     r5, r0

    ldr     r0, [r5, #0]    // arg0
    ldr     r1, [r5, #4]    // arg1
    ldr     r2, [r5, #8]    // arg2
    ldr     r3, [r5, #12]   // arg3
    ldr     r4, [r5, #16]   // func_idx
    push    {r4}
    bl      Kernel_Syscalls
    add     sp, sp, #4

    str     r0, [r5, #0]

    pop     {lr, r4, r5}
    bx      lr
