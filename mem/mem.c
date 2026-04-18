#include <stdint.h>
#include <stddef.h>

#include <mem_routines.h>
#include <mem/mem.h>
#include <settings.h>

// TODO: Move this defines into OwnersManager
// ============== DEFINES ==============
#define NO_OWNER      0
#define KERNEL_OWNER  1

// ============= TYPEDEFS ==============
typedef struct
{
    uint16_t block_num;
    uint16_t owner_id;
    uint16_t permissions;
    uint16_t reserved;
} Memory_Page;

// ======== STATIC SUBROUTINES =========
static uint16_t Memory_FindFirstFreeBlock(uint16_t required_pages);
static void Memory_BlockChangeOwnerID(uint16_t first_page, uint16_t required_pages, uint16_t required_id);
static uint16_t Memory_GetBlockPagesCount(uint16_t requester_id, uint16_t first_page);

// ============ GLOBAL VARS ============
__attribute__((section(".kernel_bss")))
Memory_Page pages[MEM_PAGES_COUNT];

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
            end_of_seq = i + 1;
            break;
        }
    }
    // Why extra space is here?
    // bcz idgf
    return ( 0 != end_of_seq) ? end_of_seq - free_pages : 0;
}

// Counts pages allocated/binded to block
static uint16_t Memory_GetBlockPagesCount(uint16_t requester_id, uint16_t first_page)
{
    uint16_t pages_count = 0, current_page = first_page;

    while (pages[current_page].owner_id == requester_id)
    {
        current_page++;
        pages_count++;
    }

    return pages_count;
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
void *Memory_Allocate(uint16_t requester_id, uint32_t bytes_len)
{
    // FIXME: Memory need to be allocated with 2^n size and on prop address
    uint16_t required_pages = bytes_len / MEM_PAGE_SIZE_IN_BYTES +
        bytes_len % MEM_PAGE_SIZE_IN_BYTES ? 1 : 0;

    uint16_t block_begin_page = Memory_FindFirstFreeBlock(required_pages);

    if (0 == block_begin_page)
        return NULL;

    Memory_BlockChangeOwnerID(block_begin_page, required_pages, requester_id);

    return (void *)(MEM_STACK_TOP_ADDRESS + block_begin_page * MEM_PAGE_SIZE_IN_BYTES);
}

// SVC
//
// Handler:
// id = DetectID()
// Memory_Free(id, args[0])

// Frees early allocated block of memory with specified OwnerID
void Memory_Free(uint16_t requester_id, void *block)
{
    uint16_t i, first_page = ((uint32_t)block - MEM_STACK_TOP_ADDRESS) / MEM_PAGE_SIZE_IN_BYTES;
    // FIXME: Block size counts without <block, only block>=
    // FIXME: There's no check for address bounds
    uint16_t pages_count = Memory_GetBlockPagesCount(requester_id, first_page);

    if (0 == pages_count)
        return;

    for (i = first_page; i < first_page + pages_count; i++)
    {
        pages[i].owner_id = 0;
        pages[i].permissions = 0;
    }
}