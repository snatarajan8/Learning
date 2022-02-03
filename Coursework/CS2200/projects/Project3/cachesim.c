#include "cachesim.h"

#define TRUE 1
#define FALSE 0

/**
 * The stuct that you may use to store the metadata for each block in the L1 and L2 caches
 */
typedef struct block_t {
    uint64_t tag; // The tag stored in that block
    uint8_t valid; // Valid bit
    uint8_t dirty; // Dirty bit

    /**************** TODO ******************/

    /*
        Add another variable here to perform the LRU replacement. Look into using a counter
        variable that will keep track of the oldest block in a set
    */


} block;


/**
 * A struct for storing the configuration of both the L1 and L2 caches as passed in the
 * cache_init function. All values represent number of bits. You may add any parameters
 * here, however I strongly suggest not removing anything from the config struct
 */
typedef struct config_t {
    uint64_t C1; /* Size of cache L1 */
    uint64_t C2; /* Size of cache L2 */
    uint64_t S; /* Set associativity of L2 */
    uint64_t B; /* Block size of both caches */
} config;


/****** Do not modify the below function headers ******/
static uint64_t get_tag(uint64_t address, uint64_t C, uint64_t B, uint64_t S);
static uint64_t get_index(uint64_t address, uint64_t C, uint64_t B, uint64_t S);
static uint64_t convert_tag(uint64_t tag, uint64_t index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S);
static uint64_t convert_index(uint64_t tag, uint64_t index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S);
static uint64_t convert_tag_l1(uint64_t l2_tag, uint64_t l2_index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S);
static uint64_t convert_index_l1(uint64_t l2_tag, uint64_t l2_index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S);

/****** You may add Globals and other function headers that you may need below this line ******/





/**
 * Subroutine for initializing your cache with the passed in arguments.
 * You may initialize any globals you might need in this subroutine
 *
 * @param C1 The total size of your L1 cache is 2^C1 bytes
 * @param C2 The tatal size of your L2 cache is 2^C2 bytes
 * @param S The total number of blocks in a line/set of your L2 cache are 2^S
 * @param B The size of your blocks is 2^B bytes
 */
void cache_init(uint64_t C1, uint64_t C2, uint64_t S, uint64_t B)
{
    /* 
        Initialize the caches here. I strongly suggest using arrays for representing
        meta data stored in the caches. The block_t struct given above maybe useful
    */

    /**************** TODO ******************/
}

/**
 * Subroutine that simulates one cache event at a time.
 * @param rw The type of access, READ or WRITE
 * @param address The address that is being accessed
 * @param stats The struct that you are supposed to store the stats in
 */
void cache_access (char rw, uint64_t address, struct cache_stats_t *stats)
{
    /* 
        Suggested approach:
            -> Find the L1 tag and index of the address that is being passed in to the function
            -> Check if there is a hit in the L1 cache
            -> If L1 misses, check the L2 cache for a hit (Hint: If L2 hits, update L1 with new values)
            -> If L2 misses, need to get values from memory, and update L2 and L1 caches
            
            * We will leave it upto you to decide what must be updated and when
     */

    /**************** TODO ******************/

    
}

/**
 * Subroutine for freeing up memory, and performing any final calculations before the statistics
 * are outputed by the driver
 */
void cache_cleanup (struct cache_stats_t *stats)
{
    /*
        Make sure to free up all the memory you malloc'ed here. To check if you have freed up the
        the memory, run valgrind. For more information, google how to use valgrind.
    */

    /**************** TODO ******************/
}

/**
 * Subroutine to compute the Tag of a given address based on the parameters passed in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache in bits (i.e. Size of cache is 2^C)
 * @param B The size of the cache block in bits (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache in bits (i.e. Set-Associativity is 2^S)
 * 
 * @return The computed tag
 */
static uint64_t get_tag(uint64_t address, uint64_t C, uint64_t B, uint64_t S)
{
    /**************** TODO ******************/
    return 0;
}

/**
 * Subroutine to compute the Index of a given address based on the parameters passed in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache in bits (i.e. Size of cache is 2^C)
 * @param B The size of the cache block in bits (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache in bits (i.e. Set-Associativity is 2^S)
 *
 * @return The computed index
 */
static uint64_t get_index(uint64_t address, uint64_t C, uint64_t B, uint64_t S)
{
    /**************** TODO ******************/
    return 0;
}


/**** DO NOT MODIFY CODE BELOW THIS LINE UNLESS YOU ARE ABSOLUTELY SURE OF WHAT YOU ARE DOING ****/

/*
    Note:   The below functions will be useful in converting the L1 tag and index into corresponding L2
            tag and index. These should be used when you are evicitng a block from the L1 cache, and
            you need to update the block in L2 cache that corresponds to the evicted block.

            The newly added functions will be useful for converting L2 indecies ang tags into the corresponding
            L1 index and tags. Make sure to understand how they are working.
*/

/**
 * This function converts the tag stored in an L1 block and the index of that L1 block into corresponding
 * tag of the L2 block
 *
 * @param tag The tag that needs to be converted (i.e. L1 tag)
 * @param index The index of the L1 cache (i.e. The index from which the tag was found)
 * @param C1 The size of the L1 cache in bits
 * @param C2 The size of the l2 cache in bits
 * @param B The size of the block in bits
 * @param S The set associativity of the L2 cache
 */
static uint64_t convert_tag(uint64_t tag, uint64_t index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S)
{
    uint64_t reconstructed_address = (tag << (C1 - B)) | index;
    return reconstructed_address >> (C2 - B - S);
}

/**
 * This function converts the tag stored in an L1 block and the index of that L1 block into corresponding
 * index of the L2 block
 *
 * @param tag The tag stored in the L1 index
 * @param index The index of the L1 cache (i.e. The index from which the tag was found)
 * @param C1 The size of the L1 cache in bits
 * @param C2 The size of the l2 cache in bits
 * @param B The size of the block in bits
 * @param S The set associativity of the L2 cache
 */
static uint64_t convert_index(uint64_t tag, uint64_t index, uint64_t C1, uint64_t C2, uint64_t B,  uint64_t S)
{
    // Reconstructed address without the block offset bits
    uint64_t reconstructed_address = (tag << (C1 - B)) | index;
    // Create index mask for L2 without including the block offset bits
    return reconstructed_address & ((1 << (C2 - S - B)) - 1);
}

/**
 * This function converts the tag stored in an L2 block and the index of that L2 block into corresponding
 * tag of the L1 cache
 *
 * @param l2_tag The L2 tag
 * @param l2_index The index of the L2 block
 * @param C1 The size of the L1 cache in bits
 * @param C2 The size of the l2 cache in bits
 * @param B The size of the block in bits
 * @param S The set associativity of the L2 cache
 * @return The L1 tag linked to the L2 index and tag
 */
static uint64_t convert_tag_l1(uint64_t l2_tag, uint64_t l2_index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S) {
    uint64_t reconstructed_address = (l2_tag << (C2 - B - S)) | l2_index;
    return reconstructed_address >> (C1 - B);
}

/**
 * This function converts the tag stored in an L2 block and the index of that L2 block into corresponding
 * index of the L1 block
 *
 * @param l2_tag The L2 tag
 * @param l2_index The index of the L2 block
 * @param C1 The size of the L1 cache in bits
 * @param C2 The size of the l2 cache in bits
 * @param B The size of the block in bits
 * @param S The set associativity of the L2 cache
 * @return The L1 index of the L2 block
 */
static uint64_t convert_index_l1(uint64_t l2_tag, uint64_t l2_index, uint64_t C1, uint64_t C2, uint64_t B, uint64_t S) {
    uint64_t reconstructed_address = (l2_tag << (C2 - B - S)) | l2_index;
    return reconstructed_address & ((1 << (C1 - B)) - 1);
}
