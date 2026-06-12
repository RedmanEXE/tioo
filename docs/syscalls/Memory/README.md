# Memory

`Memory_` category contains functions to manage memory for programs and tasks. It includes allocation and free features.

## Summary

| Public functions                    | Short description                                        |
|-------------------------------------|----------------------------------------------------------|
| [Memory_Allocate](#memory_allocate) | Allocates memory for the task, that calls this function. |
| [Memory_Free](#memory_free)         | Frees a previously allocated block of memory.            |

## Public functions

### Memory_Allocate
```c++
void *Memory_Allocate(uint32_t bytes_len);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Allocates memory for task, that calls this function.

| Parameters | Description                                    |
|------------|------------------------------------------------|
| bytes_len  | `uint32_t`: required size for allocated block. |

| Returns   | Description                          |
|-----------|--------------------------------------|
| `void *`  | Pointer to begin of allocated block. |

### Memory_Free
```c++
void Memory_Free(void *block);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Frees early allocated block of memory.

| Parameters | Description                                     |
|------------|-------------------------------------------------|
| block      | `void *`: block address, that need to be freed. |
