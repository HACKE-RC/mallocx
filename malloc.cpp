#include "malloc.hpp"
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
            currentNode->previous = (head*)((uintptr_t)currentNode - PAGE_SIZE);
        }
        else {
            currentNode->previous = nullptr;
        }

        currentNode->next = (head*)((uintptr_t)currentNode + PAGE_SIZE);
        currentNode->left = currentNode->right = nullptr;
        currentNode->status = unused;
        currentNode->size = PAGE_SIZE;
        currentNode->childSize = currentNode->size / 2;
        currentNode = currentNode->next;
    }
}

void* mallocx(size_t size) {
    if (freeList == nullptr) {
        init();
    }

    size = size +  sizeof(head);

    if (size < MINIMUM_ALLOCATION_SIZE) {
        size = MINIMUM_ALLOCATION_SIZE;
    }

// round up to the nearest power of two
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;

    head* currentNode = freeList;

    while (true) {
        if (size > PAGE_SIZE) {
            if ((currentNode->level == 0) && (currentNode->status != allocated) && (currentNode->next != nullptr)) {
                size_t blocksToCoalesce = size / PAGE_SIZE;
                head* tempNode{};
                bool canCoalesce = true;

                if (blocksToCoalesce > MAXIMUM_COALESCE_BLOCKS) {
                    return nullptr;
                }

                tempNode = currentNode->next;
                for (size_t i = 0; i < blocksToCoalesce - 1; i++) {
                    if (tempNode->status == allocated) {
                        canCoalesce = false;
                        break;
                    }
                    tempNode = tempNode->next;
                }

                if (canCoalesce) {
                    return coalesceBlocks(currentNode, blocksToCoalesce);
                }
            }
        }

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
        currentNode->right->next = currentNode->next;
        currentNode = currentNode->left;
    }

    currentNode->status = allocated;
    return (currentNode + sizeof(head));
}

void* coalesceBlocks(head* node, size_t n) {
    head* lastNode{};

    lastNode = node;
    for (int i = 0; i < n - 1; i ++) {
        lastNode = lastNode->next;
    }

    node->next = lastNode->next;
    node->size = PAGE_SIZE * n;
    node->status = allocated;

    return (node + sizeof(head));
}
