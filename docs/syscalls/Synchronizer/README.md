# Synchronizer

`Synchronizer_` category contains functions for synchronizers - objects that created especially to synchronize two or more tasks.

## Summary

| Public functions                                            | Short description                                 |
|-------------------------------------------------------------|---------------------------------------------------|
| [Synchronizer_FreeObject](#Synchronizer_FreeObject)         | Frees a previously allocated synchronizer object. |
| [Synchronizer_GetResource](#Synchronizer_GetResource)       | Tries to get resource from the synchronizer.      |
| [Synchronizer_ReturnResource](#Synchronizer_ReturnResource) | Returns the resource back to the synchronizer.    |

| Returnable errors                                                                               | Short description                           |
|-------------------------------------------------------------------------------------------------|---------------------------------------------|
| [SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS](#SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS)                     | ID of the unknown synchronizer.             |
| [SYNCHRONIZER_ERROR_THERE_IS_NO_FREE_SLOTS](#SYNCHRONIZER_ERROR_THERE_IS_NO_FREE_SLOTS)         | All synchronizers slots were used.          |
| [SYNCHRONIZER_ERROR_WRONG_TYPE](#SYNCHRONIZER_ERROR_WRONG_TYPE)                                 | Type of the object is incorrect or unknown. |
| [SYNCHRONIZER_ERROR_OBJECT_IS_ALREADY_FREE](#SYNCHRONIZER_ERROR_OBJECT_IS_ALREADY_FREE)         | Synchronizer is already free.               |
| [SYNCHRONIZER_ERROR_RESOURCE_NOT_USED](#SYNCHRONIZER_ERROR_RESOURCE_NOT_USED)                   | Resource is already unused.                 |
| [SYNCHRONIZER_ERROR_RESOURCE_YOU_ARE_NOT_OWNER](#SYNCHRONIZER_ERROR_RESOURCE_YOU_ARE_NOT_OWNER) | Resource cannot be returned by this task.   |

## Public functions

### Synchronizer_FreeObject
```c++
void Synchronizer_FreeObject(uint16_t syncer_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Frees a previously allocated synchronizer object.

| Parameters | Description                                                         |
|------------|---------------------------------------------------------------------|
| syncer_id  | `uint16_t`: ID of the syncronization object, that need to be freed. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Synchronizer_GetResource
```c++
int32_t Synchronizer_GetResource(uint16_t syncer_id, int32_t timeout);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Tries to get resource from the synchronizer. Every type of the synchronization object implements this function differently.

| Parameters | Description                                                                                                                              |
|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| syncer_id  | `uint16_t`: ID of the syncronization object, that need to be used.                                                                       |
| timeout    | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", all other values kicks the task to sleep permanently. |

| Returns             | Description                                                                                                                         |
|---------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| `int32_t`           | Resource getting state. `1` - if resource used successfully, `0` - if "sleep alarm" countdown has ended and resource is still busy. |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error.                                    |

### Synchronizer_ReturnResource
```c++
void Synchronizer_ReturnResource(uint16_t syncer_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Returns the resource back to the synchronizer. If any other task waits this resource, it will be "awakened".

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

## Returnable errors

### SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS
```c++
#define SYNCHRONIZER_ERROR_ID_OUT_OF_BOUNDS             (-1)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-1`
- Argument of the function contains ID of the unknown synchronizer object.

### PROGRAM_ERROR_THERE_IS_NO_EMPTY_SLOTS
```c++
#define SYNCHRONIZER_ERROR_THERE_IS_NO_FREE_SLOTS       (-2)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-2`
- There's no free synchronizers slots in the poll. Try to free a few synchronizers before another call.

### SYNCHRONIZER_ERROR_WRONG_TYPE
```c++
#define SYNCHRONIZER_ERROR_WRONG_TYPE                   (-3)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-3`
- Type of the object is incorrect or unknown. Check, that correct ID of the object is used.

### SYNCHRONIZER_ERROR_OBJECT_IS_ALREADY_FREE
```c++
#define SYNCHRONIZER_ERROR_OBJECT_IS_ALREADY_FREE       (-4)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-4`
- Synchronizer is already free.

### SYNCHRONIZER_ERROR_RESOURCE_NOT_USED
```c++
#define SYNCHRONIZER_ERROR_RESOURCE_NOT_USED            (-5)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-5`
- Resource is already unused: semaphore counter equals 0, mutex is unlocked, etc.

### SYNCHRONIZER_ERROR_RESOURCE_YOU_ARE_NOT_OWNER
```c++
#define SYNCHRONIZER_ERROR_RESOURCE_YOU_ARE_NOT_OWNER   (-6)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-6`
- Resource cannot be returned by this task. It occurs only when synchronization object locks on specified task and cannot be unlocked by another task.
