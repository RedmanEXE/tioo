# Semaphore 
**implements [`Synchronizer`](/docs/syscalls/Synchronizer/README.md)**

`Semaphore_` subcategory implements some functions from synchronizers "interface". Basic counting semaphore.

## Summary

| Public functions                                  | Short description               |
|---------------------------------------------------|---------------------------------|
| [Semaphore_CreateObject](#Semaphore_CreateObject) | Creates a new semaphore object. |

| Interface functions (private)                         | Short description                       |
|-------------------------------------------------------|-----------------------------------------|
| [Semaphore_GetResource](#Semaphore_GetResource)       | Tries to get resource from the mutex.   |
| [Semaphore_ReturnResource](#Semaphore_ReturnResource) | Returns the resource back to the mutex. |

## Public functions

### Semaphore_CreateObject
```c++
uint16_t Semaphore_CreateObject(uint8_t max_count);
```

- **Added** in `1.0.0`
- Creates a new semaphore object.

| Parameters | Description                                                                      |
|------------|----------------------------------------------------------------------------------|
| max_count  | `uint8_t`: The maximum number of tasks that can use the resource simultaneously. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `uint16_t`          | ID of the created semaphore.                                                                     |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

## Interface functions (private)

### Semaphore_GetResource
```c++
int32_t Semaphore_GetResource(uint16_t syncer_id, int32_t timeout);
```

- **Added** in `1.0.0`
- Tries to get resource from the semaphore. If semaphore don't have any free slot, task, that called this function, will be kicked to sleep.

| Parameters | Description                                                                                                                              |
|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| syncer_id  | `uint16_t`: ID of the mutex, that need to be used.                                                                                       |
| timeout    | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", all other values kicks the task to sleep permanently. |

| Returns             | Description                                                                                                                         |
|---------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| `int32_t`           | Resource getting state. `1` - if resource used successfully, `0` - if "sleep alarm" countdown has ended and resource is still busy. |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error.                                    |

### Semaphore_ReturnResource
```c++
void Semaphore_ReturnResource(uint16_t syncer_id);
```

- **Added** in `1.0.0`
- Returns the resource back to the semaphore. Any task can return resource, even if it doesn't use it.

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |
