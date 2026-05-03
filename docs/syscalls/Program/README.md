# Program

`Program_` category contains functions, created to manipulate programs. Programs are wrappers for tasks (tasks group in other words),
and **MUST** be used in task management, because all tasks want to be bonded with their program.

## Summary

| Public functions                        | Short description                                                      |
|-----------------------------------------|------------------------------------------------------------------------|
| [Program_AddTask](#Program_AddTask)     | Adds a task for program, where this function called.                   |
| [Program_Execute](#Program_Execute)     | Creates a program, and a task for it.                                  |
| [Program_GetID](#Program_GetID)         | Returns ID of the program, that called this function.                  |
| [Program_Terminate](#Program_Terminate) | Terminates a program and frees all resources, that this program holds. |

| Returnable errors                                                               | Short description            |
|---------------------------------------------------------------------------------|------------------------------|
| [PROGRAM_ERROR_ID_OUT_OF_BOUNDS](#PROGRAM_ERROR_ID_OUT_OF_BOUNDS)               | ID of the unknown program.   |
| [PROGRAM_ERROR_THERE_IS_NO_EMPTY_SLOTS](#PROGRAM_ERROR_THERE_IS_NO_EMPTY_SLOTS) | All program slots were used. |

## Public functions

### Program_AddTask
```c++
uint16_t Program_AddTask(void*(* func)(void*), void *arg);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Adds a task for program, where this function called.

| Parameters | Description                                                                                                                                                                           |
|------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| func       | `void*(*)(void*)`: a pointer to the function, that will be executed in new task. Code in this function gets in arguments value from `arg` argument, and returns pointer to any value. |
| arg        | `void *`: a pointer to any value. This pointer is passed as an argument to the new task.                                                                                              |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | Launched task ID. Can be used as an argument in other functions.                                 |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Program_Execute
```c++
uint16_t Program_Execute(void*(* func)(void*), void *arg);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Creates a program, and a task for it, which will be in the `LAUNCHED` state.

| Parameters | Description                                                                                                                                                        |
|------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| func       | `void*(*)(void*)`: a pointer to the main function of program. Code in this function gets in arguments value from `arg` argument, and returns pointer to any value. |
| arg        | `void *`: a pointer to any value. This pointer is passed as an argument to the main function.                                                                      |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | Launched program ID. Can be used as an argument in other functions.                              |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Program_GetID
```c++
uint16_t Program_GetID();
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Returns ID of the program, that called this function.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | Program ID.                                                                                      |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Program_Terminate
```c++
void Program_Terminate();
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Terminates a program and frees all resources, that this program holds. It includes all memory blocks, synchronizers and tasks.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

## Returnable errors

### PROGRAM_ERROR_ID_OUT_OF_BOUNDS
```c++
#define PROGRAM_ERROR_ID_OUT_OF_BOUNDS              (-1)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-1`
- Argument of the function contains ID of the unknown program.

### PROGRAM_ERROR_THERE_IS_NO_EMPTY_SLOTS
```c++
#define PROGRAM_ERROR_THERE_IS_NO_EMPTY_SLOTS       (-2)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-2`
- There's no free program slots in the poll. Try to terminate a few programs before another call.
