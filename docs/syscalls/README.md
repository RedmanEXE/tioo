# SysCalls list

TiOO kernel contains minimum of features, which might be needed in the OS development. This includes next categories:
- [`Cablegram`](Cablegram/README.md): cablegram queues features, like send and receive.
- [`Memory`](Memory/README.md): memory allocation and free. NOTE! It is strongly **not recommended** to allocate memory on program's runtime.
- [`Program`](Program/README.md): anything about programs.
- [`Task`](Task/README.md): anything about tasks and manipulation on them.
- [`Synchronizer`](Synchronizer/README.md): functions for synchronization objects, includes these subcategories:
    - [`Mutex`](Mutex/README.md): mutexes functions.
    - [`Semaphore`](Semaphore/README.md): semaphores functions.

## SysCalls table

| Name                                                                              | Function number | Returns               | Argument 0             | Argument 1           | Argument 2   | Argument 3           | Notes |
|-----------------------------------------------------------------------------------|-----------------|-----------------------|------------------------|----------------------|--------------|----------------------|-------|
| [Memory_Allocate](Memory/README.md#memory_allocate)                               | 0x00            | `void *block`         | `uint32_t bytes_len`   |                      |              |                      |       |
| [Memory_Free](Memory/README.md#memory_free)                                       | 0x01            |                       | `void *block`          |                      |              |                      |       |
| [Program_AddTask](Program/README.md#program_addtask)                              | 0x02            | `uint16_t task_id`    | `void*(* func)(void*)` | `void *arg`          |              |                      |       |
| [Program_Execute](Program/README.md#program_execute)                              | 0x03            | `uint16_t program_id` | `void*(* func)(void*)` | `void *arg`          | `void *data` | `uint32_t heap_size` |       |
| [Program_GetID](Program/README.md#program_getID)                                  | 0x04            | `uint16_t program_id` |                        |                      |              |                      |       |
| [Program_Terminate](Program/README.md#program_terminate)                          | 0x05            |                       |                        |                      |              |                      |       |
| [Task_Free](Task/README.md#task_free)                                             | 0x06            |                       | `uint16_t task_id`     |                      |              |                      |       |
| [Task_GetID](Task/README.md#task_getid)                                           | 0x07            | `uint16_t task_id`    |                        |                      |              |                      |       |
| [Task_KickIntoSleep](Task/README.md#task_kickintosleep)                           | 0x08            |                       | `int32_t sleep_timer`  |                      |              |                      |       |
| [Task_Kill](Task/README.md#task_kill)                                             | 0x09            |                       | `uint16_t task_id`     |                      |              |                      |       |
| [Task_Launch](Task/README.md#task_launch)                                         | 0x0A            |                       | `uint16_t task_id`     |                      |              |                      |       |
| [Cablegram_Send](Cablegram/README.md#cablegram_send)                              | 0x0B            |                       | `uint16_t receiver_id` | `Cablegram_Item *in` |              |                      |       |
| [Cablegram_Receive](Cablegram/README.md#cablegram_receive)                        | 0x0C            | `int32_t received`    | `Cablegram_Item *out`  |                      |              |                      |       |
| [Cablegram_WaitAndReceive](Cablegram/README.md#cablegram_waitandreceive)          | 0x0D            | `int32_t received`    | `Cablegram_Item *out`  | `int32_t timeout`    |              |                      |       |
| [Mutex_CreateObject](Mutex/README.md#mutex_createobject)                          | 0x0E            | `uint16_t syncer_id`  |                        |                      |              |                      |       |
| [Semaphore_CreateObject](Semaphore/README.md#semaphore_createobject)              | 0x0F            | `uint16_t syncer_id`  | `uint8_t max_count`    |                      |              |                      |       |
| [Synchronizer_FreeObject](Synchronizer/README.md#synchronizer_freeobject)         | 0x10            |                       | `uint16_t syncer_id`   |                      |              |                      |       |
| [Synchronizer_GetResource](Synchronizer/README.md#synchronizer_getresource)       | 0x11            | `int32_t received`    | `uint16_t syncer_id`   | `int32_t timeout`    |              |                      |       |
| [Synchronizer_ReturnResource](Synchronizer/README.md#synchronizer_returnresource) | 0x12            |                       | `uint16_t syncer_id`   |                      |              |                      |       |

> [!WARNING]
> All functions can return value in `int32_t` bounds.
  If returnable is negative - function returns an error. For error information, see the function description.
