.thumb
.syntax unified

.type Platform_SVCHandler, %function
.global Platform_SVCHandler
Platform_SVCHandler:
    tst     lr, #4
    ite     eq
    mrseq   r0, msp
    mrsne   r0, psp

    b       Kernel_Syscalls