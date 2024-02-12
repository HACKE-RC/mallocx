#ifndef MALLOCX_MALLOC_HPP
#define MALLOCX_MALLOC_HPP
#include <array>
#include <cstdlib>

#define MIN 5
#define LEVELS 7
#define PAGE 4096
#define POOL_SIZE 0xC00000
#define POOL_ARRAY_SIZE 3072

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
    head* left = nullptr;
    head* right = nullptr;
    head* next = nullptr;
    head* previous = nullptr;
    enum flag status = unused;
    short int level{};
};

void init();
void test();

extern std::array<head*, LEVELS> poolArrays;
extern std::array<head*, POOL_ARRAY_SIZE> poolArrayLevel1;      // 4KB blocks

#endif
