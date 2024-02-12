#include "malloc.hpp"
#include <iostream>
#include <array>
#include <cstdint>
#include <sys/mman.h>

head* freeList = nullptr;

void init(){
   // put poolArrayLevel1 on the mmap'd memory
   // write a function to divide the chunks in case of a memory allocation

    void* memory = mmap(nullptr, 12*1024*1024, PROT_READ|PROT_WRITE,
                        MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (memory == MAP_FAILED) {
        return;
    }
    freeList = (head*)memory;
    head* currentNode = freeList;

    for (int i = 0; i < (sizes[i] - 1); i++) {
        if (i != 0) {
            currentNode->previous = (head*)((uintptr_t)currentNode - PAGE);
        }
        else {
            currentNode->previous = nullptr;
        }

        currentNode->next = (head*)((uintptr_t)currentNode + PAGE);
        currentNode->left = currentNode->right = nullptr;
        currentNode->level = 0;
        currentNode->status = unused;
        currentNode = currentNode->next;
    }

    test();
}

void test() {
    std::cout << "Test" << std::endl;
    // poolArrayLevel1[0]->left = nullptr;
}