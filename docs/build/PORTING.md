# How to port kernel for another CPU architecture?

Kernel porting is a very complex task. It requires a good understanding of the CPU architecture and some experience with assembly languages.\
But if low-level programming is easy-peasy for you, let's continue!

## Prerequirements for CPU

- Your CPU must have at least one internal timer (f.e., systimer on ARMv7 architecture).
  > [!IMPORTANT] If your CPU doesn't have any timers, you can use timer, which included with your MCU, 
  > but this solution will not work on any other MCU with this CPU.
- Recommended, but isn't required: NVIC or any other interruptions priority system.
- For now, kernel can use only one core. Note this on multicore systems.

## General rules

All architecture-dependent code/functions/something-else must be placed into architecture directories!\
Select architecture name for your port and remember it as `$ARCH_DIR`.

## List of functions/files to port

To create a port, you must write some architecture-dependent functions/files:
- `boot/$ARCH_DIR/`:
  - `startup.S/Platform_ResetHandler()` - entry function for CPU.\
    This function must set up all required registers (like stack pointer, f.e.) and call `Kernel_EntryPoint()` kernel function.
  - `vectors.c` - interrupt vectors table.\
    If CPU supports IVT, you can specify it here.
- `cmake/$ARCH_DIR/`:
  - `toolchain.cmake` - mini-script to specify tools, that will be used on build.
- `peripherals/`:
  - `ints/$ARCH_DIR/controller.S/Platform_InterruptionSetPriority(uint8_t int_idx, uint8_t priority)` - NVIC priority setup.\
    If your CPU doesn't support interruptions priority, leave it blank.
  - `systimer/$ARCH_DIR/systimer.S/Platform_SysTimerSetup(uint32_t reload_timer)` - system timer setup.\
    System timer is used to switch tasks for multitasking. `reload_timer` is in MCU ticks.
- `syscalls/$ARCH_DIR/`:
  - `syscall_handler.S/Platform_SCHandler()` - handler for syscalls.\
    This function must save all required registers and call `Kernel_Syscalls(arg0, arg1, arg2, arg3, func_idx)` kernel function.\
    After returning from `Kernel_Syscalls`, the function must correctly complete the syscall!
- `tasks/$ARCH_DIR/`:
  - `context.S/Platform_CreateTaskContext(void *stack_ptr, void *(* func)(void *), void *arg, uint32_t create_with_extras)` - function, that creates task context.\
    Function must create task context on `stack_ptr` address.\
    `func` - address of the entry function. `arg` - argument of this function.\
    `create_with_extras` specifies type of the stack frame: `0` - create context only with registers, which saved automatically by CPU, when interrupt occurred. `1` - full context.
  - `context.S/Platform_ChangeCurrentContextPointer(void *new_ptr)` - function, that just changes current program stack pointer to `new_ptr` value.
  - `context.S/Platform_GetArgumentValueFromContext(void *stack_ptr, uint32_t index)` - returns value from task's context.\
    Context guarantied to be full!
  - `context.S/Platform_PutReturnValueIntoContext(void *stack_ptr, uint32_t result)` - writes value into task's context.\
    Context guarantied to be full!
  - `manager.S/Platform_PendSVHandler()` - handler for current task context change.\
    This function must call `void *TasksManager_Switch(void *sp_to_save)` kernel function. This action changes current task in manager.
  - `manager.S/Platform_ScheduleTaskSwitch()` - function, which called by system timer handler.\
    Switches task or sets task switch flag.