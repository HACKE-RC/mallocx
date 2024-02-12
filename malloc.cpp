#include "malloc.hpp"
#include <iostream>
#include <array>
#include <cstdint>
#include <sys/mman.h>

head* freeList = nullptr;

void init(){
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

    while (true) {
        if ((currentNode->left != nullptr) && (currentNode->left->status == allocated)) {
            if ((currentNode->right != nullptr)){
                if ((currentNode->right->status == unused)) {
                    currentNode = currentNode->right;
                }
                else {
                    currentNode = currentNode->next;
                }
            }
        }
        else if (currentNode->status == allocated) {
            if (currentNode->next != nullptr) {
                currentNode = currentNode->next;
            }
        }

        if (currentNode->size == size) {
            break;
        }

        if ((currentNode->status == allocated) || (size > currentNode->size)){
            if (currentNode->next != nullptr) {
                currentNode = currentNode->next;
            }
            continue;
        }

        currentNode->left = currentNode;
        currentNode->right = (head*)((uintptr_t)currentNode + currentNode->childSize);
        currentNode->status = unused;
        currentNode->size = currentNode->size / 2;
        currentNode->right->size = currentNode->size;
        currentNode = currentNode->left;
    }

    currentNode->status = allocated;
    return currentNode;
}

