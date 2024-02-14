#include "string.hpp"

void memoryset(void *start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++)
    {
        *(uint8_t *)((uint64_t)start + i) = value;
    }
}

void memorycpy(void* destination, const void* source, uint64_t num) {
    uint8_t* dest = (uint8_t*)destination;
    const uint8_t* src = (const uint8_t*)source;

    for (uint64_t i = 0; i < num; i++) {
        dest[i] = src[i];
    }
}
