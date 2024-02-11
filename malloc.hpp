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

extern std::array<head*, LEVELS> poolArrays;
// extern head* poolArrayLevel1[];
// extern head* poolArrayLevel2[];
// extern head* poolArrayLevel3[];
// extern head* poolArrayLevel4[];
// extern head* poolArrayLevel5[];
// extern head* poolArrayLevel6[];
// extern head* poolArrayLevel7[];

extern std::array<head*, POOL_ARRAY_SIZE> poolArrayLevel1;      // 4KB blocks
extern std::array<head*, POOL_ARRAY_SIZE * 2> poolArrayLevel2;  // 2KB blocks
extern std::array<head*, POOL_ARRAY_SIZE * 4> poolArrayLevel3;  // 1KB blocks
extern std::array<head*, POOL_ARRAY_SIZE * 8> poolArrayLevel4;  // 512B blocks
extern std::array<head*, POOL_ARRAY_SIZE * 16> poolArrayLevel5; // 128B blocks
extern std::array<head*, POOL_ARRAY_SIZE * 32> poolArrayLevel6; // 64B blocks
extern std::array<head*, POOL_ARRAY_SIZE * 64> poolArrayLevel7; // 32B blocks

#endif
