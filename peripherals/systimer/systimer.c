#include "systimer.h"

#include <stdint.h>
#include <settings.h>

extern void Platform_SysTimerSetup(uint32_t reload_timer);

void SystemTimer_InitializeForTaskSwitching()
{
    Platform_SysTimerSetup(PLATFORM_SYSTIMER_TIMING_TICK);
}