#ifndef __KERNEL_MM_
#define __KERNEL_MM_

typedef struct KHEAP_BLOCK_MANAGER {
    struct KHEAP_BLOCK_MANAGER  *next;
    uint32_t                    num_blocks;
    uint32_t                    block_size;
} KHEAP_BLOCK_MANAGER;

void k_init_heap();
KHEAP_BLOCK_MANAGER *kheap_insert_blocks_at_best_fit(uint32_t total_size);
KHEAP_BLOCK_MANAGER *k_heap_add_block_manager(uint32_t block_size, uint32_t num_blocks);
uint8_t k_heap_free_block(uint32_t block_number);
KHEAP_BLOCK_MANAGER *get_best_fit_for_malloc(uint32_t requested_size);
void *k_malloc(uint32_t size);


#endif
