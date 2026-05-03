#include <stdint.h>

#include <syscalls/syscalls.h>
#include <mem/mem.h>

#include <programs/programs.h>
#include <tasks/tasks.h>
#include <ipc/ipc.h>

#include "owners/owners.h"

// ======== DEFAULT SUBROUTINES ========
uint32_t Kernel_Syscalls(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3,
						 uint32_t func_idx);

uint32_t Kernel_Syscalls(
	uint32_t arg0,
	uint32_t arg1,
	uint32_t arg2,
	uint32_t arg3,
	uint32_t func_idx)
{
	((void)func_idx), ((void)arg0), ((void)arg1), ((void)arg2), ((void)arg3);
	if (SCN_CALLS_LENGTH <= func_idx)
		return 0;


	switch (func_idx)
	{
		case SCN_MEMORY_ALLOCATE:
			return (uint32_t)Memory_Allocate(Owner_GetActiveTaskProgramID(), arg0);
		case SCN_MEMORY_FREE:
			Memory_Free(Owner_GetActiveTaskProgramID(), (void *)arg0);
			break;

		case SCN_PROGRAM_ADD_TASK:
			return (uint32_t)Program_AddTask(Owner_GetActiveTaskProgramID(), (void *(*)(void *))arg0, (void *)arg1);
		case SCN_PROGRAM_EXECUTE:
			return (uint32_t)Program_Execute((void *(*)(void *)) arg0, (void *)arg1);
		case SCN_PROGRAM_GET_ID:
			return (uint32_t)Program_GetID();
		case SCN_PROGRAM_TERMINATE:
			return (uint32_t)Program_Terminate(Owner_GetActiveTaskProgramID());

		case SCN_TASK_FREE:
			return (uint32_t)Task_Free((uint16_t)arg0);
		case SCN_TASK_GET_ID:
			return (uint32_t)Task_GetID();
		case SCN_TASK_KICK_INTO_SLEEP:
			return (uint32_t)Task_KickIntoSleep(Owner_GetActiveTaskID(), (int32_t)arg0);
		case SCN_TASK_KILL:
			return (uint32_t)Task_Kill((uint16_t)arg0);
		case SCN_TASK_LAUNCH:
			return (uint32_t)Task_Launch((uint16_t)arg0);

		case SCN_IPC_CABLEGRAM_SEND:
			return (uint32_t)Cablegram_Send((uint16_t)arg0, (Cablegram_Item *)arg1);
		case SCN_IPC_CABLEGRAM_RECEIVE:
			return (uint32_t)Cablegram_Receive(Owner_GetActiveTaskProgramID(), (Cablegram_Item *)arg0);
		case SCN_IPC_CABLEGRAM_WAIT_AND_RECEIVE:
			return (uint32_t)Cablegram_WaitAndReceive(Owner_GetActiveTaskProgramID(), Owner_GetActiveTaskID(), (Cablegram_Item *)arg0, (int32_t)arg1);

		case SCN_SYNCER_MUTEX_CREATE:
			return (uint32_t)Mutex_CreateObject();
		case SCN_SYNCER_SEMAPHORE_CREATE:
			return (uint32_t)Semaphore_CreateObject((uint8_t)arg0);
		case SCN_SYNCER_FREE_OBJECT:
			return (uint32_t)Synchronizer_FreeObject((uint16_t)arg0);
		case SCN_SYNCER_GET_RESOURCE:
			return (uint32_t)Synchronizer_GetResource((uint16_t)arg0, Owner_GetActiveTaskID(), (int32_t)arg1);
		case SCN_SYNCER_RETURN_RESOURCE:
			return (uint32_t)Synchronizer_ReturnResource((uint16_t)arg0, Owner_GetActiveTaskID());

		default:
			break;
	}
	return 0;
}
