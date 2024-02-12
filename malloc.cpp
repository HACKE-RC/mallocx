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
        currentNode->size = PAGE;
        currentNode->childSize = currentNode->size / 2;
        currentNode = currentNode->next;
    }
}

void* mallocx(size_t size) {
    if (freeList == nullptr) {
        init();
    }

    if (size < 32) {
        size = 32;
    }

    if (PAGE >= size) {
        size--;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size++;
    }

    head* currentNode = freeList;

    while (currentNode->size != size) {
        if ((currentNode->status == allocated) || (size > currentNode->size)){
            if (currentNode->next != nullptr) {
                currentNode = currentNode->next;
            }
            continue;
        }

        currentNode->left = currentNode;
        currentNode->right = (head*)((uintptr_t)currentNode + currentNode->childSize);
        currentNode->size = currentNode->size / 2;
        currentNode->level += 1;
        currentNode->status = unused;
        currentNode->childSize = currentNode->size / 2;

        if ((currentNode->left != nullptr) && (currentNode->left->status == unused)) {
            currentNode = currentNode->left;
        }
        else if ((currentNode->right != nullptr) && (currentNode->right->status == unused)) {
            currentNode = currentNode->right;
        }
        else {
            return nullptr;
        }
    }

    currentNode->status = allocated;
    return currentNode;
}

