# Cablegram

`Cablegram_` category contains features for programs' messaging. Any program receive CablegramsQueue on creation: something like mailbox.
This queue can be fetched for new cablegrams by [`Cablegram_Receive`](#cablegram_receive).\
Any mailbox have limits and if program tries to send cablegram to the full mailbox, it fails.

## Summary

| Public functions                                      | Short description                                                   |
|-------------------------------------------------------|---------------------------------------------------------------------|
| [Cablegram_Send](#cablegram_send)                     | Sends cablegram to the queue of the another program.                |
| [Cablegram_Receive](#cablegram_receive)               | Checks for new cablegrams in the queue.                             |
| [Cablegram_WaitAndReceive](#cablegram_waitandreceive) | Checks for new cablegrams in the queue, or kicks task to the sleep. |

| Public structures                 | Short description    |
|-----------------------------------|----------------------|
| [Cablegram_Item](#cablegram_item) | Cablegram structure. |

| Returnable errors                                                                     | Short description          |
|---------------------------------------------------------------------------------------|----------------------------|
| [CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS](#cablegram_error_program_id_out_of_bounds) | ID of the unknown program. |
| [CABLEGRAM_ERROR_QUEUE_IS_FULL](#cablegram_error_queue_is_full)                       | Receiver's queue is full.  |

## Public functions

### Cablegram_Send
```c++
void Cablegram_Send(uint16_t receiver_id, Cablegram_Item *in);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Sends cablegram to the queue of the another program. Receiver's queue must have free space or this function fails.

| Parameters  | Description                                                                             |
|-------------|-----------------------------------------------------------------------------------------|
| receiver_id | `uint16_t`: ID of the program, that must receive this cablegram.                        |
| in          | `Cablegram_Item *`: pointer to a [`Cablegram_Item`](#Cablegram_Item) structure to send. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Cablegram_Receive
```c++
int32_t Cablegram_Receive(Cablegram_Item *out);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Checks for new cablegrams in the queue. If there's any cablegrams, it will be copied in `out` argument.

| Parameters | Description                                                                                                              |
|------------|--------------------------------------------------------------------------------------------------------------------------|
| out        | `Cablegram_Item *`: pointer to a [`Cablegram_Item`](#cablegram_item) structure to be filled with the received cablegram. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `int32_t`           | Count of received cablegrams. `0` - if there's no any cablegrams in the queue.                   |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Cablegram_WaitAndReceive
```c++
int32_t Cablegram_WaitAndReceive(Cablegram_Item *out, int32_t timeout);
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Checks for new cablegrams in the queue. If there's any cablegrams, it will be copied in `out` argument.\
  If there's no any cablegrams, task puts in the "sleep" state. To get more information about "sleep" routines, check [`Task_KickIntoSleep`](/docs/syscalls/Task/README.md#task_kickintosleep)

| Parameters | Description                                                                                                                              |
|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| out        | `Cablegram_Item *`: pointer to a [`Cablegram_Item`](#cablegram_item) structure to be filled with the received cablegram.                 |
| timeout    | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", all other values kicks the task to sleep permanently. |

| Returns             | Description                                                                                                  |
|---------------------|--------------------------------------------------------------------------------------------------------------|
| `int32_t`           | Count of received cablegrams. `0` - if "sleep alarm" countdown has ended and there's no cablegrams received. |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error.             |

## Public structures

### Cablegram_Item
```c++
typedef struct
{
    uint16_t sender_id;
    uint16_t type;

    uint32_t data;
} Cablegram_Item;
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Cablegram structure.

| Parameters | Description                                                                             |
|------------|-----------------------------------------------------------------------------------------|
| sender_id  | `uint16_t`: ID of the program, that send this cablegram. Can be used to send responses. |
| type       | `uint16_t`: Type of the cablegram.                                                      |
| data       | `uint32_t`: Data, that's included with cablegram.                                       |

## Returnable errors

### CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS
```c++
#define CABLEGRAM_ERROR_PROGRAM_ID_OUT_OF_BOUNDS    (-1)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-1`
- Argument of the function contains ID of the unknown program.

### CABLEGRAM_ERROR_QUEUE_IS_FULL
```c++
#define CABLEGRAM_ERROR_QUEUE_IS_FULL               (-2)
```

- **Added** in [`1.0.0`](/docs/versions/README.md#100)
- Value: `-2`
- Function cannot be completed successfully, because receiver's cablegrams queue is full.
