# Task

`Task_` category contains anything about tasks: launch states, functions to manage these states and more than you can dream (somewhere in the future...).

## Summary

| Public functions                          | Short description                                                |
|-------------------------------------------|------------------------------------------------------------------|
| [Task_Free](#Task_Free)                   | Frees task and its stack.                                        |
| [Task_GetID](#Task_GetID)                 | Returns ID of the task, that called this function.               |
| [Task_KickIntoSleep](#Task_KickIntoSleep) | Puts task into "sleep" for the specified number of milliseconds. |
| [Task_Kill](#Task_Kill)                   | Kills task (aka sets task state to `SUSPENDED` value).           |
| [Task_Launch](#Task_Launch)               | Sets task state to `LAUNCHED` value.                             |

## Public functions

### Task_Free
```c++
void Task_Free(uint16_t task_id);
```

- **Added** in `1.0.0`
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

- **Added** in `1.0.0`
- Returns ID of the task, that called this function.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | Task ID.                                                                                         |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Task_KickIntoSleep
```c++
void Task_KickIntoSleep(int32_t sleep_time);
```

- **Added** in `1.0.0`
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

- **Added** in `1.0.0`
- Kills task (aka sets task state to `SUSPENDED` value). To launch it again, use [`Task_Launch`](#Task_Launch) function.\
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

- **Added** in `1.0.0`
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
