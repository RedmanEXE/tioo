# Mutex
**implements [`Synchronizer`](/docs/syscalls/Synchronizer/README.md)**

`Mutex_` subcategory implements some functions from synchronizers "interface". Basic mutex.

## Summary

| Public functions                          | Short description           |
|-------------------------------------------|-----------------------------|
| [Mutex_CreateObject](#mutex_createobject) | Creates a new mutex object. |

| Interface functions (private)                 | Short description                       |
|-----------------------------------------------|-----------------------------------------|
| [Mutex_GetResource](#mutex_getresource)       | Tries to get resource from the mutex.   |
| [Mutex_ReturnResource](#mutex_returnresource) | Returns the resource back to the mutex. |

## Public functions

### Mutex_CreateObject
```c++
uint16_t Mutex_CreateObject();
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Creates a new mutex object.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | ID of the created mutex.                                                                         |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

## Interface functions (private)

### Mutex_GetResource
```c++
int32_t Mutex_GetResource(uint16_t syncer_id, int32_t timeout);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Tries to get resource from the mutex. If mutex is used by another task, task, that called function, will be kicked to sleep.

| Parameters | Description                                                                                                                              |
|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| syncer_id  | `uint16_t`: ID of the mutex, that need to be used.                                                                                       |
| timeout    | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", all other values kicks the task to sleep permanently. |

| Returns             | Description                                                                                                                         |
|---------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| `int32_t`           | Resource getting state. `1` - if resource used successfully, `0` - if "sleep alarm" countdown has ended and resource is still busy. |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error.                                    |

### Mutex_ReturnResource
```c++
void Mutex_ReturnResource(uint16_t syncer_id);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Returns the resource back to the mutex. If a mutex is used, the resource can only be returned by the task currently using the resource.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |
