.thumb
.syntax     unified

#include    <settings.h>

.equ        SYSTICK_ENABLE, PLATFORM_SYSTICK_CTRL_CLKSOURCE_INT | PLATFORM_SYSTICK_CTRL_TICKINT_ENABLE | PLATFORM_SYSTICK_CTRL_ENABLE

.type       Platform_SysTimerSetup, %function
.global     Platform_SysTimerSetup
Platform_SysTimerSetup: // (uint32_t reload_timer)
    push    {lr}

    ldr     r1, =#0
    ldr     r2, =PLATFORM_SYSTICK_CTRL_REGISTER

    str     r1, [r2, #0]

    str     r0, [r2, #4]
    str     r1, [r2, #8]

    ldr     r0, =PLATFORM_SYSTICK_INTERRUPT_INDEX
    ldr     r1, =0xFF
    push    {r2}
    bl      Platform_InterruptionSetPriority
    pop     {r2}

    ldr     r0, =SYSTICK_ENABLE
    str     r0, [r2, #0]

    pop     {lr}
    bx      lr

.type       Platform_SysTimerHandler, %function
.global     Platform_SysTimerHandler
Platform_SysTimerHandler:
    push    {lr}

    bl      Platform_ScheduleTaskSwitch
    bl      TasksManager_UpdateSleepTimersForTasks

    pop     {lr}
    bx      lr