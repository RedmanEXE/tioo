# Task

`Task_` category contains anything about tasks: launch states, functions to manage these states and more than you can dream (somewhere in the future...).

## Summary

| Public functions                          | Short description                                                |
|-------------------------------------------|------------------------------------------------------------------|
| [Task_Free](#task_free)                   | Frees task and its stack.                                        |
| [Task_GetID](#task_getid)                 | Returns ID of the task, that called this function.               |
| [Task_KickIntoSleep](#task_kickintosleep) | Puts task into "sleep" for the specified number of milliseconds. |
| [Task_Kill](#task_kill)                   | Kills task (aka sets task state to `SUSPENDED` value).           |
| [Task_Launch](#task_launch)               | Sets task state to `LAUNCHED` value.                             |

| Returnable errors                                                         | Short description                                         |
|---------------------------------------------------------------------------|-----------------------------------------------------------|
| [TASK_ERROR_ID_OUT_OF_BOUNDS](#task_error_id_out_of_bounds)               | ID of the unknown task.                                   |
| [TASK_ERROR_THERE_IS_NO_EMPTY_SLOTS](#task_error_there_is_no_empty_slots) | All tasks slots were used.                                |
| [TASK_ERROR_TASK_IS_LAUNCHED](#task_error_task_is_launched)               | Task is launched, but function requires another state.    |
| [TASK_ERROR_TASK_IS_NOT_LAUNCHED](#task_error_task_is_not_launched)       | Task isn't launched, but function requires another state. |

## Public functions

### Task_Free
```c++
void Task_Free(uint16_t task_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Frees task and its stack.
- **Task must not be in `LAUNCHED` or `RUNNING` launch states!**

| Parameters | Description                                        |
|------------|----------------------------------------------------|
| task_id    | `uint16_t`: ID of the task, that need to be freed. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Task_GetID
```c++
uint16_t Task_GetID();
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Returns ID of the task, that called this function.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | Task ID.                                                                                         |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Task_KickIntoSleep
```c++
void Task_KickIntoSleep(int32_t sleep_time);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Puts task into "sleep" for the specified number of milliseconds. The task's launch state will be changed to `BLOCKED` value for some time,\
  and will be restored to the previous value automatically, when the "sleep alarm" countdown ends.
- **Task must be in `LAUNCHED` or `RUNNING` launch states!**

| Parameters | Description                                                                                                     |
|------------|-----------------------------------------------------------------------------------------------------------------|
| sleep_time | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", other values have no effect. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Task_Kill
```c++
void Task_Kill(uint16_t task_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Kills task (aka sets task state to `SUSPENDED` value). To launch it again, use [`Task_Launch`](#yask_launch) function.\
  When killed, task saves their state: if task will be launched again, it continues runtime from previous place in the code.
- **Task must be in `LAUNCHED` or `RUNNING` launch states!**

| Parameters | Description                                           |
|------------|-------------------------------------------------------|
| task_id    | `uint16_t`: ID of the task, that need to be launched. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Task_Launch
```c++
void Task_Launch(uint16_t task_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Sets task state to `LAUNCHED` value. After call, task can be called by the scheduler.\
  If task is "sleeping", this function **will not "wake up" it**.
- **Task must not be in `LAUNCHED` or `RUNNING` launch states!**

| Parameters | Description                                           |
|------------|-------------------------------------------------------|
| task_id    | `uint16_t`: ID of the task, that need to be launched. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

## Returnable errors

### TASK_ERROR_ID_OUT_OF_BOUNDS
```c++
#define TASK_ERROR_ID_OUT_OF_BOUNDS                 (-1)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-1`
- Argument of the function contains ID of the unknown task object.

### TASK_ERROR_THERE_IS_NO_EMPTY_SLOTS
```c++
#define TASK_ERROR_THERE_IS_NO_EMPTY_SLOTS          (-2)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-2`
- There's no free tasks slots in the poll. Try to free a few tasks before another call.

### TASK_ERROR_TASK_IS_LAUNCHED
```c++
#define TASK_ERROR_TASK_IS_LAUNCHED                 (-3)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-3`
- Task is launched, but function requires another state.

### TASK_ERROR_TASK_IS_NOT_LAUNCHED
```c++
#define TASK_ERROR_TASK_IS_NOT_LAUNCHED             (-4)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-4`
- Task isn't launched, but function requires another state.
