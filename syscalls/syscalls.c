//
// Created by REXE on 19.03.26.
//

#include <stdint.h>

#include "syscalls.h"

void Kernel_SyscallHandler(uint32_t *saved_args)
{
    // TODO: Add check for SVC number
    uint32_t syscall_number = saved_args[4];

    switch (syscall_number)
    {

    }
}