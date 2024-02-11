#include "malloc.hpp"
#include <iostream>
#include <array>
#include <cstdint>
#include <sys/mman.h>

std::array<head*, POOL_ARRAY_SIZE>      poolArrayLevel1;  // 4KB blocks
std::array<head*, POOL_ARRAY_SIZE * 2>  poolArrayLevel2;  // 2KB blocks
std::array<head*, POOL_ARRAY_SIZE * 4>  poolArrayLevel3;  // 1KB blocks
std::array<head*, POOL_ARRAY_SIZE * 8>  poolArrayLevel4;  // 512B blocks
std::array<head*, POOL_ARRAY_SIZE * 16> poolArrayLevel5;  // 128B blocks
std::array<head*, POOL_ARRAY_SIZE * 32> poolArrayLevel6;  // 64B blocks
std::array<head*, POOL_ARRAY_SIZE * 64> poolArrayLevel7;  // 32B blocks

std::array<head*, LEVELS> poolArrays;
  // poolArrayLevel2 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 2>*>(memoryPool);
    // poolArrayLevel3 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 4>*>(memoryPool);
    // poolArrayLevel4 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 8>*>(memoryPool);
    // poolArrayLevel5 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 16>*>(memoryPool);
    // poolArrayLevel6 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 32>*>(memoryPool);
    // poolArrayLevel7 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 64>*>(memoryPool);
void init(){
    void* memoryPool = malloc(100);
    poolArrayLevel1 = *new(memoryPool) std::array<head*, POOL_ARRAY_SIZE>();
    poolArrays[0] = reinterpret_cast<head*>(poolArrayLevel1.data());
    poolArrays[1] = reinterpret_cast<head*>(poolArrayLevel2.data());
    poolArrays[2] = reinterpret_cast<head*>(poolArrayLevel3.data());
    poolArrays[3] = reinterpret_cast<head*>(poolArrayLevel4.data());
    poolArrays[4] = reinterpret_cast<head*>(poolArrayLevel5.data());
    poolArrays[5] = reinterpret_cast<head*>(poolArrayLevel6.data());
    poolArrays[6] = reinterpret_cast<head*>(poolArrayLevel7.data());


    int numBlocks = 12*1024*1024 / 4096; // 3072
    // Allocate 12MB block
    void* memory = mmap(nullptr, 12*1024*1024, PROT_READ|PROT_WRITE,
                        MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    // Pointer to first block
    head* current = static_cast<head*>(memory);
    head* rootHead = current;

    // Link all blocks
    for (int i = 0; i < numBlocks-1; i++) {

        // Current block
        current->next =
               reinterpret_cast<head*>(reinterpret_cast<char*>(current) + 4096);
        if (i != 0){
            current->previous = reinterpret_cast<head*>(reinterpret_cast<char*>(current) - 4096);
        }
        // Advance to next block
        current = current->next;
    }

    // Terminate list
    current->next = nullptr;


}