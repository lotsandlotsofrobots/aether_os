#include "types.h"
#include "mm.h"

#define HEAP_START_ADDR (KHEAP_BLOCK_MANAGER*)0x40000000

/*typedef struct KHEAP_BLOCK_MANAGER {
    struct KHEAP_BLOCK_MANAGER	*next;
    uint32_t 			num_blocks;
    uint32_t                    block_size;
} KHEAP_BLOCK_MANAGER;*/

KHEAP_BLOCK_MANAGER *heap;

void k_init_heap()
{
    heap = 0;
    //k_heap_add_block(
}

KHEAP_BLOCK_MANAGER *kheap_insert_blocks_at_best_fit(uint32_t total_size)
{
    KHEAP_BLOCK_MANAGER *block = heap;

    // how do we ever get past this?
    // if we only look at heap->next, this will always trigger
    if ( heap == 0 ) 
    {
        heap = HEAP_START_ADDR;
        heap->next = 0;
        return heap;
    }

    // we are going to look for the best fit between two blocks.
    // so, we start pointing between heap - there is no before
    // and after yet, and slack_space is large so if we're looking 
    // for 100 bytes, we might hit on 100000 (<UINT32_MAX), 
    // then 2048 bytes, then 105.
    // In the event heap is only one block, this should still work
    // we will just fall through (block->next will be 0) and
    // we will just append onto the end (heap->next will become block,
    // and block->next will become 0)
    KHEAP_BLOCK_MANAGER *best_fit_before = heap;
    //KHEAP_BLOCK_MANAGER *best_fit_after = 0;
    uint32_t best_slack = UINT32_MAX;

    while ( block->next != 0 )
    {
        // first determine if there are any bytes between
        // these blocks at all...
        uint32_t total_block_size = block->num_blocks * (block->block_size + 1) 
                                    + sizeof(KHEAP_BLOCK_MANAGER);

        // find the difference in these two blocks addresses
        // there may be slack space between them
        uint32_t diff = ((uint32_t)(block - block->next)) - (total_block_size);

        if ( diff < best_slack && diff >= total_size )
        {
            best_fit_before = block;
            //best_fit_after = block->next;
            best_slack = diff;
        }

        block = block->next;
    }

    // okay presumably we have a spot we want to stick this block -
    // at the end of best_fit_before, then BFB->next = this block,
    // and this block->next = BFA.
    // just have to handle the pathalogical case of only one block 
    // located at HEAP_START_ADDR), in this case ..  i think we still do the same thing?
    
    // first recalc bfb's totalsize
    uint32_t bfb_totalsize = best_fit_before->num_blocks 
                    * (best_fit_before->block_size + 1) + sizeof(KHEAP_BLOCK_MANAGER);

    block = best_fit_before + bfb_totalsize;
    block->next = best_fit_before->next;
    best_fit_before->next = block;

    return block;
}

KHEAP_BLOCK_MANAGER *k_heap_add_block_manager(uint32_t block_size, uint32_t num_blocks)
{
    // first we need to calculate how big this is going to be, 
    // including the header, but also with the 'used' U8s at the beginning,
    // plus block_size * num_blocks
    uint32_t total_block_size 
               = num_blocks * (block_size + 1) + sizeof(KHEAP_BLOCK_MANAGER);

    KHEAP_BLOCK_MANAGER *new_block = kheap_insert_blocks_at_best_fit(total_block_size);
    new_block->num_blocks = num_blocks;
    new_block->block_size = block_size;

    uint8_t *data = (uint8_t*) new_block + sizeof(KHEAP_BLOCK_MANAGER);

    for ( uint32_t i = 0; i < block_size; ++i )
        data[i] = 0;

    return new_block;
}

uint8_t k_heap_free_block(uint32_t block_number)
{
    KHEAP_BLOCK_MANAGER *block = heap;
    KHEAP_BLOCK_MANAGER *prev = 0;

    // if we need to delete block 0, either:
    //   - it's the first block and we want heap to now point to next, or
    //   - it's the only block, and pointing heap to block->next points to 0
    if (block_number == 0)
    {
        heap = block->next;
        return 0;
    }

    uint32_t i = 0;
    while ( i < block_number && block != 0 )
    {
        prev = block;
        block = block->next;
    }
    
    if ( i != block_number )
    {
        return 1;  // error, TODO make this flag some big failure, corruption.
    }
    else
    {
        // intentionally lose track of this block
        prev->next = block->next;
    }

    return 0;
}

KHEAP_BLOCK_MANAGER *get_best_fit_for_malloc(uint32_t requested_size)
{
    KHEAP_BLOCK_MANAGER *block = heap;

    // look for a few conditions -
    // 1.  is the block_size of this block manager > size?
    // 2.  is (block_size - size) < best_slack_seen ?
    // 3.  does it have unused blocks we can grab one of ?

    uint32_t lowest_slack_seen = UINT32_MAX;
    KHEAP_BLOCK_MANAGER *best_block = 0;

    while ( block != 0 )
    {
        // does it meet conditions 1 && 2?
        bool it_fits = (block->block_size > requested_size);
        bool its_best = (( block->block_size - requested_size ) < lowest_slack_seen );
        if ( it_fits  && its_best )
        {
            // does it meet condition 3?
            uint8_t *used_block_counter = (uint8_t*)&block[1];
            for ( uint32_t i = 0; i < block->num_blocks; i++ )
            {
                // if there's a free block
                if (used_block_counter[i] == 0)
                {
                    lowest_slack_seen = block->block_size - requested_size;
                    best_block = block;
                }
            }
        }
    }

    return best_block;
}


void *k_malloc(uint32_t size)
{
    // first find a block that can hold the request
    // if there isn't one try to create one
    KHEAP_BLOCK_MANAGER *block = 0;

    // first find a block with subblocks the closest in size
    block = get_best_fit_for_malloc(size);
    
    // get the first available block inside the manager
    uint8_t *used_block_counters = (uint8_t *)&block[1];

    uint32_t i = 0;
    for ( i = 0; i < block->num_blocks; i++ )
    {
        if ( used_block_counters[i] == 0 )
            break;
    }

    // something has gone horribly awry if we hit this
    if ( i >= block->num_blocks )
        return 0;

    // assuming this all went well, return the address of that block
    // after marking it as used
    used_block_counters[i] = 1;
    
    return (void*)(&block[1] + block->num_blocks + ( i * block->block_size ));
}


 


