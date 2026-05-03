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

| Name                                                                              | Function number | Returns               | Argument 0             | Argument 1           | Argument 2 | Argument 3 | Notes |
|-----------------------------------------------------------------------------------|-----------------|-----------------------|------------------------|----------------------|------------|------------|-------|
| [Memory_Allocate](Memory/README.md#Memory_Allocate)                               | 0x00            | `void *block`         | `uint32_t bytes_len`   |                      |            |            |       |
| [Memory_Free](Memory/README.md#Memory_Free)                                       | 0x01            |                       | `void *block`          |                      |            |            |       |
| [Program_AddTask](Program/README.md#Program_AddTask)                              | 0x02            | `uint16_t task_id`    | `void*(* func)(void*)` | `void *arg`          |            |            |       |
| [Program_Execute](Program/README.md#Program_Execute)                              | 0x03            | `uint16_t program_id` | `void*(* func)(void*)` | `void *arg`          |            |            |       |
| [Program_GetID](Program/README.md#Program_GetID)                                  | 0x04            | `uint16_t program_id` |                        |                      |            |            |       |
| [Program_Terminate](Program/README.md#Program_Terminate)                          | 0x05            |                       | `uint16_t program_id`  |                      |            |            |       |
| [Task_Free](Task/README.md#Task_Free)                                             | 0x06            |                       | `uint16_t task_id`     |                      |            |            |       |
| [Task_GetID](Task/README.md#Task_GetID)                                           | 0x07            | `uint16_t task_id`    |                        |                      |            |            |       |
| [Task_KickIntoSleep](Task/README.md#Task_KickIntoSleep)                           | 0x08            |                       | `int32_t sleep_timer`  |                      |            |            |       |
| [Task_Kill](Task/README.md#Task_Kill)                                             | 0x09            |                       | `uint16_t task_id`     |                      |            |            |       |
| [Task_Launch](Task/README.md#Task_Launch)                                         | 0x0A            |                       | `uint16_t task_id`     |                      |            |            |       |
| [Cablegram_Send](Cablegram/README.md#Cablegram_Send)                              | 0x0B            |                       | `uint16_t receiver_id` | `Cablegram_Item *in` |            |            |       |
| [Cablegram_Receive](Cablegram/README.md#Cablegram_Receive)                        | 0x0C            | `int32_t received`    | `Cablegram_Item *out`  |                      |            |            |       |
| [Cablegram_WaitAndReceive](Cablegram/README.md#Cablegram_WaitAndReceive)          | 0x0D            | `int32_t received`    | `Cablegram_Item *out`  | `int32_t timeout`    |            |            |       |
| [Mutex_CreateObject](Mutex/README.md#Mutex_CreateObject)                          | 0x0E            | `uint16_t syncer_id`  |                        |                      |            |            |       |
| [Semaphore_CreateObject](Semaphore/README.md#Semaphore_CreateObject)              | 0x0F            | `uint16_t syncer_id`  | `uint8_t max_count`    |                      |            |            |       |
| [Synchronizer_FreeObject](Synchronizer/README.md#Synchronizer_FreeObject)         | 0x10            |                       | `uint16_t syncer_id`   |                      |            |            |       |
| [Synchronizer_GetResource](Synchronizer/README.md#Synchronizer_GetResource)       | 0x11            | `int32_t received`    | `uint16_t syncer_id`   | `int32_t timeout`    |            |            |       |
| [Synchronizer_ReturnResource](Synchronizer/README.md#Synchronizer_ReturnResource) | 0x12            |                       | `uint16_t syncer_id`   |                      |            |            |       |

> [!WARNING]
> All functions can return value in `int32_t` bounds.
  If returnable is negative - function returns an error. For error information, see the function description.
