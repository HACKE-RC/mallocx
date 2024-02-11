#include "malloc.hpp"
#include <iostream>
#include <array>

std::array<head*, POOL_ARRAY_SIZE>      poolArrayLevel1;  // 4KB blocks
std::array<head*, POOL_ARRAY_SIZE * 2>  poolArrayLevel2;  // 2KB blocks
std::array<head*, POOL_ARRAY_SIZE * 4>  poolArrayLevel3;  // 1KB blocks
std::array<head*, POOL_ARRAY_SIZE * 8>  poolArrayLevel4;  // 512B blocks
std::array<head*, POOL_ARRAY_SIZE * 16> poolArrayLevel5;  // 128B blocks
std::array<head*, POOL_ARRAY_SIZE * 32> poolArrayLevel6;  // 64B blocks
std::array<head*, POOL_ARRAY_SIZE * 64> poolArrayLevel7;  // 32B blocks

std::array<head*, LEVELS> poolArrays;

void init(){
    auto *memoryPool = (head*)(std::malloc(POOL_SIZE));
    poolArrayLevel1 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE>*>(memoryPool);
    // poolArrayLevel2 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 2>*>(memoryPool);
    // poolArrayLevel3 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 4>*>(memoryPool);
    // poolArrayLevel4 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 8>*>(memoryPool);
    // poolArrayLevel5 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 16>*>(memoryPool);
    // poolArrayLevel6 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 32>*>(memoryPool);
    // poolArrayLevel7 = *reinterpret_cast<std::array<head*, POOL_ARRAY_SIZE * 64>*>(memoryPool);

    poolArrays[0] = reinterpret_cast<head*>(poolArrayLevel1.data());
    poolArrays[1] = reinterpret_cast<head*>(poolArrayLevel2.data());
    poolArrays[2] = reinterpret_cast<head*>(poolArrayLevel3.data());
    poolArrays[3] = reinterpret_cast<head*>(poolArrayLevel4.data());
    poolArrays[4] = reinterpret_cast<head*>(poolArrayLevel5.data());
    poolArrays[5] = reinterpret_cast<head*>(poolArrayLevel6.data());
    poolArrays[6] = reinterpret_cast<head*>(poolArrayLevel7.data());

    for (int i = 0; i < LEVELS; i++) {
        auto poolArray = poolArrays[i];
        for (int j = 0; j < (sizes[i]); j++) {
            if (j == 0) {
                poolArray->previous = nullptr;
            }
            else{
               poolArray->previous = (poolArray - PAGE);
            }

            poolArray->next = (poolArray + PAGE);
            poolArray->level = i;
            poolArray->status = unused;
            poolArray = poolArray + PAGE;
        }
    }
}