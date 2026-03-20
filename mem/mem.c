#include <stdint.h>

#include <mem_routines.h>
#include <mem/mem.h>

// TODO: Remove this defines into owners manager
//=====DEFINES=====
#define NO_OWNER      0
#define KERNEL_OWNER  1

//=====TYPEDEFS====
typedef struct
{
    uint16_t block_num;
    uint16_t owner_id;
    uint16_t permissions;

    uint16_t reserved;
} Kernel_MemoryPage;

// ======== STATIC SUBROUTINES =========
static uint16_t Memory_FindFirstFreeBlock(uint16_t required_pages);
static void Memory_BlockChangeOwnerID(uint16_t first_page, uint16_t required_pages, uint16_t required_id);

// ======== DEFAULT SUBROUTINES ========
// NONE

//=====GLOBAL VARS=====
Kernel_MemoryPage pages[MEM_PAGES_COUNT];

// Changes OwnerID for requested amount of pages
static void Memory_BlockChangeOwnerID(uint16_t first_page, uint16_t required_pages, uint16_t required_id)
{
    uint16_t i, page = first_page;
    for (i = 0; i < required_pages; i++, page++)
        pages[page].owner_id = required_id;
}

// Finds first page of sequence with {@code required_pages} pages
// Returns: index of first page in this block
static uint16_t Memory_FindFirstFreeBlock(uint16_t required_pages)
{
    uint16_t i, free_pages = 0, end_of_seq = 0;
    for (i = 0; i < MEM_PAGES_COUNT; i++)
    {
        if (NO_OWNER == pages[i].owner_id)
            free_pages += 1;
        else
            free_pages = 0;

        if (free_pages >= required_pages)
        {
            end_of_seq = i;
            break;
        }
    }
    return ( 0 != end_of_seq) ? end_of_seq - free_pages : 0;
}

// Initializes array of pages
void Memory_Initialize(void)
{
    uint16_t i;
    for (i = 0; i < MEM_PAGES_COUNT; i++)
    {
        pages[i].block_num = i;
        pages[i].owner_id = (MEM_KERNEL_PAGES_COUNT > i) ? KERNEL_OWNER : NO_OWNER;
    }
}

// Allocates memory with req size
void *Memory_Allocate(uint16_t owner_id, uint32_t bytes_len)
{
    uint16_t required_pages = bytes_len / MEM_PAGE_SIZE_IN_BYTES +
        bytes_len % MEM_PAGE_SIZE_IN_BYTES ? 1 : 0;

    uint16_t block_begin_page = Memory_FindFirstFreeBlock(required_pages);

    if (0 == block_begin_page)
        return NULL;

    Memory_BlockChangeOwnerID(block_begin_page, required_pages, owner_id);

    return (void *)(MEM_BASE_ADDRESS + block_begin_page * MEM_PAGE_SIZE_IN_BYTES);
}

// Frees early allocated block of memory
void Memory_Free(uint16_t owner_id, void *block)
{
    (void)(owner_id);
    (void)(block);
}