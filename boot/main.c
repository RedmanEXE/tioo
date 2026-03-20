#include <syscalls/syscalls.h>

int Kernel_EntryPoint(void)
{
    Service_Register();

    while (1)
    {

    }

    return 0;
}
