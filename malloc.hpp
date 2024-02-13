#ifndef MALLOCX_MALLOC_HPP
#define MALLOCX_MALLOC_HPP
#include <array>
#include <cstdlib>

#define MIN 5
#define LEVELS 7
#define PAGE_SIZE 4096
#define POOL_SIZE 0xC00000
#define POOL_ARRAY_SIZE 3072
#define MINIMUM_ALLOCATION_SIZE 32
#define MAXIMUM_COALESCE_BLOCKS 4


inline int sizes[LEVELS] = {
    POOL_ARRAY_SIZE, POOL_ARRAY_SIZE * 2, POOL_ARRAY_SIZE * 4,
    POOL_ARRAY_SIZE * 8, POOL_ARRAY_SIZE * 16, POOL_ARRAY_SIZE * 32,
    POOL_ARRAY_SIZE * 64
};

enum flag{
    unused,
    allocated
};

struct head{
    head* previous = nullptr;
    head* right = nullptr;
    head* left = nullptr;
    head* next = nullptr;
    flag status = unused;
    size_t childSize = 0;
    size_t size = 0;
    short level = 0;
};

void init();
void* mallocx(size_t size);
void* coalesceBlocks(head* node, size_t n);
#endif
