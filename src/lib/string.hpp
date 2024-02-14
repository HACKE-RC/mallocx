#ifndef PAGING_CPP_STRING_HPP
#define PAGING_CPP_STRING_HPP
#include <cstdint>
#include <cstddef>

extern void memoryset(void *start, uint8_t value, uint64_t num);
extern void memorycpy(void* destination, const void* source, uint64_t num);
#endif //PAGING_CPP_STRING_HPP
