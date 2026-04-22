#include "systimer.h"

#include <stdint.h>

extern void Platform_SysTimerSetup(uint32_t reload_timer);

void SystemTimer_InitializeForTaskSwitching()
{
    Platform_SysTimerSetup(14999);
}