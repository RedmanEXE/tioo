# Cablegram

`Cablegram_` category contains features for programs' messaging. Any program receive CablegramsQueue on creation: something like mailbox.
This queue can be fetched for new cablegrams by [`Cablegram_Receive`](#Cablegram_Receive).\
Any mailbox have limits and if program tries send cablegram to the full mailbox, it fails.

## Summary

| Public functions                                      | Short description                                                   |
|-------------------------------------------------------|---------------------------------------------------------------------|
| [Cablegram_Send](#Cablegram_Send)                     | Sends cablegram to the queue of the another program.                |
| [Cablegram_Receive](#Cablegram_Receive)               | Checks for new cablegrams in the queue.                             |
| [Cablegram_WaitAndReceive](#Cablegram_WaitAndReceive) | Checks for new cablegrams in the queue, or kicks task to the sleep. |


## Public functions

### Cablegram_Send
```c++
void Cablegram_Send(uint16_t receiver_id, Cablegram_Item *in);
```

- **Added** in `1.0.0`
- Sends cablegram to the queue of the another program. Receiver's queue must have free space or this function fails.

| Parameters  | Description                                                      |
|-------------|------------------------------------------------------------------|
| receiver_id | `uint16_t`: ID of the program, that must receive this cablegram. |
| in          | `Cablegram_Item *`: pointer to the cablegram for sending.        |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `0`                 |                                                                                                  |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Cablegram_Receive
```c++
int32_t Cablegram_Receive(Cablegram_Item *out);
```

- **Added** in `1.0.0`
- Checks for new cablegrams in the queue. If there's any cablegrams, it will be copied in `out` argument.

| Parameters | Description                                                                                           |
|------------|-------------------------------------------------------------------------------------------------------|
| out        | `Cablegram_Item *`: pointer to a `Cablegram_Item` structure to be filled with the received cablegram. |

| Returns             | Description                                                                                      |
|---------------------|--------------------------------------------------------------------------------------------------|
| `int32_t`           | Count of received cablegrams. `0` - if there's no any cablegrams in the queue.                   |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error. |

### Cablegram_WaitAndReceive
```c++
int32_t Cablegram_WaitAndReceive(Cablegram_Item *out, int32_t timeout);
```

- **Added** in `1.0.0`
- Checks for new cablegrams in the queue. If there's any cablegrams, it will be copied in `out` argument.\
  If there's no any cablegrams, task puts in the "sleep" state. To get more information about "sleep" routines, check [`Task_KickIntoSleep`](/docs/syscalls/Task/README.md#Task_KickIntoSleep)

| Parameters | Description                                                                                                                              |
|------------|------------------------------------------------------------------------------------------------------------------------------------------|
| out        | `Cablegram_Item *`: pointer to a `Cablegram_Item` structure to be filled with the received cablegram.                                    |
| timeout    | `int32_t`: milliseconds value for "sleep alarm". All positive values sets "alarm", all other values kicks the task to sleep permanently. |

| Returns             | Description                                                                                                  |
|---------------------|--------------------------------------------------------------------------------------------------------------|
| `int32_t`           | Count of received cablegrams. `0` - if "sleep alarm" countdown has ended and there's no cablegrams received. |
| If fails: `int32_t` | If function fails, returnable contains negative value and will depend on the cause of the error.             |
